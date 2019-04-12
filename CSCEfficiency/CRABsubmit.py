from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = '2018D_HV_after'
config.General.workArea = 'crab_tests'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'test2.py'

config.Data.inputDataset = '/SingleMuon/Run2018D-ZMu-PromptReco-v2/RAW-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.lumiMask = 'json.txt'
config.Data.runRange = '324077-325175' 
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
config.Data.outputDatasetTag = 'afterHV'

config.Site.storageSite = 'T2_US_Wisconsin'
