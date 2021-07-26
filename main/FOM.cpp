#include <iostream>
#include <sstream>
#include <algorithm>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TMinuit.h"
#include "TMarker.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TAxis.h"

//from RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooConstVar.h"
#include "RooBinning.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "RooMinuit.h"
#include "RooHist.h"

// from RooFit PDFs
#include "RooExponential.h"
#include "RooLognormal.h"
#include "RooGaussian.h"
#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooSimultaneous.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooCBShape.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"
#include "doocore/io/Progress.h"

// from DooFit
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
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

void SetGraphStyle(TGraph* graph, TString title = "Graph", int linecolor = 1, int markercolor = 1, int linestyle = 1, int markerstyle = 20);

int main(int argc, char * argv[]){
  if (argc < 2) {
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  gStyle->SetTitleOffset(1.15,"Y");
  gStyle->SetPadLeftMargin(0.16);
  TCanvas c("c","c",800,600);

  int num_cpu = config.getInt("num_cpu");
  TString taggingcategory = config.getString("taggingcategory");
  TString OS_tagger = config.getString("OS_tagger");
  TString SS_tagger = config.getString("SS_tagger");
  TString FOM_tagger = config.getString("FOM_tagger");
  bool OS_tagging = config.getBool("OS_tagging");
  bool SS_tagging = config.getBool("SS_tagging");
  bool split_years      = config.getBool("split_years");
  bool fits = config.getBool("fits");

  std::string cut = config.getString("cut");

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");
  RooRealVar        obsEtaOS("obsEta"+OS_tagger,"#eta_{OS}",0.,0.5);
  RooRealVar        obsEtaSS("obsEta"+SS_tagger,"#eta_{SS}",0.,0.5);
  RooRealVar        obsEta_combined("obsEta_combined","#eta_{OSSS}",0.,0.5);
  RooRealVar        obsTimeErr("obsTimeErr","#sigma_{t}",0.005,0.2,"ps");
  RooCategory       obsTagOS("obsTag"+OS_tagger+"_NoZero","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  RooCategory       obsTagSS("obsTag"+SS_tagger+"_NoZero","Flavour Tag");
  obsTagSS.defineType("B0",1);
  obsTagSS.defineType("B0bar",-1);
  RooCategory       obsTag_combined("obsTag_combined","combined OS + SS tag");
  obsTag_combined.defineType("B0",1);
  obsTag_combined.defineType("B0bar",-1);
  RooCategory       catTagged_combined("catTagged_combined","tagged by combination of OS and SS");
  catTagged_combined.defineType("tagged",1);
  catTagged_combined.defineType("untagged",0);
  RooCategory       obsTagOS_wZero("obsTag"+OS_tagger,"Flavour Tag");
  obsTagOS_wZero.defineType("B0",1);
  obsTagOS_wZero.defineType("B0bar",-1);
  obsTagOS_wZero.defineType("untagged",0);
  RooCategory       obsTagSS_wZero("obsTag"+SS_tagger,"Flavour Tag");
  obsTagSS_wZero.defineType("B0",1);
  obsTagSS_wZero.defineType("B0bar",-1);
  obsTagSS_wZero.defineType("untagged",0);
  
  RooCategory       catYear("catYear","year of data taking");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);
  RooCategory       catTag(taggingcategory,"OS or SS tagged");
  if (OS_tagging)   catTag.defineType("OS",1);
  if (SS_tagging)   catTag.defineType("SS",-1);
  if (OS_tagging && SS_tagging)   catTag.defineType("both",10);
  catTag.defineType("untagged",0);
  RooCategory       catDDFinalStateParticles("catDDFinalStateParticles","catDDFinalStateParticles");
  catDDFinalStateParticles.defineType("Kpipi",1);
  catDDFinalStateParticles.defineType("KKpi",0);

  RooRealVar        BDT_classifier(TString(config.getString("bdt_classifier")+"_classifier"),"BDT_classifier",-1,1);

  RooArgSet         observables(obsTime,obsMass,"observables");
  observables.add(BDT_classifier);
  observables.add(obsTimeErr);
  observables.add(obsEtaOS);
  observables.add(obsEtaSS);
  observables.add(obsTagOS);
  observables.add(obsTagSS);
  observables.add(obsTagOS_wZero);
  observables.add(obsTagSS_wZero);
  observables.add(RooArgSet(obsTag_combined,obsEta_combined,catTagged_combined));
  RooArgSet         categories(catYear,catTag,catDDFinalStateParticles,"categories");

  // Get data set
  EasyTuple         tuple(config.getString("tuple"),config.getString("tree"),RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet*       data = &(tuple.ConvertToDataSet(Cut(TString(cut))));
  data->Print();

//=========================================================================================================================================================================================================================

  // Mass PDF
  // Signal
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");
  RooRealVar        parSigMassSigma("parSigMassSigma","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
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

  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11("parBkgBsDsDYield_11","parBkgBsDsDYield_11",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_12("parBkgBsDsDYield_12","parBkgBsDsDYield_12",1000,0,2000);
  RooRealVar        parBkgBsDsDYield("parBkgBsDsDYield","parBkgBsDsDYield",1000,0,2000);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend_11("pdfSigExtend_11","pdfSigExtend_11",pdfSigMass,parSigYield_11);
  RooExtendPdf      pdfSigExtend_12("pdfSigExtend_12","pdfSigExtend_12",pdfSigMass,parSigYield_12);
  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);
  RooExtendPdf      pdfBkgDsDExtend_11("pdfBkgDsDExtend_11","pdfBkgDsDExtend_11",pdfBkgDsDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfBkgDsDExtend_12("pdfBkgDsDExtend_12","pdfBkgDsDExtend_12",pdfBkgDsDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfBkgDsDExtend("pdfBkgDsDExtend","pdfBkgDsDExtend",pdfBkgDsDMass,parBkgDsDYield);
  RooExtendPdf      pdfBkgBsDsDExtend_11("pdfBkgBsDsDExtend_11","pdfBkgBsDsDExtend_11",pdfBkgBsDsDMass,parBkgBsDsDYield_11);
  RooExtendPdf      pdfBkgBsDsDExtend_12("pdfBkgBsDsDExtend_12","pdfBkgBsDsDExtend_12",pdfBkgBsDsDMass,parBkgBsDsDYield_12);
  RooExtendPdf      pdfBkgBsDsDExtend("pdfBkgBsDsDExtend","pdfBkgBsDsDExtend",pdfBkgBsDsDMass,parBkgBsDsDYield);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11,pdfBkgBsDsDExtend_11));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12,pdfBkgBsDsDExtend_12));

  RooAbsPdf*        pdfMass;

  if (split_years) {
    pdfMass = new RooSimultaneous("pdfMass","pdfMass",catYear);
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_11,"2011");
    ((RooSimultaneous*)pdfMass)->addPdf(pdfMass_12,"2012");
  }
  else  pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend,pdfBkgBsDsDExtend));

//=========================================================================================================================================================================================================================

  pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  pdfMass->getParameters(data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/Mass/StartingValues_Mass.new");

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_simultaneous_plot_all_categories(true);
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend.*", "pdfBkgDsDExtend.*", "pdfSigBsExtend.*", "pdfBkgExtend.*", "pdfBkgBsDsDExtend.*";
  Plot* Mass;

  RooDataSet* reduced_data;
  RooDataSet* reduced_data_sweighted;
  obsMass.setRange("signal",5250,5310);
  std::vector<double> bdt_cut;
  std::vector<double> eff_sig_size;
  std::vector<double> eff_sig_size_normalized;
  double eff_sig_size_value = 0.;
  std::vector<double> tagging_power;
  std::vector<double> tagging_power_normalized;
  double tagging_power_value = 0.;
  std::vector<double> resolution_dilution;
  std::vector<double> resolution_dilution_normalized;
  double resolution_dilution_value = 0.;
  std::vector<double> sin2beta_term;
  std::vector<double> sin2beta_term_normalized;
  double sin2beta_term_value = 0.;
  std::vector<double> sinphi_term;
  std::vector<double> sinphi_term_normalized;
  double sinphi_term_value = 0.;
  std::vector<double> FOM_wo_sin2beta_term;
  std::vector<double> FOM_wo_sin2beta_term_normalized;
  double FOM_wo_sin2beta_term_value = 0.;
  std::vector<double> full_FOM;
  std::vector<double> full_FOM_normalized;
  double full_FOM_value = 0.;
  std::vector<double> full_sinphi_FOM;
  std::vector<double> full_sinphi_FOM_normalized;
  double full_sinphi_FOM_value = 0.;
  SPlotFit2* splotfit;
  RooArgSet set_of_yields;
  if (split_years) {
    set_of_yields.add(RooArgSet(parSigYield_11,parBkgDsDYield_11,parSigBsYield_11,parBkgYield_11,parBkgBsDsDYield_11));
    set_of_yields.add(RooArgSet(parSigYield_12,parBkgDsDYield_12,parSigBsYield_12,parBkgYield_12,parBkgBsDsDYield_12));
  }
  else set_of_yields.add(RooArgSet(parSigYield,parBkgDsDYield,parSigBsYield,parBkgYield,parBkgBsDsDYield));

  double scan_begin = config.getDouble("scan_begin");
  double scan_end = config.getDouble("scan_end");
  int n_steps = config.getInt("n_steps");
  double scan_width = (scan_end - scan_begin)/n_steps;
  double weight = 0.;
  double tagging_dilution = 0.;
  double resolution_dilution_exp = 0.;
  double time = 0.;
  double dmd = 0.51;
  double sin2beta = 0.7;
  double sinphi = 0.55;
  double lambda = 0.75;

  if (fits) {
  	for (int i = 0; i <= n_steps; ++i) {
      double cutvalue = scan_begin + i*scan_width;
      cout << cutvalue  << endl;
      reduced_data = dynamic_cast<RooDataSet*>(data->reduce(TString(config.getString("bdt_classifier")+"_classifier>"+to_string(cutvalue))));
      pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
      reduced_data->Print();
      splotfit = new SPlotFit2(*pdfMass,*reduced_data,set_of_yields);
      splotfit->set_use_minos(config.getBool("minos"));
      splotfit->set_num_cpu(config.getInt("num_cpu"));
      RooMsgService::instance().setStreamStatus(0, false);
      RooMsgService::instance().setStreamStatus(1, false);
      splotfit->Fit();
      RooMsgService::instance().setStreamStatus(0, true);
      RooMsgService::instance().setStreamStatus(1, true);
      splotfit->WriteParametersFile("/home/fmeier/lhcb-tank/b02dd/run/FOM/FitResults_"+to_string(cutvalue)+".txt");
      cfg_plot_mass.set_plot_directory("/home/fmeier/lhcb-tank/b02dd/run/FOM/Plots/"+to_string(cutvalue));
      if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, *reduced_data, *((RooSimultaneous*)pdfMass), components_mass, "obsMass");
      else Mass = new Plot(cfg_plot_mass, obsMass, *reduced_data, *pdfMass, components_mass, "obsMass");
      Mass->set_scaletype_x(kLinear);
      Mass->set_scaletype_y(kBoth);
      Mass->PlotIt();
      if (split_years) reduced_data_sweighted = new RooDataSet("reduced_data_sweighted","reduced_data_sweighted",reduced_data,*(reduced_data->get()),TString(catTag.GetName())+"!=0","parSigYield_11_sw+parSigYield_12_sw");
      else reduced_data_sweighted = new RooDataSet("reduced_data_sweighted","reduced_data_sweighted",reduced_data,*(reduced_data->get()),TString(catTag.GetName())+"!=0","parSigYield_sw");
      reduced_data_sweighted->Print();
      bdt_cut += cutvalue;
      for (int j = 0; j < reduced_data_sweighted->numEntries(); ++j) {
        reduced_data_sweighted->get(j);
        weight = reduced_data_sweighted->weight();
        eff_sig_size_value += pow(weight,2);
        tagging_dilution = (1. - 2.*reduced_data_sweighted->get()->getRealValue("obsEta"+FOM_tagger));
        tagging_power_value += weight*pow(tagging_dilution,2);
        resolution_dilution_exp = exp(-pow(dmd*reduced_data_sweighted->get()->getRealValue("obsTimeErr"),2));
        resolution_dilution_value += weight*resolution_dilution_exp;
        time = reduced_data_sweighted->get()->getRealValue("obsTime");
        sin2beta_term_value += weight*pow(sin(dmd*time)/(1+reduced_data_sweighted->get()->getCatIndex("obsTag"+FOM_tagger)*tagging_dilution*sin2beta*resolution_dilution_exp*sin(dmd*time)),2);
        sinphi_term_value += weight*pow(2*lambda*sin(dmd*time)/(1+pow(lambda,2)+reduced_data_sweighted->get()->getCatIndex("obsTag"+FOM_tagger)*tagging_dilution*resolution_dilution_exp*(-2*lambda*sinphi*sin(dmd*time)-(1-pow(lambda,2))*cos(dmd*time))),2);
        FOM_wo_sin2beta_term_value += weight*pow(tagging_dilution,2)*resolution_dilution_exp;
        full_FOM_value += weight*pow(tagging_dilution,2)*resolution_dilution_exp*pow(sin(dmd*time)/(1+reduced_data_sweighted->get()->getCatIndex("obsTag"+FOM_tagger)*tagging_dilution*sin2beta*resolution_dilution_exp*sin(dmd*time)),2);
        full_sinphi_FOM_value += weight*pow(tagging_dilution,2)*resolution_dilution_exp*pow(2*lambda*sin(dmd*time)/(1+pow(lambda,2)+reduced_data_sweighted->get()->getCatIndex("obsTag"+FOM_tagger)*tagging_dilution*resolution_dilution_exp*(-2*lambda*sinphi*sin(dmd*time)-(1-pow(lambda,2))*cos(dmd*time))),2);
        // if (j%1000 == 0) {
        // 	cout <<	"weight = "	<<	weight 	<<	endl;
        // 	cout <<	"decay time = "	<<	time 	<<	endl;
        // 	cout <<	"tag = "	<<	reduced_data_sweighted->get()->getCatIndex("obsTag"+FOM_tagger) 	<<	endl;
        // 	cout << "tagging dilution = "	<<	tagging_dilution	<<	endl;
        // 	cout << "resolution dilution = "	<<	resolution_dilution_exp	<<	endl;
        // 	cout << "sin2beta term = "	<<	weight*pow(sin(dmd*time)/(1+reduced_data_sweighted->get()->getCatIndex("obsTag"+FOM_tagger)*tagging_dilution*sin2beta*resolution_dilution_exp*sin(dmd*time)),2)	<<	endl;
        // 	cout <<	"sinphi term = "	<<	weight*pow(2*lambda*sin(dmd*time)/(1+pow(lambda,2)+reduced_data_sweighted->get()->getCatIndex("obsTag"+FOM_tagger)*tagging_dilution*resolution_dilution_exp*(-2*lambda*sinphi*sin(dmd*time)-(1-pow(lambda,2))*cos(dmd*time))),2)	<<	endl;
        // }
      }
      eff_sig_size += pow(reduced_data_sweighted->sumEntries(),2)/eff_sig_size_value;
      tagging_power += tagging_power_value/reduced_data_sweighted->sumEntries();
      resolution_dilution += resolution_dilution_value/reduced_data_sweighted->sumEntries();
      sin2beta_term += sin2beta_term_value/reduced_data_sweighted->sumEntries();
      sinphi_term += sinphi_term_value/reduced_data_sweighted->sumEntries();
      FOM_wo_sin2beta_term += FOM_wo_sin2beta_term_value*reduced_data_sweighted->sumEntries()/eff_sig_size_value;
      full_FOM += full_FOM_value*reduced_data_sweighted->sumEntries()/eff_sig_size_value;
      full_sinphi_FOM += full_sinphi_FOM_value*reduced_data_sweighted->sumEntries()/eff_sig_size_value;
      eff_sig_size_value = 0.;
      tagging_power_value = 0.;
      resolution_dilution_value = 0.;
      sin2beta_term_value = 0.;
      sinphi_term_value = 0.;
      FOM_wo_sin2beta_term_value = 0.;
      full_FOM_value = 0.;
      full_sinphi_FOM_value = 0.;
      delete reduced_data_sweighted;
    }
    double max_eff_sig_size = *max_element(begin(eff_sig_size),end(eff_sig_size));
    double max_tagging_power = *max_element(begin(tagging_power),end(tagging_power));
    double max_resolution_dilution = *max_element(begin(resolution_dilution),end(resolution_dilution));
    double max_sin2beta_term = *max_element(begin(sin2beta_term),end(sin2beta_term));
    double max_sinphi_term = *max_element(begin(sinphi_term),end(sinphi_term));
    double max_FOM_wo_sin2beta_term = *max_element(begin(FOM_wo_sin2beta_term),end(FOM_wo_sin2beta_term));
    double max_full_FOM = *max_element(begin(full_FOM),end(full_FOM));
    double max_full_sinphi_FOM = *max_element(begin(full_sinphi_FOM),end(full_sinphi_FOM));
    for (int i = 0; i < eff_sig_size.size(); ++i) {
      eff_sig_size_normalized += eff_sig_size[i]/max_eff_sig_size;
      tagging_power_normalized += tagging_power[i]/max_tagging_power;
      resolution_dilution_normalized += resolution_dilution[i]/max_resolution_dilution;
      sin2beta_term_normalized += sin2beta_term[i]/max_sin2beta_term;
      sinphi_term_normalized += sinphi_term[i]/max_sinphi_term;
      FOM_wo_sin2beta_term_normalized += FOM_wo_sin2beta_term[i]/max_FOM_wo_sin2beta_term;
      full_FOM_normalized += full_FOM[i]/max_full_FOM;
      full_sinphi_FOM_normalized += full_sinphi_FOM[i]/max_full_sinphi_FOM;
    }
    TGraph* gr_eff_sig_size = new TGraph(eff_sig_size.size(), &bdt_cut[0], &eff_sig_size[0]);
    TGraph* gr_eff_sig_size_normalized = new TGraph(eff_sig_size_normalized.size(), &bdt_cut[0], &eff_sig_size_normalized[0]);
    gr_eff_sig_size->SetLineColor(2);
    gr_eff_sig_size->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_eff_sig_size->GetYaxis()->SetTitle("effective signal size");
    gr_eff_sig_size->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_eff_sig_size->Draw("APL");
    printPlot(&c, "SignalSize", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));

    TGraph* gr_tagging_power = new TGraph(tagging_power.size(), &bdt_cut[0], &tagging_power[0]);
    TGraph* gr_tagging_power_normalized = new TGraph(tagging_power_normalized.size(), &bdt_cut[0], &tagging_power_normalized[0]);
    gr_tagging_power->SetLineColor(2);
    gr_tagging_power->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_tagging_power->GetYaxis()->SetTitle("tagging power");
    gr_tagging_power->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_tagging_power->Draw("APL");
    printPlot(&c, "TaggingPower", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));

    TGraph* gr_resolution_dilution = new TGraph(resolution_dilution.size(), &bdt_cut[0], &resolution_dilution[0]);
    TGraph* gr_resolution_dilution_normalized = new TGraph(resolution_dilution_normalized.size(), &bdt_cut[0], &resolution_dilution_normalized[0]);
    gr_resolution_dilution->SetLineColor(2);
    gr_resolution_dilution->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_resolution_dilution->GetYaxis()->SetTitle("dilution from resolution");
    gr_resolution_dilution->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_resolution_dilution->Draw("APL");
    printPlot(&c, "ResolutionDilution", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));

    TGraph* gr_sin2beta = new TGraph(sin2beta_term.size(), &bdt_cut[0], &sin2beta_term[0]);
    TGraph* gr_sin2beta_normalized = new TGraph(sin2beta_term_normalized.size(), &bdt_cut[0], &sin2beta_term_normalized[0]);
    gr_sin2beta->SetLineColor(2);
    gr_sin2beta->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_sin2beta->GetYaxis()->SetTitle("sin(2#beta) sensitivity");
    gr_sin2beta->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_sin2beta->Draw("APL");
    printPlot(&c, "Sin2BetaTerm", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));

    TGraph* gr_sinphi = new TGraph(sinphi_term.size(), &bdt_cut[0], &sinphi_term[0]);
    TGraph* gr_sinphi_normalized = new TGraph(sinphi_term_normalized.size(), &bdt_cut[0], &sinphi_term_normalized[0]);
    gr_sinphi->SetLineColor(2);
    gr_sinphi->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    gr_sinphi->GetYaxis()->SetTitle("sin(#phi) sensitivity");
    gr_sinphi->GetXaxis()->SetLimits(scan_begin,scan_end);
    gr_sinphi->Draw("APL");
    printPlot(&c, "SinPhiTerm", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));

    TGraph* gr_FOM_wo_sin2beta_term = new TGraph(FOM_wo_sin2beta_term.size(), &bdt_cut[0], &FOM_wo_sin2beta_term[0]);
    TGraph* gr_FOM_wo_sin2beta_term_normalized = new TGraph(FOM_wo_sin2beta_term_normalized.size(), &bdt_cut[0], &FOM_wo_sin2beta_term_normalized[0]);
    TGraph* gr_full_FOM = new TGraph(full_FOM.size(), &bdt_cut[0], &full_FOM[0]);
    TGraph* gr_full_FOM_normalized = new TGraph(full_FOM_normalized.size(), &bdt_cut[0], &full_FOM_normalized[0]);
    TGraph* gr_full_sinphi_FOM = new TGraph(full_sinphi_FOM.size(), &bdt_cut[0], &full_sinphi_FOM[0]);
    TGraph* gr_full_sinphi_FOM_normalized = new TGraph(full_sinphi_FOM_normalized.size(), &bdt_cut[0], &full_sinphi_FOM_normalized[0]);

    TMultiGraph* mg = new TMultiGraph();
    SetGraphStyle(gr_eff_sig_size_normalized,"eff signal size");
    mg->Add(gr_eff_sig_size_normalized);
    SetGraphStyle(gr_tagging_power_normalized,"tagging power",2,2);;
    mg->Add(gr_tagging_power_normalized);
    SetGraphStyle(gr_resolution_dilution_normalized,"resolution dilution",3,3);
    mg->Add(gr_resolution_dilution_normalized);
    SetGraphStyle(gr_sin2beta_normalized,"decay time term",4,4);
    mg->Add(gr_sin2beta_normalized);
    SetGraphStyle(gr_sinphi_normalized,"alternative decay time term",7,7);
    mg->Add(gr_sinphi_normalized);
    SetGraphStyle(gr_FOM_wo_sin2beta_term_normalized, "w/o sine term",5,5);
    mg->Add(gr_FOM_wo_sin2beta_term_normalized);
    SetGraphStyle(gr_full_FOM_normalized, "full FOM",6,6);
    mg->Add(gr_full_FOM_normalized);
    SetGraphStyle(gr_full_sinphi_FOM_normalized, "full sin#phi FOM",8,8);
    mg->Add(gr_full_sinphi_FOM_normalized);
    mg->Draw("APL");
    mg->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    mg->GetYaxis()->SetTitle("");
    mg->SetMinimum(0.5);
    mg->SetMaximum(1.1);
    c.BuildLegend(0.25,0.2,0.5,0.5);
    printPlot(&c, "Summary", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));

    TFile file("/home/fmeier/lhcb-tank/b02dd/run/FOM/FOM_graphs.root","recreate");
    gr_eff_sig_size->Write("gr_eff_sig_size");
    gr_eff_sig_size_normalized->Write("gr_eff_sig_size_normalized");
    gr_tagging_power->Write("gr_tagging_power");
		gr_tagging_power_normalized->Write("gr_tagging_power_normalized");
		gr_resolution_dilution->Write("gr_resolution_dilution");
		gr_resolution_dilution_normalized->Write("gr_resolution_dilution_normalized");
		gr_sin2beta->Write("gr_sin2beta");
		gr_sin2beta_normalized->Write("gr_sin2beta_normalized");
		gr_sinphi->Write("gr_sinphi");
		gr_sinphi_normalized->Write("gr_sinphi_normalized");
		gr_FOM_wo_sin2beta_term->Write("gr_FOM_wo_sin2beta_term");
		gr_FOM_wo_sin2beta_term_normalized->Write("gr_FOM_wo_sin2beta_term_normalized");
		gr_full_FOM->Write("gr_full_FOM");
		gr_full_FOM_normalized->Write("gr_full_FOM_normalized");
		gr_full_sinphi_FOM->Write("gr_full_sinphi_FOM");
		gr_full_sinphi_FOM_normalized->Write("gr_full_sinphi_FOM_normalized");
		file.Close();
  }
  else {
  	TFile file("/home/fmeier/lhcb-tank/b02dd/run/FOM/FOM_graphs.root","read");
		TGraph* gr_eff_sig_size = dynamic_cast<TGraph*>(file.Get("gr_eff_sig_size"));
		TGraph* gr_eff_sig_size_normalized = dynamic_cast<TGraph*>(file.Get("gr_eff_sig_size_normalized"));
		TGraph* gr_tagging_power = dynamic_cast<TGraph*>(file.Get("gr_tagging_power"));
		TGraph* gr_tagging_power_normalized = dynamic_cast<TGraph*>(file.Get("gr_tagging_power_normalized"));
		TGraph* gr_resolution_dilution = dynamic_cast<TGraph*>(file.Get("gr_resolution_dilution"));
		TGraph* gr_resolution_dilution_normalized = dynamic_cast<TGraph*>(file.Get("gr_resolution_dilution_normalized"));
		TGraph* gr_sin2beta = dynamic_cast<TGraph*>(file.Get("gr_sin2beta"));
		TGraph* gr_sin2beta_normalized = dynamic_cast<TGraph*>(file.Get("gr_sin2beta_normalized"));
		TGraph* gr_sinphi = dynamic_cast<TGraph*>(file.Get("gr_sinphi"));
		TGraph* gr_sinphi_normalized = dynamic_cast<TGraph*>(file.Get("gr_sinphi_normalized"));
		TGraph* gr_FOM_wo_sin2beta_term = dynamic_cast<TGraph*>(file.Get("gr_FOM_wo_sin2beta_term"));
		TGraph* gr_FOM_wo_sin2beta_term_normalized = dynamic_cast<TGraph*>(file.Get("gr_FOM_wo_sin2beta_term_normalized"));
		TGraph* gr_full_FOM = dynamic_cast<TGraph*>(file.Get("gr_full_FOM"));
		TGraph* gr_full_FOM_normalized = dynamic_cast<TGraph*>(file.Get("gr_full_FOM_normalized"));
		TGraph* gr_full_sinphi_FOM = dynamic_cast<TGraph*>(file.Get("gr_full_sinphi_FOM"));
		TGraph* gr_full_sinphi_FOM_normalized = dynamic_cast<TGraph*>(file.Get("gr_full_sinphi_FOM_normalized"));
		gr_eff_sig_size->Draw("APL");
		printPlot(&c, "SignalSize", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_eff_sig_size_normalized->Draw("APL");
		printPlot(&c, "SignalSize_normalized", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_tagging_power->Draw("APL");
		printPlot(&c, "TaggingPower", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_tagging_power_normalized->Draw("APL");
		printPlot(&c, "TaggingPower_normalized", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_resolution_dilution->Draw("APL");
		printPlot(&c, "ResolutionDilution", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_resolution_dilution_normalized->Draw("APL");
		printPlot(&c, "ResolutionDilution_normalized", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_sin2beta->Draw("APL");
		printPlot(&c, "Sin2BetaTerm", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_sin2beta_normalized->Draw("APL");
		printPlot(&c, "Sin2BetaTerm_normalized", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_sinphi->Draw("APL");
		printPlot(&c, "SinPhiTerm", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		gr_sinphi_normalized->Draw("APL");
		printPlot(&c, "SinPhiTerm_normalized", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));
		TMultiGraph* mg = new TMultiGraph();
		SetGraphStyle(gr_eff_sig_size_normalized,"eff signal size");
    mg->Add(gr_eff_sig_size_normalized);
    SetGraphStyle(gr_tagging_power_normalized,"tagging power",2,2);;
    mg->Add(gr_tagging_power_normalized);
    SetGraphStyle(gr_resolution_dilution_normalized,"resolution dilution",3,3);
    mg->Add(gr_resolution_dilution_normalized);
    SetGraphStyle(gr_sin2beta_normalized,"decay time term",4,4);
    mg->Add(gr_sin2beta_normalized);
    SetGraphStyle(gr_sinphi_normalized,"alternative decay time term",7,7);
    mg->Add(gr_sinphi_normalized);
    SetGraphStyle(gr_FOM_wo_sin2beta_term_normalized, "w/o sine term",5,5);
    mg->Add(gr_FOM_wo_sin2beta_term_normalized);
    SetGraphStyle(gr_full_FOM_normalized, "full FOM",6,6);
    mg->Add(gr_full_FOM_normalized);
    SetGraphStyle(gr_full_sinphi_FOM_normalized, "full sin#phi FOM",8,8);
    mg->Add(gr_full_sinphi_FOM_normalized);
    mg->Draw("APL");
    mg->GetXaxis()->SetTitle(TString(config.getString("BDT_as_axis_title")));
    mg->GetYaxis()->SetTitle("");
    mg->SetMinimum(0.5);
    mg->SetMaximum(1.1);
    c.BuildLegend(0.25,0.2,0.5,0.5);
    printPlot(&c, "Summary", TString("/home/fmeier/lhcb-tank/b02dd/run/FOM"));	
  }

  return 0;
}

void SetGraphStyle(TGraph* graph, TString title, int linecolor, int markercolor, int linestyle, int markerstyle){
	graph->SetTitle(title);
	graph->SetLineColor(linecolor);
	graph->SetMarkerColor(markercolor);
	graph->SetLineStyle(linestyle);
	graph->SetMarkerStyle(markerstyle);
}