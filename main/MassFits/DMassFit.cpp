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
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
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
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  RooRealVar        obsMassDauOne(TString(config.getString("observable_name_DauOne")),TString(config.getString("observable_title_DauOne")),1825,1915,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo(TString(config.getString("observable_name_DauTwo")),TString(config.getString("observable_title_DauTwo")),1825,1915,"MeV/c^{2}");
  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");

  RooRealVar        varDMinTauSignificance("varDMinTauSignificance","varDMinTauSignificance",0,1000);

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);

  RooArgSet         observables(obsMassDauOne,obsMassDauTwo,obsMass,"observables");
  RooArgSet         variables(varDMinTauSignificance,"variables");
  RooArgSet         realvars(observables,variables,"realvars");
  RooArgSet         categories(catDDFinalState,"categories");
  
  // Get data set
  EasyTuple         tuple(config.getString("input_tuple"),config.getString("input_tree"),RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));
  
  data.Print();

  // Mass PDF
  RooRealVar        parSigDMassMean("parSigDMassMean","D Mean Mass",1870,1860,1880,"MeV/c^{2}");
  RooRealVar        parSigDMassSigma("parSigDMassSigma","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooGaussian       pdfSigDplusMass("pdfSigDplusMass","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma);
  RooGaussian       pdfSigDminusMass("pdfSigDminusMass","Signal Mass PDF",obsMassDauTwo,parSigDMassMean,parSigDMassSigma);

  RooRealVar        parBkgDExponent("parBkgDExponent","parBkgDExponent",-0.005,-1,1);
  RooExponential    pdfBkgDplusMass("pdfBkgDplusMass","pdfBkgDplusMass",obsMassDauOne,parBkgDExponent);
  RooExponential    pdfBkgDminusMass("pdfBkgDminusMass","pdfBkgDminusMass",obsMassDauTwo,parBkgDExponent);

  RooProdPdf        pdfSigDDMass("pdfSigDDMass","pdfSigDDMass",pdfSigDplusMass,pdfSigDminusMass);
  RooProdPdf        pdfBkgDCombMass("pdfBkgDCombMass","pdfBkgDCombMass",pdfSigDplusMass,pdfBkgDminusMass);
  RooProdPdf        pdfBkgCombDMass("pdfBkgCombDMass","pdfBkgCombDMass",pdfBkgDplusMass,pdfSigDminusMass);
  RooProdPdf        pdfBkgCombMass("pdfBkgCombMass","pdfBkgCombMass",pdfBkgDplusMass,pdfBkgDminusMass);

  RooRealVar        parSigDDYield("parSigDDYield","parSigDDYield",1000,0,100000);
  RooRealVar        parBkgDCombYield("parBkgDCombYield","parBkgDCombYield",1000,0,100000);
  RooRealVar        parBkgCombDYield("parBkgCombDYield","parBkgCombDYield",1000,0,100000);
  RooRealVar        parBkgCombYield("parBkgCombYield","parBkgCombYield",1000,0,100000);

  RooExtendPdf      pdfSigDDExtend("pdfSigDDExtend","pdfSigDDExtend",pdfSigDDMass,parSigDDYield);
  RooExtendPdf      pdfBkgDCombExtend("pdfBkgDCombExtend","pdfBkgDCombExtend",pdfBkgDCombMass,parBkgDCombYield);
  RooExtendPdf      pdfBkgCombDExtend("pdfBkgCombDExtend","pdfBkgCombDExtend",pdfBkgCombDMass,parBkgCombDYield);
  RooExtendPdf      pdfBkgCombExtend("pdfBkgCombExtend","pdfBkgCombExtend",pdfBkgCombMass,parBkgCombYield);

  RooAddPdf         pdfMass("pdfMass","Mass PDF",RooArgList(pdfSigDDExtend,pdfBkgDCombExtend,pdfBkgCombDExtend,pdfBkgCombExtend));

  // Get Starting Values and Fit PDF to data
  pdfMass.Print();
  pdfMass.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/StartingValues_Mass.new");
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

  if (config.getBool("optimize_DtauSignificance")){
    RooDataSet* reduced_data;
    int nsteps = config.getInt("nsteps");
    double cutvalue = 0.;
    double FOM = 0.;
    double FOM_max = 0.;
    std::vector<double> x_vals;
    std::vector<double> y_vals;
    std::vector<double> y_errors;
    double FOM_error_Ntot = 0.;
    double FOM_error_Nbkg = 0.;
    double FOM_error_expo = 0.;
    RooFitResult* fit_result;
    for (int i = 0; i < nsteps; ++i){
      cutvalue = -5 + i;
      reduced_data = dynamic_cast<RooDataSet*>(data.reduce(TString("varDMinTauSignificance>"+to_string(cutvalue))));
      reduced_data->Print();
      fit_result = pdfMass.fitTo(*reduced_data, fitting_args);
      x_vals += cutvalue;
      FOM = pow(parSigDDYield.getVal(),config.getDouble("FOM_expo"))/sqrt(reduced_data->sumEntries());
      y_vals += FOM;
      if (FOM > FOM_max)  FOM_max = FOM;
      y_errors += 0;
    }

    gROOT->SetStyle("Plain");
    setStyle("LHCb");
    TCanvas c("c","c",800,600);
    TGraphErrors  gr(x_vals.size(), &x_vals[0], &y_vals[0], NULL, &y_errors[0]);
    gr.GetXaxis()->SetTitle("D tau significance");
    if (config.getDouble("FOM_expo") == 1.) gr.GetYaxis()->SetTitle("FOM = S/#sqrt{S+B}");
    if (config.getDouble("FOM_expo") == 2.) gr.GetYaxis()->SetTitle("FOM = S^{2}/#sqrt{S+B}");
    if (config.getDouble("FOM_expo") == 3.) gr.GetYaxis()->SetTitle("FOM = S^{3}/#sqrt{S+B}");
    gr.Draw("AP");
    c.SaveAs("/home/fmeier/storage03/b02dd/run/sWeights/DTauSignificance_Optimization_"+TString(to_string(config.getDouble("FOM_expo")))+".pdf");

    for (int i = 0; i < x_vals.size(); ++i)  cout << x_vals.at(i) <<  "\t"  <<  y_vals.at(i) <<  endl;
  }
  else {
    PlotConfig cfg_plot_mass("cfg_plot_mass");
    cfg_plot_mass.InitializeOptions();
    cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/sWeights/Plots");

    std::vector<std::string> components_Dplus;
    components_Dplus += "pdfSigDplusMass", "pdfBkgDplusMass";
    std::vector<std::string> components_Dminus;
    components_Dminus += "pdfSigDminusMass", "pdfBkgDminusMass";

    if (config.getBool("plot_pdf")) {
      RooFitResult* fit_result = pdfMass.fitTo(data, fitting_args);
      pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/FitResult_"+TString(config.getString("identifier"))+".txt");
      doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
      fitresultprinter.Print();
      Plot MassDplus(cfg_plot_mass, obsMassDauOne, data, pdfMass, components_Dplus, "obsMassDauOne_"+string(config.getString("identifier")));
      MassDplus.PlotIt();
      Plot MassDminus(cfg_plot_mass, obsMassDauTwo, data, pdfMass, components_Dminus, "obsMassDauTwo_"+string(config.getString("identifier")));
      MassDminus.PlotIt();
    }
    else {
      Plot MassDplus(cfg_plot_mass, obsMassDauOne, data, RooArgList(), "obsMassDauOne_"+string(config.getString("identifier")));
      MassDplus.PlotIt();
      Plot MassDminus(cfg_plot_mass, obsMassDauTwo, data, RooArgList(), "obsMassDauTwo_"+string(config.getString("identifier")));
      MassDminus.PlotIt();
    }  
  }

  if (config.getBool("calculate_sweights")){
    SPlotFit2 splotfit(pdfMass,data,RooArgSet(parSigDDYield,parBkgDCombYield,parBkgCombDYield,parBkgCombYield));
    splotfit.set_use_minos(false);
    splotfit.set_num_cpu(config.getInt("num_cpu"));

    dooselection::reducer::SPlotterReducer spr(splotfit, RooArgSet(obsMassDauOne,obsMassDauTwo));
    spr.set_input_file_path(config.getString("input_tuple"));
    spr.set_input_tree_path(config.getString("input_tree"));
    spr.set_output_file_path(config.getString("sweights_tuple"));

    spr.set_output_tree_path("B02DD");
    spr.set_cut_string(TString(obsMassDauOne.GetName())+">="+to_string(obsMassDauOne.getMin())+"&&"+TString(obsMassDauOne.GetName())+"<="+to_string(obsMassDauOne.getMax())+"&&"+TString(obsMassDauTwo.GetName())+">="+to_string(obsMassDauTwo.getMin())+"&&"+TString(obsMassDauTwo.GetName())+"<="+to_string(obsMassDauTwo.getMax())+"&&"+string(config.getString("cut")));
    spr.set_plot_directory(string("/home/fmeier/storage03/b02dd/run/Reducer/Plots"));
    spr.Initialize();
    spr.Run();
    spr.Finalize();
  }

  return 0;
}
