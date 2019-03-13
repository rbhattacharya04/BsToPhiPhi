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
void bsmass() {
   int labelandtitlefonts=42;

   TCanvas* c1=createCanvas();

   TH1F *bsmassBkg = new TH1F("bsmassBkg","",50,5,5.8);
   bsmassBkg->SetBinContent(0,5.710555);
   bsmassBkg->SetBinContent(1,0.04134929);
   bsmassBkg->SetBinContent(2,0.02937976);
   bsmassBkg->SetBinContent(3,0.02720348);
   bsmassBkg->SetBinContent(4,0.02067465);
   bsmassBkg->SetBinContent(5,0.02176279);
   bsmassBkg->SetBinContent(6,0.0250272);
   bsmassBkg->SetBinContent(7,0.02067465);
   bsmassBkg->SetBinContent(8,0.0250272);
   bsmassBkg->SetBinContent(9,0.02176279);
   bsmassBkg->SetBinContent(10,0.01741023);
   bsmassBkg->SetBinContent(11,0.02829162);
   bsmassBkg->SetBinContent(12,0.02393906);
   bsmassBkg->SetBinContent(13,0.01849837);
   bsmassBkg->SetBinContent(14,0.02393906);
   bsmassBkg->SetBinContent(15,0.02067465);
   bsmassBkg->SetBinContent(16,0.02176279);
   bsmassBkg->SetBinContent(17,0.01632209);
   bsmassBkg->SetBinContent(18,0.02067465);
   bsmassBkg->SetBinContent(19,0.02393906);
   bsmassBkg->SetBinContent(20,0.02067465);
   bsmassBkg->SetBinContent(21,0.03264418);
   bsmassBkg->SetBinContent(22,0.0250272);
   bsmassBkg->SetBinContent(23,0.01632209);
   bsmassBkg->SetBinContent(24,0.01958651);
   bsmassBkg->SetBinContent(25,0.02720348);
   bsmassBkg->SetBinContent(26,0.0250272);
   bsmassBkg->SetBinContent(27,0.01958651);
   bsmassBkg->SetBinContent(28,0.01958651);
   bsmassBkg->SetBinContent(29,0.01632209);
   bsmassBkg->SetBinContent(30,0.02285093);
   bsmassBkg->SetBinContent(31,0.02067465);
   bsmassBkg->SetBinContent(32,0.01958651);
   bsmassBkg->SetBinContent(33,0.01849837);
   bsmassBkg->SetBinContent(34,0.01523395);
   bsmassBkg->SetBinContent(35,0.007616975);
   bsmassBkg->SetBinContent(36,0.01414581);
   bsmassBkg->SetBinContent(37,0.02067465);
   bsmassBkg->SetBinContent(38,0.009793254);
   bsmassBkg->SetBinContent(39,0.01849837);
   bsmassBkg->SetBinContent(40,0.01741023);
   bsmassBkg->SetBinContent(41,0.01088139);
   bsmassBkg->SetBinContent(42,0.02829162);
   bsmassBkg->SetBinContent(43,0.01305767);
   bsmassBkg->SetBinContent(44,0.01305767);
   bsmassBkg->SetBinContent(45,0.01414581);
   bsmassBkg->SetBinContent(46,0.01523395);
   bsmassBkg->SetBinContent(47,0.007616975);
   bsmassBkg->SetBinContent(48,0.01414581);
   bsmassBkg->SetBinContent(49,0.01741023);
   bsmassBkg->SetBinContent(50,0.01088139);
   bsmassBkg->SetBinContent(51,0.773667);
   bsmassBkg->SetMinimum(0.000232859);
   bsmassBkg->SetMaximum(0.2467529);
   bsmassBkg->SetEntries(6878);

   int ci = TColor::GetColor("#339900");
   bsmassBkg->SetFillColor(ci);
   bsmassBkg->SetLineColor(ci);
   bsmassBkg->GetXaxis()->SetTitle("M_{#phi#phi} (GeV)");
   bsmassBkg->GetXaxis()->SetNdivisions(505);
   bsmassBkg->GetXaxis()->SetLabelFont(labelandtitlefonts);
   bsmassBkg->GetXaxis()->SetLabelOffset(0.007);
   bsmassBkg->GetXaxis()->SetLabelSize(0.05);
   bsmassBkg->GetXaxis()->SetTitleSize(0.06);
   bsmassBkg->GetXaxis()->SetTitleOffset(1.1);
   bsmassBkg->GetXaxis()->SetTitleFont(labelandtitlefonts);

   bsmassBkg->GetYaxis()->SetTitle("Normalized no. of B_{s} candidates");
   bsmassBkg->GetYaxis()->SetNdivisions(505);
   bsmassBkg->GetYaxis()->SetLabelFont(labelandtitlefonts);
   bsmassBkg->GetYaxis()->SetLabelOffset(0.007);
   bsmassBkg->GetYaxis()->SetLabelSize(0.05);
   bsmassBkg->GetYaxis()->SetTitleSize(0.06);
   bsmassBkg->GetYaxis()->SetTitleOffset(1.1);
   bsmassBkg->GetYaxis()->SetTitleFont(labelandtitlefonts);

   bsmassBkg->GetZaxis()->SetLabelFont(42);
   bsmassBkg->GetZaxis()->SetLabelOffset(0.007);
   bsmassBkg->GetZaxis()->SetLabelSize(0.05);
   bsmassBkg->GetZaxis()->SetTitleSize(0.06);
   bsmassBkg->GetZaxis()->SetTitleFont(42);
   bsmassBkg->Draw("");
   
   TH1F *bsmassSig = new TH1F("bsmassSig","",50,5,5.8);
   bsmassSig->SetBinContent(0,0.0976);
   bsmassSig->SetBinContent(1,0.002133333);
   bsmassSig->SetBinContent(5,0.0005333333);
   bsmassSig->SetBinContent(6,0.0005333333);
   bsmassSig->SetBinContent(7,0.001066667);
   bsmassSig->SetBinContent(8,0.001066667);
   bsmassSig->SetBinContent(9,0.0005333333);
   bsmassSig->SetBinContent(10,0.002666667);
   bsmassSig->SetBinContent(11,0.0032);
   bsmassSig->SetBinContent(12,0.0032);
   bsmassSig->SetBinContent(13,0.002666667);
   bsmassSig->SetBinContent(14,0.0005333333);
   bsmassSig->SetBinContent(15,0.001066667);
   bsmassSig->SetBinContent(16,0.0032);
   bsmassSig->SetBinContent(17,0.001066667);
   bsmassSig->SetBinContent(18,0.004266667);
   bsmassSig->SetBinContent(19,0.008533333);
   bsmassSig->SetBinContent(20,0.0272);
   bsmassSig->SetBinContent(21,0.0592);
   bsmassSig->SetBinContent(22,0.1125333);
   bsmassSig->SetBinContent(23,0.1488);
   bsmassSig->SetBinContent(24,0.1562667);
   bsmassSig->SetBinContent(25,0.1173333);
   bsmassSig->SetBinContent(26,0.07253333);
   bsmassSig->SetBinContent(27,0.0544);
   bsmassSig->SetBinContent(28,0.04693333);
   bsmassSig->SetBinContent(29,0.03466666);
   bsmassSig->SetBinContent(30,0.03093333);
   bsmassSig->SetBinContent(31,0.02186667);
   bsmassSig->SetBinContent(32,0.016);
   bsmassSig->SetBinContent(33,0.01173333);
   bsmassSig->SetBinContent(34,0.01173333);
   bsmassSig->SetBinContent(35,0.0096);
   bsmassSig->SetBinContent(36,0.008533333);
   bsmassSig->SetBinContent(37,0.003733333);
   bsmassSig->SetBinContent(38,0.0048);
   bsmassSig->SetBinContent(39,0.002133333);
   bsmassSig->SetBinContent(40,0.0016);
   bsmassSig->SetBinContent(41,0.0016);
   bsmassSig->SetBinContent(42,0.002666667);
   bsmassSig->SetBinContent(44,0.0016);
   bsmassSig->SetBinContent(45,0.0016);
   bsmassSig->SetBinContent(46,0.0005333333);
   bsmassSig->SetBinContent(48,0.001066667);
   bsmassSig->SetBinContent(49,0.001066667);
   bsmassSig->SetBinContent(50,0.001066667);
   bsmassSig->SetBinContent(51,0.04);
   bsmassSig->SetEntries(2133);

   ci = TColor::GetColor("#ff0000");
   bsmassSig->SetLineColor(ci);
   bsmassSig->SetLineStyle(2);
   bsmassSig->SetLineWidth(2);
   bsmassSig->GetXaxis()->SetNdivisions(505);
   bsmassSig->GetXaxis()->SetLabelFont(labelandtitlefonts);
   bsmassSig->GetXaxis()->SetLabelOffset(0.007);
   bsmassSig->GetXaxis()->SetLabelSize(0.05);
   bsmassSig->GetXaxis()->SetTitleSize(0.06);
   bsmassSig->GetXaxis()->SetTitleFont(labelandtitlefonts);

   bsmassSig->GetYaxis()->SetLabelFont(labelandtitlefonts);
   bsmassSig->GetYaxis()->SetLabelOffset(0.007);
   bsmassSig->GetYaxis()->SetLabelSize(0.05);
   bsmassSig->GetYaxis()->SetTitleSize(0.06);
   bsmassSig->GetYaxis()->SetTitleOffset(1.3);
   bsmassSig->GetYaxis()->SetTitleFont(labelandtitlefonts);

   bsmassSig->GetZaxis()->SetLabelFont(42);
   bsmassSig->GetZaxis()->SetLabelOffset(0.007);
   bsmassSig->GetZaxis()->SetLabelSize(0.05);
   bsmassSig->GetZaxis()->SetTitleSize(0.06);
   bsmassSig->GetZaxis()->SetTitleFont(42);
   bsmassSig->Draw("SAME");
   
   TH1F *bsmassOff = new TH1F("bsmassOff","",50,5,5.8);
   bsmassOff->SetBinContent(0,0.1407503);
   bsmassOff->SetBinContent(1,0.001293661);
   bsmassOff->SetBinContent(2,0.002587322);
   bsmassOff->SetBinContent(3,0.002069858);
   bsmassOff->SetBinContent(4,0.001034929);
   bsmassOff->SetBinContent(5,0.0007761967);
   bsmassOff->SetBinContent(6,0.0005174644);
   bsmassOff->SetBinContent(7,0.001293661);
   bsmassOff->SetBinContent(8,0.003104787);
   bsmassOff->SetBinContent(9,0.0007761967);
   bsmassOff->SetBinContent(10,0.001811125);
   bsmassOff->SetBinContent(11,0.002587322);
   bsmassOff->SetBinContent(12,0.004139715);
   bsmassOff->SetBinContent(13,0.003880983);
   bsmassOff->SetBinContent(14,0.003880983);
   bsmassOff->SetBinContent(15,0.007503234);
   bsmassOff->SetBinContent(16,0.007503234);
   bsmassOff->SetBinContent(17,0.01060802);
   bsmassOff->SetBinContent(18,0.01345407);
   bsmassOff->SetBinContent(19,0.01992238);
   bsmassOff->SetBinContent(20,0.0305304);
   bsmassOff->SetBinContent(21,0.05433377);
   bsmassOff->SetBinContent(22,0.09443726);
   bsmassOff->SetBinContent(23,0.1764554);
   bsmassOff->SetBinContent(24,0.2243208);
   bsmassOff->SetBinContent(25,0.1347995);
   bsmassOff->SetBinContent(26,0.06701164);
   bsmassOff->SetBinContent(27,0.03260026);
   bsmassOff->SetBinContent(28,0.02095731);
   bsmassOff->SetBinContent(29,0.014489);
   bsmassOff->SetBinContent(30,0.01423027);
   bsmassOff->SetBinContent(31,0.007503234);
   bsmassOff->SetBinContent(32,0.00698577);
   bsmassOff->SetBinContent(33,0.005433376);
   bsmassOff->SetBinContent(34,0.004915912);
   bsmassOff->SetBinContent(35,0.00232859);
   bsmassOff->SetBinContent(36,0.001552393);
   bsmassOff->SetBinContent(37,0.00232859);
   bsmassOff->SetBinContent(38,0.002069858);
   bsmassOff->SetBinContent(39,0.002069858);
   bsmassOff->SetBinContent(40,0.001811125);
   bsmassOff->SetBinContent(41,0.001552393);
   bsmassOff->SetBinContent(42,0.001552393);
   bsmassOff->SetBinContent(43,0.001034929);
   bsmassOff->SetBinContent(44,0.001034929);
   bsmassOff->SetBinContent(45,0.002069858);
   bsmassOff->SetBinContent(46,0.0005174644);
   bsmassOff->SetBinContent(47,0.0007761967);
   bsmassOff->SetBinContent(48,0.0007761967);
   bsmassOff->SetBinContent(49,0.0005174644);
   bsmassOff->SetBinContent(50,0.0002587322);
   bsmassOff->SetBinContent(51,0.04243208);
   bsmassOff->SetEntries(4573);

   ci = TColor::GetColor("#00008f");
   bsmassOff->SetLineColor(ci);
   bsmassOff->SetLineWidth(2);
   bsmassOff->SetLineStyle(1);
   bsmassOff->GetXaxis()->SetNdivisions(505);
   bsmassOff->GetXaxis()->SetLabelFont(labelandtitlefonts);
   bsmassOff->GetXaxis()->SetLabelOffset(0.007);
   bsmassOff->GetXaxis()->SetLabelSize(0.05);
   bsmassOff->GetXaxis()->SetTitleSize(0.06);
   bsmassOff->GetXaxis()->SetTitleFont(labelandtitlefonts);
   
   bsmassOff->GetYaxis()->SetLabelFont(labelandtitlefonts);
   bsmassOff->GetYaxis()->SetLabelOffset(0.007);
   bsmassOff->GetYaxis()->SetLabelSize(0.05);
   bsmassOff->GetYaxis()->SetTitleSize(0.06);
   bsmassOff->GetYaxis()->SetTitleOffset(1.1);
   bsmassOff->GetYaxis()->SetTitleFont(labelandtitlefonts);

   bsmassOff->GetZaxis()->SetLabelFont(42);
   bsmassOff->GetZaxis()->SetLabelOffset(0.007);
   bsmassOff->GetZaxis()->SetLabelSize(0.05);
   bsmassOff->GetZaxis()->SetTitleSize(0.06);
   bsmassOff->GetZaxis()->SetTitleFont(42);
   bsmassOff->Draw("SAME");
   
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

   leg->AddEntry("bsmassSig", "L1 Signal","l");
   leg->AddEntry("bsmassOff", "Offline Signal","l");
   leg->AddEntry("bsmassBkg", "L1 Background","f");
   leg->Draw();

   createCMSText();
   
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
