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
#include "TGraphErrors.h"

//from RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooDataHist.h"
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
#include "RooKeysPdf.h"
#include "RooCBShape.h"
#include "RooSimultaneous.h"

#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
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
#include "doofit/plotting/fitresult/FitResultPrinter.h"

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
  bool massmodel_ipatia = config.getBool("ipatia");
  bool split_years      = config.getBool("split_years");

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5400,"MeV/c^{2}");
  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);
  RooRealVar        varDMinTauSignificance("varDMinTauSignificance","varDMinTauSignificance",-5,150);
  RooRealVar        DD_weight("parSigDDYield_sw","parSigDDYield_sw",-10,10);

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

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         variables(varBDT,varDMinTauSignificance,DD_weight,"variables");
  RooArgSet         realvars(observables,variables,"realvars");
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,catYear,"categories");
  
  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(WeightVar("parSigDDYield_sw"));
  
  data.Print();

  // Mass PDF
  RooAbsPdf*        pdfSigMass;
  RooAbsPdf*        pdfSigBsMass;
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
  if (!massmodel_ipatia)  pdfSigMass = new RooAddPdf("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB2),parSigMassCBFraction);

  RooRealVar        parSigMassL("parSigMassL","parSigMassL",-5.6);
  RooRealVar        parSigMassZeta("parSigMassZeta","parSigMassZeta",0);
  RooRealVar        parSigMassBeta("parSigMassBeta","parSigMassBeta",0,-0.1,0.1);
  RooRealVar        parSigMassSigma("parSigMassSigma","parSigMassSigma",9.0,5,15,"MeV/c^{2}");
  RooRealVar        parSigMassAlpha1("parSigMassAlpha1","parSigMassAlpha1",1.31);
  RooRealVar        parSigMassn1("parSigMassn1","parSigMassn1",10);
  RooRealVar        parSigMassAlpha2("parSigMassAlpha2","parSigMassAlpha2",2.28);
  RooRealVar        parSigMassn2("parSigMassn2","parSigMassn2",10);
  if (massmodel_ipatia) pdfSigMass = new RooIpatia2("pdfSigMass","pdfSigMass",obsMass,parSigMassL,parSigMassZeta,parSigMassBeta,parSigMassSigma,parSigMassMean,parSigMassAlpha1,parSigMassn1,parSigMassAlpha2,parSigMassn2);

  RooRealVar        parBkgDsDMean("parBkgDsDMean","Mean Mass",5220,5210,5230,"MeV/c^{2}");

  RooRealVar        parBkgDsDMassSigma("parBkgDsDMassSigma","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parBkgDsDMassCBExpo("parBkgDsDMassCBExpo","parBkgDsDMassCBExpo",10);
  RooRealVar        parBkgDsDMassCBAlpha("parBkgDsDMassCBAlpha","parBkgDsDMassCBAlpha",1,0.5,2);
  RooCBShape        pdfBkgDsDMass("pdfBkgDsDMass","Mass PDF",obsMass,parBkgDsDMean,parBkgDsDMassSigma,parBkgDsDMassCBAlpha,parBkgDsDMassCBExpo);

  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.52",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);
  if (!massmodel_ipatia) pdfSigBsMass = new RooAddPdf("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB2),parSigMassCBFraction);
  else pdfSigBsMass = new RooIpatia2("pdfSigBsMass","pdfSigBsMass",obsMass,parSigMassL,parSigMassZeta,parSigMassBeta,parSigMassSigma,parSigBsMassMean,parSigMassAlpha1,parSigMassn1,parSigMassAlpha2,parSigMassn2);  

  RooRealVar        parBkgDstDLowMassMean("parBkgDstDLowMassMean","Mean Mass",5060,5050,5070,"MeV/c^{2}");
  RooRealVar        parBkgDstDLowMassSigma("parBkgDstDLowMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDLowMass("pdfBkgDstDLowMass","Lower DstD Mass PDF",obsMass,parBkgDstDLowMassMean,parBkgDstDLowMassSigma);

  RooRealVar        parBkgDstDHighMassMean("parBkgDstDHighMassMean","Mean Mass",5120,5100,5140,"MeV/c^{2}");
  RooRealVar        parBkgDstDHighMassSigma("parBkgDstDHighMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDHighMass("pdfBkgDstDHighMass","Upper DstD Mass PDF",obsMass,parBkgDstDHighMassMean,parBkgDstDHighMassSigma);

  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);
  RooRealVar        parBkgDstDLowYield_11("parBkgDstDLowYield_11","parBkgDstDLowYield_11",150,0,10000);
  RooRealVar        parBkgDstDLowYield_12("parBkgDstDLowYield_12","parBkgDstDLowYield_12",450,0,10000);
  RooRealVar        parBkgDstDLowYield("parBkgDstDLowYield","parBkgDstDLowYield",600,0,10000);
  RooRealVar        parBkgDstDHighYield_11("parBkgDstDHighYield_11","parBkgDstDHighYield_11",100,0,10000);
  RooRealVar        parBkgDstDHighYield_12("parBkgDstDHighYield_12","parBkgDstDHighYield_12",300,0,10000);
  RooRealVar        parBkgDstDHighYield("parBkgDstDHighYield","parBkgDstDHighYield",500,0,10000);

  RooExtendPdf      pdfSigExtend_11("pdfSigExtend_11","pdfSigExtend_11",*pdfSigMass,parSigYield_11);
  RooExtendPdf      pdfSigExtend_12("pdfSigExtend_12","pdfSigExtend_12",*pdfSigMass,parSigYield_12);
  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",*pdfSigMass,parSigYield);
  RooExtendPdf      pdfBkgDsDExtend_11("pdfBkgDsDExtend_11","pdfBkgDsDExtend_11",pdfBkgDsDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfBkgDsDExtend_12("pdfBkgDsDExtend_12","pdfBkgDsDExtend_12",pdfBkgDsDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfBkgDsDExtend("pdfBkgDsDExtend","pdfBkgDsDExtend",pdfBkgDsDMass,parBkgDsDYield);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",*pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",*pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",*pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);
  RooExtendPdf      pdfBkgDstDLowExtend_11("pdfBkgDstDLowExtend_11","pdfBkgDstDLowExtend_11",pdfBkgDstDLowMass,parBkgDstDLowYield_11);
  RooExtendPdf      pdfBkgDstDLowExtend_12("pdfBkgDstDLowExtend_12","pdfBkgDstDLowExtend_12",pdfBkgDstDLowMass,parBkgDstDLowYield_12);
  RooExtendPdf      pdfBkgDstDLowExtend("pdfBkgDstDLowExtend","pdfBkgDstDLowExtend",pdfBkgDstDLowMass,parBkgDstDLowYield);
  RooExtendPdf      pdfBkgDstDHighExtend_11("pdfBkgDstDHighExtend_11","pdfBkgDstDHighExtend_11",pdfBkgDstDHighMass,parBkgDstDHighYield_11);
  RooExtendPdf      pdfBkgDstDHighExtend_12("pdfBkgDstDHighExtend_12","pdfBkgDstDHighExtend_12",pdfBkgDstDHighMass,parBkgDstDHighYield_12);
  RooExtendPdf      pdfBkgDstDHighExtend("pdfBkgDstDHighExtend","pdfBkgDstDHighExtend",pdfBkgDstDHighMass,parBkgDstDHighYield);

  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11/*,pdfBkgDstDLowExtend_11,pdfBkgDstDHighExtend_11,pdfBkgExtend_11*/));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12/*,pdfBkgDstDLowExtend_12,pdfBkgDstDHighExtend_12,pdfBkgExtend_12*/));
  
  RooAbsPdf*        pdfMass;

  if (split_years) {
    RooSimultaneous* pdfSimMass = new RooSimultaneous("pdfSimMass","pdfSimMass",catYear);
    pdfSimMass->addPdf(pdfMass_11,"2011");
    pdfSimMass->addPdf(pdfMass_12,"2012");
    pdfMass = pdfSimMass;
  }
  else pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgDstDLowExtend,pdfBkgDstDHighExtend,pdfBkgExtend));

  // Get Starting Values and Fit PDF to data
  pdfMass->Print();
  pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_DDweightsMass.txt");
  pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/StartingValues_Mass.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(config.getInt("num_cpu")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  RooFitResult* fit_result = pdfMass->fitTo(data, fitting_args);
  doofit::plotting::fitresult::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();

  if (massmodel_ipatia) pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/FitResults_Ipatia_DDweights_"+TString(config.getString("identifier"))+".txt");
  else pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/FitResults_DDweights_"+TString(config.getString("identifier"))+".txt");

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/sWeights/Plots/"+string(config.getString("identifier")));
  cfg_plot_mass.set_simultaneous_plot_all_categories(true);
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend.*", "pdfBkgDsDExtend.*", "pdfSigBsExtend.*", "pdfBkgDstDLowExtend.*", "pdfBkgDstDHighExtend.*", "pdfBkgExtend.*";
  Plot* Mass;
  if (massmodel_ipatia) {
    if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, data, *((RooSimultaneous*)pdfMass), components_mass, "DDweights_Ipatia_obsMass_"+string(config.getString("identifier")));
    else Mass = new Plot(cfg_plot_mass, obsMass, data, *pdfMass, components_mass, "DDweights_Ipatia_obsMass_"+string(config.getString("identifier")));
  }
  else {
    if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, data, *((RooSimultaneous*)pdfMass), components_mass, "DDweights_obsMass_"+string(config.getString("identifier")));
    else Mass = new Plot(cfg_plot_mass, obsMass, data, *pdfMass, components_mass, "DDweights_obsMass_"+string(config.getString("identifier")));
  }
  Mass->set_scaletype_x(kLinear);
  Mass->set_scaletype_y(kBoth);
  Mass->PlotIt();

  return 0;
}
