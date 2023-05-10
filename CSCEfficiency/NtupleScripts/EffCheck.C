#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;
string GetMELabel(Int_t station, Int_t ring);

void EffCheck(){
	//Constants
	float DEAD_DCFEB_THRESHOLD = 0.25;	// Efficiency threshold for dead (D)CFEBs.
	float effThreshold = 0.8;			// Efficiency threshold for file readouts.
	double lowEff = 0.6;
	double highEff = 1.02;
	int firstRun = 355000;
	int lastRun = 362800;
	
	//Flags
	bool verbose = false;
	bool chamberPlots = true;
	
	//Initializing
	char file[50];
	char name[50];
	char stationRing[10];
	char title[100];

	//Opening Text File
	ofstream cscTextEffData; 
	cscTextEffData.open("cscTextEffData.txt");
	ofstream cscEffCheck;
	cscEffCheck.open("cscEffCheck.txt");
	TFile * file0 = TFile::Open("cscEffHistoFile.root");
	
	//Begin Chamber Plots
	float binContent;
	bool printedDCFEBCheck,deadChamber;
	stringstream cscEffCheckBanner;
	if (chamberPlots){
		for (Int_t iiStation=0; iiStation < 8; iiStation++){
			for (Int_t iiRing=0; iiRing < 4; iiRing++){
				for (Int_t iiChamber=1; iiChamber < 37; iiChamber++){
					if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&iiRing==1&&iiChamber>18) continue;
					if ((iiStation==1||iiStation==2||iiStation==3||iiStation==5||iiStation==6||iiStation==7)&&(iiRing==0||iiRing==3)) continue;

					//Printing to Text File
					// first run 355100
					snprintf(name,50,"segEffStation%dRing%dChamber%dRun",iiStation+1,iiRing,iiChamber);
					TH1F * segEffChamberRun = (TH1F*)file0->Get(name);
					segEffChamberRun->GetXaxis()->SetRangeUser(firstRun,lastRun);
					cscTextEffData << file << std::endl;
					for (Int_t ii=0; ii< lastRun-firstRun; ii++){
						if (segEffChamberRun->GetBinContent(ii)>0.0&&segEffChamberRun->GetBinContent(ii) < effThreshold){
							cscTextEffData << segEffChamberRun->GetXaxis()->GetBinCenter(ii) << " " << segEffChamberRun->GetBinContent(ii) << std::endl;
						}
					}
					
					//Identifying Dead DCFEBs and Chambers
					snprintf(name,50,"segEff2DStation%dRing%dChamberDCFEB",iiStation+1,iiRing);
					printedDCFEBCheck = false;
					deadChamber = false;
					cscEffCheckBanner.str(std::string());
					cscEffCheckBanner << "--------------------------------------" << std::endl;
					cscEffCheckBanner << "CSC Segment Efficiency Station " << iiStation+1 << " Ring " << iiRing;
					cscEffCheckBanner << " (" << GetMELabel(iiStation, iiRing) << "/" << iiChamber << ")" << std::endl << std::endl;
					for (Int_t iiDCFEB = 1; iiDCFEB < 6; iiDCFEB++){
						binContent = ((TH2F*)file0->Get(name))->GetBinContent(iiChamber,iiDCFEB);
						//Check for dead chamber
						if (binContent == 0.00){
							if (!deadChamber && iiDCFEB == 1) deadChamber = true;
							else if (deadChamber && iiDCFEB == 5){
								//Print out information if chamber has been dead for all DCFEBs
								if (!printedDCFEBCheck){
									cscEffCheck << cscEffCheckBanner.str();
									printedDCFEBCheck = true;
								}
								cscEffCheck << "Potential Failure: Chamber " << iiChamber << std::endl;
							}
							continue;
						}
						else if (deadChamber) deadChamber = false;
						
						//Check for dead DCFEB
						if (binContent < DEAD_DCFEB_THRESHOLD){
							if (!printedDCFEBCheck){
								cscEffCheck << cscEffCheckBanner.str();
								printedDCFEBCheck = true;
							}
							cscEffCheck << "Potential Failure: DCFEB " << iiDCFEB << " (" << binContent << ")" << std::endl;
						}
						//Check for low efficiency TODO
						else if (binContent < 0.90){
							continue;
							if (!printedDCFEBCheck){
								cscEffCheck << cscEffCheckBanner.str();
								printedDCFEBCheck = true;
							}
							cscEffCheck << "Low Efficiency: DCFEB " << iiDCFEB << " (" << binContent << ")" << std::endl;
						}
					}
				}
			}
		}
	}
	
	//Closing File and Exiting
	cscTextEffData.close();
	cscEffCheck.close();
}

string GetMELabel(Int_t station, Int_t ring){
	string result = "";
	if ((station==1||station==2||station==3||station==5||station==6||station==7)&&(ring==0||ring==3))
		return result;
	string symb = (station < 4)? "-" : "+";
	if (station >= 4) station -= 4;

	result = "ME" + symb + to_string(station+1);
	if (ring == 0) result += "1A";
	else if (station == 0 && ring == 1) result += "1B";
	else result += to_string(ring);
	
	return result;
}
