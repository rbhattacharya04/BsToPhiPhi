#include <iostream>
#include <algorithm>
#include "TFile.h"
#include "TH1.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TStyle.h"

void bindstat(TH1F* h, double x1ndc, double y1ndc, double x2ndc, double y2ndc, int color=1)
{
  TPaveStats* ptstats = new TPaveStats(x1ndc, y1ndc, x2ndc, y2ndc, "brNDC");
  h->GetListOfFunctions()->Add(ptstats);
  ptstats->SetParent(h);
  ptstats->SetTextColor(color);
}
void createCMSText(){

    TLatex *tex = new TLatex(0.87,   0.83,"CMS");
    tex->SetNDC(true);
    tex->SetTextFont(61);
    tex->SetTextAlign(31);
    tex->SetTextSize(0.06);
    tex->Draw();

    tex = new TLatex(0.87,   0.78,"Phase-2 Upgrade");
    tex->SetNDC(true);
    tex->SetTextFont(52);
    tex->SetTextAlign(31);
    tex->SetTextSize(0.0456);
    tex->Draw();

    tex = new TLatex(0.89,   0.72,"Simulation Preliminary");
    tex->SetNDC(true);
    tex->SetTextFont(52);
    tex->SetTextAlign(31);
    tex->SetTextSize(0.0456);
    tex->Draw();
    
	tex = new TLatex(0.9,   0.91,"(14 TeV, <PU> = 140)");
    tex->SetNDC(true);
    tex->SetTextFont(42);
    tex->SetTextAlign(31);
    tex->SetTextSize(0.048);
    tex->Draw();
}
void plot( TFile* fbkg, TFile* fsig_l1,TFile* fsig_reco, const char* histo_name, const char* xtit, const char* ytit="Events", double ymax = 0) {

  //gSystem->Load("tdrstyle_C.so");
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
  //h1->SetName("TP 0 Pileup Events");
  h1->Rebin(2);
  h1->SetTitle("");

  TH1F* h2 = dynamic_cast<TH1F*>(fsig_l1->Get(histo_name));
  assert(h2);
  h2->Rebin(2);
  //h2->SetName("L1Signal");
  h2->SetTitle("");

  TH1F* h3 = dynamic_cast<TH1F*>(fsig_reco->Get(histo_name));
  assert(h3);
  h3->Rebin(2);
  //h3->SetName("OfflineSignal");
  h3->SetTitle("");
  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  
  //h1->GetXaxis()->SetTitle(xtit);
  //h1->GetYaxis()->SetTitle(ytit);
  //h1->SetLineColor(kBlack);
  //h1->SetFillColor(41);
  //h1->SetFillStyle(3359);
  //gStyle->SetHatchesSpacing(1);
  //gStyle->SetHatchesLineWidth(9);
  //h1->Draw();

  if(ymax > 0)h1->SetMaximum(ymax);
  else h1->SetMaximum(1.1*std::max(h1->GetBinContent(h1->GetMaximumBin()), h3->GetBinContent(h3->GetMaximumBin())));
  h1->SetMinimum(0.9*std::min(h1->GetBinContent(h1->GetMinimumBin()), h3->GetBinContent(h3->GetMinimumBin())));


  gStyle->SetOptStat(0);
  //h1->SetLineWidth(3);
  //h1->SetLineStyle(2);
  //h1->SetOptStat(1);
  //bindstat(h1,0.7,0.3,0.9,0.5);
  
  //h2->SetLineColor(kRed);
  //h2->SetLineWidth(4);
  //h2->SetLineStyle(9);
  //h2->SetOptStat(1);
  //h2->Draw("SAME");
  //bindstat(h2,0.7,0.5,0.9,0.7,2);
  
  //h3->SetLineColor(kBlue);
  //h3->SetLineWidth(3);
  //h3->SetLineStyle(3);
  //h3->SetOptStat(1);
  //h3->Draw("SAME");
  //bindstat(h3,0.7,0.7,0.9,0.9,3);i
  
  int ci = TColor::GetColor("#339900");
  h1->SetFillColor(ci);
  h1->SetLineColor(ci);
  h1->SetLineStyle(0);
  h1->GetXaxis()->SetTitle(xtit);
  h1->GetXaxis()->SetNdivisions(505);
  h1->GetXaxis()->SetLabelFont(labelandtitlefonts);
  h1->GetXaxis()->SetLabelOffset(0.007);
  h1->GetXaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetLabelSize(0.05);
  h1->GetXaxis()->SetTitleSize(0.06);
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


  ci = TColor::GetColor("#00008f");
  h3->SetLineColor(ci);
  h3->SetLineWidth(2);
  h3->SetLineStyle(1);
  h3->GetXaxis()->SetNdivisions(505);
  h3->GetXaxis()->SetLabelFont(labelandtitlefonts);
  h3->GetXaxis()->SetLabelOffset(0.007);
  h3->GetXaxis()->SetLabelSize(0.05);
  h3->GetXaxis()->SetTitleSize(0.06);
  h3->GetXaxis()->SetTitleFont(labelandtitlefonts);

  h3->GetYaxis()->SetLabelFont(labelandtitlefonts);
  h3->GetYaxis()->SetLabelOffset(0.007);
  h3->GetYaxis()->SetLabelSize(0.05);
  h3->GetYaxis()->SetTitleSize(0.06);
  h3->GetYaxis()->SetTitleOffset(1.1);
  h3->GetYaxis()->SetTitleFont(labelandtitlefonts);

  h3->GetZaxis()->SetLabelFont(42);
  h3->GetZaxis()->SetLabelOffset(0.007);
  h3->GetZaxis()->SetLabelSize(0.05);
  h3->GetZaxis()->SetTitleSize(0.06);
  h3->GetZaxis()->SetTitleFont(42);
  h3->Draw("SAME");
   
  TLegend *leg = new TLegend(0.63, 0.45, 0.85, 0.70, NULL, "brNDC");
  leg->SetBorderSize(0);
  leg->SetTextFont(labelandtitlefonts);

  /*leg->SetTextSize(0.04);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(0);
	leg->SetFillColor(0);
	leg->SetFillStyle(1001); */

  leg->AddEntry(h2,"L1 Signal","l");
  leg->AddEntry(h3,"Offline Signal","l");
  leg->AddEntry(h1,"L1 Background","f");
  leg->Draw();
   
  createCMSText();
}
