#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TRandom3.h"
#include <TLatex.h>

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
#include "RooChebychev.h"

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
#include "doofit/plotting/correlations/CorrelationPlot.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
#include "doofit/config/CommonConfig.h"
#include "doofit/toy/ToyFactoryStd/ToyFactoryStd.h"
#include "doofit/toy/ToyFactoryStd/ToyFactoryStdConfig.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStd.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStdConfig.h"
#include "doofit/fitter/splot/SPlotFit2.h"
#include "Erasmus/RooHORNSdini.h"

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
    std::cout << "Toy study config is optional, and only needed for bootstrapping or mass fitter validation"  <<  std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  
  int num_cpu = config.getInt("num_cpu");
  bool pereventresolution = config.getBool("pereventresolution");
  bool cp_fit = config.getBool("cp_fit");
  TString taggingcategory = config.getString("taggingcategory");
  TString OS_tagger = config.getString("OS_tagger");
  TString SS_tagger = config.getString("SS_tagger");
  bool OS_tagging = config.getBool("OS_tagging");
  bool SS_tagging = config.getBool("SS_tagging");
  bool split_years      = config.getBool("split_years");
  bool split_final_state  = config.getBool("split_final_state");
  bool split_acceptance  = config.getBool("split_acceptance");
  bool calculate_sweights = config.getBool("calculate_sweights");
  bool bootstrapping = config.getBool("bootstrapping");
  bool massfittervalidation = config.getBool("massfittervalidation");
  if ((bootstrapping || massfittervalidation) && argc < 3) {
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' - c toystudy_config_file_name" << std::endl;
    std::cout << "The toy study config file is missing! This is mandatory to perform bootstrapping or mass fitter validation!"  <<  std::endl;
    return 0;
  }
  TString method = config.getString("method");
  bool massfit = config.getBool("massfit");
  bool decaytimefit = config.getBool("decaytimefit");
  bool mistag_histograms = config.getBool("mistag_histograms");
  bool timeerr_histograms = config.getBool("timeerr_histograms");
  bool plot_acceptance = config.getBool("plot_acceptance");
  bool plot_correlation_matrix = config.getBool("plot_correlation_matrix");
  bool plot_mass_distribution = config.getBool("plot_mass_distribution");
  if (mistag_histograms || plot_acceptance || plot_correlation_matrix || plot_mass_distribution || timeerr_histograms) {
    bootstrapping = false;
    massfit = false;
    calculate_sweights = false;
    decaytimefit = false;
    massfittervalidation = false;
    if (timeerr_histograms) pereventresolution = true;
  }
  std::string cut = config.getString("cut");
  bool more_knots = config.getBool("more_knots");

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");
  RooRealVar        obsEtaOS("obsEta"+OS_tagger,"#eta_{OS}",0.,0.5);
  RooRealVar        obsEtaSS("obsEta"+SS_tagger,"#eta_{SS}",0.,0.5);
  RooRealVar        obsTimeErr("obsTimeErr","#sigma_{t}",0.005,0.2,"ps");
  RooCategory       obsTagOS("obsTag"+OS_tagger+"_NoZero","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  RooCategory       obsTagSS("obsTag"+SS_tagger+"_NoZero","Flavour Tag");
  obsTagSS.defineType("B0",1);
  obsTagSS.defineType("B0bar",-1);
  
  RooCategory       catYear("catYear","year of data taking");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooCategory       catTag(taggingcategory,"OS or SS tagged");
  if (OS_tagging)   catTag.defineType("OS",1);
  if (SS_tagging)   catTag.defineType("SS",-1);
  if (OS_tagging && SS_tagging)   catTag.defineType("both",10);
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);
  RooCategory       catDplusFinalState("catDplusFinalState","catDplusFinalState");
  catDplusFinalState.defineType("Kpipi",1);
  catDplusFinalState.defineType("KKpi",3);
  catDplusFinalState.defineType("KpiK",4);
  RooCategory       catDminusFinalState("catDminusFinalState","catDminusFinalState");
  catDminusFinalState.defineType("Kpipi",1);
  catDminusFinalState.defineType("KKpi",3);
  catDminusFinalState.defineType("KpiK",4);
  RooCategory       catMag("catMag","catMag");
  catMag.defineType("up",1);
  catMag.defineType("down",-1);
  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("signal",0);
  catBkg.defineType("LowMassBackground",50);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("signal",0);

  RooRealVar        BDTwPIDs_classifier("BDT_wPIDs_LowMass_Kpipi_classifier","BDT_wPIDs_LowMass_Kpipi_classifier",-1,1);
  RooRealVar        BDTwPIDs_KKpi_classifier("BDT_wPIDs_LowMass_KKpi_classifier","BDT_wPIDs_LowMass_KKpi_classifier",-1,1);
  RooRealVar        idxRunNumber("idxRunNumber","idxRunNumber",0);

  RooArgSet         observables(obsTime,obsMass,"observables");
  observables.add(RooArgSet(BDTwPIDs_classifier,BDTwPIDs_KKpi_classifier));
  observables.add(idxRunNumber);
  if (pereventresolution) observables.add(obsTimeErr);
  if (cp_fit){
    observables.add(obsEtaOS);
    observables.add(obsEtaSS);
    observables.add(obsTagOS);
    observables.add(obsTagSS);
  }
  RooArgSet         categories(catYear,catTag,catDDFinalState,catDDFinalStateParticles,catDminusFinalState,catDplusFinalState,catMag,"categories");
  categories.add(RooArgSet(catBkg,idxPV));
  RooArgSet         Gaussian_Constraints("Gaussian_Constraints");
  
  // Get data set
  RooDataSet*       data;
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  if (bootstrapping || massfit || calculate_sweights || plot_mass_distribution) data = &(tuple.ConvertToDataSet(Cut(TString(config.getString("cut")))));
  else if (!(massfittervalidation || plot_correlation_matrix || mistag_histograms || timeerr_histograms)) {
    cout << "What do you want to do? No use case is activated right now!" <<  endl;
    return 0;
  }
  if (bootstrapping || massfit || calculate_sweights || plot_mass_distribution || decaytimefit || plot_acceptance) {
    data->Print();
  }

//=========================================================================================================================================================================================================================

  // Mass PDF
  // Signal
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");
  RooRealVar        parSigMassSigma("parSigMassSigma","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  // RooGaussian       pdfSigMass("pdfSigMass","pdfSigMass",obsMass,parSigMassMean,parSigMassSigma);
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
  // RooGaussian       pdfSigBsMass("pdfSigBsMass","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma);

  // Bd --> D*+ D- with D*+ --> D+ pi0 Background
  RooRealVar        parBkgDstDLowMassMean("parBkgDstDLowMassMean","Mean Mass",5060,5050,5070,"MeV/c^{2}");
  RooRealVar        parBkgDstDLowMassSigma("parBkgDstDLowMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDLowMass("pdfBkgDstDLowMass","Lower DstD Mass PDF",obsMass,parBkgDstDLowMassMean,parBkgDstDLowMassSigma);

  RooRealVar        parBkgDstDHighMassMean("parBkgDstDHighMassMean","Mean Mass",5120,5100,5140,"MeV/c^{2}");
  RooRealVar        parBkgDstDHighMassSigma("parBkgDstDHighMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDHighMass("pdfBkgDstDHighMass","Upper DstD Mass PDF",obsMass,parBkgDstDHighMassMean,parBkgDstDHighMassSigma);

  RooRealVar        parBkgDstDMassFraction("parBkgDstDMassFraction","fraction between low and high component",0.5,0,1);
  RooAddPdf         pdfBkgDstDMass("pdfBkgDstDMass","pdfBkgDstDMass",RooArgList(pdfBkgDstDLowMass,pdfBkgDstDHighMass),parBkgDstDMassFraction);

  RooRealVar        parBkgDstDHornA("parBkgDstDHornA","parBkgDstDHornA",5000,5100);
  RooRealVar        parBkgDstDHornB("parBkgDstDHornB","parBkgDstDHornB",5100,5200);
  RooRealVar        parBkgDstDHornXi("parBkgDstDHornXi","parBkgDstDHornXi",0,1);
  RooRealVar        parBkgDstDHornShift("parBkgDstDHornShift","parBkgDstDHornShift",-10,10);
  RooRealVar        parBkgDstDHornSigma("parBkgDstDHornSigma","parBkgDstDHornSigma",10,1,20);
  RooRealVar        parBkgDstDHornSigmaFactor("parBkgDstDHornSigmaFactor","parBkgDstDHornSigmaFactor",2,1,5);
  RooRealVar        parBkgDstDHornFraction("parBkgDstDHornFraction","parBkgDstDHornFraction",0.5,0,1);
  // RooHORNSdini      pdfBkgDstDMass("pdfBkgDstDMass","pdfBkgDstDMass",obsMass,parBkgDstDHornA,parBkgDstDHornB,parBkgDstDHornXi,parBkgDstDHornShift,parBkgDstDHornSigma,parBkgDstDHornSigmaFactor,parBkgDstDHornFraction);

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

  // Build Chebychev polynomial p.d.f.
  RooRealVar        a0_Kpipi("a0_Kpipi","a0_Kpipi",-0.7,-1.,1.);
  RooRealVar        a1_Kpipi("a1_Kpipi","a1_Kpipi",0.03,-1.,1.);
  RooRealVar        a2_Kpipi("a2_Kpipi","a2_Kpipi",-0.07,-1.,1.);
  // RooChebychev      pdfBkgMass_Kpipi("pdfBkgMass_Kpipi","Background",obsMass,RooArgSet(a0_Kpipi,a1_Kpipi,a2_Kpipi));
  RooRealVar        a0_KKpi("a0_KKpi","a0_KKpi",-0.5,-1.,1.);
  RooRealVar        a1_KKpi("a1_KKpi","a1_KKpi",0.18,-1.,1.);
  RooRealVar        a2_KKpi("a2_KKpi","a2_KKpi",-0.04,-1.,1.);
  // RooChebychev      pdfBkgMass_KKpi("pdfBkgMass_KKpi","Background",obsMass,RooArgSet(a0_KKpi,a1_KKpi,a2_KKpi));

  RooRealVar        parSigYield_11_Kpipi("parSigYield_11_Kpipi","N_{B^{0}_{d}}^{11,K#pi#pi}",500,0,1000);
  RooRealVar        parSigYield_12_Kpipi("parSigYield_12_Kpipi","N_{B^{0}_{d}}^{12,K#pi#pi}",500,0,1000);
  RooRealVar        parSigYield_11_KKpi("parSigYield_11_KKpi","N_{B^{0}_{d}}^{11,KK#pi}",500,0,1000);
  RooRealVar        parSigYield_12_KKpi("parSigYield_12_KKpi","N_{B^{0}_{d}}^{12,KK#pi}",500,0,1000);
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
  RooRealVar        parBkgBsDsDYield_11_Kpipi("parBkgBsDsDYield_11_Kpipi","parBkgBsDsDYield_11_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12_Kpipi("parBkgBsDsDYield_12_Kpipi","parBkgBsDsDYield_12_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11_KKpi("parBkgBsDsDYield_11_KKpi","parBkgBsDsDYield_11_KKpi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12_KKpi("parBkgBsDsDYield_12_KKpi","parBkgBsDsDYield_12_KKpi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_Kpipi("parBkgBsDsDYield_Kpipi","parBkgBsDsDYield_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_KKpi("parBkgBsDsDYield_KKpi","parBkgBsDsDYield_KKpi",150,0,2000);
  RooRealVar        parBkgBsDsDYield_11("parBkgBsDsDYield_11","parBkgBsDsDYield_11",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12("parBkgBsDsDYield_12","parBkgBsDsDYield_12",1000,0,2000);
  RooRealVar        parBkgBsDsDYield("parBkgBsDsDYield","parBkgBsDsDYield",1000,0,2000);
  RooRealVar        parSigBsYield_11_Kpipi("parSigBsYield_11_Kpipi","parSigBsYield_11_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_12_Kpipi("parSigBsYield_12_Kpipi","parSigBsYield_12_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_11_KKpi("parSigBsYield_11_KKpi","parSigBsYield_11_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_12_KKpi("parSigBsYield_12_KKpi","parSigBsYield_12_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_Kpipi("parSigBsYield_Kpipi","parSigBsYield_Kpipi",300,0,1000);
  RooRealVar        parSigBsYield_KKpi("parSigBsYield_KKpi","parSigBsYield_KKpi",50,0,1000);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgDstDYield_11_Kpipi("parBkgDstDYield_11_Kpipi","parBkgDstDYield_11_Kpipi",5000,0,10000);
  RooRealVar        parBkgDstDYield_12_Kpipi("parBkgDstDYield_12_Kpipi","parBkgDstDYield_12_Kpipi",5000,0,10000);
  RooRealVar        parBkgDstDYield_11_KKpi("parBkgDstDYield_11_KKpi","parBkgDstDYield_11_KKpi",5000,0,10000);
  RooRealVar        parBkgDstDYield_12_KKpi("parBkgDstDYield_12_KKpi","parBkgDstDYield_12_KKpi",5000,0,10000);
  RooRealVar        parBkgDstDYield_Kpipi("parBkgDstDYield_Kpipi","parBkgDstDYield_Kpipi",1800,0,10000);
  RooRealVar        parBkgDstDYield_KKpi("parBkgDstDYield_KKpi","parBkgDstDYield_KKpi",700,0,10000);
  RooRealVar        parBkgDstDYield_11("parBkgDstDYield_11","parBkgDstDYield_11",5000,0,10000);
  RooRealVar        parBkgDstDYield_12("parBkgDstDYield_12","parBkgDstDYield_12",5000,0,10000);
  RooRealVar        parBkgDstDYield("parBkgDstDYield","parBkgDstDYield",5000,0,10000);
  RooRealVar        parBkgBsDstDYield_11_Kpipi("parBkgBsDstDYield_11_Kpipi","parBkgBsDstDYield_11_Kpipi",5000,0,10000);
  RooRealVar        parBkgBsDstDYield_12_Kpipi("parBkgBsDstDYield_12_Kpipi","parBkgBsDstDYield_12_Kpipi",5000,0,10000);
  RooRealVar        parBkgBsDstDYield_11_KKpi("parBkgBsDstDYield_11_KKpi","parBkgBsDstDYield_11_KKpi",5000,0,10000);
  RooRealVar        parBkgBsDstDYield_12_KKpi("parBkgBsDstDYield_12_KKpi","parBkgBsDstDYield_12_KKpi",5000,0,10000);
  RooRealVar        parBkgBsDstDYield_Kpipi("parBkgBsDstDYield_Kpipi","parBkgBsDstDYield_Kpipi",1800,0,10000);
  RooRealVar        parBkgBsDstDYield_KKpi("parBkgBsDstDYield_KKpi","parBkgBsDstDYield_KKpi",700,0,10000);
  RooRealVar        parBkgBsDstDYield_11("parBkgBsDstDYield_11","parBkgBsDstDYield_11",5000,0,10000);
  RooRealVar        parBkgBsDstDYield_12("parBkgBsDstDYield_12","parBkgBsDstDYield_12",5000,0,10000);
  RooRealVar        parBkgBsDstDYield("parBkgBsDstDYield","parBkgBsDstDYield",5000,0,10000);
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
  RooExtendPdf      pdfBkgBsDsDExtend_11_Kpipi("pdfBkgBsDsDExtend_11_Kpipi","pdfBkgBsDsDExtend_11_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_11_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_12_Kpipi("pdfBkgBsDsDExtend_12_Kpipi","pdfBkgBsDsDExtend_12_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_12_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_11_KKpi("pdfBkgBsDsDExtend_11_KKpi","pdfBkgBsDsDExtend_11_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_11_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_12_KKpi("pdfBkgBsDsDExtend_12_KKpi","pdfBkgBsDsDExtend_12_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_12_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_Kpipi("pdfBkgBsDsDExtend_Kpipi","pdfBkgBsDsDExtend_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_KKpi("pdfBkgBsDsDExtend_KKpi","pdfBkgBsDsDExtend_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_11("pdfBkgBsDsDExtend_11","pdfBkgBsDsDExtend_11",pdfBkgBsDsDMass,parBkgBsDsDYield_11);
  RooExtendPdf      pdfBkgBsDsDExtend_12("pdfBkgBsDsDExtend_12","pdfBkgBsDsDExtend_12",pdfBkgBsDsDMass,parBkgBsDsDYield_12);
  RooExtendPdf      pdfBkgBsDsDExtend("pdfBkgBsDsDExtend","pdfBkgBsDsDExtend",pdfBkgBsDsDMass,parBkgBsDsDYield);
  RooExtendPdf      pdfSigBsExtend_11_Kpipi("pdfSigBsExtend_11_Kpipi","pdfSigBsExtend_11_Kpipi",pdfSigBsMass,parSigBsYield_11_Kpipi);
  RooExtendPdf      pdfSigBsExtend_12_Kpipi("pdfSigBsExtend_12_Kpipi","pdfSigBsExtend_12_Kpipi",pdfSigBsMass,parSigBsYield_12_Kpipi);
  RooExtendPdf      pdfSigBsExtend_11_KKpi("pdfSigBsExtend_11_KKpi","pdfSigBsExtend_11_KKpi",pdfSigBsMass,parSigBsYield_11_KKpi);
  RooExtendPdf      pdfSigBsExtend_12_KKpi("pdfSigBsExtend_12_KKpi","pdfSigBsExtend_12_KKpi",pdfSigBsMass,parSigBsYield_12_KKpi);
  RooExtendPdf      pdfSigBsExtend_Kpipi("pdfSigBsExtend_Kpipi","pdfSigBsExtend_Kpipi",pdfSigBsMass,parSigBsYield_Kpipi);
  RooExtendPdf      pdfSigBsExtend_KKpi("pdfSigBsExtend_KKpi","pdfSigBsExtend_KKpi",pdfSigBsMass,parSigBsYield_KKpi);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgDstDExtend_11_Kpipi("pdfBkgDstDExtend_11_Kpipi","pdfBkgDstDExtend_11_Kpipi",pdfBkgDstDMass,parBkgDstDYield_11_Kpipi);
  RooExtendPdf      pdfBkgDstDExtend_12_Kpipi("pdfBkgDstDExtend_12_Kpipi","pdfBkgDstDExtend_12_Kpipi",pdfBkgDstDMass,parBkgDstDYield_12_Kpipi);
  RooExtendPdf      pdfBkgDstDExtend_11_KKpi("pdfBkgDstDExtend_11_KKpi","pdfBkgDstDExtend_11_KKpi",pdfBkgDstDMass,parBkgDstDYield_11_KKpi);
  RooExtendPdf      pdfBkgDstDExtend_12_KKpi("pdfBkgDstDExtend_12_KKpi","pdfBkgDstDExtend_12_KKpi",pdfBkgDstDMass,parBkgDstDYield_12_KKpi);
  RooExtendPdf      pdfBkgDstDExtend_Kpipi("pdfBkgDstDExtend_Kpipi","pdfBkgDstDExtend_Kpipi",pdfBkgDstDMass,parBkgDstDYield_Kpipi);
  RooExtendPdf      pdfBkgDstDExtend_KKpi("pdfBkgDstDExtend_KKpi","pdfBkgDstDExtend_KKpi",pdfBkgDstDMass,parBkgDstDYield_KKpi);
  RooExtendPdf      pdfBkgDstDExtend_11("pdfBkgDstDExtend_11","pdfBkgDstDExtend_11",pdfBkgDstDMass,parBkgDstDYield_11);
  RooExtendPdf      pdfBkgDstDExtend_12("pdfBkgDstDExtend_12","pdfBkgDstDExtend_12",pdfBkgDstDMass,parBkgDstDYield_12);
  RooExtendPdf      pdfBkgDstDExtend("pdfBkgDstDExtend","pdfBkgDstDExtend",pdfBkgDstDMass,parBkgDstDYield);
  // RooExtendPdf      pdfBkgBsDstDExtend_11_Kpipi("pdfBkgBsDstDExtend_11_Kpipi","pdfBkgBsDstDExtend_11_Kpipi",pdfBkgBsDstDMass,parBkgBsDstDYield_11_Kpipi);
  // RooExtendPdf      pdfBkgBsDstDExtend_12_Kpipi("pdfBkgBsDstDExtend_12_Kpipi","pdfBkgBsDstDExtend_12_Kpipi",pdfBkgBsDstDMass,parBkgBsDstDYield_12_Kpipi);
  // RooExtendPdf      pdfBkgBsDstDExtend_11_KKpi("pdfBkgBsDstDExtend_11_KKpi","pdfBkgBsDstDExtend_11_KKpi",pdfBkgBsDstDMass,parBkgBsDstDYield_11_KKpi);
  // RooExtendPdf      pdfBkgBsDstDExtend_12_KKpi("pdfBkgBsDstDExtend_12_KKpi","pdfBkgBsDstDExtend_12_KKpi",pdfBkgBsDstDMass,parBkgBsDstDYield_12_KKpi);
  // RooExtendPdf      pdfBkgBsDstDExtend_Kpipi("pdfBkgBsDstDExtend_Kpipi","pdfBkgBsDstDExtend_Kpipi",pdfBkgBsDstDMass,parBkgBsDstDYield_Kpipi);
  // RooExtendPdf      pdfBkgBsDstDExtend_KKpi("pdfBkgBsDstDExtend_KKpi","pdfBkgBsDstDExtend_KKpi",pdfBkgBsDstDMass,parBkgBsDstDYield_KKpi);
  // RooExtendPdf      pdfBkgBsDstDExtend_11("pdfBkgBsDstDExtend_11","pdfBkgBsDstDExtend_11",pdfBkgBsDstDMass,parBkgBsDstDYield_11);
  // RooExtendPdf      pdfBkgBsDstDExtend_12("pdfBkgBsDstDExtend_12","pdfBkgBsDstDExtend_12",pdfBkgBsDstDMass,parBkgBsDstDYield_12);
  // RooExtendPdf      pdfBkgBsDstDExtend("pdfBkgBsDstDExtend","pdfBkgBsDstDExtend",pdfBkgBsDstDMass,parBkgBsDstDYield);
  RooExtendPdf      pdfBkgExtend_11_Kpipi("pdfBkgExtend_11_Kpipi","pdfBkgExtend_11_Kpipi",pdfBkgMass_Kpipi,parBkgYield_11_Kpipi);
  RooExtendPdf      pdfBkgExtend_12_Kpipi("pdfBkgExtend_12_Kpipi","pdfBkgExtend_12_Kpipi",pdfBkgMass_Kpipi,parBkgYield_12_Kpipi);
  RooExtendPdf      pdfBkgExtend_11_KKpi("pdfBkgExtend_11_KKpi","pdfBkgExtend_11_KKpi",pdfBkgMass_KKpi,parBkgYield_11_KKpi);
  RooExtendPdf      pdfBkgExtend_12_KKpi("pdfBkgExtend_12_KKpi","pdfBkgExtend_12_KKpi",pdfBkgMass_KKpi,parBkgYield_12_KKpi);
  RooExtendPdf      pdfBkgExtend_Kpipi("pdfBkgExtend_Kpipi","pdfBkgExtend_Kpipi",pdfBkgMass_Kpipi,parBkgYield_Kpipi);
  RooExtendPdf      pdfBkgExtend_KKpi("pdfBkgExtend_KKpi","pdfBkgExtend_KKpi",pdfBkgMass_KKpi,parBkgYield_KKpi);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass_11_Kpipi("pdfMass_11_Kpipi","Mass PDF",RooArgList(pdfSigExtend_11_Kpipi,pdfBkgDsDExtend_11_Kpipi,pdfSigBsExtend_11_Kpipi,pdfBkgExtend_11_Kpipi,/*pdfBkgDstDExtend_11_Kpipi,*/pdfBkgBsDsDExtend_11_Kpipi/*,pdfBkgBsDstDExtend_11_Kpipi*/));
  RooAddPdf         pdfMass_12_Kpipi("pdfMass_12_Kpipi","Mass PDF",RooArgList(pdfSigExtend_12_Kpipi,pdfBkgDsDExtend_12_Kpipi,pdfSigBsExtend_12_Kpipi,pdfBkgExtend_12_Kpipi,/*pdfBkgDstDExtend_12_Kpipi,*/pdfBkgBsDsDExtend_12_Kpipi/*,pdfBkgBsDstDExtend_12_Kpipi*/));
  RooAddPdf         pdfMass_11_KKpi("pdfMass_11_KKpi","Mass PDF",RooArgList(pdfSigExtend_11_KKpi,pdfBkgDsDExtend_11_KKpi,pdfSigBsExtend_11_KKpi,pdfBkgExtend_11_KKpi,/*pdfBkgDstDExtend_11_KKpi,*/pdfBkgBsDsDExtend_11_KKpi/*,pdfBkgBsDstDExtend_11_KKpi*/));
  RooAddPdf         pdfMass_12_KKpi("pdfMass_12_KKpi","Mass PDF",RooArgList(pdfSigExtend_12_KKpi,pdfBkgDsDExtend_12_KKpi,pdfSigBsExtend_12_KKpi,pdfBkgExtend_12_KKpi,/*pdfBkgDstDExtend_12_KKpi,*/pdfBkgBsDsDExtend_12_KKpi/*,pdfBkgBsDstDExtend_12_KKpi*/));
  RooAddPdf         pdfMass_Kpipi("pdfMass_Kpipi","Mass PDF",RooArgList(pdfSigExtend_Kpipi,pdfBkgDsDExtend_Kpipi,pdfSigBsExtend_Kpipi,pdfBkgExtend_Kpipi,/*pdfBkgDstDExtend_Kpipi,*/pdfBkgBsDsDExtend_Kpipi/*,pdfBkgBsDstDExtend_Kpipi*/));
  RooAddPdf         pdfMass_KKpi("pdfMass_KKpi","Mass PDF",RooArgList(pdfSigExtend_KKpi,pdfBkgDsDExtend_KKpi,pdfSigBsExtend_KKpi,pdfBkgExtend_KKpi,/*pdfBkgDstDExtend_KKpi,*/pdfBkgBsDsDExtend_KKpi/*,pdfBkgBsDstDExtend_KKpi*/));
  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11,/*pdfBkgDstDExtend_11,*/pdfBkgBsDsDExtend_11/*,pdfBkgBsDstDExtend_11*/));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12,/*pdfBkgDstDExtend_12,*/pdfBkgBsDsDExtend_12/*,pdfBkgBsDstDExtend_12*/));

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
  else  pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend,/*pdfBkgDstDExtend,*/pdfBkgBsDsDExtend/*,pdfBkgBsDstDExtend*/));

//=========================================================================================================================================================================================================================

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

  // Asymmetries
  RooRealVar          parSigEtaDeltaProd_11("parSigEtaDeltaProd_11","A_{P}^{11}",-0.0066,-0.05,0.02);
  RooRealVar          parSigEtaDeltaProdMean_11("parSigEtaDeltaProdMean_11","#bar{#mu}",-0.0066);
  RooRealVar          parSigEtaDeltaProdSigma_11("parSigEtaDeltaProdSigma_11","#sigma_{#bar{mu}}",0.0026);

  RooRealVar          parSigEtaDeltaProdOffset("parSigEtaDeltaProdOffset","#Delta A_{P}",0.0004,-0.01,0.01);
  RooRealVar          parSigEtaDeltaProdOffsetMean("parSigEtaDeltaProdOffsetMean","#bar{#mu}",0.0004);
  RooRealVar          parSigEtaDeltaProdOffsetSigma("parSigEtaDeltaProdOffsetSigma","#sigma_{#bar{mu}}",0.0018);
  RooAddition         parSigEtaDeltaProd_12("parSigEtaDeltaProd_12","B0/B0bar production asymmetry 2012",RooArgList(parSigEtaDeltaProd_11,parSigEtaDeltaProdOffset));

  // OS tags
  RooRealVar          parSigEtaDeltaP0_OS("parSigEtaDeltaP0_OS","#Delta p_{0}^{OS}",0.0140,0.,0.03);
  RooRealVar          parSigEtaDeltaP0Mean_OS("parSigEtaDeltaP0Mean_OS","#bar{#delta p_{0}}",0.0148);
  RooRealVar          parSigEtaDeltaP0Sigma_OS("parSigEtaDeltaP0Sigma_OS","#sigma_{#bar{#delta p_{0}}}",0.0012);
  if (OS_tagging) Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_OS);

  RooRealVar          parSigEtaDeltaP1_OS("parSigEtaDeltaP1_OS","#Delta p_{1}^{OS}",0.066,0.,0.1);
  RooRealVar          parSigEtaDeltaP1Mean_OS("parSigEtaDeltaP1Mean_OS","#bar{#delta p_{1}}",0.070);
  RooRealVar          parSigEtaDeltaP1Sigma_OS("parSigEtaDeltaP1Sigma_OS","#sigma_{#bar{#delta p_{1}}}",0.012);
  if (OS_tagging) Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_OS);

  // SS tags
  RooRealVar          parSigEtaDeltaP0_SS("parSigEtaDeltaP0_SS","#Delta p_{0}^{SS}",-0.003,-0.02,0.02);
  RooRealVar          parSigEtaDeltaP0Mean_SS("parSigEtaDeltaP0Mean_SS","#bar{#delta p_{0}}",-0.0026);
  RooRealVar          parSigEtaDeltaP0Sigma_SS("parSigEtaDeltaP0Sigma_SS","#sigma_{#bar{#delta p_{0}}}",0.0044);
  if (SS_tagging) Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_SS);

  RooRealVar          parSigEtaDeltaP1_SS("parSigEtaDeltaP1_SS","#Delta p_{1}^{SS}",-0.18,-0.7,0.3);
  RooRealVar          parSigEtaDeltaP1Mean_SS("parSigEtaDeltaP1Mean_SS","#bar{#delta p_{1}}",-0.18);
  RooRealVar          parSigEtaDeltaP1Sigma_SS("parSigEtaDeltaP1Sigma_SS","#sigma_{#bar{#delta p_{1}}}",0.10);
  if (SS_tagging) Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_SS);

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
  if(more_knots) knots += 0.4;
  if(more_knots) knots += 0.6;
  knots += 0.8;
  if(more_knots) knots += 1.0;
  if(more_knots) knots += 1.5;
  knots += 2.0;
  if(more_knots) knots += 5.0;

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

  RooArgList        listofsplinecoefficients_Kpipi("listofsplinecoefficients_Kpipi");
  RooRealVar*       parSigTimeAccCSpline_Kpipi;
  for (int i = 1; i <= (knots.size()+2) ; i++) {
    std::string binname = "parSigTimeAccCSpline_Kpipi" + boost::lexical_cast<std::string>(i);
    std::string bintitle = "h_{" + boost::lexical_cast<std::string>(i) + "}";
    parSigTimeAccCSpline_Kpipi = new RooRealVar(binname.c_str(),bintitle.c_str(),1,0,2);
    listofsplinecoefficients_Kpipi.add(*parSigTimeAccCSpline_Kpipi);
  }

  RooCubicSplineFun       accspline_Kpipi("accspline_Kpipi","Spline Acceptance",obsTime,knots,listofsplinecoefficients_Kpipi);
  RooResolutionModel*     efficiencymodel_Kpipi;
  RooGaussEfficiencyModel efficiencymodel1_Kpipi("efficiencymodel1_Kpipi","Gaussefficiencymodel 1",obsTime,accspline_Kpipi,parResMean,parResSigmaCorrection1);
  RooGaussEfficiencyModel efficiencymodel2_Kpipi("efficiencymodel2_Kpipi","Gaussefficiencymodel 2",obsTime,accspline_Kpipi,parResMean,parResSigmaCorrection2);
  RooGaussEfficiencyModel efficiencymodel3_Kpipi("efficiencymodel3_Kpipi","Gaussefficiencymodel 3",obsTime,accspline_Kpipi,parResMean,parResSigma_wrongPV);
  if (!pereventresolution) efficiencymodel_Kpipi = new RooGaussEfficiencyModel("efficiencymodel_Kpipi","Gaussefficiencymodel",obsTime,accspline_Kpipi,parResMean,RooConst(0.05));
  else efficiencymodel_Kpipi = new RooEffResAddModel("efficiencymodel_Kpipi","Per event resolution efficiency model",RooArgList(efficiencymodel3_Kpipi,efficiencymodel2_Kpipi,efficiencymodel1_Kpipi),RooArgList(parResFraction_wrongPV,parResFraction2));

  RooArgList        listofsplinecoefficients_KKpi("listofsplinecoefficients_KKpi");
  RooRealVar*       parSigTimeAccCSpline_KKpi;
  for (int i = 1; i <= (knots.size()+2) ; i++) {
    std::string binname = "parSigTimeAccCSpline_KKpi" + boost::lexical_cast<std::string>(i);
    std::string bintitle = "h_{" + boost::lexical_cast<std::string>(i) + "}";
    parSigTimeAccCSpline_KKpi = new RooRealVar(binname.c_str(),bintitle.c_str(),1,0,2);
    listofsplinecoefficients_KKpi.add(*parSigTimeAccCSpline_KKpi);
  }

  RooCubicSplineFun       accspline_KKpi("accspline_KKpi","Spline Acceptance",obsTime,knots,listofsplinecoefficients_KKpi);
  RooResolutionModel*     efficiencymodel_KKpi;
  RooGaussEfficiencyModel efficiencymodel1_KKpi("efficiencymodel1_KKpi","Gaussefficiencymodel 1",obsTime,accspline_KKpi,parResMean,parResSigmaCorrection1);
  RooGaussEfficiencyModel efficiencymodel2_KKpi("efficiencymodel2_KKpi","Gaussefficiencymodel 2",obsTime,accspline_KKpi,parResMean,parResSigmaCorrection2);
  RooGaussEfficiencyModel efficiencymodel3_KKpi("efficiencymodel3_KKpi","Gaussefficiencymodel 3",obsTime,accspline_KKpi,parResMean,parResSigma_wrongPV);
  if (!pereventresolution) efficiencymodel_KKpi = new RooGaussEfficiencyModel("efficiencymodel_KKpi","Gaussefficiencymodel",obsTime,accspline_KKpi,parResMean,RooConst(0.05));
  else efficiencymodel_KKpi = new RooEffResAddModel("efficiencymodel_KKpi","Per event resolution efficiency model",RooArgList(efficiencymodel3_KKpi,efficiencymodel2_KKpi,efficiencymodel1_KKpi),RooArgList(parResFraction_wrongPV,parResFraction2));

//=========================================================================================================================================================================================================================

  // Tagging calibration
  RooRealVar          parSigEtaP0_OS("parSigEtaP0_OS","p_{0}^{OS}",0.3815,0.0,0.1);
  RooRealVar          parSigEtaP0Mean_OS("parSigEtaP0Mean_OS","#bar{p}_{0}",0.3815);
  RooRealVar          parSigEtaP0Sigma_OS("parSigEtaP0Sigma_OS","#sigma_{#bar{p}_{0}}",0.0019);
  if (OS_tagging) Gaussian_Constraints.add(parSigEtaP0Sigma_OS);

  RooRealVar          parSigEtaP1_OS("parSigEtaP1_OS","p_{1}^{OS}",0.978,0.9,1.1);
  RooRealVar          parSigEtaP1Mean_OS("parSigEtaP1Mean_OS","#bar{p}_{1}",0.978);
  RooRealVar          parSigEtaP1Sigma_OS("parSigEtaP1Sigma_OS","#sigma_{#bar{p}_{1}}",0.007);
  if (OS_tagging) Gaussian_Constraints.add(parSigEtaP1Sigma_OS);
  
  RooRealVar          parSigEtaP0P1CorrelationCoeff_OS("parSigEtaP0P1CorrelationCoeff_OS","correlation coefficient between p0 and p1 OS",0.15);
  RooRealVar          parSigEtaP0DeltaP0CorrelationCoeff_OS("parSigEtaP0DeltaP0CorrelationCoeff_OS","correlation coefficient between p0 and Delta p0 OS",-0.013);
  RooRealVar          parSigEtaP0DeltaP1CorrelationCoeff_OS("parSigEtaP0DeltaP1CorrelationCoeff_OS","correlation coefficient between p0 and Delta p1 OS",0.008);
  RooRealVar          parSigEtaP1DeltaP0CorrelationCoeff_OS("parSigEtaP1DeltaP0CorrelationCoeff_OS","correlation coefficient between p1 and Delta p0 OS",0.007);
  RooRealVar          parSigEtaP1DeltaP1CorrelationCoeff_OS("parSigEtaP1DeltaP1CorrelationCoeff_OS","correlation coefficient between p1 and Delta p1 OS",-0.024);
  RooRealVar          parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS("parSigEtaDeltaP0DeltaP1CorrelationCoeff_OS","correlation coefficient between Delta p0 and Delta p1 OS",0.086);

  RooRealVar          parSigEtaMean_OS("parSigEtaMean_OS","Mean on per-event mistag",0.3786);

  RooRealVar          parSigEtaP0_SS("parSigEtaP0_SS","p_{0}^{SS}",0.4228,0.3,0.5);
  RooRealVar          parSigEtaP0Mean_SS("parSigEtaP0Mean_SS","#bar{p}_{0}",0.4232);
  RooRealVar          parSigEtaP0Sigma_SS("parSigEtaP0Sigma_SS","#sigma_{#bar{p}_{0}}",0.0029);
  if (SS_tagging) Gaussian_Constraints.add(parSigEtaP0Sigma_SS);

  RooRealVar          parSigEtaP1_SS("parSigEtaP1_SS","p_{1}^{SS}",1.01,0.7,1.1);
  RooRealVar          parSigEtaP1Mean_SS("parSigEtaP1Mean_SS","#bar{p}_{1}",1.011);
  RooRealVar          parSigEtaP1Sigma_SS("parSigEtaP1Sigma_SS","#sigma_{#bar{p}_{1}}",0.064);
  if (SS_tagging) Gaussian_Constraints.add(parSigEtaP1Sigma_SS);

  RooRealVar          parSigEtaP0P1CorrelationCoeff_SS("parSigEtaP0P1CorrelationCoeff_SS","correlation coefficient between p0 and p1 SS",0.052);
  RooRealVar          parSigEtaP0DeltaP0CorrelationCoeff_SS("parSigEtaP0DeltaP0CorrelationCoeff_SS","correlation coefficient between p0 and Delta p0 SS",0.025);
  RooRealVar          parSigEtaP0DeltaP1CorrelationCoeff_SS("parSigEtaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between p0 and Delta p1 SS",-0.007);
  RooRealVar          parSigEtaP1DeltaP0CorrelationCoeff_SS("parSigEtaP1DeltaP0CorrelationCoeff_SS","correlation coefficient between p1 and Delta p0 SS",-0.006);
  RooRealVar          parSigEtaP1DeltaP1CorrelationCoeff_SS("parSigEtaP1DeltaP1CorrelationCoeff_SS","correlation coefficient between p1 and Delta p1 SS",0.022);
  RooRealVar          parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS("parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between Delta p0 and Delta p1 SS",0.02);

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

//=========================================================================================================================================================================================================================

  // Decay Time PDF

  RooAbsPdf*        pdfSigTime_11_OS_Kpipi;
  RooAbsPdf*        pdfSigTime_11_SS_Kpipi;
  RooAbsPdf*        pdfSigTime_12_OS_Kpipi;
  RooAbsPdf*        pdfSigTime_12_SS_Kpipi;
  RooAbsPdf*        pdfSigTime_11_BS_Kpipi;
  RooAbsPdf*        pdfSigTime_12_BS_Kpipi;
  RooAbsPdf*        pdfSigTime_11_OS_KKpi;
  RooAbsPdf*        pdfSigTime_11_SS_KKpi;
  RooAbsPdf*        pdfSigTime_12_OS_KKpi;
  RooAbsPdf*        pdfSigTime_12_SS_KKpi;
  RooAbsPdf*        pdfSigTime_11_BS_KKpi;
  RooAbsPdf*        pdfSigTime_12_BS_KKpi;

  if (cp_fit){
    pdfSigTime_11_OS_Kpipi = new RooBDecay("pdfSigTime_11_OS_Kpipi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_OS,parSigTimeSinh,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel_Kpipi,RooBDecay::SingleSided);
    pdfSigTime_11_SS_Kpipi = new RooBDecay("pdfSigTime_11_SS_Kpipi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_SS,parSigTimeSinh,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel_Kpipi,RooBDecay::SingleSided);
    pdfSigTime_12_OS_Kpipi = new RooBDecay("pdfSigTime_12_OS_Kpipi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_OS,parSigTimeSinh,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel_Kpipi,RooBDecay::SingleSided);
    pdfSigTime_12_SS_Kpipi = new RooBDecay("pdfSigTime_12_SS_Kpipi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_SS,parSigTimeSinh,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel_Kpipi,RooBDecay::SingleSided);
    pdfSigTime_11_BS_Kpipi = new RooBDecay("pdfSigTime_11_BS_Kpipi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_BS,parSigTimeSinh,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel_Kpipi,RooBDecay::SingleSided);
    pdfSigTime_12_BS_Kpipi = new RooBDecay("pdfSigTime_12_BS_Kpipi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_BS,parSigTimeSinh,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel_Kpipi,RooBDecay::SingleSided);
    pdfSigTime_11_OS_KKpi  = new RooBDecay("pdfSigTime_11_OS_KKpi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_OS,parSigTimeSinh,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel_KKpi,RooBDecay::SingleSided);
    pdfSigTime_11_SS_KKpi  = new RooBDecay("pdfSigTime_11_SS_KKpi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_SS,parSigTimeSinh,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel_KKpi,RooBDecay::SingleSided);
    pdfSigTime_12_OS_KKpi  = new RooBDecay("pdfSigTime_12_OS_KKpi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_OS,parSigTimeSinh,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel_KKpi,RooBDecay::SingleSided);
    pdfSigTime_12_SS_KKpi  = new RooBDecay("pdfSigTime_12_SS_KKpi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_SS,parSigTimeSinh,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel_KKpi,RooBDecay::SingleSided);
    pdfSigTime_11_BS_KKpi  = new RooBDecay("pdfSigTime_11_BS_KKpi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_BS,parSigTimeSinh,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel_KKpi,RooBDecay::SingleSided);
    pdfSigTime_12_BS_KKpi  = new RooBDecay("pdfSigTime_12_BS_KKpi","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_BS,parSigTimeSinh,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel_KKpi,RooBDecay::SingleSided);
  }
  else {
    pdfSigTime_11_OS_Kpipi = new RooDecay("pdfSigTime_11_OS_Kpipi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_Kpipi,RooDecay::SingleSided);
    pdfSigTime_11_SS_Kpipi = new RooDecay("pdfSigTime_11_SS_Kpipi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_Kpipi,RooDecay::SingleSided);
    pdfSigTime_12_OS_Kpipi = new RooDecay("pdfSigTime_12_OS_Kpipi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_Kpipi,RooDecay::SingleSided);
    pdfSigTime_12_SS_Kpipi = new RooDecay("pdfSigTime_12_SS_Kpipi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_Kpipi,RooDecay::SingleSided);
    pdfSigTime_11_BS_Kpipi = new RooDecay("pdfSigTime_11_BS_Kpipi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_Kpipi,RooDecay::SingleSided);
    pdfSigTime_12_BS_Kpipi = new RooDecay("pdfSigTime_12_BS_Kpipi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_Kpipi,RooDecay::SingleSided);
    pdfSigTime_11_OS_KKpi  = new RooDecay("pdfSigTime_11_OS_KKpi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_KKpi,RooDecay::SingleSided);
    pdfSigTime_11_SS_KKpi  = new RooDecay("pdfSigTime_11_SS_KKpi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_KKpi,RooDecay::SingleSided);
    pdfSigTime_12_OS_KKpi  = new RooDecay("pdfSigTime_12_OS_KKpi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_KKpi,RooDecay::SingleSided);
    pdfSigTime_12_SS_KKpi  = new RooDecay("pdfSigTime_12_SS_KKpi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_KKpi,RooDecay::SingleSided);
    pdfSigTime_11_BS_KKpi  = new RooDecay("pdfSigTime_11_BS_KKpi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_KKpi,RooDecay::SingleSided);
    pdfSigTime_12_BS_KKpi  = new RooDecay("pdfSigTime_12_BS_KKpi","P_{S}^{l}(t|#sigma_{t})",obsTime,parSigTimeTau,*efficiencymodel_KKpi,RooDecay::SingleSided);
  }

//========================================================================================================================================================================================================================

  // Build Simultaneous PDF
  RooSuperCategory  supercategory_time("supercategory_time","supercategory_time",RooArgSet(catYear,catTag));
  RooSuperCategory  supercategory_splitacceptance("supercategory_splitacceptance","supercategory_splitacceptance",RooArgSet(catYear,catTag,catDDFinalStateParticles));
  RooSimultaneous*  pdf;

  if (split_acceptance) {
    pdf = new RooSimultaneous("pdf","P",supercategory_splitacceptance);
    if(OS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_OS_Kpipi,"{2011;OS;Kpipi}");
    if(SS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_SS_Kpipi,"{2011;SS;Kpipi}");
    if(OS_tagging && SS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_BS_Kpipi,"{2011;both;Kpipi}");
    if(OS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_OS_Kpipi,"{2012;OS;Kpipi}");
    if(SS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_SS_Kpipi,"{2012;SS;Kpipi}");
    if(OS_tagging && SS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_BS_Kpipi,"{2012;both;Kpipi}");
    if(OS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_OS_KKpi,"{2011;OS;KKpi}");
    if(SS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_SS_KKpi,"{2011;SS;KKpi}");
    if(OS_tagging && SS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_BS_KKpi,"{2011;both;KKpi}");
    if(OS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_OS_KKpi,"{2012;OS;KKpi}");
    if(SS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_SS_KKpi,"{2012;SS;KKpi}");
    if(OS_tagging && SS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_BS_KKpi,"{2012;both;KKpi}");
  }
  else {
    pdf = new RooSimultaneous("pdf","P",supercategory_time);
    if(OS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_OS,"{2011;OS}");
    if(SS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_SS,"{2011;SS}");
    if(OS_tagging && SS_tagging && data->sumEntries("catYear==2011") > 0) pdf->addPdf(*pdfSigTime_11_BS,"{2011;both}");
    if(OS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_OS,"{2012;OS}");
    if(SS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_SS,"{2012;SS}");
    if(OS_tagging && SS_tagging && data->sumEntries("catYear==2012") > 0) pdf->addPdf(*pdfSigTime_12_BS,"{2012;both}");
  }

  cout  <<  "simultaneous PDF built"  <<  endl;

  // Get Starting Values
  pdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
  pdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
  pdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Acceptance_Splines.txt");
  Gaussian_Constraints.readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");

  pdf->Print();

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
  if (cp_fit) {
    constrainingPdfs.add(conpdfSigTimeDeltaM);
    constrainingPdfs.add(conpdfSigEtaDeltaProd_11);
    if (data->sumEntries("catYear==2012") > 0)  constrainingPdfs.add(conpdfSigEtaDeltaProd_12);
    if (OS_tagging) {
      // constrainingPdfs.add(conpdfSigEtaP0_OS);
      // constrainingPdfs.add(conpdfSigEtaP1_OS);
      // constrainingPdfs.add(conpdfSigEtaDeltaP0_OS);
      // constrainingPdfs.add(conpdfSigEtaDeltaP1_OS);
      constrainingPdfs.add(conpdfSigEta_OS);
    }
    if (SS_tagging)  constrainingPdfs.add(conpdfSigEta_SS);
  }
  cout  <<  "Constraints added" <<  endl;

  TIterator*  iterator = constrainingPdfs.createIterator();
  RooAbsPdf*  constrainingPdf;
  while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
    constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
    constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
  }

  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
  RooArgSet minosargset(parSigTimeSin2b,parSigTimeC);
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","migrad"))));
  if (cp_fit && !pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS)))));
  if (!cp_fit && pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsTimeErr)))));
  if (cp_fit && pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS,obsTimeErr)))));
  fitting_args.Add((TObject*)(new RooCmdArg(Offset(config.getBool("offset")))));

  if (bootstrapping) {

    doofit::config::CommonConfig cfg_com("common");
    cfg_com.InitializeOptions(argc, argv);

    ToyStudyStdConfig cfg_tstudy("toystudy");
    cfg_tstudy.InitializeOptions(cfg_com);

    cfg_com.CheckHelpFlagAndPrintHelp();
    cfg_com.PrintAll();

    PlotConfig cfg_plot("cfg_plot");

    ToyStudyStd tstudy(cfg_com, cfg_tstudy, cfg_plot);

    if (method.EqualTo("generate")) {
      fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
      fitting_args.Add((TObject*)(new RooCmdArg(Hesse(true))));
      fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
      fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
      fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));

      RooDataSet* data_bootstrapped;
      RooDataSet* data_OS;
      RooFitResult* fit_result;
      TRandom3 random(0);
      int num_events = 0;
      TStopwatch  stopwatch;
      // TH1D* hist_eta_max_converged = new TH1D("hist_eta_max_converged","hist_eta_max_converged",100,0,0.5);
      // TH1D* hist_eta_min_converged = new TH1D("hist_eta_min_converged","hist_eta_min_converged",100,0,0.5);
      // TH1D* hist_eta_max_failed = new TH1D("hist_eta_max_failed","hist_eta_max_failed",100,0,0.5);
      // TH1D* hist_eta_min_failed = new TH1D("hist_eta_min_failed","hist_eta_min_failed",100,0,0.5);
      // TH1D* hist_sine_term_converged = new TH1D("hist_sine_term_converged","hist_sine_term_converged",100,0,1);
      // TH1D* hist_sine_term_failed = new TH1D("hist_sine_term_failed","hist_sine_term_failed",100,0,1);

      for (int i = 0; i < config.getInt("nBootstraps") ; ++i) {
        cout  <<  i <<  endl;
        try {
          data_bootstrapped = new RooDataSet("data_bootstrapped","data_bootstrapped",RooArgSet(observables,categories));
          // std::vector<double> data_vector;
          num_events = random.Poisson(1410);
          for (int i = 0; i < num_events; ++i) {
            data->get(random.Rndm()*data->numEntries());
            data_bootstrapped->add(*(data->get()));
          }
          data_bootstrapped->Print();
          pdf->getParameters(*data_bootstrapped)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
          pdf->getParameters(*data_bootstrapped)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
          pdf->getParameters(*data_bootstrapped)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Acceptance_Splines.txt");
          stopwatch.Start(true);
          fit_result = pdf->fitTo(*data_bootstrapped,fitting_args);
          stopwatch.Stop();
          // data_OS = dynamic_cast<RooDataSet*>(data_bootstrapped->reduce(taggingcategory+">0"));
          // for (int i = 0; i < data_OS->numEntries(); ++i) {
          //   data_vector.push_back(data_OS->get(i)->getRealValue("obsEtaOSwCharm"));
          //   if (fit_result->status() == 3) {
          //     hist_sine_term_failed->Fill(TMath::Abs((1. - 2. * (parSigEtaP0_OS.getVal() + parSigEtaP1_OS.getVal() * (data_OS->get(i)->getRealValue("obsEtaOSwCharm") - parSigEtaMean_OS.getVal()))) * parSigTimeSin2b.getVal() * TMath::Sin(parSigTimeDeltaM.getVal() * data_OS->get(i)->getRealValue("obsTime"))));
          //   }
          //   else if (fit_result->status() == 0) {
          //     hist_sine_term_converged->Fill(TMath::Abs((1. - 2. * (parSigEtaP0_OS.getVal() + parSigEtaP1_OS.getVal() * (data_OS->get(i)->getRealValue("obsEtaOSwCharm") - parSigEtaMean_OS.getVal()))) * parSigTimeSin2b.getVal() * TMath::Sin(parSigTimeDeltaM.getVal() * data_OS->get(i)->getRealValue("obsTime"))));
          //   }
          // }
          // sort(data_vector.begin(), data_vector.end());
          // if (fit_result->status() == 3) {
          //   hist_eta_min_failed->Fill(data_vector.front());
          //   hist_eta_max_failed->Fill(data_vector.back());
          // }
          // else if (fit_result->status() == 0) {
          //   hist_eta_min_converged->Fill(data_vector.front());
          //   hist_eta_max_converged->Fill(data_vector.back());
          // }
          if (fit_result->status() != 3) throw 1;
          fit_result->Print("v");
          tstudy.StoreFitResult(fit_result, NULL, &stopwatch);
          RooAbsReal* nll = pdf->createNLL(*data_bootstrapped,ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS)),NumCPU(num_cpu,0),Optimize(0),ExternalConstraints(constrainingPdfs),Offset(config.getBool("offset")));
          RooPlot* frame = parSigTimeSin2b.frame(Range(parSigTimeSin2b.getVal()-3*parSigTimeSin2b.getError(),parSigTimeSin2b.getVal()+3*parSigTimeSin2b.getError()));
          nll->plotOn(frame, ShiftToZero());
          RooAbsReal* profile = nll->createProfile(RooArgSet(parSigTimeSin2b,parSigTimeC));
          profile->plotOn(frame,LineColor(2));
          TLatex* label = new TLatex(1,1,"");
          PlotSimple("Likelihoodscan",frame,*label,"/home/fmeier/lhcb-tank/b02dd/Bootstrapping/MCTest");
          delete profile;
          delete nll;
          delete data_bootstrapped;
        } catch (...) {
          i--;
        }
      }
      // TFile file_hist_eta(TString("/home/fmeier/lhcb-tank/b02dd/Bootstrapping/MCTest/Hist_Eta"+TString(argv[2])+".root"),"recreate");
      // hist_eta_max_converged->Write("hist_eta_max_converged");
      // hist_eta_min_converged->Write("hist_eta_min_converged");
      // hist_eta_max_failed->Write("hist_eta_max_failed");
      // hist_eta_min_failed->Write("hist_eta_min_failed");
      // file_hist_eta.Close();
      // TFile file_hist_sine_term(TString("/home/fmeier/lhcb-tank/b02dd/Bootstrapping/MCTest/Hist_Sine_Term"+TString(argv[2])+".root"),"recreate");
      // hist_sine_term_failed->Write("hist_sine_term_failed");
      // hist_sine_term_converged->Write("hist_sine_term_converged");
      // file_hist_sine_term.Close();
    }
    if (method.EqualTo("evaluate")) {
      tstudy.ReadFitResults();
      tstudy.EvaluateFitResults();
      tstudy.PlotEvaluatedParameters();
    }
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
