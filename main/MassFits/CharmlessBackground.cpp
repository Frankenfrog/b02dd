#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TRandom3.h"

//from RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooSuperCategory.h"
#include "RooConstVar.h"
#include "RooBinning.h"
#include "RooAddition.h"
#include "RooProduct.h"

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooMultiVarGaussian.h"
#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooSimultaneous.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooCBShape.h"
#include "RooChebychev.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/plotting/correlations/CorrelationPlot.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
#include "doofit/config/CommonConfig.h"
#include "Erasmus/RooHORNSdini.h"

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
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  bool split_years      = config.getBool("split_years");
  bool split_final_state  = config.getBool("split_final_state");

  bool massfit = config.getBool("massfit");
  bool plot_mass_distribution = config.getBool("plot_mass_distribution");
  if (plot_mass_distribution) massfit = false;
  std::string cut = config.getString("cut");

  RooRealVar        obsMass(TString(config.getString("observable_name_BMass")),TString(config.getString("observable_title_BMass")),5150,5500,"MeV/c^{2}");

  RooRealVar        obsMassDauOne(TString(config.getString("observable_name_DauOne")),TString(config.getString("observable_title_DauOne")),1829.62,1909.62,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo(TString(config.getString("observable_name_DauTwo")),TString(config.getString("observable_title_DauTwo")),1829.62,1909.62,"MeV/c^{2}");
  RooRealVar        varDMinBVtxSepChi2("varDMinBVtxSepChi2","varDMinBVtxSepChi2",0,100000);
  RooRealVar        varDMinTauSignificance("varDMinTauSignificance","varDMinTauSignificance",-100,100);

  RooCategory       catYear("catYear","year of data taking");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
  catDDFinalState.defineType("KpipiKKpi",13);
  catDDFinalState.defineType("KpipiKpiK",14);
  catDDFinalState.defineType("KKpiKpipi",31);
  catDDFinalState.defineType("KpiKKpipi",41);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);
  RooCategory       catDplusFinalState("catDplusFinalState","catDplusFinalState");
  catDplusFinalState.defineType("Kpipi",1);
  catDplusFinalState.defineType("KKpi",3);
  catDplusFinalState.defineType("KpiK",4);
  RooCategory       catDminusFinalState("catDminusFinalState","catDminusFinalState");
  catDminusFinalState.defineType("Kpipi",1);
  catDminusFinalState.defineType("KKpi",3);
  catDminusFinalState.defineType("KpiK",4);

  RooRealVar        BDTwPIDs_Kpipi_classifier("BDT_wPIDs_LowMass_Kpipi_classifier","BDT_wPIDs_LowMass_Kpipi_classifier",-1,1);
  RooRealVar        BDTwPIDs_KKpi_classifier("BDT_wPIDs_LowMass_KKpi_classifier","BDT_wPIDs_LowMass_KKpi_classifier",-1,1);

  RooArgSet         observables(obsMass,"observables");
  observables.add(RooArgSet(BDTwPIDs_Kpipi_classifier,BDTwPIDs_KKpi_classifier));
  observables.add(RooArgSet(obsMassDauOne,obsMassDauTwo,varDMinTauSignificance,varDMinBVtxSepChi2));
  RooArgSet         categories(catYear,catDDFinalState,catDDFinalStateParticles,catDminusFinalState,catDplusFinalState,"categories");
  
  // Get data set

  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet*       data = &(tuple.ConvertToDataSet(Cut(TString(config.getString("cut")))));
  data->Print();

  if (plot_mass_distribution) {
    PlotConfig cfg_plot_mass("cfg_plot_mass");
    cfg_plot_mass.InitializeOptions();
    cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/CharmlessBackground/Plots/"+config.getString("identifier"));
    cfg_plot_mass.set_simultaneous_plot_all_categories(true);
    // cfg_plot_mass.set_label_text("#splitline{LHCb 3fb^{-1}}{inoffiziell}");
    // cfg_plot_mass.set_y_axis_label("Kandidaten");
    Plot Mass(cfg_plot_mass, obsMass, *data, RooArgList());
    Mass.set_scaletype_x(kLinear);
    Mass.set_scaletype_y(kBoth);
    Mass.PlotIt();
    return 0;
  }

//=========================================================================================================================================================================================================================

  // Mass PDF
  // Signal
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");
  RooRealVar        parSigMassSigma("parSigMassSigma","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  // RooGaussian       pdfSigMass("pdfSigMass","pdfSigMass",obsMass,parSigMassMean,parSigMassSigma);
  RooRealVar        parSigMassSigmaScale("parSigMassSigmaScale","Scale of MC resolution",1,0,2);

  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  RooProduct        parSigMassSigma1Product("parSigMassSigma1Product","parSigMassSigma1Product",RooArgList(parSigMassSigma1,parSigMassSigmaScale));
  RooRealVar        parSigMassCB1Expo("parSigMassCB1Expo","parSigMassCB1Expo",10);
  RooRealVar        parSigMassCB1Alpha("parSigMassCB1Alpha","parSigMassCB1Alpha",1.28);
  RooCBShape        pdfSigMassCB1("pdfSigMassCB1","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma1Product,parSigMassCB1Alpha,parSigMassCB1Expo);

  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooProduct        parSigMassSigma2Product("parSigMassSigma2Product","parSigMassSigma2Product",RooArgList(parSigMassSigma2,parSigMassSigmaScale));
  RooRealVar        parSigMassCB2Expo("parSigMassCB2Expo","parSigMassCB2Expo",10);
  RooRealVar        parSigMassCB2Alpha("parSigMassCB2Alpha","parSigMassCB2Alpha",-1.32);
  RooCBShape        pdfSigMassCB2("pdfSigMassCB2","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma2Product,parSigMassCB2Alpha,parSigMassCB2Expo);

  RooRealVar        parSigMassSigma3("parSigMassSigma3","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooProduct        parSigMassSigma3Product("parSigMassSigma3Product","parSigMassSigma3Product",RooArgList(parSigMassSigma3,parSigMassSigmaScale));
  RooRealVar        parSigMassCB3Expo("parSigMassCB3Expo","parSigMassCB3Expo",10,1,100);
  RooRealVar        parSigMassCB3Alpha("parSigMassCB3Alpha","parSigMassCB3Alpha",2,0,5);
  RooCBShape        pdfSigMassCB3("pdfSigMassCB3","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma3Product,parSigMassCB3Alpha,parSigMassCB3Expo);

  RooRealVar        parSigMassCBFraction("parSigMassCBFraction","parSigMassCBFraction",0.5);
  RooRealVar        parSigMassCBFraction2("parSigMassCBFraction2","parSigMassCBFraction2",0.5);
  RooAddPdf         pdfSigMass("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB3,pdfSigMassCB2),RooArgList(parSigMassCBFraction,parSigMassCBFraction2));

  // B0 --> DsD background
  RooRealVar        parBkgDsDMean("parBkgDsDMean","Mean Mass",5220,5210,5230,"MeV/c^{2}");

  RooRealVar        parBkgDsDMassSigma1("parBkgDsDMassSigma1","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parBkgDsDMassCB1Expo("parBkgDsDMassCB1Expo","parBkgDsDMassCB1Expo",10,1,100);
  RooRealVar        parBkgDsDMassCB1Alpha("parBkgDsDMassCB1Alpha","parBkgDsDMassCB1Alpha",1,0.5,2);
  RooCBShape        pdfBkgDsDMassCB1("pdfBkgDsDMassCB1","Mass PDF",obsMass,parBkgDsDMean,parBkgDsDMassSigma1,parBkgDsDMassCB1Alpha,parBkgDsDMassCB1Expo);

  RooRealVar        parBkgDsDMassSigma2("parBkgDsDMassSigma2","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooRealVar        parBkgDsDMassCB2Expo("parBkgDsDMassCB2Expo","parBkgDsDMassCB2Expo",10,1,100);
  RooRealVar        parBkgDsDMassCB2Alpha("parBkgDsDMassCB2Alpha","parBkgDsDMassCB2Alpha",-1,-2,-0.5);
  RooCBShape        pdfBkgDsDMassCB2("pdfBkgDsDMassCB2","Mass PDF",obsMass,parBkgDsDMean,parBkgDsDMassSigma2,parBkgDsDMassCB2Alpha,parBkgDsDMassCB2Expo);

  RooRealVar        parBkgDsDMassCBFraction("parBkgDsDMassCBFraction","parBkgDsDMassCBFraction",0.5);
  RooAddPdf         pdfBkgDsDMass("pdfBkgDsDMass","pdfBkgDsDMass",RooArgList(pdfBkgDsDMassCB1,pdfBkgDsDMassCB2),parBkgDsDMassCBFraction);

  // Bs --> DsD background
  RooFormulaVar     parBkgBsDsDMassMean("parBkgBsDsDMassMean","shifted Bs --> DsD Mean Mass","@0+87.35",RooArgList(parBkgDsDMean));
  RooCBShape        pdfBkgBsDsDMassCB1("pdfBkgBsDsDMassCB1","Mass PDF",obsMass,parBkgBsDsDMassMean,parBkgDsDMassSigma1,parBkgDsDMassCB1Alpha,parBkgDsDMassCB1Expo);
  RooCBShape        pdfBkgBsDsDMassCB2("pdfBkgBsDsDMassCB2","Mass PDF",obsMass,parBkgBsDsDMassMean,parBkgDsDMassSigma2,parBkgDsDMassCB2Alpha,parBkgDsDMassCB2Expo);
  RooAddPdf         pdfBkgBsDsDMass("pdfBkgBsDsDMass","pdfBkgBsDsDMass",RooArgList(pdfBkgBsDsDMassCB1,pdfBkgBsDsDMassCB2),parBkgDsDMassCBFraction);

  // Bs --> DD signal
  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.35",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1Product,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2Product,parSigMassCB2Alpha,parSigMassCB2Expo);
  RooCBShape        pdfSigBsMassCB3("pdfSigBsMassCB3","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma3Product,parSigMassCB3Alpha,parSigMassCB3Expo);
  RooAddPdf         pdfSigBsMass("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB3,pdfSigBsMassCB2),RooArgList(parSigMassCBFraction,parSigMassCBFraction2));
  // RooGaussian       pdfSigBsMass("pdfSigBsMass","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma);

  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);
  RooRealVar        parBkgExponent_Kpipi("parBkgExponent_Kpipi","parBkgExponent_Kpipi",-0.001,-1,1);
  RooExponential    pdfBkgMass_Kpipi("pdfBkgMass_Kpipi","pdfBkgMass_Kpipi",obsMass,parBkgExponent_Kpipi);
  RooRealVar        parBkgExponent_KKpi("parBkgExponent_KKpi","parBkgExponent_KKpi",-0.001,-1,1);
  RooExponential    pdfBkgMass_KKpi("pdfBkgMass_KKpi","pdfBkgMass_KKpi",obsMass,parBkgExponent_KKpi);

  RooRealVar        parSigYield_11_Kpipi("parSigYield_11_Kpipi","N_{B^{0}_{d}}^{11,K#pi#pi}",500,0,1000);
  RooRealVar        parSigYield_12_Kpipi("parSigYield_12_Kpipi","N_{B^{0}_{d}}^{12,K#pi#pi}",500,0,1000);
  RooRealVar        parSigYield_11_KKpi("parSigYield_11_KKpi","N_{B^{0}_{d}}^{11,KK#pi}",500,0,1000);
  RooRealVar        parSigYield_12_KKpi("parSigYield_12_KKpi","N_{B^{0}_{d}}^{12,KK#pi}",500,0,1000);
  RooRealVar        parSigYield_Kpipi("parSigYield_Kpipi","parSigYield_Kpipi",1000,0,2000);
  RooRealVar        parSigYield_KKpi("parSigYield_KKpi","parSigYield_KKpi",200,0,1000);
  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parBkgDsDYield_11_Kpipi("parBkgDsDYield_11_Kpipi","parBkgDsDYield_11_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_Kpipi("parBkgDsDYield_12_Kpipi","parBkgDsDYield_12_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_11_KKpi("parBkgDsDYield_11_KKpi","parBkgDsDYield_11_KKpi",1000,0,2000);
  RooRealVar        parBkgDsDYield_12_KKpi("parBkgDsDYield_12_KKpi","parBkgDsDYield_12_KKpi",1000,0,2000);
  RooRealVar        parBkgDsDYield_Kpipi("parBkgDsDYield_Kpipi","parBkgDsDYield_Kpipi",1000,0,2000);
  RooRealVar        parBkgDsDYield_KKpi("parBkgDsDYield_KKpi","parBkgDsDYield_KKpi",150,0,2000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11_Kpipi("parBkgBsDsDYield_11_Kpipi","parBkgBsDsDYield_11_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12_Kpipi("parBkgBsDsDYield_12_Kpipi","parBkgBsDsDYield_12_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11_KKpi("parBkgBsDsDYield_11_KKpi","parBkgBsDsDYield_11_KKpi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12_KKpi("parBkgBsDsDYield_12_KKpi","parBkgBsDsDYield_12_KKpi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_Kpipi("parBkgBsDsDYield_Kpipi","parBkgBsDsDYield_Kpipi",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_KKpi("parBkgBsDsDYield_KKpi","parBkgBsDsDYield_KKpi",150,0,2000);
  RooRealVar        parBkgBsDsDYield_11("parBkgBsDsDYield_11","parBkgBsDsDYield_11",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12("parBkgBsDsDYield_12","parBkgBsDsDYield_12",1000,0,2000);
  RooRealVar        parBkgBsDsDYield("parBkgBsDsDYield","parBkgBsDsDYield",1000,0,2000);
  RooRealVar        parSigBsYield_11_Kpipi("parSigBsYield_11_Kpipi","parSigBsYield_11_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_12_Kpipi("parSigBsYield_12_Kpipi","parSigBsYield_12_Kpipi",100,0,1000);
  RooRealVar        parSigBsYield_11_KKpi("parSigBsYield_11_KKpi","parSigBsYield_11_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_12_KKpi("parSigBsYield_12_KKpi","parSigBsYield_12_KKpi",100,0,1000);
  RooRealVar        parSigBsYield_Kpipi("parSigBsYield_Kpipi","parSigBsYield_Kpipi",300,0,1000);
  RooRealVar        parSigBsYield_KKpi("parSigBsYield_KKpi","parSigBsYield_KKpi",50,0,1000);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgYield_11_Kpipi("parBkgYield_11_Kpipi","parBkgYield_11_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_12_Kpipi("parBkgYield_12_Kpipi","parBkgYield_12_Kpipi",5000,0,10000);
  RooRealVar        parBkgYield_11_KKpi("parBkgYield_11_KKpi","parBkgYield_11_KKpi",5000,0,10000);
  RooRealVar        parBkgYield_12_KKpi("parBkgYield_12_KKpi","parBkgYield_12_KKpi",5000,0,10000);
  RooRealVar        parBkgYield_Kpipi("parBkgYield_Kpipi","parBkgYield_Kpipi",1800,0,10000);
  RooRealVar        parBkgYield_KKpi("parBkgYield_KKpi","parBkgYield_KKpi",700,0,10000);
  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend_11_Kpipi("pdfSigExtend_11_Kpipi","pdfSigExtend_11_Kpipi",pdfSigMass,parSigYield_11_Kpipi);
  RooExtendPdf      pdfSigExtend_12_Kpipi("pdfSigExtend_12_Kpipi","pdfSigExtend_12_Kpipi",pdfSigMass,parSigYield_12_Kpipi);
  RooExtendPdf      pdfSigExtend_11_KKpi("pdfSigExtend_11_KKpi","pdfSigExtend_11_KKpi",pdfSigMass,parSigYield_11_KKpi);
  RooExtendPdf      pdfSigExtend_12_KKpi("pdfSigExtend_12_KKpi","pdfSigExtend_12_KKpi",pdfSigMass,parSigYield_12_KKpi);
  RooExtendPdf      pdfSigExtend_Kpipi("pdfSigExtend_Kpipi","pdfSigExtend_Kpipi",pdfSigMass,parSigYield_Kpipi);
  RooExtendPdf      pdfSigExtend_KKpi("pdfSigExtend_KKpi","pdfSigExtend_KKpi",pdfSigMass,parSigYield_KKpi);
  RooExtendPdf      pdfSigExtend_11("pdfSigExtend_11","pdfSigExtend_11",pdfSigMass,parSigYield_11);
  RooExtendPdf      pdfSigExtend_12("pdfSigExtend_12","pdfSigExtend_12",pdfSigMass,parSigYield_12);
  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);
  RooExtendPdf      pdfBkgDsDExtend_11_Kpipi("pdfBkgDsDExtend_11_Kpipi","pdfBkgDsDExtend_11_Kpipi",pdfBkgDsDMass,parBkgDsDYield_11_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_12_Kpipi("pdfBkgDsDExtend_12_Kpipi","pdfBkgDsDExtend_12_Kpipi",pdfBkgDsDMass,parBkgDsDYield_12_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_11_KKpi("pdfBkgDsDExtend_11_KKpi","pdfBkgDsDExtend_11_KKpi",pdfBkgDsDMass,parBkgDsDYield_11_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_12_KKpi("pdfBkgDsDExtend_12_KKpi","pdfBkgDsDExtend_12_KKpi",pdfBkgDsDMass,parBkgDsDYield_12_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_Kpipi("pdfBkgDsDExtend_Kpipi","pdfBkgDsDExtend_Kpipi",pdfBkgDsDMass,parBkgDsDYield_Kpipi);
  RooExtendPdf      pdfBkgDsDExtend_KKpi("pdfBkgDsDExtend_KKpi","pdfBkgDsDExtend_KKpi",pdfBkgDsDMass,parBkgDsDYield_KKpi);
  RooExtendPdf      pdfBkgDsDExtend_11("pdfBkgDsDExtend_11","pdfBkgDsDExtend_11",pdfBkgDsDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfBkgDsDExtend_12("pdfBkgDsDExtend_12","pdfBkgDsDExtend_12",pdfBkgDsDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfBkgDsDExtend("pdfBkgDsDExtend","pdfBkgDsDExtend",pdfBkgDsDMass,parBkgDsDYield);
  RooExtendPdf      pdfBkgBsDsDExtend_11_Kpipi("pdfBkgBsDsDExtend_11_Kpipi","pdfBkgBsDsDExtend_11_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_11_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_12_Kpipi("pdfBkgBsDsDExtend_12_Kpipi","pdfBkgBsDsDExtend_12_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_12_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_11_KKpi("pdfBkgBsDsDExtend_11_KKpi","pdfBkgBsDsDExtend_11_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_11_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_12_KKpi("pdfBkgBsDsDExtend_12_KKpi","pdfBkgBsDsDExtend_12_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_12_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_Kpipi("pdfBkgBsDsDExtend_Kpipi","pdfBkgBsDsDExtend_Kpipi",pdfBkgBsDsDMass,parBkgBsDsDYield_Kpipi);
  RooExtendPdf      pdfBkgBsDsDExtend_KKpi("pdfBkgBsDsDExtend_KKpi","pdfBkgBsDsDExtend_KKpi",pdfBkgBsDsDMass,parBkgBsDsDYield_KKpi);
  RooExtendPdf      pdfBkgBsDsDExtend_11("pdfBkgBsDsDExtend_11","pdfBkgBsDsDExtend_11",pdfBkgBsDsDMass,parBkgBsDsDYield_11);
  RooExtendPdf      pdfBkgBsDsDExtend_12("pdfBkgBsDsDExtend_12","pdfBkgBsDsDExtend_12",pdfBkgBsDsDMass,parBkgBsDsDYield_12);
  RooExtendPdf      pdfBkgBsDsDExtend("pdfBkgBsDsDExtend","pdfBkgBsDsDExtend",pdfBkgBsDsDMass,parBkgBsDsDYield);
  RooExtendPdf      pdfSigBsExtend_11_Kpipi("pdfSigBsExtend_11_Kpipi","pdfSigBsExtend_11_Kpipi",pdfSigBsMass,parSigBsYield_11_Kpipi);
  RooExtendPdf      pdfSigBsExtend_12_Kpipi("pdfSigBsExtend_12_Kpipi","pdfSigBsExtend_12_Kpipi",pdfSigBsMass,parSigBsYield_12_Kpipi);
  RooExtendPdf      pdfSigBsExtend_11_KKpi("pdfSigBsExtend_11_KKpi","pdfSigBsExtend_11_KKpi",pdfSigBsMass,parSigBsYield_11_KKpi);
  RooExtendPdf      pdfSigBsExtend_12_KKpi("pdfSigBsExtend_12_KKpi","pdfSigBsExtend_12_KKpi",pdfSigBsMass,parSigBsYield_12_KKpi);
  RooExtendPdf      pdfSigBsExtend_Kpipi("pdfSigBsExtend_Kpipi","pdfSigBsExtend_Kpipi",pdfSigBsMass,parSigBsYield_Kpipi);
  RooExtendPdf      pdfSigBsExtend_KKpi("pdfSigBsExtend_KKpi","pdfSigBsExtend_KKpi",pdfSigBsMass,parSigBsYield_KKpi);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend_11_Kpipi("pdfBkgExtend_11_Kpipi","pdfBkgExtend_11_Kpipi",pdfBkgMass_Kpipi,parBkgYield_11_Kpipi);
  RooExtendPdf      pdfBkgExtend_12_Kpipi("pdfBkgExtend_12_Kpipi","pdfBkgExtend_12_Kpipi",pdfBkgMass_Kpipi,parBkgYield_12_Kpipi);
  RooExtendPdf      pdfBkgExtend_11_KKpi("pdfBkgExtend_11_KKpi","pdfBkgExtend_11_KKpi",pdfBkgMass_KKpi,parBkgYield_11_KKpi);
  RooExtendPdf      pdfBkgExtend_12_KKpi("pdfBkgExtend_12_KKpi","pdfBkgExtend_12_KKpi",pdfBkgMass_KKpi,parBkgYield_12_KKpi);
  RooExtendPdf      pdfBkgExtend_Kpipi("pdfBkgExtend_Kpipi","pdfBkgExtend_Kpipi",pdfBkgMass_Kpipi,parBkgYield_Kpipi);
  RooExtendPdf      pdfBkgExtend_KKpi("pdfBkgExtend_KKpi","pdfBkgExtend_KKpi",pdfBkgMass_KKpi,parBkgYield_KKpi);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass_11_Kpipi("pdfMass_11_Kpipi","Mass PDF",RooArgList(pdfSigExtend_11_Kpipi,pdfBkgDsDExtend_11_Kpipi,pdfSigBsExtend_11_Kpipi,pdfBkgExtend_11_Kpipi,pdfBkgBsDsDExtend_11_Kpipi));
  RooAddPdf         pdfMass_12_Kpipi("pdfMass_12_Kpipi","Mass PDF",RooArgList(pdfSigExtend_12_Kpipi,pdfBkgDsDExtend_12_Kpipi,pdfSigBsExtend_12_Kpipi,pdfBkgExtend_12_Kpipi,pdfBkgBsDsDExtend_12_Kpipi));
  RooAddPdf         pdfMass_11_KKpi("pdfMass_11_KKpi","Mass PDF",RooArgList(pdfSigExtend_11_KKpi,pdfBkgDsDExtend_11_KKpi,pdfSigBsExtend_11_KKpi,pdfBkgExtend_11_KKpi,pdfBkgBsDsDExtend_11_KKpi));
  RooAddPdf         pdfMass_12_KKpi("pdfMass_12_KKpi","Mass PDF",RooArgList(pdfSigExtend_12_KKpi,pdfBkgDsDExtend_12_KKpi,pdfSigBsExtend_12_KKpi,pdfBkgExtend_12_KKpi,pdfBkgBsDsDExtend_12_KKpi));
  RooAddPdf         pdfMass_Kpipi("pdfMass_Kpipi","Mass PDF",RooArgList(pdfSigExtend_Kpipi,pdfBkgDsDExtend_Kpipi,pdfSigBsExtend_Kpipi,pdfBkgExtend_Kpipi,pdfBkgBsDsDExtend_Kpipi));
  RooAddPdf         pdfMass_KKpi("pdfMass_KKpi","Mass PDF",RooArgList(pdfSigExtend_KKpi,pdfBkgDsDExtend_KKpi,pdfSigBsExtend_KKpi,pdfBkgExtend_KKpi,pdfBkgBsDsDExtend_KKpi));
  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11,pdfBkgBsDsDExtend_11));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12,pdfBkgBsDsDExtend_12));

  RooSuperCategory  supercategory_mass("supercategory_mass","supercategory_mass",RooArgList(catYear,catDDFinalStateParticles));
  RooAbsPdf*        pdfMass;

  if (split_years) {
    if (split_final_state) {
      pdfMass = new RooSimultaneous("pdfMass","pdfMass",supercategory_mass);
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11_Kpipi,"{2011;Kpipi}");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12_Kpipi,"{2012;Kpipi}");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11_KKpi,"{2011;KKpi}");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12_KKpi,"{2012;KKpi}");
    }
    else {
      pdfMass = new RooSimultaneous("pdfMass","pdfMass",catYear);
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11,"2011");
      ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12,"2012");
    }
  }
  else if (split_final_state) {
    pdfMass = new RooSimultaneous("pdfMass","pdfMass",catDDFinalStateParticles);
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_Kpipi,"Kpipi");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_KKpi,"KKpi");
  }
  else  pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend/*,pdfBkgBsDsDExtend*/));

//=========================================================================================================================================================================================================================

  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","migrad"))));
  fitting_args.Add((TObject*)(new RooCmdArg(Offset(config.getBool("offset")))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  if (massfit) {
    pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_CharmlessBackground.txt");
    pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/CharmlessBackground/StartingValues.new");

    RooFitResult* fit_result = pdfMass->fitTo(*data, fitting_args);
    doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result);
    fitresultprinter.Print();
    pdfMass->getParameters(data)->writeToFile(TString("/home/fmeier/storage03/b02dd/run/CharmlessBackground/FitResults_"+config.getString("identifier")+".txt"));

    PlotConfig cfg_plot_mass("cfg_plot_mass");
    cfg_plot_mass.InitializeOptions();
    cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/CharmlessBackground/Plots/"+config.getString("identifier"));
    cfg_plot_mass.set_simultaneous_plot_all_categories(true);
    // cfg_plot_mass.set_label_text("#splitline{LHCb 3fb^{-1}}{inoffiziell}");
    // cfg_plot_mass.set_y_axis_label("Kandidaten");
    std::vector<std::string> components_mass;
    components_mass += "pdfSigExtend.*", "pdfBkgDsDExtend.*", "pdfSigBsExtend.*", "pdfBkgExtend.*", "pdfBkgBsDsDExtend.*";
    Plot* Mass;
    if (split_years || split_final_state) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, *data, *((RooSimultaneous*)pdfMass), components_mass);
    else Mass = new Plot(cfg_plot_mass, obsMass, *data, *pdfMass, components_mass);
    Mass->set_scaletype_x(kLinear);
    Mass->set_scaletype_y(kBoth);
    Mass->PlotIt();
  }
  return 0;
}
