#!/usr/bin/env python3
import argparse
import os
import re
import string

def main():
    if "CMSSW_BASE" not in os.environ:
        print("set up CMSSW first")
        exit(1)

    TEMPLATE_DIR = f'{os.environ["CMSSW_BASE"]}/src/CSCefficiency/CSCEfficiency/scripts/templates'

    DESC=""
    parser = argparse.ArgumentParser(description=DESC, formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--lumiMask", type=str, default="", help="optional lumiMask for job submission")
    parser.add_argument("--appendDate", action="store_true", help="if provided, append date (YYYY_MMDD) to the output dataset tag")
    parser.add_argument("--unitsPerJob", type=int, metavar="UNITS", default=4, help="files to process per job")
    parser.add_argument("-v", "--version", type=int, default=1, help="data version")
    parser.add_argument("-s", "--streams", type=lambda x: [int(i) for i in x.split(',')], default="0,1", help="desired muon stream(s) given as a comma-separated list")
    parser.add_argument("era", type=lambda x: str(x).upper(), help="era identifier (e.g. 2024A)")
    parser.add_argument("globalTag", help="global tag for data processing")
    args = parser.parse_args()

    config_template = f'{TEMPLATE_DIR}/crabConfig_template.py'
    config_prefix   = "crabConfig_CSCEff"
    exe_template    = f'{TEMPLATE_DIR}/create_ntuple_crab_template.py'
    exe_prefix      = "create_ntuple_crab_Run3Data"

    #Error checking
    if not os.path.isdir(TEMPLATE_DIR):
        parser.error("template directory not found:", TEMPLATE_DIR)
    if not os.path.isfile(config_template):
        parser.error("config template not found:", config_template)
    if not os.path.isfile(exe_template):
        parser.error("executable template not found:", exe_template)
    if args.unitsPerJob <= 0:
        parser.error("invalid files per job:", args.unitPerJob)
    if args.version <= 0:
        parser.error("invalid version:", args.version)
    if any(s != 0 and s != 1 for s in args.streams):
        parser.error("invalid muon stream(s):", args.streams)
    if not re.fullmatch("[0-9]{4}[A-Z]", args.era):
        parser.error("invalid era:", args.era)

    #Creating files
    for stream in args.streams:
        dataID = f'{args.era}{stream}v{args.version}'
        attempt = 1
        config_filename = f'{config_prefix}_{dataID}_v{attempt}.py'
        exe_filename    = f'{exe_prefix}_{dataID}_v{attempt}.py'
        while any(os.path.isfile(f) for f in [config_filename, exe_filename]):
            attempt += 1
            config_filename = f'{config_prefix}_{dataID}_v{attempt}.py'
            exe_filename    = f'{exe_prefix}_{dataID}_v{attempt}.py'

        fill_dict = {
            "era": args.era,
            "stream": stream,
            "version": args.version,
            "attempt": attempt,
            "globalTag": args.globalTag,
            "unitsPerJob": args.unitsPerJob,
            "lumiMask": args.lumiMask,
            "appendDate": args.appendDate,
        }

        print("Filling template with",fill_dict)
        for template, filename in zip([config_template, exe_template], [config_filename, exe_filename]):
            with open(template, "r") as infile:
                source = string.Template(infile.read())
                result = source.substitute(fill_dict)
            with open(filename, "w") as outfile:
                outfile.write(result)
            print("Created file:", filename)

if __name__ == "__main__":
    main()
