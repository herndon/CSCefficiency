# Import user configurations
import configparser
settings = configparser.ConfigParser()
settings.read("settings.cfg")
sectionSettings = settings[settings.get("DEFAULT", "section")]

configParams = [
    "globalTag=%s" % sectionSettings["globalTag"],
    "primaryDS=Muon%s" % sectionSettings["stream"],
    "era=%s" % sectionSettings["era"],
    "version=%s" % sectionSettings["version"],
    "attempt=%s" % sectionSettings["jobAttempt"],
]

# Initialize CRAB config
from CRABClient.UserUtilities import config
import os
config = config()

# General settings
config.General.requestName = sectionSettings["requestName"]
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

# Job settings
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = "%s/src/%s" % (os.environ["CMSSW_BASE"], sectionSettings["psetName"])
config.JobType.maxMemoryMB = 2500 
config.JobType.allowUndistributedCMSSW = True
config.JobType.pyCfgParams = configParams

# Data settings
config.Data.inputDataset = sectionSettings["dataset"]
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = int(sectionSettings["unitsPerJob"])
config.Data.publication = True
config.Data.outputDatasetTag = sectionSettings["tag"]
if sectionSettings["lumiMask"]:
    config.Data.lumiMask = sectionSettings["lumiMask"]
if sectionSettings.getboolean("appendDate"):
    from datetime import datetime
    config.Data.outputDatasetTag += f'_{datetime.now():%Y_%m%d}'

# Site settings
config.Site.storageSite = 'T2_US_Wisconsin' 
