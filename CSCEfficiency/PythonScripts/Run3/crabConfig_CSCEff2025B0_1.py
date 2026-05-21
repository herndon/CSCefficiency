from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'CSCEff2025B0_1_14'
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'create_ntuple_crab_Run3Data_2025B_1.py'
config.JobType.maxMemoryMB = 10000 
config.JobType.allowUndistributedCMSSW = True
config.JobType.numCores = 4 

config.Data.inputDataset = '/Muon0/Run2025B-ZMu-PromptReco-v1/RAW-RECO'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2 
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/Era/Prompt/Cert_320394-325273_13TeV_PromptReco_Collisions18_JSON_eraD.txt'
#config.Data.runRange = '382900-384000'
config.Data.publication = True
config.Data.outputDatasetTag = 'CSCEff2025B0_1_250513_14'

config.Site.storageSite = 'T2_US_Wisconsin' 
