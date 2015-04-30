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
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/fitter/splot/SPlotFit2.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;
using namespace doofit::fitter::splot;

void KaonPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args);
void PionPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args);

int main(int argc, char * argv[]){

  RooRealVar        obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");

  RooRealVar        BDT2_classifier("BDT2_classifier","BDT2_classifier",-1,1);
  
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
  RooArgSet         variables(BDT2_classifier,"variables");
  RooArgSet         varKaonProbNNs(varKminus_ProbNNk,varKminus_ProbNNpi,varKplus_ProbNNk,varKplus_ProbNNpi,"varKaonProbNNs");
  RooArgSet         varPionProbNNs(varPiOneminus_ProbNNk,varPiOneminus_ProbNNpi,varPiOneplus_ProbNNk,varPiOneplus_ProbNNpi,varPiTwominus_ProbNNk,varPiTwominus_ProbNNpi,varPiTwoplus_ProbNNk,varPiTwoplus_ProbNNpi,"varPionProbNNs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varKaonProbNNs);
  realvars.add(varPionProbNNs);
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,"categories");
  
  // Get data set
  EasyTuple         tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/Combined_2011_2012/DT20112012_B02DD_Stripping21r0r1_DVv36r1_20150322_fmeier_combined_20150412_fmeier_BDT_TupleB_Kpipi.root","B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut("BDT2_classifier>-0.174"));
  
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

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/PID-Optimization/PlotMass");
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend", "pdfSig1Extend", "pdfSig2Extend", "pdfBkgExtend";

  // KaonPID_Optimization(&pdfMass, &data, fitting_args);
  PionPID_Optimization(&pdfMass, &data, fitting_args);

  return 0;
}

void KaonPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args){
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/PlotMass");
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend", "pdfSig1Extend", "pdfSig2Extend", "pdfBkgExtend";
  RooRealVar  obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");
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
    num_of_events_in_signal_region = reduced_data->sumEntries("obsMass>5230&&obsMass<5330");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parSigYield = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parSigYield"));
    pdf->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Kaon/FitResults_Mass_"+to_string(i)+".txt"));
    x_vals += cutvalue;
    y_vals += pow(parSigYield->getVal(),2)/sqrt(num_of_events_in_signal_region);
    y_errors += sqrt(4.*pow(parSigYield->getVal()*parSigYield->getError(),2)/num_of_events_in_signal_region+pow(parSigYield->getVal(),4)/(4.*pow(num_of_events_in_signal_region,2)));
    Plot Mass(cfg_plot_mass, obsMass, *reduced_data, *pdf, components_mass, "obsMass_"+to_string(i));
    Mass.PlotIt();
  }

  pdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  for (int i = 1; i < nsteps; ++i) {
    cutvalue = i*0.4/nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varKminus_PID>"+to_string(cutvalue)+"&&varKplus_PID>"+to_string(cutvalue))));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries("obsMass>5230&&obsMass<5330");
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

void PionPID_Optimization(RooAbsPdf* pdf, RooDataSet* data, RooLinkedList& fitting_args){
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);
  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass");
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend", "pdfSig1Extend", "pdfSig2Extend", "pdfBkgExtend";
  RooRealVar  obsMass("obsMass","#it{m_{K#pi#pi K#pi#pi}}",5140,5400,"MeV/c^{2}");
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

  pdf->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_PionPIDOptimization.txt");
  c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses.pdf[");
  c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses_pull.pdf[");
  for (int i = 0; i < nsteps; ++i) {
    cutvalue = 1.-i*1./nsteps;
    reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<"+to_string(cutvalue)+"&&varPiTwominus_PID<"+to_string(cutvalue))+"&&varPiOneplus_PID<"+to_string(cutvalue)+"&&varPiTwoplus_PID<"+to_string(cutvalue)));
    reduced_data->Print();
    num_of_events_in_signal_region = reduced_data->sumEntries("obsMass>5230&&obsMass<5330");
    fit_result = pdf->fitTo(*reduced_data, fitting_args);
    parSigYield = dynamic_cast<RooRealVar*>(fit_result->floatParsFinal().find("parSigYield"));
    pdf->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/FitResults_Mass_"+to_string(i)+".txt"));
    x_vals += cutvalue;
    y_vals += pow(parSigYield->getVal(),2)/sqrt(num_of_events_in_signal_region);
    y_errors += sqrt(4.*pow(parSigYield->getVal()*parSigYield->getError(),2)/num_of_events_in_signal_region+pow(parSigYield->getVal(),4)/(4.*pow(num_of_events_in_signal_region,2)));
    // Plot Mass(cfg_plot_mass, obsMass, *reduced_data, *pdf, components_mass, "obsMass_"+to_string(i));
    // Mass.PlotIt();
    plot_frame = obsMass.frame();
    reduced_data->plotOn(plot_frame);
    pdf->plotOn(plot_frame, Components("pdfSigExtend"),  LineColor(214), LineStyle(2));
    pdf->plotOn(plot_frame, Components("pdfSig1Extend"), LineColor(210), LineStyle(3));
    pdf->plotOn(plot_frame, Components("pdfSig2Extend"), LineColor(226), LineStyle(4));
    pdf->plotOn(plot_frame, Components("pdfBkgExtend"),  LineColor(222), LineStyle(5));
    pdf->plotOn(plot_frame, LineColor(1));
    plot_frame->SetMaximum(250.);
    plot_frame->GetYaxis()->SetTitle((TString::Format("Candidates / ( %1.0f %s )", obsMass.getBinWidth(1), obsMass.getUnit()) ).Data());
    PlotSimple("PionPIDMasses", plot_frame, *(new TLatex()),"/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass", false);
    PlotPulls("PionPIDMasses_pull", plot_frame, *(new TLatex()),"/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass", false);
  }
  c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses.pdf]");
  c.Print("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PlotMass/pdf/PionPIDMasses_pull.pdf]");

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
  c.SaveAs("/home/fmeier/storage03/b02dd/run/PID-Optimization/Pion/PionPID.pdf");

  for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
}
