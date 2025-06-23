#!/usr/bin/env bash

while true; do
  if [[ ! -f settings.cfg ]]; then
    echo "settings.cfg not found"
    exit 1
  elif [[ ! -z $1 ]]; then
    if [[ $1 == "-h" || $1 == "--help" ]]; then
      echo "usage: $(basename $0) SECTION_NAME ..."
      echo
      echo " SECTION_NAME: the name of a section in settings.cfg with the desired options for CRAB job"
      echo " ...: additional section(s)"
      exit 1
    elif [[ -z $(grep "^\s*\[$1\]\s*$" settings.cfg) ]]; then
      echo "Section name $1 not found"
      exit 1
    fi

    sed -i -e "s|^section: .*|section: $1|" settings.cfg
  fi

  echo Using $(grep "section: " settings.cfg)
  crab submit -c $CMSSW_BASE/src/CSCefficiency/CSCEfficiency/scripts/crabConfig.py
  shift
  [[ -z $1 ]] && break
done
