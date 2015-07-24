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
#include "RooSuperCategory.h"
#include "RooDataHist.h"
#include "RooUnblindUniform.h"
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

#include "RooFormulaVar.h"
#include "RooAbsPdf.h"
#include "RooEffProd.h"
#include "RooSimultaneous.h"
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
#include "Urania/RooIpatia2.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
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
  
  if (argc != 4) {
    std::cout << "Parameters needed: InputFile InputTree OutputFile" << std::endl;
    return 1;
  }

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  TCanvas c("c","c",800,600);

  RooRealVar        obsMass("obsMass","#it{m_{K #pi #pi K #pi #pi}}",5140,5400,"MeV/c^{2}");

  RooRealVar        BDTG2_classifier("BDTG2_classifier","BDTG2_classifier",-1,1);
  
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);

  RooRealVar        varKminus_ProbNNk("Dplus_Kminus_or_piminus_ProbNNk","Dplus_Kminus_or_piminus_ProbNNk",0,1);
  RooRealVar        varKminus_ProbNNpi("Dplus_Kminus_or_piminus_ProbNNpi","Dplus_Kminus_or_piminus_ProbNNpi",0,1);
  RooRealVar        varKplus_ProbNNk("Dminus_Kplus_or_piplus_ProbNNk","Dminus_Kplus_or_piplus_ProbNNk",0,1);
  RooRealVar        varKplus_ProbNNpi("Dminus_Kplus_or_piplus_ProbNNpi","Dminus_Kplus_or_piplus_ProbNNpi",0,1);
  RooRealVar        varPiOneminus_ProbNNk("Dminus_piminus_or_Kminus_One_ProbNNk","Dminus_piminus_or_Kminus_One_ProbNNk",0,1);
  RooRealVar        varPiOneminus_ProbNNpi("Dminus_piminus_or_Kminus_One_ProbNNpi","Dminus_piminus_or_Kminus_One_ProbNNpi",0,1);
  RooRealVar        varPiOneplus_ProbNNk("Dplus_piplus_or_Kplus_One_ProbNNk","Dplus_piplus_or_Kplus_One_ProbNNk",0,1);
  RooRealVar        varPiOneplus_ProbNNpi("Dplus_piplus_or_Kplus_One_ProbNNpi","Dplus_piplus_or_Kplus_One_ProbNNpi",0,1);
  RooRealVar        varPiTwominus_ProbNNk("Dminus_piminus_or_Kminus_Two_ProbNNk","Dminus_piminus_or_Kminus_Two_ProbNNk",0,1);
  RooRealVar        varPiTwominus_ProbNNpi("Dminus_piminus_or_Kminus_Two_ProbNNpi","Dminus_piminus_or_Kminus_Two_ProbNNpi",0,1);
  RooRealVar        varPiTwoplus_ProbNNk("Dplus_piplus_or_Kplus_Two_ProbNNk","Dplus_piplus_or_Kplus_Two_ProbNNk",0,1);
  RooRealVar        varPiTwoplus_ProbNNpi("Dplus_piplus_or_Kplus_Two_ProbNNpi","Dplus_piplus_or_Kplus_Two_ProbNNpi",0,1);

  RooArgSet         observables(obsMass,"observables");
  RooArgSet         variables(BDTG2_classifier,"variables");
  RooArgSet         varKaonProbNNs(varKminus_ProbNNk,varKminus_ProbNNpi,varKplus_ProbNNk,varKplus_ProbNNpi,"varKaonProbNNs");
  RooArgSet         varPionProbNNs(varPiOneminus_ProbNNk,varPiOneminus_ProbNNpi,varPiOneplus_ProbNNk,varPiOneplus_ProbNNpi,varPiTwominus_ProbNNk,varPiTwominus_ProbNNpi,varPiTwoplus_ProbNNk,varPiTwoplus_ProbNNpi,"varPionProbNNs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varKaonProbNNs);
  realvars.add(varPionProbNNs);
  RooArgSet         categories(catTriggerSetTopo234BodyBBDT,"categories");
  
  // Get data set
  EasyTuple         tuple("/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/Combined_2011_2012/DT20112012_B02DD_Stripping21r0r1_DVv36r1_20150322_fmeier_combined_20150504_fmeier_BDT_TupleB_BDT99applied.root","B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(""));
  
  data.Print();
  
  RooFormulaVar     varKminus_PID("varKminus_PID","varKminus_PID","@0/(@0+@1)",RooArgList(varKminus_ProbNNk,varKminus_ProbNNpi));
  RooFormulaVar     varKplus_PID("varKplus_PID","varKplus_PID","@0/(@0+@1)",RooArgList(varKplus_ProbNNk,varKplus_ProbNNpi));
  RooFormulaVar     varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID","@0/(@0+@1)",RooArgList(varPiOneminus_ProbNNk,varPiOneminus_ProbNNpi));
  RooFormulaVar     varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID","@0/(@0+@1)",RooArgList(varPiOneplus_ProbNNk,varPiOneplus_ProbNNpi));
  RooFormulaVar     varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID","@0/(@0+@1)",RooArgList(varPiTwominus_ProbNNk,varPiTwominus_ProbNNpi));
  RooFormulaVar     varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID","@0/(@0+@1)",RooArgList(varPiTwoplus_ProbNNk,varPiTwoplus_ProbNNpi));
  RooArgList        PID_formulas(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID);
  data.addColumns(PID_formulas);

  // Mass PDF
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");
  RooRealVar        parSigMassSigma("parSigMassSigma","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooGaussian       pdfSigMass("pdfSigMass","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma);

  RooRealVar        parSigMassMean1("parSigMassMean1","partial reco Mean Mass",5220,5200,5250,"MeV/c^{2}");
  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooGaussian       pdfSigMass1("pdfSigMass1","partial reco Mass PDF",obsMass,parSigMassMean1,parSigMassSigma1);  
  
  RooRealVar        parSigMassMean2("parSigMassMean2","Bs Mean Mass",5360,5340,5390,"MeV/c^{2}");
  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",7.0,1.0,9.0,"MeV/c^{2}");
  RooGaussian       pdfSigMass2("pdfSigMass2","Bs Mass PDF",obsMass,parSigMassMean2,parSigMassSigma2);

  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parSig1Yield("parSig1Yield","parSig1Yield",1000,0,2000);
  RooRealVar        parSig2Yield("parSig2Yield","parSig2Yield",100,0,1000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",pdfSigMass,parSigYield);
  RooExtendPdf      pdfSig1Extend("pdfSig1Extend","pdfSig1Extend",pdfSigMass1,parSig1Yield);
  RooExtendPdf      pdfSig2Extend("pdfSig2Extend","pdfSig2Extend",pdfSigMass2,parSig2Yield);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfSig1Extend,pdfSig2Extend,pdfBkgExtend));
  
  // Get Starting Values
  pdfMass.getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");

  RooDataSet* reduced_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2"));

  SPlotFit2 splotfit(pdfMass,*reduced_data,RooArgSet(parSigYield,parSig1Yield,parSig2Yield,parBkgYield));
  splotfit.set_use_minos(false);
  splotfit.set_num_cpu(16);
  
  dooselection::reducer::SPlotterReducer spr(splotfit, RooArgSet(obsMass));
  spr.set_input_file_path(argv[1]);
  spr.set_input_tree_path(argv[2]);
  spr.set_output_file_path(argv[3]);

  spr.set_output_tree_path("B02DD");
  spr.set_cut_string("obsMass>5140&&obsMass<5400&&(Dplus_Kminus_or_piminus_ProbNNk/(Dplus_Kminus_or_piminus_ProbNNk+Dplus_Kminus_or_piminus_ProbNNpi))>0.2&&(Dminus_Kplus_or_piplus_ProbNNk/(Dminus_Kplus_or_piplus_ProbNNk+Dminus_Kplus_or_piplus_ProbNNpi))>0.2");
  spr.set_plot_directory(string("/home/fmeier/storage03/b02dd/run/Reducer/Plots"));
  spr.Initialize();
  spr.Run();
  spr.Finalize();
     
  return 0;
}