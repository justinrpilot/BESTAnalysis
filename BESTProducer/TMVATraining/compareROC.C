#include "../test/CMS_lumi.C"

void drawROC(TString particle="t"){

TFile *f1 = new TFile("TMVA_"+particle+"_tau32_SDmass.root");
TFile *f2 = new TFile("TMVA_"+particle+"_tau32_SDmass_btag.root");
TFile *f3 = new TFile("TMVA_"+particle+"_tau32_SDmass_btag_BEST.root");
TFile *f4 = new TFile("TMVA_"+particle+"_tau32_SDmass_btag_Dist.root");
TFile *f5 = new TFile("TMVA_"+particle+"_tau32_SDmass_btag_BEST5d.root");
TFile *f6 = new TFile("TMVA_"+particle+"_tau32_SDmass_btag_d.root");

TH1F *h1 = (TH1F *) f1->Get("Method_Cuts/Cuts/MVA_Cuts_effBvsS");
TH1F *h2 = (TH1F *) f2->Get("Method_Cuts/Cuts/MVA_Cuts_effBvsS");
TH1F *h3 = (TH1F *) f3->Get("Method_Cuts/Cuts/MVA_Cuts_effBvsS");
TH1F *h4 = (TH1F *) f4->Get("Method_Cuts/Cuts/MVA_Cuts_effBvsS");
TH1F *h5 = (TH1F *) f5->Get("Method_Cuts/Cuts/MVA_Cuts_effBvsS");
TH1F *h6 = (TH1F *) f6->Get("Method_Cuts/Cuts/MVA_Cuts_effBvsS");

h1->SetLineColor(1);
h2->SetLineColor(3);
h3->SetLineColor(3);
h4->SetLineColor(4);
h5->SetLineColor(4);
h6->SetLineColor(6);

h1->SetLineWidth(2);
h2->SetLineWidth(2);
h3->SetLineWidth(2);
h4->SetLineWidth(2);
h5->SetLineWidth(2);
h6->SetLineWidth(2);

h1->GetXaxis()->SetTitle(particle+" Jet Efficiency");
h1->GetYaxis()->SetTitle("Light Jet Efficiency");

TCanvas *c1 = new TCanvas();


h1->SetMinimum(0.00001);
h1->Draw();
h2->Draw("same");
//h3->Draw("same");
//h4->Draw("same");
h5->Draw("same");
h6->Draw("same");

TLegend *leg = new TLegend(0.36, 0.15, 0.88, 0.41);

TString nsub = "21";
if (particle == "t") nsub = "32";

leg->AddEntry(h1, "Jet p_{T} > 500 GeV, Jet m_{SD} > 50 GeV", "");
leg->AddEntry(h1, "#tau_{"+nsub+"} + SD Mass", "l");
leg->AddEntry(h2, "#tau_{"+nsub+"} + SD Mass + b-tag", "l");
leg->AddEntry(h5, "#tau_{"+nsub+"} + SD Mass + b-tag + 5D BEST NNs", "l");
leg->AddEntry(h6, "#tau_{"+nsub+"} + SD Mass + b-tag + d_{"+particle+"}", "l");
//leg->AddEntry(h3, "#tau_{"+nsub+"} + SD Mass + b-tag + 4D BEST NNs", "l");
//leg->AddEntry(h4, "#tau_{"+nsub+"} + SD Mass + b-tag + 4D BEST NNs + d_{"+particle+"}", "l");
leg->SetLineColor(0);leg->SetFillColor(0);
leg->Draw("same");

gPad->SetLogy(1);

CMS_lumi(c1, 4, 0);

gPad->SaveAs("roc_curve_"+particle+"_pt500_m50.pdf");

}
