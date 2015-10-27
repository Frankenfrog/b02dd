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
#include "doocore/config/EasyConfig.h"

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

void KaonPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString final_state = "Kpipi");
void PionPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber = "One", TString final_state = "Kpipi");
void KKPiPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString particle);
void ElectronPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber = "One");

int main(int argc, char * argv[]){

  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);
  catTriggerSetTopo234BodyBBDT.defineType("not triggered",0);

  RooCategory       catYear("catYear","catYear");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);

  RooRealVar        varKminus_PID("varKminus_PID","varKminus_PID",0,1);
  RooRealVar        varKplus_PID("varKplus_PID","varKplus_PID",0,1);
  RooRealVar        varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID",0,1);
  RooRealVar        varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID",0,1);
  RooRealVar        varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID",0,1);
  RooRealVar        varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID",0,1);

  RooRealVar        varPiOneminus_ProbNNpi("Dminus_piminus_or_Kminus_One_ProbNNpi","Dminus_piminus_or_Kminus_One_ProbNNpi",0,1);
  RooRealVar        varPiOneminus_ProbNNe("Dminus_piminus_or_Kminus_One_ProbNNe","Dminus_piminus_or_Kminus_One_ProbNNe",0,1);
  RooRealVar        varPiOneplus_ProbNNpi("Dplus_piplus_or_Kplus_One_ProbNNpi","Dplus_piplus_or_Kplus_One_ProbNNpi",0,1);
  RooRealVar        varPiOneplus_ProbNNe("Dplus_piplus_or_Kplus_One_ProbNNe","Dplus_piplus_or_Kplus_One_ProbNNe",0,1);
  RooRealVar        varPiTwominus_ProbNNpi("Dminus_piminus_or_Kminus_Two_ProbNNpi","Dminus_piminus_or_Kminus_Two_ProbNNpi",0,1);
  RooRealVar        varPiTwominus_ProbNNe("Dminus_piminus_or_Kminus_Two_ProbNNe","Dminus_piminus_or_Kminus_Two_ProbNNe",0,1);
  RooRealVar        varPiTwoplus_ProbNNpi("Dplus_piplus_or_Kplus_Two_ProbNNpi","Dplus_piplus_or_Kplus_Two_ProbNNpi",0,1);
  RooRealVar        varPiTwoplus_ProbNNe("Dplus_piplus_or_Kplus_Two_ProbNNe","Dplus_piplus_or_Kplus_Two_ProbNNe",0,1);

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         variables(varBDT,"variables");
  RooArgSet         varPIDs(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID,"varKaonProbNNs");
  RooArgSet         varPiOneProbNNs(varPiOneminus_ProbNNpi,varPiOneplus_ProbNNpi,varPiOneminus_ProbNNe,varPiOneplus_ProbNNe,"varPionProbNNs");
  RooArgSet         varPiTwoProbNNs(varPiTwominus_ProbNNpi,varPiTwoplus_ProbNNpi,varPiTwominus_ProbNNe,varPiTwoplus_ProbNNe,"varPiTwoProbNNs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varPIDs);
  realvars.add(varPiOneProbNNs);
  realvars.add(varPiTwoProbNNs);
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,catYear,"categories");
  
  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));
  
  data.Print();
  
  RooFormulaVar     varPiOneminus_PIDe("varPiOneminus_PIDe","varPiOneminus_PIDe","@0/(@0+@1)",RooArgList(varPiOneminus_ProbNNe,varPiOneminus_ProbNNpi));
  RooFormulaVar     varPiOneplus_PIDe("varPiOneplus_PIDe","varPiOneplus_PIDe","@0/(@0+@1)",RooArgList(varPiOneplus_ProbNNe,varPiOneplus_ProbNNpi));
  RooFormulaVar     varPiTwominus_PIDe("varPiTwominus_PIDe","varPiTwominus_PIDe","@0/(@0+@1)",RooArgList(varPiTwominus_ProbNNe,varPiTwominus_ProbNNpi));
  RooFormulaVar     varPiTwoplus_PIDe("varPiTwoplus_PIDe","varPiTwoplus_PIDe","@0/(@0+@1)",RooArgList(varPiTwoplus_ProbNNe,varPiTwoplus_ProbNNpi));
  RooArgList        PIDe_formulas(varPiOneminus_PIDe,varPiOneplus_PIDe,varPiTwominus_PIDe,varPiTwoplus_PIDe);
  data.addColumns(PIDe_formulas);

  // Mass PDF
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  pdfBkgExtend.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  pdfBkgExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/PID-Optimization/StartingValues_Mass.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(config.getInt("num_cpu")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));
  fitting_args.Add((TObject*)(new RooCmdArg(Range(5400,5600))));

  if (config.getString("PID") == "Kaon") KaonPID_Optimization(&pdfBkgExtend, &data, fitting_args, config.getString("final_state"));
  else if (config.getString("PID") == "PionOne") PionPID_Optimization(&pdfBkgExtend, &data, fitting_args, "One", config.getString("final_state"));
  else if (config.getString("PID") == "PionTwo") PionPID_Optimization(&pdfBkgExtend, &data, fitting_args, "Two", config.getString("final_state"));
  else if (config.getString("PID") == "KKpi") KKPiPID_Optimization(&pdfBkgExtend, &data, fitting_args, config.getString("particle"));
  // ElectronPID_Optimization(&pdfBkgExtend, &data, fitting_args, "One");
  // RooDataSet* optimized_electronone_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65&&varPiOneminus_PIDe<0.5&&varPiOneplus_PIDe<0.5"));
  // ElectronPID_Optimization(&pdfBkgExtend, optimized_electronone_data, fitting_args, "Two");

  return 0;
}

void KaonPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString final_state){
  RooRealVar  obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooDataSet* reduced_data;
  int nsteps = 100;
  double cutvalue = 0.;
  double num_of_events_in_signal_region = 0.;
  double num_of_bkg_in_signal_region = 0.;
  std::vector<double> x_vals;
  std::vector<double> y_vals;
  std::vector<double> y_errors;
  RooFitResult* fit_result;
  RooRealVar* parBkgExponent;

  for (int i = 0; i < nsteps; ++i) {
    cutvalue = i*1./nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varKminus_PID>"+to_string(cutvalue)+"&&varKplus_PID>"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5260&&"+TString(obsMass.GetName())+"<5300");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parBkgExponent = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parBkgExponent"));
    x_vals += cutvalue;
    num_of_bkg_in_signal_region = pdf->expectedEvents(obsMass)*(exp(5260*parBkgExponent->getVal())-exp(5300*parBkgExponent->getVal()))/(exp(5400*parBkgExponent->getVal())-exp(5600*parBkgExponent->getVal()));
    y_vals += pow(num_of_events_in_signal_region - num_of_bkg_in_signal_region,1)/sqrt(num_of_events_in_signal_region);
    cout << "cutvalue: "  <<  cutvalue  <<  endl;
    cout << "Number of events in signal region: " <<  num_of_events_in_signal_region  <<  endl;
    cout << "Number of signal candidates in signal region: "  <<  num_of_events_in_signal_region - num_of_bkg_in_signal_region  <<  endl;
    y_errors += sqrt(0.25*pow(num_of_events_in_signal_region + num_of_bkg_in_signal_region,2)+pow(num_of_bkg_in_signal_region,2))/num_of_events_in_signal_region;
    cout  << "FOM: "  <<  y_vals.at(i)  <<  " pm "  <<  y_errors.at(i)  <<  endl;
  }

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  TGraphErrors  gr(x_vals.size(),&x_vals[0], &y_vals[0], NULL, &y_errors[0]);
  gr.GetXaxis()->SetTitle("cut value");
  gr.GetYaxis()->SetTitle("FOM = S/#sqrt{S+B}");
  gr.Draw("AP");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/FOM_KaonPID_"+final_state+".pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}

void PionPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber, TString final_state){
  RooRealVar  obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooDataSet* reduced_data;
  int nsteps = 100;
  double cutvalue = 0.;
  double num_of_events_in_signal_region = 0.;
  double num_of_bkg_in_signal_region = 0.;
  std::vector<double> x_vals;
  std::vector<double> y_vals;
  std::vector<double> y_errors;
  RooFitResult* fit_result;
  RooRealVar* parBkgExponent;

  pdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  for (int i = 0; i < nsteps; ++i) {
    cutvalue = 1.-i*1./nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varPi"+pionnumber+"minus_PID<"+to_string(cutvalue)+"&&varPi"+pionnumber+"plus_PID<"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5260&&"+TString(obsMass.GetName())+"<5300");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parBkgExponent = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parBkgExponent"));
    x_vals += cutvalue;
    num_of_bkg_in_signal_region = pdf->expectedEvents(obsMass)*(exp(5260*parBkgExponent->getVal())-exp(5300*parBkgExponent->getVal()))/(exp(5400*parBkgExponent->getVal())-exp(5600*parBkgExponent->getVal()));
    y_vals += pow(num_of_events_in_signal_region - num_of_bkg_in_signal_region,1)/sqrt(num_of_events_in_signal_region);
    cout << "cutvalue: "  <<  cutvalue  <<  endl;
    cout << "Number of events in signal region: " <<  num_of_events_in_signal_region  <<  endl;
    cout << "Number of signal candidates in signal region: "  <<  num_of_events_in_signal_region - num_of_bkg_in_signal_region  <<  endl;
    y_errors += sqrt(0.25*pow(num_of_events_in_signal_region + num_of_bkg_in_signal_region,2)+pow(num_of_bkg_in_signal_region,2))/num_of_events_in_signal_region;
    cout  << "FOM: "  <<  y_vals.at(i)  <<  " pm "  <<  y_errors.at(i)  <<  endl;
  }

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  TGraphErrors  gr(x_vals.size(), &x_vals[0], &y_vals[0], NULL, &y_errors[0]);
  gr.GetXaxis()->SetTitle("cut value");
  gr.GetYaxis()->SetTitle("FOM = S/#sqrt{S+B}");
  gr.Draw("AP");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion"+pionnumber+"/FOM_PionPID_"+final_state+".pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}

void KKPiPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString particle){
  RooRealVar  obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooDataSet* reduced_data;
  int nsteps = 100;
  double cutvalue = 0.;
  double num_of_events_in_signal_region = 0.;
  double num_of_bkg_in_signal_region = 0.;
  std::vector<double> x_vals;
  std::vector<double> y_vals;
  std::vector<double> y_errors;
  RooFitResult* fit_result;
  RooRealVar* parBkgExponent;

  for (int i = 0; i < nsteps; ++i) {
    if (particle.Contains("Pion")) cutvalue = 1.-i*1./nsteps;
    else cutvalue = i*1./nsteps;
    if (particle.EqualTo("KaonTwo"))  reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("(catDDFinalState!=13||varPiOneminus_PID>"+to_string(cutvalue)+")&&(catDDFinalState!=14||varPiTwominus_PID>"+to_string(cutvalue)+")&&(catDDFinalState!=31||varPiOneplus_PID>"+to_string(cutvalue)+")&&(catDDFinalState!=41||varPiTwoplus_PID>"+to_string(cutvalue)+")")));
    else if (particle.EqualTo("PionSingle"))  reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("(catDDFinalState!=13||varPiTwominus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=14||varPiOneminus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=31||varPiTwoplus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=41||varPiOneplus_PID<"+to_string(cutvalue)+")")));
    else if (particle.EqualTo("PionOne")) reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("(catDDFinalState!=13||varPiOneplus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=14||varPiOneplus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=31||varPiOneminus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=41||varPiOneminus_PID<"+to_string(cutvalue)+")")));
    else if (particle.EqualTo("PionTwo")) reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("(catDDFinalState!=13||varPiTwoplus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=14||varPiTwoplus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=31||varPiTwominus_PID<"+to_string(cutvalue)+")&&(catDDFinalState!=41||varPiTwominus_PID<"+to_string(cutvalue)+")")));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5260&&"+TString(obsMass.GetName())+"<5300");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parBkgExponent = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parBkgExponent"));
    x_vals += cutvalue;
    num_of_bkg_in_signal_region = pdf->expectedEvents(obsMass)*(exp(5260*parBkgExponent->getVal())-exp(5300*parBkgExponent->getVal()))/(exp(5400*parBkgExponent->getVal())-exp(5600*parBkgExponent->getVal()));
    y_vals += pow(num_of_events_in_signal_region - num_of_bkg_in_signal_region,1)/sqrt(num_of_events_in_signal_region);
    cout << "cutvalue: "  <<  cutvalue  <<  endl;
    cout << "Number of events in signal region: " <<  num_of_events_in_signal_region  <<  endl;
    cout << "Number of signal candidates in signal region: "  <<  num_of_events_in_signal_region - num_of_bkg_in_signal_region  <<  endl;
    y_errors += sqrt(0.25*pow(num_of_events_in_signal_region + num_of_bkg_in_signal_region,2)+pow(num_of_bkg_in_signal_region,2))/num_of_events_in_signal_region;
    cout  << "FOM: "  <<  y_vals.at(i)  <<  " pm "  <<  y_errors.at(i)  <<  endl;
  }

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  TGraphErrors  gr(x_vals.size(), &x_vals[0], &y_vals[0], NULL, &y_errors[0]);
  gr.GetXaxis()->SetTitle("cut value");
  gr.GetYaxis()->SetTitle("FOM = S/#sqrt{S+B}");
  gr.Draw("AP");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/KKpi/FOM_"+particle+"PID_KKpi.pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}

void ElectronPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args, TString pionnumber){
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  RooRealVar  obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooDataSet* reduced_data;
  int nsteps = 20;
  double cutvalue = 0.;
  double num_of_events_in_signal_region = 0.;
  std::vector<double> x_vals;
  std::vector<double> y_vals;
  std::vector<double> y_errors;
  double FOM_error_Ntot = 0.;
  double FOM_error_Nbkg = 0.;
  double FOM_error_expo = 0.;
  RooFitResult* fit_result;
  RooRealVar* parBkgExponent;

  pdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  for (int i = 0; i < nsteps; ++i) {
    cutvalue = 1.-i*1./nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varKminus_PID>0.12&&varKplus_PID>0.12&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65&&varPi"+pionnumber+"minus_PIDe<"+to_string(cutvalue)+"&&varPi"+pionnumber+"plus_PIDe<"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries(TString(obsMass.GetName())+">5260&&"+TString(obsMass.GetName())+"<5300");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parBkgExponent = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parBkgExponent"));
    x_vals += cutvalue;
    y_vals += pow((num_of_events_in_signal_region - pdf->expectedEvents(obsMass)*(exp(5260*parBkgExponent->getVal())-exp(5300*parBkgExponent->getVal()))/(exp(5400*parBkgExponent->getVal())-exp(5600*parBkgExponent->getVal()))),2)/sqrt(num_of_events_in_signal_region);
    cout << "Number of events in signal region: " <<  num_of_events_in_signal_region  <<  endl;
    cout << "Number of signal candidates in signal region: "  <<  num_of_events_in_signal_region - pdf->expectedEvents(obsMass)*(exp(5260*parBkgExponent->getVal())-exp(5300*parBkgExponent->getVal()))/(exp(5400*parBkgExponent->getVal())-exp(5600*parBkgExponent->getVal()))  <<  endl;
    FOM_error_Ntot = 2*sqrt(y_vals.at(i))*pow(num_of_events_in_signal_region,0.25)-0.5*y_vals.at(i)/sqrt(num_of_events_in_signal_region);
    FOM_error_Nbkg = 2*(exp(5260*parBkgExponent->getVal())-exp(5300*parBkgExponent->getVal()))/(exp(5400*parBkgExponent->getVal())-exp(5600*parBkgExponent->getVal()))*sqrt(y_vals.at(i))*sqrt(pdf->expectedEvents(obsMass))/pow(num_of_events_in_signal_region,0.25);
    y_errors += sqrt(pow(FOM_error_Ntot,2)+pow(FOM_error_Nbkg,2)+pow(FOM_error_expo,2));
    cout  << "Uncertainty on FOM due to total number of candidates in signal region: "  <<  FOM_error_Ntot  <<  endl;
    cout  << "Uncertainty on FOM due to expected number of background candidates in signal region: "  <<  FOM_error_Nbkg  <<  endl;
  }

  TGraphErrors  gr(x_vals.size(), &x_vals[0], &y_vals[0], NULL, &y_errors[0]);
  gr.GetXaxis()->SetTitle("cut value");
  gr.GetYaxis()->SetTitle("FOM = S^{2}/#sqrt{S+B}");
  gr.Draw("AP");
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/Electron"+pionnumber+"/ElectronPID.pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}
