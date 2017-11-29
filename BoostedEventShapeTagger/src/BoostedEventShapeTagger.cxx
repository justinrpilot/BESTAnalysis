/*
Created:        28 November 2017
Last Updated:   28 November 2017

Justin Pilot
UC Davis

Dan Marley
daniel.edison.marley@cernSPAMNOT.ch
Texas A&M University

-----

BoostedEventShapeTagger

Development of standalone BEST package for analyzers.
Based on the framework created by Justin:
  https://github.com/justinrpilot/BESTAnalysis

Requires MiniAOD inputs to access proper set of information

*/
#include "BESTAnalysis/BoostedEventShapeTagger/interface/BoostedEventShapeTagger.h"

// constructor
BoostedEventShapeTagger::BoostedEventShapeTagger(const std::string& configFile) :
  m_TMVAName("SetMe"),
  m_xmlFile("SetMe"),
  m_TMVAVariables("SetMe"),
  m_applyKinematicCuts(true),
  m_jetSoftDropMassMin(0),
  m_jetPtMin(0),
  m_radiusSmall(0),
  m_radiusLarge(0),
  m_reclusterJetPtMin(0){
    // Configuration
    std::vector<std::string> configurations;
    read_file(configFile,configurations);
    setConfigurations(configurations);


    // Basic options
    m_applyKinematicCuts = str2bool(m_configurations.at("applyKinematicCuts"));
    m_jetSoftDropMassMin = std::stof(m_configurations.at("jetSoftDropMassMin"));
    m_jetPtMin           = std::stof(m_configurations.at("jetPtMin"));

    m_radiusSmall        = std::stof(m_configurations.at("radiusSmall"));
    m_radiusLarge        = std::stof(m_configurations.at("radiusLarge"));
    m_reclusterJetPtMin  = std::stof(m_configurations.at("reclusterJetPtMin"));


    // TMVA
    m_TMVAName      = m_configurations.at("TMVAName");
    m_xmlFile       = m_configurations.at("xmlFile");
    m_TMVAVariables = m_configurations.at("TMVAVariables");

    m_BESTvars.clear();                        // map to hold variables and their values
    m_listOfVars.clear();                      // list of variables in NN
    read_file(m_TMVAVariables,m_listOfVars);   // Read file of variables for TMVA

    m_reader = new TMVA::Reader();             // TMVA object to do NN prediction
    m_reader->SetVerbose(1);
    for (const auto& var : m_listOfVars){
        m_BESTvars[var] = -999.;               // Initialize values in map
        m_reader->AddVariable( var, &m_BESTvars[var] );
    }

    m_reader->BookMVA(m_TMVAName,m_xmlFile);
} // end constructor


BoostedEventShapeTagger::~BoostedEventShapeTagger(){
    delete m_reader;
}


std::vector<float> BoostedEventShapeTagger::execute( const pat::Jet& jet ){
    /* Execute TMVA */
    getValues(jet);       // update m_BESTvars
    m_NNresults = m_reader->EvaluateRegression( "fived" );

    return m_NNresults;
}


void BoostedEventShapeTagger::getJetValues( const pat::Jet& jet ){
    /* Grab attributes from the jet and store them in map
    
       Jet requirements:
         pT > 500 GeV
         soft-drop mass > 40 GeV
         >=2 subjets
         >=2 daughters
           daughter->pt() >= 0.05
         m_reclusterJetPtMin = 30 GeV
           transformed jets uses 10 GeV
         maxJets = 4
           sumP, sumPz
    */
    using namespace fastjet;

    // clear the map from the previous jet's values
    m_BESTvars.clear();

    // Cut on jet kinematics: pT & soft-drop mass cut
    if (m_applyKinematicCuts) {
        if ( jet.pt() < m_jetPtMin || jet.userFloat("ak8PFJetsCHSSoftDropMass") < m_jetSoftDropMassMin)
            return;
    }

    // Access the subjets
    auto const& thisSubjets   = jet.subjets();
    unsigned int numDaughters = jet.numberOfDaughters();
    if (thisSubjets.size() < 2) return;
    if (numDaughters < 2) return;


    // b-tagging
    float btagValue1 = thisSubjets.at(0)->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
    float btagValue2 = thisSubjets.at(1)->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");

    // n-subjettiness
    float tau1 = jet.userFloat("NjettinessAK8:tau1");
    float tau2 = jet.userFloat("NjettinessAK8:tau2");
    float tau3 = jet.userFloat("NjettinessAK8:tau3");

    // BEST vars
    fourv thisJet = jet.polarP4();

    // Boost to rest frame
    TLorentzVector thisJetLV;
    TLorentzVector thisJetLV_W;
    TLorentzVector thisJetLV_Z;
    TLorentzVector thisJetLV_H;
    TLorentzVector thisJetLV_top;
    thisJetLV.SetPtEtaPhiM(thisJet.Pt(), thisJet.Eta(), thisJet.Phi(), thisJet.M() );
    thisJetLV_W.SetPtEtaPhiM(thisJet.Pt(),   thisJet.Eta(), thisJet.Phi(), m_Wmass ); // W mass [GeV]
    thisJetLV_Z.SetPtEtaPhiM(thisJet.Pt(),   thisJet.Eta(), thisJet.Phi(), m_Zmass ); // Z mass
    thisJetLV_H.SetPtEtaPhiM(thisJet.Pt(),   thisJet.Eta(), thisJet.Phi(), m_Hmass ); // Higgs mass
    thisJetLV_top.SetPtEtaPhiM(thisJet.Pt(), thisJet.Eta(), thisJet.Phi(), m_Tmass ); // Top mass

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

    std::vector<fastjet::PseudoJet> topFJparticles;
    std::vector<fastjet::PseudoJet> ZFJparticles;
    std::vector<fastjet::PseudoJet> WFJparticles;
    std::vector<fastjet::PseudoJet> HFJparticles;
    std::vector<fastjet::PseudoJet> topFJparticles_noBoost;
    std::vector<fastjet::PseudoJet> jetFJparticles;
    std::vector<fastjet::PseudoJet> jetFJparticles_noBoost;
    std::vector<fastjet::PseudoJet> jetFJparticles_transformed;
    
    TVector3 transformedV;

    // loop over daughters
    auto daus(jet.daughterPtrVector());   // load the daughters
    for (unsigned int ida=0, n=daus.size(); ida<n && ida<=3; ++ida) {

        auto daughter = daus.at(ida);

        if (daughter->pt() < 0.05) continue;

        float dau_px = daughter->px();
        float dau_py = daughter->py();
        float dau_pz = daughter->pz();
        float dau_e  = daughter->energy();

        TLorentzVector thisParticleLV_jet( dau_px,dau_py,dau_pz,dau_e );
        TLorentzVector thisParticleLV_top( dau_px,dau_py,dau_pz,dau_e );
        TLorentzVector thisParticleLV_W(   dau_px,dau_py,dau_pz,dau_e );
        TLorentzVector thisParticleLV_Z(   dau_px,dau_py,dau_pz,dau_e );
        TLorentzVector thisParticleLV_H(   dau_px,dau_py,dau_pz,dau_e );

        topFJparticles_noBoost.push_back( PseudoJet( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z(), thisParticleLV_top.T() ) );
        jetFJparticles_noBoost.push_back( PseudoJet( thisParticleLV_jet.X(), thisParticleLV_jet.Y(), thisParticleLV_jet.Z(), thisParticleLV_jet.T() ) );

        TLorentzVector thisParticleLV_transformed( transformedV.X(), transformedV.Y(), transformedV.Z(), thisParticleLV_jet.E() );

        jetFJparticles_transformed.push_back( PseudoJet( thisParticleLV_transformed.X(), thisParticleLV_transformed.Y(), thisParticleLV_transformed.Z(), thisParticleLV_transformed.T() ) );    

        thisParticleLV_jet.Boost( -thisJetLV.BoostVector() );
        thisParticleLV_Z.Boost(   -thisJetLV_Z.BoostVector() );
        thisParticleLV_W.Boost(   -thisJetLV_W.BoostVector() );
        thisParticleLV_H.Boost(   -thisJetLV_H.BoostVector() );
        thisParticleLV_top.Boost( -thisJetLV_top.BoostVector() );

        pboost( thisJetLV_W.Vect(),   thisParticleLV_W.Vect(), thisParticleLV_W);
        pboost( thisJetLV_Z.Vect(),   thisParticleLV_Z.Vect(), thisParticleLV_Z);
        pboost( thisJetLV_top.Vect(), thisParticleLV_top.Vect(), thisParticleLV_top);
        pboost( thisJetLV_H.Vect(),   thisParticleLV_H.Vect(), thisParticleLV_H);

        particles_jet.push_back( thisParticleLV_jet );
        particles_top.push_back( thisParticleLV_top );
        particles_W.push_back(   thisParticleLV_W );
        particles_Z.push_back(   thisParticleLV_Z );
        particles_H.push_back(   thisParticleLV_H );

        topFJparticles.push_back( PseudoJet( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z(), thisParticleLV_top.T() ) );
        WFJparticles.push_back(   PseudoJet( thisParticleLV_W.X(), thisParticleLV_W.Y(), thisParticleLV_W.Z(), thisParticleLV_W.T() ) );
        ZFJparticles.push_back(   PseudoJet( thisParticleLV_Z.X(), thisParticleLV_Z.Y(), thisParticleLV_Z.Z(), thisParticleLV_Z.T() ) );
        HFJparticles.push_back(   PseudoJet( thisParticleLV_H.X(), thisParticleLV_H.Y(), thisParticleLV_H.Z(), thisParticleLV_H.T() ) );
        jetFJparticles.push_back( PseudoJet( thisParticleLV_jet.X(), thisParticleLV_jet.Y(), thisParticleLV_jet.Z(), thisParticleLV_jet.T() ) );

        particles2_top.push_back( math::XYZVector( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z() ));
        particles3_top.push_back( reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_top.X(), thisParticleLV_top.Y(), thisParticleLV_top.Z(), thisParticleLV_top.T()     ) ));
        particles2_W.push_back(   math::XYZVector( thisParticleLV_W.X(), thisParticleLV_W.Y(), thisParticleLV_W.Z() ));
        particles3_W.push_back(   reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_W.X(), thisParticleLV_W.Y(), thisParticleLV_W.Z(), thisParticleLV_W.T()     ) ));
        particles2_Z.push_back(   math::XYZVector( thisParticleLV_Z.X(), thisParticleLV_Z.Y(), thisParticleLV_Z.Z() ));
        particles3_Z.push_back(   reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_Z.X(), thisParticleLV_Z.Y(), thisParticleLV_Z.Z(), thisParticleLV_Z.T()     ) ));
        particles2_H.push_back(   math::XYZVector( thisParticleLV_H.X(), thisParticleLV_H.Y(), thisParticleLV_H.Z() ));
        particles3_H.push_back(   reco::LeafCandidate(+1, reco::Candidate::LorentzVector( thisParticleLV_H.X(), thisParticleLV_H.Y(), thisParticleLV_H.Z(), thisParticleLV_H.T()     ) ));
    } // end loop over daughters

    // Fox-Wolfram Moments
    double fwm[5]     = {0.0, 0.0 ,0.0 ,0.0, 0.0};
    double fwm_W[5]   = {0.0, 0.0 ,0.0 ,0.0, 0.0};
    double fwm_top[5] = {0.0, 0.0 ,0.0 ,0.0, 0.0};
    double fwm_Z[5]   = {0.0, 0.0 ,0.0 ,0.0, 0.0};
    double fwm_H[5]   = {0.0, 0.0 ,0.0 ,0.0, 0.0};

    FWMoments( particles_W,   fwm_W);
    FWMoments( particles_jet, fwm);
    FWMoments( particles_top, fwm_top);
    FWMoments( particles_Z,   fwm_Z);
    FWMoments( particles_H,   fwm_H);

    // Event Shapes
    EventShapeVariables eventShapes_top( particles2_top );
    EventShapeVariables eventShapes_W( particles2_W );
    EventShapeVariables eventShapes_Z( particles2_Z );
    EventShapeVariables eventShapes_H( particles2_H );

    // Thrust
    Thrust thrustCalculator_top( particles3_top.begin(), particles3_top.end() );
    Thrust thrustCalculator_W( particles3_W.begin(), particles3_W.end() );
    Thrust thrustCalculator_Z( particles3_Z.begin(), particles3_Z.end() );
    Thrust thrustCalculator_H( particles3_H.begin(), particles3_H.end() );

    // Recluster constituents
    JetDefinition jet_def(antikt_algorithm,  m_radiusSmall);
    JetDefinition jet_def2(antikt_algorithm, m_radiusLarge);

    ClusterSequence cs(    topFJparticles, jet_def);
    ClusterSequence cs_W(  WFJparticles,   jet_def);
    ClusterSequence cs_Z(  ZFJparticles,   jet_def);
    ClusterSequence cs_H(  HFJparticles,   jet_def);
    ClusterSequence cs_jet(jetFJparticles, jet_def);
    ClusterSequence cs_noBoost(topFJparticles_noBoost, jet_def2);

    ClusterSequence cs_transformed(jetFJparticles_transformed, jet_def);

    std::vector<PseudoJet> jetsFJ     = cs.inclusive_jets(m_reclusterJetPtMin);
    std::vector<PseudoJet> jetsFJ_W   = cs_W.inclusive_jets(m_reclusterJetPtMin);
    std::vector<PseudoJet> jetsFJ_Z   = cs_Z.inclusive_jets(m_reclusterJetPtMin);
    std::vector<PseudoJet> jetsFJ_H   = cs_H.inclusive_jets(m_reclusterJetPtMin);
    std::vector<PseudoJet> jetsFJ_jet = cs_jet.inclusive_jets(m_reclusterJetPtMin);
    std::vector<PseudoJet> jetsFJ_noBoost     = cs_noBoost.inclusive_jets(m_reclusterJetPtMin);
    std::vector<PseudoJet> jetsFJ_transformed = cs_transformed.inclusive_jets(10.0);

    // sum of jet pz and p  Indices = top, W, Z, H, j
    float sumP[5]  = {0.0};
    float sumPz[5] = {0.0};
    size_t maxJets = 4;

    // -- top
    for (size_t ii=0,size=std::min(maxJets,jetsFJ.size()); ii<size; ii++){
        sumPz[0] += jetsFJ[ii].pz();
        sumP[0]  += sqrt( jetsFJ[ii].modp2() );
    }

    // -- W jets
    for (size_t ii=0,size=std::min(maxJets,jetsFJ_W.size()); ii<size; ii++){
        sumPz[1] += jetsFJ_W[ii].pz();
        sumP[1]  += sqrt( jetsFJ_W[ii].modp2() );
    }

    // -- Z jets
    for (size_t ii=0,size=std::min(maxJets,jetsFJ_Z.size()); ii<size; ii++){
        sumPz[2] += jetsFJ_Z[ii].pz();
        sumP[2]  += sqrt( jetsFJ_Z[ii].modp2() );
    }

    // -- Higgs jets
    for (size_t ii=0,size=std::min(maxJets,jetsFJ_H.size()); ii<size; ii++){
        sumPz[3] += jetsFJ_H[ii].pz();
        sumP[3]  += sqrt( jetsFJ_H[ii].modp2() );
    }

    // -- jets
    for (size_t ii=0,size=std::min(maxJets,jetsFJ_jet.size()); ii<size; ii++){
        sumPz[4] += jetsFJ_jet[ii].pz();
        sumP[4]  += sqrt( jetsFJ_jet[ii].modp2() );
    }


    // Update the map with new values
    m_BESTvars["bDisc"]   = (btagValue1 > btagValue2) ? btagValue1 : btagValue2;
    m_BESTvars["et"]      = thisJet.Pt();
    m_BESTvars["eta"]     = thisJet.Rapidity();
    m_BESTvars["mass"]    = thisJet.M();
    m_BESTvars["SDmass"]  = jet.userFloat("ak8PFJetsCHSSoftDropMass");
    m_BESTvars["tau32"]   = (tau2 > 1e-8) ? tau3/tau2 : -999.;
    m_BESTvars["tau21"]   = (tau1 > 1e-8) ? tau2/tau1 : -999.;

    std::vector<std::string> jetNames = {"top","W","Z","H","jet"};

    for (unsigned int pp=0; pp<5; pp++){
        std::string jetName = jetNames[pp];

        m_BESTvars["sumPz_"+jetName]   = sumPz[pp];
        m_BESTvars["sumP_"+jetName]    = sumP[pp];
        m_BESTvars["PzOverP_"+jetName] =  ( sumPz[pp] / (sumP[pp] + 0.0001) ); // not used for 'jet'
    }

    m_BESTvars["Njets_top"]  = jetsFJ.size();
    m_BESTvars["Njets_W"]    = jetsFJ_W.size();
    m_BESTvars["Njets_Z"]    = jetsFJ_Z.size();
    m_BESTvars["Njets_H"]    = jetsFJ_H.size();
    m_BESTvars["Njets_jet"]  = jetsFJ_jet.size();
    m_BESTvars["Njets_orig"] = jetsFJ_noBoost.size();

    // -- top values
    m_BESTvars["h1_top"] = fwm_top[1];
    m_BESTvars["h2_top"] = fwm_top[2];
    m_BESTvars["h3_top"] = fwm_top[3];
    m_BESTvars["h4_top"] = fwm_top[4];
    m_BESTvars["isotropy_top"]   = eventShapes_top.isotropy(); 
    m_BESTvars["sphericity_top"] = eventShapes_top.sphericity(2);
    m_BESTvars["aplanarity_top"] = eventShapes_top.aplanarity(2);
    m_BESTvars["thrust_top"]     = thrustCalculator_top.thrust();

    // -- W values
    m_BESTvars["h1_W"] = fwm_W[1];
    m_BESTvars["h2_W"] = fwm_W[2];
    m_BESTvars["h3_W"] = fwm_W[3];
    m_BESTvars["h4_W"] = fwm_W[4];
    m_BESTvars["isotropy_W"]   = eventShapes_W.isotropy(); 
    m_BESTvars["sphericity_W"] = eventShapes_W.sphericity(2);
    m_BESTvars["aplanarity_W"] = eventShapes_W.aplanarity(2);
    m_BESTvars["thrust_W"]     = thrustCalculator_W.thrust();

    // -- Z values
    m_BESTvars["h1_Z"] = fwm_Z[1];
    m_BESTvars["h2_Z"] = fwm_Z[2];
    m_BESTvars["h3_Z"] = fwm_Z[3];
    m_BESTvars["h4_Z"] = fwm_Z[4];
    m_BESTvars["isotropy_Z"]   = eventShapes_Z.isotropy(); 
    m_BESTvars["sphericity_Z"] = eventShapes_Z.sphericity(2);
    m_BESTvars["aplanarity_Z"] = eventShapes_Z.aplanarity(2);
    m_BESTvars["thrust_Z"]     = thrustCalculator_Z.thrust();

    // -- H values
    m_BESTvars["h1_H"] = fwm_H[1];
    m_BESTvars["h2_H"] = fwm_H[2];
    m_BESTvars["h3_H"] = fwm_H[3];
    m_BESTvars["h4_H"] = fwm_H[4];
    m_BESTvars["isotropy_H"]   = eventShapes_H.isotropy(); 
    m_BESTvars["sphericity_H"] = eventShapes_H.sphericity(2);
    m_BESTvars["aplanarity_H"] = eventShapes_H.aplanarity(2);
    m_BESTvars["thrust_H"]     = thrustCalculator_H.thrust();

    return;
}


void BoostedEventShapeTagger::pboost( TVector3 pbeam, TVector3 plab, TLorentzVector &pboo ){
    /* Given jet constituent momentum plab, find momentum relative to
       beam direction pbeam
    */
    double pl = plab.Dot(pbeam);
    pl *= 1 / pbeam.Mag();
    // double pt = sqrt(plab.Mag()*plab.Mag()-pl*pl);

    // set x axis direction along pbeam x (0,0,1)
    TVector3 pbx;
    pbx.SetX(pbeam.Y());
    pbx.SetY(pbeam.X());
    pbx.SetZ(0.0);

    pbx *= 1. / pbx.Mag();

    // set y axis direction along -pbx x pbeam
    TVector3 pby;
    pby = -pbx.Cross(pbeam);
    pby *= 1. / pby.Mag();

    pboo.SetX((plab.Dot(pbx)));
    pboo.SetY((plab.Dot(pby)));
    pboo.SetZ(pl);

    return;
}


int BoostedEventShapeTagger::FWMoments( std::vector<TLorentzVector> particles, double (&outputs)[5] ){
    /* Fox-Wolfram moments */
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

            H0 += w1 * w2 * fw0;
            H1 += w1 * w2 * fw1;
            H2 += w1 * w2 * fw2;
            H3 += w1 * w2 * fw3;
            H4 += w1 * w2 * fw4;
        }
    }

    H0 += 1e-3;              // prevent dividing by 0
    outputs[0] = (H0);
    outputs[1] = (H1 / H0);
    outputs[2] = (H2 / H0);
    outputs[3] = (H3 / H0);
    outputs[4] = (H4 / H0);

    return 0;
}


float BoostedEventShapeTagger::LegP(float x, int order){
    /* Calculation in FWMoments */
    float value(0.0);

    if (order == 0) value = 1;
    else if (order == 1) value = x;
    else if (order == 2) value = 0.5*(3*x*x - 1);
    else if (order == 3) value = 0.5*(5*x*x*x - 3*x);
    else if (order == 4) value = 0.125*(35*x*x*x*x - 30*x*x + 3);
    else value = 0;

    return value;
}


unsigned int BoostedEventShapeTagger::getParticleID(){
    /* Use simple algorithm to get the predicted particle ID
       - Particle ID = Particle Type closest to score 
    */
    float qcdScore   = m_NNresults[0];
    float topScore   = m_NNresults[1];
    float higgsScore = m_NNresults[2];
    float wScore     = m_NNresults[3];
    float zScore     = m_NNresults[4];

    float distToQCD   = std::sqrt( pow(qcdScore-1.0,2) + pow(topScore,2)     + pow(higgsScore,2)     + pow(wScore,2)     + pow(zScore,2)  );
    float distToTOP   = std::sqrt( pow(qcdScore,2)     + pow(topScore-1.0,2) + pow(higgsScore,2)     + pow(wScore,2)     + pow(zScore,2)  );
    float distToHIGGS = std::sqrt( pow(qcdScore,2)     + pow(topScore,2)     + pow(higgsScore-1.0,2) + pow(wScore,2)     + pow(zScore,2)  );
    float distToW     = std::sqrt( pow(qcdScore,2)     + pow(topScore,2)     + pow(higgsScore,2)     + pow(wScore-1.0,2) + pow(zScore,2)  );
    float distToZ     = std::sqrt( pow(qcdScore,2)     + pow(topScore,2)     + pow(higgsScore,2)     + pow(wScore,2)     + pow(zScore-1.0,2));

    std::vector<float> dists{ distToQCD, distToTOP, distToHIGGS, distToW, distToZ};
    std::vector<float>::iterator result = std::min_element(std::begin(dists), std::end(dists));

    unsigned int particleID = std::distance(std::begin(dists), result);

    return particleID;
}


void BoostedEventShapeTagger::setConfigurations(const std::vector<std::string>& configurations){
    /* Set the configuration options */
    m_configurations.clear();
    for (const auto& config : configurations){
        // split config items by space
        std::istringstream cfg(config);
        std::istream_iterator<std::string> start(cfg), stop;
        std::vector<std::string> tokens(start, stop);

        m_configurations.insert( std::pair<std::string,std::string>(tokens.at(0),tokens.at(1)) );
    }

    return;
}


void BoostedEventShapeTagger::read_file( const std::string &file_name, std::vector<std::string> &values, const std::string &comment ) {
    /* Read in a generic file and put it into a vector of strings */
    std::ifstream tmp_name = open_file(file_name);

    // open the file and put the data into a vector
    std::string line("");
    if (tmp_name.is_open()){

        while (std::getline(tmp_name, line)) {
            std::string newstring(line);

            // allow for comments
            std::size_t lineComment = line.find(comment);
            if (lineComment != std::string::npos) newstring = line.substr(0, lineComment);

            // remove all white spaces at the end of the string
            std::size_t space_pos = newstring.rfind(" ");
            while ( space_pos != std::string::npos && space_pos == newstring.size()-1 ) {
                newstring = newstring.substr(0, newstring.rfind(" "));
                space_pos = newstring.rfind(" ");
            }

            // ignore empty lines
            if(newstring.length()==0) continue;

            values.push_back(newstring); // put values into vector
        }

        tmp_name.close();
    }

    return;
}


bool BoostedEventShapeTagger::str2bool( const std::string value ){
    /* Turn string into boolean */
    bool valueBoolean(false);

    if (value.compare("True")==0 || value.compare("true")==0 || value.compare("1")==0){
        valueBoolean = true;
    }
    else{
        valueBoolean = false;
    }

    return valueBoolean;
}


// THE END