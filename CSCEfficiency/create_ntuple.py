# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: RECO -s RAW2DIGI,L1Reco,RECO --runUnscheduled --nThreads 4 --data --era Run2_2017 --scenario pp --conditions 92X_dataRun2_Prompt_v4 --eventcontent RECO --datatier RECO --customise Configuration/DataProcessing/RecoTLR.customisePostEra_Run2_2017 --filein file:/hdfs/store/user/senka/CSC_2017data/1670035E-CD52-E711-AA85-02163E014522.root -n 100 --python_filename=recoOnlyRun2017B.py

import sys
#input_file=sys.argv[2]
#print(input_file)
#output_file=sys.argv[3]
#print(output_file)

import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('ntuple',eras.Run2_2018)
HLTProcessName='HLT'

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("PoolSource",
                            #fileNames = cms.untracked.vstring()
   #fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2018A/SingleMuon/RAW-RECO/ZMu-PromptReco-v1/000/315/257/00000/2A55950E-524B-E811-9C89-FA163E679A44.root'),
   #fileNames = cms.untracked.vstring(input_file),
   #fileNames = cms.untracked.vstring('file:/hdfs/store/user/strembat/CSCntuples/323492-32361586.root'),
                            fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/322/356/00000/E2D82F4E-91B4-E811-81E9-02163E010DC4.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/325/175/00000/6955FAD4-96B1-5D4E-AB63-ADB5C7ABCFAE.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/325/172/00000/FF018C80-477C-CA44-99F0-04F809E1BA0B.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/325/170/00000/FF16CA16-2249-7947-8597-269F40986785.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/321/219/00000/A631D7AD-53A1-E811-9206-FA163EF83AB3.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/324/878/00000/0A6EB8D9-447E-2E44-A17A-BAB86CE554A0.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/324/846/00000/EEDDB501-E05A-1F41-829E-1B7B27C2D8AF.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/325/175/00000/6955FAD4-96B1-5D4E-AB63-ADB5C7ABCFAE.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/325/172/00000/FF018C80-477C-CA44-99F0-04F809E1BA0B.root',
                                                              'root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/325/170/00000/FE61264B-DA70-6A45-BCF6-0FEE6656DD1B.root'),
)


#process.MessageLogger.cerr.FwkReport = cms.untracked.PSet(
#    reportEvery = cms.untracked.int32(1),
#    limit = cms.untracked.int32(1000)
#)

# Memory check
process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
                                        ignoreTotal = cms.untracked.int32(1),
                                        #jobReportOutputOnly = cms.untracked.bool(True),
                                        #showMallocInfo = cms.untracked.bool(True),
                                        #oncePerEventMode = cms.untracked.bool(True),
                                        #moduleMemorySummary = cms.untracked.bool(True)
)

process.MessageLogger.destinations = cms.untracked.vstring("cout")
process.MessageLogger.cout = cms.untracked.PSet(
    threshold = cms.untracked.string("INFO"),
    default   = cms.untracked.PSet( limit = cms.untracked.int32(0))
)   


# --- Activate LogVerbatim IN CSCSegment
#process.MessageLogger.categories.append("CSCSegment")
#process.MessageLogger.destinations = cms.untracked.vstring("cout")
#process.MessageLogger.cout = cms.untracked.PSet(
#    threshold = cms.untracked.string("INFO"),
#    default   = cms.untracked.PSet( limit = cms.untracked.int32(0)  ),
#    FwkReport = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
#    CSCSegment = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
#)   

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('RECO nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('RECO_RAW2DIGI_L1Reco_RECO.root'),
    outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v11', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)

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
#process.schedule = cms.Schedule(process.endjob_step,process.outputstep)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
#process.options.numberOfThreads=cms.untracked.uint32(4)
#process.options.numberOfStreams=cms.untracked.uint32(0)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
from Configuration.DataProcessing.RecoTLR import customisePostEra_Run2_2018 

#call to customisation function customisePostEra_Run2_2017 imported from Configuration.DataProcessing.RecoTLR
process = customisePostEra_Run2_2018(process)

# End of customisation functions
#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

# Output
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('CSC_TnP_ntuple.root')
    #fileName = cms.string(output_file)
)   
