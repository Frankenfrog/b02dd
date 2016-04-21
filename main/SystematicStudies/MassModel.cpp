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
#include "RooDataHist.h"
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
#include "RooHistPdf.h"

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
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' -c toystudy_config_file_name" << std::endl;
    std::cout << "Toy study config is optional, and only needed for bootstrapping"  <<  std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  bool pereventresolution = config.getBool("pereventresolution");
  bool split_years      = config.getBool("split_years");
  bool split_final_state  = config.getBool("split_final_state");
  TString method = config.getString("method");

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
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
  // catTag.defineType("untagged",0);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);

  RooArgSet         observables(obsTime,obsMass,"observables");
  if (pereventresolution) observables.add(obsTimeErr);
  observables.add(obsEtaOS);
  observables.add(obsEtaSS);
  observables.add(obsTagOS);
  observables.add(obsTagSS);

  RooArgSet         categories(catYear,catTag,catDDFinalStateParticles,"categories");
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

  // Bd --> D*+ D- with D*+ --> D+ pi0 Background
  RooRealVar        parBkgDstDLowMassMean("parBkgDstDLowMassMean","Mean Mass",5060,5050,5070,"MeV/c^{2}");
  RooRealVar        parBkgDstDLowMassSigma("parBkgDstDLowMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDLowMass("pdfBkgDstDLowMass","Lower DstD Mass PDF",obsMass,parBkgDstDLowMassMean,parBkgDstDLowMassSigma);

  RooRealVar        parBkgDstDHighMassMean("parBkgDstDHighMassMean","Mean Mass",5120,5100,5140,"MeV/c^{2}");
  RooRealVar        parBkgDstDHighMassSigma("parBkgDstDHighMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDHighMass("pdfBkgDstDHighMass","Upper DstD Mass PDF",obsMass,parBkgDstDHighMassMean,parBkgDstDHighMassSigma);

  RooRealVar        parBkgDstDMassFraction("parBkgDstDMassFraction","fraction between low and high component",0.5,0,1);
  RooAddPdf         pdfBkgDstDMass("pdfBkgDstDMass","pdfBkgDstDMass",RooArgList(pdfBkgDstDLowMass,pdfBkgDstDHighMass),parBkgDstDMassFraction);

  // Bs --> DsD background
  RooFormulaVar     parBkgBsDsDMassMean("parBkgBsDsDMassMean","shifted Bs --> DsD Mean Mass","@0+87.35",RooArgList(parBkgDsDMean));
  RooCBShape        pdfBkgBsDsDMassCB1("pdfBkgBsDsDMassCB1","Mass PDF",obsMass,parBkgBsDsDMassMean,parBkgDsDMassSigma1,parBkgDsDMassCB1Alpha,parBkgDsDMassCB1Expo);
  RooCBShape        pdfBkgBsDsDMassCB2("pdfBkgBsDsDMassCB2","Mass PDF",obsMass,parBkgBsDsDMassMean,parBkgDsDMassSigma2,parBkgDsDMassCB2Alpha,parBkgDsDMassCB2Expo);
  RooAddPdf         pdfBkgBsDsDMass("pdfBkgBsDsDMass","pdfBkgBsDsDMass",RooArgList(pdfBkgBsDsDMassCB1,pdfBkgBsDsDMassCB2),parBkgDsDMassCBFraction);

  // Bs --> D*+ D- with D*+ --> D+ pi0 Background
  RooFormulaVar     parBkgBsDstDLowMassMean("parBkgBsDstDLowMassMean","Mean Mass","@0+87.35",RooArgList(parBkgDstDLowMassMean));
  RooGaussian       pdfBkgBsDstDLowMass("pdfBkgBsDstDLowMass","Lower DstD Mass PDF",obsMass,parBkgBsDstDLowMassMean,parBkgDstDLowMassSigma);

  RooFormulaVar     parBkgBsDstDHighMassMean("parBkgBsDstDHighMassMean","Mean Mass","@0+87.35",RooArgList(parBkgDstDHighMassMean));
  RooGaussian       pdfBkgBsDstDHighMass("pdfBkgBsDstDHighMass","Upper DstD Mass PDF",obsMass,parBkgBsDstDHighMassMean,parBkgDstDHighMassSigma);

  RooAddPdf         pdfBkgBsDstDMass("pdfBkgBsDstDMass","pdfBkgBsDstDMass",RooArgList(pdfBkgBsDstDLowMass,pdfBkgBsDstDHighMass),parBkgDstDMassFraction);  

  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  // charmless background
  RooRealVar        parBkgCharmlessSigma("parBkgCharmlessSigma","parBkgCharmlessSigma",10);
  RooGaussian       pdfBkgCharmlessMass("pdfBkgCharmlessMass","pdfBkgCharmlessMass",obsMass,parSigMassMean,parBkgCharmlessSigma);

//=========================================================================================================================================================================================================================

  RooRealVar        parSigYield_11_Kpipi("parSigYield_11_Kpipi","parSigYield_11_Kpipi",500,0,1000);
  RooRealVar        parSigYield_12_Kpipi("parSigYield_12_Kpipi","parSigYield_12_Kpipi",500,0,1000);
  RooRealVar        parSigYield_11_KKpi("parSigYield_11_KKpi","parSigYield_11_KKpi",500,0,1000);
  RooRealVar        parSigYield_12_KKpi("parSigYield_12_KKpi","parSigYield_12_KKpi",500,0,1000);

  RooRealVar        parBkgDsDYield_11_Kpipi("parBkgDsDYield_11_Kpipi","parBkgDsDYield_11_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_Kpipi("parBkgDsDYield_12_Kpipi","parBkgDsDYield_12_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_11_KKpi("parBkgDsDYield_11_KKpi","parBkgDsDYield_11_KKpi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_KKpi("parBkgDsDYield_12_KKpi","parBkgDsDYield_12_KKpi",1000,0,2000);

  RooRealVar        parBkgBsDsDYield_11_Kpipi("parBkgBsDsDYield_11_Kpipi","parBkgBsDsDYield_11_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12_Kpipi("parBkgBsDsDYield_12_Kpipi","parBkgBsDsDYield_12_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11_KKpi("parBkgBsDsDYield_11_KKpi","parBkgBsDsDYield_11_KKpi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12_KKpi("parBkgBsDsDYield_12_KKpi","parBkgBsDsDYield_12_KKpi",1000,0,2000);

  RooRealVar        parSigBsYield_11_Kpipi("parSigBsYield_11_Kpipi","parSigBsYield_11_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_12_Kpipi("parSigBsYield_12_Kpipi","parSigBsYield_12_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_11_KKpi("parSigBsYield_11_KKpi","parSigBsYield_11_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_12_KKpi("parSigBsYield_12_KKpi","parSigBsYield_12_KKpi",100,0,1000);

  RooRealVar        parBkgDstDYield_11_Kpipi("parBkgDstDYield_11_Kpipi","parBkgDstDYield_11_Kpipi",5000,0,10000);
  RooRealVar        parBkgDstDYield_12_Kpipi("parBkgDstDYield_12_Kpipi","parBkgDstDYield_12_Kpipi",5000,0,10000);
  RooRealVar        parBkgDstDYield_11_KKpi("parBkgDstDYield_11_KKpi","parBkgDstDYield_11_KKpi",5000,0,10000);
  RooRealVar        parBkgDstDYield_12_KKpi("parBkgDstDYield_12_KKpi","parBkgDstDYield_12_KKpi",5000,0,10000);

  RooRealVar        parBkgYield_11_Kpipi("parBkgYield_11_Kpipi","parBkgYield_11_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_12_Kpipi("parBkgYield_12_Kpipi","parBkgYield_12_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_11_KKpi("parBkgYield_11_KKpi","parBkgYield_11_KKpi",5000,0,10000);
  RooRealVar        parBkgYield_12_KKpi("parBkgYield_12_KKpi","parBkgYield_12_KKpi",5000,0,10000);

  RooExtendPdf      pdfSigExtend_11_Kpipi("pdfSigExtend_11_Kpipi","pdfSigExtend_11_Kpipi",pdfSigMass,parSigYield_11_Kpipi);
  RooExtendPdf      pdfSigExtend_12_Kpipi("pdfSigExtend_12_Kpipi","pdfSigExtend_12_Kpipi",pdfSigMass,parSigYield_12_Kpipi);
  RooExtendPdf      pdfSigExtend_11_KKpi("pdfSigExtend_11_KKpi","pdfSigExtend_11_KKpi",pdfSigMass,parSigYield_11_KKpi);
  RooExtendPdf      pdfSigExtend_12_KKpi("pdfSigExtend_12_KKpi","pdfSigExtend_12_KKpi",pdfSigMass,parSigYield_12_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_11_Kpipi("pdfBkgDsDExtend_11_Kpipi","pdfBkgDsDExtend_11_Kpipi",pdfBkgDsDMass,parBkgDsDYield_11_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_12_Kpipi("pdfBkgDsDExtend_12_Kpipi","pdfBkgDsDExtend_12_Kpipi",pdfBkgDsDMass,parBkgDsDYield_12_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_11_KKpi("pdfBkgDsDExtend_11_KKpi","pdfBkgDsDExtend_11_KKpi",pdfBkgDsDMass,parBkgDsDYield_11_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_12_KKpi("pdfBkgDsDExtend_12_KKpi","pdfBkgDsDExtend_12_KKpi",pdfBkgDsDMass,parBkgDsDYield_12_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_11_Kpipi("pdfBkgBsDsDExtend_11_Kpipi","pdfBkgBsDsDExtend_11_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_11_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_12_Kpipi("pdfBkgBsDsDExtend_12_Kpipi","pdfBkgBsDsDExtend_12_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_12_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_11_KKpi("pdfBkgBsDsDExtend_11_KKpi","pdfBkgBsDsDExtend_11_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_11_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_12_KKpi("pdfBkgBsDsDExtend_12_KKpi","pdfBkgBsDsDExtend_12_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_12_KKpi);  
  RooExtendPdf      pdfSigBsExtend_11_Kpipi("pdfSigBsExtend_11_Kpipi","pdfSigBsExtend_11_Kpipi",pdfSigBsMass,parSigBsYield_11_Kpipi);
  RooExtendPdf      pdfSigBsExtend_12_Kpipi("pdfSigBsExtend_12_Kpipi","pdfSigBsExtend_12_Kpipi",pdfSigBsMass,parSigBsYield_12_Kpipi);
  RooExtendPdf      pdfSigBsExtend_11_KKpi("pdfSigBsExtend_11_KKpi","pdfSigBsExtend_11_KKpi",pdfSigBsMass,parSigBsYield_11_KKpi);
  RooExtendPdf      pdfSigBsExtend_12_KKpi("pdfSigBsExtend_12_KKpi","pdfSigBsExtend_12_KKpi",pdfSigBsMass,parSigBsYield_12_KKpi);
  RooExtendPdf      pdfBkgDstDExtend_11_Kpipi("pdfBkgDstDExtend_11_Kpipi","pdfBkgDstDExtend_11_Kpipi",pdfBkgDstDMass,parBkgDstDYield_11_Kpipi);
  RooExtendPdf      pdfBkgDstDExtend_12_Kpipi("pdfBkgDstDExtend_12_Kpipi","pdfBkgDstDExtend_12_Kpipi",pdfBkgDstDMass,parBkgDstDYield_12_Kpipi);
  RooExtendPdf      pdfBkgDstDExtend_11_KKpi("pdfBkgDstDExtend_11_KKpi","pdfBkgDstDExtend_11_KKpi",pdfBkgDstDMass,parBkgDstDYield_11_KKpi);
  RooExtendPdf      pdfBkgDstDExtend_12_KKpi("pdfBkgDstDExtend_12_KKpi","pdfBkgDstDExtend_12_KKpi",pdfBkgDstDMass,parBkgDstDYield_12_KKpi);
  RooExtendPdf      pdfBkgExtend_11_Kpipi("pdfBkgExtend_11_Kpipi","pdfBkgExtend_11_Kpipi",pdfBkgMass,parBkgYield_11_Kpipi);
  RooExtendPdf      pdfBkgExtend_12_Kpipi("pdfBkgExtend_12_Kpipi","pdfBkgExtend_12_Kpipi",pdfBkgMass,parBkgYield_12_Kpipi);
  RooExtendPdf      pdfBkgExtend_11_KKpi("pdfBkgExtend_11_KKpi","pdfBkgExtend_11_KKpi",pdfBkgMass,parBkgYield_11_KKpi);
  RooExtendPdf      pdfBkgExtend_12_KKpi("pdfBkgExtend_12_KKpi","pdfBkgExtend_12_KKpi",pdfBkgMass,parBkgYield_12_KKpi);

  RooAddPdf         pdfMass_11_Kpipi("pdfMass_11_Kpipi","Mass PDF",RooArgList(pdfSigExtend_11_Kpipi,pdfBkgDsDExtend_11_Kpipi,pdfBkgBsDsDExtend_11_Kpipi,pdfSigBsExtend_11_Kpipi/*,pdfBkgDstDExtend_11_Kpipi*/,pdfBkgExtend_11_Kpipi));
  RooAddPdf         pdfMass_12_Kpipi("pdfMass_12_Kpipi","Mass PDF",RooArgList(pdfSigExtend_12_Kpipi,pdfBkgDsDExtend_12_Kpipi,pdfBkgBsDsDExtend_12_Kpipi,pdfSigBsExtend_12_Kpipi/*,pdfBkgDstDExtend_12_Kpipi*/,pdfBkgExtend_12_Kpipi));
  RooAddPdf         pdfMass_11_KKpi("pdfMass_11_KKpi","Mass PDF",RooArgList(pdfSigExtend_11_KKpi,pdfBkgDsDExtend_11_KKpi,pdfBkgBsDsDExtend_11_KKpi,pdfSigBsExtend_11_KKpi/*,pdfBkgDstDExtend_11_KKpi*/,pdfBkgExtend_11_KKpi));
  RooAddPdf         pdfMass_12_KKpi("pdfMass_12_KKpi","Mass PDF",RooArgList(pdfSigExtend_12_KKpi,pdfBkgDsDExtend_12_KKpi,pdfBkgBsDsDExtend_12_KKpi,pdfSigBsExtend_12_KKpi/*,pdfBkgDstDExtend_12_KKpi*/,pdfBkgExtend_12_KKpi));

  RooSuperCategory  supercategory_mass("supercategory_mass","supercategory_mass",RooArgList(catYear,catDDFinalStateParticles));
  RooSimultaneous   pdfMass("pdfMass","pdfMass",supercategory_mass);
  pdfMass.addPdf(pdfMass_11_Kpipi,"{2011;Kpipi}");
  pdfMass.addPdf(pdfMass_12_Kpipi,"{2012;Kpipi}");
  pdfMass.addPdf(pdfMass_11_KKpi,"{2011;KKpi}");
  pdfMass.addPdf(pdfMass_12_KKpi,"{2012;KKpi}");

//=========================================================================================================================================================================================================================
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
  
  RooRealVar          parSigEtaP0P1CorrelationCoeff_OS("parSigEtaP0P1CorrelationCoeff_OS","correlation coefficient between p0 and p1 OS",-0.102);
  RooRealVar          parSigEtaP0DeltaP0CorrelationCoeff_OS("parSigEtaP0DeltaP0CorrelationCoeff_OS","correlation coefficient between p0 and Delta p0 OS",0.036);
  RooRealVar          parSigEtaP0DeltaP1CorrelationCoeff_OS("parSigEtaP0DeltaP1CorrelationCoeff_OS","correlation coefficient between p0 and Delta p1 OS",0.001);
  RooRealVar          parSigEtaP1DeltaP0CorrelationCoeff_OS("parSigEtaP1DeltaP0CorrelationCoeff_OS","correlation coefficient between p1 and Delta p0 OS",-0.002);
  RooRealVar          parSigEtaP1DeltaP1CorrelationCoeff_OS("parSigEtaP1DeltaP1CorrelationCoeff_OS","correlation coefficient between p1 and Delta p1 OS",-0.037);
  RooRealVar          parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS("parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS","correlation coefficient between Delta p0 and Delta p1 OS",0.059);

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

  RooBDecay  pdfSigTime_11_OS("pdfSigTime_11_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_OS,parSigTimeSinh,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay  pdfSigTime_11_SS("pdfSigTime_11_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_SS,parSigTimeSinh,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay  pdfSigTime_12_OS("pdfSigTime_12_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_OS,parSigTimeSinh,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay  pdfSigTime_12_SS("pdfSigTime_12_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_SS,parSigTimeSinh,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay  pdfSigTime_11_BS("pdfSigTime_11_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_BS,parSigTimeSinh,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay  pdfSigTime_12_BS("pdfSigTime_12_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_BS,parSigTimeSinh,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);

//========================================================================================================================================================================================================================

  // Build Simultaneous PDF
  RooSuperCategory  supercategory_time("supercategory_time","supercategory_time",RooArgSet(catYear,catTag));
  RooSimultaneous   pdfTime("pdfTime","P",supercategory_time);
  pdfTime.addPdf(pdfSigTime_11_OS,"{2011;OS}");
  pdfTime.addPdf(pdfSigTime_11_SS,"{2011;SS}");
  pdfTime.addPdf(pdfSigTime_11_BS,"{2011;both}");
  pdfTime.addPdf(pdfSigTime_12_OS,"{2012;OS}");
  pdfTime.addPdf(pdfSigTime_12_SS,"{2012;SS}");
  pdfTime.addPdf(pdfSigTime_12_BS,"{2012;both}");

  cout  <<  "simultaneous PDF built"  <<  endl;

//========================================================================================================================================================================================================================

  // Signal PDF
  RooProdPdf      pdfSig_11_OS("pdfSig_11_OS","pdfSig_11_OS",RooArgList(pdfSigMass,pdfSigTime_11_OS));
  RooProdPdf      pdfSig_11_SS("pdfSig_11_SS","pdfSig_11_SS",RooArgList(pdfSigMass,pdfSigTime_11_SS));
  RooProdPdf      pdfSig_11_BS("pdfSig_11_BS","pdfSig_11_BS",RooArgList(pdfSigMass,pdfSigTime_11_BS));
  RooProdPdf      pdfSig_12_OS("pdfSig_12_OS","pdfSig_12_OS",RooArgList(pdfSigMass,pdfSigTime_12_OS));
  RooProdPdf      pdfSig_12_SS("pdfSig_12_SS","pdfSig_12_SS",RooArgList(pdfSigMass,pdfSigTime_12_SS));
  RooProdPdf      pdfSig_12_BS("pdfSig_12_BS","pdfSig_12_BS",RooArgList(pdfSigMass,pdfSigTime_12_BS));

  RooRealVar      parSigYield_11_Kpipi_OS("parSigYield_11_Kpipi_OS","parSigYield_11_Kpipi_OS",500,0,1000);
  RooRealVar      parSigYield_12_Kpipi_OS("parSigYield_12_Kpipi_OS","parSigYield_12_Kpipi_OS",500,0,1000);
  RooRealVar      parSigYield_11_KKpi_OS("parSigYield_11_KKpi_OS","parSigYield_11_KKpi_OS",500,0,1000);
  RooRealVar      parSigYield_12_KKpi_OS("parSigYield_12_KKpi_OS","parSigYield_12_KKpi_OS",500,0,1000);
  RooRealVar      parSigYield_11_Kpipi_SS("parSigYield_11_Kpipi_SS","parSigYield_11_Kpipi_SS",500,0,1000);
  RooRealVar      parSigYield_12_Kpipi_SS("parSigYield_12_Kpipi_SS","parSigYield_12_Kpipi_SS",500,0,1000);
  RooRealVar      parSigYield_11_KKpi_SS("parSigYield_11_KKpi_SS","parSigYield_11_KKpi_SS",500,0,1000);
  RooRealVar      parSigYield_12_KKpi_SS("parSigYield_12_KKpi_SS","parSigYield_12_KKpi_SS",500,0,1000);
  RooRealVar      parSigYield_11_Kpipi_BS("parSigYield_11_Kpipi_BS","parSigYield_11_Kpipi_BS",500,0,1000);
  RooRealVar      parSigYield_12_Kpipi_BS("parSigYield_12_Kpipi_BS","parSigYield_12_Kpipi_BS",500,0,1000);
  RooRealVar      parSigYield_11_KKpi_BS("parSigYield_11_KKpi_BS","parSigYield_11_KKpi_BS",500,0,1000);
  RooRealVar      parSigYield_12_KKpi_BS("parSigYield_12_KKpi_BS","parSigYield_12_KKpi_BS",500,0,1000);

  RooExtendPdf    pdfSig_11_Kpipi_OS("pdfSig_11_Kpipi_OS","pdfSig_11_Kpipi_OS",pdfSig_11_OS,parSigYield_11_Kpipi_OS);
  RooExtendPdf    pdfSig_11_Kpipi_SS("pdfSig_11_Kpipi_SS","pdfSig_11_Kpipi_SS",pdfSig_11_SS,parSigYield_11_Kpipi_SS);
  RooExtendPdf    pdfSig_11_Kpipi_BS("pdfSig_11_Kpipi_BS","pdfSig_11_Kpipi_BS",pdfSig_11_BS,parSigYield_11_Kpipi_BS);
  RooExtendPdf    pdfSig_12_Kpipi_OS("pdfSig_12_Kpipi_OS","pdfSig_12_Kpipi_OS",pdfSig_12_OS,parSigYield_12_Kpipi_OS);
  RooExtendPdf    pdfSig_12_Kpipi_SS("pdfSig_12_Kpipi_SS","pdfSig_12_Kpipi_SS",pdfSig_12_SS,parSigYield_12_Kpipi_SS);
  RooExtendPdf    pdfSig_12_Kpipi_BS("pdfSig_12_Kpipi_BS","pdfSig_12_Kpipi_BS",pdfSig_12_BS,parSigYield_12_Kpipi_BS);
  RooExtendPdf    pdfSig_11_KKpi_OS("pdfSig_11_KKpi_OS","pdfSig_11_KKpi_OS",pdfSig_11_OS,parSigYield_11_KKpi_OS);
  RooExtendPdf    pdfSig_11_KKpi_SS("pdfSig_11_KKpi_SS","pdfSig_11_KKpi_SS",pdfSig_11_SS,parSigYield_11_KKpi_SS);
  RooExtendPdf    pdfSig_11_KKpi_BS("pdfSig_11_KKpi_BS","pdfSig_11_KKpi_BS",pdfSig_11_BS,parSigYield_11_KKpi_BS);
  RooExtendPdf    pdfSig_12_KKpi_OS("pdfSig_12_KKpi_OS","pdfSig_12_KKpi_OS",pdfSig_12_OS,parSigYield_12_KKpi_OS);
  RooExtendPdf    pdfSig_12_KKpi_SS("pdfSig_12_KKpi_SS","pdfSig_12_KKpi_SS",pdfSig_12_SS,parSigYield_12_KKpi_SS);
  RooExtendPdf    pdfSig_12_KKpi_BS("pdfSig_12_KKpi_BS","pdfSig_12_KKpi_BS",pdfSig_12_BS,parSigYield_12_KKpi_BS);

  // Bs PDF
  RooRealVar      parBsTau("parBsTau","parBsTau",1.512);
  RooDecay        pdfBsTime("pdfBsTime","pdfBsTime",obsTime,parBsTau,*efficiencymodel,RooDecay::SingleSided);
  RooProdPdf      pdfSigBs("pdfSigBs","pdfSigBs",RooArgList(pdfSigBsMass,pdfBsTime));

  RooRealVar      parSigBsYield_11_Kpipi_OS("parSigBsYield_11_Kpipi_OS","parSigBsYield_11_Kpipi_OS",100,0,1000);
  RooRealVar      parSigBsYield_12_Kpipi_OS("parSigBsYield_12_Kpipi_OS","parSigBsYield_12_Kpipi_OS",100,0,1000);
  RooRealVar      parSigBsYield_11_KKpi_OS("parSigBsYield_11_KKpi_OS","parSigBsYield_11_KKpi_OS",100,0,1000);
  RooRealVar      parSigBsYield_12_KKpi_OS("parSigBsYield_12_KKpi_OS","parSigBsYield_12_KKpi_OS",100,0,1000);
  RooRealVar      parSigBsYield_11_Kpipi_SS("parSigBsYield_11_Kpipi_SS","parSigBsYield_11_Kpipi_SS",100,0,1000);
  RooRealVar      parSigBsYield_12_Kpipi_SS("parSigBsYield_12_Kpipi_SS","parSigBsYield_12_Kpipi_SS",100,0,1000);
  RooRealVar      parSigBsYield_11_KKpi_SS("parSigBsYield_11_KKpi_SS","parSigBsYield_11_KKpi_SS",100,0,1000);
  RooRealVar      parSigBsYield_12_KKpi_SS("parSigBsYield_12_KKpi_SS","parSigBsYield_12_KKpi_SS",100,0,1000);
  RooRealVar      parSigBsYield_11_Kpipi_BS("parSigBsYield_11_Kpipi_BS","parSigBsYield_11_Kpipi_BS",100,0,1000);
  RooRealVar      parSigBsYield_12_Kpipi_BS("parSigBsYield_12_Kpipi_BS","parSigBsYield_12_Kpipi_BS",100,0,1000);
  RooRealVar      parSigBsYield_11_KKpi_BS("parSigBsYield_11_KKpi_BS","parSigBsYield_11_KKpi_BS",100,0,1000);
  RooRealVar      parSigBsYield_12_KKpi_BS("parSigBsYield_12_KKpi_BS","parSigBsYield_12_KKpi_BS",100,0,1000);

  RooExtendPdf    pdfSigBs_11_Kpipi_OS("pdfSigBs_11_Kpipi_OS","pdfSigBs_11_Kpipi_OS",pdfSigBs,parSigBsYield_11_Kpipi_OS);
  RooExtendPdf    pdfSigBs_11_Kpipi_SS("pdfSigBs_11_Kpipi_SS","pdfSigBs_11_Kpipi_SS",pdfSigBs,parSigBsYield_11_Kpipi_SS);
  RooExtendPdf    pdfSigBs_11_Kpipi_BS("pdfSigBs_11_Kpipi_BS","pdfSigBs_11_Kpipi_BS",pdfSigBs,parSigBsYield_11_Kpipi_BS);
  RooExtendPdf    pdfSigBs_12_Kpipi_OS("pdfSigBs_12_Kpipi_OS","pdfSigBs_12_Kpipi_OS",pdfSigBs,parSigBsYield_12_Kpipi_OS);
  RooExtendPdf    pdfSigBs_12_Kpipi_SS("pdfSigBs_12_Kpipi_SS","pdfSigBs_12_Kpipi_SS",pdfSigBs,parSigBsYield_12_Kpipi_SS);
  RooExtendPdf    pdfSigBs_12_Kpipi_BS("pdfSigBs_12_Kpipi_BS","pdfSigBs_12_Kpipi_BS",pdfSigBs,parSigBsYield_12_Kpipi_BS);
  RooExtendPdf    pdfSigBs_11_KKpi_OS("pdfSigBs_11_KKpi_OS","pdfSigBs_11_KKpi_OS",pdfSigBs,parSigBsYield_11_KKpi_OS);
  RooExtendPdf    pdfSigBs_11_KKpi_SS("pdfSigBs_11_KKpi_SS","pdfSigBs_11_KKpi_SS",pdfSigBs,parSigBsYield_11_KKpi_SS);
  RooExtendPdf    pdfSigBs_11_KKpi_BS("pdfSigBs_11_KKpi_BS","pdfSigBs_11_KKpi_BS",pdfSigBs,parSigBsYield_11_KKpi_BS);
  RooExtendPdf    pdfSigBs_12_KKpi_OS("pdfSigBs_12_KKpi_OS","pdfSigBs_12_KKpi_OS",pdfSigBs,parSigBsYield_12_KKpi_OS);
  RooExtendPdf    pdfSigBs_12_KKpi_SS("pdfSigBs_12_KKpi_SS","pdfSigBs_12_KKpi_SS",pdfSigBs,parSigBsYield_12_KKpi_SS);
  RooExtendPdf    pdfSigBs_12_KKpi_BS("pdfSigBs_12_KKpi_BS","pdfSigBs_12_KKpi_BS",pdfSigBs,parSigBsYield_12_KKpi_BS);

  // B0 --> DsD PDF
  RooDecay        pdfBkgB0Time("pdfBkgB0Time","pdfBkgB0Time",obsTime,parSigTimeTau,*efficiencymodel,RooDecay::SingleSided);
  RooProdPdf      pdfBkgDsD("pdfBkgDsD","pdfBkgDsD",RooArgList(pdfBkgDsDMass,pdfBkgB0Time));

  RooRealVar      parBkgDsDYield_11_Kpipi_OS("parBkgDsDYield_11_Kpipi_OS","parBkgDsDYield_11_Kpipi_OS",1000,0,2000);
  RooRealVar      parBkgDsDYield_12_Kpipi_OS("parBkgDsDYield_12_Kpipi_OS","parBkgDsDYield_12_Kpipi_OS",1000,0,2000);
  RooRealVar      parBkgDsDYield_11_KKpi_OS("parBkgDsDYield_11_KKpi_OS","parBkgDsDYield_11_KKpi_OS",1000,0,2000);
  RooRealVar      parBkgDsDYield_12_KKpi_OS("parBkgDsDYield_12_KKpi_OS","parBkgDsDYield_12_KKpi_OS",1000,0,2000);
  RooRealVar      parBkgDsDYield_11_Kpipi_SS("parBkgDsDYield_11_Kpipi_SS","parBkgDsDYield_11_Kpipi_SS",1000,0,2000);
  RooRealVar      parBkgDsDYield_12_Kpipi_SS("parBkgDsDYield_12_Kpipi_SS","parBkgDsDYield_12_Kpipi_SS",1000,0,2000);
  RooRealVar      parBkgDsDYield_11_KKpi_SS("parBkgDsDYield_11_KKpi_SS","parBkgDsDYield_11_KKpi_SS",1000,0,2000);
  RooRealVar      parBkgDsDYield_12_KKpi_SS("parBkgDsDYield_12_KKpi_SS","parBkgDsDYield_12_KKpi_SS",1000,0,2000);
  RooRealVar      parBkgDsDYield_11_Kpipi_BS("parBkgDsDYield_11_Kpipi_BS","parBkgDsDYield_11_Kpipi_BS",1000,0,2000);
  RooRealVar      parBkgDsDYield_12_Kpipi_BS("parBkgDsDYield_12_Kpipi_BS","parBkgDsDYield_12_Kpipi_BS",1000,0,2000);
  RooRealVar      parBkgDsDYield_11_KKpi_BS("parBkgDsDYield_11_KKpi_BS","parBkgDsDYield_11_KKpi_BS",1000,0,2000);
  RooRealVar      parBkgDsDYield_12_KKpi_BS("parBkgDsDYield_12_KKpi_BS","parBkgDsDYield_12_KKpi_BS",1000,0,2000);

  RooExtendPdf    pdfBkgDsD_11_Kpipi_OS("pdfBkgDsD_11_Kpipi_OS","pdfBkgDsD_11_Kpipi_OS",pdfBkgDsD,parBkgDsDYield_11_Kpipi_OS);
  RooExtendPdf    pdfBkgDsD_11_Kpipi_SS("pdfBkgDsD_11_Kpipi_SS","pdfBkgDsD_11_Kpipi_SS",pdfBkgDsD,parBkgDsDYield_11_Kpipi_SS);
  RooExtendPdf    pdfBkgDsD_11_Kpipi_BS("pdfBkgDsD_11_Kpipi_BS","pdfBkgDsD_11_Kpipi_BS",pdfBkgDsD,parBkgDsDYield_11_Kpipi_BS);
  RooExtendPdf    pdfBkgDsD_12_Kpipi_OS("pdfBkgDsD_12_Kpipi_OS","pdfBkgDsD_12_Kpipi_OS",pdfBkgDsD,parBkgDsDYield_12_Kpipi_OS);
  RooExtendPdf    pdfBkgDsD_12_Kpipi_SS("pdfBkgDsD_12_Kpipi_SS","pdfBkgDsD_12_Kpipi_SS",pdfBkgDsD,parBkgDsDYield_12_Kpipi_SS);
  RooExtendPdf    pdfBkgDsD_12_Kpipi_BS("pdfBkgDsD_12_Kpipi_BS","pdfBkgDsD_12_Kpipi_BS",pdfBkgDsD,parBkgDsDYield_12_Kpipi_BS);
  RooExtendPdf    pdfBkgDsD_11_KKpi_OS("pdfBkgDsD_11_KKpi_OS","pdfBkgDsD_11_KKpi_OS",pdfBkgDsD,parBkgDsDYield_11_KKpi_OS);
  RooExtendPdf    pdfBkgDsD_11_KKpi_SS("pdfBkgDsD_11_KKpi_SS","pdfBkgDsD_11_KKpi_SS",pdfBkgDsD,parBkgDsDYield_11_KKpi_SS);
  RooExtendPdf    pdfBkgDsD_11_KKpi_BS("pdfBkgDsD_11_KKpi_BS","pdfBkgDsD_11_KKpi_BS",pdfBkgDsD,parBkgDsDYield_11_KKpi_BS);
  RooExtendPdf    pdfBkgDsD_12_KKpi_OS("pdfBkgDsD_12_KKpi_OS","pdfBkgDsD_12_KKpi_OS",pdfBkgDsD,parBkgDsDYield_12_KKpi_OS);
  RooExtendPdf    pdfBkgDsD_12_KKpi_SS("pdfBkgDsD_12_KKpi_SS","pdfBkgDsD_12_KKpi_SS",pdfBkgDsD,parBkgDsDYield_12_KKpi_SS);
  RooExtendPdf    pdfBkgDsD_12_KKpi_BS("pdfBkgDsD_12_KKpi_BS","pdfBkgDsD_12_KKpi_BS",pdfBkgDsD,parBkgDsDYield_12_KKpi_BS);

  // Bs --> DsD PDF
  RooProdPdf      pdfBkgBsDsD("pdfBkgBsDsD","pdfBkgBsDsD",RooArgList(pdfBkgBsDsDMass,pdfBsTime));

  RooRealVar      parBkgBsDsDYield_11_Kpipi_OS("parBkgBsDsDYield_11_Kpipi_OS","parBkgBsDsDYield_11_Kpipi_OS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_12_Kpipi_OS("parBkgBsDsDYield_12_Kpipi_OS","parBkgBsDsDYield_12_Kpipi_OS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_11_KKpi_OS("parBkgBsDsDYield_11_KKpi_OS","parBkgBsDsDYield_11_KKpi_OS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_12_KKpi_OS("parBkgBsDsDYield_12_KKpi_OS","parBkgBsDsDYield_12_KKpi_OS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_11_Kpipi_SS("parBkgBsDsDYield_11_Kpipi_SS","parBkgBsDsDYield_11_Kpipi_SS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_12_Kpipi_SS("parBkgBsDsDYield_12_Kpipi_SS","parBkgBsDsDYield_12_Kpipi_SS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_11_KKpi_SS("parBkgBsDsDYield_11_KKpi_SS","parBkgBsDsDYield_11_KKpi_SS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_12_KKpi_SS("parBkgBsDsDYield_12_KKpi_SS","parBkgBsDsDYield_12_KKpi_SS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_11_Kpipi_BS("parBkgBsDsDYield_11_Kpipi_BS","parBkgBsDsDYield_11_Kpipi_BS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_12_Kpipi_BS("parBkgBsDsDYield_12_Kpipi_BS","parBkgBsDsDYield_12_Kpipi_BS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_11_KKpi_BS("parBkgBsDsDYield_11_KKpi_BS","parBkgBsDsDYield_11_KKpi_BS",100,0,1000);
  RooRealVar      parBkgBsDsDYield_12_KKpi_BS("parBkgBsDsDYield_12_KKpi_BS","parBkgBsDsDYield_12_KKpi_BS",100,0,1000);

  RooExtendPdf    pdfBkgBsDsD_11_Kpipi_OS("pdfBkgBsDsD_11_Kpipi_OS","pdfBkgBsDsD_11_Kpipi_OS",pdfBkgBsDsD,parBkgBsDsDYield_11_Kpipi_OS);
  RooExtendPdf    pdfBkgBsDsD_12_Kpipi_OS("pdfBkgBsDsD_12_Kpipi_OS","pdfBkgBsDsD_12_Kpipi_OS",pdfBkgBsDsD,parBkgBsDsDYield_12_Kpipi_OS);
  RooExtendPdf    pdfBkgBsDsD_11_KKpi_OS("pdfBkgBsDsD_11_KKpi_OS","pdfBkgBsDsD_11_KKpi_OS",pdfBkgBsDsD,parBkgBsDsDYield_11_KKpi_OS);
  RooExtendPdf    pdfBkgBsDsD_12_KKpi_OS("pdfBkgBsDsD_12_KKpi_OS","pdfBkgBsDsD_12_KKpi_OS",pdfBkgBsDsD,parBkgBsDsDYield_12_KKpi_OS);
  RooExtendPdf    pdfBkgBsDsD_11_Kpipi_SS("pdfBkgBsDsD_11_Kpipi_SS","pdfBkgBsDsD_11_Kpipi_SS",pdfBkgBsDsD,parBkgBsDsDYield_11_Kpipi_SS);
  RooExtendPdf    pdfBkgBsDsD_12_Kpipi_SS("pdfBkgBsDsD_12_Kpipi_SS","pdfBkgBsDsD_12_Kpipi_SS",pdfBkgBsDsD,parBkgBsDsDYield_12_Kpipi_SS);
  RooExtendPdf    pdfBkgBsDsD_11_KKpi_SS("pdfBkgBsDsD_11_KKpi_SS","pdfBkgBsDsD_11_KKpi_SS",pdfBkgBsDsD,parBkgBsDsDYield_11_KKpi_SS);
  RooExtendPdf    pdfBkgBsDsD_12_KKpi_SS("pdfBkgBsDsD_12_KKpi_SS","pdfBkgBsDsD_12_KKpi_SS",pdfBkgBsDsD,parBkgBsDsDYield_12_KKpi_SS);
  RooExtendPdf    pdfBkgBsDsD_11_Kpipi_BS("pdfBkgBsDsD_11_Kpipi_BS","pdfBkgBsDsD_11_Kpipi_BS",pdfBkgBsDsD,parBkgBsDsDYield_11_Kpipi_BS);
  RooExtendPdf    pdfBkgBsDsD_12_Kpipi_BS("pdfBkgBsDsD_12_Kpipi_BS","pdfBkgBsDsD_12_Kpipi_BS",pdfBkgBsDsD,parBkgBsDsDYield_12_Kpipi_BS);
  RooExtendPdf    pdfBkgBsDsD_11_KKpi_BS("pdfBkgBsDsD_11_KKpi_BS","pdfBkgBsDsD_11_KKpi_BS",pdfBkgBsDsD,parBkgBsDsDYield_11_KKpi_BS);
  RooExtendPdf    pdfBkgBsDsD_12_KKpi_BS("pdfBkgBsDsD_12_KKpi_BS","pdfBkgBsDsD_12_KKpi_BS",pdfBkgBsDsD,parBkgBsDsDYield_12_KKpi_BS);

  // B0 --> D*D PDF
  RooProdPdf      pdfBkgDstD("pdfBkgDstD","pdfBkgDstD",RooArgList(pdfBkgDstDMass,pdfBkgB0Time));

  RooRealVar      parBkgDstDYield_11_Kpipi_OS("parBkgDstDYield_11_Kpipi_OS","parBkgDstDYield_11_Kpipi_OS",5000,0,10000);
  RooRealVar      parBkgDstDYield_12_Kpipi_OS("parBkgDstDYield_12_Kpipi_OS","parBkgDstDYield_12_Kpipi_OS",5000,0,10000);
  RooRealVar      parBkgDstDYield_11_KKpi_OS("parBkgDstDYield_11_KKpi_OS","parBkgDstDYield_11_KKpi_OS",5000,0,10000);
  RooRealVar      parBkgDstDYield_12_KKpi_OS("parBkgDstDYield_12_KKpi_OS","parBkgDstDYield_12_KKpi_OS",5000,0,10000);
  RooRealVar      parBkgDstDYield_11_Kpipi_SS("parBkgDstDYield_11_Kpipi_SS","parBkgDstDYield_11_Kpipi_SS",5000,0,10000);
  RooRealVar      parBkgDstDYield_12_Kpipi_SS("parBkgDstDYield_12_Kpipi_SS","parBkgDstDYield_12_Kpipi_SS",5000,0,10000);
  RooRealVar      parBkgDstDYield_11_KKpi_SS("parBkgDstDYield_11_KKpi_SS","parBkgDstDYield_11_KKpi_SS",5000,0,10000);
  RooRealVar      parBkgDstDYield_12_KKpi_SS("parBkgDstDYield_12_KKpi_SS","parBkgDstDYield_12_KKpi_SS",5000,0,10000);
  RooRealVar      parBkgDstDYield_11_Kpipi_BS("parBkgDstDYield_11_Kpipi_BS","parBkgDstDYield_11_Kpipi_BS",5000,0,10000);
  RooRealVar      parBkgDstDYield_12_Kpipi_BS("parBkgDstDYield_12_Kpipi_BS","parBkgDstDYield_12_Kpipi_BS",5000,0,10000);
  RooRealVar      parBkgDstDYield_11_KKpi_BS("parBkgDstDYield_11_KKpi_BS","parBkgDstDYield_11_KKpi_BS",5000,0,10000);
  RooRealVar      parBkgDstDYield_12_KKpi_BS("parBkgDstDYield_12_KKpi_BS","parBkgDstDYield_12_KKpi_BS",5000,0,10000);

  RooExtendPdf    pdfBkgDstD_11_Kpipi_OS("pdfBkgDstD_11_Kpipi_OS","pdfBkgDstD_11_Kpipi_OS",pdfBkgDstD,parBkgDstDYield_11_Kpipi_OS);
  RooExtendPdf    pdfBkgDstD_12_Kpipi_OS("pdfBkgDstD_12_Kpipi_OS","pdfBkgDstD_12_Kpipi_OS",pdfBkgDstD,parBkgDstDYield_12_Kpipi_OS);
  RooExtendPdf    pdfBkgDstD_11_KKpi_OS("pdfBkgDstD_11_KKpi_OS","pdfBkgDstD_11_KKpi_OS",pdfBkgDstD,parBkgDstDYield_11_KKpi_OS);
  RooExtendPdf    pdfBkgDstD_12_KKpi_OS("pdfBkgDstD_12_KKpi_OS","pdfBkgDstD_12_KKpi_OS",pdfBkgDstD,parBkgDstDYield_12_KKpi_OS);
  RooExtendPdf    pdfBkgDstD_11_Kpipi_SS("pdfBkgDstD_11_Kpipi_SS","pdfBkgDstD_11_Kpipi_SS",pdfBkgDstD,parBkgDstDYield_11_Kpipi_SS);
  RooExtendPdf    pdfBkgDstD_12_Kpipi_SS("pdfBkgDstD_12_Kpipi_SS","pdfBkgDstD_12_Kpipi_SS",pdfBkgDstD,parBkgDstDYield_12_Kpipi_SS);
  RooExtendPdf    pdfBkgDstD_11_KKpi_SS("pdfBkgDstD_11_KKpi_SS","pdfBkgDstD_11_KKpi_SS",pdfBkgDstD,parBkgDstDYield_11_KKpi_SS);
  RooExtendPdf    pdfBkgDstD_12_KKpi_SS("pdfBkgDstD_12_KKpi_SS","pdfBkgDstD_12_KKpi_SS",pdfBkgDstD,parBkgDstDYield_12_KKpi_SS);
  RooExtendPdf    pdfBkgDstD_11_Kpipi_BS("pdfBkgDstD_11_Kpipi_BS","pdfBkgDstD_11_Kpipi_BS",pdfBkgDstD,parBkgDstDYield_11_Kpipi_BS);
  RooExtendPdf    pdfBkgDstD_12_Kpipi_BS("pdfBkgDstD_12_Kpipi_BS","pdfBkgDstD_12_Kpipi_BS",pdfBkgDstD,parBkgDstDYield_12_Kpipi_BS);
  RooExtendPdf    pdfBkgDstD_11_KKpi_BS("pdfBkgDstD_11_KKpi_BS","pdfBkgDstD_11_KKpi_BS",pdfBkgDstD,parBkgDstDYield_11_KKpi_BS);
  RooExtendPdf    pdfBkgDstD_12_KKpi_BS("pdfBkgDstD_12_KKpi_BS","pdfBkgDstD_12_KKpi_BS",pdfBkgDstD,parBkgDstDYield_12_KKpi_BS);

  // Bs --> D*D PDF
  RooProdPdf      pdfBkgBsDstD("pdfBkgBsDstD","pdfBkgBsDstD",RooArgList(pdfBkgBsDstDMass,pdfBsTime));

  RooRealVar      parBkgBsDstDYield_11_Kpipi_OS("parBkgBsDstDYield_11_Kpipi_OS","parBkgBsDstDYield_11_Kpipi_OS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_12_Kpipi_OS("parBkgBsDstDYield_12_Kpipi_OS","parBkgBsDstDYield_12_Kpipi_OS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_11_KKpi_OS("parBkgBsDstDYield_11_KKpi_OS","parBkgBsDstDYield_11_KKpi_OS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_12_KKpi_OS("parBkgBsDstDYield_12_KKpi_OS","parBkgBsDstDYield_12_KKpi_OS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_11_Kpipi_SS("parBkgBsDstDYield_11_Kpipi_SS","parBkgBsDstDYield_11_Kpipi_SS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_12_Kpipi_SS("parBkgBsDstDYield_12_Kpipi_SS","parBkgBsDstDYield_12_Kpipi_SS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_11_KKpi_SS("parBkgBsDstDYield_11_KKpi_SS","parBkgBsDstDYield_11_KKpi_SS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_12_KKpi_SS("parBkgBsDstDYield_12_KKpi_SS","parBkgBsDstDYield_12_KKpi_SS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_11_Kpipi_BS("parBkgBsDstDYield_11_Kpipi_BS","parBkgBsDstDYield_11_Kpipi_BS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_12_Kpipi_BS("parBkgBsDstDYield_12_Kpipi_BS","parBkgBsDstDYield_12_Kpipi_BS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_11_KKpi_BS("parBkgBsDstDYield_11_KKpi_BS","parBkgBsDstDYield_11_KKpi_BS",100,0,1000);
  RooRealVar      parBkgBsDstDYield_12_KKpi_BS("parBkgBsDstDYield_12_KKpi_BS","parBkgBsDstDYield_12_KKpi_BS",100,0,1000);

  RooExtendPdf    pdfBkgBsDstD_11_Kpipi_OS("pdfBkgBsDstD_11_Kpipi_OS","pdfBkgBsDstD_11_Kpipi_OS",pdfBkgBsDstD,parBkgBsDstDYield_11_Kpipi_OS);
  RooExtendPdf    pdfBkgBsDstD_12_Kpipi_OS("pdfBkgBsDstD_12_Kpipi_OS","pdfBkgBsDstD_12_Kpipi_OS",pdfBkgBsDstD,parBkgBsDstDYield_12_Kpipi_OS);
  RooExtendPdf    pdfBkgBsDstD_11_KKpi_OS("pdfBkgBsDstD_11_KKpi_OS","pdfBkgBsDstD_11_KKpi_OS",pdfBkgBsDstD,parBkgBsDstDYield_11_KKpi_OS);
  RooExtendPdf    pdfBkgBsDstD_12_KKpi_OS("pdfBkgBsDstD_12_KKpi_OS","pdfBkgBsDstD_12_KKpi_OS",pdfBkgBsDstD,parBkgBsDstDYield_12_KKpi_OS);
  RooExtendPdf    pdfBkgBsDstD_11_Kpipi_SS("pdfBkgBsDstD_11_Kpipi_SS","pdfBkgBsDstD_11_Kpipi_SS",pdfBkgBsDstD,parBkgBsDstDYield_11_Kpipi_SS);
  RooExtendPdf    pdfBkgBsDstD_12_Kpipi_SS("pdfBkgBsDstD_12_Kpipi_SS","pdfBkgBsDstD_12_Kpipi_SS",pdfBkgBsDstD,parBkgBsDstDYield_12_Kpipi_SS);
  RooExtendPdf    pdfBkgBsDstD_11_KKpi_SS("pdfBkgBsDstD_11_KKpi_SS","pdfBkgBsDstD_11_KKpi_SS",pdfBkgBsDstD,parBkgBsDstDYield_11_KKpi_SS);
  RooExtendPdf    pdfBkgBsDstD_12_KKpi_SS("pdfBkgBsDstD_12_KKpi_SS","pdfBkgBsDstD_12_KKpi_SS",pdfBkgBsDstD,parBkgBsDstDYield_12_KKpi_SS);
  RooExtendPdf    pdfBkgBsDstD_11_Kpipi_BS("pdfBkgBsDstD_11_Kpipi_BS","pdfBkgBsDstD_11_Kpipi_BS",pdfBkgBsDstD,parBkgBsDstDYield_11_Kpipi_BS);
  RooExtendPdf    pdfBkgBsDstD_12_Kpipi_BS("pdfBkgBsDstD_12_Kpipi_BS","pdfBkgBsDstD_12_Kpipi_BS",pdfBkgBsDstD,parBkgBsDstDYield_12_Kpipi_BS);
  RooExtendPdf    pdfBkgBsDstD_11_KKpi_BS("pdfBkgBsDstD_11_KKpi_BS","pdfBkgBsDstD_11_KKpi_BS",pdfBkgBsDstD,parBkgBsDstDYield_11_KKpi_BS);
  RooExtendPdf    pdfBkgBsDstD_12_KKpi_BS("pdfBkgBsDstD_12_KKpi_BS","pdfBkgBsDstD_12_KKpi_BS",pdfBkgBsDstD,parBkgBsDstDYield_12_KKpi_BS);

  // Background Decay Time PDF
  RooGaussModel   pdfBkgResolution("pdfBkgResolution","pdfBkgResolution",obsTime,RooConst(0),RooConst(0.05));
  RooRealVar      parBkgTimeTauOne("parBkgTimeTauOne","parBkgTimeTauOne",0.4);
  RooDecay        pdfBkgTimeOne("pdfBkgTimeOne","pdfBkgTimeOne",obsTime,parBkgTimeTauOne,pdfBkgResolution,RooDecay::SingleSided);
  RooRealVar      parBkgTimeTauTwo("parBkgTimeTauTwo","parBkgTimeTauTwo",1.0);
  RooDecay        pdfBkgTimeTwo("pdfBkgTimeTwo","pdfBkgTimeTwo",obsTime,parBkgTimeTauTwo,pdfBkgResolution,RooDecay::SingleSided);
  RooRealVar      parBkgTimeFraction("parBkgTimeFraction","parBkgTimeFraction",0.8);
  RooAddPdf       pdfBkgTime("pdfBkgTime","pdfBkgTime",RooArgList(pdfBkgTimeTwo,pdfBkgTimeOne),parBkgTimeFraction);

  RooProdPdf      pdfBkg("pdfBkg","pdfBkg",RooArgList(pdfBkgMass,pdfBkgTime));

  RooRealVar      parBkgYield_11_Kpipi_OS("parBkgYield_11_Kpipi_OS","parBkgYield_11_Kpipi_OS",5000,0,10000);
  RooRealVar      parBkgYield_12_Kpipi_OS("parBkgYield_12_Kpipi_OS","parBkgYield_12_Kpipi_OS",5000,0,10000);
  RooRealVar      parBkgYield_11_KKpi_OS("parBkgYield_11_KKpi_OS","parBkgYield_11_KKpi_OS",5000,0,10000);
  RooRealVar      parBkgYield_12_KKpi_OS("parBkgYield_12_KKpi_OS","parBkgYield_12_KKpi_OS",5000,0,10000);
  RooRealVar      parBkgYield_11_Kpipi_SS("parBkgYield_11_Kpipi_SS","parBkgYield_11_Kpipi_SS",5000,0,10000);
  RooRealVar      parBkgYield_12_Kpipi_SS("parBkgYield_12_Kpipi_SS","parBkgYield_12_Kpipi_SS",5000,0,10000);
  RooRealVar      parBkgYield_11_KKpi_SS("parBkgYield_11_KKpi_SS","parBkgYield_11_KKpi_SS",5000,0,10000);
  RooRealVar      parBkgYield_12_KKpi_SS("parBkgYield_12_KKpi_SS","parBkgYield_12_KKpi_SS",5000,0,10000);
  RooRealVar      parBkgYield_11_Kpipi_BS("parBkgYield_11_Kpipi_BS","parBkgYield_11_Kpipi_BS",5000,0,10000);
  RooRealVar      parBkgYield_12_Kpipi_BS("parBkgYield_12_Kpipi_BS","parBkgYield_12_Kpipi_BS",5000,0,10000);
  RooRealVar      parBkgYield_11_KKpi_BS("parBkgYield_11_KKpi_BS","parBkgYield_11_KKpi_BS",5000,0,10000);
  RooRealVar      parBkgYield_12_KKpi_BS("parBkgYield_12_KKpi_BS","parBkgYield_12_KKpi_BS",5000,0,10000);

  RooExtendPdf    pdfBkg_11_Kpipi_OS("pdfBkg_11_Kpipi_OS","pdfBkg_11_Kpipi_OS",pdfBkg,parBkgYield_11_Kpipi_OS);
  RooExtendPdf    pdfBkg_11_Kpipi_SS("pdfBkg_11_Kpipi_SS","pdfBkg_11_Kpipi_SS",pdfBkg,parBkgYield_11_Kpipi_SS);
  RooExtendPdf    pdfBkg_11_Kpipi_BS("pdfBkg_11_Kpipi_BS","pdfBkg_11_Kpipi_BS",pdfBkg,parBkgYield_11_Kpipi_BS);
  RooExtendPdf    pdfBkg_12_Kpipi_OS("pdfBkg_12_Kpipi_OS","pdfBkg_12_Kpipi_OS",pdfBkg,parBkgYield_12_Kpipi_OS);
  RooExtendPdf    pdfBkg_12_Kpipi_SS("pdfBkg_12_Kpipi_SS","pdfBkg_12_Kpipi_SS",pdfBkg,parBkgYield_12_Kpipi_SS);
  RooExtendPdf    pdfBkg_12_Kpipi_BS("pdfBkg_12_Kpipi_BS","pdfBkg_12_Kpipi_BS",pdfBkg,parBkgYield_12_Kpipi_BS);
  RooExtendPdf    pdfBkg_11_KKpi_OS("pdfBkg_11_KKpi_OS","pdfBkg_11_KKpi_OS",pdfBkg,parBkgYield_11_KKpi_OS);
  RooExtendPdf    pdfBkg_11_KKpi_SS("pdfBkg_11_KKpi_SS","pdfBkg_11_KKpi_SS",pdfBkg,parBkgYield_11_KKpi_SS);
  RooExtendPdf    pdfBkg_11_KKpi_BS("pdfBkg_11_KKpi_BS","pdfBkg_11_KKpi_BS",pdfBkg,parBkgYield_11_KKpi_BS);
  RooExtendPdf    pdfBkg_12_KKpi_OS("pdfBkg_12_KKpi_OS","pdfBkg_12_KKpi_OS",pdfBkg,parBkgYield_12_KKpi_OS);
  RooExtendPdf    pdfBkg_12_KKpi_SS("pdfBkg_12_KKpi_SS","pdfBkg_12_KKpi_SS",pdfBkg,parBkgYield_12_KKpi_SS);
  RooExtendPdf    pdfBkg_12_KKpi_BS("pdfBkg_12_KKpi_BS","pdfBkg_12_KKpi_BS",pdfBkg,parBkgYield_12_KKpi_BS);

  // Charmless PDF
  RooConstVar     parBkgCharmlessTimeSinh("parBkgCharmlessTimeSinh","Sh_{f}",0.0);
  RooConstVar     parBkgCharmlessTimeCos("parBkgCharmlessTimeCos","C_{f}",0.0);
  RooRealVar      parBkgCharmlessTimeSin2b("parBkgCharmlessTimeSin2b","S_{f}",1.0);

  CPCoefficient   parBkgCharmlessTimeCosh_11_OS("parBkgCharmlessTimeCosh_11_OS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient   parBkgCharmlessTimeCosh_12_OS("parBkgCharmlessTimeCosh_12_OS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient   parBkgCharmlessTimeSin_11_OS("parBkgCharmlessTimeSin_11_OS",parBkgCharmlessTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient   parBkgCharmlessTimeSin_12_OS("parBkgCharmlessTimeSin_12_OS",parBkgCharmlessTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kSin);

  CPCoefficient   parBkgCharmlessTimeCosh_11_SS("parBkgCharmlessTimeCosh_11_SS",RooConst(1.0),obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient   parBkgCharmlessTimeCosh_12_SS("parBkgCharmlessTimeCosh_12_SS",RooConst(1.0),obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient   parBkgCharmlessTimeSin_11_SS("parBkgCharmlessTimeSin_11_SS",parBkgCharmlessTimeSin2b,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient   parBkgCharmlessTimeSin_12_SS("parBkgCharmlessTimeSin_12_SS",parBkgCharmlessTimeSin2b,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);

  CPCoefficient   parBkgCharmlessTimeCosh_11_BS("parBkgCharmlessTimeCosh_11_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient   parBkgCharmlessTimeCosh_12_BS("parBkgCharmlessTimeCosh_12_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient   parBkgCharmlessTimeSin_11_BS("parBkgCharmlessTimeSin_11_BS",parBkgCharmlessTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient   parBkgCharmlessTimeSin_12_BS("parBkgCharmlessTimeSin_12_BS",parBkgCharmlessTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);

  RooBDecay       pdfBkgCharmlessTime_11_OS("pdfBkgCharmlessTime_11_OS","P(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parBkgCharmlessTimeCosh_11_OS,parBkgCharmlessTimeSinh,parBkgCharmlessTimeCos,parBkgCharmlessTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay       pdfBkgCharmlessTime_11_SS("pdfBkgCharmlessTime_11_SS","P(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parBkgCharmlessTimeCosh_11_SS,parBkgCharmlessTimeSinh,parBkgCharmlessTimeCos,parBkgCharmlessTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay       pdfBkgCharmlessTime_12_OS("pdfBkgCharmlessTime_12_OS","P(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parBkgCharmlessTimeCosh_12_OS,parBkgCharmlessTimeSinh,parBkgCharmlessTimeCos,parBkgCharmlessTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay       pdfBkgCharmlessTime_12_SS("pdfBkgCharmlessTime_12_SS","P(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parBkgCharmlessTimeCosh_12_SS,parBkgCharmlessTimeSinh,parBkgCharmlessTimeCos,parBkgCharmlessTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay       pdfBkgCharmlessTime_11_BS("pdfBkgCharmlessTime_11_BS","P(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parBkgCharmlessTimeCosh_11_BS,parBkgCharmlessTimeSinh,parBkgCharmlessTimeCos,parBkgCharmlessTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay       pdfBkgCharmlessTime_12_BS("pdfBkgCharmlessTime_12_BS","P(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parBkgCharmlessTimeCosh_12_BS,parBkgCharmlessTimeSinh,parBkgCharmlessTimeCos,parBkgCharmlessTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);

  RooProdPdf      pdfBkgCharmless_11_OS("pdfBkgCharmless_11_OS","pdfBkgCharmless_11_OS",RooArgList(pdfBkgCharmlessMass,pdfBkgCharmlessTime_11_OS));
  RooProdPdf      pdfBkgCharmless_11_SS("pdfBkgCharmless_11_SS","pdfBkgCharmless_11_SS",RooArgList(pdfBkgCharmlessMass,pdfBkgCharmlessTime_11_SS));
  RooProdPdf      pdfBkgCharmless_12_OS("pdfBkgCharmless_12_OS","pdfBkgCharmless_12_OS",RooArgList(pdfBkgCharmlessMass,pdfBkgCharmlessTime_12_OS));
  RooProdPdf      pdfBkgCharmless_12_SS("pdfBkgCharmless_12_SS","pdfBkgCharmless_12_SS",RooArgList(pdfBkgCharmlessMass,pdfBkgCharmlessTime_12_SS));
  RooProdPdf      pdfBkgCharmless_11_BS("pdfBkgCharmless_11_BS","pdfBkgCharmless_11_BS",RooArgList(pdfBkgCharmlessMass,pdfBkgCharmlessTime_11_BS));
  RooProdPdf      pdfBkgCharmless_12_BS("pdfBkgCharmless_12_BS","pdfBkgCharmless_12_BS",RooArgList(pdfBkgCharmlessMass,pdfBkgCharmlessTime_12_BS));

  RooRealVar      parBkgCharmlessYield_11_Kpipi_OS("parBkgCharmlessYield_11_Kpipi_OS","parBkgCharmlessYield_11_Kpipi_OS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_12_Kpipi_OS("parBkgCharmlessYield_12_Kpipi_OS","parBkgCharmlessYield_12_Kpipi_OS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_11_KKpi_OS("parBkgCharmlessYield_11_KKpi_OS","parBkgCharmlessYield_11_KKpi_OS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_12_KKpi_OS("parBkgCharmlessYield_12_KKpi_OS","parBkgCharmlessYield_12_KKpi_OS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_11_Kpipi_SS("parBkgCharmlessYield_11_Kpipi_SS","parBkgCharmlessYield_11_Kpipi_SS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_12_Kpipi_SS("parBkgCharmlessYield_12_Kpipi_SS","parBkgCharmlessYield_12_Kpipi_SS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_11_KKpi_SS("parBkgCharmlessYield_11_KKpi_SS","parBkgCharmlessYield_11_KKpi_SS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_12_KKpi_SS("parBkgCharmlessYield_12_KKpi_SS","parBkgCharmlessYield_12_KKpi_SS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_11_Kpipi_BS("parBkgCharmlessYield_11_Kpipi_BS","parBkgCharmlessYield_11_Kpipi_BS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_12_Kpipi_BS("parBkgCharmlessYield_12_Kpipi_BS","parBkgCharmlessYield_12_Kpipi_BS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_11_KKpi_BS("parBkgCharmlessYield_11_KKpi_BS","parBkgCharmlessYield_11_KKpi_BS",100,0,1000);
  RooRealVar      parBkgCharmlessYield_12_KKpi_BS("parBkgCharmlessYield_12_KKpi_BS","parBkgCharmlessYield_12_KKpi_BS",100,0,1000);

  RooExtendPdf    pdfBkgCharmless_11_Kpipi_OS("pdfBkgCharmless_11_Kpipi_OS","pdfBkgCharmless_11_Kpipi_OS",pdfBkgCharmless_11_OS,parBkgCharmlessYield_11_Kpipi_OS);
  RooExtendPdf    pdfBkgCharmless_12_Kpipi_OS("pdfBkgCharmless_12_Kpipi_OS","pdfBkgCharmless_12_Kpipi_OS",pdfBkgCharmless_12_OS,parBkgCharmlessYield_12_Kpipi_OS);
  RooExtendPdf    pdfBkgCharmless_11_KKpi_OS("pdfBkgCharmless_11_KKpi_OS","pdfBkgCharmless_11_KKpi_OS",pdfBkgCharmless_11_OS,parBkgCharmlessYield_11_KKpi_OS);
  RooExtendPdf    pdfBkgCharmless_12_KKpi_OS("pdfBkgCharmless_12_KKpi_OS","pdfBkgCharmless_12_KKpi_OS",pdfBkgCharmless_12_OS,parBkgCharmlessYield_12_KKpi_OS);
  RooExtendPdf    pdfBkgCharmless_11_Kpipi_SS("pdfBkgCharmless_11_Kpipi_SS","pdfBkgCharmless_11_Kpipi_SS",pdfBkgCharmless_11_SS,parBkgCharmlessYield_11_Kpipi_SS);
  RooExtendPdf    pdfBkgCharmless_12_Kpipi_SS("pdfBkgCharmless_12_Kpipi_SS","pdfBkgCharmless_12_Kpipi_SS",pdfBkgCharmless_12_SS,parBkgCharmlessYield_12_Kpipi_SS);
  RooExtendPdf    pdfBkgCharmless_11_KKpi_SS("pdfBkgCharmless_11_KKpi_SS","pdfBkgCharmless_11_KKpi_SS",pdfBkgCharmless_11_SS,parBkgCharmlessYield_11_KKpi_SS);
  RooExtendPdf    pdfBkgCharmless_12_KKpi_SS("pdfBkgCharmless_12_KKpi_SS","pdfBkgCharmless_12_KKpi_SS",pdfBkgCharmless_12_SS,parBkgCharmlessYield_12_KKpi_SS);
  RooExtendPdf    pdfBkgCharmless_11_Kpipi_BS("pdfBkgCharmless_11_Kpipi_BS","pdfBkgCharmless_11_Kpipi_BS",pdfBkgCharmless_11_BS,parBkgCharmlessYield_11_Kpipi_BS);
  RooExtendPdf    pdfBkgCharmless_12_Kpipi_BS("pdfBkgCharmless_12_Kpipi_BS","pdfBkgCharmless_12_Kpipi_BS",pdfBkgCharmless_12_BS,parBkgCharmlessYield_12_Kpipi_BS);
  RooExtendPdf    pdfBkgCharmless_11_KKpi_BS("pdfBkgCharmless_11_KKpi_BS","pdfBkgCharmless_11_KKpi_BS",pdfBkgCharmless_11_BS,parBkgCharmlessYield_11_KKpi_BS);
  RooExtendPdf    pdfBkgCharmless_12_KKpi_BS("pdfBkgCharmless_12_KKpi_BS","pdfBkgCharmless_12_KKpi_BS",pdfBkgCharmless_12_BS,parBkgCharmlessYield_12_KKpi_BS);  

//========================================================================================================================================================================================================================

  RooAddPdf       pdf_11_Kpipi_OS("pdf_11_Kpipi_OS","pdf_11_Kpipi_OS",RooArgList(pdfSig_11_Kpipi_OS,pdfSigBs_11_Kpipi_OS,pdfBkgDsD_11_Kpipi_OS,pdfBkg_11_Kpipi_OS,/*pdfBkgDstD_11_Kpipi_OS,*/pdfBkgBsDstD_11_Kpipi_OS,pdfBkgBsDsD_11_Kpipi_OS,pdfBkgCharmless_11_Kpipi_OS));
  RooAddPdf       pdf_11_Kpipi_SS("pdf_11_Kpipi_SS","pdf_11_Kpipi_SS",RooArgList(pdfSig_11_Kpipi_SS,pdfSigBs_11_Kpipi_SS,pdfBkgDsD_11_Kpipi_SS,pdfBkg_11_Kpipi_SS,/*pdfBkgDstD_11_Kpipi_SS,*/pdfBkgBsDstD_11_Kpipi_SS,pdfBkgBsDsD_11_Kpipi_SS,pdfBkgCharmless_11_Kpipi_SS));
  RooAddPdf       pdf_11_Kpipi_BS("pdf_11_Kpipi_BS","pdf_11_Kpipi_BS",RooArgList(pdfSig_11_Kpipi_BS,pdfSigBs_11_Kpipi_BS,pdfBkgDsD_11_Kpipi_BS,pdfBkg_11_Kpipi_BS,/*pdfBkgDstD_11_Kpipi_BS,*/pdfBkgBsDstD_11_Kpipi_BS,pdfBkgBsDsD_11_Kpipi_BS,pdfBkgCharmless_11_Kpipi_BS));
  RooAddPdf       pdf_12_Kpipi_OS("pdf_12_Kpipi_OS","pdf_12_Kpipi_OS",RooArgList(pdfSig_12_Kpipi_OS,pdfSigBs_12_Kpipi_OS,pdfBkgDsD_12_Kpipi_OS,pdfBkg_12_Kpipi_OS,/*pdfBkgDstD_12_Kpipi_OS,*/pdfBkgBsDstD_12_Kpipi_OS,pdfBkgBsDsD_12_Kpipi_OS,pdfBkgCharmless_12_Kpipi_OS));
  RooAddPdf       pdf_12_Kpipi_SS("pdf_12_Kpipi_SS","pdf_12_Kpipi_SS",RooArgList(pdfSig_12_Kpipi_SS,pdfSigBs_12_Kpipi_SS,pdfBkgDsD_12_Kpipi_SS,pdfBkg_12_Kpipi_SS,/*pdfBkgDstD_12_Kpipi_SS,*/pdfBkgBsDstD_12_Kpipi_SS,pdfBkgBsDsD_12_Kpipi_SS,pdfBkgCharmless_12_Kpipi_SS));
  RooAddPdf       pdf_12_Kpipi_BS("pdf_12_Kpipi_BS","pdf_12_Kpipi_BS",RooArgList(pdfSig_12_Kpipi_BS,pdfSigBs_12_Kpipi_BS,pdfBkgDsD_12_Kpipi_BS,pdfBkg_12_Kpipi_BS,/*pdfBkgDstD_12_Kpipi_BS,*/pdfBkgBsDstD_12_Kpipi_BS,pdfBkgBsDsD_12_Kpipi_BS,pdfBkgCharmless_12_Kpipi_BS));
  RooAddPdf       pdf_11_KKpi_OS("pdf_11_KKpi_OS","pdf_11_KKpi_OS",RooArgList(pdfSig_11_KKpi_OS,pdfSigBs_11_KKpi_OS,pdfBkgDsD_11_KKpi_OS,pdfBkg_11_KKpi_OS,/*pdfBkgDstD_11_KKpi_OS,*/pdfBkgBsDstD_11_KKpi_OS,pdfBkgBsDsD_11_KKpi_OS,pdfBkgCharmless_11_KKpi_OS));
  RooAddPdf       pdf_11_KKpi_SS("pdf_11_KKpi_SS","pdf_11_KKpi_SS",RooArgList(pdfSig_11_KKpi_SS,pdfSigBs_11_KKpi_SS,pdfBkgDsD_11_KKpi_SS,pdfBkg_11_KKpi_SS,/*pdfBkgDstD_11_KKpi_SS,*/pdfBkgBsDstD_11_KKpi_SS,pdfBkgBsDsD_11_KKpi_SS,pdfBkgCharmless_11_KKpi_SS));
  RooAddPdf       pdf_11_KKpi_BS("pdf_11_KKpi_BS","pdf_11_KKpi_BS",RooArgList(pdfSig_11_KKpi_BS,pdfSigBs_11_KKpi_BS,pdfBkgDsD_11_KKpi_BS,pdfBkg_11_KKpi_BS,/*pdfBkgDstD_11_KKpi_BS,*/pdfBkgBsDstD_11_KKpi_BS,pdfBkgBsDsD_11_KKpi_BS,pdfBkgCharmless_11_KKpi_BS));
  RooAddPdf       pdf_12_KKpi_OS("pdf_12_KKpi_OS","pdf_12_KKpi_OS",RooArgList(pdfSig_12_KKpi_OS,pdfSigBs_12_KKpi_OS,pdfBkgDsD_12_KKpi_OS,pdfBkg_12_KKpi_OS,/*pdfBkgDstD_12_KKpi_OS,*/pdfBkgBsDstD_12_KKpi_OS,pdfBkgBsDsD_12_KKpi_OS,pdfBkgCharmless_12_KKpi_OS));
  RooAddPdf       pdf_12_KKpi_SS("pdf_12_KKpi_SS","pdf_12_KKpi_SS",RooArgList(pdfSig_12_KKpi_SS,pdfSigBs_12_KKpi_SS,pdfBkgDsD_12_KKpi_SS,pdfBkg_12_KKpi_SS,/*pdfBkgDstD_12_KKpi_SS,*/pdfBkgBsDstD_12_KKpi_SS,pdfBkgBsDsD_12_KKpi_SS,pdfBkgCharmless_12_KKpi_SS));
  RooAddPdf       pdf_12_KKpi_BS("pdf_12_KKpi_BS","pdf_12_KKpi_BS",RooArgList(pdfSig_12_KKpi_BS,pdfSigBs_12_KKpi_BS,pdfBkgDsD_12_KKpi_BS,pdfBkg_12_KKpi_BS,/*pdfBkgDstD_12_KKpi_BS,*/pdfBkgBsDstD_12_KKpi_BS,pdfBkgBsDsD_12_KKpi_BS,pdfBkgCharmless_12_KKpi_BS));

  RooSuperCategory  supercategory_generate("supercategory_generate","supercategory_generate",RooArgList(catYear,catTag,catDDFinalStateParticles));
  RooSimultaneous   pdf_generate("pdf_generate","P",supercategory_generate);
  pdf_generate.addPdf(pdf_11_Kpipi_OS,"{2011;OS;Kpipi}");
  pdf_generate.addPdf(pdf_11_Kpipi_SS,"{2011;SS;Kpipi}");
  pdf_generate.addPdf(pdf_11_Kpipi_BS,"{2011;both;Kpipi}");
  pdf_generate.addPdf(pdf_12_Kpipi_OS,"{2012;OS;Kpipi}");
  pdf_generate.addPdf(pdf_12_Kpipi_SS,"{2012;SS;Kpipi}");
  pdf_generate.addPdf(pdf_12_Kpipi_BS,"{2012;both;Kpipi}");
  pdf_generate.addPdf(pdf_11_KKpi_OS,"{2011;OS;KKpi}");
  pdf_generate.addPdf(pdf_11_KKpi_SS,"{2011;SS;KKpi}");
  pdf_generate.addPdf(pdf_11_KKpi_BS,"{2011;both;KKpi}");
  pdf_generate.addPdf(pdf_12_KKpi_OS,"{2012;OS;KKpi}");
  pdf_generate.addPdf(pdf_12_KKpi_SS,"{2012;SS;KKpi}");
  pdf_generate.addPdf(pdf_12_KKpi_BS,"{2012;both;KKpi}");

//========================================================================================================================================================================================================================

  Gaussian_Constraints.readFromFile("/home/fmeier/storage03/b02dd/Systematics/MassModel/generation.par");
  pdfTime.Print();

  TMatrixDSym           covariancematrixSigEta_OS = CreateCovarianceMatrix(4, &parSigEtaP0Sigma_OS, &parSigEtaP1Sigma_OS, &parSigEtaP0P1CorrelationCoeff_OS, &parSigEtaDeltaP0Sigma_OS, &parSigEtaDeltaP1Sigma_OS, &parSigEtaP0DeltaP0CorrelationCoeff_OS, &parSigEtaP0DeltaP1CorrelationCoeff_OS, &parSigEtaP1DeltaP0CorrelationCoeff_OS, &parSigEtaP1DeltaP1CorrelationCoeff_OS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS);
  TMatrixDSym           covariancematrixSigEta_SS = CreateCovarianceMatrix(4, &parSigEtaP0Sigma_SS, &parSigEtaP1Sigma_SS, &parSigEtaP0P1CorrelationCoeff_SS, &parSigEtaDeltaP0Sigma_SS, &parSigEtaDeltaP1Sigma_SS, &parSigEtaP0DeltaP0CorrelationCoeff_SS, &parSigEtaP0DeltaP1CorrelationCoeff_SS, &parSigEtaP1DeltaP0CorrelationCoeff_SS, &parSigEtaP1DeltaP1CorrelationCoeff_SS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS);

  RooArgSet             constrainingPdfs("constrainingPdfs");
  RooGaussian           conpdfSigTimeTau("conpdfSigTimeTau","constraint for #tau",parSigTimeTau,parSigTimeTauMean,parSigTimeTauSigma);
  RooGaussian           conpdfSigTimeDeltaM("conpdfSigTimeDeltaM","constraint for #Delta m",parSigTimeDeltaM,parSigTimeDeltaMMean,parSigTimeDeltaMSigma);
  RooGaussian           conpdfSigEtaDeltaProd_11("conpdfSigEtaDeltaProd_11","Gaussian Constraint for production asymmetry 2011",parSigEtaDeltaProd_11,parSigEtaDeltaProdMean_11,parSigEtaDeltaProdSigma_11);
  RooGaussian           conpdfSigEtaDeltaProd_12("conpdfSigEtaDeltaProd_12","Gaussian Constraint for production asymmetry 2012",parSigEtaDeltaProdOffset,parSigEtaDeltaProdOffsetMean,parSigEtaDeltaProdOffsetSigma);
  RooMultiVarGaussian   conpdfSigEta_OS("conpdfSigEta_OS","constraint for OS FT calibration",RooArgList(parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS),RooArgList(parSigEtaP0Mean_OS,parSigEtaP1Mean_OS,parSigEtaDeltaP0Mean_OS,parSigEtaDeltaP1Mean_OS),covariancematrixSigEta_OS);
  RooMultiVarGaussian   conpdfSigEta_SS("conpdfSigEta_SS","constraint for SS FT calibration",RooArgList(parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS),RooArgList(parSigEtaP0Mean_SS,parSigEtaP1Mean_SS,parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP1Mean_SS),covariancematrixSigEta_SS);  

  constrainingPdfs.add(conpdfSigTimeTau);
  constrainingPdfs.add(conpdfSigTimeDeltaM);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_11);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_12);
  constrainingPdfs.add(conpdfSigEta_OS);
  constrainingPdfs.add(conpdfSigEta_SS);
  cout  <<  "Constraints added" <<  endl;

//========================================================================================================================================================================================================================
  
  // Mistag distributions
  TFile* mistag_histograms = new TFile("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Histograms/HIST_Eta_Distributions.root","read");
  TH1D*    TH1_Sig_OS_eta = dynamic_cast<TH1D*>(mistag_histograms->Get("hist_Sig_OS_eta"));
  TH1D*    TH1_Sig_SS_eta = dynamic_cast<TH1D*>(mistag_histograms->Get("hist_Sig_SS_eta"));
  RooDataHist DataHist_Sig_OS_eta("DataHist_Sig_OS_eta","DataHist_Sig_OS_eta",obsEtaOS,TH1_Sig_OS_eta);
  RooDataHist DataHist_Sig_SS_eta("DataHist_Sig_SS_eta","DataHist_Sig_SS_eta",obsEtaSS,TH1_Sig_SS_eta);
  RooHistPdf HistPdf_Sig_OS_eta("HistPdf_Sig_OS_eta","HistPdf_Sig_OS_eta",obsEtaOS,DataHist_Sig_OS_eta);
  RooHistPdf HistPdf_Sig_SS_eta("HistPdf_Sig_SS_eta","HistPdf_Sig_SS_eta",obsEtaSS,DataHist_Sig_SS_eta);

  TH1D*    TH1_Bkg_OS_eta = dynamic_cast<TH1D*>(mistag_histograms->Get("hist_Bkg_OS_eta"));
  TH1D*    TH1_Bkg_SS_eta = dynamic_cast<TH1D*>(mistag_histograms->Get("hist_Bkg_SS_eta"));
  RooDataHist DataHist_Bkg_OS_eta("DataHist_Bkg_OS_eta","DataHist_Bkg_OS_eta",obsEtaOS,TH1_Bkg_OS_eta);
  RooDataHist DataHist_Bkg_SS_eta("DataHist_Bkg_SS_eta","DataHist_Bkg_SS_eta",obsEtaSS,TH1_Bkg_SS_eta);
  RooHistPdf HistPdf_Bkg_OS_eta("HistPdf_Bkg_OS_eta","HistPdf_Bkg_OS_eta",obsEtaOS,DataHist_Bkg_OS_eta);
  RooHistPdf HistPdf_Bkg_SS_eta("HistPdf_Bkg_SS_eta","HistPdf_Bkg_SS_eta",obsEtaSS,DataHist_Bkg_SS_eta);

  // Workspace initializing
  RooWorkspace* ws = new RooWorkspace("ws");
  ws->import(pdf_generate);
  ws->import(RooArgSet(HistPdf_Sig_OS_eta,HistPdf_Sig_SS_eta,HistPdf_Bkg_OS_eta,HistPdf_Bkg_SS_eta));
  ws->defineSet("allobservables",observables);

  doofit::config::CommonConfig cfg_com("common");
  cfg_com.InitializeOptions(argc, argv);

  ToyFactoryStdConfig cfg_tfac("toyfac");
  cfg_tfac.InitializeOptions(cfg_com);

  ToyStudyStdConfig cfg_tstudy("toystudy");
  cfg_tstudy.InitializeOptions(cfg_tfac);

  cfg_com.CheckHelpFlagAndPrintHelp();

  ws->Print();

  cfg_tfac.set_workspace(ws);

  ToyFactoryStd tfac(cfg_com, cfg_tfac);

  cfg_com.PrintAll();

  RooDataSet* data = NULL;
  RooDataSet* data_sweighted = NULL;
  PlotConfig cfg_plot("cfg_plot");
  ToyStudyStd tstudy(cfg_com, cfg_tstudy, cfg_plot);

  if (method.EqualTo("generate")) {
    
    TIterator*  iterator = constrainingPdfs.createIterator();
    RooAbsPdf*  constrainingPdf;
    SPlotFit2* splotfit;
    RooFitResult* fit_result;
    TStopwatch  stopwatch;
    RooLinkedList fitting_args;
    fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
    fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
    fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
    fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
    fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
    fitting_args.Add((TObject*)(new RooCmdArg(Hesse(true))));
    if (!pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS)))));
    if (pereventresolution)  fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS,obsTimeErr)))));
    fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
    fitting_args.Add((TObject*)(new RooCmdArg(Offset(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
    RooDataSet* data_newconstrain_etaOS, *data_newconstrain_etaSS;
    RooArgSet set_of_yields;
    RooRealVar SigWeight_11_Kpipi("parSigYield_11_Kpipi_sw","signal weight for 11 Kpipi",-10,10);
    RooRealVar SigWeight_11_KKpi("parSigYield_11_KKpi_sw","signal weight for 11 KKpi",-10,10);
    RooRealVar SigWeight_12_Kpipi("parSigYield_12_Kpipi_sw","signal weight for 12 Kpipi",-10,10);
    RooRealVar SigWeight_12_KKpi("parSigYield_12_KKpi_sw","signal weight for 12 KKpi",-10,10);
    RooFormulaVar sum_of_signal_weights_year_finalstate("sum_of_signal_weights_year_finalstate","sum of signal weights","@0+@1+@2+@3",RooArgList(SigWeight_11_Kpipi,SigWeight_11_KKpi,SigWeight_12_Kpipi,SigWeight_12_KKpi));
    set_of_yields.add(RooArgSet(parSigYield_11_Kpipi,parBkgDsDYield_11_Kpipi,parSigBsYield_11_Kpipi,parBkgYield_11_Kpipi/*,parBkgDstDYield_11_Kpipi*/,parBkgBsDsDYield_11_Kpipi));
    set_of_yields.add(RooArgSet(parSigYield_11_KKpi,parBkgDsDYield_11_KKpi,parSigBsYield_11_KKpi,parBkgYield_11_KKpi/*,parBkgDstDYield_11_KKpi*/,parBkgBsDsDYield_11_KKpi));
    set_of_yields.add(RooArgSet(parSigYield_12_Kpipi,parBkgDsDYield_12_Kpipi,parSigBsYield_12_Kpipi,parBkgYield_12_Kpipi/*,parBkgDstDYield_12_Kpipi*/,parBkgBsDsDYield_12_Kpipi));
    set_of_yields.add(RooArgSet(parSigYield_12_KKpi,parBkgDsDYield_12_KKpi,parSigBsYield_12_KKpi,parBkgYield_12_KKpi/*,parBkgDstDYield_12_KKpi*/,parBkgBsDsDYield_12_KKpi));
    for (int i = 0; i < 5 ; ++i) {
      cout  <<  i <<  endl;
      try {
        data = tfac.Generate();
        // EasyTuple tuple(*data);
        // tuple.WriteDataSetToTree("testsignalgenerationdatasample.root","TestTree");
        // pdfMass.getParameters(data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/MassModel/generation.par");
        splotfit = new SPlotFit2(pdfMass,*data,set_of_yields);
        splotfit->set_use_minos(false);
        splotfit->set_num_cpu(config.getInt("num_cpu"));
        splotfit->set_startingvalues("/home/fmeier/storage03/b02dd/Systematics/MassModel/generation.par");
        RooMsgService::instance().setStreamStatus(0, false);
        RooMsgService::instance().setStreamStatus(1, false);
        stopwatch.Start(true);
        splotfit->Fit();
        stopwatch.Stop();
        RooMsgService::instance().setStreamStatus(0, true);
        RooMsgService::instance().setStreamStatus(1, true);
        delete splotfit;
        data->addColumn(sum_of_signal_weights_year_finalstate);
        // data_sweighted = new RooDataSet("data_sweighted","data_sweighted",data,*(data->get()),TString(catTag.GetName())+"!=0","sum_of_signal_weights_year_finalstate");
        data_sweighted = new RooDataSet("data_sweighted","data_sweighted",data,*(data->get()),"","sum_of_signal_weights_year_finalstate");
        data_sweighted->Print();
        pdfTime.getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/MassModel/generation.par");
        iterator = constrainingPdfs.createIterator();
        while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
          constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/MassModel/generation.par");
        }
        parSigEtaDeltaProdMean_11.setVal(conpdfSigEtaDeltaProd_11.generate(parSigEtaDeltaProd_11,1)->get()->getRealValue("parSigEtaDeltaProd_11"));
        parSigEtaDeltaProdOffsetMean.setVal(conpdfSigEtaDeltaProd_12.generate(parSigEtaDeltaProdOffset,1)->get()->getRealValue("parSigEtaDeltaProdOffset"));
        data_newconstrain_etaOS = conpdfSigEta_OS.generate(RooArgSet(parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS),1);
        parSigEtaP0Mean_OS.setVal(data_newconstrain_etaOS->get()->getRealValue("parSigEtaP0_OS"));
        parSigEtaP1Mean_OS.setVal(data_newconstrain_etaOS->get()->getRealValue("parSigEtaP1_OS"));
        parSigEtaDeltaP0Mean_OS.setVal(data_newconstrain_etaOS->get()->getRealValue("parSigEtaDeltaP0_OS"));
        parSigEtaDeltaP1Mean_OS.setVal(data_newconstrain_etaOS->get()->getRealValue("parSigEtaDeltaP1_OS"));
        data_newconstrain_etaSS = conpdfSigEta_SS.generate(RooArgSet(parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS),1);
        parSigEtaP0Mean_SS.setVal(data_newconstrain_etaSS->get()->getRealValue("parSigEtaP0_SS"));
        parSigEtaP1Mean_SS.setVal(data_newconstrain_etaSS->get()->getRealValue("parSigEtaP1_SS"));
        parSigEtaDeltaP0Mean_SS.setVal(data_newconstrain_etaSS->get()->getRealValue("parSigEtaDeltaP0_SS"));
        parSigEtaDeltaP1Mean_SS.setVal(data_newconstrain_etaSS->get()->getRealValue("parSigEtaDeltaP1_SS"));
        parSigTimeTauMean.setVal(conpdfSigTimeTau.generate(parSigTimeTau,1)->get()->getRealValue("parSigTimeTau"));
        parSigTimeDeltaMMean.setVal(conpdfSigTimeDeltaM.generate(parSigTimeDeltaM,1)->get()->getRealValue("parSigTimeDeltaM"));
        stopwatch.Start(true);
        fit_result = pdfTime.fitTo(*data_sweighted,fitting_args);
        stopwatch.Stop();
        fit_result->Print("v");
        tstudy.StoreFitResult(fit_result, NULL, &stopwatch);
        delete iterator;
        delete data_sweighted;
        delete data_newconstrain_etaOS;
        delete data_newconstrain_etaSS;
      } catch (...) {
        i--;
      }
    }
  }

  if (method.EqualTo("evaluate")) {
    tstudy.ReadFitResults();
    tstudy.EvaluateFitResults();
    tstudy.PlotEvaluatedParameters();
  }

  delete ws;
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
