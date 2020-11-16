from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'CSCEff13'
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'create_ntuple_crab.py'
config.JobType.maxMemoryMB = 2500 
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = '/SingleMuon/Run2018B-ZMu-PromptReco-v2/RAW-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1 
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/Era/Prompt/Cert_316998-319312_13TeV_PromptReco_Collisions18_JSON_eraB.txt'
config.Data.runRange = '316998-319312' # '322348-322355 320394-325273'
config.Data.publication = True
config.Data.outputDatasetTag = 'CSCEff_20200610'

config.Site.whitelist = ['T2_TR_METU']
config.Site.ignoreGlobalBlacklist = True
config.Site.storageSite = 'T2_US_Wisconsin' 
