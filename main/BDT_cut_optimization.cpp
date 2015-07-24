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

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooBDecay.h"
#include "RooDecay.h"
#include "RooExponential.h"
#include "RooLognormal.h"
#include "RooGaussian.h"

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

// from DooFit
#include "Urania/RooIpatia2.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;

void PlotMass(RooDataSet* data, TString cut);

int main(int argc, char * argv[]){
  
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);

  RooRealVar        obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");

  RooRealVar        BDT1_classifier("BDT1_classifier","BDT1_classifier",-1,1);
  RooRealVar        BDT2_classifier("BDT2_classifier","BDT2_classifier",-1,1);
  RooRealVar        BDTG1_classifier("BDTG1_classifier","BDTG1_classifier",-1,1);
  RooRealVar        BDTG2_classifier("BDTG2_classifier","BDTG2_classifier",-1,1);
  
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
  RooRealVar        varPiOneplus_ProbNNk("Dplus_piplus_or_Kplus_One_ProbNNk","Dplus_piplus_or_Kplus_One_ProbNNk",0,1);
  RooRealVar        varPiOneplus_ProbNNpi("Dplus_piplus_or_Kplus_One_ProbNNpi","Dplus_piplus_or_Kplus_One_ProbNNpi",0,1);
  RooRealVar        varPiTwominus_ProbNNk("Dminus_piminus_or_Kminus_Two_ProbNNk","Dminus_piminus_or_Kminus_Two_ProbNNk",0,1);
  RooRealVar        varPiTwominus_ProbNNpi("Dminus_piminus_or_Kminus_Two_ProbNNpi","Dminus_piminus_or_Kminus_Two_ProbNNpi",0,1);
  RooRealVar        varPiTwoplus_ProbNNk("Dplus_piplus_or_Kplus_Two_ProbNNk","Dplus_piplus_or_Kplus_Two_ProbNNk",0,1);
  RooRealVar        varPiTwoplus_ProbNNpi("Dplus_piplus_or_Kplus_Two_ProbNNpi","Dplus_piplus_or_Kplus_Two_ProbNNpi",0,1);

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         variables(BDT1_classifier,BDT2_classifier,BDTG1_classifier,BDTG2_classifier,"variables");
  RooArgSet         varKaonProbNNs(varKminus_ProbNNk,varKminus_ProbNNpi,varKplus_ProbNNk,varKplus_ProbNNpi,"varKaonProbNNs");
  RooArgSet         varPionProbNNs(varPiOneminus_ProbNNk,varPiOneminus_ProbNNpi,varPiOneplus_ProbNNk,varPiOneplus_ProbNNpi,varPiTwominus_ProbNNk,varPiTwominus_ProbNNpi,varPiTwoplus_ProbNNk,varPiTwoplus_ProbNNpi,"varPionProbNNs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varKaonProbNNs);
  realvars.add(varPionProbNNs);
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,"categories");
  
  // Get data set
  EasyTuple         tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/Combined_2011_2012/DT20112012_B02DD_Stripping21r0r1_DVv36r1_20150322_fmeier_combined_20150412_fmeier_BDT_TupleB_Kpipi.root","B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet();
  
  data.Print();

  RooFormulaVar     varKminus_PID("varKminus_PID","varKminus_PID","@0/(@0+@1)",RooArgList(varKminus_ProbNNk,varKminus_ProbNNpi));
  RooFormulaVar     varKplus_PID("varKplus_PID","varKplus_PID","@0/(@0+@1)",RooArgList(varKplus_ProbNNk,varKplus_ProbNNpi));
  RooFormulaVar     varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID","@0/(@0+@1)",RooArgList(varPiOneminus_ProbNNk,varPiOneminus_ProbNNpi));
  RooFormulaVar     varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID","@0/(@0+@1)",RooArgList(varPiOneplus_ProbNNk,varPiOneplus_ProbNNpi));
  RooFormulaVar     varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID","@0/(@0+@1)",RooArgList(varPiTwominus_ProbNNk,varPiTwominus_ProbNNpi));
  RooFormulaVar     varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID","@0/(@0+@1)",RooArgList(varPiTwoplus_ProbNNk,varPiTwoplus_ProbNNpi));
  RooArgList        PID_formulas(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID);
  data.addColumns(PID_formulas);

  // Mass PDF
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");
  RooRealVar        parSigMassSigma("parSigMassSigma","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooGaussian       pdfSigMass("pdfSigMass","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma);

  RooRealVar        parSigMassMean1("parSigMassMean1","partial reco Mean Mass",5220,5200,5250,"MeV/c^{2}");
  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooGaussian       pdfSigMass1("pdfSigMass1","partial reco Mass PDF",obsMass,parSigMassMean1,parSigMassSigma1);  
  
  RooRealVar        parSigMassMean2("parSigMassMean2","Bs Mean Mass",5360,5340,5390,"MeV/c^{2}");
  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooGaussian       pdfSigMass2("pdfSigMass2","Bs Mass PDF",obsMass,parSigMassMean2,parSigMassSigma2);

  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parSig1Yield("parSig1Yield","parSig1Yield",1000,0,2000);
  RooRealVar        parSig2Yield("parSig2Yield","parSig2Yield",100,0,1000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);
  RooExtendPdf      pdfSig1Extend("pdfSig1Extend","pdfSig1Extend",pdfSigMass1,parSig1Yield);
  RooExtendPdf      pdfSig2Extend("pdfSig2Extend","pdfSig2Extend",pdfSigMass2,parSig2Yield);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfSig1Extend,pdfSig2Extend,pdfBkgExtend));
  
  RooDataSet*       fitdata = dynamic_cast<RooDataSet*>(data.reduce(TString("varKminus_PID>0.2&&varKplus_PID>0.2")));
  fitdata->Print();

  PlotMass(fitdata, "BDT1_classifier>-0.014");
  PlotMass(fitdata, "BDT2_classifier>-0.010");
  PlotMass(fitdata, "BDTG1_classifier>-0.053");
  PlotMass(fitdata, "BDTG2_classifier>-0.039");
  PlotMass(fitdata, "BDT1_classifier>-0.174");
  PlotMass(fitdata, "BDT2_classifier>-0.164");
  PlotMass(fitdata, "BDTG1_classifier>-0.812");
  PlotMass(fitdata, "BDTG2_classifier>-0.784");

  // Get Starting Values and Fit PDF to data
  // pdfMass.Print();
  // pdfMass.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  // pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/StartingValues_Mass.new");
  // RooLinkedList fitting_args;
  // fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(1))));
  // fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  // fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  // fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  // fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  // fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","migrad"))));
  // fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  // fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  // fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));
  // RooFitResult* fit_result = pdfMass.fitTo(*fitdata,fitting_args);
  // TFile   fitresultwritetofile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Mass.root","recreate");
  // fit_result->Write("fit_result");
  // fitresultwritetofile.Close();
  // pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Mass.txt");
  // fit_result->Print("v");
  // fit_result->correlationMatrix().Print();

  // Plots
  pdfMass.getParameters(data)->readFromFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Mass.txt");

  // TFile   fitresultreadinfile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Mass.root","read");
  // RooFitResult* fitresult = dynamic_cast<RooFitResult*>(fitresultreadinfile.Get("fit_result"));
  // fitresultreadinfile.Close();
 
  
  // std::vector<std::string> components_mass;
  // components_mass += "pdfSigExtend", "pdfSig1Extend", "pdfSig2Extend", "pdfBkgExtend";
  // Plot Mass2(cfg_plot_mass, obsMass, *fitdata, pdfMass, components_mass);
  // Mass2.PlotIt();

  // for (int i = 0; i < 10; ++i) {
  //   double cutvalue = 0.1*i;
  //   cfg_plot_mass.set_plot_appendix("_"+to_string(i));
  //   reduced_data = dynamic_cast<RooDataSet*>(data.reduce(TString("varKminus_PID>"+to_string(cutvalue)+"&&varKplus_PID>"+to_string(cutvalue))));
  //   reduced_data->Print();
  //   fit_result = pdfMass.fitTo(*reduced_data,fitting_args);
  //   pdfMass.getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Mass_"+to_string(i)+".txt"));
  //   Plot Mass(cfg_plot_mass, obsMass, *reduced_data, pdfMass, components_mass, "obsMass_"+to_string(i));
  //   // Plot Mass(cfg_plot_mass, obsMass, *reduced_data, RooArgList(), "obsMass_"+to_string(i));
  //   Mass.PlotIt();
  // }
     
  return 0;
}

void PlotMass(RooDataSet* data, TString cut){

  RooRealVar       obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");
  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/Mass/PlotMass");

  RooDataSet* reduced_data = dynamic_cast<RooDataSet*>(data->reduce(cut));
  cout  <<  cut   <<  "\t"  <<  reduced_data->sumEntries("obsMass>5230&&obsMass<5330") <<  endl;
  
  Plot Mass(cfg_plot_mass, obsMass, *reduced_data, RooArgList(), string("obsMass_"+cut));
  Mass.PlotIt();
}