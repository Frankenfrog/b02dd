#include <iostream>
#include <sstream>

// from ROOT
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1.h"
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
#include "RooConstVar.h"
#include "RooBinning.h"
#include "RooAddition.h"
#include "RooProduct.h"

// from RooFit PDFs
#include "RooGaussModel.h"
#include "RooBDecay.h"
#include "RooDecay.h"
#include "RooExponential.h"
#include "RooLognormal.h"
#include "RooGaussian.h"
#include "RooMultiVarGaussian.h"
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
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "P2VV/RooCubicSplineFun.h"
#include "P2VV/RooCubicSplineKnot.h"
#include "P2VV/RooAbsGaussModelEfficiency.h"
#include "P2VV/RooGaussEfficiencyModel.h"
#include "P2VV/RooEffResAddModel.h"
#include "doofit/roofit/pdfs/BiasDelta.h"
#include "doofit/roofit/functions/LinearFunctionWithOffset.h"
#include "doofit/roofit/functions/TauCorrectionWithBetaFactor.h"
#include "doofit/roofit/functions/CPCoefficient.h"
#include "doofit/roofit/pdfs/DooCubicSplinePdf.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
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
using namespace doofit::roofit::functions;
using namespace doofit::roofit::pdfs;

void PlotAcceptance(RooAbsReal* acceptance1, RooFitResult* fit_result1, RooAbsReal* acceptance2, RooFitResult* fit_result2, TTree* tree);

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);
  
  int num_cpu = config.getInt("num_cpu");

  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");
  RooRealVar        obsTime_True("obsTime_True","#it{t}_{true}",0.25,10.25,"ps");

  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("signal",0);
  catBkg.defineType("LowMassBackground",50);
  RooCategory       idxPV("idxPV","idxPV");
  idxPV.defineType("signal",0);
  
  RooArgSet         observables(obsTime,obsTime_True,"observables");
  RooArgSet         categories(catBkg,idxPV,"categories");

  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(observables,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet*       data = &(tuple.ConvertToDataSet());
  TTree&            tree = tuple.tree();
  data->Print();

//=========================================================================================================================================================================================================================
  
  // Decay Time PDF 1
  std::vector<double> knots1;
  knots1 += 0.8;
  knots1 += 2.0;

  RooArgList        listofsplinecoefficients1("listofsplinecoefficients1");
  RooRealVar*       parSigTimeAccCSpline1;
  for (int i = 1; i <= (knots1.size()+2) ; i++) {
    std::string binname = "parSigTimeAccCSpline1_" + boost::lexical_cast<std::string>(i);
    parSigTimeAccCSpline1 = new RooRealVar(binname.c_str(),binname.c_str(),1,0,2);
    listofsplinecoefficients1.add(*parSigTimeAccCSpline1);
  }

  RooCubicSplineFun       accspline1("accspline1","Spline Acceptance",obsTime,knots1,listofsplinecoefficients1);
  RooGaussEfficiencyModel efficiencymodel1("efficiencymodel1","Gaussefficiencymodel",obsTime,accspline1,RooConst(0.),RooConst(0.05));
  RooRealVar              parSigTimeTau1("parSigTimeTau1","#tau",1.5,1.,2.);
  RooDecay                pdfSigTime1("pdfSigTime1","P",obsTime,parSigTimeTau1,efficiencymodel1,RooDecay::SingleSided);

//=========================================================================================================================================================================================================================
  
  // Decay Time PDF 1
  std::vector<double> knots2;
  knots2 += 0.8;
  knots2 += 2.5;

  RooArgList        listofsplinecoefficients2("listofsplinecoefficients2");
  RooRealVar*       parSigTimeAccCSpline2;
  for (int i = 1; i <= (knots2.size()+2) ; i++) {
    std::string binname = "parSigTimeAccCSpline2_" + boost::lexical_cast<std::string>(i);
    parSigTimeAccCSpline2 = new RooRealVar(binname.c_str(),binname.c_str(),1,0,2);
    listofsplinecoefficients2.add(*parSigTimeAccCSpline2);
  }

  RooCubicSplineFun       accspline2("accspline2","Spline Acceptance",obsTime,knots2,listofsplinecoefficients2);
  RooGaussEfficiencyModel efficiencymodel2("efficiencymodel2","Gaussefficiencymodel",obsTime,accspline2,RooConst(0.),RooConst(0.05));
  RooRealVar              parSigTimeTau2("parSigTimeTau2","#tau",1.5,1.,2.);
  RooDecay                pdfSigTime2("pdfSigTime2","P",obsTime,parSigTimeTau2,efficiencymodel2,RooDecay::SingleSided);

//========================================================================================================================================================================================================================

  // Get Starting Values and Fit PDF to data
  pdfSigTime1.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/Acceptancespline.txt");
  pdfSigTime2.getParameters(*data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/Acceptancespline.txt");

  RooRealVar          parSigTimeTauMean("parSigTimeTauMean","#tau",1.519);
  RooRealVar          parSigTimeTauSigma("parSigTimeTauSigma","#tau",0.005);
  RooGaussian         conpdfSigTimeTau1("conpdfSigTimeTau1","constraint for #tau",parSigTimeTau1,parSigTimeTauMean,parSigTimeTauSigma);
  RooGaussian         conpdfSigTimeTau2("conpdfSigTimeTau2","constraint for #tau",parSigTimeTau2,parSigTimeTauMean,parSigTimeTauSigma);
  
  RooFitResult* fit_result1 = pdfSigTime1.fitTo(*data,ExternalConstraints(conpdfSigTimeTau1),NumCPU(num_cpu,0),Strategy(2),Save(true),Minimizer("Minuit2","minimize"));
  pdfSigTime1.getParameters(*data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots/FitResults1.txt");
  fit_result1->Print("v");
  doofit::fitter::easyfit::FitResultPrinter fitresultprinter(*fit_result1);
  fitresultprinter.Print();
  fit_result1->correlationMatrix().Print();
  TFile   fitresultwritetofile1("/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots/FitResults1.root","recreate");
  fit_result1->Write("fit_result");
  fitresultwritetofile1.Close();

  RooFitResult* fit_result2 = pdfSigTime2.fitTo(*data,ExternalConstraints(conpdfSigTimeTau2),NumCPU(num_cpu,0),Strategy(2),Save(true),Minimizer("Minuit2","minimize"));
  pdfSigTime2.getParameters(*data)->writeToFile("/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots/FitResults2.txt");
  fit_result2->Print("v");
  doofit::fitter::easyfit::FitResultPrinter fitresultprinter2(*fit_result2);
  fitresultprinter2.Print();
  fit_result2->correlationMatrix().Print();
  TFile   fitresultwritetofile2("/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots/FitResults2.root","recreate");
  fit_result2->Write("fit_result");
  fitresultwritetofile2.Close();

  // Plots
  pdfSigTime1.getParameters(*data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots/FitResults1.txt");
  pdfSigTime2.getParameters(*data)->readFromFile("/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots/FitResults2.txt");
  PlotAcceptance(&accspline1, fit_result1, &accspline2, fit_result2, &tree);
 
  // PlotConfig cfg_plot_time("cfg_plot_time");
  // cfg_plot_time.set_plot_appendix("");
  // cfg_plot_time.set_plot_directory("/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots/PlotTime");
  // std::vector<std::string> components_time;
  // Plot Time(cfg_plot_time, obsTime, *data, pdfSigTime1, components_time);
  // Time.AddPlotArg(NumCPU(1));
  // Time.set_scaletype_x(kBoth);
  // Time.set_scaletype_y(kLogarithmic);
  // Time.PlotIt();

  return 0;
}

void PlotAcceptance(RooAbsReal* acceptance1, RooFitResult* fit_result1, RooAbsReal* acceptance2, RooFitResult* fit_result2, TTree* tree){

  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  gStyle->SetTitleOffset(1.15,"Y");
  gStyle->SetPadLeftMargin(0.16);
  TCanvas c("c","c",800,600);
  
  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");
  RooRealVar        obsTime_True("obsTime_True","#it{t}_{true}",0.25,10.25,"ps");

  TH1D hist_acceptance("hist_acceptance","hist_acceptance",250,obsTime.getMin(),obsTime.getMax());
  tree->Draw("obsTime_True>>hist_acceptance","exp(obsTime_True/1.519)*(idxPV==0&&(catBkg==0||catBkg==50)&&obsTime_True>0.25&&obsTime_True<10.25)");
  hist_acceptance.Print();
  hist_acceptance.Sumw2();
  hist_acceptance.Scale(1./hist_acceptance.GetSumOfWeights());
  hist_acceptance.Print();
  cout <<  hist_acceptance.GetSumOfWeights()  <<  endl;
  RooDataHist datahist_acceptance("datahist_acceptance","datahist_acceptance",obsTime,&hist_acceptance);
  datahist_acceptance.Print();
  RooAbsReal* acceptance_integral1 = acceptance1->createIntegral(obsTime);
  RooAbsReal* acceptance_integral2 = acceptance2->createIntegral(obsTime);
  
  c.SetLogx(false);
  RooPlot* plot = obsTime.frame(0.25,4.25,100);
  // acceptance1->plotOn(plot,VisualizeError(*fit_result,1),FillColor(kRed),FillStyle(3001),VLines(),Normalization(10./(hist_acceptance.GetNbinsX()*acceptance_integral->getVal())));
  acceptance1->plotOn(plot,LineColor(2),Normalization(10./(hist_acceptance.GetNbinsX()*acceptance_integral1->getVal())));
  acceptance2->plotOn(plot,LineColor(4),Normalization(10./(hist_acceptance.GetNbinsX()*acceptance_integral2->getVal())));
  plot->SetMinimum(0.);
  plot->SetMaximum(0.01);
  plot->GetYaxis()->SetTitle("acceptance");
  plot->Draw();
  hist_acceptance.Draw("same");
  printPlot(&c, "Acceptancespline", "/home/fmeier/lhcb-tank/b02dd/run/MC/SplineKnots");
}

