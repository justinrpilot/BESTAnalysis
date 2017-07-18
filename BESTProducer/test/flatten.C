void flatten(TString infile, TString outWeightFile, float etMin = 500, float etMax = 4000){


	TFile *inF = TFile::Open(infile, "READ");



	TTree *inTree = (TTree *) inF->Get("run/jetTree");



	TH1F *origH = new TH1F("origH", "origH", 100, etMin, etMax);
	inTree->Draw("et>>origH", Form("et > %f && et < %f", etMin, etMax));


	TH1F *flatH = new TH1F("flatH", "flatH", 100, etMin, etMax);

	for (int i = 0; i < origH->GetNbinsX(); i++)  flatH->AddBinContent(i, 1);
	cout << origH->Integral() << endl;
	flatH->Scale( origH->Integral() / origH->GetNbinsX() );


	origH->Draw();
	flatH->Draw("same");

	TH1F *weightH = (TH1F *) flatH->Clone("weightH");
	TH1F *newH = (TH1F *) origH->Clone("newH");

	weightH->Divide(origH);


	weightH->Draw("same");



	newH->Multiply(weightH);



	newH->Draw("same");


	TFile *outF = new TFile(outWeightFile, "RECREATE");
	weightH->Write();

	outF->Write();
	outF->Close();






}






