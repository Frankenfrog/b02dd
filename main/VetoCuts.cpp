#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"

//from RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooSuperCategory.h"
#include "RooDataHist.h"
#include "RooConstVar.h"
#include "RooBinning.h"
#include "RooProduct.h"
#include "RooMsgService.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;

void ChangeHistogramSettings(TH1* histogram);
TH1D LambdaHist(TTree* tree, bool veto);
TH1D DsHist(TTree* tree, bool veto);
TH1D PhiHist(TTree* tree, bool veto);

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  gStyle->SetTitleOffset(1.15,"Y");
  gStyle->SetPadLeftMargin(0.16);
  TCanvas c("c","c",800,600);

  // Get data set
  TFile* tuple_kpipi = new TFile(TString(config.getString("tuple_kpipi")),"READ");
  TTree* tree_kpipi = dynamic_cast<TTree*>(tuple_kpipi->Get("B02DD"));
  TFile* tuple_kkpi = new TFile(TString(config.getString("tuple_kkpi")),"READ");
  TTree* tree_kkpi = dynamic_cast<TTree*>(tuple_kkpi->Get("B02DD"));

  TH1D hist_lambda_before("hist_lambda_before","hist_lambda_before",150,2100,2400);
  TH1D hist_lambda_before_kpipi = LambdaHist(tree_kpipi, false);
  TH1D hist_lambda_before_kkpi = LambdaHist(tree_kkpi, false);
  
  TH1D hist_lambda_after("hist_lambda_after","hist_lambda_after",150,2100,2400);
  TH1D hist_lambda_after_kpipi = LambdaHist(tree_kpipi, true);
  TH1D hist_lambda_after_kkpi = LambdaHist(tree_kkpi, true);

  hist_lambda_before.Add(&hist_lambda_before_kpipi,&hist_lambda_before_kkpi);
  hist_lambda_after.Add(&hist_lambda_after_kpipi,&hist_lambda_after_kkpi);

  hist_lambda_before.GetYaxis()->SetTitle("Candidates / (2 MeV/c^{2})");
  hist_lambda_before.GetXaxis()->SetTitle("#it{m_{K#pi p}} (MeV/c^{2})");
  hist_lambda_before.SetMinimum(0);
  hist_lambda_before.Draw();
  hist_lambda_after.SetLineColor(2);
  hist_lambda_after.Draw("same");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/Selection/LambdaVeto.pdf");

  TH1D hist_Ds_before("hist_Ds_before","hist_Ds_before",100,1900,2000);
  TH1D hist_Ds_before_kpipi = DsHist(tree_kpipi, false);
  TH1D hist_Ds_before_kkpi = DsHist(tree_kkpi, false);

  TH1D hist_Ds_after("hist_Ds_after","hist_Ds_after",100,1900,2000);
  TH1D hist_Ds_after_kpipi = DsHist(tree_kpipi, true);
  TH1D hist_Ds_after_kkpi = DsHist(tree_kkpi, true);

  hist_Ds_before.Add(&hist_Ds_before_kpipi,&hist_Ds_before_kkpi);
  hist_Ds_after.Add(&hist_Ds_after_kpipi,&hist_Ds_after_kkpi);

  hist_Ds_before.GetYaxis()->SetTitle("Candidates / (1 MeV/c^{2})");
  hist_Ds_before.GetXaxis()->SetTitle("#it{m_{K#pi K}} (MeV/c^{2})");
  hist_Ds_before.SetMinimum(0);
  hist_Ds_before.Draw();
  hist_Ds_after.SetLineColor(2);
  hist_Ds_after.Draw("same");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/Selection/DsVeto.pdf");

  gStyle->SetTitleOffset(1.00,"Y");
  gStyle->SetPadLeftMargin(0.14);

  TH1D hist_Phi_before("hist_Phi_before","hist_Phi_before",100,1000,1100);
  TH1D hist_Phi_before_kpipi = PhiHist(tree_kpipi, false);
  TH1D hist_Phi_before_kkpi = PhiHist(tree_kkpi, false);

  TH1D hist_Phi_after("hist_Phi_after","hist_Phi_after",100,1000,1100);
  TH1D hist_Phi_after_kpipi = PhiHist(tree_kpipi, true);
  TH1D hist_Phi_after_kkpi = PhiHist(tree_kkpi, true);

  hist_Phi_before.Add(&hist_Phi_before_kpipi,&hist_Phi_before_kkpi);
  hist_Phi_after.Add(&hist_Phi_after_kpipi,&hist_Phi_after_kkpi);

  hist_Phi_before.GetYaxis()->SetTitle("Candidates / (1 MeV/c^{2})");
  hist_Phi_before.GetXaxis()->SetTitle("#it{m_{K^{+}K^{-}}} (MeV/c^{2})");
  hist_Phi_before.SetMinimum(0);
  hist_Phi_before.Draw();
  hist_Phi_after.SetLineColor(2);
  hist_Phi_after.Draw("same");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/Selection/PhiVeto.pdf");

  return 0;
}

void ChangeHistogramSettings(TH1* histogram){
  histogram->GetYaxis()->SetTitle("");
  histogram->SetMinimum(0);
  histogram->SetMaximum(10);
}

TH1D LambdaHist(TTree* tree, bool veto){
  TH1D hist_lambda("hist_lambda","hist_lambda",150,2100,2400);
  TH1D hist_lambda_dplus("hist_lambda_dplus","hist_lambda_dplus",150,2100,2400);
  TH1D hist_lambda_dminus("hist_lambda_dminus","hist_lambda_dminus",150,2100,2400);
  if (veto) {
    tree->Draw("varDminusMassHypo_Kpip>>hist_lambda_dminus","catDminusFinalState==1&&!(abs(varDminusMassHypo_Kpip-2286.46)<25&&varPiTwominus_PIDp>0.5)");
    tree->Draw("varDplusMassHypo_Kpip>>hist_lambda_dplus","catDplusFinalState==1&&!(abs(varDplusMassHypo_Kpip-2286.46)<25&&varPiTwoplus_PIDp>0.5)");
  }
  else {
    tree->Draw("varDplusMassHypo_Kpip>>hist_lambda_dplus","catDplusFinalState==1");
    tree->Draw("varDminusMassHypo_Kpip>>hist_lambda_dminus","catDminusFinalState==1");
  }
  hist_lambda.Add(&hist_lambda_dplus,&hist_lambda_dminus);
  return hist_lambda;
}

TH1D DsHist(TTree* tree, bool veto){
  TH1D hist_Ds("hist_Ds","hist_Ds",100,1900,2000);
  TH1D hist_Ds_dplus("hist_Ds_dplus","hist_Ds_dplus",100,1900,2000);
  TH1D hist_Ds_dminus("hist_Ds_dminus","hist_Ds_dminus",100,1900,2000);
  if (veto) {
    tree->Draw("varDminusMassHypo_KpiK>>hist_Ds_dminus","catDminusFinalState==1&&!(abs(varDminusMassHypo_KpiK-1968.3)<25&&varPiTwominus_PID>0.5)&&abs(varPhiMassHypo_DminusTwo-1019.461)>10");
    tree->Draw("varDplusMassHypo_KpiK>>hist_Ds_dplus","catDplusFinalState==1&&!(abs(varDplusMassHypo_KpiK-1968.3)<25&&varPiTwoplus_PID>0.5)&&abs(varPhiMassHypo_DplusTwo-1019.461)>10");
  }
  else {
    tree->Draw("varDplusMassHypo_KpiK>>hist_Ds_dplus","catDplusFinalState==1");
    tree->Draw("varDminusMassHypo_KpiK>>hist_Ds_dminus","catDminusFinalState==1");
  }
  hist_Ds.Add(&hist_Ds_dplus,&hist_Ds_dminus);
  return hist_Ds;
}

TH1D PhiHist(TTree* tree, bool veto){
  TH1D hist_Phi("hist_Phi","hist_Phi",100,1000,1100);
  TH1D hist_Phi_dplus("hist_Phi_dplus","hist_Phi_dplus",100,1000,1100);
  TH1D hist_Phi_dminus("hist_Phi_dminus","hist_Phi_dminus",100,1000,1100);
  if (veto) {
    tree->Draw("varPhiMassHypo_DminusTwo>>hist_Phi_dminus","catDminusFinalState==1&&abs(varPhiMassHypo_DminusTwo-1019.461)>10");
    tree->Draw("varPhiMassHypo_DplusTwo>>hist_Phi_dplus","catDplusFinalState==1&&abs(varPhiMassHypo_DplusTwo-1019.461)>10");
  }
  else {
    tree->Draw("varPhiMassHypo_DplusTwo>>hist_Phi_dplus","catDplusFinalState==1");
    tree->Draw("varPhiMassHypo_DminusTwo>>hist_Phi_dminus","catDminusFinalState==1");
  }
  hist_Phi.Add(&hist_Phi_dplus,&hist_Phi_dminus);
  return hist_Phi;
}