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
#include "TIterator.h"

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

void FitandPlot(RooDataSet* original_data, TString cut, TString identifier);

int main(int argc, char * argv[]){

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{+}}}",5000,5900,"MeV/c^{2}");

  // RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  // catDDFinalState.defineType("KpipiKpipi",1);
  // catDDFinalState.defineType("others",-10);
  // for (int i = 2; i < 10; ++i){
  //   catDDFinalState.defineType(to_string(i).c_str(),i);
  // }
  RooCategory        Dplus1_Kminus_or_piminus_ID("Dplus1_Kminus_or_piminus_ID","Dplus1_Kminus_or_piminus_ID");
  RooCategory        Dplus1_piplus_or_Kplus_One_ID("Dplus1_piplus_or_Kplus_One_ID","Dplus1_piplus_or_Kplus_One_ID");
  RooCategory        Dplus1_piplus_or_Kplus_Two_ID("Dplus1_piplus_or_Kplus_Two_ID","Dplus1_piplus_or_Kplus_Two_ID");
  RooCategory        Dplus2_Kminus_or_piminus_ID("Dplus2_Kminus_or_piminus_ID","Dplus2_Kminus_or_piminus_ID");
  RooCategory        Dplus2_piplus_or_Kplus_One_ID("Dplus2_piplus_or_Kplus_One_ID","Dplus2_piplus_or_Kplus_One_ID");
  RooCategory        Dplus2_piplus_or_Kplus_Two_ID("Dplus2_piplus_or_Kplus_Two_ID","Dplus2_piplus_or_Kplus_Two_ID");
  RooArgSet          IDs(Dplus1_Kminus_or_piminus_ID,Dplus1_piplus_or_Kplus_One_ID,Dplus1_piplus_or_Kplus_Two_ID,Dplus2_Kminus_or_piminus_ID,Dplus2_piplus_or_Kplus_One_ID,Dplus2_piplus_or_Kplus_Two_ID,"IDs");
  int IDvalues [4] = {-321,-211,211,321};
  TIterator*         iterator = IDs.createIterator();
  RooCategory*       IDcategory;
  while ((IDcategory = dynamic_cast<RooCategory*>(iterator->Next()))){
    for (int i = 0; i < 4; ++i){
      IDcategory->defineType(to_string(i).c_str(),IDvalues[i]);
    }
  }

  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);
  RooCategory       varDTFStatusDDPVConst("varDTFStatusDDPVConst","varDTFStatusDDPVConst");
  varDTFStatusDDPVConst.defineType("converged",0);

  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  RooRealVar        varKminus1_PID("varKminus1_PID","varKminus1_PID",0,1);
  RooRealVar        varKminus2_PID("varKminus2_PID","varKminus2_PID",0,1);
  RooRealVar        varPiOne1plus_PID("varPiOne1plus_PID","varPiOne1plus_PID",0,1);
  RooRealVar        varPiOne2plus_PID("varPiOne2plus_PID","varPiOne2plus_PID",0,1);
  RooRealVar        varPiTwo1plus_PID("varPiTwo1plus_PID","varPiTwo1plus_PID",0,1);
  RooRealVar        varPiTwo2plus_PID("varPiTwo2plus_PID","varPiTwo2plus_PID",0,1);
  RooArgSet         PIDs(varKminus1_PID,varKminus2_PID,varPiOne1plus_PID,varPiOne2plus_PID,varPiTwo1plus_PID,varPiTwo2plus_PID,"PIDs");

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         variables(varBDT,"variables");
  variables.add(IDs);
  variables.add(PIDs);
  RooArgSet         realvars(observables,variables,"realvars");
  RooArgSet         categories(/*catDDFinalState,*/catTriggerSetTopo234BodyBBDT,varDTFStatusDDPVConst,"categories");
  
  // Get data set
  EasyTuple         tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/Combined_2011_2012/DT20112012_B02DDWS_Stripping21r0r1_DVv36r1_20150501_fmeier_combined_20150504_fmeier_BDT_TupleB.root","B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet();
  
  data.Print("v");

  // FitandPlot(&data, "abs(Dplus1_Kminus_or_piminus_ID)==321&&abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211&&abs(Dplus2_Kminus_or_piminus_ID)==321&&abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211", "Kpipi");
  // FitandPlot(&data, "varKminus1_PID>0.2&&varKminus2_PID>0.2&&varPiOne1plus_PID<0.5&&varPiOne2plus_PID<0.5&&varPiTwo1plus_PID<0.65&&varPiTwo2plus_PID<0.65", "PIDcuts");
  // FitandPlot(&data, "BDTG2_classifier>-0.784", "BDT99");
  // FitandPlot(&data, "varKminus1_PID>0.2&&varKminus2_PID>0.2&&varPiOne1plus_PID<0.5&&varPiOne2plus_PID<0.5&&varPiTwo1plus_PID<0.65&&varPiTwo2plus_PID<0.65&&abs(Dplus1_Kminus_or_piminus_ID)==321&&abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211&&abs(Dplus2_Kminus_or_piminus_ID)==321&&abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211", "Kpipi_PID");
  // FitandPlot(&data, "BDTG2_classifier>-0.784&&abs(Dplus1_Kminus_or_piminus_ID)==321&&abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211&&abs(Dplus2_Kminus_or_piminus_ID)==321&&abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211", "BDT99_Kpipi");
  // FitandPlot(&data, "BDTG2_classifier>-0.784&&varKminus1_PID>0.2&&varKminus2_PID>0.2&&varPiOne1plus_PID<0.5&&varPiOne2plus_PID<0.5&&varPiTwo1plus_PID<0.65&&varPiTwo2plus_PID<0.65", "BDT99_PID");
  // FitandPlot(&data, "abs(Dplus1_Kminus_or_piminus_ID)==321&&((abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211)||(abs(Dplus1_piplus_or_Kplus_One_ID)==321&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211)||(abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==321))&&abs(Dplus2_Kminus_or_piminus_ID)==321&&((abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211)||(abs(Dplus2_piplus_or_Kplus_One_ID)==321&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211)||(abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==321))", "Kpipi_or_KKpi");
  FitandPlot(&data, "obsMassDDPVConst>5000", "all");
  FitandPlot(&data, "BDTG2_classifier>-0.784&&varKminus1_PID>0.2&&varKminus2_PID>0.2&&varPiOne1plus_PID<0.5&&varPiOne2plus_PID<0.5&&varPiTwo1plus_PID<0.65&&varPiTwo2plus_PID<0.65&&abs(Dplus1_Kminus_or_piminus_ID)==321&&abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211&&abs(Dplus2_Kminus_or_piminus_ID)==321&&abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211", "nominal");


  return 0;
}

void FitandPlot(RooDataSet* original_data, TString cut, TString identifier){

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{+}}}",5000,5900,"MeV/c^{2}");
  // Mass PDF
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.001,-0.01,0.01);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parBkgYield("parBkgYield","parBkgYield",2500000,0,3000000);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  // Get Starting Values and Fit PDF to data
  pdfBkgExtend.Print();
  // pdfBkgExtend.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
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

  RooDataSet* fitdata = dynamic_cast<RooDataSet*>(original_data->reduce(cut));
  fitdata->Print();
  RooFitResult* fit_result = pdfBkgExtend.fitTo(*fitdata, fitting_args);
  pdfBkgExtend.getParameters(*fitdata)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_WS_"+identifier+".txt");

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/Mass/Plots");
  std::vector<std::string> components_mass;
  Plot Mass(cfg_plot_mass, obsMass, *fitdata, pdfBkgExtend, components_mass, string("WSMass_"+identifier));
  Mass.PlotItLogNoLogY();
}