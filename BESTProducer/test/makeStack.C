#include "CMS_lumi.C"


void drawROC( TH1F *histS, TH1F *histB, int color, float noCutTT, float noCutQCD);

void makeStack(string var, string label, string sel, int nbins, float xmin, float xmax){

cout << sel.c_str() << endl;

TFile *fileQCD_1 = new TFile("out_QCD1.root", "READ");
TFile *fileQCD_2 = new TFile("out_QCD2.root", "READ");
TFile *fileQCD_3 = new TFile("out_QCD3.root", "READ");
TFile *fileQCD_4 = new TFile("out_QCD4.root", "READ");
TFile *fileQCD_5 = new TFile("out_QCD5.root", "READ");
TFile *fileQCD_6 = new TFile("out_QCD6.root", "READ");
TFile *fileQCD_7 = new TFile("out_QCD7.root", "READ");
TFile *fileQCD_8 = new TFile("out_QCD8.root", "READ");
TFile *fileQCD_9 = new TFile("out_QCD9.root", "READ");

TFile *fileTT = new TFile("out_ttbar.root", "READ");
TFile *fileWj = new TFile("out_Wjets.root", "READ");
TFile *fileZj = new TFile("out_Zjets.root", "READ");

TFile *sigT = new TFile("out_TTall.root", "READ");
TFile *sigW = new TFile("out_WWall.root", "READ");
TFile *sigZ = new TFile("out_ZZall.root", "READ");
TFile *sigH = new TFile("out_HHall.root", "READ");


TFile *fileDATA = new TFile("out_DATA.root", "READ");

TTree *treeQCD_1 = (TTree *) fileQCD_1->Get("jetTree");
TTree *treeQCD_2 = (TTree *) fileQCD_2->Get("jetTree");
TTree *treeQCD_3 = (TTree *) fileQCD_3->Get("jetTree");
TTree *treeQCD_4 = (TTree *) fileQCD_4->Get("jetTree");
TTree *treeQCD_5 = (TTree *) fileQCD_5->Get("jetTree");
TTree *treeQCD_6 = (TTree *) fileQCD_6->Get("jetTree");
TTree *treeQCD_7 = (TTree *) fileQCD_7->Get("jetTree");
TTree *treeQCD_8 = (TTree *) fileQCD_8->Get("jetTree");
TTree *treeQCD_9 = (TTree *) fileQCD_9->Get("jetTree");
TTree *treeDATA = (TTree *) fileDATA->Get("jetTree");

TTree *treeTT = (TTree *) fileTT->Get("jetTree");
TTree *treeWj = (TTree *) fileWj->Get("jetTree");
TTree *treeZj = (TTree *) fileZj->Get("jetTree");

TTree *tree_sigW = (TTree *) sigW->Get("jetTree");
TTree *tree_sigZ = (TTree *) sigZ->Get("jetTree");
TTree *tree_sigH = (TTree *) sigH->Get("jetTree");
TTree *tree_sigT = (TTree *) sigT->Get("jetTree");


TH1F *histQCD_1 = new TH1F("histQCD_1", "histQCD_1", nbins, xmin, xmax);
TH1F *histQCD_2 = new TH1F("histQCD_2", "histQCD_2", nbins, xmin, xmax);
TH1F *histQCD_3 = new TH1F("histQCD_3", "histQCD_3", nbins, xmin, xmax);
TH1F *histQCD_4 = new TH1F("histQCD_4", "histQCD_4", nbins, xmin, xmax);
TH1F *histQCD_5 = new TH1F("histQCD_5", "histQCD_5", nbins, xmin, xmax);
TH1F *histQCD_6 = new TH1F("histQCD_6", "histQCD_6", nbins, xmin, xmax);
TH1F *histQCD_7 = new TH1F("histQCD_7", "histQCD_7", nbins, xmin, xmax);
TH1F *histQCD_8 = new TH1F("histQCD_8", "histQCD_8", nbins, xmin, xmax);
TH1F *histQCD_9 = new TH1F("histQCD_9", "histQCD_9", nbins, xmin, xmax);
TH1F *histDATA = new TH1F("histDATA", "histDATA", nbins, xmin, xmax);
TH1F *histTT = new TH1F("histTT", "histTT", nbins, xmin, xmax);
TH1F *histWj = new TH1F("histWj", "histWj", nbins, xmin, xmax);
TH1F *histZj = new TH1F("histZj", "histZj", nbins, xmin, xmax);

TH1F *hist_sigW = new TH1F("hist_sigW", "hist_sigW", nbins, xmin, xmax);
TH1F *hist_sigZ = new TH1F("hist_sigZ", "hist_sigZ", nbins, xmin, xmax);
TH1F *hist_sigH = new TH1F("hist_sigH", "hist_sigH", nbins, xmin, xmax);
TH1F *hist_sigT = new TH1F("hist_sigT", "hist_sigT", nbins, xmin, xmax);


TCanvas *c1 = new TCanvas("c1", "c1", 0, 0, 600, 500);
c1->Range(0,0,1,1);
c1->Draw();

TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.25);
c1_1->Draw();
TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.25,0.99,0.99);
c1_2->Draw();

c1->cd();
c1_2->cd();
c1_2->SetTopMargin(0.1);
c1_2->SetBottomMargin(0.1);
c1_2->SetRightMargin(0.05);
c1_2->SetLeftMargin(0.1);
c1_2->SetFillStyle(0);

treeQCD_1->Draw( Form( "%s >> histQCD_1", var.c_str() ), sel.c_str() );
treeQCD_2->Draw( Form( "%s >> histQCD_2", var.c_str() ), sel.c_str() );
treeQCD_3->Draw( Form( "%s >> histQCD_3", var.c_str() ), sel.c_str() );
treeQCD_4->Draw( Form( "%s >> histQCD_4", var.c_str() ), sel.c_str() );
treeQCD_5->Draw( Form( "%s >> histQCD_5", var.c_str() ), sel.c_str() );
treeQCD_6->Draw( Form( "%s >> histQCD_6", var.c_str() ), sel.c_str() );
treeQCD_7->Draw( Form( "%s >> histQCD_7", var.c_str() ), sel.c_str() );
treeQCD_8->Draw( Form( "%s >> histQCD_8", var.c_str() ), sel.c_str() );
treeQCD_9->Draw( Form( "%s >> histQCD_9", var.c_str() ), sel.c_str() );

string count_sel = "bDisc > -1";

float totNumQCD = treeQCD_1->GetEntries(count_sel.c_str()) +
	       treeQCD_2->GetEntries(count_sel.c_str()) +
	       treeQCD_3->GetEntries(count_sel.c_str()) +
	       treeQCD_4->GetEntries(count_sel.c_str()) +
	       treeQCD_5->GetEntries(count_sel.c_str()) +
	       treeQCD_6->GetEntries(count_sel.c_str()) +
	       treeQCD_7->GetEntries(count_sel.c_str()) +
	       treeQCD_8->GetEntries(count_sel.c_str()) +
	       treeQCD_9->GetEntries(count_sel.c_str());

float totNumTT = tree_sigT->GetEntries(count_sel.c_str());


treeDATA->Draw( Form( "%s >> histDATA", var.c_str() ), sel.c_str() );


treeTT->Draw( Form( "%s >> histTT", var.c_str() ), sel.c_str() );
treeWj->Draw( Form( "%s >> histWj", var.c_str() ), sel.c_str() );
treeZj->Draw( Form( "%s >> histZj", var.c_str() ), sel.c_str() );

tree_sigW->Draw( Form( "%s >> hist_sigW", var.c_str() ), sel.c_str() );
tree_sigZ->Draw( Form( "%s >> hist_sigZ", var.c_str() ), sel.c_str() );
tree_sigH->Draw( Form( "%s >> hist_sigH", var.c_str() ), sel.c_str() );
tree_sigT->Draw( Form( "%s >> hist_sigT", var.c_str() ), sel.c_str() );


float lumi = 5057.32;

histQCD_1->Scale( 7823.0 * lumi / 5970600.);
histQCD_2->Scale(  648.2 * lumi / 3928870.);
histQCD_3->Scale(  186.9 * lumi / 3959768.);
histQCD_4->Scale(  32.29 * lumi / 3924080.);
histQCD_5->Scale(  9.418 * lumi / 2999069.);
histQCD_6->Scale(  0.84265 * lumi / 396409.);
histQCD_7->Scale(  0.114943 * lumi / 396100.);
histQCD_8->Scale(  0.0068291 * lumi / 399226.);
histQCD_9->Scale(  0.0001654 * lumi / 383926.);

histTT->Scale( 831.76 * lumi / 92925926. );
histWj->Scale( 95.14*.066*lumi / 1025005.);
histZj->Scale( 5.67 * lumi / 1000000.); 

hist_sigW->Scale(1.  / hist_sigW->Integral() );
hist_sigZ->Scale(1.  / hist_sigZ->Integral() );
hist_sigH->Scale(1.  / hist_sigH->Integral() );
hist_sigT->Scale(1.  / hist_sigT->Integral() );


hist_sigW->SetLineColor(kOrange+2);
hist_sigZ->SetLineColor(kMagenta+2);
hist_sigH->SetLineColor(kTeal + 3);
hist_sigT->SetLineColor(kRed + 2);

hist_sigW->SetLineWidth(2);
hist_sigZ->SetLineWidth(2);
hist_sigH->SetLineWidth(2);
hist_sigT->SetLineWidth(2);


histTT->SetFillColor(kRed);
histTT->SetLineColor(kRed);
histZj->SetFillColor(kGreen+1);
histZj->SetLineColor(kGreen+1);
histWj->SetFillColor(kBlue);
histWj->SetLineColor(kBlue);

histQCD_1->SetFillColor(kYellow + 1);
histQCD_2->SetFillColor(kYellow + 1);
histQCD_3->SetFillColor(kYellow + 1);
histQCD_4->SetFillColor(kYellow + 1);
histQCD_5->SetFillColor(kYellow + 1);
histQCD_6->SetFillColor(kYellow + 1);
histQCD_7->SetFillColor(kYellow + 1);
histQCD_8->SetFillColor(kYellow + 1);
histQCD_9->SetFillColor(kYellow + 1);
histQCD_1->SetLineColor(kYellow + 1);
histQCD_2->SetLineColor(kYellow + 1);
histQCD_3->SetLineColor(kYellow + 1);
histQCD_4->SetLineColor(kYellow + 1);
histQCD_5->SetLineColor(kYellow + 1);
histQCD_6->SetLineColor(kYellow + 1);
histQCD_7->SetLineColor(kYellow + 1);
histQCD_8->SetLineColor(kYellow + 1);
histQCD_9->SetLineColor(kYellow + 1);

float totQCD = histQCD_1->Integral() + histQCD_2->Integral() + histQCD_3->Integral() + histQCD_4->Integral() + histQCD_5->Integral() + histQCD_6->Integral() + histQCD_7->Integral() + histQCD_8->Integral() + histQCD_9->Integral();
float totDATA = histDATA->Integral() - histTT->Integral() - histWj->Integral() - histZj->Integral();

cout << histQCD_1->Integral() << endl;
cout << histQCD_2->Integral() << endl;
cout << histQCD_3->Integral() << endl;
cout << histQCD_4->Integral() << endl;
cout << histQCD_5->Integral() << endl;
cout << histQCD_6->Integral() << endl;
cout << histQCD_7->Integral() << endl;
cout << histQCD_8->Integral() << endl;
cout << histQCD_9->Integral() << endl;
cout << "Scaling QCD by: " << totDATA/totQCD << endl;

histQCD_1->Scale(totDATA / totQCD);
histQCD_2->Scale(totDATA / totQCD);
histQCD_3->Scale(totDATA / totQCD);
histQCD_4->Scale(totDATA / totQCD);
histQCD_5->Scale(totDATA / totQCD);
histQCD_6->Scale(totDATA / totQCD);
histQCD_7->Scale(totDATA / totQCD);
histQCD_8->Scale(totDATA / totQCD);
histQCD_9->Scale(totDATA / totQCD);



histDATA->SetMarkerStyle(21);
histDATA->SetMarkerSize(0.8);

THStack *stack = new THStack("stack", "stack");

stack->Add(histZj);
stack->Add(histWj);
stack->Add(histTT);
stack->Add(histQCD_1);
stack->Add(histQCD_2);
stack->Add(histQCD_3);
stack->Add(histQCD_4);
stack->Add(histQCD_5);
stack->Add(histQCD_6);
stack->Add(histQCD_7);
stack->Add(histQCD_8);
stack->Add(histQCD_9);

histDATA->Draw("E");

histDATA->SetMaximum( 4 * histDATA->GetMaximum() );
histDATA->SetMinimum( 0.0001 );
histDATA->GetXaxis()->SetTitle( label.c_str() );
stack->Draw("hist same");
histDATA->Draw("E same");
hist_sigW->Draw("same");
hist_sigZ->Draw("same");
hist_sigH->Draw("same");
hist_sigT->Draw("same");


gPad->RedrawAxis();

TH1F *totalH = (TH1F *) histQCD_1->Clone("totalH");
totalH->Add(histQCD_2);
totalH->Add(histQCD_3);
totalH->Add(histQCD_4);
totalH->Add(histQCD_5);
totalH->Add(histQCD_6);
totalH->Add(histQCD_7);
totalH->Add(histQCD_8);
totalH->Add(histQCD_9);
totalH->Add(histZj);
totalH->Add(histWj);
totalH->Add(histTT);

TH1F *hist_totQCD = (TH1F *) histQCD_1->Clone("hist_totQCD");
hist_totQCD->Add(histQCD_2);
hist_totQCD->Add(histQCD_3);
hist_totQCD->Add(histQCD_4);
hist_totQCD->Add(histQCD_5);
hist_totQCD->Add(histQCD_6);
hist_totQCD->Add(histQCD_7);
hist_totQCD->Add(histQCD_8);
hist_totQCD->Add(histQCD_9);


TH1F *ratioH = new TH1F();
ratioH = (TH1F*) histDATA->Clone("ratio");
ratioH->Sumw2();
ratioH->Divide(ratioH, totalH, 1, 1, "B");


TLegend *leg = new TLegend(0.15,0.70,0.92,0.86,"");
leg->SetNColumns(1);
leg->SetFillColor(0);
leg->SetLineColor(0);
leg->AddEntry(histDATA, "Data", "p");
leg->AddEntry(histQCD_1   ,  Form("QCD (x%f)", totDATA/totQCD),"f");
leg->AddEntry(histTT     , "t#bar{t}+jets" ,"f");
leg->AddEntry(histWj    , "W+jets","f");
leg->AddEntry(histZj      , "Z+jets","f");
leg->AddEntry(hist_sigW, "Boosted W", "l");
leg->AddEntry(hist_sigZ, "Boosted Z", "l");
leg->AddEntry(hist_sigH, "Boosted H", "l");
leg->AddEntry(hist_sigT, "Boosted t", "l");

leg->SetNColumns(4);

leg->Draw("same");

CMS_lumi(c1_2, 4, 0);



c1_1->cd();
c1_1->SetTopMargin(0.05);
        c1_1->SetBottomMargin(0.3);
        c1_1->SetRightMargin(0.05);
        c1_1->SetLeftMargin(0.1);
        c1_1->SetFillStyle(0);
ratioH->GetYaxis()->SetRangeUser(0.,2.);
        ratioH->GetYaxis()->SetTitle("Data / BG Ratio");
        ratioH->GetYaxis()->SetTitleOffset(0.4);
        ratioH->GetYaxis()->SetTitleSize(0.11);
        ratioH->GetYaxis()->SetLabelSize(0.11);
        ratioH->GetXaxis()->SetLabelSize(0.11);
        ratioH->GetXaxis()->SetTitleSize(0.11);
ratioH->GetYaxis()->SetNdivisions(4, kFALSE);
ratioH->Draw("E");

TF1 *line = new TF1("line", "1", 0, 5000);
        line->SetLineColor(kBlack);
	line->SetLineWidth(1);
        line->Draw("same");
        
        gPad->RedrawAxis();

c1_2->cd();


c1->SaveAs( Form( "plots/%s_fourD.pdf", var.c_str() ) );

gPad->SetLogy(1);

histDATA->SetMaximum( 1000000 * histDATA->GetMaximum() );
c1_2->Update();
c1->SaveAs( Form( "plots/%s_log_fourD.pdf", var.c_str() ) );

//TCanvas *c2 = new TCanvas("c2", "c2");
//c2->cd();
//drawROC(hist_sigT, hist_totQCD, 1, totNumTT, totNumQCD);

TFile *outFile = new TFile("out_histos.root", "RECREATE");
outFile->cd();

hist_totQCD->Write();
histTT->Write();
outFile->Close();


return;

}


void drawROC( TH1F *histS, TH1F *histB, int color, float noCutTT, float noCutQCD){


TGraph *rocG = new TGraph();

float sEntries = 0.0;
float bEntries = 0.0;

int n =0;

cout << "tt: " << histS->GetEntries() << "  " << noCutTT << endl;
cout << "qcd: " << histB->GetEntries() << " " << noCutQCD << endl;


for (int i = 0; i < histS->GetNbinsX(); i++){

	
	sEntries = (float(histS->GetEntries()) / noCutTT) * histS->Integral(0, i) / histS->Integral();
	bEntries = (float(histB->GetEntries()) / noCutQCD) * histB->Integral(0, i) / histB->Integral();

	cout << sEntries << "   " << bEntries << endl;

	rocG->SetPoint(++n, sEntries, bEntries);

}


TH2F *axisH = new TH2F("axisH", "axisH", 10000, 0, 1, 10000, 0, 1);
axisH->GetXaxis()->SetTitle( Form("%s Efficiency", histS->GetName() ) );
axisH->GetYaxis()->SetTitle( Form("%s Efficiency", histB->GetName() ) );
axisH->Draw("axis");

rocG->Draw("same");
rocG->SetLineWidth(2);
rocG->SetLineColor(color);
gPad->SetLogy(1);

return;

}


