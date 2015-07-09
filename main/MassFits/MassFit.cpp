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
#include "doocore/config/EasyConfig.h"

// from DooFit
#include "URANIA/RooIpatia2.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/plotting/Plot/PlotSimultaneous.h"
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/plotting/fitresult/FitResultPrinter.h"
#include "doofit/fitter/splot/SPlotFit2.h"

// from DooSelection
#include "dooselection/reducer/Reducer.h"
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
using namespace dooselection::reducer;

void ChangeHistogramSettings(TH1* histogram);

int main(int argc, char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  bool massmodel_ipatia = config.getBool("ipatia");
  bool split_years      = config.getBool("split_years");
  bool calculate_sweights = config.getBool("calculate_sweights");

  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooRealVar        obsMassDauOne("obsMassDauOne","#it{m_{K#pi#pi}}",1800,1950,"MeV/c^{2}");
  RooRealVar        obsMassDauTwo("obsMassDauTwo","#it{m_{K#pi#pi}}",1800,1950,"MeV/c^{2}");

  RooRealVar        varBDT("BDTG2_classifier","BDTG2_classifier",-1,1);

  RooCategory       catDDFinalState("catDDFinalState","catDDFinalState");
  catDDFinalState.defineType("KpipiKpipi",11);
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

  RooArgSet         observables(obsMass,obsMassDauOne,obsMassDauTwo,"observables");
  RooArgSet         variables(varBDT,"variables");
  RooArgSet         varPIDs(varKminus_PID,varKplus_PID,varPiOneminus_PID,varPiOneplus_PID,varPiTwominus_PID,varPiTwoplus_PID,"varKaonProbNNs");
  RooArgSet         realvars(observables,variables,"realvars");
  realvars.add(varPIDs);
  RooArgSet         categories(catDDFinalState,catTriggerSetTopo234BodyBBDT,catYear,"categories");
  
  // Get data set
  EasyTuple         tuple(config.getString("tuple"),"B02DD",RooArgSet(realvars,categories));
  tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = tuple.ConvertToDataSet(Cut(TString(config.getString("cut"))));
  
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

  //==============================================================================================================================================
  // Mass PDF
  // Signal
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
  RooRealVar        parBkgBsDsDMassMean("parBkgBsDsDMassMean","Bs->DsD Mean Mass",5310,"MeV/c^{2}");

  RooRealVar        parBkgBsDsDMassSigma1("parBkgBsDsDMassSigma1","Sigma of Gaussian Mass",16,"MeV/c^{2}");
  RooRealVar        parBkgBsDsDMassCB1Expo("parBkgBsDsDMassCB1Expo","parBkgBsDsDMassCB1Expo",10);
  RooRealVar        parBkgBsDsDMassCB1Alpha("parBkgBsDsDMassCB1Alpha","parBkgBsDsDMassCB1Alpha",0.23);
  RooCBShape        pdfBkgBsDsDMassCB1("pdfBkgBsDsDMassCB1","Mass PDF 1",obsMass,parBkgBsDsDMassMean,parBkgBsDsDMassSigma1,parBkgBsDsDMassCB1Alpha,parBkgBsDsDMassCB1Expo);

  RooRealVar        parBkgBsDsDMassSigma2("parBkgBsDsDMassSigma2","Sigma of Gaussian Mass",22.5,"MeV/c^{2}");
  RooRealVar        parBkgBsDsDMassCB2Expo("parBkgBsDsDMassCB2Expo","parBkgBsDsDMassCB2Expo",10);
  RooRealVar        parBkgBsDsDMassCB2Alpha("parBkgBsDsDMassCB2Alpha","parBkgBsDsDMassCB2Alpha",-1.32);
  RooCBShape        pdfBkgBsDsDMassCB2("pdfBkgBsDsDMassCB2","Mass PDF 2",obsMass,parBkgBsDsDMassMean,parBkgBsDsDMassSigma2,parBkgBsDsDMassCB2Alpha,parBkgBsDsDMassCB2Expo);

  RooRealVar        parBkgBsDsDMassCBFraction("parBkgBsDsDMassCBFraction","parBkgBsDsDMassCBFraction",0.45);
  RooAddPdf         pdfBkgBsDsDMass("pdfBkgBsDsDMass","pdfBkgBsDsDMass",RooArgList(pdfBkgBsDsDMassCB1,pdfBkgBsDsDMassCB2),parBkgBsDsDMassCBFraction);

  // Unknown peaking background between Bd and Bs
  RooRealVar        parBkgBdBsMassMean("parBkgBdBsMassMean","Mean of unknown background between Bd and Bs",5310,"MeV/c^{2}");
  RooRealVar        parBkgBdBsMassSigma("parBkgBdBsMassSigma","Sigma of Gaussian Mass",16,"MeV/c^{2}");
  RooGaussian       pdfBkgBdBsMass("pdfBkgBdBsMass","pdfBkgBdBsMass",obsMass,parBkgBdBsMassMean,parBkgBdBsMassSigma);

  // Bs --> DD signal
  RooFormulaVar     parSigBsMassMean("parSigBsMassMean","Bs Mean Mass","@0+87.52",RooArgList(parSigMassMean));
  RooCBShape        pdfSigBsMassCB1("pdfSigBsMassCB1","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma1,parSigMassCB1Alpha,parSigMassCB1Expo);
  RooCBShape        pdfSigBsMassCB2("pdfSigBsMassCB2","Bs Mass PDF",obsMass,parSigBsMassMean,parSigMassSigma2,parSigMassCB2Alpha,parSigMassCB2Expo);
  if (!massmodel_ipatia) pdfSigBsMass = new RooAddPdf("pdfSigBsMass","Bs Mass PDF",RooArgList(pdfSigBsMassCB1,pdfSigBsMassCB2),parSigMassCBFraction);

  if (massmodel_ipatia) pdfSigBsMass = new RooIpatia2("pdfSigBsMass","pdfSigBsMass",obsMass,parSigMassL,parSigMassZeta,parSigMassBeta,parSigMassSigma,parSigBsMassMean,parSigMassAlpha1,parSigMassn1,parSigMassAlpha2,parSigMassn2);  
  
  // combinatorial background
  RooRealVar        parBkgExponent("parBkgExponent","parBkgExponent",-0.1,-1,1);
  RooExponential    pdfBkgMass("pdfBkgMass","pdfBkgMass",obsMass,parBkgExponent);

  //==============================================================================================================================================
  // Extend PDFs with yields
  RooRealVar        parSigYield_11("parSigYield_11","parSigYield_11",500,0,1000);
  RooRealVar        parSigYield_12("parSigYield_12","parSigYield_12",500,0,1000);
  RooRealVar        parSigYield("parSigYield","parSigYield",500,0,1000);
  RooRealVar        parBkgDsDYield_11("parBkgDsDYield_11","parBkgDsDYield_11",1000,0,2000);
  RooRealVar        parBkgDsDYield_12("parBkgDsDYield_12","parBkgDsDYield_12",1000,0,2000);
  RooRealVar        parBkgDsDYield("parBkgDsDYield","parBkgDsDYield",1000,0,2000);
  RooRealVar        parBkgBsDsDYield_11("parBkgBsDsDYield_11","parBkgBsDsDYield_11",20,0,100);
  RooRealVar        parBkgBsDsDYield_12("parBkgBsDsDYield_12","parBkgBsDsDYield_12",20,0,100);
  RooRealVar        parBkgBsDsDYield("parBkgBsDsDYield","parBkgBsDsDYield",20,0,100);
  RooRealVar        parBkgBdBsYield_11("parBkgBdBsYield_11","parBkgBdBsYield_11",20,0,100);
  RooRealVar        parBkgBdBsYield_12("parBkgBdBsYield_12","parBkgBdBsYield_12",20,0,100);
  RooRealVar        parBkgBdBsYield("parBkgBdBsYield","parBkgBdBsYield",20,0,100);
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
  RooExtendPdf      pdfBkgBdBsExtend_11("pdfBkgBdBsExtend_11","pdfBkgBdBsExtend_11",pdfBkgBdBsMass,parBkgBdBsYield_11);
  RooExtendPdf      pdfBkgBdBsExtend_12("pdfBkgBdBsExtend_12","pdfBkgBdBsExtend_12",pdfBkgBdBsMass,parBkgBdBsYield_12);
  RooExtendPdf      pdfBkgBdBsExtend("pdfBkgBdBsExtend","pdfBkgBdBsExtend",pdfBkgBdBsMass,parBkgBdBsYield);
  RooExtendPdf      pdfSigBsExtend_11("pdfSigBsExtend_11","pdfSigBsExtend_11",*pdfSigBsMass,parSigBsYield_11);
  RooExtendPdf      pdfSigBsExtend_12("pdfSigBsExtend_12","pdfSigBsExtend_12",*pdfSigBsMass,parSigBsYield_12);
  RooExtendPdf      pdfSigBsExtend("pdfSigBsExtend","pdfSigBsExtend",*pdfSigBsMass,parSigBsYield);
  RooExtendPdf      pdfBkgExtend_11("pdfBkgExtend_11","pdfBkgExtend_11",pdfBkgMass,parBkgYield_11);
  RooExtendPdf      pdfBkgExtend_12("pdfBkgExtend_12","pdfBkgExtend_12",pdfBkgMass,parBkgYield_12);
  RooExtendPdf      pdfBkgExtend("pdfBkgExtend","pdfBkgExtend",pdfBkgMass,parBkgYield);

  RooAddPdf         pdfMass_11("pdfMass_11","Mass PDF",RooArgList(pdfSigExtend_11,pdfBkgDsDExtend_11,pdfSigBsExtend_11,pdfBkgExtend_11,pdfBkgBdBsExtend_11/*,pdfBkgBsDsDExtend_11*/));
  RooAddPdf         pdfMass_12("pdfMass_12","Mass PDF",RooArgList(pdfSigExtend_12,pdfBkgDsDExtend_12,pdfSigBsExtend_12,pdfBkgExtend_12,pdfBkgBdBsExtend_12/*,pdfBkgBsDsDExtend_12*/));
  
  RooAbsPdf*        pdfMass;

  if (split_years) {
    RooSimultaneous* pdfSimMass = new RooSimultaneous("pdfSimMass","pdfSimMass",catYear);
    pdfSimMass->addPdf(pdfMass_11,"2011");
    pdfSimMass->addPdf(pdfMass_12,"2012");
    pdfMass = pdfSimMass;
  }
  else pdfMass = new RooAddPdf("pdfMass","Mass PDF",RooArgList(pdfSigExtend,pdfBkgDsDExtend,pdfSigBsExtend,pdfBkgExtend,pdfBkgBdBsExtend/*,pdfBkgBsDsDExtend*/));

  // Get Starting Values and Fit PDF to data
  pdfMass->Print();
  pdfMass->getParameters(data)->readFromFile("/home/fmeier/git/b02dd/config/StartingValues/StartingValues_Mass.txt");
  pdfMass->getParameters(data)->writeToFile("/home/fmeier/storage03/b02dd/run/Mass/StartingValues_Mass.new");
  RooLinkedList fitting_args;
  fitting_args.Add((TObject*)(new RooCmdArg(NumCPU(config.getInt("num_cpu")))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minos(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Strategy(2))));
  fitting_args.Add((TObject*)(new RooCmdArg(Save(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Timer(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Minimizer("Minuit2","minimize"))));
  fitting_args.Add((TObject*)(new RooCmdArg(SumW2Error(false))));
  fitting_args.Add((TObject*)(new RooCmdArg(Extended(true))));
  fitting_args.Add((TObject*)(new RooCmdArg(Optimize(1))));

  RooDataSet* optimized_data = dynamic_cast<RooDataSet*>(data.reduce("varKminus_PID>0.12&&varKplus_PID>0.12&&varPiOneminus_PID<0.5&&varPiOneplus_PID<0.5&&varPiTwominus_PID<0.7&&varPiTwoplus_PID<0.7"));
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
  components_mass += "pdfSigExtend.*", "pdfBkgDsDExtend.*", "pdfSigBsExtend.*", "pdfBkgExtend.*", "pdfBkgBdBsExtend.*", "pdfBkgBsDsDExtend.*";
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
    RooArgSet set_of_yields_11(parSigYield_11,parBkgDsDYield_11,parSigBsYield_11,parBkgYield_11,parBkgBdBsYield_11/*,parBkgBsDsDYield_11*/);
    RooArgSet set_of_yields_12(parSigYield_12,parBkgDsDYield_12,parSigBsYield_12,parBkgYield_12,parBkgBdBsYield_12/*,parBkgBsDsDYield_12*/);
    SPlotFit2 splotfit(*pdfMass,*optimized_data,RooArgSet(set_of_yields_11,set_of_yields_12));
    splotfit.set_use_minos(false);
    splotfit.set_num_cpu(config.getInt("num_cpu"));
    
    dooselection::reducer::SPlotterReducer spr(splotfit, RooArgSet(obsMass,catYear));
    spr.set_input_file_path(config.getString("tuple"));
    spr.set_input_tree_path("B02DD");
    spr.set_output_file_path(config.getString("sweights_tuple"));
  
    spr.set_output_tree_path("B02DD");
    spr.set_cut_string(string(obsMass.GetName())+">="+to_string(obsMass.getMin())+"&&"+string(obsMass.GetName())+"<="+to_string(obsMass.getMax())+"&&catDDFinalState==11&&catTriggerSetTopo234BodyBBDT==1&&"+string(config.getString("cut")));
    spr.set_plot_directory(string("/home/fmeier/storage03/b02dd/run/Reducer/Plots"));
    spr.Initialize();
    spr.Run();
    spr.Finalize();

    Reducer AReducer;
    AReducer.set_input_file_path(config.getString("sweights_tuple"));
    AReducer.set_input_tree_path("B02DD");
    AReducer.set_output_file_path(config.getString("sweights_tuple"));
    AReducer.set_output_tree_path("B02DD");

    AReducer.Initialize();
  
    ReducerLeaf<Double_t>& SigWeight = AReducer.CreateDoubleLeaf("SigWeight",0.);
    SigWeight.Add(AReducer.GetInterimLeafByName("parSigYield_11_sw"), AReducer.GetInterimLeafByName("parSigYield_12_sw"));
    ReducerLeaf<Double_t>& BsSigWeight = AReducer.CreateDoubleLeaf("BsSigWeight",0.);
    BsSigWeight.Add(AReducer.GetInterimLeafByName("parSigBsYield_11_sw"), AReducer.GetInterimLeafByName("parSigBsYield_12_sw"));
    ReducerLeaf<Double_t>& BkgWeight = AReducer.CreateDoubleLeaf("BkgWeight",0.);
    BkgWeight.Add(AReducer.GetInterimLeafByName("parBkgYield_11_sw"), AReducer.GetInterimLeafByName("parBkgYield_12_sw"));
  
    AReducer.Run();
    AReducer.Finalize();
  }
  
  return 0;
}

void ChangeHistogramSettings(TH1* histogram){
  histogram->GetYaxis()->SetTitle("");
  histogram->SetMinimum(0);
  histogram->SetMaximum(10);
}
