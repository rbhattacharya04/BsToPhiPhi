#define NEL(x) (sizeof((x))/sizeof((x)[0]))

#include <set>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <chrono>

#include "TROOT.h"
#include "TSystem.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile.h"
#include "TF1.h"
#include "TLine.h"
#include "TObject.h"
#include "TKey.h"
#include "TChain.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TProfile.h"
#include "TVector3.h"
#include "TStopwatch.h"
#include "TChainElement.h"

#include "AnaUtil.h"
#include "AnalObjects.h"
#include "BsAnalysis.h"

using namespace std;

BsAnalysis::BsAnalysis()
#ifdef TRUE_CPP14
  : chain_(make_unique<TChain>("ttAnalysis/Phase2TriggerInfo")),
#else
  : chain_(unique_ptr<TChain>(new TChain("ttAnalysis/Phase2TriggerInfo"))),
#endif
    eventBr_(new TTStudy::Event()),
    tracksBr_(new vector<TTStudy::Track>()),
    bookedHistograms_(false)
{
  fileList_.clear();
  brList_.clear();
}
bool BsAnalysis::beginJob()
{
  // create vectors to hold branches
  if (studyGen_) genParticleBr_ = new vector<TTStudy::GenParticle>();
  if (checkL1Offline_) offlineTracksBr_ = new vector<TTStudy::Track>();
  nEvents_ = static_cast<long int>(chain_->GetEntriesFast()); 
  if (nEvents_ <= 0) {
    cerr << "******* nEvents = " << nEvents_ << ", returning!" << endl;
    return false;
  }
  cout << " >>> Total events available, nEvents = " << nEvents_ << endl;
  if (maxEvt_ > 0) nEvents_ = min(nEvents_, maxEvt_);
  cout << " >>> Total events to analyze, min(nEvents, maxEvt) = " << nEvents_ << endl;

  // open output files [log and histograms]
  openFiles();
  printJob(fLog_);
  
  bookHistograms();
  setTreeBranches();

  scaleFactor_ = 30000; // 30MHz, used for rate calculation
  cout << setiosflags(ios::fixed);
  cout << setprecision(2);

  return true;
}
void BsAnalysis::endJob() {
  printResults();
  printResults(fLog_);
}
bool BsAnalysis::openFiles() 
{
  fLog_.open(logFile_.c_str(), ios::out);
  if (!fLog_) {
    cerr << "File: " << logFile_ << " could not be opened!" << endl;
    return false;
  }
  fLog_ << setiosflags(ios::fixed);

  // Open the output ROOT file
  TFile* f = TFile::Open(histFile_.c_str(), "RECREATE");
  histf_.reset(move(f));

  return true;
}
// ------------------------
// Close the output file
// ------------------------
void BsAnalysis::closeFiles() 
{
  if (fLog_) {
    fLog_ << resetiosflags(ios::fixed); 
    fLog_.close();
  }

  // and finally 
  saveHistograms();
}
BsAnalysis::~BsAnalysis() {
  if (eventBr_) delete eventBr_;
  if (tracksBr_) delete tracksBr_;
  if (studyGen_ && genParticleBr_) delete genParticleBr_;
  if (offlineTracksBr_) delete offlineTracksBr_;
}
void BsAnalysis::bookHistograms() {
  histf_->cd();
  histf_->mkdir("Main");
  histf_->cd("Main");

  evcountH_      = new TH1D("evcount", "event selection counter", 13, -0.5, 12.5);
  evcount2H_      = new TH1D("evcount2", "event selection counter", 5, -0.5, 4.5);

  nDaughtersH_   = new TH1D("nDaughters"," no of daughters of Bs",10,-0.5,9.5);
  BsDecayModesH_ = new TH1D("BsDecayModes", "various decay modes of Bs",10,-0.5,9.5);

  // Outer Track
  ntrkH_             = new TH1F("ntrk", "No of tracks before any selection", 400, 0, 400);
  ntrk_p_before_acceptanceH_  = new TH1F("ntrk_p_before_acceptance", "No of positive tracks before track quality cut", 400, 0, 400);
  ntrk_n_before_acceptanceH_  = new TH1F("ntrk_n_before_acceptance", "No of negative tracks before track quality cut", 400, 0, 400);
  ntrk_p_after_acceptanceH_  = new TH1F("ntrk_p_after_acceptance", "No of positive tracks before track quality cut", 400, 0, 400);
  ntrk_n_after_acceptanceH_  = new TH1F("ntrk_n_after_acceptance", "No of negative tracks before track quality cut", 400, 0, 400);
  ntrk_p_goodH_      = new TH1F("ntrk_p_good", "No of positive tracks after track quality cut", 400, 0, 400);
  ntrk_n_goodH_      = new TH1F("ntrk_n_good", "No of negative tracks after track quality cut", 400, 0, 400);
  trkVertexZH_       = new TH1F("trkvertexZ","vertex Z of the tracks", 1000, -2, 2);
  trkVertexXYH_      = new TH1F("trkvertexXY","vertex XY of the tracks", 1000, 0, 1);
  trkPtH_            = new TH1F("trkPt","Track Pt", 100, 0, 100);
  trkChi2RedH_       = new TH1F("trkChi2", "Track Chi Square (Reduced)", 200, 0, 20);  
  trkNStubH_         = new TH1F("trkNStub", "Track nStub",11,-0.5,10.5);
  trkNStub_PSH_      = new TH1F("trkNStub_PS"," Track nStub PS", 11,-0.5,10.5);
  dzTrackPairH_      = new TH1F("dzTrackPair", "dz between a pair of tracks", 100, -1, 1);
  dzTrackPair2H_     = new TH1F("dzTrackPair2", "dz between a pair of tracks", 400, -20, 20);
  dzTrackPair3H_     = new TH1F("dzTrackPair3", "dz between a pair of tracks", 400, -20, 20);
  dzTrackPair4H_     = new TH1F("dzTrackPair4", "dz between a pair of tracks", 400, -20, 20);
  dRvsdZ1H_          = new TH2F("dRvsdZ1H","dR vs dZ",400,-20,20,50,0,5) ;
  dRvsdZ2H_          = new TH2F("dRvsdZ2H","dR vs dZ",400,-20,20,50,0,5) ;
  dxyTrackPairH_     = new TH1F("dxyTrackPair", "dxy between a pair of tracks", 100, 0, 1);
  dxyTrackPair2H_    = new TH1F("dxyTrackPair2", "dxy between a pair of tracks", 500, 0, 5);
  dxyTrackPair3H_    = new TH1F("dxyTrackPair3", "dxy between a pair of tracks", 500, 0, 5);
  dxyTrackPair4H_    = new TH1F("dxyTrackPair4", "dxy between a pair of tracks", 500, 0, 5);
  phimass0H_         = new TH1F("phimass0", "Phi candidate mass (all)", 200, 0, 10);
  phimassH_          = new TH1F("phimass", "Phi candidate mass (all)", 100, 0.98, 1.1);
  drTrackPairH_      = new TH1F("drTrackPair", "dr between a pair of tracks", 100, 0, 0.2);
  phiCandPtH_        = new TH1F("phiCandPt", "Phi Candidate Pt", 100, 3, 23);
  nPhiCandH_         = new TH1F("nPhiCand", "No of Phi candidates after candidate selection", 20, -0.5, 19.5);
  dxyPhiPairH_       = new TH1F("dxyPhiPair", "dxy between a pair of Phis after Phi pair found", 100, 0, 0.5);
  dzPhiPairH_        = new TH1F("dzPhiPair", "dz between a pair of Phis after Phi pair found", 100, -1, 1);
  drPhiPairH_        = new TH1F("drPhiPair", "dr between a pair of Phis after Phi pair found", 100, 0, 3);
  drPhi1TrackPairH_  = new TH1F("drPhi1TrackPair", "dr between a pair of tracks after Phi pair found", 100, 0, 0.2);
  drPhi2TrackPairH_  = new TH1F("drPhi2TrackPair", "dr between a pair of tracks after Phi pair found", 100, 0, 0.2);
  bsmass0H_          = new TH1F("bsmass0", "B_s mass after all other selection", 100, 0, 10);
  bsmassH_           = new TH1F("bsmass", "B_s mass after all other selection", 100, 5, 5.8);
  bsPtH_             = new TH1F("bsPt","B_s pT after all other selections",200,0,50);
  bsCandListH_       = new TH1F("bsCandList", "B_s candidates found", 4, -.5, 3.5);
  phi1PtH_           = new TH1F("phi1Pt", "First selected Phi pT after all but mass window cut", 100, 3, 23);
  phi2PtH_           = new TH1F("phi2Pt", "Second selected Phi pT after all but mass window cut", 100, 3, 23);
  phiPtH_            = new TH2D("phiPt", "Phi Pt", 100, 3, 23, 100, 3, 23);
  dxyPhi1TrackPairH_ = new TH1F("dxyPhi1TrackPair", "dxy between a pair of tracks after Phi pair found", 100, 0, 1);
  dzPhi1TrackPairH_  = new TH1F("dzPhi1TrackPair", "dz between a pair of tracks after Phi pair found", 100, -1, 1);
  dxyPhi2TrackPairH_ = new TH1F("dxyPhi2TrackPair", "dxy between a pair of tracks after Phi pair found", 100, 0, 1);
  dzPhi2TrackPairH_  = new TH1F("dzPhi2TrackPair", "dz between a pair of tracks after Phi pair found", 100, -1, 1);

  trk1PtH_           = new TH1F("trk1Pt", "Highest pT kaon pt of the 1st Bs candidate", 100, 0, 20);
  trk2PtH_           = new TH1F("trk2Pt", "Second highest pT kaon pt of the 1st Bs candidate", 100, 0, 20);
  trk3PtH_           = new TH1F("trk3Pt", "Third highest pT kaon pt of the 1st Bs candidate", 100, 0, 20);
  trk4PtH_           = new TH1F("trk4Pt", "Lowest pT kaon pt of the 1st Bs candidate", 100, 0, 20);
  trkPtSumH_         = new TH1F("trkPtSum","Sum of pTs of the 4 tracks consisting a Bs candidate",200,0,50);

  trk1EtaH_          = new TH1F("trk1Eta", "Highest pT kaon eta of the 1st Bs candidate", 100, -3, 3);
  trk2EtaH_          = new TH1F("trk2Eta", "Second highest pT kaon eta of the 1st Bs candidate", 100, -3, 3);
  trk3EtaH_          = new TH1F("trk3Eta", "Third highest pT kaon eta of the 1st Bs candidate", 100, -3, 3);
  trk4EtaH_          = new TH1F("trk4Eta", "Lowest pT kaon eta of the 1st Bs Candidate", 100, -3, 3);

  trk1PhiH_          = new TH1F("trk1Phi", "Highest pT kaon phi of the 1st Bs candidate", 100, -4, 4);
  trk2PhiH_          = new TH1F("trk2Phi", "Second highest pT kaon phi of the 1st Bs candidate", 100, -4, 4);
  trk3PhiH_          = new TH1F("trk3Phi", "Third highest pT kaon phi of the 1st Bs candidate", 100, -4, 4);
  trk4PhiH_          = new TH1F("trk4Phi", "Lowest pT kaon phi of the 1st Bs Candidate", 100, -4, 4);
  
  trk1Chi2H_         = new TH1F("trk1Chi2", "Highest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);
  trk2Chi2H_         = new TH1F("trk2Chi2", "Second highest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);
  trk3Chi2H_         = new TH1F("trk3Chi2", "Third highest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);
  trk4Chi2H_         = new TH1F("trk4Chi2", "Lowest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);

  trk1Chi2RedH_      = new TH1F("trk1Chi2Red", "Highest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);
  trk2Chi2RedH_      = new TH1F("trk2Chi2Red", "Second highest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);
  trk3Chi2RedH_      = new TH1F("trk3Chi2Red", "Third highest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);
  trk4Chi2RedH_      = new TH1F("trk4Chi2Red", "Lowest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);

  trk1nStubH_        = new TH1F("trk1nStub", "Highest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);
  trk2nStubH_        = new TH1F("trk2nStub", "Second highest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);
  trk3nStubH_        = new TH1F("trk3nStub", "Third highest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);
  trk4nStubH_        = new TH1F("trk4nStub", "Lowest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);

  trk1nStubPSH_      = new TH1F("trk1nStubPS", "Highest pT kaon PS nStub of the 1st Bs candidate", 8, -0.5, 7.5);
  trk2nStubPSH_      = new TH1F("trk2nStubPS", "Second highest pT kaon PS nStub of the 1st Bs candidate", 8, -0.5, 7.5);
  trk3nStubPSH_      = new TH1F("trk3nStubPS", "Third highest pT kaon Ps nStub of the 1st Bs candidate", 8, -0.5, 7.5);
  trk4nStubPSH_      = new TH1F("trk4nStubPS", "Lowest pT kaon PS nStub of the 1st Bs candidate", 8, -0.5, 7.5);
 
  drKaonPairH_       = new TH1F("drKaonPair","delta R between the selected kaons", 100, 0, 0.5);
  isol1H_            = new TH1F("isol1", "Isolation of the first selected track", 1000, 0, 5); 
  isol2H_            = new TH1F("isol2", "Isolation of the second selected track", 1000, 0, 5); 
  isol3H_            = new TH1F("isol3", "Isolation of the third selected track", 1000, 0, 5); 
  isol4H_            = new TH1F("isol4", "Isolation of the fourth selected track", 1000, 0, 5);

  Iso_Pt1H_          = new TH2D("Iso_Pt1","Iso vs Pt",100,0,20,100,0,5); 
  Iso_Pt2H_          = new TH2D("Iso_Pt2","Iso vs Pt",100,0,20,100,0,5); 
  Iso_Pt3H_          = new TH2D("Iso_Pt3","Iso vs Pt",100,0,20,100,0,5); 
  Iso_Pt4H_          = new TH2D("Iso_Pt4","Iso vs Pt",100,0,20,100,0,5); 

  isol_phi1H_        = new TH1F("isol_phi1", "Isolation of the first selected track", 1000, 0, 5); 
  isol_phi2H_        = new TH1F("isol_phi2", "Isolation of the second selected track", 1000, 0, 5); 

  Iso_Pt_Phi1H_      = new TH2D("Iso_Pt_Phi1", "Iso vs Pt", 100, 3, 23,100,0,5);
  Iso_Pt_Phi2H_      = new TH2D("Iso_Pt_Phi2", "Iso vs Pt", 100, 3, 23,100,0,5);
  
  isol_BsH_          = new TH1F("isol_Bs", "Isolation of the second selected track", 1000, 0, 5); 
  Iso_Pt_BsH_        = new TH2D("Isol_Pt_Bs", "Iso vs Pt", 100, 8, 28,100,0,5);
  // The rest
  centralH_ = new TH1F("c_ntrk","No of tracks in central region", 100, 0, 400);
  fwdH_     = new TH1F("f_ntrk","No of tracks in forward region", 100, 0, 400);

  anglePlanesH_ = new TH1F("anglePlanes", "Angle between Phi planes", 100, 0, 3.14);

  allDXYPVH_ = new TH1F("allDXYPVH", "dxy of all tracks from primary vertex", 200, 0, 0.02);
  allDZPVH_  = new TH1F("allDZPVH", "dz of all tracks from primary vertex", 200, -0.03, 0.03);
  all2DH_    = new TH2D("all2D","dxy  & dz for all tracks", 200, 0, 0.3, 200, -0.2, 0.2);
  allDXYH_   = new TH1F("allDXYH", "dxy of all tracks beam spot", 200, 0, 0.2);
  allDZH_    = new TH1F("allDZH", "dz of all tracks from beam spot", 200, -2.,2.);

  if (studyGen_) {
    genKPt1H_     = new TH1F("genKPt1", "Gen highest pt kaon pt", 100, 0, 20);
    genKPt2H_     = new TH1F("genKPt2", "Gen second highest pt kaon pt", 100, 0, 20);
    genKPt3H_     = new TH1F("genKPt3", "Gen third highest pt kaon pt", 100, 0, 20);
    genKPt4H_     = new TH1F("genKPt4", "Gen lowest pt kaon pt", 100, 0, 20);  
    genKPtCheckH_ = new TH1F("genKPtCheck", "Gen lowest pt kaon pt", 60, 0, 3);  
    
    genKEta1H_   = new TH1F("genKEta1", "Gen highest pt kaon eta", 100, -3, 3);
    genKEta2H_   = new TH1F("genKEta2", "Gen 2nd highest pt kaon eta", 100, -3, 3);
    genKEta3H_   = new TH1F("genKEta3", "Gen 3rd highest pt kaon eta", 100, -3, 3);
    genKEta4H_   = new TH1F("genKEta4", "Gen lowest pt kaon eta", 100, -3, 3);

    genKPhi1H_   = new TH1F("genKPhi1", "Gen highest pt kaon phi", 100, -4, 4);
    genKPhi2H_   = new TH1F("genKPhi2", "Gen 2nd highest pt kaon phi", 100, -4, 4);
    genKPhi3H_   = new TH1F("genKPhi3", "Gen 3rd highest pt kaon phi", 100, -4, 4);
    genKPhi4H_   = new TH1F("genKPhi4", "Gen lowest pt kaon phi", 100, -4, 4);
    
    genPhiMH_    = new TH1F("genPhiMass","Gen level phi mass",100, 0.8, 1.3);
    genPhiPt1H_  = new TH1F("genPhiPt1", "Highest pt Gen phi pt", 100, 0, 20);
    genPhiPt2H_  = new TH1F("genPhiPt2", "Lowest pt Gen phi pt", 100, 0, 20);
    genPhiEta1H_ = new TH1F("genPhiEta1", "Gen highest pt phi eta", 100, -3, 3);
    genPhiEta2H_ = new TH1F("genPhiEta2", "Gen 2nd highest pt phi eta", 100, -3, 3);
    genPhiPhi1H_ = new TH1F("genPhiPhi1", "Gen highest pt phi phi", 100, -4, 4);
    genPhiPhi2H_ = new TH1F("genPhiPhi2", "Gen 2nd highest pt phi phi", 100, -4, 4);
    
    genDrKPairH_   = new TH1F("genDrKPair", "Gen dr between Kaon pair", 100, 0, 0.5);
    genDrPhiPairH_ = new TH1F("genDrPhiPair", "Gen dr between Phi pair", 100, 0, 3);
    drPhiGenPhiH_  = new TH1F("drPhiGenPhi", "dr between trkphi and genphi", 100, 0, 0.1);
    genBsPtH_      = new TH1F("genBsPt", "Gen Bs pt", 100, 0, 100);
    genBsEtaH_     = new TH1F("genBsEta","Gen Bs eta",100, -3, 3);
    genBsPhiH_     = new TH1F("genBsPhi","Gen Bs phi",100,-4, 4);
    
    phiVXYH_   = new TH1F("phiVXY","VertexXY for the Gen Level Phis",200, 0, 2);
    phiVZH_    = new TH1F("phiVZ","VertexZ for the Gen Level Phis", 400, -20, 20);
    phiVH_    = new TH1F("phiV","Vertex for the Gen Level Phis", 400, -20, 20);
    phiV3DH_    = new TH3F("phiV3D","Vertex for the Gen Level Phis", 200, 0, 20,200,0,20,200,0,20);
    BsVXYH_    = new TH1F("BsVXY","VertexXY for the Gen level Bs", 200, 0, 2);
    BsVZH_     = new TH1F("BsVZ","VertexZ for the Gen Level Bs", 400, -20, 20);
    BsVH_    = new TH1F("BsV","Vertex for the Gen Level Bs", 400, -20, 20);
    BsV3DH_    = new TH3F("BsV3D","Vertex for the Gen Level Bs", 200, 0, 20,200,0,20,200,0,20);
    KaonVXYH_   = new TH1F("KaonVXY","VertexXY for the Gen Level Phis",200, 0, 2);
    KaonVZH_    = new TH1F("KaonVZ","VertexZ for the Gen Level Phis", 400, -20, 20);
    KaonVH_    = new TH1F("KaonV","Vertex for the Gen Level Kaons", 400, -20, 20);
    KaonV3DH_    = new TH3F("KaonV3D","Vertex for the Gen Level Kaons", 200, 0, 20,200,0,20,200,0,20);
    
    mDr_phi   = new TH1F("mDr_phi", "Dr between phis", 100, 0, 0.5);
    mDpt_phi  = new TH1F("mDpt_phi", "Dpt between phis", 100, 0, 5);
    mDeta_phi = new TH1F("mDeta_phi", "Deta between phis", 100, 0, 3);
    mDphi_phi = new TH1F("mDphi_phi", "Dphi between phis", 100, 0, 0.5);
    mDr_K     = new TH1F("mDr_K", "Dr between phis", 100, 0, 0.5);
    mDpt_K    = new TH1F("mDpt_K", "Dpt between phis", 100, 0, 5);
    mDeta_K   = new TH1F("mDeta_K", "Deta between phis", 100, 0, 3);
    mDphi_K   = new TH1F("mDphi_K", "Dphi between phis", 100, 0, 0.5);
    
    drVsMatchedTrkH_ = new TProfile("drVsMatchedTrk", "Profile of matched track versus dR", 100, 0, 0.5, 0, 4);
    
    signalPt1H_  = new TH1F("signalPt1", "Highest pT kaon pt after Phi pair found", 200, 0, 200);
    signalPt2H_  = new TH1F("signalPt2", "Second highest pT kaon pt after Phi pair found", 200, 0, 200);
    signalPt3H_  = new TH1F("signalPt3", "Third highest pT kaon pt after Phi pair found", 200, 0, 200);
    signalPt4H_  = new TH1F("signalPt4", "Lowest pT kaon pt after Phi pair found", 200, 0, 200);
    signalDrH_   = new TH1F("signalDrH_","", 100, 0, 0.05);
    signalPhiMH_ = new TH1F("signalPhiMass", "Signal level phi mass", 100, 0.8, 1.3);
    signalNtrkH_ = new TH1F("nsignal", "No of tracks before any selection", 10, 0, 10);
    signalCentralH_ = new TH1F("c_nsignal", "No of tracks in central region", 10, 0, 10);
    signalFwdH_  = new TH1F("f_nsignal", "No of tracks in forward region", 10, 0, 10);
    signal_VZH_  = new TH1F("signalvertexZ", "vertex Z of the tracks", 100, -10, 10);
    signal_VXYH_ = new TH1F("signalvertexXY", "vertex XY of the tracks", 100, 0, 1);
    signal_chiH_ = new TH1F("signalChi", "Track Chi Square", 100, 0, 50);
    signalDPT_H  = new TH1F("signalDPt", "Delta Pt of matched trackes", 100, 0, 10);
    
    signalDXYPVH_ = new TH1F("signalDXYPVH", "dxy of signal tracks from beam spot", 200, 0, 0.02);
    signalDZPVH_  = new TH1F("signalDZPVH", "dz of signal tracks from beam spot", 200, -0.03, 0.03);
    signal2DH_    = new TH2D("signal2D","dxy dz for signal tracks", 200, 0, 0.3, 200, -0.2, 0.2);
    signalDXYH_   = new TH1F("signalDXYH", "dxy of signal tracks beam spot", 200, 0, 0.2);
    signalDZH_    = new TH1F("signalDZH", "dz of signal tracks from beam spot", 200, -2., 2.);
  }
  if (checkL1Offline_) {
    histf_->cd();
    histf_->mkdir("Offline");
    histf_->cd("Offline");
  
    evcountOfflineH_ = new TH1D("evcountOffline", "event selection counter", 10, -0.5, 9.5);
    //nDaughtersOfflineH_ = new TH1D("nDaughtersOffline"," no of daughters of Bs",10,-0.5,9.5);
    //BsDecayModesOfflineH_ = new TH1D("BsDecayModesOffline", "various decay modes of Bs",10,-0.5,9.5);

    // Outer Track
    ntrkOfflineH_             = new TH1F("ntrkOffline", "No of tracks before any selection", 400, 0, 1000);
    trkVertexZOfflineH_       = new TH1F("trkvertexZOffline","vertex Z of the tracks", 1000, -2, 2);
    trkVertexXYOfflineH_      = new TH1F("trkvertexXYOffline","vertex XY of the tracks", 1000, 0, 1);
    trkPtOfflineH_            = new TH1F("trkPtOffline","Track Pt", 100, 0, 100);
    trkChi2RedOfflineH_       = new TH1F("trkChi2Offline", "Track Chi Square (Reduced)", 200, 0, 20);  
    trkNStubOfflineH_         = new TH1F("trkNStubOffline", "Track nStub",11,-0.5,10.5);
    trkNStub_PSOfflineH_      = new TH1F("trkNStub_PSOffline"," Track nStub PS", 11,-0.5,10.5);
    dzTrackPairOfflineH_      = new TH1F("dzTrackPairOffline", "dz between a pair of tracks", 100, -1, 1);
    dzTrackPair2OfflineH_     = new TH1F("dzTrackPair2Offline", "dz between a pair of tracks", 100, -0.2, 0.2);
    dzTrackPair3OfflineH_     = new TH1F("dzTrackPair3Offline", "dz between a pair of tracks", 100, -5, 5);
    dzTrackPair4OfflineH_     = new TH1F("dzTrackPair4Offline", "dz between a pair of tracks", 100, -5, 5);
    dRvsdZ1OfflineH_          = new TH2F("dRvsdZ1OfflineH","dR vs dZ",400,-20,20,50,0,5) ;
    dRvsdZ2OfflineH_          = new TH2F("dRvsdZ2OfflineH","dR vs dZ",400,-20,20,50,0,5) ;
    dxyTrackPairOfflineH_     = new TH1F("dxyTrackPairOffline", "dxy between a pair of tracks", 100, 0, 1);
    dxyTrackPair2OfflineH_    = new TH1F("dxyTrackPair2Offline", "dxy between a pair of tracks", 100, 0, 0.2);
    phimass0OfflineH_         = new TH1F("phimass0Offline", "Phi candidate mass (all)", 200, 0, 10);
    phimassOfflineH_          = new TH1F("phimassOffline", "Phi candidate mass (all)", 100, 0.98, 1.1);
    drTrackPairOfflineH_      = new TH1F("drTrackPairOffline", "dr between a pair of tracks", 100, 0, 0.2);
    phiCandPtOfflineH_        = new TH1F("phiCandPtOffline", "Phi Candidate Pt", 100, 3, 23);
    nPhiCandOfflineH_         = new TH1F("nPhiCandOffline", "No of Phi candidates after candidate selection", 20, -0.5, 19.5);
    dxyPhiPairOfflineH_       = new TH1F("dxyPhiPairOffline", "dxy between a pair of Phis after Phi pair found", 100, 0, 0.5);
    dzPhiPairOfflineH_        = new TH1F("dzPhiPairOffline", "dz between a pair of Phis after Phi pair found", 100, -1, 1);
    drPhiPairOfflineH_        = new TH1F("drPhiPairOffline", "dr between a pair of Phis after Phi pair found", 100, 0, 3);
    drPhi1TrackPairOfflineH_  = new TH1F("drPhi1TrackPairOffline", "dr between a pair of tracks after Phi pair found", 100, 0, 0.2);
    drPhi2TrackPairOfflineH_  = new TH1F("drPhi2TrackPairOffline", "dr between a pair of tracks after Phi pair found", 100, 0, 0.2);
    bsmass0OfflineH_          = new TH1F("bsmass0Offline", "B_s mass after all other selection", 100, 0, 10);
    bsmassOfflineH_           = new TH1F("bsmassOffline", "B_s mass after all other selection", 100, 5, 5.8);
    bsCandListOfflineH_       = new TH1F("bsCandListOffline", "B_s candidates found", 4, -.5, 3.5);
    phi1PtOfflineH_           = new TH1F("phi1PtOffline", "First selected Phi pT after all but mass window cut", 100, 3, 23);
    phi2PtOfflineH_           = new TH1F("phi2PtOffline", "Second selected Phi pT after all but mass window cut", 100, 3, 23);
    phiPtOfflineH_            = new TH2D("phiPtOffline", "Phi Pt", 100, 3, 23, 100, 3, 23);
    dxyPhi1TrackPairOfflineH_ = new TH1F("dxyPhi1TrackPairOffline", "dxy between a pair of tracks after Phi pair found", 100, 0, 1);
    dzPhi1TrackPairOfflineH_  = new TH1F("dzPhi1TrackPairOffline", "dz between a pair of tracks after Phi pair found", 100, -1, 1);
    dxyPhi2TrackPairOfflineH_ = new TH1F("dxyPhi2TrackPairOffline", "dxy between a pair of tracks after Phi pair found", 100, 0, 1);
    dzPhi2TrackPairOfflineH_  = new TH1F("dzPhi2TrackPairOffline", "dz between a pair of tracks after Phi pair found", 100, -1, 1);

    trk1PtOfflineH_           = new TH1F("trk1PtOffline", "Highest pT kaon pt of the 1st Bs candidate", 100, 0, 20);
    trk2PtOfflineH_           = new TH1F("trk2PtOffline", "Second highest pT kaon pt of the 1st Bs candidate", 100, 0, 20);
    trk3PtOfflineH_           = new TH1F("trk3PtOffline", "Third highest pT kaon pt of the 1st Bs candidate", 100, 0, 20);
    trk4PtOfflineH_           = new TH1F("trk4PtOffline", "Lowest pT kaon pt of the 1st Bs candidate", 100, 0, 20);

    trk1EtaOfflineH_          = new TH1F("trk1EtaOffline", "Highest pT kaon eta of the 1st Bs candidate", 100, -3, 3);
    trk2EtaOfflineH_          = new TH1F("trk2EtaOffline", "Second highest pT kaon eta of the 1st Bs candidate", 100, -3, 3);
    trk3EtaOfflineH_          = new TH1F("trk3EtaOffline", "Third highest pT kaon eta of the 1st Bs candidate", 100, -3, 3);
    trk4EtaOfflineH_          = new TH1F("trk4EtaOffline", "Lowest pT kaon eta of the 1st Bs Candidate", 100, -3, 3);

    trk1PhiOfflineH_          = new TH1F("trk1PhiOffline", "Highest pT kaon phi of the 1st Bs candidate", 100, -4, 4);
    trk2PhiOfflineH_          = new TH1F("trk2PhiOffline", "Second highest pT kaon phi of the 1st Bs candidate", 100, -4, 4);
    trk3PhiOfflineH_          = new TH1F("trk3PhiOffline", "Third highest pT kaon phi of the 1st Bs candidate", 100, -4, 4);
    trk4PhiOfflineH_          = new TH1F("trk4PhiOffline", "Lowest pT kaon phi of the 1st Bs Candidate", 100, -4, 4);

    trk1Chi2OfflineH_         = new TH1F("trk1Chi2Offline", "Highest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);
    trk2Chi2OfflineH_         = new TH1F("trk2Chi2Offline", "Second highest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);
    trk3Chi2OfflineH_         = new TH1F("trk3Chi2Offline", "Third highest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);
    trk4Chi2OfflineH_         = new TH1F("trk4Chi2Offline", "Lowest pT kaon Chi2 of the 1st Bs candidate", 100, 0, 100);

    trk1Chi2RedOfflineH_      = new TH1F("trk1Chi2RedOffline", "Highest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);
    trk2Chi2RedOfflineH_      = new TH1F("trk2Chi2RedOffline", "Second highest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);
    trk3Chi2RedOfflineH_      = new TH1F("trk3Chi2RedOffline", "Third highest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);
    trk4Chi2RedOfflineH_      = new TH1F("trk4Chi2RedOffline", "Lowest pT kaon reduced Chi2 of the 1st Bs candidate", 100, 0, 100);

    trk1nStubOfflineH_        = new TH1F("trk1nStubOffline", "Highest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);
    trk2nStubOfflineH_        = new TH1F("trk2nStubOffline", "Second highest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);
    trk3nStubOfflineH_        = new TH1F("trk3nStubOffline", "Third highest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);
    trk4nStubOfflineH_        = new TH1F("trk4nStubOffline", "Lowest pT kaon nStub of the 1st Bs candidate", 11, -0.5, 10.5);

    trk1nStubPSOfflineH_      = new TH1F("trk1nStubPSOffline", "Highest pT kaon PS nStub of the 1st Bs candidate", 8, -0.5, 7.5);
    trk2nStubPSOfflineH_      = new TH1F("trk2nStubPSOffline", "Second highest pT kaon PS nStub of the 1st Bs candidate", 8, -0.5, 7.5);
    trk3nStubPSOfflineH_      = new TH1F("trk3nStubPSOffline", "Third highest pT kaon Ps nStub of the 1st Bs candidate", 8, -0.5, 7.5);
    trk4nStubPSOfflineH_      = new TH1F("trk4nStubPSOffline", "Lowest pT kaon PS nStub of the 1st Bs candidate", 8, -0.5, 7.5);

    drKaonPairOfflineH_       = new TH1F("drKaonPairOffline","delta R between the selected kaons", 100, 0, 0.5);
    isol1OfflineH_            = new TH1F("isol1Offline", "Isolation of the first selected track", 1000, 0, 5); 
    isol2OfflineH_            = new TH1F("isol2Offline", "Isolation of the second selected track", 1000, 0, 5); 
    isol3OfflineH_            = new TH1F("isol3Offline", "Isolation of the third selected track", 1000, 0, 5); 
    isol4OfflineH_            = new TH1F("isol4Offline", "Isolation of the fourth selected track", 1000, 0, 5); 
    isol_phi1OfflineH_        = new TH1F("isol_phi1Offline", "Isolation of the first selected track", 1000, 0, 5); 
    isol_phi2OfflineH_        = new TH1F("isol_phi2Offline", "Isolation of the second selected track", 1000, 0, 5); 
    isol_BsOfflineH_          = new TH1F("isol_BsOffline", "Isolation of the second selected track", 1000, 0, 5); 
  

    Iso_Pt1OfflineH_          = new TH2D("Iso_Pt1_Offline","Iso vs Pt",100,0,20,100,0,5); 
    Iso_Pt2OfflineH_          = new TH2D("Iso_Pt2_Offline","Iso vs Pt",100,0,20,100,0,5); 
    Iso_Pt3OfflineH_          = new TH2D("Iso_Pt3_Offline","Iso vs Pt",100,0,20,100,0,5); 
    Iso_Pt4OfflineH_          = new TH2D("Iso_Pt4_Offline","Iso vs Pt",100,0,20,100,0,5); 
  
    Iso_Pt_Phi1OfflineH_      = new TH2D("Isol_Pt_Phi1_Offline", "Iso vs Pt", 100, 3, 23,100,0,5);
    Iso_Pt_Phi2OfflineH_      = new TH2D("Isol_Pt_Phi2_Offline", "Iso vs Pt", 100, 3, 23,100,0,5);
  
    Iso_Pt_BsOfflineH_        = new TH2D("Isol_Pt_Bs_Offline", "Iso vs Pt", 100, 8, 28,100,0,5);
  }
  histf_->cd();

  bookedHistograms_ = true;
}
void BsAnalysis::setTreeBranches() {
  if (branchFound("Event")) chain_->SetBranchAddress("Event", &eventBr_);
  if (studyGen_ && branchFound("GenParticle")) chain_->SetBranchAddress("GenParticle", &genParticleBr_);
  if (studyOffline_) {
    if (branchFound("OfflineTrack")) chain_->SetBranchAddress("OfflineTrack", &tracksBr_);
  }
  else {
    if (branchFound("L1Track")) chain_->SetBranchAddress("L1Track", &tracksBr_);
    if (checkL1Offline_ && branchFound("OfflineTrack"))
      chain_->SetBranchAddress("OfflineTrack", &offlineTracksBr_);
  }
}
bool BsAnalysis::branchFound(const string& b)
{
  const TBranch* branch = chain_->GetBranch(b.c_str());  // Get branch pointer                                                                             
  if (branch == nullptr) {
    cout << ">>> SetBranchAddress: <" << b << "> not found!" << endl;
    return false;
  }
  cout << ">>> SetBranchAddress: <" << b << "> found!" << endl;
  brList_.push_back(b);
  return true;
}
int BsAnalysis::getEntry(int lflag) const
{
  int nbytes {0};
  for (const auto& v: brList_) {
    TBranch* branch = chain_->GetBranch(v.c_str());
    if (branch == nullptr) {
      cout << ">>> Branch: " << v << " not found!" << endl;
      continue;
    }
    nbytes += branch->GetEntry(lflag);
  }
  return nbytes;
}
void BsAnalysis::clearEvent() {
  tracksBr_->clear();
  if (offlineTracksBr_) offlineTracksBr_->clear();
  if (studyGen_ && genParticleBr_) genParticleBr_->clear();
}
void BsAnalysis::clearLists() {
  phiCandList_.clear();
  bsList_.clear();
  bsOfflineList_.clear();
}
void BsAnalysis::clearGenLists() {
  genKaonList_.clear();
  genPhiCandList_.clear();
}
void BsAnalysis::eventLoop() {
  double minGenPt = 2.0;
  int nPrint = max(5000L, nEvents_/5000);
  string lastFile;
  ulong nbytes = 0;
  for (long c_entry = 0; c_entry < nEvents_; ++c_entry) {
    // reset
    clearEvent(); // vectors for branches
    clearGenLists(); // other global lists related to Generator level

    long t_entry = chain_->LoadTree(c_entry);
    if (t_entry < 0) break;

#if 0
    auto start = chrono::steady_clock::now();
#endif
    ulong nb = getEntry(t_entry); 
    nbytes += nb;
#if 0
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "GetEntry: " << chrono::duration <double, milli> (diff).count() << " ms" << endl;
#endif

    // Show the status 
    string currentFile(gSystem->BaseName(chain_->GetCurrentFile()->GetName()));

    if (verbosity_ > 2)
      cout << "Entry#: (" << c_entry << ", " << t_entry << ")"
		<< ", # of GenParticles: " << genParticleBr_->size()
		<< ", # of tracks:" << tracksBr_->size() 
		<< endl;
    if (currentFile != lastFile)
      cout << "Tree# " << setw(4) << chain_->GetTreeNumber()
           << " ==> " << chain_->GetCurrentFile()->GetName()
           << " <<< Run# " << setw(8) << eventBr_->run
           << " Event# " << setw(11) << eventBr_->event << " >>>"
           << " Events proc. " << setw(9) << c_entry << "(of " << setw(9) << nEvents_ - 1 << ")"
           << endl;
    lastFile = currentFile;
    
    // Show the status
    if (c_entry%nPrint == 0)
      cout << "Tree# " << setw(4) << chain_->GetTreeNumber()
           << " ==> " << currentFile
           << " <<< Run# " << setw(8) << eventBr_->run
           << " Event# " << setw(11) << eventBr_->event << " >>>"
           << " Events proc. " << setw(8) << c_entry
           << endl;

    histf_->cd();
    histf_->cd("Main");

    evcountH_->Fill(0);  
    evcount2H_->Fill(0);

    //if(studyGen_) checkDecayMode(); 
    // Add a genfilter to select signal events with 2 phi (Kaon pt >= 2GeV)
    if (studyGen_ && !genFilter(minGenPt)) continue;
    evcountH_->Fill(1);
    evcount2H_->Fill(1);
 
    if (studyGen_) {
      readGenParticle();
      fillGenInfo();
      plotGen(tracksBr_);
      plotGenVertex(); 
    }
    
    ntrkH_->Fill(tracksBr_->size());
    if (tracksBr_->size() < 4) continue;
    evcountH_->Fill(2);
    evcount2H_->Fill(2);
   
    // loop over tracks
    int ngood=0;
    int ngoodmatched=0;
    for(size_t it = 0; it < tracksBr_->size(); ++it){
      const TTStudy::Track& trk = tracksBr_->at(it);
      if (fabs(trk.eta) > AnaUtil::cutValue(trkCutMap(), "maxTrkEta")) continue;
      if (trk.pt < AnaUtil::cutValue(trkCutMap(), "minTrkPt")) continue;
      if (applyTrkQuality_ && (trk.chiSquareRed > AnaUtil::cutValue(trkCutMap(), "maxTrkChi2") || 
	    trk.nStub        < AnaUtil::cutValue(trkCutMap(), "minTrkLayers") ||
	    trk.nStub_PS     < AnaUtil::cutValue(trkCutMap(), "minTrkPSLayers"))) continue;
      ngood++;
      TLorentzVector trkv;  
      trkv.SetPtEtaPhiM(trk.pt, trk.eta, trk.phi, ::kmass);
      double pt_diff;
      if(studyGen_) {bool isMatched = isGenKaonMatched(trkv,pt_diff);
	if(isMatched) ngoodmatched++;}
    } 
    

    if(ngood < 4) continue;
    evcountH_->Fill(3);
    evcount2H_->Fill(3);
    if(ngoodmatched >= 4) evcount2H_->Fill(4);
    if (verbosity_ > 1) printTrackProperties(tracksBr_);

    // Outer tracks
    clearLists(); // other global lists related to detector level
    bool selection_status = selectEvent(tracksBr_, bsList_, 3, 0, false);

    bsCandListH_->Fill(bsList_.size());
    if (selection_status) {
      vector<TLorentzVector> kaonList;
      getKaonList(tracksBr_, bsList_[0], kaonList);
      fillKaonInfo(kaonList);
      fillKaonTrackInfo(tracksBr_, bsList_[0]);
      if(verbosity_ > 1){
	std::cout<<" L1 selected tracks"<<std::endl;
	cout << "index       pT      eta      phi       vx       vy      vz" << endl;
	cout << setprecision(3);
	printTrk(tracksBr_,bsList_[0].phi1.indx1);
	printTrk(tracksBr_,bsList_[0].phi1.indx2);
	printTrk(tracksBr_,bsList_[0].phi2.indx1);
	printTrk(tracksBr_,bsList_[0].phi2.indx2);
      }
      //if(studyGen_) plotGenVertex();


      if (checkL1Offline_) {
	histf_->cd();
	histf_->cd("Offline");

	evcountOfflineH_->Fill(0); 
	if (offlineTracksBr_->size() < 4) continue;
	if(verbosity_ > 1){
	  std::cout<<" Offline tracks"<<std::endl;
	  printTrackProperties(offlineTracksBr_);
	}
	evcountOfflineH_->Fill(1);
	bool selected = selectEvent(offlineTracksBr_, bsOfflineList_, 1, 0, checkL1Offline_);
	//if (selected) {
	  /*vector<size_t> tracks_to_exclude_offline;
	  tracks_to_exclude_offline.push_back(bsOfflineList_[0].phi1.indx1);
	  tracks_to_exclude_offline.push_back(bsOfflineList_[0].phi1.indx2);
	  tracks_to_exclude_offline.push_back(bsOfflineList_[0].phi2.indx1);
	  tracks_to_exclude_offline.push_back(bsOfflineList_[0].phi2.indx2);
	  double isol = computeIsolation_v2(offlineTracksBr_, bsOfflineList_[0].phi1.indx1, tracks_to_exclude_offline);  
	  isol1OfflineH_->Fill(isol); 

	  isol = computeIsolation_v2(offlineTracksBr_, bsOfflineList_[0].phi1.indx2, tracks_to_exclude_offline);  
	  isol2OfflineH_->Fill(isol); 

	  isol = computeIsolation_v2(offlineTracksBr_, bsOfflineList_[0].phi2.indx1, tracks_to_exclude_offline);  
	  isol3OfflineH_->Fill(isol); 

	  isol = computeIsolation_v2(offlineTracksBr_, bsOfflineList_[0].phi2.indx2, tracks_to_exclude_offline);  
	  isol4OfflineH_->Fill(isol);*/ 
	//}
      }
    }
  }
}
bool BsAnalysis::selectEvent(const vector<TTStudy::Track>* trackList, 
			     vector<BsInfo>& bsList, 			     
			     int ishift, 
			     int indx, 
			     bool checkL1Offline) 
{
  vector<PhiInfo> phiList;
  findPhiCandidates(trackList, phiList, indx, checkL1Offline);
  ((checkL1Offline) ? nPhiCandOfflineH_->Fill(phiList.size()) : nPhiCandH_->Fill(phiList.size()));
  
  bool event_status = false;
  if (phiList.size() < 2) return event_status;
  
  ((checkL1Offline) ? evcountOfflineH_->Fill(ishift + 1) : evcountH_->Fill(ishift + 1));

  int ecounters[] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (size_t it = 0; it < phiList.size(); ++it) {
    const PhiInfo& info_i = phiList[it];
    double drTrkPhi1 = info_i.dr;
    for (size_t jt = it+1; jt < phiList.size(); ++jt) {
      const PhiInfo& info_j = phiList[jt];

      // The same track should not end up in both the Phi's under consideration
      if (info_i.indx1 == info_j.indx1 ||
	  info_i.indx1 == info_j.indx2 ||    
	  info_i.indx2 == info_j.indx1 || 
	  info_i.indx2 == info_j.indx2) continue;
      ++ecounters[0];

      // The pair of Phi's must come from the same vertex
      double dxy, dz;
      BsAnalysis::calculateDeltaPos(info_i, info_j, dxy, dz);
      if (checkL1Offline) {
	dxyPhiPairOfflineH_->Fill(dxy);
	dzPhiPairOfflineH_->Fill(dz);
      }
      else {
	dxyPhiPairH_->Fill(dxy);
	dzPhiPairH_->Fill(dz);
      }

      if (dxy > AnaUtil::cutValue(bsCutMap(), "maxPhiPairDxy") || 
	  fabs(dz) > AnaUtil::cutValue(bsCutMap(), "maxPhiPairDz")) continue;
      ++ecounters[1];

      const TLorentzVector& phiv1 = info_i.v;
      const TLorentzVector& phiv2 = info_j.v;

      double dr = phiv1.DeltaR(phiv2);
      ((checkL1Offline) ? drPhiPairOfflineH_->Fill(dr) : drPhiPairH_->Fill(dr));

      if (dr < AnaUtil::cutValue(bsCutMap(), "minPhiPairDr") || dr > AnaUtil::cutValue(bsCutMap(), "maxPhiPairDr")) continue;
      ++ecounters[2];

      double drTrkPhi2 = info_j.dr;
      if (checkL1Offline) {
	drPhi1TrackPairOfflineH_->Fill(drTrkPhi1);
	drPhi2TrackPairOfflineH_->Fill(drTrkPhi2);
      }
      else {
	drPhi1TrackPairH_->Fill(drTrkPhi1);
	drPhi2TrackPairH_->Fill(drTrkPhi2);
      }
      if (drTrkPhi1 > AnaUtil::cutValue(bsCutMap(), "maxPhiTrkDr") || drTrkPhi2 > AnaUtil::cutValue(bsCutMap(), "maxPhiTrkDr")) continue;
      ++ecounters[3];

      TLorentzVector bsv = phiv1 + phiv2;
      double bsmass = bsv.M();
      if (checkL1Offline) {
	bsmass0OfflineH_->Fill(bsmass);
	bsmassOfflineH_->Fill(bsmass);
      }
      else {
	bsmass0H_->Fill(bsmass);
	bsmassH_->Fill(bsmass);
      }
      if (bsmass < AnaUtil::cutValue(bsCutMap(), "massLow") || bsmass > AnaUtil::cutValue(bsCutMap(), "massHigh")) continue;
      ++ecounters[4];


      BsInfo bsInfo;
      bsInfo.phi1 = info_i;
      bsInfo.phi2 = info_j;
      bsInfo.bsv = bsv;
      bsInfo.vertexX = 0.5 * (info_i.vertexX + info_j.vertexX);
      bsInfo.vertexY = 0.5 * (info_i.vertexY + info_j.vertexY);
      bsInfo.vertexZ = 0.5 * (info_i.vertexZ + info_j.vertexZ);


      if(!checkL1Offline)  bsPtH_->Fill(bsv.Pt());
      if(bsv.Pt() < 12) continue;
      ++ecounters[5];
      bsList.push_back(bsInfo);
      
      vector<TLorentzVector> kaonList;
      getKaonList(trackList, bsInfo, kaonList);
      double trkPtSum = kaonList[0].Pt()+kaonList[1].Pt()+kaonList[2].Pt()+kaonList[3].Pt();
      trkPtSumH_->Fill(trkPtSum);
      //if(trkPtSum < 12) continue;
      //++ecounters[5];
      

      if (checkL1Offline) {
	dzTrackPair4OfflineH_->Fill(info_i.dz);
	dzTrackPair4OfflineH_->Fill(info_j.dz);
	dRvsdZ2OfflineH_->Fill(info_i.dz,info_i.dr);
	dRvsdZ2OfflineH_->Fill(info_j.dz,info_j.dr);
      }
      else {
	dzTrackPair4H_->Fill(info_i.dz);
	dzTrackPair4H_->Fill(info_j.dz);
	dxyTrackPair4H_->Fill(info_i.dxy);
	dxyTrackPair4H_->Fill(info_j.dxy);
	dRvsdZ2H_->Fill(info_i.dz,info_i.dr);
	dRvsdZ2H_->Fill(info_j.dz,info_j.dr);
      }
      // Selected Phi pT
      if (checkL1Offline) {
	phi1PtOfflineH_->Fill(phiv1.Pt());
	phi2PtOfflineH_->Fill(phiv2.Pt());
	phiPtOfflineH_->Fill(phiv1.Pt(), phiv2.Pt());
      }
      else {
	phi1PtH_->Fill(phiv1.Pt());
	phi2PtH_->Fill(phiv2.Pt());
	phiPtH_->Fill(phiv1.Pt(), phiv2.Pt());
      }

      // Track pair for each Phi
      if (checkL1Offline) {
	dxyPhi1TrackPairOfflineH_->Fill(info_i.dxy);
	dzPhi1TrackPairOfflineH_->Fill(info_i.dz);

	dxyPhi2TrackPairOfflineH_->Fill(info_j.dxy);
	dzPhi2TrackPairOfflineH_->Fill(info_j.dz);
      }
      else {
	dxyPhi1TrackPairH_->Fill(info_i.dxy);
	dzPhi1TrackPairH_->Fill(info_i.dz);

	dxyPhi2TrackPairH_->Fill(info_j.dxy);
	dzPhi2TrackPairH_->Fill(info_j.dz);
      }
     
      //Calculate Isolation
 
      /*vector<size_t> tracks_to_exclude;
      tracks_to_exclude.push_back(bsInfo.phi1.indx1);
      tracks_to_exclude.push_back(bsInfo.phi1.indx2);
      tracks_to_exclude.push_back(bsInfo.phi2.indx1);
      tracks_to_exclude.push_back(bsInfo.phi2.indx2);

      double isol = computeIsolation_v2(tracksBr_, bsInfo.phi1.indx1, tracks_to_exclude);  
      if(checkL1Offline) isol1OfflineH_->Fill(isol); 
      else isol1H_->Fill(isol);

      isol = computeIsolation_v2(tracksBr_, bsInfo.phi1.indx2, tracks_to_exclude);  
      if(checkL1Offline) isol2OfflineH_->Fill(isol); 
      else isol2H_->Fill(isol);

      isol = computeIsolation_v2(tracksBr_, bsInfo.phi2.indx1, tracks_to_exclude);  
      if(checkL1Offline) isol3OfflineH_->Fill(isol); 
      else isol3H_->Fill(isol); 

      isol = computeIsolation_v2(tracksBr_, bsInfo.phi2.indx2, tracks_to_exclude);  
      if(checkL1Offline) isol4OfflineH_->Fill(isol); 
      else isol4H_->Fill(isol);*/

      vector<pair<double,double>> iso_vector;
      computeIsolation(trackList, bsInfo, iso_vector);
      
      if(checkL1Offline){
	isol1OfflineH_->Fill(iso_vector.at(0).first);
        Iso_Pt1OfflineH_->Fill(iso_vector.at(0).second,iso_vector.at(0).first);
      } 
      else{ 
	isol1H_->Fill(iso_vector.at(0).first);
        Iso_Pt1H_->Fill(iso_vector.at(0).second,iso_vector.at(0).first);
      }

      
      if(checkL1Offline){
	isol2OfflineH_->Fill(iso_vector.at(1).first); 
        Iso_Pt2OfflineH_->Fill(iso_vector.at(1).second,iso_vector.at(1).first);
      }
      else{
	isol2H_->Fill(iso_vector.at(1).first);
        Iso_Pt2H_->Fill(iso_vector.at(1).second,iso_vector.at(1).first);
      }
      
      if(checkL1Offline){ 
	isol3OfflineH_->Fill(iso_vector.at(2).first); 
	Iso_Pt3OfflineH_->Fill(iso_vector.at(2).second,iso_vector.at(2).first);
      }
      else{
	isol3H_->Fill(iso_vector.at(2).first);
	Iso_Pt3H_->Fill(iso_vector.at(2).second,iso_vector.at(2).first);
      }
      
      if(checkL1Offline){
	isol4OfflineH_->Fill(iso_vector.at(3).first); 
	Iso_Pt4OfflineH_->Fill(iso_vector.at(3).second,iso_vector.at(3).first);
      }
      else{
	isol4H_->Fill(iso_vector.at(3).first);
	Iso_Pt4H_->Fill(iso_vector.at(3).second,iso_vector.at(3).first);
      }
            
      if(checkL1Offline){
	isol_phi1OfflineH_->Fill(iso_vector.at(4).first);
        Iso_Pt_Phi1OfflineH_->Fill(iso_vector.at(4).second,iso_vector.at(4).first);
      } 
      else{
	isol_phi1H_->Fill(iso_vector.at(4).first);
 	Iso_Pt_Phi1H_->Fill(iso_vector.at(4).second,iso_vector.at(4).first);
      }
      
      if(checkL1Offline){
	isol_phi2OfflineH_->Fill(iso_vector.at(5).first);
	Iso_Pt_Phi2OfflineH_->Fill(iso_vector.at(5).second,iso_vector.at(5).first); 
      }      
      else{
	isol_phi2H_->Fill(iso_vector.at(5).first);
	Iso_Pt_Phi2H_->Fill(iso_vector.at(5).second,iso_vector.at(5).first);     
      }
      
      if(checkL1Offline){
	isol_BsOfflineH_->Fill(iso_vector.at(6).first);
	Iso_Pt_BsOfflineH_->Fill(iso_vector.at(6).second,iso_vector.at(6).first);
      } 
      else{
	isol_BsH_->Fill(iso_vector.at(6).first);
	Iso_Pt_BsH_->Fill(iso_vector.at(6).second,iso_vector.at(6).first);
      }      
      //Isolation Cut on Bs candidate
      //if(iso_vector.at(3).first > AnaUtil::cutValue(isoCutMap(), "maxIso") ) continue;
      if(applyIso_ && iso_vector.at(3).first > AnaUtil::cutValue(isoCutMap(), "maxIso") ) continue;
      ++ecounters[6];

      // Final Gen Match
      if (studyGen_) {
	if (verbosity_) 
	  cout << ">>> B_s # " << bsList.size() << ", mass: " << bsmass << " GeV" << endl;

	int n_match = doTrkGenMatch(kaonList);
	if (n_match == 4){
	  //bsmassH_->Fill(bsmass);
	  ++ecounters[7];
      
	}
      }
    }
  }
  for (size_t i = 0; i < NEL(ecounters); ++i) {
    if (ecounters[i] > 0) {
      ((checkL1Offline) ? evcountOfflineH_->Fill(ishift + 2 + i) : evcountH_->Fill(ishift + 2 + i));
    }
  }
  return (ecounters[5] > 0);
}
void BsAnalysis::findPhiCandidates(const vector<TTStudy::Track>* trackList, 
				   vector<PhiInfo>& phiList, int indx, bool checkL1Offline) 
{  
  // Loop over tracks
  vector<size_t> p_tracks;
  vector<size_t> n_tracks;
  
  vector<size_t> p_tracks_not_good;
  vector<size_t> n_tracks_not_good;

  vector<size_t> p_tracks_before_acceptance;
  vector<size_t> n_tracks_before_acceptance;

  for (size_t it = 0; it < trackList->size(); ++it) {
    const TTStudy::Track& trk = trackList->at(it);
    (signbit(trk.curvature) ? n_tracks_before_acceptance.push_back(it) : p_tracks_before_acceptance.push_back(it));
    // Apply acceptance cuts
    if (fabs(trk.eta) > AnaUtil::cutValue(trkCutMap(), "maxTrkEta")) continue;
    if (trk.pt < AnaUtil::cutValue(trkCutMap(), "minTrkPt")) continue;
    
    (signbit(trk.curvature) ? n_tracks_not_good.push_back(it) : p_tracks_not_good.push_back(it));

   if(checkL1Offline){
    trkChi2RedOfflineH_->Fill(trk.chiSquareRed);
    trkNStubOfflineH_->Fill(trk.nStub);
    trkNStub_PSOfflineH_->Fill(trk.nStub_PS); 
   }
   else{
    trkChi2RedH_->Fill(trk.chiSquareRed);
    trkNStubH_->Fill(trk.nStub);
    trkNStub_PSH_->Fill(trk.nStub_PS); 
   }

    // Optionally select tracks
    if ((applyTrkQuality_ &&!checkL1Offline) && (trk.chiSquareRed > AnaUtil::cutValue(trkCutMap(), "maxTrkChi2") || 
			     trk.nStub        < AnaUtil::cutValue(trkCutMap(), "minTrkLayers") ||
			     trk.nStub_PS     < AnaUtil::cutValue(trkCutMap(), "minTrkPSLayers"))) continue;

    // store track index depending on the charge
    (signbit(trk.curvature) ? n_tracks.push_back(it) : p_tracks.push_back(it));
  }

  ntrk_p_after_acceptanceH_->Fill(p_tracks_not_good.size());
  ntrk_n_after_acceptanceH_->Fill(n_tracks_not_good.size());
  ntrk_p_goodH_->Fill(p_tracks.size());
  ntrk_n_goodH_->Fill(n_tracks.size());
  ntrk_p_before_acceptanceH_->Fill(p_tracks_before_acceptance.size());
  ntrk_n_before_acceptanceH_->Fill(n_tracks_before_acceptance.size());
  

  // Now find phi candidates
  for (auto it: p_tracks) {
    const TTStudy::Track& trk1 = trackList->at(it);

    TLorentzVector trkv1;  
    trkv1.SetPtEtaPhiM(trk1.pt, trk1.eta, trk1.phi, ::kmass);

    for (auto jt: n_tracks) {
      const TTStudy::Track& trk2 = trackList->at(jt);

      // the track pair must come from the same vertex
      double dxy, dz;
      BsAnalysis::calculateDeltaPos(trk1, trk2, dxy, dz);

      if (checkL1Offline) {
	dzTrackPairOfflineH_->Fill(dz);
	dzTrackPair2OfflineH_->Fill(dz);
      }
      else {
	dzTrackPairH_->Fill(dz);
	dzTrackPair2H_->Fill(dz);
      }
      // First apply |dz|(track-pair) cut
      count0++;
      if (fabs(dz) > AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz")) continue;

      if (checkL1Offline) {
	dxyTrackPairOfflineH_->Fill(dxy);
	dxyTrackPair2OfflineH_->Fill(dxy);
      }
      else {
	dxyTrackPairH_->Fill(dxy);
	dxyTrackPair2H_->Fill(dxy);
      }
      // Then apply dxy(track-pair) cut
      count1++;
      if (dxy > AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy")) continue;

      TLorentzVector trkv2;
      trkv2.SetPtEtaPhiM(trk2.pt, trk2.eta, trk2.phi, ::kmass);

      // Select mass window
      TLorentzVector phiLV = trkv1 + trkv2;
      double mass = phiLV.M();
      if (checkL1Offline) {
	phimass0OfflineH_->Fill(mass);
	phimassOfflineH_->Fill(mass);
      }
      else {
	phimass0H_->Fill(mass);
	phimassH_->Fill(mass);
      }

      count2++;

      //if (mass > AnaUtil::cutValue(phiCutMap(), "massLow") && mass < AnaUtil::cutValue(phiCutMap(), "massHigh")) {
      if (mass < AnaUtil::cutValue(phiCutMap(), "massLow") || mass > AnaUtil::cutValue(phiCutMap(), "massHigh")) continue;
      vector<TLorentzVector> list;
      list.push_back(trkv1);
      list.push_back(trkv2);
      phiCandList_.push_back(list);
      double dr = trkv1.DeltaR(trkv2);
      if (checkL1Offline) {
	drTrackPairOfflineH_->Fill(dr);
	phiCandPtOfflineH_->Fill(phiLV.Pt());
	dzTrackPair3OfflineH_->Fill(dz);
	dRvsdZ1OfflineH_->Fill(dz,dr);
      }
      else {
	drTrackPairH_->Fill(dr);
	phiCandPtH_->Fill(phiLV.Pt());
	dzTrackPair3H_->Fill(dz);
	dxyTrackPair3H_->Fill(dxy);
	dRvsdZ1H_->Fill(dz,dr);
      }

	// Fill PhiInfo
      PhiInfo info;
      info.indx1 = it;
      info.indx2 = jt;
      info.dmass = fabs(::phi_polemass - mass);

      info.dxy = dxy;
      info.dz = dz;
      info.dr = dr;
      info.v = phiLV;
      info.vertexX = 0.5 * (trk1.vertexX + trk2.vertexX);
      info.vertexY = 0.5 * (trk1.vertexY + trk2.vertexY);
      info.vertexZ = 0.5 * (trk1.vertexZ + trk2.vertexZ);

      phiList.push_back(info);
     // }
    }
  }
}
void BsAnalysis::checkPhiKaonBs(const PhiInfo& info_i, const PhiInfo& info_j, const vector<TTStudy::Track>* trackList) {
  if (studyGen_) {
    // Checking Matched Phis
    double min_dr_phi1 = 999.;
    double min_dr_phi2 = 999.;
    double dpt_phi1, deta_phi1, dphi_phi1, dpt_phi2, deta_phi2, dphi_phi2;
    for (size_t i = 0; i < genPhiCandList_.size(); ++i) {
      const TTStudy::GenParticle& genphi = genPhiCandList_[i];
      TLorentzVector philv;
      philv.SetPtEtaPhiE(genphi.pt, genphi.eta, genphi.phi, genphi.energy);
      double dr_1 = info_i.v.DeltaR(philv);
      double dr_2 = info_j.v.DeltaR(philv);
      if (dr_1 < min_dr_phi1) {
	min_dr_phi1 = dr_1;
	dpt_phi1  = fabs(info_i.v.Pt() - philv.Pt());
	deta_phi1 = fabs(info_i.v.Eta() - philv.Eta());
	dphi_phi1 = info_i.v.DeltaPhi(philv);
      }
      if (dr_2 < min_dr_phi2) {
	min_dr_phi2 = dr_2;
	dpt_phi2  = fabs(info_j.v.Pt() - philv.Pt());
	deta_phi2 = fabs(info_j.v.Eta() - philv.Eta());
	dphi_phi2 = info_j.v.DeltaPhi(philv);
      }
    }
    mDr_phi->Fill(min_dr_phi1);
    mDr_phi->Fill(min_dr_phi2);

    mDpt_phi->Fill(dpt_phi1);
    mDpt_phi->Fill(dpt_phi2);

    mDeta_phi->Fill(deta_phi1);
    mDeta_phi->Fill(deta_phi2);

    mDphi_phi->Fill(dphi_phi1);
    mDphi_phi->Fill(dphi_phi2);

    // Checking Matched Kaons
    TLorentzVector kaon1, kaon2, kaon3, kaon4;
    getLV(trackList, info_i.indx1, kaon1);
    getLV(trackList, info_i.indx2, kaon2);
    getLV(trackList, info_j.indx1, kaon3);
    getLV(trackList, info_j.indx2, kaon4);

    double min_dr_kaon1 = 999.0;
    double dpt1, deta1, dphi1;
    double min_dr_kaon2 = 999.0;
    double dpt2, deta2, dphi2;
    double min_dr_kaon3 = 999.0;
    double dpt3, deta3, dphi3;
    double min_dr_kaon4 = 999.0;
    double dpt4, deta4, dphi4;
    for (size_t i = 0; i < genPhiCandList_.size(); ++i) {       
      const TTStudy::GenParticle& genphi = genPhiCandList_[i];
      for (size_t j = 0; j < genphi.daughterIndices.size(); ++j) {
	const TTStudy::GenParticle& kaon = genParticleBr_->at(genphi.daughterIndices.at(j));
	TLorentzVector kaonlv;
	kaonlv.SetPtEtaPhiE(kaon.pt, kaon.eta, kaon.phi, kaon.energy);
	double dr_1 = kaon1.DeltaR(kaonlv);
	double dr_2 = kaon2.DeltaR(kaonlv);
	double dr_3 = kaon3.DeltaR(kaonlv);
	double dr_4 = kaon4.DeltaR(kaonlv);
	if (dr_1 < min_dr_kaon1) {
	  min_dr_kaon1 = dr_1;
	  dpt1  = fabs(kaon1.Pt() - kaonlv.Pt());
	  deta1 = fabs(kaon1.Eta() - kaonlv.Eta());
	  dphi1 = kaon1.DeltaPhi(kaonlv);
	}
	if (dr_2 < min_dr_kaon2) {
	  min_dr_kaon2 = dr_2;
	  dpt2  = fabs(kaon2.Pt() - kaonlv.Pt());
	  deta2 = fabs(kaon2.Eta() - kaonlv.Eta());
	  dphi2 = kaon2.DeltaPhi(kaonlv);
	}
	if (dr_3 < min_dr_kaon3) {
	  min_dr_kaon3 = dr_3;
	  dpt3  = fabs(kaon3.Pt() - kaonlv.Pt());
	  deta3 = fabs(kaon3.Eta() - kaonlv.Eta());
	  dphi3 = kaon3.DeltaPhi(kaonlv);
	}
	if (dr_4 < min_dr_kaon4) {
	  min_dr_kaon4 = dr_4;
	  dpt4  = fabs(kaon4.Pt() - kaonlv.Pt());
	  deta4 = fabs(kaon4.Eta() - kaonlv.Eta());
	  dphi4 = kaon4.DeltaPhi(kaonlv);
	}
      }
    }
    mDr_K->Fill(min_dr_kaon1);
    mDpt_K->Fill(dpt1);
    mDphi_K->Fill(deta1);
    mDeta_K->Fill(dphi1);

    mDr_K->Fill(min_dr_kaon2);
    mDpt_K->Fill(dpt2);
    mDphi_K->Fill(deta2);
    mDeta_K->Fill(dphi2);

    mDr_K->Fill(min_dr_kaon3);
    mDpt_K->Fill(dpt3);
    mDphi_K->Fill(deta3);
    mDeta_K->Fill(dphi3);

    mDr_K->Fill(min_dr_kaon4);
    mDpt_K->Fill(dpt4);
    mDphi_K->Fill(deta4);
    mDeta_K->Fill(dphi4);
  }    
}
void BsAnalysis::getKaonList(const vector<TTStudy::Track>* trackList, const BsInfo& bsinfo, vector<TLorentzVector>& kaonList) {
  TLorentzVector lv;
  getLV(trackList, bsinfo.phi1.indx1, lv);
  kaonList.push_back(lv);

  getLV(trackList, bsinfo.phi1.indx2, lv);
  kaonList.push_back(lv);

  getLV(trackList, bsinfo.phi2.indx1, lv);
  kaonList.push_back(lv);

  getLV(trackList, bsinfo.phi2.indx2, lv);
  kaonList.push_back(lv);

  sort(kaonList.begin(), kaonList.end(), LVPtComparator());
}
void BsAnalysis::fillKaonTrackInfo(const vector<TTStudy::Track>* tracksBr, const BsInfo& bsinfo) {
  const TTStudy::Track& trk1 = tracksBr->at(bsinfo.phi1.indx1);    
  trk1Chi2H_->Fill(trk1.chiSquare);
  trk1Chi2RedH_->Fill(trk1.chiSquareRed);
  trk1nStubH_->Fill(trk1.nStub);
  trk1nStubPSH_->Fill(trk1.nStub_PS);

  const TTStudy::Track& trk2 = tracksBr->at(bsinfo.phi1.indx2);    
  trk2Chi2H_->Fill(trk2.chiSquare);
  trk2Chi2RedH_->Fill(trk2.chiSquareRed);
  trk2nStubH_->Fill(trk2.nStub);
  trk2nStubPSH_->Fill(trk2.nStub_PS);

  const TTStudy::Track& trk3 = tracksBr->at(bsinfo.phi2.indx1);    
  trk3Chi2H_->Fill(trk3.chiSquare);
  trk3Chi2RedH_->Fill(trk3.chiSquareRed);
  trk3nStubH_->Fill(trk3.nStub);
  trk3nStubPSH_->Fill(trk3.nStub_PS);

  const TTStudy::Track& trk4 = tracksBr->at(bsinfo.phi2.indx2);    
  trk4Chi2H_->Fill(trk4.chiSquare);
  trk4Chi2RedH_->Fill(trk4.chiSquareRed);
  trk4nStubH_->Fill(trk4.nStub);
  trk4nStubPSH_->Fill(trk4.nStub_PS);

  if (verbosity_ > 1) {
    cout << "Track 1 - chi2, nstub: " << trk1.chiSquare << ", " << trk1.nStub << endl
      << "Track 2 - chi2, nstub: " << trk2.chiSquare << ", " << trk2.nStub << endl
      << "Track 3 - chi2, nstub: " << trk3.chiSquare << ", " << trk3.nStub << endl
      << "Track 4 - chi2, nstub: " << trk4.chiSquare << ", " << trk4.nStub << endl;
  }
}
double BsAnalysis::computeIsolation_v2(const vector<TTStudy::Track>* trackList, 
				       size_t ref_track_index, 
				       const vector<size_t> tracks_to_exclude) 
{
  const TTStudy::Track& ref_trk = trackList->at(ref_track_index);
  TLorentzVector ref_trk_lv;
  ref_trk_lv.SetPtEtaPhiM(ref_trk.pt, ref_trk.eta, ref_trk.phi, ::kmass);
  
  double sum_pt = 0;  
  for (size_t indx = 0; indx < trackList->size(); ++indx) {
    if (indx == ref_track_index) continue;
    
    auto it = find (tracks_to_exclude.begin(), tracks_to_exclude.end(), indx); 
    if (it != tracks_to_exclude.end()) continue;

    const TTStudy::Track& trk = trackList->at(indx);
    if (fabs(trk.eta) > AnaUtil::cutValue(trkCutMap(), "maxTrkEta")) continue;
    if (trk.pt < AnaUtil::cutValue(trkCutMap(), "minTrkPt")) continue;
    if (applyTrkQuality_ && (trk.chiSquareRed > AnaUtil::cutValue(trkCutMap(), "maxTrkChi2") || 
			     trk.nStub < AnaUtil::cutValue(trkCutMap(), "minTrkLayers") ||
			     trk.nStub_PS < AnaUtil::cutValue(trkCutMap(), "minTrkPSLayers"))) continue;
    
    double dxy, dz;
    BsAnalysis::calculateDeltaPos(ref_trk, trk, dxy, dz);
    
    if (fabs(dz) > AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz")) continue;
    if (dxy > AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy")) continue;
    
    TLorentzVector trk_lv;
    trk_lv.SetPtEtaPhiM(trk.pt, trk.eta, trk.phi, ::kmass);
    
    double dR = trk_lv.DeltaR(ref_trk_lv);
    if (dR < AnaUtil::cutValue(isoCutMap(), "isoCone")) sum_pt += trk.pt;
  }   
  return sum_pt/ref_trk.pt;
}
void BsAnalysis::computeIsolation(const vector<TTStudy::Track>* trackList, const BsInfo& bsinfo, vector<pair<double,double>>& iso_vector) {
  const TTStudy::Track& trk1 = trackList->at(bsinfo.phi1.indx1);    
  TLorentzVector trk1_lv;
  trk1_lv.SetPtEtaPhiM(trk1.pt, trk1.eta, trk1.phi, ::kmass);

  const TTStudy::Track& trk2 = trackList->at(bsinfo.phi1.indx2);    
  TLorentzVector trk2_lv;
  trk2_lv.SetPtEtaPhiM(trk2.pt, trk2.eta, trk2.phi, ::kmass);

  const TTStudy::Track& trk3 = trackList->at(bsinfo.phi2.indx1);    
  TLorentzVector trk3_lv;
  trk3_lv.SetPtEtaPhiM(trk3.pt, trk3.eta, trk3.phi, ::kmass);

  const TTStudy::Track& trk4 = trackList->at(bsinfo.phi2.indx2);    
  TLorentzVector trk4_lv;
  trk4_lv.SetPtEtaPhiM(trk4.pt, trk4.eta, trk4.phi, ::kmass);

  const PhiInfo& phi1 = bsinfo.phi1;
  const PhiInfo& phi2 = bsinfo.phi2;
  

  double isol1 = 0.0,
	 isol2 = 0.0,
	 isol3 = 0.0,
	 isol4 = 0.0,
         isol_phi1 = 0.0,
         isol_phi2 = 0.0,
         isol_Bs = 0.0;
  
  for (size_t it = 0; it < trackList->size(); ++it) {
    const TTStudy::Track& trk = trackList->at(it);
    TLorentzVector trk_lv;
    trk_lv.SetPtEtaPhiM(trk.pt, trk.eta, trk.phi, ::kmass); 
    if ( AnaUtil::sameObject(trk_lv, trk1_lv) || 
	AnaUtil::sameObject(trk_lv, trk2_lv) || 
	AnaUtil::sameObject(trk_lv, trk3_lv) || 
	AnaUtil::sameObject(trk_lv, trk4_lv) ) continue;
    

    if (fabs(trk.eta) > AnaUtil::cutValue(trkCutMap(), "maxTrkEta")) continue;
    if (trk.pt < AnaUtil::cutValue(trkCutMap(), "minTrkPt")) continue;
    if (applyTrkQuality_ && (trk.chiSquareRed > AnaUtil::cutValue(trkCutMap(), "maxTrkChi2") || 
			     trk.nStub < AnaUtil::cutValue(trkCutMap(), "minTrkLayers") ||
			     trk.nStub_PS < AnaUtil::cutValue(trkCutMap(), "minTrkPSLayers"))) continue;

    double dxy1, dz1;
    BsAnalysis::calculateDeltaPos(trk1, trk, dxy1, dz1);
    
    double dxy2, dz2;
    BsAnalysis::calculateDeltaPos(trk2, trk, dxy2, dz2);
    
    double dxy3, dz3;
    BsAnalysis::calculateDeltaPos(trk3, trk, dxy3, dz3);
    
    double dxy4, dz4;
    BsAnalysis::calculateDeltaPos(trk4, trk, dxy4, dz4);
    
    double dR_1 = trk_lv.DeltaR(trk1_lv);
    double dR_2 = trk_lv.DeltaR(trk2_lv);
    double dR_3 = trk_lv.DeltaR(trk3_lv);
    double dR_4 = trk_lv.DeltaR(trk4_lv);

    if (dR_1 < AnaUtil::cutValue(isoCutMap(), "isoCone") && dR_1 > AnaUtil::cutValue(isoCutMap(), "isoInnerCone")){
      if (fabs(dz1) < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz") && dxy1 < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy"))
	isol1 += trk.pt;
    }
    if (dR_2 < AnaUtil::cutValue(isoCutMap(), "isoCone") && dR_2 > AnaUtil::cutValue(isoCutMap(), "isoInnerCone")){  
      if (fabs(dz2) < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz") && dxy2 < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy"))
	isol2 += trk.pt;
    }
    if (dR_3 < AnaUtil::cutValue(isoCutMap(), "isoCone") && dR_3 > AnaUtil::cutValue(isoCutMap(), "isoInnerCone")){
      if (fabs(dz3) < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz") && dxy3 < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy"))
      isol3 += trk.pt;
    }
    if (dR_4 < AnaUtil::cutValue(isoCutMap(), "isoCone") && dR_4 > AnaUtil::cutValue(isoCutMap(), "isoInnerCone")){
      if (fabs(dz4) < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz") && dxy4 < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy"))
	isol4 += trk.pt;
    } 
   
    //Calculaye phi isolations
    double dxy_phi1, dz_phi1;
    BsAnalysis::calculateDeltaPos(trk, phi1, dxy_phi1, dz_phi1);
    
    double dxy_phi2, dz_phi2;
    BsAnalysis::calculateDeltaPos(trk, phi2, dxy_phi2, dz_phi2);

    double dR_phi1 = trk_lv.DeltaR(phi1.v);
    double dR_phi2 = trk_lv.DeltaR(phi2.v);

    if (dR_phi1 < AnaUtil::cutValue(isoCutMap(), "isoCone") && dR_phi1 > AnaUtil::cutValue(isoCutMap(), "isoInnerCone")){
      if (fabs(dz_phi1) < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz") && dxy_phi1 < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy"))
	isol_phi1 += trk.pt;
    }
  
    if (dR_phi2 < AnaUtil::cutValue(isoCutMap(), "isoCone") && dR_phi2 > AnaUtil::cutValue(isoCutMap(), "isoInnerCone")){
      if (fabs(dz_phi2) < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz") && dxy_phi2 < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy"))
	isol_phi2 += trk.pt;
    }
 
   //Calculate Bs Isolation
   double dxy_Bs, dz_Bs;
   BsAnalysis::calculateDeltaPos(trk, bsinfo, dxy_Bs, dz_Bs);

   double dR_Bs = trk_lv.DeltaR(bsinfo.bsv);

  
   if (dR_Bs < AnaUtil::cutValue(isoCutMap(), "isoCone") && dR_Bs > AnaUtil::cutValue(isoCutMap(), "isoInnerCone")){
     if (fabs(dz_Bs) < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDz") && dxy_Bs < AnaUtil::cutValue(phiCutMap(), "maxTrkPairDxy"))
       isol_Bs += trk.pt;
   }
 
  }
  isol1 /= trk1.pt;
  iso_vector.push_back(std::make_pair(isol1,trk1.pt));
  isol2 /= trk2.pt;
  iso_vector.push_back(std::make_pair(isol2,trk2.pt));
  isol3 /= trk3.pt;
  iso_vector.push_back(std::make_pair(isol3,trk3.pt));
  isol4 /= trk4.pt;
  iso_vector.push_back(std::make_pair(isol4,trk4.pt));

  isol_phi1 /= phi1.v.Pt();
  iso_vector.push_back(std::make_pair(isol_phi1,phi1.v.Pt()));
  isol_phi2 /= phi2.v.Pt();
  iso_vector.push_back(std::make_pair(isol_phi2,phi2.v.Pt()));

  isol_Bs /= bsinfo.bsv.Pt();
  iso_vector.push_back(std::make_pair(isol_Bs,bsinfo.bsv.Pt()));
}
void BsAnalysis::fillKaonInfo(const vector<TLorentzVector>& kaonList) {
  if (verbosity_ > 1) { 
    cout << setw(10) << "No." 
      << setw(10) << "Pt" 
      << setw(10) << "Eta" 
      << setw(10) << "Phi" 
      << endl;
    int i = 0;
    for (auto& v: kaonList) {
      cout << setw(10) << i++ 
	<< setw(10) << v.Pt()
	<< setw(10) << v.Eta() 
	<< setw(10) << v.Phi()
	<< endl;
    }
  } 
  size_t ntrk = kaonList.size();
  if (ntrk) {
    trk1PtH_->Fill(kaonList[0].Pt());
    trk1EtaH_->Fill(kaonList[0].Eta());
    trk1PhiH_->Fill(kaonList[0].Phi());
  } 
  if (ntrk > 1) {
    trk2PtH_->Fill(kaonList[1].Pt());
    trk2EtaH_->Fill(kaonList[1].Eta());
    trk2PhiH_->Fill(kaonList[1].Phi());
  } 
  if (ntrk > 2) {
    trk3PtH_->Fill(kaonList[2].Pt());
    trk3EtaH_->Fill(kaonList[2].Eta());
    trk3PhiH_->Fill(kaonList[2].Phi());
  } 
  if (ntrk > 3) {
    trk4PtH_->Fill(kaonList[3].Pt());
    trk4EtaH_->Fill(kaonList[3].Eta());
    trk4PhiH_->Fill(kaonList[3].Phi());
  }

 

  for ( size_t i = 0; i < kaonList.size(); ++i) {
    const TLorentzVector& kaon1 = kaonList[i];
    for (size_t j = i+1; j < kaonList.size(); ++j) {
      const TLorentzVector& kaon2 = kaonList[j];
      double dr = kaon1.DeltaR(kaon2);
      drKaonPairH_->Fill(dr);
    }
  }
}
void BsAnalysis::fillGenInfo() {
  sort(genKaonList_.begin(), genKaonList_.end(), PtComparator<TTStudy::GenParticle>());
  if (genKaonList_.size()) {
    genKPt1H_->Fill(genKaonList_.at(0).pt);
    genKEta1H_->Fill(genKaonList_.at(0).eta);
    genKPhi1H_->Fill(genKaonList_.at(0).phi);
  }
  if (genKaonList_.size() > 1) {
    genKPt2H_->Fill(genKaonList_.at(1).pt);
    genKEta1H_->Fill(genKaonList_.at(1).eta);
    genKPhi1H_->Fill(genKaonList_.at(1).phi);
  }
  if (genKaonList_.size() > 2) {
    genKPt3H_->Fill(genKaonList_.at(2).pt);
    genKEta1H_->Fill(genKaonList_.at(2).eta);
    genKPhi1H_->Fill(genKaonList_.at(2).phi);
  }
  if (genKaonList_.size() > 3) {
    genKPt4H_->Fill(genKaonList_.at(3).pt);
    genKEta1H_->Fill(genKaonList_.at(3).eta);
    genKPhi1H_->Fill(genKaonList_.at(3).phi);
  }

  // Phi mass, how do you find that?
  for (size_t i = 0; i < genKaonList_.size(); ++i) {
    TTStudy::GenParticle& kaon1 = genKaonList_[i];
    TLorentzVector gen_kaon1_v;
    gen_kaon1_v.SetPtEtaPhiE(kaon1.pt, kaon1.eta, kaon1.phi, kaon1.energy);
    for (size_t j = i+1; j < genKaonList_.size(); ++j) {
      TTStudy::GenParticle& kaon2 = genKaonList_[j];
      TLorentzVector gen_kaon2_v;
      gen_kaon2_v.SetPtEtaPhiE(kaon2.pt, kaon2.eta, kaon2.phi, kaon2.energy);

      // what about the charges?
      TLorentzVector gen_phi = gen_kaon1_v + gen_kaon2_v;
      genPhiMH_->Fill(gen_phi.M());
    }
  }

  sort(genPhiCandList_.begin(), genPhiCandList_.end(), PtComparator<TTStudy::GenParticle>());
  if (genPhiCandList_.size()) {
    genPhiPt1H_->Fill(genPhiCandList_[0].pt);
    genPhiEta1H_->Fill(genPhiCandList_[0].eta);
    genPhiPhi1H_->Fill(genPhiCandList_[0].phi);
    genKPt1H_->Fill(genParticleBr_->at(genPhiCandList_[0].daughterIndices.at(0)).pt);
    genKPt1H_->Fill(genParticleBr_->at(genPhiCandList_[0].daughterIndices.at(1)).pt);
  }
  if (genPhiCandList_.size() > 1) {
    genPhiPt1H_->Fill(genPhiCandList_[1].pt);
    genPhiEta1H_->Fill(genPhiCandList_[1].eta);
    genPhiPhi1H_->Fill(genPhiCandList_[1].phi);
    genKPt2H_->Fill(genParticleBr_->at(genPhiCandList_[1].daughterIndices.at(0)).pt);
    genKPt2H_->Fill(genParticleBr_->at(genPhiCandList_[1].daughterIndices.at(1)).pt);
  }
}
void BsAnalysis::checkConsistency(const vector<TTStudy::Track>* tracksBr, int ntrk) const {
  if (ntrk <= 4) return;
  printTrackProperties(tracksBr);

  cout << "===== Reading GenParticles ========================================" << endl;
  cout << "index       pT      eta      phi       vx       vy      vz      pdgID" << endl;
  for (size_t i = 0; i != genParticleBr_->size(); ++i) {
    const TTStudy::GenParticle& genp = genParticleBr_->at(i);
    if (genp.status == 1 && genp.pt > 1.95)
      printGenParticle(i);
  }
}
void BsAnalysis::checkDecayMode() {
  for (size_t i = 0; i != genParticleBr_->size(); ++i) {
    const TTStudy::GenParticle& genp = genParticleBr_->at(i);
    if (abs(genp.pdgId) != 531) continue;
    nDaughtersH_->Fill(genp.daughterIndices.size());
    if (genp.daughterIndices.size() == 1 && abs(genParticleBr_->at(genp.daughterIndices.at(0)).pdgId) == 531) continue; 
    BsDecayModesH_->Fill(0); 
    if (genp.daughterIndices.size() == 2) {
      const TTStudy::GenParticle& daughter1 = genParticleBr_->at(genp.daughterIndices.at(0)); 	
      const TTStudy::GenParticle& daughter2 = genParticleBr_->at(genp.daughterIndices.at(1));
      if (abs(daughter1.pdgId) == 333 && abs(daughter2.pdgId) == 333) BsDecayModesH_->Fill(1);
      else if (abs(daughter1.pdgId) == 443 || abs(daughter2.pdgId) == 443) BsDecayModesH_->Fill(2);
      else if (abs(daughter1.pdgId) == 13  && abs(daughter2.pdgId) == 13) BsDecayModesH_->Fill(3);
      else if (abs(daughter1.pdgId) == 15  && abs(daughter2.pdgId) == 15) BsDecayModesH_->Fill(4);
      else  BsDecayModesH_->Fill(5);	
    }
    else BsDecayModesH_->Fill(6);

    for (size_t j = 0; j != genp.daughterIndices.size(); ++j) {
      const TTStudy::GenParticle& daughter = genParticleBr_->at(genp.daughterIndices.at(j));
      if (daughter.pdgId != 443) continue;
      cout << " Daughter pdgId = " << daughter.pdgId << endl;
      for (size_t k = 0; k != daughter.daughterIndices.size(); ++k) {
	const TTStudy::GenParticle& grandDaughter = genParticleBr_->at(daughter.daughterIndices.at(k));
	cout<< " grandDaughter pdgId = " << grandDaughter.pdgId << endl;
      }
    }
  }
}
void BsAnalysis::checkMatchingPhi(int ntrk) const {
  if (verbosity_ > 1) 
    cout << "# of Phi, detector level: " << phiCandList_.size() 
      << " Gen level:" << genPhiCandList_.size()
      << " #tracks: " << ntrk
      << endl;
  for (size_t it = 0; it < phiCandList_.size(); ++it) {
    const TLorentzVector& trk_k1 = phiCandList_[it].at(0);
    const TLorentzVector& trk_k2 = phiCandList_[it].at(1);
    TLorentzVector trk_phip = trk_k1 + trk_k2;
    double drmin = 999;
    int m_index = -1;
    for (size_t jt = 0; jt < genPhiCandList_.size(); ++jt) {
      const TTStudy::GenParticle& phip = genPhiCandList_[jt];
      TLorentzVector gen_phi;
      gen_phi.SetPtEtaPhiE(phip.pt, phip.eta, phip.phi, phip.energy);
      double dr = trk_phip.DeltaR(gen_phi);
      if (dr < drmin) {drmin = dr; m_index = jt;}
    }
    if (verbosity_ > 1 && drmin < 0.4) {
      cout << "MATCH phi candidate: " << it << ", gen phi: " << m_index 
	<< " deltaR[" << it << "," << m_index << "] = " << drmin
	<< endl;
    }
  }
}
void BsAnalysis::printTrackProperties(const vector<TTStudy::Track>* tracksBr) const {
  cout << "===== Reading Tracks ========================================" << endl;
  cout << "index       pT      eta      phi       vx       vy      vz" << endl;
  cout << setprecision(3);
  for (size_t i = 0; i != tracksBr->size(); i++)
    printTrk(tracksBr, i);
}
void BsAnalysis::printTrk(const vector<TTStudy::Track>* tracksBr, size_t i) const {
  const TTStudy::Track& trk = tracksBr->at(i);
  if (fabs(trk.eta) < AnaUtil::cutValue(trkCutMap(), "maxTrkEta")){
    if (trk.pt > AnaUtil::cutValue(trkCutMap(), "minTrkPt")){
      cout << setw(5) << i 
	<< setw(9) << trk.pt
	<< setw(9) << trk.eta
	<< setw(9) << trk.phi
	<< setw(9) << trk.vertexX 
	<< setw(9) << trk.vertexY
	<< setw(9) << trk.vertexZ
	<< endl;
    }
  }
}
void BsAnalysis::plotSignalProperties(const vector<TTStudy::Track>* tracksBr) {
  vector<TTStudy::Track> list;
  int central = 0;
  int fwd = 0;
  for (size_t it = 0; it < tracksBr->size(); ++it) {
    const TTStudy::Track& trk = tracksBr->at(it);
    if (trk.pt < 2) continue;
    TLorentzVector trk_v;
    getLV(tracksBr, it, trk_v);
    double min_dr = 999.9;
    int m_index = -1;
    for (size_t j = 0; j < genKaonList_.size(); ++j) {
      const TTStudy::GenParticle& kaon = genKaonList_[j];
      TLorentzVector gen_kaon_v;
      gen_kaon_v.SetPtEtaPhiE(kaon.pt, kaon.eta, kaon.phi, kaon.energy);
      double dr = trk_v.DeltaR(gen_kaon_v);
      if (dr < min_dr) {
	min_dr = dr;
	m_index = j;
      }     
    }
    signalDrH_->Fill(min_dr);
    if (min_dr < 0.02) {
      signal_VZH_->Fill(trk.vertexZ);
      double vertexXY = sqrt(pow(trk.vertexX, 2) + pow(trk.vertexY, 2));
      signal_VXYH_->Fill(vertexXY);
      signal_chiH_->Fill(trk.chiSquare);
      list.push_back(trk);
      if (fabs(trk.eta) < 1.1) central++;
      if (fabs(trk.eta) < 2.5 && fabs(trk.eta) > 1.1) fwd++;
      TTStudy::GenParticle& kaon = genKaonList_.at(m_index);
      double d_pt = fabs(trk.pt - kaon.pt);
      signalDPT_H->Fill(d_pt);
    }
  }
  signalNtrkH_->Fill(list.size());
  signalCentralH_->Fill(central);
  signalFwdH_->Fill(fwd);
  sort(list.begin(), list.end(), PtComparator<TTStudy::Track>());
  if (list.size() > 0) signalPt1H_->Fill(list[0].pt);
  if (list.size() > 1) signalPt2H_->Fill(list[1].pt);
  if (list.size() > 2) signalPt3H_->Fill(list[2].pt);
  if (list.size() > 3) signalPt4H_->Fill(list[3].pt);

  for (size_t i = 0; i < list.size(); ++i) {
    const TTStudy::Track& trk1 = list[i];
    TLorentzVector trkv1;
    trkv1.SetPtEtaPhiM(trk1.pt, trk1.eta, trk1.phi, ::kmass);
    for (size_t j = i+1; j < list.size(); j++) {
      const TTStudy::Track& trk2 = list[j];
      TLorentzVector trkv2;
      trkv2.SetPtEtaPhiM(trk2.pt, trk2.eta, trk2.phi, ::kmass);
      TLorentzVector phi = trkv1 + trkv2;
      signalPhiMH_->Fill(phi.M());
    }
  }
}
int BsAnalysis::doTrkGenMatch(const vector<TLorentzVector>& kaonList) {
  if (verbosity_ > 1)
    cout << "index       pT      eta      phi matched genindx      pdgID       dR      dpT     dEta     dPhi"
      << endl;

  int m_counter = 0;
  size_t itrk = 0;
  for (auto const& trk_kaon_v: kaonList) {
    double min_dr = 999.9;
    double delta_eta = 99, delta_phi = 99, delta_pt = 99;
    bool match = false;
    int gen_pdgID;
    size_t m_index;
    for (size_t j = 0; j < genKaonList_.size(); ++j) {
      const TTStudy::GenParticle& kaon = genKaonList_[j];
      TLorentzVector gen_kaon_v;
      gen_kaon_v.SetPtEtaPhiE(kaon.pt, kaon.eta, kaon.phi, kaon.energy);
      double dr = trk_kaon_v.DeltaR(gen_kaon_v);
      if (dr < min_dr) {
	min_dr = dr;
	m_index = j;
      }     
    }
    if (min_dr < 0.05) {
      match = true;
      ++m_counter;
      const TTStudy::GenParticle& kaon = genKaonList_.at(m_index);
      TLorentzVector gen_kaon_v;
      gen_kaon_v.SetPtEtaPhiE(kaon.pt, kaon.eta, kaon.phi, kaon.energy);
      delta_pt  = fabs(trk_kaon_v.Pt() - kaon.pt);
      delta_eta = fabs(trk_kaon_v.Eta() - kaon.eta);
      delta_phi = fabs(trk_kaon_v.DeltaPhi(gen_kaon_v));
      gen_pdgID = kaon.pdgId;
    } 
    if (verbosity_ > 1)
      cout << setprecision(3)
	<< setw(5)  << itrk++
	<< setw(9)  << trk_kaon_v.Pt()
	<< setw(9)  << trk_kaon_v.Eta()
	<< setw(9)  << trk_kaon_v.Phi()
	<< setw(8)  << match
	<< setw(8)  << m_index
	<< setw(11) << gen_pdgID
	<< setprecision(4)
	<< setw(9)  << min_dr
	<< setw(9)  << delta_pt
	<< setw(9)  << delta_eta
	<< setw(9)  << delta_phi
	<< endl;           
  } 
  if (verbosity_ > 1) {
    cout << setprecision(2);
    cout << "Match Counter# " << m_counter << endl;
  }
  return m_counter;
}

bool BsAnalysis::isGenKaonMatched(const TLorentzVector& trk_lv, double& pt_diff){
  bool match = false;
  size_t m_index;
  double min_dr = 999.9;
  for (size_t j = 0; j < genKaonList_.size(); ++j) {
    const TTStudy::GenParticle& kaon = genKaonList_[j];
    TLorentzVector gen_kaon_v;
    gen_kaon_v.SetPtEtaPhiE(kaon.pt, kaon.eta, kaon.phi, kaon.energy);
    double dr = trk_lv.DeltaR(gen_kaon_v);
    if (dr < min_dr) {
      min_dr = dr;
      m_index = j;

      pt_diff = trk_lv.Pt() - gen_kaon_v.Pt(); 
    }     
  }
  if (min_dr < 0.05) match = true;
  return match;
}
void BsAnalysis::printGenParticle(size_t i) const {
  const TTStudy::GenParticle& p = genParticleBr_->at(i);
  cout << setw(5)  << i
	    << setw(9)  << p.pt
	    << setw(9)  << p.eta
	    << setw(9)  << p.phi
	    << setw(9)  << p.vx
	    << setw(9)  << p.vy
	    << setw(9)  << p.vz
	    << setw(11) << p.pdgId
	    << endl;
}
TLorentzVector BsAnalysis::phiLV(const TTStudy::Track& trki, const TTStudy::Track& trkj) {
  TLorentzVector lvtrki, lvtrkj;  
  lvtrki.SetPtEtaPhiM(trki.pt, trki.eta, trki.phi, ::kmass);
  lvtrkj.SetPtEtaPhiM(trkj.pt, trkj.eta, trkj.phi, ::kmass);
  return (lvtrki+lvtrkj);
}
double BsAnalysis::calculateDeltaR(const TTStudy::Track& trki, const TTStudy::Track& trkj) {
  TLorentzVector lvtrki, lvtrkj;  
  lvtrki.SetPtEtaPhiM(trki.pt, trki.eta, trki.phi, ::kmass);
  lvtrkj.SetPtEtaPhiM(trkj.pt, trkj.eta, trkj.phi, ::kmass);
  return lvtrki.DeltaR(lvtrkj);
}
double BsAnalysis::calculateDeltaR(const TTStudy::GenParticle& gpi, const TTStudy::GenParticle& gpj) {
  TLorentzVector lvpi, lvpj;  
  lvpi.SetPtEtaPhiE(gpi.pt, gpi.eta, gpi.phi, gpi.energy);
  lvpj.SetPtEtaPhiE(gpj.pt, gpj.eta, gpj.phi, gpj.energy);
  return lvpi.DeltaR(lvpj);
}

void BsAnalysis::calculateDeltaPos(const TTStudy::Track& trki, const TTStudy::Track& trkj, double& dxy, double& dz) {
  dxy = sqrt(pow(trki.vertexX - trkj.vertexX, 2) + pow(trki.vertexY - trkj.vertexY, 2));
  dz  = trki.vertexZ - trkj.vertexZ;
}
void BsAnalysis::calculateDeltaPos(const PhiInfo& infoi, const PhiInfo& infoj, double& dxy, double& dz) {
  dxy = sqrt(pow(infoi.vertexX - infoj.vertexX, 2) + pow(infoi.vertexY - infoj.vertexY, 2));
  dz  = infoi.vertexZ - infoj.vertexZ;
}
void BsAnalysis::calculateDeltaPos(const TTStudy::Track& trki, const PhiInfo& infoj, double& dxy, double& dz) {
  dxy = sqrt(pow(trki.vertexX - infoj.vertexX, 2) + pow(trki.vertexY - infoj.vertexY, 2));
  dz  = trki.vertexZ - infoj.vertexZ;
}
void BsAnalysis::calculateDeltaPos(const TTStudy::Track& trki, const BsInfo& bsInfoj, double& dxy, double& dz) {
  dxy = sqrt(pow(trki.vertexX - bsInfoj.vertexX, 2) + pow(trki.vertexY - bsInfoj.vertexY, 2));
  dz  = trki.vertexZ - bsInfoj.vertexZ;
}

bool BsAnalysis::genFilter(double minPt, double maxEta) const {
  vector<TTStudy::GenParticle> list;
  for (size_t it = 0; it < genParticleBr_->size(); ++it) {
    const TTStudy::GenParticle& genp = genParticleBr_->at(it);
    if (abs(genp.pdgId) != 333) continue;  // Phi 

    const TTStudy::GenParticle& pgenp = genParticleBr_->at(genp.motherIndex);
    if (abs(pgenp.pdgId) != 531) continue; // Bs

    if (genp.daughterIndices.size() < 2) continue;
    const TTStudy::GenParticle& kaon1 = genParticleBr_->at(genp.daughterIndices.at(0));
    const TTStudy::GenParticle& kaon2 = genParticleBr_->at(genp.daughterIndices.at(1));
    if (abs(kaon1.pdgId) != 321 || abs(kaon2.pdgId) != 321) continue;
    genKPtCheckH_->Fill(kaon1.pt);
    genKPtCheckH_->Fill(kaon2.pt);
    if (kaon1.pt < minPt || fabs(kaon1.eta) > maxEta) continue;
    if (kaon2.pt < minPt || fabs(kaon2.eta) > maxEta) continue;
    list.push_back(genp);
  }

  if (list.size() >= 2) return true;
  return false;
}
void BsAnalysis::readGenParticle() {
  for (size_t it = 0; it < genParticleBr_->size(); ++it) {
    const TTStudy::GenParticle& genp = genParticleBr_->at(it);
    if (abs(genp.pdgId) != 333) continue; // Phi

    const TTStudy::GenParticle& mot = genParticleBr_->at(genp.motherIndex);
    if (abs(mot.pdgId) != 531) continue; // Bs
    genPhiCandList_.push_back(genp); 

    if (genp.daughterIndices.size() < 2) continue;
    const TTStudy::GenParticle& kaon1 = genParticleBr_->at(genp.daughterIndices.at(0));
    const TTStudy::GenParticle& kaon2 = genParticleBr_->at(genp.daughterIndices.at(1));
    if (abs(kaon1.pdgId) != 321 || abs(kaon2.pdgId) != 321) continue; // K
    genKaonList_.push_back(kaon1);
    genKaonList_.push_back(kaon2);
  }
}
void BsAnalysis::plotGen(const vector<TTStudy::Track>* tracksBr) {
  if (genPhiCandList_.size() > 1) {
    const TTStudy::GenParticle& phi1 = genPhiCandList_[0];
    TLorentzVector phi1_v;
    phi1_v.SetPtEtaPhiE(phi1.pt, phi1.eta, phi1.phi, phi1.energy);

    const TTStudy::GenParticle& phi2 = genPhiCandList_[1];
    TLorentzVector phi2_v;
    phi2_v.SetPtEtaPhiE(phi2.pt, phi2.eta, phi2.phi, phi2.energy);

    double d_rphi = phi1_v.DeltaR(phi2_v);
    genDrPhiPairH_->Fill(d_rphi); 
  }
  for (size_t it = 0; it < genPhiCandList_.size(); ++it) {
    const TTStudy::GenParticle& phi1 = genPhiCandList_[it];
    for (size_t jt = it+1; jt < genPhiCandList_.size(); ++jt) {
      const TTStudy::GenParticle& phi2 = genPhiCandList_[jt];
      if (phi1.motherIndex != phi2.motherIndex) continue;
      const TTStudy::GenParticle& mot = genParticleBr_->at(phi1.motherIndex);
      if (abs(mot.pdgId) != 531) continue; // Bs
      genBsPtH_->Fill(mot.pt);
      genBsEtaH_->Fill(mot.eta);
      genBsPhiH_->Fill(mot.phi);
    }
    if (phi1.daughterIndices.size() < 2) continue;
    const TTStudy::GenParticle& kaon1 = genParticleBr_->at(phi1.daughterIndices.at(0));
    const TTStudy::GenParticle& kaon2 = genParticleBr_->at(phi1.daughterIndices.at(1));
    if (abs(kaon1.pdgId) != 321 || abs(kaon2.pdgId) != 321) continue;

    TLorentzVector ka1_v;
    ka1_v.SetPtEtaPhiE(kaon1.pt, kaon1.eta, kaon1.phi, kaon1.energy);
    TLorentzVector ka2_v;
    ka2_v.SetPtEtaPhiE(kaon2.pt, kaon2.eta, kaon2.phi, kaon2.energy);
    double d_R = ka1_v.DeltaR(ka2_v);
    genDrKPairH_->Fill(d_R);

    int match_count = 0;
    for (size_t jt = 0; jt < tracksBr->size(); ++jt) {
      const TTStudy::Track& trk = tracksBr->at(jt);
      TLorentzVector trk_k;
      trk_k.SetPtEtaPhiM(trk.pt, trk.eta, trk.phi, ::kmass);
      double d_r1 = trk_k.DeltaR(ka1_v);
      double d_r2 = trk_k.DeltaR(ka2_v);
      if (d_r1 < 0.1 || d_r2 < 0.1) ++match_count; 
    }
    drVsMatchedTrkH_->Fill(d_R, (match_count >= 2?1:0)); 
  }
}
void BsAnalysis::plotGenVertex()
{
  bool bsfilled = false;
  for (size_t it = 0; it < genParticleBr_->size(); ++it) {
    const TTStudy::GenParticle& genp = genParticleBr_->at(it);
    if (abs(genp.pdgId) != 333) continue;

    const TTStudy::GenParticle& moth = genParticleBr_->at(genp.motherIndex);
    //Checking of Bs decay mode 
    if(moth.daughterIndices.size() < 2) continue;
    const TTStudy::GenParticle& Bs_dau1 = genParticleBr_->at(moth.daughterIndices.at(0));
    const TTStudy::GenParticle& Bs_dau2 = genParticleBr_->at(moth.daughterIndices.at(1));
    if (abs(moth.pdgId) != 531 || abs(Bs_dau1.pdgId) != 333 || abs(Bs_dau2.pdgId) != 333) continue;
    
    double vxy = sqrt(pow(genp.vx,2) + pow(genp.vy,2));
    double vz = genp.vz;
    double v = sqrt(pow(genp.vx,2) + pow(genp.vy,2) + pow(genp.vz,2));
    phiVXYH_->Fill(vxy);
    phiVZH_->Fill(vz);
    phiVH_->Fill(v);
    phiV3DH_->Fill(abs(genp.vx),abs(genp.vy),abs(genp.vz)); 

    if (!bsfilled) {
      bsfilled = true;
      vxy = sqrt(pow(moth.vx, 2) + pow(moth.vy, 2));
      vz = moth.vz;
      v = sqrt(pow(moth.vx,2) + pow(moth.vy,2) + pow(moth.vz,2));
      BsVXYH_->Fill(vxy);
      BsVZH_->Fill(vz);
      BsVH_->Fill(v);
      BsV3DH_->Fill(abs(moth.vx),abs(moth.vy),abs(moth.vz));
    }
   
    for (size_t jt = 0; jt < genp.daughterIndices.size(); ++jt) {
      const TTStudy::GenParticle& dau = genParticleBr_->at(genp.daughterIndices.at(jt)); 
      if (abs(dau.pdgId) != 321) continue;
      if (dau.pt < 2.0 || fabs(dau.eta) > 2.5) continue;
      vxy = sqrt(pow(dau.vx, 2) + pow(dau.vy, 2));
      vz = dau.vz;
      v = sqrt(pow(dau.vx,2) + pow(dau.vy,2) + pow(dau.vz,2));
      KaonVXYH_->Fill(vxy);
      KaonVZH_->Fill(vz);
      KaonVH_->Fill(v);
      KaonV3DH_->Fill(abs(dau.vx),abs(dau.vy),abs(dau.vz));
    } 
  }
}
void BsAnalysis::getLV(const vector<TTStudy::Track>* tracksBr, unsigned int indx, TLorentzVector& lv) const {
  const TTStudy::Track& trk = tracksBr->at(indx);
  lv.SetPtEtaPhiM(trk.pt, trk.eta, trk.phi, ::kmass);
}
void BsAnalysis::getTV(const vector<TTStudy::Track>* tracksBr, unsigned int indx, TVector3& v) const {
  const TTStudy::Track& trk = tracksBr->at(indx);
  v.SetPtEtaPhi(trk.pt, trk.eta, trk.phi);
}
double BsAnalysis::genInvMass(const TTStudy::GenParticle& p1, const TTStudy::GenParticle& p2) {
  TLorentzVector lv1;
  lv1.SetPtEtaPhiE(p1.pt, p1.eta, p1.phi, p1.energy);
  TLorentzVector lv2;
  lv2.SetPtEtaPhiE(p2.pt, p2.eta, p2.phi, p2.energy);
  TLorentzVector total = lv1 + lv2;
  return total.M()*1000;
}
void BsAnalysis::saveHistograms() {
  histf_->cd();
  histf_->Write();
  histf_->Close();
}
void BsAnalysis::scaleHistogram(TH1F* th, double fac) {
  for (int i = 1; i < th->GetNbinsX()+1; ++i) {
    double cont = th->GetBinContent(i);
    double err = th->GetBinError(i);
    th->SetBinContent(i, cont*fac);
    th->SetBinError(i, err*fac);
  }
}
double BsAnalysis::getPoissonError(double k, double N){
  double err = TMath::Sqrt(k*(N+k)/TMath::Power(N,3));
  return err;
}	
double BsAnalysis::getBinomailError(double k, double N){
  double err = (1./N) * TMath::Sqrt(k*(1-k/N));
  return err;
}	
void BsAnalysis::printResults(ostream& os) const {
  using namespace std;
  os << "==> Results: " << endl;

  vector<string> slist1 {
    "Events processed",
    "after GenFilter",
    "w/ ntrk >= 4",
    "w/ goodTrk >= 4",
    "w/ goodTrkMatchedKaon >= 4",
  };
  histf_->cd();
  histf_->cd("Main");
  showEfficiency(evcount2H_, slist1, "Track Slection", os);
  
  vector<string> slist {
    "Events processed",
    "after GenFilter",
    "w/ ntrk >= 4",
    "w/ goodTrk >= 4",
    "w/ >= 2 Phi",
    "w/ Phi distinct tracks",
    "w/ Phi dxy & dz2 cut",
    "w/ dR(Phi pair) cut",
    "w/ dR(Track pair) cut",
    "in Bs mass window",
    "with Bs pt > 12 Gev",
    //"with trk Pt Sum > 12 Gev",
    "isolation cut on 4 th track",
    "final gen match"
  };
  histf_->cd();
  histf_->cd("Main");
  showEfficiency(evcountH_, slist, "L1", os);

  if (checkL1Offline_) {
    vector<string> slist_offline {
      "Events selected at L1",
      "w/ ntrk >= 4",
      "w/ >= 2 Phi",
      "w/ Phi distinct tracks",
      "w/ Phi dxy & dz2 cut",
      "w/ dR(Phi pair) cut",
      "w/ dR(Track pair) cut",
      "in Bs mass window",
      "isolation cut on 4 th track",
      "final gen match"
  };
    histf_->cd();
    histf_->cd("Offline");
    showEfficiency(evcountOfflineH_, slist_offline, "Offline", os);
  }
}
bool BsAnalysis::showEfficiency(TH1D* h, 
				const vector<string>& slist, 
				const string& header, 
				ostream& os) const
{
  os << ">>> " << header << " Efficiency" << endl;
  os << setw(64) << "CutFlow"
     << setw(10) << "Events"
     << setw(10) << "AbsEff"
     << setw(10) << "Error"
     << setw(10) << "RelEff"
     << setw(10) << "Error"
     << endl;
  os << fixed << setprecision(3);
  int nbins = h->GetNbinsX();
  if (!studyGen_) --nbins;
  double cont = h->GetBinContent(1);
  for (int i = 1; i <= nbins; ++i) {
    double conti = h->GetBinContent(i);
    double contj = h->GetBinContent(i-1);
    os << setw(64) << slist[i-1]
       << setprecision(1) 
       << setw(10) << conti
       << setprecision(5) 
       << setw(10) << ((cont > 0) ? conti/cont : 0.0)
       << setprecision(3)
       << setw(10) << getBinomailError(conti, cont)
       << setprecision(5)
       << setw(10) << (i == 1 ? 1.0 : (contj > 0) ? conti/contj : 0.0)
       << setprecision(3)
       << setw(10) << getBinomailError(conti, contj)
       << endl;
  }
  if (isSignal_) {
    double k = h->GetBinContent(h->GetNbinsX());
    double N = h->GetBinContent(2);
    double eff = (k/N)*100;
    double err_Poisson = getPoissonError(k,N) * 100;
    double err_Binomial = getBinomailError(k,N) * 100;
    os << "Efficiency for Outer Tracker" << endl;
    os << "Efficiency = " << setprecision(2) << eff 
       << " Poisson Error = " << setprecision(2) << err_Poisson
       << " Binomial error = " << setprecision(2) << err_Binomial
       << endl;
  }
  else {
    double k = h->GetBinContent(h->GetNbinsX()-1);
    double N = h->GetBinContent(1);
    double rate = (k/N) * scaleFactor_;
    double err_Poisson = getPoissonError(k,N) * scaleFactor_;
    double err_Binomial = getBinomailError(k,N) * scaleFactor_;
    os << "Rate for Outer Tracker" << endl;
    os << "Rate in kHz = " << setprecision(2) << rate
       << " Poisson Error = " << setprecision(2) << err_Poisson 
       << " Binomial error = " << setprecision(2) << err_Binomial
       << endl;
  }
  return true;
}
bool BsAnalysis::readJob(const string& jobFile, int& nFiles)
{
  static const int BUF_SIZE = 256;

  // Open the file containing the datacards
  ifstream fin(jobFile.c_str(), ios::in);    
  if (!fin) {
    cerr << "Input File: " << jobFile << " could not be opened!" << endl;
    return false;
  }
  
  char buf[BUF_SIZE];
  vector<string> tokens;
  while (fin.getline(buf, BUF_SIZE, '\n')) {  // Pops off the newline character
    string line(buf);
    if (line.empty() || line == "START") continue;   

    // enable '#' and '//' style comments
    if (line.substr(0,1) == "#" || line.substr(0,2) == "//") continue;
    if (line == "END") break;

    // Split the line into words
    AnaUtil::tokenize(line, tokens);
    int vsize = tokens.size();
    assert(vsize > 1);

    string key   = tokens.at(0);
    string value = tokens.at(1);
    if (key == "dataType") {
      dataType_ = value;
      isSignal_ = (value == "signal" || value == "Signal") ? true : false;
    }
    else if (key == "studyGen") 
      studyGen_ = (stoi(value) > 0) ? true : false;
    else if (key == "studyOffline") 
      studyOffline_ = (stoi(value) > 0) ? true : false;
    else if (key == "checkL1Offline") 
      checkL1Offline_ = (stoi(value) > 0) ? true : false;
    else if (key == "applyIso") 
      applyIso_ = (stoi(value) > 0) ? true : false;
    else if (key == "dumpGenInfo") 
      dumpGenInfo_ = (stoi(value) > 0) ? true : false;
    else if (key == "histFile") 
      histFile_ = value;
    else if (key == "logFile")
      logFile_ = value;
    else if (key == "maxEvent") 
      maxEvt_ = stoi(value);
    else if (key == "verbosity") 
      verbosity_ = stoi(value);
    else if (key == "applyTrackQuality")
      applyTrkQuality_ = (stoi(value) > 0) ? true : false;
    else if (key == "inputFile") 
      AnaUtil::buildList(tokens, fileList_);
    else
      AnaUtil::storeCuts(tokens, hmap_);

    tokens.clear();
  }

  // Close the file
  fin.close();

  // Build the chain of root files
  for (auto it  = fileList_.begin(); it != fileList_.end(); ++it) {
    string fname = *it;
    cout << ">>> INFO. Adding input file " << fname << " to TChain " << endl;
    ++nFiles;
    int nevt = setInputFile(fname.c_str());
    if (maxEvt_ > 0 && nevt >= maxEvt_) break;
  }

  if (!nFiles) {
    cerr << ">>> WARN. Input Root file list is empty! exiting ..." << endl;
    return false;
  }
  printJob();
  return true;
}
void BsAnalysis::printJob(ostream& os) const
{
  os << "       datatype = " << dataType_ << endl
     << "        logFile = " << logFile_ << endl 
     << "       histFile = " << histFile_ << endl
     << "      verbosity = " << verbosity_ << endl
     << "       maxEvent = " << maxEvt_ << endl
     << "applyTrkQuality = " << boolalpha << applyTrkQuality_ << endl
     << "       studyGen = " << boolalpha << studyGen_ << endl
     << "   studyOffline = " << boolalpha << studyOffline_ << endl
     << " checkL1Offline = " << boolalpha << checkL1Offline_ << endl
     << "       applyIso = " << boolalpha << applyIso_ << endl
     << "    dumpGenInfo = " << boolalpha << dumpGenInfo_ << endl;

  // InputFiles
  if (chain_) {
    TObjArray* fileElements = chain_->GetListOfFiles();
    os << ">>> INFO. nFiles: " << fileElements->GetEntries() 
       << ", Files to analyse:" 
       << endl;
    TIter next(fileElements);
    TChainElement* chEl = 0;
    while (( chEl = dynamic_cast<TChainElement*>(next()) ))
      os << chEl->GetTitle() 
         << endl;
  }
  else
    AnaUtil::showList(fileList_, ">>> INFO. inputFiles", os);

  AnaUtil::showCuts(hmap_, os);
}
int BsAnalysis::setInputFile(const string& fname) 
{
  size_t found = fname.find("root:");
  if (found == string::npos && gSystem->AccessPathName(fname.c_str())) {
    cerr << ">>> Warning: File <<" << fname << ">> was not found!!" << endl;
    return static_cast<int>(chain_->GetEntries()); 
  }
  chain_->AddFile(fname.c_str(), -1);
  return static_cast<int>(chain_->GetEntries()); 
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " jobFile " << endl;
    exit(0);
  }     
  string jobFile(argv[1]);

  gROOT->SetBatch(kTRUE);
  
  // Create analysis object 
  cout << "=== Start of Analysis === " << endl;

  // Create  analysis object 
  BsAnalysis ana;
  ana.count0 = 0;
  ana.count1 = 0;
  ana.count2 = 0;

  // Read job input
  int nFiles = 0;
  bool succeed = ana.readJob(jobFile, nFiles);
  if (!succeed) {
    cerr << "Failed to read the job card successfully, exiting ...!" << endl;
    exit(1);
  }
  if (ana.getEntries() <= 0) {
    cerr << "No events present in the input chain, exiting ...!" << endl;
    exit(2);
  }
  
  gROOT->SetBatch(kTRUE);
  
  // Now go
  TStopwatch timer;
  cout << "Start event loop now with " << nFiles << " file(s)" << endl;
  timer.Start();
  if (!ana.beginJob()) {
    cerr << "beginJob() failed, exiting ...!" << endl;
    exit(3);
  }
  ana.eventLoop();
  ana.endJob();
  ana.closeFiles();
  cout << "=== End of Analysis === " << endl;

  timer.Stop();
  cout << "Realtime/CpuTime = " << timer.RealTime() << "/" << timer.CpuTime() << endl;
  cout << "Count0 = "<< ana.count0 << endl;
  cout << "Count1 = "<< ana.count1 << endl;
  cout << "Count2 = "<< ana.count2 << endl;
  return 0;
}
