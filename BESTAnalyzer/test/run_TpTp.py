import FWCore.ParameterSet.Config as cms

process = cms.Process("run")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(

	'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/02CE8134-F924-E611-A6E0-002481E0E440.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/10AB5E3F-F924-E611-AB17-842B2B186684.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/2CCEC364-0C25-E611-89C1-1418774105B6.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/326CF71E-4325-E611-BF96-0025905A613C.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/3C6E8016-4325-E611-82BD-0CC47A7FC736.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/4CE21592-F924-E611-AA89-0026B93AA8FF.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/5EE04DE9-FF24-E611-9A2D-90B11C0BB9FC.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/6E6A428B-4225-E611-9CF4-38EAA7A6DCF0.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/82A6F39D-4225-E611-AA09-000F530E4774.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/8ACDCD3D-F924-E611-8AAB-B083FECF8ACE.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/98F9F488-4225-E611-842C-5065F381C251.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/9A85C929-F924-E611-A12D-0CC47A7E6A8A.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/A00C4A2B-F924-E611-BBD5-002481E946EE.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/A6D0643C-F924-E611-8FE2-14187741013C.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/BC882FCA-FF24-E611-9F65-1418774121A1.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/C09D2107-F424-E611-91C8-0025901D4844.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/CA11A6F0-F824-E611-B973-0242AC110003.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/CEBE1769-F924-E611-90E1-549F3525B220.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/D0775D2D-4325-E611-8BC1-0025905A608C.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/D60CC8A0-4225-E611-A4F8-008CFA197DA8.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/DAD24F26-4325-E611-9934-002590E2DD10.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/DE21C5DF-F324-E611-B229-0025901D493E.root',
'/store/mc/RunIISpring16MiniAODv2/TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/60000/FC871439-F924-E611-9BF0-1418774108DF.root'
)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.BESTProducer = cms.EDProducer('BESTProducer',
	pdgIDforMatch = cms.int32(6),
	NNtargetX = cms.int32(1),
	NNtargetY = cms.int32(1),
	isMC = cms.int32(1),
	doMatch = cms.int32(0)

)


process.BESTAnalyzer = cms.EDProducer('BESTAnalyzer')

process.TFileService = cms.Service("TFileService", fileName = cms.string("histo_VLQ_TT.root") )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string("ana_out.root"),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      #'keep *_*run*_*_*'
                                                                      #, 'keep *_goodPatJetsCATopTagPF_*_*'
                                                                      #, 'keep recoPFJets_*_*_*'
                                                                      ) 
                               )
process.outpath = cms.EndPath(process.out)

process.p = cms.Path(process.BESTProducer*process.BESTAnalyzer)
