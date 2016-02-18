#include <iostream>
#include <sstream>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"

#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooArgSet.h"

#include "doocore/io/MsgStream.h"
#include "doocore/config/EasyConfig.h"

using namespace std;
using namespace RooFit;
using namespace doocore::io;

int main(int argc, const char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  bool MC = config.getBool("MC");

  TFile* TupleA = new TFile(TString(config.getString("tuple")),"READ");
  TTree* TreeA = (TTree*)TupleA->Get(TString(config.getString("tree")));
  
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

  cout << "Count number of candidates fulfilling normalisation condition" <<  endl;

  double normalisation_entries_Kpipi = TreeA->GetEntries(normalisation_condition_Kpipi);
  double normalisation_entries_KKpi  = TreeA->GetEntries(normalisation_condition_KKpi);

  cout << "There are " <<  normalisation_entries_Kpipi << " candidates for the Kpipi normalisation" << endl;
  cout << "There are " <<  normalisation_entries_KKpi << " candidates for the KKpi normalisation" << endl;
  cout << "Calculating preselection efficiency" <<  endl;

  double efficiency_preselection_Kpipi = TreeA->GetEntries(TString(config.getString("preselection")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
  double efficiency_preselection_KKpi  = TreeA->GetEntries(TString(config.getString("preselection")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;
  if (!MC) {
    efficiency_preselection_Kpipi = 1. - efficiency_preselection_Kpipi;
    efficiency_preselection_KKpi  = 1. - efficiency_preselection_KKpi;
  }

  cout << "Calculating PID ratio efficiency" <<  endl;

  double efficiency_pidratio_Kpipi = TreeA->GetEntries(TString(config.getString("pidratio_Kpipi")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
  double efficiency_pidratio_KKpi  = TreeA->GetEntries(TString(config.getString("pidratio_KKpi")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;
  if (!MC) {
    efficiency_pidratio_Kpipi = 1. - efficiency_pidratio_Kpipi;
    efficiency_pidratio_KKpi  = 1. - efficiency_pidratio_KKpi;
  }  

  cout << "Calculating veto efficiency" <<  endl;

  double efficiency_vetos_Kpipi = TreeA->GetEntries(TString(config.getString("vetos_Kpipi")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
  double efficiency_vetos_KKpi = TreeA->GetEntries(TString(config.getString("vetos_KKpi")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;
  if (!MC) {
    efficiency_vetos_Kpipi = 1. - efficiency_vetos_Kpipi;
    efficiency_vetos_KKpi  = 1. - efficiency_vetos_KKpi;
  }  

  // double efficiency_preselection_and_pidratio_and_vetos_Kpipi = TreeA->GetEntries(TString(config.getString("vetos_Kpipi")+"&&"+config.getString("pidratio_Kpipi")+"&&"+config.getString("preselection")+"&&"+normalisation_condition_Kpipi))/normalisation_entries_Kpipi;
  // double efficiency_preselection_and_pidratio_and_vetos_KKpi = TreeA->GetEntries(TString(config.getString("vetos_KKpi")+"&&"+config.getString("pidratio_KKpi")+"&&"+config.getString("preselection")+"&&"+normalisation_condition_KKpi))/normalisation_entries_KKpi;

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

  return 0;
}