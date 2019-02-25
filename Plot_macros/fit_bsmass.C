using namespace RooFit ;
void fit_bsmass(){
 RooRealVar mass("mass","mass",5,5.8) ;
 RooRealVar mean("mean","mean of bw",5.38,5,5.8) ;
 RooRealVar width("width","width of bw",0.1,0,1);
 RooRealVar sigma("sigma","sigma of gaussian",0.5,0,1) ;

 RooVoigtian vog("vog","voigtian PDF",mass,mean,width,sigma) ;
 
 
 //  RooRealVar mBW("mBW","mean BW",91.1875) ;
 RooRealVar mBW("mBW","mean BW",5.336,0, 5.39) ;
 //  RooRealVar sBW("sBW","sigma BW",2.4952) ;
 RooRealVar sBW("sBW","sigma BW",0.1,0,1) ;
 RooBreitWigner brietwigner("BW","BW",mass,mBW,sBW) ;

 RooRealVar mCB1("mCB1", "mCB" ,0.0,-2,2) ;
 RooRealVar sCB1("sCB1", "sCB1" ,0.5,0,50)  ;
 //RooRealVar sCB1("sCB1", "sCB1" ,2,1,2.5 )  ;
 RooRealVar nCB1("nCB1","", 100,0,200);
 RooRealVar alphaCB1("alphaCB1","", 0.6,-10,10); // RooRealVar alphaCB1("alphaCB1","", 0.6,.2,1);
 RooCBShape cball1("cball1","cball1",mass,mCB1,sCB1, alphaCB1, nCB1);
 
 RooFFTConvPdf bwcball1("BWxCB","Breit-Wigner (X) CB",mass,brietwigner, cball1) ;
 
 //TFile *inputfile = new TFile("Signal_pu200_loose_baseline_new.root","READ");
 //TFile *inputfile = new TFile("Signal_pu140_loose_baseline_new.root","READ");
 //TFile *inputfile = new TFile("Signal_pu140_loose_baseline_reco_new.root","READ");
 TFile *inputfile = new TFile("Signal_pu200_loose_baseline_reco_new.root","READ");
 //TFile *inputfile = new TFile("Signal_pu0_loose_baseline_new2_reco.root","READ");
 inputfile->cd();

 TH1F* bsmass = dynamic_cast<TH1F*>(inputfile->Get("bsmass"));
 RooDataHist dh1("dh1","dh1",mass,Import(*bsmass)) ;

 bwcball1.fitTo(dh1) ;
 RooPlot* xframe2 = mass.frame() ;
 dh1.plotOn(xframe2) ;
 bwcball1.plotOn(xframe2,"L") ;
 bwcball1.paramOn(xframe2,Layout(0.62,0.90),Format("NEU",AutoPrecision(1))) ;
 xframe2->Draw() ;
}
