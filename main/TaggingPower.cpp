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

TString OS_tag_observable;
TString OS_mistag_observable;
TString SS_tag_observable;
TString SS_mistag_observable;

double NewTaggingPowerCalculation(double total_signal_events, RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double deltap0_OS, double deltap1_OS, double p0_SS, double p1_SS, double etamean_SS, double deltap0_SS, double deltap1_SS, double p0error_OS, double p1error_OS, double p0error_SS, double p1error_SS, TString identifier);

int main(int argc, const char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  OS_tag_observable = config.getString("OS_tag_observable");
  OS_mistag_observable = config.getString("OS_mistag_observable");
  SS_tag_observable = config.getString("SS_tag_observable");
  SS_mistag_observable = config.getString("SS_mistag_observable");
  TString sweightname = config.getString("sweightname");

  RooCategory       obsTagOS(OS_tag_observable,"Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  obsTagOS.defineType("no Tag",0);
  RooCategory       obsTagSS(SS_tag_observable,"Flavour Tag");
  obsTagSS.defineType("B0",1);
  obsTagSS.defineType("B0bar",-1);
  obsTagSS.defineType("no Tag",0);
  RooCategory       catYear("catYear","catYear");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooRealVar        obsEtaOS(OS_mistag_observable,"#eta_{OS}",0,0.5);
  RooRealVar        obsEtaSS(SS_mistag_observable,"#eta_{SS}",0,0.5);
  RooRealVar        SigWeight(sweightname,"Signal weight",-10,10);

  RooArgSet         observables(obsTagOS,obsTagSS,SigWeight,obsEtaOS,obsEtaSS,catYear,"observables");

  EasyTuple         sweighted_tuple(config.getString("tuple"),config.getString("tree"),observables);
  sweighted_tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       signaldata = sweighted_tuple.ConvertToDataSet(WeightVar("SigWeight"));
  signaldata.Print();

  RooDataSet        signaldata_OS("signaldata_OS","signaldata_OS",observables,Import(signaldata),Cut("abs("+OS_tag_observable+")==1&&abs("+SS_tag_observable+")==0"),WeightVar(sweightname));
  signaldata_OS.Print();
  RooDataSet        signaldata_SS("signaldata_SS","signaldata_SS",observables,Import(signaldata),Cut("abs("+OS_tag_observable+")==0&&abs("+SS_tag_observable+")==1"),WeightVar(sweightname));
  signaldata_SS.Print();
  RooDataSet        signaldata_BS("signaldata_BS","signaldata_BS",observables,Import(signaldata),Cut("abs("+OS_tag_observable+")==1&&abs("+SS_tag_observable+")==1"),WeightVar(sweightname));
  signaldata_BS.Print();
  RooDataSet        signaldata_allOS("signaldata_allOS","signaldata_allOS",observables,Import(signaldata),Cut("abs("+OS_tag_observable+")==1"),WeightVar(sweightname));
  signaldata_allOS.Print();
  RooDataSet        signaldata_allOS_11("signaldata_allOS_11","signaldata_allOS_11",observables,Import(signaldata),Cut("abs("+OS_tag_observable+")==1&&catYear==2011"),WeightVar(sweightname));
  RooDataSet        signaldata_allOS_12("signaldata_allOS_12","signaldata_allOS_12",observables,Import(signaldata),Cut("abs("+OS_tag_observable+")==1&&catYear==2012"),WeightVar(sweightname));
  RooDataSet        signaldata_allSS("signaldata_allSS","signaldata_allSS",observables,Import(signaldata),Cut("abs("+SS_tag_observable+")==1"),WeightVar(sweightname));
  signaldata_allSS.Print();
  RooDataSet        signaldata_allSS_11("signaldata_allSS_11","signaldata_allSS_11",observables,Import(signaldata),Cut("abs("+SS_tag_observable+")==1&&catYear==2011"),WeightVar(sweightname));
  RooDataSet        signaldata_allSS_12("signaldata_allSS_12","signaldata_allSS_12",observables,Import(signaldata),Cut("abs("+SS_tag_observable+")==1&&catYear==2012"),WeightVar(sweightname));
  RooDataSet        signaldata_tagged("signaldata_tagged","signaldata_tagged",observables,Import(signaldata),Cut("abs("+SS_tag_observable+")==1||abs("+OS_tag_observable+")==1"),WeightVar(sweightname));
  signaldata_tagged.Print();

  double            mean_mistag_OS = signaldata_allOS.mean(obsEtaOS);
  double            mean_mistag_OS_error = 1./sqrt(signaldata_allOS.sumEntries());
  double            mean_mistag_OS_2011 = signaldata_allOS_11.mean(obsEtaOS);
  double            mean_mistag_OS_2012 = signaldata_allOS_12.mean(obsEtaOS);
  double            mean_mistag_OS_2011_error = 1./sqrt(signaldata_allOS_11.sumEntries());
  double            mean_mistag_OS_2012_error = 1./sqrt(signaldata_allOS_12.sumEntries());

  double            mean_mistag_SS = signaldata_allSS.mean(obsEtaSS);
  double            mean_mistag_SS_error = 1./sqrt(signaldata_allSS.sumEntries());
  double            mean_mistag_SS_2011 = signaldata_allSS_11.mean(obsEtaSS);
  double            mean_mistag_SS_2012 = signaldata_allSS_12.mean(obsEtaSS);
  double            mean_mistag_SS_2011_error = 1./sqrt(signaldata_allSS_11.sumEntries());
  double            mean_mistag_SS_2012_error = 1./sqrt(signaldata_allSS_12.sumEntries());

  cout  <<  "Mean mistag OS: "  <<  mean_mistag_OS  <<  " pm "  <<  mean_mistag_OS_error <<  endl;
  cout  <<  "Mean mistag OS 2011: "  <<  mean_mistag_OS_2011  <<  " pm "  <<  mean_mistag_OS_2011_error <<  endl;
  cout  <<  "Mean mistag OS 2012: "  <<  mean_mistag_OS_2012  <<  " pm "  <<  mean_mistag_OS_2012_error <<  endl;
  cout  <<  "Mean mistag SS: "  <<  mean_mistag_SS  <<  " pm "  <<  mean_mistag_SS_error <<  endl;
  cout  <<  "Mean mistag SS 2011: "  <<  mean_mistag_SS_2011  <<  " pm "  <<  mean_mistag_SS_2011_error <<  endl;
  cout  <<  "Mean mistag SS 2012: "  <<  mean_mistag_SS_2012  <<  " pm "  <<  mean_mistag_SS_2012_error <<  endl;
  cout  <<  "OS tagging efficiency: "  <<  signaldata_allOS.sumEntries()/signaldata.sumEntries()  <<  " pm " << sqrt(signaldata_allOS.sumEntries()/signaldata.sumEntries()*(1-signaldata_allOS.sumEntries()/signaldata.sumEntries())/signaldata.sumEntries()) <<  endl;
  cout  <<  "SS tagging efficiency: "  <<  signaldata_allSS.sumEntries()/signaldata.sumEntries()  <<  " pm " << sqrt(signaldata_allSS.sumEntries()/signaldata.sumEntries()*(1-signaldata_allSS.sumEntries()/signaldata.sumEntries())/signaldata.sumEntries()) <<  endl;
  cout  <<  "exclusive OS tagging efficiency: "  <<  signaldata_OS.sumEntries()/signaldata.sumEntries()  <<  " pm " << sqrt(signaldata_OS.sumEntries()/signaldata.sumEntries()*(1-signaldata_OS.sumEntries()/signaldata.sumEntries())/signaldata.sumEntries()) <<  endl;
  cout  <<  "exclusive SS tagging efficiency: "  <<  signaldata_SS.sumEntries()/signaldata.sumEntries()  <<  " pm " << sqrt(signaldata_SS.sumEntries()/signaldata.sumEntries()*(1-signaldata_SS.sumEntries()/signaldata.sumEntries())/signaldata.sumEntries()) <<  endl;
  cout  <<  "overlap tagging efficiency: "  <<  signaldata_BS.sumEntries()/signaldata.sumEntries()  <<  " pm " << sqrt(signaldata_BS.sumEntries()/signaldata.sumEntries()*(1-signaldata_BS.sumEntries()/signaldata.sumEntries())/signaldata.sumEntries()) <<  endl;
  cout  <<  "total tagging efficiency: "  <<  signaldata_tagged.sumEntries()/signaldata.sumEntries()  <<  " pm " << sqrt(signaldata_tagged.sumEntries()/signaldata.sumEntries()*(1-signaldata_tagged.sumEntries()/signaldata.sumEntries())/signaldata.sumEntries()) <<  endl;

  double p0_OS = config.getDouble("p0_OS") + mean_mistag_OS;
  if (config.getBool("no_global_OS_calib")) {
    mean_mistag_OS = config.getDouble("etamean_OS");
    p0_OS = config.getDouble("p0_OS");
  }

  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_OS,    p0_OS, config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "OS exclusively");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_SS,    p0_OS, config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "SS exclusively");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_BS,    p0_OS, config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "exclusive overlap");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_allOS, p0_OS, config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "all OS");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_allSS, p0_OS, config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "all SS");
  double total_taggingpower = NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata,       p0_OS, config.getDouble("p1_OS"), mean_mistag_OS, config.getDouble("deltap0_OS"), config.getDouble("deltap1_OS"), config.getDouble("p0_SS"), config.getDouble("p1_SS"), config.getDouble("etamean_SS"), config.getDouble("deltap0_SS"), config.getDouble("deltap1_SS"), config.getDouble("p0error_OS"), config.getDouble("p1error_OS"), config.getDouble("p0error_SS"), config.getDouble("p1error_SS"), "all");
  cout << "effective dilution: "  <<  sqrt(total_taggingpower/(signaldata_tagged.sumEntries()/signaldata.sumEntries())) <<  endl;
  cout << "effective mistag probability: "  <<  (1. - sqrt(total_taggingpower/(signaldata_tagged.sumEntries()/signaldata.sumEntries())))/2. <<  endl;

  return 0;
}

double NewTaggingPowerCalculation(double total_signal_events, RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double deltap0_OS, double deltap1_OS, double p0_SS, double p1_SS, double etamean_SS, double deltap0_SS, double deltap1_SS, double p0error_OS, double p1error_OS, double p0error_SS, double p1error_SS, TString identifier){

  double weight = 0., etaOS = 0., etaSS = 0., tagOS = 0., tagSS = 0., omegaOS = 0., omegaSS = 0., omegaOS_B0 = 0., omegaSS_B0 = 0., omegaOS_B0bar = 0., omegaSS_B0bar = 0.;
  double taggingpower = 0., taggingpowererror = 0., taggingpowererrorp0OScomponent = 0., taggingpowererrorp1OScomponent = 0., taggingpowererrorp0SScomponent = 0., taggingpowererrorp1SScomponent = 0.;

  for (int i = 0; i < data->numEntries(); i++) {
    data->get(i);
    weight = data->weight();
    etaOS = data->get()->getRealValue(OS_mistag_observable);
    etaSS = data->get()->getRealValue(SS_mistag_observable);
    tagOS = data->get()->getCatIndex(OS_tag_observable);
    tagSS = data->get()->getCatIndex(SS_tag_observable);
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
  return taggingpower;
}

