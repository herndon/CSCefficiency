# CSC Primitive Efficiency Measurement Package
====================

## About
--- tested in CMSSW_10_2_18
* It is based on the tag-and-probe method using the Z pole or the J/ψ pole;
* The efficiency obtained is the CSC detector efficiency times the efficiency that the muon is not scattered.
* Need RAW information to get the LCT efficiency. RECO or AOD sample is not enough.

## Table of Contents
- [Table of Contents](#table-of-contents)
    - [About](#about)
    - [Installation](#installation)
    - [Make the Ntuple](#make-the-ntuple)
    - [Make the Efficiency Plots](#make-the-efficiency-plots)
   
## Installation
<pre>
cmsrel CMSSW_10_2_18
cd CMSSW_10_2_18/src
cmsenv
mkdir CSCEfficiency
git clone https://github.com/herndon/CSCefficiency CSCEfficiency
scramv1 b
</pre>

## Make the Ntuple
1. Modify the config file [create_ntuple_local.py](CSCEfficiency/create_ntuple_local.py). 
The output file name can be changed in the following line ---
<pre>
process.aoddump.rootFileName=cms.untracked.string('???.root')
</pre>

2. Run [create_ntuple_local.py](CSCEfficiency/create_ntuple_local.py). CRAB is recommended
<pre>
voms-proxy-init -voms cms
cmsRun create_ntuple_local.py
</pre>

or
There is a CRAB submission file [crabConfig_CSCEff_v1.py](CSCEfficiency/crabConfig_CSCEff_v1.py). Also be sure to check you are using a compatible global tag if you are using a more recent release.
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
