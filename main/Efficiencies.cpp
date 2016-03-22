#include <iostream>
#include <sstream>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStyle.h"

#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooArgSet.h"

#include "doocore/io/MsgStream.h"
#include "doocore/config/EasyConfig.h"
#include "doocore/lutils/lutils.h"

using namespace std;
using namespace RooFit;
using namespace doocore::io;
using namespace doocore::lutils;

void PlotHist(TTree* tree_kpipi, TTree* tree_kkpi, TString cut, TString name);

int main(int argc, const char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  bool MC = config.getBool("MC");

  TFile* Tuple_Kpipi = new TFile(TString(config.getString("tuple_kpipi")),"READ");
  TTree* Tree_Kpipi = (TTree*)Tuple_Kpipi->Get(TString(config.getString("tree")));
  TFile* Tuple_KKpi = new TFile(TString(config.getString("tuple_kkpi")),"READ");
  TTree* Tree_KKpi = (TTree*)Tuple_KKpi->Get(TString(config.getString("tree")));
  
  TString normalisation_condition_Kpipi = "catDDFinalStateParticles==1";
  TString normalisation_condition_KKpi = "catDDFinalStateParticles==0";
  if (MC) {
    normalisation_condition_Kpipi += "&&catBkg==0&&idxPV==0";
    normalisation_condition_KKpi  += "&&catBkg==0&&idxPV==0";
  }
  else {
    normalisation_condition_Kpipi += "&&obsMass>5000&&obsMass<5500";
    normalisation_condition_KKpi  += "&&obsMass>5000&&obsMass<5500";
  }

  if (config.getBool("plots")) {
    if (config.getBool("BDT")) {
      TString inverted_bdt_cut = "((catDDFinalState==11&&BDT_wPIDs_Kpipi_classifier<-0.1)||(catDDFinalStateParticles==0&&BDT_wPIDs_KKpi_classifier<0.01))";
      PlotHist(Tree_Kpipi, Tree_KKpi, inverted_bdt_cut, "Rejected_by_BDT");
    }
    else {
      TString preselection_cut = "!("+config.getString("preselection")+")";
      PlotHist(Tree_Kpipi, Tree_KKpi, preselection_cut, "Rejected_by_Preselection");
      TString veto_cut = "!("+config.getString("vetos")+")";
      PlotHist(Tree_Kpipi, Tree_KKpi, veto_cut, "Rejected_by_MassVetos");
    }
  }
  else {
    cout << "Count number of candidates fulfilling normalisation condition" <<  endl;

    double normalisation_entries_Kpipi = Tree_Kpipi->GetEntries(normalisation_condition_Kpipi);
    double normalisation_entries_KKpi  = Tree_KKpi->GetEntries(normalisation_condition_KKpi);
  
    cout << "There are " <<  normalisation_entries_Kpipi << " candidates for the Kpipi normalisation" << endl;
    cout << "There are " <<  normalisation_entries_KKpi << " candidates for the KKpi normalisation" << endl;
    cout << "Calculating preselection efficiency" <<  endl;
  
    double efficiency_preselection_Kpipi = Tree_Kpipi->GetEntries(TString(config.getString("preselection")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
    double efficiency_preselection_KKpi  = Tree_KKpi->GetEntries(TString(config.getString("preselection")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;
    if (!MC) {
      efficiency_preselection_Kpipi = 1. - efficiency_preselection_Kpipi;
      efficiency_preselection_KKpi  = 1. - efficiency_preselection_KKpi;
    }
  
    cout << "Calculating PID ratio efficiency" <<  endl;
  
    double efficiency_pidratio_Kpipi = Tree_Kpipi->GetEntries(TString(config.getString("pidratio_Kpipi")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
    double efficiency_pidratio_KKpi  = Tree_KKpi->GetEntries(TString(config.getString("pidratio_KKpi")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;
    if (!MC) {
      efficiency_pidratio_Kpipi = 1. - efficiency_pidratio_Kpipi;
      efficiency_pidratio_KKpi  = 1. - efficiency_pidratio_KKpi;
    }  

    cout << "Calculating veto efficiency" <<  endl;
  
    double efficiency_vetos_Kpipi = Tree_Kpipi->GetEntries(TString(config.getString("vetos")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
    double efficiency_vetos_KKpi = Tree_KKpi->GetEntries(TString(config.getString("vetos")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;
    if (!MC) {
      efficiency_vetos_Kpipi = 1. - efficiency_vetos_Kpipi;
      efficiency_vetos_KKpi  = 1. - efficiency_vetos_KKpi;
    }  
  
    // double efficiency_preselection_and_pidratio_and_vetos_Kpipi = Tree_Kpipi->GetEntries(TString(config.getString("vetos")+"&&"+config.getString("pidratio_Kpipi")+"&&"+config.getString("preselection")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
    // double efficiency_preselection_and_pidratio_and_vetos_KKpi = Tree_KKpi->GetEntries(TString(config.getString("vetos")+"&&"+config.getString("pidratio_KKpi")+"&&"+config.getString("preselection")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;
  
    // if (!MC) {
    //   efficiency_preselection_and_pidratio_and_vetos_Kpipi = 1. - efficiency_preselection_and_pidratio_and_vetos_Kpipi;
    //   efficiency_preselection_and_pidratio_and_vetos_KKpi  = 1. - efficiency_preselection_and_pidratio_and_vetos_KKpi;
    // }
  
    cout  <<  "Preselection (Kpipi): "  <<  100*efficiency_preselection_Kpipi <<  " pm "  <<  100*sqrt(efficiency_preselection_Kpipi*(1 - efficiency_preselection_Kpipi)/normalisation_entries_Kpipi) <<  endl;
    cout  <<  "PID ratio (Kpipi): "  <<  100*efficiency_pidratio_Kpipi <<  " pm "  <<  100*sqrt(efficiency_pidratio_Kpipi*(1 - efficiency_pidratio_Kpipi)/normalisation_entries_Kpipi) <<  endl;
    cout  <<  "Vetos (Kpipi): "  <<  100*efficiency_vetos_Kpipi <<  " pm "  <<  100*sqrt(efficiency_vetos_Kpipi*(1 - efficiency_vetos_Kpipi)/normalisation_entries_Kpipi) <<  endl;
    // cout  <<  "Total (Kpipi): "  <<  95*efficiency_preselection_and_pidratio_and_vetos_Kpipi <<  " pm "  <<  100*sqrt(0.95*efficiency_vetos_Kpipi*(1 - 0.95*efficiency_vetos_Kpipi)/normalisation_entries_Kpipi) <<  endl;
  
    cout  <<  "Preselection (KKpi): "  <<  100*efficiency_preselection_KKpi <<  " pm "  <<  100*sqrt(efficiency_preselection_KKpi*(1 - efficiency_preselection_KKpi)/normalisation_entries_KKpi) <<  endl;
    cout  <<  "PID ratio (KKpi): "  <<  100*efficiency_pidratio_KKpi <<  " pm "  <<  100*sqrt(efficiency_pidratio_KKpi*(1 - efficiency_pidratio_KKpi)/normalisation_entries_KKpi) <<  endl;
    cout  <<  "Vetos (KKpi): "  <<  100*efficiency_vetos_KKpi <<  " pm "  <<  100*sqrt(efficiency_vetos_KKpi*(1 - efficiency_vetos_KKpi)/normalisation_entries_KKpi) <<  endl;
    // cout  <<  "Total (KKpi): "  <<  95*efficiency_preselection_and_pidratio_and_vetos_KKpi <<  " pm "  <<  100*sqrt(0.95*efficiency_vetos_KKpi*(1 - 0.95*efficiency_vetos_KKpi)/normalisation_entries_KKpi) <<  endl;
  }

  return 0;
}

void PlotHist(TTree* tree_kpipi, TTree* tree_kkpi, TString cut, TString name){
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  gStyle->SetTitleOffset(1.15,"Y");
  gStyle->SetPadLeftMargin(0.16);
  TCanvas c("c","c",800,600);
  TH1D hist("hist","hist",100,5000,5500);
  TH1D hist_Kpipi("hist_Kpipi","hist_Kpipi",100,5000,5500);
  TH1D hist_KKpi("hist_KKpi","hist_KKpi",100,5000,5500);
  tree_kpipi->Draw("obsMass>>hist_Kpipi",cut);
  tree_kkpi->Draw("obsMass>>hist_KKpi",cut);
  hist.Add(&hist_Kpipi,&hist_KKpi);
  hist.GetYaxis()->SetTitle("Candidates / (5 MeV/c^{2})");
  hist.GetXaxis()->SetTitle("#it{m_{D^{+}D^{-}}} (MeV/c^{2})");
  hist.SetMinimum(0);
  hist.Draw();
  c.SaveAs("/home/fmeier/storage03/b02dd/run/Selection/"+name+".pdf");
}