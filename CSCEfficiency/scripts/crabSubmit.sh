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
