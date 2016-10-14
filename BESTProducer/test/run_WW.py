import FWCore.ParameterSet.Config as cms

process = cms.Process("run")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(

	'root://cms-xrd-global.cern.ch//store/mc/RunIISpring16MiniAODv2/ZprimeToWW_narrow_M-3000_13TeV-madgraph/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14-v1/10000/6E0E95F5-993A-E611-B413-3417EBE51CDF.root'

	)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.run = cms.EDProducer('BESTProducer',
	pdgIDforMatch = cms.int32(24),
	NNtargetX = cms.int32(-1),
	NNtargetY = cms.int32(1),
	isMC = cms.int32(1)
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("histo_WW.root") )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string("ana_out.root"),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_*run*_*_*'
                                                                      #, 'keep *_goodPatJetsCATopTagPF_*_*'
                                                                      #, 'keep recoPFJets_*_*_*'
                                                                      ) 
                               )
process.outpath = cms.EndPath(process.out)

process.p = cms.Path(process.run)
