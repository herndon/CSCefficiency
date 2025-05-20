# CSC Primitive Efficiency Measurement Package

====================

This package has been tested in `CMSSW_15_0_6`, the release needed to run the 2025 dataset. Important details about the package are as follows:

* This package is based on the tag-and-probe method using the Z pole or the J/ψ pol.
* The efficiency obtained is the CSC detector efficiency times the efficiency that the muon is not scattered.
* The package needs RECO-RAW information to get the LCT efficiency. RECO and AOD (mini, nano or simple AOD) samples are not enough.

## Table of Contents

- [Installation](#installation)
- [Make the Ntuple](#make-the-ntuple)
   * [Local submission](#local-submission)
   * [CRAB submission](#crab-submission)
- [Make the Efficiency plots](#make-the-efficiency-plots)

## Installation
```bash
cmsrel CMSSW_15_0_6
cd CMSSW_15_0_6/src
cmsenv
#git cms-init
git clone https://github.com/herndon/CSCefficiency
scram build
```

## Make the Ntuple

For automatic CRAB/local jobs for making ntuples, check [this README](CSCEfficiency/scripts/README.md). The local job can be used to test that the settings are correct.
Alternatively, you can use the scripts within the package directory [`CSCEfficiency/`](CSCEfficiency). The instructions for that are found below.

### Local submission

1. Modify the config file [`create_ntuple_local_Run3_2025_Data_test.py`](CSCEfficiency/create_ntuple_local_Run3_2025_Data_test.py). 
The output file name can be changed in the configuration of the `TFileService` for the process:

```python
process.TFileService = cms.Service('TFileService',
    fileName = cms.string('CSCeff_Muon_202B1_1_test.root')
) 
```

2. Run the config file with `cmsRun`. This will test program on the local computer. You will still need to run voms-proxy-init to reauthenticate your grid certificate and gain access to cms data. CRAB is recommended for running larger numbers of events if the tests are successful. Steps necessary to setup access to the cms data are explained at: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookStartingGrid. The commands to run the test are below.

```bash
voms-proxy-init -voms cms -valid 192:00
cmsRun create_ntuple_local_Run3_2025_Data_test.py
```

To create scripts for more recent data, you may need to change the following things:

* Input filename
* CMSSW release
* Global tag (for loading the correct configurations and calibrations for the data and release being used)

### CRAB submission

There is a CRAB submission file [`CSCEfficiency/crabConfig_CSCEff2025B0_1.py`](CSCEfficiency/crabConfig_CSCEff2025B0_1.py) that runs the cmsRun script [`CSCEfficiency/create_ntuple_crab_Run3Data_2025B_1.py`](CSCEfficiency/create_ntuple_crab_Run3Data_2025B_1.py). These scripts are running on data described at: https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FMuon*%2FRun2025*-ZMu-PromptReco-v*%2FRAW-RECO.

Note there you can click on `config` to see the release and global tag used to process the original data. The same release (or later in the same series, only updating the minor number) and global tag should be used. You can click on files to find file names that could be used in the local script. The commands to submit the CRAB job are below - note that again you may need to reauthenticate your grid certificate.

```bash
voms-proxy-init -voms cms -valid 192:00
crab submit -c crabConfig_CSCEff2025B0_1.py
```

The first time you run the crab command each day you often have to type you voms passcode again.

The crab command, if successful, will return a report and an example crab status command to check on the job. Run that - the command will return some web links to a graphical monitor of your job status. The monit-grafana site is the useful one. It can take several tens of minutes till your job shows up there.

## Make the Efficiency plots

For a more detailed description of the scripts and how to use them, check [this README](CSCEfficiency/NtupleScripts/README.md). For a quick start, see below.

After modifying CSCEffFast.h to point to your T&P output Ntuple files run in root using the [`CSCEffFast`](CSCEfficiency/NtupleScripts/CSCEffFast.h) class:

```bash
root -b
.L CSCEffFast.C+
CSCEffFast* cscEffFast = new CSCEffFast()
```

This makes the file `cscEffHistoFile.root`.
To make plots automatically, you can use the [`PlotCSCEffFast.C`](CSCEfficiency/NtupleScripts/PlotCSCEffFast.C) script:

```bash
root -b
.x PlotCSCEffFast.C
```
