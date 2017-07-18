#include "CMS_lumi.C"

void draw(string var, string label, string sel, int nbins, float xmin, float xmax){

TFile *fileTT = new TFile("out_TTall.root", "READ");
TFile *fileZZ = new TFile("out_ZZall.root", "READ");
TFile *fileWW = new TFile("out_WWall.root", "READ");
TFile *fileJJ = new TFile("out_QCDall.root", "READ");
TFile *fileHH = new TFile("out_HHall.root", "READ");


TTree *treeTT = (TTree *) fileTT->Get("jetTree");
TTree *treeZZ = (TTree *) fileZZ->Get("jetTree");
TTree *treeWW = (TTree *) fileWW->Get("jetTree");
TTree *treeJJ = (TTree *) fileJJ->Get("jetTree");
TTree *treeHH = (TTree *) fileHH->Get("jetTree");

TH1F *histTT = new TH1F("histTT", "histTT", nbins, xmin, xmax);
TH1F *histWW = new TH1F("histWW", "histWW", nbins, xmin, xmax);
TH1F *histZZ = new TH1F("histZZ", "histZZ", nbins, xmin, xmax);
TH1F *histJJ = new TH1F("histJJ", "histJJ", nbins, xmin, xmax);
TH1F *histHH = new TH1F("histHH", "histHH", nbins, xmin, xmax);

TCanvas *c1 = new TCanvas();


/*
treeTT->Draw(Form("%s>>histTT", var.c_str()), Form("flatten*(et > 500 && et < 1500 && SDmass > 10)*(%s)", sel.c_str()));
treeZZ->Draw(Form("%s>>histZZ", var.c_str()), Form("flatten*(et > 500 && et < 1500 && SDmass > 10)*(%s)", sel.c_str()));
treeWW->Draw(Form("%s>>histWW", var.c_str()), Form("flatten*(et > 500 && et < 1500 && SDmass > 10)*(%s)", sel.c_str()));
treeJJ->Draw(Form("%s>>histJJ", var.c_str()), Form("flatten*(et > 500 && et < 1500 && SDmass > 10)*(%s)", sel.c_str()));
treeHH->Draw(Form("%s>>histHH", var.c_str()), Form("flatten*(et > 500 && et < 1500 && SDmass > 10)*(%s)", sel.c_str()));
*/

treeTT->Draw(Form("%s>>histTT", var.c_str()), Form("1*(%s)", sel.c_str()));
treeZZ->Draw(Form("%s>>histZZ", var.c_str()), Form("1*(%s)", sel.c_str()));
treeWW->Draw(Form("%s>>histWW", var.c_str()), Form("1*(%s)", sel.c_str()));
treeJJ->Draw(Form("%s>>histJJ", var.c_str()), Form("1*(%s)", sel.c_str()));
treeHH->Draw(Form("%s>>histHH", var.c_str()), Form("1*(%s)", sel.c_str()));


histTT->SetLineColor(kRed);
histWW->SetLineColor(kGreen+1);
histZZ->SetLineColor(kOrange);
histJJ->SetLineColor(kBlue);
histHH->SetLineColor(kViolet);
histTT->SetLineWidth(2);
histWW->SetLineWidth(2);
histZZ->SetLineWidth(2);
histJJ->SetLineWidth(2);
histHH->SetLineWidth(2);

histTT->GetYaxis()->SetTitle("Fraction of Jets");
histTT->GetYaxis()->SetTitleOffset(1.08);
histTT->GetYaxis()->SetTitleSize(0.055);
histTT->GetYaxis()->SetLabelSize(0.055);
histTT->GetXaxis()->SetTitleSize(0.055);
histTT->GetXaxis()->SetLabelSize(0.055);
histTT->GetXaxis()->SetTitle(label.c_str());
histTT->GetXaxis()->SetTitleFont(42);
histTT->GetYaxis()->SetTitleFont(42);
histTT->GetXaxis()->SetLabelFont(42);
histTT->GetYaxis()->SetLabelFont(42);

histTT->Scale( 1. / histTT->Integral() );
histWW->Scale( 1. / histWW->Integral() );
histZZ->Scale( 1. / histZZ->Integral() );
histJJ->Scale( 1. / histJJ->Integral() );
histHH->Scale( 1. / histHH->Integral() );
histTT->SetMaximum(1.75*TMath::Max(histTT->GetMaximum(), TMath::Max(histJJ->GetMaximum(), TMath::Max(histZZ->GetMaximum(), TMath::Max(histHH->GetMaximum(), histWW->GetMaximum())))));
histTT->SetMinimum(0);

histTT->Draw("hist");
histZZ->DrawNormalized("hist same");
histWW->DrawNormalized("hist same");
histJJ->DrawNormalized("hist  same");
histHH->DrawNormalized("hist  same");

gPad->SetBottomMargin(0.13);
gPad->SetLeftMargin(0.13);

	cout.precision(2);
	
	cout << "Classified as j " << histJJ->GetBinContent(1) << " " << histTT->GetBinContent(1) << " " << histWW->GetBinContent(1) << " " << histZZ->GetBinContent(1) << " " << histHH->GetBinContent(1) << endl;
	cout << "Classified as t " << histJJ->GetBinContent(2) << " " << histTT->GetBinContent(2) << " " << histWW->GetBinContent(2) << " " << histZZ->GetBinContent(2) << " " << histHH->GetBinContent(2) << endl;
	cout << "Classified as W " << histJJ->GetBinContent(5) << " " << histTT->GetBinContent(5) << " " << histWW->GetBinContent(5) << " " << histZZ->GetBinContent(5) << " " << histHH->GetBinContent(5) << endl;
	cout << "Classified as Z " << histJJ->GetBinContent(4) << " " << histTT->GetBinContent(4) << " " << histWW->GetBinContent(4) << " " << histZZ->GetBinContent(4) << " " << histHH->GetBinContent(4) << endl;
	cout << "Classified as H " << histJJ->GetBinContent(3) << " " << histTT->GetBinContent(3) << " " << histWW->GetBinContent(3) << " " << histZZ->GetBinContent(3) << " " << histHH->GetBinContent(3) << endl;


//c1->SetLogy();

TLegend *leg = new TLegend (0.52, 0.65, 0.89, 0.88);
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->SetNColumns(2);
leg->SetTextFont(42);
leg->AddEntry(histTT, "Top Jets", "l");
leg->AddEntry(histZZ, "Z Jets", "l");
leg->AddEntry(histWW, "W Jets", "l");
leg->AddEntry(histHH, "H Jets", "l");
leg->AddEntry(histJJ, "Light Jets", "l");
leg->Draw("same");
TLegend *leg2 = new TLegend(0.06, 0.73, 0.48, 0.88);
leg2->SetFillColor(0);
leg2->SetFillStyle(0);
leg2->SetLineWidth(0);
leg2->SetLineColor(0);
leg2->SetTextFont(42);
//leg2->AddEntry(histJJ, "0.5 TeV < Jet p_{T} < 1.5 TeV", "");
leg2->AddEntry(histJJ,   "Jet p_{T} > 0.5 TeV          ", "");
leg2->AddEntry(histJJ, "                   ", "");
//leg2->AddEntry(histJJ, "Jet m_{SD} > 10 GeV", "");
leg2->Draw("same");


CMS_lumi(c1, 4, 0);
gPad->RedrawAxis();

c1->SaveAs( Form("%s_fiveD.pdf", var.c_str()) );

}



