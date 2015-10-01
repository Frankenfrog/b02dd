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

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  gROOT->SetStyle("Plain");
  setStyle("LHCb");

  RooRealVar        varBDT1("BDT1_classifier","BDT1_classifier",-1,1);
  RooRealVar        varBDT2("BDT2_classifier","BDT2_classifier",-1,1);
  RooRealVar        varBDTG1("BDTG1_classifier","BDTG1_classifier",-1,1);
  RooRealVar        varBDTG2("BDTG2_classifier","BDTG2_classifier",-1,1);
  RooRealVar        SigWeight("SigWeight","SigWeight",-10,10);

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);
  catTriggerSetTopo234BodyBBDT.defineType("not triggered",0);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);
  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("signal",0);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("best PV",0);  

  RooArgSet         variables_data(SigWeight,"variables_data");
  RooArgSet         variables_MC(catDDFinalState,catTriggerSetTopo234BodyBBDT,catDDFinalStateParticles,catBkg,idxPV,"variables_MC");
  RooArgSet         BDT_classifier(varBDT1,varBDT2,varBDTG1,varBDTG2,"BDT_classifier");
  variables_data.add(BDT_classifier);
  variables_MC.add(BDT_classifier);
  
  // Get data set
  EasyTuple         tuple_data(config.getString("tuple_data"),"B02DD",variables_data);
  tuple_data.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple_data.ConvertToDataSet(WeightVar(SigWeight));
  
  data.Print();

  EasyTuple         tuple_MC(config.getString("tuple_MC"),"B02DD",variables_MC);
  tuple_MC.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       MC_data = tuple_MC.ConvertToDataSet(Cut("catBkg==0&&idxPV==0&&catDDFinalStateParticles>=0&&(catDDFinalState!=11||catTriggerSetTopo234BodyBBDT)"));

  TH1*              hist_BDT1_data = data.createHistogram("hist_BDT1_data",varBDT1);
  hist_BDT1_data->SetMarkerColor(4);
  hist_BDT1_data->SetLineColor(4);
  hist_BDT1_data->GetYaxis()->SetTitle("");
  TH1*              hist_BDT2_data = data.createHistogram("hist_BDT2_data",varBDT2);
  hist_BDT2_data->SetMarkerColor(4);
  hist_BDT2_data->SetLineColor(4);
  hist_BDT2_data->GetYaxis()->SetTitle("");
  TH1*              hist_BDTG1_data = data.createHistogram("hist_BDTG1_data",varBDTG1);
  hist_BDTG1_data->SetMarkerColor(4);
  hist_BDTG1_data->SetLineColor(4);
  hist_BDTG1_data->GetYaxis()->SetTitle("");
  TH1*              hist_BDTG2_data = data.createHistogram("hist_BDTG2_data",varBDTG2);
  hist_BDTG2_data->SetMarkerColor(4);
  hist_BDTG2_data->SetLineColor(4);
  hist_BDTG2_data->GetYaxis()->SetTitle("");

  TH1*              hist_BDT1_MC = MC_data.createHistogram("hist_BDT1_MC",varBDT1);
  hist_BDT1_MC->SetMarkerColor(1);
  TH1*              hist_BDT2_MC = MC_data.createHistogram("hist_BDT2_MC",varBDT2);
  hist_BDT2_MC->SetMarkerColor(1);
  TH1*              hist_BDTG1_MC = MC_data.createHistogram("hist_BDTG1_MC",varBDTG1);
  hist_BDTG1_MC->SetMarkerColor(1);
  TH1*              hist_BDTG2_MC = MC_data.createHistogram("hist_BDTG2_MC",varBDTG2);
  hist_BDTG2_MC->SetMarkerColor(1);

  TCanvas c("c","c",800,600);
  hist_BDT1_data->DrawNormalized();
  hist_BDT1_MC->DrawNormalized("same");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/BDT1_datavsMC.pdf");

  hist_BDT2_data->DrawNormalized();
  hist_BDT2_MC->DrawNormalized("same");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/BDT2_datavsMC.pdf");

  hist_BDTG1_data->DrawNormalized();
  hist_BDTG1_MC->DrawNormalized("same");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/BDTG1_datavsMC.pdf");

  hist_BDTG2_data->DrawNormalized();
  hist_BDTG2_MC->DrawNormalized("same");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/BDTG2_datavsMC.pdf");
  
  return 0;
}

void ChangeHistogramSettings(TH1* histogram){
  histogram->GetYaxis()->SetTitle("");
  histogram->SetMinimum(0);
  histogram->SetMaximum(10);
}
