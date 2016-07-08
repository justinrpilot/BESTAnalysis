/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVARegressionApplication                                          *
 *                                                                                *
 * This macro provides a simple example on how to use the trained regression MVAs *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif

using namespace TMVA;

void TMVARegressionApplication( TString myMethodList = "" ) 
{
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDEFoam"]         = 0; 
   Use["KNN"]             = 0;
   // 
   // --- Linear Discriminant Analysis
   Use["LD"]		        = 0;
   // 
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   // 
   // --- Neural Network
   Use["MLP"]             = 1; 
   // 
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 0;
   Use["BDTG"]            = 0;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVARegressionApplication" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t h1_top;
   Float_t h2_top;
   Float_t h3_top;
   Float_t h4_top;
   reader->AddVariable( "h1_top", &h1_top );
   reader->AddVariable( "h2_top", &h2_top );
   reader->AddVariable( "h3_top", &h3_top );
   reader->AddVariable( "h4_top", &h4_top );
   Float_t h1_W;
   Float_t h2_W;
   Float_t h3_W;
   Float_t h4_W;
   reader->AddVariable( "h1_W", &h1_W );
   reader->AddVariable( "h2_W", &h2_W );
   reader->AddVariable( "h3_W", &h3_W );
   reader->AddVariable( "h4_W", &h4_W );
   Float_t h1_Z;
   Float_t h2_Z;
   Float_t h3_Z;
   Float_t h4_Z;
   reader->AddVariable( "h1_Z", &h1_Z );
   reader->AddVariable( "h2_Z", &h2_Z );
   reader->AddVariable( "h3_Z", &h3_Z );
   reader->AddVariable( "h4_Z", &h4_Z );
   Float_t h1_H;
   Float_t h2_H;
   Float_t h3_H;
   Float_t h4_H;
   reader->AddVariable( "h1_H", &h1_H );
   reader->AddVariable( "h2_H", &h2_H );
   reader->AddVariable( "h3_H", &h3_H );
   reader->AddVariable( "h4_H", &h4_H );

   // Spectator variables declared in the training have to be added to the reader, too
   Float_t targetX, targetY;
   reader->AddSpectator( "targetX",  &targetX );
   reader->AddSpectator( "targetY",  &targetY );

   // --- Book the MVA methods

   TString dir    = "weights/";
   TString prefix = "TMVARegression";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = it->first + " method";
         TString weightfile = dir + prefix + "_" + TString(it->first) + ".weights.xml";
         cout << methodName << " IS THE METHOD NAME " << endl;
   	 reader->BookMVA( methodName, weightfile ); 
      }
   }
   
   // Book output histograms
   TH1* hists[100];
   Int_t nhists = -1;
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      TH1* h = new TH1F( it->first.c_str(), TString(it->first) + " method", 150, -0.5, 1.5 );
      if (it->second) hists[++nhists] = h;
   }
   nhists++;
   
   TH1* hX = new TH1F( "outputX", "outputX", 150, -0.5, 1.5 );
   TH1* hY = new TH1F( "outputY", "outputY", 150, -0.5, 1.5 );
   TH2* hXY = new TH2F( "outputXY", "outputXY", 150, -0.5, 1.5, 150, -0.5, 1.5 );
   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   TFile *input(0);
   TString fname = "histo_ZZ.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   } 
   else { 
      input = TFile::Open( "http://root.cern.ch/files/tmva_reg_example.root" ); // if not: download from ROOT server
   }
   
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegressionApp        : Using input file: " << input->GetName() << std::endl;

   // --- Event loop

   // Prepare the tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   TTree* theTree = (TTree*)input->Get("run/jetTree");
   std::cout << "--- Select signal sample" << std::endl;
   theTree->SetBranchAddress( "h1_top", &h1_top );
   theTree->SetBranchAddress( "h2_top", &h2_top );
   theTree->SetBranchAddress( "h3_top", &h3_top );
   theTree->SetBranchAddress( "h4_top", &h4_top );
   theTree->SetBranchAddress( "h1_W", &h1_W );
   theTree->SetBranchAddress( "h2_W", &h2_W );
   theTree->SetBranchAddress( "h3_W", &h3_W );
   theTree->SetBranchAddress( "h4_W", &h4_W );
   theTree->SetBranchAddress( "h1_Z", &h1_Z );
   theTree->SetBranchAddress( "h2_Z", &h2_Z );
   theTree->SetBranchAddress( "h3_Z", &h3_Z );
   theTree->SetBranchAddress( "h4_Z", &h4_Z );
   theTree->SetBranchAddress( "h1_H", &h1_H );
   theTree->SetBranchAddress( "h2_H", &h2_H );
   theTree->SetBranchAddress( "h3_H", &h3_H );
   theTree->SetBranchAddress( "h4_H", &h4_H );

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }

      theTree->GetEntry(ievt);

      // Retrieve the MVA target values (regression outputs) and fill into histograms
      // NOTE: EvaluateRegression(..) returns a vector for multi-target regression

      for (Int_t ih=0; ih<nhists; ih++) {
         TString title = hists[ih]->GetTitle();
   
	 cout <<" TITLE IS " << title << endl;
         Float_t valX = (reader->EvaluateRegression( title ))[0];
         Float_t valY = (reader->EvaluateRegression( title ))[1];
      	 hX->Fill(valX);
	 hY->Fill(valY);
	 hXY->Fill(valX, valY);

      }
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   // --- Write histograms

   TFile *target  = new TFile( "TMVARegApp.root","RECREATE" );
   for (Int_t ih=0; ih<nhists; ih++) hists[ih]->Write();
   hX->Write();
   hY->Write();
   hXY->Write();
   target->Close();

   std::cout << "--- Created root file: \"" << target->GetName() 
             << "\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;
}
