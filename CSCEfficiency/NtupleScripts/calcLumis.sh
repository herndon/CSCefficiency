which brilcalc > /dev/null
if [[ $? -ne 0 ]]; then
  echo "brilcalc not found."
  echo "set up by running the following commands:"
  echo
  echo "export NEWPATH=\$HOME/.local/bin:\$PATH"
  echo "export PATH=\$HOME/.local/bin/:/cvmfs/cms-bril.cern.ch/brilconda/bin:\$PATH"
  echo "pip install --user brilws"
  echo "export PATH=\$NEWPATH"
  echo
  echo "afterwards, add 'export PATH=\$HOME/.local/bin:\$PATH' to your .bashrc file"
  exit 1
fi

infile=$1
[[ -z $infile ]] && infile="cscEffHistoFile.root"

if [[ ! -f $infile ]]; then
  echo file not found: $infile
  exit 2
fi

runs=$(
root -l -b << EOF
TFile *infile = TFile::Open("$infile");
{
  if (infile != nullptr){
    TH2F* htemp = (TH2F*)infile->Get("segEff2DStation1Ring1ChamberRun");
    if (htemp != NULL){
      Int_t numRunBins = htemp->GetNbinsY();
      cout << htemp->GetYaxis()->GetBinLowEdge(1) << " " << htemp->GetYaxis()->GetBinUpEdge(numRunBins) << endl;
    }
    else {
      cout << "0 0" << endl;
    }
  }
  else{
    cout << "0 0" << endl;
  }
}
infile->Close();
.q
EOF
)
begin=$(cut -d ' ' -f 1 <<< $runs)
end=$(cut -d ' ' -f 2 <<< $runs)
if [[ $begin -eq 0 && $end -eq 0 ]]; then
  echo "something went wrong retrieving run range from file"
  echo "$begin-$end"
  exit 3
fi
brilcalc lumi -c web --begin $begin --end $end -u /fb -o lumi.csv
if [[ ! -f lumi.csv ]]; then
  echo error calculating lumi
  exit 3
fi
tail -2 lumi.csv
lumis=$(tail -1 lumi.csv)
rm lumi.csv
lumi=$(cut -d , -f 6 <<< $lumis)

root -l -b << EOF
TFile *infile = TFile::Open("$infile", "update");
{
  if (infile != nullptr){
    TNamed *lumi = (TNamed*)infile->Get("lumi");
    if (lumi == nullptr){
      lumi = new TNamed("lumi", "$lumi");
    }
    else {
      lumi->SetTitle("$lumi");
    }
    lumi->Write();
    cout << "Lumi updated to $lumi /fb" << endl;
  }
  else {
    cout << "File not found." << endl;
  }
}
infile->Close();
.q
EOF
