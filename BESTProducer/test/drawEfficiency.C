#include "CMS_lumi.C"

void drawEfficiency(string thiscut, string label){


gStyle->SetTitleFont(42, "xyz");
gStyle->SetLabelFont(42, "xyz");
gStyle->SetLegendFont(42);
gStyle->SetLabelSize(0.055, "xyz");
gStyle->SetTitleSize(0.055, "xyz");
gStyle->SetLegendFont(42);

TFile *zp2File = new TFile("out_TT_2TeV.root");
TFile *zp3File = new TFile("out_TT_3TeV.root");
TFile *zp4File = new TFile("out_TT_4TeV.root");
TFile *combFile = new TFile("out_QCDall.root");



TTree *zp2Tree = (TTree *) zp2File->Get("jetTree");
TTree *zp3Tree = (TTree *) zp3File->Get("jetTree");
TTree *zp4Tree = (TTree *) zp4File->Get("jetTree");
TTree *combTree = (TTree *) combFile->Get("jetTree");

float bins[13] = { 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600, 1800, 2000, 2500, 3000 };

TH1F *denom2 = new TH1F("denom2", "denom2", 12, bins);
TH1F *denom3 = new TH1F("denom3", "denom3", 12, bins);
TH1F *denom4 = new TH1F("denom4", "denom4", 12, bins);
TH1F *denomC = new TH1F("denomC", "denomC", 12, bins);
TH1F *num2 = new TH1F("num2", "num2", 12, bins);
TH1F *num3 = new TH1F("num3", "num3", 12, bins);
TH1F *num4 = new TH1F("num4", "num4", 12, bins);
TH1F *numC = new TH1F("numC", "numC", 12, bins);

num2->Sumw2();
num3->Sumw2();
num4->Sumw2();
numC->Sumw2();
denom2->Sumw2();
denom3->Sumw2();
denom4->Sumw2();
denomC->Sumw2();

zp2Tree->Draw("et >> denom2", "(et > 500 && bDisc > -1)");
zp3Tree->Draw("et >> denom3", "(et > 500 && bDisc > -1)");
zp4Tree->Draw("et >> denom4", "(et > 500 && bDisc > -1)");
combTree->Draw("et >> denomC", "(et > 500 && bDisc > -1)");
zp2Tree->Draw("et >> num2  ", Form("(et > 500 && %s)", thiscut.c_str()) );
zp3Tree->Draw("et >> num3  ", Form("(et > 500 && %s)", thiscut.c_str()) );
zp4Tree->Draw("et >> num4 ", Form("(et > 500 && %s)", thiscut.c_str()) );
combTree->Draw("et >> numC ", Form("(et > 500 && %s)", thiscut.c_str()) );



TH1F *eff2H = (TH1F *) num2->Clone("eff2H");
TH1F *eff3H = (TH1F *) num3->Clone("eff3H");
TH1F *eff4H = (TH1F *) num4->Clone("eff4H");
TH1F *effCH = (TH1F *) numC->Clone("effCH");

eff2H->Divide(num2, denom2, 1, 1, "B");
eff3H->Divide(num3, denom3, 1, 1, "B");
eff4H->Divide(num4, denom4, 1, 1, "B");
effCH->Divide(numC, denomC, 1, 1, "B");

eff2H->SetLineColor(kBlue);
eff3H->SetLineColor(kRed);
eff4H->SetLineColor(kGreen + 1);
effCH->SetLineColor(kBlack);
eff2H->SetLineWidth(2);
eff3H->SetLineWidth(2);
eff4H->SetLineWidth(2);
effCH->SetLineWidth(2);

eff4H->SetMaximum(10.0);
eff4H->SetMinimum(0.0001);
eff4H->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
eff4H->GetYaxis()->SetTitle("Efficiency");


TCanvas *c1 = new TCanvas();
eff4H->Draw("E");
//eff3H->Draw("E same");
effCH->Draw("E same");

gPad->SetBottomMargin(0.13);
gPad->SetLeftMargin(0.13);
gPad->SetLogy(1);
CMS_lumi(c1, 4, 0);

TLegend *leg = new TLegend(0.15, 0.68, 0.43,0.88);
//leg->AddEntry(eff3H, "Z' #rightarrow t#bar{t} (1.5 TeV)", "l");
//leg->AddEntry(eff2H, "Z' #rightarrow t#bar{t} (2 TeV)", "l");
leg->AddEntry(eff4H, "Z' #rightarrow t#bar{t} (4 TeV)", "l");
leg->AddEntry(effCH, "QCD", "l");
leg->AddEntry(effCH, label.c_str(), "");
leg->SetFillColor(0);
leg->SetLineWidth(0);
leg->Draw("same"); 

} 
