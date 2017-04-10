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
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

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
      edm::EDGetTokenT<std::vector<double> > fwm0Token_;
      edm::EDGetTokenT<std::vector<double> > fwm1Token_;
      edm::EDGetTokenT<std::vector<double> > fwm2Token_;
      edm::EDGetTokenT<std::vector<double> > fwm3Token_;
      edm::EDGetTokenT<std::vector<double> > fwm4Token_;

      edm::EDGetTokenT<std::vector<double> > sumPztopToken_;
      edm::EDGetTokenT<std::vector<double> > sumPzWToken_;
      edm::EDGetTokenT<std::vector<double> > sumPzZToken_;
      edm::EDGetTokenT<std::vector<double> > sumPzHToken_;
      edm::EDGetTokenT<std::vector<double> > sumPzjetToken_;
      edm::EDGetTokenT<std::vector<double> > sumPtopToken_;
      edm::EDGetTokenT<std::vector<double> > sumPWToken_;
      edm::EDGetTokenT<std::vector<double> > sumPZToken_;
      edm::EDGetTokenT<std::vector<double> > sumPHToken_;
      edm::EDGetTokenT<std::vector<double> > sumPjetToken_;

      edm::EDGetTokenT<std::vector<double> > NjetstopToken_;
      edm::EDGetTokenT<std::vector<double> > NjetsWToken_;
      edm::EDGetTokenT<std::vector<double> > NjetsZToken_;
      edm::EDGetTokenT<std::vector<double> > NjetsHToken_;
      edm::EDGetTokenT<std::vector<double> > NjetsjetToken_;

      edm::EDGetTokenT<std::vector<double> > FWmoment1topToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment2topToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment3topToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment4topToken_;
      edm::EDGetTokenT<std::vector<double> > isotropytopToken_;
      edm::EDGetTokenT<std::vector<double> > sphericitytopToken_;
      edm::EDGetTokenT<std::vector<double> > aplanaritytopToken_;
      edm::EDGetTokenT<std::vector<double> > thrusttopToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment1WToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment2WToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment3WToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment4WToken_;
      edm::EDGetTokenT<std::vector<double> > isotropyWToken_;
      edm::EDGetTokenT<std::vector<double> > sphericityWToken_;
      edm::EDGetTokenT<std::vector<double> > aplanarityWToken_;
      edm::EDGetTokenT<std::vector<double> > thrustWToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment1ZToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment2ZToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment3ZToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment4ZToken_;
      edm::EDGetTokenT<std::vector<double> > isotropyZToken_;
      edm::EDGetTokenT<std::vector<double> > sphericityZToken_;
      edm::EDGetTokenT<std::vector<double> > aplanarityZToken_;
      edm::EDGetTokenT<std::vector<double> > thrustZToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment1HToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment2HToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment3HToken_;
      edm::EDGetTokenT<std::vector<double> > FWmoment4HToken_;
      edm::EDGetTokenT<std::vector<double> > isotropyHToken_;
      edm::EDGetTokenT<std::vector<double> > sphericityHToken_;
      edm::EDGetTokenT<std::vector<double> > aplanarityHToken_;
      edm::EDGetTokenT<std::vector<double> > thrustHToken_;

      edm::EDGetTokenT<std::vector<double> > etToken_;
      edm::EDGetTokenT<std::vector<double> > etaToken_;
      edm::EDGetTokenT<std::vector<double> > massToken_;
      edm::EDGetTokenT<std::vector<double> > SDmassToken_;
      edm::EDGetTokenT<std::vector<double> > tau32Token_;
      edm::EDGetTokenT<std::vector<double> > tau21Token_;


      TMVA::Reader *reader = new TMVA::Reader();
      std::vector<std::string> listOfVars;
      std::map<std::string, float> treeVars;


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
    

   fwm0Token_ = consumes<std::vector<double> >(fwm0Tag_);
   fwm1Token_ = consumes<std::vector<double> >(fwm1Tag_);
   fwm2Token_ = consumes<std::vector<double> >(fwm2Tag_);
   fwm3Token_ = consumes<std::vector<double> >(fwm3Tag_);
   fwm4Token_ = consumes<std::vector<double> >(fwm4Tag_);
   NjetstopToken_ = consumes<std::vector<double> >(NjetstopTag_);
   NjetsWToken_ = consumes<std::vector<double> >(NjetsWTag_);
   NjetsZToken_ = consumes<std::vector<double> >(NjetsZTag_);
   NjetsHToken_ = consumes<std::vector<double> >(NjetsHTag_);
   NjetsjetToken_ = consumes<std::vector<double> >(NjetsjetTag_);

   sumPztopToken_ = consumes<std::vector<double> >(sumPztopTag_); 
   sumPzWToken_ = consumes<std::vector<double> >(sumPzWTag_); 
   sumPzZToken_ = consumes<std::vector<double> >(sumPzZTag_); 
   sumPzHToken_ = consumes<std::vector<double> >(sumPzHTag_); 
   sumPzjetToken_ = consumes<std::vector<double> >(sumPzjetTag_); 
   sumPtopToken_ = consumes<std::vector<double> >(sumPtopTag_); 
   sumPWToken_ = consumes<std::vector<double> >(sumPWTag_); 
   sumPZToken_ = consumes<std::vector<double> >(sumPZTag_); 
   sumPHToken_ = consumes<std::vector<double> >(sumPHTag_); 
   sumPjetToken_ = consumes<std::vector<double> >(sumPjetTag_); 

   FWmoment1topToken_ = consumes<std::vector<double> >(FWmoment1topTag_);
   FWmoment2topToken_ = consumes<std::vector<double> >(FWmoment2topTag_);
   FWmoment3topToken_ = consumes<std::vector<double> >(FWmoment3topTag_);
   FWmoment4topToken_ = consumes<std::vector<double> >(FWmoment4topTag_);
   isotropytopToken_ = consumes<std::vector<double> >(isotropytopTag_);
   sphericitytopToken_ = consumes<std::vector<double> >(sphericitytopTag_);
   aplanaritytopToken_ = consumes<std::vector<double> >(aplanaritytopTag_);
   thrusttopToken_ = consumes<std::vector<double> >(thrusttopTag_);
   FWmoment1WToken_ = consumes<std::vector<double> >(FWmoment1WTag_);
   FWmoment2WToken_ = consumes<std::vector<double> >(FWmoment2WTag_);
   FWmoment3WToken_ = consumes<std::vector<double> >(FWmoment3WTag_);
   FWmoment4WToken_ = consumes<std::vector<double> >(FWmoment4WTag_);
   isotropyWToken_ = consumes<std::vector<double> >(isotropyWTag_);
   sphericityWToken_ = consumes<std::vector<double> >(sphericityWTag_);
   aplanarityWToken_ = consumes<std::vector<double> >(aplanarityWTag_);
   thrustWToken_ = consumes<std::vector<double> >(thrustWTag_);
   FWmoment1ZToken_ = consumes<std::vector<double> >(FWmoment1ZTag_);
   FWmoment2ZToken_ = consumes<std::vector<double> >(FWmoment2ZTag_);
   FWmoment3ZToken_ = consumes<std::vector<double> >(FWmoment3ZTag_);
   FWmoment4ZToken_ = consumes<std::vector<double> >(FWmoment4ZTag_);
   isotropyZToken_ = consumes<std::vector<double> >(isotropyZTag_);
   sphericityZToken_ = consumes<std::vector<double> >(sphericityZTag_);
   aplanarityZToken_ = consumes<std::vector<double> >(aplanarityZTag_);
   thrustZToken_ = consumes<std::vector<double> >(thrustZTag_);
   FWmoment1HToken_ = consumes<std::vector<double> >(FWmoment1HTag_);
   FWmoment2HToken_ = consumes<std::vector<double> >(FWmoment2HTag_);
   FWmoment3HToken_ = consumes<std::vector<double> >(FWmoment3HTag_);
   FWmoment4HToken_ = consumes<std::vector<double> >(FWmoment4HTag_);
   isotropyHToken_ = consumes<std::vector<double> >(isotropyHTag_);
   sphericityHToken_ = consumes<std::vector<double> >(sphericityHTag_);
   aplanarityHToken_ = consumes<std::vector<double> >(aplanarityHTag_);
   thrustHToken_ = consumes<std::vector<double> >(thrustHTag_);

   etToken_ = consumes<std::vector<double> >(etTag_);
   etaToken_ = consumes<std::vector<double> >(etaTag_); 
   massToken_ = consumes<std::vector<double> >(massTag_); 
   SDmassToken_ = consumes<std::vector<double> >(SDmassTag_); 
   tau32Token_ = consumes<std::vector<double> >(tau32Tag_); 
   tau21Token_ = consumes<std::vector<double> >(tau21Tag_); 
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

   reader->BookMVA("top", "TMVAClassification_MLPBFGS.weights.xml");
   reader->BookMVA("W", "TMVAClassification_W_MLPBFGS.weights.xml");
   reader->BookMVA("Z", "TMVAClassification_Z_MLPBFGS.weights.xml");
   reader->BookMVA("H", "TMVAClassification_H_MLPBFGS.weights.xml");




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
Handle< std::vector<double> >    fwm0Handle;
Handle< std::vector<double> >    fwm1Handle;
Handle< std::vector<double> >    fwm2Handle;
Handle< std::vector<double> >    fwm3Handle;
Handle< std::vector<double> >    fwm4Handle;
Handle< std::vector<double> >    NjetstopHandle;
Handle< std::vector<double> >    NjetsWHandle;
Handle< std::vector<double> >    NjetsZHandle;
Handle< std::vector<double> >    NjetsHHandle;
Handle< std::vector<double> >    NjetsjetHandle;
Handle< std::vector<double> >    sumPztopHandle;
Handle< std::vector<double> >    sumPzWHandle;
Handle< std::vector<double> >    sumPzZHandle;
Handle< std::vector<double> >    sumPzHHandle;
Handle< std::vector<double> >    sumPzjetHandle;
Handle< std::vector<double> >    sumPtopHandle;
Handle< std::vector<double> >    sumPWHandle;
Handle< std::vector<double> >    sumPZHandle;
Handle< std::vector<double> >    sumPHHandle;
Handle< std::vector<double> >    sumPjetHandle;
Handle< std::vector<double> >    FWmoment1topHandle;
Handle< std::vector<double> >    FWmoment2topHandle;
Handle< std::vector<double> >    FWmoment3topHandle;
Handle< std::vector<double> >    FWmoment4topHandle;
Handle< std::vector<double> >    isotropytopHandle;
Handle< std::vector<double> >    sphericitytopHandle;
Handle< std::vector<double> >    aplanaritytopHandle;
Handle< std::vector<double> >    thrusttopHandle;
Handle< std::vector<double> >    FWmoment1WHandle;
Handle< std::vector<double> >    FWmoment2WHandle;
Handle< std::vector<double> >    FWmoment3WHandle;
Handle< std::vector<double> >    FWmoment4WHandle;
Handle< std::vector<double> >    isotropyWHandle;
Handle< std::vector<double> >    sphericityWHandle;
Handle< std::vector<double> >    aplanarityWHandle;
Handle< std::vector<double> >    thrustWHandle;
Handle< std::vector<double> >    FWmoment1ZHandle;
Handle< std::vector<double> >    FWmoment2ZHandle;
Handle< std::vector<double> >    FWmoment3ZHandle;
Handle< std::vector<double> >    FWmoment4ZHandle;
Handle< std::vector<double> >    isotropyZHandle;
Handle< std::vector<double> >    sphericityZHandle;
Handle< std::vector<double> >    aplanarityZHandle;
Handle< std::vector<double> >    thrustZHandle;
Handle< std::vector<double> >    FWmoment1HHandle;
Handle< std::vector<double> >    FWmoment2HHandle;
Handle< std::vector<double> >    FWmoment3HHandle;
Handle< std::vector<double> >    FWmoment4HHandle;
Handle< std::vector<double> >    isotropyHHandle;
Handle< std::vector<double> >    sphericityHHandle;
Handle< std::vector<double> >    aplanarityHHandle;
Handle< std::vector<double> >    thrustHHandle;
Handle< std::vector<double> >    etHandle;
Handle< std::vector<double> >    etaHandle;
Handle< std::vector<double> >    massHandle;
Handle< std::vector<double> >    SDmassHandle;
Handle< std::vector<double> >    tau32Handle;
Handle< std::vector<double> >    tau21Handle;

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


cout << etHandle->size() << endl;
double NNout1, NNout2, NNout3, NNout4;

for (size_t i = 0; i < etHandle->size(); i++){


    treeVars["PzOverP_top"]       = float ( sumPztopHandle->at(i) / (sumPtopHandle->at(i) + 0.0001) );
    treeVars["PzOverP_Z"]         = float ( sumPzZHandle->at(i) / (sumPZHandle->at(i) + 0.0001) );
    treeVars["PzOverP_W"]         = float ( sumPzWHandle->at(i) / (sumPWHandle->at(i) + 0.0001) );
    treeVars["PzOverP_H"]         = float ( sumPzHHandle->at(i) / (sumPHHandle->at(i) + 0.0001) );
    treeVars["h1_top"]            = float ( FWmoment1topHandle->at(i) );
    treeVars["h2_top"]            = float ( FWmoment2topHandle->at(i) );
    treeVars["h3_top"]            = float ( FWmoment3topHandle->at(i) );
    treeVars["h4_top"]            = float ( FWmoment4topHandle->at(i) );
    treeVars["isotropy_top"]      = float ( isotropytopHandle->at(i) );
    treeVars["spericity_top"]     = float ( sphericitytopHandle->at(i) );
    treeVars["aplanarity_top"]    = float ( aplanaritytopHandle->at(i) );
    treeVars["aplanarity_top"]    = float ( thrusttopHandle->at(i) );
    treeVars["h1_W"]              = float ( FWmoment1WHandle->at(i) );
    treeVars["h2_W"]              = float ( FWmoment2WHandle->at(i) );
    treeVars["h3_W"]              = float ( FWmoment3WHandle->at(i) );
    treeVars["h4_W"]              = float ( FWmoment4WHandle->at(i) );
    treeVars["isotropy_W"]        = float ( isotropyWHandle->at(i) );
    treeVars["spericity_W"]       = float ( sphericityWHandle->at(i) );
    treeVars["aplanarity_W"]      = float ( aplanarityWHandle->at(i) );
    treeVars["aplanarity_W"]      = float ( thrustWHandle->at(i) );
    treeVars["h1_Z"]              = float ( FWmoment1ZHandle->at(i) );
    treeVars["h2_Z"]              = float ( FWmoment2ZHandle->at(i) );
    treeVars["h3_Z"]              = float ( FWmoment3ZHandle->at(i) );
    treeVars["h4_Z"]              = float ( FWmoment4ZHandle->at(i) );
    treeVars["isotropy_Z"]        = float ( isotropyZHandle->at(i) );
    treeVars["spericity_Z"]       = float ( sphericityZHandle->at(i) );
    treeVars["aplanarity_Z"]      = float ( aplanarityZHandle->at(i) );
    treeVars["aplanarity_Z"]      = float ( thrustZHandle->at(i) );
    treeVars["h1_H"]              = float ( FWmoment1HHandle->at(i) );
    treeVars["h2_H"]              = float ( FWmoment2HHandle->at(i) );
    treeVars["h3_H"]              = float ( FWmoment3HHandle->at(i) );
    treeVars["h4_H"]              = float ( FWmoment4HHandle->at(i) );
    treeVars["isotropy_H"]        = float ( isotropyHHandle->at(i) );
    treeVars["spericity_H"]       = float ( sphericityHHandle->at(i) );
    treeVars["aplanarity_H"]      = float ( aplanarityHHandle->at(i) );
    treeVars["aplanarity_H"]      = float ( thrustHHandle->at(i) );
    treeVars["et"]                = float ( etHandle->at(i) );
    treeVars["eta"]               = float ( etaHandle->at(i) );
    treeVars["SDmass"]            = float ( SDmassHandle->at(i) );
    treeVars["tau32"]             = float ( tau32Handle->at(i) );
    treeVars["tau21"]             = float ( tau21Handle->at(i) );
    

cout <<     treeVars["PzOverP_top"] <<" " <<
    treeVars["PzOverP_Z"]         <<" " <<
    treeVars["PzOverP_W"]        <<" " <<
    treeVars["PzOverP_H"]        <<" " <<
    treeVars["h1_top"]          <<" " <<
    treeVars["h2_top"]            <<" " <<
    treeVars["h3_top"]            <<" " <<
    treeVars["h4_top"]            <<" " <<
    treeVars["isotropy_top"]     <<" " <<
    treeVars["spericity_top"]      <<" " <<
    treeVars["aplanarity_top"]     <<" " <<
    treeVars["aplanarity_top"]    <<" " <<
    treeVars["h1_W"]              <<" " <<
    treeVars["h2_W"]              <<" " <<
    treeVars["h3_W"]              <<" " <<
    treeVars["h4_W"]              <<" " <<
    treeVars["isotropy_W"]        <<" " <<
    treeVars["spericity_W"]       <<" " <<
    treeVars["aplanarity_W"]      <<" " <<
    treeVars["aplanarity_W"]      <<" " <<
    treeVars["h1_Z"]              <<" " <<
    treeVars["h2_Z"]              <<" " <<
    treeVars["h3_Z"]              <<" " <<
    treeVars["h4_Z"]              <<" " <<
    treeVars["isotropy_Z"]        <<" " <<
    treeVars["spericity_Z"]       <<" " <<
    treeVars["aplanarity_Z"]      <<" " <<
    treeVars["aplanarity_Z"]      <<" " <<
    treeVars["h1_H"]              <<" " <<
    treeVars["h2_H"]              <<" " <<
    treeVars["h3_H"]              <<" " <<
    treeVars["h4_H"]              <<" " <<
    treeVars["isotropy_H"]        <<" " <<
    treeVars["spericity_H"]       <<" " <<
    treeVars["aplanarity_H"]      <<" " <<
    treeVars["aplanarity_H"]      <<" " <<
    treeVars["et"]                <<" " <<
    treeVars["eta"]               <<" " <<
    treeVars["SDmass"]            <<" " <<
    treeVars["tau32"]             <<" " <<
    treeVars["tau21"]             <<endl;


				
    NNout1 = (reader->EvaluateRegression( "top" ))[0];
    NNout2 = (reader->EvaluateRegression( "W" ))[0];
    NNout3 = (reader->EvaluateRegression( "Z" ))[0];
    NNout4 = (reader->EvaluateRegression( "H" ))[0];

    cout << NNout1 << " " << NNout2 << " " << NNout3 << " " << NNout4 << endl;

}

 









/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
 
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
