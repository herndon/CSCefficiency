from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'CSCEffC1'
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'create_ntuple_crab.py'
config.JobType.maxMemoryMB = 2500 
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = '/SingleMuon/Run2018C-ZMu-PromptReco-v2/RAW-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 4 
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/Era/Prompt/Cert_319313-320393_13TeV_PromptReco_Collisions18_JSON_eraC.txt'
config.Data.runRange = '319313-320393' # '322348-322355 320394-325273'
config.Data.publication = True
config.Data.outputDatasetTag = 'CSCEff_20200731'

config.Site.storageSite = 'T2_US_Wisconsin' 
