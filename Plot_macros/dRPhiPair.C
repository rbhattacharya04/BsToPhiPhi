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
void dRPhiPair () {
   
   int labelandtitlefonts=42;
  
   TCanvas* c1=createCanvas();

   TH1F *drPhiPairBkg = new TH1F("drPhiPairBkg","",50,0,3);
   drPhiPairBkg->SetBinContent(1,0.05545168);
   drPhiPairBkg->SetBinContent(2,0.04295316);
   drPhiPairBkg->SetBinContent(3,0.0296461);
   drPhiPairBkg->SetBinContent(4,0.02117338);
   drPhiPairBkg->SetBinContent(5,0.01416612);
   drPhiPairBkg->SetBinContent(6,0.01150471);
   drPhiPairBkg->SetBinContent(7,0.009736049);
   drPhiPairBkg->SetBinContent(8,0.009634983);
   drPhiPairBkg->SetBinContent(9,0.008826452);
   drPhiPairBkg->SetBinContent(10,0.00820321);
   drPhiPairBkg->SetBinContent(11,0.008860141);
   drPhiPairBkg->SetBinContent(12,0.009382317);
   drPhiPairBkg->SetBinContent(13,0.01069618);
   drPhiPairBkg->SetBinContent(14,0.01079724);
   drPhiPairBkg->SetBinContent(15,0.01142049);
   drPhiPairBkg->SetBinContent(16,0.01249853);
   drPhiPairBkg->SetBinContent(17,0.01175737);
   drPhiPairBkg->SetBinContent(18,0.01236377);
   drPhiPairBkg->SetBinContent(19,0.0134755);
   drPhiPairBkg->SetBinContent(20,0.01418296);
   drPhiPairBkg->SetBinContent(21,0.01391345);
   drPhiPairBkg->SetBinContent(22,0.01517678);
   drPhiPairBkg->SetBinContent(23,0.01553051);
   drPhiPairBkg->SetBinContent(24,0.01610322);
   drPhiPairBkg->SetBinContent(25,0.01713073);
   drPhiPairBkg->SetBinContent(26,0.01644011);
   drPhiPairBkg->SetBinContent(27,0.01775397);
   drPhiPairBkg->SetBinContent(28,0.01851197);
   drPhiPairBkg->SetBinContent(29,0.01894992);
   drPhiPairBkg->SetBinContent(30,0.0204996);
   drPhiPairBkg->SetBinContent(31,0.01905099);
   drPhiPairBkg->SetBinContent(32,0.021864);
   drPhiPairBkg->SetBinContent(33,0.02233564);
   drPhiPairBkg->SetBinContent(34,0.02145973);
   drPhiPairBkg->SetBinContent(35,0.02152711);
   drPhiPairBkg->SetBinContent(36,0.02198191);
   drPhiPairBkg->SetBinContent(37,0.0239527);
   drPhiPairBkg->SetBinContent(38,0.02354844);
   drPhiPairBkg->SetBinContent(39,0.02439065);
   drPhiPairBkg->SetBinContent(40,0.02492967);
   drPhiPairBkg->SetBinContent(41,0.02550238);
   drPhiPairBkg->SetBinContent(42,0.02678256);
   drPhiPairBkg->SetBinContent(43,0.02624354);
   drPhiPairBkg->SetBinContent(44,0.02597403);
   drPhiPairBkg->SetBinContent(45,0.02600772);
   drPhiPairBkg->SetBinContent(46,0.02956188);
   drPhiPairBkg->SetBinContent(47,0.02722051);
   drPhiPairBkg->SetBinContent(48,0.0296461);
   drPhiPairBkg->SetBinContent(49,0.02966294);
   drPhiPairBkg->SetBinContent(50,0.03161689);
   drPhiPairBkg->SetBinContent(51,0.3632489);
   drPhiPairBkg->SetMinimum(0.003477377);
   drPhiPairBkg->SetMaximum(0.06106762);
   drPhiPairBkg->SetEntries(80932);

   int ci = TColor::GetColor("#339900");
   drPhiPairBkg->SetFillColor(ci);
   drPhiPairBkg->SetLineColor(ci);
   drPhiPairBkg->SetLineStyle(0);
   drPhiPairBkg->GetXaxis()->SetTitle("#DeltaR(#phi-pair)");
   drPhiPairBkg->GetXaxis()->SetNdivisions(505);
   drPhiPairBkg->GetXaxis()->SetLabelFont(labelandtitlefonts);
   drPhiPairBkg->GetXaxis()->SetLabelOffset(0.007);
   drPhiPairBkg->GetXaxis()->SetLabelSize(0.05);
   drPhiPairBkg->GetXaxis()->SetTitleSize(0.06);
   drPhiPairBkg->GetXaxis()->SetTitleOffset(1.1);
   drPhiPairBkg->GetXaxis()->SetTitleFont(labelandtitlefonts);
   drPhiPairBkg->GetYaxis()->SetTitle("Normalized no. of #phi pairs");
   drPhiPairBkg->GetYaxis()->SetNdivisions(505);
   drPhiPairBkg->GetYaxis()->SetLabelFont(labelandtitlefonts);
   drPhiPairBkg->GetYaxis()->SetLabelOffset(0.007);
   drPhiPairBkg->GetYaxis()->SetLabelSize(0.05);
   drPhiPairBkg->GetYaxis()->SetTitleSize(0.06);
   drPhiPairBkg->GetYaxis()->SetTitleOffset(1.1);
   drPhiPairBkg->GetYaxis()->SetTitleFont(labelandtitlefonts);
   
   drPhiPairBkg->GetZaxis()->SetLabelFont(42);
   drPhiPairBkg->GetZaxis()->SetLabelOffset(0.007);
   drPhiPairBkg->GetZaxis()->SetLabelSize(0.05);
   drPhiPairBkg->GetZaxis()->SetTitleSize(0.06);
   drPhiPairBkg->GetZaxis()->SetTitleFont(42);
   drPhiPairBkg->Draw("");
   
   TH1F *drPhiPairSig = new TH1F("drPhiPairSig","",50,0,3);
   drPhiPairSig->SetBinContent(1,0.01325444);
   drPhiPairSig->SetBinContent(2,0.006627219);
   drPhiPairSig->SetBinContent(3,0.01420118);
   drPhiPairSig->SetBinContent(4,0.0104142);
   drPhiPairSig->SetBinContent(5,0.02035503);
   drPhiPairSig->SetBinContent(6,0.02461538);
   drPhiPairSig->SetBinContent(7,0.03337278);
   drPhiPairSig->SetBinContent(8,0.04047337);
   drPhiPairSig->SetBinContent(9,0.04378698);
   drPhiPairSig->SetBinContent(10,0.05420118);
   drPhiPairSig->SetBinContent(11,0.05017751);
   drPhiPairSig->SetBinContent(12,0.05491124);
   drPhiPairSig->SetBinContent(13,0.05538461);
   drPhiPairSig->SetBinContent(14,0.05278106);
   drPhiPairSig->SetBinContent(15,0.04378698);
   drPhiPairSig->SetBinContent(16,0.03147929);
   drPhiPairSig->SetBinContent(17,0.02177515);
   drPhiPairSig->SetBinContent(18,0.01514793);
   drPhiPairSig->SetBinContent(19,0.01112426);
   drPhiPairSig->SetBinContent(20,0.008047338);
   drPhiPairSig->SetBinContent(21,0.007337278);
   drPhiPairSig->SetBinContent(22,0.006390532);
   drPhiPairSig->SetBinContent(23,0.01207101);
   drPhiPairSig->SetBinContent(24,0.01112426);
   drPhiPairSig->SetBinContent(25,0.01088757);
   drPhiPairSig->SetBinContent(26,0.01088757);
   drPhiPairSig->SetBinContent(27,0.0104142);
   drPhiPairSig->SetBinContent(28,0.01065089);
   drPhiPairSig->SetBinContent(29,0.01088757);
   drPhiPairSig->SetBinContent(30,0.01065089);
   drPhiPairSig->SetBinContent(31,0.01278106);
   drPhiPairSig->SetBinContent(32,0.01420118);
   drPhiPairSig->SetBinContent(33,0.01349112);
   drPhiPairSig->SetBinContent(34,0.01230769);
   drPhiPairSig->SetBinContent(35,0.01159763);
   drPhiPairSig->SetBinContent(36,0.01017751);
   drPhiPairSig->SetBinContent(37,0.0156213);
   drPhiPairSig->SetBinContent(38,0.01254438);
   drPhiPairSig->SetBinContent(39,0.01349112);
   drPhiPairSig->SetBinContent(40,0.01443787);
   drPhiPairSig->SetBinContent(41,0.01278106);
   drPhiPairSig->SetBinContent(42,0.01656805);
   drPhiPairSig->SetBinContent(43,0.01775148);
   drPhiPairSig->SetBinContent(44,0.01585799);
   drPhiPairSig->SetBinContent(45,0.01704142);
   drPhiPairSig->SetBinContent(46,0.01443787);
   drPhiPairSig->SetBinContent(47,0.01609468);
   drPhiPairSig->SetBinContent(48,0.01775148);
   drPhiPairSig->SetBinContent(49,0.01727811);
   drPhiPairSig->SetBinContent(50,0.01656805);
   drPhiPairSig->SetBinContent(51,0.1966864);
   drPhiPairSig->SetEntries(5056);

   ci = TColor::GetColor("#ff0000");
   drPhiPairSig->SetLineColor(ci);
   drPhiPairSig->SetLineStyle(2);
   drPhiPairSig->SetLineWidth(2);
   drPhiPairSig->GetXaxis()->SetNdivisions(505);
   drPhiPairSig->GetXaxis()->SetLabelFont(labelandtitlefonts);
   drPhiPairSig->GetXaxis()->SetLabelOffset(0.007);
   drPhiPairSig->GetXaxis()->SetLabelSize(0.05);
   drPhiPairSig->GetXaxis()->SetTitleSize(0.06);
   drPhiPairSig->GetXaxis()->SetTitleFont(labelandtitlefonts);
   drPhiPairSig->GetYaxis()->SetLabelFont(labelandtitlefonts);
   drPhiPairSig->GetYaxis()->SetLabelOffset(0.007);
   drPhiPairSig->GetYaxis()->SetLabelSize(0.05);
   drPhiPairSig->GetYaxis()->SetTitleSize(0.06);
   drPhiPairSig->GetYaxis()->SetTitleOffset(1.3);
   drPhiPairSig->GetYaxis()->SetTitleFont(labelandtitlefonts);

   drPhiPairSig->GetZaxis()->SetLabelFont(42);
   drPhiPairSig->GetZaxis()->SetLabelOffset(0.007);
   drPhiPairSig->GetZaxis()->SetLabelSize(0.05);
   drPhiPairSig->GetZaxis()->SetTitleSize(0.06);
   drPhiPairSig->GetZaxis()->SetTitleFont(42);
   drPhiPairSig->Draw("SAME");
   
   TH1F *drPhiPairOff = new TH1F("drPhiPairOff","",50,0,3);
   drPhiPairOff->SetBinContent(1,0.003863752);
   drPhiPairOff->SetBinContent(2,0.008235892);
   drPhiPairOff->SetBinContent(3,0.01098119);
   drPhiPairOff->SetBinContent(4,0.01189629);
   drPhiPairOff->SetBinContent(5,0.01392984);
   drPhiPairOff->SetBinContent(6,0.02216573);
   drPhiPairOff->SetBinContent(7,0.02501271);
   drPhiPairOff->SetBinContent(8,0.0359939);
   drPhiPairOff->SetBinContent(9,0.04117946);
   drPhiPairOff->SetBinContent(10,0.04656838);
   drPhiPairOff->SetBinContent(11,0.05114387);
   drPhiPairOff->SetBinContent(12,0.05551602);
   drPhiPairOff->SetBinContent(13,0.05002542);
   drPhiPairOff->SetBinContent(14,0.04972039);
   drPhiPairOff->SetBinContent(15,0.04260295);
   drPhiPairOff->SetBinContent(16,0.02928317);
   drPhiPairOff->SetBinContent(17,0.02297916);
   drPhiPairOff->SetBinContent(18,0.01494662);
   drPhiPairOff->SetBinContent(19,0.008947636);
   drPhiPairOff->SetBinContent(20,0.009049314);
   drPhiPairOff->SetBinContent(21,0.009964413);
   drPhiPairOff->SetBinContent(22,0.008744281);
   drPhiPairOff->SetBinContent(23,0.0104728);
   drPhiPairOff->SetBinContent(24,0.01067616);
   drPhiPairOff->SetBinContent(25,0.01250635);
   drPhiPairOff->SetBinContent(26,0.01281139);
   drPhiPairOff->SetBinContent(27,0.01026945);
   drPhiPairOff->SetBinContent(28,0.01281139);
   drPhiPairOff->SetBinContent(29,0.01240468);
   drPhiPairOff->SetBinContent(30,0.01270971);
   drPhiPairOff->SetBinContent(31,0.01443823);
   drPhiPairOff->SetBinContent(32,0.01270971);
   drPhiPairOff->SetBinContent(33,0.0141332);
   drPhiPairOff->SetBinContent(34,0.01484494);
   drPhiPairOff->SetBinContent(35,0.01403152);
   drPhiPairOff->SetBinContent(36,0.012303);
   drPhiPairOff->SetBinContent(37,0.0159634);
   drPhiPairOff->SetBinContent(38,0.0141332);
   drPhiPairOff->SetBinContent(39,0.01687849);
   drPhiPairOff->SetBinContent(40,0.01647178);
   drPhiPairOff->SetBinContent(41,0.01718353);
   drPhiPairOff->SetBinContent(42,0.01687849);
   drPhiPairOff->SetBinContent(43,0.01718353);
   drPhiPairOff->SetBinContent(44,0.01677682);
   drPhiPairOff->SetBinContent(45,0.01779359);
   drPhiPairOff->SetBinContent(46,0.01962379);
   drPhiPairOff->SetBinContent(47,0.01728521);
   drPhiPairOff->SetBinContent(48,0.02125064);
   drPhiPairOff->SetBinContent(49,0.02287748);
   drPhiPairOff->SetBinContent(50,0.01982715);
   drPhiPairOff->SetBinContent(51,0.2880529);
   drPhiPairOff->SetEntries(12668);

   ci = TColor::GetColor("#00008f");
   drPhiPairOff->SetLineColor(ci);
   drPhiPairOff->SetLineWidth(2);
   //   drPhiPairOff->SetLineStyle(1);
   drPhiPairOff->GetXaxis()->SetNdivisions(505);
   drPhiPairOff->GetXaxis()->SetLabelFont(labelandtitlefonts);
   drPhiPairOff->GetXaxis()->SetLabelOffset(0.007);
   drPhiPairOff->GetXaxis()->SetLabelSize(0.05);
   drPhiPairOff->GetXaxis()->SetTitleSize(0.06);
   drPhiPairOff->GetXaxis()->SetTitleFont(labelandtitlefonts);
   drPhiPairOff->GetYaxis()->SetLabelFont(labelandtitlefonts);
   drPhiPairOff->GetYaxis()->SetLabelOffset(0.007);
   drPhiPairOff->GetYaxis()->SetLabelSize(0.05);
   drPhiPairOff->GetYaxis()->SetTitleSize(0.06);
   drPhiPairOff->GetYaxis()->SetTitleOffset(1.3);
   drPhiPairOff->GetYaxis()->SetTitleFont(labelandtitlefonts);
   
   drPhiPairOff->GetZaxis()->SetLabelFont(42);
   drPhiPairOff->GetZaxis()->SetLabelOffset(0.007);
   drPhiPairOff->GetZaxis()->SetLabelSize(0.05);
   drPhiPairOff->GetZaxis()->SetTitleSize(0.06);
   drPhiPairOff->GetZaxis()->SetTitleFont(42);
   drPhiPairOff->Draw("SAME");
   
   TLegend *leg = new TLegend(0.63, 0.48, 0.85, 0.73, NULL, "brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(labelandtitlefonts);

   /*leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001); */

   leg->AddEntry("drPhiPairSig","L1 Signal","l");
   leg->AddEntry("drPhiPairOff","Offline Signal","l");
   leg->AddEntry("drPhiPairBkg","L1 Background","f");
   leg->Draw();

   createCMSText();
   
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
