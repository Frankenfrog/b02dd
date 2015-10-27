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
#include "Urania/RooIpatia2.h"
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

int main(int argc, char * argv[]){

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5000,5350,"MeV/c^{2}");

  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);
  
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",1);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);
  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("Signal",0);
  catBkg.defineType("QuasiSignal",10);
  catBkg.defineType("FullyRecoPhysBkg",20);
  catBkg.defineType("LowMassBkg",50);
  catBkg.defineType("Ghost",60);

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         variables(varBDT,"variables");
  RooArgSet         realvars(observables,variables,"realvars");
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,/*catBkg,*/"categories");
  
  // Get data set
  EasyTuple         tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/MC/Sim08/2012/MC_Sim08a_2012_Pythia8_B02DsD_Stripping20_DVv36r5_20150428_pseyfert_20150430_fmeier_BDT_TupleB.root","B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(varBDT.GetName())+">-0.784"));
  
  data.Print();

  // Mass PDF
  RooRealVar        parDsDMassMean("parDsDMassMean","Mean Mass",5280,5270,5290,"MeV/c^{2}");

  RooRealVar        parDsDMassSigma1("parDsDMassSigma1","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parDsDMassCB1Expo("parDsDMassCB1Expo","parDsDMassCB1Expo",10,1,100);
  RooRealVar        parDsDMassCB1Alpha("parDsDMassCB1Alpha","parDsDMassCB1Alpha",1,0.5,2);
  RooCBShape        pdfDsDMassCB1("pdfDsDMassCB1","Mass PDF",obsMass,parDsDMassMean,parDsDMassSigma1,parDsDMassCB1Alpha,parDsDMassCB1Expo);

  RooRealVar        parDsDMassSigma2("parDsDMassSigma2","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parDsDMassCB2Expo("parDsDMassCB2Expo","parDsDMassCB2Expo",10,1,100);
  RooRealVar        parDsDMassCB2Alpha("parDsDMassCB2Alpha","parDsDMassCB2Alpha",-1,-2,-0.5);
  RooCBShape        pdfDsDMassCB2("pdfDsDMassCB2","Mass PDF",obsMass,parDsDMassMean,parDsDMassSigma2,parDsDMassCB2Alpha,parDsDMassCB2Expo);

  RooRealVar        parDsDMassCBFraction("parDsDMassCBFraction","parDsDMassCBFraction",0.5);
  RooAddPdf         pdfDsDMass("pdfDsDMass","pdfDsDMass",RooArgList(pdfDsDMassCB1,pdfDsDMassCB2),parDsDMassCBFraction);

  RooRealVar        parDsDMassL("parDsDMassL","parDsDMassL",-3,-6,-1);
  RooRealVar        parDsDMassZeta("parDsDMassZeta","parDsDMassZeta",0);
  RooRealVar        parDsDMassBeta("parDsDMassBeta","parDsDMassBeta",0,-0.1,0.1);
  RooRealVar        parDsDMassSigma("parDsDMassSigma","parDsDMassSigma",9.0,5,15,"MeV/c^{2}");
  RooRealVar        parDsDMassAlpha1("parDsDMassAlpha1","parDsDMassAlpha1",1.5, 1, 2);
  RooRealVar        parDsDMassn1("parDsDMassn1","parDsDMassn1",10);
  RooRealVar        parDsDMassAlpha2("parDsDMassAlpha2","parDsDMassAlpha2",1.4, 0.5, 2);
  RooRealVar        parDsDMassn2("parDsDMassn2","parDsDMassn2",10);
  // RooIpatia2        pdfDsDMass("pdfDsDMass","pdfDsDMass",obsMass,parDsDMassL,parDsDMassZeta,parDsDMassBeta,parDsDMassSigma,parDsDMassMean,parDsDMassAlpha1,parDsDMassn1,parDsDMassAlpha2,parDsDMassn2);

  RooRealVar        parDsDYield("parDsDYield","parDsDYield",500,0,1000);
  RooExtendPdf      pdfDsDExtend("pdfDsDExtend","pdfDsDExtend",pdfDsDMass,parDsDYield);

  // Get Starting Values and Fit PDF to data
  pdfDsDExtend.Print();
  pdfDsDExtend.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_MC_Mass.txt");
  pdfDsDExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/StartingValues_MC_Mass.new");
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

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/MC/PlotMass");
  std::vector<std::string> components_mass;
  components_mass += "pdfDsDMassCB1", "pdfDsDMassCB2";

  RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65"));
  optimized_data->Print();
  RooFitResult* fit_result = pdfDsDExtend.fitTo(*optimized_data, fitting_args);
  pdfDsDExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/FitResults_DsDMass.txt");
  Plot Mass(cfg_plot_mass, obsMass, *optimized_data, pdfDsDExtend, components_mass, "DsDMass");
  Mass.set_scaletype_x(kLinear);
  Mass.set_scaletype_y(kBoth);
  Mass.PlotIt();

  return 0;
}