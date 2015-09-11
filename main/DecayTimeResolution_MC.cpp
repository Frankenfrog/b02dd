#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"

//from RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooConstVar.h"
#include "RooBinning.h"

// from RooFit PDFs
#include "RooGaussian.h"
#include "RooSimultaneous.h"
#include "RooAddPdf.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "doofit/roofit/pdfs/BiasDelta.h"
#include "doofit/roofit/functions/LinearFunctionWithOffset.h"
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

void PlotTime(RooDataSet* data, TString cut, RooAbsPdf* pdf, RooArgSet projectionargs, TString category, int num_cpu);

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  bool pereventresolution = config.getBool("pereventresolution");

  RooRealVar        obsTimeErr_True("obsTimeErr_True_ps","#it{t-t}_{true}",-0.4,0.4,"ps");
  RooRealVar        obsTimeErr("obsTimeErr","#sigma_{t}",0.005,0.2,"ps");
  
  RooCategory       catYear("catYear","year of data taking");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  
  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("signal",0);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("best PV",0);
  
  RooArgSet         observables(obsTimeErr_True,"observables");
  if (pereventresolution) observables.add(obsTimeErr);
  
  RooArgSet         categories(catYear,catBkg,idxPV,"categories");
  
  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet*       data = &(tuple.ConvertToDataSet());
  data->Print();

//=========================================================================================================================================================================================================================

  // Resolution model
  RooRealVar                parResMean("parResMean","parResMean",-0.0032);
  RooRealVar                parResCorrectionOffset1("parResCorrectionOffset1","Offset of linear decay time error correction",0.);
  RooRealVar                parResCorrectionOffset2("parResCorrectionOffset2","Offset of linear decay time error correction",0.);
  RooRealVar                parResSigmaCorrectionFactor1("parResSigmaCorrectionFactor1","Correctionfactor of Proper Time Errors 1",1.);
  RooRealVar                parResSigmaCorrectionFactor2("parResSigmaCorrectionFactor2","Correctionfactor of Proper Time Errors 2",1.);
  LinearFunctionWithOffset  parResSigmaCorrection1("parResSigmaCorrection1",obsTimeErr,parResSigmaCorrectionFactor1,parResCorrectionOffset1);
  LinearFunctionWithOffset  parResSigmaCorrection2("parResSigmaCorrection2",obsTimeErr,parResSigmaCorrectionFactor2,parResCorrectionOffset2);
  RooGaussian               respereventGauss1("respereventGauss1","per event resolution model 1",obsTimeErr_True,parResMean,parResSigmaCorrection1);
  RooGaussian               respereventGauss2("respereventGauss2","per event resolution model 2",obsTimeErr_True,parResMean,parResSigmaCorrection2);
  RooRealVar                parResSigma_wrongPV("parResSigma_wrongPV","Width of wrong PV component",1,0,5);
  RooGaussian               pdfGauss_wrongPV("pdfGauss_wrongPV","wrong PV resolution model",obsTimeErr_True,parResMean,parResSigma_wrongPV);
  RooRealVar                parResFraction2("parResFraction2","Fraction of second per event Gauss model",0.5);
  RooRealVar                parResFraction_wrongPV("parResFraction_wrongPV","Fraction of wrong PV Gauss model",0.1);
  RooAddPdf                 pdf("pdf","pdf",RooArgList(pdfGauss_wrongPV,respereventGauss2,respereventGauss1),RooArgList(parResFraction_wrongPV,parResFraction2));
  
//========================================================================================================================================================================================================================
  
  // Build Simultaneous PDF
  // RooSimultaneous   pdf("pdf","P",catYear);
  // pdf.addPdf(*pdfSigTime_11,"2011");
  // pdf.addPdf(*pdfSigTime_12,"2012");

  // cout  <<  "simultaneous PDF built"  <<  endl;

  // Get Starting Values and Fit PDF to data
  pdf.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Time.txt");
  
  // pdf.getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/run/MC/StartingValues.txt");
  pdf.Print();
  
  // Fit PDF to data
  pdf.getParameters(*data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/StartingValues.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
  if (pereventresolution) fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsTimeErr)))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Offset(true))));

  RooFitResult* fit_result = pdf.fitTo(*data,fitting_args);
  pdf.getParameters(*data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/MC/FitResults_Resolution_"+config.getString("resolutionmodelname")+".txt"));
  fit_result->Print("v");
  doofit::plotting::fitresult::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();
  fit_result->correlationMatrix().Print();
  TFile   fitresultwritetofile(TString("/home/fmeier/storage03/b02dd/run/MC/FitResults_Resolution_"+config.getString("resolutionmodelname")+".root"),"recreate");
  fit_result->Write("fit_result");
  fitresultwritetofile.Close();

  int entriesintree = data->numEntries();
  double Dilution = 0., proptimeerror = 0.;
  for (int i = 0; i < entriesintree; i++) {
    data->get(i);
    proptimeerror = data->get()->getRealValue("obsTimeErr");
    Dilution+=parResFraction_wrongPV.getVal()*exp(-pow(0.510*parResSigma_wrongPV.getVal(),2)/2);
    Dilution+=parResFraction2.getVal()*exp(-pow(0.510*(parResCorrectionOffset2.getVal() + parResSigmaCorrectionFactor2.getVal()*proptimeerror),2)/2);
    Dilution+=(1 - parResFraction_wrongPV.getVal() - parResFraction2.getVal())*exp(-pow(0.510*(parResCorrectionOffset1.getVal() + parResSigmaCorrectionFactor1.getVal()*proptimeerror),2)/2);
  }
  cout << Dilution/entriesintree  <<  endl;

  // Plots
  pdf.getParameters(*data)->readFromFile(TString("/home/fmeier/storage03/b02dd/run/MC/FitResults_Resolution_"+config.getString("resolutionmodelname")+".txt"));
 
  PlotConfig cfg_plot_time("cfg_plot_time");
  cfg_plot_time.set_plot_appendix("");
  cfg_plot_time.set_plot_directory("/home/fmeier/storage03/b02dd/run/MC/PlotResolution");
  std::vector<std::string> components_time;
  components_time += "respereventGauss1", "respereventGauss2", "pdfGauss_wrongPV";
  Plot Time(cfg_plot_time, obsTimeErr_True, *data, pdf, components_time);
  RooArgSet projargset(obsTimeErr);
  Time.AddPlotArg(NumCPU(1));
  Time.AddPlotArg(ProjWData(projargset,*data,true));
  Time.PlotItLogNoLogY();
  
  return 0;
}
