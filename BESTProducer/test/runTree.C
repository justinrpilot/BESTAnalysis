#include <cstdlib>
#include <iostream>
#include <map>
#include <string>


#include "TMVA/Reader.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TMVA/Tools.h"

void runTree(string inFile, string outFile, string histName, float targX, float targY, float targ3, float targ4, float targ5, bool reduce = 1) {


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
   listOfVars.push_back("target3");
   listOfVars.push_back("target4");
   listOfVars.push_back("target5");
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
   listOfVars.push_back("tau32");
   listOfVars.push_back("tau21");
   listOfVars.push_back("et1_jet");
   listOfVars.push_back("et2_jet");
   listOfVars.push_back("et3_jet");
   listOfVars.push_back("et4_jet");
   listOfVars.push_back("m12_jet");
   listOfVars.push_back("m13_jet");
   listOfVars.push_back("m23_jet");
   listOfVars.push_back("m1234_jet");
   listOfVars.push_back("et1_W");
   listOfVars.push_back("et2_W");
   listOfVars.push_back("et3_W");
   listOfVars.push_back("et4_W");
   listOfVars.push_back("m12_W");
   listOfVars.push_back("m13_W");
   listOfVars.push_back("m23_W");
   listOfVars.push_back("m1234_W");
   listOfVars.push_back("et1_Z");
   listOfVars.push_back("et2_Z");
   listOfVars.push_back("et3_Z");
   listOfVars.push_back("et4_Z");
   listOfVars.push_back("m12_Z");
   listOfVars.push_back("m13_Z");
   listOfVars.push_back("m23_Z");
   listOfVars.push_back("m1234_Z");
   listOfVars.push_back("et1_top");
   listOfVars.push_back("et2_top");
   listOfVars.push_back("et3_top");
   listOfVars.push_back("et4_top");
   listOfVars.push_back("m12_top");
   listOfVars.push_back("m13_top");
   listOfVars.push_back("m23_top");
   listOfVars.push_back("m1234_top");
   listOfVars.push_back("et1_H");
   listOfVars.push_back("et2_H");
   listOfVars.push_back("et3_H");
   listOfVars.push_back("et4_H");
   listOfVars.push_back("m12_H");
   listOfVars.push_back("m13_H");
   listOfVars.push_back("m23_H");
   listOfVars.push_back("m1234_H");
 
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
   treeVars["NNoutQCD"] = -999.999;
   treeVars["NNout5"] = -999.999;

   TFile *newFile = new TFile(outFile.c_str(), "RECREATE");
	TTree *newTree = origFiles->CloneTree(0); 

   if (doWeight) newTree->Branch( "flatten", &(treeVars[ "flatten" ]), "flatten/F"); 
   newTree->Branch("target3", &(treeVars["target3"]), "target3/F");
   newTree->Branch("target4", &(treeVars["target4"]), "target4/F");
   newTree->Branch("target5", &(treeVars["target5"]), "target5/F");
   newTree->Branch("NNout3", &(treeVars["NNout3"]), "NNout3/F");
   newTree->Branch("NNout4", &(treeVars["NNout4"]), "NNout4/F");
   newTree->Branch("NNout5", &(treeVars["NNout5"]), "NNout5/F");
   newTree->Branch("NNoutQCD", &(treeVars["NNoutQCD"]), "NNoutQCD/F");

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
   reader->AddVariable( "et1_top", &treeVars["et1_top"]);
   reader->AddVariable( "et2_top", &treeVars["et2_top"]);
   reader->AddVariable( "et3_top", &treeVars["et3_top"]);
   reader->AddVariable( "et4_top", &treeVars["et4_top"]);
   reader->AddVariable( "et1_W", &treeVars["et1_W"]);
   reader->AddVariable( "et2_W", &treeVars["et2_W"]);
   reader->AddVariable( "et3_W", &treeVars["et3_W"]);
   reader->AddVariable( "et4_W", &treeVars["et4_W"]);
   reader->AddVariable( "et1_Z", &treeVars["et1_Z"]);
   reader->AddVariable( "et2_Z", &treeVars["et2_Z"]);
   reader->AddVariable( "et3_Z", &treeVars["et3_Z"]);
   reader->AddVariable( "et4_Z", &treeVars["et4_Z"]);
   reader->AddVariable( "et1_H", &treeVars["et1_H"]);
   reader->AddVariable( "et2_H", &treeVars["et2_H"]);
   reader->AddVariable( "et3_H", &treeVars["et3_H"]);
   reader->AddVariable( "et4_H", &treeVars["et4_H"]);
   reader->AddVariable( "m12_H", &treeVars["m12_H"]);
   reader->AddVariable( "m23_H", &treeVars["m23_H"]);
   reader->AddVariable( "m13_H", &treeVars["m13_H"]);
   reader->AddVariable( "m1234_H", &treeVars["m1234_H"]);
   reader->AddVariable( "m12_W", &treeVars["m12_W"]);
   reader->AddVariable( "m23_W", &treeVars["m23_W"]);
   reader->AddVariable( "m13_W", &treeVars["m13_W"]);
   reader->AddVariable( "m1234_W", &treeVars["m1234_W"]);
   reader->AddVariable( "m12_Z", &treeVars["m12_Z"]);
   reader->AddVariable( "m23_Z", &treeVars["m23_Z"]);
   reader->AddVariable( "m13_Z", &treeVars["m13_Z"]);
   reader->AddVariable( "m1234_Z", &treeVars["m1234_Z"]);
   reader->AddVariable( "m12_top", &treeVars["m12_top"]);
   reader->AddVariable( "m23_top", &treeVars["m23_top"]);
   reader->AddVariable( "m13_top", &treeVars["m13_top"]);
   reader->AddVariable( "m1234_top", &treeVars["m1234_top"]);
   reader->AddVariable( "bDisc", &treeVars["bDisc"]);
   reader->AddVariable( "q", &treeVars["q"]);


   reader->BookMVA( "fourD", "weights/TMVARegression_MLP.weights.xml");
   //reader->BookMVA("top", "weights/TMVAClassification_MLPBFGS.weights.xml");
   //reader->BookMVA("W", "weights/TMVAClassification_W_MLPBFGS.weights.xml");
   //reader->BookMVA("Z", "weights/TMVAClassification_Z_MLPBFGS.weights.xml");
   //reader->BookMVA("H", "weights/TMVAClassification_H_MLPBFGS.weights.xml");
   //reader->BookMVA("j", "weights/TMVAClassification_j_MLPBFGS.weights.xml");

   TFile *weightFile = new TFile(histName.c_str(), "READ");
   TH1F *weightH = (TH1F *) weightFile->Get("weightH");


   int nEvents = origFiles->GetEntries("et > 500");
   float desiredEvents = 50000.0;
   TRandom* random1 = new TRandom;
for (int i = 0; i < origFiles->GetEntries(); i++){
	
	if  (i % 10000 == 0) cout << 100*(float(i) / float(nEntries)) << " Percent Complete." << endl;
	double rand = random1->Rndm();
	if (rand > (desiredEvents / float(nEvents))) continue;
		origFiles->GetEntry(i);
		cout.precision(3);


	//if (treeVars["et"] < 600.0 || treeVars["et"] > 3000.0 || treeVars["SDmass"] < 50.0) continue;	
	if (treeVars["et"] < 500.0) continue;
	if (abs(treeVars["eta"]) > 2.4) continue;
	//if (treeVars["SDmass"] < 10.0) continue;

	float NNout1 = 0;//(reader->EvaluateRegression( "top" ))[0];
	float NNout2 = 0;//(reader->EvaluateRegression( "W" ))[0];
	float NNout3 = 0;//(reader->EvaluateRegression( "Z" ))[0];
	float NNout4 = 0;//(reader->EvaluateRegression( "H" ))[0];
	float NNout5 = 0;//(reader->EvaluateRegression( "H" ))[0];
	float NNoutQCD = 0;//(reader->EvaluateRegression( "j" ))[0];

	treeVars["targetX"] = targX;
	treeVars["targetY"] = targY;
	treeVars["target3"] = targ3;
	treeVars["target4"] = targ4;
	treeVars["target5"] = targ5;


	treeVars["PzOverP_top"] = treeVars["sumPz_top"] / (treeVars["sumP_top"] + 0.00001);
	treeVars["PzOverP_W"] = treeVars["sumPz_W"] / (treeVars["sumP_W"] + 0.00001);
	treeVars["PzOverP_Z"] = treeVars["sumPz_Z"] / (treeVars["sumP_Z"] + 0.00001);
	treeVars["PzOverP_H"] = treeVars["sumPz_H"] / (treeVars["sumP_H"] + 0.00001);

	float NNout4d_1 = (reader->EvaluateRegression( "fourD"))[0];
	float NNout4d_2 = (reader->EvaluateRegression("fourD"))[1];
	float NNout4d_3 = (reader->EvaluateRegression("fourD"))[2];
	float NNout4d_4 = (reader->EvaluateRegression("fourD"))[3];
	float NNout4d_5 = (reader->EvaluateRegression("fourD"))[4];

	//cout << NNout1 << " " << NNout2 << " " << NNout3 << " " << NNout4 << endl;
	//cout << NNout4d_1 << " " << NNout4d_2 << " " << NNout4d_3 << " " << NNout4d_4 << endl;
	
	NNout1 = NNout4d_1;
	NNout2 = NNout4d_2;
	NNout3 = NNout4d_3;
	NNout4 = NNout4d_4;
	NNout5 = NNout4d_5;

	treeVars["NNoutX"] = NNout1;
	treeVars["NNoutY"] = NNout2;
	treeVars["NNout3"] = NNout3;
	treeVars["NNout4"] = NNout4;
	treeVars["NNout5"] = NNout5;
	treeVars["NNoutQCD"] = NNoutQCD;



	float distTo1 = sqrt( (NNout1 - 1.0)*(NNout1 - 1.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 0.0) * (NNout4 - 0.0) + (NNout5 - 0.0)*(NNout5 - 0.0) ) ;
	float distTo2 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 1.0) * (NNout2 - 1.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 0.0) * (NNout4 - 0.0) + (NNout5 - 0.0)*(NNout5 - 0.0)  ) ;
	float distTo3 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 1.0) * (NNout3 - 1.0) + (NNout4 - 0.0) * (NNout4 - 0.0) + (NNout5 - 0.0)*(NNout5 - 0.0)  ) ;
	float distTo4 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 1.0) * (NNout4 - 1.0) + (NNout5 - 0.0)*(NNout5 - 0.0)  ) ;
	float distTo0 = sqrt( (NNout1 - 0.0)*(NNout1 - 0.0) + (NNout2 - 0.0) * (NNout2 - 0.0) + (NNout3 - 0.0) * (NNout3 - 0.0) + (NNout4 - 0.0) * (NNout4 - 0.0) + (NNout5 - 1.0)*(NNout5 - 1.0)  ) ;

	treeVars["distTo1"] = distTo1;
	treeVars["distTo2"] = distTo2;
	treeVars["distTo3"] = distTo3;
	treeVars["distTo4"] = distTo4;
	treeVars["distTo0"] = distTo0;

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
