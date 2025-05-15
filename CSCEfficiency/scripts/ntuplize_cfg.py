# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 --conditions auto:phase1_2021_realistic -n 10 --era Run3 --eventcontent RECOSIM -s RAW2DIGI,L1Reco,RECO,RECOSIM --datatier RECO --geometry DB:Extended --io RecoPU_2021PU.io --python RecoPU_2021PU.py --filein root://cms-xrd-global.cern.ch//store/relval/CMSSW_11_3_0/RelValZMM_14/GEN-SIM-DIGI-RAW/113X_mcRun3_2021_realistic_v10-v1/00000/175b3087-820c-49c9-99ba-cba0f30ad6f5.root --fileout file:step3.root --nThreads 8
import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

import re

from Configuration.StandardSequences.Eras import eras
process = cms.Process('ntuple',eras.Run3)
HLTProcessName='HLT'

# command-line arguments
options = VarParsing.VarParsing("analysis")
options.maxEvents = 100000

# main settings
options.register("globalTag", "",
        VarParsing.VarParsing.multiplicity.singleton,
        VarParsing.VarParsing.varType.string,
        "global tag for analysis")
options.register("local", 0,
        VarParsing.VarParsing.multiplicity.singleton,
        VarParsing.VarParsing.varType.int,
        "type of job 0: local 1: CRAB submission")

# CRAB settings
options.register("primaryDS", "",
        VarParsing.VarParsing.multiplicity.singleton,
        VarParsing.VarParsing.varType.string,
        "primary dataset name (Muon0 or Muon1)")
options.register("era", "",
        VarParsing.VarParsing.multiplicity.singleton,
        VarParsing.VarParsing.varType.string,
        "era identifier (e.g. 2024A)")
options.register("version", 0,
        VarParsing.VarParsing.multiplicity.singleton,
        VarParsing.VarParsing.varType.int,
        "version identifier for era")
options.parseArguments()

# error checking
if not options.globalTag:
    raise ValueError("globalTag option is required")
if options.local:
    if not options.inputFiles:
        raise ValueError("inputFiles option is required for local submissions")
else:
    for name in ["primaryDS", "era", "version"]:
        if not getattr(options, name):
            raise ValueError("%s option is required" % name)
    if not re.fullmatch("[0-9]{4}[A-Z]", options.era):
        raise valueError("invalid era:", options.era)
    if not options.primaryDS.startswith("Muon") or not any(options.primaryDS.endswith(num) for num in "01"):
        raise ValueError("invalid primaryDS:", options.primaryDS)
    if options.version <= 0:
        raise ValueError("invalid version:", options.version)

# printout
print("Running local" if options.local else "Submitting CRAB", "job")
if options.local:
    for name in ["inputFiles", "outputFile", "maxEvents"]:
        print("%s: %s" % (name, getattr(options, name)))
else:
    for name in ["primaryDS", "era", "version"]:
        print("%s: %s" % (name, getattr(options, name)))

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
#process.load('Configuration.StandardSequences.AlCaRecoStreams_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("PoolSource", 
    fileNames = cms.untracked.vstring(options.inputFiles) if options.local else cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    #accelerators = cms.untracked.vstring('*'),
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(1)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(1),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(2),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:step3.root'),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, options.globalTag, '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)

from RecoMuon.TrackingTools.MuonSegmentMatcher_cff import *
process.load("TrackingTools.TrackAssociator.DetIdAssociatorESProducer_cff")
from TrackingTools.TrackAssociator.default_cfi import *
from RecoMuon.MuonIsolationProducers.trackExtractorBlocks_cff import MIsoTrackExtractorBlock

process.MuonSegmentMatcher = cms.PSet(
     MatchParameters = cms.PSet(
         CSCsegments = cms.InputTag("cscSegments"),
         DTradius = cms.double(0.01),
         DTsegments = cms.InputTag("dt4DSegments"),
         RPChits = cms.InputTag("rpcRecHits"),
         TightMatchCSC = cms.bool(True),
         TightMatchDT = cms.bool(False)
     ) 
)

process.aodDump = cms.EDAnalyzer('TPTrackMuonSys',
                                 TrackAssociatorParameterBlock,
                                 MuonSegmentMatcher,
                                 TrackExtractor=cms.PSet(MIsoTrackExtractorBlock),
                                 #rootFileName   = cms.untracked.string('CSC_eff_test.root'),
                                 CSCUseTimingCorrections = cms.bool( True ),
                                 CSCUseGasGainCorrections = cms.bool( True ),
                                 isMC            = cms.untracked.bool(False),
                                 saveZ            = cms.untracked.bool(True),
                                 saveJPsi            = cms.untracked.bool(False),
                                 mcTag           = cms.untracked.InputTag('genParticles'),
                                 vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                 gTracksTag      = cms.untracked.InputTag('generalTracks'),
                                 trackProducer   = cms.InputTag('csctfunpacker:'),
                                 readBadChannels = cms.bool(True),
                                 readBadChambers = cms.bool(True),
                                 hltTag      = cms.untracked.InputTag("TriggerResults","",HLTProcessName),
                                 hltEvTag    = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                 HLTMuTrgNames =  cms.vstring("HLT_Mu?_v*","HLT_Mu??_v*","HLT_Mu???_v*","HLT_IsoMu?_v*","HLT_IsoMu??_v*","HLT_IsoMu???_v*","HLT_L2Mu?_v*","HLT_L2Mu??_v*","HLT_L2Mu???_v*","HLT_SingleMu*","HLT_L1SingleMu*","HLT_IsoTkMu??_v*","HLT_TkMu??_v*"),
                                 HLTDiMuTrgName =  cms.string("HLT_DoubleMu?_v*"),
                                 #                      hltEvTag    = cms.untracked.InputTag("hltTriggerSummaryAOD","","REDIGI36X"),
                                 L1extraTag   = cms.untracked.InputTag("l1extraParticles"),
                                 dedxTag         =  cms.untracked.InputTag('dedxHarmonic2'),
                                 scalersResults = cms.InputTag("scalersRawToDigi","","RECO")
                                 )


process.outputstep = cms.EndPath(process.aodDump)


# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.outputstep)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads = 2
process.options.numberOfStreams = 0
if not options.local:
    process.options.numberOfConcurrentLuminosityBlocks = 2
    process.options.eventSetup.numberOfConcurrentIOVs = 1
    if hasattr(process, 'DQMStore'): process.DQMStore.assertLegacySafe=cms.untracked.bool(False)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
#from Configuration.DataProcessing.RecoTLR import customiseExpress 

#call to customisation function customiseExpress imported from Configuration.DataProcessing.RecoTLR
#process = customiseExpress(process)

# End of customisation functions


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string("CSCeff_Muon_%s%iv%i.root" % (
        options.era,
        int(options.primaryDS.replace("Muon","")),
        options.version,
    )) if not options.local else cms.string(options.outputFile)
)   
