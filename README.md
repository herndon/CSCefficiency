# CSC Primitive Efficiency Measurement Package
====================

## About
--- tested in CMSSW_15_0_5, this release needed to run the 2025 dataset
* It is based on the tag-and-probe method using the Z pole or the J/ψ pole;
* The efficiency obtained is the CSC detector efficiency times the efficiency that the muon is not scattered.
* Need RECO-RAW information to get the LCT efficiency. RECO, AOD (mini, nano or simple AOD) samples are not enough.

## Table of Contents
- [Table of Contents](#table-of-contents)
    - [About](#about)
    - [Installation](#installation)
    - [Make the Ntuple](#make-the-ntuple)
    - [Make the Efficiency Plots](#make-the-efficiency-plots)
   
## Installation
<pre>
cmsrel CMSSW_15_0_5
cd CMSSW_15_0_5/src
cmsenv
mkdir CSCEfficiency
git clone https://github.com/herndon/CSCefficiency CSCEfficiency
scramv1 b
</pre>

## Make the Ntuple
1. Modify the config file [create_ntuple_local_Run3_2025_Data_test.py](CSCEfficiency/create_ntuple_local_Run3_2025_Data_test.py). 
The output file name can be changed in the following line ---
<pre>
process.aoddump.rootFileName=cms.untracked.string('???.root')
</pre>

2. Run [create_ntuple_local_Run3_2025_Data_test.py](CSCEfficiency/create_ntuple_local_Run3_2025_Data_test.py). This will test program on the local computer.  You will still need to run voms-proxy-init to gain access to cms data.  CRAB is recommended for running larger numbers of events.
<pre>
voms-proxy-init -voms cms
cmsRun create_ntuple_local.py
</pre>

Steps necessary to setup access to the cms data are explained at: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookStartingGrid

Things that may need to be chanched to run more recent data are.   The input file name.  The global tag to load the correct configurations and callibrations for the data and release you are using.

or
There is a CRAB submission file [CSCEfficiency/crabConfig_CSCEff2025B0_1.py](CSCEfficiency/crabConfig_CSCEff2025B0_1.py). That runs the cmsRun script [CSCEfficiency/](CSCEfficiency/create_ntuple_crab_Run3Data_2025B_1.py)
<pre>
voms-proxy-init -voms cms
crab submit -c crabConfig_CSCEff_v1.py
</pre>


## Make the Efficiency plots
See files in [NtupleScripts](CSCEfficiency/NtupleScripts/.)
After modifying CSCEffFast.h to point to your T&P output Ntuple files run in root using:
<pre>
root -b
.L CSCEffFast.C+
CSCEffFast* cscEffFast = new CSCEffFast()
</pre>
This makes the file cscEffHistoFile.root
The file commands.txt has commands to make pretty plots from cscEffHistoFile.root.
There is scipt to make plots automatically.  However, you likely have to create of copy over the directory structure made under plots/ first.
<pre>
root
.x PlotCSCEffFast.C
</pre>
