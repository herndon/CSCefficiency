#!/bin/sh

echo "Submitting Condor Job(s)"

farmoutAnalysisJobs --input-files-per-job=1 --input-runs=319841-319851 --extra-inputs=$CMSSW_BASE/src/CSCEfficiency/CSCEfficiency/Cert_314472-319851_13TeV_PromptReco_Collisions18_JSON.txt --input-dbs-path=/SingleMuon/Run2018C-ZMu-PromptReco-v3/RAW-RECO --skip-existing-output CSCeff_2018C-v3_Aug-9-2018_319841-319851_skim $CMSSW_BASE $CMSSW_BASE/src/CSCEfficiency/CSCEfficiency/CondorSubmit.py 'inputFiles=$inputFileNames' 'outputFile=$outputFileName' --assume-input-files-exist --vsize-limit=7000 &
