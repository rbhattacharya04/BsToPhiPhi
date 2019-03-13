void roc_eta2_5()
{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Mar 15 11:03:17 2017) by ROOT version6.06/04
   TCanvas *c1 = new TCanvas("c1", "c1",0,26,1366,716);
   c1->Range(21.875,-12.25,53.125,90.25);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1F *h1__1 = new TH1F("h1__1","h1",250,25,50);
   h1__1->SetBinContent(61,1.41);
   h1__1->SetBinContent(116,2.47);
   h1__1->SetBinContent(166,6.34);
   h1__1->SetBinError(61,0.7);
   h1__1->SetBinError(116,0.93);
   h1__1->SetBinError(166,1.49);
   h1__1->SetMinimum(-2);
   h1__1->SetMaximum(80);
   h1__1->SetEntries(3);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *AText = ptstats->AddText("h1");
   AText->SetTextSize(0.0368);
   AText = ptstats->AddText("Entries = 3      ");
   AText = ptstats->AddText("Mean  =  38.89");
   AText = ptstats->AddText("Std Dev   =  3.767");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   h1__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h1__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   h1__1->SetLineColor(ci);
   h1__1->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h1__1->SetMarkerColor(ci);
   h1__1->SetMarkerStyle(20);
   h1__1->SetMarkerSize(1.2);
   h1__1->GetXaxis()->SetTitle("Efficiency (%)");
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetLabelSize(0.035);
   h1__1->GetXaxis()->SetTitleSize(0.035);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetTitle("Rate (kHz)");
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetLabelSize(0.035);
   h1__1->GetYaxis()->SetTitleSize(0.035);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetLabelSize(0.035);
   h1__1->GetZaxis()->SetTitleSize(0.035);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("C");
   
   TH1F *h2__2 = new TH1F("h2__2","h2",250,25,50);
   h2__2->SetBinContent(61,5.07);
   h2__2->SetBinContent(116,13.3);
   h2__2->SetBinContent(166,27.86);
   h2__2->SetBinError(61,0.73);
   h2__2->SetBinError(116,1.18);
   h2__2->SetBinError(166,1.72);
   h2__2->SetEntries(3);

   ci = TColor::GetColor("#0000ff");
   h2__2->SetLineColor(ci);
   h2__2->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   h2__2->SetMarkerColor(ci);
   h2__2->SetMarkerStyle(21);
   h2__2->SetMarkerSize(1.2);
   h2__2->GetXaxis()->SetLabelFont(42);
   h2__2->GetXaxis()->SetLabelSize(0.035);
   h2__2->GetXaxis()->SetTitleSize(0.035);
   h2__2->GetXaxis()->SetTitleFont(42);
   h2__2->GetYaxis()->SetLabelFont(42);
   h2__2->GetYaxis()->SetLabelSize(0.035);
   h2__2->GetYaxis()->SetTitleSize(0.035);
   h2__2->GetYaxis()->SetTitleFont(42);
   h2__2->GetZaxis()->SetLabelFont(42);
   h2__2->GetZaxis()->SetLabelSize(0.035);
   h2__2->GetZaxis()->SetTitleSize(0.035);
   h2__2->GetZaxis()->SetTitleFont(42);
   h2__2->Draw("CSAME");
   
   TH1F *h3__3 = new TH1F("h3__3","h3",250,25,50);
   h3__3->SetBinContent(61,12.18);
   h3__3->SetBinContent(116,29.57);
   h3__3->SetBinContent(166,61.75);
   h3__3->SetBinError(61,2.3);
   h3__3->SetBinError(116,3.59);
   h3__3->SetBinError(166,5.19);
   h3__3->SetEntries(3);

   ci = TColor::GetColor("#00ffff");
   h3__3->SetLineColor(ci);
   h3__3->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   h3__3->SetMarkerColor(ci);
   h3__3->SetMarkerStyle(22);
   h3__3->SetMarkerSize(1.2);
   h3__3->GetXaxis()->SetLabelFont(42);
   h3__3->GetXaxis()->SetLabelSize(0.035);
   h3__3->GetXaxis()->SetTitleSize(0.035);
   h3__3->GetXaxis()->SetTitleFont(42);
   h3__3->GetYaxis()->SetLabelFont(42);
   h3__3->GetYaxis()->SetLabelSize(0.035);
   h3__3->GetYaxis()->SetTitleSize(0.035);
   h3__3->GetYaxis()->SetTitleFont(42);
   h3__3->GetZaxis()->SetLabelFont(42);
   h3__3->GetZaxis()->SetLabelSize(0.035);
   h3__3->GetZaxis()->SetTitleSize(0.035);
   h3__3->GetZaxis()->SetTitleFont(42);
   h3__3->Draw("CSAME");
   
   TLegend *leg = new TLegend(0.25,0.75,0.5,0.93,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h1","70 Pileup","LP");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h2","140 Pileup","LP");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(62);
   entry=leg->AddEntry("h3","200 Pileup","LP");

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(62);
   leg->Draw();
      tex = new TLatex(5.03,0.1,"CMS PRELIMINARY SIMULATION");
   tex->SetTextColor(2);
   tex->SetTextFont(42);
   tex->SetTextSize(0.034);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(30.5,2,"Tight Baseline");
   tex->SetTextColor(16);
   tex->SetTextFont(42);
   tex->SetTextSize(0.03);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(36,2,"Medium Baseline");
   tex->SetTextColor(16);
   tex->SetTextFont(42);
   tex->SetTextSize(0.03);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(41,2,"Loose Baseline");
   tex->SetTextColor(16);
   tex->SetTextFont(42);
   tex->SetTextSize(0.03);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TPaveText *pt = new TPaveText(0.472808,0.94,0.527192,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   AText = pt->AddText("h1");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
