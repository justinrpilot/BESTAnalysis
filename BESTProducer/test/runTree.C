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
 
   for (unsigned i = 0; i < listOfVars.size(); i++){

	treeVars[ listOfVars[i] ] = -999.999;
        origFiles->SetBranchAddress( (listOfVars[i]).c_str() , &(treeVars[ listOfVars[i] ]) );

   }
   

   treeVars["flatten"] = -999.999;
   treeVars["PzOverP_top"] = -999.999;
   treeVars["PzOverP_W"] = -999.999;
   treeVars["PzOverP_Z"] = -999.999;
   treeVars["PzOverP_H"] = -999.999;


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

   reader->BookMVA( "MLP method", "TMVARegression_MLP.weights.xml");

   TFile *weightFile = new TFile(histName.c_str(), "READ");
   TH1F *weightH = (TH1F *) weightFile->Get("weightH");


   int nEvents = origFiles->GetEntries("et > 500.0 && et < 3000.0");
   float desiredEvents = 20000.0;
   TRandom* random1 = new TRandom;
for (int i = 0; i < origFiles->GetEntries(); i++){
	
	double rand = random1->Rndm();
		origFiles->GetEntry(i);
		cout.precision(3);
		if  (i % 100000 == 0) cout << 100*(float(i) / float(nEntries)) << " Percent Complete." << endl;


	if (treeVars["et"] < 600.0 || treeVars["et"] > 3000.0) continue;	
	if (reduce && rand > (desiredEvents / float(nEvents))) continue;

	treeVars["NNoutX"] = (reader->EvaluateRegression( "MLP method" ))[0];
	treeVars["NNoutY"] = (reader->EvaluateRegression( "MLP method" ))[1];
	treeVars["NNout3"] = (reader->EvaluateRegression( "MLP method" ))[2];
	treeVars["NNout4"] = (reader->EvaluateRegression( "MLP method" ))[3];

	treeVars["targetX"] = targX;
	treeVars["targetY"] = targY;
	treeVars["target3"] = targ3;
	treeVars["target4"] = targ4;


	treeVars["PzOverP_top"] = treeVars["sumPz_top"] / (treeVars["sumP_top"] + 0.00001);
	treeVars["PzOverP_W"] = treeVars["sumPz_W"] / (treeVars["sumP_W"] + 0.00001);
	treeVars["PzOverP_Z"] = treeVars["sumPz_Z"] / (treeVars["sumP_Z"] + 0.00001);
	treeVars["PzOverP_H"] = treeVars["sumPz_H"] / (treeVars["sumP_H"] + 0.00001);



	if (doWeight)	treeVars["flatten"] = weightH->GetBinContent(weightH->FindBin( treeVars["et"] ));


	newTree->Fill();

	}

	newFile->cd();
	newTree->Write();
	newFile->Write();
	newFile->Close();


}
