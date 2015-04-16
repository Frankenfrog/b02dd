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

using namespace std;
using namespace RooFit;
using namespace doocore::io;

void TaggingPowerCalculation(RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double p0error_OS, double p1error_OS, double p0_SS, double p1_SS, double etamean_SS, double p0error_SS, double p1error_SS, TString identifier);
void TrueTaggingPowerCalculation(RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double deltap0_OS, double deltap1_OS, double p0_SS, double p1_SS, double etamean_SS, double deltap0_SS, double deltap1_SS, double p0error_OS, double p1error_OS, double p0error_SS, double p1error_SS, TString identifier);
void NewTaggingPowerCalculation(double total_signal_events, RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double deltap0_OS, double deltap1_OS, double p0_SS, double p1_SS, double etamean_SS, double deltap0_SS, double deltap1_SS, double p0error_OS, double p1error_OS, double p0error_SS, double p1error_SS, TString identifier);

int main(int argc, const char * argv[]){
  
  RooCategory       obsTagOS("obsTagOS","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  obsTagOS.defineType("no Tag",0);
  RooCategory       obsTagSSPion("obsTagSSPion","Flavour Tag");
  obsTagSSPion.defineType("B0",1);
  obsTagSSPion.defineType("B0bar",-1);
  obsTagSSPion.defineType("no Tag",0);
  RooRealVar        obsEtaOS("obsEtaOS","#eta_{OS}",0,0.5);
  RooRealVar        obsEtaSSPion("obsEtaSSPion","#eta_{SS#pi}",0,0.5);
  RooRealVar        weight("parSigYield_sw","Signal weight",-10,10);
  
  RooArgSet         observables(obsTagOS,obsTagSSPion,weight,obsEtaOS,obsEtaSSPion,"observables");
   
  EasyTuple         sweighted_tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/2012/DT2012_B02DD_Stripping21_DVv36r1_20150322_fmeier_combined_20150323_fmeier_BDT4_TupleB_Kpipi_sweight_FT.root","B02DD",observables);
  sweighted_tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       signaldata = sweighted_tuple.ConvertToDataSet(WeightVar("parSigYield_sw"));
  signaldata.Print();
  
  RooDataSet        signaldata_OS("signaldata_OS","signaldata_OS",observables,Import(signaldata),Cut("abs(obsTagOS)==1&&abs(obsTagSSPion)==0"),WeightVar("parSigYield_sw"));
  signaldata_OS.Print();
  RooDataSet        signaldata_SS("signaldata_SS","signaldata_SS",observables,Import(signaldata),Cut("abs(obsTagOS)==0&&abs(obsTagSSPion)==1"),WeightVar("parSigYield_sw"));
  signaldata_SS.Print();
  RooDataSet        signaldata_BS("signaldata_BS","signaldata_BS",observables,Import(signaldata),Cut("abs(obsTagOS)==1&&abs(obsTagSSPion)==1"),WeightVar("parSigYield_sw"));
  signaldata_BS.Print();
  RooDataSet        signaldata_allOS("signaldata_allOS","signaldata_allOS",observables,Import(signaldata),Cut("abs(obsTagOS)==1"),WeightVar("parSigYield_sw"));
  RooDataSet        signaldata_allSS("signaldata_allSS","signaldata_allSS",observables,Import(signaldata),Cut("abs(obsTagSSPion)==1"),WeightVar("parSigYield_sw"));

  double            mean_mistag_OS = signaldata_allOS.mean(obsEtaOS);
  double            mean_mistag_OS_error = 1./sqrt(signaldata_allOS.sumEntries());
  cout  <<  "Mean mistag OS: "  <<  mean_mistag_OS  <<  " pm "  <<  mean_mistag_OS_error <<  endl;

  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_OS,    0.3657, 0.982, 0.3595, 0.0140, 0.066, 0.4232, 1.011, 0.425, -0.0026, -0.18, 0.0019, 0.007, 0.0044, 0.10, "OS exclusively");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_SS,    0.3657, 0.982, 0.3595, 0.0140, 0.066, 0.4232, 1.011, 0.425, -0.0026, -0.18, 0.0019, 0.007, 0.0044, 0.10, "SSPion exclusively");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_BS,    0.3657, 0.982, 0.3595, 0.0140, 0.066, 0.4232, 1.011, 0.425, -0.0026, -0.18, 0.0019, 0.007, 0.0044, 0.10, "exclusive overlap");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_allOS, 0.3657, 0.982, 0.3595, 0.0140, 0.066, 0.4232, 1.011, 0.425, -0.0026, -0.18, 0.0019, 0.007, 0.0044, 0.10, "all OS");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata_allSS, 0.3657, 0.982, 0.3595, 0.0140, 0.066, 0.4232, 1.011, 0.425, -0.0026, -0.18, 0.0019, 0.007, 0.0044, 0.10, "all SSPion");
  NewTaggingPowerCalculation(signaldata.sumEntries(), &signaldata,       0.3657, 0.982, 0.3595, 0.0140, 0.066, 0.4232, 1.011, 0.425, -0.0026, -0.18, 0.0019, 0.007, 0.0044, 0.10, "all");
  
  return 0;
}

void NewTaggingPowerCalculation(double total_signal_events, RooDataSet* data, double p0_OS, double p1_OS, double etamean_OS, double deltap0_OS, double deltap1_OS, double p0_SS, double p1_SS, double etamean_SS, double deltap0_SS, double deltap1_SS, double p0error_OS, double p1error_OS, double p0error_SS, double p1error_SS, TString identifier){
  
  double weight = 0., etaOS = 0., etaSS = 0., tagOS = 0., tagSS = 0., omegaOS = 0., omegaSS = 0., omegaOS_B0 = 0., omegaSS_B0 = 0., omegaOS_B0bar = 0., omegaSS_B0bar = 0.;
  double taggingpower = 0., taggingpowererror = 0., taggingpowererrorp0OScomponent = 0., taggingpowererrorp1OScomponent = 0., taggingpowererrorp0SScomponent = 0., taggingpowererrorp1SScomponent = 0.;
  
  for (int i = 0; i < data->numEntries(); i++) {
    data->get(i);
    weight = data->weight();
    etaOS = data->get()->getRealValue("obsEtaOS");
    etaSS = data->get()->getRealValue("obsEtaSSPion");
    tagOS = data->get()->getCatIndex("obsTagOS");
    tagSS = data->get()->getCatIndex("obsTagSSPion");
    omegaOS = 0.5;
    omegaOS_B0 = 0.5;
    omegaOS_B0bar = 0.5;
    omegaSS = 0.5;
    omegaSS_B0 = 0.5;
    omegaSS_B0bar = 0.5;
    if (etaOS < 0.5 && !(identifier.EqualTo("all SSPion"))) {
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