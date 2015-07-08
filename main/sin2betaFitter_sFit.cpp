#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1.h"

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
#include "RooAddition.h"
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
#include "P2VV/RooCubicSplineFun.h"
#include "P2VV/RooCubicSplineKnot.h"
#include "P2VV/RooAbsGaussModelEfficiency.h"
#include "P2VV/RooGaussEfficiencyModel.h"
#include "P2VV/RooEffResAddModel.h"
#include "doofit/roofit/pdfs/BiasDelta.h"
#include "doofit/roofit/functions/LinearFunctionWithOffset.h"
#include "doofit/roofit/functions/TauCorrectionWithBetaFactor.h"
#include "doofit/roofit/functions/CPCoefficient.h"
#include "doofit/roofit/pdfs/DooCubicSplinePdf.h"
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
using namespace doofit::roofit::functions;
using namespace doofit::roofit::pdfs;

void PlotTimeErr(RooDataSet* data, TString cut, RooAbsPdf* pdf, RooArgSet projectionargs, TString category, int num_cpu);
void PlotTime(RooDataSet* data, TString cut, RooAbsPdf* pdf, RooArgSet projectionargs, TString category, int num_cpu);
void PlotAcceptance(RooAbsReal* acceptance);
TMatrixDSym CreateCovarianceMatrix(const int size, RooRealVar* p0sigma, RooRealVar* p1sigma, RooRealVar* p0p1corr, RooRealVar* dp0sigma = 0, RooRealVar* dp1sigma = 0, RooRealVar* p0dp0corr = 0, RooRealVar* p0dp1corr = 0, RooRealVar* p1dp0corr = 0, RooRealVar* p1dp1corr = 0, RooRealVar* dp0dp1corr = 0);

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  bool pereventresolution = config.getBool("pereventresolution");
  bool cp_fit = config.getBool("cp_fit");

  RooRealVar        obsTime("obsTime","#it{t}",0.25,15.25,"ps");
  RooRealVar        obsEtaOS("obsEtaOS_StdComb","#eta_{OS}",0.,0.5);
  RooRealVar        obsEtaSSPion("obsEtaSSPion_TupleCalib","#eta_{SS#pi}",0.,0.5);
  RooRealVar        obsTimeErr("obsTimeErr","#sigma_{t}",0.005,0.2,"ps");
  RooCategory       obsTagOS("obsTagOS_StdComb_NoZero","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  RooCategory       obsTagSSPion("obsTagSSPion_NoZero","Flavour Tag");
  obsTagSSPion.defineType("B0",1);
  obsTagSSPion.defineType("B0bar",-1);
  
  RooCategory       catYear("catYear","year of data taking");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooCategory       catTag("catTaggedOSSSPion","OS or SSPion tagged");
  catTag.defineType("OS",1);
  catTag.defineType("SSPion",-1);
  catTag.defineType("both",10);
  // catTag.defineType("untagged",0);
  
  RooRealVar        SigWeight("SigWeight","Signal weight",-10,10);
  
  RooArgSet         observables(obsTime,"observables");
  if (pereventresolution) observables.add(obsTimeErr);
  if (cp_fit){
    observables.add(obsEtaOS);
    observables.add(obsEtaSSPion);
    observables.add(obsTagOS);
    observables.add(obsTagSSPion);
  }
  RooArgSet         categories(catYear,catTag,SigWeight,"categories");
  
  // Get data set
  EasyTuple         tuple("/home/fmeier/storage03/Tuple/DT20112012_B02DD_Stripping21r0r1_DVv36r1_20150322_fmeier_combined_20150520_fmeier_FT_TupleD.root","B02DD",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet*       data = &(tuple.ConvertToDataSet(WeightVar(SigWeight)));
  data->Print();

  RooDataSet        proj_data("proj_data","proj_data",data,RooArgSet(obsEtaOS,obsEtaSSPion,obsTagOS,obsTagSSPion,obsTimeErr));
  
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
  
  RooRealVar          parSigEtaDeltaP1_OS("parSigEtaDeltaP1_OS","delta scale calibration parameter probability",0.066,0.,0.1);
  RooRealVar          parSigEtaDeltaP1Mean_OS("parSigEtaDeltaP1Mean_OS","#bar{#delta p_{1}}",0.070);
  RooRealVar          parSigEtaDeltaP1Sigma_OS("parSigEtaDeltaP1Sigma_OS","#sigma_{#bar{#delta p_{1}}}",0.012);   // B+ value 0.018   Kstar 0.035

  RooRealVar          parSigEtaDeltaP0P1CorrelationCoeff_OS("parSigEtaDeltaP0P1CorrelationCoeff_OS","correlation coefficient between calibration parameters p0 and p1 or Delta p0 and Delta p1 for OS",0.14);   // B+ value 0.14  Kstar 0.07
  TMatrixDSym         covariancematrixSigEtaDelta_OS = CreateCovarianceMatrix(2, &parSigEtaDeltaP0Sigma_OS, &parSigEtaDeltaP1Sigma_OS, &parSigEtaDeltaP0P1CorrelationCoeff_OS);
  covariancematrixSigEtaDelta_OS.Print();
  
  // SSPion tags
  RooRealVar          parSigEtaDeltaP0_SS("parSigEtaDeltaP0_SS","delta mistag probability",-0.003,-0.02,0.02);
  RooRealVar          parSigEtaDeltaP0Mean_SS("parSigEtaDeltaP0Mean_SS","#bar{#delta p_{0}}",-0.0026);
  RooRealVar          parSigEtaDeltaP0Sigma_SS("parSigEtaDeltaP0Sigma_SS","#sigma_{#bar{#delta p_{0}}}",0.0044);
  
  RooRealVar          parSigEtaDeltaP1_SS("parSigEtaDeltaP1_SS","delta scale calibration parameter probability",-0.18,-0.7,0.3);
  RooRealVar          parSigEtaDeltaP1Mean_SS("parSigEtaDeltaP1Mean_SS","#bar{#delta p_{1}}",-0.18);
  RooRealVar          parSigEtaDeltaP1Sigma_SS("parSigEtaDeltaP1Sigma_SS","#sigma_{#bar{#delta p_{1}}}",0.10);

//=========================================================================================================================================================================================================================

  // Resolution model
  RooRealVar                parResMean("parResMean","parResMean",-0.0032);
  RooRealVar                parResCorrectionOffset1("parResCorrectionOffset1","Offset of linear decay time error correction",0.);
  RooRealVar                parResCorrectionOffset2("parResCorrectionOffset2","Offset of linear decay time error correction",0.);
  RooRealVar                parResSigmaCorrectionFactor1("parResSigmaCorrectionFactor1","Correctionfactor of Proper Time Errors 1",1.);
  RooRealVar                parResSigmaCorrectionFactor2("parResSigmaCorrectionFactor2","Correctionfactor of Proper Time Errors 2",1.);
  LinearFunctionWithOffset  parResSigmaCorrection1("parResSigmaCorrection1",obsTimeErr,parResSigmaCorrectionFactor1,parResCorrectionOffset1);
  LinearFunctionWithOffset  parResSigmaCorrection2("parResSigmaCorrection2",obsTimeErr,parResSigmaCorrectionFactor2,parResCorrectionOffset2);
  RooGaussModel             respereventGauss1("respereventGauss1","per event resolution model 1",obsTime,parResMean,parResSigmaCorrection1);
  RooGaussModel             respereventGauss2("respereventGauss2","per event resolution model 2",obsTime,parResMean,parResSigmaCorrection2);
  RooRealVar                parResFraction2("parResFraction2","Fraction of second per event Gauss model",0.5);

//=========================================================================================================================================================================================================================
  
  // Decay Time Acceptance
  std::vector<double> knots;
  knots += 0.5;
  knots += 1.0;
  knots += 2.0;
  knots += 8.0;

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
  if (!pereventresolution) efficiencymodel = new RooGaussEfficiencyModel("efficiencymodel","Gaussefficiencymodel",obsTime,accspline,parResMean,RooConst(0.05));
  else efficiencymodel = new RooEffResAddModel("efficiencymodel","Per event resolution efficiency model",RooArgList(efficiencymodel2,efficiencymodel1),parResFraction2);

//=========================================================================================================================================================================================================================

  // Tagging calibration
  RooRealVar          parSigEtaP0_OS("parSigEtaP0_OS","Offset on per-event mistag",0.3815,0.0,0.1);
  RooRealVar          parSigEtaP0Mean_OS("parSigEtaP0Mean_OS","#bar{p}_{0}",0.3815);
  RooRealVar          parSigEtaP0Sigma_OS("parSigEtaP0Sigma_OS","#sigma_{#bar{p}_{0}}",0.0019);   // B+ value 0.0011  Kstar 0.0022
  
  RooRealVar          parSigEtaP1_OS("parSigEtaP1_OS","Offset on per-event mistag",0.978,0.9,1.1);
  RooRealVar          parSigEtaP1Mean_OS("parSigEtaP1Mean_OS","#bar{p}_{0}",0.978);
  RooRealVar          parSigEtaP1Sigma_OS("parSigEtaP1Sigma_OS","#sigma_{#bar{p}_{0}}",0.007);  // B+ value 0.012   Kstar 0.024

  RooRealVar          parSigEtaP0P1CorrelationCoeff_OS("parSigEtaP0P1CorrelationCoeff_OS","correlation coefficient between calibration parameters p0 and p1 for OS",0.14);   // B+ value 0.14  Kstar -0.0025
  TMatrixDSym         covariancematrixSigEta_OS = CreateCovarianceMatrix(2, &parSigEtaP0Sigma_OS, &parSigEtaP1Sigma_OS, &parSigEtaP0P1CorrelationCoeff_OS);
  covariancematrixSigEta_OS.Print();
  
  RooRealVar          parSigEtaMean_OS("parSigEtaMean_OS","Mean on per-event mistag",0.3786);

  RooRealVar          parSigEtaP0_SS("parSigEtaP0_SS","Offset on per-event mistag",0.4228,0.3,0.5);
  RooRealVar          parSigEtaP0Mean_SS("parSigEtaP0Mean_SS","#bar{p}_{0}",0.4232);
  RooRealVar          parSigEtaP0Sigma_SS("parSigEtaP0Sigma_SS","#sigma_{#bar{p}_{0}}",0.0029);
  
  RooRealVar          parSigEtaP1_SS("parSigEtaP1_SS","Offset on per-event mistag",1.01,0.7,1.1);
  RooRealVar          parSigEtaP1Mean_SS("parSigEtaP1Mean_SS","#bar{p}_{0}",1.011);
  RooRealVar          parSigEtaP1Sigma_SS("parSigEtaP1Sigma_SS","#sigma_{#bar{p}_{0}}",0.064);
  
  RooRealVar          parSigEtaP0P1CorrelationCoeff_SS("parSigEtaP0P1CorrelationCoeff_SS","correlation coefficient between p0 and p1 SSPion",0.030);
  RooRealVar          parSigEtaP0DeltaP0CorrelationCoeff_SS("parSigEtaP0DeltaP0CorrelationCoeff_SS","correlation coefficient between p0 and Delta p0 SSPion",-0.007);
  RooRealVar          parSigEtaP0DeltaP1CorrelationCoeff_SS("parSigEtaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between p0 and Delta p1 SSPion",0.0016);
  RooRealVar          parSigEtaP1DeltaP0CorrelationCoeff_SS("parSigEtaP1DeltaP0CorrelationCoeff_SS","correlation coefficient between p1 and Delta p0 SSPion",0.0004);
  RooRealVar          parSigEtaP1DeltaP1CorrelationCoeff_SS("parSigEtaP1DeltaP1CorrelationCoeff_SS","correlation coefficient between p1 and Delta p1 SSPion",-0.006);
  RooRealVar          parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS("parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS","correlation coefficient between Delta p0 and Delta p1 SSPion",0.04);

  TMatrixDSym         covariancematrixSigEta_SS = CreateCovarianceMatrix(4, &parSigEtaP0Sigma_SS, &parSigEtaP1Sigma_SS, &parSigEtaP0P1CorrelationCoeff_SS, &parSigEtaDeltaP0Sigma_SS, &parSigEtaDeltaP1Sigma_SS, &parSigEtaP0DeltaP0CorrelationCoeff_SS, &parSigEtaP0DeltaP1CorrelationCoeff_SS, &parSigEtaP1DeltaP0CorrelationCoeff_SS, &parSigEtaP1DeltaP1CorrelationCoeff_SS, &parSigEtaDeltaP0DeltaP1CorrelationCoeff_SS);
  covariancematrixSigEta_SS.Print();

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
  
  CPCoefficient     parSigTimeCosh_11_SS("parSigTimeCosh_11_SS",RooConst(1.0),obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_SS("parSigTimeCosh_12_SS",RooConst(1.0),obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_SS("parSigTimeSin_11_SS",parSigTimeBlindedSin2b,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_SS("parSigTimeSin_12_SS",parSigTimeBlindedSin2b,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_SS("parSigTimeCos_11_SS",parSigTimeBlindedC,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_SS("parSigTimeCos_12_SS",parSigTimeBlindedC,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCos);

  CPCoefficient     parSigTimeCosh_11_BS("parSigTimeCosh_11_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeCosh_12_BS("parSigTimeCosh_12_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_11_BS("parSigTimeSin_11_BS",parSigTimeBlindedSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kSin);
  CPCoefficient     parSigTimeSin_12_BS("parSigTimeSin_12_BS",parSigTimeBlindedSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_11_BS("parSigTimeCos_11_BS",parSigTimeBlindedC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_11,CPCoefficient::kCos);
  CPCoefficient     parSigTimeCos_12_BS("parSigTimeCos_12_BS",parSigTimeBlindedC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSSPion,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSSPion,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd_12,CPCoefficient::kCos);
  
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
  RooSuperCategory  supercategory("supercategory","supercategory",RooArgSet(catYear,catTag));
  RooSimultaneous   pdf("pdf","P",supercategory);
  pdf.addPdf(*pdfSigTime_11_OS,"{2011;OS}");
  pdf.addPdf(*pdfSigTime_11_SS,"{2011;SSPion}");
  pdf.addPdf(*pdfSigTime_11_BS,"{2011;both}");
  pdf.addPdf(*pdfSigTime_12_OS,"{2012;OS}");
  pdf.addPdf(*pdfSigTime_12_SS,"{2012;SSPion}");
  pdf.addPdf(*pdfSigTime_12_BS,"{2012;both}");

  cout  <<  "simultaneous PDF built"  <<  endl;

  // Get Starting Values and Fit PDF to data
  pdf.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
  pdf.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
  pdf.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Acceptance_Splines.txt");
  
  // pdf.getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/StartingValues.txt");
  pdf.Print();
  
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

  TIterator*  iterator = constrainingPdfs.createIterator();
  RooAbsPdf*  constrainingPdf;
  while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
    constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Eta.txt");
    constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
    // constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/StartingValues.txt");
  }
  
  // Fit PDF to data
  pdf.getParameters(*data)->writeToFile("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/StartingValues.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
  RooArgSet minosargset(parSigTimeSin2b,parSigTimeC);
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
  if (cp_fit && !pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSSPion)))));
  if (!cp_fit && pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsTimeErr)))));
  if (cp_fit && pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSSPion,obsTimeErr)))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Offset(true))));

  RooFitResult* fit_result = pdf.fitTo(*data,fitting_args);
  pdf.getParameters(*data)->writeToFile("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/FitResults.txt");
  fit_result->Print("v");
  doofit::plotting::fitresult::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();
  fit_result->correlationMatrix().Print();
  TFile   fitresultwritetofile(TString("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/FitResults_"+config.getString("resolutionmodelname")+".root"),"recreate");
  fit_result->Write("fit_result");
  fitresultwritetofile.Close();

  // Plots
  pdf.getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/FitResults.txt");
  PlotAcceptance(&accspline);
 
  PlotConfig cfg_plot_time("cfg_plot_time");
  cfg_plot_time.set_plot_appendix("");
  cfg_plot_time.set_plot_directory("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/PlotTime");
  std::vector<std::string> components_time;
  PlotSimultaneous Time(cfg_plot_time, obsTime, *data, pdf, components_time);
  RooArgSet projargset(obsTimeErr,obsTagOS,obsTagSSPion,obsEtaOS,obsEtaSSPion);
  Time.AddPlotArg(NumCPU(1));
//  Time.AddPlotArg(Normalization(1./data->numEntries()));
  Time.AddPlotArg(ProjWData(projargset,*data,false));
  if (!cp_fit)  Time.PlotItLogY();
  
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

void PlotAcceptance(RooAbsReal* acceptance){

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  c.SetLogx(true);
  
  RooRealVar        obsTime("obsTime","#it{t}",0.25,15.25,"ps");

  RooPlot* plot = obsTime.frame();
  acceptance->plotOn(plot);
  plot->SetMinimum(0.);
  plot->SetMaximum(1.);
  plot->GetYaxis()->SetTitle("acceptance");
  plot->Draw();
  c.SaveAs("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/PlotAcceptance/Acceptancespline.pdf");
  
  c.SetLogx(false);
  plot = obsTime.frame();
  acceptance->plotOn(plot);
  plot->SetMinimum(0.);
  plot->SetMaximum(1.);
  plot->GetYaxis()->SetTitle("acceptance");
  plot->Draw();
  c.SaveAs("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/PlotAcceptance/Acceptancespline_nolog.pdf");
  
  c.SetLogx(true);
  plot = obsTime.frame();
  acceptance->plotOn(plot);
  plot->SetMinimum(0.);
  plot->SetMaximum(0.7);
  plot->GetYaxis()->SetTitle("acceptance");
  plot->Draw();
  c.SaveAs("/home/fmeier/storage03/b02dd/run/sin2betaFit_sFit/PlotAcceptance/Acceptancespline_zoomed.pdf");
}

