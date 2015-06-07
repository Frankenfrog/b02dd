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

// from DooFit
#include "URANIA/RooIpatia2.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/plotting/fitresult/FitResultPrinter.h"
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

  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");

  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  //RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  //catDDFinalState.defineType("KpipiKpipi",1);
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

  RooRealVar        varKminus_PID("varKminus_PID","varKminus_PID",0,1);
  RooRealVar        varKplus_PID("varKplus_PID","varKplus_PID",0,1);
  RooRealVar        varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID",0,1);
  RooRealVar        varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID",0,1);
  RooRealVar        varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID",0,1);
  RooRealVar        varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID",0,1);

  RooArgSet         observables(obsMassDauOne,obsMassDauTwo,"observables");
  RooArgSet         variables(varBDT,"variables");
  RooArgSet         varPIDs(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID,"varPIDs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varPIDs);
  realvars.add(IDs);
  RooArgSet         categories(/*catDDFinalState,*/catTriggerSetTopo234BodyBBDT,"categories");
  
  // Get data set
  EasyTuple         tuple(argv[1],argv[2],RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut("abs(Dplus1_Kminus_or_piminus_ID)==321&&abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211&&abs(Dplus2_Kminus_or_piminus_ID)==321&&abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211"));//Cut("(abs(varDplusMassHypo_KKpi-1968.3)>25||Dplus_piplus_or_Kplus_One_RichDLLk<-10)&&(abs(varDplusMassHypo_KpiK-1968.3)>25||Dplus_piplus_or_Kplus_Two_RichDLLk<-10)&&(abs(varDminusMassHypo_KKpi-1968.3)>25||Dminus_piminus_or_Kminus_One_RichDLLk<-10)&&(abs(varDminusMassHypo_KpiK-1968.3)>25||Dminus_piminus_or_Kminus_Two_RichDLLk<-10)"));
  
  data.Print();

  // Mass PDF
  RooRealVar        parSigDMassMean("parSigDMassMean","D Mean Mass",1870,1860,1880,"MeV/c^{2}");
  RooRealVar        parSigDMassSigma("parSigDMassSigma","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooGaussian       pdfSigDplusMass("pdfSigDplusMass","Signal Mass PDF",obsMassDauOne,parSigDMassMean,parSigDMassSigma);
  
  RooRealVar        parBkgDExponent("parBkgDExponent","parBkgDExponent",-0.005,-1,1);
  RooExponential    pdfBkgDplusMass("pdfBkgDplusMass","pdfBkgDplusMass",obsMassDauOne,parBkgDExponent);

  RooGaussian       pdfSigDminusMass("pdfSigDminusMass","Signal Mass PDF",obsMassDauTwo,parSigDMassMean,parSigDMassSigma);
  
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
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(4))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  //RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65"));
  RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce(argv[4]));
  optimized_data->Print();
  RooFitResult* fit_result = pdfMass.fitTo(*optimized_data, fitting_args);
  pdfMass.getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/sWeights/FitResult_"+TString(argv[5])+".txt");
  doofit::plotting::fitresult::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/sWeights/Plots");
  
  std::vector<std::string> components_Dplus;
  components_Dplus += "pdfSigDplusMass", "pdfBkgDplusMass";
  Plot MassDplus(cfg_plot_mass, obsMassDauOne, *optimized_data, pdfMass, components_Dplus, "obsMassDauOne_"+string(argv[5]));
  MassDplus.PlotIt();

  std::vector<std::string> components_Dminus;
  components_Dminus += "pdfSigDminusMass", "pdfBkgDminusMass";
  Plot MassDminus(cfg_plot_mass, obsMassDauTwo, *optimized_data, pdfMass, components_Dminus, "obsMassDauTwo_"+string(argv[5]));
  MassDminus.PlotIt();

  SPlotFit2 splotfit(pdfMass,*optimized_data,RooArgSet(parSigDDYield,parBkgDCombYield,parBkgCombDYield,parBkgCombYield));
  splotfit.set_use_minos(false);
  splotfit.set_num_cpu(4);
  
  dooselection::reducer::SPlotterReducer spr(splotfit, RooArgSet(obsMassDauOne,obsMassDauTwo));
  spr.set_input_file_path(argv[1]);
  spr.set_input_tree_path(argv[2]);
  spr.set_output_file_path(argv[3]);

  spr.set_output_tree_path("B02DD");
  spr.set_cut_string("obsMassDauOne>=1845&&obsMassDauOne<=1895&&obsMassDauTwo>=1845&&obsMassDauTwo<=1895&&catTriggerSetTopo234BodyBBDT==1&&"+string(argv[4])+"&&abs(Dplus1_Kminus_or_piminus_ID)==321&&abs(Dplus1_piplus_or_Kplus_One_ID)==211&&abs(Dplus1_piplus_or_Kplus_Two_ID)==211&&abs(Dplus2_Kminus_or_piminus_ID)==321&&abs(Dplus2_piplus_or_Kplus_One_ID)==211&&abs(Dplus2_piplus_or_Kplus_Two_ID)==211");
  spr.set_plot_directory(string("/home/fmeier/storage03/b02dd/run/Reducer/Plots"));
  spr.Initialize();
  spr.Run();
  spr.Finalize();


  return 0;
}
