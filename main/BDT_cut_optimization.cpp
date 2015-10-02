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
#include "TGraph.h"
#include "TMultiGraph.h"

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
#include "RooUnblindUniform.h"
#include "RooConstVar.h"
#include "RooBinning.h"
#include "RooProduct.h"

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooBDecay.h"
#include "RooDecay.h"
#include "RooExponential.h"
#include "RooLognormal.h"
#include "RooGaussian.h"
#include "RooCBShape.h"

#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooEffProd.h"
#include "RooSimultaneous.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooAddModel.h"
#include "RooHistPdf.h"
#include "RooExtendPdf.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "Urania/RooIpatia2.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);

  RooRealVar        obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5150,5600,"MeV/c^{2}");

  RooRealVar        BDT_classifier(TString(config.getString("bdt_classifier1")),"BDT_classifier",-1,1);
  RooRealVar        BDT2_classifier(TString(config.getString("bdt_classifier2")),"BDT2_classifier",-1,1);
  // RooRealVar        BDTG1_classifier("BDTG1_classifier","BDTG1_classifier",-1,1);
  // RooRealVar        BDTG2_classifier("BDTG2_classifier","BDTG2_classifier",-1,1);
  
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);
  catTriggerSetTopo234BodyBBDT.defineType("not triggered",0);
  RooCategory       catYear("catYear","catYear");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);

  RooArgSet         observables(obsMass,BDT_classifier,BDT2_classifier,"observables");
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,catYear,catDDFinalStateParticles,"categories");
  
  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));
  
  data.Print();

  // Mass PDF
  // Signal
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");

  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  RooRealVar        parSigMassCB1Expo("parSigMassCB1Expo","parSigMassCB1Expo",10);
  RooRealVar        parSigMassCB1Alpha("parSigMassCB1Alpha","parSigMassCB1Alpha",1.28);
  RooCBShape        pdfSigMassCB1("pdfSigMassCB1","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);

  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooRealVar        parSigMassCB2Expo("parSigMassCB2Expo","parSigMassCB2Expo",10);
  RooRealVar        parSigMassCB2Alpha("parSigMassCB2Alpha","parSigMassCB2Alpha",-1.32);
  RooCBShape        pdfSigMassCB2("pdfSigMassCB2","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);

  RooRealVar        parSigMassCBFraction("parSigMassCBFraction","parSigMassCBFraction",0.5,0,1);
  RooAddPdf*        pdfSigMass = new RooAddPdf("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB2),parSigMassCBFraction);

  // B0 --> DsD background
  RooRealVar        parBkgDsDMean("parBkgDsDMean","Mean Mass",5220,5210,5230,"MeV/c^{2}");

  RooRealVar        parBkgDsDMassSigma1("parBkgDsDMassSigma1","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parBkgDsDMassCB1Expo("parBkgDsDMassCB1Expo","parBkgDsDMassCB1Expo",10,1,100);
  RooRealVar        parBkgDsDMassCB1Alpha("parBkgDsDMassCB1Alpha","parBkgDsDMassCB1Alpha",1,0.5,2);
  RooCBShape        pdfBkgDsDMassCB1("pdfBkgDsDMassCB1","Mass PDF",obsMass,parBkgDsDMean,parBkgDsDMassSigma1,parBkgDsDMassCB1Alpha,parBkgDsDMassCB1Expo);

  RooRealVar        parBkgDsDMassSigma2("parBkgDsDMassSigma2","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parBkgDsDMassCB2Expo("parBkgDsDMassCB2Expo","parBkgDsDMassCB2Expo",10,1,100);
  RooRealVar        parBkgDsDMassCB2Alpha("parBkgDsDMassCB2Alpha","parBkgDsDMassCB2Alpha",-1,-2,-0.5);
  RooCBShape        pdfBkgDsDMassCB2("pdfBkgDsDMassCB2","Mass PDF",obsMass,parBkgDsDMean,parBkgDsDMassSigma2,parBkgDsDMassCB2Alpha,parBkgDsDMassCB2Expo);

  RooRealVar        parBkgDsDMassCBFraction("parBkgDsDMassCBFraction","parBkgDsDMassCBFraction",0.5);
  RooAddPdf         pdfBkgDsDMass("pdfBkgDsDMass","pdfBkgDsDMass",RooArgList(pdfBkgDsDMassCB1,pdfBkgDsDMassCB2),parBkgDsDMassCBFraction);

  // Bs --> DD signal
  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.35",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);
  RooAddPdf*        pdfSigBsMass = new RooAddPdf("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB2),parSigMassCBFraction);
  
  // combinatorial background
  RooRealVar        parBkgExponent_Kpipi("parBkgExponent_Kpipi","parBkgExponent_Kpipi",-0.001,-1,1);
  RooExponential    pdfBkgMass_Kpipi("pdfBkgMass_Kpipi","pdfBkgMass_Kpipi",obsMass,parBkgExponent_Kpipi);
  RooRealVar        parBkgExponent_KKpi("parBkgExponent_KKpi","parBkgExponent_KKpi",-0.001,-1,1);
  RooExponential    pdfBkgMass_KKpi("pdfBkgMass_KKpi","pdfBkgMass_KKpi",obsMass,parBkgExponent_KKpi);

  RooRealVar        parSigYield_11_Kpipi("parSigYield_11_Kpipi","parSigYield_11_Kpipi",500,0,1000);
  RooRealVar        parSigYield_12_Kpipi("parSigYield_12_Kpipi","parSigYield_12_Kpipi",500,0,1000);
  RooRealVar        parSigYield_11_KKpi("parSigYield_11_KKpi","parSigYield_11_KKpi",500,0,1000);
  RooRealVar        parSigYield_12_KKpi("parSigYield_12_KKpi","parSigYield_12_KKpi",500,0,1000);
  RooRealVar        parBkgDsDYield_11_Kpipi("parBkgDsDYield_11_Kpipi","parBkgDsDYield_11_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_Kpipi("parBkgDsDYield_12_Kpipi","parBkgDsDYield_12_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_11_KKpi("parBkgDsDYield_11_KKpi","parBkgDsDYield_11_KKpi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_KKpi("parBkgDsDYield_12_KKpi","parBkgDsDYield_12_KKpi",1000,0,2000);
  RooRealVar        parSigBsYield_11_Kpipi("parSigBsYield_11_Kpipi","parSigBsYield_11_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_12_Kpipi("parSigBsYield_12_Kpipi","parSigBsYield_12_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_11_KKpi("parSigBsYield_11_KKpi","parSigBsYield_11_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_12_KKpi("parSigBsYield_12_KKpi","parSigBsYield_12_KKpi",100,0,1000);
  RooRealVar        parBkgYield_11_Kpipi("parBkgYield_11_Kpipi","parBkgYield_11_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_12_Kpipi("parBkgYield_12_Kpipi","parBkgYield_12_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_11_KKpi("parBkgYield_11_KKpi","parBkgYield_11_KKpi",5000,0,10000);
  RooRealVar        parBkgYield_12_KKpi("parBkgYield_12_KKpi","parBkgYield_12_KKpi",5000,0,10000);
  
  RooExtendPdf      pdfSigExtend_11_Kpipi("pdfSigExtend_11_Kpipi","pdfSigExtend_11_Kpipi",*pdfSigMass,parSigYield_11_Kpipi);
  RooExtendPdf      pdfSigExtend_12_Kpipi("pdfSigExtend_12_Kpipi","pdfSigExtend_12_Kpipi",*pdfSigMass,parSigYield_12_Kpipi);
  RooExtendPdf      pdfSigExtend_11_KKpi("pdfSigExtend_11_KKpi","pdfSigExtend_11_KKpi",*pdfSigMass,parSigYield_11_KKpi);
  RooExtendPdf      pdfSigExtend_12_KKpi("pdfSigExtend_12_KKpi","pdfSigExtend_12_KKpi",*pdfSigMass,parSigYield_12_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_11_Kpipi("pdfBkgDsDExtend_11_Kpipi","pdfBkgDsDExtend_11_Kpipi",pdfBkgDsDMass,parBkgDsDYield_11_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_12_Kpipi("pdfBkgDsDExtend_12_Kpipi","pdfBkgDsDExtend_12_Kpipi",pdfBkgDsDMass,parBkgDsDYield_12_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_11_KKpi("pdfBkgDsDExtend_11_KKpi","pdfBkgDsDExtend_11_KKpi",pdfBkgDsDMass,parBkgDsDYield_11_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_12_KKpi("pdfBkgDsDExtend_12_KKpi","pdfBkgDsDExtend_12_KKpi",pdfBkgDsDMass,parBkgDsDYield_12_KKpi);
  RooExtendPdf      pdfSigBsExtend_11_Kpipi("pdfSigBsExtend_11_Kpipi","pdfSigBsExtend_11_Kpipi",*pdfSigBsMass,parSigBsYield_11_Kpipi);
  RooExtendPdf      pdfSigBsExtend_12_Kpipi("pdfSigBsExtend_12_Kpipi","pdfSigBsExtend_12_Kpipi",*pdfSigBsMass,parSigBsYield_12_Kpipi);
  RooExtendPdf      pdfSigBsExtend_11_KKpi("pdfSigBsExtend_11_KKpi","pdfSigBsExtend_11_KKpi",*pdfSigBsMass,parSigBsYield_11_KKpi);
  RooExtendPdf      pdfSigBsExtend_12_KKpi("pdfSigBsExtend_12_KKpi","pdfSigBsExtend_12_KKpi",*pdfSigBsMass,parSigBsYield_12_KKpi);
  RooExtendPdf      pdfBkgExtend_11_Kpipi("pdfBkgExtend_11_Kpipi","pdfBkgExtend_11_Kpipi",pdfBkgMass_Kpipi,parBkgYield_11_Kpipi);
  RooExtendPdf      pdfBkgExtend_12_Kpipi("pdfBkgExtend_12_Kpipi","pdfBkgExtend_12_Kpipi",pdfBkgMass_Kpipi,parBkgYield_12_Kpipi);
  RooExtendPdf      pdfBkgExtend_11_KKpi("pdfBkgExtend_11_KKpi","pdfBkgExtend_11_KKpi",pdfBkgMass_KKpi,parBkgYield_11_KKpi);
  RooExtendPdf      pdfBkgExtend_12_KKpi("pdfBkgExtend_12_KKpi","pdfBkgExtend_12_KKpi",pdfBkgMass_KKpi,parBkgYield_12_KKpi);
  
  RooAddPdf         pdfMass_11_Kpipi("pdfMass_11_Kpipi","Mass PDF",RooArgList(pdfSigExtend_11_Kpipi,pdfBkgDsDExtend_11_Kpipi,pdfSigBsExtend_11_Kpipi,pdfBkgExtend_11_Kpipi));
  RooAddPdf         pdfMass_12_Kpipi("pdfMass_12_Kpipi","Mass PDF",RooArgList(pdfSigExtend_12_Kpipi,pdfBkgDsDExtend_12_Kpipi,pdfSigBsExtend_12_Kpipi,pdfBkgExtend_12_Kpipi));
  RooAddPdf         pdfMass_11_KKpi("pdfMass_11_KKpi","Mass PDF",RooArgList(pdfSigExtend_11_KKpi,pdfBkgDsDExtend_11_KKpi,pdfSigBsExtend_11_KKpi,pdfBkgExtend_11_KKpi));
  RooAddPdf         pdfMass_12_KKpi("pdfMass_12_KKpi","Mass PDF",RooArgList(pdfSigExtend_12_KKpi,pdfBkgDsDExtend_12_KKpi,pdfSigBsExtend_12_KKpi,pdfBkgExtend_12_KKpi));
  
  RooSuperCategory  supercategory("supercategory","supercategory",RooArgList(catYear,catDDFinalStateParticles));
  RooSimultaneous   pdfMass("pdfMass","pdfMass",supercategory);
  pdfMass.addPdf(pdfMass_11_Kpipi,"{2011;Kpipi}");
  pdfMass.addPdf(pdfMass_12_Kpipi,"{2012;Kpipi}");
  pdfMass.addPdf(pdfMass_11_KKpi,"{2011;KKpi}");
  pdfMass.addPdf(pdfMass_12_KKpi,"{2012;KKpi}");

  // Get Starting Values and Fit PDF to data
  pdfMass.Print();
  pdfMass.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/StartingValues_Mass.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(config.getInt("num_cpu")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","migrad"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  RooDataSet* reduced_data;
  RooFitResult* fit_result;
  std::vector<double> signal_yield_bdt1;
  std::vector<double> background_yield_bdt1;
  std::vector<double> signal_yield_bdt2;
  std::vector<double> background_yield_bdt2;
  int n_steps = config.getInt("n_steps");

  for (int i = 0; i < n_steps; ++i) {
    double cutvalue = -0.3+0.01*i;
    reduced_data = dynamic_cast<RooDataSet*>(data.reduce(TString(config.getString("bdt_classifier1")+">"+to_string(cutvalue))));
    reduced_data->Print();
    fit_result = pdfMass.fitTo(*reduced_data,fitting_args);
    pdfMass.getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier1")+"/FitResults_Mass_"+to_string(i)+".txt"));
    signal_yield_bdt1 += parSigYield_11_Kpipi.getVal() + parSigYield_12_Kpipi.getVal() + parSigYield_11_KKpi.getVal() + parSigYield_12_KKpi.getVal();
    background_yield_bdt1 += parBkgYield_11_Kpipi.getVal() + parBkgYield_12_Kpipi.getVal() + parBkgYield_11_KKpi.getVal() + parBkgYield_12_KKpi.getVal();
    // reduced_data = dynamic_cast<RooDataSet*>(data.reduce(TString(config.getString("bdt_classifier2")+">"+to_string(cutvalue))));
    // reduced_data->Print();
    // fit_result = pdfMass.fitTo(*reduced_data,fitting_args);
    // pdfMass.getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier2")+"/FitResults_Mass_"+to_string(i)+".txt"));
    // signal_yield_bdt2 += parSigYield_11_Kpipi.getVal() + parSigYield_12_Kpipi.getVal() + parSigYield_11_KKpi.getVal() + parSigYield_12_KKpi.getVal();
    // background_yield_bdt2 += parBkgYield_11_Kpipi.getVal() + parBkgYield_12_Kpipi.getVal() + parBkgYield_11_KKpi.getVal() + parBkgYield_12_KKpi.getVal();
  }

  double signal_yield_bdt1_array[signal_yield_bdt1.size()];
  double background_yield_bdt1_array[signal_yield_bdt1.size()];
  // double signal_yield_bdt2_array[signal_yield_bdt2.size()];
  // double background_yield_bdt2_array[signal_yield_bdt2.size()];
  for (int i = 0; i < signal_yield_bdt1.size(); ++i) {
    signal_yield_bdt1_array[i] = signal_yield_bdt1.at(i);
    background_yield_bdt1_array[i] = background_yield_bdt1.at(i);
    // signal_yield_bdt2_array[i] = signal_yield_bdt2.at(i);
    // background_yield_bdt2_array[i] = background_yield_bdt2.at(i);
  }
  // TMultiGraph* mg = new TMultiGraph();
  // TGraph*  gr_bdt1 = new TGraph(signal_yield_bdt1.size(), signal_yield_bdt1_array, background_yield_bdt1_array);
  // gr_bdt1->SetLineColor(2);
  // TGraph*  gr_bdt2 = new TGraph(signal_yield_bdt2.size(), signal_yield_bdt2_array, background_yield_bdt2_array);
  // gr_bdt2->SetLineColor(4);
  // mg->Add(gr_bdt1);
  // mg->Add(gr_bdt2);
  // mg->Draw("AC");
  // mg->GetXaxis()->SetTitle("signal yield");
  // mg->GetYaxis()->SetTitle("background yield");
  // c.SaveAs(TString("/home/fmeier/storage03/b02dd/run/BDT-Optimization/SignalvsBackgroundYield_"+config.getString("bdt_classifier1")+".pdf"));

  // for (int i = 0; i < signal_yield_bdt1.size(); ++i)  cout <<  (int)signal_yield_bdt1.at(i) <<  "\t"  <<  (int)background_yield_bdt1.at(i) <<  "\t" <<  (int)signal_yield_bdt2.at(i) <<  "\t"  <<  (int)background_yield_bdt2.at(i) <<  endl;
  for (int i = 0; i < signal_yield_bdt1.size(); ++i)  cout <<  (int)signal_yield_bdt1.at(i) <<  "\t"  <<  (int)background_yield_bdt1.at(i) <<  endl;

  return 0;
}