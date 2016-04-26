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
#include "RooCBShape.h"
#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooAddModel.h"
#include "RooHistPdf.h"
#include "RooExtendPdf.h"
#include "RooGaussian.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
#include "Erasmus/RooHORNSdini.h"
#include "Erasmus/RooHILLdini.h"

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

  bool HORNSdini = config.getBool("HORNSdini");
  bool HILLdini = config.getBool("HILLdini");
  TString identifier = "HORNSdini";
  if (!HORNSdini && HILLdini) identifier = "HILLdini";
  if (!HORNSdini && !HILLdini) identifier = "DoubleGauss";

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",4900,5250,"MeV/c^{2}");
  
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
  catBkg.defineType("misID",30);
  catBkg.defineType("part reco",40);
  catBkg.defineType("LowMassBkg",50);
  catBkg.defineType("Ghost",60);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("best PV",0);

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         categories(catDDFinalState,catDDFinalStateParticles,idxPV,catBkg,"categories");

  // Get data set
  EasyTuple         tuple(config.getString("tuple"),config.getString("tree"),RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));
  data.Print();

  // Mass PDF
  // Bd --> D*+ D- with D*+ --> D+ pi0 Background
  RooRealVar        parBkgDstDLowMassMean("parBkgDstDLowMassMean","Mean Mass",5060,5050,5070,"MeV/c^{2}");
  RooRealVar        parBkgDstDLowMassSigma("parBkgDstDLowMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDLowMass("pdfBkgDstDLowMass","Lower DstD Mass PDF",obsMass,parBkgDstDLowMassMean,parBkgDstDLowMassSigma);

  RooRealVar        parBkgDstDHighMassMean("parBkgDstDHighMassMean","Mean Mass",5120,5100,5140,"MeV/c^{2}");
  RooRealVar        parBkgDstDHighMassSigma("parBkgDstDHighMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgDstDHighMass("pdfBkgDstDHighMass","Upper DstD Mass PDF",obsMass,parBkgDstDHighMassMean,parBkgDstDHighMassSigma);

  RooRealVar        parBkgDstDMassFraction("parBkgDstDMassFraction","fraction between low and high component",0.5,0,1);

  RooRealVar        parBkgDstDHornA("parBkgDstDHornA","parBkgDstDHornA",5000,5100);
  RooRealVar        parBkgDstDHornB("parBkgDstDHornB","parBkgDstDHornB",5100,5200);
  RooRealVar        parBkgDstDHornXi("parBkgDstDHornXi","parBkgDstDHornXi",0,1);
  RooRealVar        parBkgDstDHornShift("parBkgDstDHornShift","parBkgDstDHornShift",-10,10);
  RooRealVar        parBkgDstDHornSigma("parBkgDstDHornSigma","parBkgDstDHornSigma",10,1,20);
  RooRealVar        parBkgDstDHornSigmaFactor("parBkgDstDHornSigmaFactor","parBkgDstDHornSigmaFactor",2,1,5);
  RooRealVar        parBkgDstDHornFraction("parBkgDstDHornFraction","parBkgDstDHornFraction",0.5,0,1);

  RooAbsPdf*        pdfBkgDstDMass;
  if (HORNSdini) pdfBkgDstDMass = new RooHORNSdini("pdfBkgDstDMass","pdfBkgDstDMass",obsMass,parBkgDstDHornA,parBkgDstDHornB,parBkgDstDHornXi,parBkgDstDHornShift,parBkgDstDHornSigma,parBkgDstDHornSigmaFactor,parBkgDstDHornFraction);
  else if(HILLdini) pdfBkgDstDMass = new RooHILLdini("pdfBkgDstDMass","pdfBkgDstDMass",obsMass,parBkgDstDHornA,parBkgDstDHornB,parBkgDstDHornXi,parBkgDstDHornShift,parBkgDstDHornSigma,parBkgDstDHornSigmaFactor,parBkgDstDHornFraction);
  else pdfBkgDstDMass = new RooAddPdf("pdfBkgDstDMass","pdfBkgDstDMass",RooArgList(pdfBkgDstDLowMass,pdfBkgDstDHighMass),parBkgDstDMassFraction);

  RooRealVar        parBkgDstDYield("parBkgDstDYield","parBkgDstDYield",500,0,1000);
  RooExtendPdf      pdfBkgDstDExtend("pdfBkgDstDExtend","pdfBkgDstDExtend",*pdfBkgDstDMass,parBkgDstDYield);

  // Get Starting Values and Fit PDF to data
  pdfBkgDstDExtend.Print();
  pdfBkgDstDExtend.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_MC_Mass.txt");
  pdfBkgDstDExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/StartingValues_MC_Mass.new");
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

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/MC/PlotMass_DstD");
  cfg_plot_mass.set_label_text("#splitline{MC}{#it{B}^{0} #rightarrow #it{D}^{*+}#it{D}^{-}}");
  cfg_plot_mass.set_label_position_x(0.25);
  std::vector<std::string> components_mass;
  if (!HORNSdini) components_mass += "pdfBkgDstDHighMass", "pdfBkgDstDLowMass";

  RooFitResult* fit_result = pdfBkgDstDExtend.fitTo(data, fitting_args);
  doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();
  pdfBkgDstDExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/FitResults_DstDMass_"+identifier+".txt");
  Plot Mass(cfg_plot_mass, obsMass, data, pdfBkgDstDExtend, components_mass, string("DstDMass_"+identifier));
  Mass.set_scaletype_x(kLinear);
  Mass.set_scaletype_y(kBoth);
  Mass.PlotIt();

  return 0;
}