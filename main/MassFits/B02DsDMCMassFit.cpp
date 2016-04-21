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

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5000,5350,"MeV/c^{2}");
  
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);
  RooRealVar        BDTwPIDs_classifier("BDT_wPIDs_LowMass_Kpipi_classifier","BDT_wPIDs_LowMass_Kpipi_classifier",-1,1);

  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("Signal",0);
  catBkg.defineType("QuasiSignal",10);
  catBkg.defineType("FullyRecoPhysBkg",20);
  catBkg.defineType("misID",30);
  catBkg.defineType("LowMassBkg",50);
  catBkg.defineType("Ghost",60);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("best PV",0);

  RooArgSet         observables(obsMass,BDTwPIDs_classifier,"observables");
  RooArgSet         categories(catDDFinalState,catDDFinalStateParticles,idxPV,catBkg,"categories");

  // Get data set
  EasyTuple         tuple(config.getString("tuple"),config.getString("tree"),RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));
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

  RooRealVar        parDsDYield("parDsDYield","parDsDYield",500,0,1000);
  RooExtendPdf      pdfDsDExtend("pdfDsDExtend","pdfDsDExtend",pdfDsDMass,parDsDYield);

  // Get Starting Values and Fit PDF to data
  pdfDsDExtend.Print();
  pdfDsDExtend.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_MC_Mass.txt");
  pdfDsDExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/StartingValues_MC_Mass.new");
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
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/MC/PlotMass_DsD");
  cfg_plot_mass.set_label_text("#splitline{MC}{#it{B}^{0} #rightarrow #it{D}_{s}^{+}#it{D}^{-}}");
  cfg_plot_mass.set_label_position_x(0.25);
  std::vector<std::string> components_mass;
  components_mass += "pdfDsDMassCB1", "pdfDsDMassCB2";

  RooFitResult* fit_result = pdfDsDExtend.fitTo(data, fitting_args);
  doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();
  pdfDsDExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/MC/FitResults_DsDMass.txt");
  Plot Mass(cfg_plot_mass, obsMass, data, pdfDsDExtend, components_mass, "DsDMass");
  Mass.set_scaletype_x(kLinear);
  Mass.set_scaletype_y(kBoth);
  Mass.PlotIt();

  return 0;
}