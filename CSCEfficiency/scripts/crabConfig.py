import os
import re
import configparser
from datetime import datetime

# Import user configurations
settings = configparser.ConfigParser()
settings.read("settings.cfg")
sectionSettings = settings[settings.get("DEFAULT", "section")]

# Error checking
pattern = "/Muon\d/Run\d{4}[A-Z]-ZMu-PromptReco-v\d+/RAW-RECO"
if re.fullmatch(pattern, sectionSettings["dataset"]) is None:
    raise Exception(f'invalid input dataset: {sectionSettings["dataset"]}' + \
                    f'\nexpected input of the form: {pattern}')

# Read user configurations
primaryDS, conditions, _ = sectionSettings["dataset"].split("/")[1:]
sectionSettings["stream"] = primaryDS[-1]
sectionSettings["era"] = conditions.split("-")[0].replace("Run","")
sectionSettings["version"] = conditions[-1]

configParams = [
    "CRAB=1",
    "globalTag=%s" % sectionSettings["globalTag"],
    "outputFile=%s" % sectionSettings["outputFile"],
]

jobAttempt = 1
requestName = "%s_%i" % (sectionSettings["requestName"], jobAttempt)
while os.path.exists("crab_%s" % requestName):
    jobAttempt += 1
    requestName = "%s_%i" % (sectionSettings["requestName"], jobAttempt)

print("Submitting job:", requestName)
print("Global tag:", sectionSettings["globalTag"])

# Initialize CRAB config
from CRABClient.UserUtilities import config
config = config()

# General settings
config.General.requestName = requestName
config.General.workArea = ''
config.General.transferOutputs = True
config.General.transferLogs = True

# Job settings
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = "%s/src/%s" % (os.environ["CMSSW_BASE"], sectionSettings["psetName"])
config.JobType.maxMemoryMB = int(sectionSettings["maxMemoryMB"]) 
config.JobType.numCores = int(sectionSettings["numCores"])
config.JobType.allowUndistributedCMSSW = True
config.JobType.pyCfgParams = configParams

# Data settings
config.Data.inputDataset = sectionSettings["dataset"]
config.Data.lumiMask = sectionSettings["lumiMask"]
config.Data.runRange = sectionSettings["runRange"]
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = int(sectionSettings["unitsPerJob"])
config.Data.publication = True
config.Data.outputDatasetTag = sectionSettings["tag"]
if sectionSettings.getboolean("appendDate"):
    config.Data.outputDatasetTag += f'_{datetime.now():%Y_%m%d}'

# Site settings
config.Site.storageSite = 'T2_US_Wisconsin' 
