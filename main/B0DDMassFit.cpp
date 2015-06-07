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

// from DooFit
#include "URANIA/RooIpatia2.h"
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

  bool massmodel_ipatia = false;
  bool split_years      = false;

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  RooRealVar        varKminus_PID("varKminus_PID","varKminus_PID",0,1);
  RooRealVar        varKplus_PID("varKplus_PID","varKplus_PID",0,1);
  RooRealVar        varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID",0,1);
  RooRealVar        varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID",0,1);
  RooRealVar        varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID",0,1);
  RooRealVar        varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID",0,1);
  RooArgSet         varPIDs(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID,"varPIDs");

  RooRealVar        varDminusMassHypo_KKpi("varDminusMassHypo_KKpi","varDminusMassHypo_KKpi",0,5000);
  RooRealVar        varDminusMassHypo_KpiK("varDminusMassHypo_KpiK","varDminusMassHypo_KpiK",0,5000);
  RooRealVar        varDplusMassHypo_KKpi("varDplusMassHypo_KKpi","varDplusMassHypo_KKpi",0,5000);
  RooRealVar        varDplusMassHypo_KpiK("varDplusMassHypo_KpiK","varDplusMassHypo_KpiK",0,5000);
  RooArgSet         varDMassHypos(varDminusMassHypo_KKpi,varDminusMassHypo_KpiK,varDplusMassHypo_KKpi,varDplusMassHypo_KpiK,"varDMassHypos");

  RooRealVar        varPhiMassHypo_DminusOne("varPhiMassHypo_DminusOne","varPhiMassHypo_DminusOne",0,2000);
  RooRealVar        varPhiMassHypo_DminusTwo("varPhiMassHypo_DminusTwo","varPhiMassHypo_DminusTwo",0,2000);
  RooRealVar        varPhiMassHypo_DplusOne("varPhiMassHypo_DplusOne","varPhiMassHypo_DplusOne",0,2000);
  RooRealVar        varPhiMassHypo_DplusTwo("varPhiMassHypo_DplusTwo","varPhiMassHypo_DplusTwo",0,2000);
  RooArgSet         varPhiMassHypos(varPhiMassHypo_DminusOne,varPhiMassHypo_DminusTwo,varPhiMassHypo_DplusOne,varPhiMassHypo_DplusTwo,"varPhiMassHypos");

  RooRealVar        Dminus_piminus_or_Kminus_One_PIDK("Dminus_piminus_or_Kminus_One_PIDK","Dminus_piminus_or_Kminus_One_PIDK",-100,100);
  RooRealVar        Dminus_piminus_or_Kminus_Two_PIDK("Dminus_piminus_or_Kminus_Two_PIDK","Dminus_piminus_or_Kminus_Two_PIDK",-100,100);
  RooRealVar        Dplus_piplus_or_Kplus_One_PIDK("Dplus_piplus_or_Kplus_One_PIDK","Dplus_piplus_or_Kplus_One_PIDK",-100,100);
  RooRealVar        Dplus_piplus_or_Kplus_Two_PIDK("Dplus_piplus_or_Kplus_Two_PIDK","Dplus_piplus_or_Kplus_Two_PIDK",-100,100);  
  RooArgSet         varPIDKs(Dminus_piminus_or_Kminus_One_PIDK,Dminus_piminus_or_Kminus_Two_PIDK,Dplus_piplus_or_Kplus_One_PIDK,Dplus_piplus_or_Kplus_Two_PIDK,"varPIDKs");

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",1);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);

  RooCategory       catYear("catYear","catYear");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);

  RooArgSet         observables(obsMass,obsMassDauOne,obsMassDauTwo,"observables");
  RooArgSet         variables(varBDT,"variables");
  variables.add(varPIDs);
  variables.add(varDMassHypos);
  variables.add(varPhiMassHypos);
  variables.add(varPIDKs);
  RooArgSet         realvars(observables,variables,"realvars");
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,catYear,"categories");
  
  // Get data set
  EasyTuple         tuple(argv[1],"B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet();
  
  data.Print();

  // Mass PDF
  RooAbsPdf*        pdfSigBdMass;
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
  if (!massmodel_ipatia)  pdfSigBdMass = new RooAddPdf("pdfSigBdMass","pdfSigBdMass",RooArgList(pdfSigMassCB1,pdfSigMassCB2),parSigMassCBFraction);

  RooRealVar        parSigMassL("parSigMassL","parSigMassL",-5.6);
  RooRealVar        parSigMassZeta("parSigMassZeta","parSigMassZeta",0);
  RooRealVar        parSigMassBeta("parSigMassBeta","parSigMassBeta",0,-0.1,0.1);
  RooRealVar        parSigMassSigma("parSigMassSigma","parSigMassSigma",9.0,5,15,"MeV/c^{2}");
  RooRealVar        parSigMassAlpha1("parSigMassAlpha1","parSigMassAlpha1",1.31);
  RooRealVar        parSigMassn1("parSigMassn1","parSigMassn1",10);
  RooRealVar        parSigMassAlpha2("parSigMassAlpha2","parSigMassAlpha2",2.28);
  RooRealVar        parSigMassn2("parSigMassn2","parSigMassn2",10);
  if (massmodel_ipatia) pdfSigBdMass = new RooIpatia2("pdfSigBdMass","pdfSigBdMass",obsMass,parSigMassL,parSigMassZeta,parSigMassBeta,parSigMassSigma,parSigMassMean,parSigMassAlpha1,parSigMassn1,parSigMassAlpha2,parSigMassn2);

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
  RooExponential    pdfBkgBMass("pdfBkgDMass","pdfBkgDMass",obsMass,parBkgExponent);

  RooRealVar        parBkgEffLowDCombMassMean("parBkgEffLowDCombMassMean","Mean Mass",5120,5100,5140,"MeV/c^{2}");
  RooRealVar        parBkgEffLowDCombMassSigma("parBkgEffLowDCombMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgEffLowDCombMass("pdfBkgEffLowDCombMass","Upper DstD Mass PDF",obsMass,parBkgEffLowDCombMassMean,parBkgEffLowDCombMassSigma);

  RooRealVar        parSigDMassMean("parSigDMassMean","D Mean Mass",1870,1860,1880,"MeV/c^{2}");
  RooRealVar        parSigDMassSigma("parSigDMassSigma","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooGaussian       pdfSigDplusMass("pdfSigDplusMass","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma);
  RooGaussian       pdfSigDminusMass("pdfSigDminusMass","Signal Mass PDF",obsMassDauTwo,parSigDMassMean,parSigDMassSigma);

  RooRealVar        parBkgDExponent("parBkgDExponent","parBkgDExponent",-0.005,-1,1);
  RooExponential    pdfBkgDplusMass("pdfBkgDplusMass","pdfBkgDplusMass",obsMassDauOne,parBkgDExponent);
  RooExponential    pdfBkgDminusMass("pdfBkgDminusMass","pdfBkgDminusMass",obsMassDauTwo,parBkgDExponent);


  // Full Mass PDFs describing B, D+ and D- mass spectrum

  RooProdPdf        pdfBdDDMass("pdfBdDDMass","pdfBdDDMass",RooArgList(*pdfSigBdMass,pdfSigDplusMass,pdfSigDminusMass));
  RooProdPdf        pdfBsDDMass("pdfBsDDMass","pdfBsDDMass",RooArgList(*pdfSigBsMass,pdfSigDplusMass,pdfSigDminusMass));
  RooProdPdf        pdfDstDLowDDMass("pdfDstDLowDDMass","pdfDstDLowDDMass",RooArgList(pdfBkgDstDLowMass,pdfSigDplusMass,pdfSigDminusMass));
  RooProdPdf        pdfDstDHighDDMass("pdfDstDHighDDMass","pdfDstDHighDDMass",RooArgList(pdfBkgDstDHighMass,pdfSigDplusMass,pdfSigDminusMass));
  RooProdPdf        pdfDsDDDMass("pdfDsDDDMass","pdfDsDDDMass",RooArgList(pdfBkgDsDMass,pdfSigDplusMass,pdfSigDminusMass));

  RooProdPdf        pdfLowDCombMass("pdfLowDCombMass","pdfLowDCombMass",RooArgList(pdfBkgEffLowDCombMass,pdfSigDplusMass,pdfBkgDminusMass));
  RooProdPdf        pdfDsDDCombMass("pdfDsDDCombMass","pdfDsDDCombMass",RooArgList(pdfBkgDsDMass,pdfSigDplusMass,pdfBkgDminusMass));
  RooProdPdf        pdfBkgDCombMass("pdfBkgDCombMass","pdfBkgDCombMass",RooArgList(pdfBkgBMass,pdfSigDplusMass,pdfBkgDminusMass));

  RooProdPdf        pdfLowCombDMass("pdfLowCombDMass","pdfLowCombDMass",RooArgList(pdfBkgEffLowDCombMass,pdfBkgDplusMass,pdfSigDminusMass));
  RooProdPdf        pdfDsDCombDMass("pdfDsDCombDMass","pdfDsDCombDMass",RooArgList(pdfBkgDsDMass,pdfBkgDplusMass,pdfSigDminusMass));
  RooProdPdf        pdfBkgCombDMass("pdfBkgCombDMass","pdfBkgCombDMass",RooArgList(pdfBkgBMass,pdfBkgDplusMass,pdfSigDminusMass));

  RooProdPdf        pdfBkgCombMass("pdfBkgCombMass","pdfBkgCombMass",RooArgList(pdfBkgBMass,pdfBkgDplusMass,pdfBkgDminusMass));

  // Yields of all 3-dim mass PDFs

  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgDstDLowYield_11("parBkgDstDLowYield_11","parBkgDstDLowYield_11",150,0,10000);
  RooRealVar        parBkgDstDLowYield_12("parBkgDstDLowYield_12","parBkgDstDLowYield_12",450,0,10000);
  RooRealVar        parBkgDstDLowYield("parBkgDstDLowYield","parBkgDstDLowYield",600,0,10000);
  RooRealVar        parBkgDstDHighYield_11("parBkgDstDHighYield_11","parBkgDstDHighYield_11",100,0,10000);
  RooRealVar        parBkgDstDHighYield_12("parBkgDstDHighYield_12","parBkgDstDHighYield_12",300,0,10000);
  RooRealVar        parBkgDstDHighYield("parBkgDstDHighYield","parBkgDstDHighYield",500,0,10000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  
  RooRealVar        parLowDCombYield_11("parLowDCombYield_11","parLowDCombYield_11",5000,0,10000);
  RooRealVar        parLowDCombYield_12("parLowDCombYield_12","parLowDCombYield_12",5000,0,10000);
  RooRealVar        parLowDCombYield("parLowDCombYield","parLowDCombYield",5000,0,10000);
  RooRealVar        parDsDDCombYield_11("parDsDDCombYield_11","parDsDDCombYield_11",5000,0,10000);
  RooRealVar        parDsDDCombYield_12("parDsDDCombYield_12","parDsDDCombYield_12",5000,0,10000);
  RooRealVar        parDsDDCombYield("parDsDDCombYield","parDsDDCombYield",5000,0,10000);
  RooRealVar        parBkgDCombYield_11("parBkgDCombYield_11","parBkgDCombYield_11",5000,0,10000);
  RooRealVar        parBkgDCombYield_12("parBkgDCombYield_12","parBkgDCombYield_12",5000,0,10000);
  RooRealVar        parBkgDCombYield("parBkgDCombYield","parBkgDCombYield",5000,0,10000);

  RooRealVar        parLowCombDYield_11("parLowCombDYield_11","parLowCombDYield_11",5000,0,10000);
  RooRealVar        parLowCombDYield_12("parLowCombDYield_12","parLowCombDYield_12",5000,0,10000);
  RooRealVar        parLowCombDYield("parLowCombDYield","parLowCombDYield",5000,0,10000);
  RooRealVar        parDsDCombDYield_11("parDsDCombDYield_11","parDsDCombDYield_11",5000,0,10000);
  RooRealVar        parDsDCombDYield_12("parDsDCombDYield_12","parDsDCombDYield_12",5000,0,10000);
  RooRealVar        parDsDCombDYield("parDsDCombDYield","parDsDCombDYield",5000,0,10000);
  RooRealVar        parBkgCombDYield_11("parBkgCombDYield_11","parBkgCombDYield_11",5000,0,10000);
  RooRealVar        parBkgCombDYield_12("parBkgCombDYield_12","parBkgCombDYield_12",5000,0,10000);
  RooRealVar        parBkgCombDYield("parBkgCombDYield","parBkgCombDYield",5000,0,10000);

  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);
  
  // Extended PDFs

  RooExtendPdf      pdfBdDDMassExtend_11("pdfBdDDMassExtend_11","pdfBdDDMassExtend_11",pdfBdDDMass,parSigYield_11);
  RooExtendPdf      pdfBdDDMassExtend_12("pdfBdDDMassExtend_12","pdfBdDDMassExtend_12",pdfBdDDMass,parSigYield_12);
  RooExtendPdf      pdfBdDDMassExtend("pdfBdDDMassExtend","pdfBdDDMassExtend",pdfBdDDMass,parSigYield);
  RooExtendPdf      pdfBsDDMassExtend_11("pdfBsDDMassExtend_11","pdfBsDDMassExtend_11",pdfBsDDMass,parSigBsYield_11);
  RooExtendPdf      pdfBsDDMassExtend_12("pdfBsDDMassExtend_12","pdfBsDDMassExtend_12",pdfBsDDMass,parSigBsYield_12);
  RooExtendPdf      pdfBsDDMassExtend("pdfBsDDMassExtend","pdfBsDDMassExtend",pdfBsDDMass,parSigBsYield);
  RooExtendPdf      pdfDstDLowDDMassExtend_11("pdfDstDLowDDMassExtend_11","pdfDstDLowDDMassExtend_11",pdfDstDLowDDMass,parBkgDstDLowYield_11);
  RooExtendPdf      pdfDstDLowDDMassExtend_12("pdfDstDLowDDMassExtend_12","pdfDstDLowDDMassExtend_12",pdfDstDLowDDMass,parBkgDstDLowYield_12);
  RooExtendPdf      pdfDstDLowDDMassExtend("pdfDstDLowDDMassExtend","pdfDstDLowDDMassExtend",pdfDstDLowDDMass,parBkgDstDLowYield);
  RooExtendPdf      pdfDstDHighDDMassExtend_11("pdfDstDHighDDMassExtend_11","pdfDstDHighDDMassExtend_11",pdfDstDHighDDMass,parBkgDstDHighYield_11);
  RooExtendPdf      pdfDstDHighDDMassExtend_12("pdfDstDHighDDMassExtend_12","pdfDstDHighDDMassExtend_12",pdfDstDHighDDMass,parBkgDstDHighYield_12);
  RooExtendPdf      pdfDstDHighDDMassExtend("pdfDstDHighDDMassExtend","pdfDstDHighDDMassExtend",pdfDstDHighDDMass,parBkgDstDHighYield);
  RooExtendPdf      pdfDsDDDMassExtend_11("pdfDsDDDMassExtend_11","pdfDsDDDMassExtend_11",pdfDsDDDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfDsDDDMassExtend_12("pdfDsDDDMassExtend_12","pdfDsDDDMassExtend_12",pdfDsDDDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfDsDDDMassExtend("pdfDsDDDMassExtend","pdfDsDDDMassExtend",pdfDsDDDMass,parBkgDsDYield);
  
  RooExtendPdf      pdfLowDCombMassExtend_11("pdfLowDCombMassExtend_11","pdfLowDCombMassExtend_11",pdfLowDCombMass,parLowDCombYield_11);
  RooExtendPdf      pdfLowDCombMassExtend_12("pdfLowDCombMassExtend_12","pdfLowDCombMassExtend_12",pdfLowDCombMass,parLowDCombYield_12);
  RooExtendPdf      pdfLowDCombMassExtend("pdfLowDCombMassExtend","pdfLowDCombMassExtend",pdfLowDCombMass,parLowDCombYield);
  RooExtendPdf      pdfDsDDCombMassExtend_11("pdfDsDDCombMassExtend_11","pdfDsDDCombMassExtend_11",pdfDsDDCombMass,parDsDDCombYield_11);
  RooExtendPdf      pdfDsDDCombMassExtend_12("pdfDsDDCombMassExtend_12","pdfDsDDCombMassExtend_12",pdfDsDDCombMass,parDsDDCombYield_12);
  RooExtendPdf      pdfDsDDCombMassExtend("pdfDsDDCombMassExtend","pdfDsDDCombMassExtend",pdfDsDDCombMass,parDsDDCombYield);
  RooExtendPdf      pdfBkgDCombMassExtend_11("pdfBkgDCombMassExtend_11","pdfBkgDCombMassExtend_11",pdfBkgDCombMass,parBkgDCombYield_11);
  RooExtendPdf      pdfBkgDCombMassExtend_12("pdfBkgDCombMassExtend_12","pdfBkgDCombMassExtend_12",pdfBkgDCombMass,parBkgDCombYield_12);
  RooExtendPdf      pdfBkgDCombMassExtend("pdfBkgDCombMassExtend","pdfBkgDCombMassExtend",pdfBkgDCombMass,parBkgDCombYield);

  RooExtendPdf      pdfLowCombDMassExtend_11("pdfLowCombDMassExtend_11","pdfLowCombDMassExtend_11",pdfLowCombDMass,parLowCombDYield_11);
  RooExtendPdf      pdfLowCombDMassExtend_12("pdfLowCombDMassExtend_12","pdfLowCombDMassExtend_12",pdfLowCombDMass,parLowCombDYield_12);
  RooExtendPdf      pdfLowCombDMassExtend("pdfLowCombDMassExtend","pdfLowCombDMassExtend",pdfLowCombDMass,parLowCombDYield);
  RooExtendPdf      pdfDsDCombDMassExtend_11("pdfDsDCombDMassExtend_11","pdfDsDCombDMassExtend_11",pdfDsDCombDMass,parDsDCombDYield_11);
  RooExtendPdf      pdfDsDCombDMassExtend_12("pdfDsDCombDMassExtend_12","pdfDsDCombDMassExtend_12",pdfDsDCombDMass,parDsDCombDYield_12);
  RooExtendPdf      pdfDsDCombDMassExtend("pdfDsDCombDMassExtend","pdfDsDCombDMassExtend",pdfDsDCombDMass,parDsDCombDYield);
  RooExtendPdf      pdfBkgCombDMassExtend_11("pdfBkgCombDMassExtend_11","pdfBkgCombDMassExtend_11",pdfBkgCombDMass,parBkgCombDYield_11);
  RooExtendPdf      pdfBkgCombDMassExtend_12("pdfBkgCombDMassExtend_12","pdfBkgCombDMassExtend_12",pdfBkgCombDMass,parBkgCombDYield_12);
  RooExtendPdf      pdfBkgCombDMassExtend("pdfBkgCombDMassExtend","pdfBkgCombDMassExtend",pdfBkgCombDMass,parBkgCombDYield);

  RooExtendPdf      pdfBkgCombMassExtend_11("pdfBkgCombMassExtend_11","pdfBkgCombMassExtend_11",pdfBkgCombMass,parBkgYield_11);
  RooExtendPdf      pdfBkgCombMassExtend_12("pdfBkgCombMassExtend_12","pdfBkgCombMassExtend_12",pdfBkgCombMass,parBkgYield_12);
  RooExtendPdf      pdfBkgCombMassExtend("pdfBkgCombMassExtend","pdfBkgCombMassExtend",pdfBkgCombMass,parBkgYield);

  RooArgList        pdfList_11(pdfBdDDMassExtend_11,pdfBsDDMassExtend_11,/*pdfDstDLowDDMassExtend_11,pdfDstDHighDDMassExtend_11,*/pdfDsDDDMassExtend_11,"pdfList_11");
  //pdfList_11.add(pdfLowDCombMassExtend_11);
  pdfList_11.add(pdfDsDDCombMassExtend_11);
  pdfList_11.add(pdfBkgDCombMassExtend_11);
  //pdfList_11.add(pdfLowCombDMassExtend_11);
  pdfList_11.add(pdfDsDCombDMassExtend_11);
  pdfList_11.add(pdfBkgCombDMassExtend_11);
  pdfList_11.add(pdfBkgCombMassExtend_11);
  RooArgList        pdfList_12(pdfBdDDMassExtend_12,pdfBsDDMassExtend_12,/*pdfDstDLowDDMassExtend_12,pdfDstDHighDDMassExtend_12,*/pdfDsDDDMassExtend_12,"pdfList_12");
  //pdfList_12.add(pdfLowDCombMassExtend_12);
  pdfList_12.add(pdfDsDDCombMassExtend_12);
  pdfList_12.add(pdfBkgDCombMassExtend_12);
  //pdfList_12.add(pdfLowCombDMassExtend_12);
  pdfList_12.add(pdfDsDCombDMassExtend_12);
  pdfList_12.add(pdfBkgCombDMassExtend_12);
  pdfList_12.add(pdfBkgCombMassExtend_12);
  RooArgList        pdfList(pdfBdDDMassExtend,pdfBsDDMassExtend,/*pdfDstDLowDDMassExtend,pdfDstDHighDDMassExtend,*/pdfDsDDDMassExtend,"pdfList");
  //pdfList.add(pdfLowDCombMassExtend);
  pdfList.add(pdfDsDDCombMassExtend);
  pdfList.add(pdfBkgDCombMassExtend);
  //pdfList.add(pdfLowCombDMassExtend);
  pdfList.add(pdfDsDCombDMassExtend);
  pdfList.add(pdfBkgCombDMassExtend);
  pdfList.add(pdfBkgCombMassExtend);

  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",pdfList_11);
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",pdfList_12);
  
  RooAbsPdf*        pdfMass;

  if (split_years) {
    RooSimultaneous* pdfSimMass = new RooSimultaneous("pdfSimMass","pdfSimMass",catYear);
    pdfSimMass->addPdf(pdfMass_11,"2011");
    pdfSimMass->addPdf(pdfMass_12,"2012");
    pdfMass = pdfSimMass;
  }
  else pdfMass = new RooAddPdf("pdfMass","Mass PDF",pdfList);

  // Get Starting Values and Fit PDF to data
  pdfMass->Print();
  pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_DDweightsMass.txt");
  pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/StartingValues_Mass.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(8))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  RooFitResult* fit_result = pdfMass->fitTo(data, fitting_args);
  doofit::plotting::fitresult::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();

  if (massmodel_ipatia) pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/FitResults_Ipatia_3Dweights_"+TString(argv[2])+".txt");
  else pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/FitResults_3Dweights_"+TString(argv[2])+".txt");

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/sWeights/Plots/"+string(argv[2]));
  cfg_plot_mass.set_simultaneous_plot_all_categories(true);
  std::vector<std::string> components_mass;
  components_mass += "pdfBdDDMassExtend.*", "pdfBsDDMassExtend.*", "pdfDsDDDMassExtend.*", "pdfDsDDCombMassExtend.*", "pdfBkgDCombMassExtend.*", "pdfDsDCombDMassExtend.*", "pdfBkgCombDMassExtend.*", "pdfBkgCombMassExtend.*";
  Plot* Mass;
  if (massmodel_ipatia) {
    if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, data, *((RooSimultaneous*)pdfMass), components_mass, "3Dweights_Ipatia_obsMass_"+string(argv[2]));
    else Mass = new Plot(cfg_plot_mass, obsMass, data, *pdfMass, components_mass, "3Dweights_Ipatia_obsMass_"+string(argv[2]));
  }
  else {
    if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, data, *((RooSimultaneous*)pdfMass), components_mass, "3Dweights_obsMass_"+string(argv[2]));
    else Mass = new Plot(cfg_plot_mass, obsMass, data, *pdfMass, components_mass, "3Dweights_obsMass_"+string(argv[2]));
  }
  Mass->PlotItLogNoLogY();

  if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMassDauOne, data, *((RooSimultaneous*)pdfMass), components_mass, "3Dweights_obsMassDauOne_"+string(argv[2]));
  else Mass = new Plot(cfg_plot_mass, obsMassDauOne, data, *pdfMass, components_mass, "3Dweights_obsMassDauOne_"+string(argv[2]));
  Mass->PlotItLogNoLogY();

  if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMassDauTwo, data, *((RooSimultaneous*)pdfMass), components_mass, "3Dweights_obsMassDauTwo_"+string(argv[2]));
  else Mass = new Plot(cfg_plot_mass, obsMassDauTwo, data, *pdfMass, components_mass, "3Dweights_obsMassDauTwo_"+string(argv[2]));
  Mass->PlotItLogNoLogY();

  return 0;
}
