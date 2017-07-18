void draw(string var, string label, string sel, int nbins, float xmin, float xmax){

TFile *fileTT = new TFile("out_TT_2TeV.root", "READ");
TFile *fileZZ = new TFile("out_TT_3TeV.root", "READ");
TFile *fileWW = new TFile("out_TT_4TeV.root", "READ");


TTree *treeTT = (TTree *) fileTT->Get("jetTree");
TTree *treeZZ = (TTree *) fileZZ->Get("jetTree");
TTree *treeWW = (TTree *) fileWW->Get("jetTree");

TH1F *histTT = new TH1F("histTT", "histTT", nbins, xmin, xmax);
TH1F *histWW = new TH1F("histWW", "histWW", nbins, xmin, xmax);
TH1F *histZZ = new TH1F("histZZ", "histZZ", nbins, xmin, xmax);

TCanvas *c1 = new TCanvas();



treeTT->Draw(Form("%s>>histTT", var.c_str()), sel.c_str());
treeZZ->Draw(Form("%s>>histZZ", var.c_str()), sel.c_str());
treeWW->Draw(Form("%s>>histWW", var.c_str()), sel.c_str());

histTT->SetLineColor(kRed);
histWW->SetLineColor(kBlue+1);
histZZ->SetLineColor(kOrange);
histTT->SetLineWidth(2);
histWW->SetLineWidth(2);
histZZ->SetLineWidth(2);

histTT->GetXaxis()->SetTitle(label.c_str());

histTT->Scale( 1. / histTT->Integral() );
histWW->Scale( 1. / histWW->Integral() );
histZZ->Scale( 1. / histZZ->Integral() );
histTT->SetMaximum(1.00);
histTT->SetMinimum(0.0001);

histTT->Draw("hist");
histZZ->DrawNormalized("hist same");
histWW->DrawNormalized("hist same");


c1->SetLogy();

TLegend *leg = new TLegend (0.11, 0.91, 0.94, 0.99);
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->SetNColumns(5);
leg->AddEntry(histTT, "2 TeV Z'#rightarrow t#bar{t}", "l");
leg->AddEntry(histZZ, "3 TeV Z'#rightarrow t#bar{t}", "l");
leg->AddEntry(histWW, "4 TeV Z'#rightarrow t#bar{t}", "l");
leg->SetTextSize(0.04);
leg->Draw("same");

c1->SaveAs( Form("%s_zpmasses.pdf", var.c_str()) );

}



