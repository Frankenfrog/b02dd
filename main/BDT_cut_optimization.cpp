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
#include "TLine.h"

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
#include "RooAddition.h"

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooBDecay.h"
#include "RooDecay.h"
#include "RooExponential.h"
#include "RooLognormal.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooMultiVarGaussian.h"
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
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/roofit/functions/LinearFunctionWithOffset.h"
#include "doofit/roofit/functions/CPCoefficient.h"
#include "doofit/roofit/pdfs/DooCubicSplinePdf.h"
#include "P2VV/RooCubicSplineFun.h"
#include "P2VV/RooCubicSplineKnot.h"
#include "P2VV/RooAbsGaussModelEfficiency.h"
#include "P2VV/RooGaussEfficiencyModel.h"
#include "P2VV/RooEffResAddModel.h"
#include "doofit/fitter/splot/SPlotFit2.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;
using namespace doofit::roofit::functions;
using namespace doofit::roofit::pdfs;
using namespace doofit::fitter::splot;

TMatrixDSym CreateCovarianceMatrix(const int size, RooRealVar* p0sigma, RooRealVar* p1sigma, RooRealVar* p0p1corr, RooRealVar* dp0sigma = 0, RooRealVar* dp1sigma = 0, RooRealVar* p0dp0corr = 0, RooRealVar* p0dp1corr = 0, RooRealVar* p1dp0corr = 0, RooRealVar* p1dp1corr = 0, RooRealVar* dp0dp1corr = 0);

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  gStyle->SetTitleOffset(1.15,"Y");
  gStyle->SetPadLeftMargin(0.16);
  TCanvas c("c","c",800,600);

  bool single_optimization = config.getBool("single_optimization");
  bool optimize_Kpipi = config.getBool("optimize_Kpipi");
  bool cp_fit = config.getBool("cp_fit");
  bool pereventresolution = config.getBool("pereventresolution");
  bool fits = config.getBool("fits");

  RooRealVar        obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5150,5500,"MeV/c^{2}");
  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");
  RooRealVar        obsEtaOS("obsEtaOSwCharm","#eta_{OS}",0.,0.5);
  RooRealVar        obsEtaSS("obsEtaSS","#eta_{SS}",0.,0.5);
  RooRealVar        obsTimeErr("obsTimeErr","#sigma_{t}",0.005,0.2,"ps");
  RooCategory       obsTagOS("obsTagOSwCharm_NoZero","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  RooCategory       obsTagSS("obsTagSS_NoZero","Flavour Tag");
  obsTagSS.defineType("B0",1);
  obsTagSS.defineType("B0bar",-1);
  RooCategory       catTag("catTaggedOSSS","OS or SS tagged");
  catTag.defineType("OS",1);
  catTag.defineType("SS",-1);
  catTag.defineType("both",10);
  catTag.defineType("untagged",0);
  RooRealVar        BDT_classifier_Kpipi("BDT_wPIDs_LowMass_Kpipi_classifier","BDT_classifier",-1,1);
  RooRealVar        BDT_classifier_KKpi("BDT_wPIDs_LowMass_KKpi_classifier","BDT_classifier",-1,1);

  RooCategory       catYear("catYear","catYear");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);

  RooArgSet         observables(obsMass,BDT_classifier_Kpipi,BDT_classifier_KKpi,"observables");
  RooArgSet         categories(catYear,catDDFinalStateParticles,"categories");
  if (cp_fit) {
    observables.add(obsTime);
    observables.add(obsEtaOS);
    observables.add(obsEtaSS);
    if (pereventresolution) observables.add(obsTimeErr);
    observables.add(obsTagOS);
    observables.add(obsTagSS);
    categories.add(catTag);
  }

  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));

  data.Print();

  // Mass PDF
  // Signal
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");
  RooRealVar        parSigMassSigmaScale("parSigMassSigmaScale","Scale of MC resolution",1,0,2);

  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  RooProduct        parSigMassSigma1Product("parSigMassSigma1Product","parSigMassSigma1Product",RooArgList(parSigMassSigma1,parSigMassSigmaScale));
  RooRealVar        parSigMassCB1Expo("parSigMassCB1Expo","parSigMassCB1Expo",10);
  RooRealVar        parSigMassCB1Alpha("parSigMassCB1Alpha","parSigMassCB1Alpha",1.28);
  RooCBShape        pdfSigMassCB1("pdfSigMassCB1","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma1Product,parSigMassCB1Alpha,parSigMassCB1Expo);

  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooProduct        parSigMassSigma2Product("parSigMassSigma2Product","parSigMassSigma2Product",RooArgList(parSigMassSigma2,parSigMassSigmaScale));
  RooRealVar        parSigMassCB2Expo("parSigMassCB2Expo","parSigMassCB2Expo",10);
  RooRealVar        parSigMassCB2Alpha("parSigMassCB2Alpha","parSigMassCB2Alpha",-1.32);
  RooCBShape        pdfSigMassCB2("pdfSigMassCB2","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma2Product,parSigMassCB2Alpha,parSigMassCB2Expo);

  RooRealVar        parSigMassSigma3("parSigMassSigma3","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooProduct        parSigMassSigma3Product("parSigMassSigma3Product","parSigMassSigma3Product",RooArgList(parSigMassSigma3,parSigMassSigmaScale));
  RooRealVar        parSigMassCB3Expo("parSigMassCB3Expo","parSigMassCB3Expo",10,1,100);
  RooRealVar        parSigMassCB3Alpha("parSigMassCB3Alpha","parSigMassCB3Alpha",2,0,5);
  RooCBShape        pdfSigMassCB3("pdfSigMassCB3","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma3Product,parSigMassCB3Alpha,parSigMassCB3Expo);

  RooRealVar        parSigMassCBFraction("parSigMassCBFraction","parSigMassCBFraction",0.5);
  RooRealVar        parSigMassCBFraction2("parSigMassCBFraction2","parSigMassCBFraction2",0.5);
  RooAddPdf         pdfSigMass("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB3,pdfSigMassCB2),RooArgList(parSigMassCBFraction,parSigMassCBFraction2));

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

  // Bs --> DsD background
  RooFormulaVar     parBkgBsDsDMassMean("parBkgBsDsDMassMean","shifted Bs --> DsD Mean Mass","@0+87.35",RooArgList(parBkgDsDMean));
  RooCBShape        pdfBkgBsDsDMassCB1("pdfBkgBsDsDMassCB1","Mass PDF",obsMass,parBkgBsDsDMassMean,parBkgDsDMassSigma1,parBkgDsDMassCB1Alpha,parBkgDsDMassCB1Expo);
  RooCBShape        pdfBkgBsDsDMassCB2("pdfBkgBsDsDMassCB2","Mass PDF",obsMass,parBkgBsDsDMassMean,parBkgDsDMassSigma2,parBkgDsDMassCB2Alpha,parBkgDsDMassCB2Expo);
  RooAddPdf         pdfBkgBsDsDMass("pdfBkgBsDsDMass","pdfBkgBsDsDMass",RooArgList(pdfBkgBsDsDMassCB1,pdfBkgBsDsDMassCB2),parBkgDsDMassCBFraction);

  // Bs --> DD signal
  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.35",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1Product,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2Product,parSigMassCB2Alpha,parSigMassCB2Expo);
  RooCBShape        pdfSigBsMassCB3("pdfSigBsMassCB3","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma3Product,parSigMassCB3Alpha,parSigMassCB3Expo);
  RooAddPdf         pdfSigBsMass("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB3,pdfSigBsMassCB2),RooArgList(parSigMassCBFraction,parSigMassCBFraction2));

  // Bd --> D*+ D- with D*+ --> D+ pi0 Background
  RooRealVar        parBkgDstDLowMassMean("parBkgDstDLowMassMean","Mean Mass",5060,5050,5070,"MeV/c^{2}");
  RooRealVar        parBkgDstDLowMassSigma("parBkgDstDLowMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDLowMass("pdfBkgDstDLowMass","Lower DstD Mass PDF",obsMass,parBkgDstDLowMassMean,parBkgDstDLowMassSigma);

  RooRealVar        parBkgDstDHighMassMean("parBkgDstDHighMassMean","Mean Mass",5120,5100,5140,"MeV/c^{2}");
  RooRealVar        parBkgDstDHighMassSigma("parBkgDstDHighMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDHighMass("pdfBkgDstDHighMass","Upper DstD Mass PDF",obsMass,parBkgDstDHighMassMean,parBkgDstDHighMassSigma);

  RooRealVar        parBkgDstDMassFraction("parBkgDstDMassFraction","fraction between low and high component",0.5,0,1);
  RooAddPdf         pdfBkgDstDMass("pdfBkgDstDMass","pdfBkgDstDMass",RooArgList(pdfBkgDstDLowMass,pdfBkgDstDHighMass),parBkgDstDMassFraction);

  // Bs --> D*+ D- with D*+ --> D+ pi0 Background
  RooFormulaVar     parBkgBsDstDLowMassMean("parBkgBsDstDLowMassMean","Mean Mass","@0+87.35",RooArgList(parBkgDstDLowMassMean));
  RooGaussian       pdfBkgBsDstDLowMass("pdfBkgBsDstDLowMass","Lower DstD Mass PDF",obsMass,parBkgBsDstDLowMassMean,parBkgDstDLowMassSigma);

  RooFormulaVar     parBkgBsDstDHighMassMean("parBkgBsDstDHighMassMean","Mean Mass","@0+87.35",RooArgList(parBkgDstDHighMassMean));
  RooGaussian       pdfBkgBsDstDHighMass("pdfBkgBsDstDHighMass","Upper DstD Mass PDF",obsMass,parBkgBsDstDHighMassMean,parBkgDstDHighMassSigma);

  RooRealVar        parBkgBsDstDMassFraction("parBkgBsDstDMassFraction","fraction between low and high component",0.5,0,1);
  RooAddPdf         pdfBkgBsDstDMass("pdfBkgBsDstDMass","pdfBkgBsDstDMass",RooArgList(pdfBkgBsDstDLowMass,pdfBkgBsDstDHighMass),parBkgBsDstDMassFraction);

  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);
  RooRealVar        parBkgExponent_Kpipi("parBkgExponent_Kpipi","parBkgExponent_Kpipi",-0.001,-1,1);
  RooExponential    pdfBkgMass_Kpipi("pdfBkgMass_Kpipi","pdfBkgMass_Kpipi",obsMass,parBkgExponent_Kpipi);
  RooRealVar        parBkgExponent_KKpi("parBkgExponent_KKpi","parBkgExponent_KKpi",-0.001,-1,1);
  RooExponential    pdfBkgMass_KKpi("pdfBkgMass_KKpi","pdfBkgMass_KKpi",obsMass,parBkgExponent_KKpi);

  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11("parBkgBsDsDYield_11","parBkgBsDsDYield_11",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12("parBkgBsDsDYield_12","parBkgBsDsDYield_12",1000,0,2000);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parBkgDstDYield_11("parBkgDstDYield_11","parBkgDstDYield_11",5000,0,10000);
  RooRealVar        parBkgDstDYield_12("parBkgDstDYield_12","parBkgDstDYield_12",5000,0,10000);
  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);

  RooExtendPdf      pdfSigExtend_11("pdfSigExtend_11","pdfSigExtend_11",pdfSigMass,parSigYield_11);
  RooExtendPdf      pdfSigExtend_12("pdfSigExtend_12","pdfSigExtend_12",pdfSigMass,parSigYield_12);
  RooExtendPdf      pdfBkgDsDExtend_11("pdfBkgDsDExtend_11","pdfBkgDsDExtend_11",pdfBkgDsDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfBkgDsDExtend_12("pdfBkgDsDExtend_12","pdfBkgDsDExtend_12",pdfBkgDsDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfBkgBsDsDExtend_11("pdfBkgBsDsDExtend_11","pdfBkgBsDsDExtend_11",pdfBkgBsDsDMass,parBkgBsDsDYield_11);
  RooExtendPdf      pdfBkgBsDsDExtend_12("pdfBkgBsDsDExtend_12","pdfBkgBsDsDExtend_12",pdfBkgBsDsDMass,parBkgBsDsDYield_12);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfBkgDstDExtend_11("pdfBkgDstDExtend_11","pdfBkgDstDExtend_11",pdfBkgDstDMass,parBkgDstDYield_11);
  RooExtendPdf      pdfBkgDstDExtend_12("pdfBkgDstDExtend_12","pdfBkgDstDExtend_12",pdfBkgDstDMass,parBkgDstDYield_12);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);

  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11/*,pdfBkgDstDExtend_11,pdfBkgBsDsDExtend_11*/));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12/*,pdfBkgDstDExtend_12,pdfBkgBsDsDExtend_12*/));

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
  RooExtendPdf      pdfBkgExtend_11_Kpipi("pdfBkgExtend_11_Kpipi","pdfBkgExtend_11_Kpipi",pdfBkgMass_Kpipi,parBkgYield_11_Kpipi);
  RooExtendPdf      pdfBkgExtend_12_Kpipi("pdfBkgExtend_12_Kpipi","pdfBkgExtend_12_Kpipi",pdfBkgMass_Kpipi,parBkgYield_12_Kpipi);
  RooExtendPdf      pdfBkgExtend_11_KKpi("pdfBkgExtend_11_KKpi","pdfBkgExtend_11_KKpi",pdfBkgMass_KKpi,parBkgYield_11_KKpi);
  RooExtendPdf      pdfBkgExtend_12_KKpi("pdfBkgExtend_12_KKpi","pdfBkgExtend_12_KKpi",pdfBkgMass_KKpi,parBkgYield_12_KKpi);

  RooAddPdf         pdfMass_11_Kpipi("pdfMass_11_Kpipi","Mass PDF",RooArgList(pdfSigExtend_11_Kpipi,pdfBkgDsDExtend_11_Kpipi,pdfSigBsExtend_11_Kpipi,pdfBkgExtend_11_Kpipi/*,pdfBkgDstDExtend_11_Kpipi,pdfBkgBsDsDExtend_11_Kpipi*/));
  RooAddPdf         pdfMass_12_Kpipi("pdfMass_12_Kpipi","Mass PDF",RooArgList(pdfSigExtend_12_Kpipi,pdfBkgDsDExtend_12_Kpipi,pdfSigBsExtend_12_Kpipi,pdfBkgExtend_12_Kpipi/*,pdfBkgDstDExtend_12_Kpipi,pdfBkgBsDsDExtend_12_Kpipi*/));
  RooAddPdf         pdfMass_11_KKpi("pdfMass_11_KKpi","Mass PDF",RooArgList(pdfSigExtend_11_KKpi,pdfBkgDsDExtend_11_KKpi,pdfSigBsExtend_11_KKpi,pdfBkgExtend_11_KKpi/*,pdfBkgDstDExtend_11_KKpi,pdfBkgBsDsDExtend_11_KKpi*/));
  RooAddPdf         pdfMass_12_KKpi("pdfMass_12_KKpi","Mass PDF",RooArgList(pdfSigExtend_12_KKpi,pdfBkgDsDExtend_12_KKpi,pdfSigBsExtend_12_KKpi,pdfBkgExtend_12_KKpi/*,pdfBkgDstDExtend_12_KKpi,pdfBkgBsDsDExtend_12_KKpi*/));

  RooSuperCategory  supercategory_mass("supercategory_mass","supercategory_mass",RooArgList(catYear,catDDFinalStateParticles));

  RooAbsPdf*        pdfMass;
  if (single_optimization){
    pdfMass = new RooSimultaneous("pdfMass","pdfMass",catYear);
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11,"2011");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12,"2012");
    if (data.sumEntries("catDDFinalStateParticles==1") > 0) pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Kpipi_BDT_Optimization_wYields.txt");
    else pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_KKpi_BDT_Optimization_wYields.txt");
  }
  else {
    pdfMass = new RooSimultaneous("pdfMass","pdfMass",supercategory_mass);
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11_Kpipi,"{2011;Kpipi}");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12_Kpipi,"{2012;Kpipi}");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11_KKpi,"{2011;KKpi}");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12_KKpi,"{2012;KKpi}");
    pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_BDT_Optimization_wYields.txt");
  } 
  pdfMass->Print();
  pdfMass->getParameters(data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/Mass/StartingValues_Mass.new");

  // Lifetime and mixing parameters
  RooRealVar          parSigTimeTau("parSigTimeTau","#tau",1.5,1.,2.);
  RooRealVar          parSigTimeTauMean("parSigTimeTauMean","#tau",1.519);
  RooRealVar          parSigTimeTauSigma("parSigTimeTauSigma","#tau",0.005);
  RooRealVar          parSigTimeDeltaM("parSigTimeDeltaM","#Delta m",0.510,0.4,0.6);            // PDG2013 (0.510 +- 0.004)/ps
  RooRealVar          parSigTimeDeltaMMean("parSigTimeDeltaMMean","#Delta m",0.510);
  RooRealVar          parSigTimeDeltaMSigma("parSigTimeDeltaMSigma","#Delta m",0.004);
  RooRealVar          parSigEtaDeltaG("parSigEtaDeltaG","#Delta#Gamma",0.);

  // CPV parameters
  RooRealVar          parSigTimeSin2b("parSigTimeSin2b","#it{S_{D^{+}D^{-}}}",0.7,-2,2);
  RooRealVar          parSigTimeC("parSigTimeC","#it{C_{D^{+}D^{-}}}",0,-2,2);
  RooUnblindUniform   parSigTimeBlindedSin2b("parSigTimeBlindedSin2b","Blinding of #it{S_{D^{+}D^{-}}}","SB02DD3fb",2.,parSigTimeSin2b);
  RooUnblindUniform   parSigTimeBlindedC("parSigTimeBlindedC","Blinding of #it{C_{D^{+}D^{-}}}","CB02DD3fb",2.,parSigTimeC);

  // Asymmetries
  RooRealVar          parSigEtaDeltaProd_11("parSigEtaDeltaProd_11","A_{P}^{11}",-0.0066,-0.05,0.02);
  RooRealVar          parSigEtaDeltaProdMean_11("parSigEtaDeltaProdMean_11","#bar{#mu}",-0.0066);
  RooRealVar          parSigEtaDeltaProdSigma_11("parSigEtaDeltaProdSigma_11","#sigma_{#bar{mu}}",0.0026);

  RooRealVar          parSigEtaDeltaProdOffset("parSigEtaDeltaProdOffset","#Delta A_{P}",0.0004,-0.01,0.01);
  RooRealVar          parSigEtaDeltaProdOffsetMean("parSigEtaDeltaProdOffsetMean","#bar{#mu}",0.0004);
  RooRealVar          parSigEtaDeltaProdOffsetSigma("parSigEtaDeltaProdOffsetSigma","#sigma_{#bar{mu}}",0.0018);
  RooAddition         parSigEtaDeltaProd_12("parSigEtaDeltaProd_12","B0/B0bar production asymmetry 2012",RooArgList(parSigEtaDeltaProd_11,parSigEtaDeltaProdOffset));

  RooArgSet         Gaussian_Constraints("Gaussian_Constraints");
  // OS tags
  RooRealVar          parSigEtaDeltaP0_OS("parSigEtaDeltaP0_OS","#Delta p_{0}^{OS}",0.0140,0.,0.03);
  RooRealVar          parSigEtaDeltaP0Mean_OS("parSigEtaDeltaP0Mean_OS","#bar{#delta p_{0}}",0.0148);
  RooRealVar          parSigEtaDeltaP0Sigma_OS("parSigEtaDeltaP0Sigma_OS","#sigma_{#bar{#delta p_{0}}}",0.0012);  // B+ value 0.0016  Kstar 0.0031
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_OS);

  RooRealVar          parSigEtaDeltaP1_OS("parSigEtaDeltaP1_OS","#Delta p_{1}^{OS}",0.066,0.,0.1);
  RooRealVar          parSigEtaDeltaP1Mean_OS("parSigEtaDeltaP1Mean_OS","#bar{#delta p_{1}}",0.070);
  RooRealVar          parSigEtaDeltaP1Sigma_OS("parSigEtaDeltaP1Sigma_OS","#sigma_{#bar{#delta p_{1}}}",0.012);   // B+ value 0.018   Kstar 0.035
  Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_OS);

  // SS tags
  RooRealVar          parSigEtaDeltaP0_SS("parSigEtaDeltaP0_SS","#Delta p_{0}^{SS}",-0.003,-0.02,0.02);
  RooRealVar          parSigEtaDeltaP0Mean_SS("parSigEtaDeltaP0Mean_SS","#bar{#delta p_{0}}",-0.0026);
  RooRealVar          parSigEtaDeltaP0Sigma_SS("parSigEtaDeltaP0Sigma_SS","#sigma_{#bar{#delta p_{0}}}",0.0044);
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_SS);

  RooRealVar          parSigEtaDeltaP1_SS("parSigEtaDeltaP1_SS","#Delta p_{1}^{SS}",-0.18,-0.7,0.3);
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
    std::string bintitle = "h_{" + boost::lexical_cast<std::string>(i) + "}";
    parSigTimeAccCSpline = new RooRealVar(binname.c_str(),bintitle.c_str(),1,0,2);
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
  RooRealVar          parSigEtaP0_OS("parSigEtaP0_OS","p_{0}^{OS}",0.3815,0.0,0.1);
  RooRealVar          parSigEtaP0Mean_OS("parSigEtaP0Mean_OS","#bar{p}_{0}",0.3815);
  RooRealVar          parSigEtaP0Sigma_OS("parSigEtaP0Sigma_OS","#sigma_{#bar{p}_{0}}",0.0019);   // B+ value 0.0011  Kstar 0.0022
  Gaussian_Constraints.add(parSigEtaP0Sigma_OS);

  RooRealVar          parSigEtaP1_OS("parSigEtaP1_OS","p_{1}^{OS}",0.978,0.9,1.1);
  RooRealVar          parSigEtaP1Mean_OS("parSigEtaP1Mean_OS","#bar{p}_{1}",0.978);
  RooRealVar          parSigEtaP1Sigma_OS("parSigEtaP1Sigma_OS","#sigma_{#bar{p}_{1}}",0.007);  // B+ value 0.012   Kstar 0.024
  Gaussian_Constraints.add(parSigEtaP1Sigma_OS);
  
  RooRealVar          parSigEtaP0P1CorrelationCoeff_OS("parSigEtaP0P1CorrelationCoeff_OS","correlation coefficient between p0 and p1 OS",-0.102);
  RooRealVar          parSigEtaP0DeltaP0CorrelationCoeff_OS("parSigEtaP0DeltaP0CorrelationCoeff_OS","correlation coefficient between p0 and Delta p0 OS",0.036);
  RooRealVar          parSigEtaP0DeltaP1CorrelationCoeff_OS("parSigEtaP0DeltaP1CorrelationCoeff_OS","correlation coefficient between p0 and Delta p1 OS",0.001);
  RooRealVar          parSigEtaP1DeltaP0CorrelationCoeff_OS("parSigEtaP1DeltaP0CorrelationCoeff_OS","correlation coefficient between p1 and Delta p0 OS",-0.002);
  RooRealVar          parSigEtaP1DeltaP1CorrelationCoeff_OS("parSigEtaP1DeltaP1CorrelationCoeff_OS","correlation coefficient between p1 and Delta p1 OS",-0.037);
  RooRealVar          parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS("parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS","correlation coefficient between Delta p0 and Delta p1 OS",0.059);

  RooRealVar          parSigEtaMean_OS("parSigEtaMean_OS","Mean on per-event mistag",0.3786);

  RooRealVar          parSigEtaP0_SS("parSigEtaP0_SS","p_{0}^{SS}",0.4228,0.3,0.5);
  RooRealVar          parSigEtaP0Mean_SS("parSigEtaP0Mean_SS","#bar{p}_{0}",0.4232);
  RooRealVar          parSigEtaP0Sigma_SS("parSigEtaP0Sigma_SS","#sigma_{#bar{p}_{0}}",0.0029);
  Gaussian_Constraints.add(parSigEtaP0Sigma_SS);

  RooRealVar          parSigEtaP1_SS("parSigEtaP1_SS","p_{1}^{SS}",1.01,0.7,1.1);
  RooRealVar          parSigEtaP1Mean_SS("parSigEtaP1Mean_SS","#bar{p}_{1}",1.011);
  RooRealVar          parSigEtaP1Sigma_SS("parSigEtaP1Sigma_SS","#sigma_{#bar{p}_{1}}",0.064);
  Gaussian_Constraints.add(parSigEtaP1Sigma_SS);

  RooRealVar          parSigEtaP0P1CorrelationCoeff_SS("parSigEtaP0P1CorrelationCoeff_SS","correlation coefficient between p0 and p1 SS",0.053);
  RooRealVar          parSigEtaP0DeltaP0CorrelationCoeff_SS("parSigEtaP0DeltaP0CorrelationCoeff_SS","correlation coefficient between p0 and Delta p0 SS",0.013);
  RooRealVar          parSigEtaP0DeltaP1CorrelationCoeff_SS("parSigEtaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between p0 and Delta p1 SS",-0.009);
  RooRealVar          parSigEtaP1DeltaP0CorrelationCoeff_SS("parSigEtaP1DeltaP0CorrelationCoeff_SS","correlation coefficient between p1 and Delta p0 SS",-0.009);
  RooRealVar          parSigEtaP1DeltaP1CorrelationCoeff_SS("parSigEtaP1DeltaP1CorrelationCoeff_SS","correlation coefficient between p1 and Delta p1 SS",0.015);
  RooRealVar          parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS("parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between Delta p0 and Delta p1 SS",0.025);

  RooRealVar          parSigEtaMean_SS("parSigEtaMean_SS","Mean on per-event mistag",0.42484);

//=========================================================================================================================================================================================================================

  // RooBDecay parameters
  RooConstVar       parSigTimeSinh("parSigTimeSinh","Sh_{f}",0.0);

  CPCoefficient     parSigTimeCosh_11_OS("parSigTimeCosh_11_OS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_OS("parSigTimeCosh_12_OS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_OS("parSigTimeSin_11_OS",parSigTimeBlindedSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_OS("parSigTimeSin_12_OS",parSigTimeBlindedSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_OS("parSigTimeCos_11_OS",parSigTimeBlindedC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_OS("parSigTimeCos_12_OS",parSigTimeBlindedC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kCos);

  CPCoefficient     parSigTimeCosh_11_SS("parSigTimeCosh_11_SS",RooConst(1.0),obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_SS("parSigTimeCosh_12_SS",RooConst(1.0),obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_SS("parSigTimeSin_11_SS",parSigTimeBlindedSin2b,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_SS("parSigTimeSin_12_SS",parSigTimeBlindedSin2b,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_SS("parSigTimeCos_11_SS",parSigTimeBlindedC,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_SS("parSigTimeCos_12_SS",parSigTimeBlindedC,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCos);

  CPCoefficient     parSigTimeCosh_11_BS("parSigTimeCosh_11_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_BS("parSigTimeCosh_12_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_BS("parSigTimeSin_11_BS",parSigTimeBlindedSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_BS("parSigTimeSin_12_BS",parSigTimeBlindedSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_BS("parSigTimeCos_11_BS",parSigTimeBlindedC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_BS("parSigTimeCos_12_BS",parSigTimeBlindedC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCos);

//=========================================================================================================================================================================================================================

  // Decay Time PDF

  RooBDecay*        pdfSigTime_11_OS = new RooBDecay("pdfSigTime_11_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_OS,parSigTimeSinh,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay*        pdfSigTime_11_SS = new RooBDecay("pdfSigTime_11_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_SS,parSigTimeSinh,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay*        pdfSigTime_12_OS = new RooBDecay("pdfSigTime_12_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_OS,parSigTimeSinh,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay*        pdfSigTime_12_SS = new RooBDecay("pdfSigTime_12_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_SS,parSigTimeSinh,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay*        pdfSigTime_11_BS = new RooBDecay("pdfSigTime_11_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_BS,parSigTimeSinh,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay*        pdfSigTime_12_BS = new RooBDecay("pdfSigTime_12_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_BS,parSigTimeSinh,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);

//========================================================================================================================================================================================================================

  // Build Simultaneous PDF
  RooSuperCategory  supercategory_time("supercategory_time","supercategory_time",RooArgSet(catYear,catTag));
  RooSimultaneous   pdf("pdf","P",supercategory_time);
  pdf.addPdf(*pdfSigTime_11_OS,"{2011;OS}");
  pdf.addPdf(*pdfSigTime_11_SS,"{2011;SS}");
  pdf.addPdf(*pdfSigTime_11_BS,"{2011;both}");
  pdf.addPdf(*pdfSigTime_12_OS,"{2012;OS}");
  pdf.addPdf(*pdfSigTime_12_SS,"{2012;SS}");
  pdf.addPdf(*pdfSigTime_12_BS,"{2012;both}");

  cout  <<  "simultaneous PDF built"  <<  endl;

  // Get Starting Values
  pdf.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
  pdf.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
  pdf.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Acceptance_Splines.txt");
  Gaussian_Constraints.readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");

  pdf.Print();

  TMatrixDSym           covariancematrixSigEta_OS = CreateCovarianceMatrix(4, &parSigEtaP0Sigma_OS, &parSigEtaP1Sigma_OS, &parSigEtaP0P1CorrelationCoeff_OS, &parSigEtaDeltaP0Sigma_OS, &parSigEtaDeltaP1Sigma_OS, &parSigEtaP0DeltaP0CorrelationCoeff_OS, &parSigEtaP0DeltaP1CorrelationCoeff_OS, &parSigEtaP1DeltaP0CorrelationCoeff_OS, &parSigEtaP1DeltaP1CorrelationCoeff_OS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS);
  TMatrixDSym           covariancematrixSigEta_SS = CreateCovarianceMatrix(4, &parSigEtaP0Sigma_SS, &parSigEtaP1Sigma_SS, &parSigEtaP0P1CorrelationCoeff_SS, &parSigEtaDeltaP0Sigma_SS, &parSigEtaDeltaP1Sigma_SS, &parSigEtaP0DeltaP0CorrelationCoeff_SS, &parSigEtaP0DeltaP1CorrelationCoeff_SS, &parSigEtaP1DeltaP0CorrelationCoeff_SS, &parSigEtaP1DeltaP1CorrelationCoeff_SS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS);

  RooArgSet             constrainingPdfs("constrainingPdfs");
  RooGaussian           conpdfSigTimeTau("conpdfSigTimeTau","constraint for #tau",parSigTimeTau,parSigTimeTauMean,parSigTimeTauSigma);
  RooGaussian           conpdfSigTimeDeltaM("conpdfSigTimeDeltaM","constraint for #Delta m",parSigTimeDeltaM,parSigTimeDeltaMMean,parSigTimeDeltaMSigma);
  RooGaussian           conpdfSigEtaDeltaProd_11("conpdfSigEtaDeltaProd_11","Gaussian Constraint for production asymmetry 2011",parSigEtaDeltaProd_11,parSigEtaDeltaProdMean_11,parSigEtaDeltaProdSigma_11);
  RooGaussian           conpdfSigEtaDeltaProd_12("conpdfSigEtaDeltaProd_12","Gaussian Constraint for production asymmetry 2012",parSigEtaDeltaProdOffset,parSigEtaDeltaProdOffsetMean,parSigEtaDeltaProdOffsetSigma);
  RooGaussian           conpdfSigEtaDeltaP0_OS("conpdfSigEtaDeltaP0_OS","conpdfSigEtaDeltaP0_OS",parSigEtaDeltaP0_OS,parSigEtaDeltaP0Mean_OS,parSigEtaDeltaP0Sigma_OS);
  RooGaussian           conpdfSigEtaDeltaP1_OS("conpdfSigEtaDeltaP1_OS","conpdfSigEtaDeltaP1_OS",parSigEtaDeltaP1_OS,parSigEtaDeltaP1Mean_OS,parSigEtaDeltaP1Sigma_OS);
  RooGaussian           conpdfSigEtaDeltaP0_SS("conpdfSigEtaDeltaP0_SS","conpdfSigEtaDeltaP0_SS",parSigEtaDeltaP0_SS,parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP0Sigma_SS);
  RooGaussian           conpdfSigEtaDeltaP1_SS("conpdfSigEtaDeltaP1_SS","conpdfSigEtaDeltaP1_SS",parSigEtaDeltaP1_SS,parSigEtaDeltaP1Mean_SS,parSigEtaDeltaP1Sigma_SS);  
  RooGaussian           conpdfSigEtaP0_OS("conpdfSigEtaP0_OS","Gaussian Constraint for Offset parameter",parSigEtaP0_OS,parSigEtaP0Mean_OS,parSigEtaP0Sigma_OS);
  RooGaussian           conpdfSigEtaP1_OS("conpdfSigEtaP1_OS","Gaussian Constraint for Scale parameter",parSigEtaP1_OS,parSigEtaP1Mean_OS,parSigEtaP1Sigma_OS);
  RooMultiVarGaussian   conpdfSigEta_OS("conpdfSigEta_OS","constraint for p0 and p1 of OS FT calibration",RooArgList(parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS),RooArgList(parSigEtaP0Mean_OS,parSigEtaP1Mean_OS,parSigEtaDeltaP0Mean_OS,parSigEtaDeltaP1Mean_OS),covariancematrixSigEta_OS);
  RooGaussian           conpdfSigEtaP0_SS("conpdfSigEtaP0_SS","Gaussian Constraint for Offset parameter",parSigEtaP0_SS,parSigEtaP0Mean_SS,parSigEtaP0Sigma_SS);
  RooGaussian           conpdfSigEtaP1_SS("conpdfSigEtaP1_SS","Gaussian Constraint for Scale parameter",parSigEtaP1_SS,parSigEtaP1Mean_SS,parSigEtaP1Sigma_SS);
  RooMultiVarGaussian   conpdfSigEta_SS("conpdfSigEta_SS","constraint for SS FT calibration",RooArgList(parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS),RooArgList(parSigEtaP0Mean_SS,parSigEtaP1Mean_SS,parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP1Mean_SS),covariancematrixSigEta_SS);  

  constrainingPdfs.add(conpdfSigTimeTau);
  constrainingPdfs.add(conpdfSigTimeDeltaM);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_11);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_12);
  constrainingPdfs.add(conpdfSigEta_OS);
  constrainingPdfs.add(conpdfSigEta_SS);

  cout  <<  "Constraints added" <<  endl;

  TIterator*  iterator = constrainingPdfs.createIterator();
  RooAbsPdf*  constrainingPdf;
  while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
    constrainingPdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
    constrainingPdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
  }

  // Fit options
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(config.getInt("num_cpu")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","migrad"))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));
  if (cp_fit) {
    fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
    // fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
    if (!pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS)))));
    else fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS,obsTimeErr)))));
  }
  else {
    fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
    fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  }

  RooDataSet* reduced_data;
  RooDataSet* reduced_data_sweighted;
  obsMass.setRange("signal",5250,5310);
  std::vector<double> bdt_cut;
  std::vector<double> signal_yield;
  std::vector<double> background_yield;
  std::vector<double> sensitivity_S;
  std::vector<double> sensitivity_C;
  SPlotFit2* splotfit;
  RooArgSet set_of_yields;
  RooRealVar SigWeight_11_Kpipi("parSigYield_11_Kpipi_sw","signal weight for 11 Kpipi",-10,10);
  RooRealVar SigWeight_11_KKpi("parSigYield_11_KKpi_sw","signal weight for 11 KKpi",-10,10);
  RooRealVar SigWeight_12_Kpipi("parSigYield_12_Kpipi_sw","signal weight for 12 Kpipi",-10,10);
  RooRealVar SigWeight_12_KKpi("parSigYield_12_KKpi_sw","signal weight for 12 KKpi",-10,10);
  RooFormulaVar sum_of_signal_weights_year_finalstate("sum_of_signal_weights_year_finalstate","sum of signal weights","@0+@1+@2+@3",RooArgList(SigWeight_11_Kpipi,SigWeight_11_KKpi,SigWeight_12_Kpipi,SigWeight_12_KKpi));
  RooRealVar SigWeight_11("parSigYield_11_sw","signal weight for 11",-10,10);
  RooRealVar SigWeight_12("parSigYield_12_sw","signal weight for 12",-10,10);
  RooFormulaVar sum_of_signal_weights_year("sum_of_signal_weights_year","sum of signal weights","@0+@1",RooArgList(SigWeight_11,SigWeight_12));
  if (single_optimization) {
    set_of_yields.add(RooArgSet(parSigYield_11,parBkgDsDYield_11,parSigBsYield_11,parBkgYield_11/*,parBkgDstDYield_11,parBkgBsDsDYield_11*/));
    set_of_yields.add(RooArgSet(parSigYield_12,parBkgDsDYield_12,parSigBsYield_12,parBkgYield_12/*,parBkgDstDYield_12,parBkgBsDsDYield_12*/));
  }
  else {
    set_of_yields.add(RooArgSet(parSigYield_11_Kpipi,parBkgDsDYield_11_Kpipi,parSigBsYield_11_Kpipi,parBkgYield_11_Kpipi/*,parBkgDstDYield_11_Kpipi,parBkgBsDsDYield_11_Kpipi*/));
    set_of_yields.add(RooArgSet(parSigYield_11_KKpi,parBkgDsDYield_11_KKpi,parSigBsYield_11_KKpi,parBkgYield_11_KKpi/*,parBkgDstDYield_11_KKpi,parBkgBsDsDYield_11_KKpi*/));
    set_of_yields.add(RooArgSet(parSigYield_12_Kpipi,parBkgDsDYield_12_Kpipi,parSigBsYield_12_Kpipi,parBkgYield_12_Kpipi/*,parBkgDstDYield_12_Kpipi,parBkgBsDsDYield_12_Kpipi*/));
    set_of_yields.add(RooArgSet(parSigYield_12_KKpi,parBkgDsDYield_12_KKpi,parSigBsYield_12_KKpi,parBkgYield_12_KKpi/*,parBkgDstDYield_12_KKpi,parBkgBsDsDYield_12_KKpi*/));
  }
  RooFitResult* fit_result;
  RooAbsReal* background_integral;

  double scan_begin = config.getDouble("scan_begin");
  double scan_end = config.getDouble("scan_end");
  int n_steps = config.getInt("n_steps");
  double scan_width = (scan_end - scan_begin)/n_steps;

  if (fits) {
    for (int i = 0; i <= n_steps; ++i) {
      double cutvalue = scan_begin + i*scan_width;
      cout << cutvalue  << endl;
      if (single_optimization) {
        reduced_data = dynamic_cast<RooDataSet*>(data.reduce(TString(config.getString("bdt_classifier")+"_classifier>"+to_string(cutvalue))));
        if (data.sumEntries("catDDFinalStateParticles==1") > 0) pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Kpipi_BDT_Optimization.txt");
        else pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_KKpi_BDT_Optimization.txt");
      }
      else {
        pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_BDT_Optimization.txt");
        if (optimize_Kpipi) reduced_data = dynamic_cast<RooDataSet*>(data.reduce(TString(config.getString("bdt_classifier")+"_classifier>"+to_string(cutvalue)+"||catDDFinalStateParticles==0")));
        else reduced_data = dynamic_cast<RooDataSet*>(data.reduce(TString(config.getString("bdt_classifier")+"_classifier>"+to_string(cutvalue)+"||catDDFinalStateParticles==1")));
      } 
      reduced_data->Print();
      if (cp_fit) {
        splotfit = new SPlotFit2(*pdfMass,*reduced_data,set_of_yields);
        splotfit->set_use_minos(false);
        splotfit->set_num_cpu(config.getInt("num_cpu"));
        RooMsgService::instance().setStreamStatus(0, false);
        RooMsgService::instance().setStreamStatus(1, false);
        splotfit->Fit();
        RooMsgService::instance().setStreamStatus(0, true);
        RooMsgService::instance().setStreamStatus(1, true);
        if (single_optimization) {
          reduced_data->addColumn(sum_of_signal_weights_year);
          reduced_data_sweighted = new RooDataSet("reduced_data_sweighted","reduced_data_sweighted",reduced_data,*(reduced_data->get()),TString(catTag.GetName())+"!=0","sum_of_signal_weights_year");
        }
        else {
          reduced_data->addColumn(sum_of_signal_weights_year_finalstate);
          reduced_data_sweighted = new RooDataSet("reduced_data_sweighted","reduced_data_sweighted",reduced_data,*(reduced_data->get()),TString(catTag.GetName())+"!=0","sum_of_signal_weights_year_finalstate");
        }
        fit_result = pdf.fitTo(*reduced_data_sweighted,fitting_args);
        pdf.getParameters(data)->writeToFile(TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")+"/FitResults/FitResults_Time_"+to_string(i)+".txt"));
        doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
        fitresultprinter.Print();
        if (fit_result->status() > 0) continue;
        bdt_cut += cutvalue;
        sensitivity_S += parSigTimeSin2b.getError();
        sensitivity_C += parSigTimeC.getError();
        delete reduced_data_sweighted;
      }
      else {
        fit_result = pdfMass->fitTo(*reduced_data,fitting_args);
        if (fit_result->status() > 0) continue;
        bdt_cut += cutvalue;
        pdfMass->getParameters(data)->writeToFile(TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")+"/FitResults/FitResults_Mass_"+to_string(i)+".txt"));
        doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
        fitresultprinter.Print();
        if (single_optimization) {
          signal_yield += parSigYield_11.getVal() + parSigYield_12.getVal();
          background_integral = pdfBkgMass.createIntegral(obsMass,NormSet(obsMass),Range("signal"));
          background_yield += parBkgYield_11.getVal()*background_integral->getVal() + parBkgYield_12.getVal()*background_integral->getVal();
        }
        else if (optimize_Kpipi) {
          signal_yield += parSigYield_11_Kpipi.getVal() + parSigYield_12_Kpipi.getVal();
          background_integral = pdfBkgMass_Kpipi.createIntegral(obsMass,NormSet(obsMass),Range("signal"));
          background_yield += parBkgYield_11_Kpipi.getVal()*background_integral->getVal() + parBkgYield_12_Kpipi.getVal()*background_integral->getVal();
        }
        else {
          signal_yield += parSigYield_11_KKpi.getVal() + parSigYield_12_KKpi.getVal();
          background_integral = pdfBkgMass_KKpi.createIntegral(obsMass,NormSet(obsMass),Range("signal"));
          background_yield += parBkgYield_11_KKpi.getVal()*background_integral->getVal() + parBkgYield_12_KKpi.getVal()*background_integral->getVal();
        }
      }
    }
  }

  if (cp_fit) {
    if (fits) {
      TGraph*  gr_S_sensitivity = new TGraph(sensitivity_S.size(), &bdt_cut[0], &sensitivity_S[0]);
      gr_S_sensitivity->SetLineColor(2);
      gr_S_sensitivity->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
      gr_S_sensitivity->GetYaxis()->SetTitle("sensitivity S_{D^{+}D^{-}}");
      gr_S_sensitivity->GetXaxis()->SetLimits(scan_begin,scan_end);
      gr_S_sensitivity->Draw("AC");
      printPlot(&c, "Sensitivity_S", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));
  
      TGraph*  gr_C_sensitivity = new TGraph(sensitivity_C.size(), &bdt_cut[0], &sensitivity_C[0]);
      gr_C_sensitivity->SetLineColor(2);
      gr_C_sensitivity->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
      gr_C_sensitivity->GetYaxis()->SetTitle("sensitivity C_{D^{+}D^{-}}");
      gr_C_sensitivity->GetXaxis()->SetLimits(scan_begin,scan_end);
      gr_C_sensitivity->Draw("AC");
      printPlot(&c, "Sensitivity_C", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));
  
      TFile   sensitivitiesfile(TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")+"/Sensitivities.root"),"recreate");
      gr_S_sensitivity->Write("gr_S_sensitivity");
      gr_C_sensitivity->Write("gr_C_sensitivity");
      sensitivitiesfile.Close();

      for (int i = 0; i < sensitivity_S.size(); ++i)  cout <<  bdt_cut.at(i)  <<  "\t"  <<  round(sensitivity_S.at(i)*10000)/10000 <<  "\t"  <<  round(10000*sensitivity_C.at(i))/10000 <<  "\t" << round(sensitivity_S.at(i)*10000)/10000 + round(sensitivity_C.at(i)*10000)/10000 << endl;
    }
    else {
      TFile sensitivitiesfile(TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")+"/Sensitivities.root"),"read");
      TGraph* read_in_sensitivity_S = dynamic_cast<TGraph*>(sensitivitiesfile.Get("gr_S_sensitivity"));
      TGraph* read_in_sensitivity_C = dynamic_cast<TGraph*>(sensitivitiesfile.Get("gr_C_sensitivity"));
      TMultiGraph* mg = new TMultiGraph();
      read_in_sensitivity_S->SetLineColor(2);
      read_in_sensitivity_S->SetLineStyle(2);
      read_in_sensitivity_C->SetLineColor(4);
      read_in_sensitivity_C->SetLineStyle(9);
      mg->Add(read_in_sensitivity_S);
      mg->Add(read_in_sensitivity_C);
      mg->Draw("AC");
      mg->GetXaxis()->SetLimits(scan_begin,scan_end);
      mg->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
      mg->GetYaxis()->SetTitle("sensitivity");
      printPlot(&c, "Sensitivities", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));
      sensitivitiesfile.Close();
    }
  }
  else {
    std::vector<double> signal_efficiency;
    std::vector<double> signal_significance;
    std::vector<double> background_rejection;
    double total_signal_yield = *max_element(begin(signal_yield), end(signal_yield));
    double total_bkg_yield = *max_element(begin(background_yield), end(background_yield));
    for (int i = 0; i < signal_yield.size(); ++i) {
      signal_efficiency += signal_yield.at(i)/total_signal_yield;
      signal_significance += signal_yield.at(i)/sqrt(signal_yield.at(i)+background_yield.at(i));
      background_rejection += 1. - background_yield.at(i)/total_bkg_yield;
    }
    TLine BDT_cut_value(config.getDouble("optimal_cut"),0,config.getDouble("optimal_cut"),1);
    BDT_cut_value.SetLineStyle(2);

    TGraph*  gr_signal_yield = new TGraph(signal_yield.size(), &bdt_cut[0], &signal_yield[0]);
    gr_signal_yield->SetLineColor(2);
    gr_signal_yield->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_signal_yield->GetYaxis()->SetTitle("signal yield");
    gr_signal_yield->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_signal_yield->Draw("AC");
    BDT_cut_value.SetY1(gr_signal_yield->GetYaxis()->GetXmin());
    BDT_cut_value.SetY2(gr_signal_yield->GetYaxis()->GetXmax());
    BDT_cut_value.Draw();
    printPlot(&c, "SignalYield", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));
  
    TGraph*  gr_background_yield = new TGraph(background_yield.size(), &bdt_cut[0], &background_yield[0]);
    gr_background_yield->SetLineColor(2);
    gr_background_yield->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_background_yield->GetYaxis()->SetTitle("background yield");
    gr_background_yield->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_background_yield->Draw("AC");
    BDT_cut_value.SetY1(gr_background_yield->GetYaxis()->GetXmin());
    BDT_cut_value.SetY2(gr_background_yield->GetYaxis()->GetXmax());
    BDT_cut_value.Draw();
    printPlot(&c, "BackgroundYield", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));
  
    TGraph*  gr_signal_efficiency = new TGraph(signal_efficiency.size(), &bdt_cut[0], &signal_efficiency[0]);
    gr_signal_efficiency->SetLineColor(2);
    gr_signal_efficiency->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_signal_efficiency->GetYaxis()->SetTitle("signal efficiency");
    gr_signal_efficiency->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_signal_efficiency->Draw("AC");
    BDT_cut_value.SetY1(gr_signal_efficiency->GetYaxis()->GetXmin());
    BDT_cut_value.SetY2(gr_signal_efficiency->GetYaxis()->GetXmax());
    BDT_cut_value.Draw();
    printPlot(&c, "SignalEfficiency", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));
  
    TGraph*  gr_signal_significance = new TGraph(signal_significance.size(), &bdt_cut[0], &signal_significance[0]);
    gr_signal_significance->SetLineColor(2);
    gr_signal_significance->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_signal_significance->GetYaxis()->SetTitle("signal significance");
    gr_signal_significance->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_signal_significance->Draw("AC");
    BDT_cut_value.SetY1(gr_signal_significance->GetYaxis()->GetXmin());
    BDT_cut_value.SetY2(gr_signal_significance->GetYaxis()->GetXmax());
    BDT_cut_value.Draw();
    printPlot(&c, "SignalSignificance", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));
  
    TGraph*  ROC_curve = new TGraph(signal_efficiency.size(), &signal_efficiency[0], &background_rejection[0]);
    ROC_curve->SetLineColor(2);
    ROC_curve->GetXaxis()->SetTitle("signal efficiency");
    ROC_curve->GetYaxis()->SetTitle("background rejection");
    ROC_curve->Draw("AC");
    printPlot(&c, "ROC_Curve", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));

    // TMultiGraph* mg = new TMultiGraph();
    // mg->Add(gr_signal_efficiency);
    // mg->Add(gr_signal_significance);
    // mg->Draw("AC");
    // mg->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    // mg->GetYaxis()->SetTitle("signal yield");
    // printPlot(&c, "Summary", TString("/home/fmeier/lhcb-tank/b02dd/run/BDT-Optimization/"+config.getString("bdt_classifier")));

    for (int i = 0; i < signal_yield.size(); ++i)  cout <<  (int)signal_yield.at(i) <<  "\t"  <<  (int)background_yield.at(i) <<  endl;
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