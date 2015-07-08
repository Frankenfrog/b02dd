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
#include "doofit/fitter/splot/SPlotFit2.h"

// from DooSelection
#include "dooselection/reducer/SPlotterReducer.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;
using namespace doofit::fitter::splot;

int main(int argc, char * argv[]){

  if (argc != 3){
    doocore::io::serr << "-ERROR- \t" << "Bs2DsDMCMassFit \t" << "Parameters needed:" << doocore::io::endmsg;
    doocore::io::serr << "-ERROR- \t" << "Bs2DsDMCMassFit \t"<< "input_file_name input_tree_name" << doocore::io::endmsg;
    return 1;
  }

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5200,5400,"MeV/c^{2}");
  
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);

  RooRealVar        varKminus_PID("varKminus_PID","varKminus_PID",0,1);
  RooRealVar        varKplus_PID("varKplus_PID","varKplus_PID",0,1);
  RooRealVar        varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID",0,1);
  RooRealVar        varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID",0,1);
  RooRealVar        varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID",0,1);
  RooRealVar        varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID",0,1);

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         varPIDs(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID,"varPIDs");
  observables.add(varPIDs);
  RooArgSet         categories(catDDFinalState/*,catTriggerSetTopo234BodyBBDT*/,"categories");
  
  // Get data set
  EasyTuple         tuple(argv[1],argv[2],RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet();
  
  data.Print();

  // Mass PDF
  RooRealVar        parMassMean("parMassMean","Bs2DsD Mean Mass",5280,5270,5290,"MeV/c^{2}");

  RooRealVar        parMassSigma1("parMassSigma1","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  RooRealVar        parMassCB1Expo("parMassCB1Expo","parMassCB1Expo",10);
  RooRealVar        parMassCB1Alpha("parMassCB1Alpha","parMassCB1Alpha",1.28);
  RooCBShape        pdfMassCB1("pdfMassCB1","Mass PDF 1",obsMass,parMassMean,parMassSigma1,parMassCB1Alpha,parMassCB1Expo);

  RooRealVar        parMassSigma2("parMassSigma2","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooRealVar        parMassCB2Expo("parMassCB2Expo","parMassCB2Expo",10);
  RooRealVar        parMassCB2Alpha("parMassCB2Alpha","parMassCB2Alpha",-1.32);
  RooCBShape        pdfMassCB2("pdfMassCB2","Mass PDF 2",obsMass,parMassMean,parMassSigma2,parMassCB2Alpha,parMassCB2Expo);

  RooRealVar        parMassCBFraction("parMassCBFraction","parMassCBFraction",0.5,0,1);
  RooAddPdf         pdfMass("pdfMass","pdfMass",RooArgList(pdfMassCB1,pdfMassCB2),parMassCBFraction);

  // Get Starting Values and Fit PDF to data
  pdfMass.Print();
  pdfMass.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Bs2DsDMass.txt");
  pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/StartingValues_Bs2DsDMass.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(4))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  RooFitResult* fit_result = pdfMass.fitTo(data, fitting_args);
  pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Bs2DsDMass.txt");
  doofit::plotting::fitresult::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/Mass/Plots");
  Plot Mass(cfg_plot_mass, obsMass, data, pdfMass, "Bs2DsDMass");
  Mass.PlotIt();

  return 0;
}
