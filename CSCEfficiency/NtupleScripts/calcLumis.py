#!/usr/bin/env python3
import argparse
import json
import os
import subprocess
import ROOT

def main():
  DESC = ""
  parser = argparse.ArgumentParser(description=DESC, formatter_class=argparse.ArgumentDefaultsHelpFormatter)
  parser.add_argument("-q", "--quiet", action="store_true", help="if provided, no print statements will show")
  parser.add_argument("--json", default="lumi.json", help="json file for reading/writing calculated luminosities")
  parser.add_argument("--nostore", action="store_true", help="if provided, the luminosity will not be stored in the JSON file")
  parser.add_argument("--nowrite", action="store_true", help="if provided, the luminosity will not be stored in the ROOT file")
  parser.add_argument("--norun", action="store_true", help="if provided, just print the command instead of running")
  parser.add_argument("--recalc", action="store_true", help="if provided, re-calculate the luminosity even if an entry is found in the JSON file")
  parser.add_argument("--normtag", default="/cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json", help="normtag for lumi calculation. set to preliminary normtag by default")
  parser.add_argument("--noweb", action="store_true", help="if provided, the 'web' option will not be passed. this is recommended when running on LXPLUS")
  parser.add_argument("--online", action="store_true", help="if provided, the normtag will not be used. this is meant to be a debugging tool, as this is NOT RECOMMENDED. without a normtag, the lumi will be inaccurate.")
  parser.add_argument("-n", "--name", help="if provided, use this name as the key when saving to the JSON file. otherwise, the key will be the title of the setName object in the ROOT file")
  parser.add_argument("-l", "--lumi", type=float, help="if provided, skip calculation and save this luminosity to the file")
  parser.add_argument("-i", "--infile", default="cscEffHistoFile.root", help="input ROOT file")
  args = parser.parse_args()

  if not os.path.isfile(args.infile):
    parser.error("invalid file: %s" % args.infile)

  if args.lumi is not None and args.lumi <= 0.0:
    parser.error("invalid lumi: %s" % args.lumi)

  if args.online:
    print("WARNING: Not using a normtag is NOT recommended. Consider using a normtag with this command.")
  
  updated_lumi = args.lumi is not None
  lumi_dict = {}
  if os.path.isfile(args.json):
    with open(args.json, "r") as infile:
      lumi_dict = json.load(infile)
      if not args.quiet: print("Loaded lumi JSON")

  with ROOT.TFile.Open(args.infile, "update") as infile:
    if args.name is None:
      args.name = infile.Get("setName").GetTitle() if infile.GetListOfKeys().Contains("setName") else args.infile
    if not args.quiet: print("Loaded set '%s'" % args.name)

    firstRun = lastRun = 0
    if infile.GetListOfKeys().Contains("setRuns"):
      firstRun,lastRun = infile.Get("setRuns").GetTitle().split()
      if infile.GetListOfKeys().Contains("setRunsTrue"):
        minRun,maxRun = infile.Get("setRunsTrue").GetTitle().split()
        if minRun != firstRun or maxRun != lastRun:
          print(f'WARNING: Processed range ({minRun}-{maxRun}) does not '
              f'match reported range ({firstRun}-{lastRun}). Consider '
              'changing values for dataset in CSCEffFast.h')
          firstRun = minRun
          lastRun  = maxRun
    elif infile.GetListOfKeys().Contains("segEff2DStation1Ring1ChamberRun"):
      htemp = infile.Get("segEff2DStation1Ring1ChamberRun")
      firstRun = int(htemp.GetYaxis().GetBinLowEdge(1))
      lastRun = int(htemp.GetYaxis().GetBinUpEdge(htemp.GetNbinsY()))
    if not args.quiet: print("Determined run range: %s-%s" % (firstRun, lastRun))
    runs = "-".join([str(x) for x in [firstRun, lastRun]])

    extra = "" if args.noweb else "-c web"
    command = f"brilcalc lumi {extra} --begin {firstRun} --end {lastRun} -u /fb -o lumi.csv"
    if not args.online:
      command += f" --normtag {args.normtag}"
    if args.norun:
        print(command)
        return

    if args.lumi is None:
      if not args.recalc and args.name in lumi_dict and lumi_dict[args.name]["runs"] == runs:
        args.lumi = lumi_dict[args.name]["lumi"]
        if not args.quiet:
          print("Retrieved lumi from JSON (%s /fb)" % args.lumi)
      else:
        updated_lumi = True
        if subprocess.run("which brilcalc".split(), stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode != 0:
          print("brilcalc not found.")
          print("set up by running the following commands:\n")
          print("export NEWPATH=\$HOME/.local/bin:\$PATH")
          print("export PATH=\$HOME/.local/bin/:/cvmfs/cms-bril.cern.ch/brilconda/bin:\$PATH")
          print("pip install --user brilws")
          print("export PATH=\$NEWPATH\n")
          print("afterwards, add 'export PATH=\$HOME/.local/bin:\$PATH' to your .bashrc file\n")
          parser.error("brilcalc not found")


        if not args.quiet:
            print("Running command: %s" % command)

        try:
          subprocess.run(command.split(), check=True, capture_output=True)
        except:
          parser.error("error running brilcalc")
        lumis = subprocess.run("tail -1 lumi.csv".split(), capture_output=True, encoding="utf-8")
        os.remove("lumi.csv")
        args.lumi = lumis.stdout.strip().split(",")[-1]
        if not args.quiet:
          print("Calculated lumi (%s /fb)" % args.lumi)

    if infile.GetListOfKeys().Contains("lumi"):
      lumi = infile.Get("lumi")
      lumi.SetTitle("%s" % str(args.lumi))
    else:
      lumi = ROOT.TNamed("lumi", str(args.lumi))
    if not args.nowrite:
      lumi.Write("", ROOT.TObject.kOverwrite)
      if not args.quiet: print("Lumi updated to %s /fb in ROOT file" % args.lumi)

  if not args.nostore and updated_lumi:
    with open(args.json, "w") as outfile:
      if args.name in lumi_dict:
        lumi_dict[args.name]["lumi"] = str(args.lumi)
        lumi_dict[args.name]["runs"] = runs
      else:
        lumi_dict[args.name] = {
          "lumi": str(args.lumi),
          "runs": runs
        }
      json.dump(lumi_dict, outfile, indent=2)
      if not args.quiet: print("Saved lumi to JSON")


if __name__ == "__main__":
  main()
