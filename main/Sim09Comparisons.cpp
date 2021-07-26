#include <iostream>
#include <sstream>
#include <algorithm>

// ROOT
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TString.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TF1.h"

// RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooCategory.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooFormulaVar.h"

// RooFit PDFs
#include "RooCBShape.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"

#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/config/EasyConfig.h"
#include "doocore/io/Progress.h"

// DooCore
#include "doocore/lutils/lutils.h"

// DooFit
#include "doofit/fitter/easyfit/FitResultPrinter.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace std;
using namespace RooFit;
using namespace doocore::io;
using namespace doocore::lutils;

void CreateComparisonHistogram(TTree& tree_Sim08, TTree& tree_Sim09, TString pdf_name, int nbins, TString obs_name, TString title, double min, double max);

int main(int argc, const char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5200,5400,"MeV/c^{2}");
  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsTimeResolution("obsTimeErr_True","obsTimeErr_True",-0.5,0.5,"ps");
  
  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("signal",0);
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("bestPV",0);

  RooArgSet         observables(obsMass,obsTimeResolution,obsMassDauOne,obsMassDauTwo,"observables");
  RooArgSet         categories(catBkg,catDDFinalState,idxPV,"categories");

  EasyTuple         Sim08_tuple(config.getString("Sim08_tuple"),"B02DD",RooArgSet(observables,categories));
  Sim08_tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       Sim08_data = Sim08_tuple.ConvertToDataSet();
  Sim08_data.Print();

  EasyTuple         Sim09_tuple(config.getString("Sim09_tuple"),"B02DD",RooArgSet(observables,categories));
  Sim09_tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       Sim09_data = Sim09_tuple.ConvertToDataSet();
  Sim09_data.Print();

  // Mass PDF
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");

  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",7.0,1.0,20.0,"MeV/c^{2}");
  RooRealVar        parSigMassCB1Expo("parSigMassCB1Expo","parSigMassCB1Expo",10);
  RooRealVar        parSigMassCB1Alpha("parSigMassCB1Alpha","parSigMassCB1Alpha",1,0.5,2);
  RooCBShape        pdfSigMassCB1("pdfSigMassCB1","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);

  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",7.0,5.0,20.0,"MeV/c^{2}");
  RooRealVar        parSigMassCB2Expo("parSigMassCB2Expo","parSigMassCB2Expo",10);
  RooRealVar        parSigMassCB2Alpha("parSigMassCB2Alpha","parSigMassCB2Alpha",-1,-2,-0.5);
  RooCBShape        pdfSigMassCB2("pdfSigMassCB2","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);

  RooRealVar        parSigMassCBFraction("parSigMassCBFraction","parSigMassCBFraction",0.5);
  RooAddPdf         pdfSigMass("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB2),parSigMassCBFraction);

  RooRealVar        parSigDMassMean("parSigDMassMean","Bd Mean Mass",1870,1860,1880,"MeV/c^{2}");
  RooRealVar        parSigDMassSigma1("parSigDMassSigma1","Sigma of Gaussian Mass",7.0,1.0,10.0,"MeV/c^{2}");
  RooGaussian       pdfSigDMass1("pdfSigDMass1","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma1);

  RooRealVar        parSigDMassSigma2("parSigDMassSigma2","Sigma of Gaussian Mass",12,8,20.0,"MeV/c^{2}");
  RooGaussian       pdfSigDMass2("pdfSigDMass2","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma2);
  
  RooRealVar        parSigDMassFraction("parSigDMassFraction","parSigDMassFraction",0.5);
  RooAddPdf         pdfSigDMass("pdfSigDMass","pdfSigDMass",RooArgList(pdfSigDMass1,pdfSigDMass2),parSigDMassFraction);

  RooFormulaVar     B0MassResolution("B0MassResolution","B0MassResolution","sqrt(0.5*@0*@0+0.5*@1*@1)",RooArgList(parSigMassSigma1,parSigMassSigma2));
  RooFormulaVar     DMassResolution("DMassResolution","DMassResolution","sqrt(0.5*@0*@0+0.5*@1*@1)",RooArgList(parSigDMassSigma1,parSigDMassSigma2));

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

  RooFitResult* fit_result_Sim08 = pdfSigMass.fitTo(Sim08_data, fitting_args);
  pdfSigMass.getParameters(Sim08_data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_Mass_Sim08.txt");
  cout << "B0 Mass resolution Sim08: "  <<  B0MassResolution.getVal() <<  " pm "  <<  B0MassResolution.getPropagatedError(*fit_result_Sim08)  <<  endl;

  RooFitResult* fit_result_Sim09 = pdfSigMass.fitTo(Sim09_data, fitting_args);
  pdfSigMass.getParameters(Sim09_data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_Mass_Sim09.txt");
  cout << "B0 Mass resolution Sim09: "  <<  B0MassResolution.getVal() <<  " pm "  <<  B0MassResolution.getPropagatedError(*fit_result_Sim09)  <<  endl;

  doofit::fitter::easyfit::FitResultPrinter fitresultprinter_Sim08(*fit_result_Sim08);
  fitresultprinter_Sim08.Print();
  doofit::fitter::easyfit::FitResultPrinter fitresultprinter_Sim09(*fit_result_Sim09);
  fitresultprinter_Sim09.Print();

  fit_result_Sim08 = pdfSigDMass.fitTo(Sim08_data, fitting_args);
  pdfSigDMass.getParameters(Sim08_data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_DMass_Sim08.txt");
  cout << "D Mass resolution Sim08: "  <<  DMassResolution.getVal() <<  " pm "  <<  DMassResolution.getPropagatedError(*fit_result_Sim08)  <<  endl;

  fit_result_Sim09 = pdfSigDMass.fitTo(Sim09_data, fitting_args);
  pdfSigDMass.getParameters(Sim09_data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_DMass_Sim09.txt");
  cout << "D Mass resolution Sim09: "  <<  DMassResolution.getVal() <<  " pm "  <<  DMassResolution.getPropagatedError(*fit_result_Sim09)  <<  endl;

  doofit::fitter::easyfit::FitResultPrinter fitresultprinter_Sim08_DMass(*fit_result_Sim08);
  fitresultprinter_Sim08_DMass.Print();
  doofit::fitter::easyfit::FitResultPrinter fitresultprinter_Sim09_DMass(*fit_result_Sim09);
  fitresultprinter_Sim09_DMass.Print();

  gROOT->SetStyle("Plain");
  doocore::lutils::setStyle("LHCb");
  TCanvas c("c","c",800,600);
  RooPlot* plot = obsMass.frame();
  Sim08_data.plotOn(plot, MarkerColor(1), Rescale(1./Sim08_data.numEntries()));
  pdfSigMass.getParameters(Sim08_data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_Mass_Sim08.txt");
  pdfSigMass.plotOn(plot, LineColor(1), Normalization(1./Sim08_data.numEntries()));
  Sim09_data.plotOn(plot, MarkerColor(4), Rescale(1./Sim09_data.numEntries()));
  pdfSigMass.getParameters(Sim09_data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_Mass_Sim09.txt");
  pdfSigMass.plotOn(plot, LineColor(4), Normalization(1./Sim09_data.numEntries()));
  plot->SetMaximum(0.1);
  plot->GetYaxis()->SetTitle("Arbitrary units");
  plot->Draw();
  printPlot(&c, "B0Mass", "/home/fmeier/lhcb-tank/b02dd/run/MCComparison/PlotMass");

  plot = obsMassDauOne.frame();
  Sim08_data.plotOn(plot, MarkerColor(1), Rescale(1./Sim08_data.numEntries()));
  pdfSigDMass.getParameters(Sim08_data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_DMass_Sim08.txt");
  pdfSigDMass.plotOn(plot, LineColor(1), Normalization(1./Sim08_data.numEntries()));
  Sim09_data.plotOn(plot, MarkerColor(4), Rescale(1./Sim09_data.numEntries()));
  pdfSigDMass.getParameters(Sim09_data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/run/MCComparison/FitResults_DMass_Sim09.txt");
  pdfSigDMass.plotOn(plot, LineColor(4), Normalization(1./Sim09_data.numEntries()));
  plot->SetMaximum(0.04);
  plot->GetYaxis()->SetTitle("Arbitrary units");
  gStyle->SetLabelOffset(1.5,"y");
  plot->Draw();
  printPlot(&c, "DMass", "/home/fmeier/lhcb-tank/b02dd/run/MCComparison/PlotMass");

  return 0;
}