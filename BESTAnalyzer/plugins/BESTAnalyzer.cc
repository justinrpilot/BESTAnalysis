// -*- C++ -*-
//
// Package:    Analysis/BESTAnalyzer
// Class:      BESTAnalyzer
// 
/**\class BESTAnalyzer BESTAnalyzer.cc Analysis/BESTAnalyzer/plugins/BESTAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  justin pilot
//         Created:  Tue, 04 Apr 2017 17:19:33 GMT
//
//


// system include files
#include <memory>
#include <iostream>
#include <vector>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TLorentzVector.h"
#include "TTree.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"

//
// class declaration
//

class BESTAnalyzer : public edm::stream::EDProducer<> {
   public:
      explicit BESTAnalyzer(const edm::ParameterSet&);
      ~BESTAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<std::vector<float> > fwm0Token_;
      edm::EDGetTokenT<std::vector<float> > fwm1Token_;
      edm::EDGetTokenT<std::vector<float> > fwm2Token_;
      edm::EDGetTokenT<std::vector<float> > fwm3Token_;
      edm::EDGetTokenT<std::vector<float> > fwm4Token_;

      edm::EDGetTokenT<std::vector<float> > sumPztopToken_;
      edm::EDGetTokenT<std::vector<float> > sumPzWToken_;
      edm::EDGetTokenT<std::vector<float> > sumPzZToken_;
      edm::EDGetTokenT<std::vector<float> > sumPzHToken_;
      edm::EDGetTokenT<std::vector<float> > sumPzjetToken_;
      edm::EDGetTokenT<std::vector<float> > sumPtopToken_;
      edm::EDGetTokenT<std::vector<float> > sumPWToken_;
      edm::EDGetTokenT<std::vector<float> > sumPZToken_;
      edm::EDGetTokenT<std::vector<float> > sumPHToken_;
      edm::EDGetTokenT<std::vector<float> > sumPjetToken_;

      edm::EDGetTokenT<std::vector<float> > NjetstopToken_;
      edm::EDGetTokenT<std::vector<float> > NjetsWToken_;
      edm::EDGetTokenT<std::vector<float> > NjetsZToken_;
      edm::EDGetTokenT<std::vector<float> > NjetsHToken_;
      edm::EDGetTokenT<std::vector<float> > NjetsjetToken_;

      edm::EDGetTokenT<std::vector<float> > FWmoment1topToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment2topToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment3topToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment4topToken_;
      edm::EDGetTokenT<std::vector<float> > isotropytopToken_;
      edm::EDGetTokenT<std::vector<float> > sphericitytopToken_;
      edm::EDGetTokenT<std::vector<float> > aplanaritytopToken_;
      edm::EDGetTokenT<std::vector<float> > thrusttopToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment1WToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment2WToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment3WToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment4WToken_;
      edm::EDGetTokenT<std::vector<float> > isotropyWToken_;
      edm::EDGetTokenT<std::vector<float> > sphericityWToken_;
      edm::EDGetTokenT<std::vector<float> > aplanarityWToken_;
      edm::EDGetTokenT<std::vector<float> > thrustWToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment1ZToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment2ZToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment3ZToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment4ZToken_;
      edm::EDGetTokenT<std::vector<float> > isotropyZToken_;
      edm::EDGetTokenT<std::vector<float> > sphericityZToken_;
      edm::EDGetTokenT<std::vector<float> > aplanarityZToken_;
      edm::EDGetTokenT<std::vector<float> > thrustZToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment1HToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment2HToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment3HToken_;
      edm::EDGetTokenT<std::vector<float> > FWmoment4HToken_;
      edm::EDGetTokenT<std::vector<float> > isotropyHToken_;
      edm::EDGetTokenT<std::vector<float> > sphericityHToken_;
      edm::EDGetTokenT<std::vector<float> > aplanarityHToken_;
      edm::EDGetTokenT<std::vector<float> > thrustHToken_;

      edm::EDGetTokenT<std::vector<float> > etToken_;
      edm::EDGetTokenT<std::vector<float> > etaToken_;
      edm::EDGetTokenT<std::vector<float> > massToken_;
      edm::EDGetTokenT<std::vector<float> > SDmassToken_;
      edm::EDGetTokenT<std::vector<float> > tau32Token_;
      edm::EDGetTokenT<std::vector<float> > tau21Token_;
      edm::EDGetTokenT<std::vector<float> > bDiscToken_;
      edm::EDGetTokenT<std::vector<int> > vertToken_;
      edm::EDGetTokenT<std::vector<int> > decayModeToken_;
      edm::EDGetTokenT<std::vector<int> > nak4JetsToken_; 

      edm::EDGetTokenT<std::vector<pat::Jet> > savedJetsToken_;

      TMVA::Reader *reader;
      std::vector<std::string> listOfVars;
      
      std::map<std::string, Float_t> treeVars;

	TTree *eventTree;

	std::vector<std::string> listOfEventVars;
	std::map<std::string, float> eventVars;
   std::vector<float> NNout1vals;
   std::vector<float> NNout2vals;
   std::vector<float> NNout3vals;
   std::vector<float> NNout4vals;
   std::vector<float> NNout5vals;
   std::vector<float> etvals;
   std::vector<float> etavals;
   std::vector<float> phivals;
   std::vector<float> massvals;
   std::vector<float> sdmassvals;
   std::vector<int> decayModevals;

};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
BESTAnalyzer::BESTAnalyzer(const edm::ParameterSet& iConfig)
{
   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
edm::Service<TFileService> fs;   

edm::InputTag    fwm0Tag_ = edm::InputTag("BESTProducer", "FWmoment0", "run");
edm::InputTag    fwm1Tag_ = edm::InputTag("BESTProducer", "FWmoment1", "run");
edm::InputTag    fwm2Tag_ = edm::InputTag("BESTProducer", "FWmoment2", "run");
edm::InputTag    fwm3Tag_ = edm::InputTag("BESTProducer", "FWmoment3", "run");
edm::InputTag    fwm4Tag_ = edm::InputTag("BESTProducer", "FWmoment4", "run");
edm::InputTag    sumPztopTag_ = edm::InputTag("BESTProducer", "sumPztop", "run");
edm::InputTag    sumPzWTag_ = edm::InputTag("BESTProducer", "sumPzW", "run");
edm::InputTag    sumPzZTag_ = edm::InputTag("BESTProducer", "sumPzZ", "run");
edm::InputTag    sumPzHTag_ = edm::InputTag("BESTProducer", "sumPzH", "run");
edm::InputTag    sumPzjetTag_ = edm::InputTag("BESTProducer", "sumPzjet", "run");
edm::InputTag    sumPtopTag_ = edm::InputTag("BESTProducer", "sumPtop", "run");
edm::InputTag    sumPWTag_ = edm::InputTag("BESTProducer", "sumPW", "run");
edm::InputTag    sumPZTag_ = edm::InputTag("BESTProducer", "sumPZ", "run");
edm::InputTag    sumPHTag_ = edm::InputTag("BESTProducer", "sumPH", "run");
edm::InputTag    sumPjetTag_ = edm::InputTag("BESTProducer", "sumPjet", "run");
edm::InputTag    NjetstopTag_ = edm::InputTag("BESTProducer", "Njetstop", "run");  
edm::InputTag    NjetsWTag_ = edm::InputTag("BESTProducer", "NjetsW", "run");  
edm::InputTag    NjetsZTag_ = edm::InputTag("BESTProducer", "NjetsZ", "run");  
edm::InputTag    NjetsHTag_ = edm::InputTag("BESTProducer", "NjetsH", "run");  
edm::InputTag    NjetsjetTag_ = edm::InputTag("BESTProducer", "Njetsjet", "run");  
edm::InputTag    FWmoment1topTag_ = edm::InputTag("BESTProducer", "FWmoment1top", "run");
edm::InputTag    FWmoment2topTag_ = edm::InputTag("BESTProducer", "FWmoment2top", "run");
edm::InputTag    FWmoment3topTag_ = edm::InputTag("BESTProducer", "FWmoment3top", "run");
edm::InputTag    FWmoment4topTag_ = edm::InputTag("BESTProducer", "FWmoment4top", "run");
edm::InputTag    isotropytopTag_ = edm::InputTag("BESTProducer", "isotropytop", "run");
edm::InputTag    sphericitytopTag_ = edm::InputTag("BESTProducer", "sphericitytop", "run");
edm::InputTag    aplanaritytopTag_ = edm::InputTag("BESTProducer", "aplanaritytop", "run");
edm::InputTag    thrusttopTag_ = edm::InputTag("BESTProducer", "thrusttop", "run");
edm::InputTag    FWmoment1WTag_ = edm::InputTag("BESTProducer", "FWmoment1W", "run");
edm::InputTag    FWmoment2WTag_ = edm::InputTag("BESTProducer", "FWmoment2W", "run");
edm::InputTag    FWmoment3WTag_ = edm::InputTag("BESTProducer", "FWmoment3W", "run");
edm::InputTag    FWmoment4WTag_ = edm::InputTag("BESTProducer", "FWmoment4W", "run");
edm::InputTag    isotropyWTag_ = edm::InputTag("BESTProducer", "isotropyW", "run");
edm::InputTag    sphericityWTag_ = edm::InputTag("BESTProducer", "sphericityW", "run");
edm::InputTag    aplanarityWTag_ = edm::InputTag("BESTProducer", "aplanarityW", "run");
edm::InputTag    thrustWTag_ = edm::InputTag("BESTProducer", "thrustW", "run");
edm::InputTag    FWmoment1ZTag_ = edm::InputTag("BESTProducer", "FWmoment1Z", "run");
edm::InputTag    FWmoment2ZTag_ = edm::InputTag("BESTProducer", "FWmoment2Z", "run");
edm::InputTag    FWmoment3ZTag_ = edm::InputTag("BESTProducer", "FWmoment3Z", "run");
edm::InputTag    FWmoment4ZTag_ = edm::InputTag("BESTProducer", "FWmoment4Z", "run");
edm::InputTag    isotropyZTag_ = edm::InputTag("BESTProducer", "isotropyZ", "run");
edm::InputTag    sphericityZTag_ = edm::InputTag("BESTProducer", "sphericityZ", "run");
edm::InputTag    aplanarityZTag_ = edm::InputTag("BESTProducer", "aplanarityZ", "run");
edm::InputTag    thrustZTag_ = edm::InputTag("BESTProducer", "thrustZ", "run");
edm::InputTag    FWmoment1HTag_ = edm::InputTag("BESTProducer", "FWmoment1H", "run");
edm::InputTag    FWmoment2HTag_ = edm::InputTag("BESTProducer", "FWmoment2H", "run");
edm::InputTag    FWmoment3HTag_ = edm::InputTag("BESTProducer", "FWmoment3H", "run");
edm::InputTag    FWmoment4HTag_ = edm::InputTag("BESTProducer", "FWmoment4H", "run");
edm::InputTag    isotropyHTag_ = edm::InputTag("BESTProducer", "isotropyH", "run");
edm::InputTag    sphericityHTag_ = edm::InputTag("BESTProducer", "sphericityH", "run");
edm::InputTag    aplanarityHTag_ = edm::InputTag("BESTProducer", "aplanarityH", "run");
edm::InputTag    thrustHTag_ = edm::InputTag("BESTProducer", "thrustH", "run");
edm::InputTag    etTag_ = edm::InputTag("BESTProducer", "et", "run");
edm::InputTag    etaTag_ = edm::InputTag("BESTProducer", "eta", "run");
edm::InputTag    massTag_ = edm::InputTag("BESTProducer", "mass", "run");
edm::InputTag    SDmassTag_ = edm::InputTag("BESTProducer", "SDmass", "run");
edm::InputTag    tau32Tag_ = edm::InputTag("BESTProducer", "tau32", "run");
edm::InputTag    tau21Tag_ = edm::InputTag("BESTProducer", "tau21", "run");
edm::InputTag    bDiscTag_ = edm::InputTag("BESTProducer", "bDisc", "run"); 
edm::InputTag    vertTag_ = edm::InputTag("BESTProducer", "nPV", "run");
edm::InputTag    decayModeTag_ = edm::InputTag("BESTProducer", "decayMode", "run");
edm::InputTag    nak4JetsTag_ = edm::InputTag("BESTProducer", "nAK4Jets", "run");
edm::InputTag    savedJetsTag_ = edm::InputTag("BESTProducer", "savedJets", "run");


   fwm0Token_ = consumes<std::vector<float> >(fwm0Tag_);
   fwm1Token_ = consumes<std::vector<float> >(fwm1Tag_);
   fwm2Token_ = consumes<std::vector<float> >(fwm2Tag_);
   fwm3Token_ = consumes<std::vector<float> >(fwm3Tag_);
   fwm4Token_ = consumes<std::vector<float> >(fwm4Tag_);
   NjetstopToken_ = consumes<std::vector<float> >(NjetstopTag_);
   NjetsWToken_ = consumes<std::vector<float> >(NjetsWTag_);
   NjetsZToken_ = consumes<std::vector<float> >(NjetsZTag_);
   NjetsHToken_ = consumes<std::vector<float> >(NjetsHTag_);
   NjetsjetToken_ = consumes<std::vector<float> >(NjetsjetTag_);

   sumPztopToken_ = consumes<std::vector<float> >(sumPztopTag_); 
   sumPzWToken_ = consumes<std::vector<float> >(sumPzWTag_); 
   sumPzZToken_ = consumes<std::vector<float> >(sumPzZTag_); 
   sumPzHToken_ = consumes<std::vector<float> >(sumPzHTag_); 
   sumPzjetToken_ = consumes<std::vector<float> >(sumPzjetTag_); 
   sumPtopToken_ = consumes<std::vector<float> >(sumPtopTag_); 
   sumPWToken_ = consumes<std::vector<float> >(sumPWTag_); 
   sumPZToken_ = consumes<std::vector<float> >(sumPZTag_); 
   sumPHToken_ = consumes<std::vector<float> >(sumPHTag_); 
   sumPjetToken_ = consumes<std::vector<float> >(sumPjetTag_); 

   FWmoment1topToken_ = consumes<std::vector<float> >(FWmoment1topTag_);
   FWmoment2topToken_ = consumes<std::vector<float> >(FWmoment2topTag_);
   FWmoment3topToken_ = consumes<std::vector<float> >(FWmoment3topTag_);
   FWmoment4topToken_ = consumes<std::vector<float> >(FWmoment4topTag_);
   isotropytopToken_ = consumes<std::vector<float> >(isotropytopTag_);
   sphericitytopToken_ = consumes<std::vector<float> >(sphericitytopTag_);
   aplanaritytopToken_ = consumes<std::vector<float> >(aplanaritytopTag_);
   thrusttopToken_ = consumes<std::vector<float> >(thrusttopTag_);
   FWmoment1WToken_ = consumes<std::vector<float> >(FWmoment1WTag_);
   FWmoment2WToken_ = consumes<std::vector<float> >(FWmoment2WTag_);
   FWmoment3WToken_ = consumes<std::vector<float> >(FWmoment3WTag_);
   FWmoment4WToken_ = consumes<std::vector<float> >(FWmoment4WTag_);
   isotropyWToken_ = consumes<std::vector<float> >(isotropyWTag_);
   sphericityWToken_ = consumes<std::vector<float> >(sphericityWTag_);
   aplanarityWToken_ = consumes<std::vector<float> >(aplanarityWTag_);
   thrustWToken_ = consumes<std::vector<float> >(thrustWTag_);
   FWmoment1ZToken_ = consumes<std::vector<float> >(FWmoment1ZTag_);
   FWmoment2ZToken_ = consumes<std::vector<float> >(FWmoment2ZTag_);
   FWmoment3ZToken_ = consumes<std::vector<float> >(FWmoment3ZTag_);
   FWmoment4ZToken_ = consumes<std::vector<float> >(FWmoment4ZTag_);
   isotropyZToken_ = consumes<std::vector<float> >(isotropyZTag_);
   sphericityZToken_ = consumes<std::vector<float> >(sphericityZTag_);
   aplanarityZToken_ = consumes<std::vector<float> >(aplanarityZTag_);
   thrustZToken_ = consumes<std::vector<float> >(thrustZTag_);
   FWmoment1HToken_ = consumes<std::vector<float> >(FWmoment1HTag_);
   FWmoment2HToken_ = consumes<std::vector<float> >(FWmoment2HTag_);
   FWmoment3HToken_ = consumes<std::vector<float> >(FWmoment3HTag_);
   FWmoment4HToken_ = consumes<std::vector<float> >(FWmoment4HTag_);
   isotropyHToken_ = consumes<std::vector<float> >(isotropyHTag_);
   sphericityHToken_ = consumes<std::vector<float> >(sphericityHTag_);
   aplanarityHToken_ = consumes<std::vector<float> >(aplanarityHTag_);
   thrustHToken_ = consumes<std::vector<float> >(thrustHTag_);

   etToken_ = consumes<std::vector<float> >(etTag_);
   etaToken_ = consumes<std::vector<float> >(etaTag_); 
   massToken_ = consumes<std::vector<float> >(massTag_); 
   SDmassToken_ = consumes<std::vector<float> >(SDmassTag_); 
   tau32Token_ = consumes<std::vector<float> >(tau32Tag_); 
   tau21Token_ = consumes<std::vector<float> >(tau21Tag_); 
   bDiscToken_ = consumes<std::vector<float> > (bDiscTag_);
   vertToken_ = consumes<std::vector<int> > (vertTag_);
   decayModeToken_ = consumes<std::vector<int> > (decayModeTag_);
   nak4JetsToken_ = consumes<std::vector<int> > (nak4JetsTag_);
   savedJetsToken_ = consumes<std::vector<pat::Jet> > (savedJetsTag_);
   


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
   listOfVars.push_back("PzOverP_top");
   listOfVars.push_back("PzOverP_W");
   listOfVars.push_back("PzOverP_Z");
   listOfVars.push_back("PzOverP_H");

   
   for (unsigned i = 0; i < listOfVars.size(); i++){

	treeVars[ listOfVars[i] ] = -999.999;

  }


  eventTree = fs->make<TTree> ("eventTree", "eventTree");

  listOfEventVars.push_back("jet0_SDmass");
  listOfEventVars.push_back("jet0_tau32");
  listOfEventVars.push_back("jet0_bDisc");
  listOfEventVars.push_back("jet0_pt");
  listOfEventVars.push_back("jet0_eta");
  listOfEventVars.push_back("jet0_distToTop");
  listOfEventVars.push_back("jet1_SDmass");
  listOfEventVars.push_back("jet1_tau32");
  listOfEventVars.push_back("jet1_bDisc");
  listOfEventVars.push_back("jet1_pt");
  listOfEventVars.push_back("jet1_eta");
  listOfEventVars.push_back("jet1_distToTop");
  listOfEventVars.push_back("nPV");
  listOfEventVars.push_back("mjj");
  listOfEventVars.push_back("dy");
  listOfEventVars.push_back("Njets");
  listOfEventVars.push_back("NjetsAK4");
  listOfEventVars.push_back("jet0_NNout1");
  listOfEventVars.push_back("jet0_NNout2");
  listOfEventVars.push_back("jet0_NNout3");
  listOfEventVars.push_back("jet0_NNout4");
  listOfEventVars.push_back("jet1_NNout1");
  listOfEventVars.push_back("jet1_NNout2");
  listOfEventVars.push_back("jet1_NNout3");
  listOfEventVars.push_back("jet1_NNout4");
  listOfEventVars.push_back("jet0_NNout5");
  listOfEventVars.push_back("jet1_NNout5");
  listOfEventVars.push_back("numTop");
  listOfEventVars.push_back("numW");
  listOfEventVars.push_back("numZ");
  listOfEventVars.push_back("numH");
  listOfEventVars.push_back("numQCD");
  listOfEventVars.push_back("ht");

  for (unsigned i = 0; i < listOfEventVars.size(); i++){

	eventVars[ listOfEventVars[i] ] = -999.9;
	eventTree->Branch( (listOfEventVars[i]).c_str(), &(eventVars[ listOfEventVars[i] ]), (listOfEventVars[i]+"/F").c_str());

  }


   eventTree->Branch( "NNout1", &NNout1vals);
   eventTree->Branch( "NNout2", &NNout2vals);
   eventTree->Branch( "NNout3", &NNout3vals);
   eventTree->Branch( "NNout4", &NNout4vals);
   eventTree->Branch( "NNout5", &NNout5vals);
   eventTree->Branch( "et", &etvals);
   eventTree->Branch( "eta", &etavals);
   eventTree->Branch( "phi", &phivals);
   eventTree->Branch( "mass", &massvals);
   eventTree->Branch( "sdmass", &sdmassvals);
   eventTree->Branch( "decayMode", &decayModevals);

   reader = new TMVA::Reader();
   reader->SetVerbose(1);
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

   reader->BookMVA("fived", "TMVARegression_MLP.weights.xml");




}


BESTAnalyzer::~BESTAnalyzer()
{

 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
BESTAnalyzer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::unique_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(std::move(pOut));
*/
Handle< std::vector<float> >    fwm0Handle;
Handle< std::vector<float> >    fwm1Handle;
Handle< std::vector<float> >    fwm2Handle;
Handle< std::vector<float> >    fwm3Handle;
Handle< std::vector<float> >    fwm4Handle;
Handle< std::vector<float> >    NjetstopHandle;
Handle< std::vector<float> >    NjetsWHandle;
Handle< std::vector<float> >    NjetsZHandle;
Handle< std::vector<float> >    NjetsHHandle;
Handle< std::vector<float> >    NjetsjetHandle;
Handle< std::vector<float> >    sumPztopHandle;
Handle< std::vector<float> >    sumPzWHandle;
Handle< std::vector<float> >    sumPzZHandle;
Handle< std::vector<float> >    sumPzHHandle;
Handle< std::vector<float> >    sumPzjetHandle;
Handle< std::vector<float> >    sumPtopHandle;
Handle< std::vector<float> >    sumPWHandle;
Handle< std::vector<float> >    sumPZHandle;
Handle< std::vector<float> >    sumPHHandle;
Handle< std::vector<float> >    sumPjetHandle;
Handle< std::vector<float> >    FWmoment1topHandle;
Handle< std::vector<float> >    FWmoment2topHandle;
Handle< std::vector<float> >    FWmoment3topHandle;
Handle< std::vector<float> >    FWmoment4topHandle;
Handle< std::vector<float> >    isotropytopHandle;
Handle< std::vector<float> >    sphericitytopHandle;
Handle< std::vector<float> >    aplanaritytopHandle;
Handle< std::vector<float> >    thrusttopHandle;
Handle< std::vector<float> >    FWmoment1WHandle;
Handle< std::vector<float> >    FWmoment2WHandle;
Handle< std::vector<float> >    FWmoment3WHandle;
Handle< std::vector<float> >    FWmoment4WHandle;
Handle< std::vector<float> >    isotropyWHandle;
Handle< std::vector<float> >    sphericityWHandle;
Handle< std::vector<float> >    aplanarityWHandle;
Handle< std::vector<float> >    thrustWHandle;
Handle< std::vector<float> >    FWmoment1ZHandle;
Handle< std::vector<float> >    FWmoment2ZHandle;
Handle< std::vector<float> >    FWmoment3ZHandle;
Handle< std::vector<float> >    FWmoment4ZHandle;
Handle< std::vector<float> >    isotropyZHandle;
Handle< std::vector<float> >    sphericityZHandle;
Handle< std::vector<float> >    aplanarityZHandle;
Handle< std::vector<float> >    thrustZHandle;
Handle< std::vector<float> >    FWmoment1HHandle;
Handle< std::vector<float> >    FWmoment2HHandle;
Handle< std::vector<float> >    FWmoment3HHandle;
Handle< std::vector<float> >    FWmoment4HHandle;
Handle< std::vector<float> >    isotropyHHandle;
Handle< std::vector<float> >    sphericityHHandle;
Handle< std::vector<float> >    aplanarityHHandle;
Handle< std::vector<float> >    thrustHHandle;
Handle< std::vector<float> >    etHandle;
Handle< std::vector<float> >    etaHandle;
Handle< std::vector<float> >    massHandle;
Handle< std::vector<float> >    SDmassHandle;
Handle< std::vector<float> >    tau32Handle;
Handle< std::vector<float> >    tau21Handle;
Handle< std::vector<float> >    bDiscHandle;
Handle< std::vector<int> > vertHandle;
Handle< std::vector<int> > decayModeHandle;
Handle< std::vector<int> > nak4JetsHandle;
Handle< std::vector<pat::Jet> > savedJetsHandle;

iEvent.getByToken(   fwm0Token_, fwm0Handle );
iEvent.getByToken(   fwm1Token_, fwm1Handle );
iEvent.getByToken(   fwm2Token_, fwm2Handle );
iEvent.getByToken(   fwm3Token_, fwm3Handle );
iEvent.getByToken(   fwm4Token_, fwm4Handle );
iEvent.getByToken(   NjetstopToken_, NjetstopHandle);
iEvent.getByToken(   NjetsWToken_, NjetsWHandle);
iEvent.getByToken(   NjetsZToken_, NjetsZHandle);
iEvent.getByToken(   NjetsHToken_, NjetsHHandle);
iEvent.getByToken(   NjetsjetToken_, NjetsjetHandle);
iEvent.getByToken(   sumPztopToken_, sumPztopHandle);
iEvent.getByToken(   sumPzWToken_, sumPzWHandle);
iEvent.getByToken(   sumPzZToken_, sumPzZHandle);
iEvent.getByToken(   sumPzHToken_, sumPzHHandle);
iEvent.getByToken(   sumPzjetToken_, sumPzjetHandle);
iEvent.getByToken(   sumPtopToken_, sumPtopHandle);
iEvent.getByToken(   sumPWToken_, sumPWHandle);
iEvent.getByToken(   sumPZToken_, sumPZHandle);
iEvent.getByToken(   sumPHToken_, sumPHHandle);
iEvent.getByToken(   sumPjetToken_, sumPjetHandle);

iEvent.getByToken(   FWmoment1topToken_, FWmoment1topHandle);
iEvent.getByToken(   FWmoment2topToken_, FWmoment2topHandle);
iEvent.getByToken(   FWmoment3topToken_, FWmoment3topHandle);
iEvent.getByToken(   FWmoment4topToken_, FWmoment4topHandle);
iEvent.getByToken(   isotropytopToken_, isotropytopHandle);
iEvent.getByToken(   sphericitytopToken_, sphericitytopHandle);
iEvent.getByToken(   aplanaritytopToken_, aplanaritytopHandle);
iEvent.getByToken(   thrusttopToken_, thrusttopHandle);
iEvent.getByToken(   FWmoment1WToken_, FWmoment1WHandle);
iEvent.getByToken(   FWmoment2WToken_, FWmoment2WHandle);
iEvent.getByToken(   FWmoment3WToken_, FWmoment3WHandle);
iEvent.getByToken(   FWmoment4WToken_, FWmoment4WHandle);
iEvent.getByToken(   isotropyWToken_, isotropyWHandle);
iEvent.getByToken(   sphericityWToken_, sphericityWHandle);
iEvent.getByToken(   aplanarityWToken_, aplanarityWHandle);
iEvent.getByToken(   thrustWToken_, thrustWHandle);
iEvent.getByToken(   FWmoment1ZToken_, FWmoment1ZHandle);
iEvent.getByToken(   FWmoment2ZToken_, FWmoment2ZHandle);
iEvent.getByToken(   FWmoment3ZToken_, FWmoment3ZHandle);
iEvent.getByToken(   FWmoment4ZToken_, FWmoment4ZHandle);
iEvent.getByToken(   isotropyZToken_, isotropyZHandle);
iEvent.getByToken(   sphericityZToken_, sphericityZHandle);
iEvent.getByToken(   aplanarityZToken_, aplanarityZHandle);
iEvent.getByToken(   thrustZToken_, thrustZHandle);
iEvent.getByToken(   FWmoment1HToken_, FWmoment1HHandle);
iEvent.getByToken(   FWmoment2HToken_, FWmoment2HHandle);
iEvent.getByToken(   FWmoment3HToken_, FWmoment3HHandle);
iEvent.getByToken(   FWmoment4HToken_, FWmoment4HHandle);
iEvent.getByToken(   isotropyHToken_, isotropyHHandle);
iEvent.getByToken(   sphericityHToken_, sphericityHHandle);
iEvent.getByToken(   aplanarityHToken_, aplanarityHHandle);
iEvent.getByToken(   thrustHToken_, thrustHHandle);


iEvent.getByToken(   etToken_, etHandle);
iEvent.getByToken(   etaToken_, etaHandle);
iEvent.getByToken(   massToken_, massHandle);
iEvent.getByToken(   SDmassToken_, SDmassHandle);
iEvent.getByToken(   tau32Token_, tau32Handle);
iEvent.getByToken(   tau21Token_, tau21Handle);
iEvent.getByToken(   bDiscToken_, bDiscHandle);
iEvent.getByToken(   vertToken_, vertHandle);
iEvent.getByToken(   decayModeToken_, decayModeHandle);
iEvent.getByToken(   nak4JetsToken_, nak4JetsHandle);
iEvent.getByToken(   savedJetsToken_, savedJetsHandle);

if (etHandle->size() < 2) return;

eventVars["Njets"] = etHandle->size();
eventVars["NjetsAK4"] = nak4JetsHandle->at(0);
eventVars["nPV"] = vertHandle->at(0);

std::vector<float> NNout1, NNout2, NNout3, NNout4, NNout5;
int nTop = 0;
int nW = 0;
int nZ = 0;
int nH = 0;
int nQCD = 0;

NNout1vals.clear();
NNout2vals.clear();
NNout3vals.clear();
NNout4vals.clear();
NNout5vals.clear();
etvals.clear();
etavals.clear();
phivals.clear();
massvals.clear();
sdmassvals.clear();
decayModevals.clear();

for (size_t i = 0; i < decayModeHandle->size(); i++){

	decayModevals.push_back( decayModeHandle->at(i) );
}

float ak8_ht = 0.00;


for (size_t i = 0; i < etHandle->size(); i++){

    ak8_ht += etHandle->at(i);
    pat::Jet thisJet = savedJetsHandle->at(i); 

    if ( etHandle->at(i) < 500) continue;
    if ( SDmassHandle->at(i) < 40.0) continue;

    treeVars["PzOverP_top"]       =  ( sumPztopHandle->at(i) / (sumPtopHandle->at(i) + 0.0001) );
    treeVars["PzOverP_Z"]         =  ( sumPzZHandle->at(i) / (sumPZHandle->at(i) + 0.0001) );
    treeVars["PzOverP_W"]         =  ( sumPzWHandle->at(i) / (sumPWHandle->at(i) + 0.0001) );
    treeVars["PzOverP_H"]         =  ( sumPzHHandle->at(i) / (sumPHHandle->at(i) + 0.0001) );
    treeVars["h1_top"]            =  ( FWmoment1topHandle->at(i) );
    treeVars["h2_top"]            =  ( FWmoment2topHandle->at(i) );
    treeVars["h3_top"]            =  ( FWmoment3topHandle->at(i) );
    treeVars["h4_top"]            =  ( FWmoment4topHandle->at(i) );
    treeVars["isotropy_top"]      =  ( isotropytopHandle->at(i) );
    treeVars["sphericity_top"]     =  ( sphericitytopHandle->at(i) );
    treeVars["aplanarity_top"]    =  ( aplanaritytopHandle->at(i) );
    treeVars["thrust_top"]    =  ( thrusttopHandle->at(i) );
    treeVars["h1_W"]              =  ( FWmoment1WHandle->at(i) );
    treeVars["h2_W"]              =  ( FWmoment2WHandle->at(i) );
    treeVars["h3_W"]              =  ( FWmoment3WHandle->at(i) );
    treeVars["h4_W"]              =  ( FWmoment4WHandle->at(i) );
    treeVars["isotropy_W"]        =  ( isotropyWHandle->at(i) );
    treeVars["sphericity_W"]       =  ( sphericityWHandle->at(i) );
    treeVars["aplanarity_W"]      =  ( aplanarityWHandle->at(i) );
    treeVars["thrust_W"]      =  ( thrustWHandle->at(i) );
    treeVars["h1_Z"]              =  ( FWmoment1ZHandle->at(i) );
    treeVars["h2_Z"]              =  ( FWmoment2ZHandle->at(i) );
    treeVars["h3_Z"]              =  ( FWmoment3ZHandle->at(i) );
    treeVars["h4_Z"]              =  ( FWmoment4ZHandle->at(i) );
    treeVars["isotropy_Z"]        =  ( isotropyZHandle->at(i) );
    treeVars["sphericity_Z"]       =  ( sphericityZHandle->at(i) );
    treeVars["aplanarity_Z"]      =  ( aplanarityZHandle->at(i) );
    treeVars["thrust_Z"]      =  ( thrustZHandle->at(i) );
    treeVars["h1_H"]              =  ( FWmoment1HHandle->at(i) );
    treeVars["h2_H"]              =  ( FWmoment2HHandle->at(i) );
    treeVars["h3_H"]              =  ( FWmoment3HHandle->at(i) );
    treeVars["h4_H"]              =  ( FWmoment4HHandle->at(i) );
    treeVars["isotropy_H"]        =  ( isotropyHHandle->at(i) );
    treeVars["sphericity_H"]       =  ( sphericityHHandle->at(i) );
    treeVars["aplanarity_H"]      =  ( aplanarityHHandle->at(i) );
    treeVars["thrust_H"]      =  ( thrustHHandle->at(i) );
    treeVars["et"]                =  ( etHandle->at(i) );
    treeVars["eta"]               =  ( etaHandle->at(i) );
    treeVars["SDmass"]            =  ( SDmassHandle->at(i) );
    treeVars["tau32"]             =  ( tau32Handle->at(i) );
    treeVars["tau21"]             =  ( tau21Handle->at(i) );
    
				
    NNout1vals.push_back((reader->EvaluateRegression( "fived" ))[0]);
    NNout2vals.push_back((reader->EvaluateRegression( "fived" ))[1]);
    NNout3vals.push_back((reader->EvaluateRegression( "fived" ))[2]);
    NNout4vals.push_back((reader->EvaluateRegression( "fived" ))[3]);
    NNout5vals.push_back((reader->EvaluateRegression( "fived" ))[4]);

    etvals.push_back( etHandle->at(i));
    etavals.push_back( thisJet.eta());
    phivals.push_back( thisJet.phi());
    massvals.push_back( thisJet.mass());
    sdmassvals.push_back( SDmassHandle->at(i));



    float distTo1 = sqrt( (NNout1vals[i] - 1.0)*(NNout1vals[i] - 1.0) + (NNout2vals[i] - 0.0) * (NNout2vals[i] - 0.0) + (NNout3vals[i] - 0.0) * (NNout3vals[i] - 0.0) + (NNout4vals[i] - 0.0) * (NNout4vals[i] - 0.0) + (NNout5vals[i] - 0.0) * (NNout5vals[i] - 0.0)  ) ;
    float distTo2 = sqrt( (NNout1vals[i] - 0.0)*(NNout1vals[i] - 0.0) + (NNout2vals[i] - 1.0) * (NNout2vals[i] - 1.0) + (NNout3vals[i] - 0.0) * (NNout3vals[i] - 0.0) + (NNout4vals[i] - 0.0) * (NNout4vals[i] - 0.0) + (NNout5vals[i] - 0.0) * (NNout5vals[i] - 0.0)  ) ;
    float distTo3 = sqrt( (NNout1vals[i] - 0.0)*(NNout1vals[i] - 0.0) + (NNout2vals[i] - 0.0) * (NNout2vals[i] - 0.0) + (NNout3vals[i] - 1.0) * (NNout3vals[i] - 1.0) + (NNout4vals[i] - 0.0) * (NNout4vals[i] - 0.0) + (NNout5vals[i] - 0.0) * (NNout5vals[i] - 0.0)  ) ;
    float distTo4 = sqrt( (NNout1vals[i] - 0.0)*(NNout1vals[i] - 0.0) + (NNout2vals[i] - 0.0) * (NNout2vals[i] - 0.0) + (NNout3vals[i] - 0.0) * (NNout3vals[i] - 0.0) + (NNout4vals[i] - 1.0) * (NNout4vals[i] - 1.0) + (NNout5vals[i] - 0.0) * (NNout5vals[i] - 0.0)  ) ;
    float distTo5 = sqrt( (NNout1vals[i] - 0.0)*(NNout1vals[i] - 0.0) + (NNout2vals[i] - 0.0) * (NNout2vals[i] - 0.0) + (NNout3vals[i] - 0.0) * (NNout3vals[i] - 0.0) + (NNout4vals[i] - 0.0) * (NNout4vals[i] - 0.0) + (NNout5vals[i] - 1.0) * (NNout5vals[i] - 1.0)  ) ;

    std::vector<float> a{ distTo1, distTo2, distTo3, distTo4, distTo5};
    std::vector<float>::iterator result = std::min_element(std::begin(a), std::end(a));

    float particleType = std::distance(std::begin(a), result);

    if (particleType == 0) nQCD++;
    if (particleType == 1) nTop++;
    if (particleType == 2) nH++;
    if (particleType == 3) nZ++;
    if (particleType == 4) nW++;

}
 


/*float distTo1_jet0 = sqrt( (NNout1[0] - 1.0)*(NNout1[0] - 1.0) + (NNout2[0] - 0.0) * (NNout2[0] - 0.0) + (NNout3[0] - 0.0) * (NNout3[0] - 0.0) + (NNout4[0] - 0.0) * (NNout4[0] - 0.0) ) ;
float distTo1_jet1 = sqrt( (NNout1[1] - 1.0)*(NNout1[1] - 1.0) + (NNout2[1] - 0.0) * (NNout2[1] - 0.0) + (NNout3[1] - 0.0) * (NNout3[1] - 0.0) + (NNout4[1] - 0.0) * (NNout4[1] - 0.0) ) ;
float distTo2_jet0 = sqrt( (NNout1[0] - 0.0)*(NNout1[0] - 0.0) + (NNout2[0] - 1.0) * (NNout2[0] - 1.0) + (NNout3[0] - 0.0) * (NNout3[0] - 0.0) + (NNout4[0] - 0.0) * (NNout4[0] - 0.0) ) ;
float distTo2_jet1 = sqrt( (NNout1[1] - 0.0)*(NNout1[1] - 0.0) + (NNout2[1] - 1.0) * (NNout2[1] - 1.0) + (NNout3[1] - 0.0) * (NNout3[1] - 0.0) + (NNout4[1] - 0.0) * (NNout4[1] - 0.0) ) ;
float distTo3_jet0 = sqrt( (NNout1[0] - 0.0)*(NNout1[0] - 0.0) + (NNout2[0] - 0.0) * (NNout2[0] - 0.0) + (NNout3[0] - 1.0) * (NNout3[0] - 1.0) + (NNout4[0] - 0.0) * (NNout4[0] - 0.0) ) ;
float distTo3_jet1 = sqrt( (NNout1[1] - 0.0)*(NNout1[1] - 0.0) + (NNout2[1] - 0.0) * (NNout2[1] - 0.0) + (NNout3[1] - 1.0) * (NNout3[1] - 1.0) + (NNout4[1] - 0.0) * (NNout4[1] - 0.0) ) ;
float distTo4_jet0 = sqrt( (NNout1[0] - 0.0)*(NNout1[0] - 0.0) + (NNout2[0] - 0.0) * (NNout2[0] - 0.0) + (NNout3[0] - 0.0) * (NNout3[0] - 0.0) + (NNout4[0] - 1.0) * (NNout4[0] - 1.0) ) ;
float distTo4_jet1 = sqrt( (NNout1[1] - 0.0)*(NNout1[1] - 0.0) + (NNout2[1] - 0.0) * (NNout2[1] - 0.0) + (NNout3[1] - 0.0) * (NNout3[1] - 0.0) + (NNout4[1] - 1.0) * (NNout4[1] - 1.0) ) ;
*/


/*
eventVars["jet0_distToTop"] = distTo1_jet0;
eventVars["jet1_distToTop"] = distTo1_jet1;
eventVars["jet0_SDmass"] = SDmassHandle->at(0);
eventVars["jet0_tau32"] = tau32Handle->at(0);
eventVars["jet0_bDisc"] = bDiscHandle->at(0);
eventVars["jet0_pt"] = etHandle->at(0);
eventVars["jet0_eta"] = etaHandle->at(0);
eventVars["jet1_SDmass"] = SDmassHandle->at(1);
eventVars["jet1_tau32"] = tau32Handle->at(1);
eventVars["jet1_bDisc"] = bDiscHandle->at(1);
eventVars["jet1_pt"] = etHandle->at(1);
eventVars["jet1_eta"] = etaHandle->at(1);

eventVars["jet0_NNout1"] = NNout1[0];
eventVars["jet0_NNout2"] = NNout2[0];
eventVars["jet0_NNout3"] = NNout3[0];
eventVars["jet0_NNout4"] = NNout4[0];
eventVars["jet0_NNout5"] = NNout5[0];
eventVars["jet1_NNout1"] = NNout1[1];
eventVars["jet1_NNout2"] = NNout2[1];
eventVars["jet1_NNout3"] = NNout3[1];
eventVars["jet1_NNout4"] = NNout4[1];
eventVars["jet1_NNout5"] = NNout5[1];
*/


eventVars["numTop"] = nTop;
eventVars["numW"] = nW;
eventVars["numZ"] = nZ;
eventVars["numH"] = nH;
eventVars["numQCD"] = nQCD;
eventVars["ht"] = ak8_ht;


/*
pat::Jet patjet0 = savedJetsHandle->at(0);
TLorentzVector jet0;
jet0.SetPtEtaPhiM( patjet0.pt(), patjet0.eta(), patjet0.phi(), patjet0.mass() );
pat::Jet patjet1 = savedJetsHandle->at(1);
TLorentzVector jet1;
jet1.SetPtEtaPhiM( patjet1.pt(), patjet1.eta(), patjet1.phi(), patjet1.mass() );

TLorentzVector dijet = jet0 + jet1;

eventVars["mjj"] = dijet.M();
eventVars["dy"] = jet0.Rapidity() - jet1.Rapidity();
*/


eventTree->Fill();

 
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
BESTAnalyzer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
BESTAnalyzer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
BESTAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
BESTAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
BESTAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
BESTAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BESTAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BESTAnalyzer);
