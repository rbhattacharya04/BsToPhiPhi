#include <iostream>
#include <algorithm>
#include "TFile.h"
#include "TH1.h"
#include "TPaveStats.h"

void bindstat(TH1F* h, double x1ndc, double y1ndc, double x2ndc, double y2ndc, int color=1)
{
  TPaveStats* ptstats = new TPaveStats(x1ndc, y1ndc, x2ndc, y2ndc, "brNDC");
  h->GetListOfFunctions()->Add(ptstats);
  ptstats->SetParent(h);
  ptstats->SetTextColor(color);
}
void plot( TFile* fbkg, TFile* fsig, const char* histo_name, const char* xtit, const char* ytit="Events") {
  //gROOT->LoadMacro("set_style.C");
  set_style();
  
  TCanvas *c1 = new TCanvas("c1", "c1",4,28,800,700);
  gStyle->SetOptFit(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLeftMargin(0.15);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.15);


  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  
  int labelandtitlefonts=42;
  
  TH1F* h1 = dynamic_cast<TH1F*>(fbkg->Get(histo_name));
  assert(h1);
  //h1->SetName("L1Background");
  //h1->SetName("old_0pu");
  h1->Rebin(2);
  //h1->SetTitle("");

  TH1F* h2 = dynamic_cast<TH1F*>(fsig->Get(histo_name));
  assert(h2);
  //h2->SetName("L1Signal");
  //h2->SetName("new_0pu");
  h2->Rebin(2);
  //h2->SetTitle("");


  //h1->Scale(1./h1->GetEntries());
  //h2->Scale(1./h2->GetEntries());
  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  //h1->GetXaxis()->SetTitle(xtit);
  //h1->GetYaxis()->SetTitle(ytit);
  //h1->SetLineColor(1);

  h1->SetMaximum(1.1*std::max(h1->GetBinContent(h1->GetMaximumBin()), h2->GetBinContent(h2->GetMaximumBin())));
  h1->SetMinimum(0.9*std::min(h1->GetBinContent(h1->GetMinimumBin()), h2->GetBinContent(h2->GetMinimumBin())));


  //gStyle->SetOptStat(0);
  //gStyle->SetOptStat(111);
  int ci = TColor::GetColor("#339900");
  h1->SetFillColor(ci);
  h1->SetLineColor(ci);
  h1->GetXaxis()->SetTitle(xtit);
  h1->GetXaxis()->SetNdivisions(505);
  h1->GetXaxis()->SetLabelFont(labelandtitlefonts);
  h1->GetXaxis()->SetLabelOffset(0.007);
  h1->GetXaxis()->SetLabelSize(0.05);
  h1->GetXaxis()->SetTitleSize(0.06);
  h1->GetXaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetTitleFont(labelandtitlefonts);

  h1->GetYaxis()->SetTitle(ytit);
  h1->GetYaxis()->SetNdivisions(505);
  h1->GetYaxis()->SetLabelFont(labelandtitlefonts);
  h1->GetYaxis()->SetLabelOffset(0.007);
  h1->GetYaxis()->SetLabelSize(0.05);
  h1->GetYaxis()->SetTitleSize(0.06);
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetYaxis()->SetTitleFont(labelandtitlefonts);

  h1->GetZaxis()->SetLabelFont(42);
  h1->GetZaxis()->SetLabelOffset(0.007);
  h1->GetZaxis()->SetLabelSize(0.05);
  h1->GetZaxis()->SetTitleSize(0.06);
  h1->GetZaxis()->SetTitleFont(42);
  h1->Draw("");
  
  
  
  
  // h2->SetOptStat(kFalse);
  ci = TColor::GetColor("#ff0000");
  h2->SetLineColor(ci);
  h2->SetLineStyle(2);
  h2->SetLineWidth(2);
  h2->GetXaxis()->SetNdivisions(505);
  h2->GetXaxis()->SetLabelFont(labelandtitlefonts);
  h2->GetXaxis()->SetLabelOffset(0.007);
  h2->GetXaxis()->SetLabelSize(0.05);
  h2->GetXaxis()->SetTitleSize(0.06);
  h2->GetXaxis()->SetTitleFont(labelandtitlefonts);

  h2->GetYaxis()->SetLabelFont(labelandtitlefonts);
  h2->GetYaxis()->SetLabelOffset(0.007);
  h2->GetYaxis()->SetLabelSize(0.05);
  h2->GetYaxis()->SetTitleSize(0.06);
  h2->GetYaxis()->SetTitleOffset(1.3);
  h2->GetYaxis()->SetTitleFont(labelandtitlefonts);

  h2->GetZaxis()->SetLabelFont(42);
  h2->GetZaxis()->SetLabelOffset(0.007);
  h2->GetZaxis()->SetLabelSize(0.05);
  h2->GetZaxis()->SetTitleSize(0.06);
  h2->GetZaxis()->SetTitleFont(42);
  h2->Draw("SAME");
   
  TLegend *leg = new TLegend(0.6, 0.4, 0.85, 0.65, nullptr,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextFont(labelandtitlefonts);
   /*
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001); */

  leg->AddEntry(h1, "OLD_TDR (200 PU)","f");
  leg->AddEntry(h2, "NEW_TDR (200 PU)","l");
  //leg->AddEntry("bsmassOld", "TP 0 Pile Up events","f");
  leg->Draw();
}
