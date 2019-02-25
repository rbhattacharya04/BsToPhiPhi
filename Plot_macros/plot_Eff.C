void plot_Eff(){
  //gROOT->LoadMacro("set_style.C");
  set_style();
  TFile *_file0 = TFile::Open("resolutionhistomu+_latest.root");
  TH1D* h1;
  _file0->GetObject("myAna/pthistoM",h1);
  TH1D* h2;
  _file0->GetObject("myAna/pthisto",h2);
  h2->Rebin(2500);
  h1->Rebin(2500);
  TH1D* h3 = new TH1D(*h1);
  h3->SetName("h3");
  h3->SetTitle("L1 Tracking Efficiency vs p_{T}");
  h3->Sumw2();
  h3->Divide(h1,h2,1,1,"B");
  gStyle->SetOptStat(0);
  h3->SetMarkerStyle(20);
  h3->SetLineColor(kBlue);
  h3->GetXaxis()->SetTitle("p_{T} of the Tracking particle");
  h3->GetYaxis()->SetTitle("Efficiency of the Reconstructed Level1 Track");


   
  h3->Draw();
  /*TLatex* latex = new TLatex();
  latex->SetTextSize(0.06);
  latex->DrawLatex(2.5,0.4,"#splitline{Not for distribution,}{CMS internal, work in progress}");*/ 
}	
