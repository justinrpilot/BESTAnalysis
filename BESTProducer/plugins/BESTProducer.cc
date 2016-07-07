// -*- C++ -*-
//
// Package:    Analysis/BESTProducer
// Class:      BESTProducer
// 
/**\class BESTProducer BESTProducer.cc Analysis/BESTProducer/plugins/BESTProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  justin pilot
//         Created:  Thu, 07 Jul 2016 11:41:53 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "PhysicsTools/CandUtils/interface/EventShapeVariables.h"
#include "PhysicsTools/CandUtils/interface/Thrust.h"
#include <fastjet/JetDefinition.hh>
#include <fastjet/PseudoJet.hh>
#include "fastjet/tools/Filter.hh"
#include <fastjet/ClusterSequence.hh>
#include <fastjet/ActiveAreaSpec.hh>
#include <fastjet/ClusterSequenceArea.hh>

#include "TH2F.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TCanvas.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"


//
// class declaration
//

class BESTProducer : public edm::stream::EDProducer<> {
   public:
      explicit BESTProducer(const edm::ParameterSet&);
      ~BESTProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;
      float LegP(float x, int order);
      int FWMoments( std::vector<TLorentzVector> particles, double (&outputs)[5] );

	TFile *outfile;
      TH2F *h_preBoostJet;
      TH2F *h_postBoostJet;
      TTree *jetTree;


      TMVA::Reader *reader = new TMVA::Reader();

      std::map<std::string, float> treeVars;
      std::vector<std::string> listOfVars;

        int count;

      int pdgIDSrc_;
        int NNtargetX_;
        int NNtargetY_;
   
	edm::EDGetTokenT<std::vector<pat::PackedCandidate> > pfCandsToken_;
	edm::EDGetTokenT<std::vector<pat::Jet> > ak8JetsToken_;
	edm::EDGetTokenT<std::vector<reco::GenParticle> > genPartToken_;






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
BESTProducer::BESTProducer(const edm::ParameterSet& iConfig):
   pdgIDSrc_  (iConfig.getParameter<int>("pdgIDforMatch")),
   NNtargetX_  (iConfig.getParameter<int>("NNtargetX")),
   NNtargetY_  (iConfig.getParameter<int>("NNtargetY"))
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
  produces<std::vector<double > >("FWmoment0");
   produces<std::vector<double > >("FWmoment1");
   produces<std::vector<double > >("FWmoment2");
   produces<std::vector<double > >("FWmoment3");
   produces<std::vector<double > >("FWmoment4");

   edm::Service<TFileService> fs;
   h_preBoostJet = fs->make<TH2F>("h_preBoostJet", "h_preBoostJet", 50, -3, 3, 50, -3.5, 3.5);
   h_postBoostJet = fs->make<TH2F>("h_postBoostJet", "h_postBoostJet", 50, -3, 3, 50, -3.5, 3.5);
   count = 0;
   outfile = new TFile("jetPictures.root", "RECREATE"); 
   outfile->cd();
   

   jetTree = fs->make<TTree>("jetTree", "jetTree");


   listOfVars.push_back("et"); 
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
   listOfVars.push_back("Njets_jet");
   listOfVars.push_back("Njets_orig");

for (unsigned i = 0; i < listOfVars.size(); i++){

        treeVars[ listOfVars[i] ] = -999.99;

        jetTree->Branch( (listOfVars[i]).c_str() , &(treeVars[ listOfVars[i] ]), (listOfVars[i]+"/F").c_str() );

   }

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
   reader->AddSpectator( "targetX", &treeVars[ "targetX" ]);
   reader->AddSpectator( "targetY", &treeVars[ "targetY" ]);

   reader->BookMVA( "MLP method", "TMVARegression_MLP.weights.xml");
 


   edm::InputTag pfCandsTag_("packedPFCandidates", "", "PAT");
   edm::InputTag ak8JetsTag_("slimmedJetsAK8", "", "PAT");
   edm::InputTag genPartTag_("prunedGenParticles", "", "PAT");
   pfCandsToken_ = consumes<std::vector<pat::PackedCandidate> >(pfCandsTag_);
   ak8JetsToken_ = consumes<std::vector<pat::Jet> >(ak8JetsTag_);
   genPartToken_ = consumes<std::vector<reco::GenParticle> >(genPartTag_);


}


BESTProducer::~BESTProducer()
{
   outfile->Write();
   outfile->Close(); 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
BESTProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   using namespace std;
   using namespace fastjet;
 
   typedef reco::Candidate::PolarLorentzVector fourv;



   std::auto_ptr< std::vector<double > > fw_moments_0( new std::vector<double>() );
   std::auto_ptr< std::vector<double > > fw_moments_1( new std::vector<double>() );
   std::auto_ptr< std::vector<double > > fw_moments_2( new std::vector<double>() );
   std::auto_ptr< std::vector<double > > fw_moments_3( new std::vector<double>() );
   std::auto_ptr< std::vector<double > > fw_moments_4( new std::vector<double>() );


   Handle< std::vector<pat::PackedCandidate> > pfCands;
   iEvent.getByToken(pfCandsToken_, pfCands);

   Handle< std::vector<pat::Jet> > ak8Jets;
   iEvent.getByToken(ak8JetsToken_, ak8Jets);

   Handle< std::vector<reco::GenParticle> > genParticles;
   iEvent.getByToken(genPartToken_, genParticles);

   std::vector<TLorentzVector> genTops;

   for (std::vector<reco::GenParticle>::const_iterator pBegin = genParticles->begin(), pEnd = genParticles->end(), ipart = pBegin; ipart != pEnd; ++ipart){

	if (abs(ipart->pdgId()) == pdgIDSrc_ && ipart->status() < 30 && ipart->pt() > 0.2) {
	
   		genTops.push_back( TLorentzVector(ipart->px(), ipart->py(), ipart->pz(), ipart->energy()) );
	}


   }



   int nJets = 0;

   for (std::vector<pat::Jet>::const_iterator jetBegin = ak8Jets->begin(), jetEnd = ak8Jets->end(), ijet = jetBegin; ijet != jetEnd; ++ijet){

	bool match = false;
	for (size_t i = 0; i < genTops.size(); i++){

		TLorentzVector thisjetLV(ijet->px(), ijet->py(), ijet->pz(), ijet->energy());
		if (thisjetLV.DeltaR(genTops[i]) < 0.2) match = true;
	}


	nJets++;
	if (!match) continue;
	if (ijet->pt() < 400) continue;


	count++;


	fourv thisJet = ijet->polarP4();
	

	treeVars["et"] = thisJet.Et();

	treeVars["targetX"] = NNtargetX_;
	treeVars["targetY"] = NNtargetY_;

	TLorentzVector thisJetLV(0.,0.,0.,0.);
	TLorentzVector thisJetLV_W(0.,0.,0.,0.);
	TLorentzVector thisJetLV_Z(0.,0.,0.,0.);
	TLorentzVector thisJetLV_H(0.,0.,0.,0.);
	TLorentzVector thisJetLV_top(0.,0.,0.,0.);
	thisJetLV.SetXYZM(thisJet.X(), thisJet.Y(), thisJet.Z(), thisJet.M() );
	thisJetLV_W.SetXYZM(thisJet.X(), thisJet.Y(), thisJet.Z(), 80.4 );
	thisJetLV_Z.SetXYZM(thisJet.X(), thisJet.Y(), thisJet.Z(), 91.2 );
	thisJetLV_H.SetXYZM(thisJet.X(), thisJet.Y(), thisJet.Z(), 125. );
	thisJetLV_top.SetXYZM(thisJet.X(), thisJet.Y(), thisJet.Z(), 172.5 );


	

	//thisJetLV.Boost(-thisJetLV.BoostVector() );

	

	h_preBoostJet->Reset();
	h_postBoostJet->Reset();

	
	std::vector<TLorentzVector> particles_jet;
	std::vector<TLorentzVector> particles_top;
	std::vector<TLorentzVector> particles_W;
	std::vector<TLorentzVector> particles_Z;
	std::vector<TLorentzVector> particles_H;

	std::vector<math::XYZVector> particles2_jet;
	std::vector<math::XYZVector> particles2_top;
	std::vector<math::XYZVector> particles2_W;
	std::vector<math::XYZVector> particles2_Z;
	std::vector<math::XYZVector> particles2_H;

	std::vector<reco::LeafCandidate> particles3_jet;
	std::vector<reco::LeafCandidate> particles3_top;
	std::vector<reco::LeafCandidate> particles3_W;
	std::vector<reco::LeafCandidate> particles3_Z;
	std::vector<reco::LeafCandidate> particles3_H;


	vector<fastjet::PseudoJet> topFJparticles;
	vector<fastjet::PseudoJet> topFJparticles_noBoost;
	
	vector<fastjet::PseudoJet> jetFJparticles;
	vector<fastjet::PseudoJet> jetFJparticles_noBoost;

	
	for(unsigned int i = 0; i < ijet->numberOfDaughters(); i++){




		if (ijet->daughter(i)->pt() < 0.05) continue;

		TLorentzVector thisParticleLV_jet( ijet->daughter(i)->px(), ijet->daughter(i)->py(), ijet->daughter(i)->pz(), ijet->daughter(i)->energy() );		
		TLorentzVector thisParticleLV_top( ijet->daughter(i)->px(), ijet->daughter(i)->py(), ijet->daughter(i)->pz(), ijet->daughter(i)->energy() );		
		TLorentzVector thisParticleLV_W( ijet->daughter(i)->px(), ijet->daughter(i)->py(), ijet->daughter(i)->pz(), ijet->daughter(i)->energy() );		
		TLorentzVector thisParticleLV_Z( ijet->daughter(i)->px(), ijet->daughter(i)->py(), ijet->daughter(i)->pz(), ijet->daughter(i)->energy() );		
		TLorentzVector thisParticleLV_H( ijet->daughter(i)->px(), ijet->daughter(i)->py(), ijet->daughter(i)->pz(), ijet->daughter(i)->energy() );		


		h_preBoostJet->Fill(thisParticleLV_jet.Eta(), thisParticleLV_jet.Phi(), thisParticleLV_jet.E());

		
		topFJparticles_noBoost.push_back( PseudoJet( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z(), thisParticleLV_top.T() ) );
		jetFJparticles_noBoost.push_back( PseudoJet( thisParticleLV_jet.X(), thisParticleLV_jet.Y(), thisParticleLV_jet.Z(), thisParticleLV_jet.T() ) );
	


		thisParticleLV_jet.Boost( -thisJetLV.BoostVector() );
		thisParticleLV_Z.Boost( -thisJetLV_Z.BoostVector() );
		thisParticleLV_W.Boost( -thisJetLV_W.BoostVector() );
		thisParticleLV_H.Boost( -thisJetLV_H.BoostVector() );
		thisParticleLV_top.Boost( -thisJetLV_top.BoostVector() );

		
		particles_jet.push_back( thisParticleLV_jet );
		particles_top.push_back( thisParticleLV_top );
		particles_W.push_back( thisParticleLV_W );
		particles_Z.push_back( thisParticleLV_Z );
		particles_H.push_back( thisParticleLV_H );


		topFJparticles.push_back( PseudoJet( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z(), thisParticleLV_top.T() ) );
		jetFJparticles.push_back( PseudoJet( thisParticleLV_jet.X(), thisParticleLV_jet.Y(), thisParticleLV_jet.Z(), thisParticleLV_jet.T() ) );



		particles2_top.push_back( math::XYZVector( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z() ));
		particles3_top.push_back( reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z(), thisParticleLV_top.T()     ) ));
		particles2_W.push_back( math::XYZVector( thisParticleLV_W.X(), thisParticleLV_W.Y(), thisParticleLV_W.Z() ));
		particles3_W.push_back( reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_W.X(), thisParticleLV_W.Y(), thisParticleLV_W.Z(), thisParticleLV_W.T()     ) ));
		particles2_Z.push_back( math::XYZVector( thisParticleLV_Z.X(), thisParticleLV_Z.Y(), thisParticleLV_Z.Z() ));
		particles3_Z.push_back( reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_Z.X(), thisParticleLV_Z.Y(), thisParticleLV_Z.Z(), thisParticleLV_Z.T()     ) ));
		particles2_H.push_back( math::XYZVector( thisParticleLV_H.X(), thisParticleLV_H.Y(), thisParticleLV_H.Z() ));
		particles3_H.push_back( reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_H.X(), thisParticleLV_H.Y(), thisParticleLV_H.Z(), thisParticleLV_H.T()     ) ));

		
		h_postBoostJet->Fill(thisParticleLV_jet.Eta(), thisParticleLV_jet.Phi(), thisParticleLV_jet.E() );
		


	}

	outfile->cd();
	h_preBoostJet->Write(Form("pre_%d", count));
	h_postBoostJet->Write(Form("post_%d", count));



	double fwm[5] = { 0.0, 0.0 ,0.0 ,0.0,0.0};
	double fwm_W[5] = { 0.0, 0.0 ,0.0 ,0.0,0.0};
	double fwm_top[5] = { 0.0, 0.0 ,0.0 ,0.0,0.0};
	double fwm_Z[5] = { 0.0, 0.0 ,0.0 ,0.0,0.0};
	double fwm_H[5] = { 0.0, 0.0 ,0.0 ,0.0,0.0};
	FWMoments( particles_W, fwm_W);
	FWMoments( particles_jet, fwm);
	FWMoments( particles_top, fwm_top);
	FWMoments( particles_Z, fwm_Z);
	FWMoments( particles_H, fwm_H);

	EventShapeVariables eventShapes_top( particles2_top );
	EventShapeVariables eventShapes_W( particles2_W );
	EventShapeVariables eventShapes_Z( particles2_Z );
	EventShapeVariables eventShapes_H( particles2_H );
	Thrust thrustCalculator_top( particles3_top.begin(), particles3_top.end() );
	Thrust thrustCalculator_W( particles3_W.begin(), particles3_W.end() );
	Thrust thrustCalculator_Z( particles3_Z.begin(), particles3_Z.end() );
	Thrust thrustCalculator_H( particles3_H.begin(), particles3_H.end() );


	double R = 0.4;
        JetDefinition jet_def(antikt_algorithm, R);
        JetDefinition jet_def2(antikt_algorithm, 2*R);

	ClusterSequence cs(topFJparticles, jet_def);
	ClusterSequence cs_jet(jetFJparticles, jet_def);
	ClusterSequence cs_noBoost(topFJparticles_noBoost, jet_def2);
        
	vector<PseudoJet> jetsFJ = cs.inclusive_jets(30.0);
	vector<PseudoJet> jetsFJ_jet = cs_jet.inclusive_jets(30.0);
	vector<PseudoJet> jetsFJ_noBoost = cs_noBoost.inclusive_jets(30.0);
	treeVars["Njets_top"] = jetsFJ.size();
	treeVars["Njets_jet"] = jetsFJ_jet.size();
	treeVars["Njets_orig"] = jetsFJ_noBoost.size();

	fw_moments_0->push_back(fwm[0]);	
	fw_moments_1->push_back(fwm[1]);	
	fw_moments_2->push_back(fwm[2]);	
	fw_moments_3->push_back(fwm[3]);	
	fw_moments_4->push_back(fwm[4]);	

	treeVars["h1_top"] = fwm_top[1];
	treeVars["h2_top"] = fwm_top[2];
	treeVars["h3_top"] = fwm_top[3];
	treeVars["h4_top"] = fwm_top[4];
	treeVars["isotropy_top"] = eventShapes_top.isotropy(); 
	treeVars["sphericity_top"] = eventShapes_top.sphericity(2);
	treeVars["aplanarity_top"] = eventShapes_top.aplanarity(2);
	treeVars["thrust_top"] = thrustCalculator_top.thrust();
	treeVars["h1_W"] = fwm_W[1];
	treeVars["h2_W"] = fwm_W[2];
	treeVars["h3_W"] = fwm_W[3];
	treeVars["h4_W"] = fwm_W[4];
	treeVars["isotropy_W"] = eventShapes_W.isotropy(); 
	treeVars["sphericity_W"] = eventShapes_W.sphericity(2);
	treeVars["aplanarity_W"] = eventShapes_W.aplanarity(2);
	treeVars["thrust_W"] = thrustCalculator_W.thrust();
	treeVars["h1_Z"] = fwm_Z[1];
	treeVars["h2_Z"] = fwm_Z[2];
	treeVars["h3_Z"] = fwm_Z[3];
	treeVars["h4_Z"] = fwm_Z[4];
	treeVars["isotropy_Z"] = eventShapes_Z.isotropy(); 
	treeVars["sphericity_Z"] = eventShapes_Z.sphericity(2);
	treeVars["aplanarity_Z"] = eventShapes_Z.aplanarity(2);
	treeVars["thrust_Z"] = thrustCalculator_Z.thrust();
	treeVars["h1_H"] = fwm_H[1];
	treeVars["h2_H"] = fwm_H[2];
	treeVars["h3_H"] = fwm_H[3];
	treeVars["h4_H"] = fwm_H[4];
	treeVars["isotropy_H"] = eventShapes_H.isotropy(); 
	treeVars["sphericity_H"] = eventShapes_H.sphericity(2);
	treeVars["aplanarity_H"] = eventShapes_H.aplanarity(2);
	treeVars["thrust_H"] = thrustCalculator_H.thrust();


	treeVars["NNoutX"] = (reader->EvaluateRegression( "MLP method" ))[0];
	treeVars["NNoutY"] = (reader->EvaluateRegression( "MLP method" ))[1];








	jetTree->Fill();

    }//End jet loop




   iEvent.put( fw_moments_0, "FWmoment0");
   iEvent.put( fw_moments_1, "FWmoment1");
   iEvent.put( fw_moments_2, "FWmoment2");
   iEvent.put( fw_moments_3, "FWmoment3");
   iEvent.put( fw_moments_4, "FWmoment4");






}
// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
BESTProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
BESTProducer::endStream() {
}


float BESTProducer::LegP(float x, int order){


if (order == 0) return 1;
else if (order == 1) return x;
else if (order == 2) return 0.5*(3*x*x - 1);
else if (order == 3) return 0.5*(5*x*x*x - 3*x);
else if (order == 4) return 0.125*(35*x*x*x*x - 30*x*x + 3);
else return 0;

}

int BESTProducer::FWMoments( std::vector<TLorentzVector> particles, double (&outputs)[5] ){



	int numParticles = particles.size();



	float s = 0.0;
	for(int i = 0; i < numParticles; i++){

		s += particles[i].E();
	}



	float H0 = 0.0;
	float H4 = 0.0;
	float H3 = 0.0;
	float H2 = 0.0;
	float H1 = 0.0;

	for (int i = 0; i < numParticles; i++){

		for (int j = i; j < numParticles; j++){

			float costh = ( particles[i].Px() * particles[j].Px() + particles[i].Py() * particles[j].Py() + particles[i].Pz() * particles[j].Pz() ) / ( particles[i].P() * particles[j].P() );
			float w1 = particles[i].P();
			float w2 = particles[j].P();

			float fw0 = LegP(costh, 0);
			float fw1 = LegP(costh, 1);
			float fw2 = LegP(costh, 2);
			float fw3 = LegP(costh, 3);
			float fw4 = LegP(costh, 4);



			H0 += w1 * w2 * fw0 / (s*s);
			H1 += w1 * w2 * fw1 / (s*s);
			H2 += w1 * w2 * fw2 / (s*s);
			H3 += w1 * w2 * fw3 / (s*s);
			H4 += w1 * w2 * fw4 / (s*s);


		}
	}

	H0 += 0.001;
	outputs[0] = (H0);
	outputs[1] = (H1 / H0);
	outputs[2] = (H2 / H0);
	outputs[3] = (H3 / H0);
	outputs[4] = (H4 / H0);
	

	return 0;
}


// ------------ method called when starting to processes a run  ------------
/*
void
BESTProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
BESTProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
BESTProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
BESTProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BESTProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BESTProducer);
