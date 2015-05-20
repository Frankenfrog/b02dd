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

//from RooFit
#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooCategory.h"
#include "RooConstVar.h"

// from RooFit PDFs
#include "RooExponential.h"
#include "RooAbsPdf.h"
#include "RooExtendPdf.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/lutils/lutils.h"

// from DooFit
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

int main(int argc, char * argv[]){

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{+}}}",5150,5500,"MeV/c^{2}");
  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",1);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);

  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  RooRealVar        varKminus1_PID("varKminus1_PID","varKminus1_PID",0,1);
  RooRealVar        varKminus2_PID("varKminus2_PID","varKminus2_PID",0,1);
  RooRealVar        varPiOne1plus_PID("varPiOne1plus_PID","varPiOne1plus_PID",0,1);
  RooRealVar        varPiOne2plus_PID("varPiOne2plus_PID","varPiOne2plus_PID",0,1);
  RooRealVar        varPiTwo1plus_PID("varPiTwo1plus_PID","varPiTwo1plus_PID",0,1);
  RooRealVar        varPiTwo2plus_PID("varPiTwo2plus_PID","varPiTwo2plus_PID",0,1);
  
  RooArgSet         observables(obsMass/*,obsMassDauOne,obsMassDauTwo*/,"observables");
  RooArgSet         variables(varBDT,"variables");
  RooArgSet         PIDs(varKminus1_PID,varKminus2_PID,varPiOne1plus_PID,varPiOne2plus_PID,varPiTwo1plus_PID,varPiTwo2plus_PID,"PIDs");
  variables.add(PIDs);
  RooArgSet         realvars(observables,variables,"realvars");
  RooArgSet         categories(/*catDDFinalState,*/catTriggerSetTopo234BodyBBDT,"categories");
  
  // Get data set
  EasyTuple         tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/Combined_2011_2012/DT20112012_B02DDWS_Stripping21r0r1_DVv36r1_20150501_fmeier_combined_20150504_fmeier_BDT_TupleB.root","B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(varBDT.GetName())+">-0.784"));
  
  data.Print();

  // Mass PDF
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  // Get Starting Values and Fit PDF to data
  pdfBkgExtend.Print();
  pdfBkgExtend.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
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

  RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus1_PID>0.2&&varKminus2_PID>0.2&&varPiOne1plus_PID<0.5&&varPiOne2plus_PID<0.5&&varPiTwo1plus_PID<0.65&&varPiTwo2plus_PID<0.65"));
  optimized_data->Print();
  RooFitResult* fit_result = pdfBkgExtend.fitTo(*optimized_data, fitting_args);
  pdfBkgExtend.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_WS.txt");

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/Mass/Plots");
  std::vector<std::string> components_mass;
  Plot Mass(cfg_plot_mass, obsMass, *optimized_data, pdfBkgExtend, components_mass, "WSMass");
  Mass.PlotItLogNoLogY();

  return 0;
}
