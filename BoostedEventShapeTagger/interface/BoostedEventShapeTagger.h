#ifndef BOOSTEDEVENTSHAPETAGGER_H
#define BOOSTEDEVENTSHAPETAGGER_H

#include <fstream>

// FASTJET
#include <fastjet/JetDefinition.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/tools/Filter.hh>
#include <fastjet/ClusterSequence.hh>
#include <fastjet/GhostedAreaSpec.hh>
#include <fastjet/ClusterSequenceArea.hh>

// CMS
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "PhysicsTools/CandUtils/interface/EventShapeVariables.h"
#include "PhysicsTools/CandUtils/interface/Thrust.h"

// ROOT
#include "TLorentzRotation.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TLorentzVector.h"
#include "TFile.h"


// BoostedEventShapeTagger Class
class BoostedEventShapeTagger {

  public:

    BoostedEventShapeTagger(const std::string& configFile);
    ~BoostedEventShapeTagger();

    std::vector<float> execute( const pat::Jet& jet );

    void getJetValues( const pat::Jet& jet );
    void pboost( TVector3 pbeam, TVector3 plab, TLorentzVector &pboo );

    int FWMoments( std::vector<TLorentzVector> particles, double (&outputs)[5] );
    float LegP(float x, int order);

    unsigned int getParticleID();

    void setConfigurations(const std::vector<std::string>& configurations);
    void read_file( const std::string &file_name, std::vector<std::string> &values, const std::string &comment="#" );
    bool str2bool( const std::string value );

  protected:

    // TMVA
    TMVA::Reader *m_reader;
    std::vector<std::string> m_listOfVars;
    std::map<std::string, float> m_BESTvars;
    std::vector<float> m_NNresults;
    std::string m_TMVAName;
    std::string m_xmlFile;
    std::string m_TMVAVariables;

    std::map<std::string,std::string> m_configurations; // map of configurations

    // kinematics
    bool m_applyKinematicCuts;  // restrict jets to meet certain kinematic thresholds
    float m_jetSoftDropMassMin; // [GeV] Jet soft drop mass minimum
    float m_jetPtMin;           // [GeV] Jet pT minimum

    // boosting to rest frames
    float m_radiusSmall;        // re-clustering jets
    float m_radiusLarge;        // re-clustering jets
    float m_reclusterJetPtMin;  // [GeV] re-clustering jet pT minimum

    float m_Wmass = 80.4;       // W mass [GeV]
    float m_Zmass = 91.2;       // Z mass
    float m_Hmass = 125.;       // Higgs mass
    float m_Tmass = 172.5;      // Top mass

    std::map<std::string,std::string> m_defaultConfigs = {
             {"TMVAName",            "fived"},
             {"xmlFile",             "BESTAnalysis/BoostedEventShapeTagger/data/TMVARegression_MLP.weights.xml"},
             {"TMVAVariables",       "Analysis/B2GTTrees/data/BESTvariables.txt"},
             {"applyKinematicCuts",  "true"},
             {"radiusSmall",         "0.4"},
             {"radiusLarge",         "0.8"},
             {"reclusterJetPtMin",   "30.0"},
             {"jetSoftDropMassMin",  "40.0"},
             {"jetPtMin",            "500.0"} };
};

#endif
