#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TRandom3.h"

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
#include "RooUnblindUniform.h"
#include "RooConstVar.h"
#include "RooBinning.h"
#include "RooAddition.h"
#include "RooWorkspace.h"
#include "RooProduct.h"

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooBDecay.h"
#include "RooDecay.h"
#include "RooExponential.h"
#include "RooLognormal.h"
#include "RooGaussian.h"
#include "RooMultiVarGaussian.h"
#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooSimultaneous.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooCBShape.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "P2VV/RooCubicSplineFun.h"
#include "P2VV/RooCubicSplineKnot.h"
#include "P2VV/RooAbsGaussModelEfficiency.h"
#include "P2VV/RooGaussEfficiencyModel.h"
#include "P2VV/RooEffResAddModel.h"
#include "doofit/roofit/functions/LinearFunctionWithOffset.h"
#include "doofit/roofit/functions/CPCoefficient.h"
#include "doofit/roofit/pdfs/DooCubicSplinePdf.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/plotting/fitresult/FitResultPrinter.h"
#include "doofit/config/CommonConfig.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStd.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStdConfig.h"
#include "doofit/toy/ToyFactoryStd/ToyFactoryStd.h"
#include "doofit/toy/ToyFactoryStd/ToyFactoryStdConfig.h"
#include "doofit/fitter/splot/SPlotFit2.h"

// from DooSelection
#include "dooselection/reducer/Reducer.h"
#include "dooselection/reducer/SPlotterReducer.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;
using namespace doofit::toy;
using namespace doofit::roofit::functions;
using namespace doofit::roofit::pdfs;
using namespace doofit::fitter::splot;
using namespace dooselection::reducer;

TMatrixDSym CreateCovarianceMatrix(const int size, RooRealVar* p0sigma, RooRealVar* p1sigma, RooRealVar* p0p1corr, RooRealVar* dp0sigma = 0, RooRealVar* dp1sigma = 0, RooRealVar* p0dp0corr = 0, RooRealVar* p0dp1corr = 0, RooRealVar* p1dp0corr = 0, RooRealVar* p1dp1corr = 0, RooRealVar* dp0dp1corr = 0);

int main(int argc, char * argv[]){
  if (argc < 2) {
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' - c toystudy_config_file_name" << std::endl;
    std::cout << "Toy study config is optional, and only needed for bootstrapping"  <<  std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  bool pereventresolution = config.getBool("pereventresolution");
  bool cp_fit = config.getBool("cp_fit");
  TString SStagger = config.getString("SStagger");
  bool split_years      = config.getBool("split_years");
  bool split_final_state  = config.getBool("split_final_state");
  bool calculate_sweights = config.getBool("calculate_sweights");
  bool bootstrapping = config.getBool("bootstrapping");
  if (argc <= 2) bootstrapping = false;
  TString method = config.getString("method");
  bool massfit = config.getBool("massfit");
  bool decaytimefit = config.getBool("decaytimefit");

  if (bootstrapping && argc < 3) {
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' - c toystudy_config_file_name" << std::endl;
    std::cout << "The toy study config file is missing! This is mandatory to perform the bootstrapping!"  <<  std::endl;
    return 0;
  }

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");
  RooRealVar        obsEtaOS("obsEtaOS","#eta_{OS}",0.,0.5);
  RooRealVar        obsEtaSS("obsEtaSS","#eta_{SS}",0.,0.5);
  RooRealVar        obsTimeErr("obsTimeErr","#sigma_{t}",0.005,0.2,"ps");
  RooCategory       obsTagOS("obsTagOS","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  RooCategory       obsTagSS("obsTagSS","Flavour Tag");
  obsTagSS.defineType("B0",1);
  obsTagSS.defineType("B0bar",-1);
  
  RooCategory       catYear("catYear","year of data taking");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooCategory       catTag("catTaggedOSSS","OS or SS tagged");
  catTag.defineType("OS",1);
  catTag.defineType("SS",-1);
  catTag.defineType("both",10);
  catTag.defineType("untagged",0);
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);

  RooArgSet         observables(obsTime,obsMass,"observables");
  if (pereventresolution) observables.add(obsTimeErr);
  if (cp_fit){
    observables.add(obsEtaOS);
    observables.add(obsEtaSS);
    observables.add(obsTagOS);
    observables.add(obsTagSS);
  }
  RooArgSet         categories(catYear,catTag,catDDFinalState,catDDFinalStateParticles,"categories");
  RooArgSet         Gaussian_Constraints("Gaussian_Constraints");

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
  RooAddPdf         pdfSigMass("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB2),parSigMassCBFraction);

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
  RooAddPdf         pdfSigBsMass("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB2),parSigMassCBFraction);
  
  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);
  RooRealVar        parBkgExponent_Kpipi("parBkgExponent_Kpipi","parBkgExponent_Kpipi",-0.001,-1,1);
  RooExponential    pdfBkgMass_Kpipi("pdfBkgMass_Kpipi","pdfBkgMass_Kpipi",obsMass,parBkgExponent_Kpipi);
  RooRealVar        parBkgExponent_KKpi("parBkgExponent_KKpi","parBkgExponent_KKpi",-0.001,-1,1);
  RooExponential    pdfBkgMass_KKpi("pdfBkgMass_KKpi","pdfBkgMass_KKpi",obsMass,parBkgExponent_KKpi);

  RooRealVar        parSigYield_11_Kpipi("parSigYield_11_Kpipi","parSigYield_11_Kpipi",500,0,1000);
  RooRealVar        parSigYield_12_Kpipi("parSigYield_12_Kpipi","parSigYield_12_Kpipi",500,0,1000);
  RooRealVar        parSigYield_11_KKpi("parSigYield_11_KKpi","parSigYield_11_KKpi",500,0,1000);
  RooRealVar        parSigYield_12_KKpi("parSigYield_12_KKpi","parSigYield_12_KKpi",500,0,1000);
  RooRealVar        parSigYield_Kpipi("parSigYield_Kpipi","parSigYield_Kpipi",1000,0,2000);
  RooRealVar        parSigYield_KKpi("parSigYield_KKpi","parSigYield_KKpi",200,0,1000);
  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parBkgDsDYield_11_Kpipi("parBkgDsDYield_11_Kpipi","parBkgDsDYield_11_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_Kpipi("parBkgDsDYield_12_Kpipi","parBkgDsDYield_12_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_11_KKpi("parBkgDsDYield_11_KKpi","parBkgDsDYield_11_KKpi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_KKpi("parBkgDsDYield_12_KKpi","parBkgDsDYield_12_KKpi",1000,0,2000);
  RooRealVar        parBkgDsDYield_Kpipi("parBkgDsDYield_Kpipi","parBkgDsDYield_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_KKpi("parBkgDsDYield_KKpi","parBkgDsDYield_KKpi",150,0,2000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  RooRealVar        parSigBsYield_11_Kpipi("parSigBsYield_11_Kpipi","parSigBsYield_11_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_12_Kpipi("parSigBsYield_12_Kpipi","parSigBsYield_12_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_11_KKpi("parSigBsYield_11_KKpi","parSigBsYield_11_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_12_KKpi("parSigBsYield_12_KKpi","parSigBsYield_12_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_Kpipi("parSigBsYield_Kpipi","parSigBsYield_Kpipi",300,0,1000);
  RooRealVar        parSigBsYield_KKpi("parSigBsYield_KKpi","parSigBsYield_KKpi",50,0,1000);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgYield_11_Kpipi("parBkgYield_11_Kpipi","parBkgYield_11_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_12_Kpipi("parBkgYield_12_Kpipi","parBkgYield_12_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_11_KKpi("parBkgYield_11_KKpi","parBkgYield_11_KKpi",5000,0,10000);
  RooRealVar        parBkgYield_12_KKpi("parBkgYield_12_KKpi","parBkgYield_12_KKpi",5000,0,10000);
  RooRealVar        parBkgYield_Kpipi("parBkgYield_Kpipi","parBkgYield_Kpipi",1800,0,10000);
  RooRealVar        parBkgYield_KKpi("parBkgYield_KKpi","parBkgYield_KKpi",700,0,10000);
  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend_11_Kpipi("pdfSigExtend_11_Kpipi","pdfSigExtend_11_Kpipi",pdfSigMass,parSigYield_11_Kpipi);
  RooExtendPdf      pdfSigExtend_12_Kpipi("pdfSigExtend_12_Kpipi","pdfSigExtend_12_Kpipi",pdfSigMass,parSigYield_12_Kpipi);
  RooExtendPdf      pdfSigExtend_11_KKpi("pdfSigExtend_11_KKpi","pdfSigExtend_11_KKpi",pdfSigMass,parSigYield_11_KKpi);
  RooExtendPdf      pdfSigExtend_12_KKpi("pdfSigExtend_12_KKpi","pdfSigExtend_12_KKpi",pdfSigMass,parSigYield_12_KKpi);
  RooExtendPdf      pdfSigExtend_Kpipi("pdfSigExtend_Kpipi","pdfSigExtend_Kpipi",pdfSigMass,parSigYield_Kpipi);
  RooExtendPdf      pdfSigExtend_KKpi("pdfSigExtend_KKpi","pdfSigExtend_KKpi",pdfSigMass,parSigYield_KKpi);
  RooExtendPdf      pdfSigExtend_11("pdfSigExtend_11","pdfSigExtend_11",pdfSigMass,parSigYield_11);
  RooExtendPdf      pdfSigExtend_12("pdfSigExtend_12","pdfSigExtend_12",pdfSigMass,parSigYield_12);
  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);
  RooExtendPdf      pdfBkgDsDExtend_11_Kpipi("pdfBkgDsDExtend_11_Kpipi","pdfBkgDsDExtend_11_Kpipi",pdfBkgDsDMass,parBkgDsDYield_11_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_12_Kpipi("pdfBkgDsDExtend_12_Kpipi","pdfBkgDsDExtend_12_Kpipi",pdfBkgDsDMass,parBkgDsDYield_12_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_11_KKpi("pdfBkgDsDExtend_11_KKpi","pdfBkgDsDExtend_11_KKpi",pdfBkgDsDMass,parBkgDsDYield_11_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_12_KKpi("pdfBkgDsDExtend_12_KKpi","pdfBkgDsDExtend_12_KKpi",pdfBkgDsDMass,parBkgDsDYield_12_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_Kpipi("pdfBkgDsDExtend_Kpipi","pdfBkgDsDExtend_Kpipi",pdfBkgDsDMass,parBkgDsDYield_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_KKpi("pdfBkgDsDExtend_KKpi","pdfBkgDsDExtend_KKpi",pdfBkgDsDMass,parBkgDsDYield_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_11("pdfBkgDsDExtend_11","pdfBkgDsDExtend_11",pdfBkgDsDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfBkgDsDExtend_12("pdfBkgDsDExtend_12","pdfBkgDsDExtend_12",pdfBkgDsDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfBkgDsDExtend("pdfBkgDsDExtend","pdfBkgDsDExtend",pdfBkgDsDMass,parBkgDsDYield);
  RooExtendPdf      pdfSigBsExtend_11_Kpipi("pdfSigBsExtend_11_Kpipi","pdfSigBsExtend_11_Kpipi",pdfSigBsMass,parSigBsYield_11_Kpipi);
  RooExtendPdf      pdfSigBsExtend_12_Kpipi("pdfSigBsExtend_12_Kpipi","pdfSigBsExtend_12_Kpipi",pdfSigBsMass,parSigBsYield_12_Kpipi);
  RooExtendPdf      pdfSigBsExtend_11_KKpi("pdfSigBsExtend_11_KKpi","pdfSigBsExtend_11_KKpi",pdfSigBsMass,parSigBsYield_11_KKpi);
  RooExtendPdf      pdfSigBsExtend_12_KKpi("pdfSigBsExtend_12_KKpi","pdfSigBsExtend_12_KKpi",pdfSigBsMass,parSigBsYield_12_KKpi);
  RooExtendPdf      pdfSigBsExtend_Kpipi("pdfSigBsExtend_Kpipi","pdfSigBsExtend_Kpipi",pdfSigBsMass,parSigBsYield_Kpipi);
  RooExtendPdf      pdfSigBsExtend_KKpi("pdfSigBsExtend_KKpi","pdfSigBsExtend_KKpi",pdfSigBsMass,parSigBsYield_KKpi);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend_11_Kpipi("pdfBkgExtend_11_Kpipi","pdfBkgExtend_11_Kpipi",pdfBkgMass_Kpipi,parBkgYield_11_Kpipi);
  RooExtendPdf      pdfBkgExtend_12_Kpipi("pdfBkgExtend_12_Kpipi","pdfBkgExtend_12_Kpipi",pdfBkgMass_Kpipi,parBkgYield_12_Kpipi);
  RooExtendPdf      pdfBkgExtend_11_KKpi("pdfBkgExtend_11_KKpi","pdfBkgExtend_11_KKpi",pdfBkgMass_KKpi,parBkgYield_11_KKpi);
  RooExtendPdf      pdfBkgExtend_12_KKpi("pdfBkgExtend_12_KKpi","pdfBkgExtend_12_KKpi",pdfBkgMass_KKpi,parBkgYield_12_KKpi);
  RooExtendPdf      pdfBkgExtend_Kpipi("pdfBkgExtend_Kpipi","pdfBkgExtend_Kpipi",pdfBkgMass_Kpipi,parBkgYield_Kpipi);
  RooExtendPdf      pdfBkgExtend_KKpi("pdfBkgExtend_KKpi","pdfBkgExtend_KKpi",pdfBkgMass_KKpi,parBkgYield_KKpi);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass_11_Kpipi("pdfMass_11_Kpipi","Mass PDF",RooArgList(pdfSigExtend_11_Kpipi,pdfBkgDsDExtend_11_Kpipi,pdfSigBsExtend_11_Kpipi,pdfBkgExtend_11_Kpipi));
  RooAddPdf         pdfMass_12_Kpipi("pdfMass_12_Kpipi","Mass PDF",RooArgList(pdfSigExtend_12_Kpipi,pdfBkgDsDExtend_12_Kpipi,pdfSigBsExtend_12_Kpipi,pdfBkgExtend_12_Kpipi));
  RooAddPdf         pdfMass_11_KKpi("pdfMass_11_KKpi","Mass PDF",RooArgList(pdfSigExtend_11_KKpi,pdfBkgDsDExtend_11_KKpi,pdfSigBsExtend_11_KKpi,pdfBkgExtend_11_KKpi));
  RooAddPdf         pdfMass_12_KKpi("pdfMass_12_KKpi","Mass PDF",RooArgList(pdfSigExtend_12_KKpi,pdfBkgDsDExtend_12_KKpi,pdfSigBsExtend_12_KKpi,pdfBkgExtend_12_KKpi));
  RooAddPdf         pdfMass_Kpipi("pdfMass_Kpipi","Mass PDF",RooArgList(pdfSigExtend_Kpipi,pdfBkgDsDExtend_Kpipi,pdfSigBsExtend_Kpipi,pdfBkgExtend_Kpipi));
  RooAddPdf         pdfMass_KKpi("pdfMass_KKpi","Mass PDF",RooArgList(pdfSigExtend_KKpi,pdfBkgDsDExtend_KKpi,pdfSigBsExtend_KKpi,pdfBkgExtend_KKpi));
  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12));

  RooSuperCategory  supercategory_mass("supercategory_mass","supercategory_mass",RooArgList(catYear,catDDFinalStateParticles));
  RooAbsPdf*        pdfMass;

  if (split_years) {
    if (split_final_state) {
      pdfMass = new RooSimultaneous("pdfMass","pdfMass",supercategory_mass);
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11_Kpipi,"{2011;Kpipi}");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12_Kpipi,"{2012;Kpipi}");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11_KKpi,"{2011;KKpi}");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12_KKpi,"{2012;KKpi}");
    }
    else {
      pdfMass = new RooSimultaneous("pdfMass","pdfMass",catYear);
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11,"2011");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12,"2012");
    }
  }
  else if (split_final_state) {
    pdfMass = new RooSimultaneous("pdfMass","pdfMass",catDDFinalStateParticles);
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_Kpipi,"Kpipi");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_KKpi,"KKpi");
  }
  else  pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend));

  // Lifetime and mixing parameters
  RooRealVar          parSigTimeTau("parSigTimeTau","#tau",1.5,1.,2.);
  RooRealVar          parSigTimeTauMean("parSigTimeTauMean","#tau",1.519);
  RooRealVar          parSigTimeTauSigma("parSigTimeTauSigma","#tau",0.005);
  RooRealVar          parSigTimeDeltaM("parSigTimeDeltaM","#Delta m",0.510,0.4,0.6);
  RooRealVar          parSigTimeDeltaMMean("parSigTimeDeltaMMean","#Delta m",0.510);
  RooRealVar          parSigTimeDeltaMSigma("parSigTimeDeltaMSigma","#Delta m",0.004);
  RooRealVar          parSigEtaDeltaG("parSigEtaDeltaG","#Delta#Gamma",0.);

  // CPV parameters
  RooRealVar          parSigTimeSin2b("parSigTimeSin2b","#it{S_{D^{+}D^{-}}}",0.7,-2,2);
  RooRealVar          parSigTimeC("parSigTimeC","#it{C_{D^{+}D^{-}}}",0,-2,2);

  // Asymmetries
  RooRealVar          parSigEtaDeltaProd_11("parSigEtaDeltaProd_11","B0/B0bar production asymmetry",-0.0066,-0.05,0.02);
  RooRealVar          parSigEtaDeltaProdMean_11("parSigEtaDeltaProdMean_11","#bar{#mu}",-0.0066);
  RooRealVar          parSigEtaDeltaProdSigma_11("parSigEtaDeltaProdSigma_11","#sigma_{#bar{mu}}",0.0026);

  RooRealVar          parSigEtaDeltaProdOffset("parSigEtaDeltaProdOffset","difference between 2011 and 2012 B0/B0bar production asymmetry",0.0004,-0.01,0.01);
  RooRealVar          parSigEtaDeltaProdOffsetMean("parSigEtaDeltaProdOffsetMean","#bar{#mu}",0.0004);
  RooRealVar          parSigEtaDeltaProdOffsetSigma("parSigEtaDeltaProdOffsetSigma","#sigma_{#bar{mu}}",0.0018);
  RooAddition         parSigEtaDeltaProd_12("parSigEtaDeltaProd_12","B0/B0bar production asymmetry 2012",RooArgList(parSigEtaDeltaProd_11,parSigEtaDeltaProdOffset));

  // OS tags
  RooRealVar          parSigEtaDeltaP0_OS("parSigEtaDeltaP0_OS","delta mistag probability",0.0140,0.,0.03);
  RooRealVar          parSigEtaDeltaP0Mean_OS("parSigEtaDeltaP0Mean_OS","#bar{#delta p_{0}}",0.0148);
  RooRealVar          parSigEtaDeltaP0Sigma_OS("parSigEtaDeltaP0Sigma_OS","#sigma_{#bar{#delta p_{0}}}",0.0012);  // B+ value 0.0016  Kstar 0.0031
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_OS);

  RooRealVar          parSigEtaDeltaP1_OS("parSigEtaDeltaP1_OS","delta scale calibration parameter probability",0.066,0.,0.1);
  RooRealVar          parSigEtaDeltaP1Mean_OS("parSigEtaDeltaP1Mean_OS","#bar{#delta p_{1}}",0.070);
  RooRealVar          parSigEtaDeltaP1Sigma_OS("parSigEtaDeltaP1Sigma_OS","#sigma_{#bar{#delta p_{1}}}",0.012);   // B+ value 0.018   Kstar 0.035
  Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_OS);

  // SS tags
  RooRealVar          parSigEtaDeltaP0_SS("parSigEtaDeltaP0_SS","delta mistag probability",-0.003,-0.02,0.02);
  RooRealVar          parSigEtaDeltaP0Mean_SS("parSigEtaDeltaP0Mean_SS","#bar{#delta p_{0}}",-0.0026);
  RooRealVar          parSigEtaDeltaP0Sigma_SS("parSigEtaDeltaP0Sigma_SS","#sigma_{#bar{#delta p_{0}}}",0.0044);
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_SS);

  RooRealVar          parSigEtaDeltaP1_SS("parSigEtaDeltaP1_SS","delta scale calibration parameter probability",-0.18,-0.7,0.3);
  RooRealVar          parSigEtaDeltaP1Mean_SS("parSigEtaDeltaP1Mean_SS","#bar{#delta p_{1}}",-0.18);
  RooRealVar          parSigEtaDeltaP1Sigma_SS("parSigEtaDeltaP1Sigma_SS","#sigma_{#bar{#delta p_{1}}}",0.10);
  Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_SS);

//=========================================================================================================================================================================================================================

  // Resolution model
  RooRealVar                parResMean("parResMean","parResMean",-0.0032);
  RooRealVar                parResCorrectionOffset1("parResCorrectionOffset1","Offset of linear decay time error correction",0.);
  RooRealVar                parResCorrectionOffset2("parResCorrectionOffset2","Offset of linear decay time error correction",0.);
  RooRealVar                parResSigmaCorrectionFactor1("parResSigmaCorrectionFactor1","Correctionfactor of Proper Time Errors 1",1.);
  RooRealVar                parResSigmaCorrectionFactor2("parResSigmaCorrectionFactor2","Correctionfactor of Proper Time Errors 2",1.);
  LinearFunctionWithOffset  parResSigmaCorrection1("parResSigmaCorrection1",obsTimeErr,parResSigmaCorrectionFactor1,parResCorrectionOffset1);
  LinearFunctionWithOffset  parResSigmaCorrection2("parResSigmaCorrection2",obsTimeErr,parResSigmaCorrectionFactor2,parResCorrectionOffset2);
  RooRealVar                parResSigma_wrongPV("parResSigma_wrongPV","Width of wrong PV component",1,0,5);

  RooRealVar                parResFraction2("parResFraction2","Fraction of second per event Gauss model",0.5);
  RooRealVar                parResFraction_wrongPV("parResFraction_wrongPV","Fraction of wrong PV Gauss model",0.1);

//=========================================================================================================================================================================================================================

  // Decay Time Acceptance
  std::vector<double> knots;
  knots += 0.8;
  knots += 2.0;

  RooArgList        listofsplinecoefficients("listofsplinecoefficients");
  RooRealVar*       parSigTimeAccCSpline;
  for (int i = 1; i <= (knots.size()+2) ; i++) {
    std::string binname = "parSigTimeAccCSpline" + boost::lexical_cast<std::string>(i);
    parSigTimeAccCSpline = new RooRealVar(binname.c_str(),binname.c_str(),1,0,2);
    listofsplinecoefficients.add(*parSigTimeAccCSpline);
  }

  RooCubicSplineFun       accspline("accspline","Spline Acceptance",obsTime,knots,listofsplinecoefficients);
  RooResolutionModel*     efficiencymodel;
  RooGaussEfficiencyModel efficiencymodel1("efficiencymodel1","Gaussefficiencymodel 1",obsTime,accspline,parResMean,parResSigmaCorrection1);
  RooGaussEfficiencyModel efficiencymodel2("efficiencymodel2","Gaussefficiencymodel 2",obsTime,accspline,parResMean,parResSigmaCorrection2);
  RooGaussEfficiencyModel efficiencymodel3("efficiencymodel3","Gaussefficiencymodel 3",obsTime,accspline,parResMean,parResSigma_wrongPV);
  if (!pereventresolution) efficiencymodel = new RooGaussEfficiencyModel("efficiencymodel","Gaussefficiencymodel",obsTime,accspline,parResMean,RooConst(0.05));
  else efficiencymodel = new RooEffResAddModel("efficiencymodel","Per event resolution efficiency model",RooArgList(efficiencymodel3,efficiencymodel2,efficiencymodel1),RooArgList(parResFraction_wrongPV,parResFraction2));

//=========================================================================================================================================================================================================================

  // Tagging calibration
  RooRealVar          parSigEtaP0_OS("parSigEtaP0_OS","Offset on per-event mistag",0.3815,0.0,0.1);
  RooRealVar          parSigEtaP0Mean_OS("parSigEtaP0Mean_OS","#bar{p}_{0}",0.3815);
  RooRealVar          parSigEtaP0Sigma_OS("parSigEtaP0Sigma_OS","#sigma_{#bar{p}_{0}}",0.0019);   // B+ value 0.0011  Kstar 0.0022
  Gaussian_Constraints.add(parSigEtaP0Sigma_OS);

  RooRealVar          parSigEtaP1_OS("parSigEtaP1_OS","Offset on per-event mistag",0.978,0.9,1.1);
  RooRealVar          parSigEtaP1Mean_OS("parSigEtaP1Mean_OS","#bar{p}_{0}",0.978);
  RooRealVar          parSigEtaP1Sigma_OS("parSigEtaP1Sigma_OS","#sigma_{#bar{p}_{0}}",0.007);  // B+ value 0.012   Kstar 0.024
  Gaussian_Constraints.add(parSigEtaP1Sigma_OS);
  
  RooRealVar          parSigEtaMean_OS("parSigEtaMean_OS","Mean on per-event mistag",0.3786);

  RooRealVar          parSigEtaP0_SS("parSigEtaP0_SS","Offset on per-event mistag",0.4228,0.3,0.5);
  RooRealVar          parSigEtaP0Mean_SS("parSigEtaP0Mean_SS","#bar{p}_{0}",0.4232);
  RooRealVar          parSigEtaP0Sigma_SS("parSigEtaP0Sigma_SS","#sigma_{#bar{p}_{0}}",0.0029);
  Gaussian_Constraints.add(parSigEtaP0Sigma_SS);

  RooRealVar          parSigEtaP1_SS("parSigEtaP1_SS","Offset on per-event mistag",1.01,0.7,1.1);
  RooRealVar          parSigEtaP1Mean_SS("parSigEtaP1Mean_SS","#bar{p}_{0}",1.011);
  RooRealVar          parSigEtaP1Sigma_SS("parSigEtaP1Sigma_SS","#sigma_{#bar{p}_{0}}",0.064);
  Gaussian_Constraints.add(parSigEtaP1Sigma_SS);

  RooRealVar          parSigEtaP0P1CorrelationCoeff_SS("parSigEtaP0P1CorrelationCoeff_SS","correlation coefficient between p0 and p1 SS",0.030);
  RooRealVar          parSigEtaP0DeltaP0CorrelationCoeff_SS("parSigEtaP0DeltaP0CorrelationCoeff_SS","correlation coefficient between p0 and Delta p0 SS",-0.007);
  RooRealVar          parSigEtaP0DeltaP1CorrelationCoeff_SS("parSigEtaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between p0 and Delta p1 SS",0.0016);
  RooRealVar          parSigEtaP1DeltaP0CorrelationCoeff_SS("parSigEtaP1DeltaP0CorrelationCoeff_SS","correlation coefficient between p1 and Delta p0 SS",0.0004);
  RooRealVar          parSigEtaP1DeltaP1CorrelationCoeff_SS("parSigEtaP1DeltaP1CorrelationCoeff_SS","correlation coefficient between p1 and Delta p1 SS",-0.006);
  RooRealVar          parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS("parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between Delta p0 and Delta p1 SS",0.04);

  RooRealVar          parSigEtaMean_SS("parSigEtaMean_SS","Mean on per-event mistag",0.42484);

//=========================================================================================================================================================================================================================

  // RooBDecay parameters
  RooConstVar       parSigTimeSinh("parSigTimeSinh","Sh_{f}",0.0);

  CPCoefficient     parSigTimeCosh_11_OS("parSigTimeCosh_11_OS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_OS("parSigTimeCosh_12_OS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_OS("parSigTimeSin_11_OS",parSigTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_OS("parSigTimeSin_12_OS",parSigTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_OS("parSigTimeCos_11_OS",parSigTimeC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_OS("parSigTimeCos_12_OS",parSigTimeC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kCos);

  CPCoefficient     parSigTimeCosh_11_SS("parSigTimeCosh_11_SS",RooConst(1.0),obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_SS("parSigTimeCosh_12_SS",RooConst(1.0),obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_SS("parSigTimeSin_11_SS",parSigTimeSin2b,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_SS("parSigTimeSin_12_SS",parSigTimeSin2b,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_SS("parSigTimeCos_11_SS",parSigTimeC,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_SS("parSigTimeCos_12_SS",parSigTimeC,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCos);

  CPCoefficient     parSigTimeCosh_11_BS("parSigTimeCosh_11_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_BS("parSigTimeCosh_12_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_BS("parSigTimeSin_11_BS",parSigTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_BS("parSigTimeSin_12_BS",parSigTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_BS("parSigTimeCos_11_BS",parSigTimeC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_BS("parSigTimeCos_12_BS",parSigTimeC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCos);

//=========================================================================================================================================================================================================================

  // Decay Time PDF

  RooAbsPdf*        pdfSigTime_11_OS;
  RooAbsPdf*        pdfSigTime_11_SS;
  RooAbsPdf*        pdfSigTime_12_OS;
  RooAbsPdf*        pdfSigTime_12_SS;
  RooAbsPdf*        pdfSigTime_11_BS;
  RooAbsPdf*        pdfSigTime_12_BS;

  if (cp_fit){
    pdfSigTime_11_OS = new RooBDecay("pdfSigTime_11_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_OS,parSigTimeSinh,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
    pdfSigTime_11_SS = new RooBDecay("pdfSigTime_11_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_SS,parSigTimeSinh,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
    pdfSigTime_12_OS = new RooBDecay("pdfSigTime_12_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_OS,parSigTimeSinh,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
    pdfSigTime_12_SS = new RooBDecay("pdfSigTime_12_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_SS,parSigTimeSinh,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
    pdfSigTime_11_BS = new RooBDecay("pdfSigTime_11_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_BS,parSigTimeSinh,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
    pdfSigTime_12_BS = new RooBDecay("pdfSigTime_12_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_BS,parSigTimeSinh,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  }
  else {
    pdfSigTime_11_OS = new RooDecay("pdfSigTime_11_OS","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
    pdfSigTime_11_SS = new RooDecay("pdfSigTime_11_SS","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
    pdfSigTime_12_OS = new RooDecay("pdfSigTime_12_OS","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
    pdfSigTime_12_SS = new RooDecay("pdfSigTime_12_SS","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
    pdfSigTime_11_BS = new RooDecay("pdfSigTime_11_BS","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
    pdfSigTime_12_BS = new RooDecay("pdfSigTime_12_BS","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
  }

//========================================================================================================================================================================================================================

  // Build Simultaneous PDF
  RooSuperCategory  supercategory_time("supercategory_time","supercategory_time",RooArgSet(catYear,catTag));
  RooSimultaneous   pdfTime("pdfTime","P",supercategory_time);
  pdfTime.addPdf(*pdfSigTime_11_OS,"{2011;OS}");
  pdfTime.addPdf(*pdfSigTime_11_SS,"{2011;SS}");
  pdfTime.addPdf(*pdfSigTime_11_BS,"{2011;both}");
  pdfTime.addPdf(*pdfSigTime_12_OS,"{2012;OS}");
  pdfTime.addPdf(*pdfSigTime_12_SS,"{2012;SS}");
  pdfTime.addPdf(*pdfSigTime_12_BS,"{2012;both}");

  cout  <<  "simultaneous PDF built"  <<  endl;

  Gaussian_Constraints.readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
  pdfTime.Print();

  RooRealVar            parSigEtaDeltaP0P1CorrelationCoeff_OS("parSigEtaDeltaP0P1CorrelationCoeff_OS","correlation coefficient between calibration parameters p0 and p1 or Delta p0 and Delta p1 for OS",0.14);
  TMatrixDSym           covariancematrixSigEtaDelta_OS = CreateCovarianceMatrix(2, &parSigEtaDeltaP0Sigma_OS, &parSigEtaDeltaP1Sigma_OS, &parSigEtaDeltaP0P1CorrelationCoeff_OS);
  RooRealVar            parSigEtaP0P1CorrelationCoeff_OS("parSigEtaP0P1CorrelationCoeff_OS","correlation coefficient between calibration parameters p0 and p1 for OS",0.14);
  TMatrixDSym           covariancematrixSigEta_OS = CreateCovarianceMatrix(2, &parSigEtaP0Sigma_OS, &parSigEtaP1Sigma_OS, &parSigEtaP0P1CorrelationCoeff_OS);
  TMatrixDSym           covariancematrixSigEta_SS = CreateCovarianceMatrix(4, &parSigEtaP0Sigma_SS, &parSigEtaP1Sigma_SS, &parSigEtaP0P1CorrelationCoeff_SS, &parSigEtaDeltaP0Sigma_SS, &parSigEtaDeltaP1Sigma_SS, &parSigEtaP0DeltaP0CorrelationCoeff_SS, &parSigEtaP0DeltaP1CorrelationCoeff_SS, &parSigEtaP1DeltaP0CorrelationCoeff_SS, &parSigEtaP1DeltaP1CorrelationCoeff_SS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS);

  RooArgSet             constrainingPdfs("constrainingPdfs");
  RooGaussian           conpdfSigTimeTau("conpdfSigTimeTau","constraint for #tau",parSigTimeTau,parSigTimeTauMean,parSigTimeTauSigma);
  RooGaussian           conpdfSigTimeDeltaM("conpdfSigTimeDeltaM","constraint for #Delta m",parSigTimeDeltaM,parSigTimeDeltaMMean,parSigTimeDeltaMSigma);
  RooGaussian           conpdfSigEtaDeltaProd_11("conpdfSigEtaDeltaProd_11","Gaussian Constraint for production asymmetry 2011",parSigEtaDeltaProd_11,parSigEtaDeltaProdMean_11,parSigEtaDeltaProdSigma_11);
  RooGaussian           conpdfSigEtaDeltaProd_12("conpdfSigEtaDeltaProd_12","Gaussian Constraint for production asymmetry 2012",parSigEtaDeltaProdOffset,parSigEtaDeltaProdOffsetMean,parSigEtaDeltaProdOffsetSigma);
  RooGaussian           conpdfSigEtaDeltaP0_OS("conpdfSigEtaDeltaP0_OS","conpdfSigEtaDeltaP0_OS",parSigEtaDeltaP0_OS,parSigEtaDeltaP0Mean_OS,parSigEtaDeltaP0Sigma_OS);
  RooGaussian           conpdfSigEtaDeltaP1_OS("conpdfSigEtaDeltaP1_OS","conpdfSigEtaDeltaP1_OS",parSigEtaDeltaP1_OS,parSigEtaDeltaP1Mean_OS,parSigEtaDeltaP1Sigma_OS);
  RooMultiVarGaussian   conpdfSigEtaDelta_OS("conpdfSigEtaDelta_OS","constraint for Delta p0 and Delta p1 of OS FT calibration",RooArgList(parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS),RooArgList(parSigEtaDeltaP0Mean_OS,parSigEtaDeltaP1Mean_OS),covariancematrixSigEtaDelta_OS);
  RooGaussian           conpdfSigEtaDeltaP0_SS("conpdfSigEtaDeltaP0_SS","conpdfSigEtaDeltaP0_SS",parSigEtaDeltaP0_SS,parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP0Sigma_SS);
  RooGaussian           conpdfSigEtaDeltaP1_SS("conpdfSigEtaDeltaP1_SS","conpdfSigEtaDeltaP1_SS",parSigEtaDeltaP1_SS,parSigEtaDeltaP1Mean_SS,parSigEtaDeltaP1Sigma_SS);  
  RooGaussian           conpdfSigEtaP0_OS("conpdfSigEtaP0_OS","Gaussian Constraint for Offset parameter",parSigEtaP0_OS,parSigEtaP0Mean_OS,parSigEtaP0Sigma_OS);
  RooGaussian           conpdfSigEtaP1_OS("conpdfSigEtaP1_OS","Gaussian Constraint for Scale parameter",parSigEtaP1_OS,parSigEtaP1Mean_OS,parSigEtaP1Sigma_OS);
  RooMultiVarGaussian   conpdfSigEta_OS("conpdfSigEta_OS","constraint for p0 and p1 of OS FT calibration",RooArgList(parSigEtaP0_OS,parSigEtaP1_OS),RooArgList(parSigEtaP0Mean_OS,parSigEtaP1Mean_OS),covariancematrixSigEta_OS);
  RooGaussian           conpdfSigEtaP0_SS("conpdfSigEtaP0_SS","Gaussian Constraint for Offset parameter",parSigEtaP0_SS,parSigEtaP0Mean_SS,parSigEtaP0Sigma_SS);
  RooGaussian           conpdfSigEtaP1_SS("conpdfSigEtaP1_SS","Gaussian Constraint for Scale parameter",parSigEtaP1_SS,parSigEtaP1Mean_SS,parSigEtaP1Sigma_SS);
  RooMultiVarGaussian   conpdfSigEta_SS("conpdfSigEta_SS","constraint for SS FT calibration",RooArgList(parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS),RooArgList(parSigEtaP0Mean_SS,parSigEtaP1Mean_SS,parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP1Mean_SS),covariancematrixSigEta_SS);  

  constrainingPdfs.add(conpdfSigTimeTau);
  if (cp_fit) {
    constrainingPdfs.add(conpdfSigTimeDeltaM);
    constrainingPdfs.add(conpdfSigEtaDeltaProd_11);
    constrainingPdfs.add(conpdfSigEtaDeltaProd_12);
    constrainingPdfs.add(conpdfSigEta_OS);
    constrainingPdfs.add(conpdfSigEta_SS);
    constrainingPdfs.add(conpdfSigEtaDelta_OS);
  }
  cout  <<  "Constraints added" <<  endl;

  //========================================================================================================================================================================================================================

  RooProdPdf      pdfSig_11_OS("pdfSig_11_OS","pdfSig_11_OS",RooArgList(pdfSigMass,*pdfSigTime_11_OS));
  RooProdPdf      pdfSig_11_SS("pdfSig_11_SS","pdfSig_11_SS",RooArgList(pdfSigMass,*pdfSigTime_11_SS));
  RooProdPdf      pdfSig_11_BS("pdfSig_11_BS","pdfSig_11_BS",RooArgList(pdfSigMass,*pdfSigTime_11_BS));
  RooProdPdf      pdfSig_12_OS("pdfSig_12_OS","pdfSig_12_OS",RooArgList(pdfSigMass,*pdfSigTime_12_OS));
  RooProdPdf      pdfSig_12_SS("pdfSig_12_SS","pdfSig_12_SS",RooArgList(pdfSigMass,*pdfSigTime_12_SS));
  RooProdPdf      pdfSig_12_BS("pdfSig_12_BS","pdfSig_12_BS",RooArgList(pdfSigMass,*pdfSigTime_12_BS));

  RooRealVar      parSigFraction_11_OS("parSigFraction_11_OS","parSigFraction_11_OS",0.3);
  RooProduct      parSigYield_11_OS_Kpipi("parSigYield_11_OS_Kpipi","parSigYield_11_OS_Kpipi",RooArgList(parSigYield_11_Kpipi,parSigFraction_11_OS));
  RooRealVar      parSigFraction_11_SS("parSigFraction_11_SS","parSigFraction_11_SS",0.3);
  RooProduct      parSigYield_11_SS_Kpipi("parSigYield_11_SS_Kpipi","parSigYield_11_SS_Kpipi",RooArgList(parSigYield_11_Kpipi,parSigFraction_11_SS));
  RooFormulaVar   parSigFraction_11_BS("parSigFraction_11_BS","parSigFraction_11_BS","1-@0-@1",RooArgList(parSigFraction_11_OS,parSigFraction_11_SS));
  RooProduct      parSigYield_11_BS_Kpipi("parSigYield_11_BS_Kpipi","parSigYield_11_BS_Kpipi",RooArgList(parSigYield_11_Kpipi,parSigFraction_11_BS));
  RooRealVar      parSigFraction_12_OS("parSigFraction_12_OS","parSigFraction_12_OS",0.3);
  RooProduct      parSigYield_12_OS_Kpipi("parSigYield_12_OS_Kpipi","parSigYield_12_OS_Kpipi",RooArgList(parSigYield_12_Kpipi,parSigFraction_12_OS));
  RooRealVar      parSigFraction_12_SS("parSigFraction_12_SS","parSigFraction_12_SS",0.3);
  RooProduct      parSigYield_12_SS_Kpipi("parSigYield_12_SS_Kpipi","parSigYield_12_SS_Kpipi",RooArgList(parSigYield_12_Kpipi,parSigFraction_12_SS));  
  RooFormulaVar   parSigFraction_12_BS("parSigFraction_12_BS","parSigFraction_12_BS","1-@0-@1",RooArgList(parSigFraction_12_OS,parSigFraction_12_SS));
  RooProduct      parSigYield_12_BS_Kpipi("parSigYield_12_BS_Kpipi","parSigYield_12_BS_Kpipi",RooArgList(parSigYield_12_Kpipi,parSigFraction_12_BS));
  RooProduct      parSigYield_11_OS_KKpi("parSigYield_11_OS_KKpi","parSigYield_11_OS_KKpi",RooArgList(parSigYield_11_KKpi,parSigFraction_11_OS));
  RooProduct      parSigYield_11_SS_KKpi("parSigYield_11_SS_KKpi","parSigYield_11_SS_KKpi",RooArgList(parSigYield_11_KKpi,parSigFraction_11_SS));
  RooProduct      parSigYield_11_BS_KKpi("parSigYield_11_BS_KKpi","parSigYield_11_BS_KKpi",RooArgList(parSigYield_11_KKpi,parSigFraction_11_BS));
  RooProduct      parSigYield_12_OS_KKpi("parSigYield_12_OS_KKpi","parSigYield_12_OS_KKpi",RooArgList(parSigYield_12_KKpi,parSigFraction_12_OS));
  RooProduct      parSigYield_12_SS_KKpi("parSigYield_12_SS_KKpi","parSigYield_12_SS_KKpi",RooArgList(parSigYield_12_KKpi,parSigFraction_12_SS));  
  RooProduct      parSigYield_12_BS_KKpi("parSigYield_12_BS_KKpi","parSigYield_12_BS_KKpi",RooArgList(parSigYield_12_KKpi,parSigFraction_12_BS));

  RooExtendPdf    pdfSig_11_OS_Kpipi("pdfSig_11_OS_Kpipi","pdfSig_11_OS_Kpipi",pdfSig_11_OS,parSigYield_11_OS_Kpipi);
  RooExtendPdf    pdfSig_11_SS_Kpipi("pdfSig_11_SS_Kpipi","pdfSig_11_SS_Kpipi",pdfSig_11_SS,parSigYield_11_SS_Kpipi);
  RooExtendPdf    pdfSig_11_BS_Kpipi("pdfSig_11_BS_Kpipi","pdfSig_11_BS_Kpipi",pdfSig_11_BS,parSigYield_11_BS_Kpipi);
  RooExtendPdf    pdfSig_12_OS_Kpipi("pdfSig_12_OS_Kpipi","pdfSig_12_OS_Kpipi",pdfSig_12_OS,parSigYield_12_OS_Kpipi);
  RooExtendPdf    pdfSig_12_SS_Kpipi("pdfSig_12_SS_Kpipi","pdfSig_12_SS_Kpipi",pdfSig_12_SS,parSigYield_12_SS_Kpipi);
  RooExtendPdf    pdfSig_12_BS_Kpipi("pdfSig_12_BS_Kpipi","pdfSig_12_BS_Kpipi",pdfSig_12_BS,parSigYield_12_BS_Kpipi);
  RooExtendPdf    pdfSig_11_OS_KKpi("pdfSig_11_OS_KKpi","pdfSig_11_OS_KKpi",pdfSig_11_OS,parSigYield_11_OS_KKpi);
  RooExtendPdf    pdfSig_11_SS_KKpi("pdfSig_11_SS_KKpi","pdfSig_11_SS_KKpi",pdfSig_11_SS,parSigYield_11_SS_KKpi);
  RooExtendPdf    pdfSig_11_BS_KKpi("pdfSig_11_BS_KKpi","pdfSig_11_BS_KKpi",pdfSig_11_BS,parSigYield_11_BS_KKpi);
  RooExtendPdf    pdfSig_12_OS_KKpi("pdfSig_12_OS_KKpi","pdfSig_12_OS_KKpi",pdfSig_12_OS,parSigYield_12_OS_KKpi);
  RooExtendPdf    pdfSig_12_SS_KKpi("pdfSig_12_SS_KKpi","pdfSig_12_SS_KKpi",pdfSig_12_SS,parSigYield_12_SS_KKpi);
  RooExtendPdf    pdfSig_12_BS_KKpi("pdfSig_12_BS_KKpi","pdfSig_12_BS_KKpi",pdfSig_12_BS,parSigYield_12_BS_KKpi);

  RooRealVar      parSigBsTau("parSigBsTau","parSigBsTau",1.512);
  RooDecay        pdfSigBsTime("pdfSigBsTime","pdfSigBsTime",obsTime,parSigBsTau,*efficiencymodel,RooDecay::SingleSided);
  RooProdPdf      pdfSigBs("pdfSigBs","pdfSigBs",RooArgList(pdfSigBsMass,pdfSigBsTime));

  RooRealVar      parSigBsFraction_11_OS("parSigBsFraction_11_OS","parSigBsFraction_11_OS",0.3);
  RooProduct      parSigBsYield_11_OS_Kpipi("parSigBsYield_11_OS_Kpipi","parSigBsYield_11_OS_Kpipi",RooArgList(parSigBsYield_11_Kpipi,parSigBsFraction_11_OS));
  RooRealVar      parSigBsFraction_11_SS("parSigBsFraction_11_SS","parSigBsFraction_11_SS",0.3);
  RooProduct      parSigBsYield_11_SS_Kpipi("parSigBsYield_11_SS_Kpipi","parSigBsYield_11_SS_Kpipi",RooArgList(parSigBsYield_11_Kpipi,parSigBsFraction_11_SS));
  RooFormulaVar   parSigBsFraction_11_BS("parSigBsFraction_11_BS","parSigBsFraction_11_BS","1-@0-@1",RooArgList(parSigBsFraction_11_OS,parSigBsFraction_11_SS));
  RooProduct      parSigBsYield_11_BS_Kpipi("parSigBsYield_11_BS_Kpipi","parSigBsYield_11_BS_Kpipi",RooArgList(parSigBsYield_11_Kpipi,parSigBsFraction_11_BS));
  RooRealVar      parSigBsFraction_12_OS("parSigBsFraction_12_OS","parSigBsFraction_12_OS",0.3);
  RooProduct      parSigBsYield_12_OS_Kpipi("parSigBsYield_12_OS_Kpipi","parSigBsYield_12_OS_Kpipi",RooArgList(parSigBsYield_12_Kpipi,parSigBsFraction_12_OS));
  RooRealVar      parSigBsFraction_12_SS("parSigBsFraction_12_SS","parSigBsFraction_12_SS",0.3);
  RooProduct      parSigBsYield_12_SS_Kpipi("parSigBsYield_12_SS_Kpipi","parSigBsYield_12_SS_Kpipi",RooArgList(parSigBsYield_12_Kpipi,parSigBsFraction_12_SS));  
  RooFormulaVar   parSigBsFraction_12_BS("parSigBsFraction_12_BS","parSigBsFraction_12_BS","1-@0-@1",RooArgList(parSigBsFraction_12_OS,parSigBsFraction_12_SS));
  RooProduct      parSigBsYield_12_BS_Kpipi("parSigBsYield_12_BS_Kpipi","parSigBsYield_12_BS_Kpipi",RooArgList(parSigBsYield_12_Kpipi,parSigBsFraction_12_BS));
  RooProduct      parSigBsYield_11_OS_KKpi("parSigBsYield_11_OS_KKpi","parSigBsYield_11_OS_KKpi",RooArgList(parSigBsYield_11_KKpi,parSigBsFraction_11_OS));
  RooProduct      parSigBsYield_11_SS_KKpi("parSigBsYield_11_SS_KKpi","parSigBsYield_11_SS_KKpi",RooArgList(parSigBsYield_11_KKpi,parSigBsFraction_11_SS));
  RooProduct      parSigBsYield_11_BS_KKpi("parSigBsYield_11_BS_KKpi","parSigBsYield_11_BS_KKpi",RooArgList(parSigBsYield_11_KKpi,parSigBsFraction_11_BS));
  RooProduct      parSigBsYield_12_OS_KKpi("parSigBsYield_12_OS_KKpi","parSigBsYield_12_OS_KKpi",RooArgList(parSigBsYield_12_KKpi,parSigBsFraction_12_OS));
  RooProduct      parSigBsYield_12_SS_KKpi("parSigBsYield_12_SS_KKpi","parSigBsYield_12_SS_KKpi",RooArgList(parSigBsYield_12_KKpi,parSigBsFraction_12_SS));  
  RooProduct      parSigBsYield_12_BS_KKpi("parSigBsYield_12_BS_KKpi","parSigBsYield_12_BS_KKpi",RooArgList(parSigBsYield_12_KKpi,parSigBsFraction_12_BS));

  RooExtendPdf    pdfSigBs_11_OS_Kpipi("pdfSigBs_11_OS_Kpipi","pdfSigBs_11_OS_Kpipi",pdfSigBs,parSigBsYield_11_OS_Kpipi);
  RooExtendPdf    pdfSigBs_11_SS_Kpipi("pdfSigBs_11_SS_Kpipi","pdfSigBs_11_SS_Kpipi",pdfSigBs,parSigBsYield_11_SS_Kpipi);
  RooExtendPdf    pdfSigBs_11_BS_Kpipi("pdfSigBs_11_BS_Kpipi","pdfSigBs_11_BS_Kpipi",pdfSigBs,parSigBsYield_11_BS_Kpipi);
  RooExtendPdf    pdfSigBs_12_OS_Kpipi("pdfSigBs_12_OS_Kpipi","pdfSigBs_12_OS_Kpipi",pdfSigBs,parSigBsYield_12_OS_Kpipi);
  RooExtendPdf    pdfSigBs_12_SS_Kpipi("pdfSigBs_12_SS_Kpipi","pdfSigBs_12_SS_Kpipi",pdfSigBs,parSigBsYield_12_SS_Kpipi);
  RooExtendPdf    pdfSigBs_12_BS_Kpipi("pdfSigBs_12_BS_Kpipi","pdfSigBs_12_BS_Kpipi",pdfSigBs,parSigBsYield_12_BS_Kpipi);
  RooExtendPdf    pdfSigBs_11_OS_KKpi("pdfSigBs_11_OS_KKpi","pdfSigBs_11_OS_KKpi",pdfSigBs,parSigBsYield_11_OS_KKpi);
  RooExtendPdf    pdfSigBs_11_SS_KKpi("pdfSigBs_11_SS_KKpi","pdfSigBs_11_SS_KKpi",pdfSigBs,parSigBsYield_11_SS_KKpi);
  RooExtendPdf    pdfSigBs_11_BS_KKpi("pdfSigBs_11_BS_KKpi","pdfSigBs_11_BS_KKpi",pdfSigBs,parSigBsYield_11_BS_KKpi);
  RooExtendPdf    pdfSigBs_12_OS_KKpi("pdfSigBs_12_OS_KKpi","pdfSigBs_12_OS_KKpi",pdfSigBs,parSigBsYield_12_OS_KKpi);
  RooExtendPdf    pdfSigBs_12_SS_KKpi("pdfSigBs_12_SS_KKpi","pdfSigBs_12_SS_KKpi",pdfSigBs,parSigBsYield_12_SS_KKpi);
  RooExtendPdf    pdfSigBs_12_BS_KKpi("pdfSigBs_12_BS_KKpi","pdfSigBs_12_BS_KKpi",pdfSigBs,parSigBsYield_12_BS_KKpi);

  RooDecay        pdfBkgDsDTime("pdfBkgDsDTime","pdfBkgDsDTime",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
  RooProdPdf      pdfBkgDsD("pdfBkgDsD","pdfBkgDsD",RooArgList(pdfBkgDsDMass,pdfBkgDsDTime));

  RooRealVar      parBkgDsDFraction_11_OS("parBkgDsDFraction_11_OS","parBkgDsDFraction_11_OS",0.3);
  RooProduct      parBkgDsDYield_11_OS_Kpipi("parBkgDsDYield_11_OS_Kpipi","parBkgDsDYield_11_OS_Kpipi",RooArgList(parBkgDsDYield_11_Kpipi,parBkgDsDFraction_11_OS));
  RooRealVar      parBkgDsDFraction_11_SS("parBkgDsDFraction_11_SS","parBkgDsDFraction_11_SS",0.3);
  RooProduct      parBkgDsDYield_11_SS_Kpipi("parBkgDsDYield_11_SS_Kpipi","parBkgDsDYield_11_SS_Kpipi",RooArgList(parBkgDsDYield_11_Kpipi,parBkgDsDFraction_11_SS));
  RooFormulaVar   parBkgDsDFraction_11_BS("parBkgDsDFraction_11_BS","parBkgDsDFraction_11_BS","1-@0-@1",RooArgList(parBkgDsDFraction_11_OS,parBkgDsDFraction_11_SS));
  RooProduct      parBkgDsDYield_11_BS_Kpipi("parBkgDsDYield_11_BS_Kpipi","parBkgDsDYield_11_BS_Kpipi",RooArgList(parBkgDsDYield_11_Kpipi,parBkgDsDFraction_11_BS));
  RooRealVar      parBkgDsDFraction_12_OS("parBkgDsDFraction_12_OS","parBkgDsDFraction_12_OS",0.3);
  RooProduct      parBkgDsDYield_12_OS_Kpipi("parBkgDsDYield_12_OS_Kpipi","parBkgDsDYield_12_OS_Kpipi",RooArgList(parBkgDsDYield_12_Kpipi,parBkgDsDFraction_12_OS));
  RooRealVar      parBkgDsDFraction_12_SS("parBkgDsDFraction_12_SS","parBkgDsDFraction_12_SS",0.3);
  RooProduct      parBkgDsDYield_12_SS_Kpipi("parBkgDsDYield_12_SS_Kpipi","parBkgDsDYield_12_SS_Kpipi",RooArgList(parBkgDsDYield_12_Kpipi,parBkgDsDFraction_12_SS));  
  RooFormulaVar   parBkgDsDFraction_12_BS("parBkgDsDFraction_12_BS","parBkgDsDFraction_12_BS","1-@0-@1",RooArgList(parBkgDsDFraction_12_OS,parBkgDsDFraction_12_SS));
  RooProduct      parBkgDsDYield_12_BS_Kpipi("parBkgDsDYield_12_BS_Kpipi","parBkgDsDYield_12_BS_Kpipi",RooArgList(parBkgDsDYield_12_Kpipi,parBkgDsDFraction_12_BS));
  RooProduct      parBkgDsDYield_11_OS_KKpi("parBkgDsDYield_11_OS_KKpi","parBkgDsDYield_11_OS_KKpi",RooArgList(parBkgDsDYield_11_KKpi,parBkgDsDFraction_11_OS));
  RooProduct      parBkgDsDYield_11_SS_KKpi("parBkgDsDYield_11_SS_KKpi","parBkgDsDYield_11_SS_KKpi",RooArgList(parBkgDsDYield_11_KKpi,parBkgDsDFraction_11_SS));
  RooProduct      parBkgDsDYield_11_BS_KKpi("parBkgDsDYield_11_BS_KKpi","parBkgDsDYield_11_BS_KKpi",RooArgList(parBkgDsDYield_11_KKpi,parBkgDsDFraction_11_BS));
  RooProduct      parBkgDsDYield_12_OS_KKpi("parBkgDsDYield_12_OS_KKpi","parBkgDsDYield_12_OS_KKpi",RooArgList(parBkgDsDYield_12_KKpi,parBkgDsDFraction_12_OS));
  RooProduct      parBkgDsDYield_12_SS_KKpi("parBkgDsDYield_12_SS_KKpi","parBkgDsDYield_12_SS_KKpi",RooArgList(parBkgDsDYield_12_KKpi,parBkgDsDFraction_12_SS));  
  RooProduct      parBkgDsDYield_12_BS_KKpi("parBkgDsDYield_12_BS_KKpi","parBkgDsDYield_12_BS_KKpi",RooArgList(parBkgDsDYield_12_KKpi,parBkgDsDFraction_12_BS));

  RooExtendPdf    pdfBkgDsD_11_OS_Kpipi("pdfBkgDsD_11_OS_Kpipi","pdfBkgDsD_11_OS_Kpipi",pdfBkgDsD,parBkgDsDYield_11_OS_Kpipi);
  RooExtendPdf    pdfBkgDsD_11_SS_Kpipi("pdfBkgDsD_11_SS_Kpipi","pdfBkgDsD_11_SS_Kpipi",pdfBkgDsD,parBkgDsDYield_11_SS_Kpipi);
  RooExtendPdf    pdfBkgDsD_11_BS_Kpipi("pdfBkgDsD_11_BS_Kpipi","pdfBkgDsD_11_BS_Kpipi",pdfBkgDsD,parBkgDsDYield_11_BS_Kpipi);
  RooExtendPdf    pdfBkgDsD_12_OS_Kpipi("pdfBkgDsD_12_OS_Kpipi","pdfBkgDsD_12_OS_Kpipi",pdfBkgDsD,parBkgDsDYield_12_OS_Kpipi);
  RooExtendPdf    pdfBkgDsD_12_SS_Kpipi("pdfBkgDsD_12_SS_Kpipi","pdfBkgDsD_12_SS_Kpipi",pdfBkgDsD,parBkgDsDYield_12_SS_Kpipi);
  RooExtendPdf    pdfBkgDsD_12_BS_Kpipi("pdfBkgDsD_12_BS_Kpipi","pdfBkgDsD_12_BS_Kpipi",pdfBkgDsD,parBkgDsDYield_12_BS_Kpipi);
  RooExtendPdf    pdfBkgDsD_11_OS_KKpi("pdfBkgDsD_11_OS_KKpi","pdfBkgDsD_11_OS_KKpi",pdfBkgDsD,parBkgDsDYield_11_OS_KKpi);
  RooExtendPdf    pdfBkgDsD_11_SS_KKpi("pdfBkgDsD_11_SS_KKpi","pdfBkgDsD_11_SS_KKpi",pdfBkgDsD,parBkgDsDYield_11_SS_KKpi);
  RooExtendPdf    pdfBkgDsD_11_BS_KKpi("pdfBkgDsD_11_BS_KKpi","pdfBkgDsD_11_BS_KKpi",pdfBkgDsD,parBkgDsDYield_11_BS_KKpi);
  RooExtendPdf    pdfBkgDsD_12_OS_KKpi("pdfBkgDsD_12_OS_KKpi","pdfBkgDsD_12_OS_KKpi",pdfBkgDsD,parBkgDsDYield_12_OS_KKpi);
  RooExtendPdf    pdfBkgDsD_12_SS_KKpi("pdfBkgDsD_12_SS_KKpi","pdfBkgDsD_12_SS_KKpi",pdfBkgDsD,parBkgDsDYield_12_SS_KKpi);
  RooExtendPdf    pdfBkgDsD_12_BS_KKpi("pdfBkgDsD_12_BS_KKpi","pdfBkgDsD_12_BS_KKpi",pdfBkgDsD,parBkgDsDYield_12_BS_KKpi);

  // Background Decay Time PDF
  RooGaussModel   pdfBkgResolution("pdfBkgResolution","pdfBkgResolution",obsTime,RooConst(0),RooConst(0.05));
  RooRealVar      parBkgTimeTauOne("parBkgTimeTauOne","parBkgTimeTauOne",0.4);
  RooDecay        pdfBkgTimeOne("pdfBkgTimeOne","pdfBkgTimeOne",obsTime,parBkgTimeTauOne,pdfBkgResolution,RooDecay::SingleSided);
  RooRealVar      parBkgTimeTauTwo("parBkgTimeTauTwo","parBkgTimeTauTwo",1.0);
  RooDecay        pdfBkgTimeTwo("pdfBkgTimeTwo","pdfBkgTimeTwo",obsTime,parBkgTimeTauTwo,pdfBkgResolution,RooDecay::SingleSided);
  RooRealVar      parBkgTimeFraction("parBkgTimeFraction","parBkgTimeFraction",0.8);
  RooAddPdf       pdfBkgTime("pdfBkgTime","pdfBkgTime",RooArgList(pdfBkgTimeTwo,pdfBkgTimeOne),parBkgTimeFraction);

  RooProdPdf      pdfBkg_Kpipi("pdfBkg_Kpipi","pdfBkg_Kpipi",RooArgList(pdfBkgMass_Kpipi,pdfBkgTime));
  RooProdPdf      pdfBkg_KKpi("pdfBkg_KKpi","pdfBkg_KKpi",RooArgList(pdfBkgMass_KKpi,pdfBkgTime));

  RooRealVar      parBkgFraction_11_OS("parBkgFraction_11_OS","parBkgFraction_11_OS",0.3);
  RooProduct      parBkgYield_11_OS_Kpipi("parBkgYield_11_OS_Kpipi","parBkgYield_11_OS_Kpipi",RooArgList(parBkgYield_11_Kpipi,parBkgFraction_11_OS));
  RooRealVar      parBkgFraction_11_SS("parBkgFraction_11_SS","parBkgFraction_11_SS",0.3);
  RooProduct      parBkgYield_11_SS_Kpipi("parBkgYield_11_SS_Kpipi","parBkgYield_11_SS_Kpipi",RooArgList(parBkgYield_11_Kpipi,parBkgFraction_11_SS));
  RooFormulaVar   parBkgFraction_11_BS("parBkgFraction_11_BS","parBkgFraction_11_BS","1-@0-@1",RooArgList(parBkgFraction_11_OS,parBkgFraction_11_SS));
  RooProduct      parBkgYield_11_BS_Kpipi("parBkgYield_11_BS_Kpipi","parBkgYield_11_BS_Kpipi",RooArgList(parBkgYield_11_Kpipi,parBkgFraction_11_BS));
  RooRealVar      parBkgFraction_12_OS("parBkgFraction_12_OS","parBkgFraction_12_OS",0.3);
  RooProduct      parBkgYield_12_OS_Kpipi("parBkgYield_12_OS_Kpipi","parBkgYield_12_OS_Kpipi",RooArgList(parBkgYield_12_Kpipi,parBkgFraction_12_OS));
  RooRealVar      parBkgFraction_12_SS("parBkgFraction_12_SS","parBkgFraction_12_SS",0.3);
  RooProduct      parBkgYield_12_SS_Kpipi("parBkgYield_12_SS_Kpipi","parBkgYield_12_SS_Kpipi",RooArgList(parBkgYield_12_Kpipi,parBkgFraction_12_SS));  
  RooFormulaVar   parBkgFraction_12_BS("parBkgFraction_12_BS","parBkgFraction_12_BS","1-@0-@1",RooArgList(parBkgFraction_12_OS,parBkgFraction_12_SS));
  RooProduct      parBkgYield_12_BS_Kpipi("parBkgYield_12_BS_Kpipi","parBkgYield_12_BS_Kpipi",RooArgList(parBkgYield_12_Kpipi,parBkgFraction_12_BS));
  RooProduct      parBkgYield_11_OS_KKpi("parBkgYield_11_OS_KKpi","parBkgYield_11_OS_KKpi",RooArgList(parBkgYield_11_KKpi,parBkgFraction_11_OS));
  RooProduct      parBkgYield_11_SS_KKpi("parBkgYield_11_SS_KKpi","parBkgYield_11_SS_KKpi",RooArgList(parBkgYield_11_KKpi,parBkgFraction_11_SS));
  RooProduct      parBkgYield_11_BS_KKpi("parBkgYield_11_BS_KKpi","parBkgYield_11_BS_KKpi",RooArgList(parBkgYield_11_KKpi,parBkgFraction_11_BS));
  RooProduct      parBkgYield_12_OS_KKpi("parBkgYield_12_OS_KKpi","parBkgYield_12_OS_KKpi",RooArgList(parBkgYield_12_KKpi,parBkgFraction_12_OS));
  RooProduct      parBkgYield_12_SS_KKpi("parBkgYield_12_SS_KKpi","parBkgYield_12_SS_KKpi",RooArgList(parBkgYield_12_KKpi,parBkgFraction_12_SS));  
  RooProduct      parBkgYield_12_BS_KKpi("parBkgYield_12_BS_KKpi","parBkgYield_12_BS_KKpi",RooArgList(parBkgYield_12_KKpi,parBkgFraction_12_BS));

  RooExtendPdf    pdfBkg_11_OS_Kpipi("pdfBkg_11_OS_Kpipi","pdfBkg_11_OS_Kpipi",pdfBkg_Kpipi,parBkgYield_11_OS_Kpipi);
  RooExtendPdf    pdfBkg_11_SS_Kpipi("pdfBkg_11_SS_Kpipi","pdfBkg_11_SS_Kpipi",pdfBkg_Kpipi,parBkgYield_11_SS_Kpipi);
  RooExtendPdf    pdfBkg_11_BS_Kpipi("pdfBkg_11_BS_Kpipi","pdfBkg_11_BS_Kpipi",pdfBkg_Kpipi,parBkgYield_11_BS_Kpipi);
  RooExtendPdf    pdfBkg_12_OS_Kpipi("pdfBkg_12_OS_Kpipi","pdfBkg_12_OS_Kpipi",pdfBkg_Kpipi,parBkgYield_12_OS_Kpipi);
  RooExtendPdf    pdfBkg_12_SS_Kpipi("pdfBkg_12_SS_Kpipi","pdfBkg_12_SS_Kpipi",pdfBkg_Kpipi,parBkgYield_12_SS_Kpipi);
  RooExtendPdf    pdfBkg_12_BS_Kpipi("pdfBkg_12_BS_Kpipi","pdfBkg_12_BS_Kpipi",pdfBkg_Kpipi,parBkgYield_12_BS_Kpipi);
  RooExtendPdf    pdfBkg_11_OS_KKpi("pdfBkg_11_OS_KKpi","pdfBkg_11_OS_KKpi",pdfBkg_KKpi,parBkgYield_11_OS_KKpi);
  RooExtendPdf    pdfBkg_11_SS_KKpi("pdfBkg_11_SS_KKpi","pdfBkg_11_SS_KKpi",pdfBkg_KKpi,parBkgYield_11_SS_KKpi);
  RooExtendPdf    pdfBkg_11_BS_KKpi("pdfBkg_11_BS_KKpi","pdfBkg_11_BS_KKpi",pdfBkg_KKpi,parBkgYield_11_BS_KKpi);
  RooExtendPdf    pdfBkg_12_OS_KKpi("pdfBkg_12_OS_KKpi","pdfBkg_12_OS_KKpi",pdfBkg_KKpi,parBkgYield_12_OS_KKpi);
  RooExtendPdf    pdfBkg_12_SS_KKpi("pdfBkg_12_SS_KKpi","pdfBkg_12_SS_KKpi",pdfBkg_KKpi,parBkgYield_12_SS_KKpi);
  RooExtendPdf    pdfBkg_12_BS_KKpi("pdfBkg_12_BS_KKpi","pdfBkg_12_BS_KKpi",pdfBkg_KKpi,parBkgYield_12_BS_KKpi);

  RooAddPdf       pdf_11_OS_Kpipi("pdf_11_OS_Kpipi","pdf_11_OS_Kpipi",RooArgList(pdfSig_11_OS_Kpipi,pdfSigBs_11_OS_Kpipi,pdfBkgDsD_11_OS_Kpipi,pdfBkg_11_OS_Kpipi));
  RooAddPdf       pdf_11_SS_Kpipi("pdf_11_SS_Kpipi","pdf_11_SS_Kpipi",RooArgList(pdfSig_11_SS_Kpipi,pdfSigBs_11_SS_Kpipi,pdfBkgDsD_11_SS_Kpipi,pdfBkg_11_SS_Kpipi));
  RooAddPdf       pdf_11_BS_Kpipi("pdf_11_BS_Kpipi","pdf_11_BS_Kpipi",RooArgList(pdfSig_11_BS_Kpipi,pdfSigBs_11_BS_Kpipi,pdfBkgDsD_11_BS_Kpipi,pdfBkg_11_BS_Kpipi));
  RooAddPdf       pdf_12_OS_Kpipi("pdf_12_OS_Kpipi","pdf_12_OS_Kpipi",RooArgList(pdfSig_12_OS_Kpipi,pdfSigBs_12_OS_Kpipi,pdfBkgDsD_12_OS_Kpipi,pdfBkg_12_OS_Kpipi));
  RooAddPdf       pdf_12_SS_Kpipi("pdf_12_SS_Kpipi","pdf_12_SS_Kpipi",RooArgList(pdfSig_12_SS_Kpipi,pdfSigBs_12_SS_Kpipi,pdfBkgDsD_12_SS_Kpipi,pdfBkg_12_SS_Kpipi));
  RooAddPdf       pdf_12_BS_Kpipi("pdf_12_BS_Kpipi","pdf_12_BS_Kpipi",RooArgList(pdfSig_12_BS_Kpipi,pdfSigBs_12_BS_Kpipi,pdfBkgDsD_12_BS_Kpipi,pdfBkg_12_BS_Kpipi));
  RooAddPdf       pdf_11_OS_KKpi("pdf_11_OS_KKpi","pdf_11_OS_KKpi",RooArgList(pdfSig_11_OS_KKpi,pdfSigBs_11_OS_KKpi,pdfBkgDsD_11_OS_KKpi,pdfBkg_11_OS_KKpi));
  RooAddPdf       pdf_11_SS_KKpi("pdf_11_SS_KKpi","pdf_11_SS_KKpi",RooArgList(pdfSig_11_SS_KKpi,pdfSigBs_11_SS_KKpi,pdfBkgDsD_11_SS_KKpi,pdfBkg_11_SS_KKpi));
  RooAddPdf       pdf_11_BS_KKpi("pdf_11_BS_KKpi","pdf_11_BS_KKpi",RooArgList(pdfSig_11_BS_KKpi,pdfSigBs_11_BS_KKpi,pdfBkgDsD_11_BS_KKpi,pdfBkg_11_BS_KKpi));
  RooAddPdf       pdf_12_OS_KKpi("pdf_12_OS_KKpi","pdf_12_OS_KKpi",RooArgList(pdfSig_12_OS_KKpi,pdfSigBs_12_OS_KKpi,pdfBkgDsD_12_OS_KKpi,pdfBkg_12_OS_KKpi));
  RooAddPdf       pdf_12_SS_KKpi("pdf_12_SS_KKpi","pdf_12_SS_KKpi",RooArgList(pdfSig_12_SS_KKpi,pdfSigBs_12_SS_KKpi,pdfBkgDsD_12_SS_KKpi,pdfBkg_12_SS_KKpi));
  RooAddPdf       pdf_12_BS_KKpi("pdf_12_BS_KKpi","pdf_12_BS_KKpi",RooArgList(pdfSig_12_BS_KKpi,pdfSigBs_12_BS_KKpi,pdfBkgDsD_12_BS_KKpi,pdfBkg_12_BS_KKpi));

  RooSuperCategory  supercategory_generate("supercategory_generate","supercategory_generate",RooArgList(catYear,catTag,catDDFinalStateParticles));
  RooSimultaneous   pdf_generate("pdf_generate","P",supercategory_generate);
  pdf_generate.addPdf(pdf_11_OS_Kpipi,"{2011;OS;Kpipi}");
  pdf_generate.addPdf(pdf_11_SS_Kpipi,"{2011;SS;Kpipi}");
  pdf_generate.addPdf(pdf_11_BS_Kpipi,"{2011;both;Kpipi}");
  pdf_generate.addPdf(pdf_12_OS_Kpipi,"{2012;OS;Kpipi}");
  pdf_generate.addPdf(pdf_12_SS_Kpipi,"{2012;SS;Kpipi}");
  pdf_generate.addPdf(pdf_12_BS_Kpipi,"{2012;both;Kpipi}");
  pdf_generate.addPdf(pdf_11_OS_KKpi,"{2011;OS;KKpi}");
  pdf_generate.addPdf(pdf_11_SS_KKpi,"{2011;SS;KKpi}");
  pdf_generate.addPdf(pdf_11_BS_KKpi,"{2011;both;KKpi}");
  pdf_generate.addPdf(pdf_12_OS_KKpi,"{2012;OS;KKpi}");
  pdf_generate.addPdf(pdf_12_SS_KKpi,"{2012;SS;KKpi}");
  pdf_generate.addPdf(pdf_12_BS_KKpi,"{2012;both;KKpi}");

  // Workspace initializing
  RooWorkspace* ws = new RooWorkspace("ws");
  ws->import(pdf_generate);
  ws->defineSet("observables",observables);

  doofit::config::CommonConfig cfg_com("common");
  cfg_com.InitializeOptions(argc, argv);

  ToyFactoryStdConfig cfg_tfac("toyfac");
  cfg_tfac.InitializeOptions(cfg_com);

  ToyStudyStdConfig cfg_tstudy_mass("toystudy_mass");
  cfg_tstudy_mass.InitializeOptions(cfg_tfac);

  ToyStudyStdConfig cfg_tstudy_time("toystudy_time");
  cfg_tstudy_time.InitializeOptions(cfg_tstudy_mass);

  cfg_com.CheckHelpFlagAndPrintHelp();

  ws->Print();

  cfg_tfac.set_workspace(ws);

  ToyFactoryStd tfac(cfg_com, cfg_tfac);

  cfg_com.PrintAll();

  RooDataSet* data = NULL;
  RooDataSet* data_sweighted = NULL;
  PlotConfig cfg_plot("cfg_plot");
  ToyStudyStd tstudy_mass(cfg_com, cfg_tstudy_mass, cfg_plot);
  ToyStudyStd tstudy_time(cfg_com, cfg_tstudy_time, cfg_plot);

  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
  fitting_args.Add((TObject*)(new RooCmdArg(Hesse(true))));
  if (cp_fit && !pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS)))));
  if (!cp_fit && pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsTimeErr)))));
  if (cp_fit && pereventresolution)  fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS,obsTimeErr)))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Offset(true))));

  if (method.EqualTo("generate")) {
    
    SPlotFit2* splotfit;
    RooFitResult* fit_result;
    TStopwatch  stopwatch;
    RooArgSet set_of_yields;
    RooRealVar SigWeight_11_Kpipi("parSigYield_11_Kpipi_sw","signal weight for 11 Kpipi",-10,10);
    RooRealVar SigWeight_11_KKpi("parSigYield_11_KKpi_sw","signal weight for 11 KKpi",-10,10);
    RooRealVar SigWeight_12_Kpipi("parSigYield_12_Kpipi_sw","signal weight for 12 Kpipi",-10,10);
    RooRealVar SigWeight_12_KKpi("parSigYield_12_KKpi_sw","signal weight for 12 KKpi",-10,10);
    RooFormulaVar sum_of_signal_weights_year_finalstate("sum_of_signal_weights_year_finalstate","sum of signal weights","@0+@1+@2+@3",RooArgList(SigWeight_11_Kpipi,SigWeight_11_KKpi,SigWeight_12_Kpipi,SigWeight_12_KKpi));
    RooRealVar SigWeight_11("parSigYield_11_sw","signal weight for 11",-10,10);
    RooRealVar SigWeight_12("parSigYield_12_sw","signal weight for 12",-10,10);
    RooFormulaVar sum_of_signal_weights_year("sum_of_signal_weights_year","sum of signal weights","@0+@1",RooArgList(SigWeight_11,SigWeight_12));
    RooRealVar SigWeight_Kpipi("parSigYield_Kpipi_sw","signal weight for Kpipi",-10,10);
    RooRealVar SigWeight_KKpi("parSigYield_KKpi_sw","signal weight for KKpi",-10,10);
    RooFormulaVar sum_of_signal_weights_finalstate("sum_of_signal_weights_finalstate","sum of signal weights","@0+@1",RooArgList(SigWeight_Kpipi,SigWeight_KKpi));
    RooRealVar SigWeight_single("parSigYield_sw","signal weight",-10,10);
    if (split_years) {
      if (split_final_state) {
            set_of_yields.add(RooArgSet(parSigYield_11_Kpipi,parBkgDsDYield_11_Kpipi,parSigBsYield_11_Kpipi,parBkgYield_11_Kpipi));
            set_of_yields.add(RooArgSet(parSigYield_11_KKpi,parBkgDsDYield_11_KKpi,parSigBsYield_11_KKpi,parBkgYield_11_KKpi));
            set_of_yields.add(RooArgSet(parSigYield_12_Kpipi,parBkgDsDYield_12_Kpipi,parSigBsYield_12_Kpipi,parBkgYield_12_Kpipi));
            set_of_yields.add(RooArgSet(parSigYield_12_KKpi,parBkgDsDYield_12_KKpi,parSigBsYield_12_KKpi,parBkgYield_12_KKpi));
      }
      else {
            set_of_yields.add(RooArgSet(parSigYield_11,parBkgDsDYield_11,parSigBsYield_11,parBkgYield_11));
            set_of_yields.add(RooArgSet(parSigYield_12,parBkgDsDYield_12,parSigBsYield_12,parBkgYield_12));
      }
    }
    else if (split_final_state) {
      set_of_yields.add(RooArgSet(parSigYield_Kpipi,parBkgDsDYield_Kpipi,parSigBsYield_Kpipi,parBkgYield_Kpipi));
      set_of_yields.add(RooArgSet(parSigYield_KKpi,parBkgDsDYield_KKpi,parSigBsYield_KKpi,parBkgYield_KKpi));
    }
    else set_of_yields.add(parSigYield);
    for (int i = 0; i < 20 ; ++i) {
      cout  <<  i <<  endl;
      try {
        data = tfac.Generate();
        ws->allVars().readFromFile("/home/fmeier/storage03/Systematics/ProdAsymm/generation.par");
        pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
        splotfit = new SPlotFit2(*pdfMass,*data,set_of_yields);
        splotfit->set_use_minos(false);
        splotfit->set_num_cpu(config.getInt("num_cpu"));
        fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
        fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
        RooMsgService::instance().setStreamStatus(0, false);
        RooMsgService::instance().setStreamStatus(1, false);
        stopwatch.Start(true);
        splotfit->Fit();
        stopwatch.Stop();
        RooMsgService::instance().setStreamStatus(0, true);
        RooMsgService::instance().setStreamStatus(1, true);
        tstudy_mass.StoreFitResult(splotfit->get_fit_result(), NULL, &stopwatch);     
        
        if (split_years && split_final_state) {
          data->addColumn(sum_of_signal_weights_year_finalstate);
          data_sweighted = new RooDataSet("data_sweighted","data_sweighted",data,*(data->get()),TString(catTag.GetName())+"!=0","sum_of_signal_weights_year_finalstate");
        }
        else if (split_years) {
          data->addColumn(sum_of_signal_weights_year);
          data_sweighted = new RooDataSet("data_sweighted","data_sweighted",data,*(data->get()),TString(catTag.GetName())+"!=0","sum_of_signal_weights_year");
        }
        else if (split_final_state) {
          data->addColumn(sum_of_signal_weights_finalstate);
          data_sweighted = new RooDataSet("data_sweighted","data_sweighted",data,*(data->get()),TString(catTag.GetName())+"!=0","sum_of_signal_weights_finalstate");
        }
        else {
          data->addColumn(SigWeight_single);
          data_sweighted = new RooDataSet("data_sweighted","data_sweighted",data,*(data->get()),TString(catTag.GetName())+"!=0","parSigYield_sw");
        }
        data_sweighted->Print();
        pdfTime.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
        pdfTime.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
        pdfTime.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Acceptance_Splines.txt");
        pdfTime.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Acceptance_Splines_fixed.txt");
        TIterator*  iterator = constrainingPdfs.createIterator();
        RooAbsPdf*  constrainingPdf;
        while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
          constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
          constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
          // constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/StartingValues.txt");
        }
        parSigEtaDeltaProd_11.setVal(ws->var("parSigEtaDeltaProd_11")->getVal());
        parSigEtaDeltaProdOffset.setVal(ws->var("parSigEtaDeltaProdOffset")->getVal());
        parSigEtaDeltaP0_OS.setVal(ws->var("parSigEtaDeltaP0_OS")->getVal());
        parSigEtaDeltaP1_OS.setVal(ws->var("parSigEtaDeltaP1_OS")->getVal());
        parSigEtaDeltaP0_SS.setVal(ws->var("parSigEtaDeltaP0_SS")->getVal());
        parSigEtaDeltaP1_SS.setVal(ws->var("parSigEtaDeltaP1_SS")->getVal());
        parSigEtaP0_OS.setVal(ws->var("parSigEtaP0_OS")->getVal());
        parSigEtaP1_OS.setVal(ws->var("parSigEtaP1_OS")->getVal());
        parSigEtaP0_SS.setVal(ws->var("parSigEtaP0_SS")->getVal());
        parSigEtaP1_SS.setVal(ws->var("parSigEtaP1_SS")->getVal());
        fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(true))));
        fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
        stopwatch.Start(true);
        fit_result = pdfTime.fitTo(*data_sweighted,fitting_args);
        stopwatch.Stop();
        fit_result->Print("v");
        tstudy_time.StoreFitResult(fit_result, NULL, &stopwatch);
        delete data_sweighted;
      } catch (...) {
        i--;
      }
    }
  }

  if (method.EqualTo("evaluate")) {
    tstudy_mass.ReadFitResults();
    tstudy_mass.EvaluateFitResults();
    tstudy_mass.PlotEvaluatedParameters();
    tstudy_time.ReadFitResults();
    tstudy_time.EvaluateFitResults();
    tstudy_time.PlotEvaluatedParameters();
  }
  return 0;
}

TMatrixDSym CreateCovarianceMatrix(const int size, RooRealVar* p0sigma, RooRealVar* p1sigma, RooRealVar* p0p1corr, RooRealVar* dp0sigma, RooRealVar* dp1sigma, RooRealVar* p0dp0corr, RooRealVar* p0dp1corr, RooRealVar* p1dp0corr, RooRealVar* p1dp1corr, RooRealVar* dp0dp1corr){
  TMatrixDSym covariancematrix(size);
  covariancematrix[0][0] = pow(p0sigma->getVal(),2);
  covariancematrix[1][1] = pow(p1sigma->getVal(),2);
  covariancematrix[0][1] = p0sigma->getVal()*p1sigma->getVal()*p0p1corr->getVal();
  covariancematrix[1][0] = p0sigma->getVal()*p1sigma->getVal()*p0p1corr->getVal();
  if (size == 4) {
    covariancematrix[2][2] = pow(dp0sigma->getVal(),2);
    covariancematrix[3][3] = pow(dp1sigma->getVal(),2);
    covariancematrix[0][2] = p0sigma->getVal()*dp0sigma->getVal()*p0dp0corr->getVal();
    covariancematrix[2][0] = p0sigma->getVal()*dp0sigma->getVal()*p0dp0corr->getVal();
    covariancematrix[0][3] = p0sigma->getVal()*dp1sigma->getVal()*p0dp1corr->getVal();
    covariancematrix[3][0] = p0sigma->getVal()*dp1sigma->getVal()*p0dp1corr->getVal();
    covariancematrix[1][2] = p1sigma->getVal()*dp0sigma->getVal()*p1dp0corr->getVal();
    covariancematrix[2][1] = p1sigma->getVal()*dp0sigma->getVal()*p1dp0corr->getVal();
    covariancematrix[1][3] = p1sigma->getVal()*dp1sigma->getVal()*p1dp1corr->getVal();
    covariancematrix[3][1] = p1sigma->getVal()*dp1sigma->getVal()*p1dp1corr->getVal();
    covariancematrix[2][3] = dp0sigma->getVal()*dp1sigma->getVal()*dp0dp1corr->getVal();
    covariancematrix[3][2] = dp0sigma->getVal()*dp1sigma->getVal()*dp0dp1corr->getVal();
  }
  return covariancematrix;
}
