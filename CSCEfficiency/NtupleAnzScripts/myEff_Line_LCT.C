{

gROOT->SetStyle("Plain");
gROOT->SetBatch(1);
//gStyle->SetPaintTextFormat("3.3g");
gStyle->SetPaintTextFormat("6.1f");
gStyle->SetOptStat(0);

gStyle->SetFrameBorderMode(0);
gStyle->SetCanvasBorderMode(0);
gStyle->SetPadBorderMode(0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);
gStyle->SetTitleColor(1);
gStyle->SetStatColor(0);
gStyle->SetFrameFillColor(0);
gStyle->SetFrameLineWidth(0);
gStyle->SetCanvasBorderMode(0); 
gStyle->SetCanvasBorderSize(0);
gStyle->SetFrameBorderMode(0);

gStyle->SetMarkerStyle(8); 
gStyle->SetLineStyleString(2,"[12 12]");  
gStyle->SetOptTitle(1); 
gStyle->SetOptStat(1); 
gStyle->SetOptFit(1); 
gStyle->SetOptStat(0); 


gStyle->SetPadBorderSize(0);
gStyle->SetCanvasBorderSize(0);
gStyle->SetLegendBorderSize(0);
gStyle->SetFrameBorderSize(0);
gStyle->SetStatBorderSize(0);
gStyle->SetTitleBorderSize(0);

 gStyle->SetHistMinimumZero();

const Int_t Number = 5; 
Double_t  Red[Number] = {0.,1.00, 1.00, 1.00, .00};
Double_t  Green[Number] = {0.,0., 0.00, 1.00, 1.00};
Double_t  Blue[Number] = {1.0,1.00, 0.00, 0.00, 0.00};
Double_t  Length[Number] = {0.00, 0.4, 0.6, 0.8, 1.00};
Int_t nb = 500; 
 Int_t i=TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb); 

 gStyle->SetNumberContours(500);

 TString HistoNames[3]={"SEGEff","SEGEff_upErr","SEGEff_downErr"};

  TFile * file_in=new TFile("resultplots_NtupleAnzScripts.root","read");
  file_in->cd();

   TCanvas *ch2p2 = new TCanvas("ch2p2","ch2p2",600,400);

  for (int i=0;i<3;i++){
  
   TH2Poly *h2p = new TH2Poly();
   //   h2p=(TH2Poly)SEGEff->Clone("name");
   //   h2p=SEGEff; // working!
   //   h2p = (TH2Poly*)file_in->Get("SEGEff");
   h2p = (TH2Poly*)file_in->Get(HistoNames[i]);
   //   h2p=SEGEff->Clone("name"); // working!
   //   h2p=SEGEff_upErr->Clone("name");
   //   h2p->SetName("Boxes");
   //   h2p->SetTitle("Boxes");
   //   gStyle->SetPalette(1);

   TList *bins = h2p->GetBins(); 
   TIter Next(bins);
   TObject *obj;
   TH2PolyBin *b;
   TGraph *g;
   if (i>0){
   while ((obj = Next())) {
    b = (TH2PolyBin*)obj;
    g = (TGraph*)b->GetPolygon();
    if (g) g->SetLineWidth(0);
    if (g) g->SetLineColor(0);
    if (g) g->SetLineColorAlpha(kGreen, 0.00001);
	    }
}
   h2p->SetContour(nb); 
   if (i==0){
     h2p->GetYaxis()->SetTitle("Endcap/Station/Ring");
     //     h2p->GetXaxis()->SetTitle("Chamber within ring");
     h2p->GetXaxis()->SetTitle("#phi");
     h2p->GetYaxis()->SetTitleOffset(1.35);
     
     //h2p->SetTitle("CSC Trigger Primitive Efficiency (%)");
     h2p->SetTitle("CSC Segment Reconstruction Efficiency (%)"); 

TPaveText* cms_label = new TPaveText(0.06, 0.84, 0.9, 1.0, "NDC");
cms_label->SetFillStyle(0);
cms_label->SetBorderSize(0);
cms_label->SetTextSize(0.03);
cms_label->SetTextAlign(12);
//cms_label->AddText("CMS Preliminary                                                  #sqrt{s}=13 TeV,  2016B");
cms_label->AddText("CMS Preliminary 2018                                                                  #sqrt{s}=13 TeV, 2018A");

     h2p->Draw("colz,text");
cms_label->Draw();
   }
   else
     h2p->Draw("same,text");
     
  }
   ch2p2->SaveAs("2018A_wide_SEG.pdf");
  
}

