#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1.h"
#include "TRandom3.h"

//from RooFit
#include "RooCmdArg.h"
#include "RooMsgService.h"
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

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooBDecay.h"
#include "RooDecay.h"
#include "RooGaussian.h"
#include "RooMultiVarGaussian.h"
#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooEffProd.h"
#include "RooSimultaneous.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooAddModel.h"
#include "RooCBShape.h"
#include "RooExponential.h"
#include "RooExtendPdf.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "Urania/RooIpatia2.h"
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
#include "doofit/config/CommonConfig.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStd.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStdConfig.h"
#include "doofit/fitter/splot/SPlotFit2.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::toy;
using namespace doofit::roofit::functions;
using namespace doofit::roofit::pdfs;
using namespace doofit::fitter::splot;

TMatrixDSym CreateCovarianceMatrix(const int size, RooRealVar* p0sigma, RooRealVar* p1sigma, RooRealVar* p0p1corr, RooRealVar* dp0sigma = 0, RooRealVar* dp1sigma = 0, RooRealVar* p0dp0corr = 0, RooRealVar* p0dp1corr = 0, RooRealVar* p1dp0corr = 0, RooRealVar* p1dp1corr = 0, RooRealVar* dp0dp1corr = 0);

int main(int argc, char * argv[]){
  if (argc < 3) {
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' - c toystudy_config_file_name" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  bool pereventresolution = config.getBool("pereventresolution");
  bool split_years      = config.getBool("split_years");
  TString method = config.getString("method");

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
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
  catTag.defineType("untagged",0);
  
  RooRealVar        SigWeight_11("parSigYield_11_sw","Signal weight for 2011",-10,10);
  RooRealVar        SigWeight_12("parSigYield_12_sw","Signal weight for 2012",-10,10);
  RooFormulaVar     SigWeight("SigWeight","Signal weight","@0+@1",RooArgList(SigWeight_11,SigWeight_12));
  
  RooArgSet         observables(obsTime,obsMass,"observables");
  if (pereventresolution) observables.add(obsTimeErr);
  
  observables.add(obsEtaOS);
  observables.add(obsEtaSSPion);
  observables.add(obsTagOS);
  observables.add(obsTagSSPion);
  RooArgSet         categories(catYear,catTag,"categories");
  
  //==============================================================================================================================================
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
  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.52",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);
  RooAddPdf         pdfSigBsMass("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB2),parSigMassCBFraction);
  
  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  //==============================================================================================================================================
  // Extend PDFs with yields
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
  
  RooExtendPdf      pdfSigExtend_11("pdfSigExtend_11","pdfSigExtend_11",pdfSigMass,parSigYield_11);
  RooExtendPdf      pdfSigExtend_12("pdfSigExtend_12","pdfSigExtend_12",pdfSigMass,parSigYield_12);
  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);
  RooExtendPdf      pdfBkgDsDExtend_11("pdfBkgDsDExtend_11","pdfBkgDsDExtend_11",pdfBkgDsDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfBkgDsDExtend_12("pdfBkgDsDExtend_12","pdfBkgDsDExtend_12",pdfBkgDsDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfBkgDsDExtend("pdfBkgDsDExtend","pdfBkgDsDExtend",pdfBkgDsDMass,parBkgDsDYield);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);
  
  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12));
  
  RooAbsPdf*        pdfMass;

  if (split_years) {
    pdfMass = new RooSimultaneous("pdfMass","pdfMass",catYear);
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11,"2011");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12,"2012");
  }
  else pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend));

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
  RooRealVar                parResSigma_wrongPV("parResSigma_wrongPV","Width of wrong PV component",1,0,5);

  RooRealVar                parResFraction2("parResFraction2","Fraction of second per event Gauss model",0.5);
  RooRealVar                parResFraction_wrongPV("parResFraction_wrongPV","Fraction of wrong PV Gauss model",0.1);

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
  RooGaussEfficiencyModel efficiencymodel3("efficiencymodel3","Gaussefficiencymodel 3",obsTime,accspline,parResMean,parResSigma_wrongPV);
  if (!pereventresolution) efficiencymodel = new RooGaussEfficiencyModel("efficiencymodel","Gaussefficiencymodel",obsTime,accspline,parResMean,RooConst(0.05));
  else efficiencymodel = new RooEffResAddModel("efficiencymodel","Per event resolution efficiency model",RooArgList(efficiencymodel3,efficiencymodel2,efficiencymodel1),RooArgList(parResFraction_wrongPV,parResFraction2));

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

  RooBDecay         pdfSigTime_11_OS("pdfSigTime_11_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_OS,parSigTimeSinh,parSigTimeCos_11_OS,parSigTimeSin_11_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);;
  RooBDecay         pdfSigTime_11_SS("pdfSigTime_11_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_SS,parSigTimeSinh,parSigTimeCos_11_SS,parSigTimeSin_11_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);;
  RooBDecay         pdfSigTime_12_OS("pdfSigTime_12_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_OS,parSigTimeSinh,parSigTimeCos_12_OS,parSigTimeSin_12_OS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);;
  RooBDecay         pdfSigTime_12_SS("pdfSigTime_12_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_SS,parSigTimeSinh,parSigTimeCos_12_SS,parSigTimeSin_12_SS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);;
  RooBDecay         pdfSigTime_11_BS("pdfSigTime_11_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_11_BS,parSigTimeSinh,parSigTimeCos_11_BS,parSigTimeSin_11_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);;
  RooBDecay         pdfSigTime_12_BS("pdfSigTime_12_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_12_BS,parSigTimeSinh,parSigTimeCos_12_BS,parSigTimeSin_12_BS,parSigTimeDeltaM,*efficiencymodel,RooBDecay::SingleSided);;
  
//========================================================================================================================================================================================================================
  
  // Build Simultaneous PDF
  RooSuperCategory  supercategory("supercategory","supercategory",RooArgSet(catYear,catTag));
  RooSimultaneous   pdf("pdf","P",supercategory);
  pdf.addPdf(pdfSigTime_11_OS,"{2011;OS}");
  pdf.addPdf(pdfSigTime_11_SS,"{2011;SSPion}");
  pdf.addPdf(pdfSigTime_11_BS,"{2011;both}");
  pdf.addPdf(pdfSigTime_12_OS,"{2012;OS}");
  pdf.addPdf(pdfSigTime_12_SS,"{2012;SSPion}");
  pdf.addPdf(pdfSigTime_12_BS,"{2012;both}");

  cout  <<  "simultaneous PDF built"  <<  endl;
  
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
  constrainingPdfs.add(conpdfSigTimeDeltaM);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_11);
  constrainingPdfs.add(conpdfSigEtaDeltaProd_12);
  constrainingPdfs.add(conpdfSigEta_OS);
  constrainingPdfs.add(conpdfSigEta_SS);
  constrainingPdfs.add(conpdfSigEtaDelta_OS);
  
  cout  <<  "Constraints added" <<  endl;

  if (method.EqualTo("g") || method.EqualTo("e")) {

    doofit::config::CommonConfig cfg_com("common");
    cfg_com.InitializeOptions(argc, argv);
    
    ToyStudyStdConfig cfg_tstudy("toystudy");
    cfg_tstudy.InitializeOptions(cfg_com);
    
    cfg_com.CheckHelpFlagAndPrintHelp();
    cfg_com.PrintAll();

    ToyStudyStd tstudy(cfg_com, cfg_tstudy);

    if (method.EqualTo("g")) {

      RooLinkedList fitting_args;
      fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
      RooArgSet minosargset(parSigTimeSin2b,parSigTimeC);
      fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
      fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
      fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
      fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
      fitting_args.Add((TObject*)(new RooCmdArg(Hesse(true))));
      fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
      fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(true))));
      fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
      fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
      if (pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSSPion,obsTimeErr)))));
      else fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSSPion)))));
      fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
      fitting_args.Add((TObject*)(new RooCmdArg(Offset(true))));

      // Get original data set
      EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(observables,categories));
      tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
      RooDataSet*       data = &(tuple.ConvertToDataSet());

      RooDataSet* data_bootstrapped;
      RooDataSet* data_bootstrapped_sweighted;
      SPlotFit2* splotfit;
      TRandom3 random(0);
      TStopwatch  stopwatch;

      for (int i = 0; i < 20 ; ++i) {
        cout  <<  i <<  endl;
        try {
          data_bootstrapped = new RooDataSet("data_bootstrapped","data_bootstrapped",RooArgSet(observables,categories));
          for (int i = 0; i < data->numEntries(); ++i) {
            data->get(random.Rndm()*data->numEntries());
            data_bootstrapped->add(*(data->get()));
          }
          data_bootstrapped->Print();
          pdfMass->getParameters(data)->readFromFile("/home/fmeier/storage03/b02dd/Bootstrapping/WithMass/StartingValues_Mass.txt");
          RooArgSet set_of_yields_11(parSigYield_11,parBkgDsDYield_11,parSigBsYield_11,parBkgYield_11);
          RooArgSet set_of_yields_12(parSigYield_12,parBkgDsDYield_12,parSigBsYield_12,parBkgYield_12);
          splotfit = new SPlotFit2(*pdfMass,*data_bootstrapped,RooArgSet(set_of_yields_11,set_of_yields_12));
          splotfit->set_use_minos(false);
          splotfit->set_num_cpu(config.getInt("num_cpu"));
          RooMsgService::instance().setStreamStatus(0, false);
          RooMsgService::instance().setStreamStatus(1, false);
          splotfit->Fit();
          RooMsgService::instance().setStreamStatus(0, true);
          RooMsgService::instance().setStreamStatus(1, true);
          data_bootstrapped->addColumn(SigWeight);
          data_bootstrapped_sweighted = new RooDataSet("data_bootstrapped_sweighted","data_bootstrapped_sweighted",data_bootstrapped,*(data_bootstrapped->get()),"catTaggedOSSSPion!=0","SigWeight");
          data_bootstrapped_sweighted->Print();
          // EasyTuple tuple_bootstrapped(*data_bootstrapped_sweighted);
          // tuple_bootstrapped.WriteDataSetToTree("/home/fmeier/storage03/Tuple/Bootstrapping_Test.root","B02DD");
          pdf.getParameters(data)->readFromFile("/home/fmeier/storage03/b02dd/Bootstrapping/WithMass/generation.par");
          TIterator*  iterator = constrainingPdfs.createIterator();
          RooAbsPdf*  constrainingPdf;
          while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
            constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/Bootstrapping/WithMass/generation.par");
          }
          stopwatch.Start(true);
          RooFitResult* fit_result = pdf.fitTo(*data_bootstrapped_sweighted,fitting_args);
          stopwatch.Stop();
          fit_result->Print("v");
          tstudy.StoreFitResult(fit_result, NULL, &stopwatch);
          delete data_bootstrapped_sweighted;
        } catch (...) {
          i--;
        }
      }
    }
    
    if (method.EqualTo("e")) {
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