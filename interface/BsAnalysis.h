#ifndef __BSANALYSIS_H
#define __BSANALYSIS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

#include "TLorentzVector.h"

const double kmass = 0.493; // GeV
const double phi_polemass = 1.019445; // GeV

// Holds information about a Phi Candidate
struct PhiInfo 
{
  // track pair indices
  int indx1;
  int indx2;

  // difference from nominal mass
  double dmass;

  // position difference between track pair
  double dxy;
  double dz;

  // deltaR between track pair
  double dr;
  
  // sum of track pair vectors
  TLorentzVector v;

  // average of track vertices
  double vertexX;
  double vertexY;
  double vertexZ;  
};

// holds information about a Bs
struct BsInfo 
{
  PhiInfo phi1;
  PhiInfo phi2;
  // sum of phi pair vectors
  TLorentzVector bsv;

  // average of phi vertices
  double vertexX;
  double vertexY;
  double vertexZ;  
};

// Function objects - comparator 
class LVPtComparator {
public:
  bool operator() (const TLorentzVector& a, const TLorentzVector& b) {
    return a.Pt() > b.Pt();
  }
};
template <class T>
class PtComparator {
public:
  bool operator() (const T& a, const T& b) {
    return a.pt > b.pt;
  }
};
class PhiInfoComparator {
  public:
    bool operator() (const PhiInfo& a, const PhiInfo& b) const {
      return (a.dmass < b.dmass);
    }
};

class TFile;
class TChain;
class TH1;
class TProfile;

class BsAnalysis {
  
  public:
  BsAnalysis(); 
  ~BsAnalysis();
  
  int setInputFile(const std::string& fname);
  void setTreeBranches();
  void bookHistograms();
  void saveHistograms();  
  void printResults(std::ostream& os=std::cout) const; 
  bool beginJob();
  void endJob();
  void eventLoop();
  bool openFiles();
  void closeFiles();
  bool readJob(const std::string& jobFile, int& nFiles);
  void printJob(std::ostream& os=std::cout) const;
  void checkDecayMode(); 
  // ---------------------------------------
  // Get total number of events in the chain
  // --------------------------------------
  int getEntries() const
  {
    return static_cast<int>(chain_->GetEntries());
  }
  bool branchFound(const std::string& b);
  int getEntry(int lflag) const;

  void findPhiCandidates(const std::vector<TTStudy::Track>* trackList, 
			 std::vector<PhiInfo>& phiList, 
			 int indx=0, 
			 bool checkL1Offline=false);
  bool selectEvent(const std::vector<TTStudy::Track>* trackList, 
		   std::vector<BsInfo>& bsList, 
		   int ishift, 
		   int indx=0, 
		   bool checkL1Offline=false);
  void readGenParticle();
  void plotGen(const std::vector<TTStudy::Track>* tracksBr);
  void clearEvent();
  void clearLists();
  void clearGenLists();
  void getKaonList(const std::vector<TTStudy::Track>* trackList, const BsInfo& info, std::vector<TLorentzVector>& kaonList);
  void fillKaonInfo(const std::vector<TLorentzVector>& kaonList);
  void fillKaonTrackInfo(const std::vector<TTStudy::Track>* tracksBr, const BsInfo& info);
  void computeIsolation(const std::vector<TTStudy::Track>* trackList, const BsInfo& info, std::vector<std::pair<double,double>>& iso_vector);
  double computeIsolation_v2(const std::vector<TTStudy::Track>* trackList, 
			     size_t ref_track_index, 
			     const std::vector<size_t> tracks_to_exclude);
  void fillGenInfo();

  void checkPhiKaonBs(const PhiInfo& info_i, const PhiInfo& info_j, const std::vector<TTStudy::Track>* tracksBr);
  void checkMatchingPhi(int ntrk) const;
  void printTrackProperties(const std::vector<TTStudy::Track>* tracksBr) const;
  void checkConsistency(const std::vector<TTStudy::Track>* tracksBr, int ntrk) const;
  bool genFilter(double minPt=2.0, double maxEta=2.5) const;
  void printTrk(const std::vector<TTStudy::Track>* tracksBr, size_t i) const;
  void printGenParticle(size_t i) const;
   int doTrkGenMatch(const std::vector<TLorentzVector>& kaonList);
  bool isGenKaonMatched(const TLorentzVector& trk_lv, double& pt_diff);
  void getTV(const std::vector<TTStudy::Track>* tracksBr, unsigned int indx, TVector3& lv) const;
  void getLV(const std::vector<TTStudy::Track>* tracksBr, unsigned int indx, TLorentzVector& lv) const;
  void plotSignalProperties(const std::vector<TTStudy::Track>* tracksBr);
  void plotGenVertex();
  bool showEfficiency(TH1D* h, 
		      const std::vector<std::string>& slist, 
		      const std::string& header, 
		      std::ostream& os=std::cout) const;

  static void calculateDeltaPos(const TTStudy::Track& trki, const TTStudy::Track& trkj, double& dxy, double& dz);
  static void calculateDeltaPos(const PhiInfo& infoi, const PhiInfo& infoj, double& dxy, double& dz);
  static void calculateDeltaPos(const TTStudy::Track& trki, const PhiInfo& infoj, double& dxy, double& dz);
  static void calculateDeltaPos(const TTStudy::Track& trki, const BsInfo& bsInfoj, double& dxy, double& dz);
  static double calculateDeltaR(const TTStudy::Track& trki, const TTStudy::Track& trkj);
  static double calculateDeltaR(const TTStudy::GenParticle& gpi, const TTStudy::GenParticle& gpj);
  static void scaleHistogram(TH1F* th, double fac);
  static TLorentzVector phiLV(const TTStudy::Track& trki, const TTStudy::Track& trkj);
  static double genInvMass(const TTStudy::GenParticle&, const TTStudy::GenParticle&);
  static double getPoissonError(double k, double N);
  static double getBinomailError(double k, double N);

  const std::map<std::string, double>& trkCutMap() const {return AnaUtil::cutMap(hmap_, "trkSelCuts");}
  const std::map<std::string, double>& phiCutMap() const {return AnaUtil::cutMap(hmap_, "phiSelCuts");}
  const std::map<std::string, double>& bsCutMap() const {return AnaUtil::cutMap(hmap_, "bsSelCuts");}
  const std::map<std::string, double>& isoCutMap() const {return AnaUtil::cutMap(hmap_, "isoCuts");}

  std::unique_ptr<TChain> chain_;      // chain contains a list of root files containing the same tree
  std::unique_ptr<TFile> histf_;       // The output file with histograms

  std::string dataType_ {"signal"};
  bool isSignal_ {true};
  bool studyGen_ {false};
  bool dumpGenInfo_ {false};
  bool studyOffline_ {false};
  bool checkL1Offline_  {false};
  bool applyIso_  {true};
  std::string histFile_;
  std::string logFile_;
  int verbosity_ {0};
  bool applyTrkQuality_ {false};
  long int maxEvt_;
  long int count0;
  long int count1;
  long int count2;
  std::vector<std::string> fileList_;

  std::map<std::string, std::map<std::string, double>> hmap_;

  // Branches
  TTStudy::Event* eventBr_ {nullptr};
  std::vector<TTStudy::Track>* tracksBr_ {nullptr};
  std::vector<TTStudy::Track>* offlineTracksBr_ {nullptr};
  std::vector<TTStudy::GenParticle>* genParticleBr_ {nullptr};

  // other lists
  std::vector<TTStudy::GenParticle> genKaonList_;  
  std::vector<std::vector<TLorentzVector> > phiCandList_;
  std::vector<TTStudy::GenParticle> genPhiCandList_;
  std::vector<BsInfo> bsList_;
  std::vector<BsInfo> bsOfflineList_;

  std::vector<std::string> brList_;

  long nEntries_;
  bool bookedHistograms_; 
  double scaleFactor_;
  long int nEvents_;
  std::ofstream fLog_;   

  TH1D* nDaughtersH_;
  TH1D* BsDecayModesH_; 
  TH1D* evcountH_;
  TH1D* evcountOfflineH_;
  TH1D* evcount2H_;
  TH1D* evcount2OfflineH_;
  TH1D* trkcountH_;
  TH1D* trkcountOfflineH_;
  TH1D* phicountH_;
  TH1D* phicountOfflineH_;
  TH1D* phicount2H_;
  TH1D* phicount2OfflineH_;
  TH1F* centralH_;
  TH1F* fwdH_;
  TH1F* nH_;
  TH1F* ptDiffH_;

  TH1F* ntrkH_;
  TH1F* ntrk_p_before_acceptanceH_;
  TH1F* ntrk_n_before_acceptanceH_;
  TH1F* ntrk_p_after_acceptanceH_;
  TH1F* ntrk_n_after_acceptanceH_;
  TH1F* ntrk_p_goodH_;
  TH1F* ntrk_n_goodH_;
  TH1F* ntrkOfflineH_;
  TH1F* trkVertexZH_;
  TH1F* trkVertexZOfflineH_;
  TH1F* trkVertexXYH_;
  TH1F* trkVertexXYOfflineH_;
  TH1F* trkPtH_;
  TH1F* trkPtOfflineH_;
  TH1F* trkChi2RedH_;
  TH1F* trkChi2RedOfflineH_;
  TH1F* trkNStubH_;
  TH1F* trkNStubOfflineH_;
  TH1F* trkNStub_PSH_;
  TH1F* trkNStub_PSOfflineH_;

  TH1F* dzTrackPairH_;
  TH1F* dzTrackPairOfflineH_;
  TH1F* dzTrackPair2H_;
  TH1F* dzTrackPair2OfflineH_;
  TH1F* dzTrackPair3H_;
  TH1F* dzTrackPair3OfflineH_;
  TH1F* dzTrackPair4H_;
  TH1F* dzTrackPair4OfflineH_;
  TH1F* dxyTrackPairH_;
  TH1F* dxyTrackPairOfflineH_;
  TH1F* dxyTrackPair2H_;
  TH1F* dxyTrackPair3H_;
  TH1F* dxyTrackPair4H_;
  TH1F* dxyTrackPair2OfflineH_;
  TH2F* dRvsdZ1H_;
  TH2F* dRvsdZ2H_;
  TH2F* dRvsdZ1OfflineH_;
  TH2F* dRvsdZ2OfflineH_;

  TH1F* drTrackPairH_;
  TH1F* drTrackPairOfflineH_;

  TH1F* phiCandPtH_;
  TH1F* phiCandPtOfflineH_;
  TH1F* phimass0H_;
  TH1F* phimass0OfflineH_;
  TH1F* phimassH_;
  TH1F* phimassOfflineH_;
  TH1F* nPhiCandH_;
  TH1F* nPhiCandOfflineH_;

  TH1F* dxyPhiPairH_;
  TH1F* dxyPhiPairOfflineH_;
  TH1F* dzPhiPairH_;
  TH1F* dzPhiPairOfflineH_;
  TH1F* drPhiPairH_;
  TH1F* drPhiPairOfflineH_;

  TH1F* drPhi1TrackPairH_;
  TH1F* drPhi1TrackPairOfflineH_;
  TH1F* drPhi2TrackPairH_;
  TH1F* drPhi2TrackPairOfflineH_;

  TH1F* bsmass0H_;
  TH1F* bsPtH_;
  TH1F* bsmass0OfflineH_;
  TH1F* bsmassH_;
  TH1F* bsmassOfflineH_;

  TH1F* phi1PtH_;
  TH1F* phi1PtOfflineH_;
  TH1F* phi2PtH_;
  TH1F* phi2PtOfflineH_;
  TH2D* phiPtH_;
  TH2D* phiPtOfflineH_;
  
  TH1F* dxyPhi1TrackPairH_;
  TH1F* dxyPhi1TrackPairOfflineH_;
  TH1F* dzPhi1TrackPairH_;
  TH1F* dzPhi1TrackPairOfflineH_;

  TH1F* dxyPhi2TrackPairH_;
  TH1F* dxyPhi2TrackPairOfflineH_;
  TH1F* dzPhi2TrackPairH_;
  TH1F* dzPhi2TrackPairOfflineH_;

  TH1F* trk1PtH_;
  TH1F* trk1PtOfflineH_;
  TH1F* trk2PtH_;
  TH1F* trk2PtOfflineH_;
  TH1F* trk3PtH_;
  TH1F* trk3PtOfflineH_;
  TH1F* trk4PtH_;
  TH1F* trk4PtOfflineH_;
  TH1F* trkPtSumH_;

  TH1F* trk1EtaH_;
  TH1F* trk1EtaOfflineH_;
  TH1F* trk2EtaH_;
  TH1F* trk2EtaOfflineH_;
  TH1F* trk3EtaH_;
  TH1F* trk3EtaOfflineH_;
  TH1F* trk4EtaH_;
  TH1F* trk4EtaOfflineH_;

  TH1F* trk1PhiH_;
  TH1F* trk1PhiOfflineH_;
  TH1F* trk2PhiH_;
  TH1F* trk2PhiOfflineH_;
  TH1F* trk3PhiH_;
  TH1F* trk3PhiOfflineH_;
  TH1F* trk4PhiH_;
  TH1F* trk4PhiOfflineH_;

  TH1F* trk1Chi2H_;
  TH1F* trk1Chi2OfflineH_;
  TH1F* trk2Chi2H_;
  TH1F* trk2Chi2OfflineH_;
  TH1F* trk3Chi2H_;
  TH1F* trk3Chi2OfflineH_;
  TH1F* trk4Chi2H_;
  TH1F* trk4Chi2OfflineH_;

  TH1F* trk1Chi2RedH_;
  TH1F* trk1Chi2RedOfflineH_;
  TH1F* trk2Chi2RedH_;
  TH1F* trk2Chi2RedOfflineH_;
  TH1F* trk3Chi2RedH_;
  TH1F* trk3Chi2RedOfflineH_;
  TH1F* trk4Chi2RedH_;
  TH1F* trk4Chi2RedOfflineH_;

  TH1F* trk1nStubH_;
  TH1F* trk1nStubOfflineH_;
  TH1F* trk2nStubH_;
  TH1F* trk2nStubOfflineH_;
  TH1F* trk3nStubH_;
  TH1F* trk3nStubOfflineH_;
  TH1F* trk4nStubH_;
  TH1F* trk4nStubOfflineH_;

  TH1F* trk1nStubPSH_;
  TH1F* trk1nStubPSOfflineH_;
  TH1F* trk2nStubPSH_;
  TH1F* trk2nStubPSOfflineH_;
  TH1F* trk3nStubPSH_;
  TH1F* trk3nStubPSOfflineH_;
  TH1F* trk4nStubPSH_;
  TH1F* trk4nStubPSOfflineH_;
  
  TH1F* drKaonPairH_;
  TH1F* drKaonPairOfflineH_;
  TH1F* isol1H_;
  TH1F* isol1OfflineH_;
  TH1F* isol2H_;
  TH1F* isol2OfflineH_;
  TH1F* isol3H_;
  TH1F* isol3OfflineH_;
  TH1F* isol4H_;
  TH1F* isol4OfflineH_;
  TH1F* isol_phi1H_;
  TH1F* isol_phi2H_;
  TH1F* isol_phi1OfflineH_;
  TH1F* isol_phi2OfflineH_;
  TH1F* isol_BsH_;
  TH1F* isol_BsOfflineH_;

  TH1F* bsCandListH_;
  TH1F* bsCandListOfflineH_;
  TH1F* anglePlanesH_;

  TH1F* genKPt1H_;
  TH1F* genKPt2H_;
  TH1F* genKPt3H_;
  TH1F* genKPt4H_;
  TH1F* genKPtCheckH_;

  TH1F* genKEta1H_;
  TH1F* genKEta2H_;
  TH1F* genKEta3H_;
  TH1F* genKEta4H_;

  TH1F* genKPhi1H_;
  TH1F* genKPhi2H_;
  TH1F* genKPhi3H_;
  TH1F* genKPhi4H_;
  
  TH1F* genPhiMH_;
  TH1F* genPhiPt1H_;
  TH1F* genPhiPt2H_;

  TH1F* genPhiEta1H_;
  TH1F* genPhiEta2H_;
  TH1F* genPhiPhi1H_;
  TH1F* genPhiPhi2H_;

  TH1F* genDrKPairH_;
  TH1F* genDrPhiPairH_;
  TH1F* drPhiGenPhiH_;
  TH1F* genBsPtH_;
  TH1F* genBsEtaH_;
  TH1F* genBsPhiH_;

  TH1F* phiVXYH_;
  TH1F* phiVZH_;
  TH1F* phiVH_;
  TH3F* phiV3DH_;
  TH1F* BsVXYH_;
  TH1F* BsVZH_;
  TH1F* BsVH_;
  TH3F* BsV3DH_;
  TH1F* KaonVXYH_;
  TH1F* KaonVZH_;
  TH1F* KaonVH_;
  TH3F* KaonV3DH_;

  TH1F* mDr_K;
  TH1F* mDpt_K;
  TH1F* mDphi_K;
  TH1F* mDeta_K;
  TH1F* mDr_phi;
  TH1F* mDpt_phi;
  TH1F* mDphi_phi;
  TH1F* mDeta_phi;
  
  TH1F* signalPt1H_;
  TH1F* signalPt2H_;
  TH1F* signalPt3H_;
  TH1F* signalPt4H_;
  TH1F* signalDrH_;
  TH1F* signalPhiMH_;
  TH1F* signalNtrkH_  ;
  TH1F* signalCentralH_ ;
  TH1F* signalFwdH_ ;
  TH1F* signal_VZH_;
  TH1F* signal_VXYH_;
  TH1F* signal_chiH_;
  TH1F* signalDPT_H;
  
  TH1F* signalDXYPVH_;
  TH1F* signalDZPVH_;
  TH2D* signal2DH_;
  TH1F* signalDXYH_;
  TH1F* signalDZH_;
  TH1F* allDXYPVH_;
  TH1F* allDZPVH_;
  TH2D* all2DH_;
  TH1F* allDXYH_;
  TH1F* allDZH_;

  TProfile* drVsMatchedTrkH_;
  TH2D* Iso_Pt1H_;
  TH2D* Iso_Pt2H_;
  TH2D* Iso_Pt3H_;
  TH2D* Iso_Pt4H_;
  TH2D* Iso_Pt1OfflineH_;
  TH2D* Iso_Pt2OfflineH_;
  TH2D* Iso_Pt3OfflineH_;
  TH2D* Iso_Pt4OfflineH_;
  TH2D* Iso_Pt_Phi1H_;
  TH2D* Iso_Pt_Phi2H_;
  TH2D* Iso_Pt_Phi1OfflineH_;
  TH2D* Iso_Pt_Phi2OfflineH_;
  TH2D* Iso_Pt_BsH_;
  TH2D* Iso_Pt_BsOfflineH_;
};
#endif
