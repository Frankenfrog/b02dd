#include <iostream>
#include <sstream>

// from ROOT
#include "TROOT.h"

//from RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooConstVar.h"
#include "RooWorkspace.h"

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooTruthModel.h"
#include "RooDecay.h"
#include "RooGaussian.h"
#include "RooExtendPdf.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/lutils/lutils.h"
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
#include "doofit/config/CommonConfig.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStd.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStdConfig.h"
#include "doofit/toy/ToyFactoryStd/ToyFactoryStd.h"
#include "doofit/toy/ToyFactoryStd/ToyFactoryStdConfig.h"

using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace doocore::lutils;
using namespace doofit::plotting;
using namespace doofit::toy;

int main(int argc, char * argv[]){
  if (argc < 2) {
    std::cout << "Usage:   " << argv[0] << " 'fit_config_file_name' - c toystudy_config_file_name" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");
  TString method = config.getString("method");

  RooRealVar        obsTime("obsTime","#it{t}",0.,10.25,"ps");
  RooArgSet         observables(obsTime,"observables");

  // Lifetime
  RooRealVar        parTimeTau("parTimeTau","#tau",1.5,1.,2.);
  RooRealVar        parTimeTauMean("parTimeTauMean","#tau",1.519);
  RooRealVar        parTimeTauSigma("parTimeTauSigma","#tau",0.005);

//=========================================================================================================================================================================================================================

  // Resolution model
  // RooGaussModel     pdfresGauss("pdfresGauss","pdfresGauss",obsTime,RooConst(0),RooConst(0.01));
  RooTruthModel     pdfresGauss("pdfresGauss","pdfresGauss",obsTime);

//=========================================================================================================================================================================================================================

  // Decay Time PDF
  RooDecay          pdfTime("pdfTime","P(t)",obsTime,parTimeTau,pdfresGauss,RooDecay::SingleSided);

//========================================================================================================================================================================================================================

  // Yields and Extension
  RooRealVar        parYield("parYield","parYield", 200, 0, 1000);
  RooExtendPdf      pdfExtend("pdfExtend","pdfExtend",pdfTime,parYield);

//========================================================================================================================================================================================================================

  RooArgSet         constrainingPdfs("constrainingPdfs");
  RooGaussian       conpdfTimeTau("conpdfTimeTau","constraint for #tau",parTimeTau,parTimeTauMean,parTimeTauSigma);

  constrainingPdfs.add(conpdfTimeTau);

  cout  <<  "Constraint added" <<  endl;

//========================================================================================================================================================================================================================

  // Workspace initialisation
  RooWorkspace* ws = new RooWorkspace("ws");
  ws->import(pdfExtend);
  ws->defineSet("observables",observables);

  RooDataSet* data = NULL;

  doofit::config::CommonConfig cfg_com("common");
  cfg_com.InitializeOptions(argc, argv);

  ToyFactoryStdConfig cfg_tfac("toyfac");
  cfg_tfac.InitializeOptions(cfg_com);

  ToyStudyStdConfig cfg_tstudy("toystudy");
  cfg_tstudy.InitializeOptions(cfg_tfac);  

  cfg_com.CheckHelpFlagAndPrintHelp();

  ws->Print();

  cfg_tfac.set_workspace(ws);

  ToyFactoryStd tfac(cfg_com, cfg_tfac);

  cfg_com.PrintAll();

  PlotConfig cfg_plot("cfg_plot");
  ToyStudyStd tstudy(cfg_com, cfg_tstudy, cfg_plot);
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(num_cpu,0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(config.getBool("minos")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  // fitting_args.Add((TObject*)(new RooCmdArg(ExternalConstraints(constrainingPdfs))));
  fitting_args.Add((TObject*)(new RooCmdArg(Hesse(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(0))));
  fitting_args.Add((TObject*)(new RooCmdArg(Offset(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(false))));

  if (method.EqualTo("generate")) {
    
    RooFitResult* fit_result;
    TStopwatch  stopwatch;
    for (int i = 0; i < 500 ; ++i) {
      cout  <<  i <<  endl;
      try {
        data = tfac.Generate();
        pdfTime.getParameters(*data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/Constraints/generation.par");
        conpdfTimeTau.getParameters(*data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/Constraints/generation.par");
        parTimeTauMean.setVal(conpdfTimeTau.generate(parTimeTau,1)->get()->getRealValue("parTimeTau"));
        stopwatch.Start(true);
        RooMsgService::instance().setStreamStatus(0, false);
        RooMsgService::instance().setStreamStatus(1, false);
        fit_result = pdfTime.fitTo(*data,fitting_args);
        RooMsgService::instance().setStreamStatus(0, true);
        RooMsgService::instance().setStreamStatus(1, true);
        stopwatch.Stop();
        fit_result->Print("v");
        tstudy.StoreFitResult(fit_result, NULL, &stopwatch);
        delete data;
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

  delete ws;
  return 0;
}
