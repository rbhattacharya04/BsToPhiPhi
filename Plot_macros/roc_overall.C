//#include "TROOT.h"
//#include "TH1.h"

{  
  //gROOT->LoadMacro("set_style.C");
  set_style();

  // PU 70
  TH1F* h1 = new TH1F("h1", "h1", 250, 25, 50);  
  h1->SetBinContent(h1->FindBin(41.55), 6.34);
  h1->SetBinError(h1->FindBin(41.55), 1.49);
  h1->SetBinContent(h1->FindBin(36.58), 2.47);
  h1->SetBinError(h1->FindBin(36.58), 0.93);
  h1->SetBinContent(h1->FindBin(31.06), 1.41);
  h1->SetBinError(h1->FindBin(31.06), 0.7);
  h1->SetLineWidth(2);
  h1->SetLineColor(kRed);
  h1->SetMarkerStyle(20);
  h1->SetMarkerColor(kRed);
  h1->SetMarkerSize(1.2);
  h1->SetMinimum(-2);
  h1->SetMaximum(80);
  h1->Draw("C");
  h1->GetXaxis()->SetTitle("Efficiency (%)");
  h1->GetYaxis()->SetTitle("Rate (kHz)");

  // PU 140
  TH1F* h2 = new TH1F("h2", "h2", 250, 25, 50);  
  h2->SetBinContent(h1->FindBin(41.55), 27.86);
  h2->SetBinError(h1->FindBin(41.55), 1.72);
  h2->SetBinContent(h1->FindBin(36.58), 13.30);
  h2->SetBinError(h1->FindBin(36.58), 1.18);
  h2->SetBinContent(h1->FindBin(31.06), 5.07);
  h2->SetBinError(h1->FindBin(31.06), 0.73);
  h2->SetLineWidth(2);
  h2->SetLineColor(kBlue);
  h2->SetMarkerStyle(21);
  h2->SetMarkerColor(kBlue);
  h2->SetMarkerSize(1.2);
  h2->Draw("CSAME");

  // PU 200
  TH1F* h3 = new TH1F("h3", "h3", 250, 25, 50);  
  h3->SetBinContent(h1->FindBin(41.55), 61.75);
  h3->SetBinError(h1->FindBin(41.55), 5.19);
  h3->SetBinContent(h1->FindBin(36.58), 29.57);
  h3->SetBinError(h1->FindBin(36.58), 3.59);
  h3->SetBinContent(h1->FindBin(31.06), 12.18);
  h3->SetBinError(h1->FindBin(31.06), 2.30);
  h3->SetMarkerSize(1.2);
  h3->SetMarkerColor(kCyan);
  h3->SetMarkerStyle(22);
  h3->SetLineWidth(2);
  h3->SetLineColor(kCyan);
  h3->Draw("CSAME");

  TLegend *leg = new TLegend(0.25, 0.75, 0.5, 0.93, nullptr,"brNDC");
  leg->SetTextFont(62);
  leg->SetTextSize(0.04);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  leg->AddEntry("h1","70 Pileup","LP");
  leg->AddEntry("h2","140 Pileup","LP");
  leg->AddEntry("h3","200 Pileup","LP");

  leg->Draw();

  TLatex *tex1 = new TLatex(5.03, 0.10, "CMS PRELIMINARY SIMULATION");
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.034);
  tex1->SetTextColor(2);
  tex1->Draw();

   //ci = TColor::GetColor("#abb2b9");
   TLatex *texl = new TLatex(30.5, 2., "Tight Baseline");
   texl->SetTextColor(kBlack);
   texl->SetTextFont(42);
   texl->SetTextSize(0.03);
   texl->SetTextAngle(90);
   texl->Draw();

   TLatex *texm = new TLatex(36., 2., "Medium Baseline");
   texm->SetTextColor(kBlack);
   texm->SetTextFont(42);
   texm->SetTextSize(0.03);
   texm->SetTextAngle(90);
   texm->Draw();

   TLatex *text = new TLatex(41., 2., "Loose Baseline");
   text->SetTextColor(kBlack);
   text->SetTextFont(42);
   text->SetTextSize(0.03);
   text->SetTextAngle(90);
   text->Draw();
}
