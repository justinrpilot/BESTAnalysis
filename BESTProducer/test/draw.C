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



treeTT->Draw(Form("%s>>histTT", var.c_str()), sel.c_str());
treeZZ->Draw(Form("%s>>histZZ", var.c_str()), sel.c_str());
treeWW->Draw(Form("%s>>histWW", var.c_str()), sel.c_str());
treeJJ->Draw(Form("%s>>histJJ", var.c_str()), sel.c_str());
treeHH->Draw(Form("%s>>histHH", var.c_str()), sel.c_str());

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

histTT->GetXaxis()->SetTitle(label.c_str());

histTT->Scale( 1. / histTT->Integral() );
histTT->SetMaximum(0.25);

histTT->Draw();
histZZ->DrawNormalized("same");
histWW->DrawNormalized("same");
histJJ->DrawNormalized("same");
histHH->DrawNormalized("same");

//c1->SetLogy();

TLegend *leg = new TLegend (0.11, 0.91, 0.94, 0.99);
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->SetNColumns(5);
leg->AddEntry(histTT, "Top", "l");
leg->AddEntry(histZZ, "Z", "l");
leg->AddEntry(histWW, "W", "l");
leg->AddEntry(histHH, "H", "l");
leg->AddEntry(histJJ, "QCD", "l");
leg->Draw("same");

c1->SaveAs( Form("%s.pdf", var.c_str()) );

}



