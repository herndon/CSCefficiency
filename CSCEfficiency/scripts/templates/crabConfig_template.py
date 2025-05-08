from CRABClient.UserUtilities import config

# User settings
params = {
    "era": "$era",
    "stream": "$stream",
    "version": "$version",
    "attempt": "$attempt",
}
lumiMask = "$lumiMask"
appendDate = $appendDate
dataID = "{era}{stream}v{version}_v{attempt}".format(**params)

# Initialize CRAB config
config = config()

# General settings
config.General.requestName = f'CSCEff{dataID}'
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

# Job settings
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = f'create_ntuple_crab_Run3Data_{dataID}.py'
config.JobType.maxMemoryMB = 2500 
config.JobType.allowUndistributedCMSSW = True

# Data settings
config.Data.inputDataset = '/Muon{stream}/Run{era}-ZMu-PromptReco-v{version}/RAW-RECO'.format(**params)
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = $unitsPerJob
config.Data.publication = True
config.Data.outputDatasetTag = f'CSCEff{dataID}'
if lumiMask:
    config.Data.lumiMask = lumiMask
if appendDate:
    from datetime import datetime
    config.Data.outputDatasetTag += f'_{datetime.now():%Y_%m%d}'

# Site settings
config.Site.storageSite = 'T2_US_Wisconsin' 
