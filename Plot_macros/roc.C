TCanvas* createCanvas(){
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

    return c1;
}


void createCMSText(){

    TLatex *tex = new TLatex(0.87,   0.83,"CMS");
    tex->SetNDC(true);
    tex->SetTextFont(61);
    tex->SetTextAlign(31);
    tex->SetTextSize(0.06);
    tex->Draw();

    tex = new TLatex(0.87,   0.77,"Preliminary Projection");
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
void roc() {
   
   int labelandtitlefonts=42;

   TCanvas* c1=createCanvas();

   TH1F *h1__1 = new TH1F("h1__1","h1",250,25,50);
   h1__1->SetBinContent(61,1.41);
   h1__1->SetBinContent(116,2.47);
   h1__1->SetBinContent(166,6.34);
   h1__1->SetBinError(61,0.7);
   h1__1->SetBinError(116,0.93);
   h1__1->SetBinError(166,1.49);
   h1__1->SetMinimum(-2);
   h1__1->SetMaximum(85);
   h1__1->SetEntries(3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   h1__1->SetLineColor(ci);
   h1__1->SetLineStyle(0);
   h1__1->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   h1__1->SetMarkerColor(ci);
   h1__1->SetMarkerStyle(20);
   h1__1->SetMarkerSize(1.4);
   h1__1->GetXaxis()->SetNdivisions(505);
   h1__1->GetXaxis()->SetTitle("Efficiency (%)");
   h1__1->GetXaxis()->SetLabelFont(labelandtitlefonts);
   h1__1->GetXaxis()->SetLabelOffset(0.007);
   h1__1->GetXaxis()->SetLabelSize(0.05);
   h1__1->GetXaxis()->SetTitleSize(0.06);
   h1__1->GetXaxis()->SetTitleOffset(0.9);
   h1__1->GetXaxis()->SetTitleFont(labelandtitlefonts);
   h1__1->GetYaxis()->SetTitle("Rate (kHz)");
   h1__1->GetYaxis()->SetNdivisions(505);
   h1__1->GetYaxis()->SetLabelFont(labelandtitlefonts);
   h1__1->GetYaxis()->SetLabelOffset(0.007);
   h1__1->GetYaxis()->SetLabelSize(0.05);
   h1__1->GetYaxis()->SetTitleSize(0.06);
   h1__1->GetYaxis()->SetTitleOffset(1.1);
   h1__1->GetYaxis()->SetTitleFont(labelandtitlefonts);
   
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetLabelOffset(0.007);
   h1__1->GetZaxis()->SetLabelSize(0.05);
   h1__1->GetZaxis()->SetTitleSize(0.06);
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

   ci = TColor::GetColor("#00008f");
   h2__2->SetLineColor(ci);
   h2__2->SetLineStyle(0);
   h2__2->SetLineWidth(2);

   ci = TColor::GetColor("#00008f");
   h2__2->SetMarkerColor(ci);
   h2__2->SetMarkerStyle(21);
   h2__2->SetMarkerSize(1.4);
   h2__2->GetXaxis()->SetLabelFont(labelandtitlefonts);
   h2__2->GetXaxis()->SetLabelOffset(0.007);
   h2__2->GetXaxis()->SetLabelSize(0.05);
   h2__2->GetXaxis()->SetTitleSize(0.06);
   h2__2->GetXaxis()->SetTitleOffset(1.1);
   h2__2->GetXaxis()->SetTitleFont(labelandtitlefonts);
   h2__2->GetYaxis()->SetLabelFont(labelandtitlefonts);
   h2__2->GetYaxis()->SetLabelOffset(0.007);
   h2__2->GetYaxis()->SetLabelSize(0.05);
   h2__2->GetYaxis()->SetTitleSize(0.06);
   h2__2->GetYaxis()->SetTitleOffset(1.3);
   h2__2->GetYaxis()->SetTitleFont(labelandtitlefonts);
   
   h2__2->GetZaxis()->SetLabelFont(42);
   h2__2->GetZaxis()->SetLabelOffset(0.007);
   h2__2->GetZaxis()->SetLabelSize(0.05);
   h2__2->GetZaxis()->SetTitleSize(0.06);
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

   ci = TColor::GetColor("#16a085");
   h3__3->SetLineColor(ci);
   h3__3->SetLineStyle(0);
   h3__3->SetLineWidth(2);

   ci = TColor::GetColor("#16a085");
   h3__3->SetMarkerColor(ci);
   h3__3->SetMarkerStyle(22);
   h3__3->SetMarkerSize(1.4);
   h3__3->GetXaxis()->SetLabelFont(labelandtitlefonts);
   h3__3->GetXaxis()->SetLabelOffset(0.007);
   h3__3->GetXaxis()->SetLabelSize(0.05);
   h3__3->GetXaxis()->SetTitleSize(0.06);
   h3__3->GetXaxis()->SetTitleOffset(1.1);
   h3__3->GetXaxis()->SetTitleFont(labelandtitlefonts);
   h3__3->GetYaxis()->SetLabelFont(labelandtitlefonts);
   h3__3->GetYaxis()->SetLabelOffset(0.007);
   h3__3->GetYaxis()->SetLabelSize(0.05);
   h3__3->GetYaxis()->SetTitleSize(0.06);
   h3__3->GetYaxis()->SetTitleOffset(1.3);
   h3__3->GetYaxis()->SetTitleFont(labelandtitlefonts);

   h3__3->GetZaxis()->SetLabelFont(42);
   h3__3->GetZaxis()->SetLabelOffset(0.007);
   h3__3->GetZaxis()->SetLabelSize(0.05);
   h3__3->GetZaxis()->SetTitleSize(0.06);
   h3__3->GetZaxis()->SetTitleFont(42);
   h3__3->Draw("CSAME");
   
   TLegend *leg = new TLegend(0.18, 0.5, 0.5, 0.7, NULL, "brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(labelandtitlefonts);
   /* 
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001); */

   leg->AddEntry("h1__1", "<PU> =  70", "LP");
   leg->AddEntry("h2__2", "<PU> = 140", "LP");
   leg->AddEntry("h3__3", "<PU> = 200", "LP");
   leg->Draw();
   /*
   TLatex* tex1 = new TLatex(26.0, 70, "#splitline{#bf{CMS} #it{Preliminary}}{#splitline{PhaseII Simulation}{#sqrt{s} = 14 TeV}}");
   tex1->SetTextFont(42);
   tex1->SetTextSize(0.04);
   tex1->SetTextAngle(0);
   tex1->SetLineWidth(2);
   tex1->Draw();
   */

   createCMSText();
   
   ci = TColor::GetColor("#abb2b9");
   TLatex *texl = new TLatex(30.3, 2., "Tight Baseline");
   texl->SetTextColor(kBlack);
   texl->SetTextFont(labelandtitlefonts);
   texl->SetTextSize(0.03);
   texl->SetTextAngle(90);
   texl->Draw();

   TLatex *texm = new TLatex(35.8, 2., "Medium Baseline");
   texm->SetTextColor(kBlack);
   texm->SetTextFont(labelandtitlefonts);
   texm->SetTextSize(0.03);
   texm->SetTextAngle(90);
   texm->Draw();

   TLatex *text = new TLatex(40.8, 2., "Loose Baseline");
   text->SetTextColor(kBlack);
   text->SetTextFont(labelandtitlefonts);
   text->SetTextSize(0.03);
   text->SetTextAngle(90);
   text->Draw();

   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
