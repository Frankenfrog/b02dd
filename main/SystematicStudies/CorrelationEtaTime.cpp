#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "TProfile.h"
#include "TF1.h"

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

// from RooFit PDFs
#include "RooBDecay.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooSimultaneous.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooGaussModel.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "doofit/roofit/functions/CPCoefficient.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/plotting/fitresult/FitResultPrinter.h"
#include "doofit/config/CommonConfig.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStd.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStdConfig.h"
#include "doofit/fitter/splot/SPlotFit2.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

// from ToyMC
#include "configuration/ToyConfig.h"
#include "generator/ToyGenerator.h"

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;
using namespace doofit::toy;
using namespace doofit::roofit::functions;
using namespace doofit::fitter::splot;
using namespace cptoymc::configuration;
using namespace cptoymc::generator;

int main(int argc, char * argv[]){
  if (argc < 3) {
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' -c toystudy_config_file_name" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  TString method = config.getString("method");

  RooRealVar        obsMass("obsMass","#it{m_{D^{+} D^{-}}}",5150,5500,"MeV/c^{2}");
  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");
  RooRealVar        obsEtaOS("obsEtaOS","#eta_{OS}",0.,0.5);
  RooRealVar        obsEtaSS("obsEtaSS","#eta_{SS}",0.,0.5);
  RooCategory       obsTagOS("obsTagOS","Flavour Tag");
  obsTagOS.defineType("B0",1);
  obsTagOS.defineType("B0bar",-1);
  RooCategory       obsTagSS("obsTagSS","Flavour Tag");
  obsTagSS.defineType("B0",1);
  obsTagSS.defineType("B0bar",-1);
  
  RooCategory       catTag("catTaggedOSSS","OS or SS tagged");
  catTag.defineType("OS",1);
  catTag.defineType("SS",-1);
  catTag.defineType("both",10);
  // catTag.defineType("untagged",0);

  RooArgSet         observables(obsTime,obsMass,"observables");
  observables.add(obsEtaOS);
  observables.add(obsEtaSS);
  observables.add(obsTagOS);
  observables.add(obsTagSS);

  RooArgSet         categories(catTag,"categories");
  RooArgSet         Gaussian_Constraints("Gaussian_Constraints");

  // Mass PDF
  // Signal
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");
  RooRealVar        parSigMassSigma("parSigMassSigma","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  RooGaussian       pdfSigMass("pdfSigMass","Bd Mass PDF",obsMass,parSigMassMean,parSigMassSigma);

  // Bs --> DD signal
  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.35",RooArgList(parSigMassMean));
  RooGaussian       pdfSigBsMass("pdfSigBsMass","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma);

  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

//=========================================================================================================================================================================================================================

  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfSigBsExtend,pdfBkgExtend));

//=========================================================================================================================================================================================================================

  // Lifetime and mixing parameters
  RooRealVar          parSigTimeTau("parSigTimeTau","#tau",1.5,1.,2.);
  RooRealVar          parSigTimeTauMean("parSigTimeTauMean","#tau",1.519);
  RooRealVar          parSigTimeTauSigma("parSigTimeTauSigma","#tau",0.005);
  RooRealVar          parSigTimeDeltaM("parSigTimeDeltaM","#Delta m",0.510,0.4,0.6);
  RooRealVar          parSigTimeDeltaMMean("parSigTimeDeltaMMean","#Delta m",0.510);
  RooRealVar          parSigTimeDeltaMSigma("parSigTimeDeltaMSigma","#Delta m",0.004);
  RooRealVar          parSigEtaDeltaG("parSigEtaDeltaG","#Delta#Gamma",0.);

  // CPV parameters
  RooRealVar          parSigTimeSin2b("parSigTimeSin2b","#it{S_{D^{+}D^{-}}}",0.7,-2,2);
  RooRealVar          parSigTimeC("parSigTimeC","#it{C_{D^{+}D^{-}}}",0,-2,2);

  // Asymmetries
  RooRealVar          parSigEtaDeltaProd("parSigEtaDeltaProd","B0/B0bar production asymmetry",-0.0066,-0.05,0.02);
  RooRealVar          parSigEtaDeltaProdMean("parSigEtaDeltaProdMean","#bar{#mu}",-0.0066);
  RooRealVar          parSigEtaDeltaProdSigma("parSigEtaDeltaProdSigma","#sigma_{#bar{mu}}",0.0026);

  // OS tags
  RooRealVar          parSigEtaDeltaP0_OS("parSigEtaDeltaP0_OS","delta mistag probability",0.0140,0.,0.03);
  RooRealVar          parSigEtaDeltaP0Mean_OS("parSigEtaDeltaP0Mean_OS","#bar{#delta p_{0}}",0.0148);
  RooRealVar          parSigEtaDeltaP0Sigma_OS("parSigEtaDeltaP0Sigma_OS","#sigma_{#bar{#delta p_{0}}}",0.0012);  // B+ value 0.0016  Kstar 0.0031
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_OS);

  RooRealVar          parSigEtaDeltaP1_OS("parSigEtaDeltaP1_OS","delta scale calibration parameter probability",0.066,0.,0.1);
  RooRealVar          parSigEtaDeltaP1Mean_OS("parSigEtaDeltaP1Mean_OS","#bar{#delta p_{1}}",0.070);
  RooRealVar          parSigEtaDeltaP1Sigma_OS("parSigEtaDeltaP1Sigma_OS","#sigma_{#bar{#delta p_{1}}}",0.012);   // B+ value 0.018   Kstar 0.035
  Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_OS);

  // SS tags
  RooRealVar          parSigEtaDeltaP0_SS("parSigEtaDeltaP0_SS","delta mistag probability",-0.003,-0.02,0.02);
  RooRealVar          parSigEtaDeltaP0Mean_SS("parSigEtaDeltaP0Mean_SS","#bar{#delta p_{0}}",-0.0026);
  RooRealVar          parSigEtaDeltaP0Sigma_SS("parSigEtaDeltaP0Sigma_SS","#sigma_{#bar{#delta p_{0}}}",0.0044);
  Gaussian_Constraints.add(parSigEtaDeltaP0Sigma_SS);

  RooRealVar          parSigEtaDeltaP1_SS("parSigEtaDeltaP1_SS","delta scale calibration parameter probability",-0.18,-0.7,0.3);
  RooRealVar          parSigEtaDeltaP1Mean_SS("parSigEtaDeltaP1Mean_SS","#bar{#delta p_{1}}",-0.18);
  RooRealVar          parSigEtaDeltaP1Sigma_SS("parSigEtaDeltaP1Sigma_SS","#sigma_{#bar{#delta p_{1}}}",0.10);
  Gaussian_Constraints.add(parSigEtaDeltaP1Sigma_SS);

//=========================================================================================================================================================================================================================

  // Resolution and Decay Time Acceptance model
  RooRealVar          parResMean("parResMean","parResMean",-0.0032);
  RooGaussModel       resmodel("resmodel","resmodel",obsTime,parResMean,RooConst(0.05));

//=========================================================================================================================================================================================================================

  // Tagging calibration
  RooRealVar          parSigEtaP0_OS("parSigEtaP0_OS","Offset on per-event mistag",0.3815,0.0,0.1);
  RooRealVar          parSigEtaP0Mean_OS("parSigEtaP0Mean_OS","#bar{p}_{0}",0.3815);
  RooRealVar          parSigEtaP0Sigma_OS("parSigEtaP0Sigma_OS","#sigma_{#bar{p}_{0}}",0.0019);   // B+ value 0.0011  Kstar 0.0022
  Gaussian_Constraints.add(parSigEtaP0Sigma_OS);

  RooRealVar          parSigEtaP1_OS("parSigEtaP1_OS","Offset on per-event mistag",0.978,0.9,1.1);
  RooRealVar          parSigEtaP1Mean_OS("parSigEtaP1Mean_OS","#bar{p}_{0}",0.978);
  RooRealVar          parSigEtaP1Sigma_OS("parSigEtaP1Sigma_OS","#sigma_{#bar{p}_{0}}",0.007);  // B+ value 0.012   Kstar 0.024
  Gaussian_Constraints.add(parSigEtaP1Sigma_OS);

  RooRealVar          parSigEtaMean_OS("parSigEtaMean_OS","Mean on per-event mistag",0.3786);

  RooRealVar          parSigEtaP0_SS("parSigEtaP0_SS","Offset on per-event mistag",0.4228,0.3,0.5);
  RooRealVar          parSigEtaP0Mean_SS("parSigEtaP0Mean_SS","#bar{p}_{0}",0.4232);
  RooRealVar          parSigEtaP0Sigma_SS("parSigEtaP0Sigma_SS","#sigma_{#bar{p}_{0}}",0.0029);
  Gaussian_Constraints.add(parSigEtaP0Sigma_SS);

  RooRealVar          parSigEtaP1_SS("parSigEtaP1_SS","Offset on per-event mistag",1.01,0.7,1.1);
  RooRealVar          parSigEtaP1Mean_SS("parSigEtaP1Mean_SS","#bar{p}_{0}",1.011);
  RooRealVar          parSigEtaP1Sigma_SS("parSigEtaP1Sigma_SS","#sigma_{#bar{p}_{0}}",0.064);
  Gaussian_Constraints.add(parSigEtaP1Sigma_SS);

  RooRealVar          parSigEtaMean_SS("parSigEtaMean_SS","Mean on per-event mistag",0.42484);

//=========================================================================================================================================================================================================================

  // RooBDecay parameters
  RooConstVar       parSigTimeSinh("parSigTimeSinh","Sh_{f}",0.0);

  CPCoefficient     parSigTimeCosh_OS("parSigTimeCosh_OS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_OS("parSigTimeSin_OS",parSigTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_OS("parSigTimeCos_OS",parSigTimeC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,parSigEtaDeltaProd,CPCoefficient::kCos);

  CPCoefficient     parSigTimeCosh_SS("parSigTimeCosh_SS",RooConst(1.0),obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_SS("parSigTimeSin_SS",parSigTimeSin2b,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_SS("parSigTimeCos_SS",parSigTimeC,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd,CPCoefficient::kCos);

  CPCoefficient     parSigTimeCosh_BS("parSigTimeCosh_BS",RooConst(1.0),obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd,CPCoefficient::kCosh);
  CPCoefficient     parSigTimeSin_BS("parSigTimeSin_BS",parSigTimeSin2b,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd,CPCoefficient::kSin);
  CPCoefficient     parSigTimeCos_BS("parSigTimeCos_BS",parSigTimeC,obsTagOS,parSigEtaP0_OS,parSigEtaP1_OS,parSigEtaMean_OS,obsEtaOS,parSigEtaDeltaP0_OS,parSigEtaDeltaP1_OS,obsTagSS,parSigEtaP0_SS,parSigEtaP1_SS,parSigEtaMean_SS,obsEtaSS,parSigEtaDeltaP0_SS,parSigEtaDeltaP1_SS,parSigEtaDeltaProd,CPCoefficient::kCos);

//=========================================================================================================================================================================================================================

  // Decay Time PDF
  RooBDecay  pdfSigTime_OS("pdfSigTime_OS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_OS,parSigTimeSinh,parSigTimeCos_OS,parSigTimeSin_OS,parSigTimeDeltaM,resmodel,RooBDecay::SingleSided);
  RooBDecay  pdfSigTime_SS("pdfSigTime_SS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_SS,parSigTimeSinh,parSigTimeCos_SS,parSigTimeSin_SS,parSigTimeDeltaM,resmodel,RooBDecay::SingleSided);
  RooBDecay  pdfSigTime_BS("pdfSigTime_BS","P_{S}^{l}(t,d|#sigma_{t},#eta)",obsTime,parSigTimeTau,parSigEtaDeltaG,parSigTimeCosh_BS,parSigTimeSinh,parSigTimeCos_BS,parSigTimeSin_BS,parSigTimeDeltaM,resmodel,RooBDecay::SingleSided);

//========================================================================================================================================================================================================================

  // Build Simultaneous PDF
  RooSimultaneous   pdfTime("pdfTime","P",catTag);
  pdfTime.addPdf(pdfSigTime_OS,"OS");
  pdfTime.addPdf(pdfSigTime_SS,"SS");
  pdfTime.addPdf(pdfSigTime_BS,"both");

  cout  <<  "simultaneous PDF built"  <<  endl;

//========================================================================================================================================================================================================================

  Gaussian_Constraints.readFromFile("/home/fmeier/storage03/b02dd/Systematics/CorrelationEtaTime/generation.par");
  pdfTime.Print();

  RooArgSet             constrainingPdfs("constrainingPdfs");
  RooGaussian           conpdfSigTimeTau("conpdfSigTimeTau","constraint for #tau",parSigTimeTau,parSigTimeTauMean,parSigTimeTauSigma);
  RooGaussian           conpdfSigTimeDeltaM("conpdfSigTimeDeltaM","constraint for #Delta m",parSigTimeDeltaM,parSigTimeDeltaMMean,parSigTimeDeltaMSigma);
  RooGaussian           conpdfSigEtaDeltaProd("conpdfSigEtaDeltaProd","Gaussian Constraint for production asymmetry",parSigEtaDeltaProd,parSigEtaDeltaProdMean,parSigEtaDeltaProdSigma);
  RooGaussian           conpdfSigEtaP0_OS("conpdfSigEtaP0_OS","constraint for p0 of OS FT calibration",parSigEtaP0_OS,parSigEtaP0Mean_OS,parSigEtaP0Sigma_OS);
  RooGaussian           conpdfSigEtaP1_OS("conpdfSigEtaP1_OS","constraint for P1 of OS FT calibration",parSigEtaP1_OS,parSigEtaP1Mean_OS,parSigEtaP1Sigma_OS);
  RooGaussian           conpdfSigEtaDeltaP0_OS("conpdfSigEtaDeltaP0_OS","constraint for delta p0 of OS FT calibration",parSigEtaDeltaP0_OS,parSigEtaDeltaP0Mean_OS,parSigEtaDeltaP0Sigma_OS);
  RooGaussian           conpdfSigEtaDeltaP1_OS("conpdfSigEtaDeltaP1_OS","constraint for delta p1 of OS FT calibration",parSigEtaDeltaP1_OS,parSigEtaDeltaP1Mean_OS,parSigEtaDeltaP1Sigma_OS);
  RooGaussian           conpdfSigEtaP0_SS("conpdfSigEtaP0_SS","constraint for p0 of SS FT calibration",parSigEtaP0_SS,parSigEtaP0Mean_SS,parSigEtaP0Sigma_SS);
  RooGaussian           conpdfSigEtaP1_SS("conpdfSigEtaP1_SS","constraint for P1 of SS FT calibration",parSigEtaP1_SS,parSigEtaP1Mean_SS,parSigEtaP1Sigma_SS);
  RooGaussian           conpdfSigEtaDeltaP0_SS("conpdfSigEtaDeltaP0_SS","constraint for delta p0 of SS FT calibration",parSigEtaDeltaP0_SS,parSigEtaDeltaP0Mean_SS,parSigEtaDeltaP0Sigma_SS);
  RooGaussian           conpdfSigEtaDeltaP1_SS("conpdfSigEtaDeltaP1_SS","constraint for delta p1 of SS FT calibration",parSigEtaDeltaP1_SS,parSigEtaDeltaP1Mean_SS,parSigEtaDeltaP1Sigma_SS);

  constrainingPdfs.add(conpdfSigTimeTau);
  constrainingPdfs.add(conpdfSigTimeDeltaM);
  constrainingPdfs.add(conpdfSigEtaDeltaProd);
  constrainingPdfs.add(conpdfSigEtaP0_OS);
  constrainingPdfs.add(conpdfSigEtaP1_OS);
  constrainingPdfs.add(conpdfSigEtaDeltaP0_OS);
  constrainingPdfs.add(conpdfSigEtaDeltaP1_OS);
  constrainingPdfs.add(conpdfSigEtaP0_SS);
  constrainingPdfs.add(conpdfSigEtaP1_SS);
  constrainingPdfs.add(conpdfSigEtaDeltaP0_SS);
  constrainingPdfs.add(conpdfSigEtaDeltaP1_SS);
  cout  <<  "Constraints added" <<  endl;

//========================================================================================================================================================================================================================

  doofit::config::CommonConfig cfg_com("common");
  cfg_com.InitializeOptions(argc, argv);

  ToyStudyStdConfig cfg_tstudy("toystudy");
  cfg_tstudy.InitializeOptions(cfg_com);

  cfg_com.CheckHelpFlagAndPrintHelp();
  cfg_com.PrintAll();

  RooDataSet* data = NULL;
  RooDataSet* data_sweighted = NULL;
  TTree*      tree = NULL;
  TProfile*   profile = NULL;
  TF1*        f1 = new TF1("calib","[0] + [1]*(x-[2])",0.29,0.5);
  PlotConfig cfg_plot("cfg_plot");
  ToyStudyStd tstudy(cfg_com, cfg_tstudy, cfg_plot);
  
  ToyConfig     cfg_cptoymc;
  cfg_cptoymc.load(config.getString("ToyMC_config_file"));
  ToyGenerator  cptoymc(cfg_cptoymc);

  if (method.EqualTo("generate")) {
    
    TIterator*  iterator = constrainingPdfs.createIterator();
    RooAbsPdf*  constrainingPdf;
    SPlotFit2* splotfit;
    RooFitResult* fit_result;
    TStopwatch  stopwatch;
    RooLinkedList fitting_args;
    fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
    fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
    fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
    fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","migrad"))));
    // fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
    fitting_args.Add((TObject*)(new RooCmdArg(Hesse(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(ConditionalObservables(RooArgSet(obsEtaOS,obsEtaSS)))));
    fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
    fitting_args.Add((TObject*)(new RooCmdArg(Offset(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));
    RooArgSet set_of_yields;
    set_of_yields.add(RooArgSet(parSigYield,parSigBsYield,parBkgYield));
    for (int i = 0; i < 20 ; ++i) {
      cout  <<  i <<  endl;
      try {
        // TFile out_file("ToyMC.root","RECREATE");
        tree = new TTree("ToyMCTreetree","Tree of generation");
        cptoymc.GenerateToy(*tree);
        // tree->Draw("(obsTagSS!=obsTagTrue):obsEtaSS>>profile(100,0.29,0.5)","catBkg==1&&(catTaggedOSSS==-1||catTaggedOSSS==10)","profile");
        // profile = (TProfile*)gDirectory->Get("profile");
        // profile->Print("base");
        // f1->SetParameters(0.4313,1.00);
        // f1->FixParameter(2,profile->GetMean(1));
        // profile->Fit(f1,"N");
        // out_file.Write();
        // out_file.Close();
        // return 1;
        data = new RooDataSet("data","Toy MC data",tree, RooArgSet(observables,categories));
        data->Print();
        // EasyTuple tuple(*data);
        // tuple.WriteDataSetToTree("testsignalgenerationdatasample.root","TestTree");
        // return 1;
        pdfMass.getParameters(data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/CorrelationEtaTime/generation.par");
        splotfit = new SPlotFit2(pdfMass,*data,set_of_yields);
        splotfit->set_use_minos(false);
        splotfit->set_num_cpu(config.getInt("num_cpu"));
        splotfit->set_startingvalues("/home/fmeier/storage03/b02dd/Systematics/CorrelationEtaTime/generation.par");
        RooMsgService::instance().setStreamStatus(0, false);
        RooMsgService::instance().setStreamStatus(1, false);
        stopwatch.Start(true);
        splotfit->Fit();
        stopwatch.Stop();
        RooMsgService::instance().setStreamStatus(0, true);
        RooMsgService::instance().setStreamStatus(1, true);
        delete splotfit;
        data_sweighted = new RooDataSet("data_sweighted","data_sweighted",data,*(data->get()),TString(catTag.GetName())+"!=0","parSigYield_sw");
        data_sweighted->Print();
        pdfTime.getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/CorrelationEtaTime/generation.par");
        // parSigEtaP0_SS.setVal(f1->GetParameter(0));
        // parSigEtaP1_SS.setVal(f1->GetParameter(1));
        // parSigEtaMean_SS.setVal(f1->GetParameter(2));
        // iterator = constrainingPdfs.createIterator();
        // while ((constrainingPdf = dynamic_cast<RooAbsPdf*>(iterator->Next()))){
        //   constrainingPdf->getParameters(*data)->readFromFile("/home/fmeier/storage03/b02dd/Systematics/CorrelationEtaTime/generation.par");
        // }
        // parSigEtaDeltaProdMean.setVal(conpdfSigEtaDeltaProd.generate(parSigEtaDeltaProd,1)->get()->getRealValue("parSigEtaDeltaProd"));
        // parSigEtaP0Mean_OS.setVal(conpdfSigEtaP0_OS.generate(parSigEtaP0_OS,1)->get()->getRealValue("parSigEtaP0_OS"));
        // parSigEtaP1Mean_OS.setVal(conpdfSigEtaP1_OS.generate(parSigEtaP1_OS,1)->get()->getRealValue("parSigEtaP1_OS"));
        // parSigEtaDeltaP0Mean_OS.setVal(conpdfSigEtaDeltaP0_OS.generate(parSigEtaDeltaP0_OS,1)->get()->getRealValue("parSigEtaDeltaP0_OS"));
        // parSigEtaDeltaP1Mean_OS.setVal(conpdfSigEtaDeltaP1_OS.generate(parSigEtaDeltaP1_OS,1)->get()->getRealValue("parSigEtaDeltaP1_OS"));
        // parSigEtaP0Mean_SS.setVal(conpdfSigEtaP0_SS.generate(parSigEtaP0_SS,1)->get()->getRealValue("parSigEtaP0_SS"));
        // parSigEtaP1Mean_SS.setVal(conpdfSigEtaP1_SS.generate(parSigEtaP1_SS,1)->get()->getRealValue("parSigEtaP1_SS"));
        // parSigEtaDeltaP0Mean_SS.setVal(conpdfSigEtaDeltaP0_SS.generate(parSigEtaDeltaP0_SS,1)->get()->getRealValue("parSigEtaDeltaP0_SS"));
        // parSigEtaDeltaP1Mean_SS.setVal(conpdfSigEtaDeltaP1_SS.generate(parSigEtaDeltaP1_SS,1)->get()->getRealValue("parSigEtaDeltaP1_SS"));
        // parSigTimeTauMean.setVal(conpdfSigTimeTau.generate(parSigTimeTau,1)->get()->getRealValue("parSigTimeTau"));
        // parSigTimeDeltaMMean.setVal(conpdfSigTimeDeltaM.generate(parSigTimeDeltaM,1)->get()->getRealValue("parSigTimeDeltaM"));
        stopwatch.Start(true);
        fit_result = pdfTime.fitTo(*data_sweighted,fitting_args);
        stopwatch.Stop();
        fit_result->Print("v");
        tstudy.StoreFitResult(fit_result, NULL, &stopwatch);
        // delete iterator;
        delete data_sweighted;
        delete tree;
      } catch (...) {
        i--;
      }
    }
  }

  if (method.EqualTo("evaluate")) {
    tstudy.ReadFitResults();
    tstudy.EvaluateFitResults();
    tstudy.PlotEvaluatedParameters();
  }

  return 0;
}