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
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' - c toystudy_config_file_name" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  bool pereventresolution = config.getBool("pereventresolution");
  TString method = config.getString("method");

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

  RooArgSet         observables(obsTime,obsEtaOS,obsEtaSS,obsTagOS,obsTagSS,"observables");
  if (pereventresolution) observables.add(obsTimeErr);
  RooArgSet         categories(catYear,catTag,"categories");
  RooArgSet         allobservables(observables,categories,"allobservables");
  RooArgSet         Gaussian_Constraints("Gaussian_Constraints");

  // Lifetime and mixing parameters
  RooRealVar          parSigTimeTau("parSigTimeTau","#tau",1.5,1.,2.);
  RooRealVar          parSigTimeTauMean("parSigTimeTauMean","#tau",1.519);
  RooRealVar          parSigTimeTauSigma("parSigTimeTauSigma","#tau",0.005);
  RooRealVar          parSigTimeDeltaM("parSigTimeDeltaM","#Delta m",0.510,0.4,0.6);
  RooRealVar          parSigTimeDeltaMMean("parSigTimeDeltaMMean","#Delta m",0.510);
  RooRealVar          parSigTimeDeltaMSigma("parSigTimeDeltaMSigma","#Delta m",0.004);
  RooRealVar          parSigEtaDeltaG_generate("parSigEtaDeltaG_generate","#Delta#Gamma",0.007);
  RooRealVar          parSigEtaDeltaG_fit("parSigEtaDeltaG_fit","#Delta#Gamma",0.);

  // CPV parameters
  RooRealVar          parSigTimeSin2b("parSigTimeSin2b","#it{S_{D^{+}D^{-}}}",0.7,-2,2);
  RooRealVar          parSigTimeC("parSigTimeC","#it{C_{D^{+}D^{-}}}",0,-2,2);
  RooFormulaVar       parSigTimeADeltaGamma("parSigTimeADeltaGamma","#it{A^{#Delta #Gamma}_{D^{+}D^{-}}}","-sqrt(1-@0*@0-@1*@1)",RooArgList(parSigTimeSin2b,parSigTimeC));

  // Production asymmetries
  RooRealVar          parSigEtaDeltaProd_11("parSigEtaDeltaProd_11","B0/B0bar production asymmetry",-0.0066,-0.05,0.02);
  RooRealVar          parSigEtaDeltaProdMean_11("parSigEtaDeltaProdMean_11","#bar{#mu}",-0.0066);
  RooRealVar          parSigEtaDeltaProdSigma_11("parSigEtaDeltaProdSigma_11","#sigma_{#bar{mu}}",0.0026);

  RooRealVar          parSigEtaDeltaProdOffset("parSigEtaDeltaProdOffset","difference between 2011 and 2012 B0/B0bar production asymmetry",0.0004,-0.01,0.01);
  RooRealVar          parSigEtaDeltaProdOffsetMean("parSigEtaDeltaProdOffsetMean","#bar{#mu}",0.0004);
  RooRealVar          parSigEtaDeltaProdOffsetSigma("parSigEtaDeltaProdOffsetSigma","#sigma_{#bar{mu}}",0.0018);
  RooAddition         parSigEtaDeltaProd_12("parSigEtaDeltaProd_12","B0/B0bar production asymmetry 2012",RooArgList(parSigEtaDeltaProd_11,parSigEtaDeltaProdOffset));

  // OS mistag asymmetries
  RooRealVar          parSigEtaDeltaP0_OS("parSigEtaDeltaP0_OS","#delta p_{0}^{OS}",0.0140,0.,0.03);
  RooRealVar          parSigEtaDeltaP0Mean_OS("parSigEtaDeltaP0Mean_OS","#bar{#delta p_{0}}",0.0148);
  RooRealVar          parSigEtaDeltaP0Sigma_OS("parSigEtaDeltaP0Sigma_OS","#sigma_{#bar{#delta p_{0}}}",0.0012);  // B+ value 0.0016  Kstar 0.0031
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_OS);

  RooRealVar          parSigEtaDeltaP1_OS("parSigEtaDeltaP1_OS","#delta p_{1}^{OS}",0.066,0.,0.1);
  RooRealVar          parSigEtaDeltaP1Mean_OS("parSigEtaDeltaP1Mean_OS","#bar{#delta p_{1}}",0.070);
  RooRealVar          parSigEtaDeltaP1Sigma_OS("parSigEtaDeltaP1Sigma_OS","#sigma_{#bar{#delta p_{1}}}",0.012);   // B+ value 0.018   Kstar 0.035
  Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_OS);

  // SS mistag asymmetries
  RooRealVar          parSigEtaDeltaP0_SS("parSigEtaDeltaP0_SS","#delta p_{0}^{SS}",-0.003,-0.02,0.02);
  RooRealVar          parSigEtaDeltaP0Mean_SS("parSigEtaDeltaP0Mean_SS","#bar{#delta p_{0}}",-0.0026);
  RooRealVar          parSigEtaDeltaP0Sigma_SS("parSigEtaDeltaP0Sigma_SS","#sigma_{#bar{#delta p_{0}}}",0.0044);
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_SS);

  RooRealVar          parSigEtaDeltaP1_SS("parSigEtaDeltaP1_SS","#delta p_{1}^{SS}",-0.18,-0.7,0.3);
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
  RooRealVar          parSigEtaP0_OS("parSigEtaP0_OS","p_{0}^{OS}",0.3815,0.0,0.1);
  RooRealVar          parSigEtaP0Mean_OS("parSigEtaP0Mean_OS","#bar{p}_{0}",0.3815);
  RooRealVar          parSigEtaP0Sigma_OS("parSigEtaP0Sigma_OS","#sigma_{#bar{p}_{0}}",0.0019);   // B+ value 0.0011  Kstar 0.0022
  Gaussian_Constraints.add(parSigEtaP0Sigma_OS);

  RooRealVar          parSigEtaP1_OS("parSigEtaP1_OS","p_{1}^{OS}",0.978,0.9,1.1);
  RooRealVar          parSigEtaP1Mean_OS("parSigEtaP1Mean_OS","#bar{p}_{1}",0.978);
  RooRealVar          parSigEtaP1Sigma_OS("parSigEtaP1Sigma_OS","#sigma_{#bar{p}_{1}}",0.007);  // B+ value 0.012   Kstar 0.024
  Gaussian_Constraints.add(parSigEtaP1Sigma_OS);
  
  RooRealVar          parSigEtaMean_OS("parSigEtaMean_OS","Mean on per-event mistag",0.3786);

  RooRealVar          parSigEtaP0_SS("parSigEtaP0_SS","p_{0}^{SS}",0.4228,0.3,0.5);
  RooRealVar          parSigEtaP0Mean_SS("parSigEtaP0Mean_SS","#bar{p}_{0}",0.4232);
  RooRealVar          parSigEtaP0Sigma_SS("parSigEtaP0Sigma_SS","#sigma_{#bar{p}_{0}}",0.0029);
  Gaussian_Constraints.add(parSigEtaP0Sigma_SS);

  RooRealVar          parSigEtaP1_SS("parSigEtaP1_SS","p_{1}^{SS}",1.01,0.7,1.1);
  RooRealVar          parSigEtaP1Mean_SS("parSigEtaP1Mean_SS","#bar{p}_{1}",1.011);
  RooRealVar          parSigEtaP1Sigma_SS("parSigEtaP1Sigma_SS","#sigma_{#bar{p}_{1}}",0.064);
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
  RooConstVar       parSigTimeSinh_fit("parSigTimeSinh_fit","Sh_{f}",0.0);
  CPCoefficient     parSigTimeSinh_11_OS_generate("parSigTimeSinh_11_OS_generate",parSigTimeADeltaGamma,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_11,CPCoefficient::kSinh);
  CPCoefficient     parSigTimeSinh_12_OS_generate("parSigTimeSinh_12_OS_generate",parSigTimeADeltaGamma,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd_12,CPCoefficient::kSinh);
  CPCoefficient     parSigTimeSinh_11_SS_generate("parSigTimeSinh_11_SS_generate",parSigTimeADeltaGamma,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSinh);
  CPCoefficient     parSigTimeSinh_12_SS_generate("parSigTimeSinh_12_SS_generate",parSigTimeADeltaGamma,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSinh);
  CPCoefficient     parSigTimeSinh_11_BS_generate("parSigTimeSinh_11_BS_generate",parSigTimeADeltaGamma,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSinh);
  CPCoefficient     parSigTimeSinh_12_BS_generate("parSigTimeSinh_12_BS_generate",parSigTimeADeltaGamma,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSinh);

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
  RooBDecay         pdfSigTime_11_OS_generate("pdfSigTime_11_OS_generate","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_generate,parSigTimeCosh_11_OS,parSigTimeSinh_11_OS_generate,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_11_SS_generate("pdfSigTime_11_SS_generate","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_generate,parSigTimeCosh_11_SS,parSigTimeSinh_11_SS_generate,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_12_OS_generate("pdfSigTime_12_OS_generate","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_generate,parSigTimeCosh_12_OS,parSigTimeSinh_12_OS_generate,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_12_SS_generate("pdfSigTime_12_SS_generate","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_generate,parSigTimeCosh_12_SS,parSigTimeSinh_12_SS_generate,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_11_BS_generate("pdfSigTime_11_BS_generate","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_generate,parSigTimeCosh_11_BS,parSigTimeSinh_11_BS_generate,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_12_BS_generate("pdfSigTime_12_BS_generate","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_generate,parSigTimeCosh_12_BS,parSigTimeSinh_12_BS_generate,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);

  RooBDecay         pdfSigTime_11_OS_fit("pdfSigTime_11_OS_fit","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_fit,parSigTimeCosh_11_OS,parSigTimeSinh_fit,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_11_SS_fit("pdfSigTime_11_SS_fit","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_fit,parSigTimeCosh_11_SS,parSigTimeSinh_fit,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_12_OS_fit("pdfSigTime_12_OS_fit","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_fit,parSigTimeCosh_12_OS,parSigTimeSinh_fit,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_12_SS_fit("pdfSigTime_12_SS_fit","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_fit,parSigTimeCosh_12_SS,parSigTimeSinh_fit,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_11_BS_fit("pdfSigTime_11_BS_fit","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_fit,parSigTimeCosh_11_BS,parSigTimeSinh_fit,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);
  RooBDecay         pdfSigTime_12_BS_fit("pdfSigTime_12_BS_fit","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG_fit,parSigTimeCosh_12_BS,parSigTimeSinh_fit,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);

//========================================================================================================================================================================================================================

  // Yields
  RooRealVar        parSigYield_11_OS("parSigYield_11_OS","parSigYield_11_OS", 200, 0, 1000);
  RooRealVar        parSigYield_11_SS("parSigYield_11_SS","parSigYield_11_SS", 200, 0, 1000);
  RooRealVar        parSigYield_12_OS("parSigYield_12_OS","parSigYield_12_OS", 200, 0, 1000);
  RooRealVar        parSigYield_12_SS("parSigYield_12_SS","parSigYield_12_SS", 200, 0, 1000);
  RooRealVar        parSigYield_11_BS("parSigYield_11_BS","parSigYield_11_BS", 200, 0, 1000);
  RooRealVar        parSigYield_12_BS("parSigYield_12_BS","parSigYield_12_BS", 200, 0, 1000);

  RooExtendPdf      pdfSigExtend_11_OS_generate("pdfSigExtend_11_OS_generate","pdfSigExtend_11_OS_generate",pdfSigTime_11_OS_generate,parSigYield_11_OS);
  RooExtendPdf      pdfSigExtend_11_SS_generate("pdfSigExtend_11_SS_generate","pdfSigExtend_11_SS_generate",pdfSigTime_11_SS_generate,parSigYield_11_SS);
  RooExtendPdf      pdfSigExtend_12_OS_generate("pdfSigExtend_12_OS_generate","pdfSigExtend_12_OS_generate",pdfSigTime_12_OS_generate,parSigYield_12_OS);
  RooExtendPdf      pdfSigExtend_12_SS_generate("pdfSigExtend_12_SS_generate","pdfSigExtend_12_SS_generate",pdfSigTime_12_SS_generate,parSigYield_12_SS);
  RooExtendPdf      pdfSigExtend_11_BS_generate("pdfSigExtend_11_BS_generate","pdfSigExtend_11_BS_generate",pdfSigTime_11_BS_generate,parSigYield_11_BS);
  RooExtendPdf      pdfSigExtend_12_BS_generate("pdfSigExtend_12_BS_generate","pdfSigExtend_12_BS_generate",pdfSigTime_12_BS_generate,parSigYield_12_BS);

  RooExtendPdf      pdfSigExtend_11_OS_fit("pdfSigExtend_11_OS_fit","pdfSigExtend_11_OS_fit",pdfSigTime_11_OS_fit,parSigYield_11_OS);
  RooExtendPdf      pdfSigExtend_11_SS_fit("pdfSigExtend_11_SS_fit","pdfSigExtend_11_SS_fit",pdfSigTime_11_SS_fit,parSigYield_11_SS);
  RooExtendPdf      pdfSigExtend_12_OS_fit("pdfSigExtend_12_OS_fit","pdfSigExtend_12_OS_fit",pdfSigTime_12_OS_fit,parSigYield_12_OS);
  RooExtendPdf      pdfSigExtend_12_SS_fit("pdfSigExtend_12_SS_fit","pdfSigExtend_12_SS_fit",pdfSigTime_12_SS_fit,parSigYield_12_SS);
  RooExtendPdf      pdfSigExtend_11_BS_fit("pdfSigExtend_11_BS_fit","pdfSigExtend_11_BS_fit",pdfSigTime_11_BS_fit,parSigYield_11_BS);
  RooExtendPdf      pdfSigExtend_12_BS_fit("pdfSigExtend_12_BS_fit","pdfSigExtend_12_BS_fit",pdfSigTime_12_BS_fit,parSigYield_12_BS);

//========================================================================================================================================================================================================================

  // Build Simultaneous PDF
  RooSuperCategory  supercategory_time("supercategory_time","supercategory_time",RooArgSet(catYear,catTag));
  RooSimultaneous   pdfTime_generate("pdfTime_generate","P",supercategory_time);
  pdfTime_generate.addPdf(pdfSigExtend_11_OS_generate,"{2011;OS}");
  pdfTime_generate.addPdf(pdfSigExtend_11_SS_generate,"{2011;SS}");
  pdfTime_generate.addPdf(pdfSigExtend_11_BS_generate,"{2011;both}");
  pdfTime_generate.addPdf(pdfSigExtend_12_OS_generate,"{2012;OS}");
  pdfTime_generate.addPdf(pdfSigExtend_12_SS_generate,"{2012;SS}");
  pdfTime_generate.addPdf(pdfSigExtend_12_BS_generate,"{2012;both}");

  RooSimultaneous   pdfTime_fit("pdfTime_fit","P",supercategory_time);
  pdfTime_fit.addPdf(pdfSigTime_11_OS_fit,"{2011;OS}");
  pdfTime_fit.addPdf(pdfSigTime_11_SS_fit,"{2011;SS}");
  pdfTime_fit.addPdf(pdfSigTime_11_BS_fit,"{2011;both}");
  pdfTime_fit.addPdf(pdfSigTime_12_OS_fit,"{2012;OS}");
  pdfTime_fit.addPdf(pdfSigTime_12_SS_fit,"{2012;SS}");
  pdfTime_fit.addPdf(pdfSigTime_12_BS_fit,"{2012;both}");  

  cout  <<  "simultaneous PDF built"  <<  endl;

  Gaussian_Constraints.readFromFile("/home/fmeier/storage03/b02dd/Systematics/DeltaGammad/generation.par");

  RooRealVar            parSigEtaDeltaP0P1CorrelationCoeff_OS("parSigEtaDeltaP0P1CorrelationCoeff_OS","correlation coefficient between calibration parameters p0 and p1 or Delta p0 and Delta p1 for OS",0.14);
  TMatrixDSym           covariancematrixSigEtaDelta_OS = CreateCovarianceMatrix(2, &parSigEtaDeltaP0Sigma_OS, &parSigEtaDeltaP1Sigma_OS, &parSigEtaDeltaP0P1CorrelationCoeff_OS);
  RooRealVar            parSigEtaP0P1CorrelationCoeff_OS("parSigEtaP0P1CorrelationCoeff_OS","correlation coefficient between calibration parameters p0 and p1 for OS",0.14);
  TMatrixDSym           covariancematrixSigEta_OS = CreateCovarianceMatrix(2, &parSigEtaP0Sigma_OS, &parSigEtaP1Sigma_OS, &parSigEtaP0P1CorrelationCoeff_OS);
  TMatrixDSym           covariancematrixSigEtaDelta_SS = CreateCovarianceMatrix(2, &parSigEtaDeltaP0Sigma_SS, &parSigEtaDeltaP1Sigma_SS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS);
  TMatrixDSym           covariancematrixSigEta_SS = CreateCovarianceMatrix(2, &parSigEtaP0Sigma_SS, &parSigEtaP1Sigma_SS, &parSigEtaP0P1CorrelationCoeff_SS);
  // TMatrixDSym           covariancematrixSigEta_SS = CreateCovarianceMatrix(4, &parSigEtaP0Sigma_SS, &parSigEtaP1Sigma_SS, &parSigEtaP0P1CorrelationCoeff_SS, &parSigEtaDeltaP0Sigma_SS, &parSigEtaDeltaP1Sigma_SS, &parSigEtaP0DeltaP0CorrelationCoeff_SS, &parSigEtaP0DeltaP1CorrelationCoeff_SS, &parSigEtaP1DeltaP0CorrelationCoeff_SS, &parSigEtaP1DeltaP1CorrelationCoeff_SS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS);

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
  RooMultiVarGaussian   conpdfSigEtaDelta_SS("conpdfSigEtaDelta_SS","constraint for Delta p0 and Delta p1 of SS FT calibration",RooArgList(parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS),RooArgList(parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP1Mean_SS),covariancematrixSigEtaDelta_SS);
  RooGaussian           conpdfSigEtaP0_OS("conpdfSigEtaP0_OS","Gaussian Constraint for Offset parameter",parSigEtaP0_OS,parSigEtaP0Mean_OS,parSigEtaP0Sigma_OS);
  RooGaussian           conpdfSigEtaP1_OS("conpdfSigEtaP1_OS","Gaussian Constraint for Scale parameter",parSigEtaP1_OS,parSigEtaP1Mean_OS,parSigEtaP1Sigma_OS);
  RooMultiVarGaussian   conpdfSigEta_OS("conpdfSigEta_OS","constraint for p0 and p1 of OS FT calibration",RooArgList(parSigEtaP0_OS,parSigEtaP1_OS),RooArgList(parSigEtaP0Mean_OS,parSigEtaP1Mean_OS),covariancematrixSigEta_OS);
  RooGaussian           conpdfSigEtaP0_SS("conpdfSigEtaP0_SS","Gaussian Constraint for Offset parameter",parSigEtaP0_SS,parSigEtaP0Mean_SS,parSigEtaP0Sigma_SS);
  RooGaussian           conpdfSigEtaP1_SS("conpdfSigEtaP1_SS","Gaussian Constraint for Scale parameter",parSigEtaP1_SS,parSigEtaP1Mean_SS,parSigEtaP1Sigma_SS);
  RooMultiVarGaussian   conpdfSigEta_SS("conpdfSigEta_SS","constraint for SS FT calibration",RooArgList(parSigEtaP0_SS,parSigEtaP1_SS),RooArgList(parSigEtaP0Mean_SS,parSigEtaP1Mean_SS),covariancematrixSigEta_SS);  
  // RooMultiVarGaussian   conpdfSigEta_SS("conpdfSigEta_SS","constraint for SS FT calibration",RooArgList(parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS),RooArgList(parSigEtaP0Mean_SS,parSigEtaP1Mean_SS,parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP1Mean_SS),covariancematrixSigEta_SS);  

  constrainingPdfs.add(conpdfSigTimeTau);
  constrainingPdfs.add(conpdfSigTimeDeltaM);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_11);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_12);
  constrainingPdfs.add(conpdfSigEta_OS);
  constrainingPdfs.add(conpdfSigEta_SS);
  constrainingPdfs.add(conpdfSigEtaDelta_OS);
  // constrainingPdfs.add(conpdfSigEtaDelta_SS);

  cout  <<  "Constraints added" <<  endl;

//========================================================================================================================================================================================================================

  // Mistag distributions
  TFile* mistag_histograms = new TFile("/home/fmeier/storage03/b02dd/Histograms/HIST_Eta_Distributions.root","read");
  TH1D*    TH1_Sig_OS_eta = dynamic_cast<TH1D*>(mistag_histograms->Get("hist_Sig_OS_eta"));
  TH1D*    TH1_Sig_SS_eta = dynamic_cast<TH1D*>(mistag_histograms->Get("hist_Sig_SS_eta"));
  RooDataHist DataHist_Sig_OS_eta("DataHist_Sig_OS_eta","DataHist_Sig_OS_eta",obsEtaOS,TH1_Sig_OS_eta);
  RooDataHist DataHist_Sig_SS_eta("DataHist_Sig_SS_eta","DataHist_Sig_SS_eta",obsEtaSS,TH1_Sig_SS_eta);
  RooHistPdf HistPdf_Sig_OS_eta("HistPdf_Sig_OS_eta","HistPdf_Sig_OS_eta",obsEtaOS,DataHist_Sig_OS_eta);
  RooHistPdf HistPdf_Sig_SS_eta("HistPdf_Sig_SS_eta","HistPdf_Sig_SS_eta",obsEtaSS,DataHist_Sig_SS_eta);

//========================================================================================================================================================================================================================

  // Workspace initialisation
  RooWorkspace* ws = new RooWorkspace("ws");
  ws->import(pdfTime_generate);
  ws->import(RooArgSet(HistPdf_Sig_OS_eta,HistPdf_Sig_SS_eta));
  ws->defineSet("allobservables",allobservables);

  RooDataSet* data = NULL;
  TIterator*  iterator = constrainingPdfs.createIterator();
  RooAbsPdf*  constrainingPdf;
  while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
    constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
    constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
  }
  ws->import(constrainingPdfs);
  ws->defineSet("constrainingPdfs",constrainingPdfs);

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

  PlotConfig cfg_plot("cfg_plot");
  ToyStudyStd tstudy(cfg_com, cfg_tstudy, cfg_plot);
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
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));

  if (method.EqualTo("generate")) {
    
    RooFitResult* fit_result;
    TStopwatch  stopwatch;
    RooDataSet* data_newconstrain_etaOS, *data_newconstrain_etaSS, *data_newconstrain_deltaetaOS, *data_newconstrain_deltaetaSS;
    for (int i = 0; i < 10 ; ++i) {
      cout  <<  i <<  endl;
      try {
        data = tfac.Generate();
        pdfTime_fit.getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/DeltaGammad/generation.par");
        iterator = constrainingPdfs.createIterator();
        while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
          constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/DecayTimeFitValidation/generation.par");
        }
        parSigEtaDeltaProdMean_11.setVal(conpdfSigEtaDeltaProd_11.generate(parSigEtaDeltaProd_11,1)->get()->getRealValue("parSigEtaDeltaProd_11"));
        parSigEtaDeltaProdOffsetMean.setVal(conpdfSigEtaDeltaProd_12.generate(parSigEtaDeltaProdOffset,1)->get()->getRealValue("parSigEtaDeltaProdOffset"));
        data_newconstrain_deltaetaOS = conpdfSigEtaDelta_OS.generate(RooArgSet(parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS),1);
        parSigEtaDeltaP0Mean_OS.setVal(data_newconstrain_deltaetaOS->get()->getRealValue("parSigEtaDeltaP0_OS"));
        parSigEtaDeltaP1Mean_OS.setVal(data_newconstrain_deltaetaOS->get()->getRealValue("parSigEtaDeltaP1_OS"));
        data_newconstrain_etaOS = conpdfSigEta_OS.generate(RooArgSet(parSigEtaP0_OS,parSigEtaP1_OS),1);
        parSigEtaP0Mean_OS.setVal(data_newconstrain_etaOS->get()->getRealValue("parSigEtaP0_OS"));
        parSigEtaP1Mean_OS.setVal(data_newconstrain_etaOS->get()->getRealValue("parSigEtaP1_OS"));
        // data_newconstrain_deltaetaSS = conpdfSigEtaDelta_SS.generate(RooArgSet(parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS),1);
        // parSigEtaDeltaP0Mean_SS.setVal(data_newconstrain_deltaetaSS->get()->getRealValue("parSigEtaDeltaP0_SS"));
        // parSigEtaDeltaP1Mean_SS.setVal(data_newconstrain_deltaetaSS->get()->getRealValue("parSigEtaDeltaP1_SS"));
        data_newconstrain_etaSS = conpdfSigEta_SS.generate(RooArgSet(parSigEtaP0_SS,parSigEtaP1_SS),1);
        parSigEtaP0Mean_SS.setVal(data_newconstrain_etaSS->get()->getRealValue("parSigEtaP0_SS"));
        parSigEtaP1Mean_SS.setVal(data_newconstrain_etaSS->get()->getRealValue("parSigEtaP1_SS"));
        parSigTimeTauMean.setVal(conpdfSigTimeTau.generate(parSigTimeTau,1)->get()->getRealValue("parSigTimeTau"));
        parSigTimeDeltaMMean.setVal(conpdfSigTimeDeltaM.generate(parSigTimeDeltaM,1)->get()->getRealValue("parSigTimeDeltaM"));
        stopwatch.Start(true);
        fit_result = pdfTime_fit.fitTo(*data,fitting_args);
        stopwatch.Stop();
        fit_result->Print("v");
        tstudy.StoreFitResult(fit_result, NULL, &stopwatch);
        delete iterator;
        delete data;
        delete data_newconstrain_etaOS;
        delete data_newconstrain_etaSS;
        delete data_newconstrain_deltaetaOS;
        delete data_newconstrain_deltaetaSS;
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
