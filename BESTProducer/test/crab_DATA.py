from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = '2016B_trees'
config.General.workArea = 'NNoutputs'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_DATA.py'
config.JobType.inputFiles = ['TMVARegression_MLP.weights.xml']
config.JobType.outputFiles = ['histo_DATA.root']
config.JobType.allowUndistributedCMSSW = True 

config.section_("Data")
config.Data.inputDataset = '/JetHT/Run2016B-01Jul2016-v1/MINIAOD' 
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 3
config.Data.ignoreLocality = True
config.Data.publication = False
# This string is used to construct the output dataset name

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
