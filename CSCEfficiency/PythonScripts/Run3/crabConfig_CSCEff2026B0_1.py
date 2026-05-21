from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'CSCEff2026B0_1_1'
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'create_ntuple_crab_Run3Data_2026B_1.py'
config.JobType.maxMemoryMB = 10000 
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 4 

config.Data.inputDataset = '/Muon0/Run2026B-ZMu-PromptReco-v1/RAW-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2 
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/Era/Prompt/Cert_320394-325273_13TeV_PromptReco_Collisions18_JSON_eraD.txt'
#config.Data.runRange = '397900-397999'
config.Data.publication = True
config.Data.outputDatasetTag = 'CSCEff2026B0_1_260330_1'

config.Site.storageSite = 'T2_US_Wisconsin' 
