#define CSCEffFast_cxx
#include "/cms/herndon/cscEffRun3/CSCEffFast.h"
#include <TH1.h>
#include <TH1F.h>
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
void CSCEffFast::Loop()
{
	//   In a ROOT session, you can do:
	//      root> .L CSCEffFast.C
	//      root> CSCEffFast t
	//      root> t.GetEntry(12); // Fill t data members with entry number 12
	//      root> t.Show();       // Show values of entry 12
	//      root> t.Show(16);     // Read and show values of entry 16
	//      root> t.Loop();       // Loop on all entries
	//


	std::cout << "Start CSCEffFast" << std::endl;
	std::cout.flush();

	TFile cscEffHistoFile("cscEffHistoFile.root","Recreate");


	char name[50];
	char stationRing[10];
	char stationRingC[10];
	char title[100];


	// Define Efficiency Histogram parameters

	bool DoubleMuGun = false;
	bool LowStats = false;
	bool badRunRangesTrack = false; // Min removal for 2022ABCDEFG
	bool badRunRangesTrack2 = false; // Max removal for 2022ABCDEFG
	bool badChambersTrack = false; // Chamber fremoval for 2022ABCDEFG
	bool oldBadChambersTrack = false; // Removal for Run2


	int firstRun = 355000;
	int lastRun = 362800;

	// Pt, Eta, phi (chamber) parameters and histograms

	//const Int_t numPtBins=9;       //number of pt bins in eff plots
	//Float_t ptBins[(numPtBins+1)] = {0.0,10.0,20.0,30.0,40.0,50.0,60.0,80.0,100.0,200.0};
	const Int_t numPtBins=17;       //number of pt bins in eff plots
	Float_t ptBins[(numPtBins+1)] = {0.0,10.0,20.0,30.0,40.0,50.0,60.0,80.0,100.0,200.0,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0};


	const Int_t numEtaBins=16;       //number of eta bins in eff plots 51 or 33 or 16
	// Eta bins around 2.05-2.1 are chossen to make one overlap bin where both even and odd ME11 chambers populate the same bin
	Float_t etaBins[(numEtaBins+1)] = {0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.50,1.6,1.7,1.8,1.9,2.0,2.1120,2.2,2.3,2.45};
	// 33 bins Float_t etaBins[(numEtaBins+1)] = {0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2,1.25,1.3,1.35,1.4,1.45,1.50,1.55,1.6,1.65,1.7,1.75,1.8,1.85,1.9,1.95,2.0,2.0568,2.1120,2.15,2.2,2.25,2.3,2.35,2.4,2.45};


	// 51 bins Float_t etaBins[(numEtaBins+1)] = {0.8,0.85,0.9,0.95,1.0,1.05,1.1,1.15,1.2,1.25,1.3,1.35,1.4,1.45,1.50,1.55,1.6,1.65,1.7,1.75,1.8,1.85,1.9,1.95,2.0,2.05,2.055,2.06,2.065,2.07,2.075,2.08,2.085,2.09,2.095,2.10,2.105,2.11,2.115,2.12,2.125,2.13,2.135,2.14,2.145,2.15,2.2,2.25,2.3,2.35,2.4,2.45};
	//2.0,2.04345,2.0568,2.07015,2.0835,2.09685,2.1102,2.12355,2.1369,2.15,2.2,2.25,2.3,2.35,2.4,2.45;
	const Int_t numIsoBins=14;       //number of track based isolation bins in eff plots
	Float_t isoBins[(numIsoBins+1)] = {0.0,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.24,0.28,0.34,0.40};
	const Int_t numPVBins=12;       //number of primary vertex bins eff plots 17, 9
	Float_t pvBins[(numPVBins+1)] = {-0.5,0.5,4.5,8.5,16.5,24.5,32.5,40.5,48.5,56.5,66.5,72.5,80.5};
	//Float_t pvBins[(numPVBins+1)] = {0.0,0.5,4.5,8.5,12.5,16.5,20.5,24.5,28.5,32.5,36.5,40.5,44.5,48.5,52.5,56.5,60.5,70.5};
	const Int_t numILBins=25;       //number instantatanious lumi bins in eff plots
	Float_t ilBins[(numILBins+1)] = {0.0,1000.0,2000.0,3000.0,4000.0,5000.0,6000.0,7000.0,8000.0,9000.0,10000.0,11000.0,12000.0,13000.0,14000.0,15000.0,16000.0,17000.0,18000.0,19000.0,20000.0,21000.0,22000.0,23000.0,24000.0,25000.0};

	// 2018D
	//const Int_t numRunBins=50;       //number of run in eff plots 50
	//Float_t runBins[(numRunBins+1)] = {315200.0,315400.0,315600.0,315800.0,316000.0,316200.0,316400.0,316600.0,316800.0,317000.0,317200.0,317400.0,317600.0,317800.0,318000.0,318200.0,318400.0,318600.0,318800.0,319100.0,319200.0,319400.0,319600.0,319800.0,320000.0,320200.0,320400.0,320600.0,320800.0,321000.0,321200.0,321400.0,321600.0,321800.0,322000.0,322200.0,322400.0,322600.0,322800.0,323000.0,323200.0,323400.0,323600.0,323800.0,324000.0,324200.0,324400.0,324600.0,324800.0,325000.0,325200.0};

	// Run 3 2022 A-F (there is a G?)
	const Int_t numRunBins=35;       //number of run
	Float_t runBins[(numRunBins+1)] = {355000.0,355200.0,355400.0,355600.0,355800.0,356000.0,356200.0,356400.0,356600.0,356800.0,357000.0,357200.0,357400.0,357600.0,357800.0,358000.0,359000.0,359200.0,359400.0,359600.0,359800.0,360000.0,360200.0,360400.0,360600.0,360800.0,361000.0,361200.0,361400.0,361600.0,361800.0,362000.0,362200.0,362400.0,362600.0,362800.0};

	// layers bins, hits by layer
	const Int_t numLayerBins=6;       //number of layers
	Float_t layerBins[(numLayerBins+1)] = {0.5,1.5,2.5,3.5,4.5,5.5,6.5};


	// DCFEB bins, DCFEB regions
	const Int_t numDCFEBBins=5;       //number of run
	Float_t dCFEBBins[(numDCFEBBins+1)] = {0.5,1.5,2.5,3.5,4.5,5.5};
	Float_t dCFEBLCSBins[(numDCFEBBins+1)] = {-1.5,16.0,32.0,48.0,64.0,81.5};



	// const Int_t numLCYBins=48;       //number of local coordinate y bins in eff plots
	// Float_t lCYBins[(numLCYBins+1)] = {-160.0,
	// 				       -150.0,-140.0,-130.0,-120.0,-110.0,
	// 				       -100.0,-90.0,-80.0,-75.0,-70.0,-65.0,-60.0,-55.0,
	// 				     -50.0,-45.0,-40.0,-35.0,-30.0,-25.0,-20.0,-15.0,-10.0,-5.0,
	// 				     0.0,5.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,
	// 				       50.0,55.0,60.0,65.0,70.0,75.0,80.0,90.0,
	// 				       100.0,110.0,120.0,130.0,140.0,
	// 				       150.0,160.0};
	const Int_t numLCYBins=32;       //number of local coordinate y bins in eff plots
	Float_t lCYBins[(numLCYBins+1)] = {-160.0,-150.0,-140.0,-130.0,-120.0,-110.0,
		-100.0,-90.0,-80.0,-70.0,-60.0,-50.0,-40.0,-30.0,-20.0,-10.0,
		0.0,10.0,20.0,30.0,40.0,50.0,60.0,70.0,80.0,90.0,
		100.0,110.0,120.0,130.0,140.0,150.0,160.0};
	// LCY info for chambers
	const Int_t numLCSBins=41;       //number of local coordinate strip bins in eff plots
	Float_t lCSBins[(numLCSBins+1)] = {-1.5,0.5,2.5,4.5,6.5,8.5,10.5,12.5,14.5,16.5,18.5,20.5,22.5,24.5,26.5,28.5,30.5,32.5,34.5,36.5,38.5,
		40.5,42.5,44.5,46.5,48.5,50.5,52.5,54.5,56.5,58.5,60.5,62.5,64.5,66.5,68.5,70.5,72.5,74.5,76.5,78.5,80.5};
	const Int_t numLCWBins=36;       //number of local coordinate wire bins in eff plots
	Float_t lCWBins[(numLCWBins+1)] = {-128.0,-112.0,-96.0,-88.0,-80.0,-72.0,-64.0,-56.0,-48.0,-40.0,-32.0,-24.0,-16.0,-8.0,0.0,8.0,16.0,24.0,32.0,40.0,48.0,56.0,64.0,72.0,80.0,88.0,96.0,112.0,128.0,144.0,160.0,176.0,192.0,208.0,224.0,240.0,256.0,};




	TH1F * segEffStationCRingPT[4][4];
	TH1F * segEffStationCRingEta[4][4];
	TH1F * segEffStationCRingIso[4][4];
	TH1F * segEffStationCRingPV[4][4];
	TH1F * segEffStationCRingIL[4][4];
	// TH1F * segEffStationCRingLCY[4][4];
	// TH1F * segEffStationCRingLCW[4][4];
	// TH1F * segEffStationCRingLCS[4][4];
	// TH1F * segEffStationCRingChamber[4][4];
	TH1F * LCTEffStationCRingPT[4][4];
	TH1F * LCTEffStationCRingEta[4][4];
	TH1F * LCTEffStationCRingIso[4][4];
	TH1F * LCTEffStationCRingPV[4][4];
	TH1F * LCTEffStationCRingIL[4][4];
	// TH1F * LCTEffStationCRingLCY[4][4];
	// TH1F * LCTEffStationCRingLCW[4][4];
	// TH1F * LCTEffStationCRingLCS[4][4];
	// TH1F * LCTEffStationCRingChamber[4][4];

	TH1F * segEffStationRingPT[8][4];
	TH1F * segEffStationRingEta[8][4];
	TH1F * segEffStationRingIso[8][4];
	TH1F * segEffStationRingPV[8][4];
	TH1F * segEffStationRingIL[8][4];
	TH1F * segEffStationRingRun[8][4];
	// TH1F * segEffStationRingLCY[8][4];
	// TH1F * segEffStationRingLCW[8][4];
	// TH1F * segEffStationRingLCS[8][4];
	// TH1F * segEffStationRingChamber[8][4];
	TH1F * LCTEffStationRingPT[8][4];
	TH1F * LCTEffStationRingEta[8][4];
	TH1F * LCTEffStationRingIso[8][4];
	TH1F * LCTEffStationRingPV[8][4];
	TH1F * LCTEffStationRingIL[8][4];
	TH1F * LCTEffStationRingRun[8][4];
	// TH1F * LCTEffStationRingLCY[8][4];
	// TH1F * LCTEffStationRingLCW[8][4];
	// TH1F * LCTEffStationRingLCS[8][4];
	// TH1F * LCTEffStationRingChamber[8][4];

	TH1F * segEffStationRingChamberLCY[8][4][37];
	TH1F * segEffStationRingChamberLCW[8][4][37];
	TH1F * segEffStationRingChamberLCS[8][4][37];
	TH1F * LCTEffStationRingChamberLCY[8][4][37];
	TH1F * LCTEffStationRingChamberLCW[8][4][37];
	TH1F * LCTEffStationRingChamberLCS[8][4][37];

	TH1F * segDenStationRingChamberRun[8][4][37];
	TH1F * LCTDenStationRingChamberRun[8][4][37];
	TH1F * segNumStationRingChamberRun[8][4][37];
	TH1F * LCTNumStationRingChamberRun[8][4][37];
	TH1F * segEffStationRingChamberRun[8][4][37];
	TH1F * LCTEffStationRingChamberRun[8][4][37];



	TH2F * segEff2DStationRingChamberRun[8][4]; 
	TH2F * LCTEff2DStationRingChamberRun[8][4]; 

	TH2F * segEff2DStationRingChamberLayer[8][4]; 
	TH2F * LCTEff2DStationRingChamberLayer[8][4]; 

	TH2F * segEff2DStationRingChamberDCFEB[8][4]; 
	TH2F * LCTEff2DStationRingChamberDCFEB[8][4]; 


	TH1F *resSegStationRingChamber[8][4][37];
	TH1F *resSigmaSegStationRingChamber[8][4][37];

	TH2F *yySegStationRing[8][4];

	TH1F *zMassSegDenStationRingChamber[8][4][37];
	TH1F *zMassSegNumStationRingChamber[8][4][37];
	TH1F *zMassSegDenStationRingPV[8][4][numPVBins];
	TH1F *zMassSegNumStationRingPV[8][4][numPVBins];
	TH1F *zMassLCTNumStationRingPV[8][4][numPVBins];



	//TF1 * fit = new TF1("myfit", "[0] / sqrt(2.0 * TMath::Pi()) / [2] * exp(-(x-[1])*(x-[1])/2./[2]/[2]) + [3] + x*[4] + [5] / sqrt(2.0 * TMath::Pi()) / [7] * exp(-(x-[6])*(x-[6])/2./[7]/[7])", 76.0, 106.0);
	TF1 * fit = new TF1("myfit", "[0] / sqrt(2.0 * TMath::Pi()) / [2] * exp(-(x-[1])*(x-[1])/2./[2]/[2]) + exp([3] + x*[4]) + [5] / sqrt(2.0 * TMath::Pi()) / [7] * exp(-(x-[6])*(x-[6])/2./[7]/[7])", 76.0, 106.0);

	Bool_t fitEff = false;
	fit->SetParNames("Constant","Mean","Sigma","p0","p1","Constant2","Mean2","Sigma2");


	// Eventually use these to lable the stations and rings

	for (Int_t iiStation=0; iiStation < 8; iiStation++){
		for (Int_t iiRing=0; iiRing < 4; iiRing++){

			// if (iiStation == 0 && iiRing == 0 ) sprintf(stationRing,"ME-11A");
			// if (iiStation == 0 && iiRing == 1 ) sprintf(stationRing,"ME-11B");
			// if (iiStation == 0 && iiRing == 2 ) sprintf(stationRing,"ME-12");
			// if (iiStation == 0 && iiRing == 3 ) sprintf(stationRing,"ME-13");

			// if (iiStation == 4 && iiRing == 0 ) sprintf(stationRing,"ME+11A");
			// if (iiStation == 4 && iiRing == 1 ) sprintf(stationRing,"ME+11B");
			// if (iiStation == 4 && iiRing == 2 ) sprintf(stationRing,"ME+12");
			// if (iiStation == 4 && iiRing == 3 ) sprintf(stationRing,"ME+13");

			// if (iiStation == 2 && iiRing == 0 ) sprintf(stationRing,"ME-11AEven");
			// if (iiStation == 2 && iiRing == 3 ) sprintf(stationRing,"ME-11Odd");
			// if (iiStation == 3 && iiRing == 0 ) sprintf(stationRing,"ME-11BEven");
			// if (iiStation == 3 && iiRing == 3 ) sprintf(stationRing,"ME-11BOdd");

			// if (iiStation == 6 && iiRing == 0 ) sprintf(stationRing,"ME+11AEven");
			// if (iiStation == 6 && iiRing == 3 ) sprintf(stationRing,"ME+11Odd");
			// if (iiStation == 7 && iiRing == 0 ) sprintf(stationRing,"ME+11BEven");
			// if (iiStation == 7 && iiRing == 3 ) sprintf(stationRing,"ME+11BOdd");

			// if (iiStation == 1 && iiRing == 1 ) sprintf(stationRing,"ME-21");
			// if (iiStation == 1 && iiRing == 2 ) sprintf(stationRing,"ME-22");

			// if (iiStation == 5 && iiRing == 1 ) sprintf(stationRing,"ME+21");
			// if (iiStation == 5 && iiRing == 2 ) sprintf(stationRing,"ME+22");

			// if (iiStation == 2 && iiRing == 1 ) sprintf(stationRing,"ME-31");
			// if (iiStation == 2 && iiRing == 2 ) sprintf(stationRing,"ME-32");

			// if (iiStation == 6 && iiRing == 1 ) sprintf(stationRing,"ME+31");
			// if (iiStation == 6 && iiRing == 2 ) sprintf(stationRing,"ME+32");

			// if (iiStation == 3 && iiRing == 1 ) sprintf(stationRing,"ME-41");
			// if (iiStation == 3 && iiRing == 2 ) sprintf(stationRing,"ME-42");

			// if (iiStation == 7 && iiRing == 1 ) sprintf(stationRing,"ME+41");
			// if (iiStation == 7 && iiRing == 2 ) sprintf(stationRing,"ME+42");

			// if (iiStation == 0 && iiRing == 0 ) sprintf(stationRingC,"ME11A");
			// if (iiStation == 0 && iiRing == 1 ) sprintf(stationRingC,"ME11B");
			// if (iiStation == 0 && iiRing == 2 ) sprintf(stationRingC,"ME12");
			// if (iiStation == 0 && iiRing == 3 ) sprintf(stationRingC,"ME13");

			// if (iiStation == 2 && iiRing == 0 ) sprintf(stationRingC,"ME11AEven");
			// if (iiStation == 2 && iiRing == 3 ) sprintf(stationRingC,"ME11Odd");
			// if (iiStation == 3 && iiRing == 0 ) sprintf(stationRingC,"ME11BEven");
			// if (iiStation == 3 && iiRing == 3 ) sprintf(stationRingC,"ME11BOdd");

			// if (iiStation == 1 && iiRing == 1 ) sprintf(stationRingC,"ME21");
			// if (iiStation == 1 && iiRing == 2 ) sprintf(stationRingC,"ME22");

			// if (iiStation == 2 && iiRing == 1 ) sprintf(stationRingC,"ME31");
			// if (iiStation == 2 && iiRing == 2 ) sprintf(stationRingC,"ME32");

			// if (iiStation == 3 && iiRing == 1 ) sprintf(stationRingC,"ME41");
			// if (iiStation == 3 && iiRing == 2 ) sprintf(stationRingC,"ME42");




			// +/- together
			if (iiStation<4){
				sprintf(name,"segEffPTStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"Segment Efficiency vs p_{T} for Station %d Ring %d",iiStation+1,iiRing);
				segEffStationCRingPT[iiStation][iiRing] = new TH1F(name,title,numPtBins, &(*ptBins));
				segEffStationCRingPT[iiStation][iiRing]->GetXaxis()->SetTitle("probe p_{T} (GeV)");
				segEffStationCRingPT[iiStation][iiRing]->GetYaxis()->SetTitle("CSC Segment Reconstruction Efficiency");
				segEffStationCRingPT[iiStation][iiRing]->GetYaxis()->SetRangeUser(0.8,1.02);
				segEffStationCRingPT[iiStation][iiRing]->GetYaxis()->SetTitleOffset(1.2);
				segEffStationCRingPT[iiStation][iiRing]->SetMarkerStyle(8);
				segEffStationCRingPT[iiStation][iiRing]->SetMarkerSize(0.65);
				sprintf(name,"LCTEffPTStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"LCT Efficiency vs p_{T} for Station %d Ring %d",iiStation+1,iiRing);
				LCTEffStationCRingPT[iiStation][iiRing] = new TH1F(name,title,numPtBins, &(*ptBins));
				LCTEffStationCRingPT[iiStation][iiRing]->GetXaxis()->SetTitle("probe p_{T} (GeV)");
				LCTEffStationCRingPT[iiStation][iiRing]->GetYaxis()->SetTitle("CSC LCT Efficiency");
				LCTEffStationCRingPT[iiStation][iiRing]->GetYaxis()->SetRangeUser(0.8,1.02);
				LCTEffStationCRingPT[iiStation][iiRing]->GetYaxis()->SetTitleOffset(1.2);
				LCTEffStationCRingPT[iiStation][iiRing]->SetMarkerStyle(8);
				LCTEffStationCRingPT[iiStation][iiRing]->SetMarkerSize(0.65);


				sprintf(name,"segEffEtaStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"Segement Efficiency vs #eta for Station %d Ring %d",iiStation+1,iiRing);
				segEffStationCRingEta[iiStation][iiRing] = new TH1F(name,title,numEtaBins, &(*etaBins));
				segEffStationCRingEta[iiStation][iiRing]->GetXaxis()->SetTitle("probe #eta");
				segEffStationCRingEta[iiStation][iiRing]->GetYaxis()->SetTitle("CSC Segment Reconstruction Efficiency");
				segEffStationCRingEta[iiStation][iiRing]->GetYaxis()->SetRangeUser(0.8,1.02);
				segEffStationCRingEta[iiStation][iiRing]->GetYaxis()->SetTitleOffset(1.2);
				segEffStationCRingEta[iiStation][iiRing]->SetMarkerStyle(8);
				segEffStationCRingEta[iiStation][iiRing]->SetMarkerSize(0.65);
				sprintf(name,"LCTEffEtaStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"LCT Efficiency vs #eta for Station %d Ring %d",iiStation+1,iiRing);
				LCTEffStationCRingEta[iiStation][iiRing] = new TH1F(name,title,numEtaBins, &(*etaBins));
				LCTEffStationCRingEta[iiStation][iiRing]->GetXaxis()->SetTitle("probe #eta");
				LCTEffStationCRingEta[iiStation][iiRing]->GetYaxis()->SetTitle("CSC LCT Efficiency");
				LCTEffStationCRingEta[iiStation][iiRing]->GetYaxis()->SetRangeUser(0.8,1.02);
				LCTEffStationCRingEta[iiStation][iiRing]->GetYaxis()->SetTitleOffset(1.2);
				LCTEffStationCRingEta[iiStation][iiRing]->SetMarkerStyle(8);
				LCTEffStationCRingEta[iiStation][iiRing]->SetMarkerSize(0.65);

				sprintf(name,"segEffIsoStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"Segement Efficiency vs Iso for Station %d Ring %d",iiStation+1,iiRing);
				segEffStationCRingIso[iiStation][iiRing] = new TH1F(name,title,numIsoBins, &(*isoBins));
				sprintf(name,"LCTEffIsoStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"LCT Efficiency vs Iso for Station %d Ring %d",iiStation+1,iiRing);
				LCTEffStationCRingIso[iiStation][iiRing] = new TH1F(name,title,numIsoBins, &(*isoBins));

				sprintf(name,"segEffPVStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"Segement Efficiency vs PV for Station %d Ring %d",iiStation+1,iiRing);
				segEffStationCRingPV[iiStation][iiRing] = new TH1F(name,title,numPVBins, &(*pvBins));
				segEffStationCRingPV[iiStation][iiRing]->GetXaxis()->SetTitle("Number of Primary Vertices");
				segEffStationCRingPV[iiStation][iiRing]->GetYaxis()->SetTitle("CSC Segment Reconstruction Efficiency");
				segEffStationCRingPV[iiStation][iiRing]->GetYaxis()->SetTitleOffset(1.2);
				segEffStationCRingPV[iiStation][iiRing]->SetMarkerStyle(8);
				segEffStationCRingPV[iiStation][iiRing]->SetMarkerSize(0.65);
				sprintf(name,"LCTEffPVStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"LCT Efficiency vs PV for Station %d Ring %d",iiStation+1,iiRing);
				LCTEffStationCRingPV[iiStation][iiRing] = new TH1F(name,title,numPVBins, &(*pvBins));
				LCTEffStationCRingPV[iiStation][iiRing]->GetXaxis()->SetTitle("Number of Primary Vertices");
				LCTEffStationCRingPV[iiStation][iiRing]->GetYaxis()->SetTitle("CSC LCT Efficiency");
				LCTEffStationCRingPV[iiStation][iiRing]->GetYaxis()->SetTitleOffset(1.2);
				LCTEffStationCRingPV[iiStation][iiRing]->SetMarkerStyle(8);
				LCTEffStationCRingPV[iiStation][iiRing]->SetMarkerSize(0.65);

				sprintf(name,"segEffILStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"Segement Efficiency vs IL for Station %d Ring %d",iiStation+1,iiRing);
				segEffStationCRingIL[iiStation][iiRing] = new TH1F(name,title,numILBins, &(*ilBins));
				sprintf(name,"LCTEffILStation%dCRing%d",iiStation+1,iiRing);
				sprintf(title,"LCT Efficiency vs IL for Station %d Ring %d",iiStation+1,iiRing);
				LCTEffStationCRingIL[iiStation][iiRing] = new TH1F(name,title,numILBins, &(*ilBins));



				// sprintf(name,"segEffLCYStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"Segement Efficiency vs Y LC for Station %d Ring %d",iiStation+1,iiRing);
				// segEffStationCRingLCY[iiStation][iiRing] = new TH1F(name,title,numLCYBins, &(*lCYBins));
				// sprintf(name,"LCTEffLCYStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"LCT Efficiency vs LCY for Station %d Ring %d",iiStation+1,iiRing);
				// LCTEffStationCRingLCY[iiStation][iiRing] = new TH1F(name,title,numLCYBins, &(*lCYBins));

				// sprintf(name,"segEffLCWStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"Segement Efficiency vs Wire LC for Station %d Ring %d",iiStation+1,iiRing);
				// segEffStationCRingLCW[iiStation][iiRing] = new TH1F(name,title,numLCWBins, &(*lCWBins));
				// sprintf(name,"LCTEffLCWStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"LCT Efficiency vs Wire LC for Station %d Ring %d",iiStation+1,iiRing);
				// LCTEffStationCRingLCW[iiStation][iiRing] = new TH1F(name,title,numLCWBins, &(*lCWBins));

				// sprintf(name,"segEffLCSStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"Segement Efficiency vs Strip LC for Station %d Ring %d",iiStation+1,iiRing);
				// segEffStationCRingLCS[iiStation][iiRing] = new TH1F(name,title,numLCSBins, &(*lCSBins));
				// sprintf(name,"LCTEffLCSStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"LCT Efficiency vs LCS for Station %d Ring %d",iiStation+1,iiRing);
				// LCTEffStationCRingLCS[iiStation][iiRing] = new TH1F(name,title,numLCSBins, &(*lCSBins));

				// sprintf(name,"segEffChamberStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"Segement Efficiency vs Chamber for Station %d Ring %d",iiStation+1,iiRing);
				// segEffStationCRingChamber[iiStation][iiRing] = new TH1F(name,title,36,0.5,36.5);
				// sprintf(name,"LCTEffChamberStation%dCRing%d",iiStation+1,iiRing);
				// sprintf(title,"LCT Efficiency vs Chamber for Station %d Ring %d",iiStation+1,iiRing);
				// LCTEffStationCRingChamber[iiStation][iiRing] = new TH1F(name,title,36,0.5,36.5);

			}

			// +/- seperated 
			sprintf(name,"segEffPTStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs Pt for Station %d Ring %d",iiStation+1,iiRing);
			segEffStationRingPT[iiStation][iiRing] = new TH1F(name,title,numPtBins, &(*ptBins));
			sprintf(name,"LCTEffPTStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs Pt for Station %d Ring %d",iiStation+1,iiRing);
			LCTEffStationRingPT[iiStation][iiRing] = new TH1F(name,title,numPtBins, &(*ptBins));

			sprintf(name,"segEffEtaStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs Eta for Station %d Ring %d",iiStation+1,iiRing);
			segEffStationRingEta[iiStation][iiRing] = new TH1F(name,title,numEtaBins, &(*etaBins));
			sprintf(name,"LCTEffEtaStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs Eta for Station %d Ring %d",iiStation+1,iiRing);
			LCTEffStationRingEta[iiStation][iiRing] = new TH1F(name,title,numEtaBins, &(*etaBins));

			sprintf(name,"segEffIsoStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs Iso for Station %d Ring %d",iiStation+1,iiRing);
			segEffStationRingIso[iiStation][iiRing] = new TH1F(name,title,numIsoBins, &(*isoBins));
			sprintf(name,"LCTEffIsoStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs Iso for Station %d Ring %d",iiStation+1,iiRing);
			LCTEffStationRingIso[iiStation][iiRing] = new TH1F(name,title,numIsoBins, &(*isoBins));

			sprintf(name,"segEffPVStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs PV for Station %d Ring %d",iiStation+1,iiRing);
			segEffStationRingPV[iiStation][iiRing] = new TH1F(name,title,numPVBins, &(*pvBins));
			sprintf(name,"LCTEffPVStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs PV for Station %d Ring %d",iiStation+1,iiRing);
			LCTEffStationRingPV[iiStation][iiRing] = new TH1F(name,title,numPVBins, &(*pvBins));

			sprintf(name,"segEffILStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs IL for Station %d Ring %d",iiStation+1,iiRing);
			segEffStationRingIL[iiStation][iiRing] = new TH1F(name,title,numILBins, &(*ilBins));
			sprintf(name,"LCTEffILStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs IL for Station %d Ring %d",iiStation+1,iiRing);
			LCTEffStationRingIL[iiStation][iiRing] = new TH1F(name,title,numILBins, &(*ilBins));

			sprintf(name,"segEffRunStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs Run for Station %d Ring %d",iiStation+1,iiRing);
			segEffStationRingRun[iiStation][iiRing] = new TH1F(name,title,numRunBins, &(*runBins));
			sprintf(name,"LCTEffRunStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs Run for Station %d Ring %d",iiStation+1,iiRing);
			LCTEffStationRingRun[iiStation][iiRing] = new TH1F(name,title,numRunBins, &(*runBins));

			// sprintf(name,"segEffLCYStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"Segement Efficiency vs Y LC for Station %d Ring %d",iiStation+1,iiRing);
			// segEffStationRingLCY[iiStation][iiRing] = new TH1F(name,title,numLCYBins, &(*lCYBins));
			// sprintf(name,"LCTEffLCYStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"LCT Efficiency vs LCY for Station %d Ring %d",iiStation+1,iiRing);
			// LCTEffStationRingLCY[iiStation][iiRing] = new TH1F(name,title,numLCYBins, &(*lCYBins));

			// sprintf(name,"segEffLCWStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"Segement Efficiency vs Wire LC for Station %d Ring %d",iiStation+1,iiRing);
			// segEffStationRingLCW[iiStation][iiRing] = new TH1F(name,title,numLCWBins, &(*lCWBins));
			// sprintf(name,"LCTEffLCWStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"LCT Efficiency vs Wire LC for Station %d Ring %d",iiStation+1,iiRing);
			// LCTEffStationRingLCW[iiStation][iiRing] = new TH1F(name,title,numLCWBins, &(*lCWBins));

			// sprintf(name,"segEffLCSStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"Segement Efficiency vs Strip LC for Station %d Ring %d",iiStation+1,iiRing);
			// segEffStationRingLCS[iiStation][iiRing] = new TH1F(name,title,numLCSBins, &(*lCSBins));
			// sprintf(name,"LCTEffLCSStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"LCT Efficiency vs LCS for Station %d Ring %d",iiStation+1,iiRing);
			// LCTEffStationRingLCS[iiStation][iiRing] = new TH1F(name,title,numLCSBins, &(*lCSBins));

			// sprintf(name,"segEffChamberStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"Segement Efficiency vs Chamber for Station %d Ring %d",iiStation+1,iiRing);
			// segEffStationRingChamber[iiStation][iiRing] = new TH1F(name,title,36,0.5,36.5);
			// sprintf(name,"LCTEffChamberStation%dRing%d",iiStation+1,iiRing);
			// sprintf(title,"LCT Efficiency vs Chamber for Station %d Ring %d",iiStation+1,iiRing);
			// LCTEffStationRingChamber[iiStation][iiRing] = new TH1F(name,title,36,0.5,36.5);


			sprintf(name,"segEff2DStation%dRing%dChamberRun",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs Chamber & Run for Station %d Ring %d",iiStation+1,iiRing);
			segEff2DStationRingChamberRun[iiStation][iiRing] = new TH2F(name,title,36,0.5,36.5,numRunBins,runBins[0],runBins[numRunBins]);
			segEff2DStationRingChamberRun[iiStation][iiRing]->SetMarkerSize(0.5);

			sprintf(name,"LCTEff2DStation%dRing%dChamberRun",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs Chamber & Run for Station %d Ring %d",iiStation+1,iiRing);
			LCTEff2DStationRingChamberRun[iiStation][iiRing] = new TH2F(name,title,36,0.5,36.5,numRunBins,runBins[0],runBins[numRunBins]);
			LCTEff2DStationRingChamberRun[iiStation][iiRing]->SetMarkerSize(0.5);


			sprintf(name,"segEff2DStation%dRing%dChamberLayer",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs Chamber & Layer for Station %d Ring %d",iiStation+1,iiRing);
			segEff2DStationRingChamberLayer[iiStation][iiRing] = new TH2F(name,title,36,0.5,36.5,numLayerBins,layerBins[0],layerBins[numLayerBins]);
			segEff2DStationRingChamberLayer[iiStation][iiRing]->SetMarkerSize(0.5);

			sprintf(name,"LCTEff2DStation%dRing%dChamberLayer",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs Chamber & Layer for Station %d Ring %d",iiStation+1,iiRing);
			LCTEff2DStationRingChamberLayer[iiStation][iiRing] = new TH2F(name,title,36,0.5,36.5,numLayerBins,layerBins[0],layerBins[numLayerBins]);
			LCTEff2DStationRingChamberLayer[iiStation][iiRing]->SetMarkerSize(0.5);


			sprintf(name,"segEff2DStation%dRing%dChamberDCFEB",iiStation+1,iiRing);
			sprintf(title,"Segement Efficiency vs Chamber & DCFEB for Station %d Ring %d",iiStation+1,iiRing);
			segEff2DStationRingChamberDCFEB[iiStation][iiRing] = new TH2F(name,title,36,0.5,36.5,numDCFEBBins,dCFEBBins[0],dCFEBBins[numDCFEBBins]);
			segEff2DStationRingChamberDCFEB[iiStation][iiRing]->SetMarkerSize(0.5);

			sprintf(name,"LCTEff2DStation%dRing%dChamberDCFEB",iiStation+1,iiRing);
			sprintf(title,"LCT Efficiency vs Chamber & DCFEB for Station %d Ring %d",iiStation+1,iiRing);
			LCTEff2DStationRingChamberDCFEB[iiStation][iiRing] = new TH2F(name,title,36,0.5,36.5,numDCFEBBins,dCFEBBins[0],dCFEBBins[numDCFEBBins]);
			LCTEff2DStationRingChamberDCFEB[iiStation][iiRing]->SetMarkerSize(0.5);



			sprintf(name,"yySegStation%dRing%d",iiStation+1,iiRing);
			sprintf(title,"seg y vs track y or Station %d Ring %d",iiStation+1,iiRing);
			yySegStationRing[iiStation][iiRing] = new TH2F(name,title,160,-50.0,-10.0,160,-50.0,-10.0);
			yySegStationRing[iiStation][iiRing]->SetMarkerSize(0.5);

			for (Int_t iiPV=0; iiPV < numPVBins; iiPV++){
				sprintf(name,"zMassSegDenStation%dRing%dPV%d",iiStation+1,iiRing,iiPV);
				sprintf(title,"Z Mass Segment Den for Station %d Ring %d PV %d",iiStation+1,iiRing,iiPV);
				zMassSegDenStationRingPV[iiStation][iiRing][iiPV] = new TH1F(name,title, 120, 76.0, 106.0);
				sprintf(name,"zMassSegNumStation%dRing%dPV%d",iiStation+1,iiRing,iiPV);
				sprintf(title,"Z Mass Segment Num for Station %d Ring %d PV %d",iiStation+1,iiRing,iiPV);
				zMassSegNumStationRingPV[iiStation][iiRing][iiPV] = new TH1F(name,title, 120, 76.0, 106.0);

				sprintf(name,"zMassLCTNumStation%dRing%dPV%d",iiStation+1,iiRing,iiPV);
				sprintf(title,"Z Mass LCT Num for Station %d Ring %d PV %d",iiStation+1,iiRing,iiPV);
				zMassLCTNumStationRingPV[iiStation][iiRing][iiPV] = new TH1F(name,title, 120, 76.0, 106.0);

			}


			for (Int_t iiChamber=0; iiChamber < 37; iiChamber++){
				sprintf(name,"segDenStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segement Den vs Run for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				segDenStationRingChamberRun[iiStation][iiRing][iiChamber] = new TH1F(name,title,lastRun-firstRun,firstRun,lastRun);
				sprintf(name,"segNumStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segement Num vs Run for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				segNumStationRingChamberRun[iiStation][iiRing][iiChamber] = new TH1F(name,title,lastRun-firstRun,firstRun,lastRun);
				sprintf(name,"segEffStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segement Efficiency vs Run for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				segEffStationRingChamberRun[iiStation][iiRing][iiChamber] = new TH1F(name,title,lastRun-firstRun,firstRun,lastRun);
				segEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetMarkerSize(0.5);
				segEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetMarkerStyle(8);


				sprintf(name,"LCTDenStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
				sprintf(title,"LCT Den vs Run for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				LCTDenStationRingChamberRun[iiStation][iiRing][iiChamber] = new TH1F(name,title,lastRun-firstRun,firstRun,lastRun);
				sprintf(name,"LCTNumStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
				sprintf(title,"LCT Num vs Run for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				LCTNumStationRingChamberRun[iiStation][iiRing][iiChamber] = new TH1F(name,title,lastRun-firstRun,firstRun,lastRun);
				sprintf(name,"LCTEffStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
				sprintf(title,"LCT Efficiency vs Run for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber] = new TH1F(name,title,lastRun-firstRun,firstRun,lastRun);
				LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetMarkerSize(0.5);
				LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetMarkerStyle(8);


				sprintf(name,"zMassSegDenStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Z Mass Segment Den for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber] = new TH1F(name,title, 120, 76.0, 106.0);
				sprintf(name,"zMassSegNumStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Z Mass Segment Num for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber] = new TH1F(name,title, 120, 76.0, 106.0);

				sprintf(name,"resSegStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segment Residuals for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				resSegStationRingChamber[iiStation][iiRing][iiChamber] = new TH1F(name,title, 200, -20.0, 20.0);

				sprintf(name,"resSigmaSegStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segment Residuals for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				resSigmaSegStationRingChamber[iiStation][iiRing][iiChamber] = new TH1F(name,title, 200, -10.0, 10.0);

				sprintf(name,"segEffLCYStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segement Efficiency vs Y LC for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				segEffStationRingChamberLCY[iiStation][iiRing][iiChamber] = new TH1F(name,title,numLCYBins, &(*lCYBins));
				sprintf(name,"LCTEffLCYStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"LCT Efficiency vs LCY for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				LCTEffStationRingChamberLCY[iiStation][iiRing][iiChamber] = new TH1F(name,title,numLCYBins, &(*lCYBins));

				sprintf(name,"segEffLCWStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segement Efficiency vs Wire LC for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				segEffStationRingChamberLCW[iiStation][iiRing][iiChamber] = new TH1F(name,title,numLCWBins, &(*lCWBins));
				sprintf(name,"LCTEffLCWStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"LCT Efficiency vs Wire LC for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				LCTEffStationRingChamberLCW[iiStation][iiRing][iiChamber] = new TH1F(name,title,numLCWBins, &(*lCWBins));


				sprintf(name,"segEffLCSStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"Segement Efficiency vs Strip LC for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				segEffStationRingChamberLCS[iiStation][iiRing][iiChamber] = new TH1F(name,title,numLCSBins, &(*lCSBins));
				sprintf(name,"LCTEffLCSStation%dRing%dChamber%d",iiStation+1,iiRing,iiChamber);
				sprintf(title,"LCT Efficiency vs LCS for Station %d Ring %d Chamber %d",iiStation+1,iiRing,iiChamber);
				LCTEffStationRingChamberLCS[iiStation][iiRing][iiChamber] = new TH1F(name,title,numLCSBins, &(*lCSBins));

			}
		}
	}


	TH2F * segEff2DStationRingChamber  = new TH2F("segEff2DStationRingChamber", "Segement Efficiency 2D by Chamber & Ring",36,0.5,36.5,20,0.5,20.5);
	segEff2DStationRingChamber->GetXaxis()->SetTitle("Chamber #");
	segEff2DStationRingChamber->GetYaxis()->SetTitle("Ring ");
	segEff2DStationRingChamber->GetYaxis()->SetTitleOffset(1.45);
	segEff2DStationRingChamber->SetMarkerSize(0.5);
	segEff2DStationRingChamber->GetXaxis()->SetTickLength(0.015);
	segEff2DStationRingChamber->GetYaxis()->SetTickLength(0.015);
	const char *Rings[20] = {"ME-42","ME-41","ME-32","ME-31","ME-22","ME-21","ME-13","ME-12","ME-11B","ME-11A","ME+11A","ME+11B","ME+12","ME+13","ME+21","ME+22","ME+31","ME+32","ME+41","ME+42"};
	for (Int_t i=0;i<20;i++) { segEff2DStationRingChamber->GetYaxis()->SetBinLabel(i+1,Rings[i]);}
	TH2F * LCTEff2DStationRingChamber = new TH2F("LCTEff2DStationRingChamber", "LCT Efficiency 2D by Chamber & Ring",36,0.5,36.5,20,0.5,20.5);
	LCTEff2DStationRingChamber->GetXaxis()->SetTitle("Chamber #");
	LCTEff2DStationRingChamber->GetYaxis()->SetTitle("Ring ");
	LCTEff2DStationRingChamber->GetYaxis()->SetTitleOffset(1.45);
	LCTEff2DStationRingChamber->SetMarkerSize(0.5);
	LCTEff2DStationRingChamber->GetXaxis()->SetTickLength(0.015);
	LCTEff2DStationRingChamber->GetYaxis()->SetTickLength(0.015);
	for (Int_t i=0;i<20;i++) {LCTEff2DStationRingChamber->GetYaxis()->SetBinLabel(i+1,Rings[i]);}


	TH2F * segEffFit2DStationRingChamber = new TH2F("segEffFit2DStationRingChamber", "Fit Segment Efficiency 2D by Chamber & Ring",36,0.5,36.5,20,0.5,20.5);
	segEffFit2DStationRingChamber->GetXaxis()->SetTitle("Chamber #");
	segEffFit2DStationRingChamber->GetYaxis()->SetTitle("Ring ");
	segEffFit2DStationRingChamber->GetYaxis()->SetTitleOffset(1.45);
	segEffFit2DStationRingChamber->SetMarkerSize(0.5);
	segEffFit2DStationRingChamber->GetXaxis()->SetTickLength(0.015);
	segEffFit2DStationRingChamber->GetYaxis()->SetTickLength(0.015);
	for (Int_t i=0;i<20;i++) {segEffFit2DStationRingChamber->GetYaxis()->SetBinLabel(i+1,Rings[i]);}

	TH2F * segEffDiff2DStationRingChamber = new TH2F("segEffDiff2DStationRingChamber", "Diff Segment Efficiency 2D by Chamber & Ring",36,0.5,36.5,20,0.5,20.5);
	segEffDiff2DStationRingChamber->GetXaxis()->SetTitle("Chamber #");
	segEffDiff2DStationRingChamber->GetYaxis()->SetTitle("Ring ");
	segEffDiff2DStationRingChamber->GetYaxis()->SetTitleOffset(1.45);
	segEffDiff2DStationRingChamber->SetMarkerSize(0.5);
	segEffDiff2DStationRingChamber->GetXaxis()->SetTickLength(0.015);
	segEffDiff2DStationRingChamber->GetYaxis()->SetTickLength(0.015);
	for (Int_t i=0;i<20;i++) {segEffDiff2DStationRingChamber->GetYaxis()->SetBinLabel(i+1,Rings[i]);}

	TH1F * segEffDiff1D  = new TH1F("segEffDiff1D", "Sideband Subtration - Fit Efficiency Differences",100,-0.1,0.1);

	// Mass Histogram parameters and histrograms

	TH1F *zMassGood  = new TH1F("zMassGood", "Z Mass Good Segements", 120, 60.0, 120.0);
	TH1F *zMassAll  = new TH1F("zMassAll", "Z Mass all Good Probes", 120, 60.0, 120.0);
	TH1F *zMassBad  = new TH1F("zMassBad", "Z Mass Bad Segements", 120, 60.0, 120.0);


	// Muon Segement Histrograms

	TH1F *muonSegmentsFidAll  = new TH1F("muonSegmentsFidAll", "Number of Muon Segments Fiducial", 6, -0.5, 5.5);
	TH1F *muonSegmentsFid1  = new TH1F("muonSegmentsFid1", "Number of Muon Segments Fiducial ring 1", 6, -0.5, 5.5);
	TH1F *muonSegmentsWithME21  = new TH1F("muonSegmentsWithME21", "Number of Muon Segments found ME21", 6, -0.5, 5.5);
	TH1F *muonSegmentsNoME21  = new TH1F("muonSegmentsNoME21", "Number of Muon Segments No ME21", 6, 0.5, 5.5);

	TH1F *segmentsFidAll  = new TH1F("segmentsFidAll", "Number of CSC Segments Fiducial", 6, -0.5, 5.5);
	TH1F *segmentsFid1  = new TH1F("segmentsFid1", "Number of CSC Segments Fiducial ring 1", 6, -0.5, 5.5);
	TH1F *segmentsWithME21  = new TH1F("segmentsWithME21", "Number of CSC Segments found ME21", 6, -0.5, 5.5);
	TH1F *segmentsNoME21  = new TH1F("segmentsNoME21", "Number of CSC Segments No ME21", 6, -0.5, 5.5);

	TH1F *muonSegmentsFid2  = new TH1F("muonSegmentsFid2", "Number of Reconstructed Muon Segments Fiducial ring 2", 6, -0.5, 5.5);
	TH1F *segmentsFid2  = new TH1F("segmentsFid2", "Number of CSC Segments fiducial ring 2", 6, -0.5, 5.5);

	TH1F *muonSegmentsFid1HighPV  = new TH1F("muonSegmentsFid1HighPV", "Number Muon Segments Fiducial ring 1 High PV", 6, -0.5, 5.5);
	TH1F *muonSegmentsFid2HighPV  = new TH1F("muonSegmentsFid2HighPV", "Number Muon Segments fiducial ring 2 High PV", 6, -0.5, 5.5);
	TH1F *muonSegmentsFid1LowPV  = new TH1F("muonSegmentsFid1LowPV", "Number Muon Segments Fiducial ring 1 Low PV", 6, -0.5, 5.5);
	TH1F *muonSegmentsFid2LowPV  = new TH1F("muonSegmentsFid2LowPV", "Number Muon Segments fiducial ring 2 Low PV", 6, -0.5, 5.5);


	TH1F *segmentsFid1HighPV  = new TH1F("segmentsFid1HighPV", "Number of CSC Segments Fiducial ring 1 High PV", 6, -0.5, 5.5);
	TH1F *segmentsFid2HighPV  = new TH1F("segmentsFid2HighPV", "Number of CSC Segments fiducial ring 2 High PV", 6, -0.5, 5.5);
	TH1F *segmentsFid1LowPV  = new TH1F("segmentsFid1LowPV", "Number of CSC Segments Fiducial ring 1 Low PV", 6, -0.5, 5.5);
	TH1F *segmentsFid2LowPV  = new TH1F("segmentsFid2LowPV", "Number of CSC Segments fiducial ring 2 Low PV", 6, -0.5, 5.5);

	TH1F *segmentsFid1HighpT  = new TH1F("segmentsFid1HighpT", "Number of CSC Segments Fiducial ring 1 High pT", 6, -0.5, 5.5);
	TH1F *segmentsFid2HighpT  = new TH1F("segmentsFid2HighpT", "Number of CSC Segments fiducial ring 2 High pT", 6, -0.5, 5.5);




	// Numerology, station, ring, chamber
	// [s][r][c] station ring chamber
	// s 0 = -endcap station 1, 1 = -endcap station 2, 2 = -endcap station 3, 3 = -endcap station 4 
	// s 4 = +endcap station 1, 5 = +endcap station 2, 6 = +endcap station 3, 7 = +endcap station 4 
	// r 0 = ring 1(b), r 1 = ring 1(a), r 2 = ring 2, r 3 = ring 3
	// c 0 = chamber 01 to 17 = or 35 = chamger 16 or 32 

	// ME11 even odd plot in:
	// iiStation 1,2 and 5,6
	// iiStation 1, iiRing 0 = even ME11B, iiRing 3, odd ME11B
	// iiStation 2, iiRing 0 = even ME11A, iiRing 3, odd ME11A


	// Define Efficiency counters
	// Efficiencies based on counting with sideband subtraction
	// Fit code exists for cross check and systematic uncerainty

	// Global effiency couters

	Float_t totGlobal=0,passGlobalSeg=0,passGlobalLCT=0,totSBGlobal=0,passSBGlobalSeg=0,passSBGlobalLCT=0,effGlobalSeg = 0,effSigmaGlobalSeg = 0,effGlobalLCT = 0,effSigmaGlobalLCT = 0;

	Float_t totGlobalPt[numPtBins]={0},passGlobalSegPt[numPtBins]={0},passGlobalLCTPt[numPtBins]={0},totSBGlobalPt[numPtBins]={0},passSBGlobalSegPt[numPtBins]={0},passSBGlobalLCTPt[numPtBins]={0},effGlobalSegPt[numPtBins]={0},effSigmaGlobalSegPt[numPtBins]={0},effGlobalLCTPt[numPtBins]={0},effSigmaGlobalLCTPt[numPtBins]={0};


	// Ring Efficiency counters

	Float_t totStationRing[8][4]={0}, passStationRingSeg[8][4]={0},passStationRingLCT[8][4]={0}, totSBStationRing[8][4]={0}, passSBStationRingSeg[8][4]={0},passSBStationRingLCT[8][4]={0},effStationRingSeg[8][4]={0}, effSigmaStationRingSeg[8][4]={0},effStationRingLCT[8][4]={0}, effSigmaStationRingLCT[8][4]={0},effStationCRingSeg[4][4]={0}, effSigmaStationCRingSeg[4][4]={0},effStationCRingLCT[4][4]={0}, effSigmaStationCRingLCT[4][4]={0};


	// Chamber Efficiency counters
	Float_t totStationRingChamber[8][4][37]={0}, passStationRingChamberSeg[8][4][37]={0},  passStationRingChamberLCT[8][4][37]={0}, totSBStationRingChamber[8][4][37]={0}, passSBStationRingChamberSeg[8][4][37]={0},passSBStationRingChamberLCT[8][4][37]={0}, effStationRingChamberSeg[8][4][37]={0}, effSigmaStationRingChamberSeg[8][4][37]={0}, effStationRingChamberLCT[8][4][37]={0}, effSigmaStationRingChamberLCT[8][4][37]={0},effStationCRingChamberSeg[4][4][37]={0};


	// pT Efficiency counters
	Float_t totStationRingPt[8][4][numPtBins]={0}, passStationRingPtSeg[8][4][numPtBins]={0},passStationRingPtLCT[8][4][numPtBins]={0}, totSBStationRingPt[8][4][numPtBins]={0}, passSBStationRingPtSeg[8][4][numPtBins]={0},passSBStationRingPtLCT[8][4][numPtBins]={0}, effStationRingPtSeg[8][4][numPtBins]={0}, effSigmaStationRingPtSeg[8][4][numPtBins]={0}, effStationRingPtLCT[8][4][numPtBins]={0}, effSigmaStationRingPtLCT[8][4][numPtBins]={0},effStationCRingPtSeg[4][4][numPtBins]={0}, effSigmaStationCRingPtSeg[4][4][numPtBins]={0}, effStationCRingPtLCT[4][4][numPtBins]={0}, effSigmaStationCRingPtLCT[4][4][numPtBins]={0};
	// eta Efficiency counters
	Float_t totStationRingEta[8][4][numEtaBins]={0}, passStationRingEtaSeg[8][4][numEtaBins]={0}, passStationRingEtaLCT[8][4][numEtaBins]={0}, totSBStationRingEta[8][4][numEtaBins]={0}, passSBStationRingEtaSeg[8][4][numEtaBins]={0},passSBStationRingEtaLCT[8][4][numEtaBins]={0}, effStationRingEtaSeg[8][4][numEtaBins]={0}, effSigmaStationRingEtaSeg[8][4][numEtaBins]={0}, effStationRingEtaLCT[8][4][numEtaBins]={0}, effSigmaStationRingEtaLCT[8][4][numEtaBins]={0},effStationCRingEtaSeg[4][4][numEtaBins]={0}, effSigmaStationCRingEtaSeg[4][4][numEtaBins]={0}, effStationCRingEtaLCT[4][4][numEtaBins]={0}, effSigmaStationCRingEtaLCT[4][4][numEtaBins]={0};

	// Iso Efficiency counters
	Float_t totStationRingIso[8][4][numIsoBins]={0}, passStationRingIsoSeg[8][4][numIsoBins]={0}, passStationRingIsoLCT[8][4][numIsoBins]={0}, totSBStationRingIso[8][4][numIsoBins]={0}, passSBStationRingIsoSeg[8][4][numIsoBins]={0},passSBStationRingIsoLCT[8][4][numIsoBins]={0}, effStationRingIsoSeg[8][4][numIsoBins]={0}, effSigmaStationRingIsoSeg[8][4][numIsoBins]={0}, effStationRingIsoLCT[8][4][numIsoBins]={0}, effSigmaStationRingIsoLCT[8][4][numIsoBins]={0},effStationCRingIsoSeg[4][4][numIsoBins]={0}, effSigmaStationCRingIsoSeg[4][4][numIsoBins]={0}, effStationCRingIsoLCT[4][4][numIsoBins]={0}, effSigmaStationCRingIsoLCT[4][4][numIsoBins]={0};


	// PV Efficiency counters
	Float_t totStationRingPV[8][4][numPVBins]={0}, passStationRingPVSeg[8][4][numPVBins]={0}, passStationRingPVLCT[8][4][numPVBins]={0}, totSBStationRingPV[8][4][numPVBins]={0}, passSBStationRingPVSeg[8][4][numPVBins]={0},passSBStationRingPVLCT[8][4][numPVBins]={0}, effStationRingPVSeg[8][4][numPVBins]={0}, effSigmaStationRingPVSeg[8][4][numPVBins]={0}, effStationRingPVLCT[8][4][numPVBins]={0}, effSigmaStationRingPVLCT[8][4][numPVBins]={0},effStationCRingPVSeg[4][4][numPVBins]={0}, effSigmaStationCRingPVSeg[4][4][numPVBins]={0}, effStationCRingPVLCT[4][4][numPVBins]={0}, effSigmaStationCRingPVLCT[4][4][numPVBins]={0};

	// IL Efficiency counters
	Float_t totStationRingIL[8][4][numILBins]={0}, passStationRingILSeg[8][4][numILBins]={0}, passStationRingILLCT[8][4][numILBins]={0}, totSBStationRingIL[8][4][numILBins]={0}, passSBStationRingILSeg[8][4][numILBins]={0},passSBStationRingILLCT[8][4][numILBins]={0}, effStationRingILSeg[8][4][numILBins]={0}, effSigmaStationRingILSeg[8][4][numILBins]={0}, effStationRingILLCT[8][4][numILBins]={0}, effSigmaStationRingILLCT[8][4][numILBins]={0},effStationCRingILSeg[4][4][numILBins]={0}, effSigmaStationCRingILSeg[4][4][numILBins]={0}, effStationCRingILLCT[4][4][numILBins]={0}, effSigmaStationCRingILLCT[4][4][numILBins]={0};



	// Run Efficiency counters
	Float_t totStationRingRun[8][4][numRunBins]={0}, passStationRingRunSeg[8][4][numRunBins]={0}, passStationRingRunLCT[8][4][numRunBins]={0}, totSBStationRingRun[8][4][numRunBins]={0}, passSBStationRingRunSeg[8][4][numRunBins]={0},passSBStationRingRunLCT[8][4][numRunBins]={0}, effStationRingRunSeg[8][4][numRunBins]={0}, effSigmaStationRingRunSeg[8][4][numRunBins]={0}, effStationRingRunLCT[8][4][numRunBins]={0}, effSigmaStationRingRunLCT[8][4][numRunBins]={0};

	// Chamber and Run Efficiency counters
	Float_t totStationRingChamberRun[8][4][37][numRunBins]={0}, passStationRingChamberRunSeg[8][4][37][numRunBins]={0},  passStationRingChamberRunLCT[8][4][37][numRunBins]={0}, totSBStationRingChamberRun[8][4][37][numRunBins]={0}, passSBStationRingChamberRunSeg[8][4][37][numRunBins]={0},passSBStationRingChamberRunLCT[8][4][37][numRunBins]={0}, effStationRingChamberRunSeg[8][4][37][numRunBins]={0}, effSigmaStationRingChamberRunSeg[8][4][37][numRunBins]={0}, effStationRingChamberRunLCT[8][4][37][numRunBins]={0}, effSigmaStationRingChamberRunLCT[8][4][37][numRunBins]={0},effStationCRingChamberRunSeg[4][4][37][numRunBins]={0};


	// Chamber and Layer Efficiency counters
	Float_t totStationRingChamberLayer[8][4][37][numLayerBins]={0}, passStationRingChamberLayerSeg[8][4][37][numLayerBins]={0},  passStationRingChamberLayerLCT[8][4][37][numLayerBins]={0}, totSBStationRingChamberLayer[8][4][37][numLayerBins]={0}, passSBStationRingChamberLayerSeg[8][4][37][numLayerBins]={0},passSBStationRingChamberLayerLCT[8][4][37][numLayerBins]={0}, effStationRingChamberLayerSeg[8][4][37][numLayerBins]={0}, effSigmaStationRingChamberLayerSeg[8][4][37][numLayerBins]={0}, effStationRingChamberLayerLCT[8][4][37][numLayerBins]={0}, effSigmaStationRingChamberLayerLCT[8][4][37][numLayerBins]={0},effStationCRingChamberLayerSeg[4][4][37][numLayerBins]={0};


	// Chamber and DCFEB Efficiency counters
	Float_t totStationRingChamberDCFEB[8][4][37][numDCFEBBins]={0}, totStationRingChamberDCFEBLCT[8][4][37][numDCFEBBins]={0}, passStationRingChamberDCFEBSeg[8][4][37][numDCFEBBins]={0},  passStationRingChamberDCFEBLCT[8][4][37][numDCFEBBins]={0}, totSBStationRingChamberDCFEB[8][4][37][numDCFEBBins]={0}, passSBStationRingChamberDCFEBSeg[8][4][37][numDCFEBBins]={0},passSBStationRingChamberDCFEBLCT[8][4][37][numDCFEBBins]={0}, effStationRingChamberDCFEBSeg[8][4][37][numDCFEBBins]={0}, effSigmaStationRingChamberDCFEBSeg[8][4][37][numDCFEBBins]={0}, effStationRingChamberDCFEBLCT[8][4][37][numDCFEBBins]={0}, effSigmaStationRingChamberDCFEBLCT[8][4][37][numDCFEBBins]={0},effStationCRingChamberDCFEBSeg[4][4][37][numDCFEBBins]={0};



	// Local coordinate Y Efficiency counters
	Float_t totStationRingLCY[8][4][numLCYBins]={0},totStationRingLCYLCT[8][4][numLCYBins]={0},passStationRingLCYSeg[8][4][numLCYBins]={0}, passStationRingLCYLCT[8][4][numLCYBins]={0}, totSBStationRingLCY[8][4][numLCYBins]={0},  totSBStationRingLCYLCT[8][4][numLCYBins]={0}, passSBStationRingLCYSeg[8][4][numLCYBins]={0},passSBStationRingLCYLCT[8][4][numLCYBins]={0}, effStationRingLCYSeg[8][4][numLCYBins]={0}, effSigmaStationRingLCYSeg[8][4][numLCYBins]={0}, effStationRingLCYLCT[8][4][numLCYBins]={0}, effSigmaStationRingLCYLCT[8][4][numLCYBins]={0},effStationCRingLCYSeg[4][4][numLCYBins]={0}, effSigmaStationCRingLCYSeg[4][4][numLCYBins]={0}, effStationCRingLCYLCT[4][4][numLCYBins]={0}, effSigmaStationCRingLCYLCT[4][4][numLCYBins]={0};

	Float_t totStationRingChamberLCY[8][4][37][numLCYBins]={0},totSBStationRingChamberLCY[8][4][37][numLCYBins]={0},passStationRingChamberLCYSeg[8][4][37][numLCYBins]={0},passStationRingChamberLCYLCT[8][4][37][numLCYBins]={0},passSBStationRingChamberLCYSeg[8][4][37][numLCYBins]={0},passSBStationRingChamberLCYLCT[8][4][37][numLCYBins]={0},effStationRingChamberLCYSeg[8][4][37][numLCYBins]={0},effStationRingChamberLCYLCT[8][4][37][numLCYBins]={0},effSigmaStationRingChamberLCYSeg[8][4][37][numLCYBins]={0},effSigmaStationRingChamberLCYLCT[8][4][37][numLCYBins]={0};

	// Local coordinate Wire Efficiency counters
	Float_t totStationRingLCW[8][4][numLCWBins]={0},totStationRingLCWLCT[8][4][numLCWBins]={0},passStationRingLCWSeg[8][4][numLCWBins]={0}, passStationRingLCWLCT[8][4][numLCWBins]={0}, totSBStationRingLCW[8][4][numLCWBins]={0},  totSBStationRingLCWLCT[8][4][numLCWBins]={0}, passSBStationRingLCWSeg[8][4][numLCWBins]={0},passSBStationRingLCWLCT[8][4][numLCWBins]={0}, effStationRingLCWSeg[8][4][numLCWBins]={0}, effSigmaStationRingLCWSeg[8][4][numLCWBins]={0}, effStationRingLCWLCT[8][4][numLCWBins]={0}, effSigmaStationRingLCWLCT[8][4][numLCWBins]={0},effStationCRingLCWSeg[4][4][numLCWBins]={0}, effSigmaStationCRingLCWSeg[4][4][numLCWBins]={0}, effStationCRingLCWLCT[4][4][numLCWBins]={0}, effSigmaStationCRingLCWLCT[4][4][numLCWBins]={0};

	Float_t totStationRingChamberLCW[8][4][37][numLCWBins]={0},totSBStationRingChamberLCW[8][4][37][numLCWBins]={0},passStationRingChamberLCWSeg[8][4][37][numLCWBins]={0},passStationRingChamberLCWLCT[8][4][37][numLCWBins]={0},passSBStationRingChamberLCWSeg[8][4][37][numLCWBins]={0},passSBStationRingChamberLCWLCT[8][4][37][numLCWBins]={0},effStationRingChamberLCWSeg[8][4][37][numLCWBins]={0},effStationRingChamberLCWLCT[8][4][37][numLCWBins]={0},effSigmaStationRingChamberLCWSeg[8][4][37][numLCWBins]={0},effSigmaStationRingChamberLCWLCT[8][4][37][numLCWBins]={0};

	// Local coordinate Strip Efficiency counters
	Float_t totStationRingLCS[8][4][numLCSBins]={0}, totStationRingLCSLCT[8][4][numLCSBins]={0},passStationRingLCSSeg[8][4][numLCSBins]={0}, passStationRingLCSLCT[8][4][numLCSBins]={0}, totSBStationRingLCS[8][4][numLCSBins]={0}, totSBStationRingLCSLCT[8][4][numLCSBins]={0}, passSBStationRingLCSSeg[8][4][numLCSBins]={0},passSBStationRingLCSLCT[8][4][numLCSBins]={0}, effStationRingLCSSeg[8][4][numLCSBins]={0}, effSigmaStationRingLCSSeg[8][4][numLCSBins]={0}, effStationRingLCSLCT[8][4][numLCSBins]={0}, effSigmaStationRingLCSLCT[8][4][numLCSBins]={0},effStationCRingLCSSeg[4][4][numLCSBins]={0}, effSigmaStationCRingLCSSeg[4][4][numLCSBins]={0}, effStationCRingLCSLCT[4][4][numLCSBins]={0}, effSigmaStationCRingLCSLCT[4][4][numLCSBins]={0};

	Float_t totStationRingChamberLCS[8][4][37][numLCSBins]={0},totSBStationRingChamberLCS[8][4][37][numLCSBins]={0},passStationRingChamberLCSSeg[8][4][37][numLCSBins]={0},passStationRingChamberLCSLCT[8][4][37][numLCSBins]={0},passSBStationRingChamberLCSSeg[8][4][37][numLCSBins]={0},passSBStationRingChamberLCSLCT[8][4][37][numLCSBins]={0},effStationRingChamberLCSSeg[8][4][37][numLCSBins]={0},effStationRingChamberLCSLCT[8][4][37][numLCSBins]={0},effSigmaStationRingChamberLCSSeg[8][4][37][numLCSBins]={0},effSigmaStationRingChamberLCSLCT[8][4][37][numLCSBins]={0};



	// Special purpose and uick Efficiency Histograms
	// Most depriciated for the moment

	TH1F *globalCSCSegEffPt  = new TH1F("globalCSCSegEffPt", "ME11b CSC Seg Eff vs Pt", numPtBins, &(*ptBins));
	globalCSCSegEffPt->GetYaxis()->SetTitle("CSC Segment Efficiency");
	globalCSCSegEffPt->GetXaxis()->SetTitle("Muon Pt (GeV)");


	// Define selection
	// boolians: tracks_isTrackerMuTrk, !CSCCBad, trackVeto_isClosestToLCT
	// Tag and dimuon requirements
	Float_t tagE = 8;
	Float_t maxDRHLTAllSingleMu = 0.2;
	Float_t minDRTkMu1 = 0.2;

	// Change mass windows to be as narrow as possible and sidebands as near the edge
	// 75 to 120 available

	/* Float_t zMassMin = 83.5; */
	/* Float_t zMassMax = 98.5; */

	/* Float_t zMassLowSideBandMin = 76.0; */
	/* Float_t zMassLowSideBandMax = 83.5; */

	/* Float_t zMassHighSideBandMin = 98.5; */
	/* Float_t zMassHighSideBandMax = 106.0; */

	// Narrower set
	Float_t zMassMin = 88.0;
	Float_t zMassMax = 94.0;

	Float_t zMassLowSideBandMin = 76.0;
	Float_t zMassLowSideBandMax = 79.0;

	Float_t zMassHighSideBandMin = 103.0;
	Float_t zMassHighSideBandMax = 106.0;



	Bool_t inZMass;
	Bool_t inZMassLowSideBand;
	Bool_t inZMassHighSideBand;
	Bool_t inZMassSideBand;

	// Fiducial requirements
	Float_t cscProjDistEdge = -5.0;
	Float_t sigmaCSCProjDistEdge = -3.0;
	//  Float_t cscProjDistEdge = 0.0;
	//  Float_t sigmaCSCProjDistEdge = 0.0;
	Float_t cscDyProjHVGap = 1.0;
	Float_t sigmaCSCDyProjHVGap = 3.0;
	// Segement and LCT cuts
	// boolians: CSCDxyTTSeg, CSCDxyTTLCT
	Float_t cscDxyTTSeg = 10.0;
	Float_t sigmaCSCDxyTTSeg = 10.0;
	Float_t cscDxyTTLCT = 10.0;
	Float_t sigmaCSCDxyTTLCT = 10.0;

	Bool_t goodTag;
	Bool_t fiducialAll;
	Bool_t fiducial1;
	Bool_t fiducial11;
	Bool_t fiducial2;
	Bool_t fiducial3;
	Bool_t fiducial4;
	Bool_t foundSeg1;
	Bool_t foundSeg2;
	Bool_t foundSeg3;
	Bool_t foundSeg4;
	Bool_t foundLCT1;
	Bool_t foundLCT2;
	Bool_t foundLCT3;
	Bool_t foundLCT4;

	Bool_t foundHit1[6] = {false,false,false,false,false,false};
	Bool_t foundHit2[6] = {false,false,false,false,false,false};
	Bool_t foundHit3[6] = {false,false,false,false,false,false};
	Bool_t foundHit4[6] = {false,false,false,false,false,false};


	// Failure counters
	Int_t nFailFiducial = 0;
	Int_t nFailFoundSeg = 0;
	Int_t nFailGoodSeg = 0;
	Int_t nFailDxy = 0;

	Int_t prevRunNumber = 0;

	// Bad Chambers, track 5 independent run ranges, for the moment

	Bool_t badChamber[5][2][4][4][36] = {false};
	Int_t badChamberRun[5][2][4][4][36][2] = {0};
	Float_t badChamberLCS[5][2][4][4][36][2] = {0.0};

	// endcap 0- 1+, station 0-3 = 1-4, ring 0-3 0 is me11a, chamber 0-35 = 1-36
	// Removing chambers bellow 80%
	// move start from period D, 320394to period B, 318800


	// ????? exclude 357734?  seen in multiple rings
	if (badChambersTrack) {

		//?????? need to test if any of these are back  

		// New Dead Chambers Run 3
		badChamber[0][1][1-1][2][10-1] = true;   badChamberRun[0][1][1-1][2][10-1][0] = firstRun; badChamberRun[0][1][1-1][2][10-1][1] = lastRun; // ME+12/10

		badChamber[0][1][2-1][2][31-1] = true;   badChamberRun[0][1][2-1][2][31-1][0] = firstRun; badChamberRun[0][1][2-1][2][31-1][1] = lastRun; // ME+22/31 Came back right at the end, has this been fixed

		badChamber[0][0][4-1][2][4-1] = true;   badChamberRun[0][0][4-1][2][4-1][0] = firstRun; badChamberRun[0][0][4-1][2][4-1][1] = lastRun; // ME-42/04  Came back right at the end, has this been fixed?


		// New bad (D)CFEBs Run 3 and run ranges

		// ME+42
		badChamber[0][1][4-1][2][1-1] = true;   badChamberRun[0][1][4-1][2][1-1][0] = firstRun; badChamberRun[0][1][4-1][2][1-1][1] = lastRun; badChamberLCS[0][1][4-1][2][1-1][0] = 62.0; badChamberLCS[0][1][4-1][2][1-1][1] = 82.0;// ME+42/1 all runs, good around 359000

		badChamber[0][1][4-1][2][2-1] = true;   badChamberRun[0][1][4-1][2][2-1][0] = firstRun; badChamberRun[0][1][4-1][2][2-1][1] = lastRun; badChamberLCS[0][1][4-1][2][2-1][0] = -2.0; badChamberLCS[0][1][4-1][2][2-1][1] = 18.0;// ME+42/2 50% eff DCFEB 1, all runs, good around 359000

		if (badRunRangesTrack) badChamber[0][1][4-1][2][3-1] = true;   badChamberRun[0][1][4-1][2][3-1][0] = 356466; badChamberRun[0][1][4-1][2][3-1][1] = 357734;// ME+42/3 two bad run regions, 356466-356490, 357328-357734

		badChamber[0][1][4-1][2][6-1] = true;   badChamberRun[0][1][4-1][2][6-1][0] = firstRun; badChamberRun[0][1][4-1][2][6-1][1] = lastRun; badChamberLCS[0][1][4-1][2][6-1][0] = 30.0; badChamberLCS[0][1][4-1][2][6-1][1] = 50.0;// ME+42/6 DCFEB 3 all runs

		badChamber[0][1][4-1][2][22-1] = true;   badChamberRun[0][1][4-1][2][22-1][0] = firstRun; badChamberRun[0][1][4-1][2][22-1][1] = 362300; badChamberLCS[0][1][4-1][2][22-1][0] = -2.0; badChamberLCS[0][1][4-1][2][22-1][1] = 18.0;// ME+42/22 DCFEB 1 partially bad 70%, okay after 362300


		//ME+41
		badChamber[0][1][4-1][1][4-1] = true;   badChamberRun[0][1][4-1][1][4-1][0] = firstRun; badChamberRun[0][1][4-1][1][4-1][1] = lastRun; badChamberLCS[0][1][4-1][1][4-1][0] = 46.0; badChamberLCS[0][1][4-1][1][4-1][1] = 66.0;// ME+42/4 DCFEB 4 all runs 

		badChamber[0][1][4-1][1][9-1] = true;   badChamberRun[0][1][4-1][1][9-1][0] = 359700; badChamberRun[0][1][4-1][1][9-1][1] = lastRun; badChamberLCS[0][1][4-1][1][9-1][0] = 14.0; badChamberLCS[0][1][4-1][1][9-1][1] = 34.0;// ME+42/4 DCFEB 2 ~359700-lastRun partially bad 50% 

		badChamber[0][1][4-1][1][12-1] = true;   badChamberRun[0][1][4-1][1][12-1][0] = 362088; badChamberRun[0][1][4-1][1][12-1][1] = 362108; // ME+42/12 bad run range 362088-362108
		// ME+41-15 also a few bad run ranges but less so

		// ME+32
		badChamber[0][1][3-1][2][19-1] = true;   badChamberRun[0][1][3-1][2][19-1][0] = firstRun; badChamberRun[0][1][3-1][2][19-1][1] = lastRun; badChamberLCS[0][1][3-1][2][19-1][0] = 62.0; badChamberLCS[0][1][3-1][2][19-1][1] = 82.0;// ME+32/19 DCFEB 5 all runs 

		badChamber[0][1][3-1][2][24-1] = true;   badChamberRun[0][1][3-1][2][24-1][0] = 358500; badChamberRun[0][1][3-1][2][24-1][1] = lastRun; badChamberLCS[0][1][3-1][2][24-1][0] = 30.0; badChamberLCS[0][1][3-1][2][24-1][1] = 50.0;// ME+32/24 DCFEB 3 okay before 358500?????

		badChamber[0][1][3-1][2][29-1] = true;   badChamberRun[0][1][3-1][2][29-1][0] = firstRun; badChamberRun[0][1][3-1][2][29-1][1] = lastRun; badChamberLCS[0][1][3-1][2][29-1][0] = 46.0; badChamberLCS[0][1][3-1][2][29-1][1] = 66.0;// ME+32/29 DCFEB 4 all runs good around 359000
		// ME+32-31 maybe a bad DCFEB 1 right at the start then fixed
		badChamber[0][1][3-1][2][33-1] = true;   badChamberRun[0][1][3-1][2][33-1][0] = 356476; badChamberRun[0][1][3-1][2][33-1][1] = 356490; // ME+32-33 bad run range 356476-356490 same as chamber 34
		badChamber[0][1][3-1][2][33-1] = true;   badChamberRun[0][1][3-1][2][34-1][0] = 356476; badChamberRun[0][1][3-1][2][34-1][1] = 356490; // ME+32-34 bad run range 356476-356490 same as chamber 33


		// ME+31
		badChamber[0][1][3-1][1][5-1] = true;   badChamberRun[0][1][3-1][1][5-1][0] = 359570; badChamberRun[0][1][3-1][1][5-1][1] = 360226; // ME+31/5 // HV problem

		//ME+31/10 // 88% efficieincy no obvious reason other than OOS
		badChamber[0][1][3-1][1][10-1] = true;   badChamberRun[0][1][3-1][1][10-1][0] = 360942; badChamberRun[0][1][3-1][1][10-1][1] = 360952; // ME+31/10 // 0% eff in 360942-360952
		//ME+31/12 // 89% efficieincy no obvious reason other than OOS
		badChamber[0][1][3-1][1][13-1] = true;   badChamberRun[0][1][3-1][1][13-1][0] = 362148; badChamberRun[0][1][3-1][1][10-1][1] = 362168; // ME+31/13 0% in 362148-362168

		badChamber[0][1][3-1][1][15-1] = true;   badChamberRun[0][1][3-1][1][15-1][0] = firstRun; badChamberRun[0][1][3-1][1][15-1][1] = lastRun; badChamberLCS[0][1][3-1][1][15-1][0] = 62.0; badChamberLCS[0][1][3-1][1][15-1][1] = 82.0;// ME+31/15 30% all runs

		badChamber[0][1][3-1][1][17-1] = true;   badChamberRun[0][1][3-1][1][17-1][0] = 356310; badChamberRun[0][1][3-1][1][17-1][1] = 357734; // ME+31/17 three regions of bad efficiency.  Capture 2 of them 356310-356490, 357070-357734, 361050-361110

		// ME+22
		badChamber[0][1][2-1][2][5-1] = true;   badChamberRun[0][1][2-1][2][5-1][0] = firstRun; badChamberRun[0][1][2-1][2][5-1][1] = lastRun; badChamberLCS[0][1][2-1][2][5-1][0] = -2.0; badChamberLCS[0][1][2-1][2][5-1][1] = 18.0;// ME+22/5 DCFEB 1 all runs good around 359000

		badChamber[0][1][2-1][2][15-1] = true;   badChamberRun[0][1][2-1][2][15-1][0] = firstRun; badChamberRun[0][1][2-1][2][15-1][1] = lastRun; badChamberLCS[0][1][2-1][2][15-1][0] = 62.0; badChamberLCS[0][1][2-1][2][15-1][1] = 82.0;// ME+22/15 DCFEB 5 all runs good around 359000, there is a second DCFEB with smaller problems that I am ignoring. ????? check run range

		badChamber[0][1][2-1][2][19-1] = true;   badChamberRun[0][1][2-1][2][19-1][0] = firstRun; badChamberRun[0][1][2-1][2][19-1][1] = lastRun; badChamberLCS[0][1][2-1][2][19-1][0] = 62.0; badChamberLCS[0][1][2-1][2][19-1][1] = 82.0;// ME+22/19 DCFEB 5 all runs


		badChamber[0][1][2-1][2][27-1] = true;   badChamberRun[0][1][2-1][2][27-1][0] = 356476; badChamberRun[0][1][2-1][2][27-1][1] = 356490; // ME+22/27 in 356476-356490 also in chamber 28
		badChamber[0][1][2-1][2][28-1] = true;   badChamberRun[0][1][2-1][2][28-1][0] = 356476; badChamberRun[0][1][2-1][2][28-1][1] = 356490; // ME+22/27 in 356476-356490 also in chamber 27


		// ME+21

		if (badRunRangesTrack) badChamber[0][1][2-1][1][2-1] = true;   badChamberRun[0][1][2-1][1][2-1][0] = 355912; badChamberRun[0][1][2-1][1][2-1][1] = 355942;// ME+21/2 for 355912 to 355942

		if (badRunRangesTrack) badChamber[0][1][2-1][1][3-1] = true;   badChamberRun[0][1][2-1][1][3-1][0] = 356946; badChamberRun[0][1][2-1][1][3-1][1] = 357272;// ME+21/3 for 356946 to 357272

		badChamber[0][1][2-1][1][5-1] = true;   badChamberRun[0][1][2-1][1][5-1][0] = 357734; badChamberRun[0][1][2-1][1][5-1][1] = 360226; // ME+21/5 // HV problem E+F 357734-360226

		badChamber[0][1][2-1][1][6-1] = true;   badChamberRun[0][1][2-1][1][6-1][0] = firstRun; badChamberRun[0][1][2-1][1][6-1][1] = lastRun; badChamberLCS[0][1][2-1][1][6-1][0] = 30.0; badChamberLCS[0][1][2-1][1][6-1][1] = 50.0;// ME+21/6 all runs 

		if (badRunRangesTrack) badChamber[0][1][2-1][1][11-1] = true;   badChamberRun[0][1][2-1][1][11-1][0] = 355118; badChamberRun[0][1][2-1][1][11-1][1] = 355560;// ME+21/11 four run ranges 355118-355560, 357438-357448, 357538-357734, 361298-361334 capture first 0 area,  Also 0-100% 50% ave eff LCT around 361300

		// ME+13
		// ME+13/10 LCT 89% no dependence
		badChamber[0][1][1-1][3][11-1] = true;   badChamberRun[0][1][1-1][3][11-1][0] = firstRun; badChamberRun[0][1][1-1][3][11-1][1] = lastRun; badChamberLCS[0][1][1-1][3][11-1][0] = 30.0; badChamberLCS[0][1][1-1][3][11-1][1] = 50.0;// ME+31/11 all runs good around 359000, gen low LCT eff 89%

		badChamber[0][1][1-1][3][12-1] = true;   badChamberRun[0][1][1-1][3][12-1][0] = 357734; badChamberRun[0][1][1-1][3][12-1][1] = 361958; // ME+13/12 for 357734-361958

		badChamber[0][1][1-1][3][20-1] = true;   badChamberRun[0][1][1-1][3][20-1][0] = firstRun; badChamberRun[0][1][1-1][3][20-1][1] = lastRun; badChamberLCS[0][1][1-1][3][20-1][0] = -2.0; badChamberLCS[0][1][1-1][3][20-1][1] = 18.0;// ME+31/20 DCFEB 1 70%
		// ME+13/30 LCT only 90%


		// ME+12
		badChamber[0][1][1-1][2][13-1] = true;   badChamberRun[0][1][1-1][2][13-1][0] = firstRun; badChamberRun[0][1][1-1][2][13-1][1] = lastRun; badChamberLCS[0][1][1-1][2][13-1][0] = 62.0; badChamberLCS[0][1][1-1][2][13-1][1] = 82.0;// ME+12/13 DCFEB 5 all runs good around 359000

		badChamber[0][1][1-1][2][15-1] = true;   badChamberRun[0][1][1-1][2][15-1][0] = 357078; badChamberRun[0][1][1-1][2][15-1][1] = lastRun; badChamberLCS[0][1][1-1][2][15-1][0] = -2.0; badChamberLCS[0][1][1-1][2][15-1][1] = 18.0;// ME+12/15 DCFEB 1 all runs good around 359000 and before except for 357078 to 357734

		//ME+12-20 a few zero runs

		badChamber[0][1][1-1][2][21-1] = true;   badChamberRun[0][1][1-1][2][21-1][0] = firstRun; badChamberRun[0][1][1-1][2][21-1][1] = lastRun; badChamberLCS[0][1][1-1][2][21-1][0] = 14.0; badChamberLCS[0][1][1-1][2][21-1][1] = 66.0;// ME+12/21 DCFEB 2,4 all runs, breifly brought back around 359200
		//ME+12=24 a few low eff runs

		badChamber[0][1][1-1][2][31-1] = true;   badChamberRun[0][1][1-1][2][31-1][0] = firstRun; badChamberRun[0][1][1-1][2][31-1][1] = lastRun; badChamberLCS[0][1][1-1][2][31-1][0] = 62.0; badChamberLCS[0][1][1-1][2][31-1][1] = 82.0;// ME+12/31 all runs

		badChamber[0][1][1-1][2][34-1] = true;   badChamberRun[0][1][1-1][2][34-1][0] = 359570; badChamberRun[0][1][1-1][2][34-1][1] = 360142;// ME+12/34 for 359570 to 360142


		// ME+11A/B
		// ME+11A/B

		// ME+11A.B-1 gen low LCT 83%
		// ME+11A/B-13 357480 357482 very low eff
		// ME+11A/B-21 a few low stats run ranges
		// ME+11A/B-28 a few low stats run ranges

		if (badRunRangesTrack) badChamber[0][1][1-1][1][27-1] = true;   badChamberRun[0][1][1-1][1][27-1][0] = 357696; badChamberRun[0][1][1-1][1][27-1][1] = 357720;// ME+11A/27
		if (badRunRangesTrack) badChamber[0][1][1-1][0][27-1] = true;   badChamberRun[0][1][1-1][0][27-1][0] = 357696; badChamberRun[0][1][1-1][0][27-1][1] = 357720;// ME+11B/27


		// ME-11A
		badChamber[0][0][1-1][0][19-1] = true;  badChamberRun[0][0][1-1][0][19-1][0] = firstRun; badChamberRun[0][0][1-1][0][19-1][1] = lastRun; badChamberLCS[0][0][1-1][0][19-1][0] = 30.0; badChamberLCS[0][0][1-1][0][19-1][1] = 50.0;// ME-11A/19 all runs

		badChamber[0][0][1-1][0][20-1] = true;  badChamberRun[0][0][1-1][0][20-1][0] = firstRun; badChamberRun[0][0][1-1][0][20-1][1] = lastRun; badChamberLCS[0][0][1-1][0][20-1][0] = -2.0; badChamberLCS[0][0][1-1][0][20-1][1] = 18.0;// ME-11A/20 all runs good around 359000



		// ME-11A/B
		// also less inefficinecy earlier  
		if (badRunRangesTrack) badChamber[0][0][1-1][1][4-1] = true;   badChamberRun[0][0][1-1][1][4-1][0] = 359602; badChamberRun[0][0][1-1][1][4-1][1] = 359814;// ME-11A/4 359602 to 359814
		if (badRunRangesTrack) badChamber[0][0][1-1][0][4-1] = true;   badChamberRun[0][0][1-1][0][4-1][0] = 359602; badChamberRun[0][0][1-1][0][4-1][1] = 359814;// ME-11B/4 359602 to 359814
		if (badRunRangesTrack) badChamber[0][0][1-1][0][33-1] = true;   badChamberRun[0][0][1-1][0][33-1][0] = 356722; badChamberRun[0][0][1-1][0][33-1][1] = 357112;// ME-11B/33

		//if (badRunRangesTrack) badChamber[0][0][1-1][1][4-1] = true;   badChamberRun[0][0][1-1][1][4-1][0] = 361000.0; badChamberRun[0][0][1-1][1][4-1][1] = 361400.0;// ME-11A/4 transient E and then F 90% don't remove
		//if (badRunRangesTrack) badChamber[0][0][1-1][0][4-1] = true;   badChamberRun[0][0][1-1][0][4-1][0] = 361000.0; badChamberRun[0][0][1-1][0][4-1][1] = 361400.0;// ME-11B/4 transient E and then F 90% dont remove


		// three ranges 355134-355560, 356434-356490, 357406-357734
		if (badRunRangesTrack) badChamber[0][0][1-1][1][12-1] = true;   badChamberRun[0][0][1-1][1][12-1][0] = 355134; badChamberRun[0][0][1-1][1][12-1][1] = 357734;// ME-11A/12 transient B
		if (badRunRangesTrack) badChamber[0][0][1-1][0][12-1] = true;   badChamberRun[0][0][1-1][0][12-1][0] = 355134; badChamberRun[0][0][1-1][0][12-1][1] = 357734;// ME-11B/12 transient B

		if (badRunRangesTrack) badChamber[0][0][1-1][1][25-1] = true;   badChamberRun[0][0][1-1][1][25-1][0] = 357330; badChamberRun[0][0][1-1][1][25-1][1] = 357334;// ME-11A/25 transient B
		if (badRunRangesTrack) badChamber[0][0][1-1][0][25-1] = true;   badChamberRun[0][0][1-1][0][25-1][0] = 357330; badChamberRun[0][0][1-1][0][25-1][1] = 357334;// ME-11B/25 transient B

		if (badRunRangesTrack) badChamber[0][0][1-1][1][29-1] = true;   badChamberRun[0][0][1-1][1][29-1][0] = 360762; badChamberRun[0][0][1-1][1][29-1][1] = 361362;// ME-11A/29 transient F ?????? HV layer 3
		if (badRunRangesTrack) badChamber[0][0][1-1][0][29-1] = true;   badChamberRun[0][0][1-1][0][29-1][0] = 360762; badChamberRun[0][0][1-1][0][29-1][1] = 361362;// ME-11B/29 transient F ?????? HV layer 3


		// ME-12
		if (badRunRangesTrack) badChamber[0][0][1-1][2][7-1] = true;   badChamberRun[0][0][1-1][2][7-1][0] = 356322.0; badChamberRun[0][0][1-1][2][7-1][1] = 357734.0;// ME-12/7
		if (badRunRangesTrack) badChamber[0][0][1-1][2][22-1] = true;   badChamberRun[0][0][1-1][2][22-1][0] = 355680.0; badChamberRun[0][0][1-1][2][22-1][1] = 357614;// ME-12/22 two ranges 355680-355770, 357328-357614

		badChamber[0][0][1-1][2][27-1] = true;  badChamberRun[0][0][1-1][2][27-1][0] = firstRun; badChamberRun[0][0][1-1][2][27-1][1] = lastRun; badChamberLCS[0][0][1-1][2][27-1][0] = -2.0; badChamberLCS[0][0][1-1][2][27-1][1] = 18.0;// ME-12/27 DCFEB 1 all runs good around 359000
		badChamber[0][0][1-1][2][33-1] = true;  badChamberRun[0][0][1-1][2][33-1][0] = firstRun; badChamberRun[0][0][1-1][2][33-1][1] = lastRun; badChamberLCS[0][0][1-1][2][33-1][0] = -2.0; badChamberLCS[0][0][1-1][2][33-1][1] = 18.0;// ME-12/27 DCFEB 1 all runs good around 359000


		// ME-13
		if (badRunRangesTrack&&badRunRangesTrack2) badChamber[0][0][1-1][3][25-1] = true;   badChamberRun[0][0][1-1][3][25-1][0] = 355680; badChamberRun[0][0][1-1][3][25-1][1] = 357614;// ME-13/25 transient B

		//ME-13 30 low in 3 our of 4 (D)CFEBs for LCTs 83%

		// ME-21 	 

		badChamber[0][0][2-1][1][15-1] = true;   badChamberRun[0][0][2-1][1][15-1][0] = firstRun; badChamberRun[0][0][2-1][1][15-1][1] = lastRun; badChamberLCS[0][0][2-1][1][15-1][0] = -2.0; badChamberLCS[0][0][2-1][1][15-1][1] = 18.0;// ME-21/15 also 0% 355988-356078

		//worst ME-21 chamber Seg and LCT also a few zero eff runs
		//badChamber[0][0][2-1][1][18-1] = true;   badChamberRun[0][0][2-1][1][18-1][0] = firstRun; badChamberRun[0][0][2-1][1][18-1][1] = lastRun;// ME-21/18


		// ME-22
		// ME-22/1 86% LCT only no dependence
		badChamber[0][0][2-1][2][3-1] = true;   badChamberRun[0][0][2-1][2][3-1][0] = firstRun; badChamberRun[0][0][2-1][2][3-1][1] = lastRun; badChamberLCS[0][0][2-1][2][3-1][0] = 14.0; badChamberLCS[0][0][2-1][2][3-1][1] = 34.0;// ME-22/3 DCFEB 2 all runs, gen low LCT 86%
		badChamber[0][0][2-1][2][27-1] = true;   badChamberRun[0][0][2-1][2][27-1][0] = firstRun; badChamberRun[0][0][2-1][2][27-1][1] = lastRun; badChamberLCS[0][0][2-1][2][27-1][0] = 62.0; badChamberLCS[0][0][2-1][2][27-1][1] = 82.0;// ME-22/27 DCFEB 5 all runs good around 359000
		// ME-22/15 DCFEB 2 80% eff

		//ME-31
		badChamber[0][0][3-1][1][3-1] = true;   badChamberRun[0][0][3-1][1][3-1][0] = firstRun; badChamberRun[0][0][3-1][1][3-1][1] = 359000; badChamberLCS[0][0][3-1][1][3-1][0] = -2.0; badChamberLCS[0][0][3-1][1][3-1][1] = 18.0;// ME-31/3 B-D also 0% 356048-356078
		if (badRunRangesTrack) badChamber[0][0][3-1][1][5-1] = true;   badChamberRun[0][0][3-1][1][5-1][0] = 355862; badChamberRun[0][0][3-1][1][5-1][1] = 356824;// ME-31/5 transient B
		//ME-31/9 one run 362440 0.296893 and other single runs
		if (badRunRangesTrack) badChamber[0][0][3-1][1][14-1] = true;   badChamberRun[0][0][3-1][1][14-1][0] = 357478; badChamberRun[0][0][3-1][1][14-1][1] = 357734;// ME-31/14 transient B
		if (badRunRangesTrack) badChamber[0][0][3-1][1][18-1] = true;   badChamberRun[0][0][3-1][1][18-1][0] = 355680; badChamberRun[0][0][3-1][1][18-1][1] = 357734;// ME-31/18 B-D

		// ME-32
		badChamber[0][0][3-1][2][19-1] = true;   badChamberRun[0][0][3-1][2][19-1][0] = firstRun; badChamberRun[0][0][3-1][2][19-1][1] = lastRun; badChamberLCS[0][0][3-1][2][19-1][0] = 46.0; badChamberLCS[0][0][3-1][2][19-1][1] = 66.0;// ME-32/19 DCFEB 3 all runs, also poor efficiency runs 361188-362760 ??????
		badChamber[0][0][3-1][2][24-1] = true;   badChamberRun[0][0][3-1][2][24-1][0] = 360486; badChamberRun[0][0][3-1][2][24-1][1] = 361110; // ME-32/24 and some other single runs
		// ME-31/30 LCT 1-4 87%


		// ME-41
		if (badRunRangesTrack&&badRunRangesTrack) badChamber[0][0][4-1][1][3-1] = true;   badChamberRun[0][0][4-1][1][3-1][0] = 357330; badChamberRun[0][0][4-1][1][3-1][1] = 357734;// ME-41/3 B-D to area of bad runs 355408-356048, 357330-357734
		if (badRunRangesTrack) badChamber[0][0][4-1][1][12-1] = true;   badChamberRun[0][0][4-1][1][12-1][0] = 355862; badChamberRun[0][0][4-1][1][12-1][1] = 357734;// ME-41/12 transient B several area of zero eff 355862-355872, 356446-357734
		badChamber[0][0][4-1][1][17-1] = true;   badChamberRun[0][0][4-1][1][17-1][0] = firstRun; badChamberRun[0][0][4-1][1][17-1][1] = lastRun; badChamberLCS[0][0][4-1][1][17-1][0] = 46.0; badChamberLCS[0][0][4-1][1][17-1][1] = 66.0;// ME-41/17 DCFEB 4 all reun


		// ME-41/15 80% efficiency issues transient in period F
		if (badRunRangesTrack) badChamber[0][0][4-1][1][15-1] = true;   badChamberRun[0][0][4-1][1][15-1][0] = 360116; badChamberRun[0][0][4-1][1][15-1][1] = 361476;// ME-41/15 transient F


		// There are some other transient DCFEB problems I might want to track down


		// ME-42
		// ME-42/19 53% LCT only
		badChamber[0][0][4-1][2][27-1] = true;   badChamberRun[0][0][4-1][2][27-1][0] = firstRun; badChamberRun[0][0][4-1][2][27-1][1] = lastRun ; badChamberLCS[0][0][4-1][2][27-1][0] = 30.0; badChamberLCS[0][0][4-1][2][27-1][1] = 50.0;// ME-42/27 DCFEB 3  all runs good around 359200
		badChamber[0][0][4-1][2][30-1] = true;   badChamberRun[0][0][4-1][2][30-1][0] = 361366; badChamberRun[0][0][4-1][2][30-1][1] = lastRun ; // ME-42/30  30% efficiency problem at end of F

	}


	// Dead chambers

	if (oldBadChambersTrack) {
		badChamber[0][0][2-1][1][3-1] = true;  badChamberRun[0][0][2-1][1][3-1][0] = 316000; badChamberRun[0][0][2-1][1][3-1][1] = 325273; //ME-21/3 no data

		badChamber[0][0][4-1][2][21-1] = true;  badChamberRun[0][0][4-1][2][21-1][0] = 316000; badChamberRun[0][0][4-1][2][21-1][1] = 325273; // ME-42/21 no data



		badChamber[0][0][4-1][2][14-1] = true;  badChamberRun[0][0][4-1][2][14-1][0] = 316000; badChamberRun[0][0][4-1][2][14-1][1] = 325273; badChamberLCS[0][0][4-1][2][14-1][0] = 14.5; badChamberLCS[0][0][4-1][2][14-1][1] = 34.5;// ME-42/14 DCFEB 2


		//badChamber[0][0][1-1][0][9-1] = true;  badChamberRun[0][0][1-1][0][9-1][0] = 322599; badChamberRun[0][0][1-1][0][9-1][1] = 322633; // ME-11A/9 322599-322633 !!!!! me-1/1/09	2018-08-19	DCFEB1	opt link with ODMB time correct
		// ME-11A/10 bad in first run section
		badChamber[0][0][1-1][0][11-1] = true;  badChamberRun[0][0][1-1][0][11-1][0] = 316000; badChamberRun[0][0][1-1][0][11-1][1] = 325172; badChamberLCS[0][0][1-1][0][11-1][0] = 31.0; badChamberLCS[0][0][1-1][0][11-1][1] = 50.0;// ME-11A/11
		//badChamber[0][0][1-1][0][12-1] = true;   badChamberRun[0][0][1-1][0][12-1][0] = 322355; badChamberRun[0][0][1-1][0][12-1][1] = 322492;// ME-11B/12 322355-322492 !!!!! General low efficiencies more toward end, Nothing
		badChamber[0][0][1-1][0][25-1] = true;  badChamberRun[0][0][1-1][0][25-1][0] = 321067; badChamberRun[0][0][1-1][0][25-1][1] = 325172; badChamberLCS[0][0][1-1][0][25-1][0] = 0.0; badChamberLCS[0][0][1-1][0][25-1][1] = 16.5;// ME-11A/11 okay before 321067
		// ME-11A/26 bad at 322057 !!!!! Some low efficiencies me-1/1/26	2018-07-21	DCFEB3	opt link with ODMB, me-1/1/26	2018-12-01	DCFEB3	OTMB time note correct
		// badChamber[0][0][1-1][0][29-1] = true;  badChamberRun[0][0][1-1][0][29-1][0] = 322605; badChamberRun[0][0][1-1][0][29-1][1] = 322605;// ME-11A/29 322605 !!!!! Some low efficiencies Nothing

		badChamber[0][0][1-1][1][5-1] = true;   badChamberRun[0][0][1-1][1][5-1][0] = 316000; badChamberRun[0][0][1-1][1][5-1][1] = 325172; badChamberLCS[0][0][1-1][1][5-1][0] = 0.0; badChamberLCS[0][0][1-1][1][5-1][1] = 16.5;// ME-11B/5
		// ME-11B/10 bad in first run section
		// badChamber[0][0][1-1][1][12-1] = true;   badChamberRun[0][0][1-1][1][12-1][0] = 322355; badChamberRun[0][0][1-1][1][12-1][1] = 322492;// ME-11B/12 322355-322492 !!!!! Some low efficiecies in middle Nothing
		// ME-11B/26 70% one run at 321232 !!!!! me-1/1/26	2018-07-21	DCFEB3	opt link with ODMB time correct
		// badChamber[0][0][1-1][1][29-1] = true;   badChamberRun[0][0][1-1][1][29-1][0] = 322605; badChamberRun[0][0][1-1][1][29-1][1] = 322605;// ME-11B/29 322605 !!!!! Some low efficiences in middle Nothing

		badChamber[0][0][1-1][2][6-1] = true;   badChamberRun[0][0][1-1][2][6-1][0] = 323423; badChamberRun[0][0][1-1][2][6-1][1] = 323526; badChamberLCS[0][0][1-1][2][6-1][0] = 46.5; badChamberLCS[0][0][1-1][2][6-1][1] = 62.5;// ME-12/6 323423-323526
		badChamber[0][0][1-1][2][21-1] = true;   badChamberRun[0][0][1-1][2][21-1][0] = 316000; badChamberRun[0][0][1-1][2][21-1][1] = 325172; badChamberLCS[0][0][1-1][2][21-1][0] = 32.5; badChamberLCS[0][0][1-1][2][21-1][1] = 40.5;// ME-12/21 316000-325172
		badChamber[0][0][1-1][2][33-1] = true;   badChamberRun[0][0][1-1][2][33-1][0] = 316000; badChamberRun[0][0][1-1][2][33-1][1] = 325172; badChamberLCS[0][0][1-1][2][33-1][0] = 0.0; badChamberLCS[0][0][1-1][2][33-1][1] = 16.5;// ME-12/33
		badChamber[0][0][1-1][2][36-1] = true;   badChamberRun[0][0][1-1][2][36-1][0] = 321700; badChamberRun[0][0][1-1][2][36-1][1] = 325172; badChamberLCS[0][0][1-1][2][36-1][0] = 65.5; badChamberLCS[0][0][1-1][2][36-1][1] = 40.5;// ME-12/36 321700-325172


		badChamber[0][0][1-1][3][8-1] = true;   badChamberRun[0][0][1-1][3][8-1][0] = 316000; badChamberRun[0][0][1-1][3][8-1][1] = 321314; badChamberLCS[0][0][1-1][3][8-1][0] = 48.5; badChamberLCS[0][0][1-1][3][8-1][1] = 62.5;// ME-13/8 323423-323526

		badChamber[0][0][1-1][3][25-1] = true;   badChamberRun[0][0][1-1][3][25-1][0] = 316000; badChamberRun[0][0][1-1][3][25-1][1] = 321070; badChamberLCS[0][0][1-1][3][25-1][0] = 30.; badChamberLCS[0][0][1-1][3][25-1][1] = 50.5;// ME-13/25 316000-


		//ME13/35 bad in first run section


		badChamber[0][1][1-1][0][7-1] = true;  badChamberRun[0][1][1-1][0][7-1][0] = 318800; badChamberRun[0][1][1-1][0][7-1][1] = 325172; badChamberLCS[0][1][1-1][0][7-1][0] = 0.0; badChamberLCS[0][1][1-1][0][7-1][1] = 16.5;// ME+11A/7
		badChamber[0][1][1-1][0][20-1] = true; badChamberRun[0][1][1-1][0][20-1][0] = 318800; badChamberRun[0][1][1-1][0][20-1][1] = 325172; badChamberLCS[0][1][1-1][0][20-1][0] = 32.5; badChamberLCS[0][1][1-1][0][20-1][1] = 50.0; // ME+11A/20
		// badChamber[0][1][1-1][0][21-1] = true; badChamberRun[0][1][1-1][0][21-1][0] = 323755; badChamberRun[0][1][1-1][0][21-1][1] = 324022; // ME+11A/21 323755-324022 40% !!!!! Some low efficiencies in middle me+1/1/21	2018-08-17	DCFEB3	opt link with OTMB time not correct
		badChamber[0][1][1-1][0][29-1] = true; badChamberRun[0][1][1-1][0][29-1][0] = 318800; badChamberRun[0][1][1-1][0][29-1][1] = 325172; badChamberLCS[0][1][1-1][0][29-1][0] = 14.5; badChamberLCS[0][1][1-1][0][29-1][1] = 32.5;// ME+11A/29


		//ME+11B/18 run 319077 !!!!! A vew low efficiences in middle  me+1/1/18	2018-10-19	DCFEB7	ODMB time not correct
		// badChamber[0][1][1-1][1][21-1] = true;  badChamberRun[0][1][1-1][1][21-1][0] = 323755; badChamberRun[0][1][1-1][1][21-1][1] = 324022; // ME+11B/21 323755-324022 40% !!!!! Some low efficiencies in middle me+1/1/21	2018-08-17	DCFEB3	opt link with time approximately correct


		//ME+12/5 bad before 318800  
		// badChamber[0][1][1-1][2][8-1] = true;   badChamberRun[0][1][1-1][2][8-1][0] = 321067; badChamberRun[0][1][1-1][2][8-1][1] = 321305;// ME+12/8 ** only 321067-321305 and 322013,322014 !!!!! A few low efficincies in the middle Nothing
		badChamber[0][1][1-1][2][13-1] = true;  badChamberRun[0][1][1-1][2][13-1][0] = 316000; badChamberRun[0][1][1-1][2][13-1][1] = 325172; badChamberLCS[0][1][1-1][2][13-1][0] = 62.5; badChamberLCS[0][1][1-1][2][13-1][1] = 80.0;// ME+12/13
		badChamber[0][1][1-1][2][20-1] = true;  badChamberRun[0][1][1-1][2][20-1][0] = 316000; badChamberRun[0][1][1-1][2][20-1][1] = 325172; badChamberLCS[0][1][1-1][2][20-1][0] = 30.5; badChamberLCS[0][1][1-1][2][20-1][1] = 50.5;// ME+12/20
		badChamber[0][1][1-1][2][21-1] = true;  badChamberRun[0][1][1-1][2][21-1][0] = 316000; badChamberRun[0][1][1-1][2][21-1][1] = 325172; badChamberLCS[0][1][1-1][3][21-1][0] = 14.5; badChamberLCS[0][1][1-1][2][21-1][1] = 66.5;// ME+12/21
		// badChamber[0][1][1-1][2][28-1] = true;  badChamberRun[0][1][1-1][2][28-1][0] = 320955; badChamberRun[0][1][1-1][2][28-1][1] = 320809; // ME+12/28 320804-320809 and 320955 !!!!! A few low efficiency in middle Nothing
		badChamber[0][1][1-1][2][31-1] = true;  badChamberRun[0][1][1-1][2][31-1][0] = 316000; badChamberRun[0][1][1-1][2][31-1][1] = 325172; badChamberLCS[0][1][1-1][2][31-1][0] = 62.5; badChamberLCS[0][1][1-1][2][31-1][1] = 80.0;// ME+12/31

		badChamber[0][1][1-1][3][11-1] = true;  badChamberRun[0][1][1-1][3][11-1][0] = 316000; badChamberRun[0][1][1-1][3][11-1][1] = 325172; badChamberLCS[0][1][1-1][3][11-1][0] = 30.5; badChamberLCS[0][1][1-1][3][11-1][1] = 50.5;// ME+13/11


		//  ME-21/3 no data

		badChamber[0][0][2-1][2][1-1] = true;   badChamberRun[0][0][2-1][2][1-1][0] = 318800; badChamberRun[0][0][2-1][2][1-1][1] = 325172; badChamberLCS[0][0][2-1][2][1-1][0] = 44.5; badChamberLCS[0][0][2-1][2][1-1][1] = 66.6;// ME-22/1
		badChamber[0][0][2-1][2][3-1] = true;   badChamberRun[0][0][2-1][2][3-1][0] = 316000; badChamberRun[0][0][2-1][2][3-1][1] = 325172; badChamberLCS[0][0][2-1][2][3-1][0] = 15.5; badChamberLCS[0][0][2-1][2][3-1][1] = 32.5; // ME-22/3


		badChamber[0][1][2-1][1][3-1] = true;   badChamberRun[0][1][2-1][1][3-1][0] = 316000; badChamberRun[0][1][2-1][1][3-1][1] = 325172; badChamberLCS[0][1][2-1][1][3-1][0] = 14.5; badChamberLCS[0][1][2-1][1][3-1][1] = 64.5;// ME+21/3

		badChamber[0][1][2-1][2][5-1] = true;   badChamberRun[0][1][2-1][2][5-1][0] = 316000; badChamberRun[0][1][2-1][2][5-1][1] = 325172; badChamberLCS[0][1][2-1][2][5-1][0] = 0.; badChamberLCS[0][1][2-1][2][5-1][1] = 18.5;// ME+22/5
		badChamber[0][1][2-1][2][15-1] = true;   badChamberRun[0][1][2-1][2][15-1][0] = 316000; badChamberRun[0][1][2-1][2][15-1][1] = 325172; badChamberLCS[0][1][2-1][2][15-1][0] = 62.5; badChamberLCS[0][1][2-1][2][15-1][1] = 80.0;// ME+22/15
		badChamber[0][1][2-1][2][19-1] = true;   badChamberRun[0][1][2-1][2][19-1][0] = 316000; badChamberRun[0][1][2-1][2][19-1][1] = 325172; badChamberLCS[0][1][2-1][2][19-1][0] = 62.5; badChamberLCS[0][1][2-1][2][19-1][1] = 80.0;// ME+22/19


		badChamber[0][0][3-1][1][9-1] = true;   badChamberRun[0][0][3-1][1][9-1][0] = 316000; badChamberRun[0][0][3-1][1][9-1][1] = 325172; badChamberLCS[0][0][3-1][1][9-1][0] = 0.0; badChamberLCS[0][0][3-1][1][9-1][1] = 66.5;// ME-31/9 ** two ranges
		badChamber[0][0][3-1][1][13-1] = true;  badChamberRun[0][0][3-1][1][13-1][0] = 316000; badChamberRun[0][0][3-1][1][13-1][1] = 325172; badChamberLCS[0][0][3-1][1][13-1][0] = 30.5; badChamberLCS[0][0][3-1][1][13-1][1] = 50.5;// ME-31/13


		badChamber[0][1][3-1][1][7-1] = true;   badChamberRun[0][1][3-1][1][7-1][0] = 316000; badChamberRun[0][1][3-1][1][7-1][1] = 325172; badChamberLCS[0][1][3-1][1][7-1][0] = 30.5; badChamberLCS[0][1][3-1][1][7-1][1] = 48.5;// ME+31/7
		badChamber[0][1][3-1][1][12-1] = true;   badChamberRun[0][1][3-1][1][12-1][0] = 316000; badChamberRun[0][1][3-1][1][12-1][1] = 325172; badChamberLCS[0][1][3-1][1][12-1][0] = 62.5; badChamberLCS[0][1][3-1][1][12-1][1] = 77.5;// ME+31/12




		badChamber[0][1][3-1][2][19-1] = true;   badChamberRun[0][1][3-1][2][19-1][0] = 316000; badChamberRun[0][1][3-1][2][19-1][1] = 325172; badChamberLCS[0][1][3-1][2][19-1][0] = 62.5; badChamberLCS[0][1][3-1][2][19-1][1] = 80.0;// ME+32/19 all bad 78%
		badChamber[0][1][3-1][2][29-1] = true;   badChamberRun[0][1][3-1][2][29-1][0] = 316000; badChamberRun[0][1][3-1][2][29-1][1] = 325172; badChamberLCS[0][1][3-1][2][29-1][0] = 46.5; badChamberLCS[0][1][3-1][2][29-1][1] = 64.5;// ME+32/29


		badChamber[0][0][4-1][1][1-1] = true;   badChamberRun[0][0][4-1][1][1-1][0] = 316000; badChamberRun[0][0][4-1][1][1-1][1] = 325172; badChamberLCS[0][0][4-1][1][1-1][0] = 30.5; badChamberLCS[0][0][4-1][1][1-1][1] = 48.5;// ME-41/1
		badChamber[0][0][4-1][1][11-1] = true;   badChamberRun[0][0][4-1][1][11-1][0] = 316000; badChamberRun[0][0][4-1][1][11-1][1] = 325172; badChamberLCS[0][0][4-1][1][11-1][0] = 62.5; badChamberLCS[0][0][4-1][1][11-1][1] = 80.0;// ME-41/11
		badChamber[0][0][4-1][1][15-1] = true;   badChamberRun[0][0][4-1][1][15-1][0] = 316000; badChamberRun[0][0][4-1][1][15-1][1] = 325172; badChamberLCS[0][0][4-1][1][15-1][0] = 62.5; badChamberLCS[0][1][4-1][1][15-1][1] = 80.0;// ME-41/15



		//badChamber[0][0][4-1][2][2-1] = true;   badChamberRun[0][0][4-1][2][2-1][0] = 323492; badChamberRun[0][0][4-1][2][2-1][1] = 323493;// ME-42/2 323492-323493 !!!!! A few runs in the middle Nothing
		badChamber[0][0][4-1][2][8-1] = true;   badChamberRun[0][0][4-1][2][8-1][0] = 316000; badChamberRun[0][0][4-1][2][8-1][1] = 325172; badChamberLCS[0][0][4-1][2][8-1][0] = 14.5; badChamberLCS[0][0][4-1][2][8-1][1] = 34.5;// ME-42/8
		badChamber[0][0][4-1][2][27-1] = true;   badChamberRun[0][0][4-1][2][27-1][0] = 316000; badChamberRun[0][0][4-1][2][27-1][1] = 324077; badChamberLCS[0][0][4-1][2][27-1][0] = 30.5; badChamberLCS[0][0][4-1][2][27-1][1] = 50.5; // ME-42/27 323693-324077
		badChamber[0][0][4-1][2][34-1] = true;   badChamberRun[0][0][4-1][2][34-1][0] = 316000; badChamberRun[0][0][4-1][2][34-1][1] = 325172; badChamberLCS[0][0][4-1][2][34-1][0] = 62.5; badChamberLCS[0][0][4-1][2][34-1][1] = 80.0;// ME-42/34
		// ME-42/21 do data

		badChamber[0][1][4-1][1][15-1] = true;   badChamberRun[0][1][4-1][1][15-1][0] = 316000; badChamberRun[0][1][4-1][1][15-1][1] = 325172; badChamberLCS[0][1][4-1][1][15-1][0] = 62.5; badChamberLCS[0][1][4-1][1][15-1][1] = 80.0;// ME+41/15

		badChamber[0][1][4-1][2][32-1] = true;   badChamberRun[0][1][4-1][2][32-1][0] = 316000; badChamberRun[0][1][4-1][2][32-1][1] = 325172; badChamberLCS[0][1][4-1][2][32-1][0] = 0.0; badChamberLCS[0][1][4-1][2][32-1][1] = 18.5;// ME+42/32


		// CFEB SCA memory saturation effect

		badChamber[0][0][2-1][1][5-1] = true;   badChamberRun[0][0][2-1][1][5-1][0] = 316000; badChamberRun[0][0][2-1][1][5-1][1] = 325172; //ME-21/5
		//badChamber[0][0][2-1][1][8-1] = true;   badChamberRun[0][0][2-1][1][8-1][0] = 323423; badChamberRun[0][0][2-1][1][8-1][1] = 325172;// ME-21/9 323423-325172 Low efficiencies more at beginning and end, CFEB issue
		// Expand to full range
		badChamber[0][0][2-1][1][8-1] = true;   badChamberRun[0][0][2-1][1][8-1][0] = 316000; badChamberRun[0][0][2-1][1][8-1][1] = 325172;//

		//badChamber[0][0][2-1][1][9-1] = true;   badChamberRun[0][0][2-1][1][9-1][0] = 318800; badChamberRun[0][0][2-1][1][9-1][1] = 325172; badChamberLCS[0][0][2-1][1][9-1][0] = 45.5; badChamberLCS[0][0][2-1][1][9-1][1] = 64.5;// ME-21/9 also  Low efficiencies more at end, CFEB issue
		// expand to full range
		badChamber[0][0][2-1][1][9-1] = true;   badChamberRun[0][0][2-1][1][9-1][0] = 316000; badChamberRun[0][0][2-1][1][9-1][1] = 325172;

		badChamber[0][0][2-1][1][10-1] = true;   badChamberRun[0][0][2-1][1][10-1][0] = 316000; badChamberRun[0][0][2-1][1][10-1][1] = 325172;// ME-21/10 323432-325172 !!!!! Low efficiencies more at end, CFEB issue
		badChamber[0][0][2-1][1][17-1] = true;  badChamberRun[0][0][2-1][1][17-1][0] = 316000; badChamberRun[0][0][2-1][1][17-1][1] = 325172;// ME-21/17 !!!!! Low efficiencies more at end, CFEB issue

		// ME-22/16 CFEB Issue
		badChamber[0][0][2-1][2][16-1] = true;   badChamberRun[0][0][2-1][2][16-1][0] = 316000; badChamberRun[0][0][2-1][2][16-1][1] = 325172;
		// ME-22/20 323423-325172 40-90% efficiency !!!!! Low efficiencies more at end, CFEB issue
		badChamber[0][0][2-1][2][20-1] = true;   badChamberRun[0][0][2-1][2][20-1][0] = 316000; badChamberRun[0][0][2-1][2][20-1][1] = 325172;

		badChamber[0][0][3-1][1][18-1] = true;  badChamberRun[0][0][3-1][1][18-1][0] = 316000; badChamberRun[0][0][3-1][1][18-1][1] = 325172; //  ME-31/18 323423-325172  !!!!! !!!!! Low efficiencies more at end, CFEB issue ????

		//badChamber[0][0][4-1][2][1-1] = true;   badChamberRun[0][0][4-1][2][1-1][0] = 316000; badChamberRun[0][0][4-1][2][1-1][1] = 325172; badChamberLCS[0][0][4-1][2][1-1][0] = 32.5; badChamberLCS[0][0][4-1][2][1-1][1] = 48.5;// ME-42/1 remaining CFEB issue?
		// expand to full range
		badChamber[0][0][4-1][2][1-1] = true;   badChamberRun[0][0][4-1][2][1-1][0] = 316000; badChamberRun[0][0][4-1][2][1-1][1] = 325172;

		// Overlapping bad individual CFEB and CFEB SCA memory saturation issue

		// badChamber[0][0][4-1][2][1-1] = true;   badChamberRun[0][0][4-1][2][1-1][0] = 316000; badChamberRun[0][0][4-1][2][1-1][1] = 325172; badChamberLCS[0][0][4-1][2][1-1][0] = 32.5; badChamberLCS[0][0][4-1][2][1-1][1] = 48.5;// ME-42/1 remaining CFEB issue?

		// badChamber[0][0][2-1][1][9-1] = true;   badChamberRun[0][0][2-1][1][9-1][0] = 316000; badChamberRun[0][0][2-1][1][9-1][1] = 325172; badChamberLCS[0][0][2-1][1][9-1][0] = 45.5; badChamberLCS[0][0][2-1][1][9-1][1] = 64.5;// ME-21/9 also  Low efficiencies more at end, CFEB issue


	}
	//Exclude and ME-21 ring
	/* badChamber[0][0][2-1][1][1-1] = true;  badChamberRun[0][0][2-1][1][1-1][0] = 316000; badChamberRun[0][0][2-1][1][1-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][2-1] = true;  badChamberRun[0][0][2-1][1][2-1][0] = 316000; badChamberRun[0][0][2-1][1][2-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][4-1] = true;  badChamberRun[0][0][2-1][1][4-1][0] = 316000; badChamberRun[0][0][2-1][1][4-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][6-1] = true;  badChamberRun[0][0][2-1][1][6-1][0] = 316000; badChamberRun[0][0][2-1][1][6-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][7-1] = true;  badChamberRun[0][0][2-1][1][7-1][0] = 316000; badChamberRun[0][0][2-1][1][7-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][11-1] = true;  badChamberRun[0][0][2-1][1][11-1][0] = 316000; badChamberRun[0][0][2-1][1][11-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][12-1] = true;  badChamberRun[0][0][2-1][1][12-1][0] = 316000; badChamberRun[0][0][2-1][1][12-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][13-1] = true;  badChamberRun[0][0][2-1][1][13-1][0] = 316000; badChamberRun[0][0][2-1][1][13-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][14-1] = true;  badChamberRun[0][0][2-1][1][14-1][0] = 316000; badChamberRun[0][0][2-1][1][14-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][15-1] = true;  badChamberRun[0][0][2-1][1][15-1][0] = 316000; badChamberRun[0][0][2-1][1][15-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][16-1] = true;  badChamberRun[0][0][2-1][1][16-1][0] = 316000; badChamberRun[0][0][2-1][1][16-1][1] = lastRun; */
	/* badChamber[0][0][2-1][1][18-1] = true;  badChamberRun[0][0][2-1][1][18-1][0] = 316000; badChamberRun[0][0][2-1][1][18-1][1] = lastRun; */


	/* badChamber[0][1][2-1][1][2-1] = true;  badChamberRun[0][1][2-1][1][2-1][0] = 316000; badChamberRun[0][1][2-1][1][2-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][3-1] = true;  badChamberRun[0][1][2-1][1][3-1][0] = 316000; badChamberRun[0][1][2-1][1][3-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][4-1] = true;  badChamberRun[0][1][2-1][1][4-1][0] = 316000; badChamberRun[0][1][2-1][1][4-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][5-1] = true;  badChamberRun[0][1][2-1][1][5-1][0] = 316000; badChamberRun[0][1][2-1][1][5-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][6-1] = true;  badChamberRun[0][1][2-1][1][6-1][0] = 316000; badChamberRun[0][1][2-1][1][6-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][7-1] = true;  badChamberRun[0][1][2-1][1][7-1][0] = 316000; badChamberRun[0][1][2-1][1][7-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][8-1] = true;  badChamberRun[0][1][2-1][1][8-1][0] = 316000; badChamberRun[0][1][2-1][1][8-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][9-1] = true;  badChamberRun[0][1][2-1][1][9-1][0] = 316000; badChamberRun[0][1][2-1][1][9-1][1] = lastRun; */
	/*  badChamber[0][1][2-1][1][10-1] = true;  badChamberRun[0][1][2-1][1][10-1][0] = 316000; badChamberRun[0][1][2-1][1][10-1][1] = lastRun; */

	/* badChamber[0][1][2-1][1][1-1] = true;  badChamberRun[0][1][2-1][1][1-1][0] = 316000; badChamberRun[0][1][2-1][1][1-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][11-1] = true;  badChamberRun[0][1][2-1][1][11-1][0] = 316000; badChamberRun[0][1][2-1][1][11-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][12-1] = true;  badChamberRun[0][1][2-1][1][12-1][0] = 316000; badChamberRun[0][1][2-1][1][12-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][13-1] = true;  badChamberRun[0][1][2-1][1][13-1][0] = 316000; badChamberRun[0][1][2-1][1][13-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][14-1] = true;  badChamberRun[0][1][2-1][1][14-1][0] = 316000; badChamberRun[0][1][2-1][1][14-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][15-1] = true;  badChamberRun[0][1][2-1][1][15-1][0] = 316000; badChamberRun[0][1][2-1][1][15-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][16-1] = true;  badChamberRun[0][1][2-1][1][16-1][0] = 316000; badChamberRun[0][1][2-1][1][16-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][17-1] = true;  badChamberRun[0][1][2-1][1][17-1][0] = 316000; badChamberRun[0][1][2-1][1][17-1][1] = lastRun; */
	/*   badChamber[0][1][2-1][1][18-1] = true;  badChamberRun[0][1][2-1][1][18-1][0] = 316000; badChamberRun[0][1][2-1][1][18-1][1] = lastRun; */




	std::cout << "Getting number of entries: " << std::endl;


	if (fChain == 0) return;

	//Long64_t nentries = fChain->GetEntries();
	Long64_t nentries = 50000000;
	Int_t nCands = 0;
	Int_t nZs = 0;
	std::cout << "Number of entries: " << nentries << std::endl;


	Int_t totalFiducial = 0;
	Int_t totalFail = 0;
	Int_t totalPass = 0;

	Int_t runFiducial = 0;
	Int_t runFail = 0;
	Int_t runPass = 0;


	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) {
			std::cout << "Finishing loop over " << jentry << " of " << nentries << " - Number good Candidates: " << nCands << " - Number of Zs: " << nZs << std::endl;
			break;
		}


		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if ((jentry % 100000) ==0) std::cout << jentry << " of " << nentries << " - Number good Candidates: " << nCands << " - Number of Zs: " << nZs << std::endl; 


		// if (Cut(ientry) < 0) continue;
		// Probe and dimuon requirements
		//if (LowStats&&invMass>zMassMin&&invMass<zMassMax) invMass = 91.0;

		// CSC off
		bool badRun = (run_number==355991||run_number==355993||run_number==355994||run_number==355996||run_number==355997||run_number==356002||run_number==356003||run_number==356046||run_number==356164||run_number==356165||run_number==356170||run_number==356174||run_number==357734);
		// CSC partially off
		badRun = (badRun||run_number==355991||run_number==356001);

		// badRun=(badRun||(run_number<358500)||(run_number>359690)); //low lumi area
		// badRun=(badRun||(run_number<359690)||(run_number>360000)); // adjacent to low lumi area

		inZMass = (invMass>zMassMin)&&(invMass<zMassMax);
		inZMassLowSideBand = (invMass>zMassLowSideBandMin)&&(invMass<zMassLowSideBandMax);
		inZMassHighSideBand = (invMass>zMassHighSideBandMin)&&(invMass<zMassHighSideBandMax);
		inZMassSideBand = inZMassLowSideBand || inZMassHighSideBand;

		goodTag = ((tracks_pt>10.0)&&(MuTagPt>25.0)&&(tracks_e > tagE)&&(minDRHLTAllSingleMu < maxDRHLTAllSingleMu) &&
				(dRTkMu1 > minDRTkMu1)&&(dRTkMu1<10.0)&&tracks_IsoR03Ratio<0.1&&tracks_IsoR05Ratio<0.1&&iSameVtx&&(!badRun)&&
				(inZMass||inZMassLowSideBand||inZMassHighSideBand)&&run_number>0);

		//&&run_number>355980&& (!(run_number>356612&&run_number<356728

		bool sameRun = (run_number == prevRunNumber);
		if (!sameRun) {
			if (runFiducial > 0) std::cout << "New Run, fid, pass, fail: " <<  prevRunNumber << "," << runFiducial << ", " << runPass << ", " << runFail << std::endl;
			prevRunNumber = run_number;
			runFiducial = 0;
			runFail = 0;
			runPass = 0;
		}



		if (goodTag) nCands++;

		// Reset ring for ME11 ab cases that are mismatched due to eta problem
		if (CSCRg1==4 && CSCTTyLc1 > -999.0 && CSCTTyLc1 > -31.25) { CSCRg1=1;} //std::cout << "Resetting ring" <<std::endl;
		if (CSCRg1==1 && CSCTTyLc1 > -999.0 && CSCTTyLc1 < -31.25) { CSCRg1=4;} //std::cout << "Resetting ring" <<std::endl;
		//std::cout << "Resetting ring" <<std::endl;      

		Int_t ring1 = CSCRg1;
		if (ring1==4) ring1 = 0;
		Int_t ring2 = CSCRg2;
		Int_t ring3 = CSCRg3;
		Int_t ring4 = CSCRg4;

		// Fiducial requirements

		fiducial1 = CSCProjDistEdge1<cscProjDistEdge &&  CSCProjDistEdge1> -100 && 
			CSCProjDistEdge1/CSCProjDistErrEdge1 < sigmaCSCProjDistEdge &&
			CSCDyProjHVGap1>cscDyProjHVGap && 
			CSCDyProjHVGap1/CSCDyErrProjHVGap1>sigmaCSCDyProjHVGap &&
			!(badChamber[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1]&&
					run_number>=badChamberRun[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][0]&&
					run_number<=badChamberRun[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][1]&&
					(CSCTTsLc1>badChamberLCS[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][0]&&
					 (CSCTTsLc1<badChamberLCS[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][1]||badChamberLCS[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][1]<0.00001))); 
		//new requirements, temp restrict eta range 2.04345,2.0568,2.07015,2.0835,2.09685,2.1102,2.12355,2.1369,2.15
		//fabs(CSCTTetaGc1) > 2.04345 && fabs(CSCTTetaGc1) < 2.15 &&
		fiducial11 =   CSCProjDistEdge1<-1.0 &&  CSCProjDistEdge1> -100 && 
			CSCProjDistEdge1/CSCProjDistErrEdge1 < -5.0 &&
			CSCProjDistErrEdge1 < 1.0 &&
			CSCDyProjHVGap1>cscDyProjHVGap && 
			CSCDyProjHVGap1/CSCDyErrProjHVGap1>sigmaCSCDyProjHVGap &&
			fabs(CSCTTyLc1+31.25)>2.5 &&
			!(badChamber[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1]&&
					run_number>=badChamberRun[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][0]&&
					run_number<=badChamberRun[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][1]&&
					(CSCTTsLc1>badChamberLCS[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][0]&&
					 (CSCTTsLc1<badChamberLCS[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][1]||badChamberLCS[0][CSCEndCapPlus][1-1][ring1][CSCCh1-1][1]<0.00001))); 


		fiducial2 = CSCProjDistEdge2<cscProjDistEdge &&  CSCProjDistEdge2> -100 && 
			CSCProjDistEdge2/CSCProjDistErrEdge2 < sigmaCSCProjDistEdge &&
			CSCDyProjHVGap2>cscDyProjHVGap && 
			CSCDyProjHVGap2/CSCDyErrProjHVGap2>sigmaCSCDyProjHVGap &&
			!(badChamber[0][CSCEndCapPlus][2-1][ring2][CSCCh2-1]&&
					run_number>=badChamberRun[0][CSCEndCapPlus][2-1][ring2][CSCCh2-1][0]&&
					run_number<=badChamberRun[0][CSCEndCapPlus][2-1][ring2][CSCCh2-1][1]&&
					(CSCTTsLc2>badChamberLCS[0][CSCEndCapPlus][2-1][ring2][CSCCh2-1][0]&&
					 (CSCTTsLc2<badChamberLCS[0][CSCEndCapPlus][2-1][ring2][CSCCh2-1][1]||badChamberLCS[0][CSCEndCapPlus][2-1][ring2][CSCCh2-1][1]<0.00001))); 
		fiducial3 = CSCProjDistEdge3<cscProjDistEdge &&  CSCProjDistEdge3> -100 && 
			CSCProjDistEdge2/CSCProjDistErrEdge3 < sigmaCSCProjDistEdge &&
			CSCDyProjHVGap3>cscDyProjHVGap && 
			CSCDyProjHVGap3/CSCDyErrProjHVGap3>sigmaCSCDyProjHVGap &&
			!(badChamber[0][CSCEndCapPlus][3-1][ring3][CSCCh3-1]&&
					run_number>=badChamberRun[0][CSCEndCapPlus][3-1][ring3][CSCCh3-1][0]&&
					run_number<=badChamberRun[0][CSCEndCapPlus][3-1][ring3][CSCCh3-1][1]&&
					(CSCTTsLc3>badChamberLCS[0][CSCEndCapPlus][3-1][ring3][CSCCh3-1][0]&&
					 (CSCTTsLc3<badChamberLCS[0][CSCEndCapPlus][3-1][ring3][CSCCh3-1][1]||badChamberLCS[0][CSCEndCapPlus][3-1][ring3][CSCCh3-1][1]<0.00001))); 
		fiducial4 = CSCProjDistEdge4<cscProjDistEdge &&  CSCProjDistEdge4> -100 && 
			CSCProjDistEdge4/CSCProjDistErrEdge4 < sigmaCSCProjDistEdge &&
			CSCDyProjHVGap4>cscDyProjHVGap && 
			CSCDyProjHVGap4/CSCDyErrProjHVGap4>sigmaCSCDyProjHVGap &&
			!(badChamber[0][CSCEndCapPlus][4-1][ring4][CSCCh4-1]&&
					run_number>=badChamberRun[0][CSCEndCapPlus][4-1][ring4][CSCCh4-1][0]&&
					run_number<=badChamberRun[0][CSCEndCapPlus][4-1][ring4][CSCCh4-1][1]&&
					(CSCTTsLc4>badChamberLCS[0][CSCEndCapPlus][4-1][ring4][CSCCh4-1][0]&&
					 (CSCTTsLc4<badChamberLCS[0][CSCEndCapPlus][4-1][ring4][CSCCh4-1][1]||badChamberLCS[0][CSCEndCapPlus][4-1][ring4][CSCCh4-1][1]<0.00001))); 

		// fiducial1 = true;
		// fiducial11 = true;
		// fiducial2 = true;
		// fiducial3 = true;
		// fiducial4 = true;


		if (goodTag&&(fiducial1||fiducial11||fiducial2||fiducial3||fiducial4)&&inZMass) nZs++;
		if (goodTag&&(fiducial1||fiducial11||fiducial2||fiducial3||fiducial4)&&(inZMassLowSideBand||inZMassHighSideBand)) nZs--;


		// Found segments
		foundSeg1 = ((CSCDxyTTSeg1<cscDxyTTSeg || 
					CSCDxyTTSeg1/CSCDxyErrTTSeg1<sigmaCSCDxyTTSeg) &&
				CSCDxyTTSeg1>0.);
		foundSeg2 = ((CSCDxyTTSeg2<cscDxyTTSeg || 
					CSCDxyTTSeg2/CSCDxyErrTTSeg2<sigmaCSCDxyTTSeg) &&
				CSCDxyTTSeg2>0.);
		foundSeg3 = ((CSCDxyTTSeg3<cscDxyTTSeg || 
					CSCDxyTTSeg3/CSCDxyErrTTSeg3<sigmaCSCDxyTTSeg) &&
				CSCDxyTTSeg3>0.);
		foundSeg4 = ((CSCDxyTTSeg4<cscDxyTTSeg || 
					CSCDxyTTSeg4/CSCDxyErrTTSeg4<sigmaCSCDxyTTSeg) &&
				CSCDxyTTSeg4>0.);

		Int_t numberSegFound = 0;
		if (foundSeg1) numberSegFound++;
		if (foundSeg2) numberSegFound++;
		if (foundSeg3) numberSegFound++;
		if (foundSeg4) numberSegFound++;


		fiducialAll = (fiducial1||fiducial11)&&fiducial2&&fiducial3&&fiducial4;
		// Removal of fiducial for segement plots
		fiducialAll = true;
		Bool_t inRing1 = (ring2==1)&&(ring3==1)&&(ring4==1);
		inRing1 = ring2==1;
		Bool_t inRing2 = (ring2==2)&&(ring3==2)&&(ring4==2);
		inRing2 = ring2==2;

		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll) muonSegmentsFidAll->Fill(tracks_numberOfMatches);
		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&inRing1) muonSegmentsFid1->Fill(tracks_numberOfMatches);
		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&inRing1&&foundSeg2) muonSegmentsWithME21->Fill(tracks_numberOfMatches);
		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&inRing1&&(!foundSeg2)) muonSegmentsNoME21->Fill(tracks_numberOfMatches);

		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll) segmentsFidAll->Fill(numberSegFound);
		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&inRing1) segmentsFid1->Fill(numberSegFound);
		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&inRing1&&foundSeg2) segmentsWithME21->Fill(numberSegFound);
		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&inRing1&&(!foundSeg2)) segmentsNoME21->Fill(numberSegFound);

		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&(ring2==2)&&(ring3==2)&&(ring4==2)) muonSegmentsFid2->Fill(tracks_numberOfMatches);
		if (tracks_pt>20.0&&inZMass&&goodTag&&fiducialAll&&(ring2==2)&&(ring3==2)&&(ring4==2)) segmentsFid2->Fill(numberSegFound);

		if (tracks_pt>20.0&&numberOfPrimaryVertices>44&&inZMass&&goodTag&&fiducialAll&&inRing1) segmentsFid1HighPV->Fill(numberSegFound);
		if (tracks_pt>20.0&&numberOfPrimaryVertices>44&&inZMass&&goodTag&&fiducialAll&&inRing2) segmentsFid2HighPV->Fill(numberSegFound);
		if (tracks_pt>20.0&&numberOfPrimaryVertices<16&&inZMass&&goodTag&&fiducialAll&&inRing1) segmentsFid1LowPV->Fill(numberSegFound);
		if (tracks_pt>20.0&&numberOfPrimaryVertices<16&&inZMass&&goodTag&&fiducialAll&&inRing2) segmentsFid2LowPV->Fill(numberSegFound);

		if (tracks_pt>20.0&&numberOfPrimaryVertices>44&&inZMass&&goodTag&&fiducialAll&&inRing1) muonSegmentsFid1HighPV->Fill(tracks_numberOfMatches);
		if (tracks_pt>20.0&&numberOfPrimaryVertices>44&&inZMass&&goodTag&&fiducialAll&&inRing2) muonSegmentsFid2HighPV->Fill(tracks_numberOfMatches);
		if (tracks_pt>20.0&&numberOfPrimaryVertices<16&&inZMass&&goodTag&&fiducialAll&&inRing1) muonSegmentsFid1LowPV->Fill(tracks_numberOfMatches);
		if (tracks_pt>20.0&&numberOfPrimaryVertices<16&&inZMass&&goodTag&&fiducialAll&&inRing2) muonSegmentsFid2LowPV->Fill(tracks_numberOfMatches);


		if (tracks_pt>200.0&&inZMass&&goodTag&&fiducialAll&&inRing1) segmentsFid1HighpT->Fill(numberSegFound);
		if (tracks_pt>200.0&&inZMass&&goodTag&&fiducialAll&&inRing2) segmentsFid2HighpT->Fill(numberSegFound);




		if (foundSeg1) {
			foundHit1[0] = CSCnSegHits1 & (1 << (1-1));
			foundHit1[1] = CSCnSegHits1 & (1 << (2-1));
			foundHit1[2] = CSCnSegHits1 & (1 << (3-1));
			foundHit1[3] = CSCnSegHits1 & (1 << (4-1));
			foundHit1[4] = CSCnSegHits1 & (1 << (5-1));
			foundHit1[5] = CSCnSegHits1 & (1 << (6-1));
		}
		if (foundSeg2) {
			foundHit2[0] = CSCnSegHits2 & (1 << (1-1));
			foundHit2[1] = CSCnSegHits2 & (1 << (2-1));
			foundHit2[2] = CSCnSegHits2 & (1 << (3-1));
			foundHit2[3] = CSCnSegHits2 & (1 << (4-1));
			foundHit2[4] = CSCnSegHits2 & (1 << (5-1));
			foundHit2[5] = CSCnSegHits2 & (1 << (6-1));
		}
		if (foundSeg3) {
			foundHit3[0] = CSCnSegHits3 & (1 << (1-1));
			foundHit3[1] = CSCnSegHits3 & (1 << (2-1));
			foundHit3[2] = CSCnSegHits3 & (1 << (3-1));
			foundHit3[3] = CSCnSegHits3 & (1 << (4-1));
			foundHit3[4] = CSCnSegHits3 & (1 << (5-1));
			foundHit3[5] = CSCnSegHits3 & (1 << (6-1));
		}
		if (foundSeg4) {
			foundHit4[0] = CSCnSegHits4 & (1 << (1-1));
			foundHit4[1] = CSCnSegHits4 & (1 << (2-1));
			foundHit4[2] = CSCnSegHits4 & (1 << (3-1));
			foundHit4[3] = CSCnSegHits4 & (1 << (4-1));
			foundHit4[4] = CSCnSegHits4 & (1 << (5-1));
			foundHit4[5] = CSCnSegHits4 & (1 << (6-1));
		}




		if (inZMass&&goodTag&&(fiducial1||fiducial11)&&fiducial2&&fiducial3&&fiducial4) {totalFiducial++;runFiducial++;}
		if (inZMass&&goodTag&&(fiducial1||fiducial11)&&fiducial2&&fiducial3&&fiducial4&&(!(foundSeg1||foundSeg2||foundSeg3||foundSeg4))) {
			totalFail++;
			runFail++;
			//std::cout << "run, event " << run_number << " " << event_number << std::endl;
			//std::cout << "dxy " << CSCDxyTTSeg1 << " " << CSCDxyTTSeg2 << " " << CSCDxyTTSeg3 << " " << CSCDxyTTSeg4 << std::endl;
			//std::cout << "LCX :" << CSCSegxLc1 << " " << CSCSegxLc2 << " " << CSCSegxLc3 << " " << CSCSegxLc4 << std::endl;


		}
		if (inZMass&&goodTag&&(fiducial1||fiducial11)&&fiducial2&&fiducial3&&fiducial4&&foundSeg1&&foundSeg2&&foundSeg3&&foundSeg4) {totalPass++;runPass++;}



		// Print out for failed events
		//if ((fiducial1||fiducial11) && (!foundSeg1) && inZMassSideBand) std::cout << "RU passed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 1 << " " << CSCRg1*1 << " " << CSCCh1*1 << " !" << std::endl;
		// if (fiducial2 && (!foundSeg2) && inZMassSideBand) std::cout << "RU passed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 2 << " " << CSCRg2*1 << " " << CSCCh2*1 <<  " !" << std::endl;
		// if (fiducial3 && (!foundSeg3) && inZMassSideBand) std::cout << "RU passed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 3 << " " << CSCRg3*1 << " " << CSCCh3*1 <<  " !" << std::endl;
		// if (fiducial4 && (!foundSeg4) && inZMassSideBand) std::cout << "RU passed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 4 << " " << CSCRg4*1 << " " << CSCCh4*1 <<  " !" << std::endl;

		// if ((fiducial1||fiducial11) && (foundSeg1) && inZMassSideBand) std::cout << "RU failed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 1 << " " << CSCRg1*1 << " " << CSCCh1*1 <<  " !" << std::endl;
		// if (fiducial2 && (foundSeg2) && inZMassSideBand) std::cout << "RU failed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 2 << " " << CSCRg2*1 << " " << CSCCh2*1 <<  " !" << std::endl;
		// if (fiducial3 && (foundSeg3) && inZMassSideBand) std::cout << "RU failed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 3 << " " << CSCRg3*1 << " " << CSCCh3*1 <<  " !" << std::endl;
		// if (fiducial4 && (foundSeg4) && inZMassSideBand) std::cout << "RU failed: Run " << run_number << " event " << event_number << " endcap, station, ring, chamber " <<  CSCEndCapPlus << " " << 4 << " " << CSCRg4*1 << " " << CSCCh4*1 <<  " !" << std::endl;



		// Found LCT
		foundLCT1 = ((CSCDxyTTLCT1<cscDxyTTLCT || 
					CSCDxyTTLCT1/CSCDxyErrTTLCT1<sigmaCSCDxyTTLCT) &&
				CSCDxyTTLCT1>0.);
		foundLCT2 = ((CSCDxyTTLCT2<cscDxyTTLCT || 
					CSCDxyTTLCT2/CSCDxyErrTTLCT2<sigmaCSCDxyTTLCT) &&
				CSCDxyTTLCT2>0.);
		foundLCT3 = ((CSCDxyTTLCT3<cscDxyTTLCT || 
					CSCDxyTTLCT3/CSCDxyErrTTLCT3<sigmaCSCDxyTTLCT) &&
				CSCDxyTTLCT3>0.);
		foundLCT4 = ((CSCDxyTTLCT4<cscDxyTTLCT || 
					CSCDxyTTLCT4/CSCDxyErrTTLCT4<sigmaCSCDxyTTLCT) &&
				CSCDxyTTLCT4>0.);


		// ZMass plots

		if ((tracks_e > tagE)&&(minDRHLTAllSingleMu < maxDRHLTAllSingleMu) &&
				(dRTkMu1 > minDRTkMu1)&&(dRTkMu1<10.0)){
			//Good tag except for Z mass
			if ((fiducial1||fiducial11)&&invMass>60.0&&invMass<120.0) {
				zMassAll->Fill(invMass);
				if (foundSeg1) {zMassGood->Fill(invMass);} else {zMassBad->Fill(invMass);}
			}
			if (fiducial2) {
				//zMassAll->Fill(invMass);
				if (foundSeg2) {zMassGood->Fill(invMass);} else {zMassBad->Fill(invMass);}
			}
			if (fiducial3) {
				//zMassAll->Fill(invMass);
				if (foundSeg3) {zMassGood->Fill(invMass);} else {zMassBad->Fill(invMass);}
			}
			if (fiducial4) {
				//zMassAll->Fill(invMass);
				if (foundSeg4) {zMassGood->Fill(invMass);} else {zMassBad->Fill(invMass);}
			}


		}




		// Station, Ring, Chamber efficiencies
		if (goodTag) {

			// Define histrogram bins	  
			Int_t pTBin = -1;
			if (tracks_pt>ptBins[numPtBins]) pTBin = numPtBins;
			for (Int_t iiPt=0; iiPt< numPtBins; iiPt++){
				if (tracks_pt>ptBins[iiPt]&&tracks_pt<ptBins[iiPt+1]) pTBin = iiPt;
			}
			Int_t etaBin = -1;
			Int_t etaBin1 = -1;
			Int_t etaBin2 = -1;
			Int_t etaBin3 = -1;
			Int_t etaBin4 = -1;
			for (Int_t iiEta=0; iiEta< numEtaBins; iiEta++){
				//if (fabs(tracks_eta)>etaBins[iiEta]&&fabs(tracks_eta)<etaBins[iiEta+1]) etaBin = iiEta;
				//std::cout << "Eta " << tracks_eta << " " << CSCTTetaGc1 << std::endl;
				if (fabs(CSCTTetaGc1)>etaBins[iiEta]&&fabs(CSCTTetaGc1)<etaBins[iiEta+1]) etaBin = iiEta;
				if (fabs(CSCTTetaGc1)>etaBins[iiEta]&&fabs(CSCTTetaGc1)<etaBins[iiEta+1]) etaBin1 = iiEta;
				if (fabs(CSCTTetaGc2)>etaBins[iiEta]&&fabs(CSCTTetaGc2)<etaBins[iiEta+1]) etaBin2 = iiEta;
				if (fabs(CSCTTetaGc3)>etaBins[iiEta]&&fabs(CSCTTetaGc3)<etaBins[iiEta+1]) etaBin3 = iiEta;
				if (fabs(CSCTTetaGc4)>etaBins[iiEta]&&fabs(CSCTTetaGc4)<etaBins[iiEta+1]) etaBin4 = iiEta;
			}
			Int_t isoBin = -1;
			for (Int_t iiIso=0; iiIso< numIsoBins; iiIso++){
				if (tracks_IsoR03Ratio>isoBins[iiIso]&&tracks_IsoR03Ratio<isoBins[iiIso+1]) isoBin = iiIso;
			}
			Int_t pvBin = -1;
			for (Int_t iiPV=0; iiPV< numPVBins; iiPV++){
				if (numberOfPrimaryVertices>pvBins[iiPV]&&numberOfPrimaryVertices<pvBins[iiPV+1]) pvBin = iiPV;
			}
			Int_t ilBin = -1;
			for (Int_t iiIL=0; iiIL< numILBins; iiIL++){
				if (LumiInst->front()>ilBins[iiIL]&&LumiInst->front()<ilBins[iiIL+1]) ilBin = iiIL;
			}
			//std::cout << "Lumi " << LumiInst->front() << " ilBin " << ilBin << " size " << LumiInst->size() << std::endl;
			Int_t runBin = -1;
			for (Int_t iiRun=0; iiRun< numRunBins; iiRun++){
				if (run_number>runBins[iiRun]&&run_number<runBins[iiRun+1]) runBin = iiRun;
			}




			Int_t lCYBin1 = -1;
			Int_t lCYBin2 = -1;
			Int_t lCYBin3 = -1;
			Int_t lCYBin4 = -1;
			Int_t lC3YBin1 = -1;
			Int_t lC3YBin2 = -1;
			Int_t lC3YBin3 = -1;
			Int_t lC3YBin4 = -1;
			for (Int_t iiLCY=0; iiLCY< numLCYBins; iiLCY++){
				if (CSCTTyLc1>lCYBins[iiLCY]&&CSCTTyLc1<lCYBins[iiLCY+1]) lCYBin1 = iiLCY;
				if (CSCTTyLc2>lCYBins[iiLCY]&&CSCTTyLc2<lCYBins[iiLCY+1]) lCYBin2 = iiLCY;
				if (CSCTTyLc3>lCYBins[iiLCY]&&CSCTTyLc3<lCYBins[iiLCY+1]) lCYBin3 = iiLCY;
				if (CSCTTyLc4>lCYBins[iiLCY]&&CSCTTyLc4<lCYBins[iiLCY+1]) lCYBin4 = iiLCY;
				if (CSCTT3yLc1>lCYBins[iiLCY]&&CSCTT3yLc1<lCYBins[iiLCY+1]) lC3YBin1 = iiLCY;
				if (CSCTT3yLc2>lCYBins[iiLCY]&&CSCTT3yLc2<lCYBins[iiLCY+1]) lC3YBin2 = iiLCY;
				if (CSCTT3yLc3>lCYBins[iiLCY]&&CSCTT3yLc3<lCYBins[iiLCY+1]) lC3YBin3 = iiLCY;
				if (CSCTT3yLc4>lCYBins[iiLCY]&&CSCTT3yLc4<lCYBins[iiLCY+1]) lC3YBin4 = iiLCY;
			}


			Int_t lCWBin1 = -1;
			Int_t lCWBin2 = -1;
			Int_t lCWBin3 = -1;
			Int_t lCWBin4 = -1;
			Int_t lC3WBin1 = -1;
			Int_t lC3WBin2 = -1;
			Int_t lC3WBin3 = -1;
			Int_t lC3WBin4 = -1;
			for (Int_t iiLCW=0; iiLCW< numLCWBins; iiLCW++){
				if (CSCTTyLc1>lCWBins[iiLCW]&&CSCTTyLc1<lCWBins[iiLCW+1]) lCWBin1 = iiLCW;
				if (CSCTTyLc2>lCWBins[iiLCW]&&CSCTTyLc2<lCWBins[iiLCW+1]) lCWBin2 = iiLCW;
				if (CSCTTyLc3>lCWBins[iiLCW]&&CSCTTyLc3<lCWBins[iiLCW+1]) lCWBin3 = iiLCW;
				if (CSCTTyLc4>lCWBins[iiLCW]&&CSCTTyLc4<lCWBins[iiLCW+1]) lCWBin4 = iiLCW;
				if (CSCTT3yLc1>lCWBins[iiLCW]&&CSCTT3yLc1<lCWBins[iiLCW+1]) lC3WBin1 = iiLCW;
				if (CSCTT3yLc2>lCWBins[iiLCW]&&CSCTT3yLc2<lCWBins[iiLCW+1]) lC3WBin2 = iiLCW;
				if (CSCTT3yLc3>lCWBins[iiLCW]&&CSCTT3yLc3<lCWBins[iiLCW+1]) lC3WBin3 = iiLCW;
				if (CSCTT3yLc4>lCWBins[iiLCW]&&CSCTT3yLc4<lCWBins[iiLCW+1]) lC3WBin4 = iiLCW;
			}


			Int_t lCSBin1 = -1;
			Int_t lCSBin2 = -1;
			Int_t lCSBin3 = -1;
			Int_t lCSBin4 = -1;
			Int_t lC3SBin1 = -1;
			Int_t lC3SBin2 = -1;
			Int_t lC3SBin3 = -1;
			Int_t lC3SBin4 = -1;
			for (Int_t iiLCS=0; iiLCS< numLCSBins; iiLCS++){
				if (CSCTTsLc1>lCSBins[iiLCS]&&CSCTTsLc1<lCSBins[iiLCS+1]) lCSBin1 = iiLCS;
				if (CSCTTsLc2>lCSBins[iiLCS]&&CSCTTsLc2<lCSBins[iiLCS+1]) lCSBin2 = iiLCS;
				if (CSCTTsLc3>lCSBins[iiLCS]&&CSCTTsLc3<lCSBins[iiLCS+1]) lCSBin3 = iiLCS;
				if (CSCTTsLc4>lCSBins[iiLCS]&&CSCTTsLc4<lCSBins[iiLCS+1]) lCSBin4 = iiLCS;
				if (CSCTT3sLc1>lCSBins[iiLCS]&&CSCTT3sLc1<lCSBins[iiLCS+1]) lC3SBin1 = iiLCS;
				if (CSCTT3sLc2>lCSBins[iiLCS]&&CSCTT3sLc2<lCSBins[iiLCS+1]) lC3SBin2 = iiLCS;
				if (CSCTT3sLc3>lCSBins[iiLCS]&&CSCTT3sLc3<lCSBins[iiLCS+1]) lC3SBin3 = iiLCS;
				if (CSCTT3sLc4>lCSBins[iiLCS]&&CSCTT3sLc4<lCSBins[iiLCS+1]) lC3SBin4 = iiLCS;
			}

			Int_t dCFEBBin1 = -1;
			Int_t dCFEBBin2 = -1;
			Int_t dCFEBBin3 = -1;
			Int_t dCFEBBin4 = -1;
			Int_t dCFEB3Bin1 = -1;
			Int_t dCFEB3Bin2 = -1;
			Int_t dCFEB3Bin3 = -1;
			Int_t dCFEB3Bin4 = -1;
			for (Int_t iiDCFEB=0; iiDCFEB< numDCFEBBins; iiDCFEB++){
				if (CSCTTsLc1>dCFEBLCSBins[iiDCFEB]&&CSCTTsLc1<dCFEBLCSBins[iiDCFEB+1]) dCFEBBin1 = iiDCFEB;
				if (CSCTTsLc2>dCFEBLCSBins[iiDCFEB]&&CSCTTsLc2<dCFEBLCSBins[iiDCFEB+1]) dCFEBBin2 = iiDCFEB;
				if (CSCTTsLc3>dCFEBLCSBins[iiDCFEB]&&CSCTTsLc3<dCFEBLCSBins[iiDCFEB+1]) dCFEBBin3 = iiDCFEB;
				if (CSCTTsLc4>dCFEBLCSBins[iiDCFEB]&&CSCTTsLc4<dCFEBLCSBins[iiDCFEB+1]) dCFEBBin4 = iiDCFEB;
				if (CSCTT3sLc1>dCFEBLCSBins[iiDCFEB]&&CSCTT3sLc1<dCFEBLCSBins[iiDCFEB+1]) dCFEB3Bin1 = iiDCFEB;
				if (CSCTT3sLc2>dCFEBLCSBins[iiDCFEB]&&CSCTT3sLc2<dCFEBLCSBins[iiDCFEB+1]) dCFEB3Bin2 = iiDCFEB;
				if (CSCTT3sLc3>dCFEBLCSBins[iiDCFEB]&&CSCTT3sLc3<dCFEBLCSBins[iiDCFEB+1]) dCFEB3Bin3 = iiDCFEB;
				if (CSCTT3sLc4>dCFEBLCSBins[iiDCFEB]&&CSCTT3sLc4<dCFEBLCSBins[iiDCFEB+1]) dCFEB3Bin4 = iiDCFEB;
			}



			// Central region
			if (inZMass) {
				if (!CSCEndCapPlus){
					if (fiducial1||fiducial11){
						totGlobal++;
						if (CSCRg1==4&&fiducial11) {totStationRing[0][0]++;totStationRingChamber[0][0][CSCCh1]++;totStationRingPt[0][0][pTBin]++;totStationRingEta[0][0][etaBin]++;totStationRingIso[0][0][isoBin]++;totStationRingPV[0][0][pvBin]++;totStationRingIL[0][0][ilBin]++;totStationRingRun[0][0][runBin]++;totStationRingChamberRun[0][0][CSCCh1][runBin]++;totStationRingLCY[0][0][lCYBin1]++;totStationRingLCYLCT[0][0][lC3YBin1]++;totStationRingLCS[0][0][lCSBin1]++;totStationRingLCSLCT[0][0][lC3SBin1]++;totStationRingChamberLCY[0][0][CSCCh1][lCYBin1]++;totStationRingChamberLCS[0][0][CSCCh1][lCSBin1]++;totStationRingChamberLCW[0][0][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[0][0][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[0][0][CSCCh1][dCFEB3Bin1]++;
							if (inZMass) segDenStationRingChamberRun[0][0][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][0][CSCCh1]->Fill(invMass);
							zMassSegDenStationRingPV[0][0][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][0][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][0][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);
								yySegStationRing[0][0]->Fill(CSCSegyLc1,CSCTTyLc1);}
							//!!!!! here is where the first segment hit info goes
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[0][0][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[0][0][CSCCh1][iiLayer]++;
							}

							if (CSCCh1%2 == 0 ) {totStationRing[1][0]++;totStationRingChamber[1][0][CSCCh1]++;totStationRingPt[1][0][pTBin]++;totStationRingEta[1][0][etaBin]++;totStationRingIso[1][0][isoBin]++;totStationRingPV[1][0][pvBin]++;totStationRingIL[1][0][ilBin]++;totStationRingRun[1][0][runBin]++;totStationRingChamberRun[1][0][CSCCh1][runBin]++;totStationRingLCY[1][0][lCYBin1]++;totStationRingLCYLCT[1][0][lC3YBin1]++;totStationRingLCS[1][0][lCSBin1]++;totStationRingLCSLCT[1][0][lC3SBin1]++;yySegStationRing[1][0]->Fill(CSCSegyLc1,CSCTTyLc1);}
							else {totStationRing[1][3]++;totStationRingChamber[1][3][CSCCh1]++;totStationRingPt[1][3][pTBin]++;totStationRingEta[1][3][etaBin]++;totStationRingIso[1][3][isoBin]++;totStationRingPV[1][3][pvBin]++;totStationRingIL[1][3][ilBin]++;totStationRingRun[1][3][runBin]++;totStationRingChamberRun[1][3][CSCCh1][runBin]++;totStationRingLCY[1][3][lCYBin1]++;totStationRingLCYLCT[1][3][lC3YBin1]++;totStationRingLCS[1][3][lCSBin1]++;totStationRingLCSLCT[1][3][lC3SBin1]++;yySegStationRing[1][3]->Fill(CSCSegyLc1,CSCTTyLc1);}		  
						}
						if (CSCRg1==1&&fiducial11) {totStationRing[0][1]++;totStationRingChamber[0][1][CSCCh1]++;totStationRingPt[0][1][pTBin]++;totStationRingEta[0][1][etaBin]++;totStationRingIso[0][1][isoBin]++;totStationRingPV[0][1][pvBin]++;totStationRingIL[0][1][ilBin]++;totStationRingRun[0][1][runBin]++;totStationRingChamberRun[0][1][CSCCh1][runBin]++;totStationRingLCY[0][1][lCYBin1]++;totStationRingLCYLCT[0][1][lC3YBin1]++;totStationRingLCS[0][1][lCSBin1]++;totStationRingLCSLCT[0][1][lC3SBin1]++;totStationRingChamberLCY[0][1][CSCCh1][lCYBin1]++;totStationRingChamberLCS[0][1][CSCCh1][lCSBin1]++;totStationRingChamberLCW[0][1][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[0][1][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[0][1][CSCCh1][dCFEB3Bin1]++;
							if (inZMass) segDenStationRingChamberRun[0][1][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][1][CSCCh1]->Fill(invMass);
							zMassSegDenStationRingPV[0][1][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][1][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][1][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);
								yySegStationRing[0][1]->Fill(CSCSegyLc1,CSCTTyLc1);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[0][1][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[0][1][CSCCh1][iiLayer]++;
							}
							if (CSCCh1%2 == 0 )  {totStationRing[2][0]++;totStationRingChamber[2][0][CSCCh1]++;totStationRingPt[2][0][pTBin]++;totStationRingEta[2][0][etaBin]++;totStationRingIso[2][0][isoBin]++;totStationRingPV[2][0][pvBin]++;totStationRingIL[2][0][ilBin]++;totStationRingRun[2][0][runBin]++;totStationRingChamberRun[2][0][CSCCh1][runBin]++;totStationRingLCY[2][0][lCYBin1]++;totStationRingLCYLCT[2][0][lC3YBin1]++;totStationRingLCS[2][0][lCSBin1]++;totStationRingLCSLCT[2][0][lC3SBin1]++;yySegStationRing[2][0]->Fill(CSCSegyLc1,CSCTTyLc1);}
							else {totStationRing[2][3]++;totStationRingChamber[2][3][CSCCh1]++;totStationRingPt[2][3][pTBin]++;totStationRingEta[2][3][etaBin]++;totStationRingIso[2][3][isoBin]++;totStationRingPV[2][3][pvBin]++;totStationRingIL[2][3][ilBin]++;totStationRingRun[2][3][runBin]++;totStationRingChamberRun[2][3][CSCCh1][runBin]++;totStationRingLCY[2][3][lCYBin1]++;totStationRingLCYLCT[2][3][lC3YBin1]++;totStationRingLCS[2][3][lCSBin1]++;totStationRingLCSLCT[2][3][lC3SBin1]++;yySegStationRing[2][3]->Fill(CSCSegyLc1,CSCTTyLc1);}
						}
						if (CSCRg1==2) {totStationRing[0][2]++;totStationRingChamber[0][2][CSCCh1]++;totStationRingPt[0][2][pTBin]++;totStationRingEta[0][2][etaBin]++;totStationRingIso[0][2][isoBin]++;totStationRingPV[0][2][pvBin]++;totStationRingIL[0][2][ilBin]++;totStationRingRun[0][2][runBin]++;totStationRingChamberRun[0][2][CSCCh1][runBin]++;totStationRingLCY[0][2][lCYBin1]++;totStationRingLCYLCT[0][2][lC3YBin1]++;totStationRingLCS[0][2][lCSBin1]++;totStationRingLCSLCT[0][2][lC3SBin1]++;totStationRingChamberLCY[0][2][CSCCh1][lCYBin1]++;totStationRingChamberLCS[0][2][CSCCh1][lCSBin1]++;totStationRingChamberLCW[0][2][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[0][2][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[0][2][CSCCh1][dCFEB3Bin1]++;
							if (inZMass) segDenStationRingChamberRun[0][2][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][2][CSCCh1]->Fill(invMass);
							zMassSegDenStationRingPV[0][2][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][2][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][2][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[0][2][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[0][2][CSCCh1][iiLayer]++;
							}
						}
						if (CSCRg1==3) {totStationRing[0][3]++;totStationRingChamber[0][3][CSCCh1]++;totStationRingPt[0][3][pTBin]++;totStationRingEta[0][3][etaBin]++;totStationRingIso[0][3][isoBin]++;totStationRingPV[0][3][pvBin]++;totStationRingIL[0][3][ilBin]++;totStationRingRun[0][3][runBin]++;totStationRingChamberRun[0][3][CSCCh1][runBin]++;totStationRingLCY[0][3][lCYBin1]++;totStationRingLCYLCT[0][3][lC3YBin1]++;totStationRingLCS[0][3][lCSBin1]++;totStationRingLCSLCT[0][3][lC3SBin1]++;totStationRingChamberLCY[0][3][CSCCh1][lCYBin1]++;totStationRingChamberLCS[0][3][CSCCh1][lCSBin1]++;totStationRingChamberLCW[0][3][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[0][3][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[0][3][CSCCh1][dCFEB3Bin1]++;
							if (inZMass) segDenStationRingChamberRun[0][3][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][3][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][3][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][3][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[0][3][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[0][3][CSCCh1][iiLayer]++;
							}
						}
						if (foundSeg1) {
							passGlobalSeg++;
							if (CSCRg1==4&&fiducial11) {passStationRingSeg[0][0]++;passStationRingChamberSeg[0][0][CSCCh1]++;passStationRingPtSeg[0][0][pTBin]++;passStationRingEtaSeg[0][0][etaBin]++;passStationRingIsoSeg[0][0][isoBin]++;passStationRingPVSeg[0][0][pvBin]++;passStationRingILSeg[0][0][ilBin]++;passStationRingRunSeg[0][0][runBin]++;passStationRingChamberRunSeg[0][0][CSCCh1][runBin]++;passStationRingLCYSeg[0][0][lCYBin1]++;passStationRingLCSSeg[0][0][lCSBin1]++;passStationRingChamberLCYSeg[0][0][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[0][0][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[0][0][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[0][0][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][0][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][0][CSCCh1]->Fill(invMass);
								zMassSegNumStationRingPV[0][0][pvBin]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passStationRingSeg[1][0]++;passStationRingChamberSeg[1][0][CSCCh1]++;passStationRingPtSeg[1][0][pTBin]++;passStationRingEtaSeg[1][0][etaBin]++;passStationRingIsoSeg[1][0][isoBin]++;passStationRingPVSeg[1][0][pvBin]++;passStationRingILSeg[1][0][ilBin]++;passStationRingRunSeg[1][0][runBin]++;passStationRingChamberRunSeg[1][0][CSCCh1][runBin]++;passStationRingLCYSeg[1][0][lCYBin1]++;;passStationRingLCSSeg[1][0][lCSBin1]++;}
								else {passStationRingSeg[1][3]++;passStationRingChamberSeg[1][3][CSCCh1]++;passStationRingPtSeg[1][3][pTBin]++;passStationRingEtaSeg[1][3][etaBin]++;passStationRingIsoSeg[1][3][isoBin]++;passStationRingPVSeg[1][3][pvBin]++;passStationRingILSeg[1][3][ilBin]++;passStationRingRunSeg[1][3][runBin]++;passStationRingChamberRunSeg[1][3][CSCCh1][runBin]++;passStationRingLCYSeg[1][3][lCYBin1]++;passStationRingLCSSeg[1][3][lCSBin1]++;}		    
							}
							if (CSCRg1==1&&fiducial11) {passStationRingSeg[0][1]++;passStationRingChamberSeg[0][1][CSCCh1]++;passStationRingPtSeg[0][1][pTBin]++;passStationRingEtaSeg[0][1][etaBin]++;passStationRingIsoSeg[0][1][isoBin]++;passStationRingPVSeg[0][1][pvBin]++;passStationRingILSeg[0][1][ilBin]++;passStationRingRunSeg[0][1][runBin]++;passStationRingChamberRunSeg[0][1][CSCCh1][runBin]++;passStationRingLCYSeg[0][1][lCYBin1]++;passStationRingLCSSeg[0][1][lCSBin1]++;passStationRingChamberLCYSeg[0][1][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[0][1][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[0][1][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[0][1][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][1][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][1][CSCCh1]->Fill(invMass);
								zMassSegNumStationRingPV[0][1][pvBin]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passStationRingSeg[2][0]++;passStationRingChamberSeg[2][0][CSCCh1]++;passStationRingPtSeg[2][0][pTBin]++;passStationRingEtaSeg[2][0][etaBin]++;passStationRingIsoSeg[2][0][isoBin]++;passStationRingPVSeg[2][0][pvBin]++;passStationRingILSeg[2][0][ilBin]++;passStationRingRunSeg[2][0][runBin]++;passStationRingChamberRunSeg[2][0][CSCCh1][runBin]++;passStationRingLCYSeg[2][0][lCYBin1]++;passStationRingLCSSeg[2][0][lCSBin1]++;}
								else {passStationRingSeg[2][3]++;passStationRingChamberSeg[2][3][CSCCh1]++;passStationRingPtSeg[2][3][pTBin]++;passStationRingEtaSeg[2][3][etaBin]++;passStationRingIsoSeg[2][3][isoBin]++;passStationRingPVSeg[2][3][pvBin]++;passStationRingILSeg[2][3][ilBin]++;passStationRingRunSeg[2][3][runBin]++;passStationRingChamberRunSeg[2][3][CSCCh1][runBin]++;passStationRingLCYSeg[2][3][lCYBin1]++;;passStationRingLCSSeg[2][3][lCSBin1]++;}		    
							}
							if (CSCRg1==2) {passStationRingSeg[0][2]++;passStationRingChamberSeg[0][2][CSCCh1]++;passStationRingPtSeg[0][2][pTBin]++;passStationRingEtaSeg[0][2][etaBin]++;passStationRingIsoSeg[0][2][isoBin]++;passStationRingPVSeg[0][2][pvBin]++;passStationRingILSeg[0][2][ilBin]++;passStationRingRunSeg[0][2][runBin]++;passStationRingChamberRunSeg[0][2][CSCCh1][runBin]++;passStationRingLCYSeg[0][2][lCYBin1]++;passStationRingLCSSeg[0][2][lCSBin1]++;passStationRingChamberLCYSeg[0][2][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[0][2][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[0][2][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[0][2][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][2][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][2][CSCCh1]->Fill(invMass);
								zMassSegNumStationRingPV[0][2][pvBin]->Fill(invMass);
							}
							if (CSCRg1==3) {passStationRingSeg[0][3]++;passStationRingChamberSeg[0][3][CSCCh1]++;passStationRingPtSeg[0][3][pTBin]++;passStationRingEtaSeg[0][3][etaBin]++;passStationRingIsoSeg[0][3][isoBin]++;passStationRingPVSeg[0][3][pvBin]++;passStationRingILSeg[0][3][ilBin]++;passStationRingRunSeg[0][3][runBin]++;passStationRingChamberRunSeg[0][3][CSCCh1][runBin]++;passStationRingLCYSeg[0][3][lCYBin1]++;passStationRingLCSSeg[0][3][lCSBin1]++;passStationRingChamberLCYSeg[0][3][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[0][3][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[0][3][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[0][3][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][3][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][3][CSCCh1]->Fill(invMass);
							}
						}
						if (foundLCT1) {
							passGlobalLCT++;
							if (CSCRg1==4&&fiducial11) {passStationRingLCT[0][0]++;passStationRingChamberLCT[0][0][CSCCh1]++;passStationRingPtLCT[0][0][pTBin]++;passStationRingEtaLCT[0][0][etaBin]++;passStationRingIsoLCT[0][0][isoBin]++;passStationRingPVLCT[0][0][pvBin]++;passStationRingILLCT[0][0][ilBin]++;passStationRingRunLCT[0][0][runBin]++;passStationRingChamberRunLCT[0][0][CSCCh1][runBin]++;passStationRingLCYLCT[0][0][lC3YBin1]++;passStationRingLCSLCT[0][0][lC3SBin1]++;passStationRingChamberLCYLCT[0][0][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[0][0][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[0][0][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[0][0][CSCCh1][dCFEB3Bin1]++;
								if (inZMass) LCTNumStationRingChamberRun[0][0][CSCCh1]->Fill(run_number);
								zMassLCTNumStationRingPV[0][0][pvBin]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passStationRingLCT[1][0]++;passStationRingChamberLCT[1][0][CSCCh1]++;passStationRingPtLCT[1][0][pTBin]++;passStationRingEtaLCT[1][0][etaBin]++;passStationRingIsoLCT[1][0][isoBin]++;passStationRingPVLCT[1][0][pvBin]++;passStationRingILLCT[1][0][ilBin]++;passStationRingRunLCT[1][0][runBin]++;passStationRingChamberRunLCT[1][0][CSCCh1][runBin]++;passStationRingLCYLCT[1][0][lC3YBin1]++;passStationRingLCSLCT[1][0][lC3SBin1]++;}
								else {passStationRingLCT[1][3]++;passStationRingChamberLCT[1][3][CSCCh1]++;passStationRingPtLCT[1][3][pTBin]++;passStationRingEtaLCT[1][3][etaBin]++;passStationRingIsoLCT[1][3][isoBin]++;passStationRingPVLCT[1][3][pvBin]++;passStationRingILLCT[1][3][ilBin]++;passStationRingRunLCT[1][3][runBin]++;passStationRingChamberRunLCT[1][3][CSCCh1][runBin]++;passStationRingLCYLCT[1][3][lC3YBin1]++;passStationRingLCSLCT[1][3][lC3SBin1]++;}
							}
							if (CSCRg1==1&&fiducial11) {passStationRingLCT[0][1]++;passStationRingChamberLCT[0][1][CSCCh1]++;passStationRingPtLCT[0][1][pTBin]++;passStationRingEtaLCT[0][1][etaBin]++;passStationRingIsoLCT[0][1][isoBin]++;passStationRingPVLCT[0][1][pvBin]++;passStationRingILLCT[0][1][ilBin]++;passStationRingRunLCT[0][1][runBin]++;passStationRingChamberRunLCT[0][1][CSCCh1][runBin]++;passStationRingLCYLCT[0][1][lC3YBin1]++;passStationRingLCSLCT[0][1][lC3SBin1]++;;passStationRingChamberLCYLCT[0][1][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[0][1][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[0][1][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[0][1][CSCCh1][dCFEB3Bin1]++;
								if (inZMass) LCTNumStationRingChamberRun[0][1][CSCCh1]->Fill(run_number);
								zMassLCTNumStationRingPV[0][1][pvBin]->Fill(invMass);		    
								if (CSCCh1%2 == 0 ) {passStationRingLCT[2][0]++;passStationRingChamberLCT[2][0][CSCCh1]++;passStationRingPtLCT[2][0][pTBin]++;passStationRingEtaLCT[2][0][etaBin]++;passStationRingIsoLCT[2][0][isoBin]++;passStationRingPVLCT[2][0][pvBin]++;passStationRingILLCT[2][0][ilBin]++;passStationRingRunLCT[2][0][runBin]++;passStationRingChamberRunLCT[2][0][CSCCh1][runBin]++;passStationRingLCYLCT[2][0][lC3YBin1]++;passStationRingLCSLCT[2][0][lC3SBin1]++;}
								else {passStationRingLCT[2][3]++;passStationRingChamberLCT[2][3][CSCCh1]++;passStationRingPtLCT[2][3][pTBin]++;passStationRingEtaLCT[2][3][etaBin]++;passStationRingIsoLCT[2][3][isoBin]++;passStationRingPVLCT[2][3][pvBin]++;passStationRingILLCT[2][3][ilBin]++;passStationRingRunLCT[2][3][runBin]++;passStationRingChamberRunLCT[2][3][CSCCh1][runBin]++;passStationRingLCYLCT[2][3][lC3YBin1]++;passStationRingLCSLCT[2][3][lC3SBin1]++;}
							}
							if (CSCRg1==2) {passStationRingLCT[0][2]++;passStationRingChamberLCT[0][2][CSCCh1]++;passStationRingPtLCT[0][2][pTBin]++;passStationRingEtaLCT[0][2][etaBin]++;passStationRingIsoLCT[0][2][isoBin]++;passStationRingPVLCT[0][2][pvBin]++;passStationRingILLCT[0][2][ilBin]++;passStationRingRunLCT[0][2][runBin]++;passStationRingChamberRunLCT[0][2][CSCCh1][runBin]++;passStationRingLCYLCT[0][2][lC3YBin1]++;passStationRingLCSLCT[0][2][lC3SBin1]++;passStationRingChamberLCYLCT[0][2][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[0][2][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[0][2][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[0][2][CSCCh1][dCFEB3Bin1]++;
								zMassLCTNumStationRingPV[0][2][pvBin]->Fill(invMass);
								if (inZMass) LCTNumStationRingChamberRun[0][2][CSCCh1]->Fill(run_number);
							}
							if (CSCRg1==3) {passStationRingLCT[0][3]++;passStationRingChamberLCT[0][3][CSCCh1]++;passStationRingPtLCT[0][3][pTBin]++;passStationRingEtaLCT[0][3][etaBin]++;passStationRingIsoLCT[0][3][isoBin]++;passStationRingPVLCT[0][3][pvBin]++;passStationRingILLCT[0][3][ilBin]++;passStationRingRunLCT[0][3][runBin]++;passStationRingChamberRunLCT[0][3][CSCCh1][runBin]++;passStationRingLCYLCT[0][3][lC3YBin1]++;passStationRingLCSLCT[0][3][lC3SBin1]++;passStationRingChamberLCYLCT[0][3][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[0][3][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[0][3][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[0][3][CSCCh1][dCFEB3Bin1]++;
								zMassLCTNumStationRingPV[0][3][pvBin]->Fill(invMass);
								if (inZMass) LCTNumStationRingChamberRun[0][3][CSCCh1]->Fill(run_number);
							}
						}
					}
					if (fiducial2){
						totGlobal++;
						if (CSCRg2==1) {totStationRing[1][1]++;totStationRingChamber[1][1][CSCCh2]++;totStationRingPt[1][1][pTBin]++;totStationRingEta[1][1][etaBin2]++;totStationRingIso[1][1][isoBin]++;totStationRingPV[1][1][pvBin]++;totStationRingIL[1][1][ilBin]++;totStationRingRun[1][1][runBin]++;totStationRingChamberRun[1][1][CSCCh2][runBin]++;totStationRingLCY[1][1][lCYBin2]++;totStationRingLCYLCT[1][1][lC3YBin2]++;totStationRingLCS[1][1][lCSBin2]++;totStationRingLCSLCT[1][1][lC3SBin2]++;totStationRingChamberLCY[1][1][CSCCh2][lCYBin2]++;totStationRingChamberLCS[1][1][CSCCh2][lCSBin2]++;totStationRingChamberLCW[1][1][CSCCh2][lCWBin2]++;totStationRingChamberDCFEB[1][1][CSCCh2][dCFEBBin2]++;totStationRingChamberDCFEBLCT[1][1][CSCCh2][dCFEB3Bin2]++;
							if (inZMass) segDenStationRingChamberRun[1][1][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[1][1][CSCCh2]->Fill(invMass);
							zMassSegDenStationRingPV[1][1][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[1][1][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[1][1][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[1][1][CSCCh2][iiLayer]++;
								if (foundHit2[iiLayer]) passStationRingChamberLayerSeg[1][1][CSCCh2][iiLayer]++;
							}
						}
						if (CSCRg2==2) {totStationRing[1][2]++;totStationRingChamber[1][2][CSCCh2]++;totStationRingPt[1][2][pTBin]++;totStationRingEta[1][2][etaBin2]++;totStationRingIso[1][2][isoBin]++;totStationRingPV[1][2][pvBin]++;totStationRingIL[1][2][ilBin]++;totStationRingRun[1][2][runBin]++;totStationRingChamberRun[1][2][CSCCh2][runBin]++;totStationRingLCY[1][2][lCYBin2]++;totStationRingLCYLCT[1][2][lC3YBin2]++;totStationRingLCS[1][2][lCSBin2]++;totStationRingLCSLCT[1][2][lC3SBin2]++;totStationRingChamberLCY[1][2][CSCCh2][lCYBin2]++;totStationRingChamberLCS[1][2][CSCCh2][lCSBin2]++;totStationRingChamberLCW[1][2][CSCCh2][lCWBin2]++;totStationRingChamberDCFEB[1][2][CSCCh2][dCFEBBin2]++;totStationRingChamberDCFEBLCT[1][2][CSCCh2][dCFEB3Bin2]++;
							if (inZMass) segDenStationRingChamberRun[1][2][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[1][2][CSCCh2]->Fill(invMass);
							zMassSegDenStationRingPV[1][2][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[1][2][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[1][2][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[1][2][CSCCh2][iiLayer]++;
								if (foundHit2[iiLayer]) passStationRingChamberLayerSeg[1][2][CSCCh2][iiLayer]++;
							}
						}
						if (foundSeg2) {
							passGlobalSeg++;
							if (CSCRg2==1) {passStationRingSeg[1][1]++;passStationRingChamberSeg[1][1][CSCCh2]++;passStationRingPtSeg[1][1][pTBin]++;passStationRingEtaSeg[1][1][etaBin2]++;passStationRingIsoSeg[1][1][isoBin]++;passStationRingPVSeg[1][1][pvBin]++;passStationRingILSeg[1][1][ilBin]++;passStationRingRunSeg[1][1][runBin]++;passStationRingChamberRunSeg[1][1][CSCCh2][runBin]++;passStationRingLCYSeg[1][1][lCYBin2]++;passStationRingLCSSeg[1][1][lCSBin2]++;passStationRingChamberLCYSeg[1][1][CSCCh2][lCYBin2]++;passStationRingChamberLCSSeg[1][1][CSCCh2][lCSBin2]++;passStationRingChamberLCWSeg[1][1][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBSeg[1][1][CSCCh2][dCFEBBin2]++;
								if (inZMass) segNumStationRingChamberRun[1][1][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[1][1][CSCCh2]->Fill(invMass);
								zMassSegNumStationRingPV[1][1][pvBin]->Fill(invMass);
							}
							if (CSCRg2==2) {passStationRingSeg[1][2]++;passStationRingChamberSeg[1][2][CSCCh2]++;passStationRingPtSeg[1][2][pTBin]++;passStationRingEtaSeg[1][2][etaBin2]++;passStationRingIsoSeg[1][2][isoBin]++;passStationRingPVSeg[1][2][pvBin]++;passStationRingILSeg[1][2][ilBin]++;passStationRingRunSeg[1][2][runBin]++;passStationRingChamberRunSeg[1][2][CSCCh2][runBin]++;passStationRingLCYSeg[1][2][lCYBin2]++;passStationRingLCSSeg[1][2][lCSBin2]++;passStationRingChamberLCYSeg[1][2][CSCCh2][lCYBin2]++;passStationRingChamberLCSSeg[1][2][CSCCh2][lCSBin2]++;passStationRingChamberLCWSeg[1][2][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBSeg[1][2][CSCCh2][dCFEBBin2]++;
								if (inZMass) segNumStationRingChamberRun[1][2][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[1][2][CSCCh2]->Fill(invMass);
								zMassSegNumStationRingPV[1][2][pvBin]->Fill(invMass);
							}
						}
						if (foundLCT2) {
							passGlobalLCT++;
							if (CSCRg2==1) {passStationRingLCT[1][1]++;passStationRingChamberLCT[1][1][CSCCh2]++;passStationRingPtLCT[1][1][pTBin]++;passStationRingEtaLCT[1][1][etaBin2]++;passStationRingIsoLCT[1][1][isoBin]++;passStationRingPVLCT[1][1][pvBin]++;passStationRingILLCT[1][1][ilBin]++;passStationRingRunLCT[1][1][runBin]++;passStationRingChamberRunLCT[1][1][CSCCh2][runBin]++;passStationRingLCYLCT[1][1][lC3YBin1]++;passStationRingLCSLCT[1][1][lC3SBin1]++;passStationRingChamberLCYLCT[1][1][CSCCh2][lCYBin2]++;passStationRingChamberLCSLCT[1][1][CSCCh2][lCSBin2]++;passStationRingChamberLCWLCT[1][1][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBLCT[1][1][CSCCh2][dCFEB3Bin2]++;
								zMassLCTNumStationRingPV[1][1][pvBin]->Fill(invMass);
								if (inZMass) LCTNumStationRingChamberRun[1][1][CSCCh2]->Fill(run_number);
							}
							if (CSCRg2==2) {passStationRingLCT[1][2]++;passStationRingChamberLCT[1][2][CSCCh2]++;passStationRingPtLCT[1][2][pTBin]++;passStationRingEtaLCT[1][2][etaBin2]++;passStationRingIsoLCT[1][2][isoBin]++;passStationRingPVLCT[1][2][pvBin]++;passStationRingILLCT[1][2][ilBin]++;passStationRingRunLCT[1][2][runBin]++;passStationRingChamberRunLCT[1][2][CSCCh2][runBin]++;passStationRingLCYLCT[1][2][lC3YBin1]++;passStationRingLCSLCT[1][2][lC3SBin1]++;passStationRingChamberLCYLCT[1][2][CSCCh2][lCYBin2]++;passStationRingChamberLCSLCT[1][2][CSCCh2][lCSBin2]++;passStationRingChamberLCWLCT[1][2][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBLCT[1][2][CSCCh2][dCFEB3Bin2]++;
								zMassLCTNumStationRingPV[1][2][pvBin]->Fill(invMass);
								if (inZMass) LCTNumStationRingChamberRun[1][2][CSCCh2]->Fill(run_number);
							}
						}
					}
					if (fiducial3){
						totGlobal++;
						if (CSCRg3==1) {totStationRing[2][1]++;totStationRingChamber[2][1][CSCCh3]++;totStationRingPt[2][1][pTBin]++;totStationRingEta[2][1][etaBin3]++;totStationRingIso[2][1][isoBin]++;totStationRingPV[2][1][pvBin]++;totStationRingIL[2][1][ilBin]++;totStationRingRun[2][1][runBin]++;totStationRingChamberRun[2][1][CSCCh3][runBin]++;totStationRingLCY[2][1][lCYBin3]++;totStationRingLCYLCT[2][1][lC3YBin3]++;totStationRingLCS[2][1][lCSBin3]++;totStationRingLCSLCT[2][1][lC3SBin3]++;totStationRingChamberLCY[2][1][CSCCh3][lCYBin3]++;totStationRingChamberLCS[2][1][CSCCh3][lCSBin3]++;totStationRingChamberLCW[2][1][CSCCh3][lCWBin3]++;totStationRingChamberDCFEB[2][1][CSCCh3][dCFEBBin3]++;totStationRingChamberDCFEBLCT[2][1][CSCCh3][dCFEB3Bin3]++;
							if (inZMass) segDenStationRingChamberRun[2][1][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[2][1][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[2][1][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[2][1][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[2][1][CSCCh3][iiLayer]++;
								if (foundHit3[iiLayer]) passStationRingChamberLayerSeg[2][1][CSCCh3][iiLayer]++;
							}
						}
						if (CSCRg3==2) {totStationRing[2][2]++;totStationRingChamber[2][2][CSCCh3]++;totStationRingPt[2][2][pTBin]++;totStationRingEta[2][2][etaBin3]++;totStationRingIso[2][2][isoBin]++;totStationRingPV[2][2][pvBin]++;totStationRingIL[2][2][ilBin]++;totStationRingRun[2][2][runBin]++;totStationRingChamberRun[2][2][CSCCh3][runBin]++;totStationRingLCY[2][2][lCYBin3]++;totStationRingLCYLCT[2][2][lC3YBin3]++;totStationRingLCS[2][2][lCSBin3]++;totStationRingLCSLCT[2][2][lC3SBin3]++;totStationRingChamberLCY[2][2][CSCCh3][lCYBin3]++;totStationRingChamberLCS[2][2][CSCCh3][lCSBin3]++;totStationRingChamberLCW[2][2][CSCCh3][lCWBin3]++;totStationRingChamberDCFEB[2][2][CSCCh3][dCFEBBin3]++;totStationRingChamberDCFEBLCT[2][2][CSCCh3][dCFEB3Bin3]++;
							if (inZMass) segDenStationRingChamberRun[2][2][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[2][2][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[2][2][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[2][2][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[2][2][CSCCh3][iiLayer]++;
								if (foundHit3[iiLayer]) passStationRingChamberLayerSeg[2][2][CSCCh3][iiLayer]++;
							}
						}
						if (foundSeg3) {
							passGlobalSeg++;
							if (CSCRg3==1) {passStationRingSeg[2][1]++;passStationRingChamberSeg[2][1][CSCCh3]++;passStationRingPtSeg[2][1][pTBin]++;passStationRingEtaSeg[2][1][etaBin3]++;passStationRingIsoSeg[2][1][isoBin]++;passStationRingPVSeg[2][1][pvBin]++;passStationRingILSeg[2][1][ilBin]++;passStationRingRunSeg[2][1][runBin]++;passStationRingChamberRunSeg[2][1][CSCCh3][runBin]++;passStationRingLCYSeg[2][1][lCYBin3]++;passStationRingLCSSeg[2][1][lCSBin3]++;passStationRingChamberLCYSeg[2][1][CSCCh3][lCYBin3]++;passStationRingChamberLCSSeg[2][1][CSCCh3][lCSBin3]++;passStationRingChamberLCWSeg[2][1][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBSeg[2][1][CSCCh3][dCFEBBin3]++;
								if (inZMass) segNumStationRingChamberRun[2][1][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[2][1][CSCCh3]->Fill(invMass);
							}
							if (CSCRg3==2) {passStationRingSeg[2][2]++;passStationRingChamberSeg[2][2][CSCCh3]++;passStationRingPtSeg[2][2][pTBin]++;passStationRingEtaSeg[2][2][etaBin3]++;passStationRingIsoSeg[2][2][isoBin]++;passStationRingPVSeg[2][2][pvBin]++;passStationRingILSeg[2][2][ilBin]++;passStationRingRunSeg[2][2][runBin]++;passStationRingChamberRunSeg[2][2][CSCCh3][runBin]++;passStationRingLCYSeg[2][2][lCYBin3]++;passStationRingLCSSeg[2][2][lCSBin3]++;passStationRingChamberLCYSeg[2][2][CSCCh3][lCYBin3]++;passStationRingChamberLCSSeg[2][2][CSCCh3][lCSBin3]++;passStationRingChamberLCWSeg[2][2][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBSeg[2][2][CSCCh3][dCFEBBin3]++;
								if (inZMass) segNumStationRingChamberRun[2][2][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[2][2][CSCCh3]->Fill(invMass);
							}
						}
						if (foundLCT3) {
							passGlobalLCT++;
							if (CSCRg3==1) {passStationRingLCT[2][1]++;passStationRingChamberLCT[2][1][CSCCh3]++;passStationRingPtLCT[2][1][pTBin]++;passStationRingEtaLCT[2][1][etaBin3]++;passStationRingIsoLCT[2][1][isoBin]++;passStationRingPVLCT[2][1][pvBin]++;passStationRingILLCT[2][1][ilBin]++;passStationRingRunLCT[2][1][runBin]++;passStationRingChamberRunLCT[2][1][CSCCh3][runBin]++;passStationRingLCYLCT[2][1][lC3YBin3]++;passStationRingLCSLCT[2][1][lC3SBin3]++;passStationRingChamberLCYLCT[2][1][CSCCh3][lCYBin3]++;passStationRingChamberLCSLCT[2][1][CSCCh3][lCSBin3]++;passStationRingChamberLCWLCT[2][1][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBLCT[2][1][CSCCh3][dCFEB3Bin3]++;
								if (inZMass) LCTNumStationRingChamberRun[2][1][CSCCh3]->Fill(run_number);
							}
							if (CSCRg3==2) {passStationRingLCT[2][2]++;passStationRingChamberLCT[2][2][CSCCh3]++;passStationRingPtLCT[2][2][pTBin]++;passStationRingEtaLCT[2][2][etaBin3]++;passStationRingIsoLCT[2][2][isoBin]++;passStationRingPVLCT[2][2][pvBin]++;passStationRingILLCT[2][2][ilBin]++;passStationRingRunLCT[2][2][runBin]++;passStationRingChamberRunLCT[2][2][CSCCh3][runBin]++;passStationRingLCYLCT[2][2][lC3YBin3]++;passStationRingLCSLCT[2][2][lC3SBin3]++;passStationRingChamberLCYLCT[2][2][CSCCh3][lCYBin3]++;passStationRingChamberLCSLCT[2][2][CSCCh3][lCSBin3]++;passStationRingChamberLCWLCT[2][2][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBLCT[2][2][CSCCh3][dCFEB3Bin3]++;
								if (inZMass) LCTNumStationRingChamberRun[2][2][CSCCh3]->Fill(run_number);		    
							}
						}
					}
					if (fiducial4){
						totGlobal++;
						if (CSCRg4==1) {totStationRing[3][1]++;totStationRingChamber[3][1][CSCCh4]++;totStationRingPt[3][1][pTBin]++;totStationRingEta[3][1][etaBin4]++;totStationRingIso[3][1][isoBin]++;totStationRingPV[3][1][pvBin]++;totStationRingIL[3][1][ilBin]++;totStationRingRun[3][1][runBin]++;totStationRingChamberRun[3][1][CSCCh4][runBin]++;totStationRingLCY[3][1][lCYBin4]++;totStationRingLCYLCT[3][1][lC3YBin4]++;totStationRingLCS[3][1][lCSBin4]++;totStationRingLCSLCT[3][1][lC3SBin4]++;totStationRingChamberLCY[3][1][CSCCh4][lCYBin4]++;totStationRingChamberLCS[3][1][CSCCh4][lCSBin4]++;totStationRingChamberLCW[3][1][CSCCh4][lCWBin4]++;totStationRingChamberDCFEB[3][1][CSCCh4][dCFEBBin4]++;totStationRingChamberDCFEBLCT[3][1][CSCCh4][dCFEB3Bin4]++;
							if (inZMass) segDenStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[3][1][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[3][1][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[3][1][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[3][1][CSCCh4][iiLayer]++;
								if (foundHit4[iiLayer]) passStationRingChamberLayerSeg[3][1][CSCCh4][iiLayer]++;
							}
						}
						if (CSCRg4==2) {totStationRing[3][2]++;totStationRingChamber[3][2][CSCCh4]++;totStationRingPt[3][2][pTBin]++;totStationRingEta[3][2][etaBin4]++;totStationRingIso[3][2][isoBin]++;totStationRingPV[3][2][pvBin]++;totStationRingIL[3][2][ilBin]++;totStationRingRun[3][2][runBin]++;totStationRingChamberRun[3][2][CSCCh4][runBin]++;totStationRingLCY[3][2][lCYBin4]++;totStationRingLCYLCT[3][2][lC3YBin4]++;totStationRingLCS[3][2][lCSBin4]++;totStationRingLCSLCT[3][2][lC3SBin4]++;totStationRingChamberLCY[3][2][CSCCh4][lCYBin4]++;totStationRingChamberLCS[3][2][CSCCh4][lCSBin4]++;totStationRingChamberLCW[3][2][CSCCh4][lCWBin4]++;totStationRingChamberDCFEB[3][2][CSCCh4][dCFEBBin4]++;totStationRingChamberDCFEBLCT[3][2][CSCCh4][dCFEB3Bin4]++;
							//if (inZMass) segDenStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
							if (inZMass) segDenStationRingChamberRun[3][2][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[3][2][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[3][2][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[3][2][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[3][2][CSCCh4][iiLayer]++;
								if (foundHit4[iiLayer]) passStationRingChamberLayerSeg[3][2][CSCCh4][iiLayer]++;
							}
						}
						if (foundSeg4) {
							passGlobalSeg++;
							if (CSCRg4==1) {passStationRingSeg[3][1]++;passStationRingChamberSeg[3][1][CSCCh4]++;passStationRingPtSeg[3][1][pTBin]++;passStationRingEtaSeg[3][1][etaBin4]++;passStationRingIsoSeg[3][1][isoBin]++;passStationRingPVSeg[3][1][pvBin]++;passStationRingILSeg[3][1][ilBin]++;passStationRingRunSeg[3][1][runBin]++;passStationRingChamberRunSeg[3][1][CSCCh4][runBin]++;passStationRingLCYSeg[3][1][lCYBin4]++;passStationRingLCSSeg[3][1][lCSBin4]++;passStationRingChamberLCYSeg[3][1][CSCCh4][lCYBin4]++;passStationRingChamberLCSSeg[3][1][CSCCh4][lCSBin4]++;passStationRingChamberLCWSeg[3][1][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBSeg[3][1][CSCCh4][dCFEBBin4]++;
								if (inZMass) segNumStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[3][1][CSCCh4]->Fill(invMass);
							}
							if (CSCRg4==2) {passStationRingSeg[3][2]++;passStationRingChamberSeg[3][2][CSCCh4]++;passStationRingPtSeg[3][2][pTBin]++;passStationRingEtaSeg[3][2][etaBin4]++;passStationRingIsoSeg[3][2][isoBin]++;passStationRingPVSeg[3][2][pvBin]++;passStationRingILSeg[3][2][ilBin]++;passStationRingRunSeg[3][2][runBin]++;passStationRingChamberRunSeg[3][2][CSCCh4][runBin]++;passStationRingLCYSeg[3][2][lCYBin4]++;passStationRingLCSSeg[3][2][lCSBin4]++;passStationRingChamberLCYSeg[3][2][CSCCh4][lCYBin4]++;passStationRingChamberLCSSeg[3][2][CSCCh4][lCSBin4]++;passStationRingChamberLCWSeg[3][2][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBSeg[3][2][CSCCh4][dCFEBBin4]++;
								if (inZMass) segNumStationRingChamberRun[3][2][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[3][2][CSCCh4]->Fill(invMass);
							}
						}
						if (foundLCT4) {
							passGlobalLCT++;
							if (CSCRg4==1) {passStationRingLCT[3][1]++;passStationRingChamberLCT[3][1][CSCCh4]++;passStationRingPtLCT[3][1][pTBin]++;passStationRingEtaLCT[3][1][etaBin4]++;passStationRingIsoLCT[3][1][isoBin]++;passStationRingPVLCT[3][1][pvBin]++;passStationRingILLCT[3][1][ilBin]++;passStationRingRunLCT[3][1][runBin]++;passStationRingChamberRunLCT[3][1][CSCCh4][runBin]++;passStationRingLCYLCT[3][1][lC3YBin4]++;passStationRingLCSLCT[3][1][lC3SBin4]++;passStationRingChamberLCYLCT[3][1][CSCCh4][lCYBin4]++;passStationRingChamberLCSLCT[3][1][CSCCh4][lCSBin4]++;passStationRingChamberLCWLCT[3][1][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBLCT[3][1][CSCCh4][dCFEB3Bin4]++;
								if (inZMass) LCTNumStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
							}
							if (CSCRg4==2) {passStationRingLCT[3][2]++;passStationRingChamberLCT[3][2][CSCCh4]++;passStationRingPtLCT[3][2][pTBin]++;passStationRingEtaLCT[3][2][etaBin4]++;passStationRingIsoLCT[3][2][isoBin]++;passStationRingPVLCT[3][2][pvBin]++;passStationRingILLCT[3][2][ilBin]++;passStationRingRunLCT[3][2][runBin]++;passStationRingChamberRunLCT[3][2][CSCCh4][runBin]++;passStationRingLCYLCT[3][2][lC3YBin4]++;passStationRingLCSLCT[3][2][lC3SBin4]++;passStationRingChamberLCYLCT[3][2][CSCCh4][lCYBin4]++;passStationRingChamberLCSLCT[3][2][CSCCh4][lCSBin4]++;passStationRingChamberLCWLCT[3][2][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBLCT[3][2][CSCCh4][dCFEB3Bin4]++;
								if (inZMass) LCTNumStationRingChamberRun[3][2][CSCCh4]->Fill(run_number);
							}
						}
					}
				}
				if (CSCEndCapPlus){
					if (fiducial1||fiducial11){
						totGlobal++;
						if (CSCRg1==4&&fiducial11) {totStationRing[4][0]++;totStationRingChamber[4][0][CSCCh1]++;totStationRingPt[4][0][pTBin]++;totStationRingEta[4][0][etaBin]++;totStationRingIso[4][0][isoBin]++;totStationRingPV[4][0][pvBin]++;totStationRingIL[4][0][ilBin]++;totStationRingRun[4][0][runBin]++;totStationRingChamberRun[4][0][CSCCh1][runBin]++;totStationRingLCY[4][0][lCYBin1]++;totStationRingLCYLCT[4][0][lC3YBin1]++;totStationRingLCS[4][0][lCSBin1]++;totStationRingLCSLCT[4][0][lC3SBin1]++;totStationRingChamberLCY[4][0][CSCCh1][lCYBin1]++;totStationRingChamberLCS[4][0][CSCCh1][lCSBin1]++;totStationRingChamberLCW[4][0][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[4][0][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[4][0][CSCCh1][dCFEB3Bin1]++;
							//if (inZMass) segDenStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
							if (inZMass) segDenStationRingChamberRun[4][0][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][0][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][0][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][0][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[4][0][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[4][0][CSCCh1][iiLayer]++;
							}
							if (CSCCh1%2 == 0 ) {totStationRing[5][0]++;totStationRingChamber[5][0][CSCCh1]++;totStationRingPt[5][0][pTBin]++;totStationRingEta[5][0][etaBin]++;totStationRingIso[5][0][isoBin]++;totStationRingPV[5][0][pvBin]++;totStationRingIL[5][0][ilBin]++;totStationRingRun[5][0][runBin]++;totStationRingChamberRun[5][0][CSCCh1][runBin]++;totStationRingLCY[5][0][lCYBin1]++;totStationRingLCYLCT[5][0][lC3YBin1]++;totStationRingLCS[5][0][lCSBin1]++;totStationRingLCSLCT[5][0][lC3SBin1]++;}
							else {totStationRing[5][3]++;totStationRingChamber[5][3][CSCCh1]++;totStationRingPt[5][3][pTBin]++;totStationRingEta[5][3][etaBin]++;totStationRingIso[5][3][isoBin]++;totStationRingPV[5][3][pvBin]++;totStationRingIL[5][3][ilBin]++;totStationRingRun[5][3][runBin]++;totStationRingChamberRun[5][3][CSCCh1][runBin]++;totStationRingLCY[5][3][lCYBin1]++;totStationRingLCYLCT[5][3][lC3YBin1]++;totStationRingLCS[5][3][lCSBin1]++;totStationRingLCSLCT[5][3][lC3SBin1]++;}
						}
						if (CSCRg1==1&&fiducial11) {totStationRing[4][1]++;totStationRingChamber[4][1][CSCCh1]++;totStationRingPt[4][1][pTBin]++;totStationRingEta[4][1][etaBin]++;totStationRingIso[4][1][isoBin]++;totStationRingPV[4][1][pvBin]++;totStationRingIL[4][1][ilBin]++;totStationRingRun[4][1][runBin]++;totStationRingChamberRun[4][1][CSCCh1][runBin]++;totStationRingLCY[4][1][lCYBin1]++;totStationRingLCYLCT[4][1][lC3YBin1]++;totStationRingLCS[4][1][lCSBin1]++;totStationRingLCSLCT[4][1][lC3SBin1]++;totStationRingChamberLCY[4][1][CSCCh1][lCYBin1]++;totStationRingChamberLCS[4][1][CSCCh1][lCSBin1]++;totStationRingChamberLCW[4][1][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[4][1][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[4][1][CSCCh1][dCFEB3Bin1]++;
							//if (inZMass) segDenStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
							if (inZMass) segDenStationRingChamberRun[4][1][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][1][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][1][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][1][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[4][1][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[4][1][CSCCh1][iiLayer]++;
							}
							if (CSCCh1%2 == 0 ) {totStationRing[6][0]++;totStationRingChamber[6][0][CSCCh1]++;totStationRingPt[6][0][pTBin]++;totStationRingEta[6][0][etaBin]++;totStationRingIso[6][0][isoBin]++;totStationRingPV[6][0][pvBin]++;totStationRingIL[6][0][ilBin]++;totStationRingRun[6][0][runBin]++;totStationRingChamberRun[6][0][CSCCh1][runBin]++;totStationRingLCY[6][0][lCYBin1]++;totStationRingLCYLCT[6][0][lC3YBin1]++;totStationRingLCS[6][0][lCSBin1]++;totStationRingLCSLCT[6][0][lC3SBin1]++;}
							else {totStationRing[6][3]++;totStationRingChamber[6][3][CSCCh1]++;totStationRingPt[6][3][pTBin]++;totStationRingEta[6][3][etaBin]++;totStationRingIso[6][3][isoBin]++;totStationRingPV[6][3][pvBin]++;totStationRingIL[6][3][ilBin]++;totStationRingRun[6][3][runBin]++;totStationRingChamberRun[6][3][CSCCh1][runBin]++;totStationRingLCY[6][3][lCYBin1]++;totStationRingLCYLCT[6][3][lC3YBin1]++;totStationRingLCS[6][3][lCSBin1]++;totStationRingLCSLCT[6][3][lC3SBin1]++;}
						}
						if (CSCRg1==2) {totStationRing[4][2]++;totStationRingChamber[4][2][CSCCh1]++;totStationRingPt[4][2][pTBin]++;totStationRingEta[4][2][etaBin]++;totStationRingIso[4][2][isoBin]++;totStationRingPV[4][2][pvBin]++;totStationRingIL[4][2][ilBin]++;totStationRingRun[4][2][runBin]++;totStationRingChamberRun[4][2][CSCCh1][runBin]++;totStationRingLCY[4][2][lCYBin1]++;totStationRingLCYLCT[4][2][lC3YBin1]++;totStationRingLCS[4][2][lCSBin1]++;totStationRingLCSLCT[4][2][lC3SBin1]++;totStationRingChamberLCY[4][2][CSCCh1][lCYBin1]++;totStationRingChamberLCS[4][2][CSCCh1][lCSBin1]++;totStationRingChamberLCW[4][2][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[4][2][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[4][2][CSCCh1][dCFEB3Bin1]++;
							//if (inZMass) segDenStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
							if (inZMass) segDenStationRingChamberRun[4][2][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][2][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][2][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][2][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[4][2][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[4][2][CSCCh1][iiLayer]++;
							}
						}
						if (CSCRg1==3) {totStationRing[4][3]++;totStationRingChamber[4][3][CSCCh1]++;totStationRingPt[4][3][pTBin]++;totStationRingEta[4][3][etaBin]++;totStationRingIso[4][3][isoBin]++;totStationRingPV[4][3][pvBin]++;totStationRingIL[4][3][ilBin]++;totStationRingRun[4][3][runBin]++;totStationRingChamberRun[4][3][CSCCh1][runBin]++;totStationRingLCY[4][3][lCYBin1]++;totStationRingLCYLCT[4][3][lC3YBin1]++;totStationRingLCS[4][3][lCSBin1]++;totStationRingLCSLCT[4][3][lC3SBin1]++;totStationRingChamberLCY[4][3][CSCCh1][lCYBin1]++;totStationRingChamberLCS[4][3][CSCCh1][lCSBin1]++;totStationRingChamberLCW[4][3][CSCCh1][lCWBin1]++;totStationRingChamberDCFEB[4][3][CSCCh1][dCFEBBin1]++;totStationRingChamberDCFEBLCT[4][3][CSCCh1][dCFEB3Bin1]++;
							if (inZMass) segDenStationRingChamberRun[4][3][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][3][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][3][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][3][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[4][3][CSCCh1][iiLayer]++;
								if (foundHit1[iiLayer]) passStationRingChamberLayerSeg[4][3][CSCCh1][iiLayer]++;
							}
						}
						if (foundSeg1) {
							passGlobalSeg++;
							if (CSCRg1==4&&fiducial11) {passStationRingSeg[4][0]++;passStationRingChamberSeg[4][0][CSCCh1]++;passStationRingPtSeg[4][0][pTBin]++;passStationRingEtaSeg[4][0][etaBin]++;passStationRingIsoSeg[4][0][isoBin]++;passStationRingPVSeg[4][0][pvBin]++;passStationRingILSeg[4][0][ilBin]++;passStationRingRunSeg[4][0][runBin]++;passStationRingChamberRunSeg[4][0][CSCCh1][runBin]++;passStationRingLCYSeg[4][0][lCYBin1]++;passStationRingLCSSeg[4][0][lCSBin1]++;passStationRingChamberLCYSeg[4][0][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[4][0][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[4][0][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[4][0][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][0][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][0][CSCCh1]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passStationRingSeg[5][0]++;passStationRingChamberSeg[5][0][CSCCh1]++;passStationRingPtSeg[5][0][pTBin]++;passStationRingEtaSeg[5][0][etaBin]++;passStationRingIsoSeg[5][0][isoBin]++;passStationRingPVSeg[5][0][pvBin]++;passStationRingILSeg[5][0][ilBin]++;passStationRingRunSeg[5][0][runBin]++;passStationRingChamberRunSeg[5][0][CSCCh1][runBin]++;passStationRingLCYSeg[5][0][lCYBin1]++;passStationRingLCSSeg[5][0][lCSBin1]++;}
								else {passStationRingSeg[5][3]++;passStationRingChamberSeg[5][3][CSCCh1]++;passStationRingPtSeg[5][3][pTBin]++;passStationRingEtaSeg[5][3][etaBin]++;passStationRingIsoSeg[5][3][isoBin]++;passStationRingPVSeg[5][3][pvBin]++;passStationRingILSeg[5][3][ilBin]++;passStationRingRunSeg[5][3][runBin]++;passStationRingChamberRunSeg[5][3][CSCCh1][runBin]++;passStationRingLCYSeg[5][3][lCYBin1]++;passStationRingLCSSeg[5][3][lCSBin1]++;}
							}
							if (CSCRg1==1&&fiducial11) {passStationRingSeg[4][1]++;passStationRingChamberSeg[4][1][CSCCh1]++;passStationRingPtSeg[4][1][pTBin]++;passStationRingEtaSeg[4][1][etaBin]++;passStationRingIsoSeg[4][1][isoBin]++;passStationRingPVSeg[4][1][pvBin]++;passStationRingILSeg[4][1][ilBin]++;passStationRingRunSeg[4][1][runBin]++;passStationRingChamberRunSeg[4][1][CSCCh1][runBin]++;passStationRingLCYSeg[4][1][lCYBin1]++;passStationRingLCSSeg[4][1][lCSBin1]++;passStationRingChamberLCYSeg[4][1][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[4][1][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[4][1][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[4][1][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][1][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][1][CSCCh1]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passStationRingSeg[6][0]++;passStationRingChamberSeg[6][0][CSCCh1]++;passStationRingPtSeg[6][0][pTBin]++;passStationRingEtaSeg[6][0][etaBin]++;passStationRingIsoSeg[6][0][isoBin]++;passStationRingPVSeg[6][0][pvBin]++;passStationRingILSeg[6][0][ilBin]++;passStationRingRunSeg[6][0][runBin]++;passStationRingChamberRunSeg[6][0][CSCCh1][runBin]++;passStationRingLCYSeg[6][0][lCYBin1]++;passStationRingLCSSeg[6][0][lCSBin1]++;}
								else {passStationRingSeg[6][3]++;passStationRingChamberSeg[6][3][CSCCh1]++;passStationRingPtSeg[6][3][pTBin]++;passStationRingEtaSeg[6][3][etaBin]++;passStationRingIsoSeg[6][3][isoBin]++;passStationRingPVSeg[6][3][pvBin]++;passStationRingILSeg[6][3][ilBin]++;passStationRingRunSeg[6][3][runBin]++;passStationRingChamberRunSeg[6][3][CSCCh1][runBin]++;passStationRingLCYSeg[6][3][lCYBin1]++;passStationRingLCSSeg[6][3][lCSBin1]++;}
							}
							if (CSCRg1==2) {passStationRingSeg[4][2]++;passStationRingChamberSeg[4][2][CSCCh1]++;passStationRingPtSeg[4][2][pTBin]++;passStationRingEtaSeg[4][2][etaBin]++;passStationRingIsoSeg[4][2][isoBin]++;passStationRingPVSeg[4][2][pvBin]++;passStationRingILSeg[4][2][ilBin]++;passStationRingRunSeg[4][2][runBin]++;passStationRingChamberRunSeg[4][2][CSCCh1][runBin]++;passStationRingLCYSeg[4][2][lCYBin1]++;passStationRingLCSSeg[4][2][lCSBin1]++;passStationRingChamberLCYSeg[4][2][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[4][2][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[4][2][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[4][2][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][2][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][2][CSCCh1]->Fill(invMass);
							}
							if (CSCRg1==3) {passStationRingSeg[4][3]++;passStationRingChamberSeg[4][3][CSCCh1]++;passStationRingPtSeg[4][3][pTBin]++;passStationRingEtaSeg[4][3][etaBin]++;passStationRingIsoSeg[4][3][isoBin]++;passStationRingPVSeg[4][3][pvBin]++;passStationRingILSeg[4][3][ilBin]++;passStationRingRunSeg[4][3][runBin]++;passStationRingChamberRunSeg[4][3][CSCCh1][runBin]++;passStationRingLCYSeg[4][3][lCYBin1]++;passStationRingLCSSeg[4][3][lCSBin1]++;passStationRingChamberLCYSeg[4][3][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[4][3][CSCCh1][lCSBin1]++;passStationRingChamberLCWSeg[4][3][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBSeg[4][3][CSCCh1][dCFEBBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][3][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][3][CSCCh1]->Fill(invMass);
							}
						}
						if (foundLCT1) {
							passGlobalLCT++;
							if (CSCRg1==4&&fiducial11) {passStationRingLCT[4][0]++;passStationRingChamberLCT[4][0][CSCCh1]++;passStationRingPtLCT[4][0][pTBin]++;passStationRingEtaLCT[4][0][etaBin]++;passStationRingIsoLCT[4][0][isoBin]++;passStationRingPVLCT[4][0][pvBin]++;passStationRingILLCT[4][0][ilBin]++;passStationRingRunLCT[4][0][runBin]++;passStationRingChamberRunLCT[4][0][CSCCh1][runBin]++;passStationRingLCYLCT[4][0][lC3YBin1]++;passStationRingLCSLCT[4][0][lC3SBin1]++;passStationRingChamberLCYLCT[4][0][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[4][0][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[4][0][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[4][0][CSCCh1][dCFEB3Bin1]++;
								if (inZMass) LCTNumStationRingChamberRun[4][0][CSCCh1]->Fill(run_number);		    
								if (CSCCh1%2 == 0 ) {passStationRingLCT[5][0]++;passStationRingChamberLCT[5][0][CSCCh1]++;passStationRingPtLCT[5][0][pTBin]++;passStationRingEtaLCT[5][0][etaBin]++;passStationRingIsoLCT[5][0][isoBin]++;passStationRingPVLCT[5][0][pvBin]++;passStationRingILLCT[5][0][ilBin]++;passStationRingRunLCT[5][0][runBin]++;passStationRingChamberRunLCT[5][0][CSCCh1][runBin]++;passStationRingLCYLCT[5][0][lC3YBin1]++;passStationRingLCSLCT[5][0][lC3SBin1]++;}
								else {passStationRingLCT[5][3]++;passStationRingChamberLCT[5][3][CSCCh1]++;passStationRingPtLCT[5][3][pTBin]++;passStationRingEtaLCT[5][3][etaBin]++;;passStationRingIsoLCT[5][3][isoBin]++;passStationRingPVLCT[5][3][pvBin]++;passStationRingILLCT[5][3][ilBin]++;passStationRingRunLCT[5][3][runBin]++;passStationRingChamberRunLCT[5][3][CSCCh1][runBin]++;passStationRingLCYLCT[5][3][lC3YBin1]++;passStationRingLCSLCT[5][3][lC3SBin1]++;}
							}
							if (CSCRg1==1&&fiducial11) {passStationRingLCT[4][1]++;passStationRingChamberLCT[4][1][CSCCh1]++;passStationRingPtLCT[4][1][pTBin]++;passStationRingEtaLCT[4][1][etaBin]++;passStationRingIsoLCT[4][1][isoBin]++;passStationRingPVLCT[4][1][pvBin]++;passStationRingILLCT[4][1][ilBin]++;passStationRingRunLCT[4][1][runBin]++;passStationRingChamberRunLCT[4][1][CSCCh1][runBin]++;passStationRingLCYLCT[4][1][lC3YBin1]++;passStationRingLCSLCT[4][1][lC3SBin1]++;passStationRingChamberLCYLCT[4][1][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[4][1][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[4][1][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[4][1][CSCCh1][dCFEB3Bin1]++;
								if (inZMass) LCTNumStationRingChamberRun[4][1][CSCCh1]->Fill(run_number);		    
								if (CSCCh1%2 == 0 ) {passStationRingLCT[6][0]++;passStationRingChamberLCT[6][0][CSCCh1]++;passStationRingPtLCT[6][0][pTBin]++;passStationRingEtaLCT[6][0][etaBin]++;passStationRingIsoLCT[6][0][isoBin]++;passStationRingPVLCT[6][0][pvBin]++;passStationRingILLCT[6][0][ilBin]++;passStationRingRunLCT[6][0][runBin]++;passStationRingChamberRunLCT[6][0][CSCCh1][runBin]++;passStationRingLCYLCT[6][0][lC3YBin1]++;passStationRingLCSLCT[6][0][lC3SBin1]++;}
								else {passStationRingLCT[6][3]++;passStationRingChamberLCT[6][3][CSCCh1]++;passStationRingPtLCT[6][3][pTBin]++;passStationRingEtaLCT[6][3][etaBin]++;passStationRingIsoLCT[6][3][isoBin]++;passStationRingPVLCT[6][3][pvBin]++;passStationRingILLCT[6][3][ilBin]++;passStationRingRunLCT[6][3][runBin]++;passStationRingChamberRunLCT[6][3][CSCCh1][runBin]++;passStationRingLCYLCT[6][3][lC3YBin1]++;passStationRingLCSLCT[6][3][lC3SBin1]++;}
							}
							if (CSCRg1==2) {passStationRingLCT[4][2]++;passStationRingChamberLCT[4][2][CSCCh1]++;passStationRingPtLCT[4][2][pTBin]++;passStationRingEtaLCT[4][2][etaBin]++;passStationRingIsoLCT[4][2][isoBin]++;passStationRingPVLCT[4][2][pvBin]++;passStationRingILLCT[4][2][ilBin]++;passStationRingRunLCT[4][2][runBin]++;passStationRingChamberRunLCT[4][2][CSCCh1][runBin]++;passStationRingLCYLCT[4][2][lC3YBin1]++;passStationRingLCSLCT[4][2][lC3SBin1]++;passStationRingChamberLCYLCT[4][2][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[4][2][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[4][2][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[4][2][CSCCh1][dCFEB3Bin1]++;
								if (inZMass) LCTNumStationRingChamberRun[4][2][CSCCh1]->Fill(run_number);
							}
							if (CSCRg1==3) {passStationRingLCT[4][3]++;passStationRingChamberLCT[4][3][CSCCh1]++;passStationRingPtLCT[4][3][pTBin]++;passStationRingEtaLCT[4][3][etaBin]++;passStationRingIsoLCT[4][3][isoBin]++;passStationRingPVLCT[4][3][pvBin]++;passStationRingILLCT[4][3][ilBin]++;passStationRingRunLCT[4][3][runBin]++;passStationRingChamberRunLCT[4][3][CSCCh1][runBin]++;passStationRingLCYLCT[4][3][lC3YBin1]++;passStationRingLCSLCT[4][3][lC3SBin1]++;passStationRingChamberLCYLCT[4][3][CSCCh1][lCYBin1]++;passStationRingChamberLCSLCT[4][3][CSCCh1][lCSBin1]++;passStationRingChamberLCWLCT[4][3][CSCCh1][lCWBin1]++;passStationRingChamberDCFEBLCT[4][3][CSCCh1][dCFEB3Bin1]++;
								if (inZMass) LCTNumStationRingChamberRun[4][3][CSCCh1]->Fill(run_number);
							}
						}
					}
					if (fiducial2){
						totGlobal++;
						if (CSCRg2==1) {totStationRing[5][1]++;totStationRingChamber[5][1][CSCCh2]++;totStationRingPt[5][1][pTBin]++;totStationRingEta[5][1][etaBin2]++;totStationRingIso[5][1][isoBin]++;totStationRingPV[5][1][pvBin]++;totStationRingIL[5][1][ilBin]++;totStationRingRun[5][1][runBin]++;totStationRingChamberRun[5][1][CSCCh2][runBin]++;totStationRingLCY[5][1][lCYBin2]++;totStationRingLCYLCT[5][1][lC3YBin2]++;totStationRingLCS[5][1][lCSBin2]++;totStationRingLCSLCT[5][1][lC3SBin2]++;totStationRingChamberLCY[5][1][CSCCh2][lCYBin2]++;totStationRingChamberLCS[5][1][CSCCh2][lCSBin2]++;totStationRingChamberLCW[5][1][CSCCh2][lCWBin2]++;totStationRingChamberDCFEB[5][1][CSCCh2][dCFEBBin2]++;totStationRingChamberDCFEBLCT[5][1][CSCCh2][dCFEB3Bin2]++;
							if (inZMass) segDenStationRingChamberRun[5][1][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[5][1][CSCCh2]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[5][1][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[5][1][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[5][1][CSCCh2][iiLayer]++;
								if (foundHit2[iiLayer]) passStationRingChamberLayerSeg[5][1][CSCCh2][iiLayer]++;
							}
						}
						if (CSCRg2==2) {totStationRing[5][2]++;totStationRingChamber[5][2][CSCCh2]++;totStationRingPt[5][2][pTBin]++;totStationRingEta[5][2][etaBin2]++;totStationRingIso[5][2][isoBin]++;totStationRingPV[5][2][pvBin]++;totStationRingIL[5][2][ilBin]++;totStationRingRun[5][2][runBin]++;totStationRingChamberRun[5][2][CSCCh2][runBin]++;totStationRingLCY[5][2][lCYBin2]++;totStationRingLCYLCT[5][2][lC3YBin2]++;totStationRingLCS[5][2][lCSBin2]++;totStationRingLCSLCT[5][2][lC3SBin2]++;totStationRingChamberLCY[5][2][CSCCh2][lCYBin2]++;totStationRingChamberLCS[5][2][CSCCh2][lCSBin2]++;totStationRingChamberLCW[5][2][CSCCh2][lCWBin2]++;totStationRingChamberDCFEB[5][2][CSCCh2][dCFEBBin2]++;totStationRingChamberDCFEBLCT[5][2][CSCCh2][dCFEB3Bin2]++;
							if (inZMass) segDenStationRingChamberRun[5][2][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[5][2][CSCCh2]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[5][2][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[5][2][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[5][2][CSCCh2][iiLayer]++;
								if (foundHit2[iiLayer]) passStationRingChamberLayerSeg[5][2][CSCCh2][iiLayer]++;
							}
						}
						if (foundSeg2) {
							passGlobalSeg++;
							if (CSCRg2==1) {passStationRingSeg[5][1]++;passStationRingChamberSeg[5][1][CSCCh2]++;passStationRingPtSeg[5][1][pTBin]++;passStationRingEtaSeg[5][1][etaBin2]++;passStationRingIsoSeg[5][1][isoBin]++;passStationRingPVSeg[5][1][pvBin]++;passStationRingILSeg[5][1][ilBin]++;passStationRingRunSeg[5][1][runBin]++;passStationRingChamberRunSeg[5][1][CSCCh2][runBin]++;passStationRingLCYSeg[5][1][lCYBin2]++;passStationRingLCSSeg[5][1][lCSBin2]++;passStationRingChamberLCYSeg[5][1][CSCCh2][lCYBin2]++;passStationRingChamberLCSSeg[5][1][CSCCh2][lCSBin2]++;passStationRingChamberLCWSeg[5][1][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBSeg[5][1][CSCCh2][dCFEBBin2]++;
								if (inZMass) segNumStationRingChamberRun[5][1][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[5][1][CSCCh2]->Fill(invMass);
							}
							if (CSCRg2==2) {passStationRingSeg[5][2]++;passStationRingChamberSeg[5][2][CSCCh2]++;passStationRingPtSeg[5][2][pTBin]++;passStationRingEtaSeg[5][2][etaBin2]++;passStationRingIsoSeg[5][2][isoBin]++;passStationRingPVSeg[5][2][pvBin]++;passStationRingILSeg[5][2][ilBin]++;passStationRingRunSeg[5][2][runBin]++;passStationRingChamberRunSeg[5][2][CSCCh2][runBin]++;passStationRingLCYSeg[5][2][lCYBin2]++;passStationRingLCSSeg[5][2][lCSBin2]++;passStationRingChamberLCYSeg[5][2][CSCCh2][lCYBin2]++;passStationRingChamberLCSSeg[5][2][CSCCh2][lCSBin2]++;passStationRingChamberLCWSeg[5][2][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBSeg[5][2][CSCCh2][dCFEBBin2]++;
								if (inZMass) segNumStationRingChamberRun[5][2][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[5][2][CSCCh2]->Fill(invMass);
							}
						}
						if (foundLCT2) {
							passGlobalLCT++;
							if (CSCRg2==1) {passStationRingLCT[5][1]++;passStationRingChamberLCT[5][1][CSCCh2]++;passStationRingPtLCT[5][1][pTBin]++;passStationRingEtaLCT[5][1][etaBin2]++;passStationRingIsoLCT[5][1][isoBin]++;passStationRingPVLCT[5][1][pvBin]++;passStationRingILLCT[5][1][ilBin]++;passStationRingRunLCT[5][1][runBin]++;passStationRingChamberRunLCT[5][1][CSCCh2][runBin]++;passStationRingLCYLCT[5][1][lC3YBin2]++;passStationRingLCSLCT[5][1][lC3SBin2]++;passStationRingChamberLCYLCT[5][1][CSCCh2][lCYBin2]++;passStationRingChamberLCSLCT[5][1][CSCCh2][lCSBin2]++;passStationRingChamberLCWLCT[5][1][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBLCT[5][1][CSCCh2][dCFEB3Bin2]++;
								if (inZMass) LCTNumStationRingChamberRun[5][1][CSCCh2]->Fill(run_number);
							}
							if (CSCRg2==2) {passStationRingLCT[5][2]++;passStationRingChamberLCT[5][2][CSCCh2]++;passStationRingPtLCT[5][2][pTBin]++;passStationRingEtaLCT[5][2][etaBin2]++;passStationRingIsoLCT[5][2][isoBin]++;passStationRingPVLCT[5][2][pvBin]++;passStationRingILLCT[5][2][ilBin]++;passStationRingRunLCT[5][2][runBin]++;passStationRingChamberRunLCT[5][2][CSCCh2][runBin]++;passStationRingLCYLCT[5][2][lC3YBin2]++;passStationRingLCSLCT[5][2][lC3SBin2]++;passStationRingChamberLCYLCT[5][2][CSCCh2][lCYBin2]++;passStationRingChamberLCSLCT[5][2][CSCCh2][lCSBin2]++;passStationRingChamberLCWLCT[5][2][CSCCh2][lCWBin2]++;passStationRingChamberDCFEBLCT[5][2][CSCCh2][dCFEB3Bin2]++;
								if (inZMass) LCTNumStationRingChamberRun[5][2][CSCCh2]->Fill(run_number);
							}
						}
					}
					if (fiducial3){
						totGlobal++;
						if (CSCRg3==1) {totStationRing[6][1]++;totStationRingChamber[6][1][CSCCh3]++;totStationRingPt[6][1][pTBin]++;totStationRingEta[6][1][etaBin3]++;totStationRingIso[6][1][isoBin]++;totStationRingPV[6][1][pvBin]++;totStationRingIL[6][1][ilBin]++;totStationRingRun[6][1][runBin]++;totStationRingChamberRun[6][1][CSCCh3][runBin]++;totStationRingLCY[6][1][lCYBin3]++;totStationRingLCYLCT[6][1][lC3YBin3]++;totStationRingLCS[6][1][lCSBin3]++;totStationRingLCSLCT[6][1][lC3SBin3]++;totStationRingChamberLCY[6][1][CSCCh3][lCYBin3]++;totStationRingChamberLCS[6][1][CSCCh3][lCSBin3]++;totStationRingChamberLCW[6][1][CSCCh3][lCWBin3]++;totStationRingChamberDCFEB[6][1][CSCCh3][dCFEBBin3]++;totStationRingChamberDCFEBLCT[6][1][CSCCh3][dCFEB3Bin3]++;
							if (inZMass) segDenStationRingChamberRun[6][1][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[6][1][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[6][1][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[6][1][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[6][1][CSCCh3][iiLayer]++;
								if (foundHit3[iiLayer]) passStationRingChamberLayerSeg[6][1][CSCCh3][iiLayer]++;
							}
						}
						if (CSCRg3==2) {totStationRing[6][2]++;totStationRingChamber[6][2][CSCCh3]++;totStationRingPt[6][2][pTBin]++;totStationRingEta[6][2][etaBin3]++;totStationRingIso[6][2][isoBin]++;totStationRingPV[6][2][pvBin]++;totStationRingIL[6][2][ilBin]++;totStationRingRun[6][2][runBin]++;totStationRingChamberRun[6][2][CSCCh3][runBin]++;totStationRingLCY[6][2][lCYBin3]++;totStationRingLCYLCT[6][2][lC3YBin3]++;totStationRingLCS[6][2][lCSBin3]++;totStationRingLCSLCT[6][2][lC3SBin3]++;totStationRingChamberLCY[6][2][CSCCh3][lCYBin3]++;totStationRingChamberLCS[6][2][CSCCh3][lCSBin3]++;totStationRingChamberLCW[6][2][CSCCh3][lCWBin3]++;totStationRingChamberDCFEB[6][2][CSCCh3][dCFEBBin3]++;totStationRingChamberDCFEBLCT[6][2][CSCCh3][dCFEB3Bin3]++;
							if (inZMass) segDenStationRingChamberRun[6][2][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[6][2][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[6][2][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[6][2][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[6][2][CSCCh3][iiLayer]++;
								if (foundHit3[iiLayer]) passStationRingChamberLayerSeg[6][2][CSCCh3][iiLayer]++;
							}
						}
						if (foundSeg3) {
							passGlobalSeg++;
							if (CSCRg3==1) {passStationRingSeg[6][1]++;passStationRingChamberSeg[6][1][CSCCh3]++;passStationRingPtSeg[6][1][pTBin]++;passStationRingEtaSeg[6][1][etaBin3]++;passStationRingIsoSeg[6][1][isoBin]++;passStationRingPVSeg[6][1][pvBin]++;passStationRingILSeg[6][1][ilBin]++;passStationRingRunSeg[6][1][runBin]++;passStationRingChamberRunSeg[6][1][CSCCh3][runBin]++;passStationRingLCYSeg[6][1][lCYBin3]++;passStationRingLCSSeg[6][1][lCSBin3]++;passStationRingChamberLCYSeg[6][1][CSCCh3][lCYBin3]++;passStationRingChamberLCSSeg[6][1][CSCCh3][lCSBin3]++;passStationRingChamberLCWSeg[6][1][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBSeg[6][1][CSCCh3][dCFEBBin3]++;
								if (inZMass) segNumStationRingChamberRun[6][1][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[6][1][CSCCh3]->Fill(invMass);
							}
							if (CSCRg3==2) {passStationRingSeg[6][2]++;passStationRingChamberSeg[6][2][CSCCh3]++;passStationRingPtSeg[6][2][pTBin]++;passStationRingEtaSeg[6][2][etaBin3]++;passStationRingIsoSeg[6][2][isoBin]++;passStationRingPVSeg[6][2][pvBin]++;passStationRingILSeg[6][2][ilBin]++;passStationRingRunSeg[6][2][runBin]++;passStationRingChamberRunSeg[6][2][CSCCh3][runBin]++;passStationRingLCYSeg[6][2][lCYBin3]++;passStationRingLCSSeg[6][2][lCSBin3]++;passStationRingChamberLCYSeg[6][2][CSCCh3][lCYBin3]++;passStationRingChamberLCSSeg[6][2][CSCCh3][lCSBin3]++;passStationRingChamberLCWSeg[6][2][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBSeg[6][2][CSCCh3][dCFEBBin3]++;
								if (inZMass) segNumStationRingChamberRun[6][2][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[6][2][CSCCh3]->Fill(invMass);
							}
						}
						if (foundLCT3) {
							passGlobalLCT++;
							if (CSCRg3==1) {passStationRingLCT[6][1]++;passStationRingChamberLCT[6][1][CSCCh3]++;passStationRingPtLCT[6][1][pTBin]++;passStationRingEtaLCT[6][1][etaBin3]++;passStationRingIsoLCT[6][1][isoBin]++;passStationRingPVLCT[6][1][pvBin]++;passStationRingILLCT[6][1][ilBin]++;passStationRingRunLCT[6][1][runBin]++;passStationRingChamberRunLCT[6][1][CSCCh3][runBin]++;passStationRingLCYLCT[6][1][lC3YBin3]++;passStationRingLCSLCT[6][1][lC3SBin3]++;passStationRingChamberLCYLCT[6][1][CSCCh3][lCYBin3]++;passStationRingChamberLCSLCT[6][1][CSCCh3][lCSBin3]++;passStationRingChamberLCWLCT[6][1][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBLCT[6][1][CSCCh3][dCFEB3Bin3]++;
								if (inZMass) LCTNumStationRingChamberRun[6][1][CSCCh3]->Fill(run_number);
							}
							if (CSCRg3==2) {passStationRingLCT[6][2]++;passStationRingChamberLCT[6][2][CSCCh3]++;passStationRingPtLCT[6][2][pTBin]++;passStationRingEtaLCT[6][2][etaBin3]++;passStationRingIsoLCT[6][2][isoBin]++;passStationRingPVLCT[6][2][pvBin]++;passStationRingILLCT[6][2][ilBin]++;passStationRingRunLCT[6][2][runBin]++;passStationRingChamberRunLCT[6][2][CSCCh3][runBin]++;passStationRingLCYLCT[6][2][lC3YBin3]++;passStationRingLCSLCT[6][2][lC3SBin3]++;passStationRingChamberLCYLCT[6][2][CSCCh3][lCYBin3]++;passStationRingChamberLCSLCT[6][2][CSCCh3][lCSBin3]++;passStationRingChamberLCWLCT[6][2][CSCCh3][lCWBin3]++;passStationRingChamberDCFEBLCT[6][2][CSCCh3][dCFEB3Bin3]++;
								if (inZMass) LCTNumStationRingChamberRun[6][2][CSCCh3]->Fill(run_number);
							}
						}
					}
					if (fiducial4){
						totGlobal++;
						if (CSCRg4==1) {totStationRing[7][1]++;totStationRingChamber[7][1][CSCCh4]++;totStationRingPt[7][1][pTBin]++;totStationRingEta[7][1][etaBin4]++;totStationRingIso[7][1][isoBin]++;totStationRingPV[7][1][pvBin]++;totStationRingIL[7][1][ilBin]++;totStationRingRun[7][1][runBin]++;totStationRingChamberRun[7][1][CSCCh4][runBin]++;totStationRingLCY[7][1][lCYBin4]++;totStationRingLCYLCT[7][1][lC3YBin4]++;totStationRingLCS[7][1][lCSBin4]++;totStationRingLCSLCT[7][1][lC3SBin4]++;totStationRingChamberLCY[7][1][CSCCh4][lCYBin4]++;totStationRingChamberLCS[7][1][CSCCh4][lCSBin4]++;totStationRingChamberLCW[7][1][CSCCh4][lCWBin4]++;totStationRingChamberDCFEB[7][1][CSCCh4][dCFEBBin4]++;totStationRingChamberDCFEBLCT[7][1][CSCCh4][dCFEB3Bin4]++;
							if (inZMass) segDenStationRingChamberRun[7][1][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[7][1][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[7][1][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[7][1][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[7][1][CSCCh4][iiLayer]++;
								if (foundHit4[iiLayer]) passStationRingChamberLayerSeg[7][1][CSCCh4][iiLayer]++;
							}
						}
						if (CSCRg4==2) {totStationRing[7][2]++;totStationRingChamber[7][2][CSCCh4]++;totStationRingPt[7][2][pTBin]++;totStationRingEta[7][2][etaBin4]++;totStationRingIso[7][2][isoBin]++;totStationRingPV[7][2][pvBin]++;totStationRingIL[7][2][ilBin]++;totStationRingRun[7][2][runBin]++;totStationRingChamberRun[7][2][CSCCh4][runBin]++;totStationRingLCY[7][2][lCYBin4]++;totStationRingLCYLCT[7][2][lC3YBin4]++;totStationRingLCS[7][2][lCSBin4]++;totStationRingLCSLCT[7][2][lC3SBin4]++;totStationRingChamberLCY[7][2][CSCCh4][lCYBin4]++;totStationRingChamberLCS[7][2][CSCCh4][lCSBin4]++;totStationRingChamberLCW[7][2][CSCCh4][lCWBin4]++;totStationRingChamberDCFEB[7][2][CSCCh4][dCFEBBin4]++;totStationRingChamberDCFEBLCT[7][2][CSCCh4][dCFEB3Bin4]++;
							if (inZMass) segDenStationRingChamberRun[7][2][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[7][2][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[7][2][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[7][2][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
							for (Int_t iiLayer = 0; iiLayer < 6; iiLayer++){
								totStationRingChamberLayer[7][2][CSCCh4][iiLayer]++;
								if (foundHit4[iiLayer]) passStationRingChamberLayerSeg[7][2][CSCCh4][iiLayer]++;
							}
						}
						if (foundSeg4) {
							passGlobalSeg++;
							if (CSCRg4==1) {passStationRingSeg[7][1]++;passStationRingChamberSeg[7][1][CSCCh4]++;passStationRingPtSeg[7][1][pTBin]++;passStationRingEtaSeg[7][1][etaBin4]++;passStationRingIsoSeg[7][1][isoBin]++;passStationRingPVSeg[7][1][pvBin]++;passStationRingILSeg[7][1][ilBin]++;passStationRingRunSeg[7][1][runBin]++;passStationRingChamberRunSeg[7][1][CSCCh4][runBin]++;passStationRingLCYSeg[7][1][lCYBin4]++;passStationRingLCSSeg[7][1][lCSBin4]++;passStationRingChamberLCYSeg[7][1][CSCCh4][lCYBin4]++;passStationRingChamberLCSSeg[7][1][CSCCh4][lCSBin4]++;passStationRingChamberLCWSeg[7][1][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBSeg[7][1][CSCCh4][dCFEBBin4]++;
								if (inZMass) segNumStationRingChamberRun[7][1][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[7][1][CSCCh4]->Fill(invMass);
							}
							if (CSCRg4==2) {passStationRingSeg[7][2]++;passStationRingChamberSeg[7][2][CSCCh4]++;passStationRingPtSeg[7][2][pTBin]++;passStationRingEtaSeg[7][2][etaBin4]++;passStationRingIsoSeg[7][2][isoBin]++;passStationRingPVSeg[7][2][pvBin]++;passStationRingILSeg[7][2][ilBin]++;passStationRingRunSeg[7][2][runBin]++;passStationRingChamberRunSeg[7][2][CSCCh4][runBin]++;passStationRingLCYSeg[7][2][lCYBin4]++;passStationRingLCSSeg[7][2][lCSBin4]++;passStationRingChamberLCYSeg[7][2][CSCCh1][lCYBin1]++;passStationRingChamberLCSSeg[7][2][CSCCh4][lCSBin4]++;passStationRingChamberLCWSeg[7][2][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBSeg[7][2][CSCCh4][dCFEBBin4]++;
								if (inZMass) segNumStationRingChamberRun[7][2][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[7][2][CSCCh4]->Fill(invMass);
							}
						}
						if (foundLCT4) {
							passGlobalLCT++;
							if (CSCRg4==1) {passStationRingLCT[7][1]++;passStationRingChamberLCT[7][1][CSCCh4]++;passStationRingPtLCT[7][1][pTBin]++;passStationRingEtaLCT[7][1][etaBin4]++;passStationRingIsoLCT[7][1][isoBin]++;passStationRingPVLCT[7][1][pvBin]++;passStationRingILLCT[7][1][ilBin]++;passStationRingRunLCT[7][1][runBin]++;passStationRingChamberRunLCT[7][1][CSCCh4][runBin]++;passStationRingLCYLCT[7][1][lC3YBin4]++;passStationRingLCSLCT[7][1][lC3SBin4]++;passStationRingChamberLCYLCT[7][1][CSCCh4][lCYBin4]++;passStationRingChamberLCSLCT[7][1][CSCCh4][lCSBin4]++;passStationRingChamberLCWLCT[7][1][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBLCT[7][1][CSCCh4][dCFEB3Bin4]++;
								if (inZMass) LCTNumStationRingChamberRun[7][1][CSCCh4]->Fill(run_number);
							}
							if (CSCRg4==2) {passStationRingLCT[7][2]++;passStationRingChamberLCT[7][2][CSCCh4]++;passStationRingPtLCT[7][2][pTBin]++;passStationRingEtaLCT[7][2][etaBin4]++;passStationRingIsoLCT[7][2][isoBin]++;passStationRingPVLCT[7][2][pvBin]++;passStationRingILLCT[7][2][ilBin]++;passStationRingRunLCT[7][2][runBin]++;passStationRingChamberRunLCT[7][2][CSCCh4][runBin]++;passStationRingLCYLCT[7][2][lC3YBin4]++;passStationRingLCSLCT[7][2][lC3SBin4]++;passStationRingChamberLCYLCT[7][2][CSCCh4][lCYBin4]++;passStationRingChamberLCSLCT[7][2][CSCCh4][lCSBin4]++;passStationRingChamberLCWLCT[7][2][CSCCh4][lCWBin4]++;passStationRingChamberDCFEBLCT[7][2][CSCCh4][dCFEB3Bin4]++;
								if (inZMass) LCTNumStationRingChamberRun[7][2][CSCCh4]->Fill(run_number);
							}
						}
					}

				}


			} // end Zmass

			// Sidebands
			if (inZMassLowSideBand||inZMassHighSideBand) {

				if (!CSCEndCapPlus){
					if (fiducial1||fiducial11){
						totSBGlobal++;
						if (CSCRg1==4&&fiducial11) {totSBStationRing[0][0]++;totSBStationRingChamber[0][0][CSCCh1]++;totSBStationRingPt[0][0][pTBin]++;totSBStationRingEta[0][0][etaBin]++;totSBStationRingIso[0][0][isoBin]++;totSBStationRingPV[0][0][pvBin]++;totSBStationRingIL[0][0][ilBin]++;totSBStationRingRun[0][0][runBin]++;totSBStationRingChamberRun[0][0][CSCCh1][runBin]++;totSBStationRingLCY[0][0][lCYBin1]++;totSBStationRingLCYLCT[0][0][lC3YBin1]++;totSBStationRingLCS[0][0][lCSBin1]++;totSBStationRingLCSLCT[0][0][lC3SBin1]++;totSBStationRingChamberLCY[0][0][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[0][0][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[0][0][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[0][0][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][0][CSCCh1]->Fill(invMass);
							zMassSegDenStationRingPV[0][0][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][0][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][0][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);
								yySegStationRing[0][0]->Fill(CSCSegyLc1,CSCTTyLc1);}
							if (CSCCh1%2 == 0 ) {totSBStationRing[1][0]++;totSBStationRingChamber[1][0][CSCCh1]++;totSBStationRingPt[1][0][pTBin]++;totSBStationRingEta[1][0][etaBin]++;totSBStationRingIso[1][0][isoBin]++;totSBStationRingPV[1][0][pvBin]++;totSBStationRingIL[1][0][ilBin]++;totSBStationRingRun[1][0][runBin]++;totSBStationRingChamberRun[1][0][CSCCh1][runBin]++;totSBStationRingLCY[1][0][lCYBin1]++;totSBStationRingLCYLCT[1][0][lC3YBin1]++;totSBStationRingLCS[1][0][lCSBin1]++;totSBStationRingLCSLCT[1][0][lC3SBin1]++;yySegStationRing[1][0]->Fill(CSCSegyLc1,CSCTTyLc1);}
							else {totSBStationRing[1][3]++;totSBStationRingChamber[1][3][CSCCh1]++;totSBStationRingPt[1][3][pTBin]++;totSBStationRingEta[1][3][etaBin]++;totSBStationRingIso[1][3][isoBin]++;totSBStationRingPV[1][3][pvBin]++;totSBStationRingIL[1][3][ilBin]++;totSBStationRingRun[1][3][runBin]++;totSBStationRingChamberRun[1][3][CSCCh1][runBin]++;totSBStationRingLCY[1][3][lCYBin1]++;totSBStationRingLCYLCT[1][3][lC3YBin1]++;totSBStationRingLCS[1][3][lCSBin1]++;totSBStationRingLCSLCT[1][3][lC3SBin1]++;yySegStationRing[1][3]->Fill(CSCSegyLc1,CSCTTyLc1);}
						}
						if (CSCRg1==1&&fiducial11) {totSBStationRing[0][1]++;totSBStationRingChamber[0][1][CSCCh1]++;totSBStationRingPt[0][1][pTBin]++;totSBStationRingEta[0][1][etaBin]++;totSBStationRingIso[0][1][isoBin]++;totSBStationRingPV[0][1][pvBin]++;totSBStationRingIL[0][1][ilBin]++;totSBStationRingRun[0][1][runBin]++;totSBStationRingChamberRun[0][1][CSCCh1][runBin]++;totSBStationRingLCY[0][1][lCYBin1]++;totSBStationRingLCYLCT[0][1][lC3YBin1]++;totSBStationRingLCS[0][1][lCSBin1]++;totSBStationRingLCSLCT[0][1][lC3SBin1]++;totSBStationRingChamberLCY[0][1][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[0][1][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[0][1][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[0][1][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][1][CSCCh1]->Fill(invMass);
							zMassSegDenStationRingPV[0][1][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][1][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][1][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);
								yySegStationRing[0][1]->Fill(CSCSegyLc1,CSCTTyLc1);}
							if (CSCCh1%2 == 0 )  {totSBStationRing[2][0]++;totSBStationRingChamber[2][0][CSCCh1]++;totSBStationRingPt[2][0][pTBin]++;totSBStationRingEta[2][0][etaBin]++;totSBStationRingIso[2][0][isoBin]++;totSBStationRingPV[2][0][pvBin]++;totSBStationRingIL[2][0][ilBin]++;totSBStationRingRun[2][0][runBin]++;totSBStationRingChamberRun[2][0][CSCCh1][runBin]++;totSBStationRingLCY[2][0][lCYBin1]++;totSBStationRingLCYLCT[2][0][lC3YBin1]++;totSBStationRingLCS[2][0][lCSBin1]++;totSBStationRingLCSLCT[2][0][lC3SBin1]++;yySegStationRing[2][0]->Fill(CSCSegyLc1,CSCTTyLc1);}
							else {totSBStationRing[2][3]++;totSBStationRingChamber[2][3][CSCCh1]++;totSBStationRingPt[2][3][pTBin]++;totSBStationRingEta[2][3][etaBin]++;totSBStationRingIso[2][3][isoBin]++;totSBStationRingPV[2][3][pvBin]++;totSBStationRingIL[2][3][ilBin]++;totSBStationRingRun[2][3][runBin]++;totSBStationRingChamberRun[2][3][CSCCh1][runBin]++;totSBStationRingLCY[2][3][lCYBin1]++;totSBStationRingLCYLCT[2][3][lC3YBin1]++;totSBStationRingLCS[2][3][lCSBin1]++;totSBStationRingLCSLCT[2][3][lC3SBin1]++;yySegStationRing[2][3]->Fill(CSCSegyLc1,CSCTTyLc1);}
						}
						if (CSCRg1==2) {totSBStationRing[0][2]++;totSBStationRingChamber[0][2][CSCCh1]++;totSBStationRingPt[0][2][pTBin]++;totSBStationRingEta[0][2][etaBin]++;totSBStationRingIso[0][2][isoBin]++;totSBStationRingPV[0][2][pvBin]++;totSBStationRingIL[0][2][ilBin]++;totSBStationRingRun[0][2][runBin]++;totSBStationRingChamberRun[0][2][CSCCh1][runBin]++;totSBStationRingLCY[0][2][lCYBin1]++;totSBStationRingLCYLCT[0][2][lC3YBin1]++;totSBStationRingLCS[0][2][lCSBin1]++;totSBStationRingLCSLCT[0][2][lC3SBin1]++;totSBStationRingChamberLCY[0][2][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[0][2][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[0][2][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[0][2][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][2][CSCCh1]->Fill(invMass);
							zMassSegDenStationRingPV[0][2][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][2][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][2][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
						}
						if (CSCRg1==3) {totSBStationRing[0][3]++;totSBStationRingChamber[0][3][CSCCh1]++;totSBStationRingPt[0][3][pTBin]++;totSBStationRingEta[0][3][etaBin]++;totSBStationRingIso[0][3][isoBin]++;totSBStationRingPV[0][3][pvBin]++;totSBStationRingIL[0][3][ilBin]++;totSBStationRingRun[0][3][runBin]++;totSBStationRingChamberRun[0][3][CSCCh1][runBin]++;totSBStationRingLCY[0][3][lCYBin1]++;totSBStationRingLCYLCT[0][3][lC3YBin1]++;totSBStationRingLCS[0][3][lCSBin1]++;totSBStationRingLCSLCT[0][3][lC3SBin1]++;totSBStationRingChamberLCY[0][3][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[0][3][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[0][3][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[0][3][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[0][3][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[0][3][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[0][3][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
						}
						if (foundSeg1) {
							passSBGlobalSeg++;
							if (CSCRg1==4&&fiducial11) {passSBStationRingSeg[0][0]++;passSBStationRingChamberSeg[0][0][CSCCh1]++;passSBStationRingPtSeg[0][0][pTBin]++;passSBStationRingEtaSeg[0][0][etaBin]++;passSBStationRingIsoSeg[0][0][isoBin]++;passSBStationRingPVSeg[0][0][pvBin]++;passSBStationRingILSeg[0][0][ilBin]++;passSBStationRingRunSeg[0][0][runBin]++;passSBStationRingChamberRunSeg[0][0][CSCCh1][runBin]++;passSBStationRingLCYSeg[0][0][lCYBin1]++;passSBStationRingLCSSeg[0][0][lCSBin1]++;passSBStationRingChamberLCYSeg[0][0][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[0][0][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[0][0][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][0][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][0][CSCCh1]->Fill(invMass);
								zMassSegNumStationRingPV[0][0][pvBin]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passSBStationRingSeg[1][0]++;passSBStationRingChamberSeg[1][0][CSCCh1]++;passSBStationRingPtSeg[1][0][pTBin]++;passSBStationRingEtaSeg[1][0][etaBin]++;passSBStationRingIsoSeg[1][0][isoBin]++;passSBStationRingPVSeg[1][0][pvBin]++;passSBStationRingILSeg[1][0][ilBin]++;passSBStationRingRunSeg[1][0][runBin]++;passSBStationRingChamberRunSeg[1][0][CSCCh1][runBin]++;passSBStationRingLCYSeg[1][0][lCYBin1]++;;passSBStationRingLCSSeg[1][0][lCSBin1]++;}
								else {passSBStationRingSeg[1][3]++;passSBStationRingChamberSeg[1][3][CSCCh1]++;passSBStationRingPtSeg[1][3][pTBin]++;passSBStationRingEtaSeg[1][3][etaBin]++;passSBStationRingIsoSeg[1][3][isoBin]++;passSBStationRingPVSeg[1][3][pvBin]++;passSBStationRingILSeg[1][3][ilBin]++;passSBStationRingRunSeg[1][3][runBin]++;passSBStationRingChamberRunSeg[1][3][CSCCh1][runBin]++;passSBStationRingLCYSeg[1][3][lCYBin1]++;passSBStationRingLCSSeg[1][3][lCSBin1]++;}		    
							}
							if (CSCRg1==1&&fiducial11) {passSBStationRingSeg[0][1]++;passSBStationRingChamberSeg[0][1][CSCCh1]++;passSBStationRingPtSeg[0][1][pTBin]++;passSBStationRingEtaSeg[0][1][etaBin]++;passSBStationRingIsoSeg[0][1][isoBin]++;passSBStationRingPVSeg[0][1][pvBin]++;passSBStationRingILSeg[0][1][ilBin]++;passSBStationRingRunSeg[0][1][runBin]++;passSBStationRingChamberRunSeg[0][1][CSCCh1][runBin]++;passSBStationRingLCYSeg[0][1][lCYBin1]++;passSBStationRingLCSSeg[0][1][lCSBin1]++;passSBStationRingChamberLCYSeg[0][1][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[0][1][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[0][1][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][1][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][1][CSCCh1]->Fill(invMass);
								zMassSegNumStationRingPV[0][1][pvBin]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passSBStationRingSeg[2][0]++;passSBStationRingChamberSeg[2][0][CSCCh1]++;passSBStationRingPtSeg[2][0][pTBin]++;passSBStationRingEtaSeg[2][0][etaBin]++;passSBStationRingIsoSeg[2][0][isoBin]++;passSBStationRingPVSeg[2][0][pvBin]++;passSBStationRingILSeg[2][0][ilBin]++;passSBStationRingRunSeg[2][0][runBin]++;passSBStationRingChamberRunSeg[2][0][CSCCh1][runBin]++;passSBStationRingLCYSeg[2][0][lCYBin1]++;passSBStationRingLCSSeg[2][0][lCSBin1]++;}
								else {passSBStationRingSeg[2][3]++;passSBStationRingChamberSeg[2][3][CSCCh1]++;passSBStationRingPtSeg[2][3][pTBin]++;passSBStationRingEtaSeg[2][3][etaBin]++;passSBStationRingIsoSeg[2][3][isoBin]++;passSBStationRingPVSeg[2][3][pvBin]++;passSBStationRingILSeg[2][3][ilBin]++;passSBStationRingRunSeg[2][3][runBin]++;passSBStationRingChamberRunSeg[2][3][CSCCh1][runBin]++;passSBStationRingLCYSeg[2][3][lCYBin1]++;;passSBStationRingLCSSeg[2][3][lCSBin1]++;}		    
							}
							if (CSCRg1==2) {passSBStationRingSeg[0][2]++;passSBStationRingChamberSeg[0][2][CSCCh1]++;passSBStationRingPtSeg[0][2][pTBin]++;passSBStationRingEtaSeg[0][2][etaBin]++;passSBStationRingIsoSeg[0][2][isoBin]++;passSBStationRingPVSeg[0][2][pvBin]++;passSBStationRingILSeg[0][2][ilBin]++;passSBStationRingRunSeg[0][2][runBin]++;passSBStationRingChamberRunSeg[0][2][CSCCh1][runBin]++;passSBStationRingLCYSeg[0][2][lCYBin1]++;passSBStationRingLCSSeg[0][2][lCSBin1]++;passSBStationRingChamberLCYSeg[0][2][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[0][2][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[0][2][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][2][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][2][CSCCh1]->Fill(invMass);
								zMassSegNumStationRingPV[0][2][pvBin]->Fill(invMass);
							}
							if (CSCRg1==3) {passSBStationRingSeg[0][3]++;passSBStationRingChamberSeg[0][3][CSCCh1]++;passSBStationRingPtSeg[0][3][pTBin]++;passSBStationRingEtaSeg[0][3][etaBin]++;passSBStationRingIsoSeg[0][3][isoBin]++;passSBStationRingPVSeg[0][3][pvBin]++;passSBStationRingILSeg[0][3][ilBin]++;passSBStationRingRunSeg[0][3][runBin]++;passSBStationRingChamberRunSeg[0][3][CSCCh1][runBin]++;passSBStationRingLCYSeg[0][3][lCYBin1]++;passSBStationRingLCSSeg[0][3][lCSBin1]++;passSBStationRingChamberLCYSeg[0][3][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[0][3][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[0][3][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[0][3][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[0][3][CSCCh1]->Fill(invMass);
							}
						}
						if (foundLCT1) {
							passSBGlobalLCT++;
							if (CSCRg1==4&&fiducial11) {passSBStationRingLCT[0][0]++;passSBStationRingChamberLCT[0][0][CSCCh1]++;passSBStationRingPtLCT[0][0][pTBin]++;passSBStationRingEtaLCT[0][0][etaBin]++;passSBStationRingIsoLCT[0][0][isoBin]++;passSBStationRingPVLCT[0][0][pvBin]++;passSBStationRingILLCT[0][0][ilBin]++;passSBStationRingRunLCT[0][0][runBin]++;passSBStationRingChamberRunLCT[0][0][CSCCh1][runBin]++;passSBStationRingLCYLCT[0][0][lC3YBin1]++;passSBStationRingLCSLCT[0][0][lC3SBin1]++;passSBStationRingChamberLCYLCT[0][0][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[0][0][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[0][0][CSCCh1][lCWBin1]++;
								zMassLCTNumStationRingPV[0][0][pvBin]->Fill(invMass);		    
								if (CSCCh1%2 == 0 ) {passSBStationRingLCT[1][0]++;passSBStationRingChamberLCT[1][0][CSCCh1]++;passSBStationRingPtLCT[1][0][pTBin]++;passSBStationRingEtaLCT[1][0][etaBin]++;passSBStationRingIsoLCT[1][0][isoBin]++;passSBStationRingPVLCT[1][0][pvBin]++;passSBStationRingILLCT[1][0][ilBin]++;passSBStationRingRunLCT[1][0][runBin]++;passSBStationRingChamberRunLCT[1][0][CSCCh1][runBin]++;passSBStationRingLCYLCT[1][0][lC3YBin1]++;passSBStationRingLCSLCT[1][0][lC3SBin1]++;}
								else {passSBStationRingLCT[1][3]++;passSBStationRingChamberLCT[1][3][CSCCh1]++;passSBStationRingPtLCT[1][3][pTBin]++;passSBStationRingEtaLCT[1][3][etaBin]++;passSBStationRingIsoLCT[1][3][isoBin]++;passSBStationRingPVLCT[1][3][pvBin]++;passSBStationRingILLCT[1][3][ilBin]++;passSBStationRingRunLCT[1][3][runBin]++;passSBStationRingChamberRunLCT[1][3][CSCCh1][runBin]++;passSBStationRingLCYLCT[1][3][lC3YBin1]++;passSBStationRingLCSLCT[1][3][lC3SBin1]++;}
							}
							if (CSCRg1==1&&fiducial11) {passSBStationRingLCT[0][1]++;passSBStationRingChamberLCT[0][1][CSCCh1]++;passSBStationRingPtLCT[0][1][pTBin]++;passSBStationRingEtaLCT[0][1][etaBin]++;passSBStationRingIsoLCT[0][1][isoBin]++;passSBStationRingPVLCT[0][1][pvBin]++;passSBStationRingILLCT[0][1][ilBin]++;passSBStationRingRunLCT[0][1][runBin]++;passSBStationRingChamberRunLCT[0][1][CSCCh1][runBin]++;passSBStationRingLCYLCT[0][1][lC3YBin1]++;passSBStationRingLCSLCT[0][1][lC3SBin1]++;;passSBStationRingChamberLCYLCT[0][1][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[0][1][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[0][1][CSCCh1][lCWBin1]++;
								zMassLCTNumStationRingPV[0][1][pvBin]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passSBStationRingLCT[2][0]++;passSBStationRingChamberLCT[2][0][CSCCh1]++;passSBStationRingPtLCT[2][0][pTBin]++;passSBStationRingEtaLCT[2][0][etaBin]++;passSBStationRingIsoLCT[2][0][isoBin]++;passSBStationRingPVLCT[2][0][pvBin]++;passSBStationRingILLCT[2][0][ilBin]++;passSBStationRingRunLCT[2][0][runBin]++;passSBStationRingChamberRunLCT[2][0][CSCCh1][runBin]++;passSBStationRingLCYLCT[2][0][lC3YBin1]++;passSBStationRingLCSLCT[2][0][lC3SBin1]++;}
								else {passSBStationRingLCT[2][3]++;passSBStationRingChamberLCT[2][3][CSCCh1]++;passSBStationRingPtLCT[2][3][pTBin]++;passSBStationRingEtaLCT[2][3][etaBin]++;passSBStationRingIsoLCT[2][3][isoBin]++;passSBStationRingPVLCT[2][3][pvBin]++;passSBStationRingILLCT[2][3][ilBin]++;passSBStationRingRunLCT[2][3][runBin]++;passSBStationRingChamberRunLCT[2][3][CSCCh1][runBin]++;passSBStationRingLCYLCT[2][3][lC3YBin1]++;passSBStationRingLCSLCT[2][3][lC3SBin1]++;}
							}
							if (CSCRg1==2) {passSBStationRingLCT[0][2]++;passSBStationRingChamberLCT[0][2][CSCCh1]++;passSBStationRingPtLCT[0][2][pTBin]++;passSBStationRingEtaLCT[0][2][etaBin]++;passSBStationRingIsoLCT[0][2][isoBin]++;passSBStationRingPVLCT[0][2][pvBin]++;passSBStationRingILLCT[0][2][ilBin]++;passSBStationRingRunLCT[0][2][runBin]++;passSBStationRingChamberRunLCT[0][2][CSCCh1][runBin]++;passSBStationRingLCYLCT[0][2][lC3YBin1]++;passSBStationRingLCSLCT[0][2][lC3SBin1]++;passSBStationRingChamberLCYLCT[0][2][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[0][2][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[0][2][CSCCh1][lCWBin1]++;
								zMassLCTNumStationRingPV[0][2][pvBin]->Fill(invMass);
							}
							if (CSCRg1==3) {passSBStationRingLCT[0][3]++;passSBStationRingChamberLCT[0][3][CSCCh1]++;passSBStationRingPtLCT[0][3][pTBin]++;passSBStationRingEtaLCT[0][3][etaBin]++;passSBStationRingIsoLCT[0][3][isoBin]++;passSBStationRingPVLCT[0][3][pvBin]++;passSBStationRingILLCT[0][3][ilBin]++;passSBStationRingRunLCT[0][3][runBin]++;passSBStationRingChamberRunLCT[0][3][CSCCh1][runBin]++;passSBStationRingLCYLCT[0][3][lC3YBin1]++;passSBStationRingLCSLCT[0][3][lC3SBin1]++;passSBStationRingChamberLCYLCT[0][3][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[0][3][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[0][3][CSCCh1][lCWBin1]++;
								zMassLCTNumStationRingPV[0][3][pvBin]->Fill(invMass);
							}
						}
					}
					if (fiducial2){
						totSBGlobal++;
						if (CSCRg2==1) {totSBStationRing[1][1]++;totSBStationRingChamber[1][1][CSCCh2]++;totSBStationRingPt[1][1][pTBin]++;totSBStationRingEta[1][1][etaBin2]++;totSBStationRingIso[1][1][isoBin]++;totSBStationRingPV[1][1][pvBin]++;totSBStationRingIL[1][1][ilBin]++;totSBStationRingRun[1][1][runBin]++;totSBStationRingChamberRun[1][1][CSCCh2][runBin]++;totSBStationRingLCY[1][1][lCYBin2]++;totSBStationRingLCYLCT[1][1][lC3YBin2]++;totSBStationRingLCS[1][1][lCSBin2]++;totSBStationRingLCSLCT[1][1][lC3SBin2]++;totSBStationRingChamberLCY[1][1][CSCCh2][lCYBin2]++;totSBStationRingChamberLCS[1][1][CSCCh2][lCSBin2]++;totSBStationRingChamberLCW[1][1][CSCCh2][lCWBin2]++;
							if (inZMass) segDenStationRingChamberRun[1][1][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[1][1][CSCCh2]->Fill(invMass);
							zMassSegDenStationRingPV[1][1][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[1][1][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[1][1][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
						}
						if (CSCRg2==2) {totSBStationRing[1][2]++;totSBStationRingChamber[1][2][CSCCh2]++;totSBStationRingPt[1][2][pTBin]++;totSBStationRingEta[1][2][etaBin2]++;totSBStationRingIso[1][2][isoBin]++;totSBStationRingPV[1][2][pvBin]++;totSBStationRingIL[1][2][ilBin]++;totSBStationRingRun[1][2][runBin]++;totSBStationRingChamberRun[1][2][CSCCh2][runBin]++;totSBStationRingLCY[1][2][lCYBin2]++;totSBStationRingLCYLCT[1][2][lC3YBin2]++;totSBStationRingLCS[1][2][lCSBin2]++;totSBStationRingLCSLCT[1][2][lC3SBin2]++;totSBStationRingChamberLCY[1][2][CSCCh2][lCYBin2]++;totSBStationRingChamberLCS[1][2][CSCCh2][lCSBin2]++;totSBStationRingChamberLCW[1][2][CSCCh2][lCWBin2]++;
							if (inZMass) segDenStationRingChamberRun[1][2][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[1][2][CSCCh2]->Fill(invMass);
							zMassSegDenStationRingPV[1][2][pvBin]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[1][2][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[1][2][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
						}
						if (foundSeg2) {
							passSBGlobalSeg++;
							if (CSCRg2==1) {passSBStationRingSeg[1][1]++;passSBStationRingChamberSeg[1][1][CSCCh2]++;passSBStationRingPtSeg[1][1][pTBin]++;passSBStationRingEtaSeg[1][1][etaBin2]++;passSBStationRingIsoSeg[1][1][isoBin]++;passSBStationRingPVSeg[1][1][pvBin]++;passSBStationRingILSeg[1][1][ilBin]++;passSBStationRingRunSeg[1][1][runBin]++;passSBStationRingChamberRunSeg[1][1][CSCCh2][runBin]++;passSBStationRingLCYSeg[1][1][lCYBin2]++;passSBStationRingLCSSeg[1][1][lCSBin2]++;passSBStationRingChamberLCYSeg[1][1][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSSeg[1][1][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWSeg[1][1][CSCCh2][lCWBin2]++;
								if (inZMass) segNumStationRingChamberRun[1][1][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[1][1][CSCCh2]->Fill(invMass);
								zMassSegNumStationRingPV[1][1][pvBin]->Fill(invMass);
							}
							if (CSCRg2==2) {passSBStationRingSeg[1][2]++;passSBStationRingChamberSeg[1][2][CSCCh2]++;passSBStationRingPtSeg[1][2][pTBin]++;passSBStationRingEtaSeg[1][2][etaBin2]++;passSBStationRingIsoSeg[1][2][isoBin]++;passSBStationRingPVSeg[1][2][pvBin]++;passSBStationRingILSeg[1][2][ilBin]++;passSBStationRingRunSeg[1][2][runBin]++;passSBStationRingChamberRunSeg[1][2][CSCCh2][runBin]++;passSBStationRingLCYSeg[1][2][lCYBin2]++;passSBStationRingLCSSeg[1][2][lCSBin2]++;passSBStationRingChamberLCYSeg[1][2][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSSeg[1][2][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWSeg[1][2][CSCCh2][lCWBin2]++;
								if (inZMass) segNumStationRingChamberRun[1][2][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[1][2][CSCCh2]->Fill(invMass);
								zMassSegNumStationRingPV[1][2][pvBin]->Fill(invMass);
							}
						}
						if (foundLCT2) {
							passSBGlobalLCT++;
							if (CSCRg2==1) {passSBStationRingLCT[1][1]++;passSBStationRingChamberLCT[1][1][CSCCh2]++;passSBStationRingPtLCT[1][1][pTBin]++;passSBStationRingEtaLCT[1][1][etaBin2]++;passSBStationRingIsoLCT[1][1][isoBin]++;passSBStationRingPVLCT[1][1][pvBin]++;passSBStationRingILLCT[1][1][ilBin]++;passSBStationRingRunLCT[1][1][runBin]++;passSBStationRingChamberRunLCT[1][1][CSCCh2][runBin]++;passSBStationRingLCYLCT[1][1][lC3YBin1]++;passSBStationRingLCSLCT[1][1][lC3SBin1]++;passSBStationRingChamberLCYLCT[1][1][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSLCT[1][1][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWLCT[1][1][CSCCh2][lCWBin2]++;
								zMassLCTNumStationRingPV[1][1][pvBin]->Fill(invMass);
							}
							if (CSCRg2==2) {passSBStationRingLCT[1][2]++;passSBStationRingChamberLCT[1][2][CSCCh2]++;passSBStationRingPtLCT[1][2][pTBin]++;passSBStationRingEtaLCT[1][2][etaBin2]++;passSBStationRingIsoLCT[1][2][isoBin]++;passSBStationRingPVLCT[1][2][pvBin]++;passSBStationRingILLCT[1][2][ilBin]++;passSBStationRingRunLCT[1][2][runBin]++;passSBStationRingChamberRunLCT[1][2][CSCCh2][runBin]++;passSBStationRingLCYLCT[1][2][lC3YBin1]++;passSBStationRingLCSLCT[1][2][lC3SBin1]++;passSBStationRingChamberLCYLCT[1][2][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSLCT[1][2][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWLCT[1][2][CSCCh2][lCWBin2]++;
								zMassLCTNumStationRingPV[1][2][pvBin]->Fill(invMass);
							}
						}
					}
					if (fiducial3){
						totSBGlobal++;
						if (CSCRg3==1) {totSBStationRing[2][1]++;totSBStationRingChamber[2][1][CSCCh3]++;totSBStationRingPt[2][1][pTBin]++;totSBStationRingEta[2][1][etaBin3]++;totSBStationRingIso[2][1][isoBin]++;totSBStationRingPV[2][1][pvBin]++;totSBStationRingIL[2][1][ilBin]++;totSBStationRingRun[2][1][runBin]++;totSBStationRingChamberRun[2][1][CSCCh3][runBin]++;totSBStationRingLCY[2][1][lCYBin3]++;totSBStationRingLCYLCT[2][1][lC3YBin3]++;totSBStationRingLCS[2][1][lCSBin3]++;totSBStationRingLCSLCT[2][1][lC3SBin3]++;totSBStationRingChamberLCY[2][1][CSCCh3][lCYBin3]++;totSBStationRingChamberLCS[2][1][CSCCh3][lCSBin3]++;totSBStationRingChamberLCW[2][1][CSCCh3][lCWBin3]++;
							if (inZMass) segDenStationRingChamberRun[2][1][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[2][1][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[2][1][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[2][1][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
						}
						if (CSCRg3==2) {totSBStationRing[2][2]++;totSBStationRingChamber[2][2][CSCCh3]++;totSBStationRingPt[2][2][pTBin]++;totSBStationRingEta[2][2][etaBin3]++;totSBStationRingIso[2][2][isoBin]++;totSBStationRingPV[2][2][pvBin]++;totSBStationRingIL[2][2][ilBin]++;totSBStationRingRun[2][2][runBin]++;totSBStationRingChamberRun[2][2][CSCCh3][runBin]++;totSBStationRingLCY[2][2][lCYBin3]++;totSBStationRingLCYLCT[2][2][lC3YBin3]++;totSBStationRingLCS[2][2][lCSBin3]++;totSBStationRingLCSLCT[2][2][lC3SBin3]++;totSBStationRingChamberLCY[2][2][CSCCh3][lCYBin3]++;totSBStationRingChamberLCS[2][2][CSCCh3][lCSBin3]++;totSBStationRingChamberLCW[2][2][CSCCh3][lCWBin3]++;
							if (inZMass) segDenStationRingChamberRun[2][2][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[2][2][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[2][2][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[2][2][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
						}
						if (foundSeg3) {
							passSBGlobalSeg++;
							if (CSCRg3==1) {passSBStationRingSeg[2][1]++;passSBStationRingChamberSeg[2][1][CSCCh3]++;passSBStationRingPtSeg[2][1][pTBin]++;passSBStationRingEtaSeg[2][1][etaBin3]++;passSBStationRingIsoSeg[2][1][isoBin]++;passSBStationRingPVSeg[2][1][pvBin]++;passSBStationRingILSeg[2][1][ilBin]++;passSBStationRingRunSeg[2][1][runBin]++;passSBStationRingChamberRunSeg[2][1][CSCCh3][runBin]++;passSBStationRingLCYSeg[2][1][lCYBin3]++;passSBStationRingLCSSeg[2][1][lCSBin3]++;passSBStationRingChamberLCYSeg[2][1][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSSeg[2][1][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWSeg[2][1][CSCCh3][lCWBin3]++;
								if (inZMass) segNumStationRingChamberRun[2][1][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[2][1][CSCCh3]->Fill(invMass);
							}
							if (CSCRg3==2) {passSBStationRingSeg[2][2]++;passSBStationRingChamberSeg[2][2][CSCCh3]++;passSBStationRingPtSeg[2][2][pTBin]++;passSBStationRingEtaSeg[2][2][etaBin3]++;passSBStationRingIsoSeg[2][2][isoBin]++;passSBStationRingPVSeg[2][2][pvBin]++;passSBStationRingILSeg[2][2][ilBin]++;passSBStationRingRunSeg[2][2][runBin]++;passSBStationRingChamberRunSeg[2][2][CSCCh3][runBin]++;passSBStationRingLCYSeg[2][2][lCYBin3]++;passSBStationRingLCSSeg[2][2][lCSBin3]++;passSBStationRingChamberLCYSeg[2][2][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSSeg[2][2][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWSeg[2][2][CSCCh3][lCWBin3]++;
								if (inZMass) segNumStationRingChamberRun[2][2][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[2][2][CSCCh3]->Fill(invMass);
							}
						}
						if (foundLCT3) {
							passSBGlobalLCT++;
							if (CSCRg3==1) {passSBStationRingLCT[2][1]++;passSBStationRingChamberLCT[2][1][CSCCh3]++;passSBStationRingPtLCT[2][1][pTBin]++;passSBStationRingEtaLCT[2][1][etaBin3]++;passSBStationRingIsoLCT[2][1][isoBin]++;passSBStationRingPVLCT[2][1][pvBin]++;passSBStationRingILLCT[2][1][ilBin]++;passSBStationRingRunLCT[2][1][runBin]++;passSBStationRingChamberRunLCT[2][1][CSCCh3][runBin]++;passSBStationRingLCYLCT[2][1][lC3YBin3]++;passSBStationRingLCSLCT[2][1][lC3SBin3]++;passSBStationRingChamberLCYLCT[2][1][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSLCT[2][1][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWLCT[2][1][CSCCh3][lCWBin3]++;}
							if (CSCRg3==2) {passSBStationRingLCT[2][2]++;passSBStationRingChamberLCT[2][2][CSCCh3]++;passSBStationRingPtLCT[2][2][pTBin]++;passSBStationRingEtaLCT[2][2][etaBin3]++;passSBStationRingIsoLCT[2][2][isoBin]++;passSBStationRingPVLCT[2][2][pvBin]++;passSBStationRingILLCT[2][2][ilBin]++;passSBStationRingRunLCT[2][2][runBin]++;passSBStationRingChamberRunLCT[2][2][CSCCh3][runBin]++;passSBStationRingLCYLCT[2][2][lC3YBin3]++;passSBStationRingLCSLCT[2][2][lC3SBin3]++;passSBStationRingChamberLCYLCT[2][2][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSLCT[2][2][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWLCT[2][2][CSCCh3][lCWBin3]++;}
						}
					}
					if (fiducial4){
						totSBGlobal++;
						if (CSCRg4==1) {totSBStationRing[3][1]++;totSBStationRingChamber[3][1][CSCCh4]++;totSBStationRingPt[3][1][pTBin]++;totSBStationRingEta[3][1][etaBin4]++;totSBStationRingIso[3][1][isoBin]++;totSBStationRingPV[3][1][pvBin]++;totSBStationRingIL[3][1][ilBin]++;totSBStationRingRun[3][1][runBin]++;totSBStationRingChamberRun[3][1][CSCCh4][runBin]++;totSBStationRingLCY[3][1][lCYBin4]++;totSBStationRingLCYLCT[3][1][lC3YBin4]++;totSBStationRingLCS[3][1][lCSBin4]++;totSBStationRingLCSLCT[3][1][lC3SBin4]++;totSBStationRingChamberLCY[3][1][CSCCh4][lCYBin4]++;totSBStationRingChamberLCS[3][1][CSCCh4][lCSBin4]++;totSBStationRingChamberLCW[3][1][CSCCh4][lCWBin4]++;
							if (inZMass) segDenStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[3][1][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[3][1][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[3][1][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
						}
						if (CSCRg4==2) {totSBStationRing[3][2]++;totSBStationRingChamber[3][2][CSCCh4]++;totSBStationRingPt[3][2][pTBin]++;totSBStationRingEta[3][2][etaBin4]++;totSBStationRingIso[3][2][isoBin]++;totSBStationRingPV[3][2][pvBin]++;totSBStationRingIL[3][2][ilBin]++;totSBStationRingRun[3][2][runBin]++;totSBStationRingChamberRun[3][2][CSCCh4][runBin]++;totSBStationRingLCY[3][2][lCYBin4]++;totSBStationRingLCYLCT[3][2][lC3YBin4]++;totSBStationRingLCS[3][2][lCSBin4]++;totSBStationRingLCSLCT[3][2][lC3SBin4]++;totSBStationRingChamberLCY[3][2][CSCCh4][lCYBin4]++;totSBStationRingChamberLCS[3][2][CSCCh4][lCSBin4]++;totSBStationRingChamberLCW[3][2][CSCCh4][lCWBin4]++;
							if (inZMass) segDenStationRingChamberRun[3][2][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[3][2][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[3][2][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[3][2][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
						}
						if (foundSeg4) {
							passSBGlobalSeg++;
							if (CSCRg4==1) {passSBStationRingSeg[3][1]++;passSBStationRingChamberSeg[3][1][CSCCh4]++;passSBStationRingPtSeg[3][1][pTBin]++;passSBStationRingEtaSeg[3][1][etaBin4]++;passSBStationRingIsoSeg[3][1][isoBin]++;passSBStationRingPVSeg[3][1][pvBin]++;passSBStationRingILSeg[3][1][ilBin]++;passSBStationRingRunSeg[3][1][runBin]++;passSBStationRingChamberRunSeg[3][1][CSCCh4][runBin]++;passSBStationRingLCYSeg[3][1][lCYBin4]++;passSBStationRingLCSSeg[3][1][lCSBin4]++;passSBStationRingChamberLCYSeg[3][1][CSCCh4][lCYBin4]++;passSBStationRingChamberLCSSeg[3][1][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWSeg[3][1][CSCCh4][lCWBin4]++;
								if (inZMass) segNumStationRingChamberRun[3][1][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[3][1][CSCCh4]->Fill(invMass);
							}
							if (CSCRg4==2) {passSBStationRingSeg[3][2]++;passSBStationRingChamberSeg[3][2][CSCCh4]++;passSBStationRingPtSeg[3][2][pTBin]++;passSBStationRingEtaSeg[3][2][etaBin4]++;passSBStationRingIsoSeg[3][2][isoBin]++;passSBStationRingPVSeg[3][2][pvBin]++;passSBStationRingILSeg[3][2][ilBin]++;passSBStationRingRunSeg[3][2][runBin]++;passSBStationRingChamberRunSeg[3][2][CSCCh4][runBin]++;passSBStationRingLCYSeg[3][2][lCYBin4]++;passSBStationRingLCSSeg[3][2][lCSBin4]++;passSBStationRingChamberLCYSeg[3][2][CSCCh4][lCYBin4]++;passSBStationRingChamberLCSSeg[3][2][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWSeg[3][2][CSCCh4][lCWBin4]++;
								if (inZMass) segNumStationRingChamberRun[3][2][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[3][2][CSCCh4]->Fill(invMass);
							}
						}
						if (foundLCT4) {
							passSBGlobalLCT++;
							if (CSCRg4==1) {passSBStationRingLCT[3][1]++;passSBStationRingChamberLCT[3][1][CSCCh4]++;passSBStationRingPtLCT[3][1][pTBin]++;passSBStationRingEtaLCT[3][1][etaBin4]++;passSBStationRingIsoLCT[3][1][isoBin]++;passSBStationRingPVLCT[3][1][pvBin]++;passSBStationRingILLCT[3][1][ilBin]++;passSBStationRingRunLCT[3][1][runBin]++;passSBStationRingChamberRunLCT[3][1][CSCCh4][runBin]++;passSBStationRingLCYLCT[3][1][lC3YBin4]++;passSBStationRingLCSLCT[3][1][lC3SBin4]++;passSBStationRingChamberLCYLCT[3][1][CSCCh4][lCYBin4]++;passSBStationRingChamberLCSLCT[3][1][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWLCT[3][1][CSCCh4][lCWBin4]++;}
							if (CSCRg4==2) {passSBStationRingLCT[3][2]++;passSBStationRingChamberLCT[3][2][CSCCh4]++;passSBStationRingPtLCT[3][2][pTBin]++;passSBStationRingEtaLCT[3][2][etaBin4]++;passSBStationRingIsoLCT[3][2][isoBin]++;passSBStationRingPVLCT[3][2][pvBin]++;passSBStationRingILLCT[3][2][ilBin]++;passSBStationRingRunLCT[3][2][runBin]++;passSBStationRingChamberRunLCT[3][2][CSCCh4][runBin]++;passSBStationRingLCYLCT[3][2][lC3YBin4]++;passSBStationRingLCSLCT[3][2][lC3SBin4]++;passSBStationRingChamberLCYLCT[3][2][CSCCh4][lCYBin4]++;passSBStationRingChamberLCSLCT[3][2][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWLCT[3][2][CSCCh4][lCWBin4]++;}
						}
					}
				}
				if (CSCEndCapPlus){
					if (fiducial1||fiducial11){
						totSBGlobal++;
						if (CSCRg1==4&&fiducial11) {totSBStationRing[4][0]++;totSBStationRingChamber[4][0][CSCCh1]++;totSBStationRingPt[4][0][pTBin]++;totSBStationRingEta[4][0][etaBin]++;totSBStationRingIso[4][0][isoBin]++;totSBStationRingPV[4][0][pvBin]++;totSBStationRingIL[4][0][ilBin]++;totSBStationRingRun[4][0][runBin]++;totSBStationRingChamberRun[4][0][CSCCh1][runBin]++;totSBStationRingLCY[4][0][lCYBin1]++;totSBStationRingLCYLCT[4][0][lC3YBin1]++;totSBStationRingLCS[4][0][lCSBin1]++;totSBStationRingLCSLCT[4][0][lC3SBin1]++;totSBStationRingChamberLCY[4][0][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[4][0][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[4][0][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[4][0][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][0][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][0][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][0][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							if (CSCCh1%2 == 0 ) {totSBStationRing[5][0]++;totSBStationRingChamber[5][0][CSCCh1]++;totSBStationRingPt[5][0][pTBin]++;totSBStationRingEta[5][0][etaBin]++;totSBStationRingIso[5][0][isoBin]++;totSBStationRingPV[5][0][pvBin]++;totSBStationRingIL[5][0][ilBin]++;totSBStationRingRun[5][0][runBin]++;totSBStationRingChamberRun[5][0][CSCCh1][runBin]++;totSBStationRingLCY[5][0][lCYBin1]++;totSBStationRingLCYLCT[5][0][lC3YBin1]++;totSBStationRingLCS[5][0][lCSBin1]++;totSBStationRingLCSLCT[5][0][lC3SBin1]++;}
							else {totSBStationRing[5][3]++;totSBStationRingChamber[5][3][CSCCh1]++;totSBStationRingPt[5][3][pTBin]++;totSBStationRingEta[5][3][etaBin]++;totSBStationRingIso[5][3][isoBin]++;totSBStationRingPV[5][3][pvBin]++;totSBStationRingIL[5][3][ilBin]++;totSBStationRingRun[5][3][runBin]++;totSBStationRingChamberRun[5][3][CSCCh1][runBin]++;totSBStationRingLCY[5][3][lCYBin1]++;totSBStationRingLCYLCT[5][3][lC3YBin1]++;totSBStationRingLCS[5][3][lCSBin1]++;totSBStationRingLCSLCT[5][3][lC3SBin1]++;}
						}
						if (CSCRg1==1&&fiducial11) {totSBStationRing[4][1]++;totSBStationRingChamber[4][1][CSCCh1]++;totSBStationRingPt[4][1][pTBin]++;totSBStationRingEta[4][1][etaBin]++;totSBStationRingIso[4][1][isoBin]++;totSBStationRingPV[4][1][pvBin]++;totSBStationRingIL[4][1][ilBin]++;totSBStationRingRun[4][1][runBin]++;totSBStationRingChamberRun[4][1][CSCCh1][runBin]++;totSBStationRingLCY[4][1][lCYBin1]++;totSBStationRingLCYLCT[4][1][lC3YBin1]++;totSBStationRingLCS[4][1][lCSBin1]++;totSBStationRingLCSLCT[4][1][lC3SBin1]++;totSBStationRingChamberLCY[4][1][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[4][1][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[4][1][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[4][1][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][1][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][1][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][1][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
							if (CSCCh1%2 == 0 ) {totSBStationRing[6][0]++;totSBStationRingChamber[6][0][CSCCh1]++;totSBStationRingPt[6][0][pTBin]++;totSBStationRingEta[6][0][etaBin]++;totSBStationRingIso[6][0][isoBin]++;totSBStationRingPV[6][0][pvBin]++;totSBStationRingIL[6][0][ilBin]++;totSBStationRingRun[6][0][runBin]++;totSBStationRingChamberRun[6][0][CSCCh1][runBin]++;totSBStationRingLCY[6][0][lCYBin1]++;totSBStationRingLCYLCT[6][0][lC3YBin1]++;totSBStationRingLCS[6][0][lCSBin1]++;totSBStationRingLCSLCT[6][0][lC3SBin1]++;}
							else {totSBStationRing[6][3]++;totSBStationRingChamber[6][3][CSCCh1]++;totSBStationRingPt[6][3][pTBin]++;totSBStationRingEta[6][3][etaBin]++;totSBStationRingIso[6][3][isoBin]++;totSBStationRingPV[6][3][pvBin]++;totSBStationRingIL[6][3][ilBin]++;totSBStationRingRun[6][3][runBin]++;totSBStationRingChamberRun[6][3][CSCCh1][runBin]++;totSBStationRingLCY[6][3][lCYBin1]++;totSBStationRingLCYLCT[6][3][lC3YBin1]++;totSBStationRingLCS[6][3][lCSBin1]++;totSBStationRingLCSLCT[6][3][lC3SBin1]++;}
						}
						if (CSCRg1==2) {totSBStationRing[4][2]++;totSBStationRingChamber[4][2][CSCCh1]++;totSBStationRingPt[4][2][pTBin]++;totSBStationRingEta[4][2][etaBin]++;totSBStationRingIso[4][2][isoBin]++;totSBStationRingPV[4][2][pvBin]++;totSBStationRingIL[4][2][ilBin]++;totSBStationRingRun[4][2][runBin]++;totSBStationRingChamberRun[4][2][CSCCh1][runBin]++;totSBStationRingLCY[4][2][lCYBin1]++;totSBStationRingLCYLCT[4][2][lC3YBin1]++;totSBStationRingLCS[4][2][lCSBin1]++;totSBStationRingLCSLCT[4][2][lC3SBin1]++;totSBStationRingChamberLCY[4][2][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[4][2][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[4][2][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[4][2][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][2][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][2][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][2][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
						}
						if (CSCRg1==3) {totSBStationRing[4][3]++;totSBStationRingChamber[4][3][CSCCh1]++;totSBStationRingPt[4][3][pTBin]++;totSBStationRingEta[4][3][etaBin]++;totSBStationRingIso[4][3][isoBin]++;totSBStationRingPV[4][3][pvBin]++;totSBStationRingIL[4][3][ilBin]++;totSBStationRingRun[4][3][runBin]++;totSBStationRingChamberRun[4][3][CSCCh1][runBin]++;totSBStationRingLCY[4][3][lCYBin1]++;totSBStationRingLCYLCT[4][3][lC3YBin1]++;totSBStationRingLCS[4][3][lCSBin1]++;totSBStationRingLCSLCT[4][3][lC3SBin1]++;totSBStationRingChamberLCY[4][3][CSCCh1][lCYBin1]++;totSBStationRingChamberLCS[4][3][CSCCh1][lCSBin1]++;totSBStationRingChamberLCW[4][3][CSCCh1][lCWBin1]++;
							if (inZMass) segDenStationRingChamberRun[4][3][CSCCh1]->Fill(run_number);
							zMassSegDenStationRingChamber[4][3][CSCCh1]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[4][3][CSCCh1]->Fill(CSCDxyTTSeg1);resSigmaSegStationRingChamber[4][3][CSCCh1]->Fill(CSCDxyTTSeg1/CSCDxyErrTTSeg1);}
						}
						if (foundSeg1) {
							passSBGlobalSeg++;
							if (CSCRg1==4&&fiducial11) {passSBStationRingSeg[4][0]++;passSBStationRingChamberSeg[4][0][CSCCh1]++;passSBStationRingPtSeg[4][0][pTBin]++;passSBStationRingEtaSeg[4][0][etaBin]++;passSBStationRingIsoSeg[4][0][isoBin]++;passSBStationRingPVSeg[4][0][pvBin]++;passSBStationRingILSeg[4][0][ilBin]++;passSBStationRingRunSeg[4][0][runBin]++;passSBStationRingChamberRunSeg[4][0][CSCCh1][runBin]++;passSBStationRingLCYSeg[4][0][lCYBin1]++;passSBStationRingLCSSeg[4][0][lCSBin1]++;passSBStationRingChamberLCYSeg[4][0][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[4][0][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[4][0][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][0][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][0][CSCCh1]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passSBStationRingSeg[5][0]++;passSBStationRingChamberSeg[5][0][CSCCh1]++;passSBStationRingPtSeg[5][0][pTBin]++;passSBStationRingEtaSeg[5][0][etaBin]++;passSBStationRingIsoSeg[5][0][isoBin]++;passSBStationRingPVSeg[5][0][pvBin]++;passSBStationRingILSeg[5][0][ilBin]++;passSBStationRingRunSeg[5][0][runBin]++;passSBStationRingChamberRunSeg[5][0][CSCCh1][runBin]++;passSBStationRingLCYSeg[5][0][lCYBin1]++;passSBStationRingLCSSeg[5][0][lCSBin1]++;}
								else {passSBStationRingSeg[5][3]++;passSBStationRingChamberSeg[5][3][CSCCh1]++;passSBStationRingPtSeg[5][3][pTBin]++;passSBStationRingEtaSeg[5][3][etaBin]++;passSBStationRingIsoSeg[5][3][isoBin]++;passSBStationRingPVSeg[5][3][pvBin]++;passSBStationRingILSeg[5][3][ilBin]++;passSBStationRingRunSeg[5][3][runBin]++;passSBStationRingChamberRunSeg[5][3][CSCCh1][runBin]++;passSBStationRingLCYSeg[5][3][lCYBin1]++;passSBStationRingLCSSeg[5][3][lCSBin1]++;}
							}
							if (CSCRg1==1&&fiducial11) {passSBStationRingSeg[4][1]++;passSBStationRingChamberSeg[4][1][CSCCh1]++;passSBStationRingPtSeg[4][1][pTBin]++;passSBStationRingEtaSeg[4][1][etaBin]++;passSBStationRingIsoSeg[4][1][isoBin]++;passSBStationRingPVSeg[4][1][pvBin]++;passSBStationRingILSeg[4][1][ilBin]++;passSBStationRingRunSeg[4][1][runBin]++;passSBStationRingChamberRunSeg[4][1][CSCCh1][runBin]++;passSBStationRingLCYSeg[4][1][lCYBin1]++;passSBStationRingLCSSeg[4][1][lCSBin1]++;passSBStationRingChamberLCYSeg[4][1][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[4][1][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[4][1][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][1][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][1][CSCCh1]->Fill(invMass);
								if (CSCCh1%2 == 0 ) {passSBStationRingSeg[6][0]++;passSBStationRingChamberSeg[6][0][CSCCh1]++;passSBStationRingPtSeg[6][0][pTBin]++;passSBStationRingEtaSeg[6][0][etaBin]++;passSBStationRingIsoSeg[6][0][isoBin]++;passSBStationRingPVSeg[6][0][pvBin]++;passSBStationRingILSeg[6][0][ilBin]++;passSBStationRingRunSeg[6][0][runBin]++;passSBStationRingChamberRunSeg[6][0][CSCCh1][runBin]++;passSBStationRingLCYSeg[6][0][lCYBin1]++;passSBStationRingLCSSeg[6][0][lCSBin1]++;}
								else {passSBStationRingSeg[6][3]++;passSBStationRingChamberSeg[6][3][CSCCh1]++;passSBStationRingPtSeg[6][3][pTBin]++;passSBStationRingEtaSeg[6][3][etaBin]++;passSBStationRingIsoSeg[6][3][isoBin]++;passSBStationRingPVSeg[6][3][pvBin]++;passSBStationRingILSeg[6][3][ilBin]++;passSBStationRingRunSeg[6][3][runBin]++;passSBStationRingChamberRunSeg[6][3][CSCCh1][runBin]++;passSBStationRingLCYSeg[6][3][lCYBin1]++;passSBStationRingLCSSeg[6][3][lCSBin1]++;}
							}
							if (CSCRg1==2) {passSBStationRingSeg[4][2]++;passSBStationRingChamberSeg[4][2][CSCCh1]++;passSBStationRingPtSeg[4][2][pTBin]++;passSBStationRingEtaSeg[4][2][etaBin]++;passSBStationRingIsoSeg[4][2][isoBin]++;passSBStationRingPVSeg[4][2][pvBin]++;passSBStationRingILSeg[4][2][ilBin]++;passSBStationRingRunSeg[4][2][runBin]++;passSBStationRingChamberRunSeg[4][2][CSCCh1][runBin]++;passSBStationRingLCYSeg[4][2][lCYBin1]++;passSBStationRingLCSSeg[4][2][lCSBin1]++;passSBStationRingChamberLCYSeg[4][2][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[4][2][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[4][2][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][2][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][2][CSCCh1]->Fill(invMass);
							}
							if (CSCRg1==3) {passSBStationRingSeg[4][3]++;passSBStationRingChamberSeg[4][3][CSCCh1]++;passSBStationRingPtSeg[4][3][pTBin]++;passSBStationRingEtaSeg[4][3][etaBin]++;passSBStationRingIsoSeg[4][3][isoBin]++;passSBStationRingPVSeg[4][3][pvBin]++;passSBStationRingILSeg[4][3][ilBin]++;passSBStationRingRunSeg[4][3][runBin]++;passSBStationRingChamberRunSeg[4][3][CSCCh1][runBin]++;passSBStationRingLCYSeg[4][3][lCYBin1]++;passSBStationRingLCSSeg[4][3][lCSBin1]++;passSBStationRingChamberLCYSeg[4][3][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[4][3][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWSeg[4][3][CSCCh1][lCWBin1]++;
								if (inZMass) segNumStationRingChamberRun[4][3][CSCCh1]->Fill(run_number);
								zMassSegNumStationRingChamber[4][3][CSCCh1]->Fill(invMass);
							}
						}
						if (foundLCT1) {
							passSBGlobalLCT++;
							if (CSCRg1==4&&fiducial11) {passSBStationRingLCT[4][0]++;passSBStationRingChamberLCT[4][0][CSCCh1]++;passSBStationRingPtLCT[4][0][pTBin]++;passSBStationRingEtaLCT[4][0][etaBin]++;passSBStationRingIsoLCT[4][0][isoBin]++;passSBStationRingPVLCT[4][0][pvBin]++;passSBStationRingILLCT[4][0][ilBin]++;passSBStationRingRunLCT[4][0][runBin]++;passSBStationRingChamberRunLCT[4][0][CSCCh1][runBin]++;passSBStationRingLCYLCT[4][0][lC3YBin1]++;passSBStationRingLCSLCT[4][0][lC3SBin1]++;passSBStationRingChamberLCYLCT[4][0][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[4][0][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[4][0][CSCCh1][lCWBin1]++;
								if (CSCCh1%2 == 0 ) {passSBStationRingLCT[5][0]++;passSBStationRingChamberLCT[5][0][CSCCh1]++;passSBStationRingPtLCT[5][0][pTBin]++;passSBStationRingEtaLCT[5][0][etaBin]++;passSBStationRingIsoLCT[5][0][isoBin]++;passSBStationRingPVLCT[5][0][pvBin]++;passSBStationRingILLCT[5][0][ilBin]++;passSBStationRingRunLCT[5][0][runBin]++;passSBStationRingChamberRunLCT[5][0][CSCCh1][runBin]++;passSBStationRingLCYLCT[5][0][lC3YBin1]++;passSBStationRingLCSLCT[5][0][lC3SBin1]++;}
								else {passSBStationRingLCT[5][3]++;passSBStationRingChamberLCT[5][3][CSCCh1]++;passSBStationRingPtLCT[5][3][pTBin]++;passSBStationRingEtaLCT[5][3][etaBin]++;;passSBStationRingIsoLCT[5][3][isoBin]++;passSBStationRingPVLCT[5][3][pvBin]++;passSBStationRingILLCT[5][3][ilBin]++;passSBStationRingRunLCT[5][3][runBin]++;passSBStationRingChamberRunLCT[5][3][CSCCh1][runBin]++;passSBStationRingLCYLCT[5][3][lC3YBin1]++;passSBStationRingLCSLCT[5][3][lC3SBin1]++;}
							}
							if (CSCRg1==1&&fiducial11) {passSBStationRingLCT[4][1]++;passSBStationRingChamberLCT[4][1][CSCCh1]++;passSBStationRingPtLCT[4][1][pTBin]++;passSBStationRingEtaLCT[4][1][etaBin]++;passSBStationRingIsoLCT[4][1][isoBin]++;passSBStationRingPVLCT[4][1][pvBin]++;passSBStationRingILLCT[4][1][ilBin]++;passSBStationRingRunLCT[4][1][runBin]++;passSBStationRingChamberRunLCT[4][1][CSCCh1][runBin]++;passSBStationRingLCYLCT[4][1][lC3YBin1]++;passSBStationRingLCSLCT[4][1][lC3SBin1]++;passSBStationRingChamberLCYLCT[4][1][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[4][1][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[4][1][CSCCh1][lCWBin1]++;
								if (CSCCh1%2 == 0 ) {passSBStationRingLCT[6][0]++;passSBStationRingChamberLCT[6][0][CSCCh1]++;passSBStationRingPtLCT[6][0][pTBin]++;passSBStationRingEtaLCT[6][0][etaBin]++;passSBStationRingIsoLCT[6][0][isoBin]++;passSBStationRingPVLCT[6][0][pvBin]++;passSBStationRingILLCT[6][0][ilBin]++;passSBStationRingRunLCT[6][0][runBin]++;passSBStationRingChamberRunLCT[6][0][CSCCh1][runBin]++;passSBStationRingLCYLCT[6][0][lC3YBin1]++;passSBStationRingLCSLCT[6][0][lC3SBin1]++;}
								else {passSBStationRingLCT[6][3]++;passSBStationRingChamberLCT[6][3][CSCCh1]++;passSBStationRingPtLCT[6][3][pTBin]++;passSBStationRingEtaLCT[6][3][etaBin]++;passSBStationRingIsoLCT[6][3][isoBin]++;passSBStationRingPVLCT[6][3][pvBin]++;passSBStationRingILLCT[6][3][ilBin]++;passSBStationRingRunLCT[6][3][runBin]++;passSBStationRingChamberRunLCT[6][3][CSCCh1][runBin]++;passSBStationRingLCYLCT[6][3][lC3YBin1]++;passSBStationRingLCSLCT[6][3][lC3SBin1]++;}
							}
							if (CSCRg1==2) {passSBStationRingLCT[4][2]++;passSBStationRingChamberLCT[4][2][CSCCh1]++;passSBStationRingPtLCT[4][2][pTBin]++;passSBStationRingEtaLCT[4][2][etaBin]++;passSBStationRingIsoLCT[4][2][isoBin]++;passSBStationRingPVLCT[4][2][pvBin]++;passSBStationRingILLCT[4][2][ilBin]++;passSBStationRingRunLCT[4][2][runBin]++;passSBStationRingChamberRunLCT[4][2][CSCCh1][runBin]++;passSBStationRingLCYLCT[4][2][lC3YBin1]++;passSBStationRingLCSLCT[4][2][lC3SBin1]++;passSBStationRingChamberLCYLCT[4][2][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[4][2][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[4][2][CSCCh1][lCWBin1]++;}
							if (CSCRg1==3) {passSBStationRingLCT[4][3]++;passSBStationRingChamberLCT[4][3][CSCCh1]++;passSBStationRingPtLCT[4][3][pTBin]++;passSBStationRingEtaLCT[4][3][etaBin]++;passSBStationRingIsoLCT[4][3][isoBin]++;passSBStationRingPVLCT[4][3][pvBin]++;passSBStationRingILLCT[4][3][ilBin]++;passSBStationRingRunLCT[4][3][runBin]++;passSBStationRingChamberRunLCT[4][3][CSCCh1][runBin]++;passSBStationRingLCYLCT[4][3][lC3YBin1]++;passSBStationRingLCSLCT[4][3][lC3SBin1]++;passSBStationRingChamberLCYLCT[4][3][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSLCT[4][3][CSCCh1][lCSBin1]++;passSBStationRingChamberLCWLCT[4][3][CSCCh1][lCWBin1]++;}
						}
					}
					if (fiducial2){
						totSBGlobal++;
						if (CSCRg2==1) {totSBStationRing[5][1]++;totSBStationRingChamber[5][1][CSCCh2]++;totSBStationRingPt[5][1][pTBin]++;totSBStationRingEta[5][1][etaBin2]++;totSBStationRingIso[5][1][isoBin]++;totSBStationRingPV[5][1][pvBin]++;totSBStationRingIL[5][1][ilBin]++;totSBStationRingRun[5][1][runBin]++;totSBStationRingChamberRun[5][1][CSCCh2][runBin]++;totSBStationRingLCY[5][1][lCYBin2]++;totSBStationRingLCYLCT[5][1][lC3YBin2]++;totSBStationRingLCS[5][1][lCSBin2]++;totSBStationRingLCSLCT[5][1][lC3SBin2]++;totSBStationRingChamberLCY[5][1][CSCCh2][lCYBin2]++;totSBStationRingChamberLCS[5][1][CSCCh2][lCSBin2]++;totSBStationRingChamberLCW[5][1][CSCCh2][lCWBin2]++;
							if (inZMass) segDenStationRingChamberRun[5][1][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[5][1][CSCCh2]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[5][1][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[5][1][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
						}
						if (CSCRg2==2) {totSBStationRing[5][2]++;totSBStationRingChamber[5][2][CSCCh2]++;totSBStationRingPt[5][2][pTBin]++;totSBStationRingEta[5][2][etaBin2]++;totSBStationRingIso[5][2][isoBin]++;totSBStationRingPV[5][2][pvBin]++;totSBStationRingIL[5][2][ilBin]++;totSBStationRingRun[5][2][runBin]++;totSBStationRingChamberRun[5][2][CSCCh2][runBin]++;totSBStationRingLCY[5][2][lCYBin2]++;totSBStationRingLCYLCT[5][2][lC3YBin2]++;totSBStationRingLCS[5][2][lCSBin2]++;totSBStationRingLCSLCT[5][2][lC3SBin2]++;totSBStationRingChamberLCY[5][2][CSCCh2][lCYBin2]++;totSBStationRingChamberLCS[5][2][CSCCh2][lCSBin2]++;totSBStationRingChamberLCW[5][2][CSCCh2][lCWBin2]++;
							if (inZMass) segDenStationRingChamberRun[5][2][CSCCh2]->Fill(run_number);
							zMassSegDenStationRingChamber[5][2][CSCCh2]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[5][2][CSCCh2]->Fill(CSCDxyTTSeg2);resSigmaSegStationRingChamber[5][2][CSCCh2]->Fill(CSCDxyTTSeg2/CSCDxyErrTTSeg2);}
						}
						if (foundSeg2) {
							passSBGlobalSeg++;
							if (CSCRg2==1) {passSBStationRingSeg[5][1]++;passSBStationRingChamberSeg[5][1][CSCCh2]++;passSBStationRingPtSeg[5][1][pTBin]++;passSBStationRingEtaSeg[5][1][etaBin2]++;passSBStationRingIsoSeg[5][1][isoBin]++;passSBStationRingPVSeg[5][1][pvBin]++;passSBStationRingILSeg[5][1][ilBin]++;passSBStationRingRunSeg[5][1][runBin]++;passSBStationRingChamberRunSeg[5][1][CSCCh2][runBin]++;passSBStationRingLCYSeg[5][1][lCYBin2]++;passSBStationRingLCSSeg[5][1][lCSBin2]++;passSBStationRingChamberLCYSeg[5][1][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSSeg[5][1][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWSeg[5][1][CSCCh2][lCWBin2]++;
								if (inZMass) segNumStationRingChamberRun[5][1][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[5][1][CSCCh2]->Fill(invMass);
							}
							if (CSCRg2==2) {passSBStationRingSeg[5][2]++;passSBStationRingChamberSeg[5][2][CSCCh2]++;passSBStationRingPtSeg[5][2][pTBin]++;passSBStationRingEtaSeg[5][2][etaBin2]++;passSBStationRingIsoSeg[5][2][isoBin]++;passSBStationRingPVSeg[5][2][pvBin]++;passSBStationRingILSeg[5][2][ilBin]++;passSBStationRingRunSeg[5][2][runBin]++;passSBStationRingChamberRunSeg[5][2][CSCCh2][runBin]++;passSBStationRingLCYSeg[5][2][lCYBin2]++;passSBStationRingLCSSeg[5][2][lCSBin2]++;passSBStationRingChamberLCYSeg[5][2][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSSeg[5][2][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWSeg[5][2][CSCCh2][lCWBin2]++;
								if (inZMass) segNumStationRingChamberRun[5][2][CSCCh2]->Fill(run_number);
								zMassSegNumStationRingChamber[5][2][CSCCh2]->Fill(invMass);
							}
						}
						if (foundLCT2) {
							passSBGlobalLCT++;
							if (CSCRg2==1) {passSBStationRingLCT[5][1]++;passSBStationRingChamberLCT[5][1][CSCCh2]++;passSBStationRingPtLCT[5][1][pTBin]++;passSBStationRingEtaLCT[5][1][etaBin2]++;passSBStationRingIsoLCT[5][1][isoBin]++;passSBStationRingPVLCT[5][1][pvBin]++;passSBStationRingILLCT[5][1][ilBin]++;passSBStationRingRunLCT[5][1][runBin]++;passSBStationRingChamberRunLCT[5][1][CSCCh2][runBin]++;passSBStationRingLCYLCT[5][1][lC3YBin2]++;passSBStationRingLCSLCT[5][1][lC3SBin2]++;passSBStationRingChamberLCYLCT[5][1][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSLCT[5][1][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWLCT[5][1][CSCCh2][lCWBin2]++;}
							if (CSCRg2==2) {passSBStationRingLCT[5][2]++;passSBStationRingChamberLCT[5][2][CSCCh2]++;passSBStationRingPtLCT[5][2][pTBin]++;passSBStationRingEtaLCT[5][2][etaBin2]++;passSBStationRingIsoLCT[5][2][isoBin]++;passSBStationRingPVLCT[5][2][pvBin]++;passSBStationRingILLCT[5][2][ilBin]++;passSBStationRingRunLCT[5][2][runBin]++;passSBStationRingChamberRunLCT[5][2][CSCCh2][runBin]++;passSBStationRingLCYLCT[5][2][lC3YBin2]++;passSBStationRingLCSLCT[5][2][lC3SBin2]++;passSBStationRingChamberLCYLCT[5][2][CSCCh2][lCYBin2]++;passSBStationRingChamberLCSLCT[5][2][CSCCh2][lCSBin2]++;passSBStationRingChamberLCWLCT[5][2][CSCCh2][lCWBin2]++;}
						}
					}
					if (fiducial3){
						totSBGlobal++;
						if (CSCRg3==1) {totSBStationRing[6][1]++;totSBStationRingChamber[6][1][CSCCh3]++;totSBStationRingPt[6][1][pTBin]++;totSBStationRingEta[6][1][etaBin3]++;totSBStationRingIso[6][1][isoBin]++;totSBStationRingPV[6][1][pvBin]++;totSBStationRingIL[6][1][ilBin]++;totSBStationRingRun[6][1][runBin]++;totSBStationRingChamberRun[6][1][CSCCh3][runBin]++;totSBStationRingLCY[6][1][lCYBin3]++;totSBStationRingLCYLCT[6][1][lC3YBin3]++;totSBStationRingLCS[6][1][lCSBin3]++;totSBStationRingLCSLCT[6][1][lC3SBin3]++;totSBStationRingChamberLCY[6][1][CSCCh3][lCYBin3]++;totSBStationRingChamberLCS[6][1][CSCCh3][lCSBin3]++;totSBStationRingChamberLCW[6][1][CSCCh3][lCWBin3]++;
							if (inZMass) segDenStationRingChamberRun[6][1][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[6][1][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[6][1][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[6][1][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
						}
						if (CSCRg3==2) {totSBStationRing[6][2]++;totSBStationRingChamber[6][2][CSCCh3]++;totSBStationRingPt[6][2][pTBin]++;totSBStationRingEta[6][2][etaBin3]++;totSBStationRingIso[6][2][isoBin]++;totSBStationRingPV[6][2][pvBin]++;totSBStationRingIL[6][2][ilBin]++;totSBStationRingRun[6][2][runBin]++;totSBStationRingChamberRun[6][2][CSCCh3][runBin]++;totSBStationRingLCY[6][2][lCYBin3]++;totSBStationRingLCYLCT[6][2][lC3YBin3]++;totSBStationRingLCS[6][2][lCSBin3]++;totSBStationRingLCSLCT[6][2][lC3SBin3]++;totSBStationRingChamberLCY[6][2][CSCCh3][lCYBin3]++;totSBStationRingChamberLCS[6][2][CSCCh3][lCSBin3]++;totSBStationRingChamberLCW[6][2][CSCCh3][lCWBin3]++;
							if (inZMass) segDenStationRingChamberRun[6][2][CSCCh3]->Fill(run_number);
							zMassSegDenStationRingChamber[6][2][CSCCh3]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[6][2][CSCCh3]->Fill(CSCDxyTTSeg3);resSigmaSegStationRingChamber[6][2][CSCCh3]->Fill(CSCDxyTTSeg3/CSCDxyErrTTSeg3);}
						}
						if (foundSeg3) {
							passSBGlobalSeg++;
							if (CSCRg3==1) {passSBStationRingSeg[6][1]++;passSBStationRingChamberSeg[6][1][CSCCh3]++;passSBStationRingPtSeg[6][1][pTBin]++;passSBStationRingEtaSeg[6][1][etaBin3]++;passSBStationRingIsoSeg[6][1][isoBin]++;passSBStationRingPVSeg[6][1][pvBin]++;passSBStationRingILSeg[6][1][ilBin]++;passSBStationRingRunSeg[6][1][runBin]++;passSBStationRingChamberRunSeg[6][1][CSCCh3][runBin]++;passSBStationRingLCYSeg[6][1][lCYBin3]++;passSBStationRingLCSSeg[6][1][lCSBin3]++;passSBStationRingChamberLCYSeg[6][1][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSSeg[6][1][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWSeg[6][1][CSCCh3][lCWBin3]++;
								if (inZMass) segNumStationRingChamberRun[6][1][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[6][1][CSCCh3]->Fill(invMass);
							}
							if (CSCRg3==2) {passSBStationRingSeg[6][2]++;passSBStationRingChamberSeg[6][2][CSCCh3]++;passSBStationRingPtSeg[6][2][pTBin]++;passSBStationRingEtaSeg[6][2][etaBin3]++;passSBStationRingIsoSeg[6][2][isoBin]++;passSBStationRingPVSeg[6][2][pvBin]++;passSBStationRingILSeg[6][2][ilBin]++;passSBStationRingRunSeg[6][2][runBin]++;passSBStationRingChamberRunSeg[6][2][CSCCh3][runBin]++;passSBStationRingLCYSeg[6][2][lCYBin3]++;passSBStationRingLCSSeg[6][2][lCSBin3]++;passSBStationRingChamberLCYSeg[6][2][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSSeg[6][2][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWSeg[6][2][CSCCh3][lCWBin3]++;
								if (inZMass) segNumStationRingChamberRun[6][2][CSCCh3]->Fill(run_number);
								zMassSegNumStationRingChamber[6][2][CSCCh3]->Fill(invMass);
							}
						}
						if (foundLCT3) {
							passSBGlobalLCT++;
							if (CSCRg3==1) {passSBStationRingLCT[6][1]++;passSBStationRingChamberLCT[6][1][CSCCh3]++;passSBStationRingPtLCT[6][1][pTBin]++;passSBStationRingEtaLCT[6][1][etaBin3]++;passSBStationRingIsoLCT[6][1][isoBin]++;passSBStationRingPVLCT[6][1][pvBin]++;passSBStationRingILLCT[6][1][ilBin]++;passSBStationRingRunLCT[6][1][runBin]++;passSBStationRingChamberRunLCT[6][1][CSCCh3][runBin]++;passSBStationRingLCYLCT[6][1][lC3YBin3]++;passSBStationRingLCSLCT[6][1][lC3SBin3]++;passSBStationRingChamberLCYLCT[6][1][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSLCT[6][1][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWLCT[6][1][CSCCh3][lCWBin3]++;}
							if (CSCRg3==2) {passSBStationRingLCT[6][2]++;passSBStationRingChamberLCT[6][2][CSCCh3]++;passSBStationRingPtLCT[6][2][pTBin]++;passSBStationRingEtaLCT[6][2][etaBin3]++;passSBStationRingIsoLCT[6][2][isoBin]++;passSBStationRingPVLCT[6][2][pvBin]++;passSBStationRingILLCT[6][2][ilBin]++;passSBStationRingRunLCT[6][2][runBin]++;passSBStationRingChamberRunLCT[6][2][CSCCh3][runBin]++;passSBStationRingLCYLCT[6][2][lC3YBin3]++;passSBStationRingLCSLCT[6][2][lC3SBin3]++;passSBStationRingChamberLCYLCT[6][2][CSCCh3][lCYBin3]++;passSBStationRingChamberLCSLCT[6][2][CSCCh3][lCSBin3]++;passSBStationRingChamberLCWLCT[6][2][CSCCh3][lCWBin3]++;}
						}
					}
					if (fiducial4){
						totSBGlobal++;
						if (CSCRg4==1) {totSBStationRing[7][1]++;totSBStationRingChamber[7][1][CSCCh4]++;totSBStationRingPt[7][1][pTBin]++;totSBStationRingEta[7][1][etaBin4]++;totSBStationRingIso[7][1][isoBin]++;totSBStationRingPV[7][1][pvBin]++;totSBStationRingIL[7][1][ilBin]++;totSBStationRingRun[7][1][runBin]++;totSBStationRingChamberRun[7][1][CSCCh4][runBin]++;totSBStationRingLCY[7][1][lCYBin4]++;totSBStationRingLCYLCT[7][1][lC3YBin4]++;totSBStationRingLCS[7][1][lCSBin4]++;totSBStationRingLCSLCT[7][1][lC3SBin4]++;totSBStationRingChamberLCY[7][1][CSCCh4][lCYBin4]++;totSBStationRingChamberLCS[7][1][CSCCh4][lCSBin4]++;totSBStationRingChamberLCW[7][1][CSCCh4][lCWBin4]++;
							if (inZMass) segDenStationRingChamberRun[7][1][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[7][1][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[7][1][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[7][1][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
						}
						if (CSCRg4==2) {totSBStationRing[7][2]++;totSBStationRingChamber[7][2][CSCCh4]++;totSBStationRingPt[7][2][pTBin]++;totSBStationRingEta[7][2][etaBin4]++;totSBStationRingIso[7][2][isoBin]++;totSBStationRingPV[7][2][pvBin]++;totSBStationRingIL[7][2][ilBin]++;totSBStationRingRun[7][2][runBin]++;totSBStationRingChamberRun[7][2][CSCCh4][runBin]++;totSBStationRingLCY[7][2][lCYBin4]++;totSBStationRingLCYLCT[7][2][lC3YBin4]++;totSBStationRingLCS[7][2][lCSBin4]++;totSBStationRingLCSLCT[7][2][lC3SBin4]++;totSBStationRingChamberLCY[7][2][CSCCh4][lCYBin4]++;totSBStationRingChamberLCS[7][2][CSCCh4][lCSBin4]++;totSBStationRingChamberLCW[7][2][CSCCh4][lCWBin4]++;
							if (inZMass) segDenStationRingChamberRun[7][2][CSCCh4]->Fill(run_number);
							zMassSegDenStationRingChamber[7][2][CSCCh4]->Fill(invMass);
							if (inZMass) {resSegStationRingChamber[7][2][CSCCh4]->Fill(CSCDxyTTSeg4);resSigmaSegStationRingChamber[7][2][CSCCh4]->Fill(CSCDxyTTSeg4/CSCDxyErrTTSeg4);}
						}
						if (foundSeg4) {
							passSBGlobalSeg++;
							if (CSCRg4==1) {passSBStationRingSeg[7][1]++;passSBStationRingChamberSeg[7][1][CSCCh4]++;passSBStationRingPtSeg[7][1][pTBin]++;passSBStationRingEtaSeg[7][1][etaBin4]++;passSBStationRingIsoSeg[7][1][isoBin]++;passSBStationRingPVSeg[7][1][pvBin]++;passSBStationRingILSeg[7][1][ilBin]++;passSBStationRingRunSeg[7][1][runBin]++;passSBStationRingChamberRunSeg[7][1][CSCCh4][runBin]++;passSBStationRingLCYSeg[7][1][lCYBin4]++;passSBStationRingLCSSeg[7][1][lCSBin4]++;passSBStationRingChamberLCYSeg[7][1][CSCCh4][lCYBin4]++;passSBStationRingChamberLCSSeg[7][1][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWSeg[7][1][CSCCh4][lCWBin4]++;
								if (inZMass) segNumStationRingChamberRun[7][1][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[7][1][CSCCh4]->Fill(invMass);
							}
							if (CSCRg4==2) {passSBStationRingSeg[7][2]++;passSBStationRingChamberSeg[7][2][CSCCh4]++;passSBStationRingPtSeg[7][2][pTBin]++;passSBStationRingEtaSeg[7][2][etaBin4]++;passSBStationRingIsoSeg[7][2][isoBin]++;passSBStationRingPVSeg[7][2][pvBin]++;passSBStationRingILSeg[7][2][ilBin]++;passSBStationRingRunSeg[7][2][runBin]++;passSBStationRingChamberRunSeg[7][2][CSCCh4][runBin]++;passSBStationRingLCYSeg[7][2][lCYBin4]++;passSBStationRingLCSSeg[7][2][lCSBin4]++;passSBStationRingChamberLCYSeg[7][2][CSCCh1][lCYBin1]++;passSBStationRingChamberLCSSeg[7][2][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWSeg[7][2][CSCCh4][lCWBin4]++;
								if (inZMass) segNumStationRingChamberRun[7][2][CSCCh4]->Fill(run_number);
								zMassSegNumStationRingChamber[7][2][CSCCh4]->Fill(invMass);
							}
						}
						if (foundLCT4) {
							passSBGlobalLCT++;
							if (CSCRg4==1) {passSBStationRingLCT[7][1]++;passSBStationRingChamberLCT[7][1][CSCCh4]++;passSBStationRingPtLCT[7][1][pTBin]++;passSBStationRingEtaLCT[7][1][etaBin4]++;passSBStationRingIsoLCT[7][1][isoBin]++;passSBStationRingPVLCT[7][1][pvBin]++;passSBStationRingILLCT[7][1][ilBin]++;passSBStationRingRunLCT[7][1][runBin]++;passSBStationRingChamberRunLCT[7][1][CSCCh4][runBin]++;passSBStationRingLCYLCT[7][1][lC3YBin4]++;passSBStationRingLCSLCT[7][1][lC3SBin4]++;passSBStationRingChamberLCYLCT[7][1][CSCCh4][lCYBin4]++;passSBStationRingChamberLCSLCT[7][1][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWLCT[7][1][CSCCh4][lCWBin4]++;}
							if (CSCRg4==2) {passSBStationRingLCT[7][2]++;passSBStationRingChamberLCT[7][2][CSCCh4]++;passSBStationRingPtLCT[7][2][pTBin]++;passSBStationRingEtaLCT[7][2][etaBin4]++;passSBStationRingIsoLCT[7][2][isoBin]++;passSBStationRingPVLCT[7][2][pvBin]++;passSBStationRingILLCT[7][2][ilBin]++;passSBStationRingRunLCT[7][2][runBin]++;passSBStationRingChamberRunLCT[7][2][CSCCh4][runBin]++;passSBStationRingLCYLCT[7][2][lC3YBin4]++;passSBStationRingLCSLCT[7][2][lC3SBin4]++;passSBStationRingChamberLCYLCT[7][2][CSCCh4][lCYBin4]++;passSBStationRingChamberLCSLCT[7][2][CSCCh4][lCSBin4]++;passSBStationRingChamberLCWLCT[7][2][CSCCh4][lCWBin4]++;}
						}
					}

				}

			} // end sideband

		}



	} // end loop over jentry
	Float_t binVal;

	std::cout << nentries << " of " << nentries << " - Number good Candidates: " << nCands << " - Number of Zs: " << nZs << std::endl;

	// // efficiency calculations
	// // Total, Ring and Chamber efficiencies
	// if (totGlobal>0.5)  effGlobalSeg = passGlobalSeg/totGlobal;
	// if (totGlobal>0.5) effSigmaGlobalSeg = sqrt(effGlobalSeg*(1.0-effGlobalSeg)/totGlobal);
	// //std::cout << "Global efficiency" << std::endl;
	// //std::cout << "tot: " << totGlobal << std::endl;
	// //std::cout << "eff: " << effGlobalSeg << " +/- " << effSigmaGlobalSeg << std::endl;

	// if (totGlobal>0.5)  effGlobalLCT = passGlobalLCT/totGlobal;
	// if (totGlobal>0.5) effSigmaGlobalLCT = sqrt(effGlobalLCT*(1.0-effGlobalLCT)/totGlobal);
	// //std::cout << "Global efficiency" << std::endl;
	// //std::cout << "tot: " << totGlobal << std::endl;
	// //std::cout << "eff: " << effGlobalLCT << " +/- " << effSigmaGlobalLCT << std::endl;



	for (Int_t iiStation=0; iiStation < 8; iiStation++){
		for (Int_t iiRing=0; iiRing < 4; iiRing++){

			//     if (totStationRing[iiStation][iiRing]>0.5)  effStationRingSeg[iiStation][iiRing] = passStationRingSeg[iiStation][iiRing]/totStationRing[iiStation][iiRing];
			//     if (totStationRing[iiStation][iiRing]>0.5) effSigmaStationRingSeg[iiStation][iiRing] = sqrt(effStationRingSeg[iiStation][iiRing]*(1.0-effStationRingSeg[iiStation][iiRing])/totStationRing[iiStation][iiRing]);
			//     //std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << std::endl;
			//     //std::cout << "tot: " << totStationRing[iiStation][iiRing] << std::endl;
			//     //std::cout << "eff: " << effStationRingSeg[iiStation][iiRing] << " +/- " << effSigmaStationRingSeg[iiStation][iiRing] << std::endl;



			//     if ((totStationRing[iiStation][iiRing]>0.5)&&(totSBStationRing[iiStation][iiRing]>0.5)&&((totStationRing[iiStation][iiRing]-totSBStationRing[iiStation][iiRing])>0.5)) {
			// 	 effStationRingSeg[iiStation][iiRing] = (passStationRingSeg[iiStation][iiRing]-passSBStationRingSeg[iiStation][iiRing])/(totStationRing[iiStation][iiRing]-totSBStationRing[iiStation][iiRing]);
			// 	 effSigmaStationRingSeg[iiStation][iiRing] = sqrt(((passStationRingSeg[iiStation][iiRing]+passSBStationRingSeg[iiStation][iiRing])*(1.-effStationRingSeg[iiStation][iiRing])*(1.-effStationRingSeg[iiStation][iiRing]))+ ((totStationRing[iiStation][iiRing]-passStationRingSeg[iiStation][iiRing])+(totSBStationRing[iiStation][iiRing]-passSBStationRingSeg[iiStation][iiRing]))*effStationRingSeg[iiStation][iiRing]*effStationRingSeg[iiStation][iiRing])/(totStationRing[iiStation][iiRing]-totSBStationRing[iiStation][iiRing]);

			// 	 effStationRingLCT[iiStation][iiRing] = (passStationRingLCT[iiStation][iiRing]-passSBStationRingLCT[iiStation][iiRing])/(totStationRing[iiStation][iiRing]-totSBStationRing[iiStation][iiRing]);
			// 	 effSigmaStationRingLCT[iiStation][iiRing] = sqrt(((passStationRingLCT[iiStation][iiRing]+passSBStationRingLCT[iiStation][iiRing])*(1.-effStationRingLCT[iiStation][iiRing])*(1.-effStationRingLCT[iiStation][iiRing]))+ ((totStationRing[iiStation][iiRing]-passStationRingLCT[iiStation][iiRing])+(totSBStationRing[iiStation][iiRing]-passSBStationRingLCT[iiStation][iiRing]))*effStationRingLCT[iiStation][iiRing]*effStationRingLCT[iiStation][iiRing])/(totStationRing[iiStation][iiRing]-totSBStationRing[iiStation][iiRing]);

			//     }

			//     //std::cout << "Ring efficiency SBS: Station " << iiStation << " Ring " << iiRing << std::endl;
			//     //std::cout << "tot: " << totStationRing[iiStation][iiRing] << std::endl;
			//     //std::cout << "eff: " << effStationRingSeg[iiStation][iiRing] << " +/- " << effSigmaStationRingSeg[iiStation][iiRing] << std::endl;






			for (Int_t iiChamber=0; iiChamber< 37; iiChamber++){
				if (DoubleMuGun) totSBStationRingChamber[iiStation][iiRing][iiChamber] = 1.0;
				if (LowStats) {
					totSBStationRingChamber[iiStation][iiRing][iiChamber] = 0.0000001;
					passSBStationRingChamberSeg[iiStation][iiRing][iiChamber] = 0.0000001;
					passSBStationRingChamberLCT[iiStation][iiRing][iiChamber] = 0.0000001;
				}

				if ((totStationRingChamber[iiStation][iiRing][iiChamber]>0.0000005)&&((totStationRingChamber[iiStation][iiRing][iiChamber]-totSBStationRingChamber[iiStation][iiRing][iiChamber])>0.0000005)) {
					effStationRingChamberSeg[iiStation][iiRing][iiChamber] = (passStationRingChamberSeg[iiStation][iiRing][iiChamber]-passSBStationRingChamberSeg[iiStation][iiRing][iiChamber])/(totStationRingChamber[iiStation][iiRing][iiChamber]-totSBStationRingChamber[iiStation][iiRing][iiChamber]);
					effSigmaStationRingChamberSeg[iiStation][iiRing][iiChamber] = sqrt(((passStationRingChamberSeg[iiStation][iiRing][iiChamber]+passSBStationRingChamberSeg[iiStation][iiRing][iiChamber])*(1.-effStationRingChamberSeg[iiStation][iiRing][iiChamber])*(1.-effStationRingChamberSeg[iiStation][iiRing][iiChamber]))+ ((totStationRingChamber[iiStation][iiRing][iiChamber]-passStationRingChamberSeg[iiStation][iiRing][iiChamber])+(totSBStationRingChamber[iiStation][iiRing][iiChamber]-passSBStationRingChamberSeg[iiStation][iiRing][iiChamber]))*effStationRingChamberSeg[iiStation][iiRing][iiChamber]*effStationRingChamberSeg[iiStation][iiRing][iiChamber])/(totStationRingChamber[iiStation][iiRing][iiChamber]-totSBStationRingChamber[iiStation][iiRing][iiChamber]);


					effStationRingChamberLCT[iiStation][iiRing][iiChamber] = (passStationRingChamberLCT[iiStation][iiRing][iiChamber]-passSBStationRingChamberLCT[iiStation][iiRing][iiChamber])/(totStationRingChamber[iiStation][iiRing][iiChamber]-totSBStationRingChamber[iiStation][iiRing][iiChamber]);
					effSigmaStationRingChamberLCT[iiStation][iiRing][iiChamber] = sqrt(((passStationRingChamberLCT[iiStation][iiRing][iiChamber]+passSBStationRingChamberLCT[iiStation][iiRing][iiChamber])*(1.-effStationRingChamberLCT[iiStation][iiRing][iiChamber])*(1.-effStationRingChamberLCT[iiStation][iiRing][iiChamber]))+ ((totStationRingChamber[iiStation][iiRing][iiChamber]-passStationRingChamberLCT[iiStation][iiRing][iiChamber])+(totSBStationRingChamber[iiStation][iiRing][iiChamber]-passSBStationRingChamberLCT[iiStation][iiRing][iiChamber]))*effStationRingChamberLCT[iiStation][iiRing][iiChamber]*effStationRingChamberLCT[iiStation][iiRing][iiChamber])/(totStationRingChamber[iiStation][iiRing][iiChamber]-totSBStationRingChamber[iiStation][iiRing][iiChamber]);

				}
				// Root histograms bin zero, underflow, 1 - nbins content, nbins+1 overflow
				// segEffStationRingChamber[iiStation][iiRing]->SetBinContent(iiChamber,effStationRingChamberSeg[iiStation][iiRing][iiChamber]);
				// segEffStationRingChamber[iiStation][iiRing]->SetBinError(iiChamber,effSigmaStationRingChamberSeg[iiStation][iiRing][iiChamber]);


				// LCTEffStationRingChamber[iiStation][iiRing]->SetBinContent(iiChamber,effStationRingChamberLCT[iiStation][iiRing][iiChamber]);
				// LCTEffStationRingChamber[iiStation][iiRing]->SetBinError(iiChamber,effSigmaStationRingChamberLCT[iiStation][iiRing][iiChamber]);


				if (effStationRingChamberSeg[iiStation][iiRing][iiChamber] > 1.1 || fabs(effStationRingChamberSeg[iiStation][iiRing][iiChamber] - 1.0 )  < 0.001 ) {
					std::cout << "Eff > 0.99999: " << effStationRingChamberSeg[iiStation][iiRing][iiChamber] << " " <<  effSigmaStationRingChamberSeg[iiStation][iiRing][iiChamber] << " " << totStationRingChamber[iiStation][iiRing][iiChamber] << " " << totSBStationRingChamber[iiStation][iiRing][iiChamber] << " " << passStationRingChamberSeg[iiStation][iiRing][iiChamber] << " " << passSBStationRingChamberSeg[iiStation][iiRing][iiChamber] << std::endl;
				}


				Int_t ybin = 0;
				if (iiStation == 0 && iiRing == 0) ybin = 10;
				if (iiStation == 0 && iiRing == 1) ybin = 9;
				if (iiStation == 0 && iiRing == 2) ybin = 8;
				if (iiStation == 0 && iiRing == 3) ybin = 7;
				if (iiStation == 1 && iiRing == 1) ybin = 6;
				if (iiStation == 1 && iiRing == 2) ybin = 5;
				if (iiStation == 2 && iiRing == 1) ybin = 4;
				if (iiStation == 2 && iiRing == 2) ybin = 3;
				if (iiStation == 3 && iiRing == 1) ybin = 2;
				if (iiStation == 3 && iiRing == 2) ybin = 1;

				if (iiStation == 4 && iiRing == 0) ybin = 11;
				if (iiStation == 4 && iiRing == 1) ybin = 12;
				if (iiStation == 4 && iiRing == 2) ybin = 13;
				if (iiStation == 4 && iiRing == 3) ybin = 14;
				if (iiStation == 5 && iiRing == 1) ybin = 15;
				if (iiStation == 5 && iiRing == 2) ybin = 16;
				if (iiStation == 6 && iiRing == 1) ybin = 17;
				if (iiStation == 6 && iiRing == 2) ybin = 18;
				if (iiStation == 7 && iiRing == 1) ybin = 19;
				if (iiStation == 7 && iiRing == 2) ybin = 20;

				segEff2DStationRingChamber->SetBinContent(iiChamber,ybin,effStationRingChamberSeg[iiStation][iiRing][iiChamber]);
				segEff2DStationRingChamber->SetBinError(iiChamber,ybin,effSigmaStationRingChamberSeg[iiStation][iiRing][iiChamber]);
				LCTEff2DStationRingChamber->SetBinContent(iiChamber,ybin,effStationRingChamberLCT[iiStation][iiRing][iiChamber]);
				LCTEff2DStationRingChamber->SetBinError(iiChamber,ybin,effSigmaStationRingChamberLCT[iiStation][iiRing][iiChamber]);


				segEffStationRingChamberRun[iiStation][iiRing][iiChamber]->Add(segNumStationRingChamberRun[iiStation][iiRing][iiChamber]);
				segEffStationRingChamberRun[iiStation][iiRing][iiChamber]->Divide(segDenStationRingChamberRun[iiStation][iiRing][iiChamber]);
				segEffStationRingChamberRun[iiStation][iiRing][iiChamber]->Write();



				LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber]->Add(LCTNumStationRingChamberRun[iiStation][iiRing][iiChamber]);
				LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber]->Divide(segDenStationRingChamberRun[iiStation][iiRing][iiChamber]);
				LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber]->Write();

				for (Int_t ii=0; ii< lastRun-firstRun; ii++){
					if (segDenStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)==0&&segNumStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)==0){
						segEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetBinContent(ii,-0.001);
					}
					if (segDenStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)>0&&segNumStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)==0){
						segEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetBinContent(ii,0.001);
					}

					if (segDenStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)==0&&LCTNumStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)==0){
						LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetBinContent(ii,-0.001);
					}
					if (segDenStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)>0&&LCTNumStationRingChamberRun[iiStation][iiRing][iiChamber]->GetBinContent(ii)==0){
						LCTEffStationRingChamberRun[iiStation][iiRing][iiChamber]->SetBinContent(ii,0.001);
					}


				}





				// 	 // if (fitEff) {
				// 	 //   fit->SetParameters(zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->Integral()*0.8,zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->GetMean(),zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->GetRMS(),5.0,-0.8,zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->Integral()*0.2,zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->GetMean(),zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->GetRMS()*1.5);
				// 	 //   fit->SetParLimits(3,0.0,20.0);
				// 	 //   fit->SetParLimits(4,-2.0,0.0);
				// 	 //   fit->SetParLimits(0,0.0,zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->Integral());
				// 	 //   fit->SetParLimits(5,0.0,zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->Integral());

				// 	 //   zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->Fit("myfit");
				// 	 //   Float_t denSum = fabs(fit->GetParameter(0))+fabs(fit->GetParameter(5));

				// 	 //   //fit->SetParameters(zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->Integral()*0.8,zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->GetMean(),zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->GetRMS(),20.0,-0.5,zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->Integral()*0.2,zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->GetMean(),zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->GetRMS()*1.5);
				// 	 //   fit->SetParLimits(3,0.0,100.0);
				// 	 //   fit->SetParLimits(4,-2.0,0.0);
				// 	 //   fit->SetParLimits(0,0.0,zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->Integral());
				// 	 //   fit->SetParLimits(5,0.0,zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->Integral());

				// 	 //   zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->Fit("myfit");
				// 	 //   Float_t numSum = fabs(fit->GetParameter(0))+fabs(fit->GetParameter(5));

				// 	 //   segEffFit2DStationRingChamber->SetBinContent(iiChamber,ybin,numSum/denSum);
				// 	 //   segEffFit2DStationRingChamber->SetBinError(iiChamber,ybin,0.0);

				// 	 //   segEffDiff2DStationRingChamber->SetBinContent(iiChamber,ybin,effStationRingChamberSeg[iiStation][iiRing][iiChamber]-numSum/denSum);
				// 	 //   segEffDiff2DStationRingChamber->SetBinError(iiChamber,ybin,0.0);

				// 	 //   if (effStationRingChamberSeg[iiStation][iiRing][iiChamber]>0.001) segEffDiff1D->Fill(effStationRingChamberSeg[iiStation][iiRing][iiChamber]-numSum/denSum);
				// 	 // }



				zMassSegDenStationRingChamber[iiStation][iiRing][iiChamber]->Write();
				zMassSegNumStationRingChamber[iiStation][iiRing][iiChamber]->Write();
				resSegStationRingChamber[iiStation][iiRing][iiChamber]->Write();
				resSigmaSegStationRingChamber[iiStation][iiRing][iiChamber]->Write();



				for (Int_t iiRun=0; iiRun< numRunBins; iiRun++){

					if ((totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]>0.5)&&((totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-totSBStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun])>0.5)) {
						effStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun] = (passStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun]-passSBStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun])/(totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-totSBStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]);
						effSigmaStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun] = sqrt(((passStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun]+passSBStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun])*(1.-effStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun])*(1.-effStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun]))+ ((totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-passStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun])+(totSBStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-passSBStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun]))*effStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun]*effStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun])/(totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-totSBStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]);
						effStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun] = (passStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun]-passSBStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun])/(totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-totSBStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]);
						effSigmaStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun] = sqrt(((passStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun]+passSBStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun])*(1.-effStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun])*(1.-effStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun]))+ ((totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-passStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun])+(totSBStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-passSBStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun]))*effStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun]*effStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun])/(totStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]-totSBStationRingChamberRun[iiStation][iiRing][iiChamber][iiRun]);
					}




					segEff2DStationRingChamberRun[iiStation][iiRing]->SetBinContent(iiChamber,iiRun+1,effStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun]);
					segEff2DStationRingChamberRun[iiStation][iiRing]->SetBinError(iiChamber,iiRun+1,effSigmaStationRingChamberRunSeg[iiStation][iiRing][iiChamber][iiRun]);
					LCTEff2DStationRingChamberRun[iiStation][iiRing]->SetBinContent(iiChamber,iiRun+1,effStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun]);
					LCTEff2DStationRingChamberRun[iiStation][iiRing]->SetBinError(iiChamber,iiRun+1,effSigmaStationRingChamberRunLCT[iiStation][iiRing][iiChamber][iiRun]);

				}

				segEff2DStationRingChamberRun[iiStation][iiRing]->Write();
				LCTEff2DStationRingChamberRun[iiStation][iiRing]->Write();
				yySegStationRing[iiStation][iiRing]->Write();


				for (Int_t iiLayer=0; iiLayer< numLayerBins; iiLayer++){

					if ((totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]>0.5)&&((totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-totSBStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer])>0.5)) {
						effStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer] = (passStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer]-passSBStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer])/(totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-totSBStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]);
						effSigmaStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer] = sqrt(((passStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer]+passSBStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer])*(1.-effStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer])*(1.-effStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer]))+ ((totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-passStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer])+(totSBStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-passSBStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer]))*effStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer]*effStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer])/(totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-totSBStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]);
						//effStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer] = (passStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer]-passSBStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer])/(totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-totSBStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]);
						//effSigmaStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer] = sqrt(((passStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer]+passSBStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer])*(1.-effStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer])*(1.-effStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer]))+ ((totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-passStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer])+(totSBStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-passSBStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer]))*effStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer]*effStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer])/(totStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]-totSBStationRingChamberLayer[iiStation][iiRing][iiChamber][iiLayer]);
					}




					segEff2DStationRingChamberLayer[iiStation][iiRing]->SetBinContent(iiChamber,iiLayer+1,effStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer]);
					segEff2DStationRingChamberLayer[iiStation][iiRing]->SetBinError(iiChamber,iiLayer+1,effSigmaStationRingChamberLayerSeg[iiStation][iiRing][iiChamber][iiLayer]);
					//LCTEff2DStationRingChamberLayer[iiStation][iiRing]->SetBinContent(iiChamber,iiLayer+1,effStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer]);
					//LCTEff2DStationRingChamberLayer[iiStation][iiRing]->SetBinError(iiChamber,iiLayer+1,effSigmaStationRingChamberLayerLCT[iiStation][iiRing][iiChamber][iiLayer]);

				}

				segEff2DStationRingChamberLayer[iiStation][iiRing]->Write();
				LCTEff2DStationRingChamberLayer[iiStation][iiRing]->Write();






				for (Int_t iiDCFEB=0; iiDCFEB< numDCFEBBins; iiDCFEB++){

					if ((totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]>0.5)&&((totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-totSBStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB])>0.5)) {
						effStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB] = (passStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB]-passSBStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB])/(totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-totSBStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]);
						effSigmaStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB] = sqrt(((passStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB]+passSBStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB])*(1.-effStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB])*(1.-effStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB]))+ ((totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-passStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB])+(totSBStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-passSBStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB]))*effStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB]*effStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB])/(totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-totSBStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]);
						effStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB] = (passStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB]-passSBStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB])/(totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-totSBStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]);
						effSigmaStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB] = sqrt(((passStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB]+passSBStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB])*(1.-effStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB])*(1.-effStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB]))+ ((totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-passStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB])+(totSBStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-passSBStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB]))*effStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB]*effStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB])/(totStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]-totSBStationRingChamberDCFEB[iiStation][iiRing][iiChamber][iiDCFEB]);
					}




					segEff2DStationRingChamberDCFEB[iiStation][iiRing]->SetBinContent(iiChamber,iiDCFEB+1,effStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB]);
					segEff2DStationRingChamberDCFEB[iiStation][iiRing]->SetBinError(iiChamber,iiDCFEB+1,effSigmaStationRingChamberDCFEBSeg[iiStation][iiRing][iiChamber][iiDCFEB]);
					LCTEff2DStationRingChamberDCFEB[iiStation][iiRing]->SetBinContent(iiChamber,iiDCFEB+1,effStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB]);
					LCTEff2DStationRingChamberDCFEB[iiStation][iiRing]->SetBinError(iiChamber,iiDCFEB+1,effSigmaStationRingChamberDCFEBLCT[iiStation][iiRing][iiChamber][iiDCFEB]);

				}

				segEff2DStationRingChamberDCFEB[iiStation][iiRing]->Write();
				LCTEff2DStationRingChamberDCFEB[iiStation][iiRing]->Write();

			}



			for (Int_t iiPt=0; iiPt< numPtBins; iiPt++){
				//if (totStationRingPt[iiStation][iiRing][iiPt]>0.5)  effStationRingPtSeg[iiStation][iiRing][iiPt] = passStationRingPtSeg[iiStation][iiRing][iiPt]/totStationRingPt[iiStation][iiRing][iiPt];
				//if (totStationRingPt[iiStation][iiRing][iiPt]>0.5) effSigmaStationRingPtSeg[iiStation][iiRing][iiPt] = sqrt(effStationRingPtSeg[iiStation][iiRing][iiPt]*(1.0-effStationRingPtSeg[iiStation][iiRing][iiPt])/totStationRingPt[iiStation][iiRing][iiPt]);
				//std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " Pt Bin " << iiPt << std::endl;
				//std::cout << "tot: " << totStationRingPt[iiStation][iiRing][iiPt] << std::endl;
				//std::cout << "eff: " << effStationRingPtSeg[iiStation][iiRing][iiPt] << " +/- " << effSigmaStationRingPtSeg[iiStation][iiRing][iiPt] << std::endl;

				if (DoubleMuGun) totSBStationRingPt[iiStation][iiRing][iiPt] = 1.0;
				if (LowStats) totSBStationRingPt[iiStation][iiRing][iiPt] = 0.0000001;
				if (LowStats) passSBStationRingPtSeg[iiStation][iiRing][iiPt] = 0.0000001;
				if (LowStats) passSBStationRingPtLCT[iiStation][iiRing][iiPt] = 0.0000001;
				if (iiStation<4&&LowStats) {
					totSBStationRingPt[iiStation+4][iiRing][iiPt] = 0.0000001;
					passSBStationRingPtSeg[iiStation+4][iiRing][iiPt] = 0.0000001;
					passSBStationRingPtLCT[iiStation+4][iiRing][iiPt] = 0.0000001;
				}

				if ((totStationRingPt[iiStation][iiRing][iiPt]>0.0000005)&&((totStationRingPt[iiStation][iiRing][iiPt]-totSBStationRingPt[iiStation][iiRing][iiPt])>0.0000005)) {
					effStationRingPtSeg[iiStation][iiRing][iiPt] = (passStationRingPtSeg[iiStation][iiRing][iiPt]-passSBStationRingPtSeg[iiStation][iiRing][iiPt])/(totStationRingPt[iiStation][iiRing][iiPt]-totSBStationRingPt[iiStation][iiRing][iiPt]);
					effSigmaStationRingPtSeg[iiStation][iiRing][iiPt] = sqrt(((passStationRingPtSeg[iiStation][iiRing][iiPt]+passSBStationRingPtSeg[iiStation][iiRing][iiPt])*(1.-effStationRingPtSeg[iiStation][iiRing][iiPt])*(1.-effStationRingPtSeg[iiStation][iiRing][iiPt]))+ ((totStationRingPt[iiStation][iiRing][iiPt]-passStationRingPtSeg[iiStation][iiRing][iiPt])+(totSBStationRingPt[iiStation][iiRing][iiPt]-passSBStationRingPtSeg[iiStation][iiRing][iiPt]))*effStationRingPtSeg[iiStation][iiRing][iiPt]*effStationRingPtSeg[iiStation][iiRing][iiPt])/(totStationRingPt[iiStation][iiRing][iiPt]-totSBStationRingPt[iiStation][iiRing][iiPt]);

					effStationRingPtLCT[iiStation][iiRing][iiPt] = (passStationRingPtLCT[iiStation][iiRing][iiPt]-passSBStationRingPtLCT[iiStation][iiRing][iiPt])/(totStationRingPt[iiStation][iiRing][iiPt]-totSBStationRingPt[iiStation][iiRing][iiPt]);
					effSigmaStationRingPtLCT[iiStation][iiRing][iiPt] = sqrt(((passStationRingPtLCT[iiStation][iiRing][iiPt]+passSBStationRingPtLCT[iiStation][iiRing][iiPt])*(1.-effStationRingPtLCT[iiStation][iiRing][iiPt])*(1.-effStationRingPtLCT[iiStation][iiRing][iiPt]))+ ((totStationRingPt[iiStation][iiRing][iiPt]-passStationRingPtLCT[iiStation][iiRing][iiPt])+(totSBStationRingPt[iiStation][iiRing][iiPt]-passSBStationRingPtLCT[iiStation][iiRing][iiPt]))*effStationRingPtLCT[iiStation][iiRing][iiPt]*effStationRingPtLCT[iiStation][iiRing][iiPt])/(totStationRingPt[iiStation][iiRing][iiPt]-totSBStationRingPt[iiStation][iiRing][iiPt]);

				}

				if ((iiStation<4)&&((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])>0.00000005)&&(((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])-(totSBStationRingPt[iiStation][iiRing][iiPt]+totSBStationRingPt[iiStation+4][iiRing][iiPt]))>0.0000005)) {
					effStationCRingPtSeg[iiStation][iiRing][iiPt] = ((passStationRingPtSeg[iiStation][iiRing][iiPt]+passStationRingPtSeg[iiStation+4][iiRing][iiPt])-(passSBStationRingPtSeg[iiStation][iiRing][iiPt]+passSBStationRingPtSeg[iiStation+4][iiRing][iiPt]))/((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])-(totSBStationRingPt[iiStation][iiRing][iiPt]+totSBStationRingPt[iiStation+4][iiRing][iiPt]));
					effSigmaStationCRingPtSeg[iiStation][iiRing][iiPt] = sqrt((((passStationRingPtSeg[iiStation][iiRing][iiPt]+passStationRingPtSeg[iiStation+4][iiRing][iiPt])+(passSBStationRingPtSeg[iiStation][iiRing][iiPt]+passSBStationRingPtSeg[iiStation+4][iiRing][iiPt]))*(1.-effStationCRingPtSeg[iiStation][iiRing][iiPt])*(1.-effStationCRingPtSeg[iiStation][iiRing][iiPt]))+ (((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])-(passStationRingPtSeg[iiStation][iiRing][iiPt]+passStationRingPtSeg[iiStation+4][iiRing][iiPt]))+((totSBStationRingPt[iiStation][iiRing][iiPt]+totSBStationRingPt[iiStation+4][iiRing][iiPt])-(passSBStationRingPtSeg[iiStation][iiRing][iiPt]+passSBStationRingPtSeg[iiStation+4][iiRing][iiPt])))*effStationCRingPtSeg[iiStation][iiRing][iiPt]*effStationCRingPtSeg[iiStation][iiRing][iiPt])/((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])-(totSBStationRingPt[iiStation][iiRing][iiPt]+totSBStationRingPt[iiStation+4][iiRing][iiPt]));

					effStationCRingPtLCT[iiStation][iiRing][iiPt] = ((passStationRingPtLCT[iiStation][iiRing][iiPt]+passStationRingPtLCT[iiStation+4][iiRing][iiPt])-(passSBStationRingPtLCT[iiStation][iiRing][iiPt]+passSBStationRingPtLCT[iiStation+4][iiRing][iiPt]))/((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])-(totSBStationRingPt[iiStation][iiRing][iiPt]+totSBStationRingPt[iiStation+4][iiRing][iiPt]));
					effSigmaStationCRingPtLCT[iiStation][iiRing][iiPt] = sqrt((((passStationRingPtLCT[iiStation][iiRing][iiPt]+passStationRingPtLCT[iiStation+4][iiRing][iiPt])+(passSBStationRingPtLCT[iiStation][iiRing][iiPt]+passSBStationRingPtLCT[iiStation+4][iiRing][iiPt]))*(1.-effStationCRingPtLCT[iiStation][iiRing][iiPt])*(1.-effStationCRingPtLCT[iiStation][iiRing][iiPt]))+ (((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])-(passStationRingPtLCT[iiStation][iiRing][iiPt]+passStationRingPtLCT[iiStation+4][iiRing][iiPt]))+((totSBStationRingPt[iiStation][iiRing][iiPt]+totSBStationRingPt[iiStation+4][iiRing][iiPt])-(passSBStationRingPtLCT[iiStation][iiRing][iiPt]+passSBStationRingPtLCT[iiStation+4][iiRing][iiPt])))*effStationCRingPtLCT[iiStation][iiRing][iiPt]*effStationCRingPtLCT[iiStation][iiRing][iiPt])/((totStationRingPt[iiStation][iiRing][iiPt]+totStationRingPt[iiStation+4][iiRing][iiPt])-(totSBStationRingPt[iiStation][iiRing][iiPt]+totSBStationRingPt[iiStation+4][iiRing][iiPt]));
				}

				segEffStationRingPT[iiStation][iiRing]->SetBinContent(iiPt+1,effStationRingPtSeg[iiStation][iiRing][iiPt]);
				segEffStationRingPT[iiStation][iiRing]->SetBinError(iiPt+1,effSigmaStationRingPtSeg[iiStation][iiRing][iiPt]);
				LCTEffStationRingPT[iiStation][iiRing]->SetBinContent(iiPt+1,effStationRingPtLCT[iiStation][iiRing][iiPt]);
				LCTEffStationRingPT[iiStation][iiRing]->SetBinError(iiPt+1,effSigmaStationRingPtLCT[iiStation][iiRing][iiPt]);
				if (iiStation<4){
					segEffStationCRingPT[iiStation][iiRing]->SetBinContent(iiPt+1,effStationCRingPtSeg[iiStation][iiRing][iiPt]);
					segEffStationCRingPT[iiStation][iiRing]->SetBinError(iiPt+1,effSigmaStationCRingPtSeg[iiStation][iiRing][iiPt]);
					LCTEffStationCRingPT[iiStation][iiRing]->SetBinContent(iiPt+1,effStationCRingPtLCT[iiStation][iiRing][iiPt]);
					LCTEffStationCRingPT[iiStation][iiRing]->SetBinError(iiPt+1,effSigmaStationCRingPtLCT[iiStation][iiRing][iiPt]);
				}
			}
			segEffStationRingPT[iiStation][iiRing]->Write();
			LCTEffStationRingPT[iiStation][iiRing]->Write();
			if (iiStation<4){
				segEffStationRingPT[iiStation][iiRing]->Write();
				LCTEffStationRingPT[iiStation][iiRing]->Write();
			}


			for (Int_t iiEta=0; iiEta< numEtaBins; iiEta++){
				//if (totStationRingEta[iiStation][iiRing][iiEta]>0.5)  effStationRingEtaSeg[iiStation][iiRing][iiEta] = passStationRingEtaSeg[iiStation][iiRing][iiEta]/totStationRingEta[iiStation][iiRing][iiEta];
				//if (totStationRingEta[iiStation][iiRing][iiEta]>0.5) effSigmaStationRingEtaSeg[iiStation][iiRing][iiEta] = sqrt(effStationRingEtaSeg[iiStation][iiRing][iiEta]*(1.0-effStationRingEtaSeg[iiStation][iiRing][iiEta])/totStationRingEta[iiStation][iiRing][iiEta]);
				//std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " Eta Bin " << iiEta << std::endl;
				//std::cout << "tot: " << totStationRingEta[iiStation][iiRing][iiEta] << std::endl;
				//std::cout << "eff: " << effStationRingEtaSeg[iiStation][iiRing][iiEta] << " +/- " << effSigmaStationRingEtaSeg[iiStation][iiRing][iiEta] << std::endl;
				if (DoubleMuGun) totSBStationRingEta[iiStation][iiRing][iiEta] = 1.0;
				if (LowStats) totSBStationRingEta[iiStation][iiRing][iiEta] = 0.0000001;
				if (LowStats) passSBStationRingEtaSeg[iiStation][iiRing][iiEta] = 0.0000001;
				if (LowStats) passSBStationRingEtaLCT[iiStation][iiRing][iiEta] = 0.0000001;
				if (iiStation<4&&LowStats) {
					totSBStationRingEta[iiStation+4][iiRing][iiEta] = 0.0000001;
					passSBStationRingEtaSeg[iiStation+4][iiRing][iiEta] = 0.0000001;
					passSBStationRingEtaLCT[iiStation+4][iiRing][iiEta] = 0.0000001;
				}

				if ((totStationRingEta[iiStation][iiRing][iiEta]>0.0000005)&&((totStationRingEta[iiStation][iiRing][iiEta]-totSBStationRingEta[iiStation][iiRing][iiEta])>0.0000005)) {
					effStationRingEtaSeg[iiStation][iiRing][iiEta] = (passStationRingEtaSeg[iiStation][iiRing][iiEta]-passSBStationRingEtaSeg[iiStation][iiRing][iiEta])/(totStationRingEta[iiStation][iiRing][iiEta]-totSBStationRingEta[iiStation][iiRing][iiEta]);
					effSigmaStationRingEtaSeg[iiStation][iiRing][iiEta] = sqrt(((passStationRingEtaSeg[iiStation][iiRing][iiEta]+passSBStationRingEtaSeg[iiStation][iiRing][iiEta])*(1.-effStationRingEtaSeg[iiStation][iiRing][iiEta])*(1.-effStationRingEtaSeg[iiStation][iiRing][iiEta]))+ ((totStationRingEta[iiStation][iiRing][iiEta]-passStationRingEtaSeg[iiStation][iiRing][iiEta])+(totSBStationRingEta[iiStation][iiRing][iiEta]-passSBStationRingEtaSeg[iiStation][iiRing][iiEta]))*effStationRingEtaSeg[iiStation][iiRing][iiEta]*effStationRingEtaSeg[iiStation][iiRing][iiEta])/(totStationRingEta[iiStation][iiRing][iiEta]-totSBStationRingEta[iiStation][iiRing][iiEta]);
					effStationRingEtaLCT[iiStation][iiRing][iiEta] = (passStationRingEtaLCT[iiStation][iiRing][iiEta]-passSBStationRingEtaLCT[iiStation][iiRing][iiEta])/(totStationRingEta[iiStation][iiRing][iiEta]-totSBStationRingEta[iiStation][iiRing][iiEta]);
					effSigmaStationRingEtaLCT[iiStation][iiRing][iiEta] = sqrt(((passStationRingEtaLCT[iiStation][iiRing][iiEta]+passSBStationRingEtaLCT[iiStation][iiRing][iiEta])*(1.-effStationRingEtaLCT[iiStation][iiRing][iiEta])*(1.-effStationRingEtaLCT[iiStation][iiRing][iiEta]))+ ((totStationRingEta[iiStation][iiRing][iiEta]-passStationRingEtaLCT[iiStation][iiRing][iiEta])+(totSBStationRingEta[iiStation][iiRing][iiEta]-passSBStationRingEtaLCT[iiStation][iiRing][iiEta]))*effStationRingEtaLCT[iiStation][iiRing][iiEta]*effStationRingEtaLCT[iiStation][iiRing][iiEta])/(totStationRingEta[iiStation][iiRing][iiEta]-totSBStationRingEta[iiStation][iiRing][iiEta]);
				}

				if ((iiStation<4)&&((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])>0.0000005)&&(((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])-(totSBStationRingEta[iiStation][iiRing][iiEta]+totSBStationRingEta[iiStation+4][iiRing][iiEta]))>0000000.5)) {
					effStationCRingEtaSeg[iiStation][iiRing][iiEta] = ((passStationRingEtaSeg[iiStation][iiRing][iiEta]+passStationRingEtaSeg[iiStation+4][iiRing][iiEta])-(passSBStationRingEtaSeg[iiStation][iiRing][iiEta]+passSBStationRingEtaSeg[iiStation+4][iiRing][iiEta]))/((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])-(totSBStationRingEta[iiStation][iiRing][iiEta]+totSBStationRingEta[iiStation+4][iiRing][iiEta]));
					effSigmaStationCRingEtaSeg[iiStation][iiRing][iiEta] = sqrt((((passStationRingEtaSeg[iiStation][iiRing][iiEta]+passStationRingEtaSeg[iiStation+4][iiRing][iiEta])+(passSBStationRingEtaSeg[iiStation][iiRing][iiEta]+passSBStationRingEtaSeg[iiStation+4][iiRing][iiEta]))*(1.-effStationCRingEtaSeg[iiStation][iiRing][iiEta])*(1.-effStationCRingEtaSeg[iiStation][iiRing][iiEta]))+ (((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])-(passStationRingEtaSeg[iiStation][iiRing][iiEta]+passStationRingEtaSeg[iiStation+4][iiRing][iiEta]))+((totSBStationRingEta[iiStation][iiRing][iiEta]+totSBStationRingEta[iiStation+4][iiRing][iiEta])-(passSBStationRingEtaSeg[iiStation][iiRing][iiEta]+passSBStationRingEtaSeg[iiStation+4][iiRing][iiEta])))*effStationCRingEtaSeg[iiStation][iiRing][iiEta]*effStationCRingEtaSeg[iiStation][iiRing][iiEta])/((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])-(totSBStationRingEta[iiStation][iiRing][iiEta]+totSBStationRingEta[iiStation+4][iiRing][iiEta]));

					effStationCRingEtaLCT[iiStation][iiRing][iiEta] = ((passStationRingEtaLCT[iiStation][iiRing][iiEta]+passStationRingEtaLCT[iiStation+4][iiRing][iiEta])-(passSBStationRingEtaLCT[iiStation][iiRing][iiEta]+passSBStationRingEtaLCT[iiStation+4][iiRing][iiEta]))/((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])-(totSBStationRingEta[iiStation][iiRing][iiEta]+totSBStationRingEta[iiStation+4][iiRing][iiEta]));
					effSigmaStationCRingEtaLCT[iiStation][iiRing][iiEta] = sqrt((((passStationRingEtaLCT[iiStation][iiRing][iiEta]+passStationRingEtaLCT[iiStation+4][iiRing][iiEta])+(passSBStationRingEtaLCT[iiStation][iiRing][iiEta]+passSBStationRingEtaLCT[iiStation+4][iiRing][iiEta]))*(1.-effStationCRingEtaLCT[iiStation][iiRing][iiEta])*(1.-effStationCRingEtaLCT[iiStation][iiRing][iiEta]))+ (((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])-(passStationRingEtaLCT[iiStation][iiRing][iiEta]+passStationRingEtaLCT[iiStation+4][iiRing][iiEta]))+((totSBStationRingEta[iiStation][iiRing][iiEta]+totSBStationRingEta[iiStation+4][iiRing][iiEta])-(passSBStationRingEtaLCT[iiStation][iiRing][iiEta]+passSBStationRingEtaLCT[iiStation+4][iiRing][iiEta])))*effStationCRingEtaLCT[iiStation][iiRing][iiEta]*effStationCRingEtaLCT[iiStation][iiRing][iiEta])/((totStationRingEta[iiStation][iiRing][iiEta]+totStationRingEta[iiStation+4][iiRing][iiEta])-(totSBStationRingEta[iiStation][iiRing][iiEta]+totSBStationRingEta[iiStation+4][iiRing][iiEta]));
				}


				segEffStationRingEta[iiStation][iiRing]->SetBinContent(iiEta+1,effStationRingEtaSeg[iiStation][iiRing][iiEta]);
				segEffStationRingEta[iiStation][iiRing]->SetBinError(iiEta+1,effSigmaStationRingEtaSeg[iiStation][iiRing][iiEta]);
				LCTEffStationRingEta[iiStation][iiRing]->SetBinContent(iiEta+1,effStationRingEtaLCT[iiStation][iiRing][iiEta]);
				LCTEffStationRingEta[iiStation][iiRing]->SetBinError(iiEta+1,effSigmaStationRingEtaLCT[iiStation][iiRing][iiEta]);

				if (iiStation < 4) {
					segEffStationCRingEta[iiStation][iiRing]->SetBinContent(iiEta+1,effStationCRingEtaSeg[iiStation][iiRing][iiEta]);
					segEffStationCRingEta[iiStation][iiRing]->SetBinError(iiEta+1,effSigmaStationCRingEtaSeg[iiStation][iiRing][iiEta]);
					LCTEffStationCRingEta[iiStation][iiRing]->SetBinContent(iiEta+1,effStationCRingEtaLCT[iiStation][iiRing][iiEta]);
					LCTEffStationCRingEta[iiStation][iiRing]->SetBinError(iiEta+1,effSigmaStationCRingEtaLCT[iiStation][iiRing][iiEta]);
				}


			}
			segEffStationRingEta[iiStation][iiRing]->Write();
			LCTEffStationRingEta[iiStation][iiRing]->Write();

			if (iiStation < 4) {
				segEffStationCRingEta[iiStation][iiRing]->Write();
				LCTEffStationCRingEta[iiStation][iiRing]->Write();
			}


			for (Int_t iiIso=0; iiIso< numIsoBins; iiIso++){
				//if (totStationRingIso[iiStation][iiRing][iiIso]>0.5)  effStationRingIsoSeg[iiStation][iiRing][iiIso] = passStationRingIsoSeg[iiStation][iiRing][iiIso]/totStationRingIso[iiStation][iiRing][iiIso];
				//if (totStationRingIso[iiStation][iiRing][iiIso]>0.5) effSigmaStationRingIsoSeg[iiStation][iiRing][iiIso] = sqrt(effStationRingIsoSeg[iiStation][iiRing][iiIso]*(1.0-effStationRingIsoSeg[iiStation][iiRing][iiIso])/totStationRingIso[iiStation][iiRing][iiIso]);
				//std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " Iso Bin " << iiIso << std::endl;
				//std::cout << "tot: " << totStationRingIso[iiStation][iiRing][iiIso] << std::endl;
				//std::cout << "eff: " << effStationRingIsoSeg[iiStation][iiRing][iiIso] << " +/- " << effSigmaStationRingIsoSeg[iiStation][iiRing][iiIso] << std::endl;

				if ((totStationRingIso[iiStation][iiRing][iiIso]>0.5)&&((totStationRingIso[iiStation][iiRing][iiIso]-totSBStationRingIso[iiStation][iiRing][iiIso])>0.5)) {
					effStationRingIsoSeg[iiStation][iiRing][iiIso] = (passStationRingIsoSeg[iiStation][iiRing][iiIso]-passSBStationRingIsoSeg[iiStation][iiRing][iiIso])/(totStationRingIso[iiStation][iiRing][iiIso]-totSBStationRingIso[iiStation][iiRing][iiIso]);
					effSigmaStationRingIsoSeg[iiStation][iiRing][iiIso] = sqrt(((passStationRingIsoSeg[iiStation][iiRing][iiIso]+passSBStationRingIsoSeg[iiStation][iiRing][iiIso])*(1.-effStationRingIsoSeg[iiStation][iiRing][iiIso])*(1.-effStationRingIsoSeg[iiStation][iiRing][iiIso]))+ ((totStationRingIso[iiStation][iiRing][iiIso]-passStationRingIsoSeg[iiStation][iiRing][iiIso])+(totSBStationRingIso[iiStation][iiRing][iiIso]-passSBStationRingIsoSeg[iiStation][iiRing][iiIso]))*effStationRingIsoSeg[iiStation][iiRing][iiIso]*effStationRingIsoSeg[iiStation][iiRing][iiIso])/(totStationRingIso[iiStation][iiRing][iiIso]-totSBStationRingIso[iiStation][iiRing][iiIso]);
					effStationRingIsoLCT[iiStation][iiRing][iiIso] = (passStationRingIsoLCT[iiStation][iiRing][iiIso]-passSBStationRingIsoLCT[iiStation][iiRing][iiIso])/(totStationRingIso[iiStation][iiRing][iiIso]-totSBStationRingIso[iiStation][iiRing][iiIso]);
					effSigmaStationRingIsoLCT[iiStation][iiRing][iiIso] = sqrt(((passStationRingIsoLCT[iiStation][iiRing][iiIso]+passSBStationRingIsoLCT[iiStation][iiRing][iiIso])*(1.-effStationRingIsoLCT[iiStation][iiRing][iiIso])*(1.-effStationRingIsoLCT[iiStation][iiRing][iiIso]))+ ((totStationRingIso[iiStation][iiRing][iiIso]-passStationRingIsoLCT[iiStation][iiRing][iiIso])+(totSBStationRingIso[iiStation][iiRing][iiIso]-passSBStationRingIsoLCT[iiStation][iiRing][iiIso]))*effStationRingIsoLCT[iiStation][iiRing][iiIso]*effStationRingIsoLCT[iiStation][iiRing][iiIso])/(totStationRingIso[iiStation][iiRing][iiIso]-totSBStationRingIso[iiStation][iiRing][iiIso]);
				}

				if ((iiStation<4)&&((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])>0.5)&&(((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])-(totSBStationRingIso[iiStation][iiRing][iiIso]+totSBStationRingIso[iiStation+4][iiRing][iiIso]))>0.5)) {
					effStationCRingIsoSeg[iiStation][iiRing][iiIso] = ((passStationRingIsoSeg[iiStation][iiRing][iiIso]+passStationRingIsoSeg[iiStation+4][iiRing][iiIso])-(passSBStationRingIsoSeg[iiStation][iiRing][iiIso]+passSBStationRingIsoSeg[iiStation+4][iiRing][iiIso]))/((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])-(totSBStationRingIso[iiStation][iiRing][iiIso]+totSBStationRingIso[iiStation+4][iiRing][iiIso]));
					effSigmaStationCRingIsoSeg[iiStation][iiRing][iiIso] = sqrt((((passStationRingIsoSeg[iiStation][iiRing][iiIso]+passStationRingIsoSeg[iiStation+4][iiRing][iiIso])+(passSBStationRingIsoSeg[iiStation][iiRing][iiIso]+passSBStationRingIsoSeg[iiStation+4][iiRing][iiIso]))*(1.-effStationCRingIsoSeg[iiStation][iiRing][iiIso])*(1.-effStationCRingIsoSeg[iiStation][iiRing][iiIso]))+ (((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])-(passStationRingIsoSeg[iiStation][iiRing][iiIso]+passStationRingIsoSeg[iiStation+4][iiRing][iiIso]))+((totSBStationRingIso[iiStation][iiRing][iiIso]+totSBStationRingIso[iiStation+4][iiRing][iiIso])-(passSBStationRingIsoSeg[iiStation][iiRing][iiIso]+passSBStationRingIsoSeg[iiStation+4][iiRing][iiIso])))*effStationCRingIsoSeg[iiStation][iiRing][iiIso]*effStationCRingIsoSeg[iiStation][iiRing][iiIso])/((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])-(totSBStationRingIso[iiStation][iiRing][iiIso]+totSBStationRingIso[iiStation+4][iiRing][iiIso]));

					effStationCRingIsoLCT[iiStation][iiRing][iiIso] = ((passStationRingIsoLCT[iiStation][iiRing][iiIso]+passStationRingIsoLCT[iiStation+4][iiRing][iiIso])-(passSBStationRingIsoLCT[iiStation][iiRing][iiIso]+passSBStationRingIsoLCT[iiStation+4][iiRing][iiIso]))/((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])-(totSBStationRingIso[iiStation][iiRing][iiIso]+totSBStationRingIso[iiStation+4][iiRing][iiIso]));
					effSigmaStationCRingIsoLCT[iiStation][iiRing][iiIso] = sqrt((((passStationRingIsoLCT[iiStation][iiRing][iiIso]+passStationRingIsoLCT[iiStation+4][iiRing][iiIso])+(passSBStationRingIsoLCT[iiStation][iiRing][iiIso]+passSBStationRingIsoLCT[iiStation+4][iiRing][iiIso]))*(1.-effStationCRingIsoLCT[iiStation][iiRing][iiIso])*(1.-effStationCRingIsoLCT[iiStation][iiRing][iiIso]))+ (((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])-(passStationRingIsoLCT[iiStation][iiRing][iiIso]+passStationRingIsoLCT[iiStation+4][iiRing][iiIso]))+((totSBStationRingIso[iiStation][iiRing][iiIso]+totSBStationRingIso[iiStation+4][iiRing][iiIso])-(passSBStationRingIsoLCT[iiStation][iiRing][iiIso]+passSBStationRingIsoLCT[iiStation+4][iiRing][iiIso])))*effStationCRingIsoLCT[iiStation][iiRing][iiIso]*effStationCRingIsoLCT[iiStation][iiRing][iiIso])/((totStationRingIso[iiStation][iiRing][iiIso]+totStationRingIso[iiStation+4][iiRing][iiIso])-(totSBStationRingIso[iiStation][iiRing][iiIso]+totSBStationRingIso[iiStation+4][iiRing][iiIso]));
				}

				segEffStationRingIso[iiStation][iiRing]->SetBinContent(iiIso+1,effStationRingIsoSeg[iiStation][iiRing][iiIso]);
				segEffStationRingIso[iiStation][iiRing]->SetBinError(iiIso+1,effSigmaStationRingIsoSeg[iiStation][iiRing][iiIso]);
				LCTEffStationRingIso[iiStation][iiRing]->SetBinContent(iiIso+1,effStationRingIsoLCT[iiStation][iiRing][iiIso]);
				LCTEffStationRingIso[iiStation][iiRing]->SetBinError(iiIso+1,effSigmaStationRingIsoLCT[iiStation][iiRing][iiIso]);
				if (iiStation < 4){
					segEffStationCRingIso[iiStation][iiRing]->SetBinContent(iiIso+1,effStationCRingIsoSeg[iiStation][iiRing][iiIso]);
					segEffStationCRingIso[iiStation][iiRing]->SetBinError(iiIso+1,effSigmaStationCRingIsoSeg[iiStation][iiRing][iiIso]);
					LCTEffStationCRingIso[iiStation][iiRing]->SetBinContent(iiIso+1,effStationCRingIsoLCT[iiStation][iiRing][iiIso]);
					LCTEffStationCRingIso[iiStation][iiRing]->SetBinError(iiIso+1,effSigmaStationCRingIsoLCT[iiStation][iiRing][iiIso]);
				}



			}
			segEffStationRingIso[iiStation][iiRing]->Write();
			LCTEffStationRingIso[iiStation][iiRing]->Write();

			if (iiStation<4){
				segEffStationCRingIso[iiStation][iiRing]->Write();
				LCTEffStationCRingIso[iiStation][iiRing]->Write();
			}




			for (Int_t iiPV=0; iiPV< numPVBins; iiPV++){
				//if (totStationRingPV[iiStation][iiRing][iiPV]>0.5)  effStationRingPVSeg[iiStation][iiRing][iiPV] = passStationRingPVSeg[iiStation][iiRing][iiPV]/totStationRingPV[iiStation][iiRing][iiPV];
				//if (totStationRingPV[iiStation][iiRing][iiPV]>0.5) effSigmaStationRingPVSeg[iiStation][iiRing][iiPV] = sqrt(effStationRingPVSeg[iiStation][iiRing][iiPV]*(1.0-effStationRingPVSeg[iiStation][iiRing][iiPV])/totStationRingPV[iiStation][iiRing][iiPV]);
				//std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " PV Bin " << iiPV << std::endl;
				//std::cout << "tot: " << totStationRingPV[iiStation][iiRing][iiPV] << std::endl;
				//std::cout << "eff: " << effStationRingPVSeg[iiStation][iiRing][iiPV] << " +/- " << effSigmaStationRingPVSeg[iiStation][iiRing][iiPV] << std::endl;


				if (LowStats) totSBStationRingPt[iiStation][iiRing][iiPV] = 0.0000001;
				if (LowStats) passSBStationRingPtSeg[iiStation][iiRing][iiPV] = 0.0000001;
				if (LowStats) passSBStationRingPtLCT[iiStation][iiRing][iiPV] = 0.0000001;
				if (iiStation<4&&LowStats) {
					totSBStationRingPt[iiStation+4][iiRing][iiPV] = 0.0000001;
					passSBStationRingPtSeg[iiStation+4][iiRing][iiPV] = 0.0000001;
					passSBStationRingPtLCT[iiStation+4][iiRing][iiPV] = 0.0000001;
				}


				if ((totStationRingPV[iiStation][iiRing][iiPV]>0.5)&&((totStationRingPV[iiStation][iiRing][iiPV]-totSBStationRingPV[iiStation][iiRing][iiPV])>0.5)) {
					effStationRingPVSeg[iiStation][iiRing][iiPV] = (passStationRingPVSeg[iiStation][iiRing][iiPV]-passSBStationRingPVSeg[iiStation][iiRing][iiPV])/(totStationRingPV[iiStation][iiRing][iiPV]-totSBStationRingPV[iiStation][iiRing][iiPV]);
					effSigmaStationRingPVSeg[iiStation][iiRing][iiPV] = sqrt(((passStationRingPVSeg[iiStation][iiRing][iiPV]+passSBStationRingPVSeg[iiStation][iiRing][iiPV])*(1.-effStationRingPVSeg[iiStation][iiRing][iiPV])*(1.-effStationRingPVSeg[iiStation][iiRing][iiPV]))+ ((totStationRingPV[iiStation][iiRing][iiPV]-passStationRingPVSeg[iiStation][iiRing][iiPV])+(totSBStationRingPV[iiStation][iiRing][iiPV]-passSBStationRingPVSeg[iiStation][iiRing][iiPV]))*effStationRingPVSeg[iiStation][iiRing][iiPV]*effStationRingPVSeg[iiStation][iiRing][iiPV])/(totStationRingPV[iiStation][iiRing][iiPV]-totSBStationRingPV[iiStation][iiRing][iiPV]);
					effStationRingPVLCT[iiStation][iiRing][iiPV] = (passStationRingPVLCT[iiStation][iiRing][iiPV]-passSBStationRingPVLCT[iiStation][iiRing][iiPV])/(totStationRingPV[iiStation][iiRing][iiPV]-totSBStationRingPV[iiStation][iiRing][iiPV]);
					effSigmaStationRingPVLCT[iiStation][iiRing][iiPV] = sqrt(((passStationRingPVLCT[iiStation][iiRing][iiPV]+passSBStationRingPVLCT[iiStation][iiRing][iiPV])*(1.-effStationRingPVLCT[iiStation][iiRing][iiPV])*(1.-effStationRingPVLCT[iiStation][iiRing][iiPV]))+ ((totStationRingPV[iiStation][iiRing][iiPV]-passStationRingPVLCT[iiStation][iiRing][iiPV])+(totSBStationRingPV[iiStation][iiRing][iiPV]-passSBStationRingPVLCT[iiStation][iiRing][iiPV]))*effStationRingPVLCT[iiStation][iiRing][iiPV]*effStationRingPVLCT[iiStation][iiRing][iiPV])/(totStationRingPV[iiStation][iiRing][iiPV]-totSBStationRingPV[iiStation][iiRing][iiPV]);
				}

				if ((iiStation<4)&&((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])>0.5)&&(((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])-(totSBStationRingPV[iiStation][iiRing][iiPV]+totSBStationRingPV[iiStation+4][iiRing][iiPV]))>0.5)) {
					effStationCRingPVSeg[iiStation][iiRing][iiPV] = ((passStationRingPVSeg[iiStation][iiRing][iiPV]+passStationRingPVSeg[iiStation+4][iiRing][iiPV])-(passSBStationRingPVSeg[iiStation][iiRing][iiPV]+passSBStationRingPVSeg[iiStation+4][iiRing][iiPV]))/((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])-(totSBStationRingPV[iiStation][iiRing][iiPV]+totSBStationRingPV[iiStation+4][iiRing][iiPV]));
					effSigmaStationCRingPVSeg[iiStation][iiRing][iiPV] = sqrt((((passStationRingPVSeg[iiStation][iiRing][iiPV]+passStationRingPVSeg[iiStation+4][iiRing][iiPV])+(passSBStationRingPVSeg[iiStation][iiRing][iiPV]+passSBStationRingPVSeg[iiStation+4][iiRing][iiPV]))*(1.-effStationCRingPVSeg[iiStation][iiRing][iiPV])*(1.-effStationCRingPVSeg[iiStation][iiRing][iiPV]))+ (((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])-(passStationRingPVSeg[iiStation][iiRing][iiPV]+passStationRingPVSeg[iiStation+4][iiRing][iiPV]))+((totSBStationRingPV[iiStation][iiRing][iiPV]+totSBStationRingPV[iiStation+4][iiRing][iiPV])-(passSBStationRingPVSeg[iiStation][iiRing][iiPV]+passSBStationRingPVSeg[iiStation+4][iiRing][iiPV])))*effStationCRingPVSeg[iiStation][iiRing][iiPV]*effStationCRingPVSeg[iiStation][iiRing][iiPV])/((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])-(totSBStationRingPV[iiStation][iiRing][iiPV]+totSBStationRingPV[iiStation+4][iiRing][iiPV]));

					effStationCRingPVLCT[iiStation][iiRing][iiPV] = ((passStationRingPVLCT[iiStation][iiRing][iiPV]+passStationRingPVLCT[iiStation+4][iiRing][iiPV])-(passSBStationRingPVLCT[iiStation][iiRing][iiPV]+passSBStationRingPVLCT[iiStation+4][iiRing][iiPV]))/((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])-(totSBStationRingPV[iiStation][iiRing][iiPV]+totSBStationRingPV[iiStation+4][iiRing][iiPV]));
					effSigmaStationCRingPVLCT[iiStation][iiRing][iiPV] = sqrt((((passStationRingPVLCT[iiStation][iiRing][iiPV]+passStationRingPVLCT[iiStation+4][iiRing][iiPV])+(passSBStationRingPVLCT[iiStation][iiRing][iiPV]+passSBStationRingPVLCT[iiStation+4][iiRing][iiPV]))*(1.-effStationCRingPVLCT[iiStation][iiRing][iiPV])*(1.-effStationCRingPVLCT[iiStation][iiRing][iiPV]))+ (((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])-(passStationRingPVLCT[iiStation][iiRing][iiPV]+passStationRingPVLCT[iiStation+4][iiRing][iiPV]))+((totSBStationRingPV[iiStation][iiRing][iiPV]+totSBStationRingPV[iiStation+4][iiRing][iiPV])-(passSBStationRingPVLCT[iiStation][iiRing][iiPV]+passSBStationRingPVLCT[iiStation+4][iiRing][iiPV])))*effStationCRingPVLCT[iiStation][iiRing][iiPV]*effStationCRingPVLCT[iiStation][iiRing][iiPV])/((totStationRingPV[iiStation][iiRing][iiPV]+totStationRingPV[iiStation+4][iiRing][iiPV])-(totSBStationRingPV[iiStation][iiRing][iiPV]+totSBStationRingPV[iiStation+4][iiRing][iiPV]));
				}

				segEffStationRingPV[iiStation][iiRing]->SetBinContent(iiPV+1,effStationRingPVSeg[iiStation][iiRing][iiPV]);
				segEffStationRingPV[iiStation][iiRing]->SetBinError(iiPV+1,effSigmaStationRingPVSeg[iiStation][iiRing][iiPV]);
				LCTEffStationRingPV[iiStation][iiRing]->SetBinContent(iiPV+1,effStationRingPVLCT[iiStation][iiRing][iiPV]);
				LCTEffStationRingPV[iiStation][iiRing]->SetBinError(iiPV+1,effSigmaStationRingPVLCT[iiStation][iiRing][iiPV]);
				if (iiStation < 4){
					segEffStationCRingPV[iiStation][iiRing]->SetBinContent(iiPV+1,effStationCRingPVSeg[iiStation][iiRing][iiPV]);
					segEffStationCRingPV[iiStation][iiRing]->SetBinError(iiPV+1,effSigmaStationCRingPVSeg[iiStation][iiRing][iiPV]);
					LCTEffStationCRingPV[iiStation][iiRing]->SetBinContent(iiPV+1,effStationCRingPVLCT[iiStation][iiRing][iiPV]);
					LCTEffStationCRingPV[iiStation][iiRing]->SetBinError(iiPV+1,effSigmaStationCRingPVLCT[iiStation][iiRing][iiPV]);
				}

				//zMassSegDenStationRingPV[iiStation][iiRing][iiPV]->Write();
				//zMassSegNumStationRingPV[iiStation][iiRing][iiPV]->Write();
				//zMassLCTNumStationRingPV[iiStation][iiRing][iiPV]->Write();


			}
			segEffStationRingPV[iiStation][iiRing]->Write();
			LCTEffStationRingPV[iiStation][iiRing]->Write();
			if (iiStation<4){
				segEffStationCRingPV[iiStation][iiRing]->Write();
				LCTEffStationCRingPV[iiStation][iiRing]->Write();
			}




			for (Int_t iiIL=0; iiIL< numILBins; iiIL++){
				//if (totStationRingIL[iiStation][iiRing][iiIL]>0.5)  effStationRingILSeg[iiStation][iiRing][iiIL] = passStationRingILSeg[iiStation][iiRing][iiIL]/totStationRingIL[iiStation][iiRing][iiIL];
				//if (totStationRingIL[iiStation][iiRing][iiIL]>0.5) effSigmaStationRingILSeg[iiStation][iiRing][iiIL] = sqrt(effStationRingILSeg[iiStation][iiRing][iiIL]*(1.0-effStationRingILSeg[iiStation][iiRing][iiIL])/totStationRingIL[iiStation][iiRing][iiIL]);
				//std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " IL Bin " << iiIL << std::endl;
				//std::cout << "tot: " << totStationRingIL[iiStation][iiRing][iiIL] << std::endl;
				//std::cout << "eff: " << effStationRingILSeg[iiStation][iiRing][iiIL] << " +/- " << effSigmaStationRingILSeg[iiStation][iiRing][iiIL] << std::endl;

				if ((totStationRingIL[iiStation][iiRing][iiIL]>0.5)&&((totStationRingIL[iiStation][iiRing][iiIL]-totSBStationRingIL[iiStation][iiRing][iiIL])>0.5)) {
					effStationRingILSeg[iiStation][iiRing][iiIL] = (passStationRingILSeg[iiStation][iiRing][iiIL]-passSBStationRingILSeg[iiStation][iiRing][iiIL])/(totStationRingIL[iiStation][iiRing][iiIL]-totSBStationRingIL[iiStation][iiRing][iiIL]);
					effSigmaStationRingILSeg[iiStation][iiRing][iiIL] = sqrt(((passStationRingILSeg[iiStation][iiRing][iiIL]+passSBStationRingILSeg[iiStation][iiRing][iiIL])*(1.-effStationRingILSeg[iiStation][iiRing][iiIL])*(1.-effStationRingILSeg[iiStation][iiRing][iiIL]))+ ((totStationRingIL[iiStation][iiRing][iiIL]-passStationRingILSeg[iiStation][iiRing][iiIL])+(totSBStationRingIL[iiStation][iiRing][iiIL]-passSBStationRingILSeg[iiStation][iiRing][iiIL]))*effStationRingILSeg[iiStation][iiRing][iiIL]*effStationRingILSeg[iiStation][iiRing][iiIL])/(totStationRingIL[iiStation][iiRing][iiIL]-totSBStationRingIL[iiStation][iiRing][iiIL]);
					effStationRingILLCT[iiStation][iiRing][iiIL] = (passStationRingILLCT[iiStation][iiRing][iiIL]-passSBStationRingILLCT[iiStation][iiRing][iiIL])/(totStationRingIL[iiStation][iiRing][iiIL]-totSBStationRingIL[iiStation][iiRing][iiIL]);
					effSigmaStationRingILLCT[iiStation][iiRing][iiIL] = sqrt(((passStationRingILLCT[iiStation][iiRing][iiIL]+passSBStationRingILLCT[iiStation][iiRing][iiIL])*(1.-effStationRingILLCT[iiStation][iiRing][iiIL])*(1.-effStationRingILLCT[iiStation][iiRing][iiIL]))+ ((totStationRingIL[iiStation][iiRing][iiIL]-passStationRingILLCT[iiStation][iiRing][iiIL])+(totSBStationRingIL[iiStation][iiRing][iiIL]-passSBStationRingILLCT[iiStation][iiRing][iiIL]))*effStationRingILLCT[iiStation][iiRing][iiIL]*effStationRingILLCT[iiStation][iiRing][iiIL])/(totStationRingIL[iiStation][iiRing][iiIL]-totSBStationRingIL[iiStation][iiRing][iiIL]);
				}

				if ((iiStation<4)&&((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])>0.5)&&(((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])-(totSBStationRingIL[iiStation][iiRing][iiIL]+totSBStationRingIL[iiStation+4][iiRing][iiIL]))>0.5)) {
					effStationCRingILSeg[iiStation][iiRing][iiIL] = ((passStationRingILSeg[iiStation][iiRing][iiIL]+passStationRingILSeg[iiStation+4][iiRing][iiIL])-(passSBStationRingILSeg[iiStation][iiRing][iiIL]+passSBStationRingILSeg[iiStation+4][iiRing][iiIL]))/((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])-(totSBStationRingIL[iiStation][iiRing][iiIL]+totSBStationRingIL[iiStation+4][iiRing][iiIL]));
					effSigmaStationCRingILSeg[iiStation][iiRing][iiIL] = sqrt((((passStationRingILSeg[iiStation][iiRing][iiIL]+passStationRingILSeg[iiStation+4][iiRing][iiIL])+(passSBStationRingILSeg[iiStation][iiRing][iiIL]+passSBStationRingILSeg[iiStation+4][iiRing][iiIL]))*(1.-effStationCRingILSeg[iiStation][iiRing][iiIL])*(1.-effStationCRingILSeg[iiStation][iiRing][iiIL]))+ (((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])-(passStationRingILSeg[iiStation][iiRing][iiIL]+passStationRingILSeg[iiStation+4][iiRing][iiIL]))+((totSBStationRingIL[iiStation][iiRing][iiIL]+totSBStationRingIL[iiStation+4][iiRing][iiIL])-(passSBStationRingILSeg[iiStation][iiRing][iiIL]+passSBStationRingILSeg[iiStation+4][iiRing][iiIL])))*effStationCRingILSeg[iiStation][iiRing][iiIL]*effStationCRingILSeg[iiStation][iiRing][iiIL])/((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])-(totSBStationRingIL[iiStation][iiRing][iiIL]+totSBStationRingIL[iiStation+4][iiRing][iiIL]));

					effStationCRingILLCT[iiStation][iiRing][iiIL] = ((passStationRingILLCT[iiStation][iiRing][iiIL]+passStationRingILLCT[iiStation+4][iiRing][iiIL])-(passSBStationRingILLCT[iiStation][iiRing][iiIL]+passSBStationRingILLCT[iiStation+4][iiRing][iiIL]))/((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])-(totSBStationRingIL[iiStation][iiRing][iiIL]+totSBStationRingIL[iiStation+4][iiRing][iiIL]));
					effSigmaStationCRingILLCT[iiStation][iiRing][iiIL] = sqrt((((passStationRingILLCT[iiStation][iiRing][iiIL]+passStationRingILLCT[iiStation+4][iiRing][iiIL])+(passSBStationRingILLCT[iiStation][iiRing][iiIL]+passSBStationRingILLCT[iiStation+4][iiRing][iiIL]))*(1.-effStationCRingILLCT[iiStation][iiRing][iiIL])*(1.-effStationCRingILLCT[iiStation][iiRing][iiIL]))+ (((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])-(passStationRingILLCT[iiStation][iiRing][iiIL]+passStationRingILLCT[iiStation+4][iiRing][iiIL]))+((totSBStationRingIL[iiStation][iiRing][iiIL]+totSBStationRingIL[iiStation+4][iiRing][iiIL])-(passSBStationRingILLCT[iiStation][iiRing][iiIL]+passSBStationRingILLCT[iiStation+4][iiRing][iiIL])))*effStationCRingILLCT[iiStation][iiRing][iiIL]*effStationCRingILLCT[iiStation][iiRing][iiIL])/((totStationRingIL[iiStation][iiRing][iiIL]+totStationRingIL[iiStation+4][iiRing][iiIL])-(totSBStationRingIL[iiStation][iiRing][iiIL]+totSBStationRingIL[iiStation+4][iiRing][iiIL]));
				}

				segEffStationRingIL[iiStation][iiRing]->SetBinContent(iiIL+1,effStationRingILSeg[iiStation][iiRing][iiIL]);
				segEffStationRingIL[iiStation][iiRing]->SetBinError(iiIL+1,effSigmaStationRingILSeg[iiStation][iiRing][iiIL]);
				LCTEffStationRingIL[iiStation][iiRing]->SetBinContent(iiIL+1,effStationRingILLCT[iiStation][iiRing][iiIL]);
				LCTEffStationRingIL[iiStation][iiRing]->SetBinError(iiIL+1,effSigmaStationRingILLCT[iiStation][iiRing][iiIL]);
				if (iiStation < 4){
					segEffStationCRingIL[iiStation][iiRing]->SetBinContent(iiIL+1,effStationCRingILSeg[iiStation][iiRing][iiIL]);
					segEffStationCRingIL[iiStation][iiRing]->SetBinError(iiIL+1,effSigmaStationCRingILSeg[iiStation][iiRing][iiIL]);
					LCTEffStationCRingIL[iiStation][iiRing]->SetBinContent(iiIL+1,effStationCRingILLCT[iiStation][iiRing][iiIL]);
					LCTEffStationCRingIL[iiStation][iiRing]->SetBinError(iiIL+1,effSigmaStationCRingILLCT[iiStation][iiRing][iiIL]);
				}



			}
			segEffStationRingIL[iiStation][iiRing]->Write();
			LCTEffStationRingIL[iiStation][iiRing]->Write();
			if (iiStation<4){
				segEffStationCRingIL[iiStation][iiRing]->Write();
				LCTEffStationCRingIL[iiStation][iiRing]->Write();
			}





			for (Int_t iiRun=0; iiRun< numRunBins; iiRun++){
				//if (totStationRingRun[iiStation][iiRing][iiRun]>0.5)  effStationRingRunSeg[iiStation][iiRing][iiRun] = passStationRingRunSeg[iiStation][iiRing][iiRun]/totStationRingRun[iiStation][iiRing][iiRun];
				//if (totStationRingRun[iiStation][iiRing][iiRun]>0.5) effSigmaStationRingRunSeg[iiStation][iiRing][iiRun] = sqrt(effStationRingRunSeg[iiStation][iiRing][iiRun]*(1.0-effStationRingRunSeg[iiStation][iiRing][iiRun])/totStationRingRun[iiStation][iiRing][iiRun]);
				//std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " Run Bin " << iiRun << std::endl;
				//std::cout << "tot: " << totStationRingRun[iiStation][iiRing][iiRun] << std::endl;
				//std::cout << "eff: " << effStationRingRunSeg[iiStation][iiRing][iiRun] << " +/- " << effSigmaStationRingRunSeg[iiStation][iiRing][iiRun] << std::endl;

				if ((totStationRingRun[iiStation][iiRing][iiRun]>0.5)&&((totStationRingRun[iiStation][iiRing][iiRun]-totSBStationRingRun[iiStation][iiRing][iiRun])>0.5)) {
					effStationRingRunSeg[iiStation][iiRing][iiRun] = (passStationRingRunSeg[iiStation][iiRing][iiRun]-passSBStationRingRunSeg[iiStation][iiRing][iiRun])/(totStationRingRun[iiStation][iiRing][iiRun]-totSBStationRingRun[iiStation][iiRing][iiRun]);
					effSigmaStationRingRunSeg[iiStation][iiRing][iiRun] = sqrt(((passStationRingRunSeg[iiStation][iiRing][iiRun]+passSBStationRingRunSeg[iiStation][iiRing][iiRun])*(1.-effStationRingRunSeg[iiStation][iiRing][iiRun])*(1.-effStationRingRunSeg[iiStation][iiRing][iiRun]))+ ((totStationRingRun[iiStation][iiRing][iiRun]-passStationRingRunSeg[iiStation][iiRing][iiRun])+(totSBStationRingRun[iiStation][iiRing][iiRun]-passSBStationRingRunSeg[iiStation][iiRing][iiRun]))*effStationRingRunSeg[iiStation][iiRing][iiRun]*effStationRingRunSeg[iiStation][iiRing][iiRun])/(totStationRingRun[iiStation][iiRing][iiRun]-totSBStationRingRun[iiStation][iiRing][iiRun]);
					effStationRingRunLCT[iiStation][iiRing][iiRun] = (passStationRingRunLCT[iiStation][iiRing][iiRun]-passSBStationRingRunLCT[iiStation][iiRing][iiRun])/(totStationRingRun[iiStation][iiRing][iiRun]-totSBStationRingRun[iiStation][iiRing][iiRun]);
					effSigmaStationRingRunLCT[iiStation][iiRing][iiRun] = sqrt(((passStationRingRunLCT[iiStation][iiRing][iiRun]+passSBStationRingRunLCT[iiStation][iiRing][iiRun])*(1.-effStationRingRunLCT[iiStation][iiRing][iiRun])*(1.-effStationRingRunLCT[iiStation][iiRing][iiRun]))+ ((totStationRingRun[iiStation][iiRing][iiRun]-passStationRingRunLCT[iiStation][iiRing][iiRun])+(totSBStationRingRun[iiStation][iiRing][iiRun]-passSBStationRingRunLCT[iiStation][iiRing][iiRun]))*effStationRingRunLCT[iiStation][iiRing][iiRun]*effStationRingRunLCT[iiStation][iiRing][iiRun])/(totStationRingRun[iiStation][iiRing][iiRun]-totSBStationRingRun[iiStation][iiRing][iiRun]);
				}

				segEffStationRingRun[iiStation][iiRing]->SetBinContent(iiRun+1,effStationRingRunSeg[iiStation][iiRing][iiRun]);
				segEffStationRingRun[iiStation][iiRing]->SetBinError(iiRun+1,effSigmaStationRingRunSeg[iiStation][iiRing][iiRun]);
				LCTEffStationRingRun[iiStation][iiRing]->SetBinContent(iiRun+1,effStationRingRunLCT[iiStation][iiRing][iiRun]);
				LCTEffStationRingRun[iiStation][iiRing]->SetBinError(iiRun+1,effSigmaStationRingRunLCT[iiStation][iiRing][iiRun]);


			}
			segEffStationRingRun[iiStation][iiRing]->Write();
			LCTEffStationRingRun[iiStation][iiRing]->Write();



			//      for (Int_t iiLCW=0; iiLCW< numLCWBins; iiLCW++){
			// // 	 //if (totStationRingLCW[iiStation][iiRing][iiLCW]>0.5)  effStationRingLCWSeg[iiStation][iiRing][iiLCW] = passStationRingLCWSeg[iiStation][iiRing][iiLCW]/totStationRingLCW[iiStation][iiRing][iiLCW];
			// // 	 //if (totStationRingLCW[iiStation][iiRing][iiLCW]>0.5) effSigmaStationRingLCWSeg[iiStation][iiRing][iiLCW] = sqrt(effStationRingLCWSeg[iiStation][iiRing][iiLCW]*(1.0-effStationRingLCWSeg[iiStation][iiRing][iiLCW])/totStationRingLCW[iiStation][iiRing][iiLCW]);
			// // 	 //std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " LCW Bin " << iiLCW << std::endl;
			// // 	 //std::cout << "tot: " << totStationRingLCW[iiStation][iiRing][iiLCW] << std::endl;
			// // 	 //std::cout << "eff: " << effStationRingLCWSeg[iiStation][iiRing][iiLCW] << " +/- " << effSigmaStationRingLCWSeg[iiStation][iiRing][iiLCW] << std::endl;

			// //     if ((totStationRingLCW[iiStation][iiRing][iiLCW]>0.5)&&((totStationRingLCW[iiStation][iiRing][iiLCW]-totSBStationRingLCW[iiStation][iiRing][iiLCW])>0.5)) {
			// // 	 effStationRingLCWSeg[iiStation][iiRing][iiLCW] = (passStationRingLCWSeg[iiStation][iiRing][iiLCW]-passSBStationRingLCWSeg[iiStation][iiRing][iiLCW])/(totStationRingLCW[iiStation][iiRing][iiLCW]-totSBStationRingLCW[iiStation][iiRing][iiLCW]);
			// // 	 effSigmaStationRingLCWSeg[iiStation][iiRing][iiLCW] = sqrt(((passStationRingLCWSeg[iiStation][iiRing][iiLCW]+passSBStationRingLCWSeg[iiStation][iiRing][iiLCW])*(1.-effStationRingLCWSeg[iiStation][iiRing][iiLCW])*(1.-effStationRingLCWSeg[iiStation][iiRing][iiLCW]))+ ((totStationRingLCW[iiStation][iiRing][iiLCW]-passStationRingLCWSeg[iiStation][iiRing][iiLCW])+(totSBStationRingLCW[iiStation][iiRing][iiLCW]-passSBStationRingLCWSeg[iiStation][iiRing][iiLCW]))*effStationRingLCWSeg[iiStation][iiRing][iiLCW]*effStationRingLCWSeg[iiStation][iiRing][iiLCW])/(totStationRingLCW[iiStation][iiRing][iiLCW]-totSBStationRingLCW[iiStation][iiRing][iiLCW]);
			// //     }
			// //     if ((totStationRingLCWLCT[iiStation][iiRing][iiLCW]>0.5)&&((totStationRingLCWLCT[iiStation][iiRing][iiLCW]-totSBStationRingLCWLCT[iiStation][iiRing][iiLCW])>0.5)) {
			// // 	 effStationRingLCWLCT[iiStation][iiRing][iiLCW] = (passStationRingLCWLCT[iiStation][iiRing][iiLCW]-passSBStationRingLCWLCT[iiStation][iiRing][iiLCW])/(totStationRingLCWLCT[iiStation][iiRing][iiLCW]-totSBStationRingLCWLCT[iiStation][iiRing][iiLCW]);
			// // 	 effSigmaStationRingLCWLCT[iiStation][iiRing][iiLCW] = sqrt(((passStationRingLCWLCT[iiStation][iiRing][iiLCW]+passSBStationRingLCWLCT[iiStation][iiRing][iiLCW])*(1.-effStationRingLCWLCT[iiStation][iiRing][iiLCW])*(1.-effStationRingLCWLCT[iiStation][iiRing][iiLCW]))+ ((totStationRingLCWLCT[iiStation][iiRing][iiLCW]-passStationRingLCWLCT[iiStation][iiRing][iiLCW])+(totSBStationRingLCWLCT[iiStation][iiRing][iiLCW]-passSBStationRingLCWLCT[iiStation][iiRing][iiLCW]))*effStationRingLCWLCT[iiStation][iiRing][iiLCW]*effStationRingLCWLCT[iiStation][iiRing][iiLCW])/(totStationRingLCWLCT[iiStation][iiRing][iiLCW]-totSBStationRingLCWLCT[iiStation][iiRing][iiLCW]);
			// //     }

			// // 	 if ((iiStation<4)&&((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])>0.5)&&(((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])-(totSBStationRingLCW[iiStation][iiRing][iiLCW]+totSBStationRingLCW[iiStation+4][iiRing][iiLCW]))>0.5)) {
			// // 	   effStationCRingLCWSeg[iiStation][iiRing][iiLCW] = ((passStationRingLCWSeg[iiStation][iiRing][iiLCW]+passStationRingLCWSeg[iiStation+4][iiRing][iiLCW])-(passSBStationRingLCWSeg[iiStation][iiRing][iiLCW]+passSBStationRingLCWSeg[iiStation+4][iiRing][iiLCW]))/((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])-(totSBStationRingLCW[iiStation][iiRing][iiLCW]+totSBStationRingLCW[iiStation+4][iiRing][iiLCW]));
			// // 	   effSigmaStationCRingLCWSeg[iiStation][iiRing][iiLCW] = sqrt((((passStationRingLCWSeg[iiStation][iiRing][iiLCW]+passStationRingLCWSeg[iiStation+4][iiRing][iiLCW])+(passSBStationRingLCWSeg[iiStation][iiRing][iiLCW]+passSBStationRingLCWSeg[iiStation+4][iiRing][iiLCW]))*(1.-effStationCRingLCWSeg[iiStation][iiRing][iiLCW])*(1.-effStationCRingLCWSeg[iiStation][iiRing][iiLCW]))+ (((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])-(passStationRingLCWSeg[iiStation][iiRing][iiLCW]+passStationRingLCWSeg[iiStation+4][iiRing][iiLCW]))+((totSBStationRingLCW[iiStation][iiRing][iiLCW]+totSBStationRingLCW[iiStation+4][iiRing][iiLCW])-(passSBStationRingLCWSeg[iiStation][iiRing][iiLCW]+passSBStationRingLCWSeg[iiStation+4][iiRing][iiLCW])))*effStationCRingLCWSeg[iiStation][iiRing][iiLCW]*effStationCRingLCWSeg[iiStation][iiRing][iiLCW])/((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])-(totSBStationRingLCW[iiStation][iiRing][iiLCW]+totSBStationRingLCW[iiStation+4][iiRing][iiLCW]));

			// // 	   effStationCRingLCWLCT[iiStation][iiRing][iiLCW] = ((passStationRingLCWLCT[iiStation][iiRing][iiLCW]+passStationRingLCWLCT[iiStation+4][iiRing][iiLCW])-(passSBStationRingLCWLCT[iiStation][iiRing][iiLCW]+passSBStationRingLCWLCT[iiStation+4][iiRing][iiLCW]))/((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])-(totSBStationRingLCW[iiStation][iiRing][iiLCW]+totSBStationRingLCW[iiStation+4][iiRing][iiLCW]));
			// // 	   effSigmaStationCRingLCWLCT[iiStation][iiRing][iiLCW] = sqrt((((passStationRingLCWLCT[iiStation][iiRing][iiLCW]+passStationRingLCWLCT[iiStation+4][iiRing][iiLCW])+(passSBStationRingLCWLCT[iiStation][iiRing][iiLCW]+passSBStationRingLCWLCT[iiStation+4][iiRing][iiLCW]))*(1.-effStationCRingLCWLCT[iiStation][iiRing][iiLCW])*(1.-effStationCRingLCWLCT[iiStation][iiRing][iiLCW]))+ (((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])-(passStationRingLCWLCT[iiStation][iiRing][iiLCW]+passStationRingLCWLCT[iiStation+4][iiRing][iiLCW]))+((totSBStationRingLCW[iiStation][iiRing][iiLCW]+totSBStationRingLCW[iiStation+4][iiRing][iiLCW])-(passSBStationRingLCWLCT[iiStation][iiRing][iiLCW]+passSBStationRingLCWLCT[iiStation+4][iiRing][iiLCW])))*effStationCRingLCWLCT[iiStation][iiRing][iiLCW]*effStationCRingLCWLCT[iiStation][iiRing][iiLCW])/((totStationRingLCW[iiStation][iiRing][iiLCW]+totStationRingLCW[iiStation+4][iiRing][iiLCW])-(totSBStationRingLCW[iiStation][iiRing][iiLCW]+totSBStationRingLCW[iiStation+4][iiRing][iiLCW]));
			// // 	 }


			// 	  //segEffStationRingLCW[iiStation][iiRing]->SetBinContent(iiLCW+1,effStationRingLCWSeg[iiStation][iiRing][iiLCW]);
			// 	  //segEffStationRingLCW[iiStation][iiRing]->SetBinError(iiLCW+1,effSigmaStationRingLCWSeg[iiStation][iiRing][iiLCW]);
			// 	  //LCTEffStationRingLCW[iiStation][iiRing]->SetBinContent(iiLCW+1,effStationRingLCWLCT[iiStation][iiRing][iiLCW]);
			// 	// LCTEffStationRingLCW[iiStation][iiRing]->SetBinError(iiLCW+1,effSigmaStationRingLCWLCT[iiStation][iiRing][iiLCW]);
			// //     if (iiStation < 4){
			// //     segEffStationCRingLCW[iiStation][iiRing]->SetBinContent(iiLCW+1,effStationCRingLCWSeg[iiStation][iiRing][iiLCW]);
			// //     segEffStationCRingLCW[iiStation][iiRing]->SetBinError(iiLCW+1,effSigmaStationCRingLCWSeg[iiStation][iiRing][iiLCW]);
			// //     LCTEffStationCRingLCW[iiStation][iiRing]->SetBinContent(iiLCW+1,effStationCRingLCWLCT[iiStation][iiRing][iiLCW]);
			// //     LCTEffStationCRingLCW[iiStation][iiRing]->SetBinError(iiLCW+1,effSigmaStationCRingLCWLCT[iiStation][iiRing][iiLCW]);
			// //     }

			//     for (Int_t iiChamber=0; iiChamber < 37; iiChamber++){

			// 	 if ((totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]>0.5)&&((totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-totSBStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW])>0.5)) {
			// 	   effStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW] = (passStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW]-passSBStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW])/(totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-totSBStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]);
			// 	   effSigmaStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW] = sqrt(((passStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW]+passSBStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW])*(1.-effStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW])*(1.-effStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW]))+ ((totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-passStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW])+(totSBStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-passSBStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW]))*effStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW]*effStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW])/(totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-totSBStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]);

			// 	   effStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW] = (passStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW]-passSBStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW])/(totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-totSBStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]);
			// 	   effSigmaStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW] = sqrt(((passStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW]+passSBStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW])*(1.-effStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW])*(1.-effStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW]))+ ((totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-passStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW])+(totSBStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-passSBStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW]))*effStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW]*effStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW])/(totStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]-totSBStationRingChamberLCW[iiStation][iiRing][iiChamber][iiLCW]);

			// 	 }	 

			// 	 segEffStationRingChamberLCW[iiStation][iiRing][iiChamber]->SetBinContent(iiLCW+1,effStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW]);
			// 	 segEffStationRingChamberLCW[iiStation][iiRing][iiChamber]->SetBinError(iiLCW+1,effSigmaStationRingChamberLCWSeg[iiStation][iiRing][iiChamber][iiLCW]);
			// 	 LCTEffStationRingChamberLCW[iiStation][iiRing][iiChamber]->SetBinContent(iiLCW+1,effStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW]);
			// 	 LCTEffStationRingChamberLCW[iiStation][iiRing][iiChamber]->SetBinError(iiLCW+1,effSigmaStationRingChamberLCWLCT[iiStation][iiRing][iiChamber][iiLCW]);
			//     }


			//      }
			//     // segEffStationRingLCW[iiStation][iiRing]->Write();
			//     // LCTEffStationRingLCW[iiStation][iiRing]->Write();
			//     // if (iiStation < 4){
			//     // segEffStationCRingLCW[iiStation][iiRing]->Write();
			//     // LCTEffStationCRingLCW[iiStation][iiRing]->Write(); 
			//     // }

			//     for (Int_t iiChamber=0; iiChamber < 37; iiChamber++){
			// 	 segEffStationRingChamberLCW[iiStation][iiRing][iiChamber]->Write();
			// 	 LCTEffStationRingChamberLCW[iiStation][iiRing][iiChamber]->Write();
			//     }       

			for (Int_t iiLCY=0; iiLCY< numLCYBins; iiLCY++){
				// 	 //if (totStationRingLCY[iiStation][iiRing][iiLCY]>0.5)  effStationRingLCYSeg[iiStation][iiRing][iiLCY] = passStationRingLCYSeg[iiStation][iiRing][iiLCY]/totStationRingLCY[iiStation][iiRing][iiLCY];
				// 	 //if (totStationRingLCY[iiStation][iiRing][iiLCY]>0.5) effSigmaStationRingLCYSeg[iiStation][iiRing][iiLCY] = sqrt(effStationRingLCYSeg[iiStation][iiRing][iiLCY]*(1.0-effStationRingLCYSeg[iiStation][iiRing][iiLCY])/totStationRingLCY[iiStation][iiRing][iiLCY]);
				// 	 //std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " LCY Bin " << iiLCY << std::endl;
				// 	 //std::cout << "tot: " << totStationRingLCY[iiStation][iiRing][iiLCY] << std::endl;
				// 	 //std::cout << "eff: " << effStationRingLCYSeg[iiStation][iiRing][iiLCY] << " +/- " << effSigmaStationRingLCYSeg[iiStation][iiRing][iiLCY] << std::endl;

				// if ((totStationRingLCY[iiStation][iiRing][iiLCY]>0.5)&&((totStationRingLCY[iiStation][iiRing][iiLCY]-totSBStationRingLCY[iiStation][iiRing][iiLCY])>0.5)) {
				// 	 effStationRingLCYSeg[iiStation][iiRing][iiLCY] = (passStationRingLCYSeg[iiStation][iiRing][iiLCY]-passSBStationRingLCYSeg[iiStation][iiRing][iiLCY])/(totStationRingLCY[iiStation][iiRing][iiLCY]-totSBStationRingLCY[iiStation][iiRing][iiLCY]);
				// 	 effSigmaStationRingLCYSeg[iiStation][iiRing][iiLCY] = sqrt(((passStationRingLCYSeg[iiStation][iiRing][iiLCY]+passSBStationRingLCYSeg[iiStation][iiRing][iiLCY])*(1.-effStationRingLCYSeg[iiStation][iiRing][iiLCY])*(1.-effStationRingLCYSeg[iiStation][iiRing][iiLCY]))+ ((totStationRingLCY[iiStation][iiRing][iiLCY]-passStationRingLCYSeg[iiStation][iiRing][iiLCY])+(totSBStationRingLCY[iiStation][iiRing][iiLCY]-passSBStationRingLCYSeg[iiStation][iiRing][iiLCY]))*effStationRingLCYSeg[iiStation][iiRing][iiLCY]*effStationRingLCYSeg[iiStation][iiRing][iiLCY])/(totStationRingLCY[iiStation][iiRing][iiLCY]-totSBStationRingLCY[iiStation][iiRing][iiLCY]);
				// }
				// if ((totStationRingLCYLCT[iiStation][iiRing][iiLCY]>0.5)&&((totStationRingLCYLCT[iiStation][iiRing][iiLCY]-totSBStationRingLCYLCT[iiStation][iiRing][iiLCY])>0.5)) {
				// 	 effStationRingLCYLCT[iiStation][iiRing][iiLCY] = (passStationRingLCYLCT[iiStation][iiRing][iiLCY]-passSBStationRingLCYLCT[iiStation][iiRing][iiLCY])/(totStationRingLCYLCT[iiStation][iiRing][iiLCY]-totSBStationRingLCYLCT[iiStation][iiRing][iiLCY]);
				// 	 effSigmaStationRingLCYLCT[iiStation][iiRing][iiLCY] = sqrt(((passStationRingLCYLCT[iiStation][iiRing][iiLCY]+passSBStationRingLCYLCT[iiStation][iiRing][iiLCY])*(1.-effStationRingLCYLCT[iiStation][iiRing][iiLCY])*(1.-effStationRingLCYLCT[iiStation][iiRing][iiLCY]))+ ((totStationRingLCYLCT[iiStation][iiRing][iiLCY]-passStationRingLCYLCT[iiStation][iiRing][iiLCY])+(totSBStationRingLCYLCT[iiStation][iiRing][iiLCY]-passSBStationRingLCYLCT[iiStation][iiRing][iiLCY]))*effStationRingLCYLCT[iiStation][iiRing][iiLCY]*effStationRingLCYLCT[iiStation][iiRing][iiLCY])/(totStationRingLCYLCT[iiStation][iiRing][iiLCY]-totSBStationRingLCYLCT[iiStation][iiRing][iiLCY]);
				// }

				// 	 if ((iiStation<4)&&((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])>0.5)&&(((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])-(totSBStationRingLCY[iiStation][iiRing][iiLCY]+totSBStationRingLCY[iiStation+4][iiRing][iiLCY]))>0.5)) {
				// 	   effStationCRingLCYSeg[iiStation][iiRing][iiLCY] = ((passStationRingLCYSeg[iiStation][iiRing][iiLCY]+passStationRingLCYSeg[iiStation+4][iiRing][iiLCY])-(passSBStationRingLCYSeg[iiStation][iiRing][iiLCY]+passSBStationRingLCYSeg[iiStation+4][iiRing][iiLCY]))/((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])-(totSBStationRingLCY[iiStation][iiRing][iiLCY]+totSBStationRingLCY[iiStation+4][iiRing][iiLCY]));
				// 	   effSigmaStationCRingLCYSeg[iiStation][iiRing][iiLCY] = sqrt((((passStationRingLCYSeg[iiStation][iiRing][iiLCY]+passStationRingLCYSeg[iiStation+4][iiRing][iiLCY])+(passSBStationRingLCYSeg[iiStation][iiRing][iiLCY]+passSBStationRingLCYSeg[iiStation+4][iiRing][iiLCY]))*(1.-effStationCRingLCYSeg[iiStation][iiRing][iiLCY])*(1.-effStationCRingLCYSeg[iiStation][iiRing][iiLCY]))+ (((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])-(passStationRingLCYSeg[iiStation][iiRing][iiLCY]+passStationRingLCYSeg[iiStation+4][iiRing][iiLCY]))+((totSBStationRingLCY[iiStation][iiRing][iiLCY]+totSBStationRingLCY[iiStation+4][iiRing][iiLCY])-(passSBStationRingLCYSeg[iiStation][iiRing][iiLCY]+passSBStationRingLCYSeg[iiStation+4][iiRing][iiLCY])))*effStationCRingLCYSeg[iiStation][iiRing][iiLCY]*effStationCRingLCYSeg[iiStation][iiRing][iiLCY])/((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])-(totSBStationRingLCY[iiStation][iiRing][iiLCY]+totSBStationRingLCY[iiStation+4][iiRing][iiLCY]));

				// 	   effStationCRingLCYLCT[iiStation][iiRing][iiLCY] = ((passStationRingLCYLCT[iiStation][iiRing][iiLCY]+passStationRingLCYLCT[iiStation+4][iiRing][iiLCY])-(passSBStationRingLCYLCT[iiStation][iiRing][iiLCY]+passSBStationRingLCYLCT[iiStation+4][iiRing][iiLCY]))/((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])-(totSBStationRingLCY[iiStation][iiRing][iiLCY]+totSBStationRingLCY[iiStation+4][iiRing][iiLCY]));
				// 	   effSigmaStationCRingLCYLCT[iiStation][iiRing][iiLCY] = sqrt((((passStationRingLCYLCT[iiStation][iiRing][iiLCY]+passStationRingLCYLCT[iiStation+4][iiRing][iiLCY])+(passSBStationRingLCYLCT[iiStation][iiRing][iiLCY]+passSBStationRingLCYLCT[iiStation+4][iiRing][iiLCY]))*(1.-effStationCRingLCYLCT[iiStation][iiRing][iiLCY])*(1.-effStationCRingLCYLCT[iiStation][iiRing][iiLCY]))+ (((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])-(passStationRingLCYLCT[iiStation][iiRing][iiLCY]+passStationRingLCYLCT[iiStation+4][iiRing][iiLCY]))+((totSBStationRingLCY[iiStation][iiRing][iiLCY]+totSBStationRingLCY[iiStation+4][iiRing][iiLCY])-(passSBStationRingLCYLCT[iiStation][iiRing][iiLCY]+passSBStationRingLCYLCT[iiStation+4][iiRing][iiLCY])))*effStationCRingLCYLCT[iiStation][iiRing][iiLCY]*effStationCRingLCYLCT[iiStation][iiRing][iiLCY])/((totStationRingLCY[iiStation][iiRing][iiLCY]+totStationRingLCY[iiStation+4][iiRing][iiLCY])-(totSBStationRingLCY[iiStation][iiRing][iiLCY]+totSBStationRingLCY[iiStation+4][iiRing][iiLCY]));
				// 	 }


				// segEffStationRingLCY[iiStation][iiRing]->SetBinContent(iiLCY+1,effStationRingLCYSeg[iiStation][iiRing][iiLCY]);
				// segEffStationRingLCY[iiStation][iiRing]->SetBinError(iiLCY+1,effSigmaStationRingLCYSeg[iiStation][iiRing][iiLCY]);
				// LCTEffStationRingLCY[iiStation][iiRing]->SetBinContent(iiLCY+1,effStationRingLCYLCT[iiStation][iiRing][iiLCY]);
				// LCTEffStationRingLCY[iiStation][iiRing]->SetBinError(iiLCY+1,effSigmaStationRingLCYLCT[iiStation][iiRing][iiLCY]);
				// if (iiStation<4){
				// segEffStationCRingLCY[iiStation][iiRing]->SetBinContent(iiLCY+1,effStationCRingLCYSeg[iiStation][iiRing][iiLCY]);
				// segEffStationCRingLCY[iiStation][iiRing]->SetBinError(iiLCY+1,effSigmaStationCRingLCYSeg[iiStation][iiRing][iiLCY]);
				// LCTEffStationCRingLCY[iiStation][iiRing]->SetBinContent(iiLCY+1,effStationCRingLCYLCT[iiStation][iiRing][iiLCY]);
				// LCTEffStationCRingLCY[iiStation][iiRing]->SetBinError(iiLCY+1,effSigmaStationCRingLCYLCT[iiStation][iiRing][iiLCY]);
				// }

				for (Int_t iiChamber=0; iiChamber < 37; iiChamber++){

					if ((totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]>0.5)&&((totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-totSBStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY])>0.5)) {
						effStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY] = (passStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY]-passSBStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY])/(totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-totSBStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]);
						effSigmaStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY] = sqrt(((passStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY]+passSBStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY])*(1.-effStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY])*(1.-effStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY]))+ ((totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-passStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY])+(totSBStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-passSBStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY]))*effStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY]*effStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY])/(totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-totSBStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]);

						effStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY] = (passStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY]-passSBStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY])/(totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-totSBStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]);
						effSigmaStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY] = sqrt(((passStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY]+passSBStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY])*(1.-effStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY])*(1.-effStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY]))+ ((totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-passStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY])+(totSBStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-passSBStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY]))*effStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY]*effStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY])/(totStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]-totSBStationRingChamberLCY[iiStation][iiRing][iiChamber][iiLCY]);
					}	 

					segEffStationRingChamberLCY[iiStation][iiRing][iiChamber]->SetBinContent(iiLCY+1,effStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY]);
					segEffStationRingChamberLCY[iiStation][iiRing][iiChamber]->SetBinError(iiLCY+1,effSigmaStationRingChamberLCYSeg[iiStation][iiRing][iiChamber][iiLCY]);
					LCTEffStationRingChamberLCY[iiStation][iiRing][iiChamber]->SetBinContent(iiLCY+1,effStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY]);
					LCTEffStationRingChamberLCY[iiStation][iiRing][iiChamber]->SetBinError(iiLCY+1,effSigmaStationRingChamberLCYLCT[iiStation][iiRing][iiChamber][iiLCY]);

				}


			} //end loog over LCY bins
			// segEffStationRingLCY[iiStation][iiRing]->Write();
			// LCTEffStationRingLCY[iiStation][iiRing]->Write();
			// if (iiStation<4){
			// segEffStationCRingLCY[iiStation][iiRing]->Write();
			// LCTEffStationCRingLCY[iiStation][iiRing]->Write();
			// }
			for (Int_t iiChamber=0; iiChamber < 37; iiChamber++){
				segEffStationRingChamberLCY[iiStation][iiRing][iiChamber]->Write();
				LCTEffStationRingChamberLCY[iiStation][iiRing][iiChamber]->Write();
			}      

			for (Int_t iiLCS=0; iiLCS< numLCSBins; iiLCS++){
				// 	 //if (totStationRingLCS[iiStation][iiRing][iiLCS]>0.5)  effStationRingLCSSeg[iiStation][iiRing][iiLCS] = passStationRingLCSSeg[iiStation][iiRing][iiLCS]/totStationRingLCS[iiStation][iiRing][iiLCS];
				// 	 //if (totStationRingLCS[iiStation][iiRing][iiLCS]>0.5) effSigmaStationRingLCSSeg[iiStation][iiRing][iiLCS] = sqrt(effStationRingLCSSeg[iiStation][iiRing][iiLCS]*(1.0-effStationRingLCSSeg[iiStation][iiRing][iiLCS])/totStationRingLCS[iiStation][iiRing][iiLCS]);
				// 	 //std::cout << "Ring efficiency: Station " << iiStation << " Ring " << iiRing << " LCS Bin " << iiLCS << std::endl;
				// 	 //std::cout << "tot: " << totStationRingLCS[iiStation][iiRing][iiLCS] << std::endl;
				// 	 //std::cout << "eff: " << effStationRingLCSSeg[iiStation][iiRing][iiLCS] << " +/- " << effSigmaStationRingLCSSeg[iiStation][iiRing][iiLCS] << std::endl;

				// if ((totStationRingLCS[iiStation][iiRing][iiLCS]>0.5)&&((totStationRingLCS[iiStation][iiRing][iiLCS]-totSBStationRingLCS[iiStation][iiRing][iiLCS])>0.5)) {
				// 	 effStationRingLCSSeg[iiStation][iiRing][iiLCS] = (passStationRingLCSSeg[iiStation][iiRing][iiLCS]-passSBStationRingLCSSeg[iiStation][iiRing][iiLCS])/(totStationRingLCS[iiStation][iiRing][iiLCS]-totSBStationRingLCS[iiStation][iiRing][iiLCS]);
				// 	 effSigmaStationRingLCSSeg[iiStation][iiRing][iiLCS] = sqrt(((passStationRingLCSSeg[iiStation][iiRing][iiLCS]+passSBStationRingLCSSeg[iiStation][iiRing][iiLCS])*(1.-effStationRingLCSSeg[iiStation][iiRing][iiLCS])*(1.-effStationRingLCSSeg[iiStation][iiRing][iiLCS]))+ ((totStationRingLCS[iiStation][iiRing][iiLCS]-passStationRingLCSSeg[iiStation][iiRing][iiLCS])+(totSBStationRingLCS[iiStation][iiRing][iiLCS]-passSBStationRingLCSSeg[iiStation][iiRing][iiLCS]))*effStationRingLCSSeg[iiStation][iiRing][iiLCS]*effStationRingLCSSeg[iiStation][iiRing][iiLCS])/(totStationRingLCS[iiStation][iiRing][iiLCS]-totSBStationRingLCS[iiStation][iiRing][iiLCS]);
				// }
				// if ((totStationRingLCSLCT[iiStation][iiRing][iiLCS]>0.5)&&((totStationRingLCSLCT[iiStation][iiRing][iiLCS]-totSBStationRingLCSLCT[iiStation][iiRing][iiLCS])>0.5)) {
				// 	 effStationRingLCSLCT[iiStation][iiRing][iiLCS] = (passStationRingLCSLCT[iiStation][iiRing][iiLCS]-passSBStationRingLCSLCT[iiStation][iiRing][iiLCS])/(totStationRingLCSLCT[iiStation][iiRing][iiLCS]-totSBStationRingLCSLCT[iiStation][iiRing][iiLCS]);
				// 	 effSigmaStationRingLCSLCT[iiStation][iiRing][iiLCS] = sqrt(((passStationRingLCSLCT[iiStation][iiRing][iiLCS]+passSBStationRingLCSLCT[iiStation][iiRing][iiLCS])*(1.-effStationRingLCSLCT[iiStation][iiRing][iiLCS])*(1.-effStationRingLCSLCT[iiStation][iiRing][iiLCS]))+ ((totStationRingLCSLCT[iiStation][iiRing][iiLCS]-passStationRingLCSLCT[iiStation][iiRing][iiLCS])+(totSBStationRingLCSLCT[iiStation][iiRing][iiLCS]-passSBStationRingLCSLCT[iiStation][iiRing][iiLCS]))*effStationRingLCSLCT[iiStation][iiRing][iiLCS]*effStationRingLCSLCT[iiStation][iiRing][iiLCS])/(totStationRingLCSLCT[iiStation][iiRing][iiLCS]-totSBStationRingLCSLCT[iiStation][iiRing][iiLCS]);
				// }

				// 	 if ((iiStation<4)&&((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])>0.5)&&(((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])-(totSBStationRingLCS[iiStation][iiRing][iiLCS]+totSBStationRingLCS[iiStation+4][iiRing][iiLCS]))>0.5)) {
				// 	   effStationCRingLCSSeg[iiStation][iiRing][iiLCS] = ((passStationRingLCSSeg[iiStation][iiRing][iiLCS]+passStationRingLCSSeg[iiStation+4][iiRing][iiLCS])-(passSBStationRingLCSSeg[iiStation][iiRing][iiLCS]+passSBStationRingLCSSeg[iiStation+4][iiRing][iiLCS]))/((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])-(totSBStationRingLCS[iiStation][iiRing][iiLCS]+totSBStationRingLCS[iiStation+4][iiRing][iiLCS]));
				// 	   effSigmaStationCRingLCSSeg[iiStation][iiRing][iiLCS] = sqrt((((passStationRingLCSSeg[iiStation][iiRing][iiLCS]+passStationRingLCSSeg[iiStation+4][iiRing][iiLCS])+(passSBStationRingLCSSeg[iiStation][iiRing][iiLCS]+passSBStationRingLCSSeg[iiStation+4][iiRing][iiLCS]))*(1.-effStationCRingLCSSeg[iiStation][iiRing][iiLCS])*(1.-effStationCRingLCSSeg[iiStation][iiRing][iiLCS]))+ (((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])-(passStationRingLCSSeg[iiStation][iiRing][iiLCS]+passStationRingLCSSeg[iiStation+4][iiRing][iiLCS]))+((totSBStationRingLCS[iiStation][iiRing][iiLCS]+totSBStationRingLCS[iiStation+4][iiRing][iiLCS])-(passSBStationRingLCSSeg[iiStation][iiRing][iiLCS]+passSBStationRingLCSSeg[iiStation+4][iiRing][iiLCS])))*effStationCRingLCSSeg[iiStation][iiRing][iiLCS]*effStationCRingLCSSeg[iiStation][iiRing][iiLCS])/((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])-(totSBStationRingLCS[iiStation][iiRing][iiLCS]+totSBStationRingLCS[iiStation+4][iiRing][iiLCS]));

				// 	   effStationCRingLCSLCT[iiStation][iiRing][iiLCS] = ((passStationRingLCSLCT[iiStation][iiRing][iiLCS]+passStationRingLCSLCT[iiStation+4][iiRing][iiLCS])-(passSBStationRingLCSLCT[iiStation][iiRing][iiLCS]+passSBStationRingLCSLCT[iiStation+4][iiRing][iiLCS]))/((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])-(totSBStationRingLCS[iiStation][iiRing][iiLCS]+totSBStationRingLCS[iiStation+4][iiRing][iiLCS]));
				// 	   effSigmaStationCRingLCSLCT[iiStation][iiRing][iiLCS] = sqrt((((passStationRingLCSLCT[iiStation][iiRing][iiLCS]+passStationRingLCSLCT[iiStation+4][iiRing][iiLCS])+(passSBStationRingLCSLCT[iiStation][iiRing][iiLCS]+passSBStationRingLCSLCT[iiStation+4][iiRing][iiLCS]))*(1.-effStationCRingLCSLCT[iiStation][iiRing][iiLCS])*(1.-effStationCRingLCSLCT[iiStation][iiRing][iiLCS]))+ (((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])-(passStationRingLCSLCT[iiStation][iiRing][iiLCS]+passStationRingLCSLCT[iiStation+4][iiRing][iiLCS]))+((totSBStationRingLCS[iiStation][iiRing][iiLCS]+totSBStationRingLCS[iiStation+4][iiRing][iiLCS])-(passSBStationRingLCSLCT[iiStation][iiRing][iiLCS]+passSBStationRingLCSLCT[iiStation+4][iiRing][iiLCS])))*effStationCRingLCSLCT[iiStation][iiRing][iiLCS]*effStationCRingLCSLCT[iiStation][iiRing][iiLCS])/((totStationRingLCS[iiStation][iiRing][iiLCS]+totStationRingLCS[iiStation+4][iiRing][iiLCS])-(totSBStationRingLCS[iiStation][iiRing][iiLCS]+totSBStationRingLCS[iiStation+4][iiRing][iiLCS]));
				// 	 }


				// segEffStationRingLCS[iiStation][iiRing]->SetBinContent(iiLCS+1,effStationRingLCSSeg[iiStation][iiRing][iiLCS]);
				// segEffStationRingLCS[iiStation][iiRing]->SetBinError(iiLCS+1,effSigmaStationRingLCSSeg[iiStation][iiRing][iiLCS]);
				// LCTEffStationRingLCS[iiStation][iiRing]->SetBinContent(iiLCS+1,effStationRingLCSLCT[iiStation][iiRing][iiLCS]);
				// LCTEffStationRingLCS[iiStation][iiRing]->SetBinError(iiLCS+1,effSigmaStationRingLCSLCT[iiStation][iiRing][iiLCS]);
				// if (iiStation<4){
				// segEffStationCRingLCS[iiStation][iiRing]->SetBinContent(iiLCS+1,effStationCRingLCSSeg[iiStation][iiRing][iiLCS]);
				// segEffStationCRingLCS[iiStation][iiRing]->SetBinError(iiLCS+1,effSigmaStationCRingLCSSeg[iiStation][iiRing][iiLCS]);
				// LCTEffStationCRingLCS[iiStation][iiRing]->SetBinContent(iiLCS+1,effStationCRingLCSLCT[iiStation][iiRing][iiLCS]);
				// LCTEffStationCRingLCS[iiStation][iiRing]->SetBinError(iiLCS+1,effSigmaStationCRingLCSLCT[iiStation][iiRing][iiLCS]);
				// }

				for (Int_t iiChamber=0; iiChamber < 37; iiChamber++){

					if ((totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]>0.5)&&((totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-totSBStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS])>0.5)) {
						effStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS] = (passStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS]-passSBStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS])/(totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-totSBStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]);
						effSigmaStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS] = sqrt(((passStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS]+passSBStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS])*(1.-effStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS])*(1.-effStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS]))+ ((totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-passStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS])+(totSBStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-passSBStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS]))*effStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS]*effStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS])/(totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-totSBStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]);

						effStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS] = (passStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS]-passSBStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS])/(totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-totSBStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]);
						effSigmaStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS] = sqrt(((passStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS]+passSBStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS])*(1.-effStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS])*(1.-effStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS]))+ ((totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-passStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS])+(totSBStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-passSBStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS]))*effStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS]*effStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS])/(totStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]-totSBStationRingChamberLCS[iiStation][iiRing][iiChamber][iiLCS]);
					}	 

					segEffStationRingChamberLCS[iiStation][iiRing][iiChamber]->SetBinContent(iiLCS+1,effStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS]);
					segEffStationRingChamberLCS[iiStation][iiRing][iiChamber]->SetBinError(iiLCS+1,effSigmaStationRingChamberLCSSeg[iiStation][iiRing][iiChamber][iiLCS]);
					LCTEffStationRingChamberLCS[iiStation][iiRing][iiChamber]->SetBinContent(iiLCS+1,effStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS]);
					LCTEffStationRingChamberLCS[iiStation][iiRing][iiChamber]->SetBinError(iiLCS+1,effSigmaStationRingChamberLCSLCT[iiStation][iiRing][iiChamber][iiLCS]);

				}


			} //end loog over LCS bins
			// segEffStationRingLCS[iiStation][iiRing]->Write();
			// LCTEffStationRingLCS[iiStation][iiRing]->Write();
			// if (iiStation<4){
			// segEffStationCRingLCS[iiStation][iiRing]->Write();
			// LCTEffStationCRingLCS[iiStation][iiRing]->Write();
			// }
			for (Int_t iiChamber=0; iiChamber < 37; iiChamber++){
				segEffStationRingChamberLCS[iiStation][iiRing][iiChamber]->Write();
				LCTEffStationRingChamberLCS[iiStation][iiRing][iiChamber]->Write();
			}      



		} // end loop over rings 
	} // end loop over stations

	// segEff2DStationRingChamber->Write();
	// LCTEff2DStationRingChamber->Write();

	// if (fitEff) {
	//   segEffFit2DStationRingChamber->Write();
	//   segEffDiff2DStationRingChamber->Write();
	//   segEffDiff1D->Write();
	// }

	// for (Int_t iiPt=0; iiPt< numPtBins; iiPt++){
	//   if (totGlobalPt[iiPt]>0.5) effGlobalSegPt[iiPt] = passGlobalSegPt[iiPt]/totGlobalPt[iiPt];
	//   if (totGlobalPt[iiPt]>0.5) effSigmaGlobalSegPt[iiPt] = sqrt(effGlobalSegPt[iiPt]*(1.0-effGlobalSegPt[iiPt])/totGlobalPt[iiPt]);
	//   binVal = (ptBins[iiPt]+ptBins[iiPt+1])/2.0;
	//   globalCSCSegEffPt->Fill(binVal,effGlobalSegPt[iiPt]);
	//   globalCSCSegEffPt->SetBinError(iiPt+1,effSigmaGlobalSegPt[iiPt]);
	//   //std::cout << "tot: " << totGlobalPt[iiPt] << std::endl;
	//   //std::cout << "eff: " << effGlobalSegPt[iiPt] << std::endl;
	//   //std::cout << "err: " << effSigmaGlobalSegPt[iiPt] << std::endl;

	// } // end loop over iiPt bins




	// // Counter printout
	// std::cout << "Failed fiducial  " << nFailFiducial << std::endl;
	// std::cout << "Failed Found Seg " << nFailFoundSeg << std::endl;
	// std::cout << "Failed Good Seg  " << nFailGoodSeg << std::endl;
	// std::cout << "Failed dxy       " << nFailDxy << std::endl;



	zMassAll->Write();
	zMassGood->Write();
	zMassBad->Write();

	muonSegmentsFidAll->Write();
	muonSegmentsFid1->Write();
	muonSegmentsFid2->Write();
	muonSegmentsWithME21->Write();
	muonSegmentsNoME21->Write();

	segmentsFidAll->Write();
	segmentsFid1->Write();
	segmentsFid2->Write();
	segmentsWithME21->Write();
	segmentsNoME21->Write();

	segmentsFid1HighPV->Write();
	segmentsFid2HighPV->Write();
	segmentsFid1LowPV->Write();
	segmentsFid2LowPV->Write();

	muonSegmentsFid1HighPV->Write();
	muonSegmentsFid2HighPV->Write();
	muonSegmentsFid1LowPV->Write();
	muonSegmentsFid2LowPV->Write();

	segmentsFid1HighpT->Write();
	segmentsFid2HighpT->Write();



	std::cout << "Total, pass, fail " << totalFiducial << " " << totalPass << " " << totalFail << std::endl;

	// globalCSCSegEffPt->Write();

	cscEffHistoFile.Write();
	cscEffHistoFile.Close();


}

// int main() {
//   CSCEffFast* cscEffFast = new CSCEffFast();
//   cscEffFast->Loop();
//   return 0;
// }

/*
	 .L CSCEffFast.C+
	 CSCEffFast* cscEffFast = new CSCEffFast()
	 cscEffFast->Loop()
	 */
