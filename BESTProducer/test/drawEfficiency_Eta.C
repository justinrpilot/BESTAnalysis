#include "CMS_lumi.C"

void drawEfficiency(string thiscut, string label){


TFile *zp2File = new TFile("out_TT_2TeV.root");
TFile *zp3File = new TFile("out_TT_3TeV.root");
TFile *zp4File = new TFile("out_TT_4TeV.root");
TFile *combFile = new TFile("out_QCDall.root");



TTree *zp2Tree = (TTree *) zp2File->Get("jetTree");
TTree *zp3Tree = (TTree *) zp3File->Get("jetTree");
TTree *zp4Tree = (TTree *) zp4File->Get("jetTree");
TTree *combTree = (TTree *) combFile->Get("jetTree");


TH1F *denom2 = new TH1F("denom2", "denom2", 20, -3, 3);
TH1F *denom3 = new TH1F("denom3", "denom3", 20, -3, 3);
TH1F *denom4 = new TH1F("denom4", "denom4", 20, -3, 3);
TH1F *denomC = new TH1F("denomC", "denomC", 20, -3, 3);
TH1F *num2 = new TH1F("num2", "num2", 20, -3, 3);
TH1F *num3 = new TH1F("num3", "num3", 20, -3, 3);
TH1F *num4 = new TH1F("num4", "num4", 20, -3, 3);
TH1F *numC = new TH1F("numC", "numC", 20, -3, 3);

num2->Sumw2();
num3->Sumw2();
num4->Sumw2();
numC->Sumw2();
denom2->Sumw2();
denom3->Sumw2();
denom4->Sumw2();
denomC->Sumw2();

zp2Tree->Draw("eta >> denom2", "(et > 500 && bDisc > -1)");
zp3Tree->Draw("eta >> denom3", "(et > 500 && bDisc > -1)");
zp4Tree->Draw("eta >> denom4", "(et > 500 && bDisc > -1)");
combTree->Draw("eta >> denomC", "(et > 500 && bDisc > -1)");
zp2Tree->Draw("eta >> num2  ", Form("(et > 500 && %s)", thiscut.c_str()) );
zp3Tree->Draw("eta >> num3  ", Form("(et > 500 && %s)", thiscut.c_str()) );
zp4Tree->Draw("eta >> num4 ", Form("(et > 500 && %s)", thiscut.c_str()) );
combTree->Draw("eta >> numC ", Form("(et > 500 && %s)", thiscut.c_str()) );



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
eff4H->GetXaxis()->SetTitle("Jet #eta");
eff4H->GetYaxis()->SetTitle("Efficiency");


TCanvas *c1 = new TCanvas();
//eff2H->Draw("E");
//eff3H->Draw("E same");
eff4H->Draw("E");
effCH->Draw("E same");

gPad->SetLogy(1);
CMS_lumi(c1, 4, 0);

TLegend *leg = new TLegend(0.15, 0.68, 0.43,0.88);
leg->AddEntry(eff4H, "Z' #rightarrow t#bar{t} (4 TeV)", "l");
leg->AddEntry(effCH, "QCD", "l");
leg->AddEntry(effCH, label.c_str(), "");
leg->SetFillColor(0);
leg->SetLineWidth(0);
leg->Draw("same"); 

} 
