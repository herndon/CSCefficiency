#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "TStyle.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TFrame.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMarker.h"
#include "TLine.h"
#include "TBox.h"

using namespace std;

void PlotCSCEffFast(){


	char file[50];
	char name[50];
	char stationRing[10];
	char title[100];

	bool chamberPlots = true;

	double lowEff = 0.6;
	double highEff = 1.02;

	int firstRun = 355000;
	int lastRun = 362800;


	ofstream cscTextEffData; 

	cscTextEffData.open("cscTextEffData.txt");

	gROOT->SetStyle("Plain");   // set plain TStyle
	//gStyle->SetOptStat(111111); // draw statistics on plots,
	// (0) for no output
	//gStyle->SetOptFit(1111);    // draw fit results on plot,
	// (0) for no ouput
	//gStyle->SetPalette(57);     // set color map
	//gStyle->SetOptTitle(0);     // suppress title box


	gStyle->SetOptStat(0);
	gStyle->SetPalette(kBlueRedYellow);
	gStyle->SetPaintTextFormat("3.2f");
	gStyle->SetCanvasDefH(1200);
	gStyle->SetCanvasDefW(1600);


	TCanvas c1("c1","<Title>",0,0,1600,1200);

	gStyle->SetTitleX(0.2);

	TFile * file0 = TFile::Open("cscEffHistoFile.root");


	gStyle->SetOptStat(1);

	TH1F * zMassAll = (TH1F*)file0->Get("zMassAll");
	zMassAll->GetXaxis()->SetRangeUser(75.0,105.0);
	zMassAll->Draw();

	c1.Print("plots/zMassRun3.png");


	TH1F * muonSegmentsFidAll = (TH1F*)file0->Get("muonSegmentsFidAll");
	muonSegmentsFidAll->GetXaxis()->SetRangeUser(-0.5,5.5);
	muonSegmentsFidAll->Draw();
	c1.Print("plots/muonSegmentsFidAll.png");

	TH1F * muonSegmentsFid1 = (TH1F*)file0->Get("muonSegmentsFid1");
	muonSegmentsFid1->GetXaxis()->SetRangeUser(-0.5,5.5);
	muonSegmentsFid1->Draw();
	c1.Print("plots/muonSegmentsFid1.png");

	TH1F * muonSegmentsFid2 = (TH1F*)file0->Get("muonSegmentsFid2");
	muonSegmentsFid2->GetXaxis()->SetRangeUser(-0.5,5.5);
	muonSegmentsFid2->Draw();
	c1.Print("plots/muonSegmentsFid2.png");


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
	c1.Print("plots/muonSegmentsFid1vsFid2.png");


	TH1F * muonSegmentsWithME21 = (TH1F*)file0->Get("muonSegmentsWithME21");
	muonSegmentsWithME21->GetXaxis()->SetRangeUser(-0.5,5.5);
	muonSegmentsWithME21->Draw();
	c1.Print("plots/muonSegmentsWithME21.png");

	TH1F * muonSegmentsNoME21 = (TH1F*)file0->Get("muonSegmentsNoME21");
	muonSegmentsNoME21->GetXaxis()->SetRangeUser(-0.5,5.5);
	muonSegmentsNoME21->Draw();
	c1.Print("plots/muonSegmentsNoME21.png");




	TH1F * segmentsFidAll = (TH1F*)file0->Get("segmentsFidAll");
	segmentsFidAll->GetXaxis()->SetRangeUser(-0.5,5.5);
	segmentsFidAll->Draw();
	c1.Print("plots/segmentsFidAll.png");

	TH1F * segmentsFid1 = (TH1F*)file0->Get("segmentsFid1");
	segmentsFid1->GetXaxis()->SetRangeUser(-0.5,5.5);
	segmentsFid1->Draw();
	c1.Print("plots/segmentsFid1.png");

	TH1F * segmentsFid2 = (TH1F*)file0->Get("segmentsFid2");
	segmentsFid2->GetXaxis()->SetRangeUser(-0.5,5.5);
	segmentsFid2->Draw();
	c1.Print("plots/segmentsFid2.png");

	segmentsFidAll->Scale(factor/segmentsFidAll->GetEntries());
	segmentsFid1->Scale(factor/segmentsFid1->GetEntries());
	segmentsFid2->Scale(factor/segmentsFid2->GetEntries());
	segmentsFidAll->Draw();
	segmentsFid2->SetLineColor(kBlue);
	segmentsFid2->SetTitle("Number of CSC Segments Fiducial ring 1 vs 2");
	segmentsFid2->Draw();
	segmentsFid1->SetLineColor(kRed);
	segmentsFid1->Draw("SAME");
	c1.Print("plots/segmentsFid1vsFid2.png");


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
	c1.Print("plots/segmentsFid1vsFid2HighPV.png");

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
	c1.Print("plots/segmentsFid1vsFid2LowPV.png");

	segmentsFid1LowPV->SetTitle("Number of CSC Segments ring 1 PV<=15 vs >=45");
	segmentsFid1LowPV->SetLineColor(kBlue);
	segmentsFid1LowPV->Draw();
	segmentsFid1HighPV->SetLineColor(kRed);
	segmentsFid1HighPV->Draw("SAME");
	c1.Print("plots/segmentsinME21LowVsHighPV.png");

	segmentsFid2LowPV->SetTitle("Number of CSC Segments ring 2 PV<=15 vs >=45");
	segmentsFid2LowPV->SetLineColor(kBlue);
	segmentsFid2LowPV->Draw();
	segmentsFid2HighPV->SetLineColor(kRed);
	segmentsFid2HighPV->Draw("SAME");
	c1.Print("plots/segmentsinME22LowVsHighPV.png");







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
	c1.Print("plots/muonSegmentsFid1vsFid2HighPV.png");

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
	c1.Print("plots/muonSegmentsFid1vsFid2LowPV.png");

	muonSegmentsFid1LowPV->SetTitle("Number of CSC Segments ring 1 PV<=15 vs >=45");
	muonSegmentsFid1LowPV->SetLineColor(kBlue);
	muonSegmentsFid1LowPV->Draw();
	muonSegmentsFid1HighPV->SetLineColor(kRed);
	muonSegmentsFid1HighPV->Draw("SAME");
	c1.Print("plots/muonSegmentsinME21LowVsHighPV.png");

	muonSegmentsFid2LowPV->SetTitle("Number of CSC Segments ring 2 PV<=15 vs >=45");
	muonSegmentsFid2LowPV->SetLineColor(kBlue);
	muonSegmentsFid2LowPV->Draw();
	muonSegmentsFid2HighPV->SetLineColor(kRed);
	muonSegmentsFid2HighPV->Draw("SAME");
	c1.Print("plots/muonSegmentsinME22LowVsHighPV.png");











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
	c1.Print("plots/segmentsFid1vsFid2HighpT.png");




	TH1F * segmentsWithME21 = (TH1F*)file0->Get("segmentsWithME21");
	segmentsWithME21->GetXaxis()->SetRangeUser(-0.5,5.5);
	segmentsWithME21->Draw();
	c1.Print("plots/segmentsWithME21.png");


	TH1F * segmentsNoME21 = (TH1F*)file0->Get("segmentsNoME21");
	segmentsNoME21->GetXaxis()->SetRangeUser(-0.5,5.5);
	segmentsNoME21->Draw();
	c1.Print("plots/segmentsNoME21.png");


	segmentsWithME21->Scale(factor/segmentsWithME21->GetEntries());
	segmentsNoME21->Scale(factor/segmentsNoME21->GetEntries());
	segmentsWithME21->SetTitle("Number of CSC Segments w vs w/0 ME11 cases");
	segmentsWithME21->Draw();
	segmentsNoME21->SetLineColor(kRed);
	segmentsNoME21->Draw("SAME");
	c1.Print("plots/segmentsWvsW)ME21.png");



	gStyle->SetOptStat(0);  


	TH1F * segEffPTStation1CRing0 = (TH1F*)file0->Get("segEffPTStation1CRing0");
	TH1F * segEffPTStation1CRing1 = (TH1F*)file0->Get("segEffPTStation1CRing1");
	TH1F * segEffPTStation1CRing2 = (TH1F*)file0->Get("segEffPTStation1CRing2");
	TH1F * segEffPTStation1CRing3 = (TH1F*)file0->Get("segEffPTStation1CRing3");


	segEffPTStation1CRing0->SetTitle("     CSC Segment Efficiency vs p_{T}         Run 3 Data");
	segEffPTStation1CRing0->GetYaxis()->SetRangeUser(lowEff,1.02);
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

	TLegend *legendSegPT = new TLegend(0.85,0.8,1.0,1.0);
	legendSegPT->AddEntry(segEffPTStation1CRing0,"ME11a");
	legendSegPT->AddEntry(segEffPTStation1CRing1,"ME11b");
	legendSegPT->AddEntry(segEffPTStation1CRing2,"ME12");
	legendSegPT->AddEntry(segEffPTStation1CRing3,"ME13");
	legendSegPT->Draw();

	c1.Print("plots/CSCSegEffRun3DataME1vsPt.png");  


	TH1F * segEffPTStation2CRing1 = (TH1F*)file0->Get("segEffPTStation2CRing1");
	TH1F * segEffPTStation2CRing2 = (TH1F*)file0->Get("segEffPTStation2CRing2");
	TH1F * segEffPTStation3CRing1 = (TH1F*)file0->Get("segEffPTStation3CRing1");
	TH1F * segEffPTStation3CRing2 = (TH1F*)file0->Get("segEffPTStation3CRing2");
	TH1F * segEffPTStation4CRing1 = (TH1F*)file0->Get("segEffPTStation4CRing1");
	TH1F * segEffPTStation4CRing2 = (TH1F*)file0->Get("segEffPTStation4CRing2");


	segEffPTStation2CRing1->SetTitle("     CSC Segment Efficiency vs p_{T}         Run 3 Data");
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

	TLegend *legendSegPT2 = new TLegend(0.85,0.8,1.0,1.0);
	legendSegPT2->AddEntry(segEffPTStation2CRing1,"ME21");
	legendSegPT2->AddEntry(segEffPTStation3CRing1,"ME31");
	legendSegPT2->AddEntry(segEffPTStation4CRing1,"ME41");
	legendSegPT2->AddEntry(segEffPTStation2CRing2,"ME22");
	legendSegPT2->AddEntry(segEffPTStation3CRing2,"ME32");
	legendSegPT2->AddEntry(segEffPTStation4CRing2,"ME42");
	legendSegPT2->Draw();

	c1.Print("plots/CSCSegEffRun3DataME234vsPt.png");

	TH1F * segEffEtaStation1CRing0 = (TH1F*)file0->Get("segEffEtaStation1CRing0");
	TH1F * segEffEtaStation1CRing1 = (TH1F*)file0->Get("segEffEtaStation1CRing1");
	TH1F * segEffEtaStation1CRing2 = (TH1F*)file0->Get("segEffEtaStation1CRing2");
	TH1F * segEffEtaStation1CRing3 = (TH1F*)file0->Get("segEffEtaStation1CRing3");


	segEffEtaStation1CRing0->SetTitle("     CSC Segment Efficiency vs #eta         Run 3 Data");
	segEffEtaStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
	segEffEtaStation1CRing0->GetXaxis()->SetRangeUser(0.8,2.5);
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

	TLegend *legendSegEta = new TLegend(0.85,0.8,1.0,1.0);
	legendSegEta->AddEntry(segEffEtaStation1CRing0,"ME11a");
	legendSegEta->AddEntry(segEffEtaStation1CRing1,"ME11b");
	legendSegEta->AddEntry(segEffEtaStation1CRing2,"ME12");
	legendSegEta->AddEntry(segEffEtaStation1CRing3,"ME13");
	legendSegEta->Draw();

	c1.Print("plots/CSCSegEffRun3DataME1vsEta.png");  


	TH1F * segEffEtaStation2CRing1 = (TH1F*)file0->Get("segEffEtaStation2CRing1");
	TH1F * segEffEtaStation2CRing2 = (TH1F*)file0->Get("segEffEtaStation2CRing2");
	TH1F * segEffEtaStation3CRing1 = (TH1F*)file0->Get("segEffEtaStation3CRing1");
	TH1F * segEffEtaStation3CRing2 = (TH1F*)file0->Get("segEffEtaStation3CRing2");
	TH1F * segEffEtaStation4CRing1 = (TH1F*)file0->Get("segEffEtaStation4CRing1");
	TH1F * segEffEtaStation4CRing2 = (TH1F*)file0->Get("segEffEtaStation4CRing2");


	segEffEtaStation2CRing1->SetTitle("     CSC Segment Efficiency vs #eta         Run 3 Data");
	segEffEtaStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
	segEffEtaStation2CRing1->GetXaxis()->SetRangeUser(0.8,2.5);
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

	TLegend *legendSegEta2 = new TLegend(0.85,0.8,1.0,1.0);
	legendSegEta2->AddEntry(segEffEtaStation2CRing1,"ME21");
	legendSegEta2->AddEntry(segEffEtaStation3CRing1,"ME31");
	legendSegEta2->AddEntry(segEffEtaStation4CRing1,"ME41");
	legendSegEta2->AddEntry(segEffEtaStation2CRing2,"ME22");
	legendSegEta2->AddEntry(segEffEtaStation3CRing2,"ME32");
	legendSegEta2->AddEntry(segEffEtaStation4CRing2,"ME42");
	legendSegEta2->Draw();

	c1.Print("plots/CSCSegEffRun3DataME234vsEta.png");


	TH1F * segEffPVStation1CRing0 = (TH1F*)file0->Get("segEffPVStation1CRing0");
	TH1F * segEffPVStation1CRing1 = (TH1F*)file0->Get("segEffPVStation1CRing1");
	TH1F * segEffPVStation1CRing2 = (TH1F*)file0->Get("segEffPVStation1CRing2");
	TH1F * segEffPVStation1CRing3 = (TH1F*)file0->Get("segEffPVStation1CRing3");


	segEffPVStation1CRing0->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
	segEffPVStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
	segEffPVStation1CRing0->GetXaxis()->SetRangeUser(0.0,56.0);
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

	TLegend *legendSegPV = new TLegend(0.85,0.8,1.0,1.0);
	legendSegPV->AddEntry(segEffPVStation1CRing0,"ME11a");
	legendSegPV->AddEntry(segEffPVStation1CRing1,"ME11b");
	legendSegPV->AddEntry(segEffPVStation1CRing2,"ME12");
	legendSegPV->AddEntry(segEffPVStation1CRing3,"ME13");
	legendSegPV->Draw();

	c1.Print("plots/CSCSegEffRun3DataME1vsPV.png");  


	TH1F * segEffPVStation2CRing1 = (TH1F*)file0->Get("segEffPVStation2CRing1");
	TH1F * segEffPVStation2CRing2 = (TH1F*)file0->Get("segEffPVStation2CRing2");
	TH1F * segEffPVStation3CRing1 = (TH1F*)file0->Get("segEffPVStation3CRing1");
	TH1F * segEffPVStation3CRing2 = (TH1F*)file0->Get("segEffPVStation3CRing2");
	TH1F * segEffPVStation4CRing1 = (TH1F*)file0->Get("segEffPVStation4CRing1");
	TH1F * segEffPVStation4CRing2 = (TH1F*)file0->Get("segEffPVStation4CRing2");


	segEffPVStation2CRing1->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
	segEffPVStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
	segEffPVStation2CRing1->GetXaxis()->SetRangeUser(0.0,56.0);
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

	TLegend *legendSegPV2 = new TLegend(0.85,0.8,1.0,1.0);
	legendSegPV2->AddEntry(segEffPVStation2CRing1,"ME21");
	legendSegPV2->AddEntry(segEffPVStation3CRing1,"ME31");
	legendSegPV2->AddEntry(segEffPVStation4CRing1,"ME41");
	legendSegPV2->AddEntry(segEffPVStation2CRing2,"ME22");
	legendSegPV2->AddEntry(segEffPVStation3CRing2,"ME32");
	legendSegPV2->AddEntry(segEffPVStation4CRing2,"ME42");
	legendSegPV2->Draw();

	c1.Print("plots/CSCSegEffRun3DataME234vsPV.png");



	TH1F * segEffPVStation2Ring1 = (TH1F*)file0->Get("segEffPVStation2Ring1");
	TH1F * segEffPVStation2Ring2 = (TH1F*)file0->Get("segEffPVStation2Ring2");
	TH1F * segEffPVStation3Ring1 = (TH1F*)file0->Get("segEffPVStation3Ring1");
	TH1F * segEffPVStation3Ring2 = (TH1F*)file0->Get("segEffPVStation3Ring2");
	TH1F * segEffPVStation4Ring1 = (TH1F*)file0->Get("segEffPVStation4Ring1");
	TH1F * segEffPVStation4Ring2 = (TH1F*)file0->Get("segEffPVStation4Ring2");


	segEffPVStation2Ring1->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
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

	TLegend *legendSegPV3 = new TLegend(0.85,0.8,1.0,1.0);
	legendSegPV3->AddEntry(segEffPVStation2Ring1,"ME-21");
	legendSegPV3->AddEntry(segEffPVStation3Ring1,"ME-31");
	legendSegPV3->AddEntry(segEffPVStation4Ring1,"ME-41");
	legendSegPV3->AddEntry(segEffPVStation2Ring2,"ME-22");
	legendSegPV3->AddEntry(segEffPVStation3Ring2,"ME-32");
	legendSegPV3->AddEntry(segEffPVStation4Ring2,"ME-42");
	legendSegPV3->Draw();

	c1.Print("plots/CSCSegEffRun3DataME-234vsPV.png");







	TH1F * segEffPVStation6Ring1 = (TH1F*)file0->Get("segEffPVStation6Ring1");
	TH1F * segEffPVStation6Ring2 = (TH1F*)file0->Get("segEffPVStation6Ring2");
	TH1F * segEffPVStation7Ring1 = (TH1F*)file0->Get("segEffPVStation7Ring1");
	TH1F * segEffPVStation7Ring2 = (TH1F*)file0->Get("segEffPVStation7Ring2");
	TH1F * segEffPVStation8Ring1 = (TH1F*)file0->Get("segEffPVStation8Ring1");
	TH1F * segEffPVStation8Ring2 = (TH1F*)file0->Get("segEffPVStation8Ring2");


	segEffPVStation6Ring1->SetTitle("     CSC Segment Efficiency vs PV         Run 3 Data");
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

	TLegend *legendSegPV4 = new TLegend(0.85,0.8,1.0,1.0);
	legendSegPV4->AddEntry(segEffPVStation6Ring1,"ME+21");
	legendSegPV4->AddEntry(segEffPVStation7Ring1,"ME+31");
	legendSegPV4->AddEntry(segEffPVStation8Ring1,"ME+41");
	legendSegPV4->AddEntry(segEffPVStation6Ring2,"ME+22");
	legendSegPV4->AddEntry(segEffPVStation7Ring2,"ME+32");
	legendSegPV4->AddEntry(segEffPVStation8Ring2,"ME+42");
	legendSegPV4->Draw();

	c1.Print("plots/CSCSegEffRun3DataME+234vsPV.png");





	TH2F * segEff2DStationRingChamber = (TH2F*)file0->Get("segEff2DStationRingChamber");

	segEff2DStationRingChamber->SetTitle("CSC Segment Efficiency 2D by Chamber & Ring        Run 3 Data");
	segEff2DStationRingChamber->SetMarkerSize(0.75);
	segEff2DStationRingChamber->GetYaxis()->SetTickLength(0.0015);
	segEff2DStationRingChamber->GetZaxis()->SetRangeUser(0.0,1.005);
	segEff2DStationRingChamber->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DRingChamber.png");


	TH1F * LCTEffPTStation1CRing0 = (TH1F*)file0->Get("LCTEffPTStation1CRing0");
	TH1F * LCTEffPTStation1CRing1 = (TH1F*)file0->Get("LCTEffPTStation1CRing1");
	TH1F * LCTEffPTStation1CRing2 = (TH1F*)file0->Get("LCTEffPTStation1CRing2");
	TH1F * LCTEffPTStation1CRing3 = (TH1F*)file0->Get("LCTEffPTStation1CRing3");


	LCTEffPTStation1CRing0->SetTitle("     CSC LCT Efficiency vs p_{T}         Run 3 Data");
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

	TLegend *legendLCTPT = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTPT->AddEntry(LCTEffPTStation1CRing0,"ME11a");
	legendLCTPT->AddEntry(LCTEffPTStation1CRing1,"ME11b");
	legendLCTPT->AddEntry(LCTEffPTStation1CRing2,"ME12");
	legendLCTPT->AddEntry(LCTEffPTStation1CRing3,"ME13");
	legendLCTPT->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME1vsPt.png");  


	TH1F * LCTEffPTStation2CRing1 = (TH1F*)file0->Get("LCTEffPTStation2CRing1");
	TH1F * LCTEffPTStation2CRing2 = (TH1F*)file0->Get("LCTEffPTStation2CRing2");
	TH1F * LCTEffPTStation3CRing1 = (TH1F*)file0->Get("LCTEffPTStation3CRing1");
	TH1F * LCTEffPTStation3CRing2 = (TH1F*)file0->Get("LCTEffPTStation3CRing2");
	TH1F * LCTEffPTStation4CRing1 = (TH1F*)file0->Get("LCTEffPTStation4CRing1");
	TH1F * LCTEffPTStation4CRing2 = (TH1F*)file0->Get("LCTEffPTStation4CRing2");


	LCTEffPTStation2CRing1->SetTitle("     CSC LCT Efficiency vs p_{T}         Run 3 Data");
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

	TLegend *legendLCTPT2 = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTPT2->AddEntry(LCTEffPTStation2CRing1,"ME21");
	legendLCTPT2->AddEntry(LCTEffPTStation3CRing1,"ME31");
	legendLCTPT2->AddEntry(LCTEffPTStation4CRing1,"ME41");
	legendLCTPT2->AddEntry(LCTEffPTStation2CRing2,"ME22");
	legendLCTPT2->AddEntry(LCTEffPTStation3CRing2,"ME32");
	legendLCTPT2->AddEntry(LCTEffPTStation4CRing2,"ME42");
	legendLCTPT2->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME234vsPt.png");

	TH1F * LCTEffEtaStation1CRing0 = (TH1F*)file0->Get("LCTEffEtaStation1CRing0");
	TH1F * LCTEffEtaStation1CRing1 = (TH1F*)file0->Get("LCTEffEtaStation1CRing1");
	TH1F * LCTEffEtaStation1CRing2 = (TH1F*)file0->Get("LCTEffEtaStation1CRing2");
	TH1F * LCTEffEtaStation1CRing3 = (TH1F*)file0->Get("LCTEffEtaStation1CRing3");


	LCTEffEtaStation1CRing0->SetTitle("     CSC LCT Efficiency vs #eta         Run 3 Data");
	LCTEffEtaStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
	LCTEffEtaStation1CRing0->GetXaxis()->SetRangeUser(0.8,2.5);
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

	TLegend *legendLCTEta = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTEta->AddEntry(LCTEffEtaStation1CRing0,"ME11a");
	legendLCTEta->AddEntry(LCTEffEtaStation1CRing1,"ME11b");
	legendLCTEta->AddEntry(LCTEffEtaStation1CRing2,"ME12");
	legendLCTEta->AddEntry(LCTEffEtaStation1CRing3,"ME13");
	legendLCTEta->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME1vsEta.png");  


	TH1F * LCTEffEtaStation2CRing1 = (TH1F*)file0->Get("LCTEffEtaStation2CRing1");
	TH1F * LCTEffEtaStation2CRing2 = (TH1F*)file0->Get("LCTEffEtaStation2CRing2");
	TH1F * LCTEffEtaStation3CRing1 = (TH1F*)file0->Get("LCTEffEtaStation3CRing1");
	TH1F * LCTEffEtaStation3CRing2 = (TH1F*)file0->Get("LCTEffEtaStation3CRing2");
	TH1F * LCTEffEtaStation4CRing1 = (TH1F*)file0->Get("LCTEffEtaStation4CRing1");
	TH1F * LCTEffEtaStation4CRing2 = (TH1F*)file0->Get("LCTEffEtaStation4CRing2");


	LCTEffEtaStation2CRing1->SetTitle("     CSC LCT Efficiency vs #eta         Run 3 Data");
	LCTEffEtaStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
	LCTEffEtaStation2CRing1->GetXaxis()->SetRangeUser(0.8,2.5);
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

	TLegend *legendLCTEta2 = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTEta2->AddEntry(LCTEffEtaStation2CRing1,"ME21");
	legendLCTEta2->AddEntry(LCTEffEtaStation3CRing1,"ME31");
	legendLCTEta2->AddEntry(LCTEffEtaStation4CRing1,"ME41");
	legendLCTEta2->AddEntry(LCTEffEtaStation2CRing2,"ME22");
	legendLCTEta2->AddEntry(LCTEffEtaStation3CRing2,"ME32");
	legendLCTEta2->AddEntry(LCTEffEtaStation4CRing2,"ME42");
	legendLCTEta2->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME234vsEta.png");


	TH1F * LCTEffPVStation1CRing0 = (TH1F*)file0->Get("LCTEffPVStation1CRing0");
	TH1F * LCTEffPVStation1CRing1 = (TH1F*)file0->Get("LCTEffPVStation1CRing1");
	TH1F * LCTEffPVStation1CRing2 = (TH1F*)file0->Get("LCTEffPVStation1CRing2");
	TH1F * LCTEffPVStation1CRing3 = (TH1F*)file0->Get("LCTEffPVStation1CRing3");


	LCTEffPVStation1CRing0->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
	LCTEffPVStation1CRing0->GetYaxis()->SetRangeUser(lowEff,highEff);
	LCTEffPVStation1CRing0->GetXaxis()->SetRangeUser(0.0,56.0);
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

	TLegend *legendLCTPV = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTPV->AddEntry(LCTEffPVStation1CRing0,"ME11a");
	legendLCTPV->AddEntry(LCTEffPVStation1CRing1,"ME11b");
	legendLCTPV->AddEntry(LCTEffPVStation1CRing2,"ME12");
	legendLCTPV->AddEntry(LCTEffPVStation1CRing3,"ME13");
	legendLCTPV->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME1vsPV.png");  


	TH1F * LCTEffPVStation2CRing1 = (TH1F*)file0->Get("LCTEffPVStation2CRing1");
	TH1F * LCTEffPVStation2CRing2 = (TH1F*)file0->Get("LCTEffPVStation2CRing2");
	TH1F * LCTEffPVStation3CRing1 = (TH1F*)file0->Get("LCTEffPVStation3CRing1");
	TH1F * LCTEffPVStation3CRing2 = (TH1F*)file0->Get("LCTEffPVStation3CRing2");
	TH1F * LCTEffPVStation4CRing1 = (TH1F*)file0->Get("LCTEffPVStation4CRing1");
	TH1F * LCTEffPVStation4CRing2 = (TH1F*)file0->Get("LCTEffPVStation4CRing2");


	LCTEffPVStation2CRing1->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
	LCTEffPVStation2CRing1->GetYaxis()->SetRangeUser(lowEff,highEff);
	LCTEffPVStation2CRing1->GetXaxis()->SetRangeUser(0.0,56.0);
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

	TLegend *legendLCTPV2 = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTPV2->AddEntry(LCTEffPVStation2CRing1,"ME21");
	legendLCTPV2->AddEntry(LCTEffPVStation3CRing1,"ME31");
	legendLCTPV2->AddEntry(LCTEffPVStation4CRing1,"ME41");
	legendLCTPV2->AddEntry(LCTEffPVStation2CRing2,"ME22");
	legendLCTPV2->AddEntry(LCTEffPVStation3CRing2,"ME32");
	legendLCTPV2->AddEntry(LCTEffPVStation4CRing2,"ME42");
	legendLCTPV2->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME234vsPV.png");






	TH1F * LCTEffPVStation2Ring1 = (TH1F*)file0->Get("LCTEffPVStation2Ring1");
	TH1F * LCTEffPVStation2Ring2 = (TH1F*)file0->Get("LCTEffPVStation2Ring2");
	TH1F * LCTEffPVStation3Ring1 = (TH1F*)file0->Get("LCTEffPVStation3Ring1");
	TH1F * LCTEffPVStation3Ring2 = (TH1F*)file0->Get("LCTEffPVStation3Ring2");
	TH1F * LCTEffPVStation4Ring1 = (TH1F*)file0->Get("LCTEffPVStation4Ring1");
	TH1F * LCTEffPVStation4Ring2 = (TH1F*)file0->Get("LCTEffPVStation4Ring2");


	LCTEffPVStation2Ring1->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
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

	TLegend *legendLCTPV3 = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTPV3->AddEntry(LCTEffPVStation2Ring1,"ME-21");
	legendLCTPV3->AddEntry(LCTEffPVStation3Ring1,"ME-31");
	legendLCTPV3->AddEntry(LCTEffPVStation4Ring1,"ME-41");
	legendLCTPV3->AddEntry(LCTEffPVStation2Ring2,"ME-22");
	legendLCTPV3->AddEntry(LCTEffPVStation3Ring2,"ME-32");
	legendLCTPV3->AddEntry(LCTEffPVStation4Ring2,"ME-42");
	legendLCTPV3->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME-234vsPV.png");



	TH1F * LCTEffPVStation6Ring1 = (TH1F*)file0->Get("LCTEffPVStation6Ring1");
	TH1F * LCTEffPVStation6Ring2 = (TH1F*)file0->Get("LCTEffPVStation6Ring2");
	TH1F * LCTEffPVStation7Ring1 = (TH1F*)file0->Get("LCTEffPVStation7Ring1");
	TH1F * LCTEffPVStation7Ring2 = (TH1F*)file0->Get("LCTEffPVStation7Ring2");
	TH1F * LCTEffPVStation8Ring1 = (TH1F*)file0->Get("LCTEffPVStation8Ring1");
	TH1F * LCTEffPVStation8Ring2 = (TH1F*)file0->Get("LCTEffPVStation8Ring2");


	LCTEffPVStation6Ring1->SetTitle("     CSC LCT Efficiency vs PV         Run 3 Data");
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

	TLegend *legendLCTPV4 = new TLegend(0.85,0.8,1.0,1.0);
	legendLCTPV4->AddEntry(LCTEffPVStation6Ring1,"ME+21");
	legendLCTPV4->AddEntry(LCTEffPVStation7Ring1,"ME+31");
	legendLCTPV4->AddEntry(LCTEffPVStation8Ring1,"ME+41");
	legendLCTPV4->AddEntry(LCTEffPVStation6Ring2,"ME+22");
	legendLCTPV4->AddEntry(LCTEffPVStation7Ring2,"ME+32");
	legendLCTPV4->AddEntry(LCTEffPVStation8Ring2,"ME+42");
	legendLCTPV4->Draw();

	c1.Print("plots/CSCLCTEffRun3DataME+234vsPV.png");









	TH2F * LCTEff2DStationRingChamber = (TH2F*)file0->Get("LCTEff2DStationRingChamber");

	LCTEff2DStationRingChamber->SetTitle("CSC LCT Efficiency 2D by Chamber & Ring        Run 3 Data");
	LCTEff2DStationRingChamber->SetMarkerSize(0.75);
	LCTEff2DStationRingChamber->GetYaxis()->SetTickLength(0.0015);
	LCTEff2DStationRingChamber->GetZaxis()->SetRangeUser(0.0,1.005);
	LCTEff2DStationRingChamber->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DRingChamber.png");



	TH2F * segEff2DStation1Ring0ChamberRun = (TH2F*)file0->Get("segEff2DStation1Ring0ChamberRun");

	segEff2DStation1Ring0ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-11A");
	segEff2DStation1Ring0ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring0ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation1Ring0ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring0ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring0ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring0ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring0ChamberRun->SetMarkerSize(0.6);
	segEff2DStation1Ring0ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-11A.png");

	TH2F * segEff2DStation1Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation1Ring1ChamberRun");

	segEff2DStation1Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-11B");
	segEff2DStation1Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation1Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation1Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-11B.png");

	TH2F * segEff2DStation1Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation1Ring2ChamberRun");

	segEff2DStation1Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-12");
	segEff2DStation1Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation1Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation1Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-12.png");

	TH2F * segEff2DStation1Ring3ChamberRun = (TH2F*)file0->Get("segEff2DStation1Ring3ChamberRun");

	segEff2DStation1Ring3ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-13");
	segEff2DStation1Ring3ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring3ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation1Ring3ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring3ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring3ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring3ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring3ChamberRun->SetMarkerSize(0.6);
	segEff2DStation1Ring3ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-13.png");

	TH2F * segEff2DStation5Ring0ChamberRun = (TH2F*)file0->Get("segEff2DStation5Ring0ChamberRun");

	segEff2DStation5Ring0ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+11A");
	segEff2DStation5Ring0ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring0ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation5Ring0ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring0ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring0ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring0ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring0ChamberRun->SetMarkerSize(0.6);
	segEff2DStation5Ring0ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+11A.png");

	TH2F * segEff2DStation5Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation5Ring1ChamberRun");

	segEff2DStation5Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+11B");
	segEff2DStation5Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation5Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation5Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+11B.png");

	TH2F * segEff2DStation5Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation5Ring2ChamberRun");

	segEff2DStation5Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+12");
	segEff2DStation5Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation5Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation5Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+12.png");

	TH2F * segEff2DStation5Ring3ChamberRun = (TH2F*)file0->Get("segEff2DStation5Ring3ChamberRun");

	segEff2DStation5Ring3ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+13");
	segEff2DStation5Ring3ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring3ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation5Ring3ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring3ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring3ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring3ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring3ChamberRun->SetMarkerSize(0.6);
	segEff2DStation5Ring3ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+13.png");

	TH2F * segEff2DStation2Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation2Ring1ChamberRun");

	segEff2DStation2Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-21");
	segEff2DStation2Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation2Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation2Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation2Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation2Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation2Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation2Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation2Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-21.png");

	TH2F * segEff2DStation2Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation2Ring2ChamberRun");

	segEff2DStation2Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-22");
	segEff2DStation2Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation2Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation2Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation2Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation2Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation2Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation2Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation2Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-22.png");

	TH2F * segEff2DStation3Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation3Ring1ChamberRun");

	segEff2DStation3Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-31");
	segEff2DStation3Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation3Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation3Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation3Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation3Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation3Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation3Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation3Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-31.png");

	TH2F * segEff2DStation3Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation3Ring2ChamberRun");

	segEff2DStation3Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-32");
	segEff2DStation3Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation3Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation3Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation3Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation3Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation3Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation3Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation3Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-32.png");

	TH2F * segEff2DStation4Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation4Ring1ChamberRun");

	segEff2DStation4Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-41");
	segEff2DStation4Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation4Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation4Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation4Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation4Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation4Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation4Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation4Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-41.png");

	TH2F * segEff2DStation4Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation4Ring2ChamberRun");

	segEff2DStation4Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME-42");
	segEff2DStation4Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation4Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation4Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation4Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation4Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation4Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation4Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation4Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME-42.png");

	TH2F * segEff2DStation6Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation6Ring1ChamberRun");

	segEff2DStation6Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+21");
	segEff2DStation6Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation6Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation6Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation6Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation6Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation6Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation6Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation6Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+21.png");

	TH2F * segEff2DStation6Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation6Ring2ChamberRun");

	segEff2DStation6Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+22");
	segEff2DStation6Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation6Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation6Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation6Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation6Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation6Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation6Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation6Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+22.png");

	TH2F * segEff2DStation7Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation7Ring1ChamberRun");

	segEff2DStation7Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+31");
	segEff2DStation7Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation7Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation7Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation7Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation7Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation7Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation7Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation7Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+31.png");

	TH2F * segEff2DStation7Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation7Ring2ChamberRun");

	segEff2DStation7Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+32");
	segEff2DStation7Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation7Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation7Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation7Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation7Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation7Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation7Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation7Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+32.png");

	TH2F * segEff2DStation8Ring1ChamberRun = (TH2F*)file0->Get("segEff2DStation8Ring1ChamberRun");

	segEff2DStation8Ring1ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+41");
	segEff2DStation8Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation8Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation8Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation8Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation8Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation8Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation8Ring1ChamberRun->SetMarkerSize(0.6);
	segEff2DStation8Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+41.png");

	TH2F * segEff2DStation8Ring2ChamberRun = (TH2F*)file0->Get("segEff2DStation8Ring2ChamberRun");

	segEff2DStation8Ring2ChamberRun->SetTitle("CSC Segment Efficiency vs Chamber and Run ME+42");
	segEff2DStation8Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation8Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	segEff2DStation8Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation8Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	segEff2DStation8Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	segEff2DStation8Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation8Ring2ChamberRun->SetMarkerSize(0.6);
	segEff2DStation8Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberRunME+42.png");





	TH2F * segEff2DStation1Ring0ChamberLayer = (TH2F*)file0->Get("segEff2DStation1Ring0ChamberLayer");

	segEff2DStation1Ring0ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-11A");
	segEff2DStation1Ring0ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring0ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation1Ring0ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring0ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring0ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring0ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring0ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation1Ring0ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-11A.png");

	TH2F * segEff2DStation1Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation1Ring1ChamberLayer");

	segEff2DStation1Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-11B");
	segEff2DStation1Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation1Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation1Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-11B.png");

	TH2F * segEff2DStation1Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation1Ring2ChamberLayer");

	segEff2DStation1Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-12");
	segEff2DStation1Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation1Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation1Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-12.png");

	TH2F * segEff2DStation1Ring3ChamberLayer = (TH2F*)file0->Get("segEff2DStation1Ring3ChamberLayer");

	segEff2DStation1Ring3ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-13");
	segEff2DStation1Ring3ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring3ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation1Ring3ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring3ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring3ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring3ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring3ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation1Ring3ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-13.png");

	TH2F * segEff2DStation5Ring0ChamberLayer = (TH2F*)file0->Get("segEff2DStation5Ring0ChamberLayer");

	segEff2DStation5Ring0ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+11A");
	segEff2DStation5Ring0ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring0ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation5Ring0ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring0ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring0ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring0ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring0ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation5Ring0ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+11A.png");

	TH2F * segEff2DStation5Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation5Ring1ChamberLayer");

	segEff2DStation5Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+11B");
	segEff2DStation5Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation5Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation5Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+11B.png");

	TH2F * segEff2DStation5Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation5Ring2ChamberLayer");

	segEff2DStation5Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+12");
	segEff2DStation5Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation5Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation5Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+12.png");

	TH2F * segEff2DStation5Ring3ChamberLayer = (TH2F*)file0->Get("segEff2DStation5Ring3ChamberLayer");

	segEff2DStation5Ring3ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+13");
	segEff2DStation5Ring3ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring3ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation5Ring3ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring3ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring3ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring3ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring3ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation5Ring3ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+13.png");

	TH2F * segEff2DStation2Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation2Ring1ChamberLayer");

	segEff2DStation2Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-21");
	segEff2DStation2Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation2Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation2Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation2Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation2Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation2Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation2Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation2Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-21.png");

	TH2F * segEff2DStation2Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation2Ring2ChamberLayer");

	segEff2DStation2Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-22");
	segEff2DStation2Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation2Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation2Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation2Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation2Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation2Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation2Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation2Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-22.png");

	TH2F * segEff2DStation3Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation3Ring1ChamberLayer");

	segEff2DStation3Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-31");
	segEff2DStation3Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation3Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation3Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation3Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation3Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation3Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation3Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation3Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-31.png");

	TH2F * segEff2DStation3Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation3Ring2ChamberLayer");

	segEff2DStation3Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-32");
	segEff2DStation3Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation3Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation3Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation3Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation3Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation3Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation3Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation3Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-32.png");

	TH2F * segEff2DStation4Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation4Ring1ChamberLayer");

	segEff2DStation4Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-41");
	segEff2DStation4Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation4Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation4Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation4Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation4Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation4Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation4Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation4Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-41.png");

	TH2F * segEff2DStation4Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation4Ring2ChamberLayer");

	segEff2DStation4Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME-42");
	segEff2DStation4Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation4Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation4Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation4Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation4Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation4Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation4Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation4Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME-42.png");

	TH2F * segEff2DStation6Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation6Ring1ChamberLayer");

	segEff2DStation6Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+21");
	segEff2DStation6Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation6Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation6Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation6Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation6Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation6Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation6Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation6Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+21.png");

	TH2F * segEff2DStation6Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation6Ring2ChamberLayer");

	segEff2DStation6Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+22");
	segEff2DStation6Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation6Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation6Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation6Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation6Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation6Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation6Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation6Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+22.png");

	TH2F * segEff2DStation7Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation7Ring1ChamberLayer");

	segEff2DStation7Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+31");
	segEff2DStation7Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation7Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation7Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation7Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation7Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation7Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation7Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation7Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+31.png");

	TH2F * segEff2DStation7Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation7Ring2ChamberLayer");

	segEff2DStation7Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+32");
	segEff2DStation7Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation7Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation7Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation7Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation7Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation7Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation7Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation7Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+32.png");

	TH2F * segEff2DStation8Ring1ChamberLayer = (TH2F*)file0->Get("segEff2DStation8Ring1ChamberLayer");

	segEff2DStation8Ring1ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+41");
	segEff2DStation8Ring1ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation8Ring1ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation8Ring1ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation8Ring1ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation8Ring1ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation8Ring1ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation8Ring1ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation8Ring1ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+41.png");

	TH2F * segEff2DStation8Ring2ChamberLayer = (TH2F*)file0->Get("segEff2DStation8Ring2ChamberLayer");

	segEff2DStation8Ring2ChamberLayer->SetTitle("CSC Segment Efficiency vs Chamber and Layer ME+42");
	segEff2DStation8Ring2ChamberLayer->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation8Ring2ChamberLayer->GetYaxis()->SetTitle("Layer ");
	segEff2DStation8Ring2ChamberLayer->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation8Ring2ChamberLayer->GetXaxis()->SetTickLength(0.015);
	segEff2DStation8Ring2ChamberLayer->GetYaxis()->SetTickLength(0.015);
	segEff2DStation8Ring2ChamberLayer->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation8Ring2ChamberLayer->SetMarkerSize(0.6);
	segEff2DStation8Ring2ChamberLayer->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberLayerME+42.png");







	TH2F * segEff2DStation1Ring0ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation1Ring0ChamberDCFEB");

	segEff2DStation1Ring0ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-11A");
	segEff2DStation1Ring0ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring0ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation1Ring0ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring0ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring0ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring0ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring0ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation1Ring0ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-11A.png");

	TH2F * segEff2DStation1Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation1Ring1ChamberDCFEB");

	segEff2DStation1Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-11B");
	segEff2DStation1Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation1Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation1Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-11B.png");

	TH2F * segEff2DStation1Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation1Ring2ChamberDCFEB");

	segEff2DStation1Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-12");
	segEff2DStation1Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation1Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation1Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-12.png");

	TH2F * segEff2DStation1Ring3ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation1Ring3ChamberDCFEB");

	segEff2DStation1Ring3ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-13");
	segEff2DStation1Ring3ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation1Ring3ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation1Ring3ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation1Ring3ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation1Ring3ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation1Ring3ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation1Ring3ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation1Ring3ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-13.png");

	TH2F * segEff2DStation5Ring0ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation5Ring0ChamberDCFEB");

	segEff2DStation5Ring0ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+11A");
	segEff2DStation5Ring0ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring0ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation5Ring0ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring0ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring0ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring0ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring0ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation5Ring0ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+11A.png");

	TH2F * segEff2DStation5Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation5Ring1ChamberDCFEB");

	segEff2DStation5Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+11B");
	segEff2DStation5Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation5Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation5Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+11B.png");

	TH2F * segEff2DStation5Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation5Ring2ChamberDCFEB");

	segEff2DStation5Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+12");
	segEff2DStation5Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation5Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation5Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+12.png");

	TH2F * segEff2DStation5Ring3ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation5Ring3ChamberDCFEB");

	segEff2DStation5Ring3ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+13");
	segEff2DStation5Ring3ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation5Ring3ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation5Ring3ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation5Ring3ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation5Ring3ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation5Ring3ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation5Ring3ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation5Ring3ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+13.png");

	TH2F * segEff2DStation2Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation2Ring1ChamberDCFEB");

	segEff2DStation2Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-21");
	segEff2DStation2Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation2Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation2Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation2Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation2Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation2Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation2Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation2Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-21.png");

	TH2F * segEff2DStation2Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation2Ring2ChamberDCFEB");

	segEff2DStation2Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-22");
	segEff2DStation2Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation2Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation2Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation2Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation2Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation2Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation2Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation2Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-22.png");

	TH2F * segEff2DStation3Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation3Ring1ChamberDCFEB");

	segEff2DStation3Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-31");
	segEff2DStation3Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation3Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation3Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation3Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation3Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation3Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation3Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation3Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-31.png");

	TH2F * segEff2DStation3Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation3Ring2ChamberDCFEB");

	segEff2DStation3Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-32");
	segEff2DStation3Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation3Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation3Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation3Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation3Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation3Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation3Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation3Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-32.png");

	TH2F * segEff2DStation4Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation4Ring1ChamberDCFEB");

	segEff2DStation4Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-41");
	segEff2DStation4Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation4Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation4Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation4Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation4Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation4Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation4Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation4Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-41.png");

	TH2F * segEff2DStation4Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation4Ring2ChamberDCFEB");

	segEff2DStation4Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME-42");
	segEff2DStation4Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation4Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation4Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation4Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation4Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation4Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation4Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation4Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME-42.png");

	TH2F * segEff2DStation6Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation6Ring1ChamberDCFEB");

	segEff2DStation6Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+21");
	segEff2DStation6Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation6Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation6Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation6Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation6Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation6Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation6Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation6Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+21.png");

	TH2F * segEff2DStation6Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation6Ring2ChamberDCFEB");

	segEff2DStation6Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+22");
	segEff2DStation6Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation6Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation6Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation6Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation6Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation6Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation6Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation6Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+22.png");

	TH2F * segEff2DStation7Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation7Ring1ChamberDCFEB");

	segEff2DStation7Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+31");
	segEff2DStation7Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation7Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation7Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation7Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation7Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation7Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation7Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation7Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+31.png");

	TH2F * segEff2DStation7Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation7Ring2ChamberDCFEB");

	segEff2DStation7Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+32");
	segEff2DStation7Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation7Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation7Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation7Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation7Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation7Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation7Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation7Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+32.png");

	TH2F * segEff2DStation8Ring1ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation8Ring1ChamberDCFEB");

	segEff2DStation8Ring1ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+41");
	segEff2DStation8Ring1ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation8Ring1ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation8Ring1ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation8Ring1ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation8Ring1ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation8Ring1ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation8Ring1ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation8Ring1ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+41.png");

	TH2F * segEff2DStation8Ring2ChamberDCFEB = (TH2F*)file0->Get("segEff2DStation8Ring2ChamberDCFEB");

	segEff2DStation8Ring2ChamberDCFEB->SetTitle("CSC Segment Efficiency vs Chamber and DCFEB ME+42");
	segEff2DStation8Ring2ChamberDCFEB->GetXaxis()->SetTitle("Chamber #");
	segEff2DStation8Ring2ChamberDCFEB->GetYaxis()->SetTitle("DCFEB ");
	segEff2DStation8Ring2ChamberDCFEB->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStation8Ring2ChamberDCFEB->GetXaxis()->SetTickLength(0.015);
	segEff2DStation8Ring2ChamberDCFEB->GetYaxis()->SetTickLength(0.015);
	segEff2DStation8Ring2ChamberDCFEB->GetZaxis()->SetRangeUser(0.0,1.0);
	segEff2DStation8Ring2ChamberDCFEB->SetMarkerSize(0.6);
	segEff2DStation8Ring2ChamberDCFEB->Draw("COLZ TEXT");
	c1.Print("plots/CSCSegEffRun3Data2DChamberDCFEBME+42.png");









	TH2F * LCTEff2DStation1Ring0ChamberRun = (TH2F*)file0->Get("LCTEff2DStation1Ring0ChamberRun");

	LCTEff2DStation1Ring0ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-11A");
	LCTEff2DStation1Ring0ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation1Ring0ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation1Ring0ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation1Ring0ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring0ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring0ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation1Ring0ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation1Ring0ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-11A.png");

	TH2F * LCTEff2DStation1Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation1Ring1ChamberRun");

	LCTEff2DStation1Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-11B");
	LCTEff2DStation1Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation1Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation1Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation1Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation1Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation1Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-11B.png");

	TH2F * LCTEff2DStation1Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation1Ring2ChamberRun");

	LCTEff2DStation1Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-12");
	LCTEff2DStation1Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation1Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation1Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation1Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation1Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation1Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-12.png");

	TH2F * LCTEff2DStation1Ring3ChamberRun = (TH2F*)file0->Get("LCTEff2DStation1Ring3ChamberRun");

	LCTEff2DStation1Ring3ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-13");
	LCTEff2DStation1Ring3ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation1Ring3ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation1Ring3ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation1Ring3ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring3ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation1Ring3ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation1Ring3ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation1Ring3ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-13.png");

	TH2F * LCTEff2DStation5Ring0ChamberRun = (TH2F*)file0->Get("LCTEff2DStation5Ring0ChamberRun");

	LCTEff2DStation5Ring0ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+11A");
	LCTEff2DStation5Ring0ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation5Ring0ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation5Ring0ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation5Ring0ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring0ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring0ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation5Ring0ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation5Ring0ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+11A.png");

	TH2F * LCTEff2DStation5Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation5Ring1ChamberRun");

	LCTEff2DStation5Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+11B");
	LCTEff2DStation5Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation5Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation5Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation5Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation5Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation5Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+11B.png");

	TH2F * LCTEff2DStation5Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation5Ring2ChamberRun");

	LCTEff2DStation5Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+12");
	LCTEff2DStation5Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation5Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation5Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation5Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation5Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation5Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+12.png");

	TH2F * LCTEff2DStation5Ring3ChamberRun = (TH2F*)file0->Get("LCTEff2DStation5Ring3ChamberRun");

	LCTEff2DStation5Ring3ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+13");
	LCTEff2DStation5Ring3ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation5Ring3ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation5Ring3ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation5Ring3ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring3ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation5Ring3ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation5Ring3ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation5Ring3ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+13.png");

	TH2F * LCTEff2DStation2Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation2Ring1ChamberRun");

	LCTEff2DStation2Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-21");
	LCTEff2DStation2Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation2Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation2Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation2Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation2Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation2Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation2Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation2Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-21.png");

	TH2F * LCTEff2DStation2Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation2Ring2ChamberRun");

	LCTEff2DStation2Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-22");
	LCTEff2DStation2Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation2Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation2Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation2Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation2Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation2Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation2Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation2Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-22.png");

	TH2F * LCTEff2DStation3Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation3Ring1ChamberRun");

	LCTEff2DStation3Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-31");
	LCTEff2DStation3Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation3Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation3Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation3Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation3Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation3Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation3Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation3Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-31.png");

	TH2F * LCTEff2DStation3Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation3Ring2ChamberRun");

	LCTEff2DStation3Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-32");
	LCTEff2DStation3Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation3Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation3Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation3Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation3Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation3Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation3Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation3Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-32.png");

	TH2F * LCTEff2DStation4Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation4Ring1ChamberRun");

	LCTEff2DStation4Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-41");
	LCTEff2DStation4Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation4Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation4Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation4Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation4Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation4Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation4Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation4Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-41.png");

	TH2F * LCTEff2DStation4Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation4Ring2ChamberRun");

	LCTEff2DStation4Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME-42");
	LCTEff2DStation4Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation4Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation4Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation4Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation4Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation4Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation4Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation4Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME-42.png");

	TH2F * LCTEff2DStation6Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation6Ring1ChamberRun");

	LCTEff2DStation6Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+21");
	LCTEff2DStation6Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation6Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation6Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation6Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation6Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation6Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation6Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation6Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+21.png");

	TH2F * LCTEff2DStation6Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation6Ring2ChamberRun");

	LCTEff2DStation6Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+22");
	LCTEff2DStation6Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation6Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation6Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation6Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation6Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation6Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation6Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation6Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+22.png");

	TH2F * LCTEff2DStation7Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation7Ring1ChamberRun");

	LCTEff2DStation7Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+31");
	LCTEff2DStation7Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation7Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation7Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation7Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation7Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation7Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation7Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation7Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+31.png");

	TH2F * LCTEff2DStation7Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation7Ring2ChamberRun");

	LCTEff2DStation7Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+32");
	LCTEff2DStation7Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation7Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation7Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation7Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation7Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation7Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation7Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation7Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+32.png");

	TH2F * LCTEff2DStation8Ring1ChamberRun = (TH2F*)file0->Get("LCTEff2DStation8Ring1ChamberRun");

	LCTEff2DStation8Ring1ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+41");
	LCTEff2DStation8Ring1ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation8Ring1ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation8Ring1ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation8Ring1ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation8Ring1ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation8Ring1ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation8Ring1ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation8Ring1ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+41.png");

	TH2F * LCTEff2DStation8Ring2ChamberRun = (TH2F*)file0->Get("LCTEff2DStation8Ring2ChamberRun");

	LCTEff2DStation8Ring2ChamberRun->SetTitle("CSC LCT Efficiency vs Chamber and Run ME+42");
	LCTEff2DStation8Ring2ChamberRun->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStation8Ring2ChamberRun->GetYaxis()->SetTitle("Run ");
	LCTEff2DStation8Ring2ChamberRun->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStation8Ring2ChamberRun->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStation8Ring2ChamberRun->GetYaxis()->SetTickLength(0.015);
	LCTEff2DStation8Ring2ChamberRun->GetZaxis()->SetRangeUser(0.0,1.0);
	LCTEff2DStation8Ring2ChamberRun->SetMarkerSize(0.6);
	LCTEff2DStation8Ring2ChamberRun->Draw("COLZ TEXT");
	c1.Print("plots/CSCLCTEffRun3Data2DChamberRunME+42.png");



	if (chamberPlots){
		for (Int_t iiStation=0; iiStation < 8; iiStation++){
			for (Int_t iiRing=0; iiRing < 4; iiRing++){
				for (Int_t iiChamber=1; iiChamber < 37; iiChamber++){
					if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&iiRing==1&&iiChamber>18) continue;
					if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&(iiRing==0||iiRing==3)) continue;

					sprintf(name,"segEffLCSStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
					if (iiStation<4) {
						if (iiRing == 0) {
							sprintf(title,"Segment Efficiency vs Strip LC for ME-%d%dA/%d",iiStation+1,iiRing+1,iiChamber);
							sprintf(file,"plots/ME-%d%dA/cscSegEffRun3DataME-%d%dA-%dLCS.png",iiStation+1,iiRing+1,iiStation+1,iiRing+1,iiChamber);
						} else if (iiStation==0&&iiRing == 1) {
							sprintf(title,"Segment Efficiency vs Strip LC for ME-%d%dB/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%dB/cscSegEffRun3DataME-%d%dB-%dLCS.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						} else {
							sprintf(title,"Segment Efficiency vs Strip LC for ME-%d%d/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%d/cscSegEffRun3DataME-%d%d-%dLCS.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						}
					} else {
						if (iiRing == 0) {
							sprintf(title,"Segment Efficiency vs Strip LC for ME+%d%dA/%d",iiStation+1-4,iiRing+1,iiChamber);
							sprintf(file,"plots/ME+%d%dA/cscSegEffRun3DataME+%d%dA-%dLCS.png",iiStation+1-4,iiRing+1,iiStation+1-4,iiRing+1,iiChamber);
						} else if (iiStation==4&&iiRing == 1) {
							sprintf(title,"Segment Efficiency vs Strip LC for ME+%d%dB/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%dB/cscSegEffRun3DataME+%d%dB-%dLCS.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						} else {
							sprintf(title,"Segment Efficiency vs Strip LC for ME+%d%d/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%d/cscSegEffRun3DataME+%d%d-%dLCS.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						}
					}



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



					sprintf(name,"segEffLCYStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);

					if (iiStation<4) {
						if (iiRing == 0) {
							sprintf(title,"Segment Efficiency vs Y LC for ME-%d%dA/%d",iiStation+1,iiRing+1,iiChamber);
							sprintf(file,"plots/ME-%d%dA/cscSegEffRun3DataME-%d%dA-%dLCY.png",iiStation+1,iiRing+1,iiStation+1,iiRing+1,iiChamber);
						} else if (iiStation==0&&iiRing == 1) {
							sprintf(title,"Segment Efficiency vs Y LC for ME-%d%dB/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%dB/cscSegEffRun3DataME-%d%dB-%dLCY.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						} else {
							sprintf(title,"Segment Efficiency vs Y LC for ME-%d%d/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%d/cscSegEffRun3DataME-%d%d-%dLCY.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						}
					} else {
						if (iiRing == 0) {
							sprintf(title,"Segment Efficiency vs Y LC for ME+%d%dA/%d",iiStation+1-4,iiRing+1,iiChamber);
							sprintf(file,"plots/ME+%d%dA/cscSegEffRun3DataME+%d%dA-%dLCY.png",iiStation+1-4,iiRing+1,iiStation+1-4,iiRing+1,iiChamber);
						} else if (iiStation==4&&iiRing == 1) {
							sprintf(title,"Segment Efficiency vs Y LC for ME+%d%dB/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%dB/cscSegEffRun3DataME+%d%dB-%dLCY.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						} else {
							sprintf(title,"Segment Efficiency vs Y LC for ME+%d%d/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%d/cscSegEffRun3DataME+%d%d-%dLCY.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						}
					}



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


					sprintf(name,"segEffStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);

					if (iiStation<4) {
						if (iiRing == 0) {
							sprintf(title,"Segment Efficiency vs Run for ME-%d%dA/%d",iiStation+1,iiRing+1,iiChamber);
							sprintf(file,"plots/ME-%d%dA/cscSegEffRun3DataME-%d%dA-%dRun.png",iiStation+1,iiRing+1,iiStation+1,iiRing+1,iiChamber);
						} else if (iiStation==0&&iiRing == 1) {
							sprintf(title,"Segment Efficiency vs Run for ME-%d%dB/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%dB/cscSegEffRun3DataME-%d%dB-%dRun.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						} else {
							sprintf(title,"Segment Efficiency vs Run for ME-%d%d/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%d/cscSegEffRun3DataME-%d%d-%dRun.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						}
					} else {
						if (iiRing == 0) {
							sprintf(title,"Segment Efficiency vs Run for ME+%d%dA/%d",iiStation+1-4,iiRing+1,iiChamber);
							sprintf(file,"plots/ME+%d%dA/cscSegEffRun3DataME+%d%dA-%dRun.png",iiStation+1-4,iiRing+1,iiStation+1-4,iiRing+1,iiChamber);
						} else if (iiStation==4&&iiRing == 1) {
							sprintf(title,"Segment Efficiency vs Run for ME+%d%dB/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%dB/cscSegEffRun3DataME+%d%dB-%dRun.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						} else {
							sprintf(title,"Segment Efficiency vs Run for ME+%d%d/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%d/cscSegEffRun3DataME+%d%d-%dRun.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						}
					}



					TH1F * segEffChamberRun = (TH1F*)file0->Get(name);
					segEffChamberRun->SetTitle(title);
					segEffChamberRun->GetXaxis()->SetTitle("Run Number");
					segEffChamberRun->GetYaxis()->SetTitle("CSC Segment Reconstuction Efficiency");
					segEffChamberRun->GetYaxis()->SetTitleOffset(1.45);
					segEffChamberRun->GetXaxis()->SetTickLength(0.015);
					segEffChamberRun->GetYaxis()->SetTickLength(0.015);
					segEffChamberRun->GetYaxis()->SetRangeUser(0.0,1.05);
					segEffChamberRun->GetXaxis()->SetRangeUser(355000.0,lastRun);
					segEffChamberRun->SetLineColor(kBlack);
					segEffChamberRun->SetMarkerColor(kBlack);
					segEffChamberRun->SetMarkerStyle(8);
					segEffChamberRun->SetMarkerSize(0.75);
					segEffChamberRun->Draw("HIST P");
					c1.Print(file);
					// first run 355100
					cscTextEffData << file << std::endl;
					for (Int_t ii=0; ii< lastRun-firstRun; ii++){
						if (segEffChamberRun->GetBinContent(ii)>0.0&&segEffChamberRun->GetBinContent(ii)<0.8){
							cscTextEffData << segEffChamberRun->GetXaxis()->GetBinCenter(ii) << " " << segEffChamberRun->GetBinContent(ii) << std::endl;
						}
					}	  

				}
			}
		}


		for (Int_t iiStation=0; iiStation < 8; iiStation++){
			for (Int_t iiRing=0; iiRing < 4; iiRing++){
				for (Int_t iiChamber=1; iiChamber < 37; iiChamber++){
					if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&iiRing==1&&iiChamber>18) continue;
					if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&(iiRing==0||iiRing==3)) continue;
					sprintf(name,"LCTEffLCSStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);

					if (iiStation<4) {
						if (iiRing == 0) {
							sprintf(title,"LCT Efficiency vs Strip LC for ME-%d%dA/%d",iiStation+1,iiRing+1,iiChamber);
							sprintf(file,"plots/ME-%d%dA/cscLCTEffRun3DataME-%d%dA-%dLCS.png",iiStation+1,iiRing+1,iiStation+1,iiRing+1,iiChamber);
						} else if (iiStation==0&&iiRing == 1) {
							sprintf(title,"LCT Efficiency vs Strip LC for ME-%d%dB/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%dB/cscLCTEffRun3DataME-%d%dB-%dLCS.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						} else {
							sprintf(title,"LCT Efficiency vs Strip LC for ME-%d%d/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%d/cscLCTEffRun3DataME-%d%d-%dLCS.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						}
					} else {
						if (iiRing == 0) {
							sprintf(title,"LCT Efficiency vs Strip LC for ME+%d%dA/%d",iiStation+1-4,iiRing+1,iiChamber);
							sprintf(file,"plots/ME+%d%dA/cscLCTEffRun3DataME+%d%dA-%dLCS.png",iiStation+1-4,iiRing+1,iiStation+1-4,iiRing+1,iiChamber);
						} else if (iiStation==4&&iiRing == 1) {
							sprintf(title,"LCT Efficiency vs Strip LC for ME+%d%dB/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%dB/cscLCTEffRun3DataME+%d%dB-%dLCS.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						} else {
							sprintf(title,"LCT Efficiency vs Strip LC for ME+%d%d/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%d/cscLCTEffRun3DataME+%d%d-%dLCS.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						}
					}



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



					sprintf(name,"LCTEffLCYStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);

					if (iiStation<4) {
						if (iiRing == 0) {
							sprintf(title,"LCT Efficiency vs Y LC for ME-%d%dA/%d",iiStation+1,iiRing+1,iiChamber);
							sprintf(file,"plots/ME-%d%dA/cscLCTEffRun3DataME-%d%dA-%dLCY.png",iiStation+1,iiRing+1,iiStation+1,iiRing+1,iiChamber);
						} else if (iiStation==0&&iiRing == 1) {
							sprintf(title,"LCT Efficiency vs Y LC for ME-%d%dB/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%dB/cscLCTEffRun3DataME-%d%dB-%dLCY.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						} else {
							sprintf(title,"LCT Efficiency vs Y LC for ME-%d%d/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%d/cscLCTEffRun3DataME-%d%d-%dLCY.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						}
					} else {
						if (iiRing == 0) {
							sprintf(title,"LCT Efficiency vs Y LC for ME+%d%dA/%d",iiStation+1-4,iiRing+1,iiChamber);
							sprintf(file,"plots/ME+%d%dA/cscLCTEffRun3DataME+%d%dA-%dLCY.png",iiStation+1-4,iiRing+1,iiStation+1-4,iiRing+1,iiChamber);
						} else if (iiStation==4&&iiRing == 1) {
							sprintf(title,"LCT Efficiency vs Y LC for ME+%d%dB/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%dB/cscLCTEffRun3DataME+%d%dB-%dLCY.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						} else {
							sprintf(title,"LCT Efficiency vs Y LC for ME+%d%d/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%d/cscLCTEffRun3DataME+%d%d-%dLCY.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						}
					}



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


					sprintf(name,"LCTEffStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);

					if (iiStation<4) {
						if (iiRing == 0) {
							sprintf(title,"LCT Efficiency vs Run for ME-%d%dA/%d",iiStation+1,iiRing+1,iiChamber);
							sprintf(file,"plots/ME-%d%dA/cscLCTEffRun3DataME-%d%dA-%dRun.png",iiStation+1,iiRing+1,iiStation+1,iiRing+1,iiChamber);
						} else if (iiStation==0&&iiRing == 1) {
							sprintf(title,"LCT Efficiency vs Run for ME-%d%dB/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%dB/cscLCTEffRun3DataME-%d%dB-%dRun.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						} else {
							sprintf(title,"LCT Efficiency vs Run for ME-%d%d/%d",iiStation+1,iiRing,iiChamber);
							sprintf(file,"plots/ME-%d%d/cscLCTEffRun3DataME-%d%d-%dRun.png",iiStation+1,iiRing,iiStation+1,iiRing,iiChamber);
						}
					} else {
						if (iiRing == 0) {
							sprintf(title,"LCT Efficiency vs Run for ME+%d%dA/%d",iiStation+1-4,iiRing+1,iiChamber);
							sprintf(file,"plots/ME+%d%dA/cscLCTEffRun3DataME+%d%dA-%dRun.png",iiStation+1-4,iiRing+1,iiStation+1-4,iiRing+1,iiChamber);
						} else if (iiStation==4&&iiRing == 1) {
							sprintf(title,"LCT Efficiency vs Run for ME+%d%dB/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%dB/cscLCTEffRun3DataME+%d%dB-%dRun.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						} else {
							sprintf(title,"LCT Efficiency vs Run for ME+%d%d/%d",iiStation+1-4,iiRing,iiChamber);
							sprintf(file,"plots/ME+%d%d/cscLCTEffRun3DataME+%d%d-%dRun.png",iiStation+1-4,iiRing,iiStation+1-4,iiRing,iiChamber);
						}
					}



					TH1F * LCTEffChamberRun = (TH1F*)file0->Get(name);
					LCTEffChamberRun->SetTitle(title);
					LCTEffChamberRun->GetXaxis()->SetTitle("Run Number");
					LCTEffChamberRun->GetYaxis()->SetTitle("CSC LCT Efficiency");
					LCTEffChamberRun->GetYaxis()->SetTitleOffset(1.45);
					LCTEffChamberRun->GetXaxis()->SetTickLength(0.015);
					LCTEffChamberRun->GetYaxis()->SetTickLength(0.015);
					LCTEffChamberRun->GetYaxis()->SetRangeUser(0.0,1.05);
					LCTEffChamberRun->GetXaxis()->SetRangeUser(355000.0,lastRun);
					LCTEffChamberRun->SetLineColor(kBlack);
					LCTEffChamberRun->SetMarkerColor(kBlack);
					LCTEffChamberRun->SetMarkerStyle(8);
					LCTEffChamberRun->SetMarkerSize(0.75);
					LCTEffChamberRun->Draw("HIST P");
					c1.Print(file);




				}
			}
		}

	}

	cscTextEffData.close();    

}
