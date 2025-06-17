if [[ -z $1 ]]; then
  echo "usage: $0 JOB ..."
  echo
  echo " JOB: the name of a section in settings.cfg with the desired options for CRAB job"
  echo " ...: additional section(s)"
  exit 1
fi

while [[ $# -gt 0 ]]; do
  if [[ ! -z $1 && -f settings.cfg ]]; then
    if [[ -z $(grep "^\s*\[$1\]\s*$" settings.cfg) ]]; then
      echo "Section name $1 not found"
      exit 1
    fi

    sed -i -e "s|^section: .*|section: $1|" settings.cfg
  fi

  echo Using $(grep "^\s*\[$1\]\s*$" settings.cfg) settings
  crab submit -c $CMSSW_BASE/src/CSCefficiency/CSCEfficiency/scripts/crabConfig.py
  shift
done
