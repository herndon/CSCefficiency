from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = '2018D_small_memory_test_SMC_2'
config.General.workArea = 'crab_tests'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'create_ntuple.py'

config.Data.inputDataset = '/SingleMuon/Run2018D-ZMu-PromptReco-v2/RAW-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 15
#config.Data.splitting = 'Automatic'
config.Data.lumiMask = 'full_json.txt'
#config.Data.runRange = '324077-325175' #after 2018D HV change
config.Data.runRange = '325170-325175'
#config.Data.runRange = '320500-325175' #all 2018D
config.Data.outLFNDirBase = '/store/user/%s/CRAB_dirs/' % (getUsernameFromSiteDB())
config.Data.publication = True
config.Data.outputDatasetTag = '2018D_small_memory_test_SMC_2'

config.Site.storageSite = 'T2_US_Wisconsin'
