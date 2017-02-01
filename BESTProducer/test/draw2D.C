{



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
TH2F *jjHist = new TH2F("jjHist", "jjHist", 1000, -1.2, 1.2, 1000, -1.2, 1.2);
TH2F *wwHist = new TH2F("wwHist", "wwHist", 1000, -1.2, 1.2, 1000, -1.2, 1.2);
TH2F *ttHist = new TH2F("ttHist", "ttHist", 1000, -1.2, 1.2, 1000, -1.2, 1.2);
TH2F *zzHist = new TH2F("zzHist", "zzHist", 1000, -1.2, 1.2, 1000, -1.2, 1.2);
TH2F *hhHist = new TH2F("hhHist", "hhHist", 1000, -1.2, 1.2, 1000, -1.2, 1.2);


TCutG *gcut = new TCutG("gcut",32);
gcut->SetVarX("(NNout3-NNout4)");
gcut->SetVarY("(NNoutX-NNoutY)");

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
zzHist->SetLineColor(kYellow);
hhHist->SetLineColor(kViolet);
jjHist->SetMarkerColor(kBlue);
ttHist->SetMarkerColor(kRed);
wwHist->SetMarkerColor(kGreen);
zzHist->SetMarkerColor(kYellow);
hhHist->SetMarkerColor(kViolet);
jjHist->SetLineWidth(0.5);
ttHist->SetLineWidth(0.5);
wwHist->SetLineWidth(0.5);
zzHist->SetLineWidth(0.5);
hhHist->SetLineWidth(0.5);

jjHist->Draw("scat");
c1->SaveAs("jj_4dOutput.pdf");
TCanvas *c2 = new TCanvas();
c2->cd();
ttHist->Draw("scat  ");
c2->SaveAs("tt_4dOutput.pdf");
TCanvas *c5 = new TCanvas();
c5->cd();
wwHist->Draw("scat  ");
c5->SaveAs("ww_4dOutput.pdf");

TCanvas *c4 = new TCanvas();
c4->cd();
zzHist->Draw("scat  ");
c4->SaveAs("zz_4dOutput.pdf");

TCanvas *c3 = new TCanvas();
c3->cd();
hhHist->Draw("scat  ");
c3->SaveAs("hh_4dOutput.pdf");

TCanvas *c6 = new TCanvas();
ttHist->Draw("scat");
wwHist->Draw("scat same");
zzHist->Draw("scat same");
hhHist->Draw("scat same");
jjHist->Draw("scat same");
c6->SaveAs("all_4dOutput.pdf");



TLegend *leg = new TLegend(0.1, 0.91, 0.91, 0.99);
leg->SetNColumns(5);
leg->AddEntry(jjHist, "QCD", "l");
leg->AddEntry(ttHist, "Top", "l");
leg->AddEntry(wwHist, "W", "l");
leg->AddEntry(zzHist, "Z", "l");
leg->AddEntry(hhHist, "H", "l");
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


