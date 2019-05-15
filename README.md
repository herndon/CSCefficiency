# CSC Primitive Efficiency Measurement Package
====================

## About
--- tested in CMSSW_10_2_14
* It is based on the tag-and-probe method using the Z pole or the J/ψ pole;
* The efficiency obtained is the CSC detector efficiency times the efficiency that the muon is not scattered.
* Need RAW information to get the LCT efficiency. RECO or AOD sample is not good.

## Table of Contents
- [Table of Contents](#table-of-contents)
    - [About](#about)
    - [Installation](#installation)
    - [Make the Ntuple](#make-the-ntuple)
    - [Make the Efficiency Plots](#make-the-efficiency-plots)
   
## Installation
<pre>
cmsrel CMSSW_10_1_2_patch2
cd CMSSW_10_1_2_patch2/src
cmsenv
mkdir CSCEfficiency
git clone https://github.com/stremreich/CSCefficiency CSCEfficiency
scramv1 b
</pre>

## Make the Ntuple
1. Modify the config file [create_ntuple.py](CSCEfficiency/create_ntuple.py). 
The output file name can be changed in the following line ---
<pre>
process.aoddump.rootFileName=cms.untracked.string('ntuple.root')
</pre>

Choose if you want to save Z or/and J/psi events: 
<pre>                               
saveZ            = cms.untracked.bool(True),
saveJPsi         = cms.untracked.bool(False),
</pre>

2. Run [create_ntuple.py](CSCEfficiency/create_ntuple.py). CRAB is recommended, but you may be able to run on Condor as well:
<pre>
farmoutAnalysisJobs  --input-files-per-job=1  --skip-existing-output CSCeff_job $CMSSW_BASE $CMSSW_BASE/src/CSCEfficiency/create_ntuple.py --input-file-list=$CMSSW_BASE/src/CSCEfficiency/[list_of_file_names] 'inputFiles=$inputFileNames' 'outputFile=$outputFileName' --assume-input-files-exist --vsize-limit=7000
</pre>

There is a CRAB submission file [CRABsubmit.py](CSCEfficiency/CRABsubmit.py). Also be sure to check the global tag, which may require a more recent CMSSW release.

## Make the Efficiency plots
1. Setup  [Config.py](CSCEfficiency/NtupleAnzScripts/Config.py).
   1. Setup for Data or for MC:
   <pre>
    RunOnMC=False # or True
   </pre>
   
   2. Setup using Z resonance or using J/ψ resonance:
   <pre>
   Resonance="Z" # or "JPsi"
   </pre>
   
   3. Setup how to categorize the data:
   <pre>
   Group="Chambers" #x axis: stations; y axis: efficiency
   #options are
   </pre>
   <table style="width:100%"  align="center">
    <tr>
      <th> Group </th><th> x axis </th><th>y axis</th><th>z axis</th><th> Comments</th>
    </tr>
    <!--<tr>
      <td>"Stations"</td><td>stations</td><td>efficiency</td><td></td>
    </tr>-->
    <tr>
      <td>"Chambers"</td><td>chamber number</td><td>rings</td><td>efficiency</td>
    </tr>
    <tr>
      <td>"Stationspt"</td><td>pt in GeV</td><td>efficiency</td><td></td><td>make a plot for each station</td>
    </tr>
    <tr>
      <td>"Stationseta"</td><td>|η|</td><td>efficiency</td><td></td><td>make a plot for each station</td>
    </tr>
    <tr>
      <td>"Stationsphi"</td><td>ϕ</td><td>efficiency</td><td></td><td>make a plot for each station</td>
    </tr>
    <tr>
      <td>"StationsPV"</td><td>NPU</td><td>efficiency</td><td></td><td>make a plot for each station</td>
    </tr>
    <!--<tr>
      <td>"pt","eta", or "phi"</td><td>pt,|η|,ϕ</td><td>efficiency</td><td></td><td>make one plot for all stations, not tested yet</td>
    </tr>-->
   </table> 
   
   4. Arrange space for the temporary file (you may change the path but not the file name): 
      It may take two times the size of the Ntuple file space. The variable is `TemporaryOutputFile`. By default, it will use the linux         temporary path: /tmp/.
      
   5. Tag and probe file (do not need to change): The variable is `TagProbeFitResult`.
   
   6. result file (do not need to change): The variable is `ResultPlotsFileName`
   
   7. Station categorizing method: variable `station` is a python dictionary. The format of each component in the dictionary is "key(index):(logic expression in C style,name,color,station number)". e.g.
   <pre>
    stations={
        ......
        2:("( CSCRg1==1 )","ME11B",kRed-9,1),
        ......}
   </pre>
   
2. Categorize the data and run the tag-and-probe package in CMSSW:
   <pre> cd NtupleAnzScripts
   python Step1_matchOtherStationsORME13.py Ntuple.root output_dir group_var
   </pre>
   The command above will run the efficiency calculation for the segment efficiecny measurement. For LCT efficiency an additional requirement is used for the probe: there should be no other tracker track that is closer to LCT. So to run efficiency calculation for the LCT efficiecny measurement run with the LCT option:
   <pre> cd NtupleAnzScripts
   python Step1_matchOtherStationsORME13.py Ntuple.root output_dir LCT group_var
   </pre>
   At present you need to provide the "Group" variable you set in Config.py in the command line as well. This was originally used to be able to run multiple tag and probe processes simultaneously, but has since been broken on login0X machines. For now, only run one type of TnP binning at a time.
   
3. Wait until all jobs finished. Use `ps -f` to check. Make sure you have output files called TnP_NtupleAnzScripts_bla.root for all your stations/chambers. If any file is missing you can rerun the TnP fit. Example for ME11: 
<pre>
nohup cmsRun TagandProbe.py Tmp_NtupleAnzScriptsME11.root 1 &
</pre>
(The '1' option is the station #)

There is also a shell script [rerun.sh](CSCEfficiency/NtupleAnzScripts/rerun.sh) for use in re-running entire groups of chamber TnP files. Be careful not to start too many background jobs, even though they should be fairly quick individually.
4. Make the plot:
   <pre>
   python Step2_PlotAll_pallete.py input_dir 
   </pre>
   Plots are in the result root file resultplots_NtupleAnzScripts.root.
5. Read plots from root file and produce nice plots for stations 1,2,3 and 4 and another plot for stations 12+13,11A,11B:
   <pre>
   python plotAllEff_afterStep2.py output_plot_name
   </pre>
   
