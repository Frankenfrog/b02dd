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
#include "doofit/plotting/Plot/PlotConfig.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;

void KaonPID_Optimization(RooAbsPdf* pdf, RooAbsPdf* pdfD, RooDataSet* data, RooLinkedList& fitting_args);
void PionPID_Optimization(RooAbsPdf* pdf, RooAbsPdf* pdfD, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber = "One");
void ElectronPID_Optimization(RooAbsPdf* pdf, RooAbsPdf* pdfD, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber = "One");

int main(int argc, char * argv[]){

  bool massmodel_ipatia = false;


  // RooRealVar        obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");
  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5100,5500,"MeV/c^{2}");
  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");

  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  RooRealVar        varDplusMassHypo_KKpi("varDplusMassHypo_KKpi","varDplusMassHypo_KKpi",0,5000);
  RooRealVar        varDplusMassHypo_KpiK("varDplusMassHypo_KpiK","varDplusMassHypo_KpiK",0,5000);
  RooRealVar        varDminusMassHypo_KKpi("varDminusMassHypo_KKpi","varDminusMassHypo_KKpi",0,5000);
  RooRealVar        varDminusMassHypo_KpiK("varDminusMassHypo_KpiK","varDminusMassHypo_KpiK",0,5000);

  RooRealVar        varPiOneplus_DLLk("Dplus_piplus_or_Kplus_One_RichDLLk","Dplus_piplus_or_Kplus_One_RichDLLk",-100,100);
  RooRealVar        varPiTwoplus_DLLk("Dplus_piplus_or_Kplus_Two_RichDLLk","Dplus_piplus_or_Kplus_Two_RichDLLk",-100,100);
  RooRealVar        varPiOneminus_DLLk("Dminus_piminus_or_Kminus_One_RichDLLk","Dminus_piminus_or_Kminus_One_RichDLLk",-100,100);
  RooRealVar        varPiTwominus_DLLk("Dminus_piminus_or_Kminus_Two_RichDLLk","Dminus_piminus_or_Kminus_Two_RichDLLk",-100,100);

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",1);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);

  RooRealVar        varKminus_ProbNNk("Dplus_Kminus_or_piminus_ProbNNk","Dplus_Kminus_or_piminus_ProbNNk",0,1);
  RooRealVar        varKminus_ProbNNpi("Dplus_Kminus_or_piminus_ProbNNpi","Dplus_Kminus_or_piminus_ProbNNpi",0,1);
  RooRealVar        varKplus_ProbNNk("Dminus_Kplus_or_piplus_ProbNNk","Dminus_Kplus_or_piplus_ProbNNk",0,1);
  RooRealVar        varKplus_ProbNNpi("Dminus_Kplus_or_piplus_ProbNNpi","Dminus_Kplus_or_piplus_ProbNNpi",0,1);
  RooRealVar        varPiOneminus_ProbNNk("Dminus_piminus_or_Kminus_One_ProbNNk","Dminus_piminus_or_Kminus_One_ProbNNk",0,1);
  RooRealVar        varPiOneminus_ProbNNpi("Dminus_piminus_or_Kminus_One_ProbNNpi","Dminus_piminus_or_Kminus_One_ProbNNpi",0,1);
  RooRealVar        varPiOneminus_ProbNNe("Dminus_piminus_or_Kminus_One_ProbNNe","Dminus_piminus_or_Kminus_One_ProbNNe",0,1);
  RooRealVar        varPiOneplus_ProbNNk("Dplus_piplus_or_Kplus_One_ProbNNk","Dplus_piplus_or_Kplus_One_ProbNNk",0,1);
  RooRealVar        varPiOneplus_ProbNNpi("Dplus_piplus_or_Kplus_One_ProbNNpi","Dplus_piplus_or_Kplus_One_ProbNNpi",0,1);
  RooRealVar        varPiOneplus_ProbNNe("Dplus_piplus_or_Kplus_One_ProbNNe","Dplus_piplus_or_Kplus_One_ProbNNe",0,1);
  RooRealVar        varPiTwominus_ProbNNk("Dminus_piminus_or_Kminus_Two_ProbNNk","Dminus_piminus_or_Kminus_Two_ProbNNk",0,1);
  RooRealVar        varPiTwominus_ProbNNpi("Dminus_piminus_or_Kminus_Two_ProbNNpi","Dminus_piminus_or_Kminus_Two_ProbNNpi",0,1);
  RooRealVar        varPiTwominus_ProbNNe("Dminus_piminus_or_Kminus_Two_ProbNNe","Dminus_piminus_or_Kminus_Two_ProbNNe",0,1);
  RooRealVar        varPiTwoplus_ProbNNk("Dplus_piplus_or_Kplus_Two_ProbNNk","Dplus_piplus_or_Kplus_Two_ProbNNk",0,1);
  RooRealVar        varPiTwoplus_ProbNNpi("Dplus_piplus_or_Kplus_Two_ProbNNpi","Dplus_piplus_or_Kplus_Two_ProbNNpi",0,1);
  RooRealVar        varPiTwoplus_ProbNNe("Dplus_piplus_or_Kplus_Two_ProbNNe","Dplus_piplus_or_Kplus_Two_ProbNNe",0,1);

  RooArgSet         observables(obsMass/*,obsMassDauOne,obsMassDauTwo*/,"observables");
  RooArgSet         variables(varBDT,"variables");
  RooArgSet         MassHypos(varDplusMassHypo_KKpi,varDplusMassHypo_KpiK,varDminusMassHypo_KKpi,varDminusMassHypo_KpiK,"MassHypos");
  // variables.add(MassHypos);
  RooArgSet         DLLs(varPiOneplus_DLLk,varPiOneminus_DLLk,varPiTwoplus_DLLk,varPiTwominus_DLLk,"DLLs");
  // variables.add(DLLs);
  RooArgSet         varKaonProbNNs(varKminus_ProbNNk,varKminus_ProbNNpi,varKplus_ProbNNk,varKplus_ProbNNpi,"varKaonProbNNs");
  RooArgSet         varPiOneProbNNs(varPiOneminus_ProbNNk,varPiOneminus_ProbNNpi,varPiOneplus_ProbNNk,varPiOneplus_ProbNNpi,varPiOneminus_ProbNNe,varPiOneplus_ProbNNe,"varPionProbNNs");
  RooArgSet         varPiTwoProbNNs(varPiTwominus_ProbNNk,varPiTwominus_ProbNNpi,varPiTwoplus_ProbNNk,varPiTwoplus_ProbNNpi,varPiTwominus_ProbNNe,varPiTwoplus_ProbNNe,"varPiTwoProbNNs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varKaonProbNNs);
  realvars.add(varPiOneProbNNs);
  realvars.add(varPiTwoProbNNs);
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,"categories");
  
  // Get data set
  EasyTuple         tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/Combined_2011_2012/DT20112012_B02DD_Stripping21r0r1_DVv36r1_20150322_fmeier_combined_20150504_fmeier_BDT_TupleB_BDT99applied.root","B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet();//Cut("(abs(varDplusMassHypo_KKpi-1968.3)>25||Dplus_piplus_or_Kplus_One_RichDLLk<-10)&&(abs(varDplusMassHypo_KpiK-1968.3)>25||Dplus_piplus_or_Kplus_Two_RichDLLk<-10)&&(abs(varDminusMassHypo_KKpi-1968.3)>25||Dminus_piminus_or_Kminus_One_RichDLLk<-10)&&(abs(varDminusMassHypo_KpiK-1968.3)>25||Dminus_piminus_or_Kminus_Two_RichDLLk<-10)"));
  
  data.Print();

  RooFormulaVar     varKminus_PID("varKminus_PID","varKminus_PID","@0/(@0+@1)",RooArgList(varKminus_ProbNNk,varKminus_ProbNNpi));
  RooFormulaVar     varKplus_PID("varKplus_PID","varKplus_PID","@0/(@0+@1)",RooArgList(varKplus_ProbNNk,varKplus_ProbNNpi));
  RooFormulaVar     varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID","@0/(@0+@1)",RooArgList(varPiOneminus_ProbNNk,varPiOneminus_ProbNNpi));
  RooFormulaVar     varPiOneminus_PIDe("varPiOneminus_PIDe","varPiOneminus_PIDe","@0/(@0+@1)",RooArgList(varPiOneminus_ProbNNe,varPiOneminus_ProbNNpi));
  RooFormulaVar     varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID","@0/(@0+@1)",RooArgList(varPiOneplus_ProbNNk,varPiOneplus_ProbNNpi));
  RooFormulaVar     varPiOneplus_PIDe("varPiOneplus_PIDe","varPiOneplus_PIDe","@0/(@0+@1)",RooArgList(varPiOneplus_ProbNNe,varPiOneplus_ProbNNpi));
  RooFormulaVar     varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID","@0/(@0+@1)",RooArgList(varPiTwominus_ProbNNk,varPiTwominus_ProbNNpi));
  RooFormulaVar     varPiTwominus_PIDe("varPiTwominus_PIDe","varPiTwominus_PIDe","@0/(@0+@1)",RooArgList(varPiTwominus_ProbNNe,varPiTwominus_ProbNNpi));
  RooFormulaVar     varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID","@0/(@0+@1)",RooArgList(varPiTwoplus_ProbNNk,varPiTwoplus_ProbNNpi));
  RooFormulaVar     varPiTwoplus_PIDe("varPiTwoplus_PIDe","varPiTwoplus_PIDe","@0/(@0+@1)",RooArgList(varPiTwoplus_ProbNNe,varPiTwoplus_ProbNNpi));
  RooArgList        PID_formulas(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID);
  data.addColumns(PID_formulas);
  RooArgList        PIDe_formulas(varPiOneminus_PIDe,varPiOneplus_PIDe,varPiTwominus_PIDe,varPiTwoplus_PIDe);
  data.addColumns(PIDe_formulas);

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

  EasyTuple         tuple_DsD_MC("/fhgfs/groups/e5/lhcb/NTuples/B02DD/MC/Sim08/2012/MC_Sim08a_2012_Pythia8_B02DsD_Stripping20_DVv36r5_20150428_pseyfert_20150430_fmeier_BDT_TupleB.root","B02DD",RooArgSet(realvars,categories));
  tuple_DsD_MC.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data_DsD_MC = tuple_DsD_MC.ConvertToDataSet(Cut(TString(varBDT.GetName())+">-0.784"));//&&(abs(varDplusMassHypo_KKpi-1968.3)>25||Dplus_piplus_or_Kplus_One_RichDLLk<-10)&&(abs(varDplusMassHypo_KpiK-1968.3)>25||Dplus_piplus_or_Kplus_Two_RichDLLk<-10)&&(abs(varDminusMassHypo_KKpi-1968.3)>25||Dminus_piminus_or_Kminus_One_RichDLLk<-10)&&(abs(varDminusMassHypo_KpiK-1968.3)>25||Dminus_piminus_or_Kminus_Two_RichDLLk<-10)"));
  data_DsD_MC.addColumns(PID_formulas);
  data_DsD_MC.Print();
  RooDataSet*       data_DsD_MC_optimized = dynamic_cast<RooDataSet*>(data_DsD_MC.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65"));
  RooKeysPdf        pdfBkgDsDMass("pdfBkgDsDMass","pdfBkgDsDMass", obsMass, *data_DsD_MC_optimized);

  // RooRealVar        parBkgDsDMean("parBkgDsDMean","partial reco Mean Mass",5220,5200,5250,"MeV/c^{2}");
  // RooRealVar        parBkgDsDSigma("parBkgDsDSigma","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  // RooGaussian       pdfBkgDsDMass("pdfBkgDsDMass","partial reco Mass PDF",obsMass,parBkgDsDMean,parBkgDsDSigma);

  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.52",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);
  if (!massmodel_ipatia) pdfSigBsMass = new RooAddPdf("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB2),parSigMassCBFraction);

  if (massmodel_ipatia) pdfSigBsMass = new RooIpatia2("pdfSigBsMass","pdfSigBsMass",obsMass,parSigMassL,parSigMassZeta,parSigMassBeta,parSigMassSigma,parSigBsMassMean,parSigMassAlpha1,parSigMassn1,parSigMassAlpha2,parSigMassn2);  
  
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",*pdfSigMass,parSigYield);
  RooExtendPdf      pdfBkgDsDExtend("pdfBkgDsDExtend","pdfBkgDsDExtend",pdfBkgDsDMass,parBkgDsDYield);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",*pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend));

  RooRealVar        parSigDMassMean("parSigDMassMean","Bd Mean Mass",1870,1860,1880,"MeV/c^{2}");
  RooRealVar        parSigDMassSigma("parSigDMassSigma","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooGaussian       pdfSigDMass("pdfSigDMass","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma);

  RooRealVar        parBkgDExponent("parBkgDExponent","parBkgDExponent",-0.005,-1,1);
  RooExponential    pdfBkgDMass("pdfBkgDMass","pdfBkgDMass",obsMassDauOne,parBkgDExponent);

  RooRealVar        parSigDYield("parSigDYield","parSigDYield",4000,0,10000);
  RooRealVar        parBkgDYield("parBkgDYield","parBkgDYield",3000,0,10000);

  RooExtendPdf      pdfSigDExtend("pdfSigDExtend","pdfSigDExtend",pdfSigDMass,parSigDYield);
  RooExtendPdf      pdfBkgDExtend("pdfBkgDExtend","pdfBkgDExtend",pdfBkgDMass,parBkgDYield);
  RooAddPdf         pdfDMass("pdfDMass","Mass PDF",RooArgList(pdfSigDExtend,pdfBkgDExtend));  

  // Get Starting Values and Fit PDF to data
  pdfMass.Print();
  pdfMass.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/PID-Optimization/StartingValues_Mass.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(4))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  // KaonPID_Optimization(&pdfMass, &pdfDMass, &data, fitting_args);
  RooDataSet* optimized_kaon_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2"));
  // PionPID_Optimization(&pdfMass, &pdfDMass, optimized_kaon_data, fitting_args, "One");
  RooDataSet* optimized_pionone_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5"));
  // PionPID_Optimization(&pdfMass, &pdfDMass, optimized_pionone_data, fitting_args, "Two");
  RooDataSet* optimized_piontwo_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65"));
  // ElectronPID_Optimization(&pdfMass, &pdfDMass, &data, fitting_args, "One");
  // RooDataSet* optimized_electronone_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65&&varPiOneminus_PIDe<0.5&&varPiOneplus_PIDe<0.5"));
  // ElectronPID_Optimization(&pdfMass, &pdfDMass, optimized_electronone_data, fitting_args, "Two");

  RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65"));
  optimized_data->Print();
  RooFitResult* fit_result = pdfMass.fitTo(*optimized_data, fitting_args);
  if (massmodel_ipatia) pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Ipatia.txt");
  else pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults.txt");

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/Mass/Plots");
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend", "pdfBkgDsDExtend", "pdfSigBsExtend", "pdfBkgExtend";
  if (massmodel_ipatia) {
    Plot Mass(cfg_plot_mass, obsMass, *optimized_data, pdfMass, components_mass, "Ipatia_obsMass_optimized");
    Mass.PlotItLogNoLogY();
  }
  else {
    Plot Mass(cfg_plot_mass, obsMass, *optimized_data, pdfMass, components_mass, "obsMass_optimized");
    Mass.PlotItLogNoLogY();
  }
  

  // fit_result = pdfDMass.fitTo(*optimized_data, fitting_args);
  // std::vector<std::string> components_Dmass;
  // components_Dmass += "pdfSigDExtend", "pdfBkgDExtend";
  // Plot MassD(cfg_plot_mass, obsMassDauOne, *optimized_data, pdfDMass, components_Dmass, "obsMassDauOne_optimized");
  // MassD.PlotIt();

  return 0;
}

void KaonPID_Optimization(RooAbsPdf* pdf, RooAbsPdf* pdfD, RooDataSet* data, RooLinkedList& fitting_args){
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/PlotMass");
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend", "pdfBkgDsDExtend", "pdfSigBsExtend", "pdfBkgExtend";
  std::vector<std::string> components_Dmass;
  components_Dmass += "pdfSigDExtend", "pdfBkgDExtend";
  // RooRealVar  obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");
  RooRealVar  obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
  RooRealVar  obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar  obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooDataSet* reduced_data;
  int nsteps = 10;
  double cutvalue = 0.;
  double sum_of_squared_weights = 0.;
  double num_of_events_in_signal_region = 0.;
  std::vector<double> x_vals;
  std::vector<double> y_vals;
  std::vector<double> y_errors;
  RooFitResult* fit_result;
  RooRealVar* parSigYield;

  for (int i = 0; i < nsteps; ++i) {
    cutvalue = i*1./nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varKminus_PID>"+to_string(cutvalue)+"&&varKplus_PID>"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5240&&"+TString(obsMass.GetName())+"<5320");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parSigYield = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parSigYield"));
    pdf->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/FitResults_Mass_"+to_string(i)+".txt"));
    x_vals += cutvalue;
    y_vals += pow(parSigYield->getVal(),2)/sqrt(num_of_events_in_signal_region);
    y_errors += sqrt(4.*pow(parSigYield->getVal()*parSigYield->getError(),2)/num_of_events_in_signal_region+pow(parSigYield->getVal(),4)/(4.*pow(num_of_events_in_signal_region,2)));
    Plot Mass(cfg_plot_mass, obsMass, *reduced_data, *pdf, components_mass, "obsMass_"+to_string(i));
    Mass.PlotItLogNoLogY();
    // fit_result = pdfD->fitTo(*reduced_data, fitting_args);
    // pdfD->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/FitResults_DMass_"+to_string(i)+".txt"));
    // Plot MassDauOne(cfg_plot_mass, obsMassDauOne, *reduced_data, *pdfD, components_Dmass, "obsMassDauOne_"+to_string(i));
    // MassDauOne.PlotIt();
    // Plot MassDauTwo(cfg_plot_mass, obsMassDauTwo, *reduced_data, RooArgList(), "obsMassDauTwo_"+to_string(i));
    // MassDauTwo.PlotIt();
  }

  pdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  for (int i = 1; i < nsteps; ++i) {
    cutvalue = i*0.4/nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varKminus_PID>"+to_string(cutvalue)+"&&varKplus_PID>"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5240&&"+TString(obsMass.GetName())+"<5320");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parSigYield = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parSigYield"));
    pdf->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/FitResults_Mass_detailed_"+to_string(i)+".txt"));
    x_vals += cutvalue;
    y_vals += pow(parSigYield->getVal(),2)/sqrt(num_of_events_in_signal_region);
    y_errors += sqrt(4.*pow(parSigYield->getVal()*parSigYield->getError(),2)/num_of_events_in_signal_region+pow(parSigYield->getVal(),4)/(4.*pow(num_of_events_in_signal_region,2)));
    Plot Mass(cfg_plot_mass, obsMass, *reduced_data, *pdf, components_mass, "obsMass_detailed_"+to_string(i));
    Mass.PlotIt();
  }

  double gr_x_vals[x_vals.size()];
  double gr_y_vals[x_vals.size()];
  double gr_y_errors[x_vals.size()];
  for (int i = 0; i < x_vals.size(); ++i) {
    gr_x_vals[i] = x_vals.at(i);
    gr_y_vals[i] = y_vals.at(i);
    gr_y_errors[i] = y_errors.at(i);
  }
  TGraphErrors  gr(x_vals.size(),gr_x_vals, gr_y_vals, NULL, gr_y_errors);
  gr.GetXaxis()->SetTitle("cut value");
  gr.GetYaxis()->SetTitle("FOM = S^{2}/#sqrt{S+B}");
  gr.Draw("AP");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/KaonPID.pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}

void PionPID_Optimization(RooAbsPdf* pdf, RooAbsPdf* pdfD, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber){
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory(std::string("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion"+pionnumber+"/PlotMass"));
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend", "pdfBkgDsDExtend", "pdfSigBsExtend", "pdfBkgExtend";
  std::vector<std::string> components_Dmass;
  components_Dmass += "pdfSigDExtend", "pdfBkgDExtend";
  // RooRealVar  obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");
  RooRealVar  obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
  RooRealVar  obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar  obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooDataSet* reduced_data;
  int nsteps = 20;
  double cutvalue = 0.;
  double sum_of_squared_weights = 0.;
  double num_of_events_in_signal_region = 0.;
  std::vector<double> x_vals;
  std::vector<double> y_vals;
  std::vector<double> y_errors;
  RooFitResult* fit_result;
  RooRealVar* parSigYield;
  RooPlot* plot_frame;

  pdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  // c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses.pdf[");
  // c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses_pull.pdf[");
  for (int i = 0; i < nsteps; ++i) {
    cutvalue = 1.-i*1./nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varPi"+pionnumber+"minus_PID<"+to_string(cutvalue)+"&&varPi"+pionnumber+"plus_PID<"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5240&&"+TString(obsMass.GetName())+"<5320");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parSigYield = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parSigYield"));
    pdf->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion"+pionnumber+"/FitResults_Mass_"+to_string(i)+".txt"));
    x_vals += cutvalue;
    y_vals += pow(parSigYield->getVal(),2)/sqrt(num_of_events_in_signal_region);
    y_errors += sqrt(4.*pow(parSigYield->getVal()*parSigYield->getError(),2)/num_of_events_in_signal_region+pow(parSigYield->getVal(),4)/(4.*pow(num_of_events_in_signal_region,2)));
    Plot Mass(cfg_plot_mass, obsMass, *reduced_data, *pdf, components_mass, "obsMass_"+to_string(i));
    Mass.PlotIt();
    // fit_result = pdfD->fitTo(*reduced_data, fitting_args);
    // pdfD->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/FitResults_DMass_"+to_string(i)+".txt"));
    // Plot MassDauOne(cfg_plot_mass, obsMassDauOne, *reduced_data, *pdfD, components_Dmass, "obsMassDauOne_"+to_string(i));
    // MassDauOne.PlotIt();
    // Plot MassDauTwo(cfg_plot_mass, obsMassDauTwo, *reduced_data, RooArgList(), "obsMassDauTwo_"+to_string(i));
    // MassDauTwo.PlotIt();
    // plot_frame = obsMass.frame();
    // reduced_data->plotOn(plot_frame);
    // pdf->plotOn(plot_frame, Components("pdfSigExtend"),  LineColor(214), LineStyle(2));
    // pdf->plotOn(plot_frame, Components("pdfBkgDsDExtend"), LineColor(210), LineStyle(3));
    // pdf->plotOn(plot_frame, Components("pdfSigBsExtend"), LineColor(226), LineStyle(4));
    // pdf->plotOn(plot_frame, Components("pdfBkgExtend"),  LineColor(222), LineStyle(5));
    // pdf->plotOn(plot_frame, LineColor(1));
    // plot_frame->SetMaximum(250.);
    // plot_frame->GetYaxis()->SetTitle((TString::Format("Candidates / ( %1.0f %s )", obsMass.getBinWidth(1), obsMass.getUnit()) ).Data());
    // PlotSimple("PionPIDMasses", plot_frame, *(new TLatex()),"/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass", false);
    // PlotPulls("PionPIDMasses_pull", plot_frame, *(new TLatex()),"/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass", false);
  }
  // c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses.pdf]");
  // c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses_pull.pdf]");

  double gr_x_vals[x_vals.size()];
  double gr_y_vals[x_vals.size()];
  double gr_y_errors[x_vals.size()];
  for (int i = 0; i < x_vals.size(); ++i) {
    gr_x_vals[i] = x_vals.at(i);
    gr_y_vals[i] = y_vals.at(i);
    gr_y_errors[i] = y_errors.at(i);
  }

  TGraphErrors  gr(x_vals.size(),gr_x_vals, gr_y_vals, NULL, gr_y_errors);
  gr.GetXaxis()->SetTitle("cut value");
  gr.GetYaxis()->SetTitle("FOM = S^{2}/#sqrt{S+B}");
  gr.SetFillColor(1);
  gr.SetFillStyle(1001);   // solid
  c.SetFrameFillColor(0);
  c.SetFrameBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetLegendBorderSize(0);

  // set the paper & margin sizes
  gStyle->SetPaperSize(20,26);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05); // increase for colz plots
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.14);

  // use large fonts
  // lhcbStyle->SetTextFont(132);
  // lhcbStyle->SetTextSize(0.06);
  // lhcbStyle->SetLabelFont(132,"x");
  // lhcbStyle->SetLabelFont(132,"y");
  gr.GetXaxis()->SetLabelSize(0.06);
  gr.GetYaxis()->SetLabelSize(0.06);
  // lhcbStyle->SetTitleFont(132);
  // lhcbStyle->SetTitleFont(132,"x");
  // lhcbStyle->SetTitleFont(132,"y");
  // lhcbStyle->SetTitleSize(1.2*0.06,"x");
  // lhcbStyle->SetTitleSize(1.2*0.06,"y");

  // use medium bold lines and thick markers
  // lhcbStyle->SetLineWidth(2.00);

  // lhcbStyle->SetHistLineWidth(2.00);
  // lhcbStyle->SetFuncWidth(2.00);
  // lhcbStyle->SetGridWidth(2.00);
  // lhcbStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  // lhcbStyle->SetMarkerStyle(20);
  // lhcbStyle->SetMarkerSize(1.0);

  // label offsets
  gr.GetXaxis()->SetLabelOffset(0.010);
  gr.GetYaxis()->SetLabelOffset(0.010);

  // by default, do not display histogram decorations:
  // lhcbStyle->SetOptStat(0);
  //lhcbStyle->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  // lhcbStyle->SetStatFormat("6.3g"); // specified as c printf options
  // lhcbStyle->SetOptTitle(0);
  // lhcbStyle->SetOptFit(0);
  //lhcbStyle->SetOptFit(1011); // order is probability, Chi2, errors, parameters
  //titles
  gr.GetXaxis()->SetTitleOffset(0.95);
  gr.GetYaxis()->SetTitleOffset(0.95);
  // lhcbStyle->SetTitleFillColor(0);
  // lhcbStyle->SetTitleStyle(0);
  // lhcbStyle->SetTitleBorderSize(0);
  // lhcbStyle->SetTitleFont(132,"title");
  // lhcbStyle->SetTitleX(0.0);
  // lhcbStyle->SetTitleY(1.0);
  // lhcbStyle->SetTitleW(1.0);
  // lhcbStyle->SetTitleH(0.05);

  // put tick marks on top and RHS of plots
  // lhcbStyle->SetPadTickX(1);
  // lhcbStyle->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  gr.GetXaxis()->SetNdivisions(505);
  gr.GetYaxis()->SetNdivisions(510);

  gROOT->ForceStyle();
  gr.GetYaxis()->SetTitleOffset(0.5);
  gr.Draw("AP");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion"+pionnumber+"/PionPID.pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}

void ElectronPID_Optimization(RooAbsPdf* pdf, RooAbsPdf* pdfD, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber){
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory(std::string("/home/fmeier/storage03/b02dd/run/PID-Optimization/Electron"+pionnumber+"/PlotMass"));
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend", "pdfBkgDsDExtend", "pdfSigBsExtend", "pdfBkgExtend";
  std::vector<std::string> components_Dmass;
  components_Dmass += "pdfSigDExtend", "pdfBkgDExtend";
  // RooRealVar  obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");
  RooRealVar  obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
  RooRealVar  obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar  obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooDataSet* reduced_data;
  int nsteps = 20;
  double cutvalue = 0.;
  double sum_of_squared_weights = 0.;
  double num_of_events_in_signal_region = 0.;
  std::vector<double> x_vals;
  std::vector<double> y_vals;
  std::vector<double> y_errors;
  RooFitResult* fit_result;
  RooRealVar* parSigYield;
  RooPlot* plot_frame;

  pdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  for (int i = 0; i < nsteps; ++i) {
    cutvalue = 1.-i*1./nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65&&varPi"+pionnumber+"minus_PIDe<"+to_string(cutvalue)+"&&varPi"+pionnumber+"plus_PIDe<"+to_string(cutvalue))));
    // reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varPi"+pionnumber+"minus_PIDe<"+to_string(cutvalue)+"&&varPi"+pionnumber+"plus_PIDe<"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5240&&"+TString(obsMass.GetName())+"<5320");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parSigYield = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parSigYield"));
    pdf->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Electron"+pionnumber+"/FitResults_Mass_"+to_string(i)+".txt"));
    x_vals += cutvalue;
    y_vals += pow(parSigYield->getVal(),2)/sqrt(num_of_events_in_signal_region);
    y_errors += sqrt(4.*pow(parSigYield->getVal()*parSigYield->getError(),2)/num_of_events_in_signal_region+pow(parSigYield->getVal(),4)/(4.*pow(num_of_events_in_signal_region,2)));
    Plot Mass(cfg_plot_mass, obsMass, *reduced_data, *pdf, components_mass, "obsMass_"+to_string(i));
    Mass.PlotIt();
    // fit_result = pdfD->fitTo(*reduced_data, fitting_args);
    // pdfD->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Electron"+pionnumber+"/FitResults_DMass_"+to_string(i)+".txt"));
    // Plot MassDauOne(cfg_plot_mass, obsMassDauOne, *reduced_data, *pdfD, components_Dmass, "obsMassDauOne_"+to_string(i));
    // MassDauOne.PlotIt();
  }

  double gr_x_vals[x_vals.size()];
  double gr_y_vals[x_vals.size()];
  double gr_y_errors[x_vals.size()];
  for (int i = 0; i < x_vals.size(); ++i) {
    gr_x_vals[i] = x_vals.at(i);
    gr_y_vals[i] = y_vals.at(i);
    gr_y_errors[i] = y_errors.at(i);
  }

  TGraphErrors  gr(x_vals.size(),gr_x_vals, gr_y_vals, NULL, gr_y_errors);
  gr.GetXaxis()->SetTitle("cut value");
  gr.GetYaxis()->SetTitle("FOM = S^{2}/#sqrt{S+B}");
  gr.Draw("AP");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/Electron"+pionnumber+"/ElectronPID.pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}
