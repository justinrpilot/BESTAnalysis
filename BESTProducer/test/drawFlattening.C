void drawFlatten(string inFile, string label){


	

	TFile *f = TFile::Open(inFile.c_str(), "READ");
	TTree *tree = (TTree *) f->Get("jetTree");

	TH1F *rawH = new TH1F("rawH", "rawH", 50, 0, 3000);
	TH1F *flatH = new TH1F("flatH", "flatH", 50, 0, 3000);


	TCanvas *c1 = new TCanvas();

	tree->Draw("et>>rawH");

	tree->Draw("et>>flatH", "flatten", "same");


	rawH->SetLineColor(kBlack);
	rawH->SetLineWidth(2);

	flatH->SetLineColor(kRed);
	flatH->SetLineWidth(2);


	rawH->Draw();
	flatH->Draw("E same");

	rawH->GetXaxis()->SetTitle("Jet p_{T}");
	rawH->GetYaxis()->SetTitle("Jets");

	TLegend *leg = new TLegend(0.65,0.75,0.89, 0.89);
	leg->AddEntry(rawH, "Original", "l");
	leg->AddEntry(flatH, "Flattened", "l");
	leg->AddEntry(flatH, label.c_str(), "");

	leg->SetLineWidth(0);
	leg->SetFillColor(0);
	leg->Draw("same");

	c1->SaveAs(Form("%s_flattened.pdf", label.c_str()));

		
}

