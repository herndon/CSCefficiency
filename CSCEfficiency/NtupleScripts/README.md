# Scripts for CSC Efficiency

- [Creating the Efficiency Histogram File](#creating-the-efficiency-histogram-file)
   * [Bad Chamber Removal](#bad-chamber-removal)
   * [Analyzing New Data](#analyzing-new-data)
- [Calculate and/or Embed Luminosity](#calculate-andor-embed-luminosity)
   * [Installing `brilcalc`](#installing-brilcalc)
- [Saving Final Plots](#saving-final-plots)

## Creating the Efficiency Histogram File

To calculate CSC efficiency using the ntuples, you can use the `CSCEffFast` class defined in [`CSCEffFast.h`](CSCEffFast.h) and [`CSCEffFast.C`](CSCEffFast.C).
To begin an efficiency analysis, you can run the script as a standalone executable or through the ROOT CLI. This will create a histogram file `cscEffHistoFile.root` 
with all of the efficiency calculations put into relevant plots. To run the script, see options below.

```bash
# (1) standalone executable
make analyze
./analyze

# (2) ROOT CLI
root -b
.L CSCEffFast.C+
auto *csc = new CSCEffFast()
```

However, the script should be edited to point towards the desired files for analysis. This is done in `CSCEffFast.h` using the `dataset` structs. To point toward
pre-existing datasets, simply find the `firstSet` and `lastSet` variables and set them to the datasets you want. For example, if you want to analyze 2024Iv1-2,
the code may include something like the following.

```C++
#if newData
  static constexpr dataset firstSet = d2024Iv1;
  static constexpr dataset lastSet  = d2024Iv2;
#else
  //...
#endif
```

**NOTE**: To remain compatible with 2022 analysis and retain reproducibility of the plots, there is a `newData` pre-processor macro. This should *always* be set to 
`true` unless you want to reproduce the 2022 histogram file. Accordingly, you should edit the `firstSet` and `lastSet` variables within the block that asserts
`newData=true`, similar to the code snippet above.

### Bad Chamber Removal

When plotting these output histograms at a later stage (see [here](#saving-final-plots)), an automatic efficiency analysis can be done. This will flag  
runs, chambers, etc. below given thresholds and output a `BadChambers_auto.h` file. This header file can be used with `CSCEffFast` to recalculate efficiencies
while ignoring these flagged sections. To do so, change the `autoRemoval` pre-processor macro found in [`CSCEffFast.C`](CSCEffFast.C) to `true`. The program will automatically
filter  out the flagged chambers when doing its efficiency calculations.

### Analyzing New Data

If you want to calculate efficiencies for new data, you must follow these steps. First, you need to create a new `dataset` variable to hold the run range and string 
identifier for the era. For example, if you want to add a new variable for 2024Iv2, the line would look something like the following.

```C++
static constexpr dataset d2024Iv2 = {386798, 387000, "2024Iv2"};
```

The naming convention for the string identifier is the acquisition era (e.g. 2024I) followed by the processing version (e.g. v1). The convention for the `dataset`
variable is to name it 'd' followed by the string identifier provided. Remember that if you want to process this new data, you need to modify `firstSet` and `lastSet`
as instructed in the previous section.

Now that the struct variable is ready, you must list the files that need to be loaded for this dataset in the constructor.
For example, the ntuples for 2024Iv2 would be listed as the following.

```C++
CSCEffFast::CSCEffFast() : fChain(0)
{
  // ...

  // *must* be in the 'newData' block below!
  if (newData){
    // ...

    // make sure to enclose the list of files with the following conditional
    if (firstRun <= d2024Iv2.lastRun && d2025Iv2.firstRun <= lastRun){
      // list the files. of course, change the source directory and final filename for the ntuples as needed
      numberFiles += chain->Add("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_1_241007_1/241009_145815/*/*.root"); //Muon0
      numberFiles += chain->Add("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_1_241007_1/241009_151524/*/*.root"); //Muon1
    }

  // ...
}
```

## Calculate and/or Embed Luminosity

To help format titles in final plots, the luminosity needs to be calculated. This is done through the script [`calcLumis.py`](calcLumis.py). 
To see available options for running this script, run the following.

```bash
./calcLumis.py --help
```

This script uses the `brilcalc` tool to calculate the luminosity for a given run range. (This is why exact run ranges are important in `CSCEffFast`!) If you do not
have `brilcalc` installed, follow the instructions [here](#installing-brilcalc). For *most* cases, the default options are sufficient to calculate and store the 
luminosity. In other words, just run `./calcLumis.py`.

The benefit of this script is that it will only calculate luminosities if it cannot find the luminosity stored in [`lumi.json`](lumi.json). 
This way if any alterations are made to `CSCEffFast` and the script is re-ran the luminosity is read from the JSON file and does not need to be recalculated.

**NOTE**: For slightly better accuracy, the `brilcalc` command can be run without the `web` option. This does not work on the UW HEP server at the moment, but will work
on LXPLUS. If you are using `calcLumis.py` on LXPLUS, you can use the `--no-web` option to omit it. Note that `calcLumis.py` is independent of any CMSSW release but
expects a CSCEfficiency histogram file as input. Thus, if desired, the script and the input file can be transferred to LXPLUS and run without issue.

### Installing `brilcalc`

Set up by running the following commands:

```bash
export NEWPATH=$HOME/.local/bin:$PATH
export PATH=$HOME/.local/bin/:/cvmfs/cms-bril.cern.ch/brilconda310/bin:$PATH
pip install --user brilws
export PATH=$NEWPATH
```

**NOTE**: At this time, `brilcalc` crashes when run off-site (e.g. on this server). For the moment, you will need to do the following. Feel free to
change the input filename as you need.

1. Use `calcLumis.py` to print out the command you need to run. This can be done using the `--norun` flag. For example, `./calcLumis.py --infile
cscEffHistoFile.root --noweb --norun`. The command will be printed out in the last line. 
2. In a different terminal session, `ssh` to the CERN lxplus server and run the command. 
(If it doesn't work, run the commands above to install `brilws` on that server!)
3. Check the output `lumi.csv` file. At the end of the file, copy the number under "Total recorded". This is the luminosity we want.
4. Back in the UW server, run the following command to write and store the desired luminosity: `./calcLumis.py --infile cscEffHistoFile.root --lumi
<LUMI>`. Of course, replace `<LUMI>` with the luminosity you recorded in the previous step.
5. Save changes to the `lumi.csv` file to avoid re-calculating in the future, if desired.

## Saving Final Plots

Final plots can be created either by a standalone executable or the ROOT CLI, similar to before:

```bash
# (1) standalone executable
make plot
./plot

# (2) ROOT CLI
root -b
.x PlotCSCEffFast.C
```

If you use the standalone executable, there is also an optional argument for the input filename. If it is not provided, the script will default to `cscEffHistoFile.root`.
Running this script will create plots in `plots/SETNAME/`, where `SETNAME` is the name of the processed datasets given by `CSCEffFast`. When processing single datasets,
the set name is the string identifier for that dataset. There is no need to create any directories before running, as any missing directories will be created when the
script needs it.

The script can be customized by changing the booleans under the `# Flags` comment. A code snippet below shows this.

```C++
// Flags
int verbose = 1; // 0: None. 1: Simple printouts. 2: Simple printouts and ROOT drawing statements
bool summaryPlots = true; // Efficiency plot per ring or for the full system
bool chamberPlots = false; // Plots of run, LCT, LCY efficiency per chamber.  Plot printing time is lengthy
//bool runAnalysis = false; // Run Analysis per chamber wont get done unless chamber plots are on (old run analysis printout)
bool effCheck = true; // Run efficiency check analysis, right now only an analysis of DCFEBs
bool DCFEBAnalysis = true; // Run DCFEB analysis for specific run ranges
bool segmentAnalysis = false; // Segment plots for debugging
```

The `effCheck` variable toggles the automated efficiency analysis, as mentioned [here](#bad-chamber-removal).
