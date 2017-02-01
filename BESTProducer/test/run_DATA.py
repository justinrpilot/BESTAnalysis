import FWCore.ParameterSet.Config as cms

process = cms.Process("run")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(


	'root://cms-xrd-global.cern.ch//store/data/Run2016B/JetHT/MINIAOD/01Jul2016-v1/00000/085E58F6-A544-E611-BB10-00A0D1EC7FB8.root'

	)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.run = cms.EDProducer('BESTProducer',
	pdgIDforMatch = cms.int32(24),
	NNtargetX = cms.int32(0),
	NNtargetY = cms.int32(1),
	isMC = cms.int32(0)
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("histo_DATA.root") )

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
