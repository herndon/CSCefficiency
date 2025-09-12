//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 18 10:59:44 2019 by ROOT/version 6.18/00
// from TTree Fraction//Fraction
// found on file: /hdfs/store/user/strembat/TnPFiles_May-16-2019/2018D/afterHV/PV/SEG/Tmp_NtupleAnzScripts.root
//////////////////////////////////////////////////////////

#ifndef CSCEffFast_h
#define CSCEffFast_h

#include <TSystem.h>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "stdio.h"
#include <iostream>


// Header file for the classes stored in the TTree if any.
#include <vector>

#define newData true

class CSCEffFast {
  public :
    // Define dataset run ranges
    typedef struct {
      Int_t firstRun;
      Int_t lastRun;
      Text_t id[10];
    } dataset;
    static constexpr dataset d2022all = {355000, 362760, "2022"};

    static constexpr dataset d2023all = {367100, 370790, "2023"};
    static constexpr dataset d2023Cv1 = {367100, 367515, "2023Cv1"};
    static constexpr dataset d2023Cv2 = {367516, 367758, "2023Cv2"};
    static constexpr dataset d2023Cv4 = {367765, 369694, "2023Cv4"};
    static constexpr dataset d2023Dv1 = {369803, 370580, "2023Dv1"};
    static constexpr dataset d2023Dv2 = {370603, 370790, "2023Dv2"};

    static constexpr dataset d2024all = {379412, 387000, "2024"};
    //static constexpr dataset d2024Bv1 = {378900, 379400, "2024Bv1"};// this data is pretty much all bad
    static constexpr dataset d2024Cv1 = {379412, 380252, "2024Cv1"};
    static constexpr dataset d2024Dv1 = {380253, 380947, "2024Dv1"};
    static constexpr dataset d2024Ev1 = {380948, 381383, "2024Ev1"};
    static constexpr dataset d2024Ev2 = {381384, 381600, "2024Ev2"};
    static constexpr dataset d2024Fv1 = {381944, 383779, "2024Fv1"};
    static constexpr dataset d2024Gv1 = {383780, 385813, "2024Gv1"};
    static constexpr dataset d2024Gv1r = {383780, 385813, "2024Gv1"};
    //static constexpr dataset d2024HIv12 = {385814, 387000, "2024HIv12"};
    static constexpr dataset d2024Hv1 = {385814, 386408, "2024Hv1"};
    static constexpr dataset d2024Iv1 = {386409, 386797, "2024Iv1"};
    static constexpr dataset d2024Iv2 = {386798, 387000, "2024Iv2"};

    static constexpr dataset d2025all = {391658, 395899, "2025"};
    static constexpr dataset d2025Bv1 = {391658, 392112, "2025Bv1"};
    static constexpr dataset d2025Cv1 = {392175, 393087, "2025Cv1"};
    static constexpr dataset d2025Cv2 = {393111, 393516, "2025Cv2"};
    static constexpr dataset d2025Dv1 = {394637, 395899, "2025Dv1"};
    static constexpr dataset d2025Ev1 = {395968, 396597, "2025Ev1"};
#if newData
    //static constexpr dataset firstSet = d2025all;
    //static constexpr dataset lastSet  = d2025all;
    static constexpr dataset firstSet = d2025Ev1;
    static constexpr dataset lastSet  = d2025Ev1;
#else
    static const Int_t firstSet = d2022all;
    static const Int_t lastSet  = d2022all;
#endif
    // These can be different from the sets' run ranges.
    // If specified, any datasets within the run range will have
    // their full set of files included for the script, but only
    // those in the run range will be included in the efficiency
    // calculation.
    static const Int_t firstRun = firstSet.firstRun;
    static const Int_t lastRun  = lastSet.lastRun;

    TNamed *setName, *setRuns, *setRunsTrue;

    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    // Fixed size dimensions of array or collections stored in the TTree if any.

    // Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    Int_t           run_number;
    Int_t           event_number;
    Int_t           LumiBlock;
    Int_t           LumiSection;
    std::vector<float>   *LumiInst;
    std::vector<float>   *LumiInstErr;
    std::vector<float>   *LumiInstQlty;
    std::vector<float>   *LumiEtInst;
    std::vector<float>   *LumiEtInstErr;
    std::vector<float>   *LumiEtInstQlty;
    std::vector<float>   *LumiStartOrbit;
    std::vector<float>   *LumiNumOrbits;
    Int_t           bunchX;
    Int_t           orbitNumb;
    Float_t         mcweight;
    UInt_t          numberOfPUVertices;
    Float_t         numberOfPUVerticesMixingTruth;
    UInt_t          numberOfPUVerticesTot;
    UInt_t          numberOfPrimaryVertices;
    Bool_t          trgSingle;
    Int_t           nTrkCountCSCSeg;
    Int_t           nTotalTrks;
    Bool_t          trackVeto_strict;
    Bool_t          trackVeto_isClosestToLCT;
    Int_t           myRegion;
    Float_t         MuTagPt;
    Float_t         MuTagEta;
    Float_t         MuTagPhi;
    Float_t         MuTagIsoR03Ratio;
    Float_t         MuTagIsoR05Ratio;
    Float_t         MuTagPFIsoR04Ratio;
    Int_t           MuTagPromt;
    Int_t           MuTagnSegTrkArb;
    Bool_t          MuTagCaloL;
    Bool_t          MuTagCaloT;
    Float_t         MuTagtracktruth_pt;
    Float_t         MuTagtracktruth_p;
    Float_t         MuTagtracktruth_id;
    ULong64_t       MuTagtracktruth_type;
    Bool_t          MuTagtracktruth_isPileup;
    Int_t           MuTagtracktruth_thesamewith;
    Float_t         vtx_r;
    Float_t         vtx_z;
    Float_t         vtx_rError;
    Float_t         vtx_zError;
    Float_t         vtx_normChi2;
    Int_t           vtx_size;
    Bool_t          iSameVtx;
    Float_t         invMass;
    Float_t         tracks_e;
    Float_t         tracks_pt;
    Float_t         tracks_eta;
    Float_t         tracks_phi;
    Int_t           tracks_charge;
    Int_t           tracks_id;
    Float_t         tracks_normchi2;
    Float_t         tracks_dxy;
    Float_t         tracks_dz;
    Float_t         tracks_vx;
    Float_t         tracks_vy;
    Float_t         tracks_vz;
    Float_t         tracks_IsoR03Ratio;
    Float_t         tracks_IsoR05Ratio;
    Float_t         tracks_qoverp;
    Float_t         tracks_lambda;
    Int_t           tracks_recHitsSize;
    Int_t           tracks_numberOfValidHits;
    Int_t           tracks_numberOfLostHits;
    Float_t         tracks_qoverpError;
    Float_t         tracks_ptError;
    Float_t         tracks_thetaError;
    Float_t         tracks_lambdaError;
    Float_t         tracks_etaError;
    Float_t         tracks_phiError;
    Float_t         tracks_dxyError;
    Float_t         tracks_d0Error;
    Float_t         tracks_dszError;
    Float_t         tracks_dzError;
    Bool_t          tracks_isCaloMuTrk;
    Bool_t          tracks_isTrackerMuTrk;
    Int_t           tracks_numberOfMatches;
    Float_t         tracktruth_pt;
    Float_t         tracktruth_p;
    Float_t         tracktruth_e;
    Float_t         tracktruth_id;
    ULong64_t       tracktruth_type;
    Bool_t          tracktruth_isPileup;
    Int_t           tracktruth_thesamewith;
    Bool_t          CSCEndCapPlus;
    UChar_t         CSCRg1;
    UChar_t         CSCCh1;
    Bool_t          CSCCBad1;
    Float_t         CSCDyProjHVGap1;
    Float_t         CSCDyErrProjHVGap1;
    Float_t         CSCProjDistEdge1;
    Float_t         CSCProjDistErrEdge1;
    Float_t         CSCTTxLc1;
    Float_t         CSCTTwLc1;
    Float_t         CSCTTyLc1;
    Float_t         CSCTTsLc1;
    Float_t         CSCTTwSegxLc1;
    Float_t         CSCTTwSegyLc1;
    Float_t         CSCTT3xLc1;
    Float_t         CSCTT3wLc1;
    Float_t         CSCTT3yLc1;
    Float_t         CSCTT3sLc1;
    Float_t         CSCTT3wLCTxLc1;
    Float_t         CSCTT3wLCTyLc1;
    Float_t         CSCTTxGc1;
    Float_t         CSCTTyGc1;
    Float_t         CSCTTzGc1;
    Float_t         CSCTTetaGc1;
    Float_t         CSCTT3xGc1;
    Float_t         CSCTT3yGc1;
    Float_t         CSCTT3zGc1;
    Float_t         CSCTT3etaGc1;
    Float_t         CSCSegNumber1;
    Float_t         DTSegNumber1;
    Float_t         RPCSegNumber1;
    Float_t         CSCSegxLc1;
    Float_t         CSCSegyLc1;
    Float_t         CSCSegxErrLc1;
    Float_t         CSCSegyErrLc1;
    Float_t         CSCdXdZTTSeg1;
    Float_t         CSCdYdZTTSeg1;
    Float_t         CSCSegChisqProb1;
    Int_t           CSCnSegHits1;
    Float_t         CSCDxTTSeg1;
    Float_t         CSCDxErrTTSeg1;
    Float_t         CSCDyTTSeg1;
    Float_t         CSCDyErrTTSeg1;
    Float_t         CSCDxyTTSeg1;
    Float_t         CSCDxyErrTTSeg1;
    Float_t         CSCLCTxLc1;
    Float_t         CSCLCTyLc1;
    Int_t           CSCLCTbx1;
    Int_t           N_seg_inChamber1;
    Float_t         CSCDxTTLCT1;
    Float_t         CSCDxErrTTLCT1;
    Float_t         CSCDyTTLCT1;
    Float_t         CSCDyErrTTLCT1;
    Float_t         CSCDxyTTLCT1;
    Float_t         CSCDxyErrTTLCT1;
    Float_t         dRTkMu1;
    UChar_t         CSCRg2;
    UChar_t         CSCCh2;
    Bool_t          CSCCBad2;
    Float_t         CSCDyProjHVGap2;
    Float_t         CSCDyErrProjHVGap2;
    Float_t         CSCProjDistEdge2;
    Float_t         CSCProjDistErrEdge2;
    Float_t         CSCTTxLc2;
    Float_t         CSCTTwLc2;
    Float_t         CSCTTyLc2;
    Float_t         CSCTTsLc2;
    Float_t         CSCTTwSegxLc2;
    Float_t         CSCTTwSegyLc2;
    Float_t         CSCTT3xLc2;
    Float_t         CSCTT3wLc2;
    Float_t         CSCTT3yLc2;
    Float_t         CSCTT3sLc2;
    Float_t         CSCTT3wLCTxLc2;
    Float_t         CSCTT3wLCTyLc2;
    Float_t         CSCTTxGc2;
    Float_t         CSCTTyGc2;
    Float_t         CSCTTzGc2;
    Float_t         CSCTTetaGc2;
    Float_t         CSCTT3xGc2;
    Float_t         CSCTT3yGc2;
    Float_t         CSCTT3zGc2;
    Float_t         CSCTT3etaGc2;
    Float_t         CSCSegNumber2;
    Float_t         DTSegNumber2;
    Float_t         RPCSegNumber2;
    Float_t         CSCSegxLc2;
    Float_t         CSCSegyLc2;
    Float_t         CSCSegxErrLc2;
    Float_t         CSCSegyErrLc2;
    Float_t         CSCdXdZTTSeg2;
    Float_t         CSCdYdZTTSeg2;
    Float_t         CSCSegChisqProb2;
    Int_t           CSCnSegHits2;
    Float_t         CSCDxTTSeg2;
    Float_t         CSCDxErrTTSeg2;
    Float_t         CSCDyTTSeg2;
    Float_t         CSCDyErrTTSeg2;
    Float_t         CSCDxyTTSeg2;
    Float_t         CSCDxyErrTTSeg2;
    Float_t         CSCLCTxLc2;
    Float_t         CSCLCTyLc2;
    Int_t           CSCLCTbx2;
    Int_t           N_seg_inChamber2;
    Float_t         CSCDxTTLCT2;
    Float_t         CSCDxErrTTLCT2;
    Float_t         CSCDyTTLCT2;
    Float_t         CSCDyErrTTLCT2;
    Float_t         CSCDxyTTLCT2;
    Float_t         CSCDxyErrTTLCT2;
    Float_t         dRTkMu2;
    UChar_t         CSCRg3;
    UChar_t         CSCCh3;
    Bool_t          CSCCBad3;
    Float_t         CSCDyProjHVGap3;
    Float_t         CSCDyErrProjHVGap3;
    Float_t         CSCProjDistEdge3;
    Float_t         CSCProjDistErrEdge3;
    Float_t         CSCTTxLc3;
    Float_t         CSCTTwLc3;
    Float_t         CSCTTyLc3;
    Float_t         CSCTTsLc3;
    Float_t         CSCTTwSegxLc3;
    Float_t         CSCTTwSegyLc3;
    Float_t         CSCTT3xLc3;
    Float_t         CSCTT3wLc3;
    Float_t         CSCTT3yLc3;
    Float_t         CSCTT3sLc3;
    Float_t         CSCTT3wLCTxLc3;
    Float_t         CSCTT3wLCTyLc3;
    Float_t         CSCTTxGc3;
    Float_t         CSCTTyGc3;
    Float_t         CSCTTzGc3;
    Float_t         CSCTTetaGc3;
    Float_t         CSCTT3xGc3;
    Float_t         CSCTT3yGc3;
    Float_t         CSCTT3zGc3;
    Float_t         CSCTT3etaGc3;
    Float_t         CSCSegNumber3;
    Float_t         DTSegNumber3;
    Float_t         RPCSegNumber3;
    Float_t         CSCSegxLc3;
    Float_t         CSCSegyLc3;
    Float_t         CSCSegxErrLc3;
    Float_t         CSCSegyErrLc3;
    Float_t         CSCdXdZTTSeg3;
    Float_t         CSCdYdZTTSeg3;
    Float_t         CSCSegChisqProb3;
    Int_t           CSCnSegHits3;
    Float_t         CSCDxTTSeg3;
    Float_t         CSCDxErrTTSeg3;
    Float_t         CSCDyTTSeg3;
    Float_t         CSCDyErrTTSeg3;
    Float_t         CSCDxyTTSeg3;
    Float_t         CSCDxyErrTTSeg3;
    Float_t         CSCLCTxLc3;
    Float_t         CSCLCTyLc3;
    Int_t           CSCLCTbx3;
    Int_t           N_seg_inChamber3;
    Float_t         CSCDxTTLCT3;
    Float_t         CSCDxErrTTLCT3;
    Float_t         CSCDyTTLCT3;
    Float_t         CSCDyErrTTLCT3;
    Float_t         CSCDxyTTLCT3;
    Float_t         CSCDxyErrTTLCT3;
    Float_t         dRTkMu3;
    UChar_t         CSCRg4;
    UChar_t         CSCCh4;
    Bool_t          CSCCBad4;
    Float_t         CSCDyProjHVGap4;
    Float_t         CSCDyErrProjHVGap4;
    Float_t         CSCProjDistEdge4;
    Float_t         CSCProjDistErrEdge4;
    Float_t         CSCTTxLc4;
    Float_t         CSCTTwLc4;
    Float_t         CSCTTyLc4;
    Float_t         CSCTTsLc4;
    Float_t         CSCTTwSegxLc4;
    Float_t         CSCTTwSegyLc4;
    Float_t         CSCTT3xLc4;
    Float_t         CSCTT3wLc4;
    Float_t         CSCTT3yLc4;
    Float_t         CSCTT3sLc4;
    Float_t         CSCTT3wLCTxLc4;
    Float_t         CSCTT3wLCTyLc4;
    Float_t         CSCTTxGc4;
    Float_t         CSCTTyGc4;
    Float_t         CSCTTzGc4;
    Float_t         CSCTTetaGc4;
    Float_t         CSCTT3xGc4;
    Float_t         CSCTT3yGc4;
    Float_t         CSCTT3zGc4;
    Float_t         CSCTT3etaGc4;
    Float_t         CSCSegNumber4;
    Float_t         DTSegNumber4;
    Float_t         RPCSegNumber4;
    Float_t         CSCSegxLc4;
    Float_t         CSCSegyLc4;
    Float_t         CSCSegxErrLc4;
    Float_t         CSCSegyErrLc4;
    Float_t         CSCdXdZTTSeg4;
    Float_t         CSCdYdZTTSeg4;
    Float_t         CSCSegChisqProb4;
    Int_t           CSCnSegHits4;
    Float_t         CSCDxTTSeg4;
    Float_t         CSCDxErrTTSeg4;
    Float_t         CSCDyTTSeg4;
    Float_t         CSCDyErrTTSeg4;
    Float_t         CSCDxyTTSeg4;
    Float_t         CSCDxyErrTTSeg4;
    Float_t         CSCLCTxLc4;
    Float_t         CSCLCTyLc4;
    Int_t           CSCLCTbx4;
    Int_t           N_seg_inChamber4;
    Float_t         CSCDxTTLCT4;
    Float_t         CSCDxErrTTLCT4;
    Float_t         CSCDyTTLCT4;
    Float_t         CSCDyErrTTLCT4;
    Float_t         CSCDxyTTLCT4;
    Float_t         CSCDxyErrTTLCT4;
    Float_t         dRTkMu4;
    std::vector<bool>    *HLTMuAcceptance;
    Float_t         HLTDiMuAcceptance;
    std::vector<float>   *minDRHLTMu;
    Float_t         minDRHLTDiMu;
    Float_t         minDRHLTAllSingleMu;

    // List of branches
    TBranch        *b_run_number;   //!
    TBranch        *b_event_number;   //!
    TBranch        *b_LumiBlock;   //!
    TBranch        *b_LumiSection;   //!
    TBranch        *b_LumiInst;   //!
    TBranch        *b_LumiInstErr;   //!
    TBranch        *b_LumiInstQlty;   //!
    TBranch        *b_LumiEtInst;   //!
    TBranch        *b_LumiEtInstErr;   //!
    TBranch        *b_LumiEtInstQlty;   //!
    TBranch        *b_LumiStartOrbit;   //!
    TBranch        *b_LumiNumOrbits;   //!
    TBranch        *b_bunchX;   //!
    TBranch        *b_orbitNumb;   //!
    TBranch        *b_mcweight;   //!
    TBranch        *b_numberOfPUVertices;   //!
    TBranch        *b_numberOfPUVerticesMixingTruth;   //!
    TBranch        *b_numberOfPUVerticesTot;   //!
    TBranch        *b_numberOfPrimaryVertices;   //!
    TBranch        *b_trgSingle;   //!
    TBranch        *b_nTrkCountCSCSeg;   //!
    TBranch        *b_nTotalTrks;   //!
    TBranch        *b_trackVeto_strict;   //!
    TBranch        *b_trackVeto_isClosestToLCT;   //!
    TBranch        *b_myRegion;   //!
    TBranch        *b_MuTagPt;   //!
    TBranch        *b_MuTagEta;   //!
    TBranch        *b_MuTagPhi;   //!
    TBranch        *b_MuTagIsoR03Ratio;   //!
    TBranch        *b_MuTagIsoR05Ratio;   //!
    TBranch        *b_MuTagPFIsoR04Ratio;   //!
    TBranch        *b_MuTagPromt;   //!
    TBranch        *b_MuTagnSegTrkArb;   //!
    TBranch        *b_MuTagCaloL;   //!
    TBranch        *b_MuTagCaloT;   //!
    TBranch        *b_MuTagtracktruth_pt;   //!
    TBranch        *b_MuTagtracktruth_p;   //!
    TBranch        *b_MuTagtracktruth_id;   //!
    TBranch        *b_MuTagtracktruth_type;   //!
    TBranch        *b_MuTagtracktruth_isPileup;   //!
    TBranch        *b_MuTagtracktruth_thesamewith;   //!
    TBranch        *b_vtx_r;   //!
    TBranch        *b_vtx_z;   //!
    TBranch        *b_vtx_rError;   //!
    TBranch        *b_vtx_zError;   //!
    TBranch        *b_vtx_normChi2;   //!
    TBranch        *b_vtx_size;   //!
    TBranch        *b_iSameVtx;   //!
    TBranch        *b_invMass;   //!
    TBranch        *b_tracks_e;   //!
    TBranch        *b_tracks_pt;   //!
    TBranch        *b_tracks_eta;   //!
    TBranch        *b_tracks_phi;   //!
    TBranch        *b_tracks_charge;   //!
    TBranch        *b_tracks_id;   //!
    TBranch        *b_tracks_normchi2;   //!
    TBranch        *b_tracks_dxy;   //!
    TBranch        *b_tracks_dz;   //!
    TBranch        *b_tracks_vx;   //!
    TBranch        *b_tracks_vy;   //!
    TBranch        *b_tracks_vz;   //!
    TBranch        *b_tracks_IsoR03Ratio;   //!
    TBranch        *b_tracks_IsoR05Ratio;   //!
    TBranch        *b_tracks_qoverp;   //!
    TBranch        *b_tracks_lambda;   //!
    TBranch        *b_tracks_recHitsSize;   //!
    TBranch        *b_tracks_numberOfValidHits;   //!
    TBranch        *b_tracks_numberOfLostHits;   //!
    TBranch        *b_tracks_qoverpError;   //!
    TBranch        *b_tracks_ptError;   //!
    TBranch        *b_tracks_thetaError;   //!
    TBranch        *b_tracks_lambdaError;   //!
    TBranch        *b_tracks_etaError;   //!
    TBranch        *b_tracks_phiError;   //!
    TBranch        *b_tracks_dxyError;   //!
    TBranch        *b_tracks_d0Error;   //!
    TBranch        *b_tracks_dszError;   //!
    TBranch        *b_tracks_dzError;   //!
    TBranch        *b_tracks_isCaloMuTrk;   //!
    TBranch        *b_tracks_isTrackerMuTrk;   //!
    TBranch        *b_tracks_numberOfMatches;   //!
    TBranch        *b_tracktruth_pt;   //!
    TBranch        *b_tracktruth_p;   //!
    TBranch        *b_tracktruth_e;   //!
    TBranch        *b_tracktruth_id;   //!
    TBranch        *b_tracktruth_type;   //!
    TBranch        *b_tracktruth_isPileup;   //!
    TBranch        *b_tracktruth_thesamewith;   //!
    TBranch        *b_CSCEndCapPlus;   //!
    TBranch        *b_CSCRg1;   //!
    TBranch        *b_CSCCh1;   //!
    TBranch        *b_CSCCBad1;   //!
    TBranch        *b_CSCDyProjHVGap1;   //!
    TBranch        *b_CSCDyErrProjHVGap1;   //!
    TBranch        *b_CSCProjDistEdge1;   //!
    TBranch        *b_CSCProjDistErrEdge1;   //!
    TBranch        *b_CSCTTxLc1;   //!
    TBranch        *b_CSCTTwLc1;   //!
    TBranch        *b_CSCTTyLc1;   //!
    TBranch        *b_CSCTTsLc1;   //!
    TBranch        *b_CSCTTwSegxLc1;   //!
    TBranch        *b_CSCTTwSegyLc1;   //!
    TBranch        *b_CSCTT3xLc1;   //!
    TBranch        *b_CSCTT3wLc1;   //!
    TBranch        *b_CSCTT3yLc1;   //!
    TBranch        *b_CSCTT3sLc1;   //!
    TBranch        *b_CSCTT3wLCTxLc1;   //!
    TBranch        *b_CSCTT3wLCTyLc1;   //!
    TBranch        *b_CSCTTxGc1;   //!
    TBranch        *b_CSCTTyGc1;   //!
    TBranch        *b_CSCTTzGc1;   //!
    TBranch        *b_CSCTTetaGc1;   //!
    TBranch        *b_CSCTT3xGc1;   //!
    TBranch        *b_CSCTT3yGc1;   //!
    TBranch        *b_CSCTT3zGc1;   //!
    TBranch        *b_CSCTT3etaGc1;   //!
    TBranch        *b_CSCSegNumber1;   //!
    TBranch        *b_DTSegNumber1;   //!
    TBranch        *b_RPCSegNumber1;   //!
    TBranch        *b_CSCSegxLc1;   //!
    TBranch        *b_CSCSegyLc1;   //!
    TBranch        *b_CSCSegxErrLc1;   //!
    TBranch        *b_CSCSegyErrLc1;   //!
    TBranch        *b_CSCdXdZTTSeg1;   //!
    TBranch        *b_CSCdYdZTTSeg1;   //!
    TBranch        *b_CSCSegChisqProb1;   //!
    TBranch        *b_CSCnSegHits1;   //!
    TBranch        *b_CSCDxTTSeg1;   //!
    TBranch        *b_CSCDxErrTTSeg1;   //!
    TBranch        *b_CSCDyTTSeg1;   //!
    TBranch        *b_CSCDyErrTTSeg1;   //!
    TBranch        *b_CSCDxyTTSeg1;   //!
    TBranch        *b_CSCDxyErrTTSeg1;   //!
    TBranch        *b_CSCLCTxLc1;   //!
    TBranch        *b_CSCLCTyLc1;   //!
    TBranch        *b_CSCLCTbx1;   //!
    TBranch        *b_N_seg_inChamber1;   //!
    TBranch        *b_CSCDxTTLCT1;   //!
    TBranch        *b_CSCDxErrTTLCT1;   //!
    TBranch        *b_CSCDyTTLCT1;   //!
    TBranch        *b_CSCDyErrTTLCT1;   //!
    TBranch        *b_CSCDxyTTLCT1;   //!
    TBranch        *b_CSCDxyErrTTLCT1;   //!
    TBranch        *b_dRTkMu1;   //!
    TBranch        *b_CSCRg2;   //!
    TBranch        *b_CSCCh2;   //!
    TBranch        *b_CSCCBad2;   //!
    TBranch        *b_CSCDyProjHVGap2;   //!
    TBranch        *b_CSCDyErrProjHVGap2;   //!
    TBranch        *b_CSCProjDistEdge2;   //!
    TBranch        *b_CSCProjDistErrEdge2;   //!
    TBranch        *b_CSCTTxLc2;   //!
    TBranch        *b_CSCTTwLc2;   //!
    TBranch        *b_CSCTTyLc2;   //!
    TBranch        *b_CSCTTsLc2;   //!
    TBranch        *b_CSCTTwSegxLc2;   //!
    TBranch        *b_CSCTTwSegyLc2;   //!
    TBranch        *b_CSCTT3xLc2;   //!
    TBranch        *b_CSCTT3wLc2;   //!
    TBranch        *b_CSCTT3yLc2;   //!
    TBranch        *b_CSCTT3sLc2;   //!
    TBranch        *b_CSCTT3wLCTxLc2;   //!
    TBranch        *b_CSCTT3wLCTyLc2;   //!
    TBranch        *b_CSCTTxGc2;   //!
    TBranch        *b_CSCTTyGc2;   //!
    TBranch        *b_CSCTTzGc2;   //!
    TBranch        *b_CSCTTetaGc2;   //!
    TBranch        *b_CSCTT3xGc2;   //!
    TBranch        *b_CSCTT3yGc2;   //!
    TBranch        *b_CSCTT3zGc2;   //!
    TBranch        *b_CSCTT3etaGc2;   //!
    TBranch        *b_CSCSegNumber2;   //!
    TBranch        *b_DTSegNumber2;   //!
    TBranch        *b_RPCSegNumber2;   //!
    TBranch        *b_CSCSegxLc2;   //!
    TBranch        *b_CSCSegyLc2;   //!
    TBranch        *b_CSCSegxErrLc2;   //!
    TBranch        *b_CSCSegyErrLc2;   //!
    TBranch        *b_CSCdXdZTTSeg2;   //!
    TBranch        *b_CSCdYdZTTSeg2;   //!
    TBranch        *b_CSCSegChisqProb2;   //!
    TBranch        *b_CSCnSegHits2;   //!
    TBranch        *b_CSCDxTTSeg2;   //!
    TBranch        *b_CSCDxErrTTSeg2;   //!
    TBranch        *b_CSCDyTTSeg2;   //!
    TBranch        *b_CSCDyErrTTSeg2;   //!
    TBranch        *b_CSCDxyTTSeg2;   //!
    TBranch        *b_CSCDxyErrTTSeg2;   //!
    TBranch        *b_CSCLCTxLc2;   //!
    TBranch        *b_CSCLCTyLc2;   //!
    TBranch        *b_CSCLCTbx2;   //!
    TBranch        *b_N_seg_inChamber2;   //!
    TBranch        *b_CSCDxTTLCT2;   //!
    TBranch        *b_CSCDxErrTTLCT2;   //!
    TBranch        *b_CSCDyTTLCT2;   //!
    TBranch        *b_CSCDyErrTTLCT2;   //!
    TBranch        *b_CSCDxyTTLCT2;   //!
    TBranch        *b_CSCDxyErrTTLCT2;   //!
    TBranch        *b_dRTkMu2;   //!
    TBranch        *b_CSCRg3;   //!
    TBranch        *b_CSCCh3;   //!
    TBranch        *b_CSCCBad3;   //!
    TBranch        *b_CSCDyProjHVGap3;   //!
    TBranch        *b_CSCDyErrProjHVGap3;   //!
    TBranch        *b_CSCProjDistEdge3;   //!
    TBranch        *b_CSCProjDistErrEdge3;   //!
    TBranch        *b_CSCTTxLc3;   //!
    TBranch        *b_CSCTTwLc3;   //!
    TBranch        *b_CSCTTyLc3;   //!
    TBranch        *b_CSCTTsLc3;   //!
    TBranch        *b_CSCTTwSegxLc3;   //!
    TBranch        *b_CSCTTwSegyLc3;   //!
    TBranch        *b_CSCTT3xLc3;   //!
    TBranch        *b_CSCTT3wLc3;   //!
    TBranch        *b_CSCTT3yLc3;   //!
    TBranch        *b_CSCTT3sLc3;   //!
    TBranch        *b_CSCTT3wLCTxLc3;   //!
    TBranch        *b_CSCTT3wLCTyLc3;   //!
    TBranch        *b_CSCTTxGc3;   //!
    TBranch        *b_CSCTTyGc3;   //!
    TBranch        *b_CSCTTzGc3;   //!
    TBranch        *b_CSCTTetaGc3;   //!
    TBranch        *b_CSCTT3xGc3;   //!
    TBranch        *b_CSCTT3yGc3;   //!
    TBranch        *b_CSCTT3zGc3;   //!
    TBranch        *b_CSCTT3etaGc3;   //!
    TBranch        *b_CSCSegNumber3;   //!
    TBranch        *b_DTSegNumber3;   //!
    TBranch        *b_RPCSegNumber3;   //!
    TBranch        *b_CSCSegxLc3;   //!
    TBranch        *b_CSCSegyLc3;   //!
    TBranch        *b_CSCSegxErrLc3;   //!
    TBranch        *b_CSCSegyErrLc3;   //!
    TBranch        *b_CSCdXdZTTSeg3;   //!
    TBranch        *b_CSCdYdZTTSeg3;   //!
    TBranch        *b_CSCSegChisqProb3;   //!
    TBranch        *b_CSCnSegHits3;   //!
    TBranch        *b_CSCDxTTSeg3;   //!
    TBranch        *b_CSCDxErrTTSeg3;   //!
    TBranch        *b_CSCDyTTSeg3;   //!
    TBranch        *b_CSCDyErrTTSeg3;   //!
    TBranch        *b_CSCDxyTTSeg3;   //!
    TBranch        *b_CSCDxyErrTTSeg3;   //!
    TBranch        *b_CSCLCTxLc3;   //!
    TBranch        *b_CSCLCTyLc3;   //!
    TBranch        *b_CSCLCTbx3;   //!
    TBranch        *b_N_seg_inChamber3;   //!
    TBranch        *b_CSCDxTTLCT3;   //!
    TBranch        *b_CSCDxErrTTLCT3;   //!
    TBranch        *b_CSCDyTTLCT3;   //!
    TBranch        *b_CSCDyErrTTLCT3;   //!
    TBranch        *b_CSCDxyTTLCT3;   //!
    TBranch        *b_CSCDxyErrTTLCT3;   //!
    TBranch        *b_dRTkMu3;   //!
    TBranch        *b_CSCRg4;   //!
    TBranch        *b_CSCCh4;   //!
    TBranch        *b_CSCCBad4;   //!
    TBranch        *b_CSCDyProjHVGap4;   //!
    TBranch        *b_CSCDyErrProjHVGap4;   //!
    TBranch        *b_CSCProjDistEdge4;   //!
    TBranch        *b_CSCProjDistErrEdge4;   //!
    TBranch        *b_CSCTTxLc4;   //!
    TBranch        *b_CSCTTwLc4;   //!
    TBranch        *b_CSCTTyLc4;   //!
    TBranch        *b_CSCTTsLc4;   //!
    TBranch        *b_CSCTTwSegxLc4;   //!
    TBranch        *b_CSCTTwSegyLc4;   //!
    TBranch        *b_CSCTT3xLc4;   //!
    TBranch        *b_CSCTT3wLc4;   //!
    TBranch        *b_CSCTT3yLc4;   //!
    TBranch        *b_CSCTT3sLc4;   //!
    TBranch        *b_CSCTT3wLCTxLc4;   //!
    TBranch        *b_CSCTT3wLCTyLc4;   //!
    TBranch        *b_CSCTTxGc4;   //!
    TBranch        *b_CSCTTyGc4;   //!
    TBranch        *b_CSCTTzGc4;   //!
    TBranch        *b_CSCTTetaGc4;   //!
    TBranch        *b_CSCTT3xGc4;   //!
    TBranch        *b_CSCTT3yGc4;   //!
    TBranch        *b_CSCTT3zGc4;   //!
    TBranch        *b_CSCTT3etaGc4;   //!
    TBranch        *b_CSCSegNumber4;   //!
    TBranch        *b_DTSegNumber4;   //!
    TBranch        *b_RPCSegNumber4;   //!
    TBranch        *b_CSCSegxLc4;   //!
    TBranch        *b_CSCSegyLc4;   //!
    TBranch        *b_CSCSegxErrLc4;   //!
    TBranch        *b_CSCSegyErrLc4;   //!
    TBranch        *b_CSCdXdZTTSeg4;   //!
    TBranch        *b_CSCdYdZTTSeg4;   //!
    TBranch        *b_CSCSegChisqProb4;   //!
    TBranch        *b_CSCnSegHits4;   //!
    TBranch        *b_CSCDxTTSeg4;   //!
    TBranch        *b_CSCDxErrTTSeg4;   //!
    TBranch        *b_CSCDyTTSeg4;   //!
    TBranch        *b_CSCDyErrTTSeg4;   //!
    TBranch        *b_CSCDxyTTSeg4;   //!
    TBranch        *b_CSCDxyErrTTSeg4;   //!
    TBranch        *b_CSCLCTxLc4;   //!
    TBranch        *b_CSCLCTyLc4;   //!
    TBranch        *b_CSCLCTbx4;   //!
    TBranch        *b_N_seg_inChamber4;   //!
    TBranch        *b_CSCDxTTLCT4;   //!
    TBranch        *b_CSCDxErrTTLCT4;   //!
    TBranch        *b_CSCDyTTLCT4;   //!
    TBranch        *b_CSCDyErrTTLCT4;   //!
    TBranch        *b_CSCDxyTTLCT4;   //!
    TBranch        *b_CSCDxyErrTTLCT4;   //!
    TBranch        *b_dRTkMu4;   //!
    TBranch        *b_HLTMuAcceptance;   //!
    TBranch        *b_HLTDiMuAcceptance;   //!
    TBranch        *b_minDRHLTMu;   //!
    TBranch        *b_minDRHLTDiMu;   //!
    TBranch        *b_minDRHLTAllSingleMu;   //!


    CSCEffFast();
    virtual ~CSCEffFast();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef CSCEffFast_cxx
CSCEffFast::CSCEffFast() : fChain(0)
{
  Int_t numberFiles = 0;
  TChain *chain = new TChain("aodDump/Fraction");

  //std::cout << "Analyzing " << (newData? "2023 or 2024" : "2022") << " data." << std::endl;
  std::string name = "";
  std::cout << "Analyzing ";
  if (firstSet.firstRun <= firstRun && lastSet.lastRun >= lastRun){
    TString first(firstSet.id), last(lastSet.id), period = first(0,first.First('v'));
    char v1 = first[first.Length()-1], v2 = last[last.Length()-1];
    if (last.BeginsWith(period)){
      if (v1==v2) name = first;
      else name = period + "v" + v1 + "-" + v2;
    }
    else name = first + "-" + last;
    std::cout << name << " data." << std::endl;
  }
  else std::cout << "runs " << firstRun << "-" << lastRun << "." << std::endl;
  setName = new TNamed("setName", name.c_str());
  setRuns = new TNamed("setRuns", TString::Format("%i %i", firstRun, lastRun).Data());

  if (newData){


    //        chain->Add("/afs/hep.wisc.edu/home/herndon/software/cscEffRun3_2023/CMSSW_13_0_3/src/CSCEfficiency/CSCEfficiency/test_2023_7.root");
    //     numberFiles++;

    // 2023B
    // for (int fileNum=0;fileNum < 260;fileNum++) {
    //   if ((!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023B0_2023_0426_11/230508_133443/0000/CSCeff_Muon_2023B0_%d.root",fileNum)))&&fileNum!=88) {
    //    chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023B0_2023_0426_11/230508_133443/0000/CSCeff_Muon_2023B0_%d.root",fileNum));
    //    numberFiles++;
    //  }
    // }

    // for (int fileNum=0;fileNum < 260;fileNum++) {
    //  if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023B1_20231_0426_11/230508_134923/0000/CSCeff_Muon_2023B1_%d.root",fileNum))) {
    //    chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023B1_20231_0426_11/230508_134923/0000/CSCeff_Muon_2023B1_%d.root",fileNum));
    //    numberFiles++;
    //  }
    // }

    // for (int fileNum=0;fileNum < 40;fileNum++) {
    //   if ((!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023B0_2023_0426_12/230512_142707/0000/CSCeff_Muon_2023B0_%d.root",fileNum)))&&fileNum!=88) {
    //    chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023B0_2023_0426_12/230512_142707/0000/CSCeff_Muon_2023B0_%d.root",fileNum));
    //    numberFiles++;
    //  }
    // }

    // for (int fileNum=0;fileNum < 40;fileNum++) {
    //  if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023B1_20231_0426_12/230512_142748/0000/CSCeff_Muon_2023B1_%d.root",fileNum))) {
    //    chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023B1_20231_0426_12/230512_142748/0000/CSCeff_Muon_2023B1_%d.root",fileNum));
    //    numberFiles++;
    //  }
    // }

    // 2023C old
    // for (int fileNum=0;fileNum < 380;fileNum++) {
    //   if ((!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023C0_2023_0512_1/230513_012701/0000/CSCeff_Muon_2023C0_%d.root",fileNum)))&&fileNum!=88) {
    // 	chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023C0_2023_0512_1/230513_012701/0000/CSCeff_Muon_2023C0_%d.root",fileNum));
    // 	numberFiles++;
    //   }
    // }

    // for (int fileNum=0;fileNum < 380;fileNum++) {
    //   if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023C1_2023_0512_1/230513_012833/0000/CSCeff_Muon_2023C1_%d.root",fileNum))) {
    // 	chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023C1_2023_0512_1/230513_012833/0000/CSCeff_Muon_2023C1_%d.root",fileNum));
    // 	numberFiles++;
    //   }
    // }

    // 2024B, this data is pretty much all bad
    // if (firstRun <= d2024Bv1.lastRun && d2024Bv1.firstRun <= lastRun){
    //   for (int fileNum=0; fileNum<140; fileNum++){//Muon0
    //     if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024B0_1_240417_8/240417_104015/0000/CSCeff_Muon_2024B_1_%d.root",fileNum))){
    //       chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024B0_1_240417_8/240417_104015/0000/CSCeff_Muon_2024B_1_%d.root",fileNum));
    //       numberFiles++;
    //     }
    //   }
    //   for (int fileNum=0; fileNum<140; fileNum++){//Muon1
    //     if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024B1_1_240415_8/240417_104156/0000/CSCeff_Muon_2024B_1_%d.root",fileNum))){
    //       chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024B1_1_240415_8/240417_104156/0000/CSCeff_Muon_2024B_1_%d.root",fileNum));
    //       numberFiles++;
    //     }
    //   }
    // }

    // 2025B v1
    if (firstRun <= d2025Bv1.lastRun && d2025Bv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon0/CSCEff2025B0v1/250521_171915/0000/CSCEff2025B0v1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon0/CSCEff2025B0v1/250521_171915/0000/CSCEff2025B0v1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon1/CSCEff2025B1v1/250521_190332/0000/CSCEff2025B1v1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon1/CSCEff2025B1v1/250521_190332/0000/CSCEff2025B1v1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2025C v1
    if (firstRun <= d2025Cv1.lastRun && d2025Cv1.firstRun <= lastRun){

      // Repladced older files with full 202C processing
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0000/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0000/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0001/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0001/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0002/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0002/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0003/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_1_250521_15/250623_224153/0003/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0000/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0000/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0001/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0001/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
     for (int fileNum=2000; fileNum<3000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0002/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0002/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0003/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_1_250521_15/250623_224249/0003/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2025C v2
    if (firstRun <= d2025Cv2.lastRun && d2025Cv2.firstRun <= lastRun){

      // Repladced older files with full 202C processing
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_2_250707_2/250707_195128/0000/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_2_250707_2/250707_195128/0000/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_2_250707_2/250707_195128/0001/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_2_250707_2/250707_195128/0001/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_2_250707_2/250707_195128/0002/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2025C0_2_250707_2/250707_195128/0002/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_2_250707_2/250707_195405/0000/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_2_250707_2/250707_195405/0000/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_2_250707_2/250707_195405/0001/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_2_250707_2/250707_195405/0001/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_2_250707_2/250707_195405/0002/CSCeff_Muon_2025C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2025C1_2_250707_2/250707_195405/0002/CSCeff_Muon_2025C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2025D v1
    if (firstRun <= d2025Dv1.lastRun && d2025Dv1.firstRun <= lastRun){
      numberFiles += chain->Add("/hdfs/store/user/marquez/Muon0/CSCEff2025D0v1/250819_163115/*/*.root");
      numberFiles += chain->Add("/hdfs/store/user/marquez/Muon1/CSCEff2025D1v1/250819_163143/*/*.root");
    }

    // 2025E v1
    if (firstRun <= d2025Ev1.lastRun && d2025Ev1.firstRun <= lastRun){
      numberFiles += chain->Add("/hdfs/store/user/marquez/Muon0/CSCEff2025E0v1/250909_161359/*/*.root");
      numberFiles += chain->Add("/hdfs/store/user/marquez/Muon1/CSCEff2025E1v1/250909_161425/*/*.root");
    }
    
    // 2024C v1
    if (firstRun <= d2024Cv1.lastRun && d2024Cv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024C0_1_240430_11/240430_151603/0000/CSCeff_Muon_2024C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024C0_1_240430_11/240430_151603/0000/CSCeff_Muon_2024C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024C1_1_240430_11/240430_151643/0000/CSCeff_Muon_2024C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024C1_1_240430_11/240430_151643/0000/CSCeff_Muon_2024C_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024C0_1_240430_11/240430_151603/0001/CSCeff_Muon_2024C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024C0_1_240430_11/240430_151603/0001/CSCeff_Muon_2024C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024C1_1_240430_11/240430_151643/0001/CSCeff_Muon_2024C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024C1_1_240430_11/240430_151643/0001/CSCeff_Muon_2024C_1_%d.root",fileNum));
          numberFiles++;
        }
      }


      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024C0_1_240430_12/240516_010259/0000/CSCeff_Muon_2024C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024C0_1_240430_12/240516_010259/0000/CSCeff_Muon_2024C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024C1_1_240430_12/240516_010858/0000/CSCeff_Muon_2024C_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024C1_1_240430_12/240516_010858/0000/CSCeff_Muon_2024C_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2024D v1
    if (firstRun <= d2024Dv1.lastRun && d2024Dv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_2/240518_021852/0000/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_2/240518_021852/0000/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_2/240518_021852/0001/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_2/240518_021852/0001/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_2/240518_021852/0002/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_2/240518_021852/0002/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_2/240518_021945/0000/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_2/240518_021945/0000/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_2/240518_021945/0001/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_2/240518_021945/0001/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_2/240518_021945/0002/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_2/240518_021945/0002/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<200; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_3/240525_190406/0000/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024D0_1_240517_3/240525_190406/0000/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<200; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_3/240525_190504/0000/CSCeff_Muon_2024D_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024D1_1_240517_3/240525_190504/0000/CSCeff_Muon_2024D_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2024E v1
    if (firstRun <= d2024Ev1.lastRun && d2024Ev1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_1_240525_2/240621_201455/0000/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_1_240525_2/240621_201455/0000/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_1_240525_2/240621_201455/0001/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_1_240525_2/240621_201455/0001/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<2230; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_1_240525_2/240621_201455/0002/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_1_240525_2/240621_201455/0002/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }


      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_1_240525_2/240621_201605/0000/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_1_240525_2/240621_201605/0000/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_1_240525_2/240621_201605/0001/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_1_240525_2/240621_201605/0001/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<2231; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_1_240525_2/240621_201605/0002/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_1_240525_2/240621_201605/0002/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2024E v2
    if (firstRun <= d2024Ev2.lastRun && d2024Ev2.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_2_240525_3/240621_203546/0000/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_2_240525_3/240621_203546/0000/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<1640; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_2_240525_3/240621_203546/0001/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024E0_2_240525_3/240621_203546/0001/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_2_240525_4/240621_203641/0000/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_2_240525_4/240621_203641/0000/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<1643; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_2_240525_4/240621_203641/0001/CSCeff_Muon_2024E_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024E1_2_240525_4/240621_203641/0001/CSCeff_Muon_2024E_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2024F v1
    if (firstRun <= d2024Fv1.lastRun && d2024Fv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0000/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0000/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0001/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0001/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0002/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0002/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0003/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0003/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0004/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0004/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0005/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0005/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=6000; fileNum<7000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0006/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_3/240725_164959/0006/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0000/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0000/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0001/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0001/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0002/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0002/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0003/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0003/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0004/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0004/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0005/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0005/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=6000; fileNum<7000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0006/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_3/240725_165100/0006/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2024F v1
    if (firstRun <= d2024Fv1.lastRun && d2024Fv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0000/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0000/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0001/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0001/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0002/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0002/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0003/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0003/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0004/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0004/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0005/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0005/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=6000; fileNum<6150; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0006/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024F0_1_240621_6/240803_172637/0006/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }


      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0000/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0000/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0001/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0001/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0002/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0002/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0003/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0003/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0004/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0004/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0005/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0005/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=6000; fileNum<6150; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0006/CSCeff_Muon_2024F_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024F1_1_240621_6/240803_172748/0006/CSCeff_Muon_2024F_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2024G v1
    if (firstRun <= d2024Gv1.lastRun && d2024Gv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0000/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0000/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0001/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0001/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0002/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0002/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0003/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0003/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0004/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0004/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0005/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0005/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=6000; fileNum<7000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0006/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_1_240827_1/240827_204329/0006/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }


      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0000/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0000/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0001/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0001/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0002/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0002/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0003/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0003/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0004/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0004/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0005/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0005/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=6000; fileNum<7000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0006/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_1_240827_1/240827_205810/0006/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }


      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0000/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0000/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0001/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0001/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0002/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0002/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0003/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0003/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0004/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0004/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0005/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0005/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=6000; fileNum<7000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0006/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0006/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=7000; fileNum<8000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0007/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024G0_2_240928_1/240928_081802/0007/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }



      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0000/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0000/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0001/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0001/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<3000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0002/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0002/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=3000; fileNum<4000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0003/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0003/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=4000; fileNum<5000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0004/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0004/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=5000; fileNum<6000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0005/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0005/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=6000; fileNum<7000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0006/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0006/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=7000; fileNum<8000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0007/CSCeff_Muon_2024G_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024G1_2_240928_1/240928_081942/0007/CSCeff_Muon_2024G_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2024G v1r
    if (firstRun <= d2024Gv1r.lastRun && d2024Gv1r.firstRun <= lastRun){

    }

    // 2024H v1
    if (firstRun <= d2024Hv1.lastRun && d2024Hv1.firstRun <= lastRun){
       for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
          if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024H0_1_241007_1/241008_151510/0000/CSCeff_Muon_2024H_1_%d.root",fileNum))){
            chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024H0_1_241007_1/241008_151510/0000/CSCeff_Muon_2024H_1_%d.root",fileNum));
            numberFiles++;
          }
       }
       for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
          if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024H1_1_241007_1/241008_151848/0000/CSCeff_Muon_2024H_1_%d.root",fileNum))){
            chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024H1_1_241007_1/241008_151848/0000/CSCeff_Muon_2024H_1_%d.root",fileNum));
            numberFiles++;
          }
       }
       for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
          if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024H1_1_241007_1/241008_151848/0001/CSCeff_Muon_2024H_1_%d.root",fileNum))){
            chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024H1_1_241007_1/241008_151848/0001/CSCeff_Muon_2024H_1_%d.root",fileNum));
            numberFiles++;
          }
       }
       for (int fileNum=2000; fileNum<2104; fileNum++){//Muon1
          if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024H1_1_241007_1/241008_151848/0002/CSCeff_Muon_2024H_1_%d.root",fileNum))){
            chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024H1_1_241007_1/241008_151848/0002/CSCeff_Muon_2024H_1_%d.root",fileNum));
            numberFiles++;
          }
       }
    }

    // 2024I v1
    if (firstRun <= d2024Iv1.lastRun && d2024Iv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_1_241007_1/241009_145815/0000/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_1_241007_1/241009_145815/0000/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<1300; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_1_241007_1/241009_145815/0001/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_1_241007_1/241009_145815/0001/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_1_241007_1/241009_151524/0000/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_1_241007_1/241009_151524/0000/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<1320; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_1_241007_1/241009_151524/0001/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_1_241007_1/241009_151524/0001/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      // Rest of period I v1

      for (int fileNum=0; fileNum<810; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_1_241007_2/241202_180723/0000/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_1_241007_2/241202_180723/0000/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<810; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_1_241007_2/241202_182117/0000/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_1_241007_2/241202_182117/0000/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }

    }

    // 2024I v2
    if (firstRun <= d2024Iv2.lastRun && d2024Iv2.firstRun <= lastRun){
      for (int fileNum=0; fileNum<1000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_2_241202_1/241202_192229/0000/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_2_241202_1/241202_192229/0000/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_2_241202_1/241202_192229/0001/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_2_241202_1/241202_192229/0001/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=2000; fileNum<2210; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_2_241202_1/241202_192229/0002/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2024I0_2_241202_1/241202_192229/0002/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=0; fileNum<1000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_2_241202_1/241202_192337/0000/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_2_241202_1/241202_192337/0000/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=1000; fileNum<2000; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_2_241202_1/241202_192337/0001/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_2_241202_1/241202_192337/0001/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }

      for (int fileNum=2000; fileNum<2232; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_2_241202_1/241202_192337/0002/CSCeff_Muon_2024I_1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2024I1_2_241202_1/241202_192337/0002/CSCeff_Muon_2024I_1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2023D v2
    if (firstRun <= d2023Dv2.lastRun && d2023Dv2.firstRun <= lastRun){
      for (int fileNum=0; fileNum<295; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon0/CSCEff2023D0_2023_0721_1/230721_162538/0000/CSCeff_Muon_2023D0v2_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon0/CSCEff2023D0_2023_0721_1/230721_162538/0000/CSCeff_Muon_2023D0v2_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<700; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon1/CSCEff2023D1_2023_0721_1/230721_162644/0000/CSCeff_Muon_2023D1v2_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon1/CSCEff2023D1_2023_0721_1/230721_162644/0000/CSCeff_Muon_2023D1v2_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2023D v1
    if (firstRun <= d2023Dv1.lastRun && d2023Dv1.firstRun <= lastRun){
      for (int fileNum=0; fileNum<709; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023D0_2023_0712_1/230713_023111/0000/CSCeff_Muon_2023D0v1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023D0_2023_0712_1/230713_023111/0000/CSCeff_Muon_2023D0v1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<653; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023D0_2023_0712_2/230720_135219/0000/CSCeff_Muon_2023D0v1_%d.root", fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023D0_2023_0712_2/230720_135219/0000/CSCeff_Muon_2023D0v1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<700; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023D1_2023_0712_1/230713_021426/0000/CSCeff_Muon_2023D1v1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023D1_2023_0712_1/230713_021426/0000/CSCeff_Muon_2023D1v1_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<656; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023D1_2023_0712_2/230720_135524/0000/CSCeff_Muon_2023D1v1_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023D1_2023_0712_2/230720_135524/0000/CSCeff_Muon_2023D1v1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2023C v4
    if (firstRun <= d2023Cv4.lastRun && d2023Cv4.firstRun <= lastRun){
      for (int fileNum=0; fileNum<999; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon0/CSCEff2023C0_2023_0628_2/230728_025317/0000/CSCeff_Muon_2023C0v4_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon0/CSCEff2023C0_2023_0628_2/230728_025317/0000/CSCeff_Muon_2023C0v4_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<1936; fileNum++){//Muon0
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon0/CSCEff2023C0_2023_0628_2/230728_025317/0001/CSCeff_Muon_2023C0v4_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon0/CSCEff2023C0_2023_0628_2/230728_025317/0001/CSCeff_Muon_2023C0v4_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0; fileNum<999; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon1/CSCEff2023C1_2023_0628_1/230629_140919/0000/CSCeff_Muon_2023C1v4_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon1/CSCEff2023C1_2023_0628_1/230629_140919/0000/CSCeff_Muon_2023C1v4_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=1000; fileNum<1939; fileNum++){//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/marquez/Muon1/CSCEff2023C1_2023_0628_1/230629_140919/0001/CSCeff_Muon_2023C1v4_%d.root",fileNum))){
          chain->Add(Form("/hdfs/store/user/marquez/Muon1/CSCEff2023C1_2023_0628_1/230629_140919/0001/CSCeff_Muon_2023C1v4_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2023C v2 (new)
    if (firstRun <= d2023Cv2.lastRun && d2023Cv2.firstRun <= lastRun){
      for (int fileNum=0;fileNum < 725;fileNum++) {//Muon0
        if ((!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023C0_2023_0512_2/230522_170454/0000/CSCeff_Muon_2023C0_%d.root",fileNum)))&&fileNum!=88) {
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023C0_2023_0512_2/230522_170454/0000/CSCeff_Muon_2023C0_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0;fileNum < 725;fileNum++) {//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023C1_2023_0512_2/230522_170711/0000/CSCeff_Muon_2023C1_%d.root",fileNum))) {
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023C1_2023_0512_2/230522_170711/0000/CSCeff_Muon_2023C1_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

    // 2023C v1 (new)
    if (firstRun <= d2023Cv1.lastRun && d2023Cv1.firstRun <= lastRun){
      for (int fileNum=0;fileNum < 460;fileNum++) {//Muon0
        if ((!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023C0_2023_0512_3/230522_230520/0000/CSCeff_Muon_2023C0v2_%d.root",fileNum)))&&fileNum!=88){
          chain->Add(Form("/hdfs/store/user/herndon/Muon0/CSCEff2023C0_2023_0512_3/230522_230520/0000/CSCeff_Muon_2023C0v2_%d.root",fileNum));
          numberFiles++;
        }
      }
      for (int fileNum=0;fileNum < 460;fileNum++) {//Muon1
        if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023C1_2023_0512_3/230522_232605/0000/CSCeff_Muon_2023C1v2_%d.root",fileNum))) {
          chain->Add(Form("/hdfs/store/user/herndon/Muon1/CSCEff2023C1_2023_0512_3/230522_232605/0000/CSCeff_Muon_2023C1v2_%d.root",fileNum));
          numberFiles++;
        }
      }
    }

  } else {

    // 2022G
    for (int fileNum=0;fileNum < 1000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022G2_2023_0221_01/230222_040427/0000/CSCeff_SingleMuon_2022G2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022G2_2023_0221_01/230222_040427/0000/CSCeff_SingleMuon_2022G2_%d.root",fileNum));
        numberFiles++;
      }
    }


    for (int fileNum=1000;fileNum < 1225;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022G2_2023_0221_01/230222_040427/0001/CSCeff_SingleMuon_2022G2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022G2_2023_0221_01/230222_040427/0001/CSCeff_SingleMuon_2022G2_%d.root",fileNum));
        numberFiles++;
      }
    }


    // 2022F
    for (int fileNum=0;fileNum < 1000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0000/CSCeff_SingleMuon_2022F2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0000/CSCeff_SingleMuon_2022F2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=1000;fileNum < 2000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0001/CSCeff_SingleMuon_2022F2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0001/CSCeff_SingleMuon_2022F2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=2000;fileNum < 3000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0002/CSCeff_SingleMuon_2022F2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0002/CSCeff_SingleMuon_2022F2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=3000;fileNum < 4000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0003/CSCeff_SingleMuon_2022F2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0003/CSCeff_SingleMuon_2022F2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=4000;fileNum < 5000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0004/CSCeff_SingleMuon_2022F2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0004/CSCeff_SingleMuon_2022F2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=5000;fileNum < 6000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0005/CSCeff_SingleMuon_2022F2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0005/CSCeff_SingleMuon_2022F2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=6000;fileNum < 6603;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0006/CSCeff_SingleMuon_2022F2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022F2_2022_1026_03/221122_231823/0006/CSCeff_SingleMuon_2022F2_%d.root",fileNum));
        numberFiles++;
      }
    }






    // 2022E
    for (int fileNum=0;fileNum < 1000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_32/221012_134114/0000/CSCeff_SingleMuon_2022E2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_32/221012_134114/0000/CSCeff_SingleMuon_2022E2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=1000;fileNum < 2000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_32/221012_134114/0001/CSCeff_SingleMuon_2022E2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_32/221012_134114/0001/CSCeff_SingleMuon_2022E2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=2000;fileNum < 2204;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_32/221012_134114/0002/CSCeff_SingleMuon_2022E2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_32/221012_134114/0002/CSCeff_SingleMuon_2022E2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=0;fileNum < 1000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_34/221025_210323/0000/CSCeff_SingleMuon_2022E2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_34/221025_210323/0000/CSCeff_SingleMuon_2022E2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=1000;fileNum < 1614;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_34/221025_210323/0001/CSCeff_SingleMuon_2022E2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022E2_2022_1004_34/221025_210323/0001/CSCeff_SingleMuon_2022E2_%d.root",fileNum));
        numberFiles++;
      }
    }

    // 2022B-D

    for (int fileNum=0;fileNum < 200;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/SingleMuon/CSCEff2022B_20220725_9/220725_221302/0000/CSCeff_SingleMuon_2022B_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/SingleMuon/CSCEff2022B_20220725_9/220725_221302/0000/CSCeff_SingleMuon_2022B_%d.root",fileNum));
        numberFiles++;
      }
    }
    for (int fileNum=0;fileNum < 800;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/SingleMuon/CSCEff2022C_20220809_8/220809_153259/0000/CSCeff_SingleMuon_2022C_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/SingleMuon/CSCEff2022C_20220809_8/220809_153259/0000/CSCeff_SingleMuon_2022C_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=0;fileNum < 1000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022C2_20220824_21/220824_152209/0000/CSCeff_SingleMuon_2022C2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022C2_20220824_21/220824_152209/0000/CSCeff_SingleMuon_2022C2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=1000;fileNum < 2000;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022C2_20220824_21/220824_152209/0001/CSCeff_SingleMuon_2022C2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022C2_20220824_21/220824_152209/0001/CSCeff_SingleMuon_2022C2_%d.root",fileNum));
        numberFiles++;
      }
    }

    for (int fileNum=0;fileNum < 355;fileNum++) {
      if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/Muon/CSCEff2022D2_20220824_20/220824_161937/0000/CSCeff_SingleMuon_2022D2_%d.root",fileNum))) {
        chain->Add(Form("/hdfs/store/user/herndon/Muon/CSCEff2022D2_20220824_20/220824_161937/0000/CSCeff_SingleMuon_2022D2_%d.root",fileNum));
        numberFiles++;
      }
    }

  }

  //if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/DYToLL_M-50_TuneCP5_14TeV-pythia8/CSCEffRun3MC2_20220519_2/220519_175853/0001/CSCEff_Zmm_MC_Run3_1__%d.root",fileNum))) {
  // chain->Add(Form("/hdfs/store/user/herndon/DYToLL_M-50_TuneCP5_14TeV-pythia8/CSCEffRun3MC2_20220519_2/220519_175853/0001/CSCEff_Zmm_MC_Run3_1__%d.root",fileNum));
  //    numberFiles++;
  //  }

  //  if (!gSystem->AccessPathName(Form("/hdfs/store/user/herndon/DYToLL_M-50_TuneCP5_14TeV-pythia8/CSCEffRun3MC2_20220519_2/220519_175853/0002/CSCEff_Zmm_MC_Run3_1__%d.root",fileNum))) {
  //    chain->Add(Form("/hdfs/store/user/herndon/DYToLL_M-50_TuneCP5_14TeV-pythia8/CSCEffRun3MC2_20220519_2/220519_175853/0002/CSCEff_Zmm_MC_Run3_1__%d.root",fileNum));
  //    numberFiles++;
  //  }





  std::cout << "Number Files: " << numberFiles << std::endl;


  Init(chain);
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  /* if (tree == 0) { */
  /*    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/cms/herndon/cscEff/test.root"); */
  /*    if (!f || !f->IsOpen()) { */
  /*       f = new TFile("/cms/herndon/cscEff/test.root"); */
  /*    } */
  /*    TDirectory * dir = (TDirectory*)f->Get("/cms/herndon/cscEff/test.root:/aodDump"); */
  /*    dir->GetObject("Fraction",tree); */

  /* } */
  /* Init(tree); */
  Loop();
}


CSCEffFast::~CSCEffFast()
{
  if (fChain) delete fChain->GetCurrentFile();
  delete setName;
  delete setRuns;
  if (setRunsTrue) delete setRunsTrue;
}

Int_t CSCEffFast::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t CSCEffFast::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void CSCEffFast::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  LumiInst = 0;
  LumiInstErr = 0;
  LumiInstQlty = 0;
  LumiEtInst = 0;
  LumiEtInstErr = 0;
  LumiEtInstQlty = 0;
  LumiStartOrbit = 0;
  LumiNumOrbits = 0;
  HLTMuAcceptance = 0;
  minDRHLTMu = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);


  fChain->SetBranchAddress("run_number", &run_number, &b_run_number);
  fChain->SetBranchAddress("event_number", &event_number, &b_event_number);
  fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
  fChain->SetBranchAddress("LumiSection", &LumiSection, &b_LumiSection);
  fChain->SetBranchAddress("LumiInst", &LumiInst, &b_LumiInst);
  fChain->SetBranchAddress("LumiInstErr", &LumiInstErr, &b_LumiInstErr);
  fChain->SetBranchAddress("LumiInstQlty", &LumiInstQlty, &b_LumiInstQlty);
  fChain->SetBranchAddress("LumiEtInst", &LumiEtInst, &b_LumiEtInst);
  fChain->SetBranchAddress("LumiEtInstErr", &LumiEtInstErr, &b_LumiEtInstErr);
  fChain->SetBranchAddress("LumiEtInstQlty", &LumiEtInstQlty, &b_LumiEtInstQlty);
  fChain->SetBranchAddress("LumiStartOrbit", &LumiStartOrbit, &b_LumiStartOrbit);
  fChain->SetBranchAddress("LumiNumOrbits", &LumiNumOrbits, &b_LumiNumOrbits);
  fChain->SetBranchAddress("bunchX", &bunchX, &b_bunchX);
  fChain->SetBranchAddress("orbitNumb", &orbitNumb, &b_orbitNumb);
  fChain->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
  fChain->SetBranchAddress("numberOfPUVertices", &numberOfPUVertices, &b_numberOfPUVertices);
  fChain->SetBranchAddress("numberOfPUVerticesMixingTruth", &numberOfPUVerticesMixingTruth, &b_numberOfPUVerticesMixingTruth);
  fChain->SetBranchAddress("numberOfPUVerticesTot", &numberOfPUVerticesTot, &b_numberOfPUVerticesTot);
  fChain->SetBranchAddress("numberOfPrimaryVertices", &numberOfPrimaryVertices, &b_numberOfPrimaryVertices);
  fChain->SetBranchAddress("trgSingle", &trgSingle, &b_trgSingle);
  fChain->SetBranchAddress("nTrkCountCSCSeg", &nTrkCountCSCSeg, &b_nTrkCountCSCSeg);
  fChain->SetBranchAddress("nTotalTrks", &nTotalTrks, &b_nTotalTrks);
  fChain->SetBranchAddress("trackVeto_strict", &trackVeto_strict, &b_trackVeto_strict);
  fChain->SetBranchAddress("trackVeto_isClosestToLCT", &trackVeto_isClosestToLCT, &b_trackVeto_isClosestToLCT);
  fChain->SetBranchAddress("myRegion", &myRegion, &b_myRegion);
  fChain->SetBranchAddress("MuTagPt", &MuTagPt, &b_MuTagPt);
  fChain->SetBranchAddress("MuTagEta", &MuTagEta, &b_MuTagEta);
  fChain->SetBranchAddress("MuTagPhi", &MuTagPhi, &b_MuTagPhi);
  fChain->SetBranchAddress("MuTagIsoR03Ratio", &MuTagIsoR03Ratio, &b_MuTagIsoR03Ratio);
  fChain->SetBranchAddress("MuTagIsoR05Ratio", &MuTagIsoR05Ratio, &b_MuTagIsoR05Ratio);
  fChain->SetBranchAddress("MuTagPFIsoR04Ratio", &MuTagPFIsoR04Ratio, &b_MuTagPFIsoR04Ratio);
  fChain->SetBranchAddress("MuTagPromt", &MuTagPromt, &b_MuTagPromt);
  fChain->SetBranchAddress("MuTagnSegTrkArb", &MuTagnSegTrkArb, &b_MuTagnSegTrkArb);
  fChain->SetBranchAddress("MuTagCaloL", &MuTagCaloL, &b_MuTagCaloL);
  fChain->SetBranchAddress("MuTagCaloT", &MuTagCaloT, &b_MuTagCaloT);
  fChain->SetBranchAddress("MuTagtracktruth_pt", &MuTagtracktruth_pt, &b_MuTagtracktruth_pt);
  fChain->SetBranchAddress("MuTagtracktruth_p", &MuTagtracktruth_p, &b_MuTagtracktruth_p);
  fChain->SetBranchAddress("MuTagtracktruth_id", &MuTagtracktruth_id, &b_MuTagtracktruth_id);
  fChain->SetBranchAddress("MuTagtracktruth_type", &MuTagtracktruth_type, &b_MuTagtracktruth_type);
  fChain->SetBranchAddress("MuTagtracktruth_isPileup", &MuTagtracktruth_isPileup, &b_MuTagtracktruth_isPileup);
  fChain->SetBranchAddress("MuTagtracktruth_thesamewith", &MuTagtracktruth_thesamewith, &b_MuTagtracktruth_thesamewith);
  fChain->SetBranchAddress("vtx_r", &vtx_r, &b_vtx_r);
  fChain->SetBranchAddress("vtx_z", &vtx_z, &b_vtx_z);
  fChain->SetBranchAddress("vtx_rError", &vtx_rError, &b_vtx_rError);
  fChain->SetBranchAddress("vtx_zError", &vtx_zError, &b_vtx_zError);
  fChain->SetBranchAddress("vtx_normChi2", &vtx_normChi2, &b_vtx_normChi2);
  fChain->SetBranchAddress("vtx_size", &vtx_size, &b_vtx_size);
  fChain->SetBranchAddress("iSameVtx", &iSameVtx, &b_iSameVtx);
  fChain->SetBranchAddress("invMass", &invMass, &b_invMass);
  fChain->SetBranchAddress("tracks_e", &tracks_e, &b_tracks_e);
  fChain->SetBranchAddress("tracks_pt", &tracks_pt, &b_tracks_pt);
  fChain->SetBranchAddress("tracks_eta", &tracks_eta, &b_tracks_eta);
  fChain->SetBranchAddress("tracks_phi", &tracks_phi, &b_tracks_phi);
  fChain->SetBranchAddress("tracks_charge", &tracks_charge, &b_tracks_charge);
  fChain->SetBranchAddress("tracks_id", &tracks_id, &b_tracks_id);
  fChain->SetBranchAddress("tracks_normchi2", &tracks_normchi2, &b_tracks_normchi2);
  fChain->SetBranchAddress("tracks_dxy", &tracks_dxy, &b_tracks_dxy);
  fChain->SetBranchAddress("tracks_dz", &tracks_dz, &b_tracks_dz);
  fChain->SetBranchAddress("tracks_vx", &tracks_vx, &b_tracks_vx);
  fChain->SetBranchAddress("tracks_vy", &tracks_vy, &b_tracks_vy);
  fChain->SetBranchAddress("tracks_vz", &tracks_vz, &b_tracks_vz);
  fChain->SetBranchAddress("tracks_IsoR03Ratio", &tracks_IsoR03Ratio, &b_tracks_IsoR03Ratio);
  fChain->SetBranchAddress("tracks_IsoR05Ratio", &tracks_IsoR05Ratio, &b_tracks_IsoR05Ratio);
  fChain->SetBranchAddress("tracks_qoverp", &tracks_qoverp, &b_tracks_qoverp);
  fChain->SetBranchAddress("tracks_lambda", &tracks_lambda, &b_tracks_lambda);
  fChain->SetBranchAddress("tracks_recHitsSize", &tracks_recHitsSize, &b_tracks_recHitsSize);
  fChain->SetBranchAddress("tracks_numberOfValidHits", &tracks_numberOfValidHits, &b_tracks_numberOfValidHits);
  fChain->SetBranchAddress("tracks_numberOfLostHits", &tracks_numberOfLostHits, &b_tracks_numberOfLostHits);
  fChain->SetBranchAddress("tracks_qoverpError", &tracks_qoverpError, &b_tracks_qoverpError);
  fChain->SetBranchAddress("tracks_ptError", &tracks_ptError, &b_tracks_ptError);
  fChain->SetBranchAddress("tracks_thetaError", &tracks_thetaError, &b_tracks_thetaError);
  fChain->SetBranchAddress("tracks_lambdaError", &tracks_lambdaError, &b_tracks_lambdaError);
  fChain->SetBranchAddress("tracks_etaError", &tracks_etaError, &b_tracks_etaError);
  fChain->SetBranchAddress("tracks_phiError", &tracks_phiError, &b_tracks_phiError);
  fChain->SetBranchAddress("tracks_dxyError", &tracks_dxyError, &b_tracks_dxyError);
  fChain->SetBranchAddress("tracks_d0Error", &tracks_d0Error, &b_tracks_d0Error);
  fChain->SetBranchAddress("tracks_dszError", &tracks_dszError, &b_tracks_dszError);
  fChain->SetBranchAddress("tracks_dzError", &tracks_dzError, &b_tracks_dzError);
  fChain->SetBranchAddress("tracks_isCaloMuTrk", &tracks_isCaloMuTrk, &b_tracks_isCaloMuTrk);
  fChain->SetBranchAddress("tracks_isTrackerMuTrk", &tracks_isTrackerMuTrk, &b_tracks_isTrackerMuTrk);
  fChain->SetBranchAddress("tracks_numberOfMatches", &tracks_numberOfMatches, &b_tracks_numberOfMatches);
  fChain->SetBranchAddress("tracktruth_pt", &tracktruth_pt, &b_tracktruth_pt);
  fChain->SetBranchAddress("tracktruth_p", &tracktruth_p, &b_tracktruth_p);
  fChain->SetBranchAddress("tracktruth_e", &tracktruth_e, &b_tracktruth_e);
  fChain->SetBranchAddress("tracktruth_id", &tracktruth_id, &b_tracktruth_id);
  fChain->SetBranchAddress("tracktruth_type", &tracktruth_type, &b_tracktruth_type);
  fChain->SetBranchAddress("tracktruth_isPileup", &tracktruth_isPileup, &b_tracktruth_isPileup);
  fChain->SetBranchAddress("tracktruth_thesamewith", &tracktruth_thesamewith, &b_tracktruth_thesamewith);
  fChain->SetBranchAddress("CSCEndCapPlus", &CSCEndCapPlus, &b_CSCEndCapPlus);
  fChain->SetBranchAddress("CSCRg1", &CSCRg1, &b_CSCRg1);
  fChain->SetBranchAddress("CSCCh1", &CSCCh1, &b_CSCCh1);
  fChain->SetBranchAddress("CSCCBad1", &CSCCBad1, &b_CSCCBad1);
  fChain->SetBranchAddress("CSCDyProjHVGap1", &CSCDyProjHVGap1, &b_CSCDyProjHVGap1);
  fChain->SetBranchAddress("CSCDyErrProjHVGap1", &CSCDyErrProjHVGap1, &b_CSCDyErrProjHVGap1);
  fChain->SetBranchAddress("CSCProjDistEdge1", &CSCProjDistEdge1, &b_CSCProjDistEdge1);
  fChain->SetBranchAddress("CSCProjDistErrEdge1", &CSCProjDistErrEdge1, &b_CSCProjDistErrEdge1);
  fChain->SetBranchAddress("CSCTTxLc1", &CSCTTxLc1, &b_CSCTTxLc1);
  fChain->SetBranchAddress("CSCTTwLc1", &CSCTTwLc1, &b_CSCTTwLc1);
  fChain->SetBranchAddress("CSCTTyLc1", &CSCTTyLc1, &b_CSCTTyLc1);
  fChain->SetBranchAddress("CSCTTsLc1", &CSCTTsLc1, &b_CSCTTsLc1);
  fChain->SetBranchAddress("CSCTTwSegxLc1", &CSCTTwSegxLc1, &b_CSCTTwSegxLc1);
  fChain->SetBranchAddress("CSCTTwSegyLc1", &CSCTTwSegyLc1, &b_CSCTTwSegyLc1);
  fChain->SetBranchAddress("CSCTT3xLc1", &CSCTT3xLc1, &b_CSCTT3xLc1);
  fChain->SetBranchAddress("CSCTT3wLc1", &CSCTT3wLc1, &b_CSCTT3wLc1);
  fChain->SetBranchAddress("CSCTT3yLc1", &CSCTT3yLc1, &b_CSCTT3yLc1);
  fChain->SetBranchAddress("CSCTT3sLc1", &CSCTT3sLc1, &b_CSCTT3sLc1);
  fChain->SetBranchAddress("CSCTT3wLCTxLc1", &CSCTT3wLCTxLc1, &b_CSCTT3wLCTxLc1);
  fChain->SetBranchAddress("CSCTT3wLCTyLc1", &CSCTT3wLCTyLc1, &b_CSCTT3wLCTyLc1);
  fChain->SetBranchAddress("CSCTTxGc1", &CSCTTxGc1, &b_CSCTTxGc1);
  fChain->SetBranchAddress("CSCTTyGc1", &CSCTTyGc1, &b_CSCTTyGc1);
  fChain->SetBranchAddress("CSCTTzGc1", &CSCTTzGc1, &b_CSCTTzGc1);
  fChain->SetBranchAddress("CSCTTetaGc1", &CSCTTetaGc1, &b_CSCTTetaGc1);
  fChain->SetBranchAddress("CSCTT3xGc1", &CSCTT3xGc1, &b_CSCTT3xGc1);
  fChain->SetBranchAddress("CSCTT3yGc1", &CSCTT3yGc1, &b_CSCTT3yGc1);
  fChain->SetBranchAddress("CSCTT3zGc1", &CSCTT3zGc1, &b_CSCTT3zGc1);
  fChain->SetBranchAddress("CSCTT3etaGc1", &CSCTT3etaGc1, &b_CSCTT3etaGc1);
  fChain->SetBranchAddress("CSCSegNumber1", &CSCSegNumber1, &b_CSCSegNumber1);
  fChain->SetBranchAddress("DTSegNumber1", &DTSegNumber1, &b_DTSegNumber1);
  fChain->SetBranchAddress("RPCSegNumber1", &RPCSegNumber1, &b_RPCSegNumber1);
  fChain->SetBranchAddress("CSCSegxLc1", &CSCSegxLc1, &b_CSCSegxLc1);
  fChain->SetBranchAddress("CSCSegyLc1", &CSCSegyLc1, &b_CSCSegyLc1);
  fChain->SetBranchAddress("CSCSegxErrLc1", &CSCSegxErrLc1, &b_CSCSegxErrLc1);
  fChain->SetBranchAddress("CSCSegyErrLc1", &CSCSegyErrLc1, &b_CSCSegyErrLc1);
  fChain->SetBranchAddress("CSCdXdZTTSeg1", &CSCdXdZTTSeg1, &b_CSCdXdZTTSeg1);
  fChain->SetBranchAddress("CSCdYdZTTSeg1", &CSCdYdZTTSeg1, &b_CSCdYdZTTSeg1);
  fChain->SetBranchAddress("CSCSegChisqProb1", &CSCSegChisqProb1, &b_CSCSegChisqProb1);
  fChain->SetBranchAddress("CSCnSegHits1", &CSCnSegHits1, &b_CSCnSegHits1);
  fChain->SetBranchAddress("CSCDxTTSeg1", &CSCDxTTSeg1, &b_CSCDxTTSeg1);
  fChain->SetBranchAddress("CSCDxErrTTSeg1", &CSCDxErrTTSeg1, &b_CSCDxErrTTSeg1);
  fChain->SetBranchAddress("CSCDyTTSeg1", &CSCDyTTSeg1, &b_CSCDyTTSeg1);
  fChain->SetBranchAddress("CSCDyErrTTSeg1", &CSCDyErrTTSeg1, &b_CSCDyErrTTSeg1);
  fChain->SetBranchAddress("CSCDxyTTSeg1", &CSCDxyTTSeg1, &b_CSCDxyTTSeg1);
  fChain->SetBranchAddress("CSCDxyErrTTSeg1", &CSCDxyErrTTSeg1, &b_CSCDxyErrTTSeg1);
  fChain->SetBranchAddress("CSCLCTxLc1", &CSCLCTxLc1, &b_CSCLCTxLc1);
  fChain->SetBranchAddress("CSCLCTyLc1", &CSCLCTyLc1, &b_CSCLCTyLc1);
  fChain->SetBranchAddress("CSCLCTbx1", &CSCLCTbx1, &b_CSCLCTbx1);
  fChain->SetBranchAddress("N_seg_inChamber1", &N_seg_inChamber1, &b_N_seg_inChamber1);
  fChain->SetBranchAddress("CSCDxTTLCT1", &CSCDxTTLCT1, &b_CSCDxTTLCT1);
  fChain->SetBranchAddress("CSCDxErrTTLCT1", &CSCDxErrTTLCT1, &b_CSCDxErrTTLCT1);
  fChain->SetBranchAddress("CSCDyTTLCT1", &CSCDyTTLCT1, &b_CSCDyTTLCT1);
  fChain->SetBranchAddress("CSCDyErrTTLCT1", &CSCDyErrTTLCT1, &b_CSCDyErrTTLCT1);
  fChain->SetBranchAddress("CSCDxyTTLCT1", &CSCDxyTTLCT1, &b_CSCDxyTTLCT1);
  fChain->SetBranchAddress("CSCDxyErrTTLCT1", &CSCDxyErrTTLCT1, &b_CSCDxyErrTTLCT1);
  fChain->SetBranchAddress("dRTkMu1", &dRTkMu1, &b_dRTkMu1);
  fChain->SetBranchAddress("CSCRg2", &CSCRg2, &b_CSCRg2);
  fChain->SetBranchAddress("CSCCh2", &CSCCh2, &b_CSCCh2);
  fChain->SetBranchAddress("CSCCBad2", &CSCCBad2, &b_CSCCBad2);
  fChain->SetBranchAddress("CSCDyProjHVGap2", &CSCDyProjHVGap2, &b_CSCDyProjHVGap2);
  fChain->SetBranchAddress("CSCDyErrProjHVGap2", &CSCDyErrProjHVGap2, &b_CSCDyErrProjHVGap2);
  fChain->SetBranchAddress("CSCProjDistEdge2", &CSCProjDistEdge2, &b_CSCProjDistEdge2);
  fChain->SetBranchAddress("CSCProjDistErrEdge2", &CSCProjDistErrEdge2, &b_CSCProjDistErrEdge2);
  fChain->SetBranchAddress("CSCTTxLc2", &CSCTTxLc2, &b_CSCTTxLc2);
  fChain->SetBranchAddress("CSCTTwLc2", &CSCTTwLc2, &b_CSCTTwLc2);
  fChain->SetBranchAddress("CSCTTyLc2", &CSCTTyLc2, &b_CSCTTyLc2);
  fChain->SetBranchAddress("CSCTTsLc2", &CSCTTsLc2, &b_CSCTTsLc2);
  fChain->SetBranchAddress("CSCTTwSegxLc2", &CSCTTwSegxLc2, &b_CSCTTwSegxLc2);
  fChain->SetBranchAddress("CSCTTwSegyLc2", &CSCTTwSegyLc2, &b_CSCTTwSegyLc2);
  fChain->SetBranchAddress("CSCTT3xLc2", &CSCTT3xLc2, &b_CSCTT3xLc2);
  fChain->SetBranchAddress("CSCTT3wLc2", &CSCTT3wLc2, &b_CSCTT3wLc2);
  fChain->SetBranchAddress("CSCTT3yLc2", &CSCTT3yLc2, &b_CSCTT3yLc2);
  fChain->SetBranchAddress("CSCTT3sLc2", &CSCTT3sLc2, &b_CSCTT3sLc2);
  fChain->SetBranchAddress("CSCTT3wLCTxLc2", &CSCTT3wLCTxLc2, &b_CSCTT3wLCTxLc2);
  fChain->SetBranchAddress("CSCTT3wLCTyLc2", &CSCTT3wLCTyLc2, &b_CSCTT3wLCTyLc2);
  fChain->SetBranchAddress("CSCTTxGc2", &CSCTTxGc2, &b_CSCTTxGc2);
  fChain->SetBranchAddress("CSCTTyGc2", &CSCTTyGc2, &b_CSCTTyGc2);
  fChain->SetBranchAddress("CSCTTzGc2", &CSCTTzGc2, &b_CSCTTzGc2);
  fChain->SetBranchAddress("CSCTTetaGc2", &CSCTTetaGc2, &b_CSCTTetaGc2);
  fChain->SetBranchAddress("CSCTT3xGc2", &CSCTT3xGc2, &b_CSCTT3xGc2);
  fChain->SetBranchAddress("CSCTT3yGc2", &CSCTT3yGc2, &b_CSCTT3yGc2);
  fChain->SetBranchAddress("CSCTT3zGc2", &CSCTT3zGc2, &b_CSCTT3zGc2);
  fChain->SetBranchAddress("CSCTT3etaGc2", &CSCTT3etaGc2, &b_CSCTT3etaGc2);
  fChain->SetBranchAddress("CSCSegNumber2", &CSCSegNumber2, &b_CSCSegNumber2);
  fChain->SetBranchAddress("DTSegNumber2", &DTSegNumber2, &b_DTSegNumber2);
  fChain->SetBranchAddress("RPCSegNumber2", &RPCSegNumber2, &b_RPCSegNumber2);
  fChain->SetBranchAddress("CSCSegxLc2", &CSCSegxLc2, &b_CSCSegxLc2);
  fChain->SetBranchAddress("CSCSegyLc2", &CSCSegyLc2, &b_CSCSegyLc2);
  fChain->SetBranchAddress("CSCSegxErrLc2", &CSCSegxErrLc2, &b_CSCSegxErrLc2);
  fChain->SetBranchAddress("CSCSegyErrLc2", &CSCSegyErrLc2, &b_CSCSegyErrLc2);
  fChain->SetBranchAddress("CSCdXdZTTSeg2", &CSCdXdZTTSeg2, &b_CSCdXdZTTSeg2);
  fChain->SetBranchAddress("CSCdYdZTTSeg2", &CSCdYdZTTSeg2, &b_CSCdYdZTTSeg2);
  fChain->SetBranchAddress("CSCSegChisqProb2", &CSCSegChisqProb2, &b_CSCSegChisqProb2);
  fChain->SetBranchAddress("CSCnSegHits2", &CSCnSegHits2, &b_CSCnSegHits2);
  fChain->SetBranchAddress("CSCDxTTSeg2", &CSCDxTTSeg2, &b_CSCDxTTSeg2);
  fChain->SetBranchAddress("CSCDxErrTTSeg2", &CSCDxErrTTSeg2, &b_CSCDxErrTTSeg2);
  fChain->SetBranchAddress("CSCDyTTSeg2", &CSCDyTTSeg2, &b_CSCDyTTSeg2);
  fChain->SetBranchAddress("CSCDyErrTTSeg2", &CSCDyErrTTSeg2, &b_CSCDyErrTTSeg2);
  fChain->SetBranchAddress("CSCDxyTTSeg2", &CSCDxyTTSeg2, &b_CSCDxyTTSeg2);
  fChain->SetBranchAddress("CSCDxyErrTTSeg2", &CSCDxyErrTTSeg2, &b_CSCDxyErrTTSeg2);
  fChain->SetBranchAddress("CSCLCTxLc2", &CSCLCTxLc2, &b_CSCLCTxLc2);
  fChain->SetBranchAddress("CSCLCTyLc2", &CSCLCTyLc2, &b_CSCLCTyLc2);
  fChain->SetBranchAddress("CSCLCTbx2", &CSCLCTbx2, &b_CSCLCTbx2);
  fChain->SetBranchAddress("N_seg_inChamber2", &N_seg_inChamber2, &b_N_seg_inChamber2);
  fChain->SetBranchAddress("CSCDxTTLCT2", &CSCDxTTLCT2, &b_CSCDxTTLCT2);
  fChain->SetBranchAddress("CSCDxErrTTLCT2", &CSCDxErrTTLCT2, &b_CSCDxErrTTLCT2);
  fChain->SetBranchAddress("CSCDyTTLCT2", &CSCDyTTLCT2, &b_CSCDyTTLCT2);
  fChain->SetBranchAddress("CSCDyErrTTLCT2", &CSCDyErrTTLCT2, &b_CSCDyErrTTLCT2);
  fChain->SetBranchAddress("CSCDxyTTLCT2", &CSCDxyTTLCT2, &b_CSCDxyTTLCT2);
  fChain->SetBranchAddress("CSCDxyErrTTLCT2", &CSCDxyErrTTLCT2, &b_CSCDxyErrTTLCT2);
  fChain->SetBranchAddress("dRTkMu2", &dRTkMu2, &b_dRTkMu2);
  fChain->SetBranchAddress("CSCRg3", &CSCRg3, &b_CSCRg3);
  fChain->SetBranchAddress("CSCCh3", &CSCCh3, &b_CSCCh3);
  fChain->SetBranchAddress("CSCCBad3", &CSCCBad3, &b_CSCCBad3);
  fChain->SetBranchAddress("CSCDyProjHVGap3", &CSCDyProjHVGap3, &b_CSCDyProjHVGap3);
  fChain->SetBranchAddress("CSCDyErrProjHVGap3", &CSCDyErrProjHVGap3, &b_CSCDyErrProjHVGap3);
  fChain->SetBranchAddress("CSCProjDistEdge3", &CSCProjDistEdge3, &b_CSCProjDistEdge3);
  fChain->SetBranchAddress("CSCProjDistErrEdge3", &CSCProjDistErrEdge3, &b_CSCProjDistErrEdge3);
  fChain->SetBranchAddress("CSCTTxLc3", &CSCTTxLc3, &b_CSCTTxLc3);
  fChain->SetBranchAddress("CSCTTwLc3", &CSCTTwLc3, &b_CSCTTwLc3);
  fChain->SetBranchAddress("CSCTTyLc3", &CSCTTyLc3, &b_CSCTTyLc3);
  fChain->SetBranchAddress("CSCTTsLc3", &CSCTTsLc3, &b_CSCTTsLc3);
  fChain->SetBranchAddress("CSCTTwSegxLc3", &CSCTTwSegxLc3, &b_CSCTTwSegxLc3);
  fChain->SetBranchAddress("CSCTTwSegyLc3", &CSCTTwSegyLc3, &b_CSCTTwSegyLc3);
  fChain->SetBranchAddress("CSCTT3xLc3", &CSCTT3xLc3, &b_CSCTT3xLc3);
  fChain->SetBranchAddress("CSCTT3wLc3", &CSCTT3wLc3, &b_CSCTT3wLc3);
  fChain->SetBranchAddress("CSCTT3yLc3", &CSCTT3yLc3, &b_CSCTT3yLc3);
  fChain->SetBranchAddress("CSCTT3sLc3", &CSCTT3sLc3, &b_CSCTT3sLc3);
  fChain->SetBranchAddress("CSCTT3wLCTxLc3", &CSCTT3wLCTxLc3, &b_CSCTT3wLCTxLc3);
  fChain->SetBranchAddress("CSCTT3wLCTyLc3", &CSCTT3wLCTyLc3, &b_CSCTT3wLCTyLc3);
  fChain->SetBranchAddress("CSCTTxGc3", &CSCTTxGc3, &b_CSCTTxGc3);
  fChain->SetBranchAddress("CSCTTyGc3", &CSCTTyGc3, &b_CSCTTyGc3);
  fChain->SetBranchAddress("CSCTTzGc3", &CSCTTzGc3, &b_CSCTTzGc3);
  fChain->SetBranchAddress("CSCTTetaGc3", &CSCTTetaGc3, &b_CSCTTetaGc3);
  fChain->SetBranchAddress("CSCTT3xGc3", &CSCTT3xGc3, &b_CSCTT3xGc3);
  fChain->SetBranchAddress("CSCTT3yGc3", &CSCTT3yGc3, &b_CSCTT3yGc3);
  fChain->SetBranchAddress("CSCTT3zGc3", &CSCTT3zGc3, &b_CSCTT3zGc3);
  fChain->SetBranchAddress("CSCTT3etaGc3", &CSCTT3etaGc3, &b_CSCTT3etaGc3);
  fChain->SetBranchAddress("CSCSegNumber3", &CSCSegNumber3, &b_CSCSegNumber3);
  fChain->SetBranchAddress("DTSegNumber3", &DTSegNumber3, &b_DTSegNumber3);
  fChain->SetBranchAddress("RPCSegNumber3", &RPCSegNumber3, &b_RPCSegNumber3);
  fChain->SetBranchAddress("CSCSegxLc3", &CSCSegxLc3, &b_CSCSegxLc3);
  fChain->SetBranchAddress("CSCSegyLc3", &CSCSegyLc3, &b_CSCSegyLc3);
  fChain->SetBranchAddress("CSCSegxErrLc3", &CSCSegxErrLc3, &b_CSCSegxErrLc3);
  fChain->SetBranchAddress("CSCSegyErrLc3", &CSCSegyErrLc3, &b_CSCSegyErrLc3);
  fChain->SetBranchAddress("CSCdXdZTTSeg3", &CSCdXdZTTSeg3, &b_CSCdXdZTTSeg3);
  fChain->SetBranchAddress("CSCdYdZTTSeg3", &CSCdYdZTTSeg3, &b_CSCdYdZTTSeg3);
  fChain->SetBranchAddress("CSCSegChisqProb3", &CSCSegChisqProb3, &b_CSCSegChisqProb3);
  fChain->SetBranchAddress("CSCnSegHits3", &CSCnSegHits3, &b_CSCnSegHits3);
  fChain->SetBranchAddress("CSCDxTTSeg3", &CSCDxTTSeg3, &b_CSCDxTTSeg3);
  fChain->SetBranchAddress("CSCDxErrTTSeg3", &CSCDxErrTTSeg3, &b_CSCDxErrTTSeg3);
  fChain->SetBranchAddress("CSCDyTTSeg3", &CSCDyTTSeg3, &b_CSCDyTTSeg3);
  fChain->SetBranchAddress("CSCDyErrTTSeg3", &CSCDyErrTTSeg3, &b_CSCDyErrTTSeg3);
  fChain->SetBranchAddress("CSCDxyTTSeg3", &CSCDxyTTSeg3, &b_CSCDxyTTSeg3);
  fChain->SetBranchAddress("CSCDxyErrTTSeg3", &CSCDxyErrTTSeg3, &b_CSCDxyErrTTSeg3);
  fChain->SetBranchAddress("CSCLCTxLc3", &CSCLCTxLc3, &b_CSCLCTxLc3);
  fChain->SetBranchAddress("CSCLCTyLc3", &CSCLCTyLc3, &b_CSCLCTyLc3);
  fChain->SetBranchAddress("CSCLCTbx3", &CSCLCTbx3, &b_CSCLCTbx3);
  fChain->SetBranchAddress("N_seg_inChamber3", &N_seg_inChamber3, &b_N_seg_inChamber3);
  fChain->SetBranchAddress("CSCDxTTLCT3", &CSCDxTTLCT3, &b_CSCDxTTLCT3);
  fChain->SetBranchAddress("CSCDxErrTTLCT3", &CSCDxErrTTLCT3, &b_CSCDxErrTTLCT3);
  fChain->SetBranchAddress("CSCDyTTLCT3", &CSCDyTTLCT3, &b_CSCDyTTLCT3);
  fChain->SetBranchAddress("CSCDyErrTTLCT3", &CSCDyErrTTLCT3, &b_CSCDyErrTTLCT3);
  fChain->SetBranchAddress("CSCDxyTTLCT3", &CSCDxyTTLCT3, &b_CSCDxyTTLCT3);
  fChain->SetBranchAddress("CSCDxyErrTTLCT3", &CSCDxyErrTTLCT3, &b_CSCDxyErrTTLCT3);
  fChain->SetBranchAddress("dRTkMu3", &dRTkMu3, &b_dRTkMu3);
  fChain->SetBranchAddress("CSCRg4", &CSCRg4, &b_CSCRg4);
  fChain->SetBranchAddress("CSCCh4", &CSCCh4, &b_CSCCh4);
  fChain->SetBranchAddress("CSCCBad4", &CSCCBad4, &b_CSCCBad4);
  fChain->SetBranchAddress("CSCDyProjHVGap4", &CSCDyProjHVGap4, &b_CSCDyProjHVGap4);
  fChain->SetBranchAddress("CSCDyErrProjHVGap4", &CSCDyErrProjHVGap4, &b_CSCDyErrProjHVGap4);
  fChain->SetBranchAddress("CSCProjDistEdge4", &CSCProjDistEdge4, &b_CSCProjDistEdge4);
  fChain->SetBranchAddress("CSCProjDistErrEdge4", &CSCProjDistErrEdge4, &b_CSCProjDistErrEdge4);
  fChain->SetBranchAddress("CSCTTxLc4", &CSCTTxLc4, &b_CSCTTxLc4);
  fChain->SetBranchAddress("CSCTTwLc4", &CSCTTwLc4, &b_CSCTTwLc4);
  fChain->SetBranchAddress("CSCTTyLc4", &CSCTTyLc4, &b_CSCTTyLc4);
  fChain->SetBranchAddress("CSCTTsLc4", &CSCTTsLc4, &b_CSCTTsLc4);
  fChain->SetBranchAddress("CSCTTwSegxLc4", &CSCTTwSegxLc4, &b_CSCTTwSegxLc4);
  fChain->SetBranchAddress("CSCTTwSegyLc4", &CSCTTwSegyLc4, &b_CSCTTwSegyLc4);
  fChain->SetBranchAddress("CSCTT3xLc4", &CSCTT3xLc4, &b_CSCTT3xLc4);
  fChain->SetBranchAddress("CSCTT3wLc4", &CSCTT3wLc4, &b_CSCTT3wLc4);
  fChain->SetBranchAddress("CSCTT3yLc4", &CSCTT3yLc4, &b_CSCTT3yLc4);
  fChain->SetBranchAddress("CSCTT3sLc4", &CSCTT3sLc4, &b_CSCTT3sLc4);
  fChain->SetBranchAddress("CSCTT3wLCTxLc4", &CSCTT3wLCTxLc4, &b_CSCTT3wLCTxLc4);
  fChain->SetBranchAddress("CSCTT3wLCTyLc4", &CSCTT3wLCTyLc4, &b_CSCTT3wLCTyLc4);
  fChain->SetBranchAddress("CSCTTxGc4", &CSCTTxGc4, &b_CSCTTxGc4);
  fChain->SetBranchAddress("CSCTTyGc4", &CSCTTyGc4, &b_CSCTTyGc4);
  fChain->SetBranchAddress("CSCTTzGc4", &CSCTTzGc4, &b_CSCTTzGc4);
  fChain->SetBranchAddress("CSCTTetaGc4", &CSCTTetaGc4, &b_CSCTTetaGc4);
  fChain->SetBranchAddress("CSCTT3xGc4", &CSCTT3xGc4, &b_CSCTT3xGc4);
  fChain->SetBranchAddress("CSCTT3yGc4", &CSCTT3yGc4, &b_CSCTT3yGc4);
  fChain->SetBranchAddress("CSCTT3zGc4", &CSCTT3zGc4, &b_CSCTT3zGc4);
  fChain->SetBranchAddress("CSCTT3etaGc4", &CSCTT3etaGc4, &b_CSCTT3etaGc4);
  fChain->SetBranchAddress("CSCSegNumber4", &CSCSegNumber4, &b_CSCSegNumber4);
  fChain->SetBranchAddress("DTSegNumber4", &DTSegNumber4, &b_DTSegNumber4);
  fChain->SetBranchAddress("RPCSegNumber4", &RPCSegNumber4, &b_RPCSegNumber4);
  fChain->SetBranchAddress("CSCSegxLc4", &CSCSegxLc4, &b_CSCSegxLc4);
  fChain->SetBranchAddress("CSCSegyLc4", &CSCSegyLc4, &b_CSCSegyLc4);
  fChain->SetBranchAddress("CSCSegxErrLc4", &CSCSegxErrLc4, &b_CSCSegxErrLc4);
  fChain->SetBranchAddress("CSCSegyErrLc4", &CSCSegyErrLc4, &b_CSCSegyErrLc4);
  fChain->SetBranchAddress("CSCdXdZTTSeg4", &CSCdXdZTTSeg4, &b_CSCdXdZTTSeg4);
  fChain->SetBranchAddress("CSCdYdZTTSeg4", &CSCdYdZTTSeg4, &b_CSCdYdZTTSeg4);
  fChain->SetBranchAddress("CSCSegChisqProb4", &CSCSegChisqProb4, &b_CSCSegChisqProb4);
  fChain->SetBranchAddress("CSCnSegHits4", &CSCnSegHits4, &b_CSCnSegHits4);
  fChain->SetBranchAddress("CSCDxTTSeg4", &CSCDxTTSeg4, &b_CSCDxTTSeg4);
  fChain->SetBranchAddress("CSCDxErrTTSeg4", &CSCDxErrTTSeg4, &b_CSCDxErrTTSeg4);
  fChain->SetBranchAddress("CSCDyTTSeg4", &CSCDyTTSeg4, &b_CSCDyTTSeg4);
  fChain->SetBranchAddress("CSCDyErrTTSeg4", &CSCDyErrTTSeg4, &b_CSCDyErrTTSeg4);
  fChain->SetBranchAddress("CSCDxyTTSeg4", &CSCDxyTTSeg4, &b_CSCDxyTTSeg4);
  fChain->SetBranchAddress("CSCDxyErrTTSeg4", &CSCDxyErrTTSeg4, &b_CSCDxyErrTTSeg4);
  fChain->SetBranchAddress("CSCLCTxLc4", &CSCLCTxLc4, &b_CSCLCTxLc4);
  fChain->SetBranchAddress("CSCLCTyLc4", &CSCLCTyLc4, &b_CSCLCTyLc4);
  fChain->SetBranchAddress("CSCLCTbx4", &CSCLCTbx4, &b_CSCLCTbx4);
  fChain->SetBranchAddress("N_seg_inChamber4", &N_seg_inChamber4, &b_N_seg_inChamber4);
  fChain->SetBranchAddress("CSCDxTTLCT4", &CSCDxTTLCT4, &b_CSCDxTTLCT4);
  fChain->SetBranchAddress("CSCDxErrTTLCT4", &CSCDxErrTTLCT4, &b_CSCDxErrTTLCT4);
  fChain->SetBranchAddress("CSCDyTTLCT4", &CSCDyTTLCT4, &b_CSCDyTTLCT4);
  fChain->SetBranchAddress("CSCDyErrTTLCT4", &CSCDyErrTTLCT4, &b_CSCDyErrTTLCT4);
  fChain->SetBranchAddress("CSCDxyTTLCT4", &CSCDxyTTLCT4, &b_CSCDxyTTLCT4);
  fChain->SetBranchAddress("CSCDxyErrTTLCT4", &CSCDxyErrTTLCT4, &b_CSCDxyErrTTLCT4);
  fChain->SetBranchAddress("dRTkMu4", &dRTkMu4, &b_dRTkMu4);
  fChain->SetBranchAddress("HLTMuAcceptance", &HLTMuAcceptance, &b_HLTMuAcceptance);
  fChain->SetBranchAddress("HLTDiMuAcceptance", &HLTDiMuAcceptance, &b_HLTDiMuAcceptance);
  fChain->SetBranchAddress("minDRHLTMu", &minDRHLTMu, &b_minDRHLTMu);
  fChain->SetBranchAddress("minDRHLTDiMu", &minDRHLTDiMu, &b_minDRHLTDiMu);
  fChain->SetBranchAddress("minDRHLTAllSingleMu", &minDRHLTAllSingleMu, &b_minDRHLTAllSingleMu);
  Notify();
}

Bool_t CSCEffFast::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void CSCEffFast::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t CSCEffFast::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef CSCEffFast_cxx
