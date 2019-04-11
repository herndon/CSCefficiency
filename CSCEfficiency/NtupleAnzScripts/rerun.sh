#!/bin/bash
echo "First arg: $1" #TnP dir name
echo "Second arg: $2" #SEG or LCT
echo "Third arg: $3" #Station
echo "Fourth arg: $4" #Ring
echo "Fifth arg: $5" #+/-
dirname="/nfs_scratch/stremreich/TnPFiles/$1/ch/$2"
echo "dirname: $dirname"
lsname="$dirname/Tmp_NtupleAnzScriptsME$5$3_$4*.root"
echo "lsname: $lsname"

for filename in $lsname; do
  Tempname="${filename/Tmp/TnP}"
  TnPname="${Tempname/ME/_ME}"
  echo "Looking for $TnPname"
  if [ ! -f $TnPname ]; then
    echo "RUNNING TNP TO CREATE $TnPname"
    echo "cmd: nohup cmsRun TagandProbe.py $filename $3 &"
    nohup cmsRun TagandProbe.py $filename $3 &
  fi
done
