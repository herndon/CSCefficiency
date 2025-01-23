from CRABClient.UserUtilities import config
from datetime import datetime
config = config()

params = {
    "dataset": "$dataset",
    "stream": "$stream",
    "version": "$version",
    "attempt": "$attempt",
}
dataID = "{dataset}{stream}v{version}_v{attempt}".format(**params)

config.General.requestName = f'CSCEff{dataID}'
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = f'create_ntuple_crab_Run3Data_{dataID}.py'
config.JobType.maxMemoryMB = 2500 
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = '/Muon{stream}/Run{dataset}-ZMu-PromptReco-v{version}/RAW-RECO'.format(**params)
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = $unitsPerJob
#config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/Era/Prompt/Cert_320394-325273_13TeV_PromptReco_Collisions18_JSON_eraD.txt'
config.Data.publication = True
config.Data.outputDatasetTag = f'CSCEff{dataID}'
#config.Data.outputDatasettag = f'CSCEff{dataID}_{datetime.now():%Y_%m%d}'

config.Site.storageSite = 'T2_US_Wisconsin' 
