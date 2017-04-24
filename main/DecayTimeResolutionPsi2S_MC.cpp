#include <iostream>
#include <sstream>
#include <chrono>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TAxis.h"

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
#include "RooList.h"
#include "RooCurve.h"
#include "RooNumIntConfig.h"

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
#include "doofit/roofit/functions/LinearFunctionWithOffset.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"

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

  RooRealVar        obsTimeErr_True("obsTimeErr_True","#it{t-t}_{true}",-40,40,"ps");
  RooRealVar        obsTimeErr("obsTimeErr","#sigma_{t}",0.0001,0.2,"ps");
  
  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("signal",0);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("best PV",0);
  
  RooArgSet         observables(obsTimeErr_True,"observables");
  if (pereventresolution) observables.add(obsTimeErr);
  
  RooArgSet         categories(catBkg,idxPV,"categories");
  
  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"Bd2psi2SmumuKS",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet*       data = &(tuple.ConvertToDataSet());
  data->Print();

//=========================================================================================================================================================================================================================

  // Resolution model
  RooRealVar                parResMean("parResMean","parResMean",-0.0032);
  RooRealVar                parResCorrectionOffset1("parResCorrectionOffset1","Offset of linear decay time error correction",0.);
  RooRealVar                parResCorrectionOffset2("parResCorrectionOffset2","Offset of linear decay time error correction",0.);
  RooRealVar                parResCorrectionOffset3("parResCorrectionOffset3","Offset of linear decay time error correction",0.);
  RooRealVar                parResCorrectionOffset4("parResCorrectionOffset4","Offset of linear decay time error correction",0.);
  RooRealVar                parResSigmaCorrectionFactor1("parResSigmaCorrectionFactor1","Correctionfactor of Proper Time Errors 1",1.);
  RooRealVar                parResSigmaCorrectionFactor2("parResSigmaCorrectionFactor2","Correctionfactor of Proper Time Errors 2",1.);
  RooRealVar                parResSigmaCorrectionFactor3("parResSigmaCorrectionFactor3","Correctionfactor of Proper Time Errors 3",1.);
  RooRealVar                parResSigmaCorrectionFactor4("parResSigmaCorrectionFactor4","Correctionfactor of Proper Time Errors 4",1.);
  LinearFunctionWithOffset  parResSigmaCorrection1("parResSigmaCorrection1",obsTimeErr,parResSigmaCorrectionFactor1,parResCorrectionOffset1);
  LinearFunctionWithOffset  parResSigmaCorrection2("parResSigmaCorrection2",obsTimeErr,parResSigmaCorrectionFactor2,parResCorrectionOffset2);
  LinearFunctionWithOffset  parResSigmaCorrection3("parResSigmaCorrection3",obsTimeErr,parResSigmaCorrectionFactor3,parResCorrectionOffset3);
  LinearFunctionWithOffset  parResSigmaCorrection4("parResSigmaCorrection4",obsTimeErr,parResSigmaCorrectionFactor4,parResCorrectionOffset4);
  RooGaussian               respereventGauss1("respereventGauss1","per event resolution model 1",obsTimeErr_True,parResMean,parResSigmaCorrection1);
  RooGaussian               respereventGauss2("respereventGauss2","per event resolution model 2",obsTimeErr_True,parResMean,parResSigmaCorrection2);
  RooGaussian               respereventGauss3("respereventGauss3","per event resolution model 3",obsTimeErr_True,parResMean,parResSigmaCorrection3);
  RooGaussian               respereventGauss4("respereventGauss4","per event resolution model 4",obsTimeErr_True,parResMean,parResSigmaCorrection4);
  RooRealVar                parResSigma_wrongPV("parResSigma_wrongPV","Width of wrong PV component",1,0,5);
  RooGaussian               pdfGauss_wrongPV("pdfGauss_wrongPV","wrong PV resolution model",obsTimeErr_True,parResMean,parResSigma_wrongPV);
  RooRealVar                parResFraction2("parResFraction2","Fraction of second per event Gauss model",0.5);
  RooRealVar                parResFraction3("parResFraction3","Fraction of third per event Gauss model",0.5);
  RooRealVar                parResFraction4("parResFraction4","Fraction of fourth per event Gauss model",0.5);
  RooRealVar                parResFraction_wrongPV("parResFraction_wrongPV","Fraction of wrong PV Gauss model",0.1);
  RooAbsPdf*                pdf;
  if (config.getString("order") == "single") pdf = new RooAddPdf("pdf","pdf",RooArgList(pdfGauss_wrongPV,respereventGauss1),RooArgList(parResFraction_wrongPV));
  else if (config.getString("order") == "double") pdf = new RooAddPdf("pdf","pdf",RooArgList(pdfGauss_wrongPV,respereventGauss2,respereventGauss1),RooArgList(parResFraction_wrongPV,parResFraction2));
  else if (config.getString("order") == "triple") pdf = new RooAddPdf("pdf","pdf",RooArgList(pdfGauss_wrongPV,respereventGauss3,respereventGauss2,respereventGauss1),RooArgList(parResFraction_wrongPV,parResFraction3,parResFraction2));
  else if (config.getString("order") == "four") pdf = new RooAddPdf("pdf","pdf",RooArgList(pdfGauss_wrongPV,respereventGauss4,respereventGauss3,respereventGauss2,respereventGauss1),RooArgList(parResFraction_wrongPV,parResFraction4,parResFraction3,parResFraction2));
  
//========================================================================================================================================================================================================================

  // Get Starting Values and Fit PDF to data
  pdf->getParameters(*data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/run/MC/StartingValues_MC_Resolution_Psi2S.txt");
  pdf->Print();
  
  // Fit PDF to data
  pdf->getParameters(*data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/MC/StartingValues.new");
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

  // RooFitResult* fit_result = pdf->fitTo(*data,fitting_args);
  // pdf->getParameters(*data)->writeToFile(TString("/home/fmeier/lhcb-tank/b02dd/run/MC/FitResults_Resolution_Psi2S_"+config.getString("resolutionmodelname")+".txt"));
  // fit_result->Print("v");
  // doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
  // fitresultprinter.Print();
  // fit_result->correlationMatrix().Print();
  // TFile   fitresultwritetofile(TString("/home/fmeier/lhcb-tank/b02dd/run/MC/FitResults_Resolution_Psi2S_"+config.getString("resolutionmodelname")+".root"),"recreate");
  // fit_result->Write("fit_result");
  // fitresultwritetofile.Close();

  const int entriesintree = data->numEntries();
  double Dilution = 0., proptimeerror = 0.;
  for (auto i = 0; i < entriesintree; i++) {
    data->get(i);
    proptimeerror = data->get()->getRealValue("obsTimeErr");
    Dilution+=parResFraction_wrongPV.getVal()*exp(-pow(0.510*parResSigma_wrongPV.getVal(),2)/2);
    Dilution+=parResFraction2.getVal()*exp(-pow(0.510*(parResCorrectionOffset2.getVal() + parResSigmaCorrectionFactor2.getVal()*proptimeerror),2)/2);
    Dilution+=(1 - parResFraction_wrongPV.getVal() - parResFraction2.getVal())*exp(-pow(0.510*(parResCorrectionOffset1.getVal() + parResSigmaCorrectionFactor1.getVal()*proptimeerror),2)/2);
  }
  cout << Dilution/entriesintree  <<  endl;

  // Plots
  pdf->getParameters(*data)->readFromFile(TString("/home/fmeier/lhcb-tank/b02dd/run/MC/FitResults_Resolution_Psi2S_"+config.getString("resolutionmodelname")+".txt"));

  obsTimeErr_True.setRange("small_range",-2,2);
  obsTimeErr_True.setRange("large_range",-40,40);
  obsTimeErr_True.setBins(100);
  PlotConfig cfg_plot_time("cfg_plot_time");
  cfg_plot_time.set_plot_appendix("large_range");
  cfg_plot_time.set_plot_directory("/home/fmeier/lhcb-tank/b02dd/run/MC/PlotResolution_Psi2S");
  cfg_plot_time.set_label_text("MC");
  std::vector<std::string> components_time;
  components_time += "pdfGauss_wrongPV", "respereventGauss1", "respereventGauss2", "respereventGauss3", "respereventGauss4";
  Plot Time(cfg_plot_time, obsTimeErr_True, *data, *pdf, components_time);
  RooArgSet projargset(obsTimeErr);
  Time.AddPlotArg(NumCPU(1));
  Time.AddPlotArg(ProjWData(projargset,*data,true));
  Time.set_scaletype_x(kLinear);
  Time.set_scaletype_y(kBoth);
  Time.set_plot_range("large_range");
  // Time.PlotIt();
  
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TString rangeName = "large_range";

  int nbins = 100;
  int nsteps = 100;
  double min = obsTimeErr_True.getBinning(rangeName).binLow(1);
  double max = obsTimeErr_True.getBinning(rangeName).binHigh(nbins);
  double increment = (max - min)/nsteps;
  double width = (max - min)/nbins;
  RooPlot* plot_frame = obsTimeErr_True.frame(min,max);
  data->plotOn(plot_frame);

  RooArgSet norm_set(*(pdf->getObservables(*data)),"norm_set");
  norm_set.Print();
  RooArgSet int_set(*(pdf->getObservables(*data)),"int_set");
  int_set.remove(obsTimeErr_True,true,true);
  int_set.Print();

  RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-3);
  RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-3);
  // RooMsgService::instance().addStream(DEBUG,Topic(Integration));

  RooAbsReal* integral = pdf->createIntegral(int_set, RooFit::NormSet(norm_set), Range(rangeName));
  RooAbsReal* norm_integral = pdf->createIntegral(norm_set, RooFit::NormSet(norm_set), Range(rangeName));
  integral->Print("v");
  norm_integral->Print("v");
  sinfo << integral->getVal() << " " << norm_integral->getVal() << endmsg;

  RooAbsReal* integral_Gauss1 = respereventGauss1.createIntegral(int_set, RooFit::NormSet(norm_set), Range(rangeName));
  RooAbsReal* norm_integral_Gauss1 = respereventGauss1.createIntegral(norm_set, RooFit::NormSet(norm_set), Range(rangeName));
  sinfo << integral_Gauss1->getVal() << " " << norm_integral_Gauss1->getVal() << endmsg;

  RooAbsReal* integral_Gauss2 = respereventGauss2.createIntegral(int_set, RooFit::NormSet(norm_set), Range(rangeName));
  RooAbsReal* norm_integral_Gauss2 = respereventGauss2.createIntegral(norm_set, RooFit::NormSet(norm_set), Range(rangeName));
  sinfo << integral_Gauss2->getVal() << " " << norm_integral_Gauss2->getVal() << endmsg;

  RooAbsReal* integral_Gauss3 = respereventGauss3.createIntegral(int_set, RooFit::NormSet(norm_set), Range(rangeName));
  RooAbsReal* norm_integral_Gauss3 = respereventGauss3.createIntegral(norm_set, RooFit::NormSet(norm_set), Range(rangeName));
  sinfo << integral_Gauss3->getVal() << " " << norm_integral_Gauss3->getVal() << endmsg;

  RooAbsReal* integral_wPV = pdfGauss_wrongPV.createIntegral(obsTimeErr_True, Range(rangeName));
  sinfo << integral_wPV->getVal() << " " << pdfGauss_wrongPV.getVal() <<  endmsg;

  double total = 0;
  double value = 0;
  double value_direct = 0;
  double value_Gauss1 = 0;
  double value_Gauss2 = 0;
  double value_wPV = 0;
  double obs_value = min+0.5*increment;

  std::vector<double> x_vals(nsteps, 0);
  std::vector<double> y_vals(nsteps, 0);
  std::vector<double> y_vals_direct(nsteps, 0);
  std::vector<double> y_vals_Gauss1(nsteps, 0);
  std::vector<double> y_vals_Gauss2(nsteps, 0);
  std::vector<double> y_vals_wPV(nsteps, 0);
  for (int i = 0; i < nsteps; i++){
    obsTimeErr_True.setVal(obs_value);
    std::chrono::high_resolution_clock::time_point time_start(std::chrono::high_resolution_clock::now());
    value_direct = integral->getVal() * entriesintree * width;
    value_Gauss1 = integral_Gauss1->getVal() * entriesintree * width * (1. - parResFraction2.getVal() - parResFraction_wrongPV.getVal());
    value_Gauss2 = integral_Gauss2->getVal() * entriesintree * width * parResFraction2.getVal();
    // value_wPV    = integral_Gauss3->getVal() * entriesintree * width * parResFraction_wrongPV.getVal();
    value_wPV = pdfGauss_wrongPV.getVal()/integral_wPV->getVal() * entriesintree * width * parResFraction_wrongPV.getVal();
    value = value_Gauss1 + value_Gauss2 + value_wPV;
    // sinfo << obs_value << " " << pdfGauss_wrongPV.getVal() << " " << integral_wPV->getVal() << endmsg;
    // sinfo << obs_value << " " << value_wPV <<  endmsg;
    std::chrono::high_resolution_clock::time_point time_stop(std::chrono::high_resolution_clock::now());
    x_vals.at(i) = obs_value;
    y_vals.at(i) = value;
    y_vals_direct.at(i) = value_direct;
    y_vals_Gauss1.at(i) = value_Gauss1;
    y_vals_Gauss2.at(i) = value_Gauss2;
    y_vals_wPV.at(i) = value_wPV;
    double duration(std::chrono::duration_cast<std::chrono::microseconds>(time_stop - time_start).count());
    total += duration;
    // sdebug << "duration = " << duration*1e-3 << "ms" << endmsg;
    obs_value += increment;
  }
  sdebug << "total duration = " << total*1e-3 << "ms" << endmsg;
  sdebug << "total duration/per integral = " << total*1e-3/nsteps << "ms" << endmsg;

  TGraph* graph = new TGraph(x_vals.size(), &x_vals[0], &y_vals[0]);
  TGraph* graph_direct = new TGraph(x_vals.size(), &x_vals[0], &y_vals_direct[0]);
  TGraph* graph_Gauss1 = new TGraph(x_vals.size(), &x_vals[0], &y_vals_Gauss1[0]);
  TGraph* graph_Gauss2 = new TGraph(x_vals.size(), &x_vals[0], &y_vals_Gauss2[0]);
  TGraph* graph_wPV = new TGraph(x_vals.size(), &x_vals[0], &y_vals_wPV[0]);

  RooList*  Gauss1_curve_list = new RooList();
  Gauss1_curve_list->Add(graph_Gauss1);
  RooCurve* Gauss1_curve = new RooCurve();
  Gauss1_curve->Merge(Gauss1_curve_list);
  Gauss1_curve->SetLineColor(214);
  Gauss1_curve->SetLineStyle(2);
  plot_frame->addPlotable(Gauss1_curve, "same");

  RooList*  Gauss2_curve_list = new RooList();
  Gauss2_curve_list->Add(graph_Gauss2);
  RooCurve* Gauss2_curve = new RooCurve();
  Gauss2_curve->Merge(Gauss2_curve_list);
  Gauss2_curve->SetLineColor(210);
  Gauss2_curve->SetLineStyle(3);
  plot_frame->addPlotable(Gauss2_curve, "same");

  RooList*  wPV_curve_list = new RooList();
  wPV_curve_list->Add(graph_wPV);
  RooCurve* wPV_curve = new RooCurve();
  wPV_curve->Merge(wPV_curve_list);
  wPV_curve->SetLineColor(226);
  wPV_curve->SetLineStyle(4);
  plot_frame->addPlotable(wPV_curve, "same");

  RooList*  curve_list = new RooList();
  curve_list->Add(graph);
  RooCurve* curve = new RooCurve();
  curve->Merge(curve_list);
  curve->SetLineColor(1);
  plot_frame->addPlotable(curve, "same");

  // RooList*  curve_list_direct = new RooList();
  // curve_list_direct->Add(graph_direct);
  // RooCurve* curve_direct = new RooCurve();
  // curve_direct->Merge(curve_list_direct);
  // curve_direct->SetLineColor(222);
  // plot_frame->addPlotable(curve_direct, "same");

  plot_frame->SetMinimum(0.5);
  plot_frame->SetMaximum(1e6);
  TString ylabel = plot_frame->GetYaxis()->GetTitle();
  ylabel.ReplaceAll("Events","Candidates");
  plot_frame->GetYaxis()->SetTitle(ylabel);

  TLatex label(0.25,0.8,"MC");
  PlotSimple("TimeErr_True",plot_frame,label,"/home/fmeier/lhcb-tank/b02dd/run/MC/PlotResolution_Psi2S",false);
  PlotPulls("TimeErr_True_Pulls",plot_frame,label,"/home/fmeier/lhcb-tank/b02dd/run/MC/PlotResolution_Psi2S",true);

  return 0;
}
