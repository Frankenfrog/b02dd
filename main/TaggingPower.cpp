#include <iostream>
#include <sstream>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"

#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooCategory.h"
#include "RooArgSet.h"

#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/config/EasyConfig.h"

using namespace std;
using namespace RooFit;
using namespace doocore::io;

void NewTaggingPowerCalculation(double total_signal_events, RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double deltap0_OS, double deltap1_OS, double p0_SS, double p1_SS, double etamean_SS, double deltap0_SS, double deltap1_SS, double p0error_OS, double p1error_OS, double p0error_SS, double p1error_SS, TString identifier);

int main(int argc, const char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  RooCategory       obsTagOS("obsTagOSwCharm","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  obsTagOS.defineType("no Tag",0);
  RooCategory       obsTagSS("obsTagSS","Flavour Tag");
  obsTagSS.defineType("B0",1);
  obsTagSS.defineType("B0bar",-1);
  obsTagSS.defineType("no Tag",0);
  RooRealVar        obsEtaOS("obsEtaOSwCharm","#eta_{OS}",0,0.5);
  RooRealVar        obsEtaSS("obsEtaSS","#eta_{SS}",0,0.5);
  RooRealVar        weight("SigWeight","Signal weight",-10,10);
  
  RooArgSet         observables(obsTagOS,obsTagSS,weight,obsEtaOS,obsEtaSS,"observables");
   
  EasyTuple         sweighted_tuple(config.getString("tuple"),"B02DD",observables);
  sweighted_tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       signaldata = sweighted_tuple.ConvertToDataSet(WeightVar("SigWeight"));
  signaldata.Print();
  
  RooDataSet        signaldata_OS("signaldata_OS","signaldata_OS",observables,Import(signaldata),Cut("abs(obsTagOSwCharm)==1&&abs(obsTagSS)==0"),WeightVar("SigWeight"));
  signaldata_OS.Print();
  RooDataSet        signaldata_SS("signaldata_SS","signaldata_SS",observables,Import(signaldata),Cut("abs(obsTagOSwCharm)==0&&abs(obsTagSS)==1"),WeightVar("SigWeight"));
  signaldata_SS.Print();
  RooDataSet        signaldata_BS("signaldata_BS","signaldata_BS",observables,Import(signaldata),Cut("abs(obsTagOSwCharm)==1&&abs(obsTagSS)==1"),WeightVar("SigWeight"));
  signaldata_BS.Print();
  RooDataSet        signaldata_allOS("signaldata_allOS","signaldata_allOS",observables,Import(signaldata),Cut("abs(obsTagOSwCharm)==1"),WeightVar("SigWeight"));
  RooDataSet        signaldata_allSS("signaldata_allSS","signaldata_allSS",observables,Import(signaldata),Cut("abs(obsTagSS)==1"),WeightVar("SigWeight"));

  double            mean_mistag_OS = signaldata_allOS.mean(obsEtaOS);
  double            mean_mistag_OS_error = 1./sqrt(signaldata_allOS.sumEntries());
  cout  <<  "Mean mistag OS: "  <<  mean_mistag_OS  <<  " pm "  <<  mean_mistag_OS_error <<  endl;

  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_OS,    mean_mistag_OS+config.getDouble("p0_OS"), config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "OS exclusively");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_SS,    mean_mistag_OS+config.getDouble("p0_OS"), config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "SS exclusively");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_BS,    mean_mistag_OS+config.getDouble("p0_OS"), config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "exclusive overlap");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_allOS, mean_mistag_OS+config.getDouble("p0_OS"), config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "all OS");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_allSS, mean_mistag_OS+config.getDouble("p0_OS"), config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "all SS");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata,       mean_mistag_OS+config.getDouble("p0_OS"), config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "all");
  
  return 0;
}

void NewTaggingPowerCalculation(double total_signal_events, RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double deltap0_OS, double deltap1_OS, double p0_SS, double p1_SS, double etamean_SS, double deltap0_SS, double deltap1_SS, double p0error_OS, double p1error_OS, double p0error_SS, double p1error_SS, TString identifier){
  
  double weight = 0., etaOS = 0., etaSS = 0., tagOS = 0., tagSS = 0., omegaOS = 0., omegaSS = 0., omegaOS_B0 = 0., omegaSS_B0 = 0., omegaOS_B0bar = 0., omegaSS_B0bar = 0.;
  double taggingpower = 0., taggingpowererror = 0., taggingpowererrorp0OScomponent = 0., taggingpowererrorp1OScomponent = 0., taggingpowererrorp0SScomponent = 0., taggingpowererrorp1SScomponent = 0.;
  
  for (int i = 0; i < data->numEntries(); i++) {
    data->get(i);
    weight = data->weight();
    etaOS = data->get()->getRealValue("obsEtaOSwCharm");
    etaSS = data->get()->getRealValue("obsEtaSS");
    tagOS = data->get()->getCatIndex("obsTagOSwCharm");
    tagSS = data->get()->getCatIndex("obsTagSS");
    omegaOS = 0.5;
    omegaOS_B0 = 0.5;
    omegaOS_B0bar = 0.5;
    omegaSS = 0.5;
    omegaSS_B0 = 0.5;
    omegaSS_B0bar = 0.5;
    if (etaOS < 0.5 && !(identifier.EqualTo("all SS"))) {
      omegaOS = p0_OS + p1_OS * (etaOS - etamean_OS);
      if (omegaOS < 0.5) {
        omegaOS_B0 = p0_OS + 0.5*deltap0_OS + (p1_OS + 0.5*deltap1_OS) * (etaOS - etamean_OS);
        omegaOS_B0bar = p0_OS - 0.5*deltap0_OS + (p1_OS - 0.5*deltap1_OS) * (etaOS - etamean_OS);
      }
    }
    if (etaSS < 0.5 && !(identifier.EqualTo("all OS"))) {
      omegaSS = p0_SS + p1_SS * (etaSS - etamean_SS);
      if (omegaSS < 0.5) {
        omegaSS_B0 = p0_SS + 0.5*deltap0_SS + (p1_SS + 0.5*deltap1_SS) * (etaSS - etamean_SS);
        omegaSS_B0bar = p0_SS - 0.5*deltap0_SS + (p1_SS - 0.5*deltap1_SS) * (etaSS - etamean_SS);
      }
    }

    taggingpower += weight*pow(-tagOS*(1.0 - 2.0*omegaOS)-tagSS*(1.0 - 2.0*omegaSS)+tagOS*tagSS*(omegaOS_B0 - omegaOS_B0bar + omegaSS_B0 - omegaSS_B0bar - 2.0*(omegaOS_B0*omegaSS_B0 - omegaOS_B0bar*omegaSS_B0bar)),2);
    taggingpowererrorp0OScomponent += weight*(4.0*tagOS - 4.0*tagOS*tagSS*(omegaSS_B0 - omegaSS_B0bar))*p0error_OS*(-tagOS*(1.0 - 2.0*omegaOS)-tagSS*(1.0 - 2.0*omegaSS)+tagOS*tagSS*(omegaOS_B0 - omegaOS_B0bar + omegaSS_B0 - omegaSS_B0bar - 2.0*(omegaOS_B0*omegaSS_B0 - omegaOS_B0bar*omegaSS_B0bar)));
    taggingpowererrorp1OScomponent += weight*(etaOS - etamean_OS)*(4.0*tagOS - 4.0*tagOS*tagSS*(omegaSS_B0 - omegaSS_B0bar))*p1error_OS*(-tagOS*(1.0 - 2.0*omegaOS)-tagSS*(1.0 - 2.0*omegaSS)+tagOS*tagSS*(omegaOS_B0 - omegaOS_B0bar + omegaSS_B0 - omegaSS_B0bar - 2.0*(omegaOS_B0*omegaSS_B0 - omegaOS_B0bar*omegaSS_B0bar)));
    taggingpowererrorp0SScomponent += weight*(4.0*tagSS - 4.0*tagOS*tagSS*(omegaOS_B0 - omegaOS_B0bar))*p0error_SS*(-tagOS*(1.0 - 2.0*omegaOS)-tagSS*(1.0 - 2.0*omegaSS)+tagOS*tagSS*(omegaOS_B0 - omegaOS_B0bar + omegaSS_B0 - omegaSS_B0bar - 2.0*(omegaOS_B0*omegaSS_B0 - omegaOS_B0bar*omegaSS_B0bar)));
    taggingpowererrorp1SScomponent += weight*(etaSS - etamean_SS)*(4.0*tagSS - 4.0*tagOS*tagSS*(omegaOS_B0 - omegaOS_B0bar))*p1error_SS*(-tagOS*(1.0 - 2.0*omegaOS)-tagSS*(1.0 - 2.0*omegaSS)+tagOS*tagSS*(omegaOS_B0 - omegaOS_B0bar + omegaSS_B0 - omegaSS_B0bar - 2.0*(omegaOS_B0*omegaSS_B0 - omegaOS_B0bar*omegaSS_B0bar)));
  }
  taggingpowererror = sqrt(pow(taggingpowererrorp0SScomponent,2)+pow(taggingpowererrorp1SScomponent,2)+pow(taggingpowererrorp0OScomponent,2)+pow(taggingpowererrorp1OScomponent,2)+pow(taggingpower,2)/(total_signal_events));
  taggingpower /= total_signal_events;
  taggingpowererror /= total_signal_events;

  cout  <<  "Taggingpower component for "  <<  identifier <<  ": "  <<  100*taggingpower  <<  " pm " <<  100*taggingpowererror  <<  endl;
}