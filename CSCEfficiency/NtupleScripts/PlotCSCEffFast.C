#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH2Poly.h"
#include "TLatex.h"
#include "TFrame.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMarker.h"
#include "TLine.h"
#include "TBox.h"

#include "TLegend.h"
#include "TROOT.h"
#include "TFile.h"
#include "TError.h"
#include "Math/Vector2D.h"

using namespace std;
using ROOT::Math::Polar2DVector;

const int NUM_BAD_RANGES=50;

string GetMELabel(Int_t station, Int_t ring=-1, Int_t chamber=-1);
void DrawCMSLumi(string lumi);
string Printout(const string& title, string info, bool legend=false);
int GetRingIndex(Int_t station, Int_t ring);

void PlotCSCEffFast(string filename="cscEffHistoFile.root"){
  // Initializing
  TFile * file0 = TFile::Open(filename.c_str());
  if (!file0 || file0->IsZombie()) return;

  string dataset = "";
  string lumi = "";
  string dataInfo = "";
  {
    TNamed *setName = (TNamed*)file0->Get("setName");
    if (setName != nullptr) dataset = setName->GetTitle();
    
    TNamed *lumiInfo = (TNamed*)file0->Get("lumi");
    stringstream ssLumi;
    if (lumiInfo == nullptr) cout << "Luminosity not stored in file." << endl;
    else{
      ssLumi << lumiInfo->GetTitle();
      float tempLumi; ssLumi >> tempLumi;
      ssLumi.str(""); ssLumi.clear();
      ssLumi << fixed << setprecision(1) << tempLumi;
      lumi = ssLumi.str();
    }
    if (dataset == "" || lumi == "") dataInfo = "Run 3";
    else dataInfo = dataset + " " + lumi + " fb^{-1}";
    dataInfo += " (13.6 TeV)";
  }

  char file[100];
  char name[50];
  char stationRing[10];
  char title[100];
  char label[10];

  // Flags
  int verbose = 1; // 0: None. 1: Simple printouts. 2: Simple printouts and ROOT drawing statements
  bool summaryPlots = true; // Efficiency plot per ring or for the full system
  bool chamberPlots = false; // Plots of run, LCT, LCY efficiency per chamber.  Plot printing time is lengthy
  //bool runAnalysis = false; // Run Analysis per chamber wont get done unless chamber plots are on (old run analysis printout)
  bool effCheck = true; // Run efficiency check analysis, right now only an analysis of DCFEBs
  bool DCFEBAnalysis = true; // Run DCFEB analysis for specific run ranges
  bool segmentAnalysis = false; // Segment plots for debugging

  // Constants
  float deadDCFEBThreshold = 0.10; // Efficiency threshold for dead (D)CFEBs.
  float effThreshold = 0.50; // Efficiency threshold for old file readouts.
  float maxRemovalThreshold = 0.20; // Efficiency threshold for maximal removal of low efficiency DCFEBs
  float runDepEffThreshold = 0.20; // Efficiency threshold for run-dependent chamber failures
  float lowEffChamberThreshold = 0.90; // Efficiency threshold for low efficiency chamber printouts
  float DCFEBRanges[5][2] = { {-2.0,18.0}, {14.0,34.0}, {30.0,50.0}, {46.0,66.0},{62.0,82.0}};
  double lowEff = 0.9;
  double highEff = 1.02;
  double lowEff2D = 0.5;
  
  Int_t numRunBins, firstRun, lastRun;
  {
    TH2F *htemp = (TH2F*)file0->Get("segEff2DStation1Ring1ChamberRun");
    numRunBins = htemp->GetNbinsY();
    firstRun = htemp->GetYaxis()->GetBinLowEdge(1);
    lastRun = htemp->GetYaxis()->GetBinUpEdge(numRunBins);
    cout << "Processing data for ";
    if (dataset != "") cout << dataset << " (";
    cout << "runs " << firstRun << "-" << lastRun;
    if (dataset != "") cout << ")";
    cout << endl;
  }

  string plotdir = "plots/";
  plotdir += (dataset != ""? dataset : "dataset") + "/";
  if (summaryPlots || chamberPlots || DCFEBAnalysis){
    DIR *tempdir = opendir("plots");
    if (!tempdir) mkdir("plots", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    else closedir(tempdir);
    if (dataset != ""){
      tempdir = opendir(plotdir.c_str());
      if (!tempdir) mkdir(plotdir.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
      else closedir(tempdir);
    }
  }

  // Efficiency Check text files
  if (verbose < 2) gErrorIgnoreLevel = kWarning;
  ofstream cscRunEffData; 
  //if (runAnalysis) cscRunEffData.open("cscRunEffData.txt");
  ofstream cscEffCheck, cscEffCheckSimple, badChambersHeader;
  if (effCheck){
    cscEffCheck.open("cscEffCheck.txt");
    cscEffCheckSimple.open("cscEffCheckSimple.txt");
    
    stringstream ssEffSummary;
    if (dataset != "") ssEffSummary << dataset << ": ";
    ssEffSummary << firstRun << "-" << lastRun << endl;
    ssEffSummary << "Dead DCFEB: " << int(deadDCFEBThreshold*100) << "%" << endl;
    ssEffSummary << "Efficiency Threshold: " << int(maxRemovalThreshold*100) << "%" << endl;
    ssEffSummary << "Low Efficiency Chamber Range: " << int(maxRemovalThreshold*100) 
      << "% < eff < " << int(lowEffChamberThreshold*100) << "%" << endl; 
    if (runDepEffThreshold != maxRemovalThreshold)
      ssEffSummary << " Run-Dependent Efficiency Threshold: " << int(runDepEffThreshold*100) << "%" << endl;
    cscEffCheck << Printout("Thresholds", ssEffSummary.str());
    cscEffCheckSimple << Printout("Thresholds", ssEffSummary.str());

    badChambersHeader.open("BadChambers_auto.h");
    badChambersHeader << "#ifndef BadChambers_h" << endl;
    badChambersHeader << "#define BadChambers_h" << endl << endl;
    if (dataset != "") badChambersHeader << "// " << dataset << endl;
    badChambersHeader << "void SetBadChambers(Bool_t badChamber[" << NUM_BAD_RANGES 
      << "][2][4][4][36], Int_t badChamberRun[" << NUM_BAD_RANGES 
      << "][2][4][4][36][2], Float_t badChamberLCS[" << NUM_BAD_RANGES 
      << "][2][4][4][36][2]){" << endl;
    badChambersHeader << "    // endcap 0- 1+, station 0-3 = 1-4, ring 0-3 0 is me11a, chamber 0-35 = 1-36" << endl;
    if (dataset != "") badChambersHeader << "    // " << dataset << endl;
    badChambersHeader << "    int firstRun = " << firstRun << ", lastRun = " << lastRun << ";" << endl << endl;
  }

  // Setting Plotting Styles
  gROOT->SetStyle("Plain");     // set plain TStyle
                                // gStyle->SetOptStat(111111);   // draw statistics on plots,
                                // (0) for no output
                                // gStyle->SetOptFit(1111);     // draw fit results on plot,
                                // (0) for no ouput
                                // gStyle->SetPalette(57);     // set color map
                                // gStyle->SetOptTitle(0);     // suppress title box
  gStyle->SetOptStat(0);
  gStyle->SetPalette(kBlueRedYellow);
  gStyle->SetPaintTextFormat("3.2f");
  gStyle->SetCanvasDefH(1200);
  gStyle->SetCanvasDefW(1600);

  // Begin Drawing
  TCanvas c1("c1","<Title>",0,0,1600,1200);
  Float_t oldRightMargin = c1.GetRightMargin();
  gStyle->SetTitleX(0.2);
  gStyle->SetOptStat(1);

  if (summaryPlots) {
    {
      DIR *tempdir = opendir((plotdir + "DCFEB").c_str());
      if (!tempdir) mkdir((plotdir + "DCFEB").c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
      else closedir(tempdir);
      tempdir = opendir((plotdir + "Layer").c_str());
      if (!tempdir) mkdir((plotdir + "Layer").c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
      else closedir(tempdir);
      tempdir = opendir((plotdir + "Run").c_str());
      if (!tempdir) mkdir((plotdir + "Run").c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
      else closedir(tempdir);
    }
    
    if (verbose) cout << "Drawing summary plots..." << endl;

    // Z Mass
    TH1F * zMassAll = (TH1F*)file0->Get("zMassAll");
    zMassAll->GetXaxis()->SetRangeUser(75.0,105.0);
    zMassAll->Draw();
    c1.Print((plotdir + "zMassRun3.png").c_str());



    if (segmentAnalysis){
      // Drawing Muon Segments
      TH1F * muonSegmentsFidAll = (TH1F*)file0->Get("muonSegmentsFidAll");
      muonSegmentsFidAll->GetXaxis()->SetRangeUser(-0.5,5.5);
      muonSegmentsFidAll->Draw();
      c1.Print((plotdir + "muonSegmentsFidAll.png").c_str());

      TH1F * muonSegmentsFid1 = (TH1F*)file0->Get("muonSegmentsFid1");
      muonSegmentsFid1->GetXaxis()->SetRangeUser(-0.5,5.5);
      muonSegmentsFid1->Draw();
      c1.Print((plotdir + "muonSegmentsFid1.png").c_str());

      TH1F * muonSegmentsFid2 = (TH1F*)file0->Get("muonSegmentsFid2");
      muonSegmentsFid2->GetXaxis()->SetRangeUser(-0.5,5.5);
      muonSegmentsFid2->Draw();
      c1.Print((plotdir + "muonSegmentsFid2.png").c_str());

      Double_t factor = 1.;
      muonSegmentsFidAll->Scale(factor/muonSegmentsFidAll->GetEntries());
      muonSegmentsFid1->Scale(factor/muonSegmentsFid1->GetEntries());
      muonSegmentsFid2->Scale(factor/muonSegmentsFid2->GetEntries());
      muonSegmentsFidAll->Draw();
      muonSegmentsFid2->SetLineColor(kBlue);
      muonSegmentsFid2->SetTitle("Number of Muon Segments Fiducial ring 1 vs 2");
      muonSegmentsFid2->Draw();
      muonSegmentsFid1->SetLineColor(kRed);
      muonSegmentsFid1->Draw("SAME");
      c1.Print((plotdir + "muonSegmentsFid1vsFid2.png").c_str());

      TH1F * muonSegmentsWithME21 = (TH1F*)file0->Get("muonSegmentsWithME21");
      muonSegmentsWithME21->GetXaxis()->SetRangeUser(-0.5,5.5);
      muonSegmentsWithME21->Draw();
      c1.Print((plotdir + "muonSegmentsWithME21.png").c_str());

      TH1F * muonSegmentsNoME21 = (TH1F*)file0->Get("muonSegmentsNoME21");
      muonSegmentsNoME21->GetXaxis()->SetRangeUser(-0.5,5.5);
      muonSegmentsNoME21->Draw();
      c1.Print((plotdir + "muonSegmentsNoME21.png").c_str());



      // Drawing CSC Segments
      TH1F * segmentsFidAll = (TH1F*)file0->Get("segmentsFidAll");
      segmentsFidAll->GetXaxis()->SetRangeUser(-0.5,5.5);
      segmentsFidAll->Draw();
      c1.Print((plotdir + "segmentsFidAll.png").c_str());

      TH1F * segmentsFid1 = (TH1F*)file0->Get("segmentsFid1");
      segmentsFid1->GetXaxis()->SetRangeUser(-0.5,5.5);
      segmentsFid1->Draw();
      c1.Print((plotdir + "segmentsFid1.png").c_str());

      TH1F * segmentsFid2 = (TH1F*)file0->Get("segmentsFid2");
      segmentsFid2->GetXaxis()->SetRangeUser(-0.5,5.5);
      segmentsFid2->Draw();
      c1.Print((plotdir + "segmentsFid2.png").c_str());

      segmentsFidAll->Scale(factor/segmentsFidAll->GetEntries());
      segmentsFid1->Scale(factor/segmentsFid1->GetEntries());
      segmentsFid2->Scale(factor/segmentsFid2->GetEntries());
      segmentsFidAll->Draw();
      segmentsFid2->SetLineColor(kBlue);
      segmentsFid2->SetTitle("Number of CSC Segments Fiducial ring 1 vs 2");
      segmentsFid2->Draw();
      segmentsFid1->SetLineColor(kRed);
      segmentsFid1->Draw("SAME");
      c1.Print((plotdir + "segmentsFid1vsFid2.png").c_str());



      // Drawing CSC Segments with Low/High PV
      TH1F * segmentsFid1HighPV = (TH1F*)file0->Get("segmentsFid1HighPV");
      segmentsFid1HighPV->GetXaxis()->SetRangeUser(-0.5,5.5);
      TH1F * segmentsFid2HighPV = (TH1F*)file0->Get("segmentsFid2HighPV");
      segmentsFid2HighPV->GetXaxis()->SetRangeUser(-0.5,5.5);

      segmentsFid1HighPV->Scale(factor/segmentsFid1HighPV->GetEntries());
      segmentsFid2HighPV->Scale(factor/segmentsFid2HighPV->GetEntries());
      segmentsFid2HighPV->SetLineColor(kBlue);
      segmentsFid2HighPV->SetTitle("Number of CSC Segments ring 1 vs 2 PV>=45");
      segmentsFid2HighPV->Draw();
      segmentsFid1HighPV->SetLineColor(kRed);
      segmentsFid1HighPV->Draw("SAME");
      c1.Print((plotdir + "segmentsFid1vsFid2HighPV.png").c_str());

      TH1F * segmentsFid1LowPV = (TH1F*)file0->Get("segmentsFid1LowPV");
      segmentsFid1LowPV->GetXaxis()->SetRangeUser(-0.5,5.5);
      TH1F * segmentsFid2LowPV = (TH1F*)file0->Get("segmentsFid2LowPV");
      segmentsFid2LowPV->GetXaxis()->SetRangeUser(-0.5,5.5);

      segmentsFid1LowPV->Scale(factor/segmentsFid1LowPV->GetEntries());
      segmentsFid2LowPV->Scale(factor/segmentsFid2LowPV->GetEntries());
      segmentsFid2LowPV->SetLineColor(kBlue);
      segmentsFid2LowPV->SetTitle("Number of CSC Segments ring 1 vs 2 PV<=15");
      segmentsFid2LowPV->Draw();
      segmentsFid1LowPV->SetLineColor(kRed);
      segmentsFid1LowPV->Draw("SAME");
      c1.Print((plotdir + "segmentsFid1vsFid2LowPV.png").c_str());

      segmentsFid1LowPV->SetTitle("Number of CSC Segments ring 1 PV<=15 vs >=45");
      segmentsFid1LowPV->SetLineColor(kBlue);
      segmentsFid1LowPV->Draw();
      segmentsFid1HighPV->SetLineColor(kRed);
      segmentsFid1HighPV->Draw("SAME");
      c1.Print((plotdir + "segmentsinME21LowVsHighPV.png").c_str());

      segmentsFid2LowPV->SetTitle("Number of CSC Segments ring 2 PV<=15 vs >=45");
      segmentsFid2LowPV->SetLineColor(kBlue);
      segmentsFid2LowPV->Draw();
      segmentsFid2HighPV->SetLineColor(kRed);
      segmentsFid2HighPV->Draw("SAME");
      c1.Print((plotdir + "segmentsinME22LowVsHighPV.png").c_str());



      // Drawing Muon Segments with Low/High PV
      TH1F * muonSegmentsFid1HighPV = (TH1F*)file0->Get("muonSegmentsFid1HighPV");
      muonSegmentsFid1HighPV->GetXaxis()->SetRangeUser(-0.5,5.5);
      TH1F * muonSegmentsFid2HighPV = (TH1F*)file0->Get("muonSegmentsFid2HighPV");
      muonSegmentsFid2HighPV->GetXaxis()->SetRangeUser(-0.5,5.5);

      muonSegmentsFid1HighPV->Scale(factor/muonSegmentsFid1HighPV->GetEntries());
      muonSegmentsFid2HighPV->Scale(factor/muonSegmentsFid2HighPV->GetEntries());
      muonSegmentsFid2HighPV->SetLineColor(kBlue);
      muonSegmentsFid2HighPV->SetTitle("Number of CSC Segments ring 1 vs 2 PV>=45");
      muonSegmentsFid2HighPV->Draw();
      muonSegmentsFid1HighPV->SetLineColor(kRed);
      muonSegmentsFid1HighPV->Draw("SAME");
      c1.Print((plotdir + "muonSegmentsFid1vsFid2HighPV.png").c_str());

      TH1F * muonSegmentsFid1LowPV = (TH1F*)file0->Get("muonSegmentsFid1LowPV");
      muonSegmentsFid1LowPV->GetXaxis()->SetRangeUser(-0.5,5.5);
      TH1F * muonSegmentsFid2LowPV = (TH1F*)file0->Get("muonSegmentsFid2LowPV");
      muonSegmentsFid2LowPV->GetXaxis()->SetRangeUser(-0.5,5.5);

      muonSegmentsFid1LowPV->Scale(factor/muonSegmentsFid1LowPV->GetEntries());
      muonSegmentsFid2LowPV->Scale(factor/muonSegmentsFid2LowPV->GetEntries());
      muonSegmentsFid2LowPV->SetLineColor(kBlue);
      muonSegmentsFid2LowPV->SetTitle("Number of CSC Segments ring 1 vs 2 PV<=15");
      muonSegmentsFid2LowPV->Draw();
      muonSegmentsFid1LowPV->SetLineColor(kRed);
      muonSegmentsFid1LowPV->Draw("SAME");
      c1.Print((plotdir + "muonSegmentsFid1vsFid2LowPV.png").c_str());

      muonSegmentsFid1LowPV->SetTitle("Number of CSC Segments ring 1 PV<=15 vs >=45");
      muonSegmentsFid1LowPV->SetLineColor(kBlue);
      muonSegmentsFid1LowPV->Draw();
      muonSegmentsFid1HighPV->SetLineColor(kRed);
      muonSegmentsFid1HighPV->Draw("SAME");
      c1.Print((plotdir + "muonSegmentsinME21LowVsHighPV.png").c_str());

      muonSegmentsFid2LowPV->SetTitle("Number of CSC Segments ring 2 PV<=15 vs >=45");
      muonSegmentsFid2LowPV->SetLineColor(kBlue);
      muonSegmentsFid2LowPV->Draw();
      muonSegmentsFid2HighPV->SetLineColor(kRed);
      muonSegmentsFid2HighPV->Draw("SAME");
      c1.Print((plotdir + "muonSegmentsinME22LowVsHighPV.png").c_str());



      // Drawing CSC Segments with High pT
      TH1F * segmentsFid1HighpT = (TH1F*)file0->Get("segmentsFid1HighpT");
      segmentsFid1HighpT->GetXaxis()->SetRangeUser(-0.5,5.5);
      TH1F * segmentsFid2HighpT = (TH1F*)file0->Get("segmentsFid2HighpT");
      segmentsFid2HighpT->GetXaxis()->SetRangeUser(-0.5,5.5);

      segmentsFid1HighpT->Scale(factor/segmentsFid1HighpT->GetEntries());
      segmentsFid2HighpT->Scale(factor/segmentsFid2HighpT->GetEntries());
      segmentsFid2HighpT->SetLineColor(kBlue);
      segmentsFid2HighpT->SetTitle("Number of CSC Segments Fiducial ring 1 vs 2 pT>200.");
      segmentsFid2HighpT->Draw();
      segmentsFid1HighpT->SetLineColor(kRed);
      segmentsFid1HighpT->Draw("SAME");
      c1.Print((plotdir + "segmentsFid1vsFid2HighpT.png").c_str());



      // Drawing CSC Segments with and without ME21
      TH1F * segmentsWithME21 = (TH1F*)file0->Get("segmentsWithME21");
      segmentsWithME21->GetXaxis()->SetRangeUser(-0.5,5.5);
      segmentsWithME21->Draw();
      c1.Print((plotdir + "segmentsWithME21.png").c_str());

      TH1F * segmentsNoME21 = (TH1F*)file0->Get("segmentsNoME21");
      segmentsNoME21->GetXaxis()->SetRangeUser(-0.5,5.5);
      segmentsNoME21->Draw();
      c1.Print((plotdir + "segmentsNoME21.png").c_str());

      segmentsWithME21->Scale(factor/segmentsWithME21->GetEntries());
      segmentsNoME21->Scale(factor/segmentsNoME21->GetEntries());
      segmentsWithME21->SetTitle("Number of CSC Segments w vs w/0 ME21 cases");
      segmentsWithME21->Draw();
      segmentsNoME21->SetLineColor(kRed);
      segmentsNoME21->Draw("SAME");
      c1.Print((plotdir + "segmentsWvsWoME21.png").c_str());
    }


    // Setting New Stat Block
    gStyle->SetOptStat(0);  

    // Efficiency vs. CSCs
    gPad->SetTicks();
    TH1F * segEffCSCs = (TH1F*)file0->Get("segEffCSCs");
    segEffCSCs->SetTitle("");
    segEffCSCs->GetXaxis()->SetRangeUser(70.0, 102.0);
    segEffCSCs->GetXaxis()->SetTitle("Segment Efficiency (%)");
    segEffCSCs->GetYaxis()->SetTitle("Number of CSCs ");
    segEffCSCs->GetYaxis()->SetTickSize(0.02);
    segEffCSCs->Draw("hist");
    DrawCMSLumi(dataInfo);
    {
      float leftMargin = gPad->GetLeftMargin(), topMargin = gPad->GetTopMargin();
      TLatex textStats;
      textStats.SetTextSize(0.03);
      textStats.SetTextAlign(kHAlignLeft+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.1,  "Entries:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.15, "Mean:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.2,  "RMS:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.25, "Underflow:");
      textStats.SetTextAlign(kHAlignRight+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.1,
          TString::Format("%.0f", segEffCSCs->GetEntries()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.15,
          TString::Format("%.1f", segEffCSCs->GetMean()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.2,
          TString::Format("%.1f", segEffCSCs->GetRMS()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.25,
          TString::Format("%.0f", segEffCSCs->GetBinContent(0)));
    }
    c1.Print((plotdir + "segEffCSCs.png").c_str());
    c1.Print((plotdir + "segEffCSCs.pdf").c_str());
    
    TH1F * LCTEffCSCs = (TH1F*)file0->Get("LCTEffCSCs");
    LCTEffCSCs->SetTitle("");
    LCTEffCSCs->GetXaxis()->SetRangeUser(70.0, 102.0);
    LCTEffCSCs->GetXaxis()->SetTitle("LCT Efficiency (%)");
    LCTEffCSCs->GetYaxis()->SetTitle("Number of CSCs ");
    LCTEffCSCs->GetYaxis()->SetTickSize(0.02);
    LCTEffCSCs->Draw("hist");
    DrawCMSLumi(dataInfo);
    {
      float leftMargin = gPad->GetLeftMargin(), topMargin = gPad->GetTopMargin();
      TLatex textStats;
      textStats.SetTextSize(0.03);
      textStats.SetTextAlign(kHAlignLeft+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.1,  "Entries:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.15, "Mean:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.2,  "RMS:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.25, "Underflow:");
      textStats.SetTextAlign(kHAlignRight+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.1,
          TString::Format("%.0f", LCTEffCSCs->GetEntries()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.15,
          TString::Format("%.1f", LCTEffCSCs->GetMean()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.2,
          TString::Format("%.1f", LCTEffCSCs->GetRMS()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.25,
          TString::Format("%.0f", LCTEffCSCs->GetBinContent(0)));
    }
    c1.Print((plotdir + "LCTEffCSCs.png").c_str());
    c1.Print((plotdir + "LCTEffCSCs.pdf").c_str());

    // Efficiency vs. DCFEBs
    TH1F * segEffDCFEBs = (TH1F*)file0->Get("segEffDCFEBs");
    segEffDCFEBs->SetTitle("");
    segEffDCFEBs->GetXaxis()->SetRangeUser(70.0, 102.0);
    segEffDCFEBs->GetXaxis()->SetTitle("Segment Efficiency (%)");
    segEffDCFEBs->GetYaxis()->SetTitle("Number of (D)CFEBs ");
    segEffDCFEBs->GetYaxis()->SetTickSize(0.02);
    segEffDCFEBs->Draw("hist");
    DrawCMSLumi(dataInfo);
    {
      float leftMargin = gPad->GetLeftMargin(), topMargin = gPad->GetTopMargin();
      TLatex textStats;
      textStats.SetTextSize(0.03);
      textStats.SetTextAlign(kHAlignLeft+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.1,  "Entries:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.15, "Mean:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.2,  "RMS:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.25, "Underflow:");
      textStats.SetTextAlign(kHAlignRight+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.1,
          TString::Format("%.0f", segEffDCFEBs->GetEntries()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.15,
          TString::Format("%.1f", segEffDCFEBs->GetMean()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.2,
          TString::Format("%.1f", segEffDCFEBs->GetRMS()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.25,
          TString::Format("%.0f", segEffDCFEBs->GetBinContent(0)));
    }
    c1.Print((plotdir + "segEffDCFEBs.png").c_str());
    c1.Print((plotdir + "segEffDCFEBs.pdf").c_str());
    
    TH1F * LCTEffDCFEBs = (TH1F*)file0->Get("LCTEffDCFEBs");
    LCTEffDCFEBs->SetTitle("");
    LCTEffDCFEBs->GetXaxis()->SetRangeUser(70.0, 102.0);
    LCTEffDCFEBs->GetXaxis()->SetTitle("LCT Efficiency (%)");
    LCTEffDCFEBs->GetYaxis()->SetTitle("Number of (D)CFEBs ");
    LCTEffDCFEBs->GetYaxis()->SetTickSize(0.02);
    LCTEffDCFEBs->Draw("hist");
    DrawCMSLumi(dataInfo);
    {
      float leftMargin = gPad->GetLeftMargin(), topMargin = gPad->GetTopMargin();
      TLatex textStats;
      textStats.SetTextSize(0.03);
      textStats.SetTextAlign(kHAlignLeft+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.1,  "Entries:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.15, "Mean:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.2,  "RMS:");
      textStats.DrawLatexNDC(leftMargin+0.1, 1-1.3*topMargin-0.25, "Underflow:");
      textStats.SetTextAlign(kHAlignRight+kVAlignBottom);
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.1,
          TString::Format("%.0f", LCTEffDCFEBs->GetEntries()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.15,
          TString::Format("%.1f", LCTEffDCFEBs->GetMean()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.2,
          TString::Format("%.1f", LCTEffDCFEBs->GetRMS()));
      textStats.DrawLatexNDC(leftMargin+0.3, 1-1.3*topMargin-0.25,
          TString::Format("%.0f", LCTEffDCFEBs->GetBinContent(0)));
    }
    c1.Print((plotdir + "LCTEffDCFEBs.png").c_str());
    c1.Print((plotdir + "LCTEffDCFEBs.pdf").c_str());
    gPad->SetTicks(0, 0);


    c1.SetRightMargin(0.125);

    // Drawing CSC Segment Efficiency vs. pT
    TH1F * segEffPTStation1CRing0 = (TH1F*)file0->Get("segEffPTStation1CRing0");
    TH1F * segEffPTStation1CRing1 = (TH1F*)file0->Get("segEffPTStation1CRing1");
    TH1F * segEffPTStation1CRing2 = (TH1F*)file0->Get("segEffPTStation1CRing2");
    TH1F * segEffPTStation1CRing3 = (TH1F*)file0->Get("segEffPTStation1CRing3");

    //segEffPTStation1CRing0->SetTitle("     CSC Segment Efficiency vs p_{T}         Run 3 Data");
    segEffPTStation1CRing0->SetTitle("");
    segEffPTStation1CRing0->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffPTStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
    segEffPTStation1CRing0->GetXaxis()->SetRangeUser(10.0,100.0);
    segEffPTStation1CRing0->SetLineColor(kRed);
    segEffPTStation1CRing0->SetMarkerColor(kRed);
    segEffPTStation1CRing0->SetMarkerStyle(8);
    segEffPTStation1CRing0->SetMarkerSize(0.75);
    segEffPTStation1CRing0->Draw("PE1");
    segEffPTStation1CRing1->SetLineColor(kOrange-3);
    segEffPTStation1CRing1->SetMarkerColor(kOrange-3);
    segEffPTStation1CRing1->SetMarkerStyle(8);
    segEffPTStation1CRing1->SetMarkerSize(0.75);
    segEffPTStation1CRing1->Draw("PE1 SAME");
    segEffPTStation1CRing2->SetLineColor(kBlue);
    segEffPTStation1CRing2->SetMarkerColor(kBlue);
    segEffPTStation1CRing2->SetMarkerStyle(8);
    segEffPTStation1CRing2->SetMarkerSize(0.75);
    segEffPTStation1CRing2->Draw("PE1 SAME");
    segEffPTStation1CRing3->SetMarkerStyle(8);
    segEffPTStation1CRing3->SetMarkerSize(0.75);
    segEffPTStation1CRing3->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegPT = new TLegend(0.88,0.7,0.98,0.9);
    legendSegPT->AddEntry(segEffPTStation1CRing0,"ME11a");
    legendSegPT->AddEntry(segEffPTStation1CRing1,"ME11b");
    legendSegPT->AddEntry(segEffPTStation1CRing2,"ME12");
    legendSegPT->AddEntry(segEffPTStation1CRing3,"ME13");
    legendSegPT->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME1vsPt.png").c_str());  



    // Drawing CSC Segment Efficiency vs. pT
    TH1F * segEffPTStation2CRing1 = (TH1F*)file0->Get("segEffPTStation2CRing1");
    TH1F * segEffPTStation2CRing2 = (TH1F*)file0->Get("segEffPTStation2CRing2");
    TH1F * segEffPTStation3CRing1 = (TH1F*)file0->Get("segEffPTStation3CRing1");
    TH1F * segEffPTStation3CRing2 = (TH1F*)file0->Get("segEffPTStation3CRing2");
    TH1F * segEffPTStation4CRing1 = (TH1F*)file0->Get("segEffPTStation4CRing1");
    TH1F * segEffPTStation4CRing2 = (TH1F*)file0->Get("segEffPTStation4CRing2");

    //segEffPTStation2CRing1->SetTitle("     CSC Segment Efficiency vs p_{T}         Run 3 Data");
    segEffPTStation2CRing1->SetTitle("");
    segEffPTStation2CRing1->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffPTStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
    segEffPTStation2CRing1->GetXaxis()->SetRangeUser(10.0,100.0);
    segEffPTStation2CRing1->SetLineColor(kRed);
    segEffPTStation2CRing1->SetMarkerColor(kRed);
    segEffPTStation2CRing1->SetMarkerStyle(8);
    segEffPTStation2CRing1->SetMarkerSize(0.75);
    segEffPTStation2CRing1->Draw("PE1");
    segEffPTStation3CRing1->SetLineColor(kOrange-3);
    segEffPTStation3CRing1->SetMarkerColor(kOrange-3);
    segEffPTStation3CRing1->SetMarkerStyle(8);
    segEffPTStation3CRing1->SetMarkerSize(0.75);
    segEffPTStation3CRing1->Draw("PE1 SAME");
    segEffPTStation4CRing1->SetLineColor(kOrange);
    segEffPTStation4CRing1->SetMarkerColor(kOrange);
    segEffPTStation4CRing1->SetMarkerStyle(8);
    segEffPTStation4CRing1->SetMarkerSize(0.75);
    segEffPTStation4CRing1->Draw("PE1 SAME");
    segEffPTStation2CRing2->SetLineColor(kAzure+6);
    segEffPTStation2CRing2->SetMarkerColor(kAzure+6);
    segEffPTStation2CRing2->SetMarkerStyle(8);
    segEffPTStation2CRing2->SetMarkerSize(0.75);
    segEffPTStation2CRing2->Draw("PE1 SAME");
    segEffPTStation3CRing2->SetLineColor(kBlue);
    segEffPTStation3CRing2->SetMarkerColor(kBlue);
    segEffPTStation3CRing2->SetMarkerStyle(8);
    segEffPTStation3CRing2->SetMarkerSize(0.75);
    segEffPTStation3CRing2->Draw("PE1 SAME");
    segEffPTStation4CRing2->SetLineColor(kBlue+2);
    segEffPTStation4CRing2->SetMarkerColor(kBlue+2);
    segEffPTStation4CRing2->SetMarkerStyle(8);
    segEffPTStation4CRing2->SetMarkerSize(0.75);
    segEffPTStation4CRing2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegPT2 = new TLegend(0.88,0.7,0.98,0.9);
    legendSegPT2->AddEntry(segEffPTStation2CRing1,"ME21");
    legendSegPT2->AddEntry(segEffPTStation3CRing1,"ME31");
    legendSegPT2->AddEntry(segEffPTStation4CRing1,"ME41");
    legendSegPT2->AddEntry(segEffPTStation2CRing2,"ME22");
    legendSegPT2->AddEntry(segEffPTStation3CRing2,"ME32");
    legendSegPT2->AddEntry(segEffPTStation4CRing2,"ME42");
    legendSegPT2->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME234vsPt.png").c_str());



    // Drawing CSC Segment Efficiency vs. Eta
    TH1F * segEffEtaStation1CRing0 = (TH1F*)file0->Get("segEffEtaStation1CRing0");
    TH1F * segEffEtaStation1CRing1 = (TH1F*)file0->Get("segEffEtaStation1CRing1");
    TH1F * segEffEtaStation1CRing2 = (TH1F*)file0->Get("segEffEtaStation1CRing2");
    TH1F * segEffEtaStation1CRing3 = (TH1F*)file0->Get("segEffEtaStation1CRing3");

    //segEffEtaStation1CRing0->SetTitle("     CSC Segment Efficiency vs #eta         Run 3 Data");
    segEffEtaStation1CRing0->SetTitle("");
    segEffEtaStation1CRing0->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffEtaStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
    //segEffEtaStation1CRing0->GetXaxis()->SetRangeUser(0.8,2.5);
    segEffEtaStation1CRing0->SetLineColor(kRed);
    segEffEtaStation1CRing0->SetMarkerColor(kRed);
    segEffEtaStation1CRing0->SetMarkerStyle(8);
    segEffEtaStation1CRing0->SetMarkerSize(0.75);
    segEffEtaStation1CRing0->Draw("PE1");
    segEffEtaStation1CRing1->SetLineColor(kOrange-3);
    segEffEtaStation1CRing1->SetMarkerColor(kOrange-3);
    segEffEtaStation1CRing1->SetMarkerStyle(8);
    segEffEtaStation1CRing1->SetMarkerSize(0.75);
    segEffEtaStation1CRing1->Draw("PE1 SAME");
    segEffEtaStation1CRing2->SetLineColor(kBlue);
    segEffEtaStation1CRing2->SetMarkerColor(kBlue);
    segEffEtaStation1CRing2->SetMarkerStyle(8);
    segEffEtaStation1CRing2->SetMarkerSize(0.75);
    segEffEtaStation1CRing2->Draw("PE1 SAME");
    segEffEtaStation1CRing3->SetMarkerStyle(8);
    segEffEtaStation1CRing3->SetMarkerSize(0.75);
    segEffEtaStation1CRing3->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegEta = new TLegend(0.88,0.7,0.98,0.9);
    legendSegEta->AddEntry(segEffEtaStation1CRing0,"ME11a");
    legendSegEta->AddEntry(segEffEtaStation1CRing1,"ME11b");
    legendSegEta->AddEntry(segEffEtaStation1CRing2,"ME12");
    legendSegEta->AddEntry(segEffEtaStation1CRing3,"ME13");
    legendSegEta->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME1vsEta.png").c_str());  



    // Drawing CSC Segment Efficiency vs. Eta
    TH1F * segEffEtaStation2CRing1 = (TH1F*)file0->Get("segEffEtaStation2CRing1");
    TH1F * segEffEtaStation2CRing2 = (TH1F*)file0->Get("segEffEtaStation2CRing2");
    TH1F * segEffEtaStation3CRing1 = (TH1F*)file0->Get("segEffEtaStation3CRing1");
    TH1F * segEffEtaStation3CRing2 = (TH1F*)file0->Get("segEffEtaStation3CRing2");
    TH1F * segEffEtaStation4CRing1 = (TH1F*)file0->Get("segEffEtaStation4CRing1");
    TH1F * segEffEtaStation4CRing2 = (TH1F*)file0->Get("segEffEtaStation4CRing2");

    //segEffEtaStation2CRing1->SetTitle("     CSC Segment Efficiency vs #eta         Run 3 Data");
    segEffEtaStation2CRing1->SetTitle("");
    segEffEtaStation2CRing1->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffEtaStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
    //segEffEtaStation2CRing1->GetXaxis()->SetRangeUser(0.8,2.5);
    segEffEtaStation2CRing1->SetLineColor(kRed);
    segEffEtaStation2CRing1->SetMarkerColor(kRed);
    segEffEtaStation2CRing1->SetMarkerStyle(8);
    segEffEtaStation2CRing1->SetMarkerSize(0.75);
    segEffEtaStation2CRing1->Draw("PE1");
    segEffEtaStation3CRing1->SetLineColor(kOrange-3);
    segEffEtaStation3CRing1->SetMarkerColor(kOrange-3);
    segEffEtaStation3CRing1->SetMarkerStyle(8);
    segEffEtaStation3CRing1->SetMarkerSize(0.75);
    segEffEtaStation3CRing1->Draw("PE1 SAME");
    segEffEtaStation4CRing1->SetLineColor(kOrange);
    segEffEtaStation4CRing1->SetMarkerColor(kOrange);
    segEffEtaStation4CRing1->SetMarkerStyle(8);
    segEffEtaStation4CRing1->SetMarkerSize(0.75);
    segEffEtaStation4CRing1->Draw("PE1 SAME");
    segEffEtaStation2CRing2->SetLineColor(kAzure+6);
    segEffEtaStation2CRing2->SetMarkerColor(kAzure+6);
    segEffEtaStation2CRing2->SetMarkerStyle(8);
    segEffEtaStation2CRing2->SetMarkerSize(0.75);
    segEffEtaStation2CRing2->Draw("PE1 SAME");
    segEffEtaStation3CRing2->SetLineColor(kBlue);
    segEffEtaStation3CRing2->SetMarkerColor(kBlue);
    segEffEtaStation3CRing2->SetMarkerStyle(8);
    segEffEtaStation3CRing2->SetMarkerSize(0.75);
    segEffEtaStation3CRing2->Draw("PE1 SAME");
    segEffEtaStation4CRing2->SetLineColor(kBlue+2);
    segEffEtaStation4CRing2->SetMarkerColor(kBlue+2);
    segEffEtaStation4CRing2->SetMarkerStyle(8);
    segEffEtaStation4CRing2->SetMarkerSize(0.75);
    segEffEtaStation4CRing2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegEta2 = new TLegend(0.88,0.7,0.98,0.9);
    legendSegEta2->AddEntry(segEffEtaStation2CRing1,"ME21");
    legendSegEta2->AddEntry(segEffEtaStation3CRing1,"ME31");
    legendSegEta2->AddEntry(segEffEtaStation4CRing1,"ME41");
    legendSegEta2->AddEntry(segEffEtaStation2CRing2,"ME22");
    legendSegEta2->AddEntry(segEffEtaStation3CRing2,"ME32");
    legendSegEta2->AddEntry(segEffEtaStation4CRing2,"ME42");
    legendSegEta2->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME234vsEta.png").c_str());



    // Drawing CSC Segment Efficiency vs. PV (CRing)
    TH1F * segEffPVStation1CRing0 = (TH1F*)file0->Get("segEffPVStation1CRing0");
    TH1F * segEffPVStation1CRing1 = (TH1F*)file0->Get("segEffPVStation1CRing1");
    TH1F * segEffPVStation1CRing2 = (TH1F*)file0->Get("segEffPVStation1CRing2");
    TH1F * segEffPVStation1CRing3 = (TH1F*)file0->Get("segEffPVStation1CRing3");

    //segEffPVStation1CRing0->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
    segEffPVStation1CRing0->SetTitle("");
    segEffPVStation1CRing0->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffPVStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
    segEffPVStation1CRing0->GetXaxis()->SetRangeUser(0.0,66.0);
    segEffPVStation1CRing0->SetLineColor(kRed);
    segEffPVStation1CRing0->SetMarkerColor(kRed);
    segEffPVStation1CRing0->SetMarkerStyle(8);
    segEffPVStation1CRing0->SetMarkerSize(0.75);
    segEffPVStation1CRing0->Draw("PE1");
    segEffPVStation1CRing1->SetLineColor(kOrange-3);
    segEffPVStation1CRing1->SetMarkerColor(kOrange-3);
    segEffPVStation1CRing1->SetMarkerStyle(8);
    segEffPVStation1CRing1->SetMarkerSize(0.75);
    segEffPVStation1CRing1->Draw("PE1 SAME");
    segEffPVStation1CRing2->SetLineColor(kBlue);
    segEffPVStation1CRing2->SetMarkerColor(kBlue);
    segEffPVStation1CRing2->SetMarkerStyle(8);
    segEffPVStation1CRing2->SetMarkerSize(0.75);
    segEffPVStation1CRing2->Draw("PE1 SAME");
    segEffPVStation1CRing3->SetMarkerStyle(8);
    segEffPVStation1CRing3->SetMarkerSize(0.75);
    segEffPVStation1CRing3->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegPV = new TLegend(0.88,0.7,0.98,0.9);
    legendSegPV->AddEntry(segEffPVStation1CRing0,"ME11a");
    legendSegPV->AddEntry(segEffPVStation1CRing1,"ME11b");
    legendSegPV->AddEntry(segEffPVStation1CRing2,"ME12");
    legendSegPV->AddEntry(segEffPVStation1CRing3,"ME13");
    legendSegPV->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME1vsPV.png").c_str());  



    // Drawing CSC Segment Efficiency vs. PV (CRing)
    TH1F * segEffPVStation2CRing1 = (TH1F*)file0->Get("segEffPVStation2CRing1");
    TH1F * segEffPVStation2CRing2 = (TH1F*)file0->Get("segEffPVStation2CRing2");
    TH1F * segEffPVStation3CRing1 = (TH1F*)file0->Get("segEffPVStation3CRing1");
    TH1F * segEffPVStation3CRing2 = (TH1F*)file0->Get("segEffPVStation3CRing2");
    TH1F * segEffPVStation4CRing1 = (TH1F*)file0->Get("segEffPVStation4CRing1");
    TH1F * segEffPVStation4CRing2 = (TH1F*)file0->Get("segEffPVStation4CRing2");

    //segEffPVStation2CRing1->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
    segEffPVStation2CRing1->SetTitle("");
    segEffPVStation2CRing1->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffPVStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
    segEffPVStation2CRing1->GetXaxis()->SetRangeUser(0.0,66.0);
    segEffPVStation2CRing1->SetLineColor(kRed);
    segEffPVStation2CRing1->SetMarkerColor(kRed);
    segEffPVStation2CRing1->SetMarkerStyle(8);
    segEffPVStation2CRing1->SetMarkerSize(0.75);
    segEffPVStation2CRing1->Draw("PE1");
    segEffPVStation3CRing1->SetLineColor(kOrange-3);
    segEffPVStation3CRing1->SetMarkerColor(kOrange-3);
    segEffPVStation3CRing1->SetMarkerStyle(8);
    segEffPVStation3CRing1->SetMarkerSize(0.75);
    segEffPVStation3CRing1->Draw("PE1 SAME");
    segEffPVStation4CRing1->SetLineColor(kOrange);
    segEffPVStation4CRing1->SetMarkerColor(kOrange);
    segEffPVStation4CRing1->SetMarkerStyle(8);
    segEffPVStation4CRing1->SetMarkerSize(0.75);
    segEffPVStation4CRing1->Draw("PE1 SAME");
    segEffPVStation2CRing2->SetLineColor(kAzure+6);
    segEffPVStation2CRing2->SetMarkerColor(kAzure+6);
    segEffPVStation2CRing2->SetMarkerStyle(8);
    segEffPVStation2CRing2->SetMarkerSize(0.75);
    segEffPVStation2CRing2->Draw("PE1 SAME");
    segEffPVStation3CRing2->SetLineColor(kBlue);
    segEffPVStation3CRing2->SetMarkerColor(kBlue);
    segEffPVStation3CRing2->SetMarkerStyle(8);
    segEffPVStation3CRing2->SetMarkerSize(0.75);
    segEffPVStation3CRing2->Draw("PE1 SAME");
    segEffPVStation4CRing2->SetLineColor(kBlue+2);
    segEffPVStation4CRing2->SetMarkerColor(kBlue+2);
    segEffPVStation4CRing2->SetMarkerStyle(8);
    segEffPVStation4CRing2->SetMarkerSize(0.75);
    segEffPVStation4CRing2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegPV2 = new TLegend(0.88,0.7,0.98,0.9);
    legendSegPV2->AddEntry(segEffPVStation2CRing1,"ME21");
    legendSegPV2->AddEntry(segEffPVStation3CRing1,"ME31");
    legendSegPV2->AddEntry(segEffPVStation4CRing1,"ME41");
    legendSegPV2->AddEntry(segEffPVStation2CRing2,"ME22");
    legendSegPV2->AddEntry(segEffPVStation3CRing2,"ME32");
    legendSegPV2->AddEntry(segEffPVStation4CRing2,"ME42");
    legendSegPV2->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME234vsPV.png").c_str());



    // Drawing CSC Segment Efficiency vs. PV (Ring)
    TH1F * segEffPVStation2Ring1 = (TH1F*)file0->Get("segEffPVStation2Ring1");
    TH1F * segEffPVStation2Ring2 = (TH1F*)file0->Get("segEffPVStation2Ring2");
    TH1F * segEffPVStation3Ring1 = (TH1F*)file0->Get("segEffPVStation3Ring1");
    TH1F * segEffPVStation3Ring2 = (TH1F*)file0->Get("segEffPVStation3Ring2");
    TH1F * segEffPVStation4Ring1 = (TH1F*)file0->Get("segEffPVStation4Ring1");
    TH1F * segEffPVStation4Ring2 = (TH1F*)file0->Get("segEffPVStation4Ring2");

    //segEffPVStation2Ring1->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
    segEffPVStation2Ring1->SetTitle("");
    segEffPVStation2Ring1->GetXaxis()->SetTitle("Number of Primary Vertices");
    segEffPVStation2Ring1->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffPVStation2Ring1->GetYaxis()->SetRangeUser(lowEff,highEff);
    segEffPVStation2Ring1->GetXaxis()->SetRangeUser(10.0,70.0);
    segEffPVStation2Ring1->SetLineColor(kRed);
    segEffPVStation2Ring1->SetMarkerColor(kRed);
    segEffPVStation2Ring1->SetMarkerStyle(8);
    segEffPVStation2Ring1->SetMarkerSize(0.75);
    segEffPVStation2Ring1->Draw("PE1");
    segEffPVStation3Ring1->SetLineColor(kOrange-3);
    segEffPVStation3Ring1->SetMarkerColor(kOrange-3);
    segEffPVStation3Ring1->SetMarkerStyle(8);
    segEffPVStation3Ring1->SetMarkerSize(0.75);
    segEffPVStation3Ring1->Draw("PE1 SAME");
    segEffPVStation4Ring1->SetLineColor(kOrange);
    segEffPVStation4Ring1->SetMarkerColor(kOrange);
    segEffPVStation4Ring1->SetMarkerStyle(8);
    segEffPVStation4Ring1->SetMarkerSize(0.75);
    segEffPVStation4Ring1->Draw("PE1 SAME");
    segEffPVStation2Ring2->SetLineColor(kAzure+6);
    segEffPVStation2Ring2->SetMarkerColor(kAzure+6);
    segEffPVStation2Ring2->SetMarkerStyle(8);
    segEffPVStation2Ring2->SetMarkerSize(0.75);
    segEffPVStation2Ring2->Draw("PE1 SAME");
    segEffPVStation3Ring2->SetLineColor(kBlue);
    segEffPVStation3Ring2->SetMarkerColor(kBlue);
    segEffPVStation3Ring2->SetMarkerStyle(8);
    segEffPVStation3Ring2->SetMarkerSize(0.75);
    segEffPVStation3Ring2->Draw("PE1 SAME");
    segEffPVStation4Ring2->SetLineColor(kBlue+2);
    segEffPVStation4Ring2->SetMarkerColor(kBlue+2);
    segEffPVStation4Ring2->SetMarkerStyle(8);
    segEffPVStation4Ring2->SetMarkerSize(0.75);
    segEffPVStation4Ring2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegPV3 = new TLegend(0.88,0.7,0.98,0.9);
    legendSegPV3->AddEntry(segEffPVStation2Ring1,"ME-21");
    legendSegPV3->AddEntry(segEffPVStation3Ring1,"ME-31");
    legendSegPV3->AddEntry(segEffPVStation4Ring1,"ME-41");
    legendSegPV3->AddEntry(segEffPVStation2Ring2,"ME-22");
    legendSegPV3->AddEntry(segEffPVStation3Ring2,"ME-32");
    legendSegPV3->AddEntry(segEffPVStation4Ring2,"ME-42");
    legendSegPV3->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME-234vsPV.png").c_str());



    // Drawing CSC Segment Efficiency vs. PV (Ring)
    TH1F * segEffPVStation6Ring1 = (TH1F*)file0->Get("segEffPVStation6Ring1");
    TH1F * segEffPVStation6Ring2 = (TH1F*)file0->Get("segEffPVStation6Ring2");
    TH1F * segEffPVStation7Ring1 = (TH1F*)file0->Get("segEffPVStation7Ring1");
    TH1F * segEffPVStation7Ring2 = (TH1F*)file0->Get("segEffPVStation7Ring2");
    TH1F * segEffPVStation8Ring1 = (TH1F*)file0->Get("segEffPVStation8Ring1");
    TH1F * segEffPVStation8Ring2 = (TH1F*)file0->Get("segEffPVStation8Ring2");

    //segEffPVStation6Ring1->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
    segEffPVStation6Ring1->SetTitle("");
    segEffPVStation6Ring1->GetXaxis()->SetTitle("Number of Primary Vertices");
    segEffPVStation6Ring1->GetYaxis()->SetTitle("CSC Segment Efficiency ");
    segEffPVStation6Ring1->GetYaxis()->SetRangeUser(lowEff,highEff);
    segEffPVStation6Ring1->GetXaxis()->SetRangeUser(10.0,70.0);
    segEffPVStation6Ring1->SetLineColor(kRed);
    segEffPVStation6Ring1->SetMarkerColor(kRed);
    segEffPVStation6Ring1->SetMarkerStyle(8);
    segEffPVStation6Ring1->SetMarkerSize(0.75);
    segEffPVStation6Ring1->Draw("PE1");
    segEffPVStation7Ring1->SetLineColor(kOrange-3);
    segEffPVStation7Ring1->SetMarkerColor(kOrange-3);
    segEffPVStation7Ring1->SetMarkerStyle(8);
    segEffPVStation7Ring1->SetMarkerSize(0.75);
    segEffPVStation7Ring1->Draw("PE1 SAME");
    segEffPVStation8Ring1->SetLineColor(kOrange);
    segEffPVStation8Ring1->SetMarkerColor(kOrange);
    segEffPVStation8Ring1->SetMarkerStyle(8);
    segEffPVStation8Ring1->SetMarkerSize(0.75);
    segEffPVStation8Ring1->Draw("PE1 SAME");
    segEffPVStation6Ring2->SetLineColor(kAzure+6);
    segEffPVStation6Ring2->SetMarkerColor(kAzure+6);
    segEffPVStation6Ring2->SetMarkerStyle(8);
    segEffPVStation6Ring2->SetMarkerSize(0.75);
    segEffPVStation6Ring2->Draw("PE1 SAME");
    segEffPVStation7Ring2->SetLineColor(kBlue);
    segEffPVStation7Ring2->SetMarkerColor(kBlue);
    segEffPVStation7Ring2->SetMarkerStyle(8);
    segEffPVStation7Ring2->SetMarkerSize(0.75);
    segEffPVStation7Ring2->Draw("PE1 SAME");
    segEffPVStation8Ring2->SetLineColor(kBlue+2);
    segEffPVStation8Ring2->SetMarkerColor(kBlue+2);
    segEffPVStation8Ring2->SetMarkerStyle(8);
    segEffPVStation8Ring2->SetMarkerSize(0.75);
    segEffPVStation8Ring2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendSegPV4 = new TLegend(0.88,0.7,0.98,0.9);
    legendSegPV4->AddEntry(segEffPVStation6Ring1,"ME+21");
    legendSegPV4->AddEntry(segEffPVStation7Ring1,"ME+31");
    legendSegPV4->AddEntry(segEffPVStation8Ring1,"ME+41");
    legendSegPV4->AddEntry(segEffPVStation6Ring2,"ME+22");
    legendSegPV4->AddEntry(segEffPVStation7Ring2,"ME+32");
    legendSegPV4->AddEntry(segEffPVStation8Ring2,"ME+42");
    legendSegPV4->Draw();

    c1.Print((plotdir + "CSCSegEffRun3DataME+234vsPV.png").c_str());



    // Drawing 2D CSC Segment Efficiency
    TH2F * segEff2DStationRingChamber = (TH2F*)file0->Get("segEff2DStationRingChamber");

    //sprintf(title, "CSC Seg. Eff.     Run 3%s", dataInfo.c_str());
    segEff2DStationRingChamber->SetTitle("");
    segEff2DStationRingChamber->SetMarkerSize(0.75);
    segEff2DStationRingChamber->GetYaxis()->SetTickLength(0.0015);
    segEff2DStationRingChamber->GetZaxis()->SetRangeUser(0.0,1.005);
    segEff2DStationRingChamber->GetZaxis()->SetTitle("CSC Segment Efficiency ");
    segEff2DStationRingChamber->Draw("COLZ TEXT");
    DrawCMSLumi(dataInfo);
    c1.Print((plotdir + "CSCSegEffRun3Data2DRingChamber.png").c_str());
    c1.Print((plotdir + "CSCSegEffRun3Data2DRingChamber.pdf").c_str());


    segEff2DStationRingChamber->GetZaxis()->SetRangeUser(lowEff2D,1.005);
    c1.Print((plotdir + "CSCSegEffRun3Data2DRingChamber50-100.png").c_str());
 

    

    // Drawing CSC LCT Efficiency vs. pT
    TH1F * LCTEffPTStation1CRing0 = (TH1F*)file0->Get("LCTEffPTStation1CRing0");
    TH1F * LCTEffPTStation1CRing1 = (TH1F*)file0->Get("LCTEffPTStation1CRing1");
    TH1F * LCTEffPTStation1CRing2 = (TH1F*)file0->Get("LCTEffPTStation1CRing2");
    TH1F * LCTEffPTStation1CRing3 = (TH1F*)file0->Get("LCTEffPTStation1CRing3");

    //LCTEffPTStation1CRing0->SetTitle("     CSC LCT Efficiency vs p_{T}         Run 3 Data");
    LCTEffPTStation1CRing0->SetTitle("");
    LCTEffPTStation1CRing0->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffPTStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
    LCTEffPTStation1CRing0->GetXaxis()->SetRangeUser(10.0,100.0);
    LCTEffPTStation1CRing0->SetLineColor(kRed);
    LCTEffPTStation1CRing0->SetMarkerColor(kRed);
    LCTEffPTStation1CRing0->SetMarkerStyle(8);
    LCTEffPTStation1CRing0->SetMarkerSize(0.75);
    LCTEffPTStation1CRing0->Draw("PE1");
    LCTEffPTStation1CRing1->SetLineColor(kOrange-3);
    LCTEffPTStation1CRing1->SetMarkerColor(kOrange-3);
    LCTEffPTStation1CRing1->SetMarkerStyle(8);
    LCTEffPTStation1CRing1->SetMarkerSize(0.75);
    LCTEffPTStation1CRing1->Draw("PE1 SAME");
    LCTEffPTStation1CRing2->SetLineColor(kBlue);
    LCTEffPTStation1CRing2->SetMarkerColor(kBlue);
    LCTEffPTStation1CRing2->SetMarkerStyle(8);
    LCTEffPTStation1CRing2->SetMarkerSize(0.75);
    LCTEffPTStation1CRing2->Draw("PE1 SAME");
    LCTEffPTStation1CRing3->SetMarkerStyle(8);
    LCTEffPTStation1CRing3->SetMarkerSize(0.75);
    LCTEffPTStation1CRing3->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTPT = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTPT->AddEntry(LCTEffPTStation1CRing0,"ME11a");
    legendLCTPT->AddEntry(LCTEffPTStation1CRing1,"ME11b");
    legendLCTPT->AddEntry(LCTEffPTStation1CRing2,"ME12");
    legendLCTPT->AddEntry(LCTEffPTStation1CRing3,"ME13");
    legendLCTPT->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME1vsPt.png").c_str());  



    // Drawing CSC LCT Efficiency vs. pT
    TH1F * LCTEffPTStation2CRing1 = (TH1F*)file0->Get("LCTEffPTStation2CRing1");
    TH1F * LCTEffPTStation2CRing2 = (TH1F*)file0->Get("LCTEffPTStation2CRing2");
    TH1F * LCTEffPTStation3CRing1 = (TH1F*)file0->Get("LCTEffPTStation3CRing1");
    TH1F * LCTEffPTStation3CRing2 = (TH1F*)file0->Get("LCTEffPTStation3CRing2");
    TH1F * LCTEffPTStation4CRing1 = (TH1F*)file0->Get("LCTEffPTStation4CRing1");
    TH1F * LCTEffPTStation4CRing2 = (TH1F*)file0->Get("LCTEffPTStation4CRing2");

    //LCTEffPTStation2CRing1->SetTitle("     CSC LCT Efficiency vs p_{T}         Run 3 Data");
    LCTEffPTStation2CRing1->SetTitle("");
    LCTEffPTStation2CRing1->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffPTStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
    LCTEffPTStation2CRing1->GetXaxis()->SetRangeUser(10.0,100.0);
    LCTEffPTStation2CRing1->SetLineColor(kRed);
    LCTEffPTStation2CRing1->SetMarkerColor(kRed);
    LCTEffPTStation2CRing1->SetMarkerStyle(8);
    LCTEffPTStation2CRing1->SetMarkerSize(0.75);
    LCTEffPTStation2CRing1->Draw("PE1");
    LCTEffPTStation3CRing1->SetLineColor(kOrange-3);
    LCTEffPTStation3CRing1->SetMarkerColor(kOrange-3);
    LCTEffPTStation3CRing1->SetMarkerStyle(8);
    LCTEffPTStation3CRing1->SetMarkerSize(0.75);
    LCTEffPTStation3CRing1->Draw("PE1 SAME");
    LCTEffPTStation4CRing1->SetLineColor(kOrange);
    LCTEffPTStation4CRing1->SetMarkerColor(kOrange);
    LCTEffPTStation4CRing1->SetMarkerStyle(8);
    LCTEffPTStation4CRing1->SetMarkerSize(0.75);
    LCTEffPTStation4CRing1->Draw("PE1 SAME");
    LCTEffPTStation2CRing2->SetLineColor(kAzure+6);
    LCTEffPTStation2CRing2->SetMarkerColor(kAzure+6);
    LCTEffPTStation2CRing2->SetMarkerStyle(8);
    LCTEffPTStation2CRing2->SetMarkerSize(0.75);
    LCTEffPTStation2CRing2->Draw("PE1 SAME");
    LCTEffPTStation3CRing2->SetLineColor(kBlue);
    LCTEffPTStation3CRing2->SetMarkerColor(kBlue);
    LCTEffPTStation3CRing2->SetMarkerStyle(8);
    LCTEffPTStation3CRing2->SetMarkerSize(0.75);
    LCTEffPTStation3CRing2->Draw("PE1 SAME");
    LCTEffPTStation4CRing2->SetLineColor(kBlue+2);
    LCTEffPTStation4CRing2->SetMarkerColor(kBlue+2);
    LCTEffPTStation4CRing2->SetMarkerStyle(8);
    LCTEffPTStation4CRing2->SetMarkerSize(0.75);
    LCTEffPTStation4CRing2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTPT2 = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTPT2->AddEntry(LCTEffPTStation2CRing1,"ME21");
    legendLCTPT2->AddEntry(LCTEffPTStation3CRing1,"ME31");
    legendLCTPT2->AddEntry(LCTEffPTStation4CRing1,"ME41");
    legendLCTPT2->AddEntry(LCTEffPTStation2CRing2,"ME22");
    legendLCTPT2->AddEntry(LCTEffPTStation3CRing2,"ME32");
    legendLCTPT2->AddEntry(LCTEffPTStation4CRing2,"ME42");
    legendLCTPT2->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME234vsPt.png").c_str());



    // Drawing CSC LCT Efficiency vs. Eta
    TH1F * LCTEffEtaStation1CRing0 = (TH1F*)file0->Get("LCTEffEtaStation1CRing0");
    TH1F * LCTEffEtaStation1CRing1 = (TH1F*)file0->Get("LCTEffEtaStation1CRing1");
    TH1F * LCTEffEtaStation1CRing2 = (TH1F*)file0->Get("LCTEffEtaStation1CRing2");
    TH1F * LCTEffEtaStation1CRing3 = (TH1F*)file0->Get("LCTEffEtaStation1CRing3");

    //LCTEffEtaStation1CRing0->SetTitle("     CSC LCT Efficiency vs #eta         Run 3 Data");
    LCTEffEtaStation1CRing0->SetTitle("");
    LCTEffEtaStation1CRing0->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffEtaStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
    //LCTEffEtaStation1CRing0->GetXaxis()->SetRangeUser(0.8,2.5);
    LCTEffEtaStation1CRing0->SetLineColor(kRed);
    LCTEffEtaStation1CRing0->SetMarkerColor(kRed);
    LCTEffEtaStation1CRing0->SetMarkerStyle(8);
    LCTEffEtaStation1CRing0->SetMarkerSize(0.75);
    LCTEffEtaStation1CRing0->Draw("PE1");
    LCTEffEtaStation1CRing1->SetLineColor(kOrange-3);
    LCTEffEtaStation1CRing1->SetMarkerColor(kOrange-3);
    LCTEffEtaStation1CRing1->SetMarkerStyle(8);
    LCTEffEtaStation1CRing1->SetMarkerSize(0.75);
    LCTEffEtaStation1CRing1->Draw("PE1 SAME");
    LCTEffEtaStation1CRing2->SetLineColor(kBlue);
    LCTEffEtaStation1CRing2->SetMarkerColor(kBlue);
    LCTEffEtaStation1CRing2->SetMarkerStyle(8);
    LCTEffEtaStation1CRing2->SetMarkerSize(0.75);
    LCTEffEtaStation1CRing2->Draw("PE1 SAME");
    LCTEffEtaStation1CRing3->SetMarkerStyle(8);
    LCTEffEtaStation1CRing3->SetMarkerSize(0.75);
    LCTEffEtaStation1CRing3->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTEta = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTEta->AddEntry(LCTEffEtaStation1CRing0,"ME11a");
    legendLCTEta->AddEntry(LCTEffEtaStation1CRing1,"ME11b");
    legendLCTEta->AddEntry(LCTEffEtaStation1CRing2,"ME12");
    legendLCTEta->AddEntry(LCTEffEtaStation1CRing3,"ME13");
    legendLCTEta->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME1vsEta.png").c_str());  



    // Drawing CSC LCT Efficiency vs. Eta
    TH1F * LCTEffEtaStation2CRing1 = (TH1F*)file0->Get("LCTEffEtaStation2CRing1");
    TH1F * LCTEffEtaStation2CRing2 = (TH1F*)file0->Get("LCTEffEtaStation2CRing2");
    TH1F * LCTEffEtaStation3CRing1 = (TH1F*)file0->Get("LCTEffEtaStation3CRing1");
    TH1F * LCTEffEtaStation3CRing2 = (TH1F*)file0->Get("LCTEffEtaStation3CRing2");
    TH1F * LCTEffEtaStation4CRing1 = (TH1F*)file0->Get("LCTEffEtaStation4CRing1");
    TH1F * LCTEffEtaStation4CRing2 = (TH1F*)file0->Get("LCTEffEtaStation4CRing2");

    //LCTEffEtaStation2CRing1->SetTitle("     CSC LCT Efficiency vs #eta         Run 3 Data");
    LCTEffEtaStation2CRing1->SetTitle("");
    LCTEffEtaStation2CRing1->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffEtaStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
    //LCTEffEtaStation2CRing1->GetXaxis()->SetRangeUser(0.8,2.5);
    LCTEffEtaStation2CRing1->SetLineColor(kRed);
    LCTEffEtaStation2CRing1->SetMarkerColor(kRed);
    LCTEffEtaStation2CRing1->SetMarkerStyle(8);
    LCTEffEtaStation2CRing1->SetMarkerSize(0.75);
    LCTEffEtaStation2CRing1->Draw("PE1");
    LCTEffEtaStation3CRing1->SetLineColor(kOrange-3);
    LCTEffEtaStation3CRing1->SetMarkerColor(kOrange-3);
    LCTEffEtaStation3CRing1->SetMarkerStyle(8);
    LCTEffEtaStation3CRing1->SetMarkerSize(0.75);
    LCTEffEtaStation3CRing1->Draw("PE1 SAME");
    LCTEffEtaStation4CRing1->SetLineColor(kOrange);
    LCTEffEtaStation4CRing1->SetMarkerColor(kOrange);
    LCTEffEtaStation4CRing1->SetMarkerStyle(8);
    LCTEffEtaStation4CRing1->SetMarkerSize(0.75);
    LCTEffEtaStation4CRing1->Draw("PE1 SAME");
    LCTEffEtaStation2CRing2->SetLineColor(kAzure+6);
    LCTEffEtaStation2CRing2->SetMarkerColor(kAzure+6);
    LCTEffEtaStation2CRing2->SetMarkerStyle(8);
    LCTEffEtaStation2CRing2->SetMarkerSize(0.75);
    LCTEffEtaStation2CRing2->Draw("PE1 SAME");
    LCTEffEtaStation3CRing2->SetLineColor(kBlue);
    LCTEffEtaStation3CRing2->SetMarkerColor(kBlue);
    LCTEffEtaStation3CRing2->SetMarkerStyle(8);
    LCTEffEtaStation3CRing2->SetMarkerSize(0.75);
    LCTEffEtaStation3CRing2->Draw("PE1 SAME");
    LCTEffEtaStation4CRing2->SetLineColor(kBlue+2);
    LCTEffEtaStation4CRing2->SetMarkerColor(kBlue+2);
    LCTEffEtaStation4CRing2->SetMarkerStyle(8);
    LCTEffEtaStation4CRing2->SetMarkerSize(0.75);
    LCTEffEtaStation4CRing2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTEta2 = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTEta2->AddEntry(LCTEffEtaStation2CRing1,"ME21");
    legendLCTEta2->AddEntry(LCTEffEtaStation3CRing1,"ME31");
    legendLCTEta2->AddEntry(LCTEffEtaStation4CRing1,"ME41");
    legendLCTEta2->AddEntry(LCTEffEtaStation2CRing2,"ME22");
    legendLCTEta2->AddEntry(LCTEffEtaStation3CRing2,"ME32");
    legendLCTEta2->AddEntry(LCTEffEtaStation4CRing2,"ME42");
    legendLCTEta2->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME234vsEta.png").c_str());



    // Drawing CSC LCT Efficiency vs. PV (CRing)
    TH1F * LCTEffPVStation1CRing0 = (TH1F*)file0->Get("LCTEffPVStation1CRing0");
    TH1F * LCTEffPVStation1CRing1 = (TH1F*)file0->Get("LCTEffPVStation1CRing1");
    TH1F * LCTEffPVStation1CRing2 = (TH1F*)file0->Get("LCTEffPVStation1CRing2");
    TH1F * LCTEffPVStation1CRing3 = (TH1F*)file0->Get("LCTEffPVStation1CRing3");

    //LCTEffPVStation1CRing0->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
    LCTEffPVStation1CRing0->SetTitle("");
    LCTEffPVStation1CRing0->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffPVStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
    LCTEffPVStation1CRing0->GetXaxis()->SetRangeUser(0.0,66.0);
    LCTEffPVStation1CRing0->SetLineColor(kRed);
    LCTEffPVStation1CRing0->SetMarkerColor(kRed);
    LCTEffPVStation1CRing0->SetMarkerStyle(8);
    LCTEffPVStation1CRing0->SetMarkerSize(0.75);
    LCTEffPVStation1CRing0->Draw("PE1");
    LCTEffPVStation1CRing1->SetLineColor(kOrange-3);
    LCTEffPVStation1CRing1->SetMarkerColor(kOrange-3);
    LCTEffPVStation1CRing1->SetMarkerStyle(8);
    LCTEffPVStation1CRing1->SetMarkerSize(0.75);
    LCTEffPVStation1CRing1->Draw("PE1 SAME");
    LCTEffPVStation1CRing2->SetLineColor(kBlue);
    LCTEffPVStation1CRing2->SetMarkerColor(kBlue);
    LCTEffPVStation1CRing2->SetMarkerStyle(8);
    LCTEffPVStation1CRing2->SetMarkerSize(0.75);
    LCTEffPVStation1CRing2->Draw("PE1 SAME");
    LCTEffPVStation1CRing3->SetMarkerStyle(8);
    LCTEffPVStation1CRing3->SetMarkerSize(0.75);
    LCTEffPVStation1CRing3->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTPV = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTPV->AddEntry(LCTEffPVStation1CRing0,"ME11a");
    legendLCTPV->AddEntry(LCTEffPVStation1CRing1,"ME11b");
    legendLCTPV->AddEntry(LCTEffPVStation1CRing2,"ME12");
    legendLCTPV->AddEntry(LCTEffPVStation1CRing3,"ME13");
    legendLCTPV->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME1vsPV.png").c_str());  



    // Drawing CSC LCT Efficiency vs. PV (CRing)
    TH1F * LCTEffPVStation2CRing1 = (TH1F*)file0->Get("LCTEffPVStation2CRing1");
    TH1F * LCTEffPVStation2CRing2 = (TH1F*)file0->Get("LCTEffPVStation2CRing2");
    TH1F * LCTEffPVStation3CRing1 = (TH1F*)file0->Get("LCTEffPVStation3CRing1");
    TH1F * LCTEffPVStation3CRing2 = (TH1F*)file0->Get("LCTEffPVStation3CRing2");
    TH1F * LCTEffPVStation4CRing1 = (TH1F*)file0->Get("LCTEffPVStation4CRing1");
    TH1F * LCTEffPVStation4CRing2 = (TH1F*)file0->Get("LCTEffPVStation4CRing2");

    //LCTEffPVStation2CRing1->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
    LCTEffPVStation2CRing1->SetTitle("");
    LCTEffPVStation2CRing1->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffPVStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
    LCTEffPVStation2CRing1->GetXaxis()->SetRangeUser(0.0,66.0);
    LCTEffPVStation2CRing1->SetLineColor(kRed);
    LCTEffPVStation2CRing1->SetMarkerColor(kRed);
    LCTEffPVStation2CRing1->SetMarkerStyle(8);
    LCTEffPVStation2CRing1->SetMarkerSize(0.75);
    LCTEffPVStation2CRing1->Draw("PE1");
    LCTEffPVStation3CRing1->SetLineColor(kOrange-3);
    LCTEffPVStation3CRing1->SetMarkerColor(kOrange-3);
    LCTEffPVStation3CRing1->SetMarkerStyle(8);
    LCTEffPVStation3CRing1->SetMarkerSize(0.75);
    LCTEffPVStation3CRing1->Draw("PE1 SAME");
    LCTEffPVStation4CRing1->SetLineColor(kOrange);
    LCTEffPVStation4CRing1->SetMarkerColor(kOrange);
    LCTEffPVStation4CRing1->SetMarkerStyle(8);
    LCTEffPVStation4CRing1->SetMarkerSize(0.75);
    LCTEffPVStation4CRing1->Draw("PE1 SAME");
    LCTEffPVStation2CRing2->SetLineColor(kAzure+6);
    LCTEffPVStation2CRing2->SetMarkerColor(kAzure+6);
    LCTEffPVStation2CRing2->SetMarkerStyle(8);
    LCTEffPVStation2CRing2->SetMarkerSize(0.75);
    LCTEffPVStation2CRing2->Draw("PE1 SAME");
    LCTEffPVStation3CRing2->SetLineColor(kBlue);
    LCTEffPVStation3CRing2->SetMarkerColor(kBlue);
    LCTEffPVStation3CRing2->SetMarkerStyle(8);
    LCTEffPVStation3CRing2->SetMarkerSize(0.75);
    LCTEffPVStation3CRing2->Draw("PE1 SAME");
    LCTEffPVStation4CRing2->SetLineColor(kBlue+2);
    LCTEffPVStation4CRing2->SetMarkerColor(kBlue+2);
    LCTEffPVStation4CRing2->SetMarkerStyle(8);
    LCTEffPVStation4CRing2->SetMarkerSize(0.75);
    LCTEffPVStation4CRing2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTPV2 = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTPV2->AddEntry(LCTEffPVStation2CRing1,"ME21");
    legendLCTPV2->AddEntry(LCTEffPVStation3CRing1,"ME31");
    legendLCTPV2->AddEntry(LCTEffPVStation4CRing1,"ME41");
    legendLCTPV2->AddEntry(LCTEffPVStation2CRing2,"ME22");
    legendLCTPV2->AddEntry(LCTEffPVStation3CRing2,"ME32");
    legendLCTPV2->AddEntry(LCTEffPVStation4CRing2,"ME42");
    legendLCTPV2->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME234vsPV.png").c_str());



    // Drawing CSC LCT Efficiency vs. PV (Ring)
    TH1F * LCTEffPVStation2Ring1 = (TH1F*)file0->Get("LCTEffPVStation2Ring1");
    TH1F * LCTEffPVStation2Ring2 = (TH1F*)file0->Get("LCTEffPVStation2Ring2");
    TH1F * LCTEffPVStation3Ring1 = (TH1F*)file0->Get("LCTEffPVStation3Ring1");
    TH1F * LCTEffPVStation3Ring2 = (TH1F*)file0->Get("LCTEffPVStation3Ring2");
    TH1F * LCTEffPVStation4Ring1 = (TH1F*)file0->Get("LCTEffPVStation4Ring1");
    TH1F * LCTEffPVStation4Ring2 = (TH1F*)file0->Get("LCTEffPVStation4Ring2");

    //LCTEffPVStation2Ring1->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
    LCTEffPVStation2Ring1->SetTitle("");
    LCTEffPVStation2Ring1->GetXaxis()->SetTitle("Number of Primary Vertices");
    LCTEffPVStation2Ring1->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffPVStation2Ring1->GetYaxis()->SetRangeUser(lowEff,highEff);
    LCTEffPVStation2Ring1->GetXaxis()->SetRangeUser(10.0,70.0);
    LCTEffPVStation2Ring1->SetLineColor(kRed);
    LCTEffPVStation2Ring1->SetMarkerColor(kRed);
    LCTEffPVStation2Ring1->SetMarkerStyle(8);
    LCTEffPVStation2Ring1->SetMarkerSize(0.75);
    LCTEffPVStation2Ring1->Draw("PE1");
    LCTEffPVStation3Ring1->SetLineColor(kOrange-3);
    LCTEffPVStation3Ring1->SetMarkerColor(kOrange-3);
    LCTEffPVStation3Ring1->SetMarkerStyle(8);
    LCTEffPVStation3Ring1->SetMarkerSize(0.75);
    LCTEffPVStation3Ring1->Draw("PE1 SAME");
    LCTEffPVStation4Ring1->SetLineColor(kOrange);
    LCTEffPVStation4Ring1->SetMarkerColor(kOrange);
    LCTEffPVStation4Ring1->SetMarkerStyle(8);
    LCTEffPVStation4Ring1->SetMarkerSize(0.75);
    LCTEffPVStation4Ring1->Draw("PE1 SAME");
    LCTEffPVStation2Ring2->SetLineColor(kAzure+6);
    LCTEffPVStation2Ring2->SetMarkerColor(kAzure+6);
    LCTEffPVStation2Ring2->SetMarkerStyle(8);
    LCTEffPVStation2Ring2->SetMarkerSize(0.75);
    LCTEffPVStation2Ring2->Draw("PE1 SAME");
    LCTEffPVStation3Ring2->SetLineColor(kBlue);
    LCTEffPVStation3Ring2->SetMarkerColor(kBlue);
    LCTEffPVStation3Ring2->SetMarkerStyle(8);
    LCTEffPVStation3Ring2->SetMarkerSize(0.75);
    LCTEffPVStation3Ring2->Draw("PE1 SAME");
    LCTEffPVStation4Ring2->SetLineColor(kBlue+2);
    LCTEffPVStation4Ring2->SetMarkerColor(kBlue+2);
    LCTEffPVStation4Ring2->SetMarkerStyle(8);
    LCTEffPVStation4Ring2->SetMarkerSize(0.75);
    LCTEffPVStation4Ring2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTPV3 = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTPV3->AddEntry(LCTEffPVStation2Ring1,"ME-21");
    legendLCTPV3->AddEntry(LCTEffPVStation3Ring1,"ME-31");
    legendLCTPV3->AddEntry(LCTEffPVStation4Ring1,"ME-41");
    legendLCTPV3->AddEntry(LCTEffPVStation2Ring2,"ME-22");
    legendLCTPV3->AddEntry(LCTEffPVStation3Ring2,"ME-32");
    legendLCTPV3->AddEntry(LCTEffPVStation4Ring2,"ME-42");
    legendLCTPV3->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME-234vsPV.png").c_str());



    // Drawing CSC LCT Efficiency vs. PV (Ring)
    TH1F * LCTEffPVStation6Ring1 = (TH1F*)file0->Get("LCTEffPVStation6Ring1");
    TH1F * LCTEffPVStation6Ring2 = (TH1F*)file0->Get("LCTEffPVStation6Ring2");
    TH1F * LCTEffPVStation7Ring1 = (TH1F*)file0->Get("LCTEffPVStation7Ring1");
    TH1F * LCTEffPVStation7Ring2 = (TH1F*)file0->Get("LCTEffPVStation7Ring2");
    TH1F * LCTEffPVStation8Ring1 = (TH1F*)file0->Get("LCTEffPVStation8Ring1");
    TH1F * LCTEffPVStation8Ring2 = (TH1F*)file0->Get("LCTEffPVStation8Ring2");

    //LCTEffPVStation6Ring1->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
    LCTEffPVStation6Ring1->SetTitle("");
    LCTEffPVStation6Ring1->GetXaxis()->SetTitle("Number of Primary Vertices");
    LCTEffPVStation6Ring1->GetYaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEffPVStation6Ring1->GetYaxis()->SetRangeUser(lowEff,highEff);
    LCTEffPVStation6Ring1->GetXaxis()->SetRangeUser(10.0,70.0);
    LCTEffPVStation6Ring1->SetLineColor(kRed);
    LCTEffPVStation6Ring1->SetMarkerColor(kRed);
    LCTEffPVStation6Ring1->SetMarkerStyle(8);
    LCTEffPVStation6Ring1->SetMarkerSize(0.75);
    LCTEffPVStation6Ring1->Draw("PE1");
    LCTEffPVStation7Ring1->SetLineColor(kOrange-3);
    LCTEffPVStation7Ring1->SetMarkerColor(kOrange-3);
    LCTEffPVStation7Ring1->SetMarkerStyle(8);
    LCTEffPVStation7Ring1->SetMarkerSize(0.75);
    LCTEffPVStation7Ring1->Draw("PE1 SAME");
    LCTEffPVStation8Ring1->SetLineColor(kOrange);
    LCTEffPVStation8Ring1->SetMarkerColor(kOrange);
    LCTEffPVStation8Ring1->SetMarkerStyle(8);
    LCTEffPVStation8Ring1->SetMarkerSize(0.75);
    LCTEffPVStation8Ring1->Draw("PE1 SAME");
    LCTEffPVStation6Ring2->SetLineColor(kAzure+6);
    LCTEffPVStation6Ring2->SetMarkerColor(kAzure+6);
    LCTEffPVStation6Ring2->SetMarkerStyle(8);
    LCTEffPVStation6Ring2->SetMarkerSize(0.75);
    LCTEffPVStation6Ring2->Draw("PE1 SAME");
    LCTEffPVStation7Ring2->SetLineColor(kBlue);
    LCTEffPVStation7Ring2->SetMarkerColor(kBlue);
    LCTEffPVStation7Ring2->SetMarkerStyle(8);
    LCTEffPVStation7Ring2->SetMarkerSize(0.75);
    LCTEffPVStation7Ring2->Draw("PE1 SAME");
    LCTEffPVStation8Ring2->SetLineColor(kBlue+2);
    LCTEffPVStation8Ring2->SetMarkerColor(kBlue+2);
    LCTEffPVStation8Ring2->SetMarkerStyle(8);
    LCTEffPVStation8Ring2->SetMarkerSize(0.75);
    LCTEffPVStation8Ring2->Draw("PE1 SAME");
    DrawCMSLumi(dataInfo);

    TLegend *legendLCTPV4 = new TLegend(0.88,0.7,0.98,0.9);
    legendLCTPV4->AddEntry(LCTEffPVStation6Ring1,"ME+21");
    legendLCTPV4->AddEntry(LCTEffPVStation7Ring1,"ME+31");
    legendLCTPV4->AddEntry(LCTEffPVStation8Ring1,"ME+41");
    legendLCTPV4->AddEntry(LCTEffPVStation6Ring2,"ME+22");
    legendLCTPV4->AddEntry(LCTEffPVStation7Ring2,"ME+32");
    legendLCTPV4->AddEntry(LCTEffPVStation8Ring2,"ME+42");
    legendLCTPV4->Draw();

    c1.Print((plotdir + "CSCLCTEffRun3DataME+234vsPV.png").c_str());



    // Drawing 2D CSC LCT Efficiency
    TH2F * LCTEff2DStationRingChamber = (TH2F*)file0->Get("LCTEff2DStationRingChamber");

    //sprintf(title, "CSC LCT Eff.     Run 3%s", dataInfo.c_str());
    LCTEff2DStationRingChamber->SetTitle("");
    LCTEff2DStationRingChamber->SetMarkerSize(0.75);
    LCTEff2DStationRingChamber->GetYaxis()->SetTickLength(0.0015);
    LCTEff2DStationRingChamber->GetZaxis()->SetRangeUser(0.0,1.005);
    LCTEff2DStationRingChamber->GetZaxis()->SetTitle("CSC LCT Efficiency ");
    LCTEff2DStationRingChamber->Draw("COLZ TEXT");
    DrawCMSLumi(dataInfo);
    c1.Print((plotdir + "CSCLCTEffRun3Data2DRingChamber.png").c_str());
    c1.Print((plotdir + "CSCLCTEffRun3Data2DRingChamber.pdf").c_str());

    LCTEff2DStationRingChamber->GetZaxis()->SetRangeUser(lowEff2D,1.005);
    c1.Print((plotdir + "CSCLCTEffRun3Data2DRingChamber50-100.png").c_str());


    // Drawing Detector Efficiency Plots
    {
      // Define constants
      struct Ring {
        double inner, outer;
        Ring(double i=0, double o=0) : inner(i), outer(o){}
      };
      //const Ring RADII_ME1[3]   = {Ring(101,260), Ring(281.49,455.99), Ring(511.99,676.15)};
      const Ring RADII_ME1[4]   = {Ring(71,161), Ring(161,260), Ring(281.49,455.99), Ring(511.99,676.15)};
      const Ring RADII_ME234[2] = {Ring(146.9,336.56), Ring(364.02,687.08)};
      const double PHI_START = 0.; //degrees
      const double DEG_TO_RAD = M_PI/180.0;

      for (int iiStation=0; iiStation < 8; iiStation++){
        bool isME1 = (iiStation == 0 || iiStation == 4);
        TH2Poly *detplot = new TH2Poly(
            ("csc" + GetMELabel(iiStation)).c_str(), "",
            -750, 750, -750, 750);
        for (int iiRing=0; iiRing < 4; iiRing++){
          if (!isME1 && (iiRing == 0 || iiRing == 3)) continue;

          int numChambers = (!isME1 && iiRing == 1) ? 18 : 36;
          for (int iiChamber=1; iiChamber<=numChambers; iiChamber++){
            // Get appropriate ring struct
            Ring ring;
            if (!isME1) ring = RADII_ME234[iiRing-1];
            else ring = RADII_ME1[iiRing];
            //else if (iiRing == 0) continue; //ring = RADII_ME1[0];
            //else ring = RADII_ME1[iiRing-1];

            // Get phi
            double dPhi = (360.0/numChambers)*DEG_TO_RAD;
            double phi = PHI_START*DEG_TO_RAD + dPhi*(iiChamber-1);

            // Get coordinates
            Polar2DVector v1(ring.inner, phi);
            Polar2DVector v2(ring.inner, phi+dPhi);
            Polar2DVector v3(ring.outer, phi+dPhi);
            Polar2DVector v4(ring.outer, phi);

            // Add chamber bin
            double x[4] = {v1.X(), v2.X(), v3.X(), v4.X()};
            double y[4] = {v1.Y(), v2.Y(), v3.Y(), v4.Y()};
            int binnum = detplot->AddBin(4, x, y);
            //cout << GetMELabel(iiStation, iiRing, iiChamber) << " " << binnum << endl;

            // Get "center" coordinate
            Polar2DVector center(ring.inner + 0.01, phi + 0.01);
            int findbin = detplot->FindBin(center.X(), center.Y());
            if (findbin != binnum){
              cout << "Misidentified bin (ID, bin): " << GetMELabel(iiStation, iiRing, iiChamber) << " " << findbin << endl;
              continue;
            }
            //if (isME1 && iiRing <= 1) continue;
            detplot->Fill(center.X(), center.Y(), segEff2DStationRingChamber->GetBinContent(iiChamber, GetRingIndex(iiStation, iiRing)));
          }
        }
        detplot->GetZaxis()->SetLabelSize(0.035);
        detplot->GetZaxis()->SetLabelFont(42);
        detplot->GetZaxis()->SetTitleSize(0.035);
        detplot->GetZaxis()->SetTitleFont(42);
        detplot->GetZaxis()->SetTitle((GetMELabel(iiStation) + " Segment Efficiency ").c_str());
        detplot->GetZaxis()->SetRangeUser(0.0,1.005);
        detplot->Draw("COLZ L");
        DrawCMSLumi(dataInfo);
        c1.Print((plotdir + GetMELabel(iiStation) + ".png").c_str());
      }
    }
    
    // Drawing 2D CSC Efficiency Plots
    for (Int_t iiStation=0; iiStation<8; iiStation++){
      for (Int_t iiRing=0; iiRing<4; iiRing++){
        if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&(iiRing==0||iiRing==3)) continue;
        sprintf(label, "%s", GetMELabel(iiStation, iiRing).c_str());

        // Drawing 2D CSC Segment Efficiency and Run
        sprintf(name, "segEff2DStation%dRing%dChamberRun", iiStation+1, iiRing);
        //sprintf(title, "CSC Segment Efficiency vs Chamber and Run %s", label);
        sprintf(file, (plotdir + "Run/CSCSegEffRun3Data2DChamberRun%s.png").c_str(), label);
        TH2F * segEff2DStationRingChamberRun = (TH2F*)file0->Get(name);
        segEff2DStationRingChamberRun->SetTitle("");
        segEff2DStationRingChamberRun->GetXaxis()->SetTitle("Chamber #");
        segEff2DStationRingChamberRun->GetYaxis()->SetTitle("Run ");
        segEff2DStationRingChamberRun->GetYaxis()->SetTitleOffset(1.45);
        segEff2DStationRingChamberRun->GetYaxis()->SetNoExponent();
        segEff2DStationRingChamberRun->GetXaxis()->SetTickLength(0.015);
        segEff2DStationRingChamberRun->GetYaxis()->SetTickLength(0.015);
        segEff2DStationRingChamberRun->GetYaxis()->SetLabelSize(0.026);
        segEff2DStationRingChamberRun->GetZaxis()->SetTitle((GetMELabel(iiStation, iiRing) + " Segment Efficiency ").c_str());
        segEff2DStationRingChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
        segEff2DStationRingChamberRun->SetMarkerSize(0.75);
        segEff2DStationRingChamberRun->Draw("COLZ TEXT");
        DrawCMSLumi(dataInfo);
        c1.Print(file);

        // Drawing 2D CSC Segment Efficiency and Layer
        sprintf(name, "segEff2DStation%dRing%dChamberLayer", iiStation+1, iiRing);
        //sprintf(title, "CSC Segment Efficiency vs Chamber and Layer %s", label);
        sprintf(file, (plotdir + "Layer/CSCSegEffRun3Data2DChamberLayer%s.png").c_str(), label);
        TH2F * segEff2DStationRingChamberLayer = (TH2F*)file0->Get(name);
        segEff2DStationRingChamberLayer->SetTitle("");
        segEff2DStationRingChamberLayer->GetXaxis()->SetTitle("Chamber #");
        segEff2DStationRingChamberLayer->GetYaxis()->SetTitle("Layer ");
        segEff2DStationRingChamberLayer->GetYaxis()->SetTitleOffset(1.45);
        segEff2DStationRingChamberLayer->GetXaxis()->SetTickLength(0.015);
        segEff2DStationRingChamberLayer->GetYaxis()->SetTickLength(0.015);
        segEff2DStationRingChamberLayer->GetZaxis()->SetTitle((GetMELabel(iiStation, iiRing) + " Segment Efficiency ").c_str());
        segEff2DStationRingChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
        segEff2DStationRingChamberLayer->SetMarkerSize(0.75);
        segEff2DStationRingChamberLayer->Draw("COLZ TEXT");
        DrawCMSLumi(dataInfo);
        c1.Print(file);

        // Drawing 2D CSC Segment Efficiency and DCFEB
        sprintf(name, "segEff2DStation%dRing%dChamberDCFEB", iiStation+1, iiRing);
        //sprintf(title, "CSC Segment Efficiency vs Chamber and DCFEB %s", label);
        sprintf(file, (plotdir + "DCFEB/CSCSegEffRun3Data2DChamberDCFEB%s.png").c_str(), GetMELabel(iiStation, iiRing).c_str());
        TH2F * segEff2DStationRingChamberDCFEB = (TH2F*)file0->Get(name);
        segEff2DStationRingChamberDCFEB->SetTitle("");
        segEff2DStationRingChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
        segEff2DStationRingChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
        segEff2DStationRingChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
        segEff2DStationRingChamberDCFEB->GetXaxis()->SetTickLength(0.015);
        segEff2DStationRingChamberDCFEB->GetYaxis()->SetTickLength(0.015);
        segEff2DStationRingChamberDCFEB->GetZaxis()->SetTitle((GetMELabel(iiStation, iiRing) + " Segment Efficiency ").c_str());
        segEff2DStationRingChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
        segEff2DStationRingChamberDCFEB->SetMarkerSize(0.75);
        segEff2DStationRingChamberDCFEB->Draw("COLZ TEXT");
        DrawCMSLumi(dataInfo);
        c1.Print(file);

        // Drawing 2D CSC LCT Efficiency and Run
        sprintf(name, "LCTEff2DStation%dRing%dChamberRun", iiStation+1, iiRing);
        //sprintf(title, "CSC LCT Efficiency vs Chamber and Run %s", label);
        sprintf(file, (plotdir + "Run/CSCLCTEffRun3Data2DChamberRun%s.png").c_str(), label);
        TH2F * LCTEff2DStationRingChamberRun = (TH2F*)file0->Get(name);
        LCTEff2DStationRingChamberRun->SetTitle("");
        LCTEff2DStationRingChamberRun->GetXaxis()->SetTitle("Chamber #");
        LCTEff2DStationRingChamberRun->GetYaxis()->SetTitle("Run ");
        LCTEff2DStationRingChamberRun->GetYaxis()->SetTitleOffset(1.45);
        LCTEff2DStationRingChamberRun->GetYaxis()->SetNoExponent();
        LCTEff2DStationRingChamberRun->GetXaxis()->SetTickLength(0.015);
        LCTEff2DStationRingChamberRun->GetYaxis()->SetTickLength(0.015);
        LCTEff2DStationRingChamberRun->GetYaxis()->SetLabelSize(0.026);
        LCTEff2DStationRingChamberRun->GetZaxis()->SetTitle((GetMELabel(iiStation, iiRing) + " LCT Efficiency ").c_str());
        LCTEff2DStationRingChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
        LCTEff2DStationRingChamberRun->SetMarkerSize(0.75);
        LCTEff2DStationRingChamberRun->Draw("COLZ TEXT");
        DrawCMSLumi(dataInfo);
        c1.Print(file);

        // Drawing 2D CSC LCT Efficiency and DCFEB
        sprintf(name, "LCTEff2DStation%dRing%dChamberDCFEB", iiStation+1, iiRing);
        //sprintf(title, "CSC LCT Efficiency vs Chamber and DCFEB %s", label);
        sprintf(file, (plotdir + "DCFEB/CSCLCTEffRun3Data2DChamberDCFEB%s.png").c_str(), GetMELabel(iiStation, iiRing).c_str());
        TH2F * LCTEff2DStationRingChamberDCFEB = (TH2F*)file0->Get(name);
        LCTEff2DStationRingChamberDCFEB->SetTitle("");
        LCTEff2DStationRingChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
        LCTEff2DStationRingChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
        LCTEff2DStationRingChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
        LCTEff2DStationRingChamberDCFEB->GetXaxis()->SetTickLength(0.015);
        LCTEff2DStationRingChamberDCFEB->GetYaxis()->SetTickLength(0.015);
        LCTEff2DStationRingChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
        LCTEff2DStationRingChamberDCFEB->GetZaxis()->SetTitle((GetMELabel(iiStation, iiRing) + " LCT Efficiency ").c_str());
        LCTEff2DStationRingChamberDCFEB->SetMarkerSize(0.75);
        LCTEff2DStationRingChamberDCFEB->Draw("COLZ TEXT");
        DrawCMSLumi(dataInfo);
        c1.Print(file);
      }
    }
    c1.SetRightMargin(oldRightMargin);
  }



  // Begin Chamber Plots
  if (chamberPlots){
    {
      DIR *tempdir = opendir((plotdir + "ChamberPlots").c_str());
      if (!tempdir) mkdir((plotdir + "ChamberPlots").c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
      else closedir(tempdir);
    }
    if (verbose) cout << "Drawing chamber plots..." << endl;
    for (Int_t iiStation=0; iiStation < 8; iiStation++){
      for (Int_t iiRing=0; iiRing < 4; iiRing++){
        if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&(iiRing==0||iiRing==3)) continue;
        // Check for chamber plot directory
        {
          DIR *chdir = opendir((plotdir + GetMELabel(iiStation, iiRing)).c_str());
          if (!chdir) mkdir((plotdir + GetMELabel(iiStation, iiRing)).c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
          else closedir(chdir);
        }

        sprintf(label, "%s", GetMELabel(iiStation, iiRing).c_str());
        for (Int_t iiChamber=1; iiChamber < 37; iiChamber++){
          if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&iiRing==1&&iiChamber>18) continue;

          // Drawing CSC Segment Efficiency vs. Strip LC
          sprintf(name,"segEffLCSStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
          sprintf(title, "Segment Efficiency vs Strip LC for %s/%d",label,iiChamber);
          sprintf(file, (plotdir + "ChamberPlots/%s/cscSegEffRun3Data%s-%dLCS.png").c_str(),label,label,iiChamber);

          TH1F * segEffChamberLCS = (TH1F*)file0->Get(name);
          segEffChamberLCS->SetTitle(title);
          segEffChamberLCS->GetXaxis()->SetTitle("Strip Local Coordinate");
          segEffChamberLCS->GetYaxis()->SetTitle("CSC Segment Reconstuction Efficiency");
          segEffChamberLCS->GetYaxis()->SetTitleOffset(1.45);
          segEffChamberLCS->GetXaxis()->SetTickLength(0.015);
          segEffChamberLCS->GetYaxis()->SetTickLength(0.015);
          segEffChamberLCS->GetYaxis()->SetRangeUser(0.0,1.05);
          segEffChamberLCS->SetLineColor(kBlack);
          segEffChamberLCS->SetMarkerColor(kBlack);
          segEffChamberLCS->SetMarkerStyle(8);
          segEffChamberLCS->SetMarkerSize(0.75);
          segEffChamberLCS->Draw("PE1");
          c1.Print(file);


          // Drawing CSC Segment Efficiency vs. Y LC
          sprintf(name,"segEffLCYStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
          sprintf(title,"Segment Efficiency vs Y LC for %s/%d",label,iiChamber);
          sprintf(file,(plotdir + "ChamberPlots/%s/cscSegEffRun3Data%s-%dLCY.png").c_str(),label,label,iiChamber);

          TH1F * segEffChamberLCY = (TH1F*)file0->Get(name);
          segEffChamberLCY->SetTitle(title);
          segEffChamberLCY->GetXaxis()->SetTitle("Y Local Coordinate");
          segEffChamberLCY->GetYaxis()->SetTitle("CSC Segment Reconstuction Efficiency");
          segEffChamberLCY->GetYaxis()->SetTitleOffset(1.45);
          segEffChamberLCY->GetXaxis()->SetTickLength(0.015);
          segEffChamberLCY->GetYaxis()->SetTickLength(0.015);
          segEffChamberLCY->GetYaxis()->SetRangeUser(0.0,1.05);
          segEffChamberLCY->SetLineColor(kBlack);
          segEffChamberLCY->SetMarkerColor(kBlack);
          segEffChamberLCY->SetMarkerStyle(8);
          segEffChamberLCY->SetMarkerSize(0.75);
          segEffChamberLCY->Draw("PE1");
          c1.Print(file);


          // Drawing CSC Segment Efficiency vs. Run
          sprintf(name,"segEffStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
          sprintf(title,"Segment Efficiency vs Run for %s/%d",label,iiChamber);
          sprintf(file,(plotdir + "ChamberPlots/%s/cscSegEffRun3Data%s-%dRun.png").c_str(),label,label,iiChamber);

          TH1F * segEffChamberRun = (TH1F*)file0->Get(name);
          segEffChamberRun->SetTitle(title);
          segEffChamberRun->GetXaxis()->SetTitle("Run Number");
          segEffChamberRun->GetYaxis()->SetTitle("CSC Segment Reconstuction Efficiency");
          segEffChamberRun->GetYaxis()->SetTitleOffset(1.45);
          segEffChamberRun->GetXaxis()->SetTickLength(0.015);
          segEffChamberRun->GetYaxis()->SetTickLength(0.015);
          segEffChamberRun->GetYaxis()->SetRangeUser(0.0,1.05);
          segEffChamberRun->GetXaxis()->SetRangeUser(firstRun,lastRun);
          segEffChamberRun->SetLineColor(kBlack);
          segEffChamberRun->SetMarkerColor(kBlack);
          segEffChamberRun->SetMarkerStyle(8);
          segEffChamberRun->SetMarkerSize(0.75);
          segEffChamberRun->Draw("HIST P");
          c1.Print(file);

          // Old Printing to Text File
          // first run 355100
          /*
          if (runAnalysis) {
            cscRunEffData << file << endl;
            for (Int_t ii=0; ii< lastRun-firstRun; ii++){
              if (segEffChamberRun->GetBinContent(ii)>0.0&&segEffChamberRun->GetBinContent(ii) < effThreshold){
                cscRunEffData << segEffChamberRun->GetXaxis()->GetBinCenter(ii) << " " << segEffChamberRun->GetBinContent(ii) << endl;
              }
            }
          }
          */

          // Drawing LCT Efficiency vs. Strip LC
          sprintf(name,"LCTEffLCSStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
          sprintf(title,"LCT Efficiency vs Strip LC for %s/%d",label,iiChamber);
          sprintf(file,(plotdir + "ChamberPlots/%s/cscLCTEffRun3Data%s-%dLCS.png").c_str(),label,label,iiChamber);

          TH1F * LCTEffChamberLCS = (TH1F*)file0->Get(name);
          LCTEffChamberLCS->SetTitle(title);
          LCTEffChamberLCS->GetXaxis()->SetTitle("Strip Local Coordinate");
          LCTEffChamberLCS->GetYaxis()->SetTitle("CSC LCT Reconstuction Efficiency");
          LCTEffChamberLCS->GetYaxis()->SetTitleOffset(1.45);
          LCTEffChamberLCS->GetXaxis()->SetTickLength(0.015);
          LCTEffChamberLCS->GetYaxis()->SetTickLength(0.015);
          LCTEffChamberLCS->GetYaxis()->SetRangeUser(0.0,1.05);
          LCTEffChamberLCS->SetLineColor(kBlack);
          LCTEffChamberLCS->SetMarkerColor(kBlack);
          LCTEffChamberLCS->SetMarkerStyle(8);
          LCTEffChamberLCS->SetMarkerSize(0.75);
          LCTEffChamberLCS->Draw("PE1");
          c1.Print(file);


          // Drawing LCT Efficiency vs. Y LC
          sprintf(name,"LCTEffLCYStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
          sprintf(title,"LCT Efficiency vs Y LC for %s/%d",label,iiChamber);
          sprintf(file,(plotdir + "ChamberPlots/%s/cscLCTEffRun3Data%s-%dLCY.png").c_str(),label,label,iiChamber);

          TH1F * LCTEffChamberLCY = (TH1F*)file0->Get(name);
          LCTEffChamberLCY->SetTitle(title);
          LCTEffChamberLCY->GetXaxis()->SetTitle("Y Local Coordinate");
          LCTEffChamberLCY->GetYaxis()->SetTitle("CSC LCT Reconstuction Efficiency");
          LCTEffChamberLCY->GetYaxis()->SetTitleOffset(1.45);
          LCTEffChamberLCY->GetXaxis()->SetTickLength(0.015);
          LCTEffChamberLCY->GetYaxis()->SetTickLength(0.015);
          LCTEffChamberLCY->GetYaxis()->SetRangeUser(0.0,1.05);
          LCTEffChamberLCY->SetLineColor(kBlack);
          LCTEffChamberLCY->SetMarkerColor(kBlack);
          LCTEffChamberLCY->SetMarkerStyle(8);
          LCTEffChamberLCY->SetMarkerSize(0.75);
          LCTEffChamberLCY->Draw("PE1");
          c1.Print(file);


          // Drawing LCT Efficiency vs. Run
          sprintf(name,"LCTEffStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
          sprintf(title,"LCT Efficiency vs Run for %s/%d",label,iiChamber);
          sprintf(file,(plotdir + "ChamberPlots/%s/cscLCTEffRun3Data%s-%dRun.png").c_str(),label,label,iiChamber);

          TH1F * LCTEffChamberRun = (TH1F*)file0->Get(name);
          LCTEffChamberRun->SetTitle(title);
          LCTEffChamberRun->GetXaxis()->SetTitle("Run Number");
          LCTEffChamberRun->GetYaxis()->SetTitle("CSC LCT Efficiency");
          LCTEffChamberRun->GetYaxis()->SetTitleOffset(1.45);
          LCTEffChamberRun->GetXaxis()->SetTickLength(0.015);
          LCTEffChamberRun->GetYaxis()->SetTickLength(0.015);
          LCTEffChamberRun->GetYaxis()->SetRangeUser(0.0,1.05);
          LCTEffChamberRun->GetXaxis()->SetRangeUser(firstRun,lastRun);
          LCTEffChamberRun->SetLineColor(kBlack);
          LCTEffChamberRun->SetMarkerColor(kBlack);
          LCTEffChamberRun->SetMarkerStyle(8);
          LCTEffChamberRun->SetMarkerSize(0.75);
          LCTEffChamberRun->Draw("HIST P");
          c1.Print(file);
        }
      }
    }
    cscRunEffData.close();
  }

  // Efficiency Checking
  if (effCheck){
    if (verbose) cout << "Checking efficiencies..." << endl;
    bool bBadDCFEBs[8][4][36][5] = {0};
    string sAutoHeaderChambers[8][4][36]; 
    bool runDepAnalysis = ((TH2F*)file0->Get("segEff2DStation1Ring1DCFEB1ChamberRun") != NULL);
    stringstream ssDeadChambers, ssDeadDCFEBs, ssDeadDCFEBsWithEff, ssLowEffChambers;
    stringstream ssRunDepChamberSeg, ssRunDepChamberLCT;
    stringstream ssRunDepDCFEBSeg, ssRunDepDCFEBSegDead, ssRunDepDCFEBSegDeadWithEff;
    stringstream ssRunDepDCFEBLCT, ssRunDepDCFEBLCTDead, ssRunDepDCFEBLCTDeadWithEff;
    ssLowEffChambers << fixed << setprecision(2);
    ssRunDepChamberSeg << fixed << setprecision(2);
    ssRunDepChamberLCT << fixed << setprecision(2);
    ssDeadDCFEBsWithEff << fixed << setprecision(2);
    for (Int_t iiStation=0; iiStation < 8; iiStation++){
      for (Int_t iiRing=0; iiRing < 4; iiRing++){
        if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&(iiRing==0||iiRing==3)) continue;
        Int_t totDCFEBs;
        if (iiRing==0) totDCFEBs = 3;
        else if ((iiStation == 0 || iiStation == 4) && (iiRing == 1 || iiRing == 3)) totDCFEBs = 4;
        else totDCFEBs = 5;

        for (Int_t iiChamber=1; iiChamber < 37; iiChamber++){
          if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&iiRing==1&&iiChamber>18) continue;
          stringstream ssAutoHeader;
          ssAutoHeader << fixed << setprecision(2);
          int numMaxRemoval=0, numIneffDCFEBsSeg=0, numIneffDCFEBsLCT=0;
          float lowEffChamberAvgSeg=0., lowEffChamberAvgLCT=0.;

          int rangeIndex = 0;
          string indexstr = "][";
          if (iiStation < 4) indexstr += "0][" + to_string(iiStation+1);
          else indexstr += "1][" + to_string(iiStation+1-4);
          indexstr += "-1][" + to_string(iiRing) + "][" + to_string(iiChamber) + "-1]";

          // Identifying Dead DCFEBs and Chambers
          bool bDeadChamber = false;
          for (Int_t iiDCFEB = 1; iiDCFEB < 6; iiDCFEB++){
            bool bDeadDCFEB = false;
            Float_t segEff = ((TH2F*)file0->Get(("segEff2DStation" + to_string(iiStation+1) + "Ring" + to_string(iiRing) + "ChamberDCFEB").c_str()))
              ->GetBinContent(iiChamber,iiDCFEB);
            Float_t LCTEff = ((TH2F*)file0->Get(("LCTEff2DStation" + to_string(iiStation+1) + "Ring" + to_string(iiRing) + "ChamberDCFEB").c_str()))
              ->GetBinContent(iiChamber,iiDCFEB);
            lowEffChamberAvgSeg += segEff;
            lowEffChamberAvgLCT += LCTEff;

            // Check for dead chamber
            if (segEff == 0.00){
              if (!bDeadChamber && iiDCFEB == 1) bDeadChamber = true;
              else if (bDeadChamber && iiDCFEB == totDCFEBs){
                // List dead chamber
                ssDeadChambers << GetMELabel(iiStation, iiRing, iiChamber) << endl;

                // Generate automatic array values for removal in CSCEffFast.C
                if (rangeIndex < NUM_BAD_RANGES){
                  if (ssAutoHeader.str() == "")
                    ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                  ssAutoHeader << "    // Dead Chamber" << endl;
                  ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                  ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = firstRun;  ";
                  ssAutoHeader << "badChamberRun[" << rangeIndex++ << indexstr << "[1] = lastRun;  " << endl << endl;
                }
                else if (verbose) cout << "Dead Chamber " << GetMELabel(iiStation, iiRing, iiChamber) << " all runs" << endl;
                for (Int_t iiDCFEB=0; iiDCFEB<5; iiDCFEB++)
                  bBadDCFEBs[iiStation][iiRing][iiChamber-1][iiDCFEB] = true;
              }
              continue;
            }
            else if (bDeadChamber) bDeadChamber = false;

            // Check for dead DCFEB
            if (segEff < deadDCFEBThreshold){
              bDeadDCFEB = true;
              bBadDCFEBs[iiStation][iiRing][iiChamber-1][iiDCFEB-1] = true;
              if (LCTEff < deadDCFEBThreshold){
                // List dead DCFEB (Seg and LCT)
                ssDeadDCFEBs << GetMELabel(iiStation, iiRing, iiChamber) << " DCFEB " << iiDCFEB << endl;
                ssDeadDCFEBsWithEff << GetMELabel(iiStation, iiRing, iiChamber) << " DCFEB " << iiDCFEB;
                ssDeadDCFEBsWithEff << ": (" << (segEff*100) << "%, " << (LCTEff*100) << "%)" << endl;
              }
              else{
                // List dead DCFEB (Seg only)
                ssDeadDCFEBs << GetMELabel(iiStation, iiRing, iiChamber) << " DCFEB " << iiDCFEB << " *" << endl;
                ssDeadDCFEBsWithEff << GetMELabel(iiStation, iiRing, iiChamber) << " DCFEB " << iiDCFEB;
                ssDeadDCFEBsWithEff << ": (" << (segEff*100) << "%, " << (LCTEff*100) << "%) *" << endl;
              }

              // Generate automatic array values for removal in CSCEffFast.C
              if (rangeIndex < NUM_BAD_RANGES){
                if (ssAutoHeader.str() == "")
                  ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                ssAutoHeader << "    // Dead DCFEB " << iiDCFEB;
                if (LCTEff < deadDCFEBThreshold) ssAutoHeader << " seg " << (segEff*100) << "\% LCT " << (LCTEff*100) << "\%";
                else ssAutoHeader << " seg " << (segEff*100) << "\%";
                ssAutoHeader << " all runs" << endl;
                ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = firstRun;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = lastRun;  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                ssAutoHeader << endl << endl;
              }
              else if (verbose) cout << "Dead DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " all runs" << endl;
            }
            else if (LCTEff < deadDCFEBThreshold){
              // Generate automatic array values for removal in CSCEffFast.C
              if (rangeIndex < NUM_BAD_RANGES){
                if (ssAutoHeader.str() == "")
                  ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                bDeadDCFEB = true;
                bBadDCFEBs[iiStation][iiRing][iiChamber-1][iiDCFEB-1] = true;

                ssAutoHeader << "    //  Dead DCFEB " << iiDCFEB;
                ssAutoHeader << " LCT " << (LCTEff*100) << "\% all runs" << endl;
                ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = firstRun;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = lastRun;  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                ssAutoHeader << endl << endl;
              }
              else if (verbose) cout << "Dead DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " all runs" << endl;

              // List dead DCFEB (LCT only)
              ssDeadDCFEBs << GetMELabel(iiStation, iiRing, iiChamber) << " DCFEB " << iiDCFEB << " **" << endl;
              ssDeadDCFEBsWithEff << GetMELabel(iiStation, iiRing, iiChamber) << " DCFEB " << iiDCFEB;
              ssDeadDCFEBsWithEff << ": (" << (segEff*100) << "%, " << (LCTEff*100) << "%) **" << endl;
            }

            // Maximal Removal for low efficiency DCFEBs
            if (segEff > deadDCFEBThreshold && segEff < maxRemovalThreshold){
              numMaxRemoval++;
              bBadDCFEBs[iiStation][iiRing][iiChamber-1][iiDCFEB-1] = true;
              // Generate automatic array values for removal in CSCEffFast.C
              if (rangeIndex < NUM_BAD_RANGES){
                if (ssAutoHeader.str() == "")
                  ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                ssAutoHeader << "    // Low Efficiency DCFEB " << iiDCFEB;
                if (LCTEff > deadDCFEBThreshold && LCTEff < maxRemovalThreshold)
                  ssAutoHeader << " seg " << (segEff*100) << "\% LCT " << (LCTEff*100) << "\%";
                else
                  ssAutoHeader << " seg " << (segEff*100) << "\%";
                ssAutoHeader << " all runs" << endl;
                ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = firstRun;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = lastRun;  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                ssAutoHeader << endl << endl;
              }
              else if (verbose) cout << "Low Efficiency DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " all runs" << endl;
            }
            else if (LCTEff > deadDCFEBThreshold && LCTEff < maxRemovalThreshold){
              numMaxRemoval++;
              bBadDCFEBs[iiStation][iiRing][iiChamber-1][iiDCFEB-1] = true;
              // Generate automatic array values for removal in CSCEffFast.C
              if (rangeIndex < NUM_BAD_RANGES){
                if (ssAutoHeader.str() == "")
                  ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                ssAutoHeader << "    //  Low Efficiency DCFEB " << iiDCFEB;
                ssAutoHeader << " LCT " << (LCTEff*100) << "\% all runs" << endl;
                ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = firstRun;  ";
                ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = lastRun;  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                ssAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                ssAutoHeader << endl << endl;
              }
              else if (verbose) cout << "Low Efficiency DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " all runs" << endl;
            }

            // Low efficiency flag
            if (segEff > maxRemovalThreshold && segEff < lowEffChamberThreshold){
              numIneffDCFEBsSeg++;
            }
            if (LCTEff > maxRemovalThreshold && LCTEff < lowEffChamberThreshold){
              numIneffDCFEBsLCT++;
            }

            if (numIneffDCFEBsSeg == totDCFEBs){
              ssLowEffChambers << GetMELabel(iiStation, iiRing, iiChamber) << ": ("
                << (lowEffChamberAvgSeg/totDCFEBs)*100 << "%, " << (lowEffChamberAvgLCT/totDCFEBs)*100 << "%)";
              if (numIneffDCFEBsLCT != totDCFEBs) ssLowEffChambers << " *";
              ssLowEffChambers << endl;
            }
            else if (numIneffDCFEBsLCT == totDCFEBs)
              ssLowEffChambers << GetMELabel(iiStation, iiRing, iiChamber) << ": (" 
                << (lowEffChamberAvgSeg/totDCFEBs)*100 << "%, " << (lowEffChamberAvgLCT/totDCFEBs)*100 << "%) **" << endl;
          }

          // Run-Dependent Chamber Analysis
          // NOTE: Average of 1D histogram is h->Integral()/h->GetNbinsX();
          // -> May want to eventually change runDepEffThreshold to ~10% below average of ring.
          if (!runDepAnalysis || bDeadChamber) continue;
          const int badChamberRunRangesMax = 5;
          int badChamberRunRangesIndexSeg = 0, badChamberRunRangesIndexLCT = 0;
          Int_t badChamberRunRangesSeg[badChamberRunRangesMax][2] = {0}, badChamberRunRangesLCT[badChamberRunRangesMax][2] = {0};

          bool bPrintedRunDepChamberSeg=false, bNewRunDepChamberRangeSeg=false;
          Int_t badChamberFirstRunSeg=0, badChamberLastRunSeg=0;
          bool bPrintedRunDepChamberLCT=false, bNewRunDepChamberRangeLCT=false;
          Int_t badChamberFirstRunLCT=0, badChamberLastRunLCT=0;

          Float_t runDepChamberAvgSeg=0., runDepChamberAvgLCT=0.;
          Int_t numBadRunBinsSeg=0, numBadRunBinsLCT=0;
          for (Int_t iiRunBin=1; iiRunBin<=numRunBins; iiRunBin++){
            //Int_t iiRun = firstRun + (iiRunBin-1)*(lastRun-firstRun)/numRunBins;

            Int_t numDCFEBsSeg=0, numDCFEBsLCT=0;
            for (Int_t iiDCFEB = 1; iiDCFEB<6; iiDCFEB++){
              if (iiDCFEB > totDCFEBs) break;
              sprintf(name, "segEff2DStation%dRing%dDCFEB%dChamberRun", iiStation+1, iiRing, iiDCFEB);
              Float_t segEff = ((TH2F*)file0->Get(name))->GetBinContent(iiChamber, iiRunBin);
              sprintf(name, "LCTEff2DStation%dRing%dDCFEB%dChamberRun", iiStation+1, iiRing, iiDCFEB);
              Float_t LCTEff = ((TH2F*)file0->Get(name))->GetBinContent(iiChamber, iiRunBin);
              Int_t iiRun = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin);

              // Seg Analysis
              if (segEff < runDepEffThreshold && segEff != -1){
                runDepChamberAvgSeg += segEff;
                numDCFEBsSeg++;
                if (numDCFEBsSeg == totDCFEBs){
                  numBadRunBinsSeg++;
                  // Check if chamber name was printed and, if not, print it.
                  if (!bPrintedRunDepChamberSeg){
                    ssRunDepChamberSeg << endl << GetMELabel(iiStation, iiRing, iiChamber) << " ";
                    badChamberFirstRunSeg = iiRun;
                    bPrintedRunDepChamberSeg = true;
                  }
                  // Check if there are multiple ranges being printed for a chamber
                  if (bNewRunDepChamberRangeSeg){
                    ssRunDepChamberSeg << ", ";
                    badChamberFirstRunSeg = iiRun;
                    bNewRunDepChamberRangeSeg = false;
                  }
                  //badChamberLastRunSeg = iiRun+100;
                  if (iiRunBin<numRunBins) badChamberLastRunSeg = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1);
                  else badChamberLastRunSeg = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinUpEdge(iiRunBin);
                }
              }
              else if (badChamberLastRunSeg != 0){
                // Generate automatic array values for removal in CSCEffFast.C
                if (rangeIndex < NUM_BAD_RANGES){
                  if (ssAutoHeader.str() == "")
                    ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                  ssAutoHeader << "    //  Run-Dependent Low Efficiency Chamber";
                  ssAutoHeader << " " << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << endl;
                  ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                  ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badChamberFirstRunSeg << ";  ";
                  ssAutoHeader << "badChamberRun[" << rangeIndex++ << indexstr << "[1] = " << badChamberLastRunSeg << ";  ";
                  ssAutoHeader << endl << endl;
                }
                else if (verbose) 
                  cout << "Low Efficiency Chamber " << GetMELabel(iiStation, iiRing, iiChamber) << " run " << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << endl;

                // Save the run range for the chambers
                ssRunDepChamberSeg << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << " (" << (runDepChamberAvgSeg/numBadRunBinsSeg)*100 << "%)";
                runDepChamberAvgSeg=0.;
                numBadRunBinsSeg=0;
                if (badChamberRunRangesIndexSeg < badChamberRunRangesMax){
                  badChamberRunRangesSeg[badChamberRunRangesIndexSeg][0] = badChamberFirstRunSeg;
                  badChamberRunRangesSeg[badChamberRunRangesIndexSeg++][1] = badChamberLastRunSeg;
                }
                else if (verbose) cout << "Ommitted range " << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << endl;

                badChamberFirstRunSeg = badChamberLastRunSeg = 0;
                bNewRunDepChamberRangeSeg = true;

              }


              // LCT Analysis
              if (LCTEff < runDepEffThreshold && LCTEff != -1){
                runDepChamberAvgLCT += LCTEff;
                numDCFEBsLCT++;
                if (numDCFEBsLCT == totDCFEBs){
                  numBadRunBinsLCT++;
                  // Check if chamber name was printed and, if not, print it.
                  if (!bPrintedRunDepChamberLCT){
                    ssRunDepChamberLCT << endl << GetMELabel(iiStation, iiRing, iiChamber) << " ";
                    badChamberFirstRunLCT = iiRun;
                    bPrintedRunDepChamberLCT = true;
                  }
                  // Check if there are multiple ranges being printed for a chamber
                  if (bNewRunDepChamberRangeLCT){
                    ssRunDepChamberLCT << ", ";
                    badChamberFirstRunLCT = iiRun;
                    bNewRunDepChamberRangeLCT = false;
                  }
                  //badChamberLastRunLCT = iiRun+100;
                  if (iiRunBin<numRunBins) badChamberLastRunLCT = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1);
                  else badChamberLastRunLCT = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinUpEdge(iiRunBin);
                }
              }
              else if (badChamberLastRunLCT != 0){
                // Generate automatic array values for removal in CSCEffFast.C (Suppressed for LCT)
                /*if (rangeIndex < NUM_BAD_RANGES){
                  if (ssAutoHeader.str() == "")
                    ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                  ssAutoHeader << "    //  Run-Dependent Low Efficiency Chamber";
                  ssAutoHeader << " " << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << endl;
                  ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                  ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badChamberFirstRunLCT << ";  ";
                  ssAutoHeader << "badChamberRun[" << rangeIndex++ << indexstr << "[1] = " << badChamberLastRunLCT << ";  ";
                  ssAutoHeader << endl << endl;
                }
                else if (verbose) 
                  cout << "Low Efficiency Chamber " << GetMELabel(iiStation, iiRing, iiChamber) << " run " << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << endl;
                */

                // Save the run range for the chambers
                ssRunDepChamberLCT << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << " (" << (runDepChamberAvgLCT/numBadRunBinsLCT)*100 << "%)";
                runDepChamberAvgLCT=0.;
                numBadRunBinsLCT=0;
                if (badChamberRunRangesIndexLCT < badChamberRunRangesMax){
                  badChamberRunRangesLCT[badChamberRunRangesIndexLCT][0] = badChamberFirstRunLCT;
                  badChamberRunRangesLCT[badChamberRunRangesIndexLCT++][1] = badChamberLastRunLCT;
                }
                else if (verbose) cout << "Ommitted range " << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << endl;

                badChamberFirstRunLCT = badChamberLastRunLCT = 0;
                bNewRunDepChamberRangeLCT = true;

              }
            }
          }
          // Segment Analysis (Post-loop)
          if (badChamberLastRunSeg != 0){
            // Generate automatic array values for removal in CSCEffFast.C
            if (rangeIndex < NUM_BAD_RANGES){
              if (ssAutoHeader.str() == "")
                ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
              ssAutoHeader << "    //  Run-Dependent Low Efficiency Chamber";
              ssAutoHeader << " " << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << endl;
              ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
              ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badChamberFirstRunSeg << ";  ";
              ssAutoHeader << "badChamberRun[" << rangeIndex++ << indexstr << "[1] = " << badChamberLastRunSeg << ";  ";
              ssAutoHeader << endl << endl;
            }
            else if (verbose) 
              cout << "Low Efficiency Chamber " << GetMELabel(iiStation, iiRing, iiChamber) << " run " << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << endl;

            // Save the run range for the chambers
            if (badChamberFirstRunSeg == firstRun && badChamberLastRunSeg == lastRun)
              ssRunDepChamberSeg << "all runs (" << (runDepChamberAvgSeg/numBadRunBinsSeg)*100 << "%)";
            else ssRunDepChamberSeg << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << " (" << (runDepChamberAvgSeg/numBadRunBinsSeg)*100 << "%)";
            if (badChamberRunRangesIndexSeg < badChamberRunRangesMax){
              badChamberRunRangesSeg[badChamberRunRangesIndexSeg][0] = badChamberFirstRunSeg;
              badChamberRunRangesSeg[badChamberRunRangesIndexSeg++][1] = badChamberLastRunSeg;
            }
            else if (verbose) cout << "Ommitted range " << badChamberFirstRunSeg << "-" << badChamberLastRunSeg << endl;
          }
          // LCT Analysis (Post-loop)
          if (badChamberLastRunLCT != 0){
            // Generate automatic array values for removal in CSCEffFast.C (Suppressed for LCT)
            /*
            if (rangeIndex < NUM_BAD_RANGES){
              if (ssAutoHeader.str() == "")
                ssAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
              ssAutoHeader << "    //  Run-Dependent Low Efficiency Chamber";
              ssAutoHeader << " " << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << endl;
              ssAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
              ssAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badChamberFirstRunLCT << ";  ";
              ssAutoHeader << "badChamberRun[" << rangeIndex++ << indexstr << "[1] = " << badChamberLastRunLCT << ";  ";
              ssAutoHeader << endl << endl;
            }
            else if (verbose) 
              cout << "Low Efficiency Chamber " << GetMELabel(iiStation, iiRing, iiChamber) << " run " << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << endl;
            */

            // Save the run range for the chambers
            if (badChamberFirstRunLCT == firstRun && badChamberLastRunLCT == lastRun)
              ssRunDepChamberLCT << "all runs (" << (runDepChamberAvgLCT/numBadRunBinsLCT)*100 << "%)";
            else ssRunDepChamberLCT << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << " (" << (runDepChamberAvgLCT/numBadRunBinsLCT)*100 << "%)";
            if (badChamberRunRangesIndexLCT < badChamberRunRangesMax){
              badChamberRunRangesLCT[badChamberRunRangesIndexLCT][0] = badChamberFirstRunLCT;
              badChamberRunRangesLCT[badChamberRunRangesIndexLCT++][1] = badChamberLastRunLCT;
            }
            else if (verbose) cout << "Ommitted range " << badChamberFirstRunLCT << "-" << badChamberLastRunLCT << endl;
          }



          // Run-dependent DCFEB analysis
          bool bPrintedRunDepDCFEBSeg=false, bNewRunDepDCFEBRangeSeg=false;
          Int_t badDCFEBFirstRunSeg=0, badDCFEBLastRunSeg=0;
          bool bPrintedRunDepDCFEBSegDead=false, bNewRunDepDCFEBRangeSegDead=false;
          Int_t badDCFEBFirstRunSegDead=0, badDCFEBLastRunSegDead=0;
          Int_t numBadDCFEBBinsSeg, numBadDCFEBBinsSegDead;
          Float_t sumDCFEBEffSeg;
          bool bPrintedRunDepDCFEBLCT=false, bNewRunDepDCFEBRangeLCT=false;
          Int_t badDCFEBFirstRunLCT=0, badDCFEBLastRunLCT=0;
          bool bPrintedRunDepDCFEBLCTDead=false, bNewRunDepDCFEBRangeLCTDead=false;
          Int_t badDCFEBFirstRunLCTDead=0, badDCFEBLastRunLCTDead=0;
          Int_t numBadDCFEBBinsLCT, numBadDCFEBBinsLCTDead;
          Float_t sumDCFEBEffLCT;

          string tempRunDepDCFEBSeg="", tempRunDepDCFEBSegDead="", tempRunDepDCFEBSegDeadWithEff="";
          string tempRunDepDCFEBLCT="", tempRunDepDCFEBLCTDead="", tempRunDepDCFEBLCTDeadWithEff="";
          stringstream ssTempAutoHeader;
          ssTempAutoHeader << fixed << setprecision(2);
          for (Int_t iiDCFEB=1; iiDCFEB<6; iiDCFEB++){
            if (iiDCFEB > totDCFEBs) break;
            if (bBadDCFEBs[iiStation][iiRing][iiChamber-1][iiDCFEB-1] == true) continue;
            bPrintedRunDepDCFEBSeg = bNewRunDepDCFEBRangeSeg = false;
            bPrintedRunDepDCFEBSegDead = bNewRunDepDCFEBRangeSegDead = false;
            bPrintedRunDepDCFEBLCT = bNewRunDepDCFEBRangeLCT = false;
            bPrintedRunDepDCFEBLCTDead = bNewRunDepDCFEBRangeLCTDead = false;
            sumDCFEBEffSeg = sumDCFEBEffLCT = 0;
            numBadDCFEBBinsSeg = numBadDCFEBBinsLCT = 0;
            numBadDCFEBBinsSegDead = numBadDCFEBBinsLCTDead = 0;

            for (Int_t iiRunBin=1; iiRunBin<=numRunBins; iiRunBin++){
              //Int_t iiRun = firstRun + (iiRunBin-1)*(lastRun-firstRun)/numRunBins;
              sprintf(name, "segEff2DStation%dRing%dDCFEB%dChamberRun", iiStation+1, iiRing, iiDCFEB);
              Float_t segEff = ((TH2F*)file0->Get(name))->GetBinContent(iiChamber, iiRunBin);
              sprintf(name, "LCTEff2DStation%dRing%dDCFEB%dChamberRun", iiStation+1, iiRing, iiDCFEB);
              Float_t LCTEff = ((TH2F*)file0->Get(name))->GetBinContent(iiChamber, iiRunBin);
              Int_t iiRun = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin);

              bool consideredSeg = false, consideredLCT = false;
              for (int i=0; i<badChamberRunRangesMax; i++){
                if (badChamberRunRangesSeg[i][0] == 0 && badChamberRunRangesLCT[i][0] == 0) break;
                consideredSeg = consideredSeg || (iiRun >= badChamberRunRangesSeg[i][0] && iiRun < badChamberRunRangesSeg[i][1]);
                consideredLCT = consideredLCT || (iiRun >= badChamberRunRangesLCT[i][0] && iiRun < badChamberRunRangesLCT[i][1]);
              }

              // Segment Analysis
              if (segEff < runDepEffThreshold && segEff != -1 && !consideredSeg){
                sumDCFEBEffSeg += segEff;

                // Run-specific Dead DCFEBs
                if (segEff < deadDCFEBThreshold){
                  numBadDCFEBBinsSegDead++;
                  // Check if chamber/DCFEB name was printed and, if not, print it.
                  if (!bPrintedRunDepDCFEBSegDead){
                    tempRunDepDCFEBSegDead += "\n" + GetMELabel(iiStation, iiRing, iiChamber) + " DCFEB " + to_string(iiDCFEB) + " ";
                    tempRunDepDCFEBSegDeadWithEff += "\n" + GetMELabel(iiStation, iiRing, iiChamber) + " DCFEB " + to_string(iiDCFEB) + " ";
                    badDCFEBFirstRunSegDead = iiRun;
                    bPrintedRunDepDCFEBSegDead = true;
                  }
                  // Check if there are multiple ranges being printed for a DCFEB
                  if (bNewRunDepDCFEBRangeSegDead){
                    tempRunDepDCFEBSegDead += ", ";
                    tempRunDepDCFEBSegDeadWithEff += ", ";
                    badDCFEBFirstRunSegDead = iiRun;
                    bNewRunDepDCFEBRangeSegDead = false;
                  }
                  if (iiRunBin<numRunBins) badDCFEBLastRunSegDead = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1);
                  else badDCFEBLastRunSegDead = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinUpEdge(iiRunBin);
                }
                else{
                  numBadDCFEBBinsSeg++;
                  if (badDCFEBLastRunSegDead != 0){
                    // Save the run range for the DCFEBs
                    stringstream ssAvg; ssAvg << fixed << setprecision(2) << (sumDCFEBEffSeg/numBadDCFEBBinsSegDead)*100;
                    tempRunDepDCFEBSegDead += to_string(badDCFEBFirstRunSegDead) + "-" + to_string(badDCFEBLastRunSegDead);
                    tempRunDepDCFEBSegDeadWithEff += to_string(badDCFEBFirstRunSegDead) + "-" + to_string(badDCFEBLastRunSegDead);
                    tempRunDepDCFEBSegDeadWithEff += " (" + ssAvg.str() + "%)";
                    badDCFEBFirstRunSegDead = badDCFEBLastRunSegDead = 0;
                    bNewRunDepDCFEBRangeSegDead = true;
                  }
                  // Check if chamber/DCFEB name was printed and, if not, print it.
                  if (!bPrintedRunDepDCFEBSeg){
                    tempRunDepDCFEBSeg += "\n" + GetMELabel(iiStation, iiRing, iiChamber) + " DCFEB " + to_string(iiDCFEB) + " ";
                    badDCFEBFirstRunSeg = iiRun;
                    bPrintedRunDepDCFEBSeg = true;
                  }
                  // Check if there are multiple ranges being printed for a DCFEB
                  if (bNewRunDepDCFEBRangeSeg){
                    tempRunDepDCFEBSeg += ", ";
                    badDCFEBFirstRunSeg = iiRun;
                    bNewRunDepDCFEBRangeSeg = false;
                  }
                  //badDCFEBLastRunSeg = iiRun+100;
                  if (iiRunBin<numRunBins) badDCFEBLastRunSeg = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1);
                  else badDCFEBLastRunSeg = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinUpEdge(iiRunBin);
                }
              }
              else if (badDCFEBLastRunSeg != 0){
                //Float_t avg = sumDCFEBEffSeg * (lastRun - firstRun) / ( (badDCFEBLastRunSeg - badDCFEBFirstRunSeg) * numRunBins);
                Float_t avg = sumDCFEBEffSeg / numBadDCFEBBinsSeg;
                stringstream ssAvg; ssAvg << fixed << setprecision(2) << (avg*100);

                // Generate automatic array values for removal in CSCEffFast.C
                if (rangeIndex < NUM_BAD_RANGES){
                  if (ssAutoHeader.str() == "" && ssTempAutoHeader.str() == "")
                    ssTempAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                  ssTempAutoHeader << "    //  Run-Dependent Low Efficiency DCFEB " << iiDCFEB;
                  ssTempAutoHeader << " seg " << (avg*100) << "\% " << badDCFEBFirstRunSeg << "-" << badDCFEBLastRunSeg << endl;
                  ssTempAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                  ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badDCFEBFirstRunSeg << ";  ";
                  ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = " << badDCFEBLastRunSeg << ";  ";
                  ssTempAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                  ssTempAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                  ssTempAutoHeader << endl << endl;
                }
                else if (verbose) 
                  cout << "Low Efficiency DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " run " << badDCFEBFirstRunSeg << "-" << badDCFEBLastRunSeg << endl;

                // Save the run range for the DCFEBs
                tempRunDepDCFEBSeg += to_string(badDCFEBFirstRunSeg) + "-" + to_string(badDCFEBLastRunSeg);
                tempRunDepDCFEBSeg += " (" + ssAvg.str() + "%)";
                badDCFEBFirstRunSeg = badDCFEBLastRunSeg = 0;
                sumDCFEBEffSeg = numBadDCFEBBinsSeg = 0;
                bNewRunDepDCFEBRangeSeg = true;
              }

              // LCT Analysis
              if (LCTEff < runDepEffThreshold && LCTEff != -1 && !consideredLCT){
                sumDCFEBEffLCT += LCTEff;

                // Run-specific Dead DCFEBs
                if (LCTEff < deadDCFEBThreshold){
                  numBadDCFEBBinsLCTDead++;
                  // Check if chamber/DCFEB name was printed and, if not, print it.
                  if (!bPrintedRunDepDCFEBLCTDead){
                    tempRunDepDCFEBLCTDead += "\n" + GetMELabel(iiStation, iiRing, iiChamber) + " DCFEB " + to_string(iiDCFEB) + " ";
                    tempRunDepDCFEBLCTDeadWithEff += "\n" + GetMELabel(iiStation, iiRing, iiChamber) + " DCFEB " + to_string(iiDCFEB) + " ";
                    badDCFEBFirstRunLCTDead = iiRun;
                    bPrintedRunDepDCFEBLCTDead = true;
                  }
                  // Check if there are multiple ranges being printed for a DCFEB
                  if (bNewRunDepDCFEBRangeLCTDead){
                    tempRunDepDCFEBLCTDead += ", ";
                    tempRunDepDCFEBLCTDeadWithEff += ", ";
                    badDCFEBFirstRunLCTDead = iiRun;
                    bNewRunDepDCFEBRangeLCTDead = false;
                  }
                  if (iiRunBin<numRunBins) badDCFEBLastRunLCTDead = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1);
                  else badDCFEBLastRunLCTDead = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinUpEdge(iiRunBin);
                }
                else{
                  numBadDCFEBBinsLCT++;
                  if (badDCFEBLastRunLCTDead != 0){
                    // Save the run range for the DCFEBs
                    stringstream ssAvg; ssAvg << fixed << setprecision(2) << (sumDCFEBEffLCT/numBadDCFEBBinsLCTDead)*100;
                    tempRunDepDCFEBLCTDead += to_string(badDCFEBFirstRunLCTDead) + "-" + to_string(badDCFEBLastRunLCTDead);
                    tempRunDepDCFEBLCTDeadWithEff += to_string(badDCFEBFirstRunLCTDead) + "-" + to_string(badDCFEBLastRunLCTDead);
                    tempRunDepDCFEBLCTDeadWithEff += " (" + ssAvg.str() + "%)";
                    badDCFEBFirstRunLCTDead = badDCFEBLastRunLCTDead = 0;
                    bNewRunDepDCFEBRangeLCTDead = true;
                  }
                  // Check if chamber/DCFEB name was printed and, if not, print it.
                  if (!bPrintedRunDepDCFEBLCT){
                    tempRunDepDCFEBLCT += "\n" + GetMELabel(iiStation, iiRing, iiChamber) + " DCFEB " + to_string(iiDCFEB) + " ";
                    badDCFEBFirstRunLCT = iiRun;
                    bPrintedRunDepDCFEBLCT = true;
                  }
                  // Check if there are multiple ranges being printed for a DCFEB
                  if (bNewRunDepDCFEBRangeLCT){
                    tempRunDepDCFEBLCT += ", ";
                    badDCFEBFirstRunLCT = iiRun;
                    bNewRunDepDCFEBRangeLCT = false;
                  }
                  //badDCFEBLastRunLCT = iiRun+100;
                  if (iiRunBin<numRunBins) badDCFEBLastRunLCT = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1);
                  else badDCFEBLastRunLCT = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinUpEdge(iiRunBin);
                }
              }
              else if (badDCFEBLastRunLCT != 0){
                //Float_t avg = sumDCFEBEffLCT * (lastRun - firstRun) / ( (badDCFEBLastRunLCT - badDCFEBFirstRunLCT) * numRunBins);
                Float_t avg = sumDCFEBEffLCT / numBadDCFEBBinsLCT;
                stringstream ssAvg; ssAvg << fixed << setprecision(2) << (avg*100);

                // Generate automatic array values for removal in CSCEffFast.C (Suppressed for LCT)
                /*
                if (rangeIndex < NUM_BAD_RANGES){
                  if (ssAutoHeader.str() == "" && ssTempAutoHeader.str() == "")
                    ssTempAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                  ssTempAutoHeader << "    //  Run-Dependent Low Efficiency DCFEB " << iiDCFEB;
                  ssTempAutoHeader << " LCT " << (avg*100) << "\% " << badDCFEBFirstRunLCT << "-" << badDCFEBLastRunLCT << endl;
                  ssTempAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                  ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badDCFEBFirstRunLCT << ";  ";
                  ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = " << badDCFEBLastRunLCT << ";  ";
                  ssTempAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                  ssTempAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                  ssTempAutoHeader << endl << endl;
                }
                else if (verbose) 
                  cout << "Low Efficiency DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " run " << badDCFEBFirstRunLCT << "-" << badDCFEBLastRunLCT << endl;
                */

                // Save the run range for the DCFEBs
                tempRunDepDCFEBLCT += to_string(badDCFEBFirstRunLCT) + "-" + to_string(badDCFEBLastRunLCT);
                tempRunDepDCFEBLCT += " (" + ssAvg.str() + "%)";
                badDCFEBFirstRunLCT = badDCFEBLastRunLCT = 0;
                sumDCFEBEffLCT = numBadDCFEBBinsLCT = 0;
                bNewRunDepDCFEBRangeLCT = true;
              }
            }
            // Segment Analysis (Post-loop)
            if (bPrintedRunDepDCFEBSeg) numBadDCFEBBinsSeg++;
            if (badDCFEBLastRunSeg != 0){
              //Float_t avg = sumDCFEBEffSeg * (lastRun - firstRun) / ( (badDCFEBLastRunSeg - badDCFEBFirstRunSeg) * numRunBins);
              Float_t avg = sumDCFEBEffSeg / numBadDCFEBBinsSeg;
              stringstream ssAvg; ssAvg << fixed << setprecision(2) << (avg*100);

              // Generate automatic array values for removal in CSCEffFast.C
              if (rangeIndex < NUM_BAD_RANGES){
                if (ssAutoHeader.str() == "" && ssTempAutoHeader.str() == "")
                  ssTempAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                ssTempAutoHeader << "    //  Run-Dependent Low Efficiency DCFEB " << iiDCFEB;
                ssTempAutoHeader << " seg " << (avg*100) << "\% " << badDCFEBFirstRunSeg << "-" << badDCFEBLastRunSeg << endl;
                ssTempAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badDCFEBFirstRunSeg << ";  ";
                ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = " << badDCFEBLastRunSeg << ";  ";
                ssTempAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                ssTempAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                ssTempAutoHeader << endl << endl;
              }
              else if (verbose) 
                cout << "Low Efficiency DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " run " << badDCFEBFirstRunSeg << "-" << badDCFEBLastRunSeg << endl;

              // Save the run range for the DCFEBs
              if (badDCFEBFirstRunSeg == firstRun && badDCFEBLastRunSeg == lastRun) tempRunDepDCFEBSeg += "all runs";
              else tempRunDepDCFEBSeg += to_string(badDCFEBFirstRunSeg) + "-" + to_string(badDCFEBLastRunSeg);
              tempRunDepDCFEBSeg += " (" + ssAvg.str() + "%)";
              badDCFEBFirstRunSeg = badDCFEBLastRunSeg = 0;
            }
            if (badDCFEBLastRunSegDead != 0){
              // Save the run range for the DCFEBs
              if (badDCFEBFirstRunSegDead == firstRun && badDCFEBLastRunSegDead == lastRun){
                tempRunDepDCFEBSegDead += "all runs";
                tempRunDepDCFEBSegDeadWithEff += "all runs";
              }
              else{
                stringstream ssAvg; ssAvg << fixed << setprecision(2) << (sumDCFEBEffSeg/numBadDCFEBBinsSegDead)*100;
                tempRunDepDCFEBSegDead += to_string(badDCFEBFirstRunSegDead) + "-" + to_string(badDCFEBLastRunSegDead);
                tempRunDepDCFEBSegDeadWithEff += to_string(badDCFEBFirstRunSegDead) + "-" + to_string(badDCFEBLastRunSegDead);
                tempRunDepDCFEBSegDeadWithEff += " (" + ssAvg.str() + "%)";
              }
              badDCFEBFirstRunSegDead = badDCFEBLastRunSegDead = 0;
            }
            // LCT Analysis (Post-loop)
            if (bPrintedRunDepDCFEBLCT) numBadDCFEBBinsLCT++;
            if (badDCFEBLastRunLCT != 0){
              //Float_t avg = sumDCFEBEffLCT * (lastRun - firstRun) / ( (badDCFEBLastRunLCT - badDCFEBFirstRunLCT) * numRunBins);
              Float_t avg = sumDCFEBEffLCT / numBadDCFEBBinsLCT;
              stringstream ssAvg; ssAvg << fixed << setprecision(2) << (avg*100);

              // Generate automatic array values for removal in CSCEffFast.C (Suppressed for LCT)
              /*
              if (rangeIndex < NUM_BAD_RANGES){
                if (ssAutoHeader.str() == "" && ssTempAutoHeader.str() == "")
                  ssTempAutoHeader << endl << "    // ----- " << GetMELabel(iiStation, iiRing, iiChamber) << " -----" << endl;
                ssTempAutoHeader << "    //  Run-Dependent Low Efficiency DCFEB " << iiDCFEB;
                ssTempAutoHeader << " LCT " << (avg*100) << "\% " << badDCFEBFirstRunLCT << "-" << badDCFEBLastRunLCT << endl;
                ssTempAutoHeader << "    badChamber[" << rangeIndex << indexstr << " = true;  ";
                ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[0] = " << badDCFEBFirstRunLCT << ";  ";
                ssTempAutoHeader << "badChamberRun[" << rangeIndex << indexstr << "[1] = " << badDCFEBLastRunLCT << ";  ";
                ssTempAutoHeader << "badChamberLCS[" << rangeIndex << indexstr << "[0] = " << DCFEBRanges[iiDCFEB-1][0] << ";  ";
                ssTempAutoHeader << "badChamberLCS[" << rangeIndex++ << indexstr << "[1] = " << DCFEBRanges[iiDCFEB-1][1] << ";";
                ssTempAutoHeader << endl << endl;
              }
              else if (verbose) 
                cout << "Low Efficiency DCFEB " << GetMELabel(iiStation, iiRing, iiChamber) << " " << iiDCFEB << " run " << badDCFEBFirstRunLCT << "-" << badDCFEBLastRunLCT << endl;
              */

              // Save the run range for the DCFEBs
              if (badDCFEBFirstRunLCT == firstRun && badDCFEBLastRunLCT == lastRun) tempRunDepDCFEBLCT += "all runs";
              else tempRunDepDCFEBLCT += to_string(badDCFEBFirstRunLCT) + "-" + to_string(badDCFEBLastRunLCT);
              tempRunDepDCFEBLCT += " (" + ssAvg.str() + "%)";
              badDCFEBFirstRunLCT = badDCFEBLastRunLCT = 0;
            }
            if (badDCFEBLastRunLCTDead != 0){
              // Save the run range for the DCFEBs
              if (badDCFEBFirstRunLCTDead == firstRun && badDCFEBLastRunLCTDead == lastRun){
                tempRunDepDCFEBLCTDead += "all runs";
                tempRunDepDCFEBLCTDeadWithEff += "all runs";
              }
              else{
                stringstream ssAvg; ssAvg << fixed << setprecision(2) << (sumDCFEBEffLCT/numBadDCFEBBinsLCTDead)*100;
                tempRunDepDCFEBLCTDead += to_string(badDCFEBFirstRunLCTDead) + "-" + to_string(badDCFEBLastRunLCTDead);
                tempRunDepDCFEBLCTDeadWithEff += to_string(badDCFEBFirstRunLCTDead) + "-" + to_string(badDCFEBLastRunLCTDead);
                tempRunDepDCFEBLCTDeadWithEff += " (" + ssAvg.str() + "%)";
              }
              badDCFEBFirstRunLCTDead = badDCFEBLastRunLCTDead = 0;
            }
          }
          ssRunDepDCFEBSeg << tempRunDepDCFEBSeg;
          ssRunDepDCFEBSegDead << tempRunDepDCFEBSegDead;
          ssRunDepDCFEBSegDeadWithEff << tempRunDepDCFEBSegDeadWithEff;
          ssRunDepDCFEBLCT << tempRunDepDCFEBLCT;
          ssRunDepDCFEBLCTDead << tempRunDepDCFEBLCTDead;
          ssRunDepDCFEBLCTDeadWithEff << tempRunDepDCFEBLCTDeadWithEff;
          ssAutoHeader << ssTempAutoHeader.str();

          sAutoHeaderChambers[iiStation][iiRing][iiChamber] += ssAutoHeader.str();
        }
      }
    }
    //Print Low Efficiency Chambers to File
    cscEffCheck << Printout("Low Efficiency Chambers", ssLowEffChambers.str(), true);
    //Print Dead Chambers to File
    cscEffCheck << Printout("Dead Chambers", ssDeadChambers.str());
    cscEffCheckSimple << Printout("Dead Chambers", ssDeadChambers.str());
    //Print Dead DCFEBs to File (without efficiency)
    cscEffCheckSimple << Printout("Dead DCFEBs", ssDeadDCFEBs.str(), true);
    //Print Dead DCFEBs to File (with efficiency)
    cscEffCheck << Printout("Dead DCFEBs", ssDeadDCFEBsWithEff.str(), true);
    if (runDepAnalysis){
      //Print run-dependent chamber failures (segment)
      cscEffCheck << Printout("Run-Dependent Chamber Issues (Segment)", ssRunDepChamberSeg.str());
      //Print run-dependent chamber failures (LCT)
      cscEffCheck << Printout("Run-Dependent Chamber Issues (LCT)", ssRunDepChamberLCT.str());
      //Print run-dependent DCFEB failures (segment)
      cscEffCheck << Printout("Run-Dependent DCFEB Issues (Segment)", ssRunDepDCFEBSeg.str());
      //Print run-dependent DCFEB failures (LCT)
      cscEffCheck << Printout("Run-Dependent DCFEB Issues (LCT)", ssRunDepDCFEBLCT.str());
      //Print run-dependent dead DCFEB failures (segment)
      cscEffCheck << Printout("Run-Dependent Dead DCFEBs (Segment)", ssRunDepDCFEBSegDeadWithEff.str());
      cscEffCheckSimple << Printout("Run-Dependent Dead DCFEBs (Segment)", ssRunDepDCFEBSegDead.str());
      //Print run-dependent dead DCFEB failures (LCT)
      cscEffCheck << Printout("Run-Dependent Dead DCFEBs (LCT)", ssRunDepDCFEBLCTDeadWithEff.str());
      cscEffCheckSimple << Printout("Run-Dependent Dead DCFEBs (LCT)", ssRunDepDCFEBLCTDead.str());
    }
    //Print auto-generated removal statements
    //cscEffCheck << endl;
    //cscEffCheck << endl << "Auto Header" << endl << "-----------" << endl;
    for (Int_t iiStation=0; iiStation<8; iiStation++)
      for (Int_t iiRing=0; iiRing<4; iiRing++)
        for (Int_t iiChamber=0; iiChamber<36; iiChamber++)
          badChambersHeader << sAutoHeaderChambers[iiStation][iiRing][iiChamber];
          //cscEffCheck << sAutoHeaderChambers[iiStation][iiRing][iiChamber];
    //cscEffCheck << endl;
    badChambersHeader << endl << "}" << endl << endl;
    badChambersHeader << "#endif//BadChambers_h" << endl;
    // Closing Text Files and Exiting
    cscEffCheck.close();
    cscEffCheckSimple.close();
    badChambersHeader.close();
  }

  if (DCFEBAnalysis && (TH2F*)file0->Get("segEff2DStation1Ring1DCFEB1ChamberRun") != NULL){
    if (verbose) cout << "Analyzing DCFEB plots..." << endl;
    // Check for plots/DCFEBAnalysis directory
    {
      DIR *tempdir = opendir((plotdir + "DCFEBAnalysis").c_str());
      if (!tempdir) mkdir((plotdir + "DCFEBAnalysis").c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
      else closedir(tempdir);
    }

    gStyle->SetOptStat(0);
    c1.SetRightMargin(0.135);
    for (Int_t iiStation = 0; iiStation < 8; iiStation++){
      for (Int_t iiRing = 0; iiRing < 4; iiRing++){
        if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&(iiRing==0||iiRing==3)) continue;
        int numChambers = (iiStation != 0 && iiStation != 4 && iiRing == 1) ? 18 : 36;
        Int_t totDCFEBs = 5;
        if (iiRing==0) totDCFEBs = 3;
        else if ((iiStation == 0 || iiStation == 4) && (iiRing == 1 || iiRing == 3)) totDCFEBs = 4;

        //sprintf(title, "Segment DCFEB Analysis %s", GetMELabel(iiStation, iiRing).c_str());
        sprintf(file, (plotdir + "DCFEBAnalysis/CSCSegEffRun3Data2DChamberRunCompact%s.pdf").c_str(), GetMELabel(iiStation,iiRing).c_str());
        c1.Print(((string)file + "[").c_str());
        for (Int_t iiPage=0; iiPage*10<numRunBins; iiPage++){
          Int_t numBins = (numRunBins-iiPage*10 > 10)? 10 : numRunBins-iiPage*10;

          sprintf(name, "segEff2DStation%dRing%dDCFEBChamberRunCompact%d", iiStation+1, iiRing, iiPage);
          TH2F * hcompactSeg = new TH2F(name, "", numChambers, 0.5, numChambers+0.5, numBins*totDCFEBs, 0, numBins*totDCFEBs);
          for (Int_t iiChamber=1; iiChamber <= numChambers; iiChamber++){ 
            hcompactSeg->GetXaxis()->SetBinLabel(iiChamber, to_string(iiChamber).c_str());
            for (Int_t iiRunBin=0; iiRunBin < numBins; iiRunBin++){
              for (Int_t iiDCFEB=1; iiDCFEB <= totDCFEBs; iiDCFEB++){
                sprintf(name, "segEff2DStation%dRing%dDCFEB%dChamberRun", iiStation+1, iiRing, iiDCFEB);
                Float_t segEff = ((TH2F*)file0->Get(name))->GetBinContent(iiChamber, iiRunBin+1+iiPage*10);
                Int_t iiRun = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1+iiPage*10);

                if (segEff != -1) hcompactSeg->SetBinContent(iiChamber, totDCFEBs*iiRunBin + iiDCFEB, segEff);
                if (iiDCFEB == totDCFEBs/2+1)
                  hcompactSeg->GetYaxis()->SetBinLabel(totDCFEBs*iiRunBin + iiDCFEB, (to_string(iiRun) + " #" + to_string(iiDCFEB)).c_str());
                else
                  hcompactSeg->GetYaxis()->SetBinLabel(totDCFEBs*iiRunBin + iiDCFEB, ("#" + to_string(iiDCFEB)).c_str());
              }
            }
          }
          hcompactSeg->SetMarkerSize(0.6);
          hcompactSeg->GetXaxis()->SetLabelSize(0.035);
          hcompactSeg->GetXaxis()->SetTickLength(0.02);
          hcompactSeg->GetXaxis()->SetTitle("Chamber #");
          hcompactSeg->GetXaxis()->SetTitleFont(42);
          hcompactSeg->GetXaxis()->SetTitleSize(0.035);
          hcompactSeg->GetYaxis()->SetTickLength(0.01);
          hcompactSeg->GetYaxis()->SetLabelSize(0.026);
          hcompactSeg->GetYaxis()->SetTitle("Run + #DCFEB ");
          hcompactSeg->GetYaxis()->SetTitleFont(42);
          hcompactSeg->GetYaxis()->SetTitleSize(0.035);
          hcompactSeg->GetYaxis()->SetTitleOffset(1.5);
          hcompactSeg->GetZaxis()->SetRangeUser(0,1.0);
          hcompactSeg->GetZaxis()->SetTitle("Segment DCFEB Efficiency ");
          hcompactSeg->GetZaxis()->SetTitleFont(42);
          hcompactSeg->GetZaxis()->SetTitleSize(0.035);
          hcompactSeg->GetZaxis()->SetTitleOffset(1.1);
          hcompactSeg->Draw("COLZ TEXT");
          for (Int_t iiRunBin=0; iiRunBin < numBins; iiRunBin++){
            TLine *line = new TLine(0.5-0.05*numChambers, totDCFEBs*iiRunBin + totDCFEBs,numChambers + 0.5,totDCFEBs*iiRunBin + totDCFEBs);
            line->Draw();
          }
          DrawCMSLumi(dataInfo);
          c1.Print(file);
        }
        c1.Print(((string)file + "]").c_str());

        //sprintf(title, "LCT DCFEB Analysis %s", GetMELabel(iiStation, iiRing).c_str());
        sprintf(file, (plotdir + "DCFEBAnalysis/CSCLCTEffRun3Data2DChamberRunCompact%s.pdf").c_str(), GetMELabel(iiStation,iiRing).c_str());
        c1.Print(((string)file + "[").c_str());
        for (Int_t iiPage=0; iiPage*10<numRunBins; iiPage++){
          Int_t numBins = (numRunBins-iiPage*10 > 10)? 10 : numRunBins-iiPage*10;

          sprintf(name, "LCTEff2DStation%dRing%dDCFEBChamberRunCompact%d", iiStation+1, iiRing, iiPage);
          TH2F * hcompactLCT = new TH2F(name, "", numChambers, 0.5, numChambers + 0.5, numBins*totDCFEBs, 0, numBins*totDCFEBs);
          for (Int_t iiChamber=1; iiChamber <= numChambers; iiChamber++){ 
            hcompactLCT->GetXaxis()->SetBinLabel(iiChamber, to_string(iiChamber).c_str());
            for (Int_t iiRunBin=0; iiRunBin < numBins; iiRunBin++){
              for (Int_t iiDCFEB=1; iiDCFEB <= totDCFEBs; iiDCFEB++){
                sprintf(name, "LCTEff2DStation%dRing%dDCFEB%dChamberRun", iiStation+1, iiRing, iiDCFEB);
                Float_t LCTEff = ((TH2F*)file0->Get(name))->GetBinContent(iiChamber, iiRunBin+1+iiPage*10);
                Int_t iiRun = ((TH2F*)file0->Get(name))->GetYaxis()->GetBinLowEdge(iiRunBin+1+iiPage*10);

                if (LCTEff != -1) hcompactLCT->SetBinContent(iiChamber, totDCFEBs*iiRunBin + iiDCFEB, LCTEff);
                if (iiDCFEB == totDCFEBs/2+1)
                  hcompactLCT->GetYaxis()->SetBinLabel(totDCFEBs*iiRunBin + iiDCFEB, (to_string(iiRun) + " #" + to_string(iiDCFEB)).c_str());
                else
                  hcompactLCT->GetYaxis()->SetBinLabel(totDCFEBs*iiRunBin + iiDCFEB, ("#" + to_string(iiDCFEB)).c_str());
              }
            }
          }
          hcompactLCT->SetMarkerSize(0.6);
          hcompactLCT->GetXaxis()->SetLabelSize(0.035);
          hcompactLCT->GetXaxis()->SetTickLength(0.02);
          hcompactLCT->GetXaxis()->SetTitle("Chamber #");
          hcompactLCT->GetXaxis()->SetTitleFont(42);
          hcompactLCT->GetXaxis()->SetTitleSize(0.035);
          hcompactLCT->GetYaxis()->SetTickLength(0.01);
          hcompactLCT->GetYaxis()->SetLabelSize(0.026);
          hcompactLCT->GetYaxis()->SetTitle("Run + #DCFEB ");
          hcompactLCT->GetYaxis()->SetTitleFont(42);
          hcompactLCT->GetYaxis()->SetTitleSize(0.035);
          hcompactLCT->GetYaxis()->SetTitleOffset(1.5);
          hcompactLCT->GetZaxis()->SetRangeUser(0,1.0);
          hcompactLCT->GetZaxis()->SetTitle("LCT DCFEB Efficiency ");
          hcompactLCT->GetZaxis()->SetTitleFont(42);
          hcompactLCT->GetZaxis()->SetTitleSize(0.035);
          hcompactLCT->GetZaxis()->SetTitleOffset(1.1);
          hcompactLCT->Draw("COLZ TEXT");
          for (Int_t iiRunBin=0; iiRunBin < numBins; iiRunBin++){
            TLine *line = new TLine(0.5-0.05*numChambers, totDCFEBs*iiRunBin + totDCFEBs,numChambers + 0.5,totDCFEBs*iiRunBin + totDCFEBs);
            line->Draw();
          }
          DrawCMSLumi(dataInfo);
          c1.Print(file);
        }
        c1.Print(((string)file + "]").c_str());
      }
    }
    c1.SetRightMargin(oldRightMargin);
  }

  c1.Close();
  file0->Close();
}

#ifndef __CLING__
int main(int argc, char *argv[]){
  if (argc > 2){
    cerr << "Too many arguments." << endl;
    return 1;
  }
  string filename="cscEffHistoFile.root";
  if (argc == 2) filename = argv[1];
  PlotCSCEffFast(filename);
  return 0;
}
#endif

// Helper functions
string GetMELabel(Int_t station, Int_t ring, Int_t chamber){
  //station: 0-7
  //ring: 0-3
  //chamber: 1-36
  string result = "";
  if ((station==1||station==2||station==3||station==5||station==6||station==7)&&(ring==0||ring==3)){
    cout << "Unexpected station/ring. Given " << station << "/" << ring << endl;
    return result;
  }
  if (chamber!=-1&&(station==1||station==2||station==3||station==5||station==6||station==7)&&ring==1&&chamber>18){
    cout << "Unexpected station/ring/chamber. Given " << station << "/" << ring << "/" << chamber << endl;
    return result;
  }
  string symb = (station < 4)? "-" : "+";
  if (station >= 4) station -= 4;

  result = "ME" + symb + to_string(station+1);
  if (ring != -1){
    if (ring == 0) result += "1A";
    else if (station == 0 && ring == 1) result += "1B";
    else result += to_string(ring);
    if (chamber != -1) result += "/" + to_string(chamber);
  }

  return result;
}

void DrawCMSLumi(string lumi){
  gPad->Update();
  Double_t ycoord = (gPad->GetUymax()-gPad->GetUymin())/100 + gPad->GetUymax();
  TLatex textCMS(gPad->GetUxmin(), ycoord,
      "#font[61]{CMS}#scale[0.76]{#font[52]{ Preliminary}}");
  textCMS.SetTextSize(0.03);
  TLatex textInfo(gPad->GetUxmax(), ycoord,
      TString::Format("#font[42]{%s}", lumi.c_str()));
  textInfo.SetTextSize(0.03 * 0.6/0.75);
  textInfo.SetTextAlign(kHAlignRight+kVAlignBottom);
  textCMS.DrawClone();
  textInfo.DrawClone();
}

string Printout(const string& title, string info, bool legend){
  if (info == "") return "";
  while (isspace(info[0])) info = info.substr(1);
  while (isspace(info[info.size()-1])) info = info.substr(0,info.size()-1);
  string result = title + "\n";
  for (int i=0; i<title.size(); i++) result += "-";
  result += "\n" + info;
  if (legend) result += "\n\n *  Segment Only\n ** LCT Only"; 
  result += "\n\n\n";
  return result;
}

int GetRingIndex(int station, int ring){
  //station: 0-7
  //ring: 0-3
  enum RingIndex {
    MEm42, MEm41, MEm32, MEm31, MEm22, MEm21, MEm13, MEm12, MEm11b, MEm11a,
    MEp11a, MEp11b, MEp12, MEp13, MEp21, MEp22, MEp31, MEp32, MEp41, MEp42
  };
  int index = -2;
  if (station == 0){
    if (ring == 0) index = MEm11a;
    else if (ring == 1) index = MEm11b;
    else if (ring == 2) index = MEm12;
    else if (ring == 3) index = MEm13;
  }
  else if (station == 1) index = (ring == 1)? MEm21:MEm22;
  else if (station == 2) index = (ring == 1)? MEm31:MEm32;
  else if (station == 3) index = (ring == 1)? MEm41:MEm42;
  else if (station == 4){
    if (ring == 0) index = MEp11a;
    else if (ring == 1) index = MEp11b;
    else if (ring == 2) index = MEp12;
    else if (ring == 3) index = MEp13;
  }
  else if (station == 5) index = (ring == 1)? MEp21:MEp22;
  else if (station == 6) index = (ring == 1)? MEp31:MEp32;
  else if (station == 7) index = (ring == 1)? MEp41:MEp42;
  return index+1;
}
