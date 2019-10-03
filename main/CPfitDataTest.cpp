#include "iostream"
#include "vector"

#include "TFile.h"

#include "RooDataSet.h"
#include "RooBDecay.h"
#include "RooDecay.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooUnblindUniform.h"
#include "RooFitResult.h"
#include "RooArgSet.h"
#include "RooAbsArg.h"
#include "RooConstVar.h"
#include "RooGaussModel.h"
#include "RooDecay.h"

#include "doocore/lutils/lutils.h"
#include "doofit/builder/EasyPdf/EasyPdf.h"
#include "doocore/io/EasyTuple.h"
#include "doofit/plotting/Plot/Plot.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
#include "P2VV/RooCubicSplineFun.h"
#include "P2VV/RooGaussEfficiencyModel.h"
#include "P2VV/RooEffResAddModel.h"

#include "DecRateCoeff/DecRateCoeff_Bd.h"

using namespace RooFit;
using namespace std;

int main(int argc, char const *argv[])
{
    // lhcb style
    doocore::lutils::setStyle();

    // observables
    RooRealVar              obsTime("obsTime", "#it{t}", 0.3, 10.3, "ps");

    RooCategory             obsTagOS("obsTagOS", "obsTagOS");
                            obsTagOS.defineType("B",+1);
                            obsTagOS.defineType("Bbar",-1);
                            obsTagOS.defineType("untagged",0);
    RooRealVar              obsEtaOS("obsEtaOS", "obsEtaOS", 0.0, 0.0, 0.5);

    RooCategory             obsTagSS("obsTagSS", "obsTagSS");
                            obsTagSS.defineType("B",+1);
                            obsTagSS.defineType("Bbar",-1);
                            obsTagSS.defineType("untagged",0);
    RooRealVar              obsEtaSS("obsEtaSS", "obsEtaSS", 0.0, 0.0, 0.5);

    RooCategory             catChargeConf("catChargeConf", "catChargeConf");
                            catChargeConf.defineType("Dst+D-",-1);
                            catChargeConf.defineType("Dst-D+",+1);

    RooArgSet               observables("observableset");
                            observables.add(obsTime);
                            observables.add(catChargeConf);
                            observables.add(obsTagOS);
                            observables.add(obsEtaOS);
                            observables.add(obsTagSS);
                            observables.add(obsEtaSS);

    // // dataset
    RooDataSet*             data2;

    // Data
    RooRealVar              Bd_yield_sw("Bd_yield_sw", "Bd_yield_sw", -1000.0, 1000.0);
                            observables.add(Bd_yield_sw);

    doocore::io::EasyTuple  etuple("/fhgfs/groups/e5/lhcb/analysis/B2OC/B02DstD/Data/combined/run1/DT1112_B02DstD_Stripping21r0r1_DVv41r3_20170606_mschellenberg_Kpi_Kpipi_TupleEplus_test2plus.root",
                            "DecayTree", observables);
                            data2 = (RooDataSet*) &etuple.ConvertToDataSet(WeightVar(Bd_yield_sw));

    // // corrected weights
    // double weightSum = 0;
    // double weightSquareSum = 0;

    // for (int i = 0; i < data2->numEntries(); ++i)
    // {
    //     cout << "sweight: " <<  ((RooRealVar&) (*data2->get(i))["Bd_yield_sw"]).getValV() << endl;
    //     weightSum += ((RooRealVar&) (*data2->get(i))["Bd_yield_sw"]).getValV();
    //     weightSquareSum += (((RooRealVar&) (*data2->get(i))["Bd_yield_sw"]).getValV())*(((RooRealVar&) (*data2->get(i))["Bd_yield_sw"]).getValV());

    // }
    // RooFormulaVar               sWeightfixed("sWeightfixed", "sWeightfixed", "@0*@1/@2", RooArgList(Bd_yield_sw, (RooRealVar&) RooConst(weightSum), (RooRealVar&) RooConst(weightSquareSum)));

    // RooRealVar* sWeightfixedVar =  (RooRealVar*)data2->addColumn(sWeightfixed);
    //                          observables.add(*sWeightfixedVar);

    // RooDataSet*              data = new RooDataSet("data_sWeighted", "data_sWeighted", data2, observables, "", sWeightfixedVar->GetName());


    // parameters
    RooRealVar              parTau("parTau", "parTau", 1.52);
    RooRealVar              parDM("parDM", "parDM", 0.5065);
    RooRealVar              parDGamma("parDGamma", "parDGamma", 0.0);

    RooRealVar              parAdet("parAdet", "parAdet", 0.0);
    RooRealVar              parAprod("parAprod", "parAprod", 0.0);

    RooRealVar              parCh("parCh", "parCh", 0.0);
    RooRealVar              parChbar("parChbar", "parChbar", 0.0);
    RooRealVar              parSh("parSh", "parSh", 0.0);
    RooRealVar              parShbar("parShbar", "parShbar", 0.0);

    RooRealVar              parCmean("parCmean", "parCmean", 0.0);
    RooRealVar              parCdelta("parCdelta", "parCdelta", 0.0);
    RooRealVar              parSmean("parSmean", "parSmean", 0.0);
    RooRealVar              parSdelta("parSdelta", "parSdelta", 0.0);

    RooUnblindUniform       parCmeanBlind("parCmeanBlind", "parCmeanBlind", "CmeanB02DstD5fb", 1.0, parCmean);
    RooUnblindUniform       parCdeltaBlind("parCdeltaBlind", "parCdeltaBlind", "CdeltaB02DstD5fb", 1.0, parCdelta);
    RooUnblindUniform       parSmeanBlind("parSmeanBlind", "parSmeanBlind", "SmeanB02DstD5fb", 1.0, parSmean);
    RooUnblindUniform       parSdeltaBlind("parSdeltaBlind", "parSdeltaBlind", "SdeltaB02DstD5fb", 1.0, parSdelta);

    RooFormulaVar           parS("parS", "parS", "@0+@1", RooArgList(parSmeanBlind, parSdeltaBlind));
    RooFormulaVar           parSbar("parSbar", "parSbar", "@0-@1", RooArgList(parSmeanBlind, parSdeltaBlind));
    RooFormulaVar           parC("parC", "parC", "@0+@1", RooArgList(parCmeanBlind, parCdeltaBlind));
    RooFormulaVar           parCbar("parCbar", "parCbar", "@0-@1", RooArgList(parCmeanBlind, parCdeltaBlind));

    RooRealVar              parTagEffOS("parTagEffOS", "parTagEffOS", 0.0);
    RooRealVar              parTagDEffOS("parTagDEffOS", "parTagDEffOS", 0.0);
    RooRealVar              parTagEffSS("parTagEffSS", "parTagEffSS", 0.0);
    RooRealVar              parTagDEffSS("parTagDEffSS", "parTagDEffSS", 0.0);

    // decratecoeffs
    DecRateCoeff_Bd                         parCosh(
                                                "parCosh",
                                                "parCosh",
                                                DecRateCoeff_Bd::kCosh,
                                                catChargeConf,
                                                parCh,
                                                parChbar,
                                                obsTagOS,
                                                obsEtaOS,
                                                obsEtaOS,
                                                parTagEffOS,
                                                parTagDEffOS,
                                                obsTagSS,
                                                obsEtaSS,
                                                obsEtaSS,
                                                parTagEffSS,
                                                parTagDEffSS,
                                                parAprod,
                                                parAdet
                                            );
    DecRateCoeff_Bd                         parSinh(
                                                "parSinh",
                                                "parSinh",
                                                DecRateCoeff_Bd::kSinh,
                                                catChargeConf,
                                                parSh,
                                                parShbar,
                                                obsTagOS,
                                                obsEtaOS,
                                                obsEtaOS,
                                                parTagEffOS,
                                                parTagDEffOS,
                                                obsTagSS,
                                                obsEtaSS,
                                                obsEtaSS,
                                                parTagEffSS,
                                                parTagDEffSS,
                                                parAprod,
                                                parAdet
                                            );
    DecRateCoeff_Bd                         parCos(
                                                "parCos",
                                                "parCos",
                                                DecRateCoeff_Bd::kCos,
                                                catChargeConf,
                                                parC,
                                                parCbar,
                                                obsTagOS,
                                                obsEtaOS,
                                                obsEtaOS,
                                                parTagEffOS,
                                                parTagDEffOS,
                                                obsTagSS,
                                                obsEtaSS,
                                                obsEtaSS,
                                                parTagEffSS,
                                                parTagDEffSS,
                                                parAprod,
                                                parAdet
                                            );
    DecRateCoeff_Bd                         parSin(
                                                "parSin",
                                                "parSin",
                                                DecRateCoeff_Bd::kSin,
                                                catChargeConf,
                                                parS,
                                                parSbar,
                                                obsTagOS,
                                                obsEtaOS,
                                                obsEtaOS,
                                                parTagEffOS,
                                                parTagDEffOS,
                                                obsTagSS,
                                                obsEtaSS,
                                                obsEtaSS,
                                                parTagEffSS,
                                                parTagDEffSS,
                                                parAprod,
                                                parAdet
                                            );

    // resolution
    RooRealVar              parResMean("parResMean", "parResMean", 0);
    RooRealVar              parResSigma1("parResSigma1", "parResSigma1", 0.1);
    RooRealVar              parResSigma2("parResSigma2", "parResSigma2", 0.1);
    RooRealVar              parResSigma3("parResSigma3", "parResSigma3", 0.1);
    RooRealVar              parResFrac1("parResFrac1", "parResFrac1", 0.5);
    RooRealVar              parResFrac2("parResFrac2", "parResFrac2", 0.5);

    // acceptance
    vector<double> knots;
    knots.push_back(0.3);
    knots.push_back(0.5);
    knots.push_back(2.7);
    knots.push_back(6.3);
    knots.push_back(10.3);

    RooArgList splineList("splineList");

    RooRealVar* parAccSpline;

    for (unsigned int i=1; i <= (knots.size()); i++){
        std::string binname = "parAccSpline" + boost::lexical_cast<std::string>(i);
        parAccSpline = new RooRealVar(binname.c_str(),binname.c_str(),1,0,4);
        splineList.add(*parAccSpline);
        if (i==1 || i==knots.size())
        {
            splineList.add(*parAccSpline);
        }
    }

    // pdfs
    RooCubicSplineFun           pdfAccSpline("pdfAccSpline", "pdfAccSpline", obsTime, knots, splineList);
    RooGaussEfficiencyModel     pdfResGauss1("pdfResGauss1", "pdfResGauss1", obsTime, dynamic_cast<RooAbsGaussModelEfficiency&>(pdfAccSpline), parResMean, parResSigma1);
    RooGaussEfficiencyModel     pdfResGauss2("pdfResGauss2", "pdfResGauss2", obsTime, dynamic_cast<RooAbsGaussModelEfficiency&>(pdfAccSpline), parResMean, parResSigma2);
    RooGaussEfficiencyModel     pdfResGauss3("pdfResGauss3", "pdfResGauss3", obsTime, dynamic_cast<RooAbsGaussModelEfficiency&>(pdfAccSpline), parResMean, parResSigma3);

    RooEffResAddModel           pdfResGauss("pdfResGauss", "pdfResGauss", RooArgList(pdfResGauss1, pdfResGauss2, pdfResGauss3), RooArgList(parResFrac1, parResFrac2));
    RooBDecay                   pdfDecayTime("pdfDecayTime", "pdfDecayTime", obsTime, parTau, parDGamma, parCosh, parSinh, parCos, parSin, parDM, pdfResGauss, RooBDecay::SingleSided);
    // RooDecay                    pdfDecayTime("pdfDecayTime", "pdfDecayTime", obsTime, parTau, pdfResGauss, RooDecay::SingleSided);

    // fit
    pdfDecayTime.getParameters(data2)->readFromFile("/net/lhcb-tank/user_area/pibis/repos/B02DstD/config/fits/CPFitData_inputparameters.txt");

    // options to control construction of fit
    RooLinkedList fitting_args;
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::NumCPU(10))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Offset(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Extended(false))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Minimizer("Minuit2","migrad"))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Optimize(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Hesse(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Minos(false))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Save(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Strategy(2))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::SumW2Error(true))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::PrintLevel(1))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::Warnings(false))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::PrintEvalErrors(-1))));
    fitting_args.Add((TObject*)(new RooCmdArg(RooFit::ConditionalObservables(RooArgSet(obsEtaOS, obsEtaSS)))));

    cout << "printing data" << endl;
    // data->Print();
    data2->Print();

    cout << "printing data verbose" << endl;
    // data->Print("v");
    data2->Print("v");

    RooFitResult * fitResult = pdfDecayTime.fitTo(*data2, fitting_args);
    
    pdfDecayTime.getParameters(data2)->writeToFile("/net/lhcb-tank/user_area/pibis/repos/B02DstD/config/fits/CPFitData_outputparameters.txt");

    if (fitResult)
    {
        doofit::fitter::easyfit::FitResultPrinter printer(*fitResult);
        printer.Print();
        fitResult->correlationMatrix().Print();
    }

    // plotting with doofit
    doofit::plotting::PlotConfig cfg_plot("cfg_plot");
    cfg_plot.InitializeOptions();
    cfg_plot.set_label_text("LHCb simulation");
    cfg_plot.set_plot_directory("/net/lhcb-tank/user_area/pibis/repos/B02DstD/plots/decayTimeFits/CPFitData");

    // plot PDF and directly specify components
    RooArgSet plotset(catChargeConf, obsTagOS, obsEtaOS, obsTagSS, obsEtaSS);

    doofit::plotting::Plot myplot1(cfg_plot, obsTime, *data2, RooArgList(pdfDecayTime), "B02DstD");
    myplot1.set_scaletype_y(doofit::plotting::kBoth);
    // myplot1.AddPlotArg(ProjWData(plotset, *data2));
    myplot1.AddPlotArg(NumCPU(10));
    // myplot1.AddPlotArg(Normalization(1.0, RooAbsReal::NumEvent));
    myplot1.PlotIt();
    myplot1.PlotIt();

    return 0;
}