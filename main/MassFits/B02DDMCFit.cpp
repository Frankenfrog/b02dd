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
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "doofit/plotting/Plot/Plot.h"
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

int main(int argc, char * argv[]){
  if (argc < 2) {
    std::cout << "Usage:   " << argv[0] << " fit_config_file_name" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5230,5330,"MeV/c^{2}");
  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);

  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("Signal",0);
  catBkg.defineType("QuasiSignal",10);
  catBkg.defineType("FullyRecoPhysBkg",20);
  catBkg.defineType("LowMassBkg",50);
  catBkg.defineType("Ghost",60);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("best PV",0);

  RooArgSet         observables("observables");
  if (config.getBool("B0")) observables.add(obsMass);
  if (config.getBool("Dpm")) observables.add(RooArgSet(obsMassDauOne,obsMassDauTwo));
  RooArgSet         categories(catDDFinalState,catDDFinalStateParticles,catBkg,idxPV,"categories");

  // Get data set
  EasyTuple         tuple(config.getString("tuple"),config.getString("tree"),RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));
  data.Print();

  // Mass PDF
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");

  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parSigMassCB1Expo("parSigMassCB1Expo","parSigMassCB1Expo",10,1,100);
  RooRealVar        parSigMassCB1Alpha("parSigMassCB1Alpha","parSigMassCB1Alpha",1,0.5,2);
  RooCBShape        pdfSigMassCB1("pdfSigMassCB1","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);

  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parSigMassCB2Expo("parSigMassCB2Expo","parSigMassCB2Expo",10,1,100);
  RooRealVar        parSigMassCB2Alpha("parSigMassCB2Alpha","parSigMassCB2Alpha",-1,-2,-0.5);
  RooCBShape        pdfSigMassCB2("pdfSigMassCB2","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);

  RooRealVar        parSigMassCBFraction("parSigMassCBFraction","parSigMassCBFraction",0.5);
  RooAddPdf         pdfSigMass("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB2),parSigMassCBFraction);

  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);

  RooRealVar        parSigDMassMean("parSigDMassMean","Bd Mean Mass",1870,1860,1880,"MeV/c^{2}");
  RooRealVar        parSigDMassSigma1("parSigDMassSigma1","Sigma of Gaussian Mass",7.0,1.0,10.0,"MeV/c^{2}");
  RooGaussian       pdfSigDMass1("pdfSigDMass1","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma1);

  RooRealVar        parSigDMassSigma2("parSigDMassSigma2","Sigma of Gaussian Mass",12,8,20.0,"MeV/c^{2}");
  RooGaussian       pdfSigDMass2("pdfSigDMass2","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma2);
  
  RooRealVar        parSigDMassFraction("parSigDMassFraction","parSigDMassFraction",0.5,0,1);
  RooAddPdf         pdfSigDMass("pdfSigDMass","pdfSigDMass",RooArgList(pdfSigDMass1,pdfSigDMass2),parSigDMassFraction);

  RooRealVar        parSigDYield("parSigDYield","parSigDYield",25000,0,30000);
  RooExtendPdf      pdfSigDExtend("pdfSigDExtend","pdfSigDExtend",pdfSigDMass,parSigDYield);

  // Fit options
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
  RooFitResult* fit_result;
  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory(string("/home/fmeier/storage03/b02dd/run/MC/PlotMass_"+config.getString("identifier")));
  cfg_plot_mass.set_label_text("#splitline{MC}{#it{B}^{0} #rightarrow #it{D}^{+}#it{D}^{-}}");
  cfg_plot_mass.set_label_position_x(0.20);

  if (config.getBool("B0")) {
    pdfSigExtend.Print();
    pdfSigExtend.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_MC_Mass.txt");
    pdfSigExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/StartingValues_MC_Mass.new");

    fit_result = pdfSigExtend.fitTo(data, fitting_args);
    doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
    fitresultprinter.Print();
    pdfSigExtend.getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/MC/FitResults_Mass_"+config.getString("identifier")+".txt"));
    std::vector<std::string> components_mass;
    components_mass += "pdfSigExtend";
    Plot Mass(cfg_plot_mass, obsMass, data, pdfSigExtend, components_mass, "CB_obsMass");
    Mass.set_scaletype_x(kLinear);
    Mass.set_scaletype_y(kBoth);
    Mass.PlotIt();
  }

  if (config.getBool("Dpm")) {
    fit_result = pdfSigDExtend.fitTo(data, fitting_args);
    pdfSigDExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/FitResults_DMass.txt");
    std::vector<std::string> components_Dmass;
    components_Dmass += "pdfSigDExtend";
    Plot MassD(cfg_plot_mass, obsMassDauOne, data, pdfSigDExtend, components_Dmass, "obsMassDauOne");
    MassD.PlotIt();
  }

  return 0;
}