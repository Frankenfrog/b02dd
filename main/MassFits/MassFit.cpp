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

void ChangeHistogramSettings(TH1* histogram);

int main(int argc, char * argv[]){

  bool massmodel_ipatia = false;
  bool split_years      = true;
  bool calculate_sweights = true;

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1845,1895,"MeV/c^{2}");

  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  RooRealVar        varDplusMassHypo_KKpi("varDplusMassHypo_KKpi","varDplusMassHypo_KKpi",0,5000);
  RooRealVar        varDplusMassHypo_KpiK("varDplusMassHypo_KpiK","varDplusMassHypo_KpiK",0,5000);
  RooRealVar        varDminusMassHypo_KKpi("varDminusMassHypo_KKpi","varDminusMassHypo_KKpi",0,5000);
  RooRealVar        varDminusMassHypo_KpiK("varDminusMassHypo_KpiK","varDminusMassHypo_KpiK",0,5000);

  RooRealVar        varPiOneplus_DLLk("Dplus_piplus_or_Kplus_One_RichDLLk","Dplus_piplus_or_Kplus_One_RichDLLk",-100,100);
  RooRealVar        varPiTwoplus_DLLk("Dplus_piplus_or_Kplus_Two_RichDLLk","Dplus_piplus_or_Kplus_Two_RichDLLk",-100,100);
  RooRealVar        varPiOneminus_DLLk("Dminus_piminus_or_Kminus_One_RichDLLk","Dminus_piminus_or_Kminus_One_RichDLLk",-100,100);
  RooRealVar        varPiTwominus_DLLk("Dminus_piminus_or_Kminus_Two_RichDLLk","Dminus_piminus_or_Kminus_Two_RichDLLk",-100,100);

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",1);
  RooCategory       catTriggerSetTopo234BodyBBDT("catTriggerSetTopo234BodyBBDT","catTriggerSetTopo234BodyBBDT");
  catTriggerSetTopo234BodyBBDT.defineType("triggered",1);

  RooCategory       catYear("catYear","catYear");
  catYear.defineType("2011",2011);
  catYear.defineType("2012",2012);

  RooRealVar        varKminus_PID("varKminus_PID","varKminus_PID",0,1);
  RooRealVar        varKplus_PID("varKplus_PID","varKplus_PID",0,1);
  RooRealVar        varPiOneminus_PID("varPiOneminus_PID","varPiOneminus_PID",0,1);
  RooRealVar        varPiOneplus_PID("varPiOneplus_PID","varPiOneplus_PID",0,1);
  RooRealVar        varPiTwominus_PID("varPiTwominus_PID","varPiTwominus_PID",0,1);
  RooRealVar        varPiTwoplus_PID("varPiTwoplus_PID","varPiTwoplus_PID",0,1);

  RooArgSet         observables(obsMass/*,obsMassDauOne,obsMassDauTwo*/,"observables");
  RooArgSet         variables(varBDT,"variables");
  RooArgSet         MassHypos(varDplusMassHypo_KKpi,varDplusMassHypo_KpiK,varDminusMassHypo_KKpi,varDminusMassHypo_KpiK,"MassHypos");
  // variables.add(MassHypos);
  RooArgSet         DLLs(varPiOneplus_DLLk,varPiOneminus_DLLk,varPiTwoplus_DLLk,varPiTwominus_DLLk,"DLLs");
  // variables.add(DLLs);
  RooArgSet         varPIDs(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID,"varKaonProbNNs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varPIDs);
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,catYear,"categories");
  
  // Get data set
  EasyTuple         tuple(argv[1],"B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(argv[2]));
  
  data.Print();

  RooDataSet*       data_2011 = dynamic_cast<RooDataSet*>(data.reduce("catYear==2011"));
  RooDataSet*       data_2012 = dynamic_cast<RooDataSet*>(data.reduce("catYear==2012"));
  RooDataSet*       data_2011_BDT = dynamic_cast<RooDataSet*>(data_2011->reduce("BDTG2_classifier>-0.843"));
  RooDataSet*       data_2012_BDT = dynamic_cast<RooDataSet*>(data_2012->reduce("BDTG2_classifier>-0.843"));
  RooDataSet*       data_BDT = dynamic_cast<RooDataSet*>(data.reduce("BDTG2_classifier>-0.843"));

  TH1*              hist_2011 = data_2011->createHistogram("hist_2011",obsMass);
  TH1*              hist_2012 = data_2012->createHistogram("hist_2012",obsMass);
  TH1*              hist_2011_BDT = data_2011_BDT->createHistogram("hist_2011_BDT",obsMass);
  TH1*              hist_2012_BDT = data_2012_BDT->createHistogram("hist_2012_BDT",obsMass);
  TH1*              hist = data.createHistogram("hist",obsMass);
  TH1*              hist_BDT = data_BDT->createHistogram("hist_BDT",obsMass);

  hist_2011->Divide(hist_2011_BDT);
  hist_2012->Divide(hist_2012_BDT);
  hist->Divide(hist_BDT);
  gROOT->SetStyle("Plain");
  setStyle("LHCb");
  // TCanvas c("c","c",800,600);
  // ChangeHistogramSettings(hist_2011);
  // hist_2011->Draw();
  // c.SaveAs("/home/fmeier/storage03/b02dd/run/BDTinvEffect_11.pdf");
  // ChangeHistogramSettings(hist_2012);
  // hist_2012->Draw();
  // c.SaveAs("/home/fmeier/storage03/b02dd/run/BDTinvEffect_12.pdf");
  // ChangeHistogramSettings(hist);
  // hist->Draw();
  // c.SaveAs("/home/fmeier/storage03/b02dd/run/BDTinvEffect.pdf");

  // Mass PDF
  RooAbsPdf*        pdfSigMass;
  RooAbsPdf*        pdfSigBsMass;
  RooRealVar        parSigMassMean("parSigMassMean","Bd Mean Mass",5280,5270,5290,"MeV/c^{2}");

  RooRealVar        parSigMassSigma1("parSigMassSigma1","Sigma of Gaussian Mass",9,7,20,"MeV/c^{2}");
  RooRealVar        parSigMassCB1Expo("parSigMassCB1Expo","parSigMassCB1Expo",10);
  RooRealVar        parSigMassCB1Alpha("parSigMassCB1Alpha","parSigMassCB1Alpha",1.28);
  RooCBShape        pdfSigMassCB1("pdfSigMassCB1","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);

  RooRealVar        parSigMassSigma2("parSigMassSigma2","Sigma of Gaussian Mass",8.0,1.0,10.0,"MeV/c^{2}");
  RooRealVar        parSigMassCB2Expo("parSigMassCB2Expo","parSigMassCB2Expo",10);
  RooRealVar        parSigMassCB2Alpha("parSigMassCB2Alpha","parSigMassCB2Alpha",-1.32);
  RooCBShape        pdfSigMassCB2("pdfSigMassCB2","Signal Mass PDF",obsMass,parSigMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);

  RooRealVar        parSigMassCBFraction("parSigMassCBFraction","parSigMassCBFraction",0.5,0,1);
  if (!massmodel_ipatia)  pdfSigMass = new RooAddPdf("pdfSigMass","pdfSigMass",RooArgList(pdfSigMassCB1,pdfSigMassCB2),parSigMassCBFraction);

  RooRealVar        parSigMassL("parSigMassL","parSigMassL",-5.6);
  RooRealVar        parSigMassZeta("parSigMassZeta","parSigMassZeta",0);
  RooRealVar        parSigMassBeta("parSigMassBeta","parSigMassBeta",0,-0.1,0.1);
  RooRealVar        parSigMassSigma("parSigMassSigma","parSigMassSigma",9.0,5,15,"MeV/c^{2}");
  RooRealVar        parSigMassAlpha1("parSigMassAlpha1","parSigMassAlpha1",1.31);
  RooRealVar        parSigMassn1("parSigMassn1","parSigMassn1",10);
  RooRealVar        parSigMassAlpha2("parSigMassAlpha2","parSigMassAlpha2",2.28);
  RooRealVar        parSigMassn2("parSigMassn2","parSigMassn2",10);
  if (massmodel_ipatia) pdfSigMass = new RooIpatia2("pdfSigMass","pdfSigMass",obsMass,parSigMassL,parSigMassZeta,parSigMassBeta,parSigMassSigma,parSigMassMean,parSigMassAlpha1,parSigMassn1,parSigMassAlpha2,parSigMassn2);

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

  RooRealVar        parBkgBsDsDMassMean("parBkgBsDsDMassMean","Bs->DsD Mean Mass",5320,5310,5350,"MeV/c^{2}");
  RooRealVar        parBkgBsDsDMassSigma("parBkgBsDsDMassSigma","Sigma of Gaussian Mass",10.0,1.0,20.0,"MeV/c^{2}");
  RooGaussian       pdfBkgBsDsDMass("pdfBkgBsDsDMass","pdfBkgBsDsDMass",obsMass,parBkgBsDsDMassMean,parBkgBsDsDMassSigma);

  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.52",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);
  if (!massmodel_ipatia) pdfSigBsMass = new RooAddPdf("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB2),parSigMassCBFraction);

  if (massmodel_ipatia) pdfSigBsMass = new RooIpatia2("pdfSigBsMass","pdfSigBsMass",obsMass,parSigMassL,parSigMassZeta,parSigMassBeta,parSigMassSigma,parSigBsMassMean,parSigMassAlpha1,parSigMassn1,parSigMassAlpha2,parSigMassn2);  
  
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11("parBkgBsDsDYield_11","parBkgBsDsDYield_11",20,0,100);
  RooRealVar        parBkgBsDsDYield_12("parBkgBsDsDYield_12","parBkgBsDsDYield_12",20,0,100);
  RooRealVar        parBkgBsDsDYield("parBkgBsDsDYield","parBkgBsDsDYield",20,0,100);
  RooRealVar        parSigBsYield_11("parSigBsYield_11","parSigBsYield_11",100,0,1000);
  RooRealVar        parSigBsYield_12("parSigBsYield_12","parSigBsYield_12",100,0,1000);
  RooRealVar        parSigBsYield("parSigBsYield","parSigBsYield",100,0,1000);
  RooRealVar        parBkgYield_11("parBkgYield_11","parBkgYield_11",5000,0,10000);
  RooRealVar        parBkgYield_12("parBkgYield_12","parBkgYield_12",5000,0,10000);
  RooRealVar        parBkgYield("parBkgYield","parBkgYield",5000,0,10000);

  RooExtendPdf      pdfSigExtend_11("pdfSigExtend_11","pdfSigExtend_11",*pdfSigMass,parSigYield_11);
  RooExtendPdf      pdfSigExtend_12("pdfSigExtend_12","pdfSigExtend_12",*pdfSigMass,parSigYield_12);
  RooExtendPdf      pdfSigExtend("pdfSigExtend","pdfSigExtend",*pdfSigMass,parSigYield);
  RooExtendPdf      pdfBkgDsDExtend_11("pdfBkgDsDExtend_11","pdfBkgDsDExtend_11",pdfBkgDsDMass,parBkgDsDYield_11);
  RooExtendPdf      pdfBkgDsDExtend_12("pdfBkgDsDExtend_12","pdfBkgDsDExtend_12",pdfBkgDsDMass,parBkgDsDYield_12);
  RooExtendPdf      pdfBkgDsDExtend("pdfBkgDsDExtend","pdfBkgDsDExtend",pdfBkgDsDMass,parBkgDsDYield);
  RooExtendPdf      pdfBkgBsDsDExtend_11("pdfBkgBsDsDExtend_11","pdfBkgBsDsDExtend_11",pdfBkgBsDsDMass,parBkgBsDsDYield_11);
  RooExtendPdf      pdfBkgBsDsDExtend_12("pdfBkgBsDsDExtend_12","pdfBkgBsDsDExtend_12",pdfBkgBsDsDMass,parBkgBsDsDYield_12);
  RooExtendPdf      pdfBkgBsDsDExtend("pdfBkgBsDsDExtend","pdfBkgBsDsDExtend",pdfBkgBsDsDMass,parBkgBsDsDYield);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",*pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",*pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",*pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11,pdfBkgBsDsDExtend_11));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12,pdfBkgBsDsDExtend_12));
  
  RooAbsPdf*        pdfMass;

  if (split_years) {
    RooSimultaneous* pdfSimMass = new RooSimultaneous("pdfSimMass","pdfSimMass",catYear);
    pdfSimMass->addPdf(pdfMass_11,"2011");
    pdfSimMass->addPdf(pdfMass_12,"2012");
    pdfMass = pdfSimMass;
  }
  else pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend,pdfBkgBsDsDExtend));

  // Get Starting Values and Fit PDF to data
  pdfMass->Print();
  pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/StartingValues_Mass.new");
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

  RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.2&&varKplus_PID>0.2&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.65&&varPiTwoplus_PID<0.65"));
  // RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0."));
  optimized_data->Print();
  RooFitResult* fit_result = pdfMass->fitTo(*optimized_data, fitting_args);
  doofit::plotting::fitresult::FitResultPrinter fitresultprinter(*fit_result);
  fitresultprinter.Print();

  if (massmodel_ipatia) pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults_Ipatia.txt");
  else pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/FitResults.txt");

  PlotConfig cfg_plot_mass("cfg_plot_mass");
  cfg_plot_mass.InitializeOptions();
  cfg_plot_mass.set_plot_directory("/home/fmeier/storage03/b02dd/run/Mass/Plots");
  cfg_plot_mass.set_simultaneous_plot_all_categories(true);
  std::vector<std::string> components_mass;
  components_mass += "pdfSigExtend.*", "pdfBkgDsDExtend.*", "pdfSigBsExtend.*", "pdfBkgExtend.*", "pdfBkgBsDsDExtend.*";
  Plot* Mass;
  if (massmodel_ipatia) {
    if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, *optimized_data, *((RooSimultaneous*)pdfMass), components_mass, "Ipatia_obsMass");
    else Mass = new Plot(cfg_plot_mass, obsMass, *optimized_data, *pdfMass, components_mass, "Ipatia_obsMass");
  }
  else {
    if (split_years) Mass = new PlotSimultaneous(cfg_plot_mass, obsMass, *optimized_data, *((RooSimultaneous*)pdfMass), components_mass, "obsMass");
    else Mass = new Plot(cfg_plot_mass, obsMass, *optimized_data, *pdfMass, components_mass, "obsMass");
  }
  Mass->PlotItLogNoLogY();

  if (calculate_sweights && split_years){
    RooArgSet set_of_yields_11(parSigYield_11,parBkgDsDYield_11,parSigBsYield_11,parBkgYield_11,parBkgBsDsDYield_11);
    RooArgSet set_of_yields_12(parSigYield_12,parBkgDsDYield_12,parSigBsYield_12,parBkgYield_12,parBkgBsDsDYield_12);
    SPlotFit2 splotfit(*pdfMass,*optimized_data,RooArgSet(set_of_yields_11,set_of_yields_12));
    splotfit.set_use_minos(false);
    splotfit.set_num_cpu(4);
    
    dooselection::reducer::SPlotterReducer spr(splotfit, RooArgSet(obsMass,catYear));
    spr.set_input_file_path(argv[1]);
    spr.set_input_tree_path("B02DD");
    spr.set_output_file_path(argv[3]);
  
    spr.set_output_tree_path("B02DD");
    spr.set_cut_string(string(obsMass.GetName())+">="+to_string(obsMass.getMin())+"&&"+string(obsMass.GetName())+"<="+to_string(obsMass.getMax())+"&&catDDFinalState==1&&catTriggerSetTopo234BodyBBDT==1&&"+string(argv[2]));
    spr.set_plot_directory(string("/home/fmeier/storage03/b02dd/run/Reducer/Plots"));
    spr.Initialize();
    spr.Run();
    spr.Finalize();
  }
  
  return 0;
}

void ChangeHistogramSettings(TH1* histogram){
  histogram->GetYaxis()->SetTitle("");
  histogram->SetMinimum(0);
  histogram->SetMaximum(10);
}
