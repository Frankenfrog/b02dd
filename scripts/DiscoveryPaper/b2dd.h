//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 21 09:58:01 2015 by ROOT version 6.00/02
// from TTree B02DD/GrimReaperTree
// found on file: DT2012_B02DD_Stripping21_DVv36r1_20150322_fmeier_combined_20150412_fmeier_BDT_TupleB_Kpipi.root
//////////////////////////////////////////////////////////

#ifndef b2dd_h
#define b2dd_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class b2dd {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxB0_ENDVERTEX_COV = 1;
   const Int_t kMaxB0_OWNPV_COV = 1;
   const Int_t kMaxDplus_ENDVERTEX_COV = 1;
   const Int_t kMaxDplus_OWNPV_COV = 1;
   const Int_t kMaxDplus_ORIVX_COV = 1;
   const Int_t kMaxDplus_Kminus_or_piminus_OWNPV_COV = 1;
   const Int_t kMaxDplus_Kminus_or_piminus_ORIVX_COV = 1;
   const Int_t kMaxDplus_piplus_or_Kplus_One_OWNPV_COV = 1;
   const Int_t kMaxDplus_piplus_or_Kplus_One_ORIVX_COV = 1;
   const Int_t kMaxDplus_piplus_or_Kplus_Two_OWNPV_COV = 1;
   const Int_t kMaxDplus_piplus_or_Kplus_Two_ORIVX_COV = 1;
   const Int_t kMaxDminus_ENDVERTEX_COV = 1;
   const Int_t kMaxDminus_OWNPV_COV = 1;
   const Int_t kMaxDminus_ORIVX_COV = 1;
   const Int_t kMaxDminus_Kplus_or_piplus_OWNPV_COV = 1;
   const Int_t kMaxDminus_Kplus_or_piplus_ORIVX_COV = 1;
   const Int_t kMaxDminus_piminus_or_Kminus_One_OWNPV_COV = 1;
   const Int_t kMaxDminus_piminus_or_Kminus_One_ORIVX_COV = 1;
   const Int_t kMaxDminus_piminus_or_Kminus_Two_OWNPV_COV = 1;
   const Int_t kMaxDminus_piminus_or_Kminus_Two_ORIVX_COV = 1;

   // Declaration of leaf types
   Double_t        B0_LOKI_ENERGY;
   Double_t        B0_LOKI_ETA;
   Double_t        B0_LOKI_PHI;
   Double_t        B0_ENDVERTEX_X;
   Double_t        B0_ENDVERTEX_Y;
   Double_t        B0_ENDVERTEX_Z;
   Double_t        B0_ENDVERTEX_XERR;
   Double_t        B0_ENDVERTEX_YERR;
   Double_t        B0_ENDVERTEX_ZERR;
   Double_t        B0_ENDVERTEX_CHI2;
   Int_t           B0_ENDVERTEX_NDOF;
   Float_t         B0_ENDVERTEX_COV_[3][3];
   Double_t        B0_OWNPV_X;
   Double_t        B0_OWNPV_Y;
   Double_t        B0_OWNPV_Z;
   Double_t        B0_OWNPV_XERR;
   Double_t        B0_OWNPV_YERR;
   Double_t        B0_OWNPV_ZERR;
   Double_t        B0_OWNPV_CHI2;
   Int_t           B0_OWNPV_NDOF;
   Float_t         B0_OWNPV_COV_[3][3];
   Double_t        B0_IP_OWNPV;
   Double_t        B0_IPCHI2_OWNPV;
   Double_t        B0_FD_OWNPV;
   Double_t        B0_FDCHI2_OWNPV;
   Double_t        B0_DIRA_OWNPV;
   Double_t        B0_P;
   Double_t        B0_PT;
   Double_t        B0_PE;
   Double_t        B0_PX;
   Double_t        B0_PY;
   Double_t        B0_PZ;
   Double_t        B0_MM;
   Double_t        B0_MMERR;
   Double_t        B0_M;
   Int_t           B0_ID;
   Double_t        B0_TAU;
   Double_t        B0_TAUERR;
   Double_t        B0_TAUCHI2;
   Double_t        B0_X;
   Double_t        B0_Y;
   Double_t        B0_LOKI_DIRA;
   Double_t        B0_LOKI_DTF_CHI2NDOF;
   Double_t        B0_LOKI_DTF_CTAU;
   Double_t        B0_LOKI_DTF_CTAUERR;
   Double_t        B0_LOKI_DTF_CTAUERR_D1;
   Double_t        B0_LOKI_DTF_CTAUERR_D2;
   Double_t        B0_LOKI_DTF_CTAUERR_NOPV;
   Double_t        B0_LOKI_DTF_CTAUS;
   Double_t        B0_LOKI_DTF_CTAU_D1;
   Double_t        B0_LOKI_DTF_CTAU_D2;
   Double_t        B0_LOKI_DTF_CTAU_NOPV;
   Double_t        B0_LOKI_DTF_VCHI2NDOF;
   Double_t        B0_LOKI_FDCHI2;
   Double_t        B0_LOKI_FDS;
   Double_t        B0_LOKI_MASSERR_DDConstr;
   Double_t        B0_LOKI_MASSERR_DminusConstr;
   Double_t        B0_LOKI_MASSERR_DplusConstr;
   Double_t        B0_LOKI_MASS_DDConstr;
   Double_t        B0_LOKI_MASS_DminusConstr;
   Double_t        B0_LOKI_MASS_Dminus_NoPVConstr;
   Double_t        B0_LOKI_MASS_DplusConstr;
   Double_t        B0_LOKI_MASS_Dplus_NoPVConstr;
   Int_t           B0_Fit_nPV;
   Float_t         B0_Fit_Dminus_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_M[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_MERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_ID[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_PE[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_PX[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_PY[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_PZ[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_XERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_YERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P0_ZERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_ID[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_PE[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_PX[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_PY[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_PZ[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_XERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_YERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P1_ZERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_ID[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_PE[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_PX[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_PY[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_PZ[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_XERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_YERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_P2_ZERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_ctau[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_ctauErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_decayLength[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_decayLengthErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_tau[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dminus_tauErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_M[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_MERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_ID[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_PE[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_PX[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_PY[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_PZ[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_XERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_YERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P0_ZERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_ID[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_PE[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_PX[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_PY[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_PZ[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_XERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_YERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P1_ZERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_ID[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_PE[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_PX[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_PY[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_PZ[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_XERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_YERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_P2_ZERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_ctau[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_ctauErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_decayLength[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_decayLengthErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_tau[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Dplus_tauErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_IP[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_IPCHI2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_M[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_MERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_P[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PT[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PTERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_XVAR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_XYCOV[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_XZCOV[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_YVAR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_YZCOV[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_ZVAR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_PV_key[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_X[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_XERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Y[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_YERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_Z[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_ZERR[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_chi2[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_ctau[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_ctauErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_decayLength[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_decayLengthErr[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_nDOF[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_nIter[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_status[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_tau[1];   //[B0_Fit_nPV]
   Float_t         B0_Fit_tauErr[1];   //[B0_Fit_nPV]
   Int_t           B0_FitDDConst_nPV;
   Float_t         B0_FitDDConst_Dminus_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_M[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_MERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_ID[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_PE[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_PX[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_PY[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_PZ[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_XERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_YERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P0_ZERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_ID[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_PE[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_PX[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_PY[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_PZ[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_XERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_YERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P1_ZERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_ID[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_PE[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_PX[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_PY[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_PZ[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_XERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_YERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_P2_ZERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_ctau[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_ctauErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_decayLength[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_decayLengthErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_tau[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dminus_tauErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_M[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_MERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_ID[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_PE[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_PX[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_PY[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_PZ[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_XERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_YERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P0_ZERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_ID[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_PE[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_PX[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_PY[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_PZ[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_XERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_YERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P1_ZERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_ID[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_PE[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_PX[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_PY[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_PZ[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_XERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_YERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_P2_ZERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_ctau[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_ctauErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_decayLength[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_decayLengthErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_tau[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Dplus_tauErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_IP[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_IPCHI2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_M[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_MERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_P[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PT[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PTERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_XVAR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_XYCOV[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_XZCOV[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_YVAR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_YZCOV[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_ZVAR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_PV_key[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_X[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_XERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Y[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_YERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_Z[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_ZERR[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_chi2[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_ctau[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_ctauErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_decayLength[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_decayLengthErr[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_nDOF[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_nIter[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_status[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_tau[1];   //[B0_FitDDConst_nPV]
   Float_t         B0_FitDDConst_tauErr[1];   //[B0_FitDDConst_nPV]
   Int_t           B0_FitDDPVConst_nPV;
   Float_t         B0_FitDDPVConst_Dminus_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_M[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_MERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_ID[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_PE[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_PX[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_PY[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_PZ[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_XERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_YERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P0_ZERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_ID[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_PE[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_PX[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_PY[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_PZ[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_XERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_YERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P1_ZERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_ID[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_PE[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_PX[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_PY[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_PZ[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_XERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_YERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_P2_ZERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_ctau[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_ctauErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_decayLength[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_decayLengthErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_tau[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dminus_tauErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_M[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_MERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_ID[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_PE[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_PX[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_PY[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_PZ[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_XERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_YERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P0_ZERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_ID[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_PE[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_PX[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_PY[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_PZ[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_XERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_YERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P1_ZERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_ID[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_PE[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_PX[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_PY[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_PZ[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_XERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_YERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_P2_ZERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_ctau[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_ctauErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_decayLength[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_decayLengthErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_tau[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Dplus_tauErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_IP[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_IPCHI2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_M[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_MERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_P[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PT[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PTERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_XVAR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_XYCOV[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_XZCOV[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_YVAR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_YZCOV[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_ZVAR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_PV_key[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_X[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_XERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Y[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_YERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_Z[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_ZERR[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_chi2[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_ctau[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_ctauErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_decayLength[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_decayLengthErr[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_nDOF[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_nIter[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_status[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_tau[1];   //[B0_FitDDPVConst_nPV]
   Float_t         B0_FitDDPVConst_tauErr[1];   //[B0_FitDDPVConst_nPV]
   Int_t           B0_FitPVConst_nPV;
   Float_t         B0_FitPVConst_Dminus_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_M[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_MERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_ID[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_PE[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_PX[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_PY[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_PZ[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_XERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_YERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P0_ZERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_ID[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_PE[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_PX[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_PY[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_PZ[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_XERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_YERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P1_ZERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_ID[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_PE[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_PX[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_PY[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_PZ[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_XERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_YERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_P2_ZERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_ctau[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_ctauErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_decayLength[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_decayLengthErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_tau[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dminus_tauErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_M[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_MERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_ID[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_PE[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_PX[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_PY[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_PZ[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_XERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_YERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P0_ZERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_ID[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_PE[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_PX[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_PY[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_PZ[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_XERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_YERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P1_ZERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_ID[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_PE[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_PX[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_PY[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_PZ[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_XERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_YERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_P2_ZERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_ctau[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_ctauErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_decayLength[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_decayLengthErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_tau[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Dplus_tauErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_IP[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_IPCHI2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_M[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_MERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_P[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PT[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PTERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_XVAR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_XYCOV[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_XZCOV[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_YVAR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_YZCOV[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_ZVAR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_PV_key[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_X[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_XERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Y[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_YERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_Z[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_ZERR[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_chi2[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_ctau[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_ctauErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_decayLength[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_decayLengthErr[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_nDOF[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_nIter[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_status[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_tau[1];   //[B0_FitPVConst_nPV]
   Float_t         B0_FitPVConst_tauErr[1];   //[B0_FitPVConst_nPV]
   Bool_t          B0_L0Global_Dec;
   Bool_t          B0_L0Global_TIS;
   Bool_t          B0_L0Global_TOS;
   Bool_t          B0_Hlt1Global_Dec;
   Bool_t          B0_Hlt1Global_TIS;
   Bool_t          B0_Hlt1Global_TOS;
   Bool_t          B0_Hlt1Phys_Dec;
   Bool_t          B0_Hlt1Phys_TIS;
   Bool_t          B0_Hlt1Phys_TOS;
   Bool_t          B0_Hlt2Global_Dec;
   Bool_t          B0_Hlt2Global_TIS;
   Bool_t          B0_Hlt2Global_TOS;
   Bool_t          B0_Hlt2Phys_Dec;
   Bool_t          B0_Hlt2Phys_TIS;
   Bool_t          B0_Hlt2Phys_TOS;
   Bool_t          B0_L0PhysicsDecision_Dec;
   Bool_t          B0_L0PhysicsDecision_TIS;
   Bool_t          B0_L0PhysicsDecision_TOS;
   Bool_t          B0_L0MuonDecision_Dec;
   Bool_t          B0_L0MuonDecision_TIS;
   Bool_t          B0_L0MuonDecision_TOS;
   Bool_t          B0_L0DiMuonDecision_Dec;
   Bool_t          B0_L0DiMuonDecision_TIS;
   Bool_t          B0_L0DiMuonDecision_TOS;
   Bool_t          B0_L0MuonHighDecision_Dec;
   Bool_t          B0_L0MuonHighDecision_TIS;
   Bool_t          B0_L0MuonHighDecision_TOS;
   Bool_t          B0_L0HadronDecision_Dec;
   Bool_t          B0_L0HadronDecision_TIS;
   Bool_t          B0_L0HadronDecision_TOS;
   Bool_t          B0_L0ElectronDecision_Dec;
   Bool_t          B0_L0ElectronDecision_TIS;
   Bool_t          B0_L0ElectronDecision_TOS;
   Bool_t          B0_L0PhotonDecision_Dec;
   Bool_t          B0_L0PhotonDecision_TIS;
   Bool_t          B0_L0PhotonDecision_TOS;
   Bool_t          B0_Hlt1TrackAllL0Decision_Dec;
   Bool_t          B0_Hlt1TrackAllL0Decision_TIS;
   Bool_t          B0_Hlt1TrackAllL0Decision_TOS;
   Bool_t          B0_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          B0_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          B0_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          B0_Hlt1L0AnyDecision_Dec;
   Bool_t          B0_Hlt1L0AnyDecision_TIS;
   Bool_t          B0_Hlt1L0AnyDecision_TOS;
   Bool_t          B0_Hlt1GlobalDecision_Dec;
   Bool_t          B0_Hlt1GlobalDecision_TIS;
   Bool_t          B0_Hlt1GlobalDecision_TOS;
   Bool_t          B0_Hlt2GlobalDecision_Dec;
   Bool_t          B0_Hlt2GlobalDecision_TIS;
   Bool_t          B0_Hlt2GlobalDecision_TOS;
   Bool_t          B0_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          B0_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          B0_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          B0_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          B0_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          B0_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          B0_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          B0_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          B0_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          B0_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2TopoE2BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2TopoE2BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2TopoE2BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2TopoE3BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2TopoE3BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2TopoE3BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2TopoE4BodyBBDTDecision_Dec;
   Bool_t          B0_Hlt2TopoE4BodyBBDTDecision_TIS;
   Bool_t          B0_Hlt2TopoE4BodyBBDTDecision_TOS;
   Bool_t          B0_Hlt2IncPhiDecision_Dec;
   Bool_t          B0_Hlt2IncPhiDecision_TIS;
   Bool_t          B0_Hlt2IncPhiDecision_TOS;
   Bool_t          B0_Hlt2IncPhiSidebandsDecision_Dec;
   Bool_t          B0_Hlt2IncPhiSidebandsDecision_TIS;
   Bool_t          B0_Hlt2IncPhiSidebandsDecision_TOS;
   Int_t           B0_TAGDECISION;
   Double_t        B0_TAGOMEGA;
   Int_t           B0_TAGDECISION_OS;
   Double_t        B0_TAGOMEGA_OS;
   Int_t           B0_TAGGER;
   Short_t         B0_OS_Muon_DEC;
   Float_t         B0_OS_Muon_PROB;
   Short_t         B0_OS_Electron_DEC;
   Float_t         B0_OS_Electron_PROB;
   Short_t         B0_OS_Kaon_DEC;
   Float_t         B0_OS_Kaon_PROB;
   Short_t         B0_SS_Kaon_DEC;
   Float_t         B0_SS_Kaon_PROB;
   Short_t         B0_SS_Pion_DEC;
   Float_t         B0_SS_Pion_PROB;
   Short_t         B0_SS_PionBDT_DEC;
   Float_t         B0_SS_PionBDT_PROB;
   Short_t         B0_VtxCharge_DEC;
   Float_t         B0_VtxCharge_PROB;
   Short_t         B0_OS_nnetKaon_DEC;
   Float_t         B0_OS_nnetKaon_PROB;
   Short_t         B0_SS_nnetKaon_DEC;
   Float_t         B0_SS_nnetKaon_PROB;
   Short_t         B0_SS_Proton_DEC;
   Float_t         B0_SS_Proton_PROB;
   Short_t         B0_OS_Charm_DEC;
   Float_t         B0_OS_Charm_PROB;
   Double_t        Dplus_LOKI_ENERGY;
   Double_t        Dplus_LOKI_ETA;
   Double_t        Dplus_LOKI_PHI;
   Double_t        Dplus_ENDVERTEX_X;
   Double_t        Dplus_ENDVERTEX_Y;
   Double_t        Dplus_ENDVERTEX_Z;
   Double_t        Dplus_ENDVERTEX_XERR;
   Double_t        Dplus_ENDVERTEX_YERR;
   Double_t        Dplus_ENDVERTEX_ZERR;
   Double_t        Dplus_ENDVERTEX_CHI2;
   Int_t           Dplus_ENDVERTEX_NDOF;
   Float_t         Dplus_ENDVERTEX_COV_[3][3];
   Double_t        Dplus_OWNPV_X;
   Double_t        Dplus_OWNPV_Y;
   Double_t        Dplus_OWNPV_Z;
   Double_t        Dplus_OWNPV_XERR;
   Double_t        Dplus_OWNPV_YERR;
   Double_t        Dplus_OWNPV_ZERR;
   Double_t        Dplus_OWNPV_CHI2;
   Int_t           Dplus_OWNPV_NDOF;
   Float_t         Dplus_OWNPV_COV_[3][3];
   Double_t        Dplus_IP_OWNPV;
   Double_t        Dplus_IPCHI2_OWNPV;
   Double_t        Dplus_FD_OWNPV;
   Double_t        Dplus_FDCHI2_OWNPV;
   Double_t        Dplus_DIRA_OWNPV;
   Double_t        Dplus_ORIVX_X;
   Double_t        Dplus_ORIVX_Y;
   Double_t        Dplus_ORIVX_Z;
   Double_t        Dplus_ORIVX_XERR;
   Double_t        Dplus_ORIVX_YERR;
   Double_t        Dplus_ORIVX_ZERR;
   Double_t        Dplus_ORIVX_CHI2;
   Int_t           Dplus_ORIVX_NDOF;
   Float_t         Dplus_ORIVX_COV_[3][3];
   Double_t        Dplus_FD_ORIVX;
   Double_t        Dplus_FDCHI2_ORIVX;
   Double_t        Dplus_DIRA_ORIVX;
   Double_t        Dplus_P;
   Double_t        Dplus_PT;
   Double_t        Dplus_PE;
   Double_t        Dplus_PX;
   Double_t        Dplus_PY;
   Double_t        Dplus_PZ;
   Double_t        Dplus_MM;
   Double_t        Dplus_MMERR;
   Double_t        Dplus_M;
   Int_t           Dplus_ID;
   Double_t        Dplus_TAU;
   Double_t        Dplus_TAUERR;
   Double_t        Dplus_TAUCHI2;
   Double_t        Dplus_X;
   Double_t        Dplus_Y;
   Double_t        Dplus_LOKI_VertexSeparation_CHI2;
   Double_t        Dplus_Kminus_or_piminus_LOKI_ENERGY;
   Double_t        Dplus_Kminus_or_piminus_LOKI_ETA;
   Double_t        Dplus_Kminus_or_piminus_LOKI_PHI;
   Double_t        Dplus_Kminus_or_piminus_OWNPV_X;
   Double_t        Dplus_Kminus_or_piminus_OWNPV_Y;
   Double_t        Dplus_Kminus_or_piminus_OWNPV_Z;
   Double_t        Dplus_Kminus_or_piminus_OWNPV_XERR;
   Double_t        Dplus_Kminus_or_piminus_OWNPV_YERR;
   Double_t        Dplus_Kminus_or_piminus_OWNPV_ZERR;
   Double_t        Dplus_Kminus_or_piminus_OWNPV_CHI2;
   Int_t           Dplus_Kminus_or_piminus_OWNPV_NDOF;
   Float_t         Dplus_Kminus_or_piminus_OWNPV_COV_[3][3];
   Double_t        Dplus_Kminus_or_piminus_IP_OWNPV;
   Double_t        Dplus_Kminus_or_piminus_IPCHI2_OWNPV;
   Double_t        Dplus_Kminus_or_piminus_ORIVX_X;
   Double_t        Dplus_Kminus_or_piminus_ORIVX_Y;
   Double_t        Dplus_Kminus_or_piminus_ORIVX_Z;
   Double_t        Dplus_Kminus_or_piminus_ORIVX_XERR;
   Double_t        Dplus_Kminus_or_piminus_ORIVX_YERR;
   Double_t        Dplus_Kminus_or_piminus_ORIVX_ZERR;
   Double_t        Dplus_Kminus_or_piminus_ORIVX_CHI2;
   Int_t           Dplus_Kminus_or_piminus_ORIVX_NDOF;
   Float_t         Dplus_Kminus_or_piminus_ORIVX_COV_[3][3];
   Double_t        Dplus_Kminus_or_piminus_P;
   Double_t        Dplus_Kminus_or_piminus_PT;
   Double_t        Dplus_Kminus_or_piminus_PE;
   Double_t        Dplus_Kminus_or_piminus_PX;
   Double_t        Dplus_Kminus_or_piminus_PY;
   Double_t        Dplus_Kminus_or_piminus_PZ;
   Double_t        Dplus_Kminus_or_piminus_M;
   Int_t           Dplus_Kminus_or_piminus_ID;
   Double_t        Dplus_Kminus_or_piminus_PIDe;
   Double_t        Dplus_Kminus_or_piminus_PIDmu;
   Double_t        Dplus_Kminus_or_piminus_PIDK;
   Double_t        Dplus_Kminus_or_piminus_PIDp;
   Double_t        Dplus_Kminus_or_piminus_ProbNNe;
   Double_t        Dplus_Kminus_or_piminus_ProbNNk;
   Double_t        Dplus_Kminus_or_piminus_ProbNNp;
   Double_t        Dplus_Kminus_or_piminus_ProbNNpi;
   Double_t        Dplus_Kminus_or_piminus_ProbNNmu;
   Double_t        Dplus_Kminus_or_piminus_ProbNNghost;
   Bool_t          Dplus_Kminus_or_piminus_hasMuon;
   Bool_t          Dplus_Kminus_or_piminus_isMuon;
   Bool_t          Dplus_Kminus_or_piminus_hasRich;
   Bool_t          Dplus_Kminus_or_piminus_hasCalo;
   Bool_t          Dplus_Kminus_or_piminus_UsedRichAerogel;
   Bool_t          Dplus_Kminus_or_piminus_UsedRich1Gas;
   Bool_t          Dplus_Kminus_or_piminus_UsedRich2Gas;
   Bool_t          Dplus_Kminus_or_piminus_RichAboveElThres;
   Bool_t          Dplus_Kminus_or_piminus_RichAboveMuThres;
   Bool_t          Dplus_Kminus_or_piminus_RichAbovePiThres;
   Bool_t          Dplus_Kminus_or_piminus_RichAboveKaThres;
   Bool_t          Dplus_Kminus_or_piminus_RichAbovePrThres;
   Double_t        Dplus_Kminus_or_piminus_RichDLLe;
   Double_t        Dplus_Kminus_or_piminus_RichDLLmu;
   Double_t        Dplus_Kminus_or_piminus_RichDLLpi;
   Double_t        Dplus_Kminus_or_piminus_RichDLLk;
   Double_t        Dplus_Kminus_or_piminus_RichDLLp;
   Double_t        Dplus_Kminus_or_piminus_RichDLLbt;
   Bool_t          Dplus_Kminus_or_piminus_InAccMuon;
   Bool_t          Dplus_Kminus_or_piminus_isMuonLoose;
   Double_t        Dplus_Kminus_or_piminus_MuonMuLL;
   Double_t        Dplus_Kminus_or_piminus_MuonBkgLL;
   Int_t           Dplus_Kminus_or_piminus_MuonNShared;
   Bool_t          Dplus_Kminus_or_piminus_InAccEcal;
   Double_t        Dplus_Kminus_or_piminus_CaloEcalE;
   Double_t        Dplus_Kminus_or_piminus_EcalPIDe;
   Double_t        Dplus_Kminus_or_piminus_EcalPIDmu;
   Bool_t          Dplus_Kminus_or_piminus_InAccHcal;
   Double_t        Dplus_Kminus_or_piminus_CaloHcalE;
   Double_t        Dplus_Kminus_or_piminus_HcalPIDe;
   Double_t        Dplus_Kminus_or_piminus_HcalPIDmu;
   Bool_t          Dplus_Kminus_or_piminus_InAccPrs;
   Double_t        Dplus_Kminus_or_piminus_PrsPIDe;
   Double_t        Dplus_Kminus_or_piminus_CaloPrsE;
   Bool_t          Dplus_Kminus_or_piminus_InAccSpd;
   Double_t        Dplus_Kminus_or_piminus_CaloSpdE;
   Bool_t          Dplus_Kminus_or_piminus_InAccBrem;
   Double_t        Dplus_Kminus_or_piminus_BremPIDe;
   Double_t        Dplus_Kminus_or_piminus_VeloCharge;
   Int_t           Dplus_Kminus_or_piminus_TRACK_Type;
   Int_t           Dplus_Kminus_or_piminus_TRACK_Key;
   Double_t        Dplus_Kminus_or_piminus_TRACK_CHI2;
   Int_t           Dplus_Kminus_or_piminus_TRACK_NDOF;
   Double_t        Dplus_Kminus_or_piminus_TRACK_CHI2NDOF;
   Double_t        Dplus_Kminus_or_piminus_TRACK_PCHI2;
   Double_t        Dplus_Kminus_or_piminus_TRACK_VeloCHI2NDOF;
   Double_t        Dplus_Kminus_or_piminus_TRACK_TCHI2NDOF;
   Double_t        Dplus_Kminus_or_piminus_VELO_UTID;
   Double_t        Dplus_Kminus_or_piminus_TRACK_FirstMeasurementX;
   Double_t        Dplus_Kminus_or_piminus_TRACK_FirstMeasurementY;
   Double_t        Dplus_Kminus_or_piminus_TRACK_FirstMeasurementZ;
   Double_t        Dplus_Kminus_or_piminus_TRACK_MatchCHI2;
   Double_t        Dplus_Kminus_or_piminus_TRACK_GhostProb;
   Double_t        Dplus_Kminus_or_piminus_TRACK_CloneDist;
   Double_t        Dplus_Kminus_or_piminus_TRACK_Likelihood;
   Double_t        Dplus_Kminus_or_piminus_X;
   Double_t        Dplus_Kminus_or_piminus_Y;
   Double_t        Dplus_piplus_or_Kplus_One_LOKI_ENERGY;
   Double_t        Dplus_piplus_or_Kplus_One_LOKI_ETA;
   Double_t        Dplus_piplus_or_Kplus_One_LOKI_PHI;
   Double_t        Dplus_piplus_or_Kplus_One_OWNPV_X;
   Double_t        Dplus_piplus_or_Kplus_One_OWNPV_Y;
   Double_t        Dplus_piplus_or_Kplus_One_OWNPV_Z;
   Double_t        Dplus_piplus_or_Kplus_One_OWNPV_XERR;
   Double_t        Dplus_piplus_or_Kplus_One_OWNPV_YERR;
   Double_t        Dplus_piplus_or_Kplus_One_OWNPV_ZERR;
   Double_t        Dplus_piplus_or_Kplus_One_OWNPV_CHI2;
   Int_t           Dplus_piplus_or_Kplus_One_OWNPV_NDOF;
   Float_t         Dplus_piplus_or_Kplus_One_OWNPV_COV_[3][3];
   Double_t        Dplus_piplus_or_Kplus_One_IP_OWNPV;
   Double_t        Dplus_piplus_or_Kplus_One_IPCHI2_OWNPV;
   Double_t        Dplus_piplus_or_Kplus_One_ORIVX_X;
   Double_t        Dplus_piplus_or_Kplus_One_ORIVX_Y;
   Double_t        Dplus_piplus_or_Kplus_One_ORIVX_Z;
   Double_t        Dplus_piplus_or_Kplus_One_ORIVX_XERR;
   Double_t        Dplus_piplus_or_Kplus_One_ORIVX_YERR;
   Double_t        Dplus_piplus_or_Kplus_One_ORIVX_ZERR;
   Double_t        Dplus_piplus_or_Kplus_One_ORIVX_CHI2;
   Int_t           Dplus_piplus_or_Kplus_One_ORIVX_NDOF;
   Float_t         Dplus_piplus_or_Kplus_One_ORIVX_COV_[3][3];
   Double_t        Dplus_piplus_or_Kplus_One_P;
   Double_t        Dplus_piplus_or_Kplus_One_PT;
   Double_t        Dplus_piplus_or_Kplus_One_PE;
   Double_t        Dplus_piplus_or_Kplus_One_PX;
   Double_t        Dplus_piplus_or_Kplus_One_PY;
   Double_t        Dplus_piplus_or_Kplus_One_PZ;
   Double_t        Dplus_piplus_or_Kplus_One_M;
   Int_t           Dplus_piplus_or_Kplus_One_ID;
   Double_t        Dplus_piplus_or_Kplus_One_PIDe;
   Double_t        Dplus_piplus_or_Kplus_One_PIDmu;
   Double_t        Dplus_piplus_or_Kplus_One_PIDK;
   Double_t        Dplus_piplus_or_Kplus_One_PIDp;
   Double_t        Dplus_piplus_or_Kplus_One_ProbNNe;
   Double_t        Dplus_piplus_or_Kplus_One_ProbNNk;
   Double_t        Dplus_piplus_or_Kplus_One_ProbNNp;
   Double_t        Dplus_piplus_or_Kplus_One_ProbNNpi;
   Double_t        Dplus_piplus_or_Kplus_One_ProbNNmu;
   Double_t        Dplus_piplus_or_Kplus_One_ProbNNghost;
   Bool_t          Dplus_piplus_or_Kplus_One_hasMuon;
   Bool_t          Dplus_piplus_or_Kplus_One_isMuon;
   Bool_t          Dplus_piplus_or_Kplus_One_hasRich;
   Bool_t          Dplus_piplus_or_Kplus_One_hasCalo;
   Bool_t          Dplus_piplus_or_Kplus_One_UsedRichAerogel;
   Bool_t          Dplus_piplus_or_Kplus_One_UsedRich1Gas;
   Bool_t          Dplus_piplus_or_Kplus_One_UsedRich2Gas;
   Bool_t          Dplus_piplus_or_Kplus_One_RichAboveElThres;
   Bool_t          Dplus_piplus_or_Kplus_One_RichAboveMuThres;
   Bool_t          Dplus_piplus_or_Kplus_One_RichAbovePiThres;
   Bool_t          Dplus_piplus_or_Kplus_One_RichAboveKaThres;
   Bool_t          Dplus_piplus_or_Kplus_One_RichAbovePrThres;
   Double_t        Dplus_piplus_or_Kplus_One_RichDLLe;
   Double_t        Dplus_piplus_or_Kplus_One_RichDLLmu;
   Double_t        Dplus_piplus_or_Kplus_One_RichDLLpi;
   Double_t        Dplus_piplus_or_Kplus_One_RichDLLk;
   Double_t        Dplus_piplus_or_Kplus_One_RichDLLp;
   Double_t        Dplus_piplus_or_Kplus_One_RichDLLbt;
   Bool_t          Dplus_piplus_or_Kplus_One_InAccMuon;
   Bool_t          Dplus_piplus_or_Kplus_One_isMuonLoose;
   Double_t        Dplus_piplus_or_Kplus_One_MuonMuLL;
   Double_t        Dplus_piplus_or_Kplus_One_MuonBkgLL;
   Int_t           Dplus_piplus_or_Kplus_One_MuonNShared;
   Bool_t          Dplus_piplus_or_Kplus_One_InAccEcal;
   Double_t        Dplus_piplus_or_Kplus_One_CaloEcalE;
   Double_t        Dplus_piplus_or_Kplus_One_EcalPIDe;
   Double_t        Dplus_piplus_or_Kplus_One_EcalPIDmu;
   Bool_t          Dplus_piplus_or_Kplus_One_InAccHcal;
   Double_t        Dplus_piplus_or_Kplus_One_CaloHcalE;
   Double_t        Dplus_piplus_or_Kplus_One_HcalPIDe;
   Double_t        Dplus_piplus_or_Kplus_One_HcalPIDmu;
   Bool_t          Dplus_piplus_or_Kplus_One_InAccPrs;
   Double_t        Dplus_piplus_or_Kplus_One_PrsPIDe;
   Double_t        Dplus_piplus_or_Kplus_One_CaloPrsE;
   Bool_t          Dplus_piplus_or_Kplus_One_InAccSpd;
   Double_t        Dplus_piplus_or_Kplus_One_CaloSpdE;
   Bool_t          Dplus_piplus_or_Kplus_One_InAccBrem;
   Double_t        Dplus_piplus_or_Kplus_One_BremPIDe;
   Double_t        Dplus_piplus_or_Kplus_One_VeloCharge;
   Int_t           Dplus_piplus_or_Kplus_One_TRACK_Type;
   Int_t           Dplus_piplus_or_Kplus_One_TRACK_Key;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_CHI2;
   Int_t           Dplus_piplus_or_Kplus_One_TRACK_NDOF;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_CHI2NDOF;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_PCHI2;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_VeloCHI2NDOF;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_TCHI2NDOF;
   Double_t        Dplus_piplus_or_Kplus_One_VELO_UTID;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementX;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementY;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementZ;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_MatchCHI2;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_GhostProb;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_CloneDist;
   Double_t        Dplus_piplus_or_Kplus_One_TRACK_Likelihood;
   Double_t        Dplus_piplus_or_Kplus_One_X;
   Double_t        Dplus_piplus_or_Kplus_One_Y;
   Double_t        Dplus_piplus_or_Kplus_Two_LOKI_ENERGY;
   Double_t        Dplus_piplus_or_Kplus_Two_LOKI_ETA;
   Double_t        Dplus_piplus_or_Kplus_Two_LOKI_PHI;
   Double_t        Dplus_piplus_or_Kplus_Two_OWNPV_X;
   Double_t        Dplus_piplus_or_Kplus_Two_OWNPV_Y;
   Double_t        Dplus_piplus_or_Kplus_Two_OWNPV_Z;
   Double_t        Dplus_piplus_or_Kplus_Two_OWNPV_XERR;
   Double_t        Dplus_piplus_or_Kplus_Two_OWNPV_YERR;
   Double_t        Dplus_piplus_or_Kplus_Two_OWNPV_ZERR;
   Double_t        Dplus_piplus_or_Kplus_Two_OWNPV_CHI2;
   Int_t           Dplus_piplus_or_Kplus_Two_OWNPV_NDOF;
   Float_t         Dplus_piplus_or_Kplus_Two_OWNPV_COV_[3][3];
   Double_t        Dplus_piplus_or_Kplus_Two_IP_OWNPV;
   Double_t        Dplus_piplus_or_Kplus_Two_IPCHI2_OWNPV;
   Double_t        Dplus_piplus_or_Kplus_Two_ORIVX_X;
   Double_t        Dplus_piplus_or_Kplus_Two_ORIVX_Y;
   Double_t        Dplus_piplus_or_Kplus_Two_ORIVX_Z;
   Double_t        Dplus_piplus_or_Kplus_Two_ORIVX_XERR;
   Double_t        Dplus_piplus_or_Kplus_Two_ORIVX_YERR;
   Double_t        Dplus_piplus_or_Kplus_Two_ORIVX_ZERR;
   Double_t        Dplus_piplus_or_Kplus_Two_ORIVX_CHI2;
   Int_t           Dplus_piplus_or_Kplus_Two_ORIVX_NDOF;
   Float_t         Dplus_piplus_or_Kplus_Two_ORIVX_COV_[3][3];
   Double_t        Dplus_piplus_or_Kplus_Two_P;
   Double_t        Dplus_piplus_or_Kplus_Two_PT;
   Double_t        Dplus_piplus_or_Kplus_Two_PE;
   Double_t        Dplus_piplus_or_Kplus_Two_PX;
   Double_t        Dplus_piplus_or_Kplus_Two_PY;
   Double_t        Dplus_piplus_or_Kplus_Two_PZ;
   Double_t        Dplus_piplus_or_Kplus_Two_M;
   Int_t           Dplus_piplus_or_Kplus_Two_ID;
   Double_t        Dplus_piplus_or_Kplus_Two_PIDe;
   Double_t        Dplus_piplus_or_Kplus_Two_PIDmu;
   Double_t        Dplus_piplus_or_Kplus_Two_PIDK;
   Double_t        Dplus_piplus_or_Kplus_Two_PIDp;
   Double_t        Dplus_piplus_or_Kplus_Two_ProbNNe;
   Double_t        Dplus_piplus_or_Kplus_Two_ProbNNk;
   Double_t        Dplus_piplus_or_Kplus_Two_ProbNNp;
   Double_t        Dplus_piplus_or_Kplus_Two_ProbNNpi;
   Double_t        Dplus_piplus_or_Kplus_Two_ProbNNmu;
   Double_t        Dplus_piplus_or_Kplus_Two_ProbNNghost;
   Bool_t          Dplus_piplus_or_Kplus_Two_hasMuon;
   Bool_t          Dplus_piplus_or_Kplus_Two_isMuon;
   Bool_t          Dplus_piplus_or_Kplus_Two_hasRich;
   Bool_t          Dplus_piplus_or_Kplus_Two_hasCalo;
   Bool_t          Dplus_piplus_or_Kplus_Two_UsedRichAerogel;
   Bool_t          Dplus_piplus_or_Kplus_Two_UsedRich1Gas;
   Bool_t          Dplus_piplus_or_Kplus_Two_UsedRich2Gas;
   Bool_t          Dplus_piplus_or_Kplus_Two_RichAboveElThres;
   Bool_t          Dplus_piplus_or_Kplus_Two_RichAboveMuThres;
   Bool_t          Dplus_piplus_or_Kplus_Two_RichAbovePiThres;
   Bool_t          Dplus_piplus_or_Kplus_Two_RichAboveKaThres;
   Bool_t          Dplus_piplus_or_Kplus_Two_RichAbovePrThres;
   Double_t        Dplus_piplus_or_Kplus_Two_RichDLLe;
   Double_t        Dplus_piplus_or_Kplus_Two_RichDLLmu;
   Double_t        Dplus_piplus_or_Kplus_Two_RichDLLpi;
   Double_t        Dplus_piplus_or_Kplus_Two_RichDLLk;
   Double_t        Dplus_piplus_or_Kplus_Two_RichDLLp;
   Double_t        Dplus_piplus_or_Kplus_Two_RichDLLbt;
   Bool_t          Dplus_piplus_or_Kplus_Two_InAccMuon;
   Bool_t          Dplus_piplus_or_Kplus_Two_isMuonLoose;
   Double_t        Dplus_piplus_or_Kplus_Two_MuonMuLL;
   Double_t        Dplus_piplus_or_Kplus_Two_MuonBkgLL;
   Int_t           Dplus_piplus_or_Kplus_Two_MuonNShared;
   Bool_t          Dplus_piplus_or_Kplus_Two_InAccEcal;
   Double_t        Dplus_piplus_or_Kplus_Two_CaloEcalE;
   Double_t        Dplus_piplus_or_Kplus_Two_EcalPIDe;
   Double_t        Dplus_piplus_or_Kplus_Two_EcalPIDmu;
   Bool_t          Dplus_piplus_or_Kplus_Two_InAccHcal;
   Double_t        Dplus_piplus_or_Kplus_Two_CaloHcalE;
   Double_t        Dplus_piplus_or_Kplus_Two_HcalPIDe;
   Double_t        Dplus_piplus_or_Kplus_Two_HcalPIDmu;
   Bool_t          Dplus_piplus_or_Kplus_Two_InAccPrs;
   Double_t        Dplus_piplus_or_Kplus_Two_PrsPIDe;
   Double_t        Dplus_piplus_or_Kplus_Two_CaloPrsE;
   Bool_t          Dplus_piplus_or_Kplus_Two_InAccSpd;
   Double_t        Dplus_piplus_or_Kplus_Two_CaloSpdE;
   Bool_t          Dplus_piplus_or_Kplus_Two_InAccBrem;
   Double_t        Dplus_piplus_or_Kplus_Two_BremPIDe;
   Double_t        Dplus_piplus_or_Kplus_Two_VeloCharge;
   Int_t           Dplus_piplus_or_Kplus_Two_TRACK_Type;
   Int_t           Dplus_piplus_or_Kplus_Two_TRACK_Key;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_CHI2;
   Int_t           Dplus_piplus_or_Kplus_Two_TRACK_NDOF;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_CHI2NDOF;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_PCHI2;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_VeloCHI2NDOF;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_TCHI2NDOF;
   Double_t        Dplus_piplus_or_Kplus_Two_VELO_UTID;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementX;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementY;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementZ;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_MatchCHI2;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_GhostProb;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_CloneDist;
   Double_t        Dplus_piplus_or_Kplus_Two_TRACK_Likelihood;
   Double_t        Dplus_piplus_or_Kplus_Two_X;
   Double_t        Dplus_piplus_or_Kplus_Two_Y;
   Double_t        Dminus_LOKI_ENERGY;
   Double_t        Dminus_LOKI_ETA;
   Double_t        Dminus_LOKI_PHI;
   Double_t        Dminus_ENDVERTEX_X;
   Double_t        Dminus_ENDVERTEX_Y;
   Double_t        Dminus_ENDVERTEX_Z;
   Double_t        Dminus_ENDVERTEX_XERR;
   Double_t        Dminus_ENDVERTEX_YERR;
   Double_t        Dminus_ENDVERTEX_ZERR;
   Double_t        Dminus_ENDVERTEX_CHI2;
   Int_t           Dminus_ENDVERTEX_NDOF;
   Float_t         Dminus_ENDVERTEX_COV_[3][3];
   Double_t        Dminus_OWNPV_X;
   Double_t        Dminus_OWNPV_Y;
   Double_t        Dminus_OWNPV_Z;
   Double_t        Dminus_OWNPV_XERR;
   Double_t        Dminus_OWNPV_YERR;
   Double_t        Dminus_OWNPV_ZERR;
   Double_t        Dminus_OWNPV_CHI2;
   Int_t           Dminus_OWNPV_NDOF;
   Float_t         Dminus_OWNPV_COV_[3][3];
   Double_t        Dminus_IP_OWNPV;
   Double_t        Dminus_IPCHI2_OWNPV;
   Double_t        Dminus_FD_OWNPV;
   Double_t        Dminus_FDCHI2_OWNPV;
   Double_t        Dminus_DIRA_OWNPV;
   Double_t        Dminus_ORIVX_X;
   Double_t        Dminus_ORIVX_Y;
   Double_t        Dminus_ORIVX_Z;
   Double_t        Dminus_ORIVX_XERR;
   Double_t        Dminus_ORIVX_YERR;
   Double_t        Dminus_ORIVX_ZERR;
   Double_t        Dminus_ORIVX_CHI2;
   Int_t           Dminus_ORIVX_NDOF;
   Float_t         Dminus_ORIVX_COV_[3][3];
   Double_t        Dminus_FD_ORIVX;
   Double_t        Dminus_FDCHI2_ORIVX;
   Double_t        Dminus_DIRA_ORIVX;
   Double_t        Dminus_P;
   Double_t        Dminus_PT;
   Double_t        Dminus_PE;
   Double_t        Dminus_PX;
   Double_t        Dminus_PY;
   Double_t        Dminus_PZ;
   Double_t        Dminus_MM;
   Double_t        Dminus_MMERR;
   Double_t        Dminus_M;
   Int_t           Dminus_ID;
   Double_t        Dminus_TAU;
   Double_t        Dminus_TAUERR;
   Double_t        Dminus_TAUCHI2;
   Double_t        Dminus_X;
   Double_t        Dminus_Y;
   Double_t        Dminus_LOKI_VertexSeparation_CHI2;
   Double_t        Dminus_Kplus_or_piplus_LOKI_ENERGY;
   Double_t        Dminus_Kplus_or_piplus_LOKI_ETA;
   Double_t        Dminus_Kplus_or_piplus_LOKI_PHI;
   Double_t        Dminus_Kplus_or_piplus_OWNPV_X;
   Double_t        Dminus_Kplus_or_piplus_OWNPV_Y;
   Double_t        Dminus_Kplus_or_piplus_OWNPV_Z;
   Double_t        Dminus_Kplus_or_piplus_OWNPV_XERR;
   Double_t        Dminus_Kplus_or_piplus_OWNPV_YERR;
   Double_t        Dminus_Kplus_or_piplus_OWNPV_ZERR;
   Double_t        Dminus_Kplus_or_piplus_OWNPV_CHI2;
   Int_t           Dminus_Kplus_or_piplus_OWNPV_NDOF;
   Float_t         Dminus_Kplus_or_piplus_OWNPV_COV_[3][3];
   Double_t        Dminus_Kplus_or_piplus_IP_OWNPV;
   Double_t        Dminus_Kplus_or_piplus_IPCHI2_OWNPV;
   Double_t        Dminus_Kplus_or_piplus_ORIVX_X;
   Double_t        Dminus_Kplus_or_piplus_ORIVX_Y;
   Double_t        Dminus_Kplus_or_piplus_ORIVX_Z;
   Double_t        Dminus_Kplus_or_piplus_ORIVX_XERR;
   Double_t        Dminus_Kplus_or_piplus_ORIVX_YERR;
   Double_t        Dminus_Kplus_or_piplus_ORIVX_ZERR;
   Double_t        Dminus_Kplus_or_piplus_ORIVX_CHI2;
   Int_t           Dminus_Kplus_or_piplus_ORIVX_NDOF;
   Float_t         Dminus_Kplus_or_piplus_ORIVX_COV_[3][3];
   Double_t        Dminus_Kplus_or_piplus_P;
   Double_t        Dminus_Kplus_or_piplus_PT;
   Double_t        Dminus_Kplus_or_piplus_PE;
   Double_t        Dminus_Kplus_or_piplus_PX;
   Double_t        Dminus_Kplus_or_piplus_PY;
   Double_t        Dminus_Kplus_or_piplus_PZ;
   Double_t        Dminus_Kplus_or_piplus_M;
   Int_t           Dminus_Kplus_or_piplus_ID;
   Double_t        Dminus_Kplus_or_piplus_PIDe;
   Double_t        Dminus_Kplus_or_piplus_PIDmu;
   Double_t        Dminus_Kplus_or_piplus_PIDK;
   Double_t        Dminus_Kplus_or_piplus_PIDp;
   Double_t        Dminus_Kplus_or_piplus_ProbNNe;
   Double_t        Dminus_Kplus_or_piplus_ProbNNk;
   Double_t        Dminus_Kplus_or_piplus_ProbNNp;
   Double_t        Dminus_Kplus_or_piplus_ProbNNpi;
   Double_t        Dminus_Kplus_or_piplus_ProbNNmu;
   Double_t        Dminus_Kplus_or_piplus_ProbNNghost;
   Bool_t          Dminus_Kplus_or_piplus_hasMuon;
   Bool_t          Dminus_Kplus_or_piplus_isMuon;
   Bool_t          Dminus_Kplus_or_piplus_hasRich;
   Bool_t          Dminus_Kplus_or_piplus_hasCalo;
   Bool_t          Dminus_Kplus_or_piplus_UsedRichAerogel;
   Bool_t          Dminus_Kplus_or_piplus_UsedRich1Gas;
   Bool_t          Dminus_Kplus_or_piplus_UsedRich2Gas;
   Bool_t          Dminus_Kplus_or_piplus_RichAboveElThres;
   Bool_t          Dminus_Kplus_or_piplus_RichAboveMuThres;
   Bool_t          Dminus_Kplus_or_piplus_RichAbovePiThres;
   Bool_t          Dminus_Kplus_or_piplus_RichAboveKaThres;
   Bool_t          Dminus_Kplus_or_piplus_RichAbovePrThres;
   Double_t        Dminus_Kplus_or_piplus_RichDLLe;
   Double_t        Dminus_Kplus_or_piplus_RichDLLmu;
   Double_t        Dminus_Kplus_or_piplus_RichDLLpi;
   Double_t        Dminus_Kplus_or_piplus_RichDLLk;
   Double_t        Dminus_Kplus_or_piplus_RichDLLp;
   Double_t        Dminus_Kplus_or_piplus_RichDLLbt;
   Bool_t          Dminus_Kplus_or_piplus_InAccMuon;
   Bool_t          Dminus_Kplus_or_piplus_isMuonLoose;
   Double_t        Dminus_Kplus_or_piplus_MuonMuLL;
   Double_t        Dminus_Kplus_or_piplus_MuonBkgLL;
   Int_t           Dminus_Kplus_or_piplus_MuonNShared;
   Bool_t          Dminus_Kplus_or_piplus_InAccEcal;
   Double_t        Dminus_Kplus_or_piplus_CaloEcalE;
   Double_t        Dminus_Kplus_or_piplus_EcalPIDe;
   Double_t        Dminus_Kplus_or_piplus_EcalPIDmu;
   Bool_t          Dminus_Kplus_or_piplus_InAccHcal;
   Double_t        Dminus_Kplus_or_piplus_CaloHcalE;
   Double_t        Dminus_Kplus_or_piplus_HcalPIDe;
   Double_t        Dminus_Kplus_or_piplus_HcalPIDmu;
   Bool_t          Dminus_Kplus_or_piplus_InAccPrs;
   Double_t        Dminus_Kplus_or_piplus_PrsPIDe;
   Double_t        Dminus_Kplus_or_piplus_CaloPrsE;
   Bool_t          Dminus_Kplus_or_piplus_InAccSpd;
   Double_t        Dminus_Kplus_or_piplus_CaloSpdE;
   Bool_t          Dminus_Kplus_or_piplus_InAccBrem;
   Double_t        Dminus_Kplus_or_piplus_BremPIDe;
   Double_t        Dminus_Kplus_or_piplus_VeloCharge;
   Int_t           Dminus_Kplus_or_piplus_TRACK_Type;
   Int_t           Dminus_Kplus_or_piplus_TRACK_Key;
   Double_t        Dminus_Kplus_or_piplus_TRACK_CHI2;
   Int_t           Dminus_Kplus_or_piplus_TRACK_NDOF;
   Double_t        Dminus_Kplus_or_piplus_TRACK_CHI2NDOF;
   Double_t        Dminus_Kplus_or_piplus_TRACK_PCHI2;
   Double_t        Dminus_Kplus_or_piplus_TRACK_VeloCHI2NDOF;
   Double_t        Dminus_Kplus_or_piplus_TRACK_TCHI2NDOF;
   Double_t        Dminus_Kplus_or_piplus_VELO_UTID;
   Double_t        Dminus_Kplus_or_piplus_TRACK_FirstMeasurementX;
   Double_t        Dminus_Kplus_or_piplus_TRACK_FirstMeasurementY;
   Double_t        Dminus_Kplus_or_piplus_TRACK_FirstMeasurementZ;
   Double_t        Dminus_Kplus_or_piplus_TRACK_MatchCHI2;
   Double_t        Dminus_Kplus_or_piplus_TRACK_GhostProb;
   Double_t        Dminus_Kplus_or_piplus_TRACK_CloneDist;
   Double_t        Dminus_Kplus_or_piplus_TRACK_Likelihood;
   Double_t        Dminus_Kplus_or_piplus_X;
   Double_t        Dminus_Kplus_or_piplus_Y;
   Double_t        Dminus_piminus_or_Kminus_One_LOKI_ENERGY;
   Double_t        Dminus_piminus_or_Kminus_One_LOKI_ETA;
   Double_t        Dminus_piminus_or_Kminus_One_LOKI_PHI;
   Double_t        Dminus_piminus_or_Kminus_One_OWNPV_X;
   Double_t        Dminus_piminus_or_Kminus_One_OWNPV_Y;
   Double_t        Dminus_piminus_or_Kminus_One_OWNPV_Z;
   Double_t        Dminus_piminus_or_Kminus_One_OWNPV_XERR;
   Double_t        Dminus_piminus_or_Kminus_One_OWNPV_YERR;
   Double_t        Dminus_piminus_or_Kminus_One_OWNPV_ZERR;
   Double_t        Dminus_piminus_or_Kminus_One_OWNPV_CHI2;
   Int_t           Dminus_piminus_or_Kminus_One_OWNPV_NDOF;
   Float_t         Dminus_piminus_or_Kminus_One_OWNPV_COV_[3][3];
   Double_t        Dminus_piminus_or_Kminus_One_IP_OWNPV;
   Double_t        Dminus_piminus_or_Kminus_One_IPCHI2_OWNPV;
   Double_t        Dminus_piminus_or_Kminus_One_ORIVX_X;
   Double_t        Dminus_piminus_or_Kminus_One_ORIVX_Y;
   Double_t        Dminus_piminus_or_Kminus_One_ORIVX_Z;
   Double_t        Dminus_piminus_or_Kminus_One_ORIVX_XERR;
   Double_t        Dminus_piminus_or_Kminus_One_ORIVX_YERR;
   Double_t        Dminus_piminus_or_Kminus_One_ORIVX_ZERR;
   Double_t        Dminus_piminus_or_Kminus_One_ORIVX_CHI2;
   Int_t           Dminus_piminus_or_Kminus_One_ORIVX_NDOF;
   Float_t         Dminus_piminus_or_Kminus_One_ORIVX_COV_[3][3];
   Double_t        Dminus_piminus_or_Kminus_One_P;
   Double_t        Dminus_piminus_or_Kminus_One_PT;
   Double_t        Dminus_piminus_or_Kminus_One_PE;
   Double_t        Dminus_piminus_or_Kminus_One_PX;
   Double_t        Dminus_piminus_or_Kminus_One_PY;
   Double_t        Dminus_piminus_or_Kminus_One_PZ;
   Double_t        Dminus_piminus_or_Kminus_One_M;
   Int_t           Dminus_piminus_or_Kminus_One_ID;
   Double_t        Dminus_piminus_or_Kminus_One_PIDe;
   Double_t        Dminus_piminus_or_Kminus_One_PIDmu;
   Double_t        Dminus_piminus_or_Kminus_One_PIDK;
   Double_t        Dminus_piminus_or_Kminus_One_PIDp;
   Double_t        Dminus_piminus_or_Kminus_One_ProbNNe;
   Double_t        Dminus_piminus_or_Kminus_One_ProbNNk;
   Double_t        Dminus_piminus_or_Kminus_One_ProbNNp;
   Double_t        Dminus_piminus_or_Kminus_One_ProbNNpi;
   Double_t        Dminus_piminus_or_Kminus_One_ProbNNmu;
   Double_t        Dminus_piminus_or_Kminus_One_ProbNNghost;
   Bool_t          Dminus_piminus_or_Kminus_One_hasMuon;
   Bool_t          Dminus_piminus_or_Kminus_One_isMuon;
   Bool_t          Dminus_piminus_or_Kminus_One_hasRich;
   Bool_t          Dminus_piminus_or_Kminus_One_hasCalo;
   Bool_t          Dminus_piminus_or_Kminus_One_UsedRichAerogel;
   Bool_t          Dminus_piminus_or_Kminus_One_UsedRich1Gas;
   Bool_t          Dminus_piminus_or_Kminus_One_UsedRich2Gas;
   Bool_t          Dminus_piminus_or_Kminus_One_RichAboveElThres;
   Bool_t          Dminus_piminus_or_Kminus_One_RichAboveMuThres;
   Bool_t          Dminus_piminus_or_Kminus_One_RichAbovePiThres;
   Bool_t          Dminus_piminus_or_Kminus_One_RichAboveKaThres;
   Bool_t          Dminus_piminus_or_Kminus_One_RichAbovePrThres;
   Double_t        Dminus_piminus_or_Kminus_One_RichDLLe;
   Double_t        Dminus_piminus_or_Kminus_One_RichDLLmu;
   Double_t        Dminus_piminus_or_Kminus_One_RichDLLpi;
   Double_t        Dminus_piminus_or_Kminus_One_RichDLLk;
   Double_t        Dminus_piminus_or_Kminus_One_RichDLLp;
   Double_t        Dminus_piminus_or_Kminus_One_RichDLLbt;
   Bool_t          Dminus_piminus_or_Kminus_One_InAccMuon;
   Bool_t          Dminus_piminus_or_Kminus_One_isMuonLoose;
   Double_t        Dminus_piminus_or_Kminus_One_MuonMuLL;
   Double_t        Dminus_piminus_or_Kminus_One_MuonBkgLL;
   Int_t           Dminus_piminus_or_Kminus_One_MuonNShared;
   Bool_t          Dminus_piminus_or_Kminus_One_InAccEcal;
   Double_t        Dminus_piminus_or_Kminus_One_CaloEcalE;
   Double_t        Dminus_piminus_or_Kminus_One_EcalPIDe;
   Double_t        Dminus_piminus_or_Kminus_One_EcalPIDmu;
   Bool_t          Dminus_piminus_or_Kminus_One_InAccHcal;
   Double_t        Dminus_piminus_or_Kminus_One_CaloHcalE;
   Double_t        Dminus_piminus_or_Kminus_One_HcalPIDe;
   Double_t        Dminus_piminus_or_Kminus_One_HcalPIDmu;
   Bool_t          Dminus_piminus_or_Kminus_One_InAccPrs;
   Double_t        Dminus_piminus_or_Kminus_One_PrsPIDe;
   Double_t        Dminus_piminus_or_Kminus_One_CaloPrsE;
   Bool_t          Dminus_piminus_or_Kminus_One_InAccSpd;
   Double_t        Dminus_piminus_or_Kminus_One_CaloSpdE;
   Bool_t          Dminus_piminus_or_Kminus_One_InAccBrem;
   Double_t        Dminus_piminus_or_Kminus_One_BremPIDe;
   Double_t        Dminus_piminus_or_Kminus_One_VeloCharge;
   Int_t           Dminus_piminus_or_Kminus_One_TRACK_Type;
   Int_t           Dminus_piminus_or_Kminus_One_TRACK_Key;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_CHI2;
   Int_t           Dminus_piminus_or_Kminus_One_TRACK_NDOF;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_CHI2NDOF;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_PCHI2;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_VeloCHI2NDOF;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_TCHI2NDOF;
   Double_t        Dminus_piminus_or_Kminus_One_VELO_UTID;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementX;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementY;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementZ;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_MatchCHI2;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_GhostProb;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_CloneDist;
   Double_t        Dminus_piminus_or_Kminus_One_TRACK_Likelihood;
   Double_t        Dminus_piminus_or_Kminus_One_X;
   Double_t        Dminus_piminus_or_Kminus_One_Y;
   Double_t        Dminus_piminus_or_Kminus_Two_LOKI_ENERGY;
   Double_t        Dminus_piminus_or_Kminus_Two_LOKI_ETA;
   Double_t        Dminus_piminus_or_Kminus_Two_LOKI_PHI;
   Double_t        Dminus_piminus_or_Kminus_Two_OWNPV_X;
   Double_t        Dminus_piminus_or_Kminus_Two_OWNPV_Y;
   Double_t        Dminus_piminus_or_Kminus_Two_OWNPV_Z;
   Double_t        Dminus_piminus_or_Kminus_Two_OWNPV_XERR;
   Double_t        Dminus_piminus_or_Kminus_Two_OWNPV_YERR;
   Double_t        Dminus_piminus_or_Kminus_Two_OWNPV_ZERR;
   Double_t        Dminus_piminus_or_Kminus_Two_OWNPV_CHI2;
   Int_t           Dminus_piminus_or_Kminus_Two_OWNPV_NDOF;
   Float_t         Dminus_piminus_or_Kminus_Two_OWNPV_COV_[3][3];
   Double_t        Dminus_piminus_or_Kminus_Two_IP_OWNPV;
   Double_t        Dminus_piminus_or_Kminus_Two_IPCHI2_OWNPV;
   Double_t        Dminus_piminus_or_Kminus_Two_ORIVX_X;
   Double_t        Dminus_piminus_or_Kminus_Two_ORIVX_Y;
   Double_t        Dminus_piminus_or_Kminus_Two_ORIVX_Z;
   Double_t        Dminus_piminus_or_Kminus_Two_ORIVX_XERR;
   Double_t        Dminus_piminus_or_Kminus_Two_ORIVX_YERR;
   Double_t        Dminus_piminus_or_Kminus_Two_ORIVX_ZERR;
   Double_t        Dminus_piminus_or_Kminus_Two_ORIVX_CHI2;
   Int_t           Dminus_piminus_or_Kminus_Two_ORIVX_NDOF;
   Float_t         Dminus_piminus_or_Kminus_Two_ORIVX_COV_[3][3];
   Double_t        Dminus_piminus_or_Kminus_Two_P;
   Double_t        Dminus_piminus_or_Kminus_Two_PT;
   Double_t        Dminus_piminus_or_Kminus_Two_PE;
   Double_t        Dminus_piminus_or_Kminus_Two_PX;
   Double_t        Dminus_piminus_or_Kminus_Two_PY;
   Double_t        Dminus_piminus_or_Kminus_Two_PZ;
   Double_t        Dminus_piminus_or_Kminus_Two_M;
   Int_t           Dminus_piminus_or_Kminus_Two_ID;
   Double_t        Dminus_piminus_or_Kminus_Two_PIDe;
   Double_t        Dminus_piminus_or_Kminus_Two_PIDmu;
   Double_t        Dminus_piminus_or_Kminus_Two_PIDK;
   Double_t        Dminus_piminus_or_Kminus_Two_PIDp;
   Double_t        Dminus_piminus_or_Kminus_Two_ProbNNe;
   Double_t        Dminus_piminus_or_Kminus_Two_ProbNNk;
   Double_t        Dminus_piminus_or_Kminus_Two_ProbNNp;
   Double_t        Dminus_piminus_or_Kminus_Two_ProbNNpi;
   Double_t        Dminus_piminus_or_Kminus_Two_ProbNNmu;
   Double_t        Dminus_piminus_or_Kminus_Two_ProbNNghost;
   Bool_t          Dminus_piminus_or_Kminus_Two_hasMuon;
   Bool_t          Dminus_piminus_or_Kminus_Two_isMuon;
   Bool_t          Dminus_piminus_or_Kminus_Two_hasRich;
   Bool_t          Dminus_piminus_or_Kminus_Two_hasCalo;
   Bool_t          Dminus_piminus_or_Kminus_Two_UsedRichAerogel;
   Bool_t          Dminus_piminus_or_Kminus_Two_UsedRich1Gas;
   Bool_t          Dminus_piminus_or_Kminus_Two_UsedRich2Gas;
   Bool_t          Dminus_piminus_or_Kminus_Two_RichAboveElThres;
   Bool_t          Dminus_piminus_or_Kminus_Two_RichAboveMuThres;
   Bool_t          Dminus_piminus_or_Kminus_Two_RichAbovePiThres;
   Bool_t          Dminus_piminus_or_Kminus_Two_RichAboveKaThres;
   Bool_t          Dminus_piminus_or_Kminus_Two_RichAbovePrThres;
   Double_t        Dminus_piminus_or_Kminus_Two_RichDLLe;
   Double_t        Dminus_piminus_or_Kminus_Two_RichDLLmu;
   Double_t        Dminus_piminus_or_Kminus_Two_RichDLLpi;
   Double_t        Dminus_piminus_or_Kminus_Two_RichDLLk;
   Double_t        Dminus_piminus_or_Kminus_Two_RichDLLp;
   Double_t        Dminus_piminus_or_Kminus_Two_RichDLLbt;
   Bool_t          Dminus_piminus_or_Kminus_Two_InAccMuon;
   Bool_t          Dminus_piminus_or_Kminus_Two_isMuonLoose;
   Double_t        Dminus_piminus_or_Kminus_Two_MuonMuLL;
   Double_t        Dminus_piminus_or_Kminus_Two_MuonBkgLL;
   Int_t           Dminus_piminus_or_Kminus_Two_MuonNShared;
   Bool_t          Dminus_piminus_or_Kminus_Two_InAccEcal;
   Double_t        Dminus_piminus_or_Kminus_Two_CaloEcalE;
   Double_t        Dminus_piminus_or_Kminus_Two_EcalPIDe;
   Double_t        Dminus_piminus_or_Kminus_Two_EcalPIDmu;
   Bool_t          Dminus_piminus_or_Kminus_Two_InAccHcal;
   Double_t        Dminus_piminus_or_Kminus_Two_CaloHcalE;
   Double_t        Dminus_piminus_or_Kminus_Two_HcalPIDe;
   Double_t        Dminus_piminus_or_Kminus_Two_HcalPIDmu;
   Bool_t          Dminus_piminus_or_Kminus_Two_InAccPrs;
   Double_t        Dminus_piminus_or_Kminus_Two_PrsPIDe;
   Double_t        Dminus_piminus_or_Kminus_Two_CaloPrsE;
   Bool_t          Dminus_piminus_or_Kminus_Two_InAccSpd;
   Double_t        Dminus_piminus_or_Kminus_Two_CaloSpdE;
   Bool_t          Dminus_piminus_or_Kminus_Two_InAccBrem;
   Double_t        Dminus_piminus_or_Kminus_Two_BremPIDe;
   Double_t        Dminus_piminus_or_Kminus_Two_VeloCharge;
   Int_t           Dminus_piminus_or_Kminus_Two_TRACK_Type;
   Int_t           Dminus_piminus_or_Kminus_Two_TRACK_Key;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_CHI2;
   Int_t           Dminus_piminus_or_Kminus_Two_TRACK_NDOF;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_CHI2NDOF;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_PCHI2;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_VeloCHI2NDOF;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_TCHI2NDOF;
   Double_t        Dminus_piminus_or_Kminus_Two_VELO_UTID;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementX;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementY;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementZ;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_MatchCHI2;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_GhostProb;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_CloneDist;
   Double_t        Dminus_piminus_or_Kminus_Two_TRACK_Likelihood;
   Double_t        Dminus_piminus_or_Kminus_Two_X;
   Double_t        Dminus_piminus_or_Kminus_Two_Y;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   UInt_t          BCID;
   Int_t           BCType;
   UInt_t          OdinTCK;
   UInt_t          L0DUTCK;
   UInt_t          HLTTCK;
   ULong64_t       GpsTime;
   Int_t           GpsYear;
   Int_t           GpsMonth;
   Int_t           GpsDay;
   Int_t           GpsHour;
   Int_t           GpsMinute;
   Double_t        GpsSecond;
   Int_t           TriggerType;
   Short_t         Polarity;
   Int_t           nPV;
   Float_t         PVX[9];   //[nPV]
   Float_t         PVY[9];   //[nPV]
   Float_t         PVZ[9];   //[nPV]
   Float_t         PVXERR[9];   //[nPV]
   Float_t         PVYERR[9];   //[nPV]
   Float_t         PVZERR[9];   //[nPV]
   Float_t         PVCHI2[9];   //[nPV]
   Float_t         PVNDOF[9];   //[nPV]
   Float_t         PVNTRACKS[9];   //[nPV]
   Int_t           nPVs;
   Int_t           nTracks;
   Int_t           nLongTracks;
   Int_t           nDownstreamTracks;
   Int_t           nUpstreamTracks;
   Int_t           nVeloTracks;
   Int_t           nTTracks;
   Int_t           nBackTracks;
   Int_t           nRich1Hits;
   Int_t           nRich2Hits;
   Int_t           nVeloClusters;
   Int_t           nITClusters;
   Int_t           nTTClusters;
   Int_t           nOTClusters;
   Int_t           nSPDHits;
   Int_t           nMuonCoordsS0;
   Int_t           nMuonCoordsS1;
   Int_t           nMuonCoordsS2;
   Int_t           nMuonCoordsS3;
   Int_t           nMuonCoordsS4;
   Int_t           nMuonTracks;
   UInt_t          StrippingB02DDBeauty2CharmLineDecision;
   Int_t           L0Global;
   UInt_t          Hlt1Global;
   UInt_t          Hlt2Global;
   Int_t           L0PhysicsDecision;
   Int_t           L0MuonDecision;
   Int_t           L0DiMuonDecision;
   Int_t           L0MuonHighDecision;
   Int_t           L0HadronDecision;
   Int_t           L0ElectronDecision;
   Int_t           L0PhotonDecision;
   UInt_t          L0nSelections;
   Int_t           Hlt1TrackAllL0Decision;
   Int_t           Hlt1TrackAllL0TightDecision;
   Int_t           Hlt1L0AnyDecision;
   Int_t           Hlt1GlobalDecision;
   UInt_t          Hlt1nSelections;
   Int_t           Hlt2GlobalDecision;
   Int_t           Hlt2Topo2BodySimpleDecision;
   Int_t           Hlt2Topo3BodySimpleDecision;
   Int_t           Hlt2Topo4BodySimpleDecision;
   Int_t           Hlt2Topo2BodyBBDTDecision;
   Int_t           Hlt2Topo3BodyBBDTDecision;
   Int_t           Hlt2Topo4BodyBBDTDecision;
   Int_t           Hlt2TopoMu2BodyBBDTDecision;
   Int_t           Hlt2TopoMu3BodyBBDTDecision;
   Int_t           Hlt2TopoMu4BodyBBDTDecision;
   Int_t           Hlt2TopoE2BodyBBDTDecision;
   Int_t           Hlt2TopoE3BodyBBDTDecision;
   Int_t           Hlt2TopoE4BodyBBDTDecision;
   Int_t           Hlt2IncPhiDecision;
   Int_t           Hlt2IncPhiSidebandsDecision;
   UInt_t          Hlt2nSelections;
   Int_t           MaxRoutingBits;
   Float_t         RoutingBits[31];   //[MaxRoutingBits]
   Double_t        obsMassDDPVConst;
   Double_t        obsMassErrDDPVConst;
   Double_t        obsMassPVConst;
   Double_t        obsMassErrPVConst;
   Double_t        obsMassDauOne;
   Double_t        obsMassErrDauOne;
   Double_t        obsMassDauTwo;
   Double_t        obsMassErrDauTwo;
   Double_t        obsMassLokiDDPVConst;
   Double_t        obsMassErrLokiDDPVConst;
   Double_t        obsMassLokiDauOne;
   Double_t        obsMassErrLokiDauOne;
   Double_t        obsMassLokiDauTwo;
   Double_t        obsMassErrLokiDauTwo;
   Double_t        obsMass;
   Double_t        obsMassErr;
   Double_t        obsTime;
   Double_t        obsTimeErr;
   Double_t        varDplusTauSignificance;
   Double_t        varDminusTauSignificance;
   Double_t        varDMinTauSignificance;
   Double_t        varDMaxTauSignificance;
   Double_t        varKSMassHypo_DplusOne;
   Double_t        varKSMassHypo_DplusTwo;
   Double_t        varKSMassHypo_DminusOne;
   Double_t        varKSMassHypo_DminusTwo;
   Double_t        varDplusMassHypo_Kpipi;
   Double_t        varDminusMassHypo_Kpipi;
   Double_t        varDplusMassHypo_KKpi;
   Double_t        varDminusMassHypo_KKpi;
   Double_t        varDplusMassHypo_KpiK;
   Double_t        varDminusMassHypo_KpiK;
   Double_t        varDplusMassHypo_KKK;
   Double_t        varDminusMassHypo_KKK;
   Double_t        varDplusMassHypo_pipipi;
   Double_t        varDminusMassHypo_pipipi;
   Double_t        varDplusMassHypo_pipiK;
   Double_t        varDminusMassHypo_pipiK;
   Double_t        varDplusMassHypo_piKpi;
   Double_t        varDminusMassHypo_piKpi;
   Double_t        varDplusMassHypo_piKK;
   Double_t        varDminusMassHypo_piKK;
   Double_t        varDplusMassHypo_Kppi;
   Double_t        varDminusMassHypo_Kppi;
   Double_t        varDplusMassHypo_Kpip;
   Double_t        varDminusMassHypo_Kpip;
   Double_t        varDplusMassHypo_pKpi;
   Double_t        varDminusMassHypo_pKpi;
   Double_t        varDplusMassHypo_ppiK;
   Double_t        varDminusMassHypo_ppiK;
   Double_t        varDplusMassHypo_pipK;
   Double_t        varDminusMassHypo_pipK;
   Double_t        varDplusMassHypo_piKp;
   Double_t        varDminusMassHypo_piKp;
   Double_t        varDplusMassHypo_ppipi;
   Double_t        varDminusMassHypo_ppipi;
   Double_t        varDplusMassHypo_pippi;
   Double_t        varDminusMassHypo_pippi;
   Double_t        varDplusMassHypo_pipip;
   Double_t        varDminusMassHypo_pipip;
   Double_t        varBMassHypo_Dpluspipi;
   Double_t        varBMassHypo_Dminuspipi;
   Double_t        varBMassHypo_DplusKpi;
   Double_t        varBMassHypo_DminusKpi;
   Double_t        varBMassHypo_DpluspiK;
   Double_t        varBMassHypo_DminuspiK;
   Double_t        varKplusTrackGhostProb;
   Double_t        varKminusTrackGhostProb;
   Double_t        varKaonMaxTrackGhostProb;
   Double_t        varPiplusOneTrackGhostProb;
   Double_t        varPiplusTwoTrackGhostProb;
   Double_t        varPiplusMaxTrackGhostProb;
   Double_t        varPiminusOneTrackGhostProb;
   Double_t        varPiminusTwoTrackGhostProb;
   Double_t        varPiminusMaxTrackGhostProb;
   Double_t        varPionMaxTrackGhostProb;
   Double_t        varPVVtxChi2ndof;
   Double_t        varPVVtxChi2ndof_log;
   Double_t        varDMinVtxSepChi2;
   Double_t        varDMaxVtxSepChi2;
   Double_t        varBEndVtxChi2ndof;
   Double_t        varBEndVtxChi2ndof_log;
   Double_t        varDplusEndVtxChi2ndof;
   Double_t        varDminusEndVtxChi2ndof;
   Double_t        varDMaxEndVtxChi2ndof;
   Double_t        varDDDTFSumPT;
   Double_t        varKaonMaxTrackFitChi2ndof;
   Double_t        varPiplusMaxTrackFitChi2ndof;
   Double_t        varPiminusMaxTrackFitChi2ndof;
   Double_t        varPionMaxTrackFitChi2ndof;
   Double_t        varDplusPionsSumPT;
   Double_t        varDplusDaughtersSumPT;
   Double_t        varDminusPionsSumPT;
   Double_t        varDminusDaughtersSumPT;
   Double_t        varDTFChi2ndof;
   Double_t        varDTFChi2ndof_log;
   Double_t        varIPChi2;
   Double_t        varIPChi2_log;
   Double_t        varDplusIPChi2;
   Double_t        varDminusIPChi2;
   Double_t        varDIPChi2Minimum;
   Double_t        varDIPChi2Maximum;
   Double_t        varPiminusOneIPChi2;
   Double_t        varPiminusTwoIPChi2;
   Double_t        varKplusIPChi2;
   Double_t        varPiplusOneIPChi2;
   Double_t        varPiplusTwoIPChi2;
   Double_t        varKminusIPChi2;
   Double_t        varKaonIPChi2Minimum;
   Double_t        varPionOneIPChi2Minimum;
   Double_t        varPionTwoIPChi2Minimum;
   Double_t        varKaonIPChi2Maximum;
   Double_t        varPionOneIPChi2Maximum;
   Double_t        varPionTwoIPChi2Maximum;
   Double_t        varBDIRAOwnPV;
   Double_t        varDplusDIRAOwnPV;
   Double_t        varDminusDIRAOwnPV;
   Double_t        varDMinDIRA;
   Double_t        varDMaxDIRA;
   Double_t        varDTFPVPosX;
   Double_t        varDTFPVPosY;
   Double_t        varDTFPVPosZ;
   Double_t        obsMomentum;
   Double_t        obsMomentumX;
   Double_t        obsMomentumY;
   Double_t        obsMomentumZ;
   Double_t        obsTransverseMomentum;
   Double_t        obsDTFMomentum;
   Double_t        obsDTFMomentumError;
   Double_t        obsDTFTransverseMomentum;
   Double_t        obsDTFTransverseMomentumError;
   Double_t        varDplusP;
   Double_t        varDplusPT;
   Double_t        varDminusP;
   Double_t        varDminusPT;
   Double_t        varDMinP;
   Double_t        varDMinPT;
   Double_t        varDMaxP;
   Double_t        varDMaxPT;
   Double_t        varPiplusOneP;
   Double_t        varPiplusOnePT;
   Double_t        varPiplusTwoP;
   Double_t        varPiplusTwoPT;
   Double_t        varPiminusOneP;
   Double_t        varPiminusOnePT;
   Double_t        varPiminusTwoP;
   Double_t        varPiminusTwoPT;
   Double_t        varKplusP;
   Double_t        varKplusPT;
   Double_t        varKminusP;
   Double_t        varKminusPT;
   Double_t        varPionOneMinP;
   Double_t        varPionTwoMinP;
   Double_t        varKaonMinP;
   Double_t        varPionOneMinPT;
   Double_t        varPionTwoMinPT;
   Double_t        varPionMinPT;
   Double_t        varKaonMinPT;
   Double_t        varHadronMinPT;
   Double_t        varPionOneMaxP;
   Double_t        varPionTwoMaxP;
   Double_t        varKaonMaxP;
   Double_t        varPionOneMaxPT;
   Double_t        varPionTwoMaxPT;
   Double_t        varPionMaxPT;
   Double_t        varKaonMaxPT;
   Double_t        varHadronMaxPT;
   Double_t        varKminusVELOChi2ndof;
   Double_t        varKplusVELOChi2ndof;
   Double_t        varKaonMinVELOChi2ndof;
   Double_t        varKaonMinVELOChi2ndof_log;
   Double_t        varKaonMaxVELOChi2ndof;
   Double_t        varKaonMaxVELOChi2ndof_log;
   Double_t        varPiplusOneVELOChi2ndof;
   Double_t        varPiplusTwoVELOChi2ndof;
   Double_t        varPiplusMinVELOChi2ndof;
   Double_t        varPiplusMaxVELOChi2ndof;
   Double_t        varPiminusOneVELOChi2ndof;
   Double_t        varPiminusTwoVELOChi2ndof;
   Double_t        varPiminusMinVELOChi2ndof;
   Double_t        varPionMinVELOChi2ndof;
   Double_t        varPionMinVELOChi2ndof_log;
   Double_t        varPiminusMaxVELOChi2ndof;
   Double_t        varPionMaxVELOChi2ndof;
   Double_t        varPionMaxVELOChi2ndof_log;
   Double_t        varHadronMinVELOChi2ndof;
   Double_t        varHadronMinVELOChi2ndof_log;
   Double_t        varHadronMaxVELOChi2ndof;
   Double_t        varHadronMaxVELOChi2ndof_log;
   Double_t        varKminusTChi2ndof;
   Double_t        varKplusTChi2ndof;
   Double_t        varKaonMinTChi2ndof;
   Double_t        varKaonMinTChi2ndof_log;
   Double_t        varKaonMaxTChi2ndof;
   Double_t        varKaonMaxTChi2ndof_log;
   Double_t        varPiplusOneTChi2ndof;
   Double_t        varPiplusTwoTChi2ndof;
   Double_t        varPiplusMinTChi2ndof;
   Double_t        varPiplusMaxTChi2ndof;
   Double_t        varPiminusOneTChi2ndof;
   Double_t        varPiminusTwoTChi2ndof;
   Double_t        varPiminusMinTChi2ndof;
   Double_t        varPionMinTChi2ndof;
   Double_t        varPionMinTChi2ndof_log;
   Double_t        varPiminusMaxTChi2ndof;
   Double_t        varPionMaxTChi2ndof;
   Double_t        varPionMaxTChi2ndof_log;
   Double_t        varHadronMinTChi2ndof;
   Double_t        varHadronMinTChi2ndof_log;
   Double_t        varHadronMaxTChi2ndof;
   Double_t        varHadronMaxTChi2ndof_log;
   Double_t        varKminusMatchChi2;
   Double_t        varKplusMatchChi2;
   Double_t        varKaonMinMatchChi2;
   Double_t        varKaonMinMatchChi2_log;
   Double_t        varKaonMaxMatchChi2;
   Double_t        varKaonMaxMatchChi2_log;
   Double_t        varPiplusOneMatchChi2;
   Double_t        varPiplusTwoMatchChi2;
   Double_t        varPiplusMinMatchChi2;
   Double_t        varPiplusMaxMatchChi2;
   Double_t        varPiminusOneMatchChi2;
   Double_t        varPiminusTwoMatchChi2;
   Double_t        varPiminusMinMatchChi2;
   Double_t        varPionMinMatchChi2;
   Double_t        varPionMinMatchChi2_log;
   Double_t        varPiminusMaxMatchChi2;
   Double_t        varPionMaxMatchChi2;
   Double_t        varPionMaxMatchChi2_log;
   Double_t        varHadronMinMatchChi2;
   Double_t        varHadronMinMatchChi2_log;
   Double_t        varHadronMaxMatchChi2;
   Double_t        varHadronMaxMatchChi2_log;
   Int_t           catTriggerL0GlobalTOS;
   Int_t           catTriggerHlt1GlobalTOS;
   Int_t           catTriggerHlt2GlobalTOS;
   Int_t           catTriggerHlt2Topo2BodyBBDTTOS;
   Int_t           catTriggerHlt2Topo3BodyBBDTTOS;
   Int_t           catTriggerHlt2Topo4BodyBBDTTOS;
   Int_t           catTriggerHlt2IncPhiTOS;
   Int_t           catTriggerSetTopo234BodyBBDT;
   Int_t           idxRandom;
   Int_t           catDplusFinalState;
   Int_t           catDminusFinalState;
   Int_t           catDDFinalState;
   Int_t           idxEventNumber;
   Int_t           idxRunNumber;
   Int_t           catNPV;
   Int_t           catMag;
   Int_t           catNTrack;
   Int_t           catYear;
   Int_t           varDTFStatusPVConst;
   Int_t           varDTFStatusDDPVConst;
   Float_t         varDTFChi2ndof_log_tmvafloatcopy;
   Float_t         varBEndVtxChi2ndof_log_tmvafloatcopy;
   Float_t         varIPChi2_log_tmvafloatcopy;
   Float_t         varBDIRAOwnPV_tmvafloatcopy;
   Float_t         varDMinTauSignificance_tmvafloatcopy;
   Float_t         varDMinPT_tmvafloatcopy;
   Float_t         varDDDTFSumPT_tmvafloatcopy;
   Float_t         varKaonMinPT_tmvafloatcopy;
   Float_t         varPionOneMinPT_tmvafloatcopy;
   Float_t         varPionTwoMinPT_tmvafloatcopy;
   Float_t         varPVVtxChi2ndof_log_tmvafloatcopy;
   Float_t         varKaonMinVELOChi2ndof_log_tmvafloatcopy;
   Float_t         varKaonMinTChi2ndof_log_tmvafloatcopy;
   Float_t         varKaonMinMatchChi2_log_tmvafloatcopy;
   Float_t         varPionMinVELOChi2ndof_log_tmvafloatcopy;
   Float_t         varPionMinTChi2ndof_log_tmvafloatcopy;
   Float_t         varPionMinMatchChi2_log_tmvafloatcopy;
   Double_t        BDT1_classifier;
   Double_t        BDT2_classifier;
   Double_t        BDTG1_classifier;
   Double_t        BDTG2_classifier;

   // List of branches
   TBranch        *b_B0_LOKI_ENERGY;   //!
   TBranch        *b_B0_LOKI_ETA;   //!
   TBranch        *b_B0_LOKI_PHI;   //!
   TBranch        *b_B0_ENDVERTEX_X;   //!
   TBranch        *b_B0_ENDVERTEX_Y;   //!
   TBranch        *b_B0_ENDVERTEX_Z;   //!
   TBranch        *b_B0_ENDVERTEX_XERR;   //!
   TBranch        *b_B0_ENDVERTEX_YERR;   //!
   TBranch        *b_B0_ENDVERTEX_ZERR;   //!
   TBranch        *b_B0_ENDVERTEX_CHI2;   //!
   TBranch        *b_B0_ENDVERTEX_NDOF;   //!
   TBranch        *b_B0_ENDVERTEX_COV_;   //!
   TBranch        *b_B0_OWNPV_X;   //!
   TBranch        *b_B0_OWNPV_Y;   //!
   TBranch        *b_B0_OWNPV_Z;   //!
   TBranch        *b_B0_OWNPV_XERR;   //!
   TBranch        *b_B0_OWNPV_YERR;   //!
   TBranch        *b_B0_OWNPV_ZERR;   //!
   TBranch        *b_B0_OWNPV_CHI2;   //!
   TBranch        *b_B0_OWNPV_NDOF;   //!
   TBranch        *b_B0_OWNPV_COV_;   //!
   TBranch        *b_B0_IP_OWNPV;   //!
   TBranch        *b_B0_IPCHI2_OWNPV;   //!
   TBranch        *b_B0_FD_OWNPV;   //!
   TBranch        *b_B0_FDCHI2_OWNPV;   //!
   TBranch        *b_B0_DIRA_OWNPV;   //!
   TBranch        *b_B0_P;   //!
   TBranch        *b_B0_PT;   //!
   TBranch        *b_B0_PE;   //!
   TBranch        *b_B0_PX;   //!
   TBranch        *b_B0_PY;   //!
   TBranch        *b_B0_PZ;   //!
   TBranch        *b_B0_MM;   //!
   TBranch        *b_B0_MMERR;   //!
   TBranch        *b_B0_M;   //!
   TBranch        *b_B0_ID;   //!
   TBranch        *b_B0_TAU;   //!
   TBranch        *b_B0_TAUERR;   //!
   TBranch        *b_B0_TAUCHI2;   //!
   TBranch        *b_B0_X;   //!
   TBranch        *b_B0_Y;   //!
   TBranch        *b_B0_LOKI_DIRA;   //!
   TBranch        *b_B0_LOKI_DTF_CHI2NDOF;   //!
   TBranch        *b_B0_LOKI_DTF_CTAU;   //!
   TBranch        *b_B0_LOKI_DTF_CTAUERR;   //!
   TBranch        *b_B0_LOKI_DTF_CTAUERR_D1;   //!
   TBranch        *b_B0_LOKI_DTF_CTAUERR_D2;   //!
   TBranch        *b_B0_LOKI_DTF_CTAUERR_NOPV;   //!
   TBranch        *b_B0_LOKI_DTF_CTAUS;   //!
   TBranch        *b_B0_LOKI_DTF_CTAU_D1;   //!
   TBranch        *b_B0_LOKI_DTF_CTAU_D2;   //!
   TBranch        *b_B0_LOKI_DTF_CTAU_NOPV;   //!
   TBranch        *b_B0_LOKI_DTF_VCHI2NDOF;   //!
   TBranch        *b_B0_LOKI_FDCHI2;   //!
   TBranch        *b_B0_LOKI_FDS;   //!
   TBranch        *b_B0_LOKI_MASSERR_DDConstr;   //!
   TBranch        *b_B0_LOKI_MASSERR_DminusConstr;   //!
   TBranch        *b_B0_LOKI_MASSERR_DplusConstr;   //!
   TBranch        *b_B0_LOKI_MASS_DDConstr;   //!
   TBranch        *b_B0_LOKI_MASS_DminusConstr;   //!
   TBranch        *b_B0_LOKI_MASS_Dminus_NoPVConstr;   //!
   TBranch        *b_B0_LOKI_MASS_DplusConstr;   //!
   TBranch        *b_B0_LOKI_MASS_Dplus_NoPVConstr;   //!
   TBranch        *b_B0_Fit_nPV;   //!
   TBranch        *b_B0_Fit_Dminus_IP;   //!
   TBranch        *b_B0_Fit_Dminus_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dminus_M;   //!
   TBranch        *b_B0_Fit_Dminus_MERR;   //!
   TBranch        *b_B0_Fit_Dminus_P;   //!
   TBranch        *b_B0_Fit_Dminus_P0_ID;   //!
   TBranch        *b_B0_Fit_Dminus_P0_IP;   //!
   TBranch        *b_B0_Fit_Dminus_P0_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dminus_P0_P;   //!
   TBranch        *b_B0_Fit_Dminus_P0_PE;   //!
   TBranch        *b_B0_Fit_Dminus_P0_PERR;   //!
   TBranch        *b_B0_Fit_Dminus_P0_PT;   //!
   TBranch        *b_B0_Fit_Dminus_P0_PTERR;   //!
   TBranch        *b_B0_Fit_Dminus_P0_PX;   //!
   TBranch        *b_B0_Fit_Dminus_P0_PY;   //!
   TBranch        *b_B0_Fit_Dminus_P0_PZ;   //!
   TBranch        *b_B0_Fit_Dminus_P0_X;   //!
   TBranch        *b_B0_Fit_Dminus_P0_XERR;   //!
   TBranch        *b_B0_Fit_Dminus_P0_Y;   //!
   TBranch        *b_B0_Fit_Dminus_P0_YERR;   //!
   TBranch        *b_B0_Fit_Dminus_P0_Z;   //!
   TBranch        *b_B0_Fit_Dminus_P0_ZERR;   //!
   TBranch        *b_B0_Fit_Dminus_P1_ID;   //!
   TBranch        *b_B0_Fit_Dminus_P1_IP;   //!
   TBranch        *b_B0_Fit_Dminus_P1_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dminus_P1_P;   //!
   TBranch        *b_B0_Fit_Dminus_P1_PE;   //!
   TBranch        *b_B0_Fit_Dminus_P1_PERR;   //!
   TBranch        *b_B0_Fit_Dminus_P1_PT;   //!
   TBranch        *b_B0_Fit_Dminus_P1_PTERR;   //!
   TBranch        *b_B0_Fit_Dminus_P1_PX;   //!
   TBranch        *b_B0_Fit_Dminus_P1_PY;   //!
   TBranch        *b_B0_Fit_Dminus_P1_PZ;   //!
   TBranch        *b_B0_Fit_Dminus_P1_X;   //!
   TBranch        *b_B0_Fit_Dminus_P1_XERR;   //!
   TBranch        *b_B0_Fit_Dminus_P1_Y;   //!
   TBranch        *b_B0_Fit_Dminus_P1_YERR;   //!
   TBranch        *b_B0_Fit_Dminus_P1_Z;   //!
   TBranch        *b_B0_Fit_Dminus_P1_ZERR;   //!
   TBranch        *b_B0_Fit_Dminus_P2_ID;   //!
   TBranch        *b_B0_Fit_Dminus_P2_IP;   //!
   TBranch        *b_B0_Fit_Dminus_P2_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dminus_P2_P;   //!
   TBranch        *b_B0_Fit_Dminus_P2_PE;   //!
   TBranch        *b_B0_Fit_Dminus_P2_PERR;   //!
   TBranch        *b_B0_Fit_Dminus_P2_PT;   //!
   TBranch        *b_B0_Fit_Dminus_P2_PTERR;   //!
   TBranch        *b_B0_Fit_Dminus_P2_PX;   //!
   TBranch        *b_B0_Fit_Dminus_P2_PY;   //!
   TBranch        *b_B0_Fit_Dminus_P2_PZ;   //!
   TBranch        *b_B0_Fit_Dminus_P2_X;   //!
   TBranch        *b_B0_Fit_Dminus_P2_XERR;   //!
   TBranch        *b_B0_Fit_Dminus_P2_Y;   //!
   TBranch        *b_B0_Fit_Dminus_P2_YERR;   //!
   TBranch        *b_B0_Fit_Dminus_P2_Z;   //!
   TBranch        *b_B0_Fit_Dminus_P2_ZERR;   //!
   TBranch        *b_B0_Fit_Dminus_PERR;   //!
   TBranch        *b_B0_Fit_Dminus_PT;   //!
   TBranch        *b_B0_Fit_Dminus_PTERR;   //!
   TBranch        *b_B0_Fit_Dminus_ctau;   //!
   TBranch        *b_B0_Fit_Dminus_ctauErr;   //!
   TBranch        *b_B0_Fit_Dminus_decayLength;   //!
   TBranch        *b_B0_Fit_Dminus_decayLengthErr;   //!
   TBranch        *b_B0_Fit_Dminus_tau;   //!
   TBranch        *b_B0_Fit_Dminus_tauErr;   //!
   TBranch        *b_B0_Fit_Dplus_IP;   //!
   TBranch        *b_B0_Fit_Dplus_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dplus_M;   //!
   TBranch        *b_B0_Fit_Dplus_MERR;   //!
   TBranch        *b_B0_Fit_Dplus_P;   //!
   TBranch        *b_B0_Fit_Dplus_P0_ID;   //!
   TBranch        *b_B0_Fit_Dplus_P0_IP;   //!
   TBranch        *b_B0_Fit_Dplus_P0_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dplus_P0_P;   //!
   TBranch        *b_B0_Fit_Dplus_P0_PE;   //!
   TBranch        *b_B0_Fit_Dplus_P0_PERR;   //!
   TBranch        *b_B0_Fit_Dplus_P0_PT;   //!
   TBranch        *b_B0_Fit_Dplus_P0_PTERR;   //!
   TBranch        *b_B0_Fit_Dplus_P0_PX;   //!
   TBranch        *b_B0_Fit_Dplus_P0_PY;   //!
   TBranch        *b_B0_Fit_Dplus_P0_PZ;   //!
   TBranch        *b_B0_Fit_Dplus_P0_X;   //!
   TBranch        *b_B0_Fit_Dplus_P0_XERR;   //!
   TBranch        *b_B0_Fit_Dplus_P0_Y;   //!
   TBranch        *b_B0_Fit_Dplus_P0_YERR;   //!
   TBranch        *b_B0_Fit_Dplus_P0_Z;   //!
   TBranch        *b_B0_Fit_Dplus_P0_ZERR;   //!
   TBranch        *b_B0_Fit_Dplus_P1_ID;   //!
   TBranch        *b_B0_Fit_Dplus_P1_IP;   //!
   TBranch        *b_B0_Fit_Dplus_P1_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dplus_P1_P;   //!
   TBranch        *b_B0_Fit_Dplus_P1_PE;   //!
   TBranch        *b_B0_Fit_Dplus_P1_PERR;   //!
   TBranch        *b_B0_Fit_Dplus_P1_PT;   //!
   TBranch        *b_B0_Fit_Dplus_P1_PTERR;   //!
   TBranch        *b_B0_Fit_Dplus_P1_PX;   //!
   TBranch        *b_B0_Fit_Dplus_P1_PY;   //!
   TBranch        *b_B0_Fit_Dplus_P1_PZ;   //!
   TBranch        *b_B0_Fit_Dplus_P1_X;   //!
   TBranch        *b_B0_Fit_Dplus_P1_XERR;   //!
   TBranch        *b_B0_Fit_Dplus_P1_Y;   //!
   TBranch        *b_B0_Fit_Dplus_P1_YERR;   //!
   TBranch        *b_B0_Fit_Dplus_P1_Z;   //!
   TBranch        *b_B0_Fit_Dplus_P1_ZERR;   //!
   TBranch        *b_B0_Fit_Dplus_P2_ID;   //!
   TBranch        *b_B0_Fit_Dplus_P2_IP;   //!
   TBranch        *b_B0_Fit_Dplus_P2_IPCHI2;   //!
   TBranch        *b_B0_Fit_Dplus_P2_P;   //!
   TBranch        *b_B0_Fit_Dplus_P2_PE;   //!
   TBranch        *b_B0_Fit_Dplus_P2_PERR;   //!
   TBranch        *b_B0_Fit_Dplus_P2_PT;   //!
   TBranch        *b_B0_Fit_Dplus_P2_PTERR;   //!
   TBranch        *b_B0_Fit_Dplus_P2_PX;   //!
   TBranch        *b_B0_Fit_Dplus_P2_PY;   //!
   TBranch        *b_B0_Fit_Dplus_P2_PZ;   //!
   TBranch        *b_B0_Fit_Dplus_P2_X;   //!
   TBranch        *b_B0_Fit_Dplus_P2_XERR;   //!
   TBranch        *b_B0_Fit_Dplus_P2_Y;   //!
   TBranch        *b_B0_Fit_Dplus_P2_YERR;   //!
   TBranch        *b_B0_Fit_Dplus_P2_Z;   //!
   TBranch        *b_B0_Fit_Dplus_P2_ZERR;   //!
   TBranch        *b_B0_Fit_Dplus_PERR;   //!
   TBranch        *b_B0_Fit_Dplus_PT;   //!
   TBranch        *b_B0_Fit_Dplus_PTERR;   //!
   TBranch        *b_B0_Fit_Dplus_ctau;   //!
   TBranch        *b_B0_Fit_Dplus_ctauErr;   //!
   TBranch        *b_B0_Fit_Dplus_decayLength;   //!
   TBranch        *b_B0_Fit_Dplus_decayLengthErr;   //!
   TBranch        *b_B0_Fit_Dplus_tau;   //!
   TBranch        *b_B0_Fit_Dplus_tauErr;   //!
   TBranch        *b_B0_Fit_IP;   //!
   TBranch        *b_B0_Fit_IPCHI2;   //!
   TBranch        *b_B0_Fit_M;   //!
   TBranch        *b_B0_Fit_MERR;   //!
   TBranch        *b_B0_Fit_P;   //!
   TBranch        *b_B0_Fit_PERR;   //!
   TBranch        *b_B0_Fit_PT;   //!
   TBranch        *b_B0_Fit_PTERR;   //!
   TBranch        *b_B0_Fit_PV_X;   //!
   TBranch        *b_B0_Fit_PV_XVAR;   //!
   TBranch        *b_B0_Fit_PV_XYCOV;   //!
   TBranch        *b_B0_Fit_PV_XZCOV;   //!
   TBranch        *b_B0_Fit_PV_Y;   //!
   TBranch        *b_B0_Fit_PV_YVAR;   //!
   TBranch        *b_B0_Fit_PV_YZCOV;   //!
   TBranch        *b_B0_Fit_PV_Z;   //!
   TBranch        *b_B0_Fit_PV_ZVAR;   //!
   TBranch        *b_B0_Fit_PV_key;   //!
   TBranch        *b_B0_Fit_X;   //!
   TBranch        *b_B0_Fit_XERR;   //!
   TBranch        *b_B0_Fit_Y;   //!
   TBranch        *b_B0_Fit_YERR;   //!
   TBranch        *b_B0_Fit_Z;   //!
   TBranch        *b_B0_Fit_ZERR;   //!
   TBranch        *b_B0_Fit_chi2;   //!
   TBranch        *b_B0_Fit_ctau;   //!
   TBranch        *b_B0_Fit_ctauErr;   //!
   TBranch        *b_B0_Fit_decayLength;   //!
   TBranch        *b_B0_Fit_decayLengthErr;   //!
   TBranch        *b_B0_Fit_nDOF;   //!
   TBranch        *b_B0_Fit_nIter;   //!
   TBranch        *b_B0_Fit_status;   //!
   TBranch        *b_B0_Fit_tau;   //!
   TBranch        *b_B0_Fit_tauErr;   //!
   TBranch        *b_B0_FitDDConst_nPV;   //!
   TBranch        *b_B0_FitDDConst_Dminus_IP;   //!
   TBranch        *b_B0_FitDDConst_Dminus_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dminus_M;   //!
   TBranch        *b_B0_FitDDConst_Dminus_MERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_ID;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_IP;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_P;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_PE;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_PT;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_PX;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_PY;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_PZ;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_X;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_XERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_Y;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_YERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_Z;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P0_ZERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_ID;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_IP;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_P;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_PE;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_PT;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_PX;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_PY;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_PZ;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_X;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_XERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_Y;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_YERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_Z;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P1_ZERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_ID;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_IP;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_P;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_PE;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_PT;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_PX;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_PY;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_PZ;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_X;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_XERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_Y;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_YERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_Z;   //!
   TBranch        *b_B0_FitDDConst_Dminus_P2_ZERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_PT;   //!
   TBranch        *b_B0_FitDDConst_Dminus_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dminus_ctau;   //!
   TBranch        *b_B0_FitDDConst_Dminus_ctauErr;   //!
   TBranch        *b_B0_FitDDConst_Dminus_decayLength;   //!
   TBranch        *b_B0_FitDDConst_Dminus_decayLengthErr;   //!
   TBranch        *b_B0_FitDDConst_Dminus_tau;   //!
   TBranch        *b_B0_FitDDConst_Dminus_tauErr;   //!
   TBranch        *b_B0_FitDDConst_Dplus_IP;   //!
   TBranch        *b_B0_FitDDConst_Dplus_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dplus_M;   //!
   TBranch        *b_B0_FitDDConst_Dplus_MERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_ID;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_IP;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_P;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_PE;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_PT;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_PX;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_PY;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_PZ;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_X;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_XERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_Y;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_YERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_Z;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P0_ZERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_ID;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_IP;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_P;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_PE;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_PT;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_PX;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_PY;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_PZ;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_X;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_XERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_Y;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_YERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_Z;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P1_ZERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_ID;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_IP;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_P;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_PE;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_PT;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_PX;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_PY;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_PZ;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_X;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_XERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_Y;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_YERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_Z;   //!
   TBranch        *b_B0_FitDDConst_Dplus_P2_ZERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_PERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_PT;   //!
   TBranch        *b_B0_FitDDConst_Dplus_PTERR;   //!
   TBranch        *b_B0_FitDDConst_Dplus_ctau;   //!
   TBranch        *b_B0_FitDDConst_Dplus_ctauErr;   //!
   TBranch        *b_B0_FitDDConst_Dplus_decayLength;   //!
   TBranch        *b_B0_FitDDConst_Dplus_decayLengthErr;   //!
   TBranch        *b_B0_FitDDConst_Dplus_tau;   //!
   TBranch        *b_B0_FitDDConst_Dplus_tauErr;   //!
   TBranch        *b_B0_FitDDConst_IP;   //!
   TBranch        *b_B0_FitDDConst_IPCHI2;   //!
   TBranch        *b_B0_FitDDConst_M;   //!
   TBranch        *b_B0_FitDDConst_MERR;   //!
   TBranch        *b_B0_FitDDConst_P;   //!
   TBranch        *b_B0_FitDDConst_PERR;   //!
   TBranch        *b_B0_FitDDConst_PT;   //!
   TBranch        *b_B0_FitDDConst_PTERR;   //!
   TBranch        *b_B0_FitDDConst_PV_X;   //!
   TBranch        *b_B0_FitDDConst_PV_XVAR;   //!
   TBranch        *b_B0_FitDDConst_PV_XYCOV;   //!
   TBranch        *b_B0_FitDDConst_PV_XZCOV;   //!
   TBranch        *b_B0_FitDDConst_PV_Y;   //!
   TBranch        *b_B0_FitDDConst_PV_YVAR;   //!
   TBranch        *b_B0_FitDDConst_PV_YZCOV;   //!
   TBranch        *b_B0_FitDDConst_PV_Z;   //!
   TBranch        *b_B0_FitDDConst_PV_ZVAR;   //!
   TBranch        *b_B0_FitDDConst_PV_key;   //!
   TBranch        *b_B0_FitDDConst_X;   //!
   TBranch        *b_B0_FitDDConst_XERR;   //!
   TBranch        *b_B0_FitDDConst_Y;   //!
   TBranch        *b_B0_FitDDConst_YERR;   //!
   TBranch        *b_B0_FitDDConst_Z;   //!
   TBranch        *b_B0_FitDDConst_ZERR;   //!
   TBranch        *b_B0_FitDDConst_chi2;   //!
   TBranch        *b_B0_FitDDConst_ctau;   //!
   TBranch        *b_B0_FitDDConst_ctauErr;   //!
   TBranch        *b_B0_FitDDConst_decayLength;   //!
   TBranch        *b_B0_FitDDConst_decayLengthErr;   //!
   TBranch        *b_B0_FitDDConst_nDOF;   //!
   TBranch        *b_B0_FitDDConst_nIter;   //!
   TBranch        *b_B0_FitDDConst_status;   //!
   TBranch        *b_B0_FitDDConst_tau;   //!
   TBranch        *b_B0_FitDDConst_tauErr;   //!
   TBranch        *b_B0_FitDDPVConst_nPV;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_M;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_MERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_ID;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_PE;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_PX;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_PY;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_PZ;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_X;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_XERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_Y;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_YERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_Z;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P0_ZERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_ID;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_PE;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_PX;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_PY;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_PZ;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_X;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_XERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_Y;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_YERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_Z;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P1_ZERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_ID;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_PE;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_PX;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_PY;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_PZ;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_X;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_XERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_Y;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_YERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_Z;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_P2_ZERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_ctau;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_ctauErr;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_decayLength;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_decayLengthErr;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_tau;   //!
   TBranch        *b_B0_FitDDPVConst_Dminus_tauErr;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_M;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_MERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_ID;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_PE;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_PX;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_PY;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_PZ;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_X;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_XERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_Y;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_YERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_Z;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P0_ZERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_ID;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_PE;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_PX;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_PY;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_PZ;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_X;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_XERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_Y;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_YERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_Z;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P1_ZERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_ID;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_IP;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_P;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_PE;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_PX;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_PY;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_PZ;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_X;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_XERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_Y;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_YERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_Z;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_P2_ZERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_PT;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_ctau;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_ctauErr;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_decayLength;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_decayLengthErr;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_tau;   //!
   TBranch        *b_B0_FitDDPVConst_Dplus_tauErr;   //!
   TBranch        *b_B0_FitDDPVConst_IP;   //!
   TBranch        *b_B0_FitDDPVConst_IPCHI2;   //!
   TBranch        *b_B0_FitDDPVConst_M;   //!
   TBranch        *b_B0_FitDDPVConst_MERR;   //!
   TBranch        *b_B0_FitDDPVConst_P;   //!
   TBranch        *b_B0_FitDDPVConst_PERR;   //!
   TBranch        *b_B0_FitDDPVConst_PT;   //!
   TBranch        *b_B0_FitDDPVConst_PTERR;   //!
   TBranch        *b_B0_FitDDPVConst_PV_X;   //!
   TBranch        *b_B0_FitDDPVConst_PV_XVAR;   //!
   TBranch        *b_B0_FitDDPVConst_PV_XYCOV;   //!
   TBranch        *b_B0_FitDDPVConst_PV_XZCOV;   //!
   TBranch        *b_B0_FitDDPVConst_PV_Y;   //!
   TBranch        *b_B0_FitDDPVConst_PV_YVAR;   //!
   TBranch        *b_B0_FitDDPVConst_PV_YZCOV;   //!
   TBranch        *b_B0_FitDDPVConst_PV_Z;   //!
   TBranch        *b_B0_FitDDPVConst_PV_ZVAR;   //!
   TBranch        *b_B0_FitDDPVConst_PV_key;   //!
   TBranch        *b_B0_FitDDPVConst_X;   //!
   TBranch        *b_B0_FitDDPVConst_XERR;   //!
   TBranch        *b_B0_FitDDPVConst_Y;   //!
   TBranch        *b_B0_FitDDPVConst_YERR;   //!
   TBranch        *b_B0_FitDDPVConst_Z;   //!
   TBranch        *b_B0_FitDDPVConst_ZERR;   //!
   TBranch        *b_B0_FitDDPVConst_chi2;   //!
   TBranch        *b_B0_FitDDPVConst_ctau;   //!
   TBranch        *b_B0_FitDDPVConst_ctauErr;   //!
   TBranch        *b_B0_FitDDPVConst_decayLength;   //!
   TBranch        *b_B0_FitDDPVConst_decayLengthErr;   //!
   TBranch        *b_B0_FitDDPVConst_nDOF;   //!
   TBranch        *b_B0_FitDDPVConst_nIter;   //!
   TBranch        *b_B0_FitDDPVConst_status;   //!
   TBranch        *b_B0_FitDDPVConst_tau;   //!
   TBranch        *b_B0_FitDDPVConst_tauErr;   //!
   TBranch        *b_B0_FitPVConst_nPV;   //!
   TBranch        *b_B0_FitPVConst_Dminus_IP;   //!
   TBranch        *b_B0_FitPVConst_Dminus_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dminus_M;   //!
   TBranch        *b_B0_FitPVConst_Dminus_MERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_ID;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_IP;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_P;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_PE;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_PT;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_PX;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_PY;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_PZ;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_X;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_XERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_Y;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_YERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_Z;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P0_ZERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_ID;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_IP;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_P;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_PE;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_PT;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_PX;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_PY;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_PZ;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_X;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_XERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_Y;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_YERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_Z;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P1_ZERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_ID;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_IP;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_P;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_PE;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_PT;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_PX;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_PY;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_PZ;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_X;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_XERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_Y;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_YERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_Z;   //!
   TBranch        *b_B0_FitPVConst_Dminus_P2_ZERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_PT;   //!
   TBranch        *b_B0_FitPVConst_Dminus_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dminus_ctau;   //!
   TBranch        *b_B0_FitPVConst_Dminus_ctauErr;   //!
   TBranch        *b_B0_FitPVConst_Dminus_decayLength;   //!
   TBranch        *b_B0_FitPVConst_Dminus_decayLengthErr;   //!
   TBranch        *b_B0_FitPVConst_Dminus_tau;   //!
   TBranch        *b_B0_FitPVConst_Dminus_tauErr;   //!
   TBranch        *b_B0_FitPVConst_Dplus_IP;   //!
   TBranch        *b_B0_FitPVConst_Dplus_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dplus_M;   //!
   TBranch        *b_B0_FitPVConst_Dplus_MERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_ID;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_IP;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_P;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_PE;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_PT;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_PX;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_PY;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_PZ;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_X;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_XERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_Y;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_YERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_Z;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P0_ZERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_ID;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_IP;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_P;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_PE;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_PT;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_PX;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_PY;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_PZ;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_X;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_XERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_Y;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_YERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_Z;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P1_ZERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_ID;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_IP;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_P;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_PE;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_PT;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_PX;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_PY;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_PZ;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_X;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_XERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_Y;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_YERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_Z;   //!
   TBranch        *b_B0_FitPVConst_Dplus_P2_ZERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_PERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_PT;   //!
   TBranch        *b_B0_FitPVConst_Dplus_PTERR;   //!
   TBranch        *b_B0_FitPVConst_Dplus_ctau;   //!
   TBranch        *b_B0_FitPVConst_Dplus_ctauErr;   //!
   TBranch        *b_B0_FitPVConst_Dplus_decayLength;   //!
   TBranch        *b_B0_FitPVConst_Dplus_decayLengthErr;   //!
   TBranch        *b_B0_FitPVConst_Dplus_tau;   //!
   TBranch        *b_B0_FitPVConst_Dplus_tauErr;   //!
   TBranch        *b_B0_FitPVConst_IP;   //!
   TBranch        *b_B0_FitPVConst_IPCHI2;   //!
   TBranch        *b_B0_FitPVConst_M;   //!
   TBranch        *b_B0_FitPVConst_MERR;   //!
   TBranch        *b_B0_FitPVConst_P;   //!
   TBranch        *b_B0_FitPVConst_PERR;   //!
   TBranch        *b_B0_FitPVConst_PT;   //!
   TBranch        *b_B0_FitPVConst_PTERR;   //!
   TBranch        *b_B0_FitPVConst_PV_X;   //!
   TBranch        *b_B0_FitPVConst_PV_XVAR;   //!
   TBranch        *b_B0_FitPVConst_PV_XYCOV;   //!
   TBranch        *b_B0_FitPVConst_PV_XZCOV;   //!
   TBranch        *b_B0_FitPVConst_PV_Y;   //!
   TBranch        *b_B0_FitPVConst_PV_YVAR;   //!
   TBranch        *b_B0_FitPVConst_PV_YZCOV;   //!
   TBranch        *b_B0_FitPVConst_PV_Z;   //!
   TBranch        *b_B0_FitPVConst_PV_ZVAR;   //!
   TBranch        *b_B0_FitPVConst_PV_key;   //!
   TBranch        *b_B0_FitPVConst_X;   //!
   TBranch        *b_B0_FitPVConst_XERR;   //!
   TBranch        *b_B0_FitPVConst_Y;   //!
   TBranch        *b_B0_FitPVConst_YERR;   //!
   TBranch        *b_B0_FitPVConst_Z;   //!
   TBranch        *b_B0_FitPVConst_ZERR;   //!
   TBranch        *b_B0_FitPVConst_chi2;   //!
   TBranch        *b_B0_FitPVConst_ctau;   //!
   TBranch        *b_B0_FitPVConst_ctauErr;   //!
   TBranch        *b_B0_FitPVConst_decayLength;   //!
   TBranch        *b_B0_FitPVConst_decayLengthErr;   //!
   TBranch        *b_B0_FitPVConst_nDOF;   //!
   TBranch        *b_B0_FitPVConst_nIter;   //!
   TBranch        *b_B0_FitPVConst_status;   //!
   TBranch        *b_B0_FitPVConst_tau;   //!
   TBranch        *b_B0_FitPVConst_tauErr;   //!
   TBranch        *b_B0_L0Global_Dec;   //!
   TBranch        *b_B0_L0Global_TIS;   //!
   TBranch        *b_B0_L0Global_TOS;   //!
   TBranch        *b_B0_Hlt1Global_Dec;   //!
   TBranch        *b_B0_Hlt1Global_TIS;   //!
   TBranch        *b_B0_Hlt1Global_TOS;   //!
   TBranch        *b_B0_Hlt1Phys_Dec;   //!
   TBranch        *b_B0_Hlt1Phys_TIS;   //!
   TBranch        *b_B0_Hlt1Phys_TOS;   //!
   TBranch        *b_B0_Hlt2Global_Dec;   //!
   TBranch        *b_B0_Hlt2Global_TIS;   //!
   TBranch        *b_B0_Hlt2Global_TOS;   //!
   TBranch        *b_B0_Hlt2Phys_Dec;   //!
   TBranch        *b_B0_Hlt2Phys_TIS;   //!
   TBranch        *b_B0_Hlt2Phys_TOS;   //!
   TBranch        *b_B0_L0PhysicsDecision_Dec;   //!
   TBranch        *b_B0_L0PhysicsDecision_TIS;   //!
   TBranch        *b_B0_L0PhysicsDecision_TOS;   //!
   TBranch        *b_B0_L0MuonDecision_Dec;   //!
   TBranch        *b_B0_L0MuonDecision_TIS;   //!
   TBranch        *b_B0_L0MuonDecision_TOS;   //!
   TBranch        *b_B0_L0DiMuonDecision_Dec;   //!
   TBranch        *b_B0_L0DiMuonDecision_TIS;   //!
   TBranch        *b_B0_L0DiMuonDecision_TOS;   //!
   TBranch        *b_B0_L0MuonHighDecision_Dec;   //!
   TBranch        *b_B0_L0MuonHighDecision_TIS;   //!
   TBranch        *b_B0_L0MuonHighDecision_TOS;   //!
   TBranch        *b_B0_L0HadronDecision_Dec;   //!
   TBranch        *b_B0_L0HadronDecision_TIS;   //!
   TBranch        *b_B0_L0HadronDecision_TOS;   //!
   TBranch        *b_B0_L0ElectronDecision_Dec;   //!
   TBranch        *b_B0_L0ElectronDecision_TIS;   //!
   TBranch        *b_B0_L0ElectronDecision_TOS;   //!
   TBranch        *b_B0_L0PhotonDecision_Dec;   //!
   TBranch        *b_B0_L0PhotonDecision_TIS;   //!
   TBranch        *b_B0_L0PhotonDecision_TOS;   //!
   TBranch        *b_B0_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_B0_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_B0_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_B0_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_B0_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_B0_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_B0_Hlt1L0AnyDecision_Dec;   //!
   TBranch        *b_B0_Hlt1L0AnyDecision_TIS;   //!
   TBranch        *b_B0_Hlt1L0AnyDecision_TOS;   //!
   TBranch        *b_B0_Hlt1GlobalDecision_Dec;   //!
   TBranch        *b_B0_Hlt1GlobalDecision_TIS;   //!
   TBranch        *b_B0_Hlt1GlobalDecision_TOS;   //!
   TBranch        *b_B0_Hlt2GlobalDecision_Dec;   //!
   TBranch        *b_B0_Hlt2GlobalDecision_TIS;   //!
   TBranch        *b_B0_Hlt2GlobalDecision_TOS;   //!
   TBranch        *b_B0_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_B0_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_B0_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_B0_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_B0_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_B0_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_B0_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_B0_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_B0_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_B0_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2TopoE2BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2TopoE2BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2TopoE2BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2TopoE3BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2TopoE3BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2TopoE3BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2TopoE4BodyBBDTDecision_Dec;   //!
   TBranch        *b_B0_Hlt2TopoE4BodyBBDTDecision_TIS;   //!
   TBranch        *b_B0_Hlt2TopoE4BodyBBDTDecision_TOS;   //!
   TBranch        *b_B0_Hlt2IncPhiDecision_Dec;   //!
   TBranch        *b_B0_Hlt2IncPhiDecision_TIS;   //!
   TBranch        *b_B0_Hlt2IncPhiDecision_TOS;   //!
   TBranch        *b_B0_Hlt2IncPhiSidebandsDecision_Dec;   //!
   TBranch        *b_B0_Hlt2IncPhiSidebandsDecision_TIS;   //!
   TBranch        *b_B0_Hlt2IncPhiSidebandsDecision_TOS;   //!
   TBranch        *b_B0_TAGDECISION;   //!
   TBranch        *b_B0_TAGOMEGA;   //!
   TBranch        *b_B0_TAGDECISION_OS;   //!
   TBranch        *b_B0_TAGOMEGA_OS;   //!
   TBranch        *b_B0_TAGGER;   //!
   TBranch        *b_B0_OS_Muon_DEC;   //!
   TBranch        *b_B0_OS_Muon_PROB;   //!
   TBranch        *b_B0_OS_Electron_DEC;   //!
   TBranch        *b_B0_OS_Electron_PROB;   //!
   TBranch        *b_B0_OS_Kaon_DEC;   //!
   TBranch        *b_B0_OS_Kaon_PROB;   //!
   TBranch        *b_B0_SS_Kaon_DEC;   //!
   TBranch        *b_B0_SS_Kaon_PROB;   //!
   TBranch        *b_B0_SS_Pion_DEC;   //!
   TBranch        *b_B0_SS_Pion_PROB;   //!
   TBranch        *b_B0_SS_PionBDT_DEC;   //!
   TBranch        *b_B0_SS_PionBDT_PROB;   //!
   TBranch        *b_B0_VtxCharge_DEC;   //!
   TBranch        *b_B0_VtxCharge_PROB;   //!
   TBranch        *b_B0_OS_nnetKaon_DEC;   //!
   TBranch        *b_B0_OS_nnetKaon_PROB;   //!
   TBranch        *b_B0_SS_nnetKaon_DEC;   //!
   TBranch        *b_B0_SS_nnetKaon_PROB;   //!
   TBranch        *b_B0_SS_Proton_DEC;   //!
   TBranch        *b_B0_SS_Proton_PROB;   //!
   TBranch        *b_B0_OS_Charm_DEC;   //!
   TBranch        *b_B0_OS_Charm_PROB;   //!
   TBranch        *b_Dplus_LOKI_ENERGY;   //!
   TBranch        *b_Dplus_LOKI_ETA;   //!
   TBranch        *b_Dplus_LOKI_PHI;   //!
   TBranch        *b_Dplus_ENDVERTEX_X;   //!
   TBranch        *b_Dplus_ENDVERTEX_Y;   //!
   TBranch        *b_Dplus_ENDVERTEX_Z;   //!
   TBranch        *b_Dplus_ENDVERTEX_XERR;   //!
   TBranch        *b_Dplus_ENDVERTEX_YERR;   //!
   TBranch        *b_Dplus_ENDVERTEX_ZERR;   //!
   TBranch        *b_Dplus_ENDVERTEX_CHI2;   //!
   TBranch        *b_Dplus_ENDVERTEX_NDOF;   //!
   TBranch        *b_Dplus_ENDVERTEX_COV_;   //!
   TBranch        *b_Dplus_OWNPV_X;   //!
   TBranch        *b_Dplus_OWNPV_Y;   //!
   TBranch        *b_Dplus_OWNPV_Z;   //!
   TBranch        *b_Dplus_OWNPV_XERR;   //!
   TBranch        *b_Dplus_OWNPV_YERR;   //!
   TBranch        *b_Dplus_OWNPV_ZERR;   //!
   TBranch        *b_Dplus_OWNPV_CHI2;   //!
   TBranch        *b_Dplus_OWNPV_NDOF;   //!
   TBranch        *b_Dplus_OWNPV_COV_;   //!
   TBranch        *b_Dplus_IP_OWNPV;   //!
   TBranch        *b_Dplus_IPCHI2_OWNPV;   //!
   TBranch        *b_Dplus_FD_OWNPV;   //!
   TBranch        *b_Dplus_FDCHI2_OWNPV;   //!
   TBranch        *b_Dplus_DIRA_OWNPV;   //!
   TBranch        *b_Dplus_ORIVX_X;   //!
   TBranch        *b_Dplus_ORIVX_Y;   //!
   TBranch        *b_Dplus_ORIVX_Z;   //!
   TBranch        *b_Dplus_ORIVX_XERR;   //!
   TBranch        *b_Dplus_ORIVX_YERR;   //!
   TBranch        *b_Dplus_ORIVX_ZERR;   //!
   TBranch        *b_Dplus_ORIVX_CHI2;   //!
   TBranch        *b_Dplus_ORIVX_NDOF;   //!
   TBranch        *b_Dplus_ORIVX_COV_;   //!
   TBranch        *b_Dplus_FD_ORIVX;   //!
   TBranch        *b_Dplus_FDCHI2_ORIVX;   //!
   TBranch        *b_Dplus_DIRA_ORIVX;   //!
   TBranch        *b_Dplus_P;   //!
   TBranch        *b_Dplus_PT;   //!
   TBranch        *b_Dplus_PE;   //!
   TBranch        *b_Dplus_PX;   //!
   TBranch        *b_Dplus_PY;   //!
   TBranch        *b_Dplus_PZ;   //!
   TBranch        *b_Dplus_MM;   //!
   TBranch        *b_Dplus_MMERR;   //!
   TBranch        *b_Dplus_M;   //!
   TBranch        *b_Dplus_ID;   //!
   TBranch        *b_Dplus_TAU;   //!
   TBranch        *b_Dplus_TAUERR;   //!
   TBranch        *b_Dplus_TAUCHI2;   //!
   TBranch        *b_Dplus_X;   //!
   TBranch        *b_Dplus_Y;   //!
   TBranch        *b_Dplus_LOKI_VertexSeparation_CHI2;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_LOKI_ENERGY;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_LOKI_ETA;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_LOKI_PHI;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_X;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_Y;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_Z;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_XERR;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_YERR;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_ZERR;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_CHI2;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_NDOF;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_OWNPV_COV_;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_IP_OWNPV;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_IPCHI2_OWNPV;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_X;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_Y;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_Z;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_XERR;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_YERR;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_ZERR;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_CHI2;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_NDOF;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ORIVX_COV_;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_P;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PT;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PE;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PX;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PY;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PZ;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_M;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ID;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PIDe;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PIDmu;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PIDK;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PIDp;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ProbNNe;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ProbNNk;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ProbNNp;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ProbNNpi;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ProbNNmu;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_ProbNNghost;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_hasMuon;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_isMuon;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_hasRich;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_hasCalo;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_UsedRichAerogel;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_UsedRich1Gas;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_UsedRich2Gas;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichAboveElThres;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichAboveMuThres;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichAbovePiThres;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichAboveKaThres;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichAbovePrThres;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichDLLe;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichDLLmu;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichDLLpi;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichDLLk;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichDLLp;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_RichDLLbt;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_InAccMuon;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_isMuonLoose;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_MuonMuLL;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_MuonBkgLL;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_MuonNShared;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_InAccEcal;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_CaloEcalE;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_EcalPIDe;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_EcalPIDmu;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_InAccHcal;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_CaloHcalE;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_HcalPIDe;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_HcalPIDmu;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_InAccPrs;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_PrsPIDe;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_CaloPrsE;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_InAccSpd;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_CaloSpdE;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_InAccBrem;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_BremPIDe;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_VeloCharge;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_Type;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_Key;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_CHI2;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_NDOF;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_PCHI2;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_TCHI2NDOF;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_VELO_UTID;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_FirstMeasurementX;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_FirstMeasurementY;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_MatchCHI2;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_GhostProb;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_CloneDist;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_TRACK_Likelihood;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_X;   //!
   TBranch        *b_Dplus_Kminus_or_piminus_Y;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_LOKI_ENERGY;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_LOKI_ETA;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_LOKI_PHI;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_X;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_Y;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_Z;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_XERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_YERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_ZERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_CHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_OWNPV_COV_;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_IP_OWNPV;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_IPCHI2_OWNPV;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_X;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_Y;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_Z;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_XERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_YERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_ZERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_CHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ORIVX_COV_;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_P;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PT;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PX;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PY;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PZ;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_M;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ID;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PIDmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PIDK;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PIDp;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ProbNNe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ProbNNk;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ProbNNp;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ProbNNpi;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ProbNNmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_ProbNNghost;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_hasMuon;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_isMuon;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_hasRich;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_hasCalo;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_UsedRichAerogel;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_UsedRich1Gas;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_UsedRich2Gas;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichAboveElThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichAboveMuThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichAbovePiThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichAboveKaThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichAbovePrThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichDLLe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichDLLmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichDLLpi;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichDLLk;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichDLLp;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_RichDLLbt;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_InAccMuon;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_isMuonLoose;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_MuonMuLL;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_MuonBkgLL;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_MuonNShared;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_InAccEcal;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_CaloEcalE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_EcalPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_EcalPIDmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_InAccHcal;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_CaloHcalE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_HcalPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_HcalPIDmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_InAccPrs;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_PrsPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_CaloPrsE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_InAccSpd;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_CaloSpdE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_InAccBrem;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_BremPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_VeloCharge;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_Type;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_Key;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_CHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_CHI2NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_PCHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_TCHI2NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_VELO_UTID;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementX;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementY;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_MatchCHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_GhostProb;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_CloneDist;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_TRACK_Likelihood;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_X;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_One_Y;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_LOKI_ENERGY;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_LOKI_ETA;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_LOKI_PHI;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_X;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_Y;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_Z;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_XERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_YERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_ZERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_CHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_OWNPV_COV_;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_IP_OWNPV;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_IPCHI2_OWNPV;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_X;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_Y;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_Z;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_XERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_YERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_ZERR;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_CHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ORIVX_COV_;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_P;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PT;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PX;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PY;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PZ;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_M;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ID;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PIDmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PIDK;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PIDp;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ProbNNe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ProbNNk;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ProbNNp;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ProbNNpi;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ProbNNmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_ProbNNghost;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_hasMuon;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_isMuon;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_hasRich;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_hasCalo;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_UsedRichAerogel;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_UsedRich1Gas;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_UsedRich2Gas;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichAboveElThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichAboveMuThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichAbovePiThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichAboveKaThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichAbovePrThres;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichDLLe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichDLLmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichDLLpi;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichDLLk;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichDLLp;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_RichDLLbt;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_InAccMuon;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_isMuonLoose;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_MuonMuLL;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_MuonBkgLL;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_MuonNShared;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_InAccEcal;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_CaloEcalE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_EcalPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_EcalPIDmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_InAccHcal;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_CaloHcalE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_HcalPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_HcalPIDmu;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_InAccPrs;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_PrsPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_CaloPrsE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_InAccSpd;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_CaloSpdE;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_InAccBrem;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_BremPIDe;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_VeloCharge;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_Type;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_Key;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_CHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_CHI2NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_PCHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_TCHI2NDOF;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_VELO_UTID;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementX;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementY;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_MatchCHI2;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_GhostProb;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_CloneDist;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_TRACK_Likelihood;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_X;   //!
   TBranch        *b_Dplus_piplus_or_Kplus_Two_Y;   //!
   TBranch        *b_Dminus_LOKI_ENERGY;   //!
   TBranch        *b_Dminus_LOKI_ETA;   //!
   TBranch        *b_Dminus_LOKI_PHI;   //!
   TBranch        *b_Dminus_ENDVERTEX_X;   //!
   TBranch        *b_Dminus_ENDVERTEX_Y;   //!
   TBranch        *b_Dminus_ENDVERTEX_Z;   //!
   TBranch        *b_Dminus_ENDVERTEX_XERR;   //!
   TBranch        *b_Dminus_ENDVERTEX_YERR;   //!
   TBranch        *b_Dminus_ENDVERTEX_ZERR;   //!
   TBranch        *b_Dminus_ENDVERTEX_CHI2;   //!
   TBranch        *b_Dminus_ENDVERTEX_NDOF;   //!
   TBranch        *b_Dminus_ENDVERTEX_COV_;   //!
   TBranch        *b_Dminus_OWNPV_X;   //!
   TBranch        *b_Dminus_OWNPV_Y;   //!
   TBranch        *b_Dminus_OWNPV_Z;   //!
   TBranch        *b_Dminus_OWNPV_XERR;   //!
   TBranch        *b_Dminus_OWNPV_YERR;   //!
   TBranch        *b_Dminus_OWNPV_ZERR;   //!
   TBranch        *b_Dminus_OWNPV_CHI2;   //!
   TBranch        *b_Dminus_OWNPV_NDOF;   //!
   TBranch        *b_Dminus_OWNPV_COV_;   //!
   TBranch        *b_Dminus_IP_OWNPV;   //!
   TBranch        *b_Dminus_IPCHI2_OWNPV;   //!
   TBranch        *b_Dminus_FD_OWNPV;   //!
   TBranch        *b_Dminus_FDCHI2_OWNPV;   //!
   TBranch        *b_Dminus_DIRA_OWNPV;   //!
   TBranch        *b_Dminus_ORIVX_X;   //!
   TBranch        *b_Dminus_ORIVX_Y;   //!
   TBranch        *b_Dminus_ORIVX_Z;   //!
   TBranch        *b_Dminus_ORIVX_XERR;   //!
   TBranch        *b_Dminus_ORIVX_YERR;   //!
   TBranch        *b_Dminus_ORIVX_ZERR;   //!
   TBranch        *b_Dminus_ORIVX_CHI2;   //!
   TBranch        *b_Dminus_ORIVX_NDOF;   //!
   TBranch        *b_Dminus_ORIVX_COV_;   //!
   TBranch        *b_Dminus_FD_ORIVX;   //!
   TBranch        *b_Dminus_FDCHI2_ORIVX;   //!
   TBranch        *b_Dminus_DIRA_ORIVX;   //!
   TBranch        *b_Dminus_P;   //!
   TBranch        *b_Dminus_PT;   //!
   TBranch        *b_Dminus_PE;   //!
   TBranch        *b_Dminus_PX;   //!
   TBranch        *b_Dminus_PY;   //!
   TBranch        *b_Dminus_PZ;   //!
   TBranch        *b_Dminus_MM;   //!
   TBranch        *b_Dminus_MMERR;   //!
   TBranch        *b_Dminus_M;   //!
   TBranch        *b_Dminus_ID;   //!
   TBranch        *b_Dminus_TAU;   //!
   TBranch        *b_Dminus_TAUERR;   //!
   TBranch        *b_Dminus_TAUCHI2;   //!
   TBranch        *b_Dminus_X;   //!
   TBranch        *b_Dminus_Y;   //!
   TBranch        *b_Dminus_LOKI_VertexSeparation_CHI2;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_LOKI_ENERGY;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_LOKI_ETA;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_LOKI_PHI;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_X;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_Y;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_Z;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_XERR;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_YERR;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_ZERR;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_CHI2;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_NDOF;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_OWNPV_COV_;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_IP_OWNPV;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_IPCHI2_OWNPV;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_X;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_Y;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_Z;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_XERR;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_YERR;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_ZERR;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_CHI2;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_NDOF;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ORIVX_COV_;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_P;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PT;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PE;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PX;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PY;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PZ;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_M;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ID;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PIDe;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PIDmu;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PIDK;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PIDp;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ProbNNe;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ProbNNk;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ProbNNp;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ProbNNpi;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ProbNNmu;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_ProbNNghost;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_hasMuon;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_isMuon;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_hasRich;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_hasCalo;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_UsedRichAerogel;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_UsedRich1Gas;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_UsedRich2Gas;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichAboveElThres;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichAboveMuThres;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichAbovePiThres;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichAboveKaThres;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichAbovePrThres;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichDLLe;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichDLLmu;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichDLLpi;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichDLLk;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichDLLp;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_RichDLLbt;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_InAccMuon;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_isMuonLoose;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_MuonMuLL;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_MuonBkgLL;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_MuonNShared;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_InAccEcal;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_CaloEcalE;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_EcalPIDe;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_EcalPIDmu;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_InAccHcal;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_CaloHcalE;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_HcalPIDe;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_HcalPIDmu;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_InAccPrs;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_PrsPIDe;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_CaloPrsE;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_InAccSpd;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_CaloSpdE;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_InAccBrem;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_BremPIDe;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_VeloCharge;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_Type;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_Key;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_CHI2;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_NDOF;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_PCHI2;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_TCHI2NDOF;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_VELO_UTID;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_FirstMeasurementX;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_FirstMeasurementY;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_MatchCHI2;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_GhostProb;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_CloneDist;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_TRACK_Likelihood;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_X;   //!
   TBranch        *b_Dminus_Kplus_or_piplus_Y;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_LOKI_ENERGY;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_LOKI_ETA;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_LOKI_PHI;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_X;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_Y;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_Z;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_XERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_YERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_ZERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_CHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_OWNPV_COV_;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_IP_OWNPV;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_IPCHI2_OWNPV;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_X;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_Y;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_Z;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_XERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_YERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_ZERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_CHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ORIVX_COV_;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_P;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PT;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PX;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PY;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PZ;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_M;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ID;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PIDmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PIDK;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PIDp;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ProbNNe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ProbNNk;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ProbNNp;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ProbNNpi;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ProbNNmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_ProbNNghost;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_hasMuon;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_isMuon;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_hasRich;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_hasCalo;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_UsedRichAerogel;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_UsedRich1Gas;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_UsedRich2Gas;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichAboveElThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichAboveMuThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichAbovePiThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichAboveKaThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichAbovePrThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichDLLe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichDLLmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichDLLpi;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichDLLk;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichDLLp;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_RichDLLbt;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_InAccMuon;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_isMuonLoose;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_MuonMuLL;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_MuonBkgLL;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_MuonNShared;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_InAccEcal;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_CaloEcalE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_EcalPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_EcalPIDmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_InAccHcal;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_CaloHcalE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_HcalPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_HcalPIDmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_InAccPrs;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_PrsPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_CaloPrsE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_InAccSpd;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_CaloSpdE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_InAccBrem;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_BremPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_VeloCharge;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_Type;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_Key;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_CHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_CHI2NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_PCHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_TCHI2NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_VELO_UTID;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementX;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementY;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_MatchCHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_GhostProb;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_CloneDist;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_TRACK_Likelihood;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_X;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_One_Y;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_LOKI_ENERGY;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_LOKI_ETA;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_LOKI_PHI;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_X;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_Y;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_Z;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_XERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_YERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_ZERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_CHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_OWNPV_COV_;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_IP_OWNPV;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_IPCHI2_OWNPV;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_X;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_Y;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_Z;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_XERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_YERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_ZERR;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_CHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ORIVX_COV_;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_P;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PT;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PX;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PY;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PZ;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_M;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ID;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PIDmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PIDK;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PIDp;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ProbNNe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ProbNNk;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ProbNNp;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ProbNNpi;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ProbNNmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_ProbNNghost;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_hasMuon;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_isMuon;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_hasRich;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_hasCalo;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_UsedRichAerogel;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_UsedRich1Gas;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_UsedRich2Gas;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichAboveElThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichAboveMuThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichAbovePiThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichAboveKaThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichAbovePrThres;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichDLLe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichDLLmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichDLLpi;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichDLLk;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichDLLp;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_RichDLLbt;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_InAccMuon;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_isMuonLoose;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_MuonMuLL;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_MuonBkgLL;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_MuonNShared;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_InAccEcal;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_CaloEcalE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_EcalPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_EcalPIDmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_InAccHcal;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_CaloHcalE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_HcalPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_HcalPIDmu;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_InAccPrs;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_PrsPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_CaloPrsE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_InAccSpd;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_CaloSpdE;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_InAccBrem;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_BremPIDe;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_VeloCharge;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_Type;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_Key;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_CHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_CHI2NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_PCHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_TCHI2NDOF;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_VELO_UTID;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementX;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementY;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_MatchCHI2;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_GhostProb;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_CloneDist;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_TRACK_Likelihood;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_X;   //!
   TBranch        *b_Dminus_piminus_or_Kminus_Two_Y;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_BCType;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLTTCK;   //!
   TBranch        *b_GpsTime;   //!
   TBranch        *b_GpsYear;   //!
   TBranch        *b_GpsMonth;   //!
   TBranch        *b_GpsDay;   //!
   TBranch        *b_GpsHour;   //!
   TBranch        *b_GpsMinute;   //!
   TBranch        *b_GpsSecond;   //!
   TBranch        *b_TriggerType;   //!
   TBranch        *b_Polarity;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_PVX;   //!
   TBranch        *b_PVY;   //!
   TBranch        *b_PVZ;   //!
   TBranch        *b_PVXERR;   //!
   TBranch        *b_PVYERR;   //!
   TBranch        *b_PVZERR;   //!
   TBranch        *b_PVCHI2;   //!
   TBranch        *b_PVNDOF;   //!
   TBranch        *b_PVNTRACKS;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_nLongTracks;   //!
   TBranch        *b_nDownstreamTracks;   //!
   TBranch        *b_nUpstreamTracks;   //!
   TBranch        *b_nVeloTracks;   //!
   TBranch        *b_nTTracks;   //!
   TBranch        *b_nBackTracks;   //!
   TBranch        *b_nRich1Hits;   //!
   TBranch        *b_nRich2Hits;   //!
   TBranch        *b_nVeloClusters;   //!
   TBranch        *b_nITClusters;   //!
   TBranch        *b_nTTClusters;   //!
   TBranch        *b_nOTClusters;   //!
   TBranch        *b_nSPDHits;   //!
   TBranch        *b_nMuonCoordsS0;   //!
   TBranch        *b_nMuonCoordsS1;   //!
   TBranch        *b_nMuonCoordsS2;   //!
   TBranch        *b_nMuonCoordsS3;   //!
   TBranch        *b_nMuonCoordsS4;   //!
   TBranch        *b_nMuonTracks;   //!
   TBranch        *b_StrippingB02DDBeauty2CharmLineDecision;   //!
   TBranch        *b_L0Global;   //!
   TBranch        *b_Hlt1Global;   //!
   TBranch        *b_Hlt2Global;   //!
   TBranch        *b_L0PhysicsDecision;   //!
   TBranch        *b_L0MuonDecision;   //!
   TBranch        *b_L0DiMuonDecision;   //!
   TBranch        *b_L0MuonHighDecision;   //!
   TBranch        *b_L0HadronDecision;   //!
   TBranch        *b_L0ElectronDecision;   //!
   TBranch        *b_L0PhotonDecision;   //!
   TBranch        *b_L0nSelections;   //!
   TBranch        *b_Hlt1TrackAllL0Decision;   //!
   TBranch        *b_Hlt1TrackAllL0TightDecision;   //!
   TBranch        *b_Hlt1L0AnyDecision;   //!
   TBranch        *b_Hlt1GlobalDecision;   //!
   TBranch        *b_Hlt1nSelections;   //!
   TBranch        *b_Hlt2GlobalDecision;   //!
   TBranch        *b_Hlt2Topo2BodySimpleDecision;   //!
   TBranch        *b_Hlt2Topo3BodySimpleDecision;   //!
   TBranch        *b_Hlt2Topo4BodySimpleDecision;   //!
   TBranch        *b_Hlt2Topo2BodyBBDTDecision;   //!
   TBranch        *b_Hlt2Topo3BodyBBDTDecision;   //!
   TBranch        *b_Hlt2Topo4BodyBBDTDecision;   //!
   TBranch        *b_Hlt2TopoMu2BodyBBDTDecision;   //!
   TBranch        *b_Hlt2TopoMu3BodyBBDTDecision;   //!
   TBranch        *b_Hlt2TopoMu4BodyBBDTDecision;   //!
   TBranch        *b_Hlt2TopoE2BodyBBDTDecision;   //!
   TBranch        *b_Hlt2TopoE3BodyBBDTDecision;   //!
   TBranch        *b_Hlt2TopoE4BodyBBDTDecision;   //!
   TBranch        *b_Hlt2IncPhiDecision;   //!
   TBranch        *b_Hlt2IncPhiSidebandsDecision;   //!
   TBranch        *b_Hlt2nSelections;   //!
   TBranch        *b_MaxRoutingBits;   //!
   TBranch        *b_RoutingBits;   //!
   TBranch        *b_obsMassDDPVConst;   //!
   TBranch        *b_obsMassErrDDPVConst;   //!
   TBranch        *b_obsMassPVConst;   //!
   TBranch        *b_obsMassErrPVConst;   //!
   TBranch        *b_obsMassDauOne;   //!
   TBranch        *b_obsMassErrDauOne;   //!
   TBranch        *b_obsMassDauTwo;   //!
   TBranch        *b_obsMassErrDauTwo;   //!
   TBranch        *b_obsMassLokiDDPVConst;   //!
   TBranch        *b_obsMassErrLokiDDPVConst;   //!
   TBranch        *b_obsMassLokiDauOne;   //!
   TBranch        *b_obsMassErrLokiDauOne;   //!
   TBranch        *b_obsMassLokiDauTwo;   //!
   TBranch        *b_obsMassErrLokiDauTwo;   //!
   TBranch        *b_obsMass;   //!
   TBranch        *b_obsMassErr;   //!
   TBranch        *b_obsTime;   //!
   TBranch        *b_obsTimeErr;   //!
   TBranch        *b_varDplusTauSignificance;   //!
   TBranch        *b_varDminusTauSignificance;   //!
   TBranch        *b_varDMinTauSignificance;   //!
   TBranch        *b_varDMaxTauSignificance;   //!
   TBranch        *b_varKSMassHypo_DplusOne;   //!
   TBranch        *b_varKSMassHypo_DplusTwo;   //!
   TBranch        *b_varKSMassHypo_DminusOne;   //!
   TBranch        *b_varKSMassHypo_DminusTwo;   //!
   TBranch        *b_varDplusMassHypo_Kpipi;   //!
   TBranch        *b_varDminusMassHypo_Kpipi;   //!
   TBranch        *b_varDplusMassHypo_KKpi;   //!
   TBranch        *b_varDminusMassHypo_KKpi;   //!
   TBranch        *b_varDplusMassHypo_KpiK;   //!
   TBranch        *b_varDminusMassHypo_KpiK;   //!
   TBranch        *b_varDplusMassHypo_KKK;   //!
   TBranch        *b_varDminusMassHypo_KKK;   //!
   TBranch        *b_varDplusMassHypo_pipipi;   //!
   TBranch        *b_varDminusMassHypo_pipipi;   //!
   TBranch        *b_varDplusMassHypo_pipiK;   //!
   TBranch        *b_varDminusMassHypo_pipiK;   //!
   TBranch        *b_varDplusMassHypo_piKpi;   //!
   TBranch        *b_varDminusMassHypo_piKpi;   //!
   TBranch        *b_varDplusMassHypo_piKK;   //!
   TBranch        *b_varDminusMassHypo_piKK;   //!
   TBranch        *b_varDplusMassHypo_Kppi;   //!
   TBranch        *b_varDminusMassHypo_Kppi;   //!
   TBranch        *b_varDplusMassHypo_Kpip;   //!
   TBranch        *b_varDminusMassHypo_Kpip;   //!
   TBranch        *b_varDplusMassHypo_pKpi;   //!
   TBranch        *b_varDminusMassHypo_pKpi;   //!
   TBranch        *b_varDplusMassHypo_ppiK;   //!
   TBranch        *b_varDminusMassHypo_ppiK;   //!
   TBranch        *b_varDplusMassHypo_pipK;   //!
   TBranch        *b_varDminusMassHypo_pipK;   //!
   TBranch        *b_varDplusMassHypo_piKp;   //!
   TBranch        *b_varDminusMassHypo_piKp;   //!
   TBranch        *b_varDplusMassHypo_ppipi;   //!
   TBranch        *b_varDminusMassHypo_ppipi;   //!
   TBranch        *b_varDplusMassHypo_pippi;   //!
   TBranch        *b_varDminusMassHypo_pippi;   //!
   TBranch        *b_varDplusMassHypo_pipip;   //!
   TBranch        *b_varDminusMassHypo_pipip;   //!
   TBranch        *b_varBMassHypo_Dpluspipi;   //!
   TBranch        *b_varBMassHypo_Dminuspipi;   //!
   TBranch        *b_varBMassHypo_DplusKpi;   //!
   TBranch        *b_varBMassHypo_DminusKpi;   //!
   TBranch        *b_varBMassHypo_DpluspiK;   //!
   TBranch        *b_varBMassHypo_DminuspiK;   //!
   TBranch        *b_varKplusTrackGhostProb;   //!
   TBranch        *b_varKminusTrackGhostProb;   //!
   TBranch        *b_varKaonMaxTrackGhostProb;   //!
   TBranch        *b_varPiplusOneTrackGhostProb;   //!
   TBranch        *b_varPiplusTwoTrackGhostProb;   //!
   TBranch        *b_varPiplusMaxTrackGhostProb;   //!
   TBranch        *b_varPiminusOneTrackGhostProb;   //!
   TBranch        *b_varPiminusTwoTrackGhostProb;   //!
   TBranch        *b_varPiminusMaxTrackGhostProb;   //!
   TBranch        *b_varPionMaxTrackGhostProb;   //!
   TBranch        *b_varPVVtxChi2ndof;   //!
   TBranch        *b_varPVVtxChi2ndof_log;   //!
   TBranch        *b_varDMinVtxSepChi2;   //!
   TBranch        *b_varDMaxVtxSepChi2;   //!
   TBranch        *b_varBEndVtxChi2ndof;   //!
   TBranch        *b_varBEndVtxChi2ndof_log;   //!
   TBranch        *b_varDplusEndVtxChi2ndof;   //!
   TBranch        *b_varDminusEndVtxChi2ndof;   //!
   TBranch        *b_varDMaxEndVtxChi2ndof;   //!
   TBranch        *b_varDDDTFSumPT;   //!
   TBranch        *b_varKaonMaxTrackFitChi2ndof;   //!
   TBranch        *b_varPiplusMaxTrackFitChi2ndof;   //!
   TBranch        *b_varPiminusMaxTrackFitChi2ndof;   //!
   TBranch        *b_varPionMaxTrackFitChi2ndof;   //!
   TBranch        *b_varDplusPionsSumPT;   //!
   TBranch        *b_varDplusDaughtersSumPT;   //!
   TBranch        *b_varDminusPionsSumPT;   //!
   TBranch        *b_varDminusDaughtersSumPT;   //!
   TBranch        *b_varDTFChi2ndof;   //!
   TBranch        *b_varDTFChi2ndof_log;   //!
   TBranch        *b_varIPChi2;   //!
   TBranch        *b_varIPChi2_log;   //!
   TBranch        *b_varDplusIPChi2;   //!
   TBranch        *b_varDminusIPChi2;   //!
   TBranch        *b_varDIPChi2Minimum;   //!
   TBranch        *b_varDIPChi2Maximum;   //!
   TBranch        *b_varPiminusOneIPChi2;   //!
   TBranch        *b_varPiminusTwoIPChi2;   //!
   TBranch        *b_varKplusIPChi2;   //!
   TBranch        *b_varPiplusOneIPChi2;   //!
   TBranch        *b_varPiplusTwoIPChi2;   //!
   TBranch        *b_varKminusIPChi2;   //!
   TBranch        *b_varKaonIPChi2Minimum;   //!
   TBranch        *b_varPionOneIPChi2Minimum;   //!
   TBranch        *b_varPionTwoIPChi2Minimum;   //!
   TBranch        *b_varKaonIPChi2Maximum;   //!
   TBranch        *b_varPionOneIPChi2Maximum;   //!
   TBranch        *b_varPionTwoIPChi2Maximum;   //!
   TBranch        *b_varBDIRAOwnPV;   //!
   TBranch        *b_varDplusDIRAOwnPV;   //!
   TBranch        *b_varDminusDIRAOwnPV;   //!
   TBranch        *b_varDMinDIRA;   //!
   TBranch        *b_varDMaxDIRA;   //!
   TBranch        *b_varDTFPVPosX;   //!
   TBranch        *b_varDTFPVPosY;   //!
   TBranch        *b_varDTFPVPosZ;   //!
   TBranch        *b_obsMomentum;   //!
   TBranch        *b_obsMomentumX;   //!
   TBranch        *b_obsMomentumY;   //!
   TBranch        *b_obsMomentumZ;   //!
   TBranch        *b_obsTransverseMomentum;   //!
   TBranch        *b_obsDTFMomentum;   //!
   TBranch        *b_obsDTFMomentumError;   //!
   TBranch        *b_obsDTFTransverseMomentum;   //!
   TBranch        *b_obsDTFTransverseMomentumError;   //!
   TBranch        *b_varDplusP;   //!
   TBranch        *b_varDplusPT;   //!
   TBranch        *b_varDminusP;   //!
   TBranch        *b_varDminusPT;   //!
   TBranch        *b_varDMinP;   //!
   TBranch        *b_varDMinPT;   //!
   TBranch        *b_varDMaxP;   //!
   TBranch        *b_varDMaxPT;   //!
   TBranch        *b_varPiplusOneP;   //!
   TBranch        *b_varPiplusOnePT;   //!
   TBranch        *b_varPiplusTwoP;   //!
   TBranch        *b_varPiplusTwoPT;   //!
   TBranch        *b_varPiminusOneP;   //!
   TBranch        *b_varPiminusOnePT;   //!
   TBranch        *b_varPiminusTwoP;   //!
   TBranch        *b_varPiminusTwoPT;   //!
   TBranch        *b_varKplusP;   //!
   TBranch        *b_varKplusPT;   //!
   TBranch        *b_varKminusP;   //!
   TBranch        *b_varKminusPT;   //!
   TBranch        *b_varPionOneMinP;   //!
   TBranch        *b_varPionTwoMinP;   //!
   TBranch        *b_varKaonMinP;   //!
   TBranch        *b_varPionOneMinPT;   //!
   TBranch        *b_varPionTwoMinPT;   //!
   TBranch        *b_varPionMinPT;   //!
   TBranch        *b_varKaonMinPT;   //!
   TBranch        *b_varHadronMinPT;   //!
   TBranch        *b_varPionOneMaxP;   //!
   TBranch        *b_varPionTwoMaxP;   //!
   TBranch        *b_varKaonMaxP;   //!
   TBranch        *b_varPionOneMaxPT;   //!
   TBranch        *b_varPionTwoMaxPT;   //!
   TBranch        *b_varPionMaxPT;   //!
   TBranch        *b_varKaonMaxPT;   //!
   TBranch        *b_varHadronMaxPT;   //!
   TBranch        *b_varKminusVELOChi2ndof;   //!
   TBranch        *b_varKplusVELOChi2ndof;   //!
   TBranch        *b_varKaonMinVELOChi2ndof;   //!
   TBranch        *b_varKaonMinVELOChi2ndof_log;   //!
   TBranch        *b_varKaonMaxVELOChi2ndof;   //!
   TBranch        *b_varKaonMaxVELOChi2ndof_log;   //!
   TBranch        *b_varPiplusOneVELOChi2ndof;   //!
   TBranch        *b_varPiplusTwoVELOChi2ndof;   //!
   TBranch        *b_varPiplusMinVELOChi2ndof;   //!
   TBranch        *b_varPiplusMaxVELOChi2ndof;   //!
   TBranch        *b_varPiminusOneVELOChi2ndof;   //!
   TBranch        *b_varPiminusTwoVELOChi2ndof;   //!
   TBranch        *b_varPiminusMinVELOChi2ndof;   //!
   TBranch        *b_varPionMinVELOChi2ndof;   //!
   TBranch        *b_varPionMinVELOChi2ndof_log;   //!
   TBranch        *b_varPiminusMaxVELOChi2ndof;   //!
   TBranch        *b_varPionMaxVELOChi2ndof;   //!
   TBranch        *b_varPionMaxVELOChi2ndof_log;   //!
   TBranch        *b_varHadronMinVELOChi2ndof;   //!
   TBranch        *b_varHadronMinVELOChi2ndof_log;   //!
   TBranch        *b_varHadronMaxVELOChi2ndof;   //!
   TBranch        *b_varHadronMaxVELOChi2ndof_log;   //!
   TBranch        *b_varKminusTChi2ndof;   //!
   TBranch        *b_varKplusTChi2ndof;   //!
   TBranch        *b_varKaonMinTChi2ndof;   //!
   TBranch        *b_varKaonMinTChi2ndof_log;   //!
   TBranch        *b_varKaonMaxTChi2ndof;   //!
   TBranch        *b_varKaonMaxTChi2ndof_log;   //!
   TBranch        *b_varPiplusOneTChi2ndof;   //!
   TBranch        *b_varPiplusTwoTChi2ndof;   //!
   TBranch        *b_varPiplusMinTChi2ndof;   //!
   TBranch        *b_varPiplusMaxTChi2ndof;   //!
   TBranch        *b_varPiminusOneTChi2ndof;   //!
   TBranch        *b_varPiminusTwoTChi2ndof;   //!
   TBranch        *b_varPiminusMinTChi2ndof;   //!
   TBranch        *b_varPionMinTChi2ndof;   //!
   TBranch        *b_varPionMinTChi2ndof_log;   //!
   TBranch        *b_varPiminusMaxTChi2ndof;   //!
   TBranch        *b_varPionMaxTChi2ndof;   //!
   TBranch        *b_varPionMaxTChi2ndof_log;   //!
   TBranch        *b_varHadronMinTChi2ndof;   //!
   TBranch        *b_varHadronMinTChi2ndof_log;   //!
   TBranch        *b_varHadronMaxTChi2ndof;   //!
   TBranch        *b_varHadronMaxTChi2ndof_log;   //!
   TBranch        *b_varKminusMatchChi2;   //!
   TBranch        *b_varKplusMatchChi2;   //!
   TBranch        *b_varKaonMinMatchChi2;   //!
   TBranch        *b_varKaonMinMatchChi2_log;   //!
   TBranch        *b_varKaonMaxMatchChi2;   //!
   TBranch        *b_varKaonMaxMatchChi2_log;   //!
   TBranch        *b_varPiplusOneMatchChi2;   //!
   TBranch        *b_varPiplusTwoMatchChi2;   //!
   TBranch        *b_varPiplusMinMatchChi2;   //!
   TBranch        *b_varPiplusMaxMatchChi2;   //!
   TBranch        *b_varPiminusOneMatchChi2;   //!
   TBranch        *b_varPiminusTwoMatchChi2;   //!
   TBranch        *b_varPiminusMinMatchChi2;   //!
   TBranch        *b_varPionMinMatchChi2;   //!
   TBranch        *b_varPionMinMatchChi2_log;   //!
   TBranch        *b_varPiminusMaxMatchChi2;   //!
   TBranch        *b_varPionMaxMatchChi2;   //!
   TBranch        *b_varPionMaxMatchChi2_log;   //!
   TBranch        *b_varHadronMinMatchChi2;   //!
   TBranch        *b_varHadronMinMatchChi2_log;   //!
   TBranch        *b_varHadronMaxMatchChi2;   //!
   TBranch        *b_varHadronMaxMatchChi2_log;   //!
   TBranch        *b_catTriggerL0GlobalTOS;   //!
   TBranch        *b_catTriggerHlt1GlobalTOS;   //!
   TBranch        *b_catTriggerHlt2GlobalTOS;   //!
   TBranch        *b_catTriggerHlt2Topo2BodyBBDTTOS;   //!
   TBranch        *b_catTriggerHlt2Topo3BodyBBDTTOS;   //!
   TBranch        *b_catTriggerHlt2Topo4BodyBBDTTOS;   //!
   TBranch        *b_catTriggerHlt2IncPhiTOS;   //!
   TBranch        *b_catTriggerSetTopo234BodyBBDT;   //!
   TBranch        *b_idxRandom;   //!
   TBranch        *b_catDplusFinalState;   //!
   TBranch        *b_catDminusFinalState;   //!
   TBranch        *b_catDDFinalState;   //!
   TBranch        *b_idxEventNumber;   //!
   TBranch        *b_idxRunNumber;   //!
   TBranch        *b_catNPV;   //!
   TBranch        *b_catMag;   //!
   TBranch        *b_catNTrack;   //!
   TBranch        *b_catYear;   //!
   TBranch        *b_varDTFStatusPVConst;   //!
   TBranch        *b_varDTFStatusDDPVConst;   //!
   TBranch        *b_varDTFChi2ndof_log_tmvafloatcopy;   //!
   TBranch        *b_varBEndVtxChi2ndof_log_tmvafloatcopy;   //!
   TBranch        *b_varIPChi2_log_tmvafloatcopy;   //!
   TBranch        *b_varBDIRAOwnPV_tmvafloatcopy;   //!
   TBranch        *b_varDMinTauSignificance_tmvafloatcopy;   //!
   TBranch        *b_varDMinPT_tmvafloatcopy;   //!
   TBranch        *b_varDDDTFSumPT_tmvafloatcopy;   //!
   TBranch        *b_varKaonMinPT_tmvafloatcopy;   //!
   TBranch        *b_varPionOneMinPT_tmvafloatcopy;   //!
   TBranch        *b_varPionTwoMinPT_tmvafloatcopy;   //!
   TBranch        *b_varPVVtxChi2ndof_log_tmvafloatcopy;   //!
   TBranch        *b_varKaonMinVELOChi2ndof_log_tmvafloatcopy;   //!
   TBranch        *b_varKaonMinTChi2ndof_log_tmvafloatcopy;   //!
   TBranch        *b_varKaonMinMatchChi2_log_tmvafloatcopy;   //!
   TBranch        *b_varPionMinVELOChi2ndof_log_tmvafloatcopy;   //!
   TBranch        *b_varPionMinTChi2ndof_log_tmvafloatcopy;   //!
   TBranch        *b_varPionMinMatchChi2_log_tmvafloatcopy;   //!
   TBranch        *b_BDT1_classifier;   //!
   TBranch        *b_BDT2_classifier;   //!
   TBranch        *b_BDTG1_classifier;   //!
   TBranch        *b_BDTG2_classifier;   //!

   b2dd(TTree *tree=0);
   virtual ~b2dd();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef b2dd_cxx
b2dd::b2dd(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
   //  TFile* f = TFile::Open("root://eos/lhcb/wg/b2oc/b02dd/DT2012_B02DD_Stripping21_DVv36r5_20150514_pseyfert_combined_KKpifinalstates_withDs.root");
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("DT2012_B02DD_Stripping21_DVv36r1_20150322_fmeier_combined_20150412_fmeier_BDT_TupleB_Kpipi.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("DT2012_B02DD_Stripping21_DVv36r1_20150322_fmeier_combined_20150412_fmeier_BDT_TupleB_Kpipi.root");
      }
      f->GetObject("B02DD",tree);

   }
   Init(tree);
}

b2dd::~b2dd()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t b2dd::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t b2dd::LoadTree(Long64_t entry)
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

void b2dd::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("B0_LOKI_ENERGY", &B0_LOKI_ENERGY, &b_B0_LOKI_ENERGY);
   fChain->SetBranchAddress("B0_LOKI_ETA", &B0_LOKI_ETA, &b_B0_LOKI_ETA);
   fChain->SetBranchAddress("B0_LOKI_PHI", &B0_LOKI_PHI, &b_B0_LOKI_PHI);
   fChain->SetBranchAddress("B0_ENDVERTEX_X", &B0_ENDVERTEX_X, &b_B0_ENDVERTEX_X);
   fChain->SetBranchAddress("B0_ENDVERTEX_Y", &B0_ENDVERTEX_Y, &b_B0_ENDVERTEX_Y);
   fChain->SetBranchAddress("B0_ENDVERTEX_Z", &B0_ENDVERTEX_Z, &b_B0_ENDVERTEX_Z);
   fChain->SetBranchAddress("B0_ENDVERTEX_XERR", &B0_ENDVERTEX_XERR, &b_B0_ENDVERTEX_XERR);
   fChain->SetBranchAddress("B0_ENDVERTEX_YERR", &B0_ENDVERTEX_YERR, &b_B0_ENDVERTEX_YERR);
   fChain->SetBranchAddress("B0_ENDVERTEX_ZERR", &B0_ENDVERTEX_ZERR, &b_B0_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("B0_ENDVERTEX_CHI2", &B0_ENDVERTEX_CHI2, &b_B0_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("B0_ENDVERTEX_NDOF", &B0_ENDVERTEX_NDOF, &b_B0_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("B0_ENDVERTEX_COV_", B0_ENDVERTEX_COV_, &b_B0_ENDVERTEX_COV_);
   fChain->SetBranchAddress("B0_OWNPV_X", &B0_OWNPV_X, &b_B0_OWNPV_X);
   fChain->SetBranchAddress("B0_OWNPV_Y", &B0_OWNPV_Y, &b_B0_OWNPV_Y);
   fChain->SetBranchAddress("B0_OWNPV_Z", &B0_OWNPV_Z, &b_B0_OWNPV_Z);
   fChain->SetBranchAddress("B0_OWNPV_XERR", &B0_OWNPV_XERR, &b_B0_OWNPV_XERR);
   fChain->SetBranchAddress("B0_OWNPV_YERR", &B0_OWNPV_YERR, &b_B0_OWNPV_YERR);
   fChain->SetBranchAddress("B0_OWNPV_ZERR", &B0_OWNPV_ZERR, &b_B0_OWNPV_ZERR);
   fChain->SetBranchAddress("B0_OWNPV_CHI2", &B0_OWNPV_CHI2, &b_B0_OWNPV_CHI2);
   fChain->SetBranchAddress("B0_OWNPV_NDOF", &B0_OWNPV_NDOF, &b_B0_OWNPV_NDOF);
   fChain->SetBranchAddress("B0_OWNPV_COV_", B0_OWNPV_COV_, &b_B0_OWNPV_COV_);
   fChain->SetBranchAddress("B0_IP_OWNPV", &B0_IP_OWNPV, &b_B0_IP_OWNPV);
   fChain->SetBranchAddress("B0_IPCHI2_OWNPV", &B0_IPCHI2_OWNPV, &b_B0_IPCHI2_OWNPV);
   fChain->SetBranchAddress("B0_FD_OWNPV", &B0_FD_OWNPV, &b_B0_FD_OWNPV);
   fChain->SetBranchAddress("B0_FDCHI2_OWNPV", &B0_FDCHI2_OWNPV, &b_B0_FDCHI2_OWNPV);
   fChain->SetBranchAddress("B0_DIRA_OWNPV", &B0_DIRA_OWNPV, &b_B0_DIRA_OWNPV);
   fChain->SetBranchAddress("B0_P", &B0_P, &b_B0_P);
   fChain->SetBranchAddress("B0_PT", &B0_PT, &b_B0_PT);
   fChain->SetBranchAddress("B0_PE", &B0_PE, &b_B0_PE);
   fChain->SetBranchAddress("B0_PX", &B0_PX, &b_B0_PX);
   fChain->SetBranchAddress("B0_PY", &B0_PY, &b_B0_PY);
   fChain->SetBranchAddress("B0_PZ", &B0_PZ, &b_B0_PZ);
   fChain->SetBranchAddress("B0_MM", &B0_MM, &b_B0_MM);
   fChain->SetBranchAddress("B0_MMERR", &B0_MMERR, &b_B0_MMERR);
   fChain->SetBranchAddress("B0_M", &B0_M, &b_B0_M);
   fChain->SetBranchAddress("B0_ID", &B0_ID, &b_B0_ID);
   fChain->SetBranchAddress("B0_TAU", &B0_TAU, &b_B0_TAU);
   fChain->SetBranchAddress("B0_TAUERR", &B0_TAUERR, &b_B0_TAUERR);
   fChain->SetBranchAddress("B0_TAUCHI2", &B0_TAUCHI2, &b_B0_TAUCHI2);
   fChain->SetBranchAddress("B0_X", &B0_X, &b_B0_X);
   fChain->SetBranchAddress("B0_Y", &B0_Y, &b_B0_Y);
   fChain->SetBranchAddress("B0_LOKI_DIRA", &B0_LOKI_DIRA, &b_B0_LOKI_DIRA);
   fChain->SetBranchAddress("B0_LOKI_DTF_CHI2NDOF", &B0_LOKI_DTF_CHI2NDOF, &b_B0_LOKI_DTF_CHI2NDOF);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAU", &B0_LOKI_DTF_CTAU, &b_B0_LOKI_DTF_CTAU);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAUERR", &B0_LOKI_DTF_CTAUERR, &b_B0_LOKI_DTF_CTAUERR);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAUERR_D1", &B0_LOKI_DTF_CTAUERR_D1, &b_B0_LOKI_DTF_CTAUERR_D1);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAUERR_D2", &B0_LOKI_DTF_CTAUERR_D2, &b_B0_LOKI_DTF_CTAUERR_D2);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAUERR_NOPV", &B0_LOKI_DTF_CTAUERR_NOPV, &b_B0_LOKI_DTF_CTAUERR_NOPV);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAUS", &B0_LOKI_DTF_CTAUS, &b_B0_LOKI_DTF_CTAUS);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAU_D1", &B0_LOKI_DTF_CTAU_D1, &b_B0_LOKI_DTF_CTAU_D1);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAU_D2", &B0_LOKI_DTF_CTAU_D2, &b_B0_LOKI_DTF_CTAU_D2);
   fChain->SetBranchAddress("B0_LOKI_DTF_CTAU_NOPV", &B0_LOKI_DTF_CTAU_NOPV, &b_B0_LOKI_DTF_CTAU_NOPV);
   fChain->SetBranchAddress("B0_LOKI_DTF_VCHI2NDOF", &B0_LOKI_DTF_VCHI2NDOF, &b_B0_LOKI_DTF_VCHI2NDOF);
   fChain->SetBranchAddress("B0_LOKI_FDCHI2", &B0_LOKI_FDCHI2, &b_B0_LOKI_FDCHI2);
   fChain->SetBranchAddress("B0_LOKI_FDS", &B0_LOKI_FDS, &b_B0_LOKI_FDS);
   fChain->SetBranchAddress("B0_LOKI_MASSERR_DDConstr", &B0_LOKI_MASSERR_DDConstr, &b_B0_LOKI_MASSERR_DDConstr);
   fChain->SetBranchAddress("B0_LOKI_MASSERR_DminusConstr", &B0_LOKI_MASSERR_DminusConstr, &b_B0_LOKI_MASSERR_DminusConstr);
   fChain->SetBranchAddress("B0_LOKI_MASSERR_DplusConstr", &B0_LOKI_MASSERR_DplusConstr, &b_B0_LOKI_MASSERR_DplusConstr);
   fChain->SetBranchAddress("B0_LOKI_MASS_DDConstr", &B0_LOKI_MASS_DDConstr, &b_B0_LOKI_MASS_DDConstr);
   fChain->SetBranchAddress("B0_LOKI_MASS_DminusConstr", &B0_LOKI_MASS_DminusConstr, &b_B0_LOKI_MASS_DminusConstr);
   fChain->SetBranchAddress("B0_LOKI_MASS_Dminus_NoPVConstr", &B0_LOKI_MASS_Dminus_NoPVConstr, &b_B0_LOKI_MASS_Dminus_NoPVConstr);
   fChain->SetBranchAddress("B0_LOKI_MASS_DplusConstr", &B0_LOKI_MASS_DplusConstr, &b_B0_LOKI_MASS_DplusConstr);
   fChain->SetBranchAddress("B0_LOKI_MASS_Dplus_NoPVConstr", &B0_LOKI_MASS_Dplus_NoPVConstr, &b_B0_LOKI_MASS_Dplus_NoPVConstr);
   fChain->SetBranchAddress("B0_Fit_nPV", &B0_Fit_nPV, &b_B0_Fit_nPV);
   fChain->SetBranchAddress("B0_Fit_Dminus_IP", B0_Fit_Dminus_IP, &b_B0_Fit_Dminus_IP);
   fChain->SetBranchAddress("B0_Fit_Dminus_IPCHI2", B0_Fit_Dminus_IPCHI2, &b_B0_Fit_Dminus_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dminus_M", B0_Fit_Dminus_M, &b_B0_Fit_Dminus_M);
   fChain->SetBranchAddress("B0_Fit_Dminus_MERR", B0_Fit_Dminus_MERR, &b_B0_Fit_Dminus_MERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P", B0_Fit_Dminus_P, &b_B0_Fit_Dminus_P);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_ID", B0_Fit_Dminus_P0_ID, &b_B0_Fit_Dminus_P0_ID);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_IP", B0_Fit_Dminus_P0_IP, &b_B0_Fit_Dminus_P0_IP);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_IPCHI2", B0_Fit_Dminus_P0_IPCHI2, &b_B0_Fit_Dminus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_P", B0_Fit_Dminus_P0_P, &b_B0_Fit_Dminus_P0_P);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_PE", B0_Fit_Dminus_P0_PE, &b_B0_Fit_Dminus_P0_PE);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_PERR", B0_Fit_Dminus_P0_PERR, &b_B0_Fit_Dminus_P0_PERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_PT", B0_Fit_Dminus_P0_PT, &b_B0_Fit_Dminus_P0_PT);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_PTERR", B0_Fit_Dminus_P0_PTERR, &b_B0_Fit_Dminus_P0_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_PX", B0_Fit_Dminus_P0_PX, &b_B0_Fit_Dminus_P0_PX);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_PY", B0_Fit_Dminus_P0_PY, &b_B0_Fit_Dminus_P0_PY);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_PZ", B0_Fit_Dminus_P0_PZ, &b_B0_Fit_Dminus_P0_PZ);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_X", B0_Fit_Dminus_P0_X, &b_B0_Fit_Dminus_P0_X);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_XERR", B0_Fit_Dminus_P0_XERR, &b_B0_Fit_Dminus_P0_XERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_Y", B0_Fit_Dminus_P0_Y, &b_B0_Fit_Dminus_P0_Y);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_YERR", B0_Fit_Dminus_P0_YERR, &b_B0_Fit_Dminus_P0_YERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_Z", B0_Fit_Dminus_P0_Z, &b_B0_Fit_Dminus_P0_Z);
   fChain->SetBranchAddress("B0_Fit_Dminus_P0_ZERR", B0_Fit_Dminus_P0_ZERR, &b_B0_Fit_Dminus_P0_ZERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_ID", B0_Fit_Dminus_P1_ID, &b_B0_Fit_Dminus_P1_ID);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_IP", B0_Fit_Dminus_P1_IP, &b_B0_Fit_Dminus_P1_IP);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_IPCHI2", B0_Fit_Dminus_P1_IPCHI2, &b_B0_Fit_Dminus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_P", B0_Fit_Dminus_P1_P, &b_B0_Fit_Dminus_P1_P);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_PE", B0_Fit_Dminus_P1_PE, &b_B0_Fit_Dminus_P1_PE);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_PERR", B0_Fit_Dminus_P1_PERR, &b_B0_Fit_Dminus_P1_PERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_PT", B0_Fit_Dminus_P1_PT, &b_B0_Fit_Dminus_P1_PT);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_PTERR", B0_Fit_Dminus_P1_PTERR, &b_B0_Fit_Dminus_P1_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_PX", B0_Fit_Dminus_P1_PX, &b_B0_Fit_Dminus_P1_PX);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_PY", B0_Fit_Dminus_P1_PY, &b_B0_Fit_Dminus_P1_PY);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_PZ", B0_Fit_Dminus_P1_PZ, &b_B0_Fit_Dminus_P1_PZ);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_X", B0_Fit_Dminus_P1_X, &b_B0_Fit_Dminus_P1_X);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_XERR", B0_Fit_Dminus_P1_XERR, &b_B0_Fit_Dminus_P1_XERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_Y", B0_Fit_Dminus_P1_Y, &b_B0_Fit_Dminus_P1_Y);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_YERR", B0_Fit_Dminus_P1_YERR, &b_B0_Fit_Dminus_P1_YERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_Z", B0_Fit_Dminus_P1_Z, &b_B0_Fit_Dminus_P1_Z);
   fChain->SetBranchAddress("B0_Fit_Dminus_P1_ZERR", B0_Fit_Dminus_P1_ZERR, &b_B0_Fit_Dminus_P1_ZERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_ID", B0_Fit_Dminus_P2_ID, &b_B0_Fit_Dminus_P2_ID);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_IP", B0_Fit_Dminus_P2_IP, &b_B0_Fit_Dminus_P2_IP);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_IPCHI2", B0_Fit_Dminus_P2_IPCHI2, &b_B0_Fit_Dminus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_P", B0_Fit_Dminus_P2_P, &b_B0_Fit_Dminus_P2_P);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_PE", B0_Fit_Dminus_P2_PE, &b_B0_Fit_Dminus_P2_PE);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_PERR", B0_Fit_Dminus_P2_PERR, &b_B0_Fit_Dminus_P2_PERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_PT", B0_Fit_Dminus_P2_PT, &b_B0_Fit_Dminus_P2_PT);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_PTERR", B0_Fit_Dminus_P2_PTERR, &b_B0_Fit_Dminus_P2_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_PX", B0_Fit_Dminus_P2_PX, &b_B0_Fit_Dminus_P2_PX);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_PY", B0_Fit_Dminus_P2_PY, &b_B0_Fit_Dminus_P2_PY);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_PZ", B0_Fit_Dminus_P2_PZ, &b_B0_Fit_Dminus_P2_PZ);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_X", B0_Fit_Dminus_P2_X, &b_B0_Fit_Dminus_P2_X);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_XERR", B0_Fit_Dminus_P2_XERR, &b_B0_Fit_Dminus_P2_XERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_Y", B0_Fit_Dminus_P2_Y, &b_B0_Fit_Dminus_P2_Y);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_YERR", B0_Fit_Dminus_P2_YERR, &b_B0_Fit_Dminus_P2_YERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_Z", B0_Fit_Dminus_P2_Z, &b_B0_Fit_Dminus_P2_Z);
   fChain->SetBranchAddress("B0_Fit_Dminus_P2_ZERR", B0_Fit_Dminus_P2_ZERR, &b_B0_Fit_Dminus_P2_ZERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_PERR", B0_Fit_Dminus_PERR, &b_B0_Fit_Dminus_PERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_PT", B0_Fit_Dminus_PT, &b_B0_Fit_Dminus_PT);
   fChain->SetBranchAddress("B0_Fit_Dminus_PTERR", B0_Fit_Dminus_PTERR, &b_B0_Fit_Dminus_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dminus_ctau", B0_Fit_Dminus_ctau, &b_B0_Fit_Dminus_ctau);
   fChain->SetBranchAddress("B0_Fit_Dminus_ctauErr", B0_Fit_Dminus_ctauErr, &b_B0_Fit_Dminus_ctauErr);
   fChain->SetBranchAddress("B0_Fit_Dminus_decayLength", B0_Fit_Dminus_decayLength, &b_B0_Fit_Dminus_decayLength);
   fChain->SetBranchAddress("B0_Fit_Dminus_decayLengthErr", B0_Fit_Dminus_decayLengthErr, &b_B0_Fit_Dminus_decayLengthErr);
   fChain->SetBranchAddress("B0_Fit_Dminus_tau", B0_Fit_Dminus_tau, &b_B0_Fit_Dminus_tau);
   fChain->SetBranchAddress("B0_Fit_Dminus_tauErr", B0_Fit_Dminus_tauErr, &b_B0_Fit_Dminus_tauErr);
   fChain->SetBranchAddress("B0_Fit_Dplus_IP", B0_Fit_Dplus_IP, &b_B0_Fit_Dplus_IP);
   fChain->SetBranchAddress("B0_Fit_Dplus_IPCHI2", B0_Fit_Dplus_IPCHI2, &b_B0_Fit_Dplus_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dplus_M", B0_Fit_Dplus_M, &b_B0_Fit_Dplus_M);
   fChain->SetBranchAddress("B0_Fit_Dplus_MERR", B0_Fit_Dplus_MERR, &b_B0_Fit_Dplus_MERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P", B0_Fit_Dplus_P, &b_B0_Fit_Dplus_P);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_ID", B0_Fit_Dplus_P0_ID, &b_B0_Fit_Dplus_P0_ID);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_IP", B0_Fit_Dplus_P0_IP, &b_B0_Fit_Dplus_P0_IP);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_IPCHI2", B0_Fit_Dplus_P0_IPCHI2, &b_B0_Fit_Dplus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_P", B0_Fit_Dplus_P0_P, &b_B0_Fit_Dplus_P0_P);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_PE", B0_Fit_Dplus_P0_PE, &b_B0_Fit_Dplus_P0_PE);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_PERR", B0_Fit_Dplus_P0_PERR, &b_B0_Fit_Dplus_P0_PERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_PT", B0_Fit_Dplus_P0_PT, &b_B0_Fit_Dplus_P0_PT);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_PTERR", B0_Fit_Dplus_P0_PTERR, &b_B0_Fit_Dplus_P0_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_PX", B0_Fit_Dplus_P0_PX, &b_B0_Fit_Dplus_P0_PX);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_PY", B0_Fit_Dplus_P0_PY, &b_B0_Fit_Dplus_P0_PY);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_PZ", B0_Fit_Dplus_P0_PZ, &b_B0_Fit_Dplus_P0_PZ);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_X", B0_Fit_Dplus_P0_X, &b_B0_Fit_Dplus_P0_X);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_XERR", B0_Fit_Dplus_P0_XERR, &b_B0_Fit_Dplus_P0_XERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_Y", B0_Fit_Dplus_P0_Y, &b_B0_Fit_Dplus_P0_Y);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_YERR", B0_Fit_Dplus_P0_YERR, &b_B0_Fit_Dplus_P0_YERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_Z", B0_Fit_Dplus_P0_Z, &b_B0_Fit_Dplus_P0_Z);
   fChain->SetBranchAddress("B0_Fit_Dplus_P0_ZERR", B0_Fit_Dplus_P0_ZERR, &b_B0_Fit_Dplus_P0_ZERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_ID", B0_Fit_Dplus_P1_ID, &b_B0_Fit_Dplus_P1_ID);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_IP", B0_Fit_Dplus_P1_IP, &b_B0_Fit_Dplus_P1_IP);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_IPCHI2", B0_Fit_Dplus_P1_IPCHI2, &b_B0_Fit_Dplus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_P", B0_Fit_Dplus_P1_P, &b_B0_Fit_Dplus_P1_P);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_PE", B0_Fit_Dplus_P1_PE, &b_B0_Fit_Dplus_P1_PE);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_PERR", B0_Fit_Dplus_P1_PERR, &b_B0_Fit_Dplus_P1_PERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_PT", B0_Fit_Dplus_P1_PT, &b_B0_Fit_Dplus_P1_PT);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_PTERR", B0_Fit_Dplus_P1_PTERR, &b_B0_Fit_Dplus_P1_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_PX", B0_Fit_Dplus_P1_PX, &b_B0_Fit_Dplus_P1_PX);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_PY", B0_Fit_Dplus_P1_PY, &b_B0_Fit_Dplus_P1_PY);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_PZ", B0_Fit_Dplus_P1_PZ, &b_B0_Fit_Dplus_P1_PZ);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_X", B0_Fit_Dplus_P1_X, &b_B0_Fit_Dplus_P1_X);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_XERR", B0_Fit_Dplus_P1_XERR, &b_B0_Fit_Dplus_P1_XERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_Y", B0_Fit_Dplus_P1_Y, &b_B0_Fit_Dplus_P1_Y);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_YERR", B0_Fit_Dplus_P1_YERR, &b_B0_Fit_Dplus_P1_YERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_Z", B0_Fit_Dplus_P1_Z, &b_B0_Fit_Dplus_P1_Z);
   fChain->SetBranchAddress("B0_Fit_Dplus_P1_ZERR", B0_Fit_Dplus_P1_ZERR, &b_B0_Fit_Dplus_P1_ZERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_ID", B0_Fit_Dplus_P2_ID, &b_B0_Fit_Dplus_P2_ID);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_IP", B0_Fit_Dplus_P2_IP, &b_B0_Fit_Dplus_P2_IP);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_IPCHI2", B0_Fit_Dplus_P2_IPCHI2, &b_B0_Fit_Dplus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_P", B0_Fit_Dplus_P2_P, &b_B0_Fit_Dplus_P2_P);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_PE", B0_Fit_Dplus_P2_PE, &b_B0_Fit_Dplus_P2_PE);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_PERR", B0_Fit_Dplus_P2_PERR, &b_B0_Fit_Dplus_P2_PERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_PT", B0_Fit_Dplus_P2_PT, &b_B0_Fit_Dplus_P2_PT);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_PTERR", B0_Fit_Dplus_P2_PTERR, &b_B0_Fit_Dplus_P2_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_PX", B0_Fit_Dplus_P2_PX, &b_B0_Fit_Dplus_P2_PX);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_PY", B0_Fit_Dplus_P2_PY, &b_B0_Fit_Dplus_P2_PY);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_PZ", B0_Fit_Dplus_P2_PZ, &b_B0_Fit_Dplus_P2_PZ);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_X", B0_Fit_Dplus_P2_X, &b_B0_Fit_Dplus_P2_X);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_XERR", B0_Fit_Dplus_P2_XERR, &b_B0_Fit_Dplus_P2_XERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_Y", B0_Fit_Dplus_P2_Y, &b_B0_Fit_Dplus_P2_Y);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_YERR", B0_Fit_Dplus_P2_YERR, &b_B0_Fit_Dplus_P2_YERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_Z", B0_Fit_Dplus_P2_Z, &b_B0_Fit_Dplus_P2_Z);
   fChain->SetBranchAddress("B0_Fit_Dplus_P2_ZERR", B0_Fit_Dplus_P2_ZERR, &b_B0_Fit_Dplus_P2_ZERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_PERR", B0_Fit_Dplus_PERR, &b_B0_Fit_Dplus_PERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_PT", B0_Fit_Dplus_PT, &b_B0_Fit_Dplus_PT);
   fChain->SetBranchAddress("B0_Fit_Dplus_PTERR", B0_Fit_Dplus_PTERR, &b_B0_Fit_Dplus_PTERR);
   fChain->SetBranchAddress("B0_Fit_Dplus_ctau", B0_Fit_Dplus_ctau, &b_B0_Fit_Dplus_ctau);
   fChain->SetBranchAddress("B0_Fit_Dplus_ctauErr", B0_Fit_Dplus_ctauErr, &b_B0_Fit_Dplus_ctauErr);
   fChain->SetBranchAddress("B0_Fit_Dplus_decayLength", B0_Fit_Dplus_decayLength, &b_B0_Fit_Dplus_decayLength);
   fChain->SetBranchAddress("B0_Fit_Dplus_decayLengthErr", B0_Fit_Dplus_decayLengthErr, &b_B0_Fit_Dplus_decayLengthErr);
   fChain->SetBranchAddress("B0_Fit_Dplus_tau", B0_Fit_Dplus_tau, &b_B0_Fit_Dplus_tau);
   fChain->SetBranchAddress("B0_Fit_Dplus_tauErr", B0_Fit_Dplus_tauErr, &b_B0_Fit_Dplus_tauErr);
   fChain->SetBranchAddress("B0_Fit_IP", B0_Fit_IP, &b_B0_Fit_IP);
   fChain->SetBranchAddress("B0_Fit_IPCHI2", B0_Fit_IPCHI2, &b_B0_Fit_IPCHI2);
   fChain->SetBranchAddress("B0_Fit_M", B0_Fit_M, &b_B0_Fit_M);
   fChain->SetBranchAddress("B0_Fit_MERR", B0_Fit_MERR, &b_B0_Fit_MERR);
   fChain->SetBranchAddress("B0_Fit_P", B0_Fit_P, &b_B0_Fit_P);
   fChain->SetBranchAddress("B0_Fit_PERR", B0_Fit_PERR, &b_B0_Fit_PERR);
   fChain->SetBranchAddress("B0_Fit_PT", B0_Fit_PT, &b_B0_Fit_PT);
   fChain->SetBranchAddress("B0_Fit_PTERR", B0_Fit_PTERR, &b_B0_Fit_PTERR);
   fChain->SetBranchAddress("B0_Fit_PV_X", B0_Fit_PV_X, &b_B0_Fit_PV_X);
   fChain->SetBranchAddress("B0_Fit_PV_XVAR", B0_Fit_PV_XVAR, &b_B0_Fit_PV_XVAR);
   fChain->SetBranchAddress("B0_Fit_PV_XYCOV", B0_Fit_PV_XYCOV, &b_B0_Fit_PV_XYCOV);
   fChain->SetBranchAddress("B0_Fit_PV_XZCOV", B0_Fit_PV_XZCOV, &b_B0_Fit_PV_XZCOV);
   fChain->SetBranchAddress("B0_Fit_PV_Y", B0_Fit_PV_Y, &b_B0_Fit_PV_Y);
   fChain->SetBranchAddress("B0_Fit_PV_YVAR", B0_Fit_PV_YVAR, &b_B0_Fit_PV_YVAR);
   fChain->SetBranchAddress("B0_Fit_PV_YZCOV", B0_Fit_PV_YZCOV, &b_B0_Fit_PV_YZCOV);
   fChain->SetBranchAddress("B0_Fit_PV_Z", B0_Fit_PV_Z, &b_B0_Fit_PV_Z);
   fChain->SetBranchAddress("B0_Fit_PV_ZVAR", B0_Fit_PV_ZVAR, &b_B0_Fit_PV_ZVAR);
   fChain->SetBranchAddress("B0_Fit_PV_key", B0_Fit_PV_key, &b_B0_Fit_PV_key);
   fChain->SetBranchAddress("B0_Fit_X", B0_Fit_X, &b_B0_Fit_X);
   fChain->SetBranchAddress("B0_Fit_XERR", B0_Fit_XERR, &b_B0_Fit_XERR);
   fChain->SetBranchAddress("B0_Fit_Y", B0_Fit_Y, &b_B0_Fit_Y);
   fChain->SetBranchAddress("B0_Fit_YERR", B0_Fit_YERR, &b_B0_Fit_YERR);
   fChain->SetBranchAddress("B0_Fit_Z", B0_Fit_Z, &b_B0_Fit_Z);
   fChain->SetBranchAddress("B0_Fit_ZERR", B0_Fit_ZERR, &b_B0_Fit_ZERR);
   fChain->SetBranchAddress("B0_Fit_chi2", B0_Fit_chi2, &b_B0_Fit_chi2);
   fChain->SetBranchAddress("B0_Fit_ctau", B0_Fit_ctau, &b_B0_Fit_ctau);
   fChain->SetBranchAddress("B0_Fit_ctauErr", B0_Fit_ctauErr, &b_B0_Fit_ctauErr);
   fChain->SetBranchAddress("B0_Fit_decayLength", B0_Fit_decayLength, &b_B0_Fit_decayLength);
   fChain->SetBranchAddress("B0_Fit_decayLengthErr", B0_Fit_decayLengthErr, &b_B0_Fit_decayLengthErr);
   fChain->SetBranchAddress("B0_Fit_nDOF", B0_Fit_nDOF, &b_B0_Fit_nDOF);
   fChain->SetBranchAddress("B0_Fit_nIter", B0_Fit_nIter, &b_B0_Fit_nIter);
   fChain->SetBranchAddress("B0_Fit_status", B0_Fit_status, &b_B0_Fit_status);
   fChain->SetBranchAddress("B0_Fit_tau", B0_Fit_tau, &b_B0_Fit_tau);
   fChain->SetBranchAddress("B0_Fit_tauErr", B0_Fit_tauErr, &b_B0_Fit_tauErr);
   fChain->SetBranchAddress("B0_FitDDConst_nPV", &B0_FitDDConst_nPV, &b_B0_FitDDConst_nPV);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_IP", B0_FitDDConst_Dminus_IP, &b_B0_FitDDConst_Dminus_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_IPCHI2", B0_FitDDConst_Dminus_IPCHI2, &b_B0_FitDDConst_Dminus_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_M", B0_FitDDConst_Dminus_M, &b_B0_FitDDConst_Dminus_M);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_MERR", B0_FitDDConst_Dminus_MERR, &b_B0_FitDDConst_Dminus_MERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P", B0_FitDDConst_Dminus_P, &b_B0_FitDDConst_Dminus_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_ID", B0_FitDDConst_Dminus_P0_ID, &b_B0_FitDDConst_Dminus_P0_ID);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_IP", B0_FitDDConst_Dminus_P0_IP, &b_B0_FitDDConst_Dminus_P0_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_IPCHI2", B0_FitDDConst_Dminus_P0_IPCHI2, &b_B0_FitDDConst_Dminus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_P", B0_FitDDConst_Dminus_P0_P, &b_B0_FitDDConst_Dminus_P0_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_PE", B0_FitDDConst_Dminus_P0_PE, &b_B0_FitDDConst_Dminus_P0_PE);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_PERR", B0_FitDDConst_Dminus_P0_PERR, &b_B0_FitDDConst_Dminus_P0_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_PT", B0_FitDDConst_Dminus_P0_PT, &b_B0_FitDDConst_Dminus_P0_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_PTERR", B0_FitDDConst_Dminus_P0_PTERR, &b_B0_FitDDConst_Dminus_P0_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_PX", B0_FitDDConst_Dminus_P0_PX, &b_B0_FitDDConst_Dminus_P0_PX);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_PY", B0_FitDDConst_Dminus_P0_PY, &b_B0_FitDDConst_Dminus_P0_PY);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_PZ", B0_FitDDConst_Dminus_P0_PZ, &b_B0_FitDDConst_Dminus_P0_PZ);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_X", B0_FitDDConst_Dminus_P0_X, &b_B0_FitDDConst_Dminus_P0_X);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_XERR", B0_FitDDConst_Dminus_P0_XERR, &b_B0_FitDDConst_Dminus_P0_XERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_Y", B0_FitDDConst_Dminus_P0_Y, &b_B0_FitDDConst_Dminus_P0_Y);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_YERR", B0_FitDDConst_Dminus_P0_YERR, &b_B0_FitDDConst_Dminus_P0_YERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_Z", B0_FitDDConst_Dminus_P0_Z, &b_B0_FitDDConst_Dminus_P0_Z);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P0_ZERR", B0_FitDDConst_Dminus_P0_ZERR, &b_B0_FitDDConst_Dminus_P0_ZERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_ID", B0_FitDDConst_Dminus_P1_ID, &b_B0_FitDDConst_Dminus_P1_ID);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_IP", B0_FitDDConst_Dminus_P1_IP, &b_B0_FitDDConst_Dminus_P1_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_IPCHI2", B0_FitDDConst_Dminus_P1_IPCHI2, &b_B0_FitDDConst_Dminus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_P", B0_FitDDConst_Dminus_P1_P, &b_B0_FitDDConst_Dminus_P1_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_PE", B0_FitDDConst_Dminus_P1_PE, &b_B0_FitDDConst_Dminus_P1_PE);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_PERR", B0_FitDDConst_Dminus_P1_PERR, &b_B0_FitDDConst_Dminus_P1_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_PT", B0_FitDDConst_Dminus_P1_PT, &b_B0_FitDDConst_Dminus_P1_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_PTERR", B0_FitDDConst_Dminus_P1_PTERR, &b_B0_FitDDConst_Dminus_P1_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_PX", B0_FitDDConst_Dminus_P1_PX, &b_B0_FitDDConst_Dminus_P1_PX);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_PY", B0_FitDDConst_Dminus_P1_PY, &b_B0_FitDDConst_Dminus_P1_PY);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_PZ", B0_FitDDConst_Dminus_P1_PZ, &b_B0_FitDDConst_Dminus_P1_PZ);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_X", B0_FitDDConst_Dminus_P1_X, &b_B0_FitDDConst_Dminus_P1_X);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_XERR", B0_FitDDConst_Dminus_P1_XERR, &b_B0_FitDDConst_Dminus_P1_XERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_Y", B0_FitDDConst_Dminus_P1_Y, &b_B0_FitDDConst_Dminus_P1_Y);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_YERR", B0_FitDDConst_Dminus_P1_YERR, &b_B0_FitDDConst_Dminus_P1_YERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_Z", B0_FitDDConst_Dminus_P1_Z, &b_B0_FitDDConst_Dminus_P1_Z);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P1_ZERR", B0_FitDDConst_Dminus_P1_ZERR, &b_B0_FitDDConst_Dminus_P1_ZERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_ID", B0_FitDDConst_Dminus_P2_ID, &b_B0_FitDDConst_Dminus_P2_ID);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_IP", B0_FitDDConst_Dminus_P2_IP, &b_B0_FitDDConst_Dminus_P2_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_IPCHI2", B0_FitDDConst_Dminus_P2_IPCHI2, &b_B0_FitDDConst_Dminus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_P", B0_FitDDConst_Dminus_P2_P, &b_B0_FitDDConst_Dminus_P2_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_PE", B0_FitDDConst_Dminus_P2_PE, &b_B0_FitDDConst_Dminus_P2_PE);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_PERR", B0_FitDDConst_Dminus_P2_PERR, &b_B0_FitDDConst_Dminus_P2_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_PT", B0_FitDDConst_Dminus_P2_PT, &b_B0_FitDDConst_Dminus_P2_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_PTERR", B0_FitDDConst_Dminus_P2_PTERR, &b_B0_FitDDConst_Dminus_P2_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_PX", B0_FitDDConst_Dminus_P2_PX, &b_B0_FitDDConst_Dminus_P2_PX);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_PY", B0_FitDDConst_Dminus_P2_PY, &b_B0_FitDDConst_Dminus_P2_PY);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_PZ", B0_FitDDConst_Dminus_P2_PZ, &b_B0_FitDDConst_Dminus_P2_PZ);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_X", B0_FitDDConst_Dminus_P2_X, &b_B0_FitDDConst_Dminus_P2_X);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_XERR", B0_FitDDConst_Dminus_P2_XERR, &b_B0_FitDDConst_Dminus_P2_XERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_Y", B0_FitDDConst_Dminus_P2_Y, &b_B0_FitDDConst_Dminus_P2_Y);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_YERR", B0_FitDDConst_Dminus_P2_YERR, &b_B0_FitDDConst_Dminus_P2_YERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_Z", B0_FitDDConst_Dminus_P2_Z, &b_B0_FitDDConst_Dminus_P2_Z);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_P2_ZERR", B0_FitDDConst_Dminus_P2_ZERR, &b_B0_FitDDConst_Dminus_P2_ZERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_PERR", B0_FitDDConst_Dminus_PERR, &b_B0_FitDDConst_Dminus_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_PT", B0_FitDDConst_Dminus_PT, &b_B0_FitDDConst_Dminus_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_PTERR", B0_FitDDConst_Dminus_PTERR, &b_B0_FitDDConst_Dminus_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_ctau", B0_FitDDConst_Dminus_ctau, &b_B0_FitDDConst_Dminus_ctau);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_ctauErr", B0_FitDDConst_Dminus_ctauErr, &b_B0_FitDDConst_Dminus_ctauErr);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_decayLength", B0_FitDDConst_Dminus_decayLength, &b_B0_FitDDConst_Dminus_decayLength);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_decayLengthErr", B0_FitDDConst_Dminus_decayLengthErr, &b_B0_FitDDConst_Dminus_decayLengthErr);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_tau", B0_FitDDConst_Dminus_tau, &b_B0_FitDDConst_Dminus_tau);
   fChain->SetBranchAddress("B0_FitDDConst_Dminus_tauErr", B0_FitDDConst_Dminus_tauErr, &b_B0_FitDDConst_Dminus_tauErr);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_IP", B0_FitDDConst_Dplus_IP, &b_B0_FitDDConst_Dplus_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_IPCHI2", B0_FitDDConst_Dplus_IPCHI2, &b_B0_FitDDConst_Dplus_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_M", B0_FitDDConst_Dplus_M, &b_B0_FitDDConst_Dplus_M);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_MERR", B0_FitDDConst_Dplus_MERR, &b_B0_FitDDConst_Dplus_MERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P", B0_FitDDConst_Dplus_P, &b_B0_FitDDConst_Dplus_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_ID", B0_FitDDConst_Dplus_P0_ID, &b_B0_FitDDConst_Dplus_P0_ID);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_IP", B0_FitDDConst_Dplus_P0_IP, &b_B0_FitDDConst_Dplus_P0_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_IPCHI2", B0_FitDDConst_Dplus_P0_IPCHI2, &b_B0_FitDDConst_Dplus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_P", B0_FitDDConst_Dplus_P0_P, &b_B0_FitDDConst_Dplus_P0_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_PE", B0_FitDDConst_Dplus_P0_PE, &b_B0_FitDDConst_Dplus_P0_PE);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_PERR", B0_FitDDConst_Dplus_P0_PERR, &b_B0_FitDDConst_Dplus_P0_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_PT", B0_FitDDConst_Dplus_P0_PT, &b_B0_FitDDConst_Dplus_P0_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_PTERR", B0_FitDDConst_Dplus_P0_PTERR, &b_B0_FitDDConst_Dplus_P0_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_PX", B0_FitDDConst_Dplus_P0_PX, &b_B0_FitDDConst_Dplus_P0_PX);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_PY", B0_FitDDConst_Dplus_P0_PY, &b_B0_FitDDConst_Dplus_P0_PY);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_PZ", B0_FitDDConst_Dplus_P0_PZ, &b_B0_FitDDConst_Dplus_P0_PZ);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_X", B0_FitDDConst_Dplus_P0_X, &b_B0_FitDDConst_Dplus_P0_X);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_XERR", B0_FitDDConst_Dplus_P0_XERR, &b_B0_FitDDConst_Dplus_P0_XERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_Y", B0_FitDDConst_Dplus_P0_Y, &b_B0_FitDDConst_Dplus_P0_Y);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_YERR", B0_FitDDConst_Dplus_P0_YERR, &b_B0_FitDDConst_Dplus_P0_YERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_Z", B0_FitDDConst_Dplus_P0_Z, &b_B0_FitDDConst_Dplus_P0_Z);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P0_ZERR", B0_FitDDConst_Dplus_P0_ZERR, &b_B0_FitDDConst_Dplus_P0_ZERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_ID", B0_FitDDConst_Dplus_P1_ID, &b_B0_FitDDConst_Dplus_P1_ID);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_IP", B0_FitDDConst_Dplus_P1_IP, &b_B0_FitDDConst_Dplus_P1_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_IPCHI2", B0_FitDDConst_Dplus_P1_IPCHI2, &b_B0_FitDDConst_Dplus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_P", B0_FitDDConst_Dplus_P1_P, &b_B0_FitDDConst_Dplus_P1_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_PE", B0_FitDDConst_Dplus_P1_PE, &b_B0_FitDDConst_Dplus_P1_PE);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_PERR", B0_FitDDConst_Dplus_P1_PERR, &b_B0_FitDDConst_Dplus_P1_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_PT", B0_FitDDConst_Dplus_P1_PT, &b_B0_FitDDConst_Dplus_P1_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_PTERR", B0_FitDDConst_Dplus_P1_PTERR, &b_B0_FitDDConst_Dplus_P1_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_PX", B0_FitDDConst_Dplus_P1_PX, &b_B0_FitDDConst_Dplus_P1_PX);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_PY", B0_FitDDConst_Dplus_P1_PY, &b_B0_FitDDConst_Dplus_P1_PY);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_PZ", B0_FitDDConst_Dplus_P1_PZ, &b_B0_FitDDConst_Dplus_P1_PZ);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_X", B0_FitDDConst_Dplus_P1_X, &b_B0_FitDDConst_Dplus_P1_X);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_XERR", B0_FitDDConst_Dplus_P1_XERR, &b_B0_FitDDConst_Dplus_P1_XERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_Y", B0_FitDDConst_Dplus_P1_Y, &b_B0_FitDDConst_Dplus_P1_Y);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_YERR", B0_FitDDConst_Dplus_P1_YERR, &b_B0_FitDDConst_Dplus_P1_YERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_Z", B0_FitDDConst_Dplus_P1_Z, &b_B0_FitDDConst_Dplus_P1_Z);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P1_ZERR", B0_FitDDConst_Dplus_P1_ZERR, &b_B0_FitDDConst_Dplus_P1_ZERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_ID", B0_FitDDConst_Dplus_P2_ID, &b_B0_FitDDConst_Dplus_P2_ID);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_IP", B0_FitDDConst_Dplus_P2_IP, &b_B0_FitDDConst_Dplus_P2_IP);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_IPCHI2", B0_FitDDConst_Dplus_P2_IPCHI2, &b_B0_FitDDConst_Dplus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_P", B0_FitDDConst_Dplus_P2_P, &b_B0_FitDDConst_Dplus_P2_P);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_PE", B0_FitDDConst_Dplus_P2_PE, &b_B0_FitDDConst_Dplus_P2_PE);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_PERR", B0_FitDDConst_Dplus_P2_PERR, &b_B0_FitDDConst_Dplus_P2_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_PT", B0_FitDDConst_Dplus_P2_PT, &b_B0_FitDDConst_Dplus_P2_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_PTERR", B0_FitDDConst_Dplus_P2_PTERR, &b_B0_FitDDConst_Dplus_P2_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_PX", B0_FitDDConst_Dplus_P2_PX, &b_B0_FitDDConst_Dplus_P2_PX);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_PY", B0_FitDDConst_Dplus_P2_PY, &b_B0_FitDDConst_Dplus_P2_PY);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_PZ", B0_FitDDConst_Dplus_P2_PZ, &b_B0_FitDDConst_Dplus_P2_PZ);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_X", B0_FitDDConst_Dplus_P2_X, &b_B0_FitDDConst_Dplus_P2_X);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_XERR", B0_FitDDConst_Dplus_P2_XERR, &b_B0_FitDDConst_Dplus_P2_XERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_Y", B0_FitDDConst_Dplus_P2_Y, &b_B0_FitDDConst_Dplus_P2_Y);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_YERR", B0_FitDDConst_Dplus_P2_YERR, &b_B0_FitDDConst_Dplus_P2_YERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_Z", B0_FitDDConst_Dplus_P2_Z, &b_B0_FitDDConst_Dplus_P2_Z);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_P2_ZERR", B0_FitDDConst_Dplus_P2_ZERR, &b_B0_FitDDConst_Dplus_P2_ZERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_PERR", B0_FitDDConst_Dplus_PERR, &b_B0_FitDDConst_Dplus_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_PT", B0_FitDDConst_Dplus_PT, &b_B0_FitDDConst_Dplus_PT);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_PTERR", B0_FitDDConst_Dplus_PTERR, &b_B0_FitDDConst_Dplus_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_ctau", B0_FitDDConst_Dplus_ctau, &b_B0_FitDDConst_Dplus_ctau);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_ctauErr", B0_FitDDConst_Dplus_ctauErr, &b_B0_FitDDConst_Dplus_ctauErr);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_decayLength", B0_FitDDConst_Dplus_decayLength, &b_B0_FitDDConst_Dplus_decayLength);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_decayLengthErr", B0_FitDDConst_Dplus_decayLengthErr, &b_B0_FitDDConst_Dplus_decayLengthErr);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_tau", B0_FitDDConst_Dplus_tau, &b_B0_FitDDConst_Dplus_tau);
   fChain->SetBranchAddress("B0_FitDDConst_Dplus_tauErr", B0_FitDDConst_Dplus_tauErr, &b_B0_FitDDConst_Dplus_tauErr);
   fChain->SetBranchAddress("B0_FitDDConst_IP", B0_FitDDConst_IP, &b_B0_FitDDConst_IP);
   fChain->SetBranchAddress("B0_FitDDConst_IPCHI2", B0_FitDDConst_IPCHI2, &b_B0_FitDDConst_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDConst_M", B0_FitDDConst_M, &b_B0_FitDDConst_M);
   fChain->SetBranchAddress("B0_FitDDConst_MERR", B0_FitDDConst_MERR, &b_B0_FitDDConst_MERR);
   fChain->SetBranchAddress("B0_FitDDConst_P", B0_FitDDConst_P, &b_B0_FitDDConst_P);
   fChain->SetBranchAddress("B0_FitDDConst_PERR", B0_FitDDConst_PERR, &b_B0_FitDDConst_PERR);
   fChain->SetBranchAddress("B0_FitDDConst_PT", B0_FitDDConst_PT, &b_B0_FitDDConst_PT);
   fChain->SetBranchAddress("B0_FitDDConst_PTERR", B0_FitDDConst_PTERR, &b_B0_FitDDConst_PTERR);
   fChain->SetBranchAddress("B0_FitDDConst_PV_X", B0_FitDDConst_PV_X, &b_B0_FitDDConst_PV_X);
   fChain->SetBranchAddress("B0_FitDDConst_PV_XVAR", B0_FitDDConst_PV_XVAR, &b_B0_FitDDConst_PV_XVAR);
   fChain->SetBranchAddress("B0_FitDDConst_PV_XYCOV", B0_FitDDConst_PV_XYCOV, &b_B0_FitDDConst_PV_XYCOV);
   fChain->SetBranchAddress("B0_FitDDConst_PV_XZCOV", B0_FitDDConst_PV_XZCOV, &b_B0_FitDDConst_PV_XZCOV);
   fChain->SetBranchAddress("B0_FitDDConst_PV_Y", B0_FitDDConst_PV_Y, &b_B0_FitDDConst_PV_Y);
   fChain->SetBranchAddress("B0_FitDDConst_PV_YVAR", B0_FitDDConst_PV_YVAR, &b_B0_FitDDConst_PV_YVAR);
   fChain->SetBranchAddress("B0_FitDDConst_PV_YZCOV", B0_FitDDConst_PV_YZCOV, &b_B0_FitDDConst_PV_YZCOV);
   fChain->SetBranchAddress("B0_FitDDConst_PV_Z", B0_FitDDConst_PV_Z, &b_B0_FitDDConst_PV_Z);
   fChain->SetBranchAddress("B0_FitDDConst_PV_ZVAR", B0_FitDDConst_PV_ZVAR, &b_B0_FitDDConst_PV_ZVAR);
   fChain->SetBranchAddress("B0_FitDDConst_PV_key", B0_FitDDConst_PV_key, &b_B0_FitDDConst_PV_key);
   fChain->SetBranchAddress("B0_FitDDConst_X", B0_FitDDConst_X, &b_B0_FitDDConst_X);
   fChain->SetBranchAddress("B0_FitDDConst_XERR", B0_FitDDConst_XERR, &b_B0_FitDDConst_XERR);
   fChain->SetBranchAddress("B0_FitDDConst_Y", B0_FitDDConst_Y, &b_B0_FitDDConst_Y);
   fChain->SetBranchAddress("B0_FitDDConst_YERR", B0_FitDDConst_YERR, &b_B0_FitDDConst_YERR);
   fChain->SetBranchAddress("B0_FitDDConst_Z", B0_FitDDConst_Z, &b_B0_FitDDConst_Z);
   fChain->SetBranchAddress("B0_FitDDConst_ZERR", B0_FitDDConst_ZERR, &b_B0_FitDDConst_ZERR);
   fChain->SetBranchAddress("B0_FitDDConst_chi2", B0_FitDDConst_chi2, &b_B0_FitDDConst_chi2);
   fChain->SetBranchAddress("B0_FitDDConst_ctau", B0_FitDDConst_ctau, &b_B0_FitDDConst_ctau);
   fChain->SetBranchAddress("B0_FitDDConst_ctauErr", B0_FitDDConst_ctauErr, &b_B0_FitDDConst_ctauErr);
   fChain->SetBranchAddress("B0_FitDDConst_decayLength", B0_FitDDConst_decayLength, &b_B0_FitDDConst_decayLength);
   fChain->SetBranchAddress("B0_FitDDConst_decayLengthErr", B0_FitDDConst_decayLengthErr, &b_B0_FitDDConst_decayLengthErr);
   fChain->SetBranchAddress("B0_FitDDConst_nDOF", B0_FitDDConst_nDOF, &b_B0_FitDDConst_nDOF);
   fChain->SetBranchAddress("B0_FitDDConst_nIter", B0_FitDDConst_nIter, &b_B0_FitDDConst_nIter);
   fChain->SetBranchAddress("B0_FitDDConst_status", B0_FitDDConst_status, &b_B0_FitDDConst_status);
   fChain->SetBranchAddress("B0_FitDDConst_tau", B0_FitDDConst_tau, &b_B0_FitDDConst_tau);
   fChain->SetBranchAddress("B0_FitDDConst_tauErr", B0_FitDDConst_tauErr, &b_B0_FitDDConst_tauErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_nPV", &B0_FitDDPVConst_nPV, &b_B0_FitDDPVConst_nPV);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_IP", B0_FitDDPVConst_Dminus_IP, &b_B0_FitDDPVConst_Dminus_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_IPCHI2", B0_FitDDPVConst_Dminus_IPCHI2, &b_B0_FitDDPVConst_Dminus_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_M", B0_FitDDPVConst_Dminus_M, &b_B0_FitDDPVConst_Dminus_M);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_MERR", B0_FitDDPVConst_Dminus_MERR, &b_B0_FitDDPVConst_Dminus_MERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P", B0_FitDDPVConst_Dminus_P, &b_B0_FitDDPVConst_Dminus_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_ID", B0_FitDDPVConst_Dminus_P0_ID, &b_B0_FitDDPVConst_Dminus_P0_ID);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_IP", B0_FitDDPVConst_Dminus_P0_IP, &b_B0_FitDDPVConst_Dminus_P0_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_IPCHI2", B0_FitDDPVConst_Dminus_P0_IPCHI2, &b_B0_FitDDPVConst_Dminus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_P", B0_FitDDPVConst_Dminus_P0_P, &b_B0_FitDDPVConst_Dminus_P0_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_PE", B0_FitDDPVConst_Dminus_P0_PE, &b_B0_FitDDPVConst_Dminus_P0_PE);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_PERR", B0_FitDDPVConst_Dminus_P0_PERR, &b_B0_FitDDPVConst_Dminus_P0_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_PT", B0_FitDDPVConst_Dminus_P0_PT, &b_B0_FitDDPVConst_Dminus_P0_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_PTERR", B0_FitDDPVConst_Dminus_P0_PTERR, &b_B0_FitDDPVConst_Dminus_P0_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_PX", B0_FitDDPVConst_Dminus_P0_PX, &b_B0_FitDDPVConst_Dminus_P0_PX);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_PY", B0_FitDDPVConst_Dminus_P0_PY, &b_B0_FitDDPVConst_Dminus_P0_PY);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_PZ", B0_FitDDPVConst_Dminus_P0_PZ, &b_B0_FitDDPVConst_Dminus_P0_PZ);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_X", B0_FitDDPVConst_Dminus_P0_X, &b_B0_FitDDPVConst_Dminus_P0_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_XERR", B0_FitDDPVConst_Dminus_P0_XERR, &b_B0_FitDDPVConst_Dminus_P0_XERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_Y", B0_FitDDPVConst_Dminus_P0_Y, &b_B0_FitDDPVConst_Dminus_P0_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_YERR", B0_FitDDPVConst_Dminus_P0_YERR, &b_B0_FitDDPVConst_Dminus_P0_YERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_Z", B0_FitDDPVConst_Dminus_P0_Z, &b_B0_FitDDPVConst_Dminus_P0_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P0_ZERR", B0_FitDDPVConst_Dminus_P0_ZERR, &b_B0_FitDDPVConst_Dminus_P0_ZERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_ID", B0_FitDDPVConst_Dminus_P1_ID, &b_B0_FitDDPVConst_Dminus_P1_ID);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_IP", B0_FitDDPVConst_Dminus_P1_IP, &b_B0_FitDDPVConst_Dminus_P1_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_IPCHI2", B0_FitDDPVConst_Dminus_P1_IPCHI2, &b_B0_FitDDPVConst_Dminus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_P", B0_FitDDPVConst_Dminus_P1_P, &b_B0_FitDDPVConst_Dminus_P1_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_PE", B0_FitDDPVConst_Dminus_P1_PE, &b_B0_FitDDPVConst_Dminus_P1_PE);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_PERR", B0_FitDDPVConst_Dminus_P1_PERR, &b_B0_FitDDPVConst_Dminus_P1_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_PT", B0_FitDDPVConst_Dminus_P1_PT, &b_B0_FitDDPVConst_Dminus_P1_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_PTERR", B0_FitDDPVConst_Dminus_P1_PTERR, &b_B0_FitDDPVConst_Dminus_P1_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_PX", B0_FitDDPVConst_Dminus_P1_PX, &b_B0_FitDDPVConst_Dminus_P1_PX);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_PY", B0_FitDDPVConst_Dminus_P1_PY, &b_B0_FitDDPVConst_Dminus_P1_PY);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_PZ", B0_FitDDPVConst_Dminus_P1_PZ, &b_B0_FitDDPVConst_Dminus_P1_PZ);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_X", B0_FitDDPVConst_Dminus_P1_X, &b_B0_FitDDPVConst_Dminus_P1_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_XERR", B0_FitDDPVConst_Dminus_P1_XERR, &b_B0_FitDDPVConst_Dminus_P1_XERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_Y", B0_FitDDPVConst_Dminus_P1_Y, &b_B0_FitDDPVConst_Dminus_P1_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_YERR", B0_FitDDPVConst_Dminus_P1_YERR, &b_B0_FitDDPVConst_Dminus_P1_YERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_Z", B0_FitDDPVConst_Dminus_P1_Z, &b_B0_FitDDPVConst_Dminus_P1_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P1_ZERR", B0_FitDDPVConst_Dminus_P1_ZERR, &b_B0_FitDDPVConst_Dminus_P1_ZERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_ID", B0_FitDDPVConst_Dminus_P2_ID, &b_B0_FitDDPVConst_Dminus_P2_ID);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_IP", B0_FitDDPVConst_Dminus_P2_IP, &b_B0_FitDDPVConst_Dminus_P2_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_IPCHI2", B0_FitDDPVConst_Dminus_P2_IPCHI2, &b_B0_FitDDPVConst_Dminus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_P", B0_FitDDPVConst_Dminus_P2_P, &b_B0_FitDDPVConst_Dminus_P2_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_PE", B0_FitDDPVConst_Dminus_P2_PE, &b_B0_FitDDPVConst_Dminus_P2_PE);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_PERR", B0_FitDDPVConst_Dminus_P2_PERR, &b_B0_FitDDPVConst_Dminus_P2_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_PT", B0_FitDDPVConst_Dminus_P2_PT, &b_B0_FitDDPVConst_Dminus_P2_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_PTERR", B0_FitDDPVConst_Dminus_P2_PTERR, &b_B0_FitDDPVConst_Dminus_P2_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_PX", B0_FitDDPVConst_Dminus_P2_PX, &b_B0_FitDDPVConst_Dminus_P2_PX);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_PY", B0_FitDDPVConst_Dminus_P2_PY, &b_B0_FitDDPVConst_Dminus_P2_PY);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_PZ", B0_FitDDPVConst_Dminus_P2_PZ, &b_B0_FitDDPVConst_Dminus_P2_PZ);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_X", B0_FitDDPVConst_Dminus_P2_X, &b_B0_FitDDPVConst_Dminus_P2_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_XERR", B0_FitDDPVConst_Dminus_P2_XERR, &b_B0_FitDDPVConst_Dminus_P2_XERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_Y", B0_FitDDPVConst_Dminus_P2_Y, &b_B0_FitDDPVConst_Dminus_P2_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_YERR", B0_FitDDPVConst_Dminus_P2_YERR, &b_B0_FitDDPVConst_Dminus_P2_YERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_Z", B0_FitDDPVConst_Dminus_P2_Z, &b_B0_FitDDPVConst_Dminus_P2_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_P2_ZERR", B0_FitDDPVConst_Dminus_P2_ZERR, &b_B0_FitDDPVConst_Dminus_P2_ZERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_PERR", B0_FitDDPVConst_Dminus_PERR, &b_B0_FitDDPVConst_Dminus_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_PT", B0_FitDDPVConst_Dminus_PT, &b_B0_FitDDPVConst_Dminus_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_PTERR", B0_FitDDPVConst_Dminus_PTERR, &b_B0_FitDDPVConst_Dminus_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_ctau", B0_FitDDPVConst_Dminus_ctau, &b_B0_FitDDPVConst_Dminus_ctau);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_ctauErr", B0_FitDDPVConst_Dminus_ctauErr, &b_B0_FitDDPVConst_Dminus_ctauErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_decayLength", B0_FitDDPVConst_Dminus_decayLength, &b_B0_FitDDPVConst_Dminus_decayLength);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_decayLengthErr", B0_FitDDPVConst_Dminus_decayLengthErr, &b_B0_FitDDPVConst_Dminus_decayLengthErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_tau", B0_FitDDPVConst_Dminus_tau, &b_B0_FitDDPVConst_Dminus_tau);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dminus_tauErr", B0_FitDDPVConst_Dminus_tauErr, &b_B0_FitDDPVConst_Dminus_tauErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_IP", B0_FitDDPVConst_Dplus_IP, &b_B0_FitDDPVConst_Dplus_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_IPCHI2", B0_FitDDPVConst_Dplus_IPCHI2, &b_B0_FitDDPVConst_Dplus_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_M", B0_FitDDPVConst_Dplus_M, &b_B0_FitDDPVConst_Dplus_M);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_MERR", B0_FitDDPVConst_Dplus_MERR, &b_B0_FitDDPVConst_Dplus_MERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P", B0_FitDDPVConst_Dplus_P, &b_B0_FitDDPVConst_Dplus_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_ID", B0_FitDDPVConst_Dplus_P0_ID, &b_B0_FitDDPVConst_Dplus_P0_ID);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_IP", B0_FitDDPVConst_Dplus_P0_IP, &b_B0_FitDDPVConst_Dplus_P0_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_IPCHI2", B0_FitDDPVConst_Dplus_P0_IPCHI2, &b_B0_FitDDPVConst_Dplus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_P", B0_FitDDPVConst_Dplus_P0_P, &b_B0_FitDDPVConst_Dplus_P0_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_PE", B0_FitDDPVConst_Dplus_P0_PE, &b_B0_FitDDPVConst_Dplus_P0_PE);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_PERR", B0_FitDDPVConst_Dplus_P0_PERR, &b_B0_FitDDPVConst_Dplus_P0_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_PT", B0_FitDDPVConst_Dplus_P0_PT, &b_B0_FitDDPVConst_Dplus_P0_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_PTERR", B0_FitDDPVConst_Dplus_P0_PTERR, &b_B0_FitDDPVConst_Dplus_P0_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_PX", B0_FitDDPVConst_Dplus_P0_PX, &b_B0_FitDDPVConst_Dplus_P0_PX);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_PY", B0_FitDDPVConst_Dplus_P0_PY, &b_B0_FitDDPVConst_Dplus_P0_PY);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_PZ", B0_FitDDPVConst_Dplus_P0_PZ, &b_B0_FitDDPVConst_Dplus_P0_PZ);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_X", B0_FitDDPVConst_Dplus_P0_X, &b_B0_FitDDPVConst_Dplus_P0_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_XERR", B0_FitDDPVConst_Dplus_P0_XERR, &b_B0_FitDDPVConst_Dplus_P0_XERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_Y", B0_FitDDPVConst_Dplus_P0_Y, &b_B0_FitDDPVConst_Dplus_P0_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_YERR", B0_FitDDPVConst_Dplus_P0_YERR, &b_B0_FitDDPVConst_Dplus_P0_YERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_Z", B0_FitDDPVConst_Dplus_P0_Z, &b_B0_FitDDPVConst_Dplus_P0_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P0_ZERR", B0_FitDDPVConst_Dplus_P0_ZERR, &b_B0_FitDDPVConst_Dplus_P0_ZERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_ID", B0_FitDDPVConst_Dplus_P1_ID, &b_B0_FitDDPVConst_Dplus_P1_ID);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_IP", B0_FitDDPVConst_Dplus_P1_IP, &b_B0_FitDDPVConst_Dplus_P1_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_IPCHI2", B0_FitDDPVConst_Dplus_P1_IPCHI2, &b_B0_FitDDPVConst_Dplus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_P", B0_FitDDPVConst_Dplus_P1_P, &b_B0_FitDDPVConst_Dplus_P1_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_PE", B0_FitDDPVConst_Dplus_P1_PE, &b_B0_FitDDPVConst_Dplus_P1_PE);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_PERR", B0_FitDDPVConst_Dplus_P1_PERR, &b_B0_FitDDPVConst_Dplus_P1_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_PT", B0_FitDDPVConst_Dplus_P1_PT, &b_B0_FitDDPVConst_Dplus_P1_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_PTERR", B0_FitDDPVConst_Dplus_P1_PTERR, &b_B0_FitDDPVConst_Dplus_P1_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_PX", B0_FitDDPVConst_Dplus_P1_PX, &b_B0_FitDDPVConst_Dplus_P1_PX);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_PY", B0_FitDDPVConst_Dplus_P1_PY, &b_B0_FitDDPVConst_Dplus_P1_PY);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_PZ", B0_FitDDPVConst_Dplus_P1_PZ, &b_B0_FitDDPVConst_Dplus_P1_PZ);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_X", B0_FitDDPVConst_Dplus_P1_X, &b_B0_FitDDPVConst_Dplus_P1_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_XERR", B0_FitDDPVConst_Dplus_P1_XERR, &b_B0_FitDDPVConst_Dplus_P1_XERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_Y", B0_FitDDPVConst_Dplus_P1_Y, &b_B0_FitDDPVConst_Dplus_P1_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_YERR", B0_FitDDPVConst_Dplus_P1_YERR, &b_B0_FitDDPVConst_Dplus_P1_YERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_Z", B0_FitDDPVConst_Dplus_P1_Z, &b_B0_FitDDPVConst_Dplus_P1_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P1_ZERR", B0_FitDDPVConst_Dplus_P1_ZERR, &b_B0_FitDDPVConst_Dplus_P1_ZERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_ID", B0_FitDDPVConst_Dplus_P2_ID, &b_B0_FitDDPVConst_Dplus_P2_ID);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_IP", B0_FitDDPVConst_Dplus_P2_IP, &b_B0_FitDDPVConst_Dplus_P2_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_IPCHI2", B0_FitDDPVConst_Dplus_P2_IPCHI2, &b_B0_FitDDPVConst_Dplus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_P", B0_FitDDPVConst_Dplus_P2_P, &b_B0_FitDDPVConst_Dplus_P2_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_PE", B0_FitDDPVConst_Dplus_P2_PE, &b_B0_FitDDPVConst_Dplus_P2_PE);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_PERR", B0_FitDDPVConst_Dplus_P2_PERR, &b_B0_FitDDPVConst_Dplus_P2_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_PT", B0_FitDDPVConst_Dplus_P2_PT, &b_B0_FitDDPVConst_Dplus_P2_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_PTERR", B0_FitDDPVConst_Dplus_P2_PTERR, &b_B0_FitDDPVConst_Dplus_P2_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_PX", B0_FitDDPVConst_Dplus_P2_PX, &b_B0_FitDDPVConst_Dplus_P2_PX);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_PY", B0_FitDDPVConst_Dplus_P2_PY, &b_B0_FitDDPVConst_Dplus_P2_PY);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_PZ", B0_FitDDPVConst_Dplus_P2_PZ, &b_B0_FitDDPVConst_Dplus_P2_PZ);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_X", B0_FitDDPVConst_Dplus_P2_X, &b_B0_FitDDPVConst_Dplus_P2_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_XERR", B0_FitDDPVConst_Dplus_P2_XERR, &b_B0_FitDDPVConst_Dplus_P2_XERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_Y", B0_FitDDPVConst_Dplus_P2_Y, &b_B0_FitDDPVConst_Dplus_P2_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_YERR", B0_FitDDPVConst_Dplus_P2_YERR, &b_B0_FitDDPVConst_Dplus_P2_YERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_Z", B0_FitDDPVConst_Dplus_P2_Z, &b_B0_FitDDPVConst_Dplus_P2_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_P2_ZERR", B0_FitDDPVConst_Dplus_P2_ZERR, &b_B0_FitDDPVConst_Dplus_P2_ZERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_PERR", B0_FitDDPVConst_Dplus_PERR, &b_B0_FitDDPVConst_Dplus_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_PT", B0_FitDDPVConst_Dplus_PT, &b_B0_FitDDPVConst_Dplus_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_PTERR", B0_FitDDPVConst_Dplus_PTERR, &b_B0_FitDDPVConst_Dplus_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_ctau", B0_FitDDPVConst_Dplus_ctau, &b_B0_FitDDPVConst_Dplus_ctau);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_ctauErr", B0_FitDDPVConst_Dplus_ctauErr, &b_B0_FitDDPVConst_Dplus_ctauErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_decayLength", B0_FitDDPVConst_Dplus_decayLength, &b_B0_FitDDPVConst_Dplus_decayLength);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_decayLengthErr", B0_FitDDPVConst_Dplus_decayLengthErr, &b_B0_FitDDPVConst_Dplus_decayLengthErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_tau", B0_FitDDPVConst_Dplus_tau, &b_B0_FitDDPVConst_Dplus_tau);
   fChain->SetBranchAddress("B0_FitDDPVConst_Dplus_tauErr", B0_FitDDPVConst_Dplus_tauErr, &b_B0_FitDDPVConst_Dplus_tauErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_IP", B0_FitDDPVConst_IP, &b_B0_FitDDPVConst_IP);
   fChain->SetBranchAddress("B0_FitDDPVConst_IPCHI2", B0_FitDDPVConst_IPCHI2, &b_B0_FitDDPVConst_IPCHI2);
   fChain->SetBranchAddress("B0_FitDDPVConst_M", B0_FitDDPVConst_M, &b_B0_FitDDPVConst_M);
   fChain->SetBranchAddress("B0_FitDDPVConst_MERR", B0_FitDDPVConst_MERR, &b_B0_FitDDPVConst_MERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_P", B0_FitDDPVConst_P, &b_B0_FitDDPVConst_P);
   fChain->SetBranchAddress("B0_FitDDPVConst_PERR", B0_FitDDPVConst_PERR, &b_B0_FitDDPVConst_PERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_PT", B0_FitDDPVConst_PT, &b_B0_FitDDPVConst_PT);
   fChain->SetBranchAddress("B0_FitDDPVConst_PTERR", B0_FitDDPVConst_PTERR, &b_B0_FitDDPVConst_PTERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_X", B0_FitDDPVConst_PV_X, &b_B0_FitDDPVConst_PV_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_XVAR", B0_FitDDPVConst_PV_XVAR, &b_B0_FitDDPVConst_PV_XVAR);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_XYCOV", B0_FitDDPVConst_PV_XYCOV, &b_B0_FitDDPVConst_PV_XYCOV);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_XZCOV", B0_FitDDPVConst_PV_XZCOV, &b_B0_FitDDPVConst_PV_XZCOV);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_Y", B0_FitDDPVConst_PV_Y, &b_B0_FitDDPVConst_PV_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_YVAR", B0_FitDDPVConst_PV_YVAR, &b_B0_FitDDPVConst_PV_YVAR);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_YZCOV", B0_FitDDPVConst_PV_YZCOV, &b_B0_FitDDPVConst_PV_YZCOV);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_Z", B0_FitDDPVConst_PV_Z, &b_B0_FitDDPVConst_PV_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_ZVAR", B0_FitDDPVConst_PV_ZVAR, &b_B0_FitDDPVConst_PV_ZVAR);
   fChain->SetBranchAddress("B0_FitDDPVConst_PV_key", B0_FitDDPVConst_PV_key, &b_B0_FitDDPVConst_PV_key);
   fChain->SetBranchAddress("B0_FitDDPVConst_X", B0_FitDDPVConst_X, &b_B0_FitDDPVConst_X);
   fChain->SetBranchAddress("B0_FitDDPVConst_XERR", B0_FitDDPVConst_XERR, &b_B0_FitDDPVConst_XERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Y", B0_FitDDPVConst_Y, &b_B0_FitDDPVConst_Y);
   fChain->SetBranchAddress("B0_FitDDPVConst_YERR", B0_FitDDPVConst_YERR, &b_B0_FitDDPVConst_YERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_Z", B0_FitDDPVConst_Z, &b_B0_FitDDPVConst_Z);
   fChain->SetBranchAddress("B0_FitDDPVConst_ZERR", B0_FitDDPVConst_ZERR, &b_B0_FitDDPVConst_ZERR);
   fChain->SetBranchAddress("B0_FitDDPVConst_chi2", B0_FitDDPVConst_chi2, &b_B0_FitDDPVConst_chi2);
   fChain->SetBranchAddress("B0_FitDDPVConst_ctau", B0_FitDDPVConst_ctau, &b_B0_FitDDPVConst_ctau);
   fChain->SetBranchAddress("B0_FitDDPVConst_ctauErr", B0_FitDDPVConst_ctauErr, &b_B0_FitDDPVConst_ctauErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_decayLength", B0_FitDDPVConst_decayLength, &b_B0_FitDDPVConst_decayLength);
   fChain->SetBranchAddress("B0_FitDDPVConst_decayLengthErr", B0_FitDDPVConst_decayLengthErr, &b_B0_FitDDPVConst_decayLengthErr);
   fChain->SetBranchAddress("B0_FitDDPVConst_nDOF", B0_FitDDPVConst_nDOF, &b_B0_FitDDPVConst_nDOF);
   fChain->SetBranchAddress("B0_FitDDPVConst_nIter", B0_FitDDPVConst_nIter, &b_B0_FitDDPVConst_nIter);
   fChain->SetBranchAddress("B0_FitDDPVConst_status", B0_FitDDPVConst_status, &b_B0_FitDDPVConst_status);
   fChain->SetBranchAddress("B0_FitDDPVConst_tau", B0_FitDDPVConst_tau, &b_B0_FitDDPVConst_tau);
   fChain->SetBranchAddress("B0_FitDDPVConst_tauErr", B0_FitDDPVConst_tauErr, &b_B0_FitDDPVConst_tauErr);
   fChain->SetBranchAddress("B0_FitPVConst_nPV", &B0_FitPVConst_nPV, &b_B0_FitPVConst_nPV);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_IP", B0_FitPVConst_Dminus_IP, &b_B0_FitPVConst_Dminus_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_IPCHI2", B0_FitPVConst_Dminus_IPCHI2, &b_B0_FitPVConst_Dminus_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_M", B0_FitPVConst_Dminus_M, &b_B0_FitPVConst_Dminus_M);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_MERR", B0_FitPVConst_Dminus_MERR, &b_B0_FitPVConst_Dminus_MERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P", B0_FitPVConst_Dminus_P, &b_B0_FitPVConst_Dminus_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_ID", B0_FitPVConst_Dminus_P0_ID, &b_B0_FitPVConst_Dminus_P0_ID);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_IP", B0_FitPVConst_Dminus_P0_IP, &b_B0_FitPVConst_Dminus_P0_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_IPCHI2", B0_FitPVConst_Dminus_P0_IPCHI2, &b_B0_FitPVConst_Dminus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_P", B0_FitPVConst_Dminus_P0_P, &b_B0_FitPVConst_Dminus_P0_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_PE", B0_FitPVConst_Dminus_P0_PE, &b_B0_FitPVConst_Dminus_P0_PE);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_PERR", B0_FitPVConst_Dminus_P0_PERR, &b_B0_FitPVConst_Dminus_P0_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_PT", B0_FitPVConst_Dminus_P0_PT, &b_B0_FitPVConst_Dminus_P0_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_PTERR", B0_FitPVConst_Dminus_P0_PTERR, &b_B0_FitPVConst_Dminus_P0_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_PX", B0_FitPVConst_Dminus_P0_PX, &b_B0_FitPVConst_Dminus_P0_PX);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_PY", B0_FitPVConst_Dminus_P0_PY, &b_B0_FitPVConst_Dminus_P0_PY);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_PZ", B0_FitPVConst_Dminus_P0_PZ, &b_B0_FitPVConst_Dminus_P0_PZ);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_X", B0_FitPVConst_Dminus_P0_X, &b_B0_FitPVConst_Dminus_P0_X);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_XERR", B0_FitPVConst_Dminus_P0_XERR, &b_B0_FitPVConst_Dminus_P0_XERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_Y", B0_FitPVConst_Dminus_P0_Y, &b_B0_FitPVConst_Dminus_P0_Y);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_YERR", B0_FitPVConst_Dminus_P0_YERR, &b_B0_FitPVConst_Dminus_P0_YERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_Z", B0_FitPVConst_Dminus_P0_Z, &b_B0_FitPVConst_Dminus_P0_Z);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P0_ZERR", B0_FitPVConst_Dminus_P0_ZERR, &b_B0_FitPVConst_Dminus_P0_ZERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_ID", B0_FitPVConst_Dminus_P1_ID, &b_B0_FitPVConst_Dminus_P1_ID);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_IP", B0_FitPVConst_Dminus_P1_IP, &b_B0_FitPVConst_Dminus_P1_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_IPCHI2", B0_FitPVConst_Dminus_P1_IPCHI2, &b_B0_FitPVConst_Dminus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_P", B0_FitPVConst_Dminus_P1_P, &b_B0_FitPVConst_Dminus_P1_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_PE", B0_FitPVConst_Dminus_P1_PE, &b_B0_FitPVConst_Dminus_P1_PE);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_PERR", B0_FitPVConst_Dminus_P1_PERR, &b_B0_FitPVConst_Dminus_P1_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_PT", B0_FitPVConst_Dminus_P1_PT, &b_B0_FitPVConst_Dminus_P1_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_PTERR", B0_FitPVConst_Dminus_P1_PTERR, &b_B0_FitPVConst_Dminus_P1_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_PX", B0_FitPVConst_Dminus_P1_PX, &b_B0_FitPVConst_Dminus_P1_PX);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_PY", B0_FitPVConst_Dminus_P1_PY, &b_B0_FitPVConst_Dminus_P1_PY);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_PZ", B0_FitPVConst_Dminus_P1_PZ, &b_B0_FitPVConst_Dminus_P1_PZ);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_X", B0_FitPVConst_Dminus_P1_X, &b_B0_FitPVConst_Dminus_P1_X);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_XERR", B0_FitPVConst_Dminus_P1_XERR, &b_B0_FitPVConst_Dminus_P1_XERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_Y", B0_FitPVConst_Dminus_P1_Y, &b_B0_FitPVConst_Dminus_P1_Y);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_YERR", B0_FitPVConst_Dminus_P1_YERR, &b_B0_FitPVConst_Dminus_P1_YERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_Z", B0_FitPVConst_Dminus_P1_Z, &b_B0_FitPVConst_Dminus_P1_Z);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P1_ZERR", B0_FitPVConst_Dminus_P1_ZERR, &b_B0_FitPVConst_Dminus_P1_ZERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_ID", B0_FitPVConst_Dminus_P2_ID, &b_B0_FitPVConst_Dminus_P2_ID);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_IP", B0_FitPVConst_Dminus_P2_IP, &b_B0_FitPVConst_Dminus_P2_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_IPCHI2", B0_FitPVConst_Dminus_P2_IPCHI2, &b_B0_FitPVConst_Dminus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_P", B0_FitPVConst_Dminus_P2_P, &b_B0_FitPVConst_Dminus_P2_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_PE", B0_FitPVConst_Dminus_P2_PE, &b_B0_FitPVConst_Dminus_P2_PE);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_PERR", B0_FitPVConst_Dminus_P2_PERR, &b_B0_FitPVConst_Dminus_P2_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_PT", B0_FitPVConst_Dminus_P2_PT, &b_B0_FitPVConst_Dminus_P2_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_PTERR", B0_FitPVConst_Dminus_P2_PTERR, &b_B0_FitPVConst_Dminus_P2_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_PX", B0_FitPVConst_Dminus_P2_PX, &b_B0_FitPVConst_Dminus_P2_PX);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_PY", B0_FitPVConst_Dminus_P2_PY, &b_B0_FitPVConst_Dminus_P2_PY);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_PZ", B0_FitPVConst_Dminus_P2_PZ, &b_B0_FitPVConst_Dminus_P2_PZ);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_X", B0_FitPVConst_Dminus_P2_X, &b_B0_FitPVConst_Dminus_P2_X);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_XERR", B0_FitPVConst_Dminus_P2_XERR, &b_B0_FitPVConst_Dminus_P2_XERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_Y", B0_FitPVConst_Dminus_P2_Y, &b_B0_FitPVConst_Dminus_P2_Y);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_YERR", B0_FitPVConst_Dminus_P2_YERR, &b_B0_FitPVConst_Dminus_P2_YERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_Z", B0_FitPVConst_Dminus_P2_Z, &b_B0_FitPVConst_Dminus_P2_Z);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_P2_ZERR", B0_FitPVConst_Dminus_P2_ZERR, &b_B0_FitPVConst_Dminus_P2_ZERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_PERR", B0_FitPVConst_Dminus_PERR, &b_B0_FitPVConst_Dminus_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_PT", B0_FitPVConst_Dminus_PT, &b_B0_FitPVConst_Dminus_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_PTERR", B0_FitPVConst_Dminus_PTERR, &b_B0_FitPVConst_Dminus_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_ctau", B0_FitPVConst_Dminus_ctau, &b_B0_FitPVConst_Dminus_ctau);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_ctauErr", B0_FitPVConst_Dminus_ctauErr, &b_B0_FitPVConst_Dminus_ctauErr);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_decayLength", B0_FitPVConst_Dminus_decayLength, &b_B0_FitPVConst_Dminus_decayLength);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_decayLengthErr", B0_FitPVConst_Dminus_decayLengthErr, &b_B0_FitPVConst_Dminus_decayLengthErr);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_tau", B0_FitPVConst_Dminus_tau, &b_B0_FitPVConst_Dminus_tau);
   fChain->SetBranchAddress("B0_FitPVConst_Dminus_tauErr", B0_FitPVConst_Dminus_tauErr, &b_B0_FitPVConst_Dminus_tauErr);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_IP", B0_FitPVConst_Dplus_IP, &b_B0_FitPVConst_Dplus_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_IPCHI2", B0_FitPVConst_Dplus_IPCHI2, &b_B0_FitPVConst_Dplus_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_M", B0_FitPVConst_Dplus_M, &b_B0_FitPVConst_Dplus_M);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_MERR", B0_FitPVConst_Dplus_MERR, &b_B0_FitPVConst_Dplus_MERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P", B0_FitPVConst_Dplus_P, &b_B0_FitPVConst_Dplus_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_ID", B0_FitPVConst_Dplus_P0_ID, &b_B0_FitPVConst_Dplus_P0_ID);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_IP", B0_FitPVConst_Dplus_P0_IP, &b_B0_FitPVConst_Dplus_P0_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_IPCHI2", B0_FitPVConst_Dplus_P0_IPCHI2, &b_B0_FitPVConst_Dplus_P0_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_P", B0_FitPVConst_Dplus_P0_P, &b_B0_FitPVConst_Dplus_P0_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_PE", B0_FitPVConst_Dplus_P0_PE, &b_B0_FitPVConst_Dplus_P0_PE);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_PERR", B0_FitPVConst_Dplus_P0_PERR, &b_B0_FitPVConst_Dplus_P0_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_PT", B0_FitPVConst_Dplus_P0_PT, &b_B0_FitPVConst_Dplus_P0_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_PTERR", B0_FitPVConst_Dplus_P0_PTERR, &b_B0_FitPVConst_Dplus_P0_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_PX", B0_FitPVConst_Dplus_P0_PX, &b_B0_FitPVConst_Dplus_P0_PX);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_PY", B0_FitPVConst_Dplus_P0_PY, &b_B0_FitPVConst_Dplus_P0_PY);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_PZ", B0_FitPVConst_Dplus_P0_PZ, &b_B0_FitPVConst_Dplus_P0_PZ);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_X", B0_FitPVConst_Dplus_P0_X, &b_B0_FitPVConst_Dplus_P0_X);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_XERR", B0_FitPVConst_Dplus_P0_XERR, &b_B0_FitPVConst_Dplus_P0_XERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_Y", B0_FitPVConst_Dplus_P0_Y, &b_B0_FitPVConst_Dplus_P0_Y);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_YERR", B0_FitPVConst_Dplus_P0_YERR, &b_B0_FitPVConst_Dplus_P0_YERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_Z", B0_FitPVConst_Dplus_P0_Z, &b_B0_FitPVConst_Dplus_P0_Z);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P0_ZERR", B0_FitPVConst_Dplus_P0_ZERR, &b_B0_FitPVConst_Dplus_P0_ZERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_ID", B0_FitPVConst_Dplus_P1_ID, &b_B0_FitPVConst_Dplus_P1_ID);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_IP", B0_FitPVConst_Dplus_P1_IP, &b_B0_FitPVConst_Dplus_P1_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_IPCHI2", B0_FitPVConst_Dplus_P1_IPCHI2, &b_B0_FitPVConst_Dplus_P1_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_P", B0_FitPVConst_Dplus_P1_P, &b_B0_FitPVConst_Dplus_P1_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_PE", B0_FitPVConst_Dplus_P1_PE, &b_B0_FitPVConst_Dplus_P1_PE);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_PERR", B0_FitPVConst_Dplus_P1_PERR, &b_B0_FitPVConst_Dplus_P1_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_PT", B0_FitPVConst_Dplus_P1_PT, &b_B0_FitPVConst_Dplus_P1_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_PTERR", B0_FitPVConst_Dplus_P1_PTERR, &b_B0_FitPVConst_Dplus_P1_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_PX", B0_FitPVConst_Dplus_P1_PX, &b_B0_FitPVConst_Dplus_P1_PX);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_PY", B0_FitPVConst_Dplus_P1_PY, &b_B0_FitPVConst_Dplus_P1_PY);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_PZ", B0_FitPVConst_Dplus_P1_PZ, &b_B0_FitPVConst_Dplus_P1_PZ);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_X", B0_FitPVConst_Dplus_P1_X, &b_B0_FitPVConst_Dplus_P1_X);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_XERR", B0_FitPVConst_Dplus_P1_XERR, &b_B0_FitPVConst_Dplus_P1_XERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_Y", B0_FitPVConst_Dplus_P1_Y, &b_B0_FitPVConst_Dplus_P1_Y);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_YERR", B0_FitPVConst_Dplus_P1_YERR, &b_B0_FitPVConst_Dplus_P1_YERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_Z", B0_FitPVConst_Dplus_P1_Z, &b_B0_FitPVConst_Dplus_P1_Z);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P1_ZERR", B0_FitPVConst_Dplus_P1_ZERR, &b_B0_FitPVConst_Dplus_P1_ZERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_ID", B0_FitPVConst_Dplus_P2_ID, &b_B0_FitPVConst_Dplus_P2_ID);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_IP", B0_FitPVConst_Dplus_P2_IP, &b_B0_FitPVConst_Dplus_P2_IP);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_IPCHI2", B0_FitPVConst_Dplus_P2_IPCHI2, &b_B0_FitPVConst_Dplus_P2_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_P", B0_FitPVConst_Dplus_P2_P, &b_B0_FitPVConst_Dplus_P2_P);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_PE", B0_FitPVConst_Dplus_P2_PE, &b_B0_FitPVConst_Dplus_P2_PE);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_PERR", B0_FitPVConst_Dplus_P2_PERR, &b_B0_FitPVConst_Dplus_P2_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_PT", B0_FitPVConst_Dplus_P2_PT, &b_B0_FitPVConst_Dplus_P2_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_PTERR", B0_FitPVConst_Dplus_P2_PTERR, &b_B0_FitPVConst_Dplus_P2_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_PX", B0_FitPVConst_Dplus_P2_PX, &b_B0_FitPVConst_Dplus_P2_PX);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_PY", B0_FitPVConst_Dplus_P2_PY, &b_B0_FitPVConst_Dplus_P2_PY);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_PZ", B0_FitPVConst_Dplus_P2_PZ, &b_B0_FitPVConst_Dplus_P2_PZ);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_X", B0_FitPVConst_Dplus_P2_X, &b_B0_FitPVConst_Dplus_P2_X);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_XERR", B0_FitPVConst_Dplus_P2_XERR, &b_B0_FitPVConst_Dplus_P2_XERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_Y", B0_FitPVConst_Dplus_P2_Y, &b_B0_FitPVConst_Dplus_P2_Y);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_YERR", B0_FitPVConst_Dplus_P2_YERR, &b_B0_FitPVConst_Dplus_P2_YERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_Z", B0_FitPVConst_Dplus_P2_Z, &b_B0_FitPVConst_Dplus_P2_Z);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_P2_ZERR", B0_FitPVConst_Dplus_P2_ZERR, &b_B0_FitPVConst_Dplus_P2_ZERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_PERR", B0_FitPVConst_Dplus_PERR, &b_B0_FitPVConst_Dplus_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_PT", B0_FitPVConst_Dplus_PT, &b_B0_FitPVConst_Dplus_PT);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_PTERR", B0_FitPVConst_Dplus_PTERR, &b_B0_FitPVConst_Dplus_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_ctau", B0_FitPVConst_Dplus_ctau, &b_B0_FitPVConst_Dplus_ctau);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_ctauErr", B0_FitPVConst_Dplus_ctauErr, &b_B0_FitPVConst_Dplus_ctauErr);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_decayLength", B0_FitPVConst_Dplus_decayLength, &b_B0_FitPVConst_Dplus_decayLength);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_decayLengthErr", B0_FitPVConst_Dplus_decayLengthErr, &b_B0_FitPVConst_Dplus_decayLengthErr);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_tau", B0_FitPVConst_Dplus_tau, &b_B0_FitPVConst_Dplus_tau);
   fChain->SetBranchAddress("B0_FitPVConst_Dplus_tauErr", B0_FitPVConst_Dplus_tauErr, &b_B0_FitPVConst_Dplus_tauErr);
   fChain->SetBranchAddress("B0_FitPVConst_IP", B0_FitPVConst_IP, &b_B0_FitPVConst_IP);
   fChain->SetBranchAddress("B0_FitPVConst_IPCHI2", B0_FitPVConst_IPCHI2, &b_B0_FitPVConst_IPCHI2);
   fChain->SetBranchAddress("B0_FitPVConst_M", B0_FitPVConst_M, &b_B0_FitPVConst_M);
   fChain->SetBranchAddress("B0_FitPVConst_MERR", B0_FitPVConst_MERR, &b_B0_FitPVConst_MERR);
   fChain->SetBranchAddress("B0_FitPVConst_P", B0_FitPVConst_P, &b_B0_FitPVConst_P);
   fChain->SetBranchAddress("B0_FitPVConst_PERR", B0_FitPVConst_PERR, &b_B0_FitPVConst_PERR);
   fChain->SetBranchAddress("B0_FitPVConst_PT", B0_FitPVConst_PT, &b_B0_FitPVConst_PT);
   fChain->SetBranchAddress("B0_FitPVConst_PTERR", B0_FitPVConst_PTERR, &b_B0_FitPVConst_PTERR);
   fChain->SetBranchAddress("B0_FitPVConst_PV_X", B0_FitPVConst_PV_X, &b_B0_FitPVConst_PV_X);
   fChain->SetBranchAddress("B0_FitPVConst_PV_XVAR", B0_FitPVConst_PV_XVAR, &b_B0_FitPVConst_PV_XVAR);
   fChain->SetBranchAddress("B0_FitPVConst_PV_XYCOV", B0_FitPVConst_PV_XYCOV, &b_B0_FitPVConst_PV_XYCOV);
   fChain->SetBranchAddress("B0_FitPVConst_PV_XZCOV", B0_FitPVConst_PV_XZCOV, &b_B0_FitPVConst_PV_XZCOV);
   fChain->SetBranchAddress("B0_FitPVConst_PV_Y", B0_FitPVConst_PV_Y, &b_B0_FitPVConst_PV_Y);
   fChain->SetBranchAddress("B0_FitPVConst_PV_YVAR", B0_FitPVConst_PV_YVAR, &b_B0_FitPVConst_PV_YVAR);
   fChain->SetBranchAddress("B0_FitPVConst_PV_YZCOV", B0_FitPVConst_PV_YZCOV, &b_B0_FitPVConst_PV_YZCOV);
   fChain->SetBranchAddress("B0_FitPVConst_PV_Z", B0_FitPVConst_PV_Z, &b_B0_FitPVConst_PV_Z);
   fChain->SetBranchAddress("B0_FitPVConst_PV_ZVAR", B0_FitPVConst_PV_ZVAR, &b_B0_FitPVConst_PV_ZVAR);
   fChain->SetBranchAddress("B0_FitPVConst_PV_key", B0_FitPVConst_PV_key, &b_B0_FitPVConst_PV_key);
   fChain->SetBranchAddress("B0_FitPVConst_X", B0_FitPVConst_X, &b_B0_FitPVConst_X);
   fChain->SetBranchAddress("B0_FitPVConst_XERR", B0_FitPVConst_XERR, &b_B0_FitPVConst_XERR);
   fChain->SetBranchAddress("B0_FitPVConst_Y", B0_FitPVConst_Y, &b_B0_FitPVConst_Y);
   fChain->SetBranchAddress("B0_FitPVConst_YERR", B0_FitPVConst_YERR, &b_B0_FitPVConst_YERR);
   fChain->SetBranchAddress("B0_FitPVConst_Z", B0_FitPVConst_Z, &b_B0_FitPVConst_Z);
   fChain->SetBranchAddress("B0_FitPVConst_ZERR", B0_FitPVConst_ZERR, &b_B0_FitPVConst_ZERR);
   fChain->SetBranchAddress("B0_FitPVConst_chi2", B0_FitPVConst_chi2, &b_B0_FitPVConst_chi2);
   fChain->SetBranchAddress("B0_FitPVConst_ctau", B0_FitPVConst_ctau, &b_B0_FitPVConst_ctau);
   fChain->SetBranchAddress("B0_FitPVConst_ctauErr", B0_FitPVConst_ctauErr, &b_B0_FitPVConst_ctauErr);
   fChain->SetBranchAddress("B0_FitPVConst_decayLength", B0_FitPVConst_decayLength, &b_B0_FitPVConst_decayLength);
   fChain->SetBranchAddress("B0_FitPVConst_decayLengthErr", B0_FitPVConst_decayLengthErr, &b_B0_FitPVConst_decayLengthErr);
   fChain->SetBranchAddress("B0_FitPVConst_nDOF", B0_FitPVConst_nDOF, &b_B0_FitPVConst_nDOF);
   fChain->SetBranchAddress("B0_FitPVConst_nIter", B0_FitPVConst_nIter, &b_B0_FitPVConst_nIter);
   fChain->SetBranchAddress("B0_FitPVConst_status", B0_FitPVConst_status, &b_B0_FitPVConst_status);
   fChain->SetBranchAddress("B0_FitPVConst_tau", B0_FitPVConst_tau, &b_B0_FitPVConst_tau);
   fChain->SetBranchAddress("B0_FitPVConst_tauErr", B0_FitPVConst_tauErr, &b_B0_FitPVConst_tauErr);
   fChain->SetBranchAddress("B0_L0Global_Dec", &B0_L0Global_Dec, &b_B0_L0Global_Dec);
   fChain->SetBranchAddress("B0_L0Global_TIS", &B0_L0Global_TIS, &b_B0_L0Global_TIS);
   fChain->SetBranchAddress("B0_L0Global_TOS", &B0_L0Global_TOS, &b_B0_L0Global_TOS);
   fChain->SetBranchAddress("B0_Hlt1Global_Dec", &B0_Hlt1Global_Dec, &b_B0_Hlt1Global_Dec);
   fChain->SetBranchAddress("B0_Hlt1Global_TIS", &B0_Hlt1Global_TIS, &b_B0_Hlt1Global_TIS);
   fChain->SetBranchAddress("B0_Hlt1Global_TOS", &B0_Hlt1Global_TOS, &b_B0_Hlt1Global_TOS);
   fChain->SetBranchAddress("B0_Hlt1Phys_Dec", &B0_Hlt1Phys_Dec, &b_B0_Hlt1Phys_Dec);
   fChain->SetBranchAddress("B0_Hlt1Phys_TIS", &B0_Hlt1Phys_TIS, &b_B0_Hlt1Phys_TIS);
   fChain->SetBranchAddress("B0_Hlt1Phys_TOS", &B0_Hlt1Phys_TOS, &b_B0_Hlt1Phys_TOS);
   fChain->SetBranchAddress("B0_Hlt2Global_Dec", &B0_Hlt2Global_Dec, &b_B0_Hlt2Global_Dec);
   fChain->SetBranchAddress("B0_Hlt2Global_TIS", &B0_Hlt2Global_TIS, &b_B0_Hlt2Global_TIS);
   fChain->SetBranchAddress("B0_Hlt2Global_TOS", &B0_Hlt2Global_TOS, &b_B0_Hlt2Global_TOS);
   fChain->SetBranchAddress("B0_Hlt2Phys_Dec", &B0_Hlt2Phys_Dec, &b_B0_Hlt2Phys_Dec);
   fChain->SetBranchAddress("B0_Hlt2Phys_TIS", &B0_Hlt2Phys_TIS, &b_B0_Hlt2Phys_TIS);
   fChain->SetBranchAddress("B0_Hlt2Phys_TOS", &B0_Hlt2Phys_TOS, &b_B0_Hlt2Phys_TOS);
   fChain->SetBranchAddress("B0_L0PhysicsDecision_Dec", &B0_L0PhysicsDecision_Dec, &b_B0_L0PhysicsDecision_Dec);
   fChain->SetBranchAddress("B0_L0PhysicsDecision_TIS", &B0_L0PhysicsDecision_TIS, &b_B0_L0PhysicsDecision_TIS);
   fChain->SetBranchAddress("B0_L0PhysicsDecision_TOS", &B0_L0PhysicsDecision_TOS, &b_B0_L0PhysicsDecision_TOS);
   fChain->SetBranchAddress("B0_L0MuonDecision_Dec", &B0_L0MuonDecision_Dec, &b_B0_L0MuonDecision_Dec);
   fChain->SetBranchAddress("B0_L0MuonDecision_TIS", &B0_L0MuonDecision_TIS, &b_B0_L0MuonDecision_TIS);
   fChain->SetBranchAddress("B0_L0MuonDecision_TOS", &B0_L0MuonDecision_TOS, &b_B0_L0MuonDecision_TOS);
   fChain->SetBranchAddress("B0_L0DiMuonDecision_Dec", &B0_L0DiMuonDecision_Dec, &b_B0_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("B0_L0DiMuonDecision_TIS", &B0_L0DiMuonDecision_TIS, &b_B0_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("B0_L0DiMuonDecision_TOS", &B0_L0DiMuonDecision_TOS, &b_B0_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("B0_L0MuonHighDecision_Dec", &B0_L0MuonHighDecision_Dec, &b_B0_L0MuonHighDecision_Dec);
   fChain->SetBranchAddress("B0_L0MuonHighDecision_TIS", &B0_L0MuonHighDecision_TIS, &b_B0_L0MuonHighDecision_TIS);
   fChain->SetBranchAddress("B0_L0MuonHighDecision_TOS", &B0_L0MuonHighDecision_TOS, &b_B0_L0MuonHighDecision_TOS);
   fChain->SetBranchAddress("B0_L0HadronDecision_Dec", &B0_L0HadronDecision_Dec, &b_B0_L0HadronDecision_Dec);
   fChain->SetBranchAddress("B0_L0HadronDecision_TIS", &B0_L0HadronDecision_TIS, &b_B0_L0HadronDecision_TIS);
   fChain->SetBranchAddress("B0_L0HadronDecision_TOS", &B0_L0HadronDecision_TOS, &b_B0_L0HadronDecision_TOS);
   fChain->SetBranchAddress("B0_L0ElectronDecision_Dec", &B0_L0ElectronDecision_Dec, &b_B0_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("B0_L0ElectronDecision_TIS", &B0_L0ElectronDecision_TIS, &b_B0_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("B0_L0ElectronDecision_TOS", &B0_L0ElectronDecision_TOS, &b_B0_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("B0_L0PhotonDecision_Dec", &B0_L0PhotonDecision_Dec, &b_B0_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("B0_L0PhotonDecision_TIS", &B0_L0PhotonDecision_TIS, &b_B0_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("B0_L0PhotonDecision_TOS", &B0_L0PhotonDecision_TOS, &b_B0_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt1TrackAllL0Decision_Dec", &B0_Hlt1TrackAllL0Decision_Dec, &b_B0_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("B0_Hlt1TrackAllL0Decision_TIS", &B0_Hlt1TrackAllL0Decision_TIS, &b_B0_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("B0_Hlt1TrackAllL0Decision_TOS", &B0_Hlt1TrackAllL0Decision_TOS, &b_B0_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("B0_Hlt1TrackAllL0TightDecision_Dec", &B0_Hlt1TrackAllL0TightDecision_Dec, &b_B0_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt1TrackAllL0TightDecision_TIS", &B0_Hlt1TrackAllL0TightDecision_TIS, &b_B0_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt1TrackAllL0TightDecision_TOS", &B0_Hlt1TrackAllL0TightDecision_TOS, &b_B0_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt1L0AnyDecision_Dec", &B0_Hlt1L0AnyDecision_Dec, &b_B0_Hlt1L0AnyDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt1L0AnyDecision_TIS", &B0_Hlt1L0AnyDecision_TIS, &b_B0_Hlt1L0AnyDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt1L0AnyDecision_TOS", &B0_Hlt1L0AnyDecision_TOS, &b_B0_Hlt1L0AnyDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt1GlobalDecision_Dec", &B0_Hlt1GlobalDecision_Dec, &b_B0_Hlt1GlobalDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt1GlobalDecision_TIS", &B0_Hlt1GlobalDecision_TIS, &b_B0_Hlt1GlobalDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt1GlobalDecision_TOS", &B0_Hlt1GlobalDecision_TOS, &b_B0_Hlt1GlobalDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2GlobalDecision_Dec", &B0_Hlt2GlobalDecision_Dec, &b_B0_Hlt2GlobalDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2GlobalDecision_TIS", &B0_Hlt2GlobalDecision_TIS, &b_B0_Hlt2GlobalDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2GlobalDecision_TOS", &B0_Hlt2GlobalDecision_TOS, &b_B0_Hlt2GlobalDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodySimpleDecision_Dec", &B0_Hlt2Topo2BodySimpleDecision_Dec, &b_B0_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodySimpleDecision_TIS", &B0_Hlt2Topo2BodySimpleDecision_TIS, &b_B0_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodySimpleDecision_TOS", &B0_Hlt2Topo2BodySimpleDecision_TOS, &b_B0_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2Topo3BodySimpleDecision_Dec", &B0_Hlt2Topo3BodySimpleDecision_Dec, &b_B0_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2Topo3BodySimpleDecision_TIS", &B0_Hlt2Topo3BodySimpleDecision_TIS, &b_B0_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2Topo3BodySimpleDecision_TOS", &B0_Hlt2Topo3BodySimpleDecision_TOS, &b_B0_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2Topo4BodySimpleDecision_Dec", &B0_Hlt2Topo4BodySimpleDecision_Dec, &b_B0_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2Topo4BodySimpleDecision_TIS", &B0_Hlt2Topo4BodySimpleDecision_TIS, &b_B0_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2Topo4BodySimpleDecision_TOS", &B0_Hlt2Topo4BodySimpleDecision_TOS, &b_B0_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodyBBDTDecision_Dec", &B0_Hlt2Topo2BodyBBDTDecision_Dec, &b_B0_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodyBBDTDecision_TIS", &B0_Hlt2Topo2BodyBBDTDecision_TIS, &b_B0_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodyBBDTDecision_TOS", &B0_Hlt2Topo2BodyBBDTDecision_TOS, &b_B0_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2Topo3BodyBBDTDecision_Dec", &B0_Hlt2Topo3BodyBBDTDecision_Dec, &b_B0_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2Topo3BodyBBDTDecision_TIS", &B0_Hlt2Topo3BodyBBDTDecision_TIS, &b_B0_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2Topo3BodyBBDTDecision_TOS", &B0_Hlt2Topo3BodyBBDTDecision_TOS, &b_B0_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2Topo4BodyBBDTDecision_Dec", &B0_Hlt2Topo4BodyBBDTDecision_Dec, &b_B0_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2Topo4BodyBBDTDecision_TIS", &B0_Hlt2Topo4BodyBBDTDecision_TIS, &b_B0_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2Topo4BodyBBDTDecision_TOS", &B0_Hlt2Topo4BodyBBDTDecision_TOS, &b_B0_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2TopoMu2BodyBBDTDecision_Dec", &B0_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_B0_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2TopoMu2BodyBBDTDecision_TIS", &B0_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_B0_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2TopoMu2BodyBBDTDecision_TOS", &B0_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_B0_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2TopoMu3BodyBBDTDecision_Dec", &B0_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_B0_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2TopoMu3BodyBBDTDecision_TIS", &B0_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_B0_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2TopoMu3BodyBBDTDecision_TOS", &B0_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_B0_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2TopoMu4BodyBBDTDecision_Dec", &B0_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_B0_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2TopoMu4BodyBBDTDecision_TIS", &B0_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_B0_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2TopoMu4BodyBBDTDecision_TOS", &B0_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_B0_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2TopoE2BodyBBDTDecision_Dec", &B0_Hlt2TopoE2BodyBBDTDecision_Dec, &b_B0_Hlt2TopoE2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2TopoE2BodyBBDTDecision_TIS", &B0_Hlt2TopoE2BodyBBDTDecision_TIS, &b_B0_Hlt2TopoE2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2TopoE2BodyBBDTDecision_TOS", &B0_Hlt2TopoE2BodyBBDTDecision_TOS, &b_B0_Hlt2TopoE2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2TopoE3BodyBBDTDecision_Dec", &B0_Hlt2TopoE3BodyBBDTDecision_Dec, &b_B0_Hlt2TopoE3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2TopoE3BodyBBDTDecision_TIS", &B0_Hlt2TopoE3BodyBBDTDecision_TIS, &b_B0_Hlt2TopoE3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2TopoE3BodyBBDTDecision_TOS", &B0_Hlt2TopoE3BodyBBDTDecision_TOS, &b_B0_Hlt2TopoE3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2TopoE4BodyBBDTDecision_Dec", &B0_Hlt2TopoE4BodyBBDTDecision_Dec, &b_B0_Hlt2TopoE4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2TopoE4BodyBBDTDecision_TIS", &B0_Hlt2TopoE4BodyBBDTDecision_TIS, &b_B0_Hlt2TopoE4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2TopoE4BodyBBDTDecision_TOS", &B0_Hlt2TopoE4BodyBBDTDecision_TOS, &b_B0_Hlt2TopoE4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2IncPhiDecision_Dec", &B0_Hlt2IncPhiDecision_Dec, &b_B0_Hlt2IncPhiDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2IncPhiDecision_TIS", &B0_Hlt2IncPhiDecision_TIS, &b_B0_Hlt2IncPhiDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2IncPhiDecision_TOS", &B0_Hlt2IncPhiDecision_TOS, &b_B0_Hlt2IncPhiDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2IncPhiSidebandsDecision_Dec", &B0_Hlt2IncPhiSidebandsDecision_Dec, &b_B0_Hlt2IncPhiSidebandsDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2IncPhiSidebandsDecision_TIS", &B0_Hlt2IncPhiSidebandsDecision_TIS, &b_B0_Hlt2IncPhiSidebandsDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2IncPhiSidebandsDecision_TOS", &B0_Hlt2IncPhiSidebandsDecision_TOS, &b_B0_Hlt2IncPhiSidebandsDecision_TOS);
   fChain->SetBranchAddress("B0_TAGDECISION", &B0_TAGDECISION, &b_B0_TAGDECISION);
   fChain->SetBranchAddress("B0_TAGOMEGA", &B0_TAGOMEGA, &b_B0_TAGOMEGA);
   fChain->SetBranchAddress("B0_TAGDECISION_OS", &B0_TAGDECISION_OS, &b_B0_TAGDECISION_OS);
   fChain->SetBranchAddress("B0_TAGOMEGA_OS", &B0_TAGOMEGA_OS, &b_B0_TAGOMEGA_OS);
   fChain->SetBranchAddress("B0_TAGGER", &B0_TAGGER, &b_B0_TAGGER);
   fChain->SetBranchAddress("B0_OS_Muon_DEC", &B0_OS_Muon_DEC, &b_B0_OS_Muon_DEC);
   fChain->SetBranchAddress("B0_OS_Muon_PROB", &B0_OS_Muon_PROB, &b_B0_OS_Muon_PROB);
   fChain->SetBranchAddress("B0_OS_Electron_DEC", &B0_OS_Electron_DEC, &b_B0_OS_Electron_DEC);
   fChain->SetBranchAddress("B0_OS_Electron_PROB", &B0_OS_Electron_PROB, &b_B0_OS_Electron_PROB);
   fChain->SetBranchAddress("B0_OS_Kaon_DEC", &B0_OS_Kaon_DEC, &b_B0_OS_Kaon_DEC);
   fChain->SetBranchAddress("B0_OS_Kaon_PROB", &B0_OS_Kaon_PROB, &b_B0_OS_Kaon_PROB);
   fChain->SetBranchAddress("B0_SS_Kaon_DEC", &B0_SS_Kaon_DEC, &b_B0_SS_Kaon_DEC);
   fChain->SetBranchAddress("B0_SS_Kaon_PROB", &B0_SS_Kaon_PROB, &b_B0_SS_Kaon_PROB);
   fChain->SetBranchAddress("B0_SS_Pion_DEC", &B0_SS_Pion_DEC, &b_B0_SS_Pion_DEC);
   fChain->SetBranchAddress("B0_SS_Pion_PROB", &B0_SS_Pion_PROB, &b_B0_SS_Pion_PROB);
   fChain->SetBranchAddress("B0_SS_PionBDT_DEC", &B0_SS_PionBDT_DEC, &b_B0_SS_PionBDT_DEC);
   fChain->SetBranchAddress("B0_SS_PionBDT_PROB", &B0_SS_PionBDT_PROB, &b_B0_SS_PionBDT_PROB);
   fChain->SetBranchAddress("B0_VtxCharge_DEC", &B0_VtxCharge_DEC, &b_B0_VtxCharge_DEC);
   fChain->SetBranchAddress("B0_VtxCharge_PROB", &B0_VtxCharge_PROB, &b_B0_VtxCharge_PROB);
   fChain->SetBranchAddress("B0_OS_nnetKaon_DEC", &B0_OS_nnetKaon_DEC, &b_B0_OS_nnetKaon_DEC);
   fChain->SetBranchAddress("B0_OS_nnetKaon_PROB", &B0_OS_nnetKaon_PROB, &b_B0_OS_nnetKaon_PROB);
   fChain->SetBranchAddress("B0_SS_nnetKaon_DEC", &B0_SS_nnetKaon_DEC, &b_B0_SS_nnetKaon_DEC);
   fChain->SetBranchAddress("B0_SS_nnetKaon_PROB", &B0_SS_nnetKaon_PROB, &b_B0_SS_nnetKaon_PROB);
   fChain->SetBranchAddress("B0_SS_Proton_DEC", &B0_SS_Proton_DEC, &b_B0_SS_Proton_DEC);
   fChain->SetBranchAddress("B0_SS_Proton_PROB", &B0_SS_Proton_PROB, &b_B0_SS_Proton_PROB);
   fChain->SetBranchAddress("B0_OS_Charm_DEC", &B0_OS_Charm_DEC, &b_B0_OS_Charm_DEC);
   fChain->SetBranchAddress("B0_OS_Charm_PROB", &B0_OS_Charm_PROB, &b_B0_OS_Charm_PROB);
   fChain->SetBranchAddress("Dplus_LOKI_ENERGY", &Dplus_LOKI_ENERGY, &b_Dplus_LOKI_ENERGY);
   fChain->SetBranchAddress("Dplus_LOKI_ETA", &Dplus_LOKI_ETA, &b_Dplus_LOKI_ETA);
   fChain->SetBranchAddress("Dplus_LOKI_PHI", &Dplus_LOKI_PHI, &b_Dplus_LOKI_PHI);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_X", &Dplus_ENDVERTEX_X, &b_Dplus_ENDVERTEX_X);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_Y", &Dplus_ENDVERTEX_Y, &b_Dplus_ENDVERTEX_Y);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_Z", &Dplus_ENDVERTEX_Z, &b_Dplus_ENDVERTEX_Z);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_XERR", &Dplus_ENDVERTEX_XERR, &b_Dplus_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_YERR", &Dplus_ENDVERTEX_YERR, &b_Dplus_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_ZERR", &Dplus_ENDVERTEX_ZERR, &b_Dplus_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_CHI2", &Dplus_ENDVERTEX_CHI2, &b_Dplus_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_NDOF", &Dplus_ENDVERTEX_NDOF, &b_Dplus_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Dplus_ENDVERTEX_COV_", Dplus_ENDVERTEX_COV_, &b_Dplus_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Dplus_OWNPV_X", &Dplus_OWNPV_X, &b_Dplus_OWNPV_X);
   fChain->SetBranchAddress("Dplus_OWNPV_Y", &Dplus_OWNPV_Y, &b_Dplus_OWNPV_Y);
   fChain->SetBranchAddress("Dplus_OWNPV_Z", &Dplus_OWNPV_Z, &b_Dplus_OWNPV_Z);
   fChain->SetBranchAddress("Dplus_OWNPV_XERR", &Dplus_OWNPV_XERR, &b_Dplus_OWNPV_XERR);
   fChain->SetBranchAddress("Dplus_OWNPV_YERR", &Dplus_OWNPV_YERR, &b_Dplus_OWNPV_YERR);
   fChain->SetBranchAddress("Dplus_OWNPV_ZERR", &Dplus_OWNPV_ZERR, &b_Dplus_OWNPV_ZERR);
   fChain->SetBranchAddress("Dplus_OWNPV_CHI2", &Dplus_OWNPV_CHI2, &b_Dplus_OWNPV_CHI2);
   fChain->SetBranchAddress("Dplus_OWNPV_NDOF", &Dplus_OWNPV_NDOF, &b_Dplus_OWNPV_NDOF);
   fChain->SetBranchAddress("Dplus_OWNPV_COV_", Dplus_OWNPV_COV_, &b_Dplus_OWNPV_COV_);
   fChain->SetBranchAddress("Dplus_IP_OWNPV", &Dplus_IP_OWNPV, &b_Dplus_IP_OWNPV);
   fChain->SetBranchAddress("Dplus_IPCHI2_OWNPV", &Dplus_IPCHI2_OWNPV, &b_Dplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dplus_FD_OWNPV", &Dplus_FD_OWNPV, &b_Dplus_FD_OWNPV);
   fChain->SetBranchAddress("Dplus_FDCHI2_OWNPV", &Dplus_FDCHI2_OWNPV, &b_Dplus_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Dplus_DIRA_OWNPV", &Dplus_DIRA_OWNPV, &b_Dplus_DIRA_OWNPV);
   fChain->SetBranchAddress("Dplus_ORIVX_X", &Dplus_ORIVX_X, &b_Dplus_ORIVX_X);
   fChain->SetBranchAddress("Dplus_ORIVX_Y", &Dplus_ORIVX_Y, &b_Dplus_ORIVX_Y);
   fChain->SetBranchAddress("Dplus_ORIVX_Z", &Dplus_ORIVX_Z, &b_Dplus_ORIVX_Z);
   fChain->SetBranchAddress("Dplus_ORIVX_XERR", &Dplus_ORIVX_XERR, &b_Dplus_ORIVX_XERR);
   fChain->SetBranchAddress("Dplus_ORIVX_YERR", &Dplus_ORIVX_YERR, &b_Dplus_ORIVX_YERR);
   fChain->SetBranchAddress("Dplus_ORIVX_ZERR", &Dplus_ORIVX_ZERR, &b_Dplus_ORIVX_ZERR);
   fChain->SetBranchAddress("Dplus_ORIVX_CHI2", &Dplus_ORIVX_CHI2, &b_Dplus_ORIVX_CHI2);
   fChain->SetBranchAddress("Dplus_ORIVX_NDOF", &Dplus_ORIVX_NDOF, &b_Dplus_ORIVX_NDOF);
   fChain->SetBranchAddress("Dplus_ORIVX_COV_", Dplus_ORIVX_COV_, &b_Dplus_ORIVX_COV_);
   fChain->SetBranchAddress("Dplus_FD_ORIVX", &Dplus_FD_ORIVX, &b_Dplus_FD_ORIVX);
   fChain->SetBranchAddress("Dplus_FDCHI2_ORIVX", &Dplus_FDCHI2_ORIVX, &b_Dplus_FDCHI2_ORIVX);
   fChain->SetBranchAddress("Dplus_DIRA_ORIVX", &Dplus_DIRA_ORIVX, &b_Dplus_DIRA_ORIVX);
   fChain->SetBranchAddress("Dplus_P", &Dplus_P, &b_Dplus_P);
   fChain->SetBranchAddress("Dplus_PT", &Dplus_PT, &b_Dplus_PT);
   fChain->SetBranchAddress("Dplus_PE", &Dplus_PE, &b_Dplus_PE);
   fChain->SetBranchAddress("Dplus_PX", &Dplus_PX, &b_Dplus_PX);
   fChain->SetBranchAddress("Dplus_PY", &Dplus_PY, &b_Dplus_PY);
   fChain->SetBranchAddress("Dplus_PZ", &Dplus_PZ, &b_Dplus_PZ);
   fChain->SetBranchAddress("Dplus_MM", &Dplus_MM, &b_Dplus_MM);
   fChain->SetBranchAddress("Dplus_MMERR", &Dplus_MMERR, &b_Dplus_MMERR);
   fChain->SetBranchAddress("Dplus_M", &Dplus_M, &b_Dplus_M);
   fChain->SetBranchAddress("Dplus_ID", &Dplus_ID, &b_Dplus_ID);
   fChain->SetBranchAddress("Dplus_TAU", &Dplus_TAU, &b_Dplus_TAU);
   fChain->SetBranchAddress("Dplus_TAUERR", &Dplus_TAUERR, &b_Dplus_TAUERR);
   fChain->SetBranchAddress("Dplus_TAUCHI2", &Dplus_TAUCHI2, &b_Dplus_TAUCHI2);
   fChain->SetBranchAddress("Dplus_X", &Dplus_X, &b_Dplus_X);
   fChain->SetBranchAddress("Dplus_Y", &Dplus_Y, &b_Dplus_Y);
   fChain->SetBranchAddress("Dplus_LOKI_VertexSeparation_CHI2", &Dplus_LOKI_VertexSeparation_CHI2, &b_Dplus_LOKI_VertexSeparation_CHI2);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_LOKI_ENERGY", &Dplus_Kminus_or_piminus_LOKI_ENERGY, &b_Dplus_Kminus_or_piminus_LOKI_ENERGY);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_LOKI_ETA", &Dplus_Kminus_or_piminus_LOKI_ETA, &b_Dplus_Kminus_or_piminus_LOKI_ETA);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_LOKI_PHI", &Dplus_Kminus_or_piminus_LOKI_PHI, &b_Dplus_Kminus_or_piminus_LOKI_PHI);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_X", &Dplus_Kminus_or_piminus_OWNPV_X, &b_Dplus_Kminus_or_piminus_OWNPV_X);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_Y", &Dplus_Kminus_or_piminus_OWNPV_Y, &b_Dplus_Kminus_or_piminus_OWNPV_Y);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_Z", &Dplus_Kminus_or_piminus_OWNPV_Z, &b_Dplus_Kminus_or_piminus_OWNPV_Z);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_XERR", &Dplus_Kminus_or_piminus_OWNPV_XERR, &b_Dplus_Kminus_or_piminus_OWNPV_XERR);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_YERR", &Dplus_Kminus_or_piminus_OWNPV_YERR, &b_Dplus_Kminus_or_piminus_OWNPV_YERR);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_ZERR", &Dplus_Kminus_or_piminus_OWNPV_ZERR, &b_Dplus_Kminus_or_piminus_OWNPV_ZERR);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_CHI2", &Dplus_Kminus_or_piminus_OWNPV_CHI2, &b_Dplus_Kminus_or_piminus_OWNPV_CHI2);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_NDOF", &Dplus_Kminus_or_piminus_OWNPV_NDOF, &b_Dplus_Kminus_or_piminus_OWNPV_NDOF);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_OWNPV_COV_", Dplus_Kminus_or_piminus_OWNPV_COV_, &b_Dplus_Kminus_or_piminus_OWNPV_COV_);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_IP_OWNPV", &Dplus_Kminus_or_piminus_IP_OWNPV, &b_Dplus_Kminus_or_piminus_IP_OWNPV);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_IPCHI2_OWNPV", &Dplus_Kminus_or_piminus_IPCHI2_OWNPV, &b_Dplus_Kminus_or_piminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_X", &Dplus_Kminus_or_piminus_ORIVX_X, &b_Dplus_Kminus_or_piminus_ORIVX_X);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_Y", &Dplus_Kminus_or_piminus_ORIVX_Y, &b_Dplus_Kminus_or_piminus_ORIVX_Y);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_Z", &Dplus_Kminus_or_piminus_ORIVX_Z, &b_Dplus_Kminus_or_piminus_ORIVX_Z);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_XERR", &Dplus_Kminus_or_piminus_ORIVX_XERR, &b_Dplus_Kminus_or_piminus_ORIVX_XERR);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_YERR", &Dplus_Kminus_or_piminus_ORIVX_YERR, &b_Dplus_Kminus_or_piminus_ORIVX_YERR);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_ZERR", &Dplus_Kminus_or_piminus_ORIVX_ZERR, &b_Dplus_Kminus_or_piminus_ORIVX_ZERR);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_CHI2", &Dplus_Kminus_or_piminus_ORIVX_CHI2, &b_Dplus_Kminus_or_piminus_ORIVX_CHI2);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_NDOF", &Dplus_Kminus_or_piminus_ORIVX_NDOF, &b_Dplus_Kminus_or_piminus_ORIVX_NDOF);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ORIVX_COV_", Dplus_Kminus_or_piminus_ORIVX_COV_, &b_Dplus_Kminus_or_piminus_ORIVX_COV_);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_P", &Dplus_Kminus_or_piminus_P, &b_Dplus_Kminus_or_piminus_P);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PT", &Dplus_Kminus_or_piminus_PT, &b_Dplus_Kminus_or_piminus_PT);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PE", &Dplus_Kminus_or_piminus_PE, &b_Dplus_Kminus_or_piminus_PE);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PX", &Dplus_Kminus_or_piminus_PX, &b_Dplus_Kminus_or_piminus_PX);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PY", &Dplus_Kminus_or_piminus_PY, &b_Dplus_Kminus_or_piminus_PY);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PZ", &Dplus_Kminus_or_piminus_PZ, &b_Dplus_Kminus_or_piminus_PZ);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_M", &Dplus_Kminus_or_piminus_M, &b_Dplus_Kminus_or_piminus_M);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ID", &Dplus_Kminus_or_piminus_ID, &b_Dplus_Kminus_or_piminus_ID);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PIDe", &Dplus_Kminus_or_piminus_PIDe, &b_Dplus_Kminus_or_piminus_PIDe);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PIDmu", &Dplus_Kminus_or_piminus_PIDmu, &b_Dplus_Kminus_or_piminus_PIDmu);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PIDK", &Dplus_Kminus_or_piminus_PIDK, &b_Dplus_Kminus_or_piminus_PIDK);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PIDp", &Dplus_Kminus_or_piminus_PIDp, &b_Dplus_Kminus_or_piminus_PIDp);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ProbNNe", &Dplus_Kminus_or_piminus_ProbNNe, &b_Dplus_Kminus_or_piminus_ProbNNe);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ProbNNk", &Dplus_Kminus_or_piminus_ProbNNk, &b_Dplus_Kminus_or_piminus_ProbNNk);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ProbNNp", &Dplus_Kminus_or_piminus_ProbNNp, &b_Dplus_Kminus_or_piminus_ProbNNp);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ProbNNpi", &Dplus_Kminus_or_piminus_ProbNNpi, &b_Dplus_Kminus_or_piminus_ProbNNpi);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ProbNNmu", &Dplus_Kminus_or_piminus_ProbNNmu, &b_Dplus_Kminus_or_piminus_ProbNNmu);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_ProbNNghost", &Dplus_Kminus_or_piminus_ProbNNghost, &b_Dplus_Kminus_or_piminus_ProbNNghost);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_hasMuon", &Dplus_Kminus_or_piminus_hasMuon, &b_Dplus_Kminus_or_piminus_hasMuon);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_isMuon", &Dplus_Kminus_or_piminus_isMuon, &b_Dplus_Kminus_or_piminus_isMuon);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_hasRich", &Dplus_Kminus_or_piminus_hasRich, &b_Dplus_Kminus_or_piminus_hasRich);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_hasCalo", &Dplus_Kminus_or_piminus_hasCalo, &b_Dplus_Kminus_or_piminus_hasCalo);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_UsedRichAerogel", &Dplus_Kminus_or_piminus_UsedRichAerogel, &b_Dplus_Kminus_or_piminus_UsedRichAerogel);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_UsedRich1Gas", &Dplus_Kminus_or_piminus_UsedRich1Gas, &b_Dplus_Kminus_or_piminus_UsedRich1Gas);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_UsedRich2Gas", &Dplus_Kminus_or_piminus_UsedRich2Gas, &b_Dplus_Kminus_or_piminus_UsedRich2Gas);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichAboveElThres", &Dplus_Kminus_or_piminus_RichAboveElThres, &b_Dplus_Kminus_or_piminus_RichAboveElThres);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichAboveMuThres", &Dplus_Kminus_or_piminus_RichAboveMuThres, &b_Dplus_Kminus_or_piminus_RichAboveMuThres);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichAbovePiThres", &Dplus_Kminus_or_piminus_RichAbovePiThres, &b_Dplus_Kminus_or_piminus_RichAbovePiThres);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichAboveKaThres", &Dplus_Kminus_or_piminus_RichAboveKaThres, &b_Dplus_Kminus_or_piminus_RichAboveKaThres);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichAbovePrThres", &Dplus_Kminus_or_piminus_RichAbovePrThres, &b_Dplus_Kminus_or_piminus_RichAbovePrThres);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichDLLe", &Dplus_Kminus_or_piminus_RichDLLe, &b_Dplus_Kminus_or_piminus_RichDLLe);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichDLLmu", &Dplus_Kminus_or_piminus_RichDLLmu, &b_Dplus_Kminus_or_piminus_RichDLLmu);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichDLLpi", &Dplus_Kminus_or_piminus_RichDLLpi, &b_Dplus_Kminus_or_piminus_RichDLLpi);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichDLLk", &Dplus_Kminus_or_piminus_RichDLLk, &b_Dplus_Kminus_or_piminus_RichDLLk);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichDLLp", &Dplus_Kminus_or_piminus_RichDLLp, &b_Dplus_Kminus_or_piminus_RichDLLp);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_RichDLLbt", &Dplus_Kminus_or_piminus_RichDLLbt, &b_Dplus_Kminus_or_piminus_RichDLLbt);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_InAccMuon", &Dplus_Kminus_or_piminus_InAccMuon, &b_Dplus_Kminus_or_piminus_InAccMuon);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_isMuonLoose", &Dplus_Kminus_or_piminus_isMuonLoose, &b_Dplus_Kminus_or_piminus_isMuonLoose);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_MuonMuLL", &Dplus_Kminus_or_piminus_MuonMuLL, &b_Dplus_Kminus_or_piminus_MuonMuLL);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_MuonBkgLL", &Dplus_Kminus_or_piminus_MuonBkgLL, &b_Dplus_Kminus_or_piminus_MuonBkgLL);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_MuonNShared", &Dplus_Kminus_or_piminus_MuonNShared, &b_Dplus_Kminus_or_piminus_MuonNShared);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_InAccEcal", &Dplus_Kminus_or_piminus_InAccEcal, &b_Dplus_Kminus_or_piminus_InAccEcal);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_CaloEcalE", &Dplus_Kminus_or_piminus_CaloEcalE, &b_Dplus_Kminus_or_piminus_CaloEcalE);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_EcalPIDe", &Dplus_Kminus_or_piminus_EcalPIDe, &b_Dplus_Kminus_or_piminus_EcalPIDe);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_EcalPIDmu", &Dplus_Kminus_or_piminus_EcalPIDmu, &b_Dplus_Kminus_or_piminus_EcalPIDmu);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_InAccHcal", &Dplus_Kminus_or_piminus_InAccHcal, &b_Dplus_Kminus_or_piminus_InAccHcal);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_CaloHcalE", &Dplus_Kminus_or_piminus_CaloHcalE, &b_Dplus_Kminus_or_piminus_CaloHcalE);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_HcalPIDe", &Dplus_Kminus_or_piminus_HcalPIDe, &b_Dplus_Kminus_or_piminus_HcalPIDe);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_HcalPIDmu", &Dplus_Kminus_or_piminus_HcalPIDmu, &b_Dplus_Kminus_or_piminus_HcalPIDmu);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_InAccPrs", &Dplus_Kminus_or_piminus_InAccPrs, &b_Dplus_Kminus_or_piminus_InAccPrs);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_PrsPIDe", &Dplus_Kminus_or_piminus_PrsPIDe, &b_Dplus_Kminus_or_piminus_PrsPIDe);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_CaloPrsE", &Dplus_Kminus_or_piminus_CaloPrsE, &b_Dplus_Kminus_or_piminus_CaloPrsE);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_InAccSpd", &Dplus_Kminus_or_piminus_InAccSpd, &b_Dplus_Kminus_or_piminus_InAccSpd);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_CaloSpdE", &Dplus_Kminus_or_piminus_CaloSpdE, &b_Dplus_Kminus_or_piminus_CaloSpdE);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_InAccBrem", &Dplus_Kminus_or_piminus_InAccBrem, &b_Dplus_Kminus_or_piminus_InAccBrem);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_BremPIDe", &Dplus_Kminus_or_piminus_BremPIDe, &b_Dplus_Kminus_or_piminus_BremPIDe);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_VeloCharge", &Dplus_Kminus_or_piminus_VeloCharge, &b_Dplus_Kminus_or_piminus_VeloCharge);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_Type", &Dplus_Kminus_or_piminus_TRACK_Type, &b_Dplus_Kminus_or_piminus_TRACK_Type);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_Key", &Dplus_Kminus_or_piminus_TRACK_Key, &b_Dplus_Kminus_or_piminus_TRACK_Key);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_CHI2", &Dplus_Kminus_or_piminus_TRACK_CHI2, &b_Dplus_Kminus_or_piminus_TRACK_CHI2);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_NDOF", &Dplus_Kminus_or_piminus_TRACK_NDOF, &b_Dplus_Kminus_or_piminus_TRACK_NDOF);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_CHI2NDOF", &Dplus_Kminus_or_piminus_TRACK_CHI2NDOF, &b_Dplus_Kminus_or_piminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_PCHI2", &Dplus_Kminus_or_piminus_TRACK_PCHI2, &b_Dplus_Kminus_or_piminus_TRACK_PCHI2);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_VeloCHI2NDOF", &Dplus_Kminus_or_piminus_TRACK_VeloCHI2NDOF, &b_Dplus_Kminus_or_piminus_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_TCHI2NDOF", &Dplus_Kminus_or_piminus_TRACK_TCHI2NDOF, &b_Dplus_Kminus_or_piminus_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_VELO_UTID", &Dplus_Kminus_or_piminus_VELO_UTID, &b_Dplus_Kminus_or_piminus_VELO_UTID);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_FirstMeasurementX", &Dplus_Kminus_or_piminus_TRACK_FirstMeasurementX, &b_Dplus_Kminus_or_piminus_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_FirstMeasurementY", &Dplus_Kminus_or_piminus_TRACK_FirstMeasurementY, &b_Dplus_Kminus_or_piminus_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_FirstMeasurementZ", &Dplus_Kminus_or_piminus_TRACK_FirstMeasurementZ, &b_Dplus_Kminus_or_piminus_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_MatchCHI2", &Dplus_Kminus_or_piminus_TRACK_MatchCHI2, &b_Dplus_Kminus_or_piminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_GhostProb", &Dplus_Kminus_or_piminus_TRACK_GhostProb, &b_Dplus_Kminus_or_piminus_TRACK_GhostProb);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_CloneDist", &Dplus_Kminus_or_piminus_TRACK_CloneDist, &b_Dplus_Kminus_or_piminus_TRACK_CloneDist);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_TRACK_Likelihood", &Dplus_Kminus_or_piminus_TRACK_Likelihood, &b_Dplus_Kminus_or_piminus_TRACK_Likelihood);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_X", &Dplus_Kminus_or_piminus_X, &b_Dplus_Kminus_or_piminus_X);
   fChain->SetBranchAddress("Dplus_Kminus_or_piminus_Y", &Dplus_Kminus_or_piminus_Y, &b_Dplus_Kminus_or_piminus_Y);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_LOKI_ENERGY", &Dplus_piplus_or_Kplus_One_LOKI_ENERGY, &b_Dplus_piplus_or_Kplus_One_LOKI_ENERGY);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_LOKI_ETA", &Dplus_piplus_or_Kplus_One_LOKI_ETA, &b_Dplus_piplus_or_Kplus_One_LOKI_ETA);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_LOKI_PHI", &Dplus_piplus_or_Kplus_One_LOKI_PHI, &b_Dplus_piplus_or_Kplus_One_LOKI_PHI);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_X", &Dplus_piplus_or_Kplus_One_OWNPV_X, &b_Dplus_piplus_or_Kplus_One_OWNPV_X);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_Y", &Dplus_piplus_or_Kplus_One_OWNPV_Y, &b_Dplus_piplus_or_Kplus_One_OWNPV_Y);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_Z", &Dplus_piplus_or_Kplus_One_OWNPV_Z, &b_Dplus_piplus_or_Kplus_One_OWNPV_Z);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_XERR", &Dplus_piplus_or_Kplus_One_OWNPV_XERR, &b_Dplus_piplus_or_Kplus_One_OWNPV_XERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_YERR", &Dplus_piplus_or_Kplus_One_OWNPV_YERR, &b_Dplus_piplus_or_Kplus_One_OWNPV_YERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_ZERR", &Dplus_piplus_or_Kplus_One_OWNPV_ZERR, &b_Dplus_piplus_or_Kplus_One_OWNPV_ZERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_CHI2", &Dplus_piplus_or_Kplus_One_OWNPV_CHI2, &b_Dplus_piplus_or_Kplus_One_OWNPV_CHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_NDOF", &Dplus_piplus_or_Kplus_One_OWNPV_NDOF, &b_Dplus_piplus_or_Kplus_One_OWNPV_NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_OWNPV_COV_", Dplus_piplus_or_Kplus_One_OWNPV_COV_, &b_Dplus_piplus_or_Kplus_One_OWNPV_COV_);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_IP_OWNPV", &Dplus_piplus_or_Kplus_One_IP_OWNPV, &b_Dplus_piplus_or_Kplus_One_IP_OWNPV);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_IPCHI2_OWNPV", &Dplus_piplus_or_Kplus_One_IPCHI2_OWNPV, &b_Dplus_piplus_or_Kplus_One_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_X", &Dplus_piplus_or_Kplus_One_ORIVX_X, &b_Dplus_piplus_or_Kplus_One_ORIVX_X);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_Y", &Dplus_piplus_or_Kplus_One_ORIVX_Y, &b_Dplus_piplus_or_Kplus_One_ORIVX_Y);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_Z", &Dplus_piplus_or_Kplus_One_ORIVX_Z, &b_Dplus_piplus_or_Kplus_One_ORIVX_Z);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_XERR", &Dplus_piplus_or_Kplus_One_ORIVX_XERR, &b_Dplus_piplus_or_Kplus_One_ORIVX_XERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_YERR", &Dplus_piplus_or_Kplus_One_ORIVX_YERR, &b_Dplus_piplus_or_Kplus_One_ORIVX_YERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_ZERR", &Dplus_piplus_or_Kplus_One_ORIVX_ZERR, &b_Dplus_piplus_or_Kplus_One_ORIVX_ZERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_CHI2", &Dplus_piplus_or_Kplus_One_ORIVX_CHI2, &b_Dplus_piplus_or_Kplus_One_ORIVX_CHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_NDOF", &Dplus_piplus_or_Kplus_One_ORIVX_NDOF, &b_Dplus_piplus_or_Kplus_One_ORIVX_NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ORIVX_COV_", Dplus_piplus_or_Kplus_One_ORIVX_COV_, &b_Dplus_piplus_or_Kplus_One_ORIVX_COV_);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_P", &Dplus_piplus_or_Kplus_One_P, &b_Dplus_piplus_or_Kplus_One_P);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PT", &Dplus_piplus_or_Kplus_One_PT, &b_Dplus_piplus_or_Kplus_One_PT);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PE", &Dplus_piplus_or_Kplus_One_PE, &b_Dplus_piplus_or_Kplus_One_PE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PX", &Dplus_piplus_or_Kplus_One_PX, &b_Dplus_piplus_or_Kplus_One_PX);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PY", &Dplus_piplus_or_Kplus_One_PY, &b_Dplus_piplus_or_Kplus_One_PY);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PZ", &Dplus_piplus_or_Kplus_One_PZ, &b_Dplus_piplus_or_Kplus_One_PZ);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_M", &Dplus_piplus_or_Kplus_One_M, &b_Dplus_piplus_or_Kplus_One_M);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ID", &Dplus_piplus_or_Kplus_One_ID, &b_Dplus_piplus_or_Kplus_One_ID);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PIDe", &Dplus_piplus_or_Kplus_One_PIDe, &b_Dplus_piplus_or_Kplus_One_PIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PIDmu", &Dplus_piplus_or_Kplus_One_PIDmu, &b_Dplus_piplus_or_Kplus_One_PIDmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PIDK", &Dplus_piplus_or_Kplus_One_PIDK, &b_Dplus_piplus_or_Kplus_One_PIDK);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PIDp", &Dplus_piplus_or_Kplus_One_PIDp, &b_Dplus_piplus_or_Kplus_One_PIDp);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ProbNNe", &Dplus_piplus_or_Kplus_One_ProbNNe, &b_Dplus_piplus_or_Kplus_One_ProbNNe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ProbNNk", &Dplus_piplus_or_Kplus_One_ProbNNk, &b_Dplus_piplus_or_Kplus_One_ProbNNk);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ProbNNp", &Dplus_piplus_or_Kplus_One_ProbNNp, &b_Dplus_piplus_or_Kplus_One_ProbNNp);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ProbNNpi", &Dplus_piplus_or_Kplus_One_ProbNNpi, &b_Dplus_piplus_or_Kplus_One_ProbNNpi);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ProbNNmu", &Dplus_piplus_or_Kplus_One_ProbNNmu, &b_Dplus_piplus_or_Kplus_One_ProbNNmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_ProbNNghost", &Dplus_piplus_or_Kplus_One_ProbNNghost, &b_Dplus_piplus_or_Kplus_One_ProbNNghost);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_hasMuon", &Dplus_piplus_or_Kplus_One_hasMuon, &b_Dplus_piplus_or_Kplus_One_hasMuon);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_isMuon", &Dplus_piplus_or_Kplus_One_isMuon, &b_Dplus_piplus_or_Kplus_One_isMuon);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_hasRich", &Dplus_piplus_or_Kplus_One_hasRich, &b_Dplus_piplus_or_Kplus_One_hasRich);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_hasCalo", &Dplus_piplus_or_Kplus_One_hasCalo, &b_Dplus_piplus_or_Kplus_One_hasCalo);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_UsedRichAerogel", &Dplus_piplus_or_Kplus_One_UsedRichAerogel, &b_Dplus_piplus_or_Kplus_One_UsedRichAerogel);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_UsedRich1Gas", &Dplus_piplus_or_Kplus_One_UsedRich1Gas, &b_Dplus_piplus_or_Kplus_One_UsedRich1Gas);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_UsedRich2Gas", &Dplus_piplus_or_Kplus_One_UsedRich2Gas, &b_Dplus_piplus_or_Kplus_One_UsedRich2Gas);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichAboveElThres", &Dplus_piplus_or_Kplus_One_RichAboveElThres, &b_Dplus_piplus_or_Kplus_One_RichAboveElThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichAboveMuThres", &Dplus_piplus_or_Kplus_One_RichAboveMuThres, &b_Dplus_piplus_or_Kplus_One_RichAboveMuThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichAbovePiThres", &Dplus_piplus_or_Kplus_One_RichAbovePiThres, &b_Dplus_piplus_or_Kplus_One_RichAbovePiThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichAboveKaThres", &Dplus_piplus_or_Kplus_One_RichAboveKaThres, &b_Dplus_piplus_or_Kplus_One_RichAboveKaThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichAbovePrThres", &Dplus_piplus_or_Kplus_One_RichAbovePrThres, &b_Dplus_piplus_or_Kplus_One_RichAbovePrThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichDLLe", &Dplus_piplus_or_Kplus_One_RichDLLe, &b_Dplus_piplus_or_Kplus_One_RichDLLe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichDLLmu", &Dplus_piplus_or_Kplus_One_RichDLLmu, &b_Dplus_piplus_or_Kplus_One_RichDLLmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichDLLpi", &Dplus_piplus_or_Kplus_One_RichDLLpi, &b_Dplus_piplus_or_Kplus_One_RichDLLpi);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichDLLk", &Dplus_piplus_or_Kplus_One_RichDLLk, &b_Dplus_piplus_or_Kplus_One_RichDLLk);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichDLLp", &Dplus_piplus_or_Kplus_One_RichDLLp, &b_Dplus_piplus_or_Kplus_One_RichDLLp);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_RichDLLbt", &Dplus_piplus_or_Kplus_One_RichDLLbt, &b_Dplus_piplus_or_Kplus_One_RichDLLbt);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_InAccMuon", &Dplus_piplus_or_Kplus_One_InAccMuon, &b_Dplus_piplus_or_Kplus_One_InAccMuon);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_isMuonLoose", &Dplus_piplus_or_Kplus_One_isMuonLoose, &b_Dplus_piplus_or_Kplus_One_isMuonLoose);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_MuonMuLL", &Dplus_piplus_or_Kplus_One_MuonMuLL, &b_Dplus_piplus_or_Kplus_One_MuonMuLL);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_MuonBkgLL", &Dplus_piplus_or_Kplus_One_MuonBkgLL, &b_Dplus_piplus_or_Kplus_One_MuonBkgLL);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_MuonNShared", &Dplus_piplus_or_Kplus_One_MuonNShared, &b_Dplus_piplus_or_Kplus_One_MuonNShared);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_InAccEcal", &Dplus_piplus_or_Kplus_One_InAccEcal, &b_Dplus_piplus_or_Kplus_One_InAccEcal);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_CaloEcalE", &Dplus_piplus_or_Kplus_One_CaloEcalE, &b_Dplus_piplus_or_Kplus_One_CaloEcalE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_EcalPIDe", &Dplus_piplus_or_Kplus_One_EcalPIDe, &b_Dplus_piplus_or_Kplus_One_EcalPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_EcalPIDmu", &Dplus_piplus_or_Kplus_One_EcalPIDmu, &b_Dplus_piplus_or_Kplus_One_EcalPIDmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_InAccHcal", &Dplus_piplus_or_Kplus_One_InAccHcal, &b_Dplus_piplus_or_Kplus_One_InAccHcal);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_CaloHcalE", &Dplus_piplus_or_Kplus_One_CaloHcalE, &b_Dplus_piplus_or_Kplus_One_CaloHcalE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_HcalPIDe", &Dplus_piplus_or_Kplus_One_HcalPIDe, &b_Dplus_piplus_or_Kplus_One_HcalPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_HcalPIDmu", &Dplus_piplus_or_Kplus_One_HcalPIDmu, &b_Dplus_piplus_or_Kplus_One_HcalPIDmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_InAccPrs", &Dplus_piplus_or_Kplus_One_InAccPrs, &b_Dplus_piplus_or_Kplus_One_InAccPrs);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_PrsPIDe", &Dplus_piplus_or_Kplus_One_PrsPIDe, &b_Dplus_piplus_or_Kplus_One_PrsPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_CaloPrsE", &Dplus_piplus_or_Kplus_One_CaloPrsE, &b_Dplus_piplus_or_Kplus_One_CaloPrsE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_InAccSpd", &Dplus_piplus_or_Kplus_One_InAccSpd, &b_Dplus_piplus_or_Kplus_One_InAccSpd);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_CaloSpdE", &Dplus_piplus_or_Kplus_One_CaloSpdE, &b_Dplus_piplus_or_Kplus_One_CaloSpdE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_InAccBrem", &Dplus_piplus_or_Kplus_One_InAccBrem, &b_Dplus_piplus_or_Kplus_One_InAccBrem);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_BremPIDe", &Dplus_piplus_or_Kplus_One_BremPIDe, &b_Dplus_piplus_or_Kplus_One_BremPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_VeloCharge", &Dplus_piplus_or_Kplus_One_VeloCharge, &b_Dplus_piplus_or_Kplus_One_VeloCharge);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_Type", &Dplus_piplus_or_Kplus_One_TRACK_Type, &b_Dplus_piplus_or_Kplus_One_TRACK_Type);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_Key", &Dplus_piplus_or_Kplus_One_TRACK_Key, &b_Dplus_piplus_or_Kplus_One_TRACK_Key);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_CHI2", &Dplus_piplus_or_Kplus_One_TRACK_CHI2, &b_Dplus_piplus_or_Kplus_One_TRACK_CHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_NDOF", &Dplus_piplus_or_Kplus_One_TRACK_NDOF, &b_Dplus_piplus_or_Kplus_One_TRACK_NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_CHI2NDOF", &Dplus_piplus_or_Kplus_One_TRACK_CHI2NDOF, &b_Dplus_piplus_or_Kplus_One_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_PCHI2", &Dplus_piplus_or_Kplus_One_TRACK_PCHI2, &b_Dplus_piplus_or_Kplus_One_TRACK_PCHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_VeloCHI2NDOF", &Dplus_piplus_or_Kplus_One_TRACK_VeloCHI2NDOF, &b_Dplus_piplus_or_Kplus_One_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_TCHI2NDOF", &Dplus_piplus_or_Kplus_One_TRACK_TCHI2NDOF, &b_Dplus_piplus_or_Kplus_One_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_VELO_UTID", &Dplus_piplus_or_Kplus_One_VELO_UTID, &b_Dplus_piplus_or_Kplus_One_VELO_UTID);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementX", &Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementX, &b_Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementY", &Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementY, &b_Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementZ", &Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementZ, &b_Dplus_piplus_or_Kplus_One_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_MatchCHI2", &Dplus_piplus_or_Kplus_One_TRACK_MatchCHI2, &b_Dplus_piplus_or_Kplus_One_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_GhostProb", &Dplus_piplus_or_Kplus_One_TRACK_GhostProb, &b_Dplus_piplus_or_Kplus_One_TRACK_GhostProb);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_CloneDist", &Dplus_piplus_or_Kplus_One_TRACK_CloneDist, &b_Dplus_piplus_or_Kplus_One_TRACK_CloneDist);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_TRACK_Likelihood", &Dplus_piplus_or_Kplus_One_TRACK_Likelihood, &b_Dplus_piplus_or_Kplus_One_TRACK_Likelihood);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_X", &Dplus_piplus_or_Kplus_One_X, &b_Dplus_piplus_or_Kplus_One_X);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_One_Y", &Dplus_piplus_or_Kplus_One_Y, &b_Dplus_piplus_or_Kplus_One_Y);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_LOKI_ENERGY", &Dplus_piplus_or_Kplus_Two_LOKI_ENERGY, &b_Dplus_piplus_or_Kplus_Two_LOKI_ENERGY);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_LOKI_ETA", &Dplus_piplus_or_Kplus_Two_LOKI_ETA, &b_Dplus_piplus_or_Kplus_Two_LOKI_ETA);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_LOKI_PHI", &Dplus_piplus_or_Kplus_Two_LOKI_PHI, &b_Dplus_piplus_or_Kplus_Two_LOKI_PHI);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_X", &Dplus_piplus_or_Kplus_Two_OWNPV_X, &b_Dplus_piplus_or_Kplus_Two_OWNPV_X);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_Y", &Dplus_piplus_or_Kplus_Two_OWNPV_Y, &b_Dplus_piplus_or_Kplus_Two_OWNPV_Y);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_Z", &Dplus_piplus_or_Kplus_Two_OWNPV_Z, &b_Dplus_piplus_or_Kplus_Two_OWNPV_Z);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_XERR", &Dplus_piplus_or_Kplus_Two_OWNPV_XERR, &b_Dplus_piplus_or_Kplus_Two_OWNPV_XERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_YERR", &Dplus_piplus_or_Kplus_Two_OWNPV_YERR, &b_Dplus_piplus_or_Kplus_Two_OWNPV_YERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_ZERR", &Dplus_piplus_or_Kplus_Two_OWNPV_ZERR, &b_Dplus_piplus_or_Kplus_Two_OWNPV_ZERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_CHI2", &Dplus_piplus_or_Kplus_Two_OWNPV_CHI2, &b_Dplus_piplus_or_Kplus_Two_OWNPV_CHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_NDOF", &Dplus_piplus_or_Kplus_Two_OWNPV_NDOF, &b_Dplus_piplus_or_Kplus_Two_OWNPV_NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_OWNPV_COV_", Dplus_piplus_or_Kplus_Two_OWNPV_COV_, &b_Dplus_piplus_or_Kplus_Two_OWNPV_COV_);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_IP_OWNPV", &Dplus_piplus_or_Kplus_Two_IP_OWNPV, &b_Dplus_piplus_or_Kplus_Two_IP_OWNPV);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_IPCHI2_OWNPV", &Dplus_piplus_or_Kplus_Two_IPCHI2_OWNPV, &b_Dplus_piplus_or_Kplus_Two_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_X", &Dplus_piplus_or_Kplus_Two_ORIVX_X, &b_Dplus_piplus_or_Kplus_Two_ORIVX_X);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_Y", &Dplus_piplus_or_Kplus_Two_ORIVX_Y, &b_Dplus_piplus_or_Kplus_Two_ORIVX_Y);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_Z", &Dplus_piplus_or_Kplus_Two_ORIVX_Z, &b_Dplus_piplus_or_Kplus_Two_ORIVX_Z);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_XERR", &Dplus_piplus_or_Kplus_Two_ORIVX_XERR, &b_Dplus_piplus_or_Kplus_Two_ORIVX_XERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_YERR", &Dplus_piplus_or_Kplus_Two_ORIVX_YERR, &b_Dplus_piplus_or_Kplus_Two_ORIVX_YERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_ZERR", &Dplus_piplus_or_Kplus_Two_ORIVX_ZERR, &b_Dplus_piplus_or_Kplus_Two_ORIVX_ZERR);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_CHI2", &Dplus_piplus_or_Kplus_Two_ORIVX_CHI2, &b_Dplus_piplus_or_Kplus_Two_ORIVX_CHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_NDOF", &Dplus_piplus_or_Kplus_Two_ORIVX_NDOF, &b_Dplus_piplus_or_Kplus_Two_ORIVX_NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ORIVX_COV_", Dplus_piplus_or_Kplus_Two_ORIVX_COV_, &b_Dplus_piplus_or_Kplus_Two_ORIVX_COV_);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_P", &Dplus_piplus_or_Kplus_Two_P, &b_Dplus_piplus_or_Kplus_Two_P);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PT", &Dplus_piplus_or_Kplus_Two_PT, &b_Dplus_piplus_or_Kplus_Two_PT);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PE", &Dplus_piplus_or_Kplus_Two_PE, &b_Dplus_piplus_or_Kplus_Two_PE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PX", &Dplus_piplus_or_Kplus_Two_PX, &b_Dplus_piplus_or_Kplus_Two_PX);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PY", &Dplus_piplus_or_Kplus_Two_PY, &b_Dplus_piplus_or_Kplus_Two_PY);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PZ", &Dplus_piplus_or_Kplus_Two_PZ, &b_Dplus_piplus_or_Kplus_Two_PZ);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_M", &Dplus_piplus_or_Kplus_Two_M, &b_Dplus_piplus_or_Kplus_Two_M);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ID", &Dplus_piplus_or_Kplus_Two_ID, &b_Dplus_piplus_or_Kplus_Two_ID);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PIDe", &Dplus_piplus_or_Kplus_Two_PIDe, &b_Dplus_piplus_or_Kplus_Two_PIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PIDmu", &Dplus_piplus_or_Kplus_Two_PIDmu, &b_Dplus_piplus_or_Kplus_Two_PIDmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PIDK", &Dplus_piplus_or_Kplus_Two_PIDK, &b_Dplus_piplus_or_Kplus_Two_PIDK);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PIDp", &Dplus_piplus_or_Kplus_Two_PIDp, &b_Dplus_piplus_or_Kplus_Two_PIDp);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ProbNNe", &Dplus_piplus_or_Kplus_Two_ProbNNe, &b_Dplus_piplus_or_Kplus_Two_ProbNNe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ProbNNk", &Dplus_piplus_or_Kplus_Two_ProbNNk, &b_Dplus_piplus_or_Kplus_Two_ProbNNk);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ProbNNp", &Dplus_piplus_or_Kplus_Two_ProbNNp, &b_Dplus_piplus_or_Kplus_Two_ProbNNp);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ProbNNpi", &Dplus_piplus_or_Kplus_Two_ProbNNpi, &b_Dplus_piplus_or_Kplus_Two_ProbNNpi);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ProbNNmu", &Dplus_piplus_or_Kplus_Two_ProbNNmu, &b_Dplus_piplus_or_Kplus_Two_ProbNNmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_ProbNNghost", &Dplus_piplus_or_Kplus_Two_ProbNNghost, &b_Dplus_piplus_or_Kplus_Two_ProbNNghost);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_hasMuon", &Dplus_piplus_or_Kplus_Two_hasMuon, &b_Dplus_piplus_or_Kplus_Two_hasMuon);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_isMuon", &Dplus_piplus_or_Kplus_Two_isMuon, &b_Dplus_piplus_or_Kplus_Two_isMuon);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_hasRich", &Dplus_piplus_or_Kplus_Two_hasRich, &b_Dplus_piplus_or_Kplus_Two_hasRich);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_hasCalo", &Dplus_piplus_or_Kplus_Two_hasCalo, &b_Dplus_piplus_or_Kplus_Two_hasCalo);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_UsedRichAerogel", &Dplus_piplus_or_Kplus_Two_UsedRichAerogel, &b_Dplus_piplus_or_Kplus_Two_UsedRichAerogel);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_UsedRich1Gas", &Dplus_piplus_or_Kplus_Two_UsedRich1Gas, &b_Dplus_piplus_or_Kplus_Two_UsedRich1Gas);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_UsedRich2Gas", &Dplus_piplus_or_Kplus_Two_UsedRich2Gas, &b_Dplus_piplus_or_Kplus_Two_UsedRich2Gas);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichAboveElThres", &Dplus_piplus_or_Kplus_Two_RichAboveElThres, &b_Dplus_piplus_or_Kplus_Two_RichAboveElThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichAboveMuThres", &Dplus_piplus_or_Kplus_Two_RichAboveMuThres, &b_Dplus_piplus_or_Kplus_Two_RichAboveMuThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichAbovePiThres", &Dplus_piplus_or_Kplus_Two_RichAbovePiThres, &b_Dplus_piplus_or_Kplus_Two_RichAbovePiThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichAboveKaThres", &Dplus_piplus_or_Kplus_Two_RichAboveKaThres, &b_Dplus_piplus_or_Kplus_Two_RichAboveKaThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichAbovePrThres", &Dplus_piplus_or_Kplus_Two_RichAbovePrThres, &b_Dplus_piplus_or_Kplus_Two_RichAbovePrThres);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichDLLe", &Dplus_piplus_or_Kplus_Two_RichDLLe, &b_Dplus_piplus_or_Kplus_Two_RichDLLe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichDLLmu", &Dplus_piplus_or_Kplus_Two_RichDLLmu, &b_Dplus_piplus_or_Kplus_Two_RichDLLmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichDLLpi", &Dplus_piplus_or_Kplus_Two_RichDLLpi, &b_Dplus_piplus_or_Kplus_Two_RichDLLpi);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichDLLk", &Dplus_piplus_or_Kplus_Two_RichDLLk, &b_Dplus_piplus_or_Kplus_Two_RichDLLk);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichDLLp", &Dplus_piplus_or_Kplus_Two_RichDLLp, &b_Dplus_piplus_or_Kplus_Two_RichDLLp);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_RichDLLbt", &Dplus_piplus_or_Kplus_Two_RichDLLbt, &b_Dplus_piplus_or_Kplus_Two_RichDLLbt);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_InAccMuon", &Dplus_piplus_or_Kplus_Two_InAccMuon, &b_Dplus_piplus_or_Kplus_Two_InAccMuon);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_isMuonLoose", &Dplus_piplus_or_Kplus_Two_isMuonLoose, &b_Dplus_piplus_or_Kplus_Two_isMuonLoose);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_MuonMuLL", &Dplus_piplus_or_Kplus_Two_MuonMuLL, &b_Dplus_piplus_or_Kplus_Two_MuonMuLL);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_MuonBkgLL", &Dplus_piplus_or_Kplus_Two_MuonBkgLL, &b_Dplus_piplus_or_Kplus_Two_MuonBkgLL);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_MuonNShared", &Dplus_piplus_or_Kplus_Two_MuonNShared, &b_Dplus_piplus_or_Kplus_Two_MuonNShared);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_InAccEcal", &Dplus_piplus_or_Kplus_Two_InAccEcal, &b_Dplus_piplus_or_Kplus_Two_InAccEcal);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_CaloEcalE", &Dplus_piplus_or_Kplus_Two_CaloEcalE, &b_Dplus_piplus_or_Kplus_Two_CaloEcalE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_EcalPIDe", &Dplus_piplus_or_Kplus_Two_EcalPIDe, &b_Dplus_piplus_or_Kplus_Two_EcalPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_EcalPIDmu", &Dplus_piplus_or_Kplus_Two_EcalPIDmu, &b_Dplus_piplus_or_Kplus_Two_EcalPIDmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_InAccHcal", &Dplus_piplus_or_Kplus_Two_InAccHcal, &b_Dplus_piplus_or_Kplus_Two_InAccHcal);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_CaloHcalE", &Dplus_piplus_or_Kplus_Two_CaloHcalE, &b_Dplus_piplus_or_Kplus_Two_CaloHcalE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_HcalPIDe", &Dplus_piplus_or_Kplus_Two_HcalPIDe, &b_Dplus_piplus_or_Kplus_Two_HcalPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_HcalPIDmu", &Dplus_piplus_or_Kplus_Two_HcalPIDmu, &b_Dplus_piplus_or_Kplus_Two_HcalPIDmu);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_InAccPrs", &Dplus_piplus_or_Kplus_Two_InAccPrs, &b_Dplus_piplus_or_Kplus_Two_InAccPrs);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_PrsPIDe", &Dplus_piplus_or_Kplus_Two_PrsPIDe, &b_Dplus_piplus_or_Kplus_Two_PrsPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_CaloPrsE", &Dplus_piplus_or_Kplus_Two_CaloPrsE, &b_Dplus_piplus_or_Kplus_Two_CaloPrsE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_InAccSpd", &Dplus_piplus_or_Kplus_Two_InAccSpd, &b_Dplus_piplus_or_Kplus_Two_InAccSpd);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_CaloSpdE", &Dplus_piplus_or_Kplus_Two_CaloSpdE, &b_Dplus_piplus_or_Kplus_Two_CaloSpdE);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_InAccBrem", &Dplus_piplus_or_Kplus_Two_InAccBrem, &b_Dplus_piplus_or_Kplus_Two_InAccBrem);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_BremPIDe", &Dplus_piplus_or_Kplus_Two_BremPIDe, &b_Dplus_piplus_or_Kplus_Two_BremPIDe);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_VeloCharge", &Dplus_piplus_or_Kplus_Two_VeloCharge, &b_Dplus_piplus_or_Kplus_Two_VeloCharge);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_Type", &Dplus_piplus_or_Kplus_Two_TRACK_Type, &b_Dplus_piplus_or_Kplus_Two_TRACK_Type);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_Key", &Dplus_piplus_or_Kplus_Two_TRACK_Key, &b_Dplus_piplus_or_Kplus_Two_TRACK_Key);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_CHI2", &Dplus_piplus_or_Kplus_Two_TRACK_CHI2, &b_Dplus_piplus_or_Kplus_Two_TRACK_CHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_NDOF", &Dplus_piplus_or_Kplus_Two_TRACK_NDOF, &b_Dplus_piplus_or_Kplus_Two_TRACK_NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_CHI2NDOF", &Dplus_piplus_or_Kplus_Two_TRACK_CHI2NDOF, &b_Dplus_piplus_or_Kplus_Two_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_PCHI2", &Dplus_piplus_or_Kplus_Two_TRACK_PCHI2, &b_Dplus_piplus_or_Kplus_Two_TRACK_PCHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_VeloCHI2NDOF", &Dplus_piplus_or_Kplus_Two_TRACK_VeloCHI2NDOF, &b_Dplus_piplus_or_Kplus_Two_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_TCHI2NDOF", &Dplus_piplus_or_Kplus_Two_TRACK_TCHI2NDOF, &b_Dplus_piplus_or_Kplus_Two_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_VELO_UTID", &Dplus_piplus_or_Kplus_Two_VELO_UTID, &b_Dplus_piplus_or_Kplus_Two_VELO_UTID);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementX", &Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementX, &b_Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementY", &Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementY, &b_Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementZ", &Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementZ, &b_Dplus_piplus_or_Kplus_Two_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_MatchCHI2", &Dplus_piplus_or_Kplus_Two_TRACK_MatchCHI2, &b_Dplus_piplus_or_Kplus_Two_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_GhostProb", &Dplus_piplus_or_Kplus_Two_TRACK_GhostProb, &b_Dplus_piplus_or_Kplus_Two_TRACK_GhostProb);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_CloneDist", &Dplus_piplus_or_Kplus_Two_TRACK_CloneDist, &b_Dplus_piplus_or_Kplus_Two_TRACK_CloneDist);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_TRACK_Likelihood", &Dplus_piplus_or_Kplus_Two_TRACK_Likelihood, &b_Dplus_piplus_or_Kplus_Two_TRACK_Likelihood);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_X", &Dplus_piplus_or_Kplus_Two_X, &b_Dplus_piplus_or_Kplus_Two_X);
   fChain->SetBranchAddress("Dplus_piplus_or_Kplus_Two_Y", &Dplus_piplus_or_Kplus_Two_Y, &b_Dplus_piplus_or_Kplus_Two_Y);
   fChain->SetBranchAddress("Dminus_LOKI_ENERGY", &Dminus_LOKI_ENERGY, &b_Dminus_LOKI_ENERGY);
   fChain->SetBranchAddress("Dminus_LOKI_ETA", &Dminus_LOKI_ETA, &b_Dminus_LOKI_ETA);
   fChain->SetBranchAddress("Dminus_LOKI_PHI", &Dminus_LOKI_PHI, &b_Dminus_LOKI_PHI);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_X", &Dminus_ENDVERTEX_X, &b_Dminus_ENDVERTEX_X);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_Y", &Dminus_ENDVERTEX_Y, &b_Dminus_ENDVERTEX_Y);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_Z", &Dminus_ENDVERTEX_Z, &b_Dminus_ENDVERTEX_Z);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_XERR", &Dminus_ENDVERTEX_XERR, &b_Dminus_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_YERR", &Dminus_ENDVERTEX_YERR, &b_Dminus_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_ZERR", &Dminus_ENDVERTEX_ZERR, &b_Dminus_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_CHI2", &Dminus_ENDVERTEX_CHI2, &b_Dminus_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_NDOF", &Dminus_ENDVERTEX_NDOF, &b_Dminus_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Dminus_ENDVERTEX_COV_", Dminus_ENDVERTEX_COV_, &b_Dminus_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Dminus_OWNPV_X", &Dminus_OWNPV_X, &b_Dminus_OWNPV_X);
   fChain->SetBranchAddress("Dminus_OWNPV_Y", &Dminus_OWNPV_Y, &b_Dminus_OWNPV_Y);
   fChain->SetBranchAddress("Dminus_OWNPV_Z", &Dminus_OWNPV_Z, &b_Dminus_OWNPV_Z);
   fChain->SetBranchAddress("Dminus_OWNPV_XERR", &Dminus_OWNPV_XERR, &b_Dminus_OWNPV_XERR);
   fChain->SetBranchAddress("Dminus_OWNPV_YERR", &Dminus_OWNPV_YERR, &b_Dminus_OWNPV_YERR);
   fChain->SetBranchAddress("Dminus_OWNPV_ZERR", &Dminus_OWNPV_ZERR, &b_Dminus_OWNPV_ZERR);
   fChain->SetBranchAddress("Dminus_OWNPV_CHI2", &Dminus_OWNPV_CHI2, &b_Dminus_OWNPV_CHI2);
   fChain->SetBranchAddress("Dminus_OWNPV_NDOF", &Dminus_OWNPV_NDOF, &b_Dminus_OWNPV_NDOF);
   fChain->SetBranchAddress("Dminus_OWNPV_COV_", Dminus_OWNPV_COV_, &b_Dminus_OWNPV_COV_);
   fChain->SetBranchAddress("Dminus_IP_OWNPV", &Dminus_IP_OWNPV, &b_Dminus_IP_OWNPV);
   fChain->SetBranchAddress("Dminus_IPCHI2_OWNPV", &Dminus_IPCHI2_OWNPV, &b_Dminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dminus_FD_OWNPV", &Dminus_FD_OWNPV, &b_Dminus_FD_OWNPV);
   fChain->SetBranchAddress("Dminus_FDCHI2_OWNPV", &Dminus_FDCHI2_OWNPV, &b_Dminus_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Dminus_DIRA_OWNPV", &Dminus_DIRA_OWNPV, &b_Dminus_DIRA_OWNPV);
   fChain->SetBranchAddress("Dminus_ORIVX_X", &Dminus_ORIVX_X, &b_Dminus_ORIVX_X);
   fChain->SetBranchAddress("Dminus_ORIVX_Y", &Dminus_ORIVX_Y, &b_Dminus_ORIVX_Y);
   fChain->SetBranchAddress("Dminus_ORIVX_Z", &Dminus_ORIVX_Z, &b_Dminus_ORIVX_Z);
   fChain->SetBranchAddress("Dminus_ORIVX_XERR", &Dminus_ORIVX_XERR, &b_Dminus_ORIVX_XERR);
   fChain->SetBranchAddress("Dminus_ORIVX_YERR", &Dminus_ORIVX_YERR, &b_Dminus_ORIVX_YERR);
   fChain->SetBranchAddress("Dminus_ORIVX_ZERR", &Dminus_ORIVX_ZERR, &b_Dminus_ORIVX_ZERR);
   fChain->SetBranchAddress("Dminus_ORIVX_CHI2", &Dminus_ORIVX_CHI2, &b_Dminus_ORIVX_CHI2);
   fChain->SetBranchAddress("Dminus_ORIVX_NDOF", &Dminus_ORIVX_NDOF, &b_Dminus_ORIVX_NDOF);
   fChain->SetBranchAddress("Dminus_ORIVX_COV_", Dminus_ORIVX_COV_, &b_Dminus_ORIVX_COV_);
   fChain->SetBranchAddress("Dminus_FD_ORIVX", &Dminus_FD_ORIVX, &b_Dminus_FD_ORIVX);
   fChain->SetBranchAddress("Dminus_FDCHI2_ORIVX", &Dminus_FDCHI2_ORIVX, &b_Dminus_FDCHI2_ORIVX);
   fChain->SetBranchAddress("Dminus_DIRA_ORIVX", &Dminus_DIRA_ORIVX, &b_Dminus_DIRA_ORIVX);
   fChain->SetBranchAddress("Dminus_P", &Dminus_P, &b_Dminus_P);
   fChain->SetBranchAddress("Dminus_PT", &Dminus_PT, &b_Dminus_PT);
   fChain->SetBranchAddress("Dminus_PE", &Dminus_PE, &b_Dminus_PE);
   fChain->SetBranchAddress("Dminus_PX", &Dminus_PX, &b_Dminus_PX);
   fChain->SetBranchAddress("Dminus_PY", &Dminus_PY, &b_Dminus_PY);
   fChain->SetBranchAddress("Dminus_PZ", &Dminus_PZ, &b_Dminus_PZ);
   fChain->SetBranchAddress("Dminus_MM", &Dminus_MM, &b_Dminus_MM);
   fChain->SetBranchAddress("Dminus_MMERR", &Dminus_MMERR, &b_Dminus_MMERR);
   fChain->SetBranchAddress("Dminus_M", &Dminus_M, &b_Dminus_M);
   fChain->SetBranchAddress("Dminus_ID", &Dminus_ID, &b_Dminus_ID);
   fChain->SetBranchAddress("Dminus_TAU", &Dminus_TAU, &b_Dminus_TAU);
   fChain->SetBranchAddress("Dminus_TAUERR", &Dminus_TAUERR, &b_Dminus_TAUERR);
   fChain->SetBranchAddress("Dminus_TAUCHI2", &Dminus_TAUCHI2, &b_Dminus_TAUCHI2);
   fChain->SetBranchAddress("Dminus_X", &Dminus_X, &b_Dminus_X);
   fChain->SetBranchAddress("Dminus_Y", &Dminus_Y, &b_Dminus_Y);
   fChain->SetBranchAddress("Dminus_LOKI_VertexSeparation_CHI2", &Dminus_LOKI_VertexSeparation_CHI2, &b_Dminus_LOKI_VertexSeparation_CHI2);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_LOKI_ENERGY", &Dminus_Kplus_or_piplus_LOKI_ENERGY, &b_Dminus_Kplus_or_piplus_LOKI_ENERGY);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_LOKI_ETA", &Dminus_Kplus_or_piplus_LOKI_ETA, &b_Dminus_Kplus_or_piplus_LOKI_ETA);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_LOKI_PHI", &Dminus_Kplus_or_piplus_LOKI_PHI, &b_Dminus_Kplus_or_piplus_LOKI_PHI);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_X", &Dminus_Kplus_or_piplus_OWNPV_X, &b_Dminus_Kplus_or_piplus_OWNPV_X);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_Y", &Dminus_Kplus_or_piplus_OWNPV_Y, &b_Dminus_Kplus_or_piplus_OWNPV_Y);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_Z", &Dminus_Kplus_or_piplus_OWNPV_Z, &b_Dminus_Kplus_or_piplus_OWNPV_Z);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_XERR", &Dminus_Kplus_or_piplus_OWNPV_XERR, &b_Dminus_Kplus_or_piplus_OWNPV_XERR);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_YERR", &Dminus_Kplus_or_piplus_OWNPV_YERR, &b_Dminus_Kplus_or_piplus_OWNPV_YERR);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_ZERR", &Dminus_Kplus_or_piplus_OWNPV_ZERR, &b_Dminus_Kplus_or_piplus_OWNPV_ZERR);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_CHI2", &Dminus_Kplus_or_piplus_OWNPV_CHI2, &b_Dminus_Kplus_or_piplus_OWNPV_CHI2);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_NDOF", &Dminus_Kplus_or_piplus_OWNPV_NDOF, &b_Dminus_Kplus_or_piplus_OWNPV_NDOF);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_OWNPV_COV_", Dminus_Kplus_or_piplus_OWNPV_COV_, &b_Dminus_Kplus_or_piplus_OWNPV_COV_);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_IP_OWNPV", &Dminus_Kplus_or_piplus_IP_OWNPV, &b_Dminus_Kplus_or_piplus_IP_OWNPV);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_IPCHI2_OWNPV", &Dminus_Kplus_or_piplus_IPCHI2_OWNPV, &b_Dminus_Kplus_or_piplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_X", &Dminus_Kplus_or_piplus_ORIVX_X, &b_Dminus_Kplus_or_piplus_ORIVX_X);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_Y", &Dminus_Kplus_or_piplus_ORIVX_Y, &b_Dminus_Kplus_or_piplus_ORIVX_Y);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_Z", &Dminus_Kplus_or_piplus_ORIVX_Z, &b_Dminus_Kplus_or_piplus_ORIVX_Z);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_XERR", &Dminus_Kplus_or_piplus_ORIVX_XERR, &b_Dminus_Kplus_or_piplus_ORIVX_XERR);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_YERR", &Dminus_Kplus_or_piplus_ORIVX_YERR, &b_Dminus_Kplus_or_piplus_ORIVX_YERR);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_ZERR", &Dminus_Kplus_or_piplus_ORIVX_ZERR, &b_Dminus_Kplus_or_piplus_ORIVX_ZERR);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_CHI2", &Dminus_Kplus_or_piplus_ORIVX_CHI2, &b_Dminus_Kplus_or_piplus_ORIVX_CHI2);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_NDOF", &Dminus_Kplus_or_piplus_ORIVX_NDOF, &b_Dminus_Kplus_or_piplus_ORIVX_NDOF);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ORIVX_COV_", Dminus_Kplus_or_piplus_ORIVX_COV_, &b_Dminus_Kplus_or_piplus_ORIVX_COV_);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_P", &Dminus_Kplus_or_piplus_P, &b_Dminus_Kplus_or_piplus_P);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PT", &Dminus_Kplus_or_piplus_PT, &b_Dminus_Kplus_or_piplus_PT);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PE", &Dminus_Kplus_or_piplus_PE, &b_Dminus_Kplus_or_piplus_PE);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PX", &Dminus_Kplus_or_piplus_PX, &b_Dminus_Kplus_or_piplus_PX);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PY", &Dminus_Kplus_or_piplus_PY, &b_Dminus_Kplus_or_piplus_PY);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PZ", &Dminus_Kplus_or_piplus_PZ, &b_Dminus_Kplus_or_piplus_PZ);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_M", &Dminus_Kplus_or_piplus_M, &b_Dminus_Kplus_or_piplus_M);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ID", &Dminus_Kplus_or_piplus_ID, &b_Dminus_Kplus_or_piplus_ID);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PIDe", &Dminus_Kplus_or_piplus_PIDe, &b_Dminus_Kplus_or_piplus_PIDe);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PIDmu", &Dminus_Kplus_or_piplus_PIDmu, &b_Dminus_Kplus_or_piplus_PIDmu);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PIDK", &Dminus_Kplus_or_piplus_PIDK, &b_Dminus_Kplus_or_piplus_PIDK);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PIDp", &Dminus_Kplus_or_piplus_PIDp, &b_Dminus_Kplus_or_piplus_PIDp);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ProbNNe", &Dminus_Kplus_or_piplus_ProbNNe, &b_Dminus_Kplus_or_piplus_ProbNNe);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ProbNNk", &Dminus_Kplus_or_piplus_ProbNNk, &b_Dminus_Kplus_or_piplus_ProbNNk);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ProbNNp", &Dminus_Kplus_or_piplus_ProbNNp, &b_Dminus_Kplus_or_piplus_ProbNNp);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ProbNNpi", &Dminus_Kplus_or_piplus_ProbNNpi, &b_Dminus_Kplus_or_piplus_ProbNNpi);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ProbNNmu", &Dminus_Kplus_or_piplus_ProbNNmu, &b_Dminus_Kplus_or_piplus_ProbNNmu);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_ProbNNghost", &Dminus_Kplus_or_piplus_ProbNNghost, &b_Dminus_Kplus_or_piplus_ProbNNghost);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_hasMuon", &Dminus_Kplus_or_piplus_hasMuon, &b_Dminus_Kplus_or_piplus_hasMuon);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_isMuon", &Dminus_Kplus_or_piplus_isMuon, &b_Dminus_Kplus_or_piplus_isMuon);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_hasRich", &Dminus_Kplus_or_piplus_hasRich, &b_Dminus_Kplus_or_piplus_hasRich);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_hasCalo", &Dminus_Kplus_or_piplus_hasCalo, &b_Dminus_Kplus_or_piplus_hasCalo);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_UsedRichAerogel", &Dminus_Kplus_or_piplus_UsedRichAerogel, &b_Dminus_Kplus_or_piplus_UsedRichAerogel);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_UsedRich1Gas", &Dminus_Kplus_or_piplus_UsedRich1Gas, &b_Dminus_Kplus_or_piplus_UsedRich1Gas);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_UsedRich2Gas", &Dminus_Kplus_or_piplus_UsedRich2Gas, &b_Dminus_Kplus_or_piplus_UsedRich2Gas);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichAboveElThres", &Dminus_Kplus_or_piplus_RichAboveElThres, &b_Dminus_Kplus_or_piplus_RichAboveElThres);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichAboveMuThres", &Dminus_Kplus_or_piplus_RichAboveMuThres, &b_Dminus_Kplus_or_piplus_RichAboveMuThres);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichAbovePiThres", &Dminus_Kplus_or_piplus_RichAbovePiThres, &b_Dminus_Kplus_or_piplus_RichAbovePiThres);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichAboveKaThres", &Dminus_Kplus_or_piplus_RichAboveKaThres, &b_Dminus_Kplus_or_piplus_RichAboveKaThres);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichAbovePrThres", &Dminus_Kplus_or_piplus_RichAbovePrThres, &b_Dminus_Kplus_or_piplus_RichAbovePrThres);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichDLLe", &Dminus_Kplus_or_piplus_RichDLLe, &b_Dminus_Kplus_or_piplus_RichDLLe);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichDLLmu", &Dminus_Kplus_or_piplus_RichDLLmu, &b_Dminus_Kplus_or_piplus_RichDLLmu);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichDLLpi", &Dminus_Kplus_or_piplus_RichDLLpi, &b_Dminus_Kplus_or_piplus_RichDLLpi);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichDLLk", &Dminus_Kplus_or_piplus_RichDLLk, &b_Dminus_Kplus_or_piplus_RichDLLk);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichDLLp", &Dminus_Kplus_or_piplus_RichDLLp, &b_Dminus_Kplus_or_piplus_RichDLLp);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_RichDLLbt", &Dminus_Kplus_or_piplus_RichDLLbt, &b_Dminus_Kplus_or_piplus_RichDLLbt);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_InAccMuon", &Dminus_Kplus_or_piplus_InAccMuon, &b_Dminus_Kplus_or_piplus_InAccMuon);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_isMuonLoose", &Dminus_Kplus_or_piplus_isMuonLoose, &b_Dminus_Kplus_or_piplus_isMuonLoose);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_MuonMuLL", &Dminus_Kplus_or_piplus_MuonMuLL, &b_Dminus_Kplus_or_piplus_MuonMuLL);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_MuonBkgLL", &Dminus_Kplus_or_piplus_MuonBkgLL, &b_Dminus_Kplus_or_piplus_MuonBkgLL);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_MuonNShared", &Dminus_Kplus_or_piplus_MuonNShared, &b_Dminus_Kplus_or_piplus_MuonNShared);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_InAccEcal", &Dminus_Kplus_or_piplus_InAccEcal, &b_Dminus_Kplus_or_piplus_InAccEcal);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_CaloEcalE", &Dminus_Kplus_or_piplus_CaloEcalE, &b_Dminus_Kplus_or_piplus_CaloEcalE);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_EcalPIDe", &Dminus_Kplus_or_piplus_EcalPIDe, &b_Dminus_Kplus_or_piplus_EcalPIDe);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_EcalPIDmu", &Dminus_Kplus_or_piplus_EcalPIDmu, &b_Dminus_Kplus_or_piplus_EcalPIDmu);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_InAccHcal", &Dminus_Kplus_or_piplus_InAccHcal, &b_Dminus_Kplus_or_piplus_InAccHcal);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_CaloHcalE", &Dminus_Kplus_or_piplus_CaloHcalE, &b_Dminus_Kplus_or_piplus_CaloHcalE);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_HcalPIDe", &Dminus_Kplus_or_piplus_HcalPIDe, &b_Dminus_Kplus_or_piplus_HcalPIDe);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_HcalPIDmu", &Dminus_Kplus_or_piplus_HcalPIDmu, &b_Dminus_Kplus_or_piplus_HcalPIDmu);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_InAccPrs", &Dminus_Kplus_or_piplus_InAccPrs, &b_Dminus_Kplus_or_piplus_InAccPrs);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_PrsPIDe", &Dminus_Kplus_or_piplus_PrsPIDe, &b_Dminus_Kplus_or_piplus_PrsPIDe);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_CaloPrsE", &Dminus_Kplus_or_piplus_CaloPrsE, &b_Dminus_Kplus_or_piplus_CaloPrsE);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_InAccSpd", &Dminus_Kplus_or_piplus_InAccSpd, &b_Dminus_Kplus_or_piplus_InAccSpd);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_CaloSpdE", &Dminus_Kplus_or_piplus_CaloSpdE, &b_Dminus_Kplus_or_piplus_CaloSpdE);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_InAccBrem", &Dminus_Kplus_or_piplus_InAccBrem, &b_Dminus_Kplus_or_piplus_InAccBrem);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_BremPIDe", &Dminus_Kplus_or_piplus_BremPIDe, &b_Dminus_Kplus_or_piplus_BremPIDe);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_VeloCharge", &Dminus_Kplus_or_piplus_VeloCharge, &b_Dminus_Kplus_or_piplus_VeloCharge);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_Type", &Dminus_Kplus_or_piplus_TRACK_Type, &b_Dminus_Kplus_or_piplus_TRACK_Type);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_Key", &Dminus_Kplus_or_piplus_TRACK_Key, &b_Dminus_Kplus_or_piplus_TRACK_Key);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_CHI2", &Dminus_Kplus_or_piplus_TRACK_CHI2, &b_Dminus_Kplus_or_piplus_TRACK_CHI2);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_NDOF", &Dminus_Kplus_or_piplus_TRACK_NDOF, &b_Dminus_Kplus_or_piplus_TRACK_NDOF);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_CHI2NDOF", &Dminus_Kplus_or_piplus_TRACK_CHI2NDOF, &b_Dminus_Kplus_or_piplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_PCHI2", &Dminus_Kplus_or_piplus_TRACK_PCHI2, &b_Dminus_Kplus_or_piplus_TRACK_PCHI2);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_VeloCHI2NDOF", &Dminus_Kplus_or_piplus_TRACK_VeloCHI2NDOF, &b_Dminus_Kplus_or_piplus_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_TCHI2NDOF", &Dminus_Kplus_or_piplus_TRACK_TCHI2NDOF, &b_Dminus_Kplus_or_piplus_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_VELO_UTID", &Dminus_Kplus_or_piplus_VELO_UTID, &b_Dminus_Kplus_or_piplus_VELO_UTID);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_FirstMeasurementX", &Dminus_Kplus_or_piplus_TRACK_FirstMeasurementX, &b_Dminus_Kplus_or_piplus_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_FirstMeasurementY", &Dminus_Kplus_or_piplus_TRACK_FirstMeasurementY, &b_Dminus_Kplus_or_piplus_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_FirstMeasurementZ", &Dminus_Kplus_or_piplus_TRACK_FirstMeasurementZ, &b_Dminus_Kplus_or_piplus_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_MatchCHI2", &Dminus_Kplus_or_piplus_TRACK_MatchCHI2, &b_Dminus_Kplus_or_piplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_GhostProb", &Dminus_Kplus_or_piplus_TRACK_GhostProb, &b_Dminus_Kplus_or_piplus_TRACK_GhostProb);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_CloneDist", &Dminus_Kplus_or_piplus_TRACK_CloneDist, &b_Dminus_Kplus_or_piplus_TRACK_CloneDist);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_TRACK_Likelihood", &Dminus_Kplus_or_piplus_TRACK_Likelihood, &b_Dminus_Kplus_or_piplus_TRACK_Likelihood);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_X", &Dminus_Kplus_or_piplus_X, &b_Dminus_Kplus_or_piplus_X);
   fChain->SetBranchAddress("Dminus_Kplus_or_piplus_Y", &Dminus_Kplus_or_piplus_Y, &b_Dminus_Kplus_or_piplus_Y);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_LOKI_ENERGY", &Dminus_piminus_or_Kminus_One_LOKI_ENERGY, &b_Dminus_piminus_or_Kminus_One_LOKI_ENERGY);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_LOKI_ETA", &Dminus_piminus_or_Kminus_One_LOKI_ETA, &b_Dminus_piminus_or_Kminus_One_LOKI_ETA);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_LOKI_PHI", &Dminus_piminus_or_Kminus_One_LOKI_PHI, &b_Dminus_piminus_or_Kminus_One_LOKI_PHI);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_X", &Dminus_piminus_or_Kminus_One_OWNPV_X, &b_Dminus_piminus_or_Kminus_One_OWNPV_X);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_Y", &Dminus_piminus_or_Kminus_One_OWNPV_Y, &b_Dminus_piminus_or_Kminus_One_OWNPV_Y);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_Z", &Dminus_piminus_or_Kminus_One_OWNPV_Z, &b_Dminus_piminus_or_Kminus_One_OWNPV_Z);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_XERR", &Dminus_piminus_or_Kminus_One_OWNPV_XERR, &b_Dminus_piminus_or_Kminus_One_OWNPV_XERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_YERR", &Dminus_piminus_or_Kminus_One_OWNPV_YERR, &b_Dminus_piminus_or_Kminus_One_OWNPV_YERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_ZERR", &Dminus_piminus_or_Kminus_One_OWNPV_ZERR, &b_Dminus_piminus_or_Kminus_One_OWNPV_ZERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_CHI2", &Dminus_piminus_or_Kminus_One_OWNPV_CHI2, &b_Dminus_piminus_or_Kminus_One_OWNPV_CHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_NDOF", &Dminus_piminus_or_Kminus_One_OWNPV_NDOF, &b_Dminus_piminus_or_Kminus_One_OWNPV_NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_OWNPV_COV_", Dminus_piminus_or_Kminus_One_OWNPV_COV_, &b_Dminus_piminus_or_Kminus_One_OWNPV_COV_);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_IP_OWNPV", &Dminus_piminus_or_Kminus_One_IP_OWNPV, &b_Dminus_piminus_or_Kminus_One_IP_OWNPV);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_IPCHI2_OWNPV", &Dminus_piminus_or_Kminus_One_IPCHI2_OWNPV, &b_Dminus_piminus_or_Kminus_One_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_X", &Dminus_piminus_or_Kminus_One_ORIVX_X, &b_Dminus_piminus_or_Kminus_One_ORIVX_X);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_Y", &Dminus_piminus_or_Kminus_One_ORIVX_Y, &b_Dminus_piminus_or_Kminus_One_ORIVX_Y);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_Z", &Dminus_piminus_or_Kminus_One_ORIVX_Z, &b_Dminus_piminus_or_Kminus_One_ORIVX_Z);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_XERR", &Dminus_piminus_or_Kminus_One_ORIVX_XERR, &b_Dminus_piminus_or_Kminus_One_ORIVX_XERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_YERR", &Dminus_piminus_or_Kminus_One_ORIVX_YERR, &b_Dminus_piminus_or_Kminus_One_ORIVX_YERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_ZERR", &Dminus_piminus_or_Kminus_One_ORIVX_ZERR, &b_Dminus_piminus_or_Kminus_One_ORIVX_ZERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_CHI2", &Dminus_piminus_or_Kminus_One_ORIVX_CHI2, &b_Dminus_piminus_or_Kminus_One_ORIVX_CHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_NDOF", &Dminus_piminus_or_Kminus_One_ORIVX_NDOF, &b_Dminus_piminus_or_Kminus_One_ORIVX_NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ORIVX_COV_", Dminus_piminus_or_Kminus_One_ORIVX_COV_, &b_Dminus_piminus_or_Kminus_One_ORIVX_COV_);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_P", &Dminus_piminus_or_Kminus_One_P, &b_Dminus_piminus_or_Kminus_One_P);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PT", &Dminus_piminus_or_Kminus_One_PT, &b_Dminus_piminus_or_Kminus_One_PT);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PE", &Dminus_piminus_or_Kminus_One_PE, &b_Dminus_piminus_or_Kminus_One_PE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PX", &Dminus_piminus_or_Kminus_One_PX, &b_Dminus_piminus_or_Kminus_One_PX);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PY", &Dminus_piminus_or_Kminus_One_PY, &b_Dminus_piminus_or_Kminus_One_PY);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PZ", &Dminus_piminus_or_Kminus_One_PZ, &b_Dminus_piminus_or_Kminus_One_PZ);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_M", &Dminus_piminus_or_Kminus_One_M, &b_Dminus_piminus_or_Kminus_One_M);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ID", &Dminus_piminus_or_Kminus_One_ID, &b_Dminus_piminus_or_Kminus_One_ID);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PIDe", &Dminus_piminus_or_Kminus_One_PIDe, &b_Dminus_piminus_or_Kminus_One_PIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PIDmu", &Dminus_piminus_or_Kminus_One_PIDmu, &b_Dminus_piminus_or_Kminus_One_PIDmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PIDK", &Dminus_piminus_or_Kminus_One_PIDK, &b_Dminus_piminus_or_Kminus_One_PIDK);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PIDp", &Dminus_piminus_or_Kminus_One_PIDp, &b_Dminus_piminus_or_Kminus_One_PIDp);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ProbNNe", &Dminus_piminus_or_Kminus_One_ProbNNe, &b_Dminus_piminus_or_Kminus_One_ProbNNe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ProbNNk", &Dminus_piminus_or_Kminus_One_ProbNNk, &b_Dminus_piminus_or_Kminus_One_ProbNNk);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ProbNNp", &Dminus_piminus_or_Kminus_One_ProbNNp, &b_Dminus_piminus_or_Kminus_One_ProbNNp);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ProbNNpi", &Dminus_piminus_or_Kminus_One_ProbNNpi, &b_Dminus_piminus_or_Kminus_One_ProbNNpi);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ProbNNmu", &Dminus_piminus_or_Kminus_One_ProbNNmu, &b_Dminus_piminus_or_Kminus_One_ProbNNmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_ProbNNghost", &Dminus_piminus_or_Kminus_One_ProbNNghost, &b_Dminus_piminus_or_Kminus_One_ProbNNghost);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_hasMuon", &Dminus_piminus_or_Kminus_One_hasMuon, &b_Dminus_piminus_or_Kminus_One_hasMuon);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_isMuon", &Dminus_piminus_or_Kminus_One_isMuon, &b_Dminus_piminus_or_Kminus_One_isMuon);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_hasRich", &Dminus_piminus_or_Kminus_One_hasRich, &b_Dminus_piminus_or_Kminus_One_hasRich);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_hasCalo", &Dminus_piminus_or_Kminus_One_hasCalo, &b_Dminus_piminus_or_Kminus_One_hasCalo);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_UsedRichAerogel", &Dminus_piminus_or_Kminus_One_UsedRichAerogel, &b_Dminus_piminus_or_Kminus_One_UsedRichAerogel);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_UsedRich1Gas", &Dminus_piminus_or_Kminus_One_UsedRich1Gas, &b_Dminus_piminus_or_Kminus_One_UsedRich1Gas);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_UsedRich2Gas", &Dminus_piminus_or_Kminus_One_UsedRich2Gas, &b_Dminus_piminus_or_Kminus_One_UsedRich2Gas);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichAboveElThres", &Dminus_piminus_or_Kminus_One_RichAboveElThres, &b_Dminus_piminus_or_Kminus_One_RichAboveElThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichAboveMuThres", &Dminus_piminus_or_Kminus_One_RichAboveMuThres, &b_Dminus_piminus_or_Kminus_One_RichAboveMuThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichAbovePiThres", &Dminus_piminus_or_Kminus_One_RichAbovePiThres, &b_Dminus_piminus_or_Kminus_One_RichAbovePiThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichAboveKaThres", &Dminus_piminus_or_Kminus_One_RichAboveKaThres, &b_Dminus_piminus_or_Kminus_One_RichAboveKaThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichAbovePrThres", &Dminus_piminus_or_Kminus_One_RichAbovePrThres, &b_Dminus_piminus_or_Kminus_One_RichAbovePrThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichDLLe", &Dminus_piminus_or_Kminus_One_RichDLLe, &b_Dminus_piminus_or_Kminus_One_RichDLLe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichDLLmu", &Dminus_piminus_or_Kminus_One_RichDLLmu, &b_Dminus_piminus_or_Kminus_One_RichDLLmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichDLLpi", &Dminus_piminus_or_Kminus_One_RichDLLpi, &b_Dminus_piminus_or_Kminus_One_RichDLLpi);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichDLLk", &Dminus_piminus_or_Kminus_One_RichDLLk, &b_Dminus_piminus_or_Kminus_One_RichDLLk);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichDLLp", &Dminus_piminus_or_Kminus_One_RichDLLp, &b_Dminus_piminus_or_Kminus_One_RichDLLp);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_RichDLLbt", &Dminus_piminus_or_Kminus_One_RichDLLbt, &b_Dminus_piminus_or_Kminus_One_RichDLLbt);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_InAccMuon", &Dminus_piminus_or_Kminus_One_InAccMuon, &b_Dminus_piminus_or_Kminus_One_InAccMuon);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_isMuonLoose", &Dminus_piminus_or_Kminus_One_isMuonLoose, &b_Dminus_piminus_or_Kminus_One_isMuonLoose);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_MuonMuLL", &Dminus_piminus_or_Kminus_One_MuonMuLL, &b_Dminus_piminus_or_Kminus_One_MuonMuLL);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_MuonBkgLL", &Dminus_piminus_or_Kminus_One_MuonBkgLL, &b_Dminus_piminus_or_Kminus_One_MuonBkgLL);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_MuonNShared", &Dminus_piminus_or_Kminus_One_MuonNShared, &b_Dminus_piminus_or_Kminus_One_MuonNShared);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_InAccEcal", &Dminus_piminus_or_Kminus_One_InAccEcal, &b_Dminus_piminus_or_Kminus_One_InAccEcal);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_CaloEcalE", &Dminus_piminus_or_Kminus_One_CaloEcalE, &b_Dminus_piminus_or_Kminus_One_CaloEcalE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_EcalPIDe", &Dminus_piminus_or_Kminus_One_EcalPIDe, &b_Dminus_piminus_or_Kminus_One_EcalPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_EcalPIDmu", &Dminus_piminus_or_Kminus_One_EcalPIDmu, &b_Dminus_piminus_or_Kminus_One_EcalPIDmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_InAccHcal", &Dminus_piminus_or_Kminus_One_InAccHcal, &b_Dminus_piminus_or_Kminus_One_InAccHcal);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_CaloHcalE", &Dminus_piminus_or_Kminus_One_CaloHcalE, &b_Dminus_piminus_or_Kminus_One_CaloHcalE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_HcalPIDe", &Dminus_piminus_or_Kminus_One_HcalPIDe, &b_Dminus_piminus_or_Kminus_One_HcalPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_HcalPIDmu", &Dminus_piminus_or_Kminus_One_HcalPIDmu, &b_Dminus_piminus_or_Kminus_One_HcalPIDmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_InAccPrs", &Dminus_piminus_or_Kminus_One_InAccPrs, &b_Dminus_piminus_or_Kminus_One_InAccPrs);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_PrsPIDe", &Dminus_piminus_or_Kminus_One_PrsPIDe, &b_Dminus_piminus_or_Kminus_One_PrsPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_CaloPrsE", &Dminus_piminus_or_Kminus_One_CaloPrsE, &b_Dminus_piminus_or_Kminus_One_CaloPrsE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_InAccSpd", &Dminus_piminus_or_Kminus_One_InAccSpd, &b_Dminus_piminus_or_Kminus_One_InAccSpd);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_CaloSpdE", &Dminus_piminus_or_Kminus_One_CaloSpdE, &b_Dminus_piminus_or_Kminus_One_CaloSpdE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_InAccBrem", &Dminus_piminus_or_Kminus_One_InAccBrem, &b_Dminus_piminus_or_Kminus_One_InAccBrem);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_BremPIDe", &Dminus_piminus_or_Kminus_One_BremPIDe, &b_Dminus_piminus_or_Kminus_One_BremPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_VeloCharge", &Dminus_piminus_or_Kminus_One_VeloCharge, &b_Dminus_piminus_or_Kminus_One_VeloCharge);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_Type", &Dminus_piminus_or_Kminus_One_TRACK_Type, &b_Dminus_piminus_or_Kminus_One_TRACK_Type);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_Key", &Dminus_piminus_or_Kminus_One_TRACK_Key, &b_Dminus_piminus_or_Kminus_One_TRACK_Key);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_CHI2", &Dminus_piminus_or_Kminus_One_TRACK_CHI2, &b_Dminus_piminus_or_Kminus_One_TRACK_CHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_NDOF", &Dminus_piminus_or_Kminus_One_TRACK_NDOF, &b_Dminus_piminus_or_Kminus_One_TRACK_NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_CHI2NDOF", &Dminus_piminus_or_Kminus_One_TRACK_CHI2NDOF, &b_Dminus_piminus_or_Kminus_One_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_PCHI2", &Dminus_piminus_or_Kminus_One_TRACK_PCHI2, &b_Dminus_piminus_or_Kminus_One_TRACK_PCHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_VeloCHI2NDOF", &Dminus_piminus_or_Kminus_One_TRACK_VeloCHI2NDOF, &b_Dminus_piminus_or_Kminus_One_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_TCHI2NDOF", &Dminus_piminus_or_Kminus_One_TRACK_TCHI2NDOF, &b_Dminus_piminus_or_Kminus_One_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_VELO_UTID", &Dminus_piminus_or_Kminus_One_VELO_UTID, &b_Dminus_piminus_or_Kminus_One_VELO_UTID);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementX", &Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementX, &b_Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementY", &Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementY, &b_Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementZ", &Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementZ, &b_Dminus_piminus_or_Kminus_One_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_MatchCHI2", &Dminus_piminus_or_Kminus_One_TRACK_MatchCHI2, &b_Dminus_piminus_or_Kminus_One_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_GhostProb", &Dminus_piminus_or_Kminus_One_TRACK_GhostProb, &b_Dminus_piminus_or_Kminus_One_TRACK_GhostProb);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_CloneDist", &Dminus_piminus_or_Kminus_One_TRACK_CloneDist, &b_Dminus_piminus_or_Kminus_One_TRACK_CloneDist);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_TRACK_Likelihood", &Dminus_piminus_or_Kminus_One_TRACK_Likelihood, &b_Dminus_piminus_or_Kminus_One_TRACK_Likelihood);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_X", &Dminus_piminus_or_Kminus_One_X, &b_Dminus_piminus_or_Kminus_One_X);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_One_Y", &Dminus_piminus_or_Kminus_One_Y, &b_Dminus_piminus_or_Kminus_One_Y);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_LOKI_ENERGY", &Dminus_piminus_or_Kminus_Two_LOKI_ENERGY, &b_Dminus_piminus_or_Kminus_Two_LOKI_ENERGY);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_LOKI_ETA", &Dminus_piminus_or_Kminus_Two_LOKI_ETA, &b_Dminus_piminus_or_Kminus_Two_LOKI_ETA);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_LOKI_PHI", &Dminus_piminus_or_Kminus_Two_LOKI_PHI, &b_Dminus_piminus_or_Kminus_Two_LOKI_PHI);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_X", &Dminus_piminus_or_Kminus_Two_OWNPV_X, &b_Dminus_piminus_or_Kminus_Two_OWNPV_X);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_Y", &Dminus_piminus_or_Kminus_Two_OWNPV_Y, &b_Dminus_piminus_or_Kminus_Two_OWNPV_Y);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_Z", &Dminus_piminus_or_Kminus_Two_OWNPV_Z, &b_Dminus_piminus_or_Kminus_Two_OWNPV_Z);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_XERR", &Dminus_piminus_or_Kminus_Two_OWNPV_XERR, &b_Dminus_piminus_or_Kminus_Two_OWNPV_XERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_YERR", &Dminus_piminus_or_Kminus_Two_OWNPV_YERR, &b_Dminus_piminus_or_Kminus_Two_OWNPV_YERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_ZERR", &Dminus_piminus_or_Kminus_Two_OWNPV_ZERR, &b_Dminus_piminus_or_Kminus_Two_OWNPV_ZERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_CHI2", &Dminus_piminus_or_Kminus_Two_OWNPV_CHI2, &b_Dminus_piminus_or_Kminus_Two_OWNPV_CHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_NDOF", &Dminus_piminus_or_Kminus_Two_OWNPV_NDOF, &b_Dminus_piminus_or_Kminus_Two_OWNPV_NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_OWNPV_COV_", Dminus_piminus_or_Kminus_Two_OWNPV_COV_, &b_Dminus_piminus_or_Kminus_Two_OWNPV_COV_);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_IP_OWNPV", &Dminus_piminus_or_Kminus_Two_IP_OWNPV, &b_Dminus_piminus_or_Kminus_Two_IP_OWNPV);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_IPCHI2_OWNPV", &Dminus_piminus_or_Kminus_Two_IPCHI2_OWNPV, &b_Dminus_piminus_or_Kminus_Two_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_X", &Dminus_piminus_or_Kminus_Two_ORIVX_X, &b_Dminus_piminus_or_Kminus_Two_ORIVX_X);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_Y", &Dminus_piminus_or_Kminus_Two_ORIVX_Y, &b_Dminus_piminus_or_Kminus_Two_ORIVX_Y);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_Z", &Dminus_piminus_or_Kminus_Two_ORIVX_Z, &b_Dminus_piminus_or_Kminus_Two_ORIVX_Z);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_XERR", &Dminus_piminus_or_Kminus_Two_ORIVX_XERR, &b_Dminus_piminus_or_Kminus_Two_ORIVX_XERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_YERR", &Dminus_piminus_or_Kminus_Two_ORIVX_YERR, &b_Dminus_piminus_or_Kminus_Two_ORIVX_YERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_ZERR", &Dminus_piminus_or_Kminus_Two_ORIVX_ZERR, &b_Dminus_piminus_or_Kminus_Two_ORIVX_ZERR);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_CHI2", &Dminus_piminus_or_Kminus_Two_ORIVX_CHI2, &b_Dminus_piminus_or_Kminus_Two_ORIVX_CHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_NDOF", &Dminus_piminus_or_Kminus_Two_ORIVX_NDOF, &b_Dminus_piminus_or_Kminus_Two_ORIVX_NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ORIVX_COV_", Dminus_piminus_or_Kminus_Two_ORIVX_COV_, &b_Dminus_piminus_or_Kminus_Two_ORIVX_COV_);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_P", &Dminus_piminus_or_Kminus_Two_P, &b_Dminus_piminus_or_Kminus_Two_P);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PT", &Dminus_piminus_or_Kminus_Two_PT, &b_Dminus_piminus_or_Kminus_Two_PT);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PE", &Dminus_piminus_or_Kminus_Two_PE, &b_Dminus_piminus_or_Kminus_Two_PE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PX", &Dminus_piminus_or_Kminus_Two_PX, &b_Dminus_piminus_or_Kminus_Two_PX);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PY", &Dminus_piminus_or_Kminus_Two_PY, &b_Dminus_piminus_or_Kminus_Two_PY);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PZ", &Dminus_piminus_or_Kminus_Two_PZ, &b_Dminus_piminus_or_Kminus_Two_PZ);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_M", &Dminus_piminus_or_Kminus_Two_M, &b_Dminus_piminus_or_Kminus_Two_M);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ID", &Dminus_piminus_or_Kminus_Two_ID, &b_Dminus_piminus_or_Kminus_Two_ID);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PIDe", &Dminus_piminus_or_Kminus_Two_PIDe, &b_Dminus_piminus_or_Kminus_Two_PIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PIDmu", &Dminus_piminus_or_Kminus_Two_PIDmu, &b_Dminus_piminus_or_Kminus_Two_PIDmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PIDK", &Dminus_piminus_or_Kminus_Two_PIDK, &b_Dminus_piminus_or_Kminus_Two_PIDK);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PIDp", &Dminus_piminus_or_Kminus_Two_PIDp, &b_Dminus_piminus_or_Kminus_Two_PIDp);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ProbNNe", &Dminus_piminus_or_Kminus_Two_ProbNNe, &b_Dminus_piminus_or_Kminus_Two_ProbNNe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ProbNNk", &Dminus_piminus_or_Kminus_Two_ProbNNk, &b_Dminus_piminus_or_Kminus_Two_ProbNNk);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ProbNNp", &Dminus_piminus_or_Kminus_Two_ProbNNp, &b_Dminus_piminus_or_Kminus_Two_ProbNNp);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ProbNNpi", &Dminus_piminus_or_Kminus_Two_ProbNNpi, &b_Dminus_piminus_or_Kminus_Two_ProbNNpi);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ProbNNmu", &Dminus_piminus_or_Kminus_Two_ProbNNmu, &b_Dminus_piminus_or_Kminus_Two_ProbNNmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_ProbNNghost", &Dminus_piminus_or_Kminus_Two_ProbNNghost, &b_Dminus_piminus_or_Kminus_Two_ProbNNghost);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_hasMuon", &Dminus_piminus_or_Kminus_Two_hasMuon, &b_Dminus_piminus_or_Kminus_Two_hasMuon);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_isMuon", &Dminus_piminus_or_Kminus_Two_isMuon, &b_Dminus_piminus_or_Kminus_Two_isMuon);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_hasRich", &Dminus_piminus_or_Kminus_Two_hasRich, &b_Dminus_piminus_or_Kminus_Two_hasRich);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_hasCalo", &Dminus_piminus_or_Kminus_Two_hasCalo, &b_Dminus_piminus_or_Kminus_Two_hasCalo);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_UsedRichAerogel", &Dminus_piminus_or_Kminus_Two_UsedRichAerogel, &b_Dminus_piminus_or_Kminus_Two_UsedRichAerogel);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_UsedRich1Gas", &Dminus_piminus_or_Kminus_Two_UsedRich1Gas, &b_Dminus_piminus_or_Kminus_Two_UsedRich1Gas);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_UsedRich2Gas", &Dminus_piminus_or_Kminus_Two_UsedRich2Gas, &b_Dminus_piminus_or_Kminus_Two_UsedRich2Gas);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichAboveElThres", &Dminus_piminus_or_Kminus_Two_RichAboveElThres, &b_Dminus_piminus_or_Kminus_Two_RichAboveElThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichAboveMuThres", &Dminus_piminus_or_Kminus_Two_RichAboveMuThres, &b_Dminus_piminus_or_Kminus_Two_RichAboveMuThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichAbovePiThres", &Dminus_piminus_or_Kminus_Two_RichAbovePiThres, &b_Dminus_piminus_or_Kminus_Two_RichAbovePiThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichAboveKaThres", &Dminus_piminus_or_Kminus_Two_RichAboveKaThres, &b_Dminus_piminus_or_Kminus_Two_RichAboveKaThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichAbovePrThres", &Dminus_piminus_or_Kminus_Two_RichAbovePrThres, &b_Dminus_piminus_or_Kminus_Two_RichAbovePrThres);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichDLLe", &Dminus_piminus_or_Kminus_Two_RichDLLe, &b_Dminus_piminus_or_Kminus_Two_RichDLLe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichDLLmu", &Dminus_piminus_or_Kminus_Two_RichDLLmu, &b_Dminus_piminus_or_Kminus_Two_RichDLLmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichDLLpi", &Dminus_piminus_or_Kminus_Two_RichDLLpi, &b_Dminus_piminus_or_Kminus_Two_RichDLLpi);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichDLLk", &Dminus_piminus_or_Kminus_Two_RichDLLk, &b_Dminus_piminus_or_Kminus_Two_RichDLLk);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichDLLp", &Dminus_piminus_or_Kminus_Two_RichDLLp, &b_Dminus_piminus_or_Kminus_Two_RichDLLp);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_RichDLLbt", &Dminus_piminus_or_Kminus_Two_RichDLLbt, &b_Dminus_piminus_or_Kminus_Two_RichDLLbt);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_InAccMuon", &Dminus_piminus_or_Kminus_Two_InAccMuon, &b_Dminus_piminus_or_Kminus_Two_InAccMuon);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_isMuonLoose", &Dminus_piminus_or_Kminus_Two_isMuonLoose, &b_Dminus_piminus_or_Kminus_Two_isMuonLoose);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_MuonMuLL", &Dminus_piminus_or_Kminus_Two_MuonMuLL, &b_Dminus_piminus_or_Kminus_Two_MuonMuLL);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_MuonBkgLL", &Dminus_piminus_or_Kminus_Two_MuonBkgLL, &b_Dminus_piminus_or_Kminus_Two_MuonBkgLL);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_MuonNShared", &Dminus_piminus_or_Kminus_Two_MuonNShared, &b_Dminus_piminus_or_Kminus_Two_MuonNShared);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_InAccEcal", &Dminus_piminus_or_Kminus_Two_InAccEcal, &b_Dminus_piminus_or_Kminus_Two_InAccEcal);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_CaloEcalE", &Dminus_piminus_or_Kminus_Two_CaloEcalE, &b_Dminus_piminus_or_Kminus_Two_CaloEcalE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_EcalPIDe", &Dminus_piminus_or_Kminus_Two_EcalPIDe, &b_Dminus_piminus_or_Kminus_Two_EcalPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_EcalPIDmu", &Dminus_piminus_or_Kminus_Two_EcalPIDmu, &b_Dminus_piminus_or_Kminus_Two_EcalPIDmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_InAccHcal", &Dminus_piminus_or_Kminus_Two_InAccHcal, &b_Dminus_piminus_or_Kminus_Two_InAccHcal);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_CaloHcalE", &Dminus_piminus_or_Kminus_Two_CaloHcalE, &b_Dminus_piminus_or_Kminus_Two_CaloHcalE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_HcalPIDe", &Dminus_piminus_or_Kminus_Two_HcalPIDe, &b_Dminus_piminus_or_Kminus_Two_HcalPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_HcalPIDmu", &Dminus_piminus_or_Kminus_Two_HcalPIDmu, &b_Dminus_piminus_or_Kminus_Two_HcalPIDmu);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_InAccPrs", &Dminus_piminus_or_Kminus_Two_InAccPrs, &b_Dminus_piminus_or_Kminus_Two_InAccPrs);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_PrsPIDe", &Dminus_piminus_or_Kminus_Two_PrsPIDe, &b_Dminus_piminus_or_Kminus_Two_PrsPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_CaloPrsE", &Dminus_piminus_or_Kminus_Two_CaloPrsE, &b_Dminus_piminus_or_Kminus_Two_CaloPrsE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_InAccSpd", &Dminus_piminus_or_Kminus_Two_InAccSpd, &b_Dminus_piminus_or_Kminus_Two_InAccSpd);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_CaloSpdE", &Dminus_piminus_or_Kminus_Two_CaloSpdE, &b_Dminus_piminus_or_Kminus_Two_CaloSpdE);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_InAccBrem", &Dminus_piminus_or_Kminus_Two_InAccBrem, &b_Dminus_piminus_or_Kminus_Two_InAccBrem);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_BremPIDe", &Dminus_piminus_or_Kminus_Two_BremPIDe, &b_Dminus_piminus_or_Kminus_Two_BremPIDe);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_VeloCharge", &Dminus_piminus_or_Kminus_Two_VeloCharge, &b_Dminus_piminus_or_Kminus_Two_VeloCharge);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_Type", &Dminus_piminus_or_Kminus_Two_TRACK_Type, &b_Dminus_piminus_or_Kminus_Two_TRACK_Type);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_Key", &Dminus_piminus_or_Kminus_Two_TRACK_Key, &b_Dminus_piminus_or_Kminus_Two_TRACK_Key);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_CHI2", &Dminus_piminus_or_Kminus_Two_TRACK_CHI2, &b_Dminus_piminus_or_Kminus_Two_TRACK_CHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_NDOF", &Dminus_piminus_or_Kminus_Two_TRACK_NDOF, &b_Dminus_piminus_or_Kminus_Two_TRACK_NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_CHI2NDOF", &Dminus_piminus_or_Kminus_Two_TRACK_CHI2NDOF, &b_Dminus_piminus_or_Kminus_Two_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_PCHI2", &Dminus_piminus_or_Kminus_Two_TRACK_PCHI2, &b_Dminus_piminus_or_Kminus_Two_TRACK_PCHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_VeloCHI2NDOF", &Dminus_piminus_or_Kminus_Two_TRACK_VeloCHI2NDOF, &b_Dminus_piminus_or_Kminus_Two_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_TCHI2NDOF", &Dminus_piminus_or_Kminus_Two_TRACK_TCHI2NDOF, &b_Dminus_piminus_or_Kminus_Two_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_VELO_UTID", &Dminus_piminus_or_Kminus_Two_VELO_UTID, &b_Dminus_piminus_or_Kminus_Two_VELO_UTID);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementX", &Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementX, &b_Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementY", &Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementY, &b_Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementZ", &Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementZ, &b_Dminus_piminus_or_Kminus_Two_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_MatchCHI2", &Dminus_piminus_or_Kminus_Two_TRACK_MatchCHI2, &b_Dminus_piminus_or_Kminus_Two_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_GhostProb", &Dminus_piminus_or_Kminus_Two_TRACK_GhostProb, &b_Dminus_piminus_or_Kminus_Two_TRACK_GhostProb);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_CloneDist", &Dminus_piminus_or_Kminus_Two_TRACK_CloneDist, &b_Dminus_piminus_or_Kminus_Two_TRACK_CloneDist);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_TRACK_Likelihood", &Dminus_piminus_or_Kminus_Two_TRACK_Likelihood, &b_Dminus_piminus_or_Kminus_Two_TRACK_Likelihood);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_X", &Dminus_piminus_or_Kminus_Two_X, &b_Dminus_piminus_or_Kminus_Two_X);
   fChain->SetBranchAddress("Dminus_piminus_or_Kminus_Two_Y", &Dminus_piminus_or_Kminus_Two_Y, &b_Dminus_piminus_or_Kminus_Two_Y);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLTTCK", &HLTTCK, &b_HLTTCK);
   fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
   fChain->SetBranchAddress("GpsYear", &GpsYear, &b_GpsYear);
   fChain->SetBranchAddress("GpsMonth", &GpsMonth, &b_GpsMonth);
   fChain->SetBranchAddress("GpsDay", &GpsDay, &b_GpsDay);
   fChain->SetBranchAddress("GpsHour", &GpsHour, &b_GpsHour);
   fChain->SetBranchAddress("GpsMinute", &GpsMinute, &b_GpsMinute);
   fChain->SetBranchAddress("GpsSecond", &GpsSecond, &b_GpsSecond);
   fChain->SetBranchAddress("TriggerType", &TriggerType, &b_TriggerType);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("PVX", PVX, &b_PVX);
   fChain->SetBranchAddress("PVY", PVY, &b_PVY);
   fChain->SetBranchAddress("PVZ", PVZ, &b_PVZ);
   fChain->SetBranchAddress("PVXERR", PVXERR, &b_PVXERR);
   fChain->SetBranchAddress("PVYERR", PVYERR, &b_PVYERR);
   fChain->SetBranchAddress("PVZERR", PVZERR, &b_PVZERR);
   fChain->SetBranchAddress("PVCHI2", PVCHI2, &b_PVCHI2);
   fChain->SetBranchAddress("PVNDOF", PVNDOF, &b_PVNDOF);
   fChain->SetBranchAddress("PVNTRACKS", PVNTRACKS, &b_PVNTRACKS);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("nLongTracks", &nLongTracks, &b_nLongTracks);
   fChain->SetBranchAddress("nDownstreamTracks", &nDownstreamTracks, &b_nDownstreamTracks);
   fChain->SetBranchAddress("nUpstreamTracks", &nUpstreamTracks, &b_nUpstreamTracks);
   fChain->SetBranchAddress("nVeloTracks", &nVeloTracks, &b_nVeloTracks);
   fChain->SetBranchAddress("nTTracks", &nTTracks, &b_nTTracks);
   fChain->SetBranchAddress("nBackTracks", &nBackTracks, &b_nBackTracks);
   fChain->SetBranchAddress("nRich1Hits", &nRich1Hits, &b_nRich1Hits);
   fChain->SetBranchAddress("nRich2Hits", &nRich2Hits, &b_nRich2Hits);
   fChain->SetBranchAddress("nVeloClusters", &nVeloClusters, &b_nVeloClusters);
   fChain->SetBranchAddress("nITClusters", &nITClusters, &b_nITClusters);
   fChain->SetBranchAddress("nTTClusters", &nTTClusters, &b_nTTClusters);
   fChain->SetBranchAddress("nOTClusters", &nOTClusters, &b_nOTClusters);
   fChain->SetBranchAddress("nSPDHits", &nSPDHits, &b_nSPDHits);
   fChain->SetBranchAddress("nMuonCoordsS0", &nMuonCoordsS0, &b_nMuonCoordsS0);
   fChain->SetBranchAddress("nMuonCoordsS1", &nMuonCoordsS1, &b_nMuonCoordsS1);
   fChain->SetBranchAddress("nMuonCoordsS2", &nMuonCoordsS2, &b_nMuonCoordsS2);
   fChain->SetBranchAddress("nMuonCoordsS3", &nMuonCoordsS3, &b_nMuonCoordsS3);
   fChain->SetBranchAddress("nMuonCoordsS4", &nMuonCoordsS4, &b_nMuonCoordsS4);
   fChain->SetBranchAddress("nMuonTracks", &nMuonTracks, &b_nMuonTracks);
   fChain->SetBranchAddress("StrippingB02DDBeauty2CharmLineDecision", &StrippingB02DDBeauty2CharmLineDecision, &b_StrippingB02DDBeauty2CharmLineDecision);
   fChain->SetBranchAddress("L0Global", &L0Global, &b_L0Global);
   fChain->SetBranchAddress("Hlt1Global", &Hlt1Global, &b_Hlt1Global);
   fChain->SetBranchAddress("Hlt2Global", &Hlt2Global, &b_Hlt2Global);
   fChain->SetBranchAddress("L0PhysicsDecision", &L0PhysicsDecision, &b_L0PhysicsDecision);
   fChain->SetBranchAddress("L0MuonDecision", &L0MuonDecision, &b_L0MuonDecision);
   fChain->SetBranchAddress("L0DiMuonDecision", &L0DiMuonDecision, &b_L0DiMuonDecision);
   fChain->SetBranchAddress("L0MuonHighDecision", &L0MuonHighDecision, &b_L0MuonHighDecision);
   fChain->SetBranchAddress("L0HadronDecision", &L0HadronDecision, &b_L0HadronDecision);
   fChain->SetBranchAddress("L0ElectronDecision", &L0ElectronDecision, &b_L0ElectronDecision);
   fChain->SetBranchAddress("L0PhotonDecision", &L0PhotonDecision, &b_L0PhotonDecision);
   fChain->SetBranchAddress("L0nSelections", &L0nSelections, &b_L0nSelections);
   fChain->SetBranchAddress("Hlt1TrackAllL0Decision", &Hlt1TrackAllL0Decision, &b_Hlt1TrackAllL0Decision);
   fChain->SetBranchAddress("Hlt1TrackAllL0TightDecision", &Hlt1TrackAllL0TightDecision, &b_Hlt1TrackAllL0TightDecision);
   fChain->SetBranchAddress("Hlt1L0AnyDecision", &Hlt1L0AnyDecision, &b_Hlt1L0AnyDecision);
   fChain->SetBranchAddress("Hlt1GlobalDecision", &Hlt1GlobalDecision, &b_Hlt1GlobalDecision);
   fChain->SetBranchAddress("Hlt1nSelections", &Hlt1nSelections, &b_Hlt1nSelections);
   fChain->SetBranchAddress("Hlt2GlobalDecision", &Hlt2GlobalDecision, &b_Hlt2GlobalDecision);
   fChain->SetBranchAddress("Hlt2Topo2BodySimpleDecision", &Hlt2Topo2BodySimpleDecision, &b_Hlt2Topo2BodySimpleDecision);
   fChain->SetBranchAddress("Hlt2Topo3BodySimpleDecision", &Hlt2Topo3BodySimpleDecision, &b_Hlt2Topo3BodySimpleDecision);
   fChain->SetBranchAddress("Hlt2Topo4BodySimpleDecision", &Hlt2Topo4BodySimpleDecision, &b_Hlt2Topo4BodySimpleDecision);
   fChain->SetBranchAddress("Hlt2Topo2BodyBBDTDecision", &Hlt2Topo2BodyBBDTDecision, &b_Hlt2Topo2BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2Topo3BodyBBDTDecision", &Hlt2Topo3BodyBBDTDecision, &b_Hlt2Topo3BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2Topo4BodyBBDTDecision", &Hlt2Topo4BodyBBDTDecision, &b_Hlt2Topo4BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2TopoMu2BodyBBDTDecision", &Hlt2TopoMu2BodyBBDTDecision, &b_Hlt2TopoMu2BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2TopoMu3BodyBBDTDecision", &Hlt2TopoMu3BodyBBDTDecision, &b_Hlt2TopoMu3BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2TopoMu4BodyBBDTDecision", &Hlt2TopoMu4BodyBBDTDecision, &b_Hlt2TopoMu4BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2TopoE2BodyBBDTDecision", &Hlt2TopoE2BodyBBDTDecision, &b_Hlt2TopoE2BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2TopoE3BodyBBDTDecision", &Hlt2TopoE3BodyBBDTDecision, &b_Hlt2TopoE3BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2TopoE4BodyBBDTDecision", &Hlt2TopoE4BodyBBDTDecision, &b_Hlt2TopoE4BodyBBDTDecision);
   fChain->SetBranchAddress("Hlt2IncPhiDecision", &Hlt2IncPhiDecision, &b_Hlt2IncPhiDecision);
   fChain->SetBranchAddress("Hlt2IncPhiSidebandsDecision", &Hlt2IncPhiSidebandsDecision, &b_Hlt2IncPhiSidebandsDecision);
   fChain->SetBranchAddress("Hlt2nSelections", &Hlt2nSelections, &b_Hlt2nSelections);
   fChain->SetBranchAddress("MaxRoutingBits", &MaxRoutingBits, &b_MaxRoutingBits);
   fChain->SetBranchAddress("RoutingBits", RoutingBits, &b_RoutingBits);
   fChain->SetBranchAddress("obsMassDDPVConst", &obsMassDDPVConst, &b_obsMassDDPVConst);
   fChain->SetBranchAddress("obsMassErrDDPVConst", &obsMassErrDDPVConst, &b_obsMassErrDDPVConst);
   fChain->SetBranchAddress("obsMassPVConst", &obsMassPVConst, &b_obsMassPVConst);
   fChain->SetBranchAddress("obsMassErrPVConst", &obsMassErrPVConst, &b_obsMassErrPVConst);
   fChain->SetBranchAddress("obsMassDauOne", &obsMassDauOne, &b_obsMassDauOne);
   fChain->SetBranchAddress("obsMassErrDauOne", &obsMassErrDauOne, &b_obsMassErrDauOne);
   fChain->SetBranchAddress("obsMassDauTwo", &obsMassDauTwo, &b_obsMassDauTwo);
   fChain->SetBranchAddress("obsMassErrDauTwo", &obsMassErrDauTwo, &b_obsMassErrDauTwo);
   fChain->SetBranchAddress("obsMassLokiDDPVConst", &obsMassLokiDDPVConst, &b_obsMassLokiDDPVConst);
   fChain->SetBranchAddress("obsMassErrLokiDDPVConst", &obsMassErrLokiDDPVConst, &b_obsMassErrLokiDDPVConst);
   fChain->SetBranchAddress("obsMassLokiDauOne", &obsMassLokiDauOne, &b_obsMassLokiDauOne);
   fChain->SetBranchAddress("obsMassErrLokiDauOne", &obsMassErrLokiDauOne, &b_obsMassErrLokiDauOne);
   fChain->SetBranchAddress("obsMassLokiDauTwo", &obsMassLokiDauTwo, &b_obsMassLokiDauTwo);
   fChain->SetBranchAddress("obsMassErrLokiDauTwo", &obsMassErrLokiDauTwo, &b_obsMassErrLokiDauTwo);
   fChain->SetBranchAddress("obsMass", &obsMass, &b_obsMass);
   fChain->SetBranchAddress("obsMassErr", &obsMassErr, &b_obsMassErr);
   fChain->SetBranchAddress("obsTime", &obsTime, &b_obsTime);
   fChain->SetBranchAddress("obsTimeErr", &obsTimeErr, &b_obsTimeErr);
   fChain->SetBranchAddress("varDplusTauSignificance", &varDplusTauSignificance, &b_varDplusTauSignificance);
   fChain->SetBranchAddress("varDminusTauSignificance", &varDminusTauSignificance, &b_varDminusTauSignificance);
   fChain->SetBranchAddress("varDMinTauSignificance", &varDMinTauSignificance, &b_varDMinTauSignificance);
   fChain->SetBranchAddress("varDMaxTauSignificance", &varDMaxTauSignificance, &b_varDMaxTauSignificance);
   fChain->SetBranchAddress("varKSMassHypo_DplusOne", &varKSMassHypo_DplusOne, &b_varKSMassHypo_DplusOne);
   fChain->SetBranchAddress("varKSMassHypo_DplusTwo", &varKSMassHypo_DplusTwo, &b_varKSMassHypo_DplusTwo);
   fChain->SetBranchAddress("varKSMassHypo_DminusOne", &varKSMassHypo_DminusOne, &b_varKSMassHypo_DminusOne);
   fChain->SetBranchAddress("varKSMassHypo_DminusTwo", &varKSMassHypo_DminusTwo, &b_varKSMassHypo_DminusTwo);
   fChain->SetBranchAddress("varDplusMassHypo_Kpipi", &varDplusMassHypo_Kpipi, &b_varDplusMassHypo_Kpipi);
   fChain->SetBranchAddress("varDminusMassHypo_Kpipi", &varDminusMassHypo_Kpipi, &b_varDminusMassHypo_Kpipi);
   fChain->SetBranchAddress("varDplusMassHypo_KKpi", &varDplusMassHypo_KKpi, &b_varDplusMassHypo_KKpi);
   fChain->SetBranchAddress("varDminusMassHypo_KKpi", &varDminusMassHypo_KKpi, &b_varDminusMassHypo_KKpi);
   fChain->SetBranchAddress("varDplusMassHypo_KpiK", &varDplusMassHypo_KpiK, &b_varDplusMassHypo_KpiK);
   fChain->SetBranchAddress("varDminusMassHypo_KpiK", &varDminusMassHypo_KpiK, &b_varDminusMassHypo_KpiK);
   fChain->SetBranchAddress("varDplusMassHypo_KKK", &varDplusMassHypo_KKK, &b_varDplusMassHypo_KKK);
   fChain->SetBranchAddress("varDminusMassHypo_KKK", &varDminusMassHypo_KKK, &b_varDminusMassHypo_KKK);
   fChain->SetBranchAddress("varDplusMassHypo_pipipi", &varDplusMassHypo_pipipi, &b_varDplusMassHypo_pipipi);
   fChain->SetBranchAddress("varDminusMassHypo_pipipi", &varDminusMassHypo_pipipi, &b_varDminusMassHypo_pipipi);
   fChain->SetBranchAddress("varDplusMassHypo_pipiK", &varDplusMassHypo_pipiK, &b_varDplusMassHypo_pipiK);
   fChain->SetBranchAddress("varDminusMassHypo_pipiK", &varDminusMassHypo_pipiK, &b_varDminusMassHypo_pipiK);
   fChain->SetBranchAddress("varDplusMassHypo_piKpi", &varDplusMassHypo_piKpi, &b_varDplusMassHypo_piKpi);
   fChain->SetBranchAddress("varDminusMassHypo_piKpi", &varDminusMassHypo_piKpi, &b_varDminusMassHypo_piKpi);
   fChain->SetBranchAddress("varDplusMassHypo_piKK", &varDplusMassHypo_piKK, &b_varDplusMassHypo_piKK);
   fChain->SetBranchAddress("varDminusMassHypo_piKK", &varDminusMassHypo_piKK, &b_varDminusMassHypo_piKK);
   fChain->SetBranchAddress("varDplusMassHypo_Kppi", &varDplusMassHypo_Kppi, &b_varDplusMassHypo_Kppi);
   fChain->SetBranchAddress("varDminusMassHypo_Kppi", &varDminusMassHypo_Kppi, &b_varDminusMassHypo_Kppi);
   fChain->SetBranchAddress("varDplusMassHypo_Kpip", &varDplusMassHypo_Kpip, &b_varDplusMassHypo_Kpip);
   fChain->SetBranchAddress("varDminusMassHypo_Kpip", &varDminusMassHypo_Kpip, &b_varDminusMassHypo_Kpip);
   fChain->SetBranchAddress("varDplusMassHypo_pKpi", &varDplusMassHypo_pKpi, &b_varDplusMassHypo_pKpi);
   fChain->SetBranchAddress("varDminusMassHypo_pKpi", &varDminusMassHypo_pKpi, &b_varDminusMassHypo_pKpi);
   fChain->SetBranchAddress("varDplusMassHypo_ppiK", &varDplusMassHypo_ppiK, &b_varDplusMassHypo_ppiK);
   fChain->SetBranchAddress("varDminusMassHypo_ppiK", &varDminusMassHypo_ppiK, &b_varDminusMassHypo_ppiK);
   fChain->SetBranchAddress("varDplusMassHypo_pipK", &varDplusMassHypo_pipK, &b_varDplusMassHypo_pipK);
   fChain->SetBranchAddress("varDminusMassHypo_pipK", &varDminusMassHypo_pipK, &b_varDminusMassHypo_pipK);
   fChain->SetBranchAddress("varDplusMassHypo_piKp", &varDplusMassHypo_piKp, &b_varDplusMassHypo_piKp);
   fChain->SetBranchAddress("varDminusMassHypo_piKp", &varDminusMassHypo_piKp, &b_varDminusMassHypo_piKp);
   fChain->SetBranchAddress("varDplusMassHypo_ppipi", &varDplusMassHypo_ppipi, &b_varDplusMassHypo_ppipi);
   fChain->SetBranchAddress("varDminusMassHypo_ppipi", &varDminusMassHypo_ppipi, &b_varDminusMassHypo_ppipi);
   fChain->SetBranchAddress("varDplusMassHypo_pippi", &varDplusMassHypo_pippi, &b_varDplusMassHypo_pippi);
   fChain->SetBranchAddress("varDminusMassHypo_pippi", &varDminusMassHypo_pippi, &b_varDminusMassHypo_pippi);
   fChain->SetBranchAddress("varDplusMassHypo_pipip", &varDplusMassHypo_pipip, &b_varDplusMassHypo_pipip);
   fChain->SetBranchAddress("varDminusMassHypo_pipip", &varDminusMassHypo_pipip, &b_varDminusMassHypo_pipip);
   fChain->SetBranchAddress("varBMassHypo_Dpluspipi", &varBMassHypo_Dpluspipi, &b_varBMassHypo_Dpluspipi);
   fChain->SetBranchAddress("varBMassHypo_Dminuspipi", &varBMassHypo_Dminuspipi, &b_varBMassHypo_Dminuspipi);
   fChain->SetBranchAddress("varBMassHypo_DplusKpi", &varBMassHypo_DplusKpi, &b_varBMassHypo_DplusKpi);
   fChain->SetBranchAddress("varBMassHypo_DminusKpi", &varBMassHypo_DminusKpi, &b_varBMassHypo_DminusKpi);
   fChain->SetBranchAddress("varBMassHypo_DpluspiK", &varBMassHypo_DpluspiK, &b_varBMassHypo_DpluspiK);
   fChain->SetBranchAddress("varBMassHypo_DminuspiK", &varBMassHypo_DminuspiK, &b_varBMassHypo_DminuspiK);
   fChain->SetBranchAddress("varKplusTrackGhostProb", &varKplusTrackGhostProb, &b_varKplusTrackGhostProb);
   fChain->SetBranchAddress("varKminusTrackGhostProb", &varKminusTrackGhostProb, &b_varKminusTrackGhostProb);
   fChain->SetBranchAddress("varKaonMaxTrackGhostProb", &varKaonMaxTrackGhostProb, &b_varKaonMaxTrackGhostProb);
   fChain->SetBranchAddress("varPiplusOneTrackGhostProb", &varPiplusOneTrackGhostProb, &b_varPiplusOneTrackGhostProb);
   fChain->SetBranchAddress("varPiplusTwoTrackGhostProb", &varPiplusTwoTrackGhostProb, &b_varPiplusTwoTrackGhostProb);
   fChain->SetBranchAddress("varPiplusMaxTrackGhostProb", &varPiplusMaxTrackGhostProb, &b_varPiplusMaxTrackGhostProb);
   fChain->SetBranchAddress("varPiminusOneTrackGhostProb", &varPiminusOneTrackGhostProb, &b_varPiminusOneTrackGhostProb);
   fChain->SetBranchAddress("varPiminusTwoTrackGhostProb", &varPiminusTwoTrackGhostProb, &b_varPiminusTwoTrackGhostProb);
   fChain->SetBranchAddress("varPiminusMaxTrackGhostProb", &varPiminusMaxTrackGhostProb, &b_varPiminusMaxTrackGhostProb);
   fChain->SetBranchAddress("varPionMaxTrackGhostProb", &varPionMaxTrackGhostProb, &b_varPionMaxTrackGhostProb);
   fChain->SetBranchAddress("varPVVtxChi2ndof", &varPVVtxChi2ndof, &b_varPVVtxChi2ndof);
   fChain->SetBranchAddress("varPVVtxChi2ndof_log", &varPVVtxChi2ndof_log, &b_varPVVtxChi2ndof_log);
   fChain->SetBranchAddress("varDMinVtxSepChi2", &varDMinVtxSepChi2, &b_varDMinVtxSepChi2);
   fChain->SetBranchAddress("varDMaxVtxSepChi2", &varDMaxVtxSepChi2, &b_varDMaxVtxSepChi2);
   fChain->SetBranchAddress("varBEndVtxChi2ndof", &varBEndVtxChi2ndof, &b_varBEndVtxChi2ndof);
   fChain->SetBranchAddress("varBEndVtxChi2ndof_log", &varBEndVtxChi2ndof_log, &b_varBEndVtxChi2ndof_log);
   fChain->SetBranchAddress("varDplusEndVtxChi2ndof", &varDplusEndVtxChi2ndof, &b_varDplusEndVtxChi2ndof);
   fChain->SetBranchAddress("varDminusEndVtxChi2ndof", &varDminusEndVtxChi2ndof, &b_varDminusEndVtxChi2ndof);
   fChain->SetBranchAddress("varDMaxEndVtxChi2ndof", &varDMaxEndVtxChi2ndof, &b_varDMaxEndVtxChi2ndof);
   fChain->SetBranchAddress("varDDDTFSumPT", &varDDDTFSumPT, &b_varDDDTFSumPT);
   fChain->SetBranchAddress("varKaonMaxTrackFitChi2ndof", &varKaonMaxTrackFitChi2ndof, &b_varKaonMaxTrackFitChi2ndof);
   fChain->SetBranchAddress("varPiplusMaxTrackFitChi2ndof", &varPiplusMaxTrackFitChi2ndof, &b_varPiplusMaxTrackFitChi2ndof);
   fChain->SetBranchAddress("varPiminusMaxTrackFitChi2ndof", &varPiminusMaxTrackFitChi2ndof, &b_varPiminusMaxTrackFitChi2ndof);
   fChain->SetBranchAddress("varPionMaxTrackFitChi2ndof", &varPionMaxTrackFitChi2ndof, &b_varPionMaxTrackFitChi2ndof);
   fChain->SetBranchAddress("varDplusPionsSumPT", &varDplusPionsSumPT, &b_varDplusPionsSumPT);
   fChain->SetBranchAddress("varDplusDaughtersSumPT", &varDplusDaughtersSumPT, &b_varDplusDaughtersSumPT);
   fChain->SetBranchAddress("varDminusPionsSumPT", &varDminusPionsSumPT, &b_varDminusPionsSumPT);
   fChain->SetBranchAddress("varDminusDaughtersSumPT", &varDminusDaughtersSumPT, &b_varDminusDaughtersSumPT);
   fChain->SetBranchAddress("varDTFChi2ndof", &varDTFChi2ndof, &b_varDTFChi2ndof);
   fChain->SetBranchAddress("varDTFChi2ndof_log", &varDTFChi2ndof_log, &b_varDTFChi2ndof_log);
   fChain->SetBranchAddress("varIPChi2", &varIPChi2, &b_varIPChi2);
   fChain->SetBranchAddress("varIPChi2_log", &varIPChi2_log, &b_varIPChi2_log);
   fChain->SetBranchAddress("varDplusIPChi2", &varDplusIPChi2, &b_varDplusIPChi2);
   fChain->SetBranchAddress("varDminusIPChi2", &varDminusIPChi2, &b_varDminusIPChi2);
   fChain->SetBranchAddress("varDIPChi2Minimum", &varDIPChi2Minimum, &b_varDIPChi2Minimum);
   fChain->SetBranchAddress("varDIPChi2Maximum", &varDIPChi2Maximum, &b_varDIPChi2Maximum);
   fChain->SetBranchAddress("varPiminusOneIPChi2", &varPiminusOneIPChi2, &b_varPiminusOneIPChi2);
   fChain->SetBranchAddress("varPiminusTwoIPChi2", &varPiminusTwoIPChi2, &b_varPiminusTwoIPChi2);
   fChain->SetBranchAddress("varKplusIPChi2", &varKplusIPChi2, &b_varKplusIPChi2);
   fChain->SetBranchAddress("varPiplusOneIPChi2", &varPiplusOneIPChi2, &b_varPiplusOneIPChi2);
   fChain->SetBranchAddress("varPiplusTwoIPChi2", &varPiplusTwoIPChi2, &b_varPiplusTwoIPChi2);
   fChain->SetBranchAddress("varKminusIPChi2", &varKminusIPChi2, &b_varKminusIPChi2);
   fChain->SetBranchAddress("varKaonIPChi2Minimum", &varKaonIPChi2Minimum, &b_varKaonIPChi2Minimum);
   fChain->SetBranchAddress("varPionOneIPChi2Minimum", &varPionOneIPChi2Minimum, &b_varPionOneIPChi2Minimum);
   fChain->SetBranchAddress("varPionTwoIPChi2Minimum", &varPionTwoIPChi2Minimum, &b_varPionTwoIPChi2Minimum);
   fChain->SetBranchAddress("varKaonIPChi2Maximum", &varKaonIPChi2Maximum, &b_varKaonIPChi2Maximum);
   fChain->SetBranchAddress("varPionOneIPChi2Maximum", &varPionOneIPChi2Maximum, &b_varPionOneIPChi2Maximum);
   fChain->SetBranchAddress("varPionTwoIPChi2Maximum", &varPionTwoIPChi2Maximum, &b_varPionTwoIPChi2Maximum);
   fChain->SetBranchAddress("varBDIRAOwnPV", &varBDIRAOwnPV, &b_varBDIRAOwnPV);
   fChain->SetBranchAddress("varDplusDIRAOwnPV", &varDplusDIRAOwnPV, &b_varDplusDIRAOwnPV);
   fChain->SetBranchAddress("varDminusDIRAOwnPV", &varDminusDIRAOwnPV, &b_varDminusDIRAOwnPV);
   fChain->SetBranchAddress("varDMinDIRA", &varDMinDIRA, &b_varDMinDIRA);
   fChain->SetBranchAddress("varDMaxDIRA", &varDMaxDIRA, &b_varDMaxDIRA);
   fChain->SetBranchAddress("varDTFPVPosX", &varDTFPVPosX, &b_varDTFPVPosX);
   fChain->SetBranchAddress("varDTFPVPosY", &varDTFPVPosY, &b_varDTFPVPosY);
   fChain->SetBranchAddress("varDTFPVPosZ", &varDTFPVPosZ, &b_varDTFPVPosZ);
   fChain->SetBranchAddress("obsMomentum", &obsMomentum, &b_obsMomentum);
   fChain->SetBranchAddress("obsMomentumX", &obsMomentumX, &b_obsMomentumX);
   fChain->SetBranchAddress("obsMomentumY", &obsMomentumY, &b_obsMomentumY);
   fChain->SetBranchAddress("obsMomentumZ", &obsMomentumZ, &b_obsMomentumZ);
   fChain->SetBranchAddress("obsTransverseMomentum", &obsTransverseMomentum, &b_obsTransverseMomentum);
   fChain->SetBranchAddress("obsDTFMomentum", &obsDTFMomentum, &b_obsDTFMomentum);
   fChain->SetBranchAddress("obsDTFMomentumError", &obsDTFMomentumError, &b_obsDTFMomentumError);
   fChain->SetBranchAddress("obsDTFTransverseMomentum", &obsDTFTransverseMomentum, &b_obsDTFTransverseMomentum);
   fChain->SetBranchAddress("obsDTFTransverseMomentumError", &obsDTFTransverseMomentumError, &b_obsDTFTransverseMomentumError);
   fChain->SetBranchAddress("varDplusP", &varDplusP, &b_varDplusP);
   fChain->SetBranchAddress("varDplusPT", &varDplusPT, &b_varDplusPT);
   fChain->SetBranchAddress("varDminusP", &varDminusP, &b_varDminusP);
   fChain->SetBranchAddress("varDminusPT", &varDminusPT, &b_varDminusPT);
   fChain->SetBranchAddress("varDMinP", &varDMinP, &b_varDMinP);
   fChain->SetBranchAddress("varDMinPT", &varDMinPT, &b_varDMinPT);
   fChain->SetBranchAddress("varDMaxP", &varDMaxP, &b_varDMaxP);
   fChain->SetBranchAddress("varDMaxPT", &varDMaxPT, &b_varDMaxPT);
   fChain->SetBranchAddress("varPiplusOneP", &varPiplusOneP, &b_varPiplusOneP);
   fChain->SetBranchAddress("varPiplusOnePT", &varPiplusOnePT, &b_varPiplusOnePT);
   fChain->SetBranchAddress("varPiplusTwoP", &varPiplusTwoP, &b_varPiplusTwoP);
   fChain->SetBranchAddress("varPiplusTwoPT", &varPiplusTwoPT, &b_varPiplusTwoPT);
   fChain->SetBranchAddress("varPiminusOneP", &varPiminusOneP, &b_varPiminusOneP);
   fChain->SetBranchAddress("varPiminusOnePT", &varPiminusOnePT, &b_varPiminusOnePT);
   fChain->SetBranchAddress("varPiminusTwoP", &varPiminusTwoP, &b_varPiminusTwoP);
   fChain->SetBranchAddress("varPiminusTwoPT", &varPiminusTwoPT, &b_varPiminusTwoPT);
   fChain->SetBranchAddress("varKplusP", &varKplusP, &b_varKplusP);
   fChain->SetBranchAddress("varKplusPT", &varKplusPT, &b_varKplusPT);
   fChain->SetBranchAddress("varKminusP", &varKminusP, &b_varKminusP);
   fChain->SetBranchAddress("varKminusPT", &varKminusPT, &b_varKminusPT);
   fChain->SetBranchAddress("varPionOneMinP", &varPionOneMinP, &b_varPionOneMinP);
   fChain->SetBranchAddress("varPionTwoMinP", &varPionTwoMinP, &b_varPionTwoMinP);
   fChain->SetBranchAddress("varKaonMinP", &varKaonMinP, &b_varKaonMinP);
   fChain->SetBranchAddress("varPionOneMinPT", &varPionOneMinPT, &b_varPionOneMinPT);
   fChain->SetBranchAddress("varPionTwoMinPT", &varPionTwoMinPT, &b_varPionTwoMinPT);
   fChain->SetBranchAddress("varPionMinPT", &varPionMinPT, &b_varPionMinPT);
   fChain->SetBranchAddress("varKaonMinPT", &varKaonMinPT, &b_varKaonMinPT);
   fChain->SetBranchAddress("varHadronMinPT", &varHadronMinPT, &b_varHadronMinPT);
   fChain->SetBranchAddress("varPionOneMaxP", &varPionOneMaxP, &b_varPionOneMaxP);
   fChain->SetBranchAddress("varPionTwoMaxP", &varPionTwoMaxP, &b_varPionTwoMaxP);
   fChain->SetBranchAddress("varKaonMaxP", &varKaonMaxP, &b_varKaonMaxP);
   fChain->SetBranchAddress("varPionOneMaxPT", &varPionOneMaxPT, &b_varPionOneMaxPT);
   fChain->SetBranchAddress("varPionTwoMaxPT", &varPionTwoMaxPT, &b_varPionTwoMaxPT);
   fChain->SetBranchAddress("varPionMaxPT", &varPionMaxPT, &b_varPionMaxPT);
   fChain->SetBranchAddress("varKaonMaxPT", &varKaonMaxPT, &b_varKaonMaxPT);
   fChain->SetBranchAddress("varHadronMaxPT", &varHadronMaxPT, &b_varHadronMaxPT);
   fChain->SetBranchAddress("varKminusVELOChi2ndof", &varKminusVELOChi2ndof, &b_varKminusVELOChi2ndof);
   fChain->SetBranchAddress("varKplusVELOChi2ndof", &varKplusVELOChi2ndof, &b_varKplusVELOChi2ndof);
   fChain->SetBranchAddress("varKaonMinVELOChi2ndof", &varKaonMinVELOChi2ndof, &b_varKaonMinVELOChi2ndof);
   fChain->SetBranchAddress("varKaonMinVELOChi2ndof_log", &varKaonMinVELOChi2ndof_log, &b_varKaonMinVELOChi2ndof_log);
   fChain->SetBranchAddress("varKaonMaxVELOChi2ndof", &varKaonMaxVELOChi2ndof, &b_varKaonMaxVELOChi2ndof);
   fChain->SetBranchAddress("varKaonMaxVELOChi2ndof_log", &varKaonMaxVELOChi2ndof_log, &b_varKaonMaxVELOChi2ndof_log);
   fChain->SetBranchAddress("varPiplusOneVELOChi2ndof", &varPiplusOneVELOChi2ndof, &b_varPiplusOneVELOChi2ndof);
   fChain->SetBranchAddress("varPiplusTwoVELOChi2ndof", &varPiplusTwoVELOChi2ndof, &b_varPiplusTwoVELOChi2ndof);
   fChain->SetBranchAddress("varPiplusMinVELOChi2ndof", &varPiplusMinVELOChi2ndof, &b_varPiplusMinVELOChi2ndof);
   fChain->SetBranchAddress("varPiplusMaxVELOChi2ndof", &varPiplusMaxVELOChi2ndof, &b_varPiplusMaxVELOChi2ndof);
   fChain->SetBranchAddress("varPiminusOneVELOChi2ndof", &varPiminusOneVELOChi2ndof, &b_varPiminusOneVELOChi2ndof);
   fChain->SetBranchAddress("varPiminusTwoVELOChi2ndof", &varPiminusTwoVELOChi2ndof, &b_varPiminusTwoVELOChi2ndof);
   fChain->SetBranchAddress("varPiminusMinVELOChi2ndof", &varPiminusMinVELOChi2ndof, &b_varPiminusMinVELOChi2ndof);
   fChain->SetBranchAddress("varPionMinVELOChi2ndof", &varPionMinVELOChi2ndof, &b_varPionMinVELOChi2ndof);
   fChain->SetBranchAddress("varPionMinVELOChi2ndof_log", &varPionMinVELOChi2ndof_log, &b_varPionMinVELOChi2ndof_log);
   fChain->SetBranchAddress("varPiminusMaxVELOChi2ndof", &varPiminusMaxVELOChi2ndof, &b_varPiminusMaxVELOChi2ndof);
   fChain->SetBranchAddress("varPionMaxVELOChi2ndof", &varPionMaxVELOChi2ndof, &b_varPionMaxVELOChi2ndof);
   fChain->SetBranchAddress("varPionMaxVELOChi2ndof_log", &varPionMaxVELOChi2ndof_log, &b_varPionMaxVELOChi2ndof_log);
   fChain->SetBranchAddress("varHadronMinVELOChi2ndof", &varHadronMinVELOChi2ndof, &b_varHadronMinVELOChi2ndof);
   fChain->SetBranchAddress("varHadronMinVELOChi2ndof_log", &varHadronMinVELOChi2ndof_log, &b_varHadronMinVELOChi2ndof_log);
   fChain->SetBranchAddress("varHadronMaxVELOChi2ndof", &varHadronMaxVELOChi2ndof, &b_varHadronMaxVELOChi2ndof);
   fChain->SetBranchAddress("varHadronMaxVELOChi2ndof_log", &varHadronMaxVELOChi2ndof_log, &b_varHadronMaxVELOChi2ndof_log);
   fChain->SetBranchAddress("varKminusTChi2ndof", &varKminusTChi2ndof, &b_varKminusTChi2ndof);
   fChain->SetBranchAddress("varKplusTChi2ndof", &varKplusTChi2ndof, &b_varKplusTChi2ndof);
   fChain->SetBranchAddress("varKaonMinTChi2ndof", &varKaonMinTChi2ndof, &b_varKaonMinTChi2ndof);
   fChain->SetBranchAddress("varKaonMinTChi2ndof_log", &varKaonMinTChi2ndof_log, &b_varKaonMinTChi2ndof_log);
   fChain->SetBranchAddress("varKaonMaxTChi2ndof", &varKaonMaxTChi2ndof, &b_varKaonMaxTChi2ndof);
   fChain->SetBranchAddress("varKaonMaxTChi2ndof_log", &varKaonMaxTChi2ndof_log, &b_varKaonMaxTChi2ndof_log);
   fChain->SetBranchAddress("varPiplusOneTChi2ndof", &varPiplusOneTChi2ndof, &b_varPiplusOneTChi2ndof);
   fChain->SetBranchAddress("varPiplusTwoTChi2ndof", &varPiplusTwoTChi2ndof, &b_varPiplusTwoTChi2ndof);
   fChain->SetBranchAddress("varPiplusMinTChi2ndof", &varPiplusMinTChi2ndof, &b_varPiplusMinTChi2ndof);
   fChain->SetBranchAddress("varPiplusMaxTChi2ndof", &varPiplusMaxTChi2ndof, &b_varPiplusMaxTChi2ndof);
   fChain->SetBranchAddress("varPiminusOneTChi2ndof", &varPiminusOneTChi2ndof, &b_varPiminusOneTChi2ndof);
   fChain->SetBranchAddress("varPiminusTwoTChi2ndof", &varPiminusTwoTChi2ndof, &b_varPiminusTwoTChi2ndof);
   fChain->SetBranchAddress("varPiminusMinTChi2ndof", &varPiminusMinTChi2ndof, &b_varPiminusMinTChi2ndof);
   fChain->SetBranchAddress("varPionMinTChi2ndof", &varPionMinTChi2ndof, &b_varPionMinTChi2ndof);
   fChain->SetBranchAddress("varPionMinTChi2ndof_log", &varPionMinTChi2ndof_log, &b_varPionMinTChi2ndof_log);
   fChain->SetBranchAddress("varPiminusMaxTChi2ndof", &varPiminusMaxTChi2ndof, &b_varPiminusMaxTChi2ndof);
   fChain->SetBranchAddress("varPionMaxTChi2ndof", &varPionMaxTChi2ndof, &b_varPionMaxTChi2ndof);
   fChain->SetBranchAddress("varPionMaxTChi2ndof_log", &varPionMaxTChi2ndof_log, &b_varPionMaxTChi2ndof_log);
   fChain->SetBranchAddress("varHadronMinTChi2ndof", &varHadronMinTChi2ndof, &b_varHadronMinTChi2ndof);
   fChain->SetBranchAddress("varHadronMinTChi2ndof_log", &varHadronMinTChi2ndof_log, &b_varHadronMinTChi2ndof_log);
   fChain->SetBranchAddress("varHadronMaxTChi2ndof", &varHadronMaxTChi2ndof, &b_varHadronMaxTChi2ndof);
   fChain->SetBranchAddress("varHadronMaxTChi2ndof_log", &varHadronMaxTChi2ndof_log, &b_varHadronMaxTChi2ndof_log);
   fChain->SetBranchAddress("varKminusMatchChi2", &varKminusMatchChi2, &b_varKminusMatchChi2);
   fChain->SetBranchAddress("varKplusMatchChi2", &varKplusMatchChi2, &b_varKplusMatchChi2);
   fChain->SetBranchAddress("varKaonMinMatchChi2", &varKaonMinMatchChi2, &b_varKaonMinMatchChi2);
   fChain->SetBranchAddress("varKaonMinMatchChi2_log", &varKaonMinMatchChi2_log, &b_varKaonMinMatchChi2_log);
   fChain->SetBranchAddress("varKaonMaxMatchChi2", &varKaonMaxMatchChi2, &b_varKaonMaxMatchChi2);
   fChain->SetBranchAddress("varKaonMaxMatchChi2_log", &varKaonMaxMatchChi2_log, &b_varKaonMaxMatchChi2_log);
   fChain->SetBranchAddress("varPiplusOneMatchChi2", &varPiplusOneMatchChi2, &b_varPiplusOneMatchChi2);
   fChain->SetBranchAddress("varPiplusTwoMatchChi2", &varPiplusTwoMatchChi2, &b_varPiplusTwoMatchChi2);
   fChain->SetBranchAddress("varPiplusMinMatchChi2", &varPiplusMinMatchChi2, &b_varPiplusMinMatchChi2);
   fChain->SetBranchAddress("varPiplusMaxMatchChi2", &varPiplusMaxMatchChi2, &b_varPiplusMaxMatchChi2);
   fChain->SetBranchAddress("varPiminusOneMatchChi2", &varPiminusOneMatchChi2, &b_varPiminusOneMatchChi2);
   fChain->SetBranchAddress("varPiminusTwoMatchChi2", &varPiminusTwoMatchChi2, &b_varPiminusTwoMatchChi2);
   fChain->SetBranchAddress("varPiminusMinMatchChi2", &varPiminusMinMatchChi2, &b_varPiminusMinMatchChi2);
   fChain->SetBranchAddress("varPionMinMatchChi2", &varPionMinMatchChi2, &b_varPionMinMatchChi2);
   fChain->SetBranchAddress("varPionMinMatchChi2_log", &varPionMinMatchChi2_log, &b_varPionMinMatchChi2_log);
   fChain->SetBranchAddress("varPiminusMaxMatchChi2", &varPiminusMaxMatchChi2, &b_varPiminusMaxMatchChi2);
   fChain->SetBranchAddress("varPionMaxMatchChi2", &varPionMaxMatchChi2, &b_varPionMaxMatchChi2);
   fChain->SetBranchAddress("varPionMaxMatchChi2_log", &varPionMaxMatchChi2_log, &b_varPionMaxMatchChi2_log);
   fChain->SetBranchAddress("varHadronMinMatchChi2", &varHadronMinMatchChi2, &b_varHadronMinMatchChi2);
   fChain->SetBranchAddress("varHadronMinMatchChi2_log", &varHadronMinMatchChi2_log, &b_varHadronMinMatchChi2_log);
   fChain->SetBranchAddress("varHadronMaxMatchChi2", &varHadronMaxMatchChi2, &b_varHadronMaxMatchChi2);
   fChain->SetBranchAddress("varHadronMaxMatchChi2_log", &varHadronMaxMatchChi2_log, &b_varHadronMaxMatchChi2_log);
   fChain->SetBranchAddress("catTriggerL0GlobalTOS", &catTriggerL0GlobalTOS, &b_catTriggerL0GlobalTOS);
   fChain->SetBranchAddress("catTriggerHlt1GlobalTOS", &catTriggerHlt1GlobalTOS, &b_catTriggerHlt1GlobalTOS);
   fChain->SetBranchAddress("catTriggerHlt2GlobalTOS", &catTriggerHlt2GlobalTOS, &b_catTriggerHlt2GlobalTOS);
   fChain->SetBranchAddress("catTriggerHlt2Topo2BodyBBDTTOS", &catTriggerHlt2Topo2BodyBBDTTOS, &b_catTriggerHlt2Topo2BodyBBDTTOS);
   fChain->SetBranchAddress("catTriggerHlt2Topo3BodyBBDTTOS", &catTriggerHlt2Topo3BodyBBDTTOS, &b_catTriggerHlt2Topo3BodyBBDTTOS);
   fChain->SetBranchAddress("catTriggerHlt2Topo4BodyBBDTTOS", &catTriggerHlt2Topo4BodyBBDTTOS, &b_catTriggerHlt2Topo4BodyBBDTTOS);
   fChain->SetBranchAddress("catTriggerHlt2IncPhiTOS", &catTriggerHlt2IncPhiTOS, &b_catTriggerHlt2IncPhiTOS);
   fChain->SetBranchAddress("catTriggerSetTopo234BodyBBDT", &catTriggerSetTopo234BodyBBDT, &b_catTriggerSetTopo234BodyBBDT);
   fChain->SetBranchAddress("idxRandom", &idxRandom, &b_idxRandom);
   fChain->SetBranchAddress("catDplusFinalState", &catDplusFinalState, &b_catDplusFinalState);
   fChain->SetBranchAddress("catDminusFinalState", &catDminusFinalState, &b_catDminusFinalState);
   fChain->SetBranchAddress("catDDFinalState", &catDDFinalState, &b_catDDFinalState);
   fChain->SetBranchAddress("idxEventNumber", &idxEventNumber, &b_idxEventNumber);
   fChain->SetBranchAddress("idxRunNumber", &idxRunNumber, &b_idxRunNumber);
   fChain->SetBranchAddress("catNPV", &catNPV, &b_catNPV);
   fChain->SetBranchAddress("catMag", &catMag, &b_catMag);
   fChain->SetBranchAddress("catNTrack", &catNTrack, &b_catNTrack);
   fChain->SetBranchAddress("catYear", &catYear, &b_catYear);
   fChain->SetBranchAddress("varDTFStatusPVConst", &varDTFStatusPVConst, &b_varDTFStatusPVConst);
   fChain->SetBranchAddress("varDTFStatusDDPVConst", &varDTFStatusDDPVConst, &b_varDTFStatusDDPVConst);
   fChain->SetBranchAddress("varDTFChi2ndof_log_tmvafloatcopy", &varDTFChi2ndof_log_tmvafloatcopy, &b_varDTFChi2ndof_log_tmvafloatcopy);
   fChain->SetBranchAddress("varBEndVtxChi2ndof_log_tmvafloatcopy", &varBEndVtxChi2ndof_log_tmvafloatcopy, &b_varBEndVtxChi2ndof_log_tmvafloatcopy);
   fChain->SetBranchAddress("varIPChi2_log_tmvafloatcopy", &varIPChi2_log_tmvafloatcopy, &b_varIPChi2_log_tmvafloatcopy);
   fChain->SetBranchAddress("varBDIRAOwnPV_tmvafloatcopy", &varBDIRAOwnPV_tmvafloatcopy, &b_varBDIRAOwnPV_tmvafloatcopy);
   fChain->SetBranchAddress("varDMinTauSignificance_tmvafloatcopy", &varDMinTauSignificance_tmvafloatcopy, &b_varDMinTauSignificance_tmvafloatcopy);
   fChain->SetBranchAddress("varDMinPT_tmvafloatcopy", &varDMinPT_tmvafloatcopy, &b_varDMinPT_tmvafloatcopy);
   fChain->SetBranchAddress("varDDDTFSumPT_tmvafloatcopy", &varDDDTFSumPT_tmvafloatcopy, &b_varDDDTFSumPT_tmvafloatcopy);
   fChain->SetBranchAddress("varKaonMinPT_tmvafloatcopy", &varKaonMinPT_tmvafloatcopy, &b_varKaonMinPT_tmvafloatcopy);
   fChain->SetBranchAddress("varPionOneMinPT_tmvafloatcopy", &varPionOneMinPT_tmvafloatcopy, &b_varPionOneMinPT_tmvafloatcopy);
   fChain->SetBranchAddress("varPionTwoMinPT_tmvafloatcopy", &varPionTwoMinPT_tmvafloatcopy, &b_varPionTwoMinPT_tmvafloatcopy);
   fChain->SetBranchAddress("varPVVtxChi2ndof_log_tmvafloatcopy", &varPVVtxChi2ndof_log_tmvafloatcopy, &b_varPVVtxChi2ndof_log_tmvafloatcopy);
   fChain->SetBranchAddress("varKaonMinVELOChi2ndof_log_tmvafloatcopy", &varKaonMinVELOChi2ndof_log_tmvafloatcopy, &b_varKaonMinVELOChi2ndof_log_tmvafloatcopy);
   fChain->SetBranchAddress("varKaonMinTChi2ndof_log_tmvafloatcopy", &varKaonMinTChi2ndof_log_tmvafloatcopy, &b_varKaonMinTChi2ndof_log_tmvafloatcopy);
   fChain->SetBranchAddress("varKaonMinMatchChi2_log_tmvafloatcopy", &varKaonMinMatchChi2_log_tmvafloatcopy, &b_varKaonMinMatchChi2_log_tmvafloatcopy);
   fChain->SetBranchAddress("varPionMinVELOChi2ndof_log_tmvafloatcopy", &varPionMinVELOChi2ndof_log_tmvafloatcopy, &b_varPionMinVELOChi2ndof_log_tmvafloatcopy);
   fChain->SetBranchAddress("varPionMinTChi2ndof_log_tmvafloatcopy", &varPionMinTChi2ndof_log_tmvafloatcopy, &b_varPionMinTChi2ndof_log_tmvafloatcopy);
   fChain->SetBranchAddress("varPionMinMatchChi2_log_tmvafloatcopy", &varPionMinMatchChi2_log_tmvafloatcopy, &b_varPionMinMatchChi2_log_tmvafloatcopy);
   fChain->SetBranchAddress("BDT1_classifier", &BDT1_classifier, &b_BDT1_classifier);
   fChain->SetBranchAddress("BDT2_classifier", &BDT2_classifier, &b_BDT2_classifier);
   fChain->SetBranchAddress("BDTG1_classifier", &BDTG1_classifier, &b_BDTG1_classifier);
   fChain->SetBranchAddress("BDTG2_classifier", &BDTG2_classifier, &b_BDTG2_classifier);
   Notify();
}

Bool_t b2dd::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void b2dd::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t b2dd::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef b2dd_cxx
