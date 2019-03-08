#define NEL(x) (sizeof((x))/sizeof((x)[0]))

#include <set>
#include <cassert>
#include <algorithm>
#include <cmath>

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
  : chain_(new TChain("ttAnalysis/ElectronTriggerInfo")),
    outputFile_(nullptr),
    dataType_("signal"),
    isSignal_(true),
    studyGen_(false),
    dumpGenInfo_(false),
    studyOffline_(false),
    verbosity_(0),
    applyTrkQuality_(false),
    eventBr_(new TTStudy::Event()),
    simTracksBr_(new std::vector<TTStudy::SimTrack>()),
    tracksBr_(new std::vector<TTStudy::Track>()),
    genParticleBr_(nullptr),
    bookedHistograms_(false)
{
  cout << "=== Start of Analysis === " << endl;
  fileList_.clear();
}
bool BsAnalysis::beginJob()
{
  outputFile_ = TFile::Open(histFile_.c_str(), "RECREATE");

  // create vectors to hold branches
  if (studyGen_) genParticleBr_ = new std::vector<TTStudy::GenParticle>();
  nEvents_ = static_cast<int>(chain_->GetEntries()); 
  if (nEvents_ <= 0) {
    cerr << "******* nEvents = " << nEvents_ << ", returning!" << endl;
    return false;
  }
  if (maxEvt_ > 0) nEvents_ = std::min(nEvents_, maxEvt_);
  cout << " >>> nEvents = " << nEvents_ << endl;

  openFiles();
  printJob(fLog_);
  
  bookHistograms();
  setTreeBranches();

  scaleFactor_ = 30000; // 30MHz, used for rate calculation
  std::cout << std::setiosflags(std::ios::fixed);
  std::cout << std::setprecision(2);

  return true;
}
void BsAnalysis::endJob() {
  printResults();
  printResults(fLog_);

  // close text files
  closeFiles();

  // and finally 
  saveHistograms();
}
bool BsAnalysis::openFiles() 
{
  fLog_.open(logFile_.c_str(), ios::out);
  if (!fLog_) {
    cerr << "File: " << logFile_ << " could not be opened!" << endl;
    return false;
  }
  fLog_ << setiosflags(ios::fixed);

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
}
BsAnalysis::~BsAnalysis() {
  if (eventBr_) delete eventBr_;
  if (simTracksBr_) delete simTracksBr_;
  if (tracksBr_) delete tracksBr_;
  if (studyGen_ && genParticleBr_) delete genParticleBr_;
}
void BsAnalysis::bookHistograms() {

  outputFile_->cd();
  evcountH_ = new TH1F("evcount", "event selection counter", 10, -0.5, 9.5);

  // Outer Track
  ntrkH_             = new TH1F("ntrk", "No of tracks before any selection", 400, 0, 1000);
  trkVertexZH_       = new TH1F("trkvertexZ","vertex Z of the tracks", 1000, -2, 2);
  trkVertexXYH_      = new TH1F("trkvertexXY","vertex XY of the tracks", 1000, 0, 1);
  trkPtH_            = new TH1F("trkPt","Track Pt", 20, 1.5, 3.5);
  trkChi2H_          = new TH1F("trkChi2", "Track Chi Square", 200, 0, 20);  
  dzTrackPairH_      = new TH1F("dzTrackPair", "dz between a pair of tracks", 100, -1, 1);
  dzTrackPair2H_     = new TH1F("dzTrackPair2", "dz between a pair of tracks", 100, -0.2, 0.2);
  dxyTrackPairH_     = new TH1F("dxyTrackPair", "dxy between a pair of tracks", 100, 0, 1);
  dxyTrackPair2H_    = new TH1F("dxyTrackPair2", "dxy between a pair of tracks", 100, 0, 0.2);
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
  trk4PtH_           = new TH1F("trk4Pt", "Lowest pT kaon pt of the 1st Bs candidate", 50, 0, 10);

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
  isol1H_            = new TH1F("isol1", "Isolation of the first selected track", 100, 0, 0.5); 
  isol2H_            = new TH1F("isol2", "Isolation of the second selected track", 100, 0, 0.5); 
  isol3H_            = new TH1F("isol3", "Isolation of the third selected track", 100, 0, 0.5); 
  isol4H_            = new TH1F("isol4", "Isolation of the fourth selected track", 100, 0, 0.5); 

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
    phiVZH_    = new TH1F("phiVZ","VertexZ for the Gen Level Phis", 200, -10, 10);
    BsVXYH_    = new TH1F("BsVXY","VertexXY for the Gen level Bs", 200, 0, 2);
    BsVZH_     = new TH1F("BsVZ","VertexZ for the Gen Level Bs", 200, -10, 10);
    
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
  bookedHistograms_ = true;
}
void BsAnalysis::setTreeBranches() {
  chain_->SetBranchAddress("Event", &eventBr_);
  chain_->SetBranchAddress("SimTrack", &simTracksBr_);

  if (studyGen_) chain_->SetBranchAddress("GenParticle", &genParticleBr_);

  std::cout << "Offline Track Option = " << std::boolalpha << studyOffline_ << std::endl;
  if (studyOffline_)
    chain_->SetBranchAddress("RecoTrack", &tracksBr_);
  else
    chain_->SetBranchAddress("L1Track", &tracksBr_);

  nEntries_ = chain_->GetEntriesFast();
  if (nEntries_ > 0) scaleFactor_ = scaleFactor_/(nEntries_*1.0);
}
void BsAnalysis::clearEvent() {
  simTracksBr_->clear();
  tracksBr_->clear();
  if (studyGen_ && genParticleBr_) genParticleBr_->clear();
}
void BsAnalysis::clearLists() {
  phiCandList_.clear();
  bsList_.clear();
}
void BsAnalysis::clearGenLists() {
  genKaonList_.clear();
  genPhiCandList_.clear();
}
void BsAnalysis::eventLoop() {
  double minGenPt = 2.0;
  int nPrint = std::max(5000L, nEntries_/5000);

  ulong nbytes = 0;
  for (long jentry = 0; jentry < nEntries_; ++jentry) {
    // reset
    clearEvent(); // vectors for branches
    clearGenLists(); // other global lists related to Generator level

    long ientry = chain_->LoadTree(jentry);
    if (ientry < 0) break;
    ulong nb = chain_->GetEntry(jentry); 
    nbytes += nb;
    
    // Show the status 
    if (jentry%nPrint == 0)
    std::cout << " ==> " << chain_->GetCurrentFile()->GetName() 
		<< " <<< Run. " << eventBr_->run 
		<< " Event. " << std::setw(9) << eventBr_->event 
		<< " >>> Events proc. " << std::setw(9) << jentry
		<< std::endl;

    if (verbosity_ > 2) {
      std::cout << "Entry#: " << jentry 
		<< ", # of GenParticles: " << genParticleBr_->size()
		<< ", # of tracks:" << tracksBr_->size() 
		<< std::endl;
    }
    evcountH_->Fill(0);
    
   
    // Add a genfilter to select signal events with 2 phi (Kaon pt >= 2GeV)
    if (studyGen_ && !genFilter(minGenPt)) continue;
    evcountH_->Fill(1);
 
    if (studyGen_) {
      readGenParticle();
      fillGenInfo();
      plotGen(tracksBr_); 
    }
    
    ntrkH_->Fill(tracksBr_->size());
    if (tracksBr_->size() < 4) continue;
    evcountH_->Fill(2);
    
    if (verbosity_ > 1) printTrackProperties(tracksBr_);

    // Outer tracks
    clearLists(); // other global lists related to detector level
    bool selection_status = selectEvent(trkSelCutMap_, phiSelCutMap_, bsSelCutMap_, tracksBr_, 2, 0);
    bsCandListH_->Fill(bsList_.size());
    if (selection_status) {
      std::vector<TLorentzVector> kaonList;
      getKaonList(tracksBr_, bsList_[0], kaonList);
      fillKaonInfo(kaonList);
      fillKaonTrackInfo(tracksBr_, bsList_[0]);
      computeIsolation(tracksBr_, bsList_[0]);
    }
  }
}
bool BsAnalysis::selectEvent(const std::map<std::string, double>& trkCutMap,
			     const std::map<std::string, double>& phiCutMap, 
			     const std::map<std::string, double>& bsCutMap, 
			     const std::vector<TTStudy::Track>* trackList, int ishift, int indx) {
  bool event_status = false;
  std::vector<PhiInfo> phiList;
  findPhiCandidates(trkCutMap, phiCutMap, trackList, phiList, indx);
  nPhiCandH_->Fill(phiList.size());

  if (phiList.size() < 2) return event_status;

  evcountH_->Fill(ishift + 1);
  int ecounters[] = {0, 0, 0, 0, 0, 0};
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
      
      const TLorentzVector& phiv1 = info_i.v;
      const TLorentzVector& phiv2 = info_j.v;
      TLorentzVector bsv = phiv1 + phiv2;
      double bsmass = bsv.M();
      
      // The pair of Phi's must come from the same vertex
      double dxy, dz;
      BsAnalysis::calculateDeltaPos(info_i, info_j, dxy, dz);
      dxyPhiPairH_->Fill(dxy);
      dzPhiPairH_->Fill(dz);
      
      if (dxy > AnaUtil::cutValue(bsCutMap, "maxPhiPairDxy") || 
	  std::fabs(dz) >AnaUtil::cutValue(bsCutMap, "maxPhiPairDz")) continue;
      ++ecounters[1];
      
      double dr = phiv1.DeltaR(phiv2);
      drPhiPairH_->Fill(dr);
      if (dr < AnaUtil::cutValue(bsCutMap, "minPhiPairDr") || dr > AnaUtil::cutValue(bsCutMap, "maxPhiPairDr")) continue;
      ++ecounters[2];
      
      double drTrkPhi2 = info_j.dr;
      drPhi1TrackPairH_->Fill(drTrkPhi1);
      drPhi2TrackPairH_->Fill(drTrkPhi2);
      if (drTrkPhi1 > AnaUtil::cutValue(bsCutMap, "maxPhiTrkDr") || drTrkPhi2 > AnaUtil::cutValue(bsCutMap, "maxPhiTrkDr")) continue;
      ++ecounters[3];
      
      bsmass0H_->Fill(bsmass);
      bsmassH_->Fill(bsmass);
      if (bsmass < AnaUtil::cutValue(bsCutMap, "massLow") || bsmass > AnaUtil::cutValue(bsCutMap, "massHigh")) continue;
      ++ecounters[4];
      
      BsInfo bsInfo;
      bsInfo.phi1 = info_i;
      bsInfo.phi2 = info_j;
      bsList_.push_back(bsInfo);
      
      // Selected Phi pT
      phi1PtH_->Fill(phiv1.Pt());
      phi2PtH_->Fill(phiv2.Pt());
      phiPtH_->Fill(phiv1.Pt(), phiv2.Pt());
      
      // Track pair for each Phi
      dxyPhi1TrackPairH_->Fill(info_i.dxy);
      dzPhi1TrackPairH_->Fill(info_i.dz);
      
      dxyPhi2TrackPairH_->Fill(info_j.dxy);
      dzPhi2TrackPairH_->Fill(info_j.dz);
      
      // Final Gen Match
      if (studyGen_) {
	if (verbosity_) 
	  std::cout << ">>> B_s # " << bsList_.size() << ", mass: " << bsmass << " GeV" << std::endl;
	
	std::vector<TLorentzVector> kaonList;
	getKaonList(trackList, bsInfo, kaonList);
	int n_match = doTrkGenMatch(kaonList);
	if (n_match == 4) ++ecounters[5];
      }
    }
  }
  for (size_t i = 0; i < NEL(ecounters); ++i)
      if (ecounters[i] > 0) evcountH_->Fill(ishift + 2 + i);

  return (ecounters[4] > 0);
}
void BsAnalysis::findPhiCandidates(const std::map<std::string, double>& trkCutMap, 
				   const std::map<std::string, double>& phiCutMap, 
				   const std::vector<TTStudy::Track>* trackList, 
				   std::vector<PhiInfo>& phiList, int indx) 
{  
  // Loop over tracks
  for (size_t it = 0; it < trackList->size(); ++it) {
    const TTStudy::Track& trk1 = trackList->at(it);

    double vertexXY = std::sqrt(std::pow(trk1.vertexX, 2) + std::pow(trk1.vertexY, 2));
    trkVertexXYH_->Fill(vertexXY);
    trkVertexZH_->Fill(trk1.vertexZ);
    trkPtH_->Fill(trk1.pt);
    trkChi2H_->Fill(trk1.chiSquare);
    
    if (0) std::cout << "pT: "      << trk1.eta << "/" << AnaUtil::cutValue(trkCutMap, "maxTrkEta") << std::endl
                     << "pT: "      << trk1.pt << "/" << AnaUtil::cutValue(trkCutMap, "minTrkPt") << std::endl
		     << "chi2: "    << trk1.chiSquareRed << "/" << AnaUtil::cutValue(trkCutMap, "maxTrkChi2") << std::endl
		     << "nStub: "   << trk1.nStub << "/" << AnaUtil::cutValue(trkCutMap, "minTrkLayers") << std::endl
		     << "nStubPS: " << trk1.nStub_PS << "/" << AnaUtil::cutValue(trkCutMap, "minTrkPSLayers") << std::endl;

    // pseudo-rapidity cut
    if (std::fabs(trk1.eta) > AnaUtil::cutValue(trkCutMap, "maxTrkEta")) continue;
    if (trk1.pt < AnaUtil::cutValue(trkCutMap, "minTrkPt")) continue;
    if (applyTrkQuality_ && (trk1.chiSquareRed > AnaUtil::cutValue(trkCutMap, "maxTrkChi2") || 
   			     trk1.nStub < AnaUtil::cutValue(trkCutMap, "minTrkLayers") ||
   			     trk1.nStub_PS < AnaUtil::cutValue(trkCutMap, "minTrkPSLayers"))) continue;

    TLorentzVector trkv1;  
    trkv1.SetPtEtaPhiM(trk1.pt, trk1.eta, trk1.phi, ::kmass);

    for (size_t jt = it+1; jt < trackList->size(); ++jt) {
      const TTStudy::Track& trk2 = trackList->at(jt);
      
      // pseudo-rapidity cut
      if (std::fabs(trk2.eta) > AnaUtil::cutValue(trkCutMap, "maxTrkEta")) continue;
      if (trk2.pt < AnaUtil::cutValue(trkCutMap, "minTrkPt")) continue;
      if (applyTrkQuality_ && (trk2.chiSquareRed > AnaUtil::cutValue(trkCutMap, "maxTrkChi2") || 
      			       trk2.nStub < AnaUtil::cutValue(trkCutMap, "minTrkLayers") ||
      			       trk2.nStub_PS < AnaUtil::cutValue(trkCutMap, "minTrkPSLayers"))) continue;
      
      // opposite charge
      if (std::signbit(trk1.curvature) == std::signbit(trk2.curvature)) continue;
      
      // the track pair must come from the same vertex
      double dxy, dz;
      BsAnalysis::calculateDeltaPos(trk1, trk2, dxy, dz);
      
      dzTrackPairH_->Fill(dz);
      dzTrackPair2H_->Fill(dz);
      // First apply |dz|(track-pair) cut
      if (std::fabs(dz) > AnaUtil::cutValue(phiCutMap, "maxTrkPairDz")) continue;
      
      dxyTrackPairH_->Fill(dxy);
      dxyTrackPair2H_->Fill(dxy);
      // Then apply dxy(track-pair) cut
      if (dxy > AnaUtil::cutValue(phiCutMap, "maxTrkPairDxy")) continue;
      
      TLorentzVector trkv2;
      trkv2.SetPtEtaPhiM(trk2.pt, trk2.eta, trk2.phi, ::kmass);
   
      // select mass window
      TLorentzVector phiLV = trkv1 + trkv2;
      double mass = phiLV.M();
      phimass0H_->Fill(mass);
      phimassH_->Fill(mass);
      
      if (AnaUtil::cutValue(phiCutMap, "massLow") <= mass && mass <= AnaUtil::cutValue(phiCutMap, "massHigh")) {
        // keep track of each phi candidate
        std::vector<TLorentzVector> list;
        list.push_back(trkv1);
        list.push_back(trkv2);
        phiCandList_.push_back(list);
        double dr = trkv1.DeltaR(trkv2);
        drTrackPairH_->Fill(dr);
	phiCandPtH_->Fill(phiLV.Pt());
	
        // Fill PhiInfo
        PhiInfo info;
        info.indx1 = it;
        info.indx2 = jt;
        info.dmass = std::fabs(::phi_polemass - mass);
	
        info.dxy = dxy;
        info.dz = dz;
        info.dr = dr;
        info.v = phiLV;
        info.vertexX = 0.5 * (trk1.vertexX + trk2.vertexX);
        info.vertexY = 0.5 * (trk1.vertexY + trk2.vertexY);
        info.vertexZ = 0.5 * (trk1.vertexZ + trk2.vertexZ);
	
        phiList.push_back(info);
      }
    }
  }
}
void BsAnalysis::checkPhiKaonBs(const PhiInfo& info_i, const PhiInfo& info_j, const std::vector<TTStudy::Track>* trackList) {
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
        dpt_phi1  = std::fabs(info_i.v.Pt() - philv.Pt());
        deta_phi1 = std::fabs(info_i.v.Eta() - philv.Eta());
        dphi_phi1 = info_i.v.DeltaPhi(philv);
      }
      if (dr_2 < min_dr_phi2) {
        min_dr_phi2 = dr_2;
        dpt_phi2  = std::fabs(info_j.v.Pt() - philv.Pt());
        deta_phi2 = std::fabs(info_j.v.Eta() - philv.Eta());
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
          dpt1  = std::fabs(kaon1.Pt() - kaonlv.Pt());
          deta1 = std::fabs(kaon1.Eta() - kaonlv.Eta());
          dphi1 = kaon1.DeltaPhi(kaonlv);
        }
        if (dr_2 < min_dr_kaon2) {
          min_dr_kaon2 = dr_2;
          dpt2  = std::fabs(kaon2.Pt() - kaonlv.Pt());
          deta2 = std::fabs(kaon2.Eta() - kaonlv.Eta());
          dphi2 = kaon2.DeltaPhi(kaonlv);
        }
        if (dr_3 < min_dr_kaon3) {
          min_dr_kaon3 = dr_3;
          dpt3  = std::fabs(kaon3.Pt() - kaonlv.Pt());
          deta3 = std::fabs(kaon3.Eta() - kaonlv.Eta());
          dphi3 = kaon3.DeltaPhi(kaonlv);
        }
        if (dr_4 < min_dr_kaon4) {
          min_dr_kaon4 = dr_4;
          dpt4  = std::fabs(kaon4.Pt() - kaonlv.Pt());
          deta4 = std::fabs(kaon4.Eta() - kaonlv.Eta());
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
void BsAnalysis::getKaonList(const std::vector<TTStudy::Track>* trackList, const BsInfo& bsinfo, std::vector<TLorentzVector>& kaonList) {
  TLorentzVector lv;
  getLV(trackList, bsinfo.phi1.indx1, lv);
  kaonList.push_back(lv);
  
  getLV(trackList, bsinfo.phi1.indx2, lv);
  kaonList.push_back(lv);
  
  getLV(trackList, bsinfo.phi2.indx1, lv);
  kaonList.push_back(lv);
  
  getLV(trackList, bsinfo.phi2.indx2, lv);
  kaonList.push_back(lv);

  std::sort(kaonList.begin(), kaonList.end(), LVPtComparator());
}
void BsAnalysis::fillKaonTrackInfo(const std::vector<TTStudy::Track>* tracksBr, const BsInfo& bsinfo) {
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
    std::cout << "Track 1 - chi2, nstub: " << trk1.chiSquare << ", " << trk1.nStub << std::endl
              << "Track 2 - chi2, nstub: " << trk2.chiSquare << ", " << trk2.nStub << std::endl
              << "Track 3 - chi2, nstub: " << trk3.chiSquare << ", " << trk3.nStub << std::endl
              << "Track 4 - chi2, nstub: " << trk4.chiSquare << ", " << trk4.nStub << std::endl;
  }
}
void BsAnalysis::computeIsolation(const std::vector<TTStudy::Track>* tracksBr, const BsInfo& bsinfo, double cone) {
  const TTStudy::Track& trk1 = tracksBr->at(bsinfo.phi1.indx1);    
  TLorentzVector trk1_lv;
  trk1_lv.SetPtEtaPhiM(trk1.pt, trk1.eta, trk1.phi, ::kmass);

  const TTStudy::Track& trk2 = tracksBr->at(bsinfo.phi1.indx2);    
  TLorentzVector trk2_lv;
  trk2_lv.SetPtEtaPhiM(trk2.pt, trk2.eta, trk2.phi, ::kmass);

  const TTStudy::Track& trk3 = tracksBr->at(bsinfo.phi2.indx1);    
  TLorentzVector trk3_lv;
  trk3_lv.SetPtEtaPhiM(trk3.pt, trk3.eta, trk3.phi, ::kmass);

  const TTStudy::Track& trk4 = tracksBr->at(bsinfo.phi2.indx2);    
  TLorentzVector trk4_lv;
  trk4_lv.SetPtEtaPhiM(trk4.pt, trk4.eta, trk4.phi, ::kmass);

  double isol1 = 0.0,
    isol2 = 0.0,
    isol3 = 0.0,
    isol4 = 0.0;
  for (size_t it = 0; it < tracksBr->size(); ++it) {
    const TTStudy::Track& trk = tracksBr->at(it);
    TLorentzVector trk_lv;
    trk_lv.SetPtEtaPhiM(trk.pt, trk.eta, trk.phi, ::kmass); 
    if ( AnaUtil::sameObject(trk_lv, trk1_lv) || 
	 AnaUtil::sameObject(trk_lv, trk2_lv) || 
	 AnaUtil::sameObject(trk_lv, trk3_lv) || 
	 AnaUtil::sameObject(trk_lv, trk4_lv) ) continue;
  
    double dR_1 = trk_lv.DeltaR(trk1_lv);
    double dR_2 = trk_lv.DeltaR(trk2_lv);
    double dR_3 = trk_lv.DeltaR(trk3_lv);
    double dR_4 = trk_lv.DeltaR(trk4_lv);

    if (dR_1 < cone) isol1 += trk.pt;
    if (dR_2 < cone) isol2 += trk.pt;
    if (dR_3 < cone) isol3 += trk.pt;
    if (dR_4 < cone) isol4 += trk.pt;
  }
  isol1 /= trk1.pt;
  isol2 /= trk2.pt;
  isol3 /= trk3.pt;
  isol4 /= trk4.pt;

  isol1H_->Fill(isol1); 
  isol2H_->Fill(isol2); 
  isol3H_->Fill(isol3); 
  isol4H_->Fill(isol4); 
}
void BsAnalysis::fillKaonInfo(const std::vector<TLorentzVector>& kaonList) {
  if (verbosity_ > 1) { 
    std::cout << std::setw(10) << "No." 
	      << std::setw(10) << "Pt" 
	      << std::setw(10) << "Eta" 
	      << std::setw(10) << "Phi" 
	      << std::endl;
    int i = 0;
    for (auto& v: kaonList) {
      std::cout << std::setw(10) << i++ 
		<< std::setw(10) << v.Pt()
		<< std::setw(10) << v.Eta() 
		<< std::setw(10) << v.Phi()
		<< std::endl;
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
    const TLorentzVector& kaon1 = kaonList.at(i);
    for (size_t j = i+1; j < kaonList.size(); ++j) {
      const TLorentzVector& kaon2 = kaonList.at(j);
      double dr = kaon1.DeltaR(kaon2);
      drKaonPairH_->Fill(dr);
    }
  }
}
void BsAnalysis::fillGenInfo() {
  std::sort(genKaonList_.begin(), genKaonList_.end(), PtComparator<TTStudy::GenParticle>());
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
  
  std::sort(genPhiCandList_.begin(), genPhiCandList_.end(), PtComparator<TTStudy::GenParticle>());
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
void BsAnalysis::checkConsistency(const std::vector<TTStudy::Track>* tracksBr, int ntrk) const {
  if (ntrk <= 4) return;
  printTrackProperties(tracksBr);

  std::cout << "===== Reading GenParticles ========================================" << std::endl;
  std::cout << "index       pT      eta      phi       vx       vy      vz      pdgID" << std::endl;
  for (size_t i = 0; i != genParticleBr_->size(); ++i) {
    const TTStudy::GenParticle& genp = genParticleBr_->at(i);
    if (genp.status == 1 && genp.pt > 1.95)
      printGenParticle(i);
  }
}
void BsAnalysis::checkMatchingPhi(int ntrk) const {
  if (verbosity_ > 1) 
    std::cout << "# of Phi, detector level: " << phiCandList_.size() 
	      << " Gen level:" << genPhiCandList_.size()
	      << " #tracks: " << ntrk
	      << std::endl;
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
      std::cout << "MATCH phi candidate: " << it << ", gen phi: " << m_index 
		<< " deltaR[" << it << "," << m_index << "] = " << drmin
		<< std::endl;
    }
  }
}
void BsAnalysis::printTrackProperties(const std::vector<TTStudy::Track>* tracksBr) const {
  std::cout << "===== Reading Tracks ========================================" << std::endl;
  std::cout << "index       pT      eta      phi       vx       vy      vz" << std::endl;
  std::cout << std::setprecision(3);
  for (size_t i = 0; i != tracksBr->size(); i++)
    printTrk(tracksBr, i);
}
void BsAnalysis::printTrk(const std::vector<TTStudy::Track>* tracksBr, size_t i) const {
  const TTStudy::Track& trk = tracksBr->at(i);
  std::cout << std::setw(5) << i 
	    << std::setw(9) << trk.pt
	    << std::setw(9) << trk.eta
	    << std::setw(9) << trk.phi
	    << std::setw(9) << trk.vertexX 
	    << std::setw(9) << trk.vertexY
	    << std::setw(9) << trk.vertexZ
	    << std::endl;
}
void BsAnalysis::plotSignalProperties(const std::vector<TTStudy::Track>* tracksBr) {
  std::vector<TTStudy::Track> list;
  int central = 0;
  int fwd = 0;
  for (size_t it = 0; it < tracksBr->size(); ++it) {
    const TTStudy::Track& trk = tracksBr->at(it);
    if (trk.pt < 2) continue;
    /*allDXYPVH_->Fill(trk.dxyWrtPV);
    allDZPVH_->Fill(trk.dzWrtPV);
    allDXYH_->Fill(trk.d0);
    allDZH_->Fill(trk.dz);
    all2DH_->Fill(trk.dxyWrtPV,trk.dzWrtPV);*/ 
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
      double vertexXY = std::sqrt(std::pow(trk.vertexX, 2) + std::pow(trk.vertexY, 2));
      signal_VXYH_->Fill(vertexXY);
      signal_chiH_->Fill(trk.chiSquare);
      list.push_back(trk);
      if (std::fabs(trk.eta) < 1.1) central++;
      if (std::fabs(trk.eta) < 2.5 && std::fabs(trk.eta) > 1.1) fwd++;
      TTStudy::GenParticle& kaon = genKaonList_.at(m_index);
      double d_pt = std::fabs(trk.pt - kaon.pt);
      signalDPT_H->Fill(d_pt);
    }
  }
  signalNtrkH_->Fill(list.size());
  signalCentralH_->Fill(central);
  signalFwdH_->Fill(fwd);
  std::sort(list.begin(), list.end(), PtComparator<TTStudy::Track>());
  if (list.size() > 0) signalPt1H_->Fill(list[0].pt);
  if (list.size() > 1) signalPt2H_->Fill(list[1].pt);
  if (list.size() > 2) signalPt3H_->Fill(list[2].pt);
  if (list.size() > 3) signalPt4H_->Fill(list[3].pt);

  for (size_t i = 0; i < list.size(); ++i) {
    const TTStudy::Track& trk1 = list[i];
    /*signalDXYPVH_->Fill(trk1.dxyWrtPV);
    signalDZPVH_->Fill(trk1.dzWrtPV);
    signal2DH_->Fill(trk1.dxyWrtPV,trk1.dzWrtPV); 
    signalDXYH_->Fill(trk1.d0);
    signalDZH_->Fill(trk1.dz);*/
    TLorentzVector trkv1;
    trkv1.SetPtEtaPhiM(trk1.pt, trk1.eta, trk1.phi, ::kmass);
    for(size_t j = i+1; j < list.size(); j++) {
      const TTStudy::Track& trk2 = list[j];
      TLorentzVector trkv2;
      trkv2.SetPtEtaPhiM(trk2.pt, trk2.eta, trk2.phi, ::kmass);
      TLorentzVector phi = trkv1 + trkv2;
      signalPhiMH_->Fill(phi.M());
    }
  }
}
int BsAnalysis::doTrkGenMatch(const std::vector<TLorentzVector>& kaonList) {
  if (verbosity_ > 1)
    std::cout << "index       pT      eta      phi matched genindx      pdgID       dR      dpT     dEta     dPhi"
	      << std::endl;
            
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
      delta_pt  = std::fabs(trk_kaon_v.Pt() - kaon.pt);
      delta_eta = std::fabs(trk_kaon_v.Eta() - kaon.eta);
      delta_phi = std::fabs(trk_kaon_v.DeltaPhi(gen_kaon_v));
      gen_pdgID = kaon.pdgId;
    } 
    if (verbosity_ > 1)
      std::cout << std::setprecision(3)
		<< std::setw(5)  << itrk++
		<< std::setw(9)  << trk_kaon_v.Pt()
		<< std::setw(9)  << trk_kaon_v.Eta()
		<< std::setw(9)  << trk_kaon_v.Phi()
		<< std::setw(8)  << match
		<< std::setw(8)  << m_index
		<< std::setw(11) << gen_pdgID
		<< std::setprecision(4)
		<< std::setw(9)  << min_dr
		<< std::setw(9)  << delta_pt
		<< std::setw(9)  << delta_eta
		<< std::setw(9)  << delta_phi
		<< std::endl;           
  } 
  if (verbosity_ > 1) {
    std::cout << std::setprecision(2);
    std::cout << "Match Counter# " << m_counter << std::endl;
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
  std::cout << std::setw(5) << i
            << std::setw(9) << p.pt
	    << std::setw(9) << p.eta
	    << std::setw(9) << p.phi
	    << std::setw(9) << p.vx
	    << std::setw(9) << p.vy
	    << std::setw(9) << p.vz
	    << std::setw(11) << p.pdgId
	    << std::endl;
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
  dxy = std::sqrt(std::pow(trki.vertexX - trkj.vertexX, 2) + std::pow(trki.vertexY - trkj.vertexY, 2));
  dz  = trki.vertexZ - trkj.vertexZ;
}
void BsAnalysis::calculateDeltaPos(const PhiInfo& infoi, const PhiInfo& infoj, double& dxy, double& dz) {
  dxy = std::sqrt(std::pow(infoi.vertexX - infoj.vertexX, 2) + std::pow(infoi.vertexY - infoj.vertexY, 2));
  dz  = infoi.vertexZ - infoj.vertexZ;
}
bool BsAnalysis::genFilter(double minPt) const {
  std::vector<TTStudy::GenParticle> list;
  //std::cout<<" Event no = "<<eventBr_->event<<std::endl;
  for (size_t it = 0; it < genParticleBr_->size(); ++it) {
    //if (it == 188217) continue;
    const TTStudy::GenParticle& genp = genParticleBr_->at(it);
    //std::cout<<" Particle no = "<<it<<" Particle Id = "<<genp.pdgId<<std::endl;
    if (std::abs(genp.pdgId) != 333) continue;  // Phi 

    const TTStudy::GenParticle& pgenp = genParticleBr_->at(genp.motherIndex);
    if (std::abs(pgenp.pdgId) != 531) continue; // Bs

    if (genp.daughterIndices.size() < 2) continue;
    const TTStudy::GenParticle& kaon1 = genParticleBr_->at(genp.daughterIndices.at(0));
    const TTStudy::GenParticle& kaon2 = genParticleBr_->at(genp.daughterIndices.at(1));
    if (std::abs(kaon1.pdgId) != 321 || std::abs(kaon2.pdgId) != 321) continue;
    genKPtCheckH_->Fill(kaon1.pt);
    genKPtCheckH_->Fill(kaon2.pt);
    if( kaon1.pt < minPt || kaon2.pt < minPt) continue;
    list.push_back(genp);
  }

  if (list.size() >= 2) return true;
  return false;
}
void BsAnalysis::readGenParticle() {
  for (size_t it = 0; it < genParticleBr_->size(); ++it) {
    const TTStudy::GenParticle& genp = genParticleBr_->at(it);
    if (std::abs(genp.pdgId) != 333) continue;

    const TTStudy::GenParticle& mot = genParticleBr_->at(genp.motherIndex);
    if (std::abs(mot.pdgId) != 531) continue;
    genPhiCandList_.push_back(genp); 

    if (genp.daughterIndices.size() < 2) continue;
    const TTStudy::GenParticle& kaon1 = genParticleBr_->at(genp.daughterIndices.at(0));
    const TTStudy::GenParticle& kaon2 = genParticleBr_->at(genp.daughterIndices.at(1));
    if (std::abs(kaon1.pdgId) != 321 || std::abs(kaon2.pdgId) != 321) continue;
    genKaonList_.push_back(kaon1);
    genKaonList_.push_back(kaon2);
  }
}
void BsAnalysis::plotGen(const std::vector<TTStudy::Track>* tracksBr) {
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
      if (std::abs(mot.pdgId) != 531) continue;
      genBsPtH_->Fill(mot.pt);
      genBsEtaH_->Fill(mot.eta);
      genBsPhiH_->Fill(mot.phi);

    }
    if (phi1.daughterIndices.size() < 2) continue;
    const TTStudy::GenParticle& kaon1 = genParticleBr_->at(phi1.daughterIndices.at(0));
    const TTStudy::GenParticle& kaon2 = genParticleBr_->at(phi1.daughterIndices.at(1));
    if (std::abs(kaon1.pdgId) != 321 || std::abs(kaon2.pdgId) != 321) continue;
    
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
    if (std::abs(genp.pdgId) != 333) continue;
    
    const TTStudy::GenParticle& moth = genParticleBr_->at(genp.motherIndex);
    if (std::abs(moth.pdgId) != 531) continue;
    double vxy = std::sqrt(std::pow(genp.vx,2) + std::pow(genp.vy,2));
    double vz = genp.vz;
    phiVXYH_->Fill(vxy);
    phiVZH_->Fill(vz); 
    
    if (!bsfilled) {
      bsfilled = true;
      vxy = std::sqrt(std::pow(moth.vx,2) + std::pow(moth.vy,2));
      vz = moth.vz;
      BsVXYH_->Fill(vxy);
      BsVZH_->Fill(vz); 
    }
  }
}
void BsAnalysis::getLV(const std::vector<TTStudy::Track>* tracksBr, unsigned int indx, TLorentzVector& lv) const {
  const TTStudy::Track& trk = tracksBr->at(indx);
  lv.SetPtEtaPhiM(trk.pt, trk.eta, trk.phi, ::kmass);
}
void BsAnalysis::getTV(const std::vector<TTStudy::Track>* tracksBr, unsigned int indx, TVector3& v) const {
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
  outputFile_->cd();
  outputFile_->Write();
  outputFile_->Close();
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
  double err = (1./N)*TMath::Sqrt(k*(1-k/N));
  return err;
}	
void BsAnalysis::printResults(std::ostream& os) const {
  using namespace std;
  os << "==> Results: " << endl;
  
  string slist[] = 
    {
      "Events processed",
      "       after GenFilter",
      "       w/ ntrk >= 4",
      "       w/ >= 2 Phi",
      "       w/ Phi distinct tracks",
      "       w/ Phi dxy & dz2 cut",
      "       w/ dR(Phi pair) cut",
      "       w/ dR(Track pair) cut",
      "       in Bs mass window",
      "       final gen match"
    };
  outputFile_->cd();
  TH1F *h = dynamic_cast<TH1F*>(gROOT->FindObject("evcount"));
  if (h) {
    os << setw(64) << "CutFlow"
       << setw(10) << "Events"
       << setw(10) << "AbsEff"
       << setw(10) << "Error"
       << setw(10) << "RelEff"
       << setw(10) << "Error"
       << endl;
    os << setprecision(3);
    int nbins = h->GetNbinsX();
    if (!studyGen_) --nbins;
    for (int i = 1; i <= nbins; ++i) {
      os << setw(64) << slist[i-1]
	 << setprecision(1) 
	 << setw(10) << int(h->GetBinContent(i))
	 << setprecision(5) 
	 << setw(10) << ((h->GetBinContent(1)>0) ? h->GetBinContent(i)/h->GetBinContent(1) : 0.0)
         << setprecision(3)
         << setw(10) << getBinomailError(h->GetBinContent(i),h->GetBinContent(1))
         << setprecision(5)
	 << setw(10) << ( i == 1?1.0:(h->GetBinContent(i-1)>0) ? h->GetBinContent(i)/h->GetBinContent(i-1) : 0.0)
         << setprecision(3)
         << setw(10) << getBinomailError(h->GetBinContent(i),h->GetBinContent(i-1))
	 << endl;
    }
    if (isSignal_) {
      double k = double(h->GetBinContent(10));
      double N = double(h->GetBinContent(2));
      double eff = (k/N)*100;
      double err_Poisson = getPoissonError(k,N) * 100;
      double err_Binomial = getBinomailError(k,N) * 100;
      os << "Efficiency for Outer Tracker" << endl;
      os << "Efficiency = " << setprecision(2) << eff 
	 << " Poisson Error = " << setprecision(2) << err_Poisson
	 << " Binomial error = " << setprecision(2) << err_Binomial
	 << endl;
    }
    else{
      double k = double(h->GetBinContent(9));
      double N = double(h->GetBinContent(1));
      double rate = (k/N)*30000;
      double err_Poisson = getPoissonError(k,N)*30000;
      double err_Binomial = getBinomailError(k,N)*30000;
      os << "Rate for Outer Tracker"<<endl;
      os << "Rate in kHz = " << setprecision(2) << rate
	 << " Poisson Error = " << setprecision(2) << err_Poisson 
	 << " Binomial error = " << setprecision(2) << err_Binomial
	 << endl;
    } 
  }
}
bool BsAnalysis::readJob(const string& jobFile, int& nFiles)
{
  static const int BUF_SIZE = 256;

  // Open the file containing the datacards
  std::ifstream fin(jobFile.c_str(), ios::in);    
  if (!fin) {
    cerr << "Input File: " << jobFile << " could not be opened!" << endl;
    return false;
  }

  // note that you must use a pointer (reference!) to the cut map
  // in order to avoid scope related issues
  map<string, map<string, double>* > hmap;
  hmap.insert(pair<string, map<string, double>* >("trkSelCuts", &trkSelCutMap_));
  hmap.insert(pair<string, map<string, double>* >("phiSelCuts", &phiSelCutMap_));
  hmap.insert(pair<string, map<string, double>* >("bsSelCuts", &bsSelCutMap_));
  
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
      studyGen_ = (std::stoi(value.c_str()) > 0) ? true : false;
    else if (key == "studyOffline") 
      studyOffline_ = (std::stoi(value.c_str()) > 0) ? true : false;
    else if (key == "dumpGenInfo") 
      dumpGenInfo_ = (std::stoi(value.c_str()) > 0) ? true : false;
    else if (key == "histFile") 
      histFile_ = value;
    else if (key == "logFile")
      logFile_ = value;
    else if (key == "maxEvent") 
      maxEvt_ = std::stoi(value.c_str());
    else if (key == "verbosity") 
      verbosity_ = std::stoi(value.c_str());
    else if (key == "inputFile") 
      AnaUtil::buildList(tokens, fileList_);
    else
      AnaUtil::storeCuts(tokens, hmap);

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

  return true;
}
void BsAnalysis::printJob(std::ostream& os) const
{
  os << "  datatype = " << dataType_ << endl
     << "   logFile = " << logFile_ << endl 
     << "  histFile = " << histFile_ << endl
     << " verbosity = " << verbosity_ << endl
     << "  maxEvent = " << maxEvt_ << endl;

  // InputFiles
  if (chain_) {
    TObjArray *fileElements = chain_->GetListOfFiles();
    os << ">>> INFO. nFiles: " << fileElements->GetEntries() 
       << ", Files to analyse:" 
       << endl;
    TIter next(fileElements);
    TChainElement *chEl = 0;
    while (( chEl = dynamic_cast<TChainElement*>(next()) ))
      os << chEl->GetTitle() 
         << endl;
  }
  else
    AnaUtil::showList(fileList_, ">>> INFO. inputFiles", os);

  // Cuts
  map<string, map<string, double> > hmap;
  hmap.insert(pair<string, map<string, double> >("trkSelCuts", trkSelCutMap_));
  hmap.insert(pair<string, map<string, double> >("phiSelCuts", phiSelCutMap_));
  hmap.insert(pair<string, map<string, double> >("bsSelCuts", bsSelCutMap_));
  AnaUtil::showCuts(hmap, os);
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

  // Create  analysis object 
  BsAnalysis ana;

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
  timer.Stop();
  cout << "Realtime/CpuTime = " << timer.RealTime() << "/" << timer.CpuTime() << endl;
  
  return 0;
}
