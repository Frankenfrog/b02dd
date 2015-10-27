#include <iostream>
#include <sstream>
#include <algorithm>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TF1.h"

#include "RooCmdArg.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooCategory.h"
#include "RooArgSet.h"

#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/config/EasyConfig.h"
#include "doocore/io/Progress.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using namespace std;
using namespace RooFit;
using namespace doocore::io;

void CreateScatterPlot(RooDataSet& data, TString hist_name, int nbins, TString x_obs_name, TString y_obs_name, TString x_title, TString y_title, double x_min, double x_max, double y_min, double y_max);
void CreateProfileHistogram(RooDataSet& data, TString profile_name, int nbins, TString x_obs_name, TString y_obs_name, TString x_title, TString y_title, double x_min, double x_max, double y_min, double y_max, bool linear_fit = false, double x_min_fit = 0.25, double x_max_fit = 10.25);

int main(int argc, const char * argv[]){
  if (argc != 2) {
    std::cout << "Usage:   " << argv[0] << " 'config_file_name'" << std::endl;
    return 0;
  }
  doocore::config::EasyConfig config(argv[1]);

  RooRealVar        obsEtaOS("obsEtaOSwCharm","#eta_{OS}",0,0.5);
  RooRealVar        obsEtaSS("obsEtaSS","#eta_{SS}",0,0.5);
  RooRealVar        obsEtaSSPion("obsEtaSSPion","#eta_{SS#pi}",0,0.5);
  RooRealVar        obsEtaSSPionBDT("obsEtaSSPionBDT","#eta_{SS#pi}",0,0.5);
  RooRealVar        obsEtaSSProton("obsEtaSSProton","#eta_{SS#p}",0,0.5);
  RooRealVar        SigWeight("SigWeight","Signal weight",-10,10);
  RooRealVar        obsMass("obsMassDDPVConst","#it{m_{D^{+} D^{-}}}",5150,5600,"MeV/c^{2}");
  RooRealVar        obsTime("obsTime","#it{t}",0.25,10.25,"ps");

  RooCategory       catBkg("catBkg","catBkg");
  catBkg.defineType("signal",0);
  
  RooArgSet         observables(obsTime,obsMass,"observables");
  observables.add(RooArgSet(obsEtaOS,obsEtaSS,obsEtaSSPion,obsEtaSSPionBDT,obsEtaSSProton));
  if (config.getBool("MC")) observables.add(catBkg);
  else observables.add(SigWeight);
  EasyTuple         sweighted_tuple(config.getString("tuple"),"B02DD",observables);
  sweighted_tuple.set_cut_variable_range(VariableRangeCutting::kCutInclusive);
  RooDataSet&       data = sweighted_tuple.ConvertToDataSet();
  data.Print();
  
  RooDataSet*       signaldata_BS;
  if (config.getBool("MC")) signaldata_BS = new RooDataSet("signaldata_BS","signaldata_BS",observables,Import(data),Cut("obsEtaOSwCharm!=0.5&&obsEtaSS!=0.5"));
  else signaldata_BS = new RooDataSet("signaldata_BS","signaldata_BS",observables,Import(data),Cut("obsEtaOSwCharm!=0.5&&obsEtaSS!=0.5"),WeightVar("SigWeight"));
  signaldata_BS->Print();
  RooDataSet*       signaldata_allOS;
  if (config.getBool("MC")) signaldata_allOS = new RooDataSet("signaldata_allOS","signaldata_allOS",observables,Import(data),Cut("obsEtaOSwCharm!=0.5"));
  else signaldata_allOS = new RooDataSet("signaldata_allOS","signaldata_allOS",observables,Import(data),Cut("obsEtaOSwCharm!=0.5"),WeightVar("SigWeight"));
  RooDataSet*       signaldata_allSS;
  if (config.getBool("MC")) signaldata_allSS = new RooDataSet("signaldata_allSS","signaldata_allSS",observables,Import(data),Cut("obsEtaSS!=0.5"));
  else signaldata_allSS = new RooDataSet("signaldata_allSS","signaldata_allSS",observables,Import(data),Cut("obsEtaSS!=0.5"),WeightVar("SigWeight"));
  RooDataSet*       signaldata_tagged;
  if (config.getBool("MC")) signaldata_tagged = new RooDataSet("signaldata_tagged","signaldata_tagged",observables,Import(data),Cut("obsEtaSS!=0.5||obsEtaOSwCharm!=0.5"));
  else signaldata_tagged = new RooDataSet("signaldata_tagged","signaldata_tagged",observables,Import(data),Cut("obsEtaSS!=0.5||obsEtaOSwCharm!=0.5"),WeightVar("SigWeight"));
  signaldata_tagged->Print();
  RooDataSet*       signaldata_SSPion;
  if (config.getBool("MC")) signaldata_SSPion = new RooDataSet("signaldata_SSPion","signaldata_SSPion",observables,Import(data),Cut("obsEtaSSPion!=0.5"));
  else signaldata_SSPion = new RooDataSet("signaldata_SSPion","signaldata_SSPion",observables,Import(data),Cut("obsEtaSSPion!=0.5"),WeightVar("SigWeight"));
  RooDataSet*       signaldata_SSPionBDT;
  if (config.getBool("MC")) signaldata_SSPionBDT = new RooDataSet("signaldata_SSPionBDT","signaldata_SSPionBDT",observables,Import(data),Cut("obsEtaSSPionBDT!=0.5"));
  else signaldata_SSPionBDT = new RooDataSet("signaldata_SSPionBDT","signaldata_SSPionBDT",observables,Import(data),Cut("obsEtaSSPionBDT!=0.5"),WeightVar("SigWeight"));
  RooDataSet*       signaldata_SSProton;
  if (config.getBool("MC")) signaldata_SSProton = new RooDataSet("signaldata_SSProton","signaldata_SSProton",observables,Import(data),Cut("obsEtaSSProton!=0.5"));
  else signaldata_SSProton = new RooDataSet("signaldata_SSProton","signaldata_SSProton",observables,Import(data),Cut("obsEtaSSProton!=0.5"),WeightVar("SigWeight"));

  RooDataSet  bootstrapped_data("bootstrapped_data","bootstrapped_data",observables,Import(data),Cut("obsEtaSS!=0.5||obsEtaOSwCharm!=0.5"));
  RooDataSet* data_temp;
  RooDataSet* data_bootstrapped;
  TRandom3 random(0);
  int n_bootstrapped_toys = 10000;

  if (config.getBool("Correlation_OS_SS")) {
    std::vector<double> correlation;
    Progress p("Generate bootstrapped toys for correlation studies", n_bootstrapped_toys);
    for (int i = 0; i < n_bootstrapped_toys; ++i) {
      data_temp = new RooDataSet("data_temp","data_temp",RooArgSet(observables));
      for (int j = 0; j < bootstrapped_data.numEntries(); ++j) {
        bootstrapped_data.get(random.Rndm()*bootstrapped_data.numEntries());
        data_temp->add(*(bootstrapped_data.get()));
      }
      data_bootstrapped = new RooDataSet("data_bootstrapped","data_bootstrapped",data_temp,RooArgSet(obsEtaOS,obsEtaSS,SigWeight),"","SigWeight");
      correlation += data_bootstrapped->correlation(obsEtaOS,obsEtaSS);
      delete data_temp;
      delete data_bootstrapped;
      ++p;
    }
    p.Finish();
  
    sort(correlation.begin(), correlation.end());
    cout  <<  "Correlation between OS mistag and SS mistag is " <<  signaldata_tagged->correlation(obsEtaOS,obsEtaSS)  <<  endl;
    cout  <<  "95% confidence interval of correlation between OS and SS mistag: (" <<  correlation.at(0.025*n_bootstrapped_toys) <<  ", "  <<  correlation.at(0.975*n_bootstrapped_toys) <<  ")" <<  endl;
  }

  if (config.getBool("Correlation_OS_time")) {
    RooDataSet  OS_data("OS_data","OS_data",observables,Import(data),Cut("obsEtaOSwCharm!=0.5"));
    std::vector<double> correlation_OS_time;
  
    Progress p_OS_time("Generate bootstrapped toys for correlation studies between OS mistag and decay time", n_bootstrapped_toys);
    for (int i = 0; i < n_bootstrapped_toys; ++i) {
      data_temp = new RooDataSet("data_temp","data_temp",RooArgSet(observables));
      for (int j = 0; j < OS_data.numEntries(); ++j) {
        OS_data.get(random.Rndm()*OS_data.numEntries());
        data_temp->add(*(OS_data.get()));
      }
      data_bootstrapped = new RooDataSet("data_bootstrapped","data_bootstrapped",data_temp,RooArgSet(obsEtaOS,obsTime,SigWeight),"","SigWeight");
      correlation_OS_time += data_bootstrapped->correlation(obsEtaOS,obsTime);
      delete data_temp;
      delete data_bootstrapped;
      ++p_OS_time;
    }
    p_OS_time.Finish();
  
    sort(correlation_OS_time.begin(), correlation_OS_time.end());
    cout  <<  "Correlation between OS mistag and decay time is " <<  signaldata_allOS->correlation(obsEtaOS,obsTime)  <<  endl;
    cout  <<  "95% confidence interval of correlation between OS and decay time: (" <<  correlation_OS_time.at(0.025*n_bootstrapped_toys) <<  ", "  <<  correlation_OS_time.at(0.975*n_bootstrapped_toys) <<  ")" <<  endl;
  }

  if (config.getBool("Correlation_SS_time")) {
    RooDataSet  SS_data("SS_data","SS_data",observables,Import(data),Cut("obsEtaSS!=0.5"));
    std::vector<double> correlation_SS_time;
  
    Progress p_SS_time("Generate bootstrapped toys for correlation studies between SS mistag and decay time", n_bootstrapped_toys);
    for (int i = 0; i < n_bootstrapped_toys; ++i) {
      data_temp = new RooDataSet("data_temp","data_temp",RooArgSet(observables));
      for (int j = 0; j < SS_data.numEntries(); ++j) {
        SS_data.get(random.Rndm()*SS_data.numEntries());
        data_temp->add(*(SS_data.get()));
      }
      data_bootstrapped = new RooDataSet("data_bootstrapped","data_bootstrapped",data_temp,RooArgSet(obsTime,obsEtaSS,SigWeight),"","SigWeight");
      correlation_SS_time += data_bootstrapped->correlation(obsEtaSS,obsTime);
      delete data_temp;
      delete data_bootstrapped;
      ++p_SS_time;
    }
    p_SS_time.Finish();
  
    sort(correlation_SS_time.begin(), correlation_SS_time.end());
    cout  <<  "Correlation between SS mistag and decay time is " <<  signaldata_allSS->correlation(obsEtaSS,obsTime)  <<  endl;
    cout  <<  "95% confidence interval of correlation between SS and decay time: (" <<  correlation_SS_time.at(0.025*n_bootstrapped_toys) <<  ", "  <<  correlation_SS_time.at(0.975*n_bootstrapped_toys) <<  ")" <<  endl;  
  }

  if (config.getBool("Correlation_mass_time")) {
    std::vector<double> correlation_mass_time;
  
    Progress p_mass_time("Generate bootstrapped toys for correlation studies between invariant mass and decay time", n_bootstrapped_toys);
    for (int i = 0; i < n_bootstrapped_toys; ++i) {
      data_temp = new RooDataSet("data_temp","data_temp",RooArgSet(observables));
      for (int j = 0; j < data.numEntries(); ++j) {
        data.get(random.Rndm()*data.numEntries());
        data_temp->add(*(data.get()));
      }
      correlation_mass_time += data_temp->correlation(obsMass,obsTime);
      delete data_temp;
      ++p_mass_time;
    }
    p_mass_time.Finish();
  
    sort(correlation_mass_time.begin(), correlation_mass_time.end());
    cout  <<  "Correlation between invariant mass and decay time is " <<  data.correlation(obsMass,obsTime)  <<  endl;
    cout  <<  "95% confidence interval of correlation between invariant mass and decay time: (" <<  correlation_mass_time.at(0.025*n_bootstrapped_toys) <<  ", "  <<  correlation_mass_time.at(0.975*n_bootstrapped_toys) <<  ")" <<  endl;  
  }

  // scatter plots
  CreateScatterPlot(*signaldata_BS, "Correlation_OS_SS", 40, "obsEtaOSwCharm", "obsEtaSS", "#it{#eta}_{OS}", "#it{#eta}_{SS}", 0.1, 0.5, 0.1, 0.5);

  // profile histograms
  CreateProfileHistogram(*signaldata_BS, "Profile_OS_SS", 40, "obsEtaOSwCharm", "obsEtaSS", "#it{#eta}_{OS}", "#it{#eta}_{SS}", 0, 0.5, 0, 0.6);
  CreateProfileHistogram(*signaldata_BS, "Profile_SS_OS", 40, "obsEtaSS", "obsEtaOSwCharm", "#it{#eta}_{SS}", "#it{#eta}_{OS}", 0, 0.5, 0, 0.6);
  CreateProfileHistogram(*signaldata_allOS, "Profile_DecayTime_OS", 100, "obsTime", "obsEtaOSwCharm", "#it{t}", "#it{#eta}_{OS}", 0.25, 10.25, 0, 0.6);
  CreateProfileHistogram(*signaldata_allSS, "Profile_DecayTime_SS", 100, "obsTime", "obsEtaSS", "#it{t}", "#it{#eta}_{SS}", 0.25, 10.25, 0, 0.6, true, 2.25, 8.25);
  CreateProfileHistogram(*signaldata_SSPion, "Profile_DecayTime_SSPion", 100, "obsTime", "obsEtaSSPion", "#it{t}", "#it{#eta}_{SS#pion}", 0.25, 10.25, 0, 0.6, true, 2.25, 8.25);
  CreateProfileHistogram(*signaldata_SSPionBDT, "Profile_DecayTime_SSPionBDT", 20, "obsTime", "obsEtaSSPionBDT", "#it{t}", "#it{#eta}_{SS#pion}", 0.25, 10.25, 0.3, 0.5, true, 2.25, 8.25);
  CreateProfileHistogram(*signaldata_SSProton, "Profile_DecayTime_SSProton", 100, "obsTime", "obsEtaSSProton", "#it{t}", "#it{#eta}_{SS#p}", 0.25, 10.25, 0, 0.6, true, 2.25, 8.25);

  return 0;
}

void CreateScatterPlot(RooDataSet& data, TString hist_name, int nbins, TString x_obs_name, TString y_obs_name, TString x_title, TString y_title, double x_min, double x_max, double y_min, double y_max){
  std::vector<double> x_values;
  std::vector<double> y_values;
  std::vector<double> weights;
  for (int i = 0; i < data.numEntries(); ++i){
    data.get(i);
    x_values += data.get()->getRealValue(x_obs_name);
    y_values += data.get()->getRealValue(y_obs_name);
    weights  += data.weight(); 
  }
  TCanvas canvas("c", "c", 800, 600);
  TH2D* hist = new TH2D(hist_name, hist_name, 40, x_min, x_max, 40, y_min, y_max);
  hist->SetNameTitle(hist_name, "");
  hist->SetStats(false);
  hist->SetXTitle(x_title);
  hist->SetYTitle(y_title);
  hist->SetMinimum(0);
  hist->FillN(x_values.size(), &x_values[0], &y_values[0], &weights[0]);
  hist->Draw("colz");
  canvas.SaveAs("/home/fmeier/storage03/b02dd/"+hist_name+".pdf");  
  delete hist;
}

void CreateProfileHistogram(RooDataSet& data, TString profile_name, int nbins, TString x_obs_name, TString y_obs_name, TString x_title, TString y_title, double x_min, double x_max, double y_min, double y_max, bool linear_fit, double x_min_fit, double x_max_fit){
  std::vector<double> x_values;
  std::vector<double> y_values;
  std::vector<double> weights;
  for (int i = 0; i < data.numEntries(); ++i){
    data.get(i);
    x_values += data.get()->getRealValue(x_obs_name);
    y_values += data.get()->getRealValue(y_obs_name);
    weights  += data.weight(); 
  }
  TCanvas canvas("c", "c", 800, 600);
  TProfile* profile = new TProfile(profile_name, profile_name, nbins, x_min, x_max);
  profile->SetNameTitle(profile_name, "");
  profile->SetStats(false);
  profile->SetXTitle(x_title);
  profile->SetYTitle(y_title);
  profile->SetMinimum(y_min);
  profile->SetMaximum(y_max);
  profile->FillN(x_values.size(), &x_values[0], &y_values[0], &weights[0]);
  if (linear_fit) {
    TF1* fit_function = new TF1("fit_function","[0]+[1]*x",x_min_fit,x_max_fit);
    profile->Fit(fit_function, "R");
  }
  profile->Draw();
  canvas.SaveAs("/home/fmeier/storage03/b02dd/"+profile_name+".pdf");  
  delete profile;
}
