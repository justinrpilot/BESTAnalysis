#include <cstdlib>
#include <iostream>
#include <map>
#include <string>


#include "TMVA/Reader.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TMVA/Tools.h"

void runTree(string inFile, string outFile, string histName, float targX, float targY, float targ3, float targ4, bool reduce = 1) {


	TChain *origFiles = new TChain("run/jetTree", "jetTree");
	origFiles->Add(inFile.c_str());
	
	int nEntries = origFiles->GetEntries();
	cout << "The old chain contains " << nEntries << " entries." << endl;

	bool doWeight = false;
	if (histName != "") doWeight = true;

	
	std::vector<std::string> listOfVars;
      std::map<std::string, float> treeVars;
   listOfVars.push_back("et"); 
   listOfVars.push_back("eta"); 
   listOfVars.push_back("mass");
   listOfVars.push_back("SDmass");
   listOfVars.push_back("tau32");
   listOfVars.push_back("tau21");
   listOfVars.push_back("h1_top"); 
   listOfVars.push_back("h2_top"); 
   listOfVars.push_back("h3_top"); 
   listOfVars.push_back("h4_top"); 
   listOfVars.push_back("isotropy_top"); 
   listOfVars.push_back("aplanarity_top"); 
   listOfVars.push_back("sphericity_top"); 
   listOfVars.push_back("thrust_top"); 
   listOfVars.push_back("h1_W"); 
   listOfVars.push_back("h2_W"); 
   listOfVars.push_back("h3_W"); 
   listOfVars.push_back("h4_W"); 
   listOfVars.push_back("isotropy_W"); 
   listOfVars.push_back("aplanarity_W"); 
   listOfVars.push_back("sphericity_W"); 
   listOfVars.push_back("thrust_W"); 
   listOfVars.push_back("h1_Z"); 
   listOfVars.push_back("h2_Z"); 
   listOfVars.push_back("h3_Z"); 
   listOfVars.push_back("h4_Z"); 
   listOfVars.push_back("isotropy_Z"); 
   listOfVars.push_back("aplanarity_Z"); 
   listOfVars.push_back("sphericity_Z"); 
   listOfVars.push_back("thrust_Z"); 
   listOfVars.push_back("h1_H"); 
   listOfVars.push_back("h2_H"); 
   listOfVars.push_back("h3_H"); 
   listOfVars.push_back("h4_H"); 
   listOfVars.push_back("isotropy_H"); 
   listOfVars.push_back("aplanarity_H"); 
   listOfVars.push_back("sphericity_H"); 
   listOfVars.push_back("thrust_H"); 
   listOfVars.push_back("targetX");
   listOfVars.push_back("targetY");
   listOfVars.push_back("NNoutX");
   listOfVars.push_back("NNoutY");
   listOfVars.push_back("Njets_top");
   listOfVars.push_back("Njets_W");
   listOfVars.push_back("Njets_Z");
   listOfVars.push_back("Njets_H");
   listOfVars.push_back("Njets_jet");
   listOfVars.push_back("Njets_orig");
   listOfVars.push_back("sumPz_top");
   listOfVars.push_back("sumPz_W");
   listOfVars.push_back("sumPz_Z");
   listOfVars.push_back("sumPz_H");
   listOfVars.push_back("sumP_top");
   listOfVars.push_back("sumP_W");
   listOfVars.push_back("sumP_Z");
   listOfVars.push_back("sumP_H");
   listOfVars.push_back("targetX");
   listOfVars.push_back("targetY");
   listOfVars.push_back("tau32");
   listOfVars.push_back("tau21");
 
   for (unsigned i = 0; i < listOfVars.size(); i++){

	treeVars[ listOfVars[i] ] = -999.999;
        origFiles->SetBranchAddress( (listOfVars[i]).c_str() , &(treeVars[ listOfVars[i] ]) );

   }
   

   treeVars["flatten"] = -999.999;
   treeVars["PzOverP_top"] = -999.999;
   treeVars["PzOverP_W"] = -999.999;
   treeVars["PzOverP_Z"] = -999.999;
   treeVars["PzOverP_H"] = -999.999;
   treeVars["sorting"] = -999.999;
   treeVars["distTo0"] = -999.999;
   treeVars["distTo1"] = -999.999;
   treeVars["distTo2"] = -999.999;
   treeVars["distTo3"] = -999.999;
   treeVars["distTo4"] = -999.999;
   treeVars["minDist"] = -999.999;

   TFile *newFile = new TFile(outFile.c_str(), "RECREATE");
	TTree *newTree = origFiles->CloneTree(0); 

   if (doWeight) newTree->Branch( "flatten", &(treeVars[ "flatten" ]), "flatten/F"); 
   newTree->Branch("target3", &(treeVars["target3"]), "target3/F");
   newTree->Branch("target4", &(treeVars["target4"]), "target4/F");
   newTree->Branch("NNout3", &(treeVars["NNout3"]), "NNout3/F");
   newTree->Branch("NNout4", &(treeVars["NNout4"]), "NNout4/F");

   newTree->Branch("PzOverP_top", &(treeVars["PzOverP_top"]), "PzOverP_top/F");
   newTree->Branch("PzOverP_W", &(treeVars["PzOverP_W"]), "PzOverP_W/F");
   newTree->Branch("PzOverP_Z", &(treeVars["PzOverP_Z"]), "PzOverP_Z/F");
   newTree->Branch("PzOverP_H", &(treeVars["PzOverP_H"]), "PzOverP_H/F");

   newTree->Branch("sorting", &(treeVars["sorting"]), "sorting/F");
   newTree->Branch("minDist", &(treeVars["minDist"]), "minDist/F");
   newTree->Branch("distTo0", &(treeVars["distTo0"]), "distTo0/F");
   newTree->Branch("distTo1", &(treeVars["distTo1"]), "distTo1/F");
   newTree->Branch("distTo2", &(treeVars["distTo2"]), "distTo2/F");
   newTree->Branch("distTo3", &(treeVars["distTo3"]), "distTo3/F");
   newTree->Branch("distTo4", &(treeVars["distTo4"]), "distTo4/F");


   TMVA::Reader *reader = new TMVA::Reader();
   //For NN inputs
   reader->AddVariable( "h1_top", &treeVars[ "h1_top" ] );
   reader->AddVariable( "h2_top", &treeVars[ "h2_top" ] );
   reader->AddVariable( "h3_top", &treeVars[ "h3_top" ] );
   reader->AddVariable( "h4_top", &treeVars[ "h4_top" ] );	
   reader->AddVariable( "h1_W", &treeVars[ "h1_W" ] );
   reader->AddVariable( "h2_W", &treeVars[ "h2_W" ] );
   reader->AddVariable( "h3_W", &treeVars[ "h3_W" ] );
   reader->AddVariable( "h4_W", &treeVars[ "h4_W" ] );	
   reader->AddVariable( "h1_Z", &treeVars[ "h1_Z" ] );
   reader->AddVariable( "h2_Z", &treeVars[ "h2_Z" ] );
   reader->AddVariable( "h3_Z", &treeVars[ "h3_Z" ] );
   reader->AddVariable( "h4_Z", &treeVars[ "h4_Z" ] );	
   reader->AddVariable( "h1_H", &treeVars[ "h1_H" ] );
   reader->AddVariable( "h2_H", &treeVars[ "h2_H" ] );
   reader->AddVariable( "h3_H", &treeVars[ "h3_H" ] );
   reader->AddVariable( "h4_H", &treeVars[ "h4_H" ] );	
   reader->AddVariable( "et", &treeVars["et"]);
   reader->AddVariable( "eta", &treeVars["eta"]);
   reader->AddVariable( "isotropy_H", &treeVars[ "isotropy_H" ] );	
   reader->AddVariable( "aplanarity_H", &treeVars[ "aplanarity_H" ] );	
   reader->AddVariable( "sphericity_H", &treeVars[ "sphericity_H" ] );	
   reader->AddVariable( "thrust_H", &treeVars[ "thrust_H" ] );	
   reader->AddVariable( "isotropy_top", &treeVars[ "isotropy_top" ] );	
   reader->AddVariable( "aplanarity_top", &treeVars[ "aplanarity_top" ] );	
   reader->AddVariable( "sphericity_top", &treeVars[ "sphericity_top" ] );	
   reader->AddVariable( "thrust_top", &treeVars[ "thrust_top" ] );	
   reader->AddVariable( "isotropy_W", &treeVars[ "isotropy_W" ] );	
   reader->AddVariable( "aplanarity_W", &treeVars[ "aplanarity_W" ] );	
   reader->AddVariable( "sphericity_W", &treeVars[ "sphericity_W" ] );	
   reader->AddVariable( "thrust_W", &treeVars[ "thrust_W" ] );	
   reader->AddVariable( "isotropy_Z", &treeVars[ "isotropy_Z" ] );	
   reader->AddVariable( "aplanarity_Z", &treeVars[ "aplanarity_Z" ] );	
   reader->AddVariable( "sphericity_Z", &treeVars[ "sphericity_Z" ] );	
   reader->AddVariable( "thrust_Z", &treeVars[ "thrust_Z" ] );	
   reader->AddVariable( "sumPz_top/sumP_top", &treeVars["PzOverP_top"] );
   reader->AddVariable( "sumPz_W/sumP_W", &treeVars["PzOverP_W"] );
   reader->AddVariable( "sumPz_Z/sumP_Z", &treeVars["PzOverP_Z"] );
   reader->AddVariable( "sumPz_H/sumP_H", &treeVars["PzOverP_H"] );
   reader->AddVariable( "tau32", &treeVars["tau32"] );
   reader->AddVariable( "tau21", &treeVars["tau21"] );
   reader->AddVariable( "SDmass", &treeVars["SDmass"]);

   reader->BookMVA( "fourD", "weights/TMVARegression_MLP.weights.xml");
   reader->BookMVA("top", "weights/TMVAClassification_MLPBFGS.weights.xml");
   reader->BookMVA("W", "weights/TMVAClassification_W_MLPBFGS.weights.xml");
   reader->BookMVA("Z", "weights/TMVAClassification_Z_MLPBFGS.weights.xml");
   reader->BookMVA("H", "weights/TMVAClassification_H_MLPBFGS.weights.xml");

   TFile *weightFile = new TFile(histName.c_str(), "READ");
   TH1F *weightH = (TH1F *) weightFile->Get("weightH");


   int nEvents = origFiles->GetEntries("et > 500.0 && et < 3000.0 && SDmass > 20.0");
   float desiredEvents = 100000.0;
   TRandom* random1 = new TRandom;
for (int i = 0; i < origFiles->GetEntries(); i++){
	
	double rand = random1->Rndm();
		origFiles->GetEntry(i);
		cout.precision(3);
		if  (i % 100000 == 0) cout << 100*(float(i) / float(nEntries)) << " Percent Complete." << endl;


	if (treeVars["et"] < 600.0 || treeVars["et"] > 3000.0 || treeVars["SDmass"] < 50.0) continue;	
	if (reduce && rand > (desiredEvents / float(nEvents))) continue;


	float NNout1 = (reader->EvaluateRegression( "top" ))[0];
	float NNout2 = (reader->EvaluateRegression( "W" ))[0];
	float NNout3 = (reader->EvaluateRegression( "Z" ))[0];
	float NNout4 = (reader->EvaluateRegression( "H" ))[0];

	float NNout4d_1 = (reader->EvaluateRegression( "fourD"))[0];
	float NNout4d_2 = (reader->EvaluateRegression( "fourD"))[1];
	float NNout4d_3 = (reader->EvaluateRegression( "fourD"))[2];
	float NNout4d_4 = (reader->EvaluateRegression( "fourD"))[3];

	cout << NNout4d_1 << " " << NNout4d_2 << " " << NNout4d_3 << " " << NNout4d_4 << endl;


	treeVars["NNoutX"] = NNout1;
	treeVars["NNoutY"] = NNout2;
	treeVars["NNout3"] = NNout3;
	treeVars["NNout4"] = NNout4;

	treeVars["targetX"] = targX;
	treeVars["targetY"] = targY;
	treeVars["target3"] = targ3;
	treeVars["target4"] = targ4;


	treeVars["PzOverP_top"] = treeVars["sumPz_top"] / (treeVars["sumP_top"] + 0.00001);
	treeVars["PzOverP_W"] = treeVars["sumPz_W"] / (treeVars["sumP_W"] + 0.00001);
	treeVars["PzOverP_Z"] = treeVars["sumPz_Z"] / (treeVars["sumP_Z"] + 0.00001);
	treeVars["PzOverP_H"] = treeVars["sumPz_H"] / (treeVars["sumP_H"] + 0.00001);



	float distTo1 = sqrt( (NNout1 - 1.0)*(NNout1 - 1.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 0.0) * (NNout4 - 0.0) ) ;
	float distTo2 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 1.0) * (NNout2 - 1.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 0.0) * (NNout4 - 0.0) ) ;
	float distTo3 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 1.0) * (NNout3 - 1.0) + (NNout4 - 0.0) * (NNout4 - 0.0) ) ;
	float distTo4 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 1.0) * (NNout4 - 1.0) ) ;
	float distTo0 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 0.0) * (NNout4 - 0.0) ) ;

	treeVars["distTo1"] = distTo1;
	treeVars["distTo2"] = distTo2;
	treeVars["distTo3"] = distTo3;
	treeVars["distTo4"] = distTo4;
	treeVars["distTo0"] = distTo4;

	if (treeVars["NNoutX"] < 0.5) {
		if (treeVars["NNoutY"] > 0.5) treeVars["sorting"] = 1.0;
		else if (treeVars["NNout3"] > 0.5) treeVars["sorting"] = 2.0;
		else if (treeVars["NNout4"] > 0.5) treeVars["sorting"] = 3.0;
		else treeVars["sorting"] = 0.0;
	}
	else treeVars["sorting"] = 4.0;


	std::vector<float> a{ distTo0, distTo1, distTo2, distTo3, distTo4};
	std::vector<float>::iterator result = std::min_element(std::begin(a), std::end(a));

	treeVars["minDist"] = std::distance(std::begin(a), result);



	if (doWeight)	treeVars["flatten"] = weightH->GetBinContent(weightH->FindBin( treeVars["et"] ));


	newTree->Fill();

	}

	newFile->cd();
	newTree->Write();
	newFile->Write();
	newFile->Close();


}
