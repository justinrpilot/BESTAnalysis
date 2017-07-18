{

gStyle->SetTitleFont(42, "xyz");
gStyle->SetLabelFont(42, "xyz");
gStyle->SetLabelSize(0.055, "xyz");
gStyle->SetTitleSize(0.055, "xyz");
gStyle->SetTitleOffset(1.15, "xy");
gStyle->SetTitleOffset(0.8, "z");
gStyle->SetLegendFont(42);

TFile *fileJJ = new TFile("out_QCDall.root", "READ");
//jjHist = (TH2F *) fileJJ->Get("outXY")->Clone("jjHist");
TFile *fileTT = new TFile("out_TTall.root", "READ");
//ttHist = (TH2F *) fileTT->Get("outXY")->Clone("ttHist");
TFile *fileWW = new TFile("out_WWall.root", "READ");
//wwHist = (TH2F *) fileWW->Get("outXY")->Clone("wwHist");
TFile *fileZZ = new TFile("out_ZZall.root", "READ");
//zzHist = (TH2F *) fileZZ->Get("outXY")->Clone("zzHist");
TFile *fileHH = new TFile("out_HHall.root", "READ");
TTree *treeTT = (TTree *) fileTT->Get("jetTree");
TTree *treeZZ = (TTree *) fileZZ->Get("jetTree");
TTree *treeWW = (TTree *) fileWW->Get("jetTree");
TTree *treeJJ = (TTree *) fileJJ->Get("jetTree");
TTree *treeHH = (TTree *) fileHH->Get("jetTree");
TH2F *jjHist = new TH2F("jjHist", "jjHist", 50, -1.2, 1.2, 50, -1.2, 1.2);
TH2F *wwHist = new TH2F("wwHist", "wwHist", 50, -1.2, 1.2, 50, -1.2, 1.2);
TH2F *ttHist = new TH2F("ttHist", "ttHist", 50, -1.2, 1.2, 50, -1.2, 1.2);
TH2F *zzHist = new TH2F("zzHist", "zzHist", 50, -1.2, 1.2, 50, -1.2, 1.2);
TH2F *hhHist = new TH2F("hhHist", "hhHist", 50, -1.2, 1.2, 50, -1.2, 1.2);


TCutG *gcut = new TCutG("gcut",32);
gcut->SetVarX("(NNoutX-NNoutY)");
gcut->SetVarY("(NNout4-NNout3)");

float xinit = 0.0;
float yinit = 0.0;
float r = 0.1;
float x = r * -1;
float y = r*r - x*x;
for (int p = 0; p < 8; p++){

        gcut->SetPoint(p, x, y);
        cout << p << " " << x << " " << y << endl;
        x += r / 8;
        y = -1*sqrt(r*r - x*x);
}
for (int p = 8; p < 16; p++){

        x += r/ 8;
        y = -1*sqrt(r*r - x*x + 0.0001);
        gcut->SetPoint(p, x, y);
        cout << p << " " << x << " " << y << endl;
}
for (int p = 16; p < 24; p++){

        cout << p << " " << x << " " << y << endl;
        x -= r / 8;
        y = sqrt(r*r - x*x);
        gcut->SetPoint(p, x, y);
}
for (int p = 24; p < 32; p++){

        x -= r/ 8;
        y = 1*sqrt(r*r - x*x);
        cout << p << " " << x << " " << y << endl;
        gcut->SetPoint(p, x, y);
}










cout << treeTT->GetEntries() << endl;
cout << treeWW->GetEntries() << endl;
cout << treeZZ->GetEntries() << endl;
cout << treeJJ->GetEntries() << endl;
string cut = "et > 500 && et < 3000";
treeTT->Draw("(NNoutX-NNout3):(NNoutY-NNout4) >> ttHist", cut.c_str(), "goff");
treeWW->Draw("(NNoutX-NNout3):(NNoutY-NNout4) >> wwHist", cut.c_str(), "goff");
treeZZ->Draw("(NNoutX-NNout3):(NNoutY-NNout4) >> zzHist", cut.c_str(), "goff");
treeJJ->Draw("(NNoutX-NNout3):(NNoutY-NNout4) >> jjHist", cut.c_str(), "goff");
treeHH->Draw("(NNoutX-NNout3):(NNoutY-NNout4) >> hhHist", cut.c_str(), "goff");

cout << ttHist->GetEntries() << endl;
cout << zzHist->GetEntries() << endl;
cout << jjHist->GetEntries() << endl;
cout << wwHist->GetEntries() << endl;




jjHist->SetLineColor(kBlue);
ttHist->SetLineColor(kRed);
wwHist->SetLineColor(kGreen);
zzHist->SetLineColor(kOrange);
hhHist->SetLineColor(kViolet);
jjHist->SetMarkerColor(kBlue);
ttHist->SetMarkerColor(kRed);
wwHist->SetMarkerColor(kGreen);
zzHist->SetMarkerColor(kOrange);
hhHist->SetMarkerColor(kViolet);
//jjHist->SetLineWidth(0.5);
//ttHist->SetLineWidth(0.5);
//wwHist->SetLineWidth(0.5);
//zzHist->SetLineWidth(0.5);
//hhHist->SetLineWidth(0.5);
jjHist->GetXaxis()->SetTitle("NN_{2} - NN_{4}");
jjHist->GetYaxis()->SetTitle("NN_{1} - NN_{3}");
hhHist->GetXaxis()->SetTitle("NN_{2} - NN_{4}");
hhHist->GetYaxis()->SetTitle("NN_{1} - NN_{3}");
ttHist->GetXaxis()->SetTitle("NN_{2} - NN_{4}");
ttHist->GetYaxis()->SetTitle("NN_{1} - NN_{3}");
zzHist->GetXaxis()->SetTitle("NN_{2} - NN_{4}");
zzHist->GetYaxis()->SetTitle("NN_{1} - NN_{3}");
wwHist->GetXaxis()->SetTitle("NN_{2} - NN_{4}");
wwHist->GetYaxis()->SetTitle("NN_{1} - NN_{3}");
jjHist->GetXaxis()->SetTitleOffset(1.60);
jjHist->GetYaxis()->SetTitleOffset(1.60);
hhHist->GetXaxis()->SetTitleOffset(1.60);
hhHist->GetYaxis()->SetTitleOffset(1.60);
ttHist->GetXaxis()->SetTitleOffset(1.60);
ttHist->GetYaxis()->SetTitleOffset(1.60);
wwHist->GetXaxis()->SetTitleOffset(1.60);
wwHist->GetYaxis()->SetTitleOffset(1.60);
zzHist->GetXaxis()->SetTitleOffset(1.60);
zzHist->GetYaxis()->SetTitleOffset(1.60);
jjHist->GetZaxis()->SetLabelSize(0);
hhHist->GetZaxis()->SetLabelSize(0);
ttHist->GetZaxis()->SetLabelSize(0);
wwHist->GetZaxis()->SetLabelSize(0);
zzHist->GetZaxis()->SetLabelSize(0);
jjHist->GetZaxis()->SetTitle("QCD Jets");
hhHist->GetZaxis()->SetTitle("Higgs Jets");
ttHist->GetZaxis()->SetTitle("Top Quark Jets");
wwHist->GetZaxis()->SetTitle("W Boson Jets");
zzHist->GetZaxis()->SetTitle("Z Boson Jets");

//ttHist->SetMaximum(100000.);
//wwHist->SetMaximum(100000.);
//zzHist->SetMaximum(100000.);
//hhHist->SetMaximum(100000.);
//jjHist->SetMaximum(100000.);
jjHist->Draw("lego");
CMS_lumi(c1, 4, 0);
c1->SaveAs("jj_5dOutput_cuts.pdf");
TCanvas *c2 = new TCanvas();
c2->cd();
ttHist->Draw("lego  ");
CMS_lumi(c2, 4, 0);
c2->SaveAs("tt_5dOutput_cuts.pdf");
TCanvas *c5 = new TCanvas();
c5->cd();
wwHist->Draw("lego  ");
CMS_lumi(c5, 4, 0);
c5->SaveAs("ww_5dOutput_cuts.pdf");

TCanvas *c4 = new TCanvas();
c4->cd();
zzHist->Draw("lego  ");
CMS_lumi(c4, 4, 0);
c4->SaveAs("zz_5dOutput_cuts.pdf");

TCanvas *c3 = new TCanvas();
c3->cd();
hhHist->Draw("lego  ");
CMS_lumi(c3, 4, 0);
c3->SaveAs("hh_5dOutput_cuts.pdf");

TCanvas *c6 = new TCanvas();


ttHist->Draw("cont3");
wwHist->Draw("cont3 same");
zzHist->Draw("cont3 same");
hhHist->Draw("cont3 same");
jjHist->Draw("cont3 same");
gPad->SetLeftMargin(0.13);
gPad->SetBottomMargin(0.13);



CMS_lumi(c6, 4, 0);
c6->SaveAs("all_5dOutput_cuts.pdf");



TLegend *leg = new TLegend(0.11, 0.58, 0.46, 0.89);
leg->SetNColumns(1);
leg->AddEntry(jjHist, "Light Jets", "l");
leg->AddEntry(ttHist, "Top Jets", "l");
leg->AddEntry(wwHist, "W Jets", "l");
leg->AddEntry(zzHist, "Z Jets", "l");
leg->AddEntry(hhHist, "H Jets", "l");
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->Draw("same");

/*
TGraph *roc = new TGraph(150*150);

int i = 0;
for (int binx = 1; binx < jjHist->GetNbinsX(); binx++){

	for (int biny = 1; biny < jjHist->GetNbinsX(); biny++){

		mistagEff = jjHist->Integral(binx, jjHist->GetNbinsX(), biny, jjHist->GetNbinsY() )  / jjHist->Integral();
		signalEff = ttHist->Integral(binx, ttHist->GetNbinsX(), biny, ttHist->GetNbinsY() )  / ttHist->Integral();		
		roc->SetPoint(i, signalEff, 1-mistagEff);
		i++;
	}

}


TCanvas *c4 = new TCanvas();
c4->cd();

roc->Draw("AP");
*/


}


