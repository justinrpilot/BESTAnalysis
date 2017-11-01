import FWCore.ParameterSet.Config as cms

process = cms.Process("run")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(


	'root://cmsxrootd-site.fnal.gov//store/data/Run2016B/JetHT/MINIAOD/23Sep2016-v3/00000/00144F9E-BA97-E611-A8B0-00259074AE48.root'

	)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.BESTProducer = cms.EDProducer('BESTProducer',
	pdgIDforMatch = cms.int32(24),
	NNtargetX = cms.int32(0),
	NNtargetY = cms.int32(1),
	isMC = cms.int32(0),
	doMatch = cms.int32(0)
)

process.BESTAnalyzer = cms.EDProducer('BESTAnalyzer')

process.TFileService = cms.Service("TFileService", fileName = cms.string("histo_DATA.root") )

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string("ana_out.root"),
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('drop *',
                                                                      'keep *_*BESTProducer*_*_*'
                                                                      #, 'keep *_goodPatJetsCATopTagPF_*_*'
                                                                      #, 'keep recoPFJets_*_*_*'
                                                                      ) 
                               )
process.outpath = cms.EndPath(process.out)

process.p = cms.Path(process.BESTProducer*process.BESTAnalyzer)
