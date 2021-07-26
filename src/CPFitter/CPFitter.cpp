#include "CPFitter.h"

// ========================== public ========================== 
CPFitter::CPFitter(doocore::config::EasyConfig config):
config_(config),
paths_(convertPairVectorToVectorPair(config_.getVoStringPairs("finalstates")).second),
years_(convertVectorStringToInt(config_.getVoStrings("years"))),
finalstates_(convertVectorStringToInt(convertPairVectorToVectorPair(config_.getVoStringPairs("finalstates")).first)),
knots_(convertVectorStringToDouble(config_.getVoStrings("knots"))),
useMC_(config_.getBool("useMC")),
doMassFit_(config_.getBool("doMassFit")),
useTrueTags_(config_.getBool("useTrueTags")),
useOSTagger_(config_.getBool("useOSTagger")),
useSSTagger_(config_.getBool("useSSTagger")),
usePerEventRes_(config_.getBool("usePerEventRes")),
readWS_(config_.getBool("readWS")),
obs_(RooArgSet()),
ws_(RooWorkspace("workspace"))
{
    // Info
    doocore::io::sinfo << "-INFO-  \t" << "You are using sin(2beta eff) Fitter" << doocore::io::endmsg;

    doocore::io::sinfo << "-INFO-  \t" << "Using following years:";
    for (int i = 0; i < years_.size(); ++i){doocore::io::sinfo << "\t" << years_[i];}
    doocore::io::sinfo << doocore::io::endmsg;

    doocore::io::sinfo << "-INFO-  \t" << "Using following finalstates:" << doocore::io::endmsg;
    for (int i = 0; i < finalstates_.size(); ++i){doocore::io::sinfo << "-INFO-  \t" << finalstates_[i] << "\t" << paths_[i] << doocore::io::endmsg;}

    if (useMC_)                     doocore::io::sinfo << "-INFO-  \t" << "Using simulation" << doocore::io::endmsg;
    else                            doocore::io::sinfo << "-INFO-  \t" << "Using data" << doocore::io::endmsg;

    if (doMassFit_)                 doocore::io::sinfo << "-INFO-  \t" << "Performing massfit" << doocore::io::endmsg;
    else                            doocore::io::sinfo << "-INFO-  \t" << "Not performing massfit" << doocore::io::endmsg;

    if (useTrueTags_)               doocore::io::sinfo << "-INFO-  \t" << "Using true tags" << doocore::io::endmsg;
    else                            doocore::io::sinfo << "-INFO-  \t" << "Not using true tags" << doocore::io::endmsg;

    if (useOSTagger_)               doocore::io::sinfo << "-INFO-  \t" << "Using OS Tagger" << doocore::io::endmsg;
    else                            doocore::io::sinfo << "-INFO-  \t" << "Not using OS Tagger" << doocore::io::endmsg;

    if (useSSTagger_)               doocore::io::sinfo << "-INFO-  \t" << "Using SS Tagger" << doocore::io::endmsg;
    else                            doocore::io::sinfo << "-INFO-  \t" << "Not using SS Tagger" << doocore::io::endmsg;

    if (usePerEventRes_)            doocore::io::sinfo << "-INFO-  \t" << "Using per event resolution" << doocore::io::endmsg;
    else                            doocore::io::sinfo << "-INFO-  \t" << "Using average resolution" << doocore::io::endmsg;

    // Errors
    if (useTrueTags_ && (useOSTagger_ || useSSTagger_)){
                                    doocore::io::serr << "-ERROR-  \t" << "Cannot use true tags and additional tagger" << doocore::io::endmsg;
                                    throw std::exception(); 
    }

    if (!(useTrueTags_ || useOSTagger_ || useSSTagger_)){
                                    doocore::io::serr << "-ERROR-  \t" << "Cannot use no taggers" << doocore::io::endmsg;
                                    throw std::exception(); 
    }

    if (!useMC_ && useTrueTags_){
                                    doocore::io::serr << "-ERROR-  \t" << "Cannot use true tags with data!" << doocore::io::endmsg;
                                    throw std::exception(); 
    }

    if (readWS_){
        readWS();
    }
    else{
        buildObservableSet_();
        buildFitPDF_();
        readData_();
        saveWS();
    }

    // ws_.Print("v");
}

RooFitResult CPFitter::performTimeFit(RooLinkedList fittingArgs){
    doocore::io::EasyTuple*     etuple = new doocore::io::EasyTuple("/fhgfs/groups/e5/lhcb/analysis/B2OC/B02DstD/forLHCBWeek/DT1112_B02DstD_Stripping21r0r1_DVv41r3_20170606_mschellenberg_TupleC1_VarRemoved_sanityCuts_LoopVar_Kpi_Kpipi_vetoes__BDTapplied_0_16plus.root"
                                ,"DecayTree", obs_);
    RooDataSet* tempData = (RooDataSet*) &etuple->ConvertToDataSet(RooFit::WeightVar("SigWeight"));

    ws_.pdf("pdfDecayTime")->getParameters((RooDataSet&) *ws_.data("data"))->readFromFile((config_.getString("inputparameters").c_str()));
    ws_.pdf("pdfDecayTime")->printComponentTree();
    if (fittingArgs.GetSize() == 0){
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::NumCPU(30))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Offset(true))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Extended(false))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Minimizer("Minuit2","migrad"))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Optimize(true))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Hesse(true))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Minos(false))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Save(true))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Strategy(2))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::SumW2Error(!useMC_))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::PrintLevel(1))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::Warnings(false))));
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::PrintEvalErrors(-1))));

        RooArgSet*                  condObsSet = new RooArgSet("condObsSet");
        if (useTrueTags_)           condObsSet->add((RooRealVar&) obs_["obsEtaTRUE"]);
        if (useOSTagger_)           condObsSet->add((RooRealVar&) obs_["obsEtaOS"]);
        if (useSSTagger_)           condObsSet->add((RooRealVar&) obs_["obsEtaSS"]);
                                    fittingArgs.Add((TObject*)(new RooCmdArg(RooFit::ConditionalObservables(*condObsSet))));
    }
    ws_.data("data")->Print("v");

    // RooFitResult*                   fitResult = ((RooAbsPdf*) ws_.pdf("pdfDecayTime"))->fitTo((RooDataSet&) *ws_.data("data"), fittingArgs);
    RooFitResult*                   fitResult = ((RooAbsPdf*) ws_.pdf("pdfDecayTime"))->fitTo(*tempData, fittingArgs);

    if (fitResult){
        doofit::fitter::easyfit::FitResultPrinter printer(*fitResult);
        printer.Print();
        fitResult->correlationMatrix().Print();
    }
    return *fitResult;
}

void CPFitter::timePlot(){
    // doofit plot
    doofit::plotting::PlotConfig*   cfg_plot = new doofit::plotting::PlotConfig("cfg_plot");
                                    cfg_plot->InitializeOptions();
    if (useMC_)                     cfg_plot->set_label_text("LHCb simulation");
    if (useMC_)                     cfg_plot->set_label_text("LHCb inofficial");
                                    cfg_plot->set_plot_directory(config_.getString("plotDir"));

    // plot PDF and directly specify components
    RooArgSet*                      plotset = new RooArgSet();
                                    plotset->add((RooCategory&) obs_["catChargeConf"]);
    if (useOSTagger_)               plotset->add((RooRealVar&) obs_["obsEtaOS"]);
    if (useOSTagger_)               plotset->add((RooCategory&) obs_["obsTagOS"]);
    if (useSSTagger_)               plotset->add((RooRealVar&) obs_["obsEtaSS"]);
    if (useSSTagger_)               plotset->add((RooCategory&) obs_["obsTagSS"]);
    if (useTrueTags_)               plotset->add((RooRealVar&) obs_["obsEtaTRUE"]);
    if (useTrueTags_)               plotset->add((RooCategory&) obs_["obsTagTRUE"]);

    doofit::plotting::Plot*         myplot1 = new doofit::plotting::Plot(*cfg_plot, (RooRealVar&) obs_["obsTime"], (RooDataSet&) *ws_.data("data"), RooArgList((RooAbsPdf&) *ws_.pdf("pdfDecayTime")), "B02DstD");
                                    myplot1->set_scaletype_y(doofit::plotting::kBoth);
                                    myplot1->AddPlotArg(RooFit::ProjWData(*plotset, (RooDataSet&) *ws_.data("data")));
                                    myplot1->AddPlotArg(RooFit::NumCPU(30));
                                    myplot1->AddPlotArg(RooFit::Normalization(1.0, RooAbsReal::NumEvent));
                                    myplot1->PlotIt();
                                    myplot1->PlotIt();
}

// ========================== private ========================== 
void CPFitter::readData_(){
    RooDataSet*                     data;
    if (useMC_)                     data = new RooDataSet("data", "data", obs_);
    else                            data = new RooDataSet("data", "data", obs_, "SigWeight");
    for (auto i = paths_.begin(); i != paths_.end(); ++i)    {
        doocore::io::EasyTuple*     etuple = new doocore::io::EasyTuple(*i, "DecayTree", obs_);
        RooDataSet*                 tempData;
                                    // tempData = (RooDataSet*) &etuple->ConvertToDataSet();
        if (useMC_)                 tempData = (RooDataSet*) &etuple->ConvertToDataSet();
        else                        tempData = (RooDataSet*) &etuple->ConvertToDataSet(RooFit::WeightVar("SigWeight"));
                                    data->append(*tempData);
    }
    ws_.import(*data);
}

void CPFitter::saveWS(){
    ws_.SaveAs(config_.getString("pathWS").c_str());
}

void CPFitter::readWS(){
    TFile *f = new TFile(config_.getString("pathWS").c_str());
    ws_ = (RooWorkspace&) *f->Get("workspace");
    f->Close();
}

void CPFitter::buildObservableSet_(){

    RooRealVar*                     obsMass = new RooRealVar("obsMass", "obsMass", 5000., 6000.);
    RooRealVar*                     SigWeight = new RooRealVar("SigWeight", "SigWeight", -10., 10.);

    RooRealVar*                     obsTime = new RooRealVar("obsTime", "t_{#kern[-0.3]{B}^{#kern[-0.3]{0}}}", 0.3, 10.3, "ps");
    RooRealVar*                     obsTimeErr = new RooRealVar("obsTimeErr", "#sigma_{t}", 0., 10., "ps");

    RooRealVar*                     obsEtaOS = new RooRealVar("obsEtaOS", "obsEtaOS", 0., 0.5);
    RooCategory*                    obsTagOS = new RooCategory("obsTagOS", "obsTagOS");
                                    obsTagOS->defineType("B",+1);
                                    obsTagOS->defineType("Bbar",-1);
                                    obsTagOS->defineType("untagged",0);
    RooRealVar*                     obsEtaSS = new RooRealVar("obsEtaSS", "obsEtaSS", 0., 0.5);
    RooCategory*                    obsTagSS = new RooCategory("obsTagSS", "obsTagSS");
                                    obsTagSS->defineType("B",+1);
                                    obsTagSS->defineType("Bbar",-1);
                                    obsTagSS->defineType("untagged",0);
    RooRealVar*                     obsEtaTRUE = new RooRealVar("obsEtaTRUE", "obsEtaTRUE", 0., 0.5);
    RooCategory*                    obsTagTRUE = new RooCategory("obsTagTRUE", "obsTagTRUE");
                                    obsTagTRUE->defineType("B",+1);
                                    obsTagTRUE->defineType("Bbar",-1);
                                    obsTagTRUE->defineType("untagged",0);

    RooCategory*                    catChargeConf = new RooCategory("catChargeConf", "catChargeConf");
                                    catChargeConf->defineType("Dst+D-",-1);
                                    catChargeConf->defineType("Dst-D+",+1);

    RooCategory*                    catFinalState = new RooCategory("catFinalState", "catFinalState");
                                    catFinalState->defineType("D02K3pi/D2Kpipi",1);
                                    catFinalState->defineType("D02K3pi/D2KKpi",2);
                                    catFinalState->defineType("D02Kpi/D2Kpipi",3);
                                    catFinalState->defineType("D02Kpi/D2KKpi",4);
                                    catFinalState->defineType("D02KK/D2Kpipi",5);

    RooArgSet*                      observables = new RooArgSet("observableset");
    if (!useMC_ && !doMassFit_)     observables->add(*SigWeight);
    if (doMassFit_)                 observables->add(*obsMass);

                                    observables->add(*obsTime);
    if (usePerEventRes_)            observables->add(*obsTimeErr);
                                    observables->add(*catChargeConf);
                                    observables->add(*catFinalState);
    if (useOSTagger_)               observables->add(*obsEtaOS);
    if (useOSTagger_)               observables->add(*obsTagOS);
    if (useSSTagger_)               observables->add(*obsEtaSS);
    if (useSSTagger_)               observables->add(*obsTagSS);
    if (useTrueTags_)               observables->add(*obsEtaTRUE);
    if (useTrueTags_)               observables->add(*obsTagTRUE);

    ws_.import(*observables);
    obs_.add(*observables);
}

void CPFitter::buildFitPDF_(){
    // parameters
    RooRealVar*                     parTau = new RooRealVar("parTau", "parTau", 1.52);
    RooRealVar*                     parDM = new RooRealVar("parDM", "parDM", 0.5065);
    RooRealVar*                     parDGamma = new RooRealVar("parDGamma", "parDGamma", 0.0);

    RooRealVar*                     parAdet = new RooRealVar("parAdet", "parAdet", 0.0);
    RooRealVar*                     parAprod = new RooRealVar("parAprod", "parAprod", 0.0);

    RooRealVar*                     parCh = new RooRealVar("parCh", "parCh", 0.0);
    RooRealVar*                     parChbar = new RooRealVar("parChbar", "parChbar", 0.0);
    RooRealVar*                     parSh = new RooRealVar("parSh", "parSh", 0.0);
    RooRealVar*                     parShbar = new RooRealVar("parShbar", "parShbar", 0.0);

    RooRealVar*                     parCmean = new RooRealVar("parCmean", "parCmean", 0.0);
    RooRealVar*                     parCdelta = new RooRealVar("parCdelta", "parCdelta", 0.0);
    RooRealVar*                     parSmean = new RooRealVar("parSmean", "parSmean", 0.0);
    RooRealVar*                     parSdelta = new RooRealVar("parSdelta", "parSdelta", 0.0);

    RooUnblindUniform*              parCmeanBlind = new RooUnblindUniform("parCmeanBlind", "parCmeanBlind", "CmeanB02DstD5fb", 1.0, *parCmean);
    RooUnblindUniform*              parCdeltaBlind = new RooUnblindUniform("parCdeltaBlind", "parCdeltaBlind", "CdeltaB02DstD5fb", 1.0, *parCdelta);
    RooUnblindUniform*              parSmeanBlind = new RooUnblindUniform("parSmeanBlind", "parSmeanBlind", "SmeanB02DstD5fb", 1.0, *parSmean);
    RooUnblindUniform*              parSdeltaBlind = new RooUnblindUniform("parSdeltaBlind", "parSdeltaBlind", "SdeltaB02DstD5fb", 1.0, *parSdelta);

    RooFormulaVar*                  parS = new RooFormulaVar("parS", "parS", "@0+@1", RooArgList(*parSmeanBlind, *parSdeltaBlind));
    RooFormulaVar*                  parSbar = new RooFormulaVar("parSbar", "parSbar", "@0-@1", RooArgList(*parSmeanBlind, *parSdeltaBlind));
    RooFormulaVar*                  parC = new RooFormulaVar("parC", "parC", "@0+@1", RooArgList(*parCmeanBlind, *parCdeltaBlind));
    RooFormulaVar*                  parCbar = new RooFormulaVar("parCbar", "parCbar", "@0-@1", RooArgList(*parCmeanBlind, *parCdeltaBlind));

    RooCategory*                    obsTag;
    RooRealVar*                     obsEta;
    RooRealVar                      *parTagEff, *parTagDEff, *parTagEffSS, *parTagDEffSS;
    DecRateCoeff_Bd                 *parCosh, *parSinh, *parCos, *parSin;

    // decay rate coefficients

    if (useOSTagger_ && useSSTagger_){
                                    parTagEff       = new RooRealVar("parTagEffOS",  "parTagEffOS",  0.0);
                                    parTagDEff      = new RooRealVar("parTagDEffOS", "parTagDEffOS", 0.0);
                                    parTagEffSS     = new RooRealVar("parTagEffSS",  "parTagEffSS",  0.0);
                                    parTagDEffSS    = new RooRealVar("parTagDEffSS", "parTagDEffSS", 0.0);

                                    parCosh = new DecRateCoeff_Bd("parCosh", "parCosh", DecRateCoeff_Bd::kCosh, (RooCategory&) obs_["catChargeConf"], *parCh, *parChbar, (RooCategory&) obs_["obsTagOS"],(RooRealVar&) obs_["obsEtaOS"],
                                        (RooRealVar&) obs_["obsEtaOS"], *parTagEff, *parTagDEff, (RooCategory&) obs_["obsTagSS"], (RooRealVar&) obs_["obsEtaSS"], (RooRealVar&) obs_["obsEtaSS"], *parTagEffSS, *parTagDEffSS, *parAprod, *parAdet);
                                    parSinh = new DecRateCoeff_Bd("parSinh", "parSinh", DecRateCoeff_Bd::kSinh, (RooCategory&) obs_["catChargeConf"], *parSh, *parShbar, (RooCategory&) obs_["obsTagOS"],(RooRealVar&) obs_["obsEtaOS"],
                                        (RooRealVar&) obs_["obsEtaOS"], *parTagEff, *parTagDEff, (RooCategory&) obs_["obsTagSS"], (RooRealVar&) obs_["obsEtaSS"], (RooRealVar&) obs_["obsEtaSS"], *parTagEffSS, *parTagDEffSS, *parAprod, *parAdet);
                                    parCos  = new DecRateCoeff_Bd("parCos",  "parCos",  DecRateCoeff_Bd::kCos,  (RooCategory&) obs_["catChargeConf"], *parC,  *parCbar,  (RooCategory&) obs_["obsTagOS"],(RooRealVar&) obs_["obsEtaOS"],
                                        (RooRealVar&) obs_["obsEtaOS"], *parTagEff, *parTagDEff, (RooCategory&) obs_["obsTagSS"], (RooRealVar&) obs_["obsEtaSS"], (RooRealVar&) obs_["obsEtaSS"], *parTagEffSS, *parTagDEffSS, *parAprod, *parAdet);
                                    parSin  = new DecRateCoeff_Bd("parSin",  "parSin",  DecRateCoeff_Bd::kSin,  (RooCategory&) obs_["catChargeConf"], *parS,  *parSbar,  (RooCategory&) obs_["obsTagOS"],(RooRealVar&) obs_["obsEtaOS"],
                                        (RooRealVar&) obs_["obsEtaOS"], *parTagEff, *parTagDEff, (RooCategory&) obs_["obsTagSS"], (RooRealVar&) obs_["obsEtaSS"], (RooRealVar&) obs_["obsEtaSS"], *parTagEffSS, *parTagDEffSS, *parAprod, *parAdet);
    }
    else{
                                    parTagEff = new RooRealVar("parTagEff", "parTagEff", 0.0);
                                    parTagDEff = new RooRealVar("parTagDEff", "parTagDEff", 0.0);

        if (useTrueTags_){
                                    obsTag = (RooCategory*) &obs_["obsTagTRUE"];
                                    obsEta = (RooRealVar*) &obs_["obsEtaTRUE"];
        }
        if (useOSTagger_){
                                    obsTag = (RooCategory*) &obs_["obsTagOS"];
                                    obsEta = (RooRealVar*) &obs_["obsEtaOS"];
        }
        if (useSSTagger_){
                                    obsTag = (RooCategory*) &obs_["obsTagSS"];
                                    obsEta = (RooRealVar*) &obs_["obsEtaSS"];
        }
                                    parCosh = new DecRateCoeff_Bd("parCosh", "parCosh", DecRateCoeff_Bd::kCosh, (RooCategory&) obs_["catChargeConf"], *parCh, *parChbar, *obsTag, *obsEta, *obsEta, *parTagEff, *parTagDEff, *parAprod, *parAdet);
                                    parSinh = new DecRateCoeff_Bd("parSinh", "parSinh", DecRateCoeff_Bd::kSinh, (RooCategory&) obs_["catChargeConf"], *parSh, *parShbar, *obsTag, *obsEta, *obsEta, *parTagEff, *parTagDEff, *parAprod, *parAdet);
                                    parCos = new DecRateCoeff_Bd("parCos",   "parCos",  DecRateCoeff_Bd::kCos,  (RooCategory&) obs_["catChargeConf"], *parC,  *parCbar,  *obsTag, *obsEta, *obsEta, *parTagEff, *parTagDEff, *parAprod, *parAdet);
                                    parSin = new DecRateCoeff_Bd("parSin",   "parSin",  DecRateCoeff_Bd::kSin,  (RooCategory&) obs_["catChargeConf"], *parS,  *parSbar,  *obsTag, *obsEta, *obsEta, *parTagEff, *parTagDEff, *parAprod, *parAdet);
    }

    // resolution
    RooRealVar*                     parResMean = new RooRealVar("parResMean", "parResMean", 0);
    RooRealVar*                     parResSigma1 = new RooRealVar("parResSigma1", "parResSigma1", 0.1);
    RooRealVar*                     parResSigma2 = new RooRealVar("parResSigma2", "parResSigma2", 0.1);
    RooRealVar*                     parResSigma3 = new RooRealVar("parResSigma3", "parResSigma3", 0.1);
    RooRealVar*                     parResFrac1 = new RooRealVar("parResFrac1", "parResFrac1", 0.5);
    RooRealVar*                     parResFrac2 = new RooRealVar("parResFrac2", "parResFrac2", 0.5);

    // acceptance
    RooArgList*                     splineList = new RooArgList("splineList");
    RooRealVar*                     parAccSpline;
    for (unsigned int i=1; i <= (knots_.size() + 2); i++){
        std::string                 binname = "parAccSpline" + std::to_string(i);
                                    parAccSpline = new RooRealVar(binname.c_str(),binname.c_str(),1,0,4);
                                    splineList->add(*parAccSpline);
    }

    // pdfs
    RooCubicSplineFun*              pdfAccSpline = new RooCubicSplineFun("pdfAccSpline", "pdfAccSpline", (RooRealVar&) obs_["obsTime"], knots_, *splineList);
    RooGaussEfficiencyModel*        pdfResGauss1 = new RooGaussEfficiencyModel("pdfResGauss1", "pdfResGauss1", (RooRealVar&) obs_["obsTime"], (RooAbsGaussModelEfficiency&) (*pdfAccSpline), *parResMean, *parResSigma1);
    RooGaussEfficiencyModel*        pdfResGauss2 = new RooGaussEfficiencyModel("pdfResGauss2", "pdfResGauss2", (RooRealVar&) obs_["obsTime"], (RooAbsGaussModelEfficiency&) (*pdfAccSpline), *parResMean, *parResSigma2);
    RooGaussEfficiencyModel*        pdfResGauss3 = new RooGaussEfficiencyModel("pdfResGauss3", "pdfResGauss3", (RooRealVar&) obs_["obsTime"], (RooAbsGaussModelEfficiency&) (*pdfAccSpline), *parResMean, *parResSigma3);

    RooEffResAddModel*              pdfResGauss = new RooEffResAddModel("pdfResGauss", "pdfResGauss", RooArgList(*pdfResGauss1, *pdfResGauss2, *pdfResGauss3), RooArgList(*parResFrac1, *parResFrac2));
    RooBDecay*                      pdfDecayTime = new RooBDecay("pdfDecayTime", "pdfDecayTime", (RooRealVar&) obs_["obsTime"], *parTau, *parDGamma, *parCosh, *parSinh, *parCos, *parSin, *parDM, *pdfResGauss, RooBDecay::SingleSided);

    ws_.import(*pdfDecayTime);
}

std::vector<int> convertVectorStringToInt(std::vector<std::string> stringVector){
    std::vector<int> intVector;
    for (auto i = stringVector.begin(); i != stringVector.end(); ++i)    {
        intVector.push_back(atoi((*i).c_str()));
    }
    return intVector;
}

std::vector<double> convertVectorStringToDouble(std::vector<std::string> stringVector){
    std::vector<double> doubleVector;
    for (auto i = stringVector.begin(); i != stringVector.end(); ++i)    {
        doubleVector.push_back(std::stod((*i).c_str()));
    }
    return doubleVector;
}

std::pair<std::vector<std::string>, std::vector<std::string>> convertPairVectorToVectorPair(std::vector<std::pair<std::string, std::string>> pairVector){
    std::pair<std::vector<std::string>, std::vector<std::string>> vectorPair;
    for (auto i = pairVector.begin(); i != pairVector.end(); ++i){
        vectorPair.first.push_back((*i).first);
        vectorPair.second.push_back((*i).second);
    }
    return vectorPair;
}
