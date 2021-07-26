/******************************************/
// B02DDPIDReweightingGrimReaper.cpp
//
// Standalone GrimReaper that adds a lot of
// common variables to trees.
//
// Author: Frank Meier
// Date: 2014-11-07
/******************************************/

// from STL
#include <tuple>
#include <list>

// from ROOT
#include "TRandom3.h"
#include "TCut.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/config/Summary.h"

// from DooSelection
#include "dooselection/reducer/Reducer.h"
#include "dooselection/reducer/ReducerLeaf.h"

using namespace dooselection::reducer;
using namespace doocore::io;

// forward declarations
// typedef tuple: head, daughters, stable particles, isMC, isFlat
typedef std::tuple<std::string, std::list<std::string>, std::list<std::string>, bool, bool> cfg_tuple;
cfg_tuple Configure(Reducer* _rdcr, std::string& _channel);
void AuxiliaryLeaves(Reducer* _rdcr, cfg_tuple& cfg);

class B02DDPIDReweightingReducer : public Reducer {

  Int_t* DDFinalState;

  Double_t* varPiOneminus_ProbNNk_value;
  Double_t* varPiOneminus_ProbNNpi_value;
  Double_t* varPiOneplus_ProbNNk_value;
  Double_t* varPiOneplus_ProbNNpi_value;
  Double_t* varPiTwominus_ProbNNk_value;
  Double_t* varPiTwominus_ProbNNpi_value;
  Double_t* varPiTwoplus_ProbNNk_value;
  Double_t* varPiTwoplus_ProbNNpi_value;

  ReducerLeaf<Double_t>* varPiOneminus_SumProbNNkpi;
  ReducerLeaf<Double_t>* varPiOneminus_PID;
  ReducerLeaf<Double_t>* varPiOneplus_SumProbNNkpi;
  ReducerLeaf<Double_t>* varPiOneplus_PID;
  ReducerLeaf<Double_t>* varPiTwominus_SumProbNNkpi;
  ReducerLeaf<Double_t>* varPiTwominus_PID;
  ReducerLeaf<Double_t>* varPiTwoplus_SumProbNNkpi;
  ReducerLeaf<Double_t>* varPiTwoplus_PID;

  Double_t* varPiOneminus_SumProbNNkpi_value;
  Double_t* varPiOneminus_PID_value;   
  Double_t* varPiOneplus_SumProbNNkpi_value;
  Double_t* varPiOneplus_PID_value;
  Double_t* varPiTwominus_SumProbNNkpi_value;
  Double_t* varPiTwominus_PID_value;
  Double_t* varPiTwoplus_SumProbNNkpi_value;
  Double_t* varPiTwoplus_PID_value;

  ReducerLeaf<Double_t>* varKaon_PID;
  ReducerLeaf<Double_t>* varPion_PID;
  ReducerLeaf<Double_t>* varPiHigh_PID;
  ReducerLeaf<Double_t>* varPiLow_PID;

  Double_t* varKaon_PID_value;
  Double_t* varPion_PID_value;
  Double_t* varPiHigh_PID_value;
  Double_t* varPiLow_PID_value;

  void CreateSpecialBranches() {

    DDFinalState     = (Int_t*)GetInterimLeafByName("catDDFinalState").branch_address();

    varPiOneminus_ProbNNk_value  = (Double_t*)GetInterimLeafByName("varPiOneminus_ProbNNk_rew").branch_address();
    varPiOneminus_ProbNNpi_value = (Double_t*)GetInterimLeafByName("varPiOneminus_ProbNNpi_rew").branch_address();
    varPiOneplus_ProbNNk_value   = (Double_t*)GetInterimLeafByName("varPiOneplus_ProbNNk_rew").branch_address();
    varPiOneplus_ProbNNpi_value  = (Double_t*)GetInterimLeafByName("varPiOneplus_ProbNNpi_rew").branch_address();
    varPiTwominus_ProbNNk_value  = (Double_t*)GetInterimLeafByName("varPiTwominus_ProbNNk_rew").branch_address();
    varPiTwominus_ProbNNpi_value = (Double_t*)GetInterimLeafByName("varPiTwominus_ProbNNpi_rew").branch_address();
    varPiTwoplus_ProbNNk_value   = (Double_t*)GetInterimLeafByName("varPiTwoplus_ProbNNk_rew").branch_address();
    varPiTwoplus_ProbNNpi_value  = (Double_t*)GetInterimLeafByName("varPiTwoplus_ProbNNpi_rew").branch_address();

    varPiOneminus_SumProbNNkpi = &(CreateDoubleLeaf("varPiOneminus_SumProbNNkpi_rew", -999999));
    varPiOneminus_PID = &(CreateDoubleLeaf("varPiOneminus_PID_rew", -999999));
    varPiOneplus_SumProbNNkpi = &(CreateDoubleLeaf("varPiOneplus_SumProbNNkpi_rew", -999999));
    varPiOneplus_PID = &(CreateDoubleLeaf("varPiOneplus_PID_rew", -999999));
    varPiTwominus_SumProbNNkpi = &(CreateDoubleLeaf("varPiTwominus_SumProbNNkpi_rew", -999999));
    varPiTwominus_PID = &(CreateDoubleLeaf("varPiTwominus_PID_rew", -999999));
    varPiTwoplus_SumProbNNkpi = &(CreateDoubleLeaf("varPiTwoplus_SumProbNNkpi_rew", -999999));
    varPiTwoplus_PID = &(CreateDoubleLeaf("varPiTwoplus_PID_rew", -999999));

    varKaon_PID = &(CreateDoubleLeaf("varKaon_PID_rew", -999999));
    varPion_PID = &(CreateDoubleLeaf("varPion_PID_rew", -999999));
    varPiHigh_PID = &(CreateDoubleLeaf("varPiHigh_PID_rew", -999999));
    varPiLow_PID = &(CreateDoubleLeaf("varPiLow_PID_rew", -999999));

    varPiOneminus_SumProbNNkpi_value = (Double_t*)varPiOneminus_SumProbNNkpi->branch_address();
    varPiOneminus_PID_value = (Double_t*)varPiOneminus_PID->branch_address();
    varPiOneplus_SumProbNNkpi_value = (Double_t*)varPiOneplus_SumProbNNkpi->branch_address();
    varPiOneplus_PID_value = (Double_t*)varPiOneplus_PID->branch_address();
    varPiTwominus_SumProbNNkpi_value = (Double_t*)varPiTwominus_SumProbNNkpi->branch_address();
    varPiTwominus_PID_value = (Double_t*)varPiTwominus_PID->branch_address();
    varPiTwoplus_SumProbNNkpi_value = (Double_t*)varPiTwoplus_SumProbNNkpi->branch_address();
    varPiTwoplus_PID_value = (Double_t*)varPiTwoplus_PID->branch_address();

    varKaon_PID_value = (Double_t*)varKaon_PID->branch_address();
    varPion_PID_value = (Double_t*)varPion_PID->branch_address();
    varPiHigh_PID_value = (Double_t*)varPiHigh_PID->branch_address();
    varPiLow_PID_value = (Double_t*)varPiLow_PID->branch_address();
  }

  void UpdateSpecialLeaves() {

    *varPiOneminus_SumProbNNkpi_value = *varPiOneminus_ProbNNk_value + *varPiOneminus_ProbNNpi_value;
    *varPiOneminus_PID_value = *varPiOneminus_ProbNNk_value / *varPiOneminus_SumProbNNkpi_value;
    *varPiOneplus_SumProbNNkpi_value = *varPiOneplus_ProbNNk_value + *varPiOneplus_ProbNNpi_value;
    *varPiOneplus_PID_value = *varPiOneplus_ProbNNk_value / *varPiOneplus_SumProbNNkpi_value;
    *varPiTwominus_SumProbNNkpi_value = *varPiTwominus_ProbNNk_value + *varPiTwominus_ProbNNpi_value;
    *varPiTwominus_PID_value = *varPiTwominus_ProbNNk_value / *varPiTwominus_SumProbNNkpi_value;
    *varPiTwoplus_SumProbNNkpi_value = *varPiTwoplus_ProbNNk_value + *varPiTwoplus_ProbNNpi_value;
    *varPiTwoplus_PID_value = *varPiTwoplus_ProbNNk_value / *varPiTwoplus_SumProbNNkpi_value;

    if (*DDFinalState == 13) {
      *varKaon_PID_value = *varPiOneminus_ProbNNk_value / (*varPiOneminus_ProbNNk_value + *varPiOneminus_ProbNNpi_value);
      *varPion_PID_value = *varPiTwominus_ProbNNk_value / (*varPiTwominus_ProbNNk_value + *varPiTwominus_ProbNNpi_value);
      *varPiHigh_PID_value = *varPiOneplus_PID_value;
      *varPiLow_PID_value = *varPiTwoplus_PID_value;
    }
    if (*DDFinalState == 14) {
      *varKaon_PID_value = *varPiTwominus_ProbNNk_value / (*varPiTwominus_ProbNNk_value + *varPiTwominus_ProbNNpi_value);
      *varPion_PID_value = *varPiOneminus_ProbNNk_value / (*varPiOneminus_ProbNNk_value + *varPiOneminus_ProbNNpi_value);
      *varPiHigh_PID_value = *varPiOneplus_PID_value;
      *varPiLow_PID_value = *varPiTwoplus_PID_value;
    }
    if (*DDFinalState == 31) {
      *varKaon_PID_value = *varPiOneplus_ProbNNk_value / (*varPiOneplus_ProbNNk_value + *varPiOneplus_ProbNNpi_value);
      *varPion_PID_value = *varPiTwoplus_ProbNNk_value / (*varPiTwoplus_ProbNNk_value + *varPiTwoplus_ProbNNpi_value);
      *varPiHigh_PID_value = *varPiOneminus_PID_value;
      *varPiLow_PID_value = *varPiTwominus_PID_value;
    }
    if (*DDFinalState == 41) {
      *varKaon_PID_value = *varPiTwoplus_ProbNNk_value / (*varPiTwoplus_ProbNNk_value + *varPiTwoplus_ProbNNpi_value);
      *varPion_PID_value = *varPiOneplus_ProbNNk_value / (*varPiOneplus_ProbNNk_value + *varPiOneplus_ProbNNpi_value);
      *varPiHigh_PID_value = *varPiOneminus_PID_value;
      *varPiLow_PID_value = *varPiTwominus_PID_value;
    }
  }
};

int main(int argc, char * argv[]){
  sinfo << "-info-  \t" << "B02DDPIDReweightingGrimReaper \t" << "Welcome!" << endmsg;
  std::string inputfile, inputtree, outputfile, outputtree, decay_channel;
  if (argc == 5){
    inputfile = argv[1];
    inputtree = argv[2];
    outputfile = argv[3];
    outputtree = argv[4];
    decay_channel = "B02DD";
  }
  else{
    serr << "-ERROR- \t" << "B02DDPIDReweightingGrimReaper \t" << "Parameters needed:" << endmsg;
    serr << "-ERROR- \t" << "B02DDPIDReweightingGrimReaper \t"<< "input_file_name input_tree_name output_file_name output_tree_name" << endmsg;
    return 1;
  }

  Reducer* reducer = new B02DDPIDReweightingReducer();
  doocore::config::Summary& summary = doocore::config::Summary::GetInstance();
  summary.AddSection("I/O");
  summary.Add("Input file", inputfile);
  summary.Add("Input tree", inputtree);
  summary.Add("Output file", outputfile);
  summary.Add("Output file", outputtree);

  // reducer part
  reducer->set_input_file_path(inputfile);
  reducer->set_input_tree_path(inputtree);
  reducer->set_output_file_path(outputfile);
  reducer->set_output_tree_path(outputtree);
  // reducer->set_num_events_process(1000);
  reducer->OverwriteExistingLeaves(false);

  reducer->Initialize();

  // config
  cfg_tuple cfg = Configure(reducer, decay_channel);

  // add leaves  
  summary.AddSection("Added leaves");
  ReducerLeaf<Double_t>& varKminus_SumProbNNkpi = reducer->CreateDoubleLeaf("varKminus_SumProbNNkpi_rew", -999999.);
  varKminus_SumProbNNkpi.Add(reducer->GetInterimLeafByName("varKminus_ProbNNk_rew"), reducer->GetInterimLeafByName("varKminus_ProbNNpi_rew"));
  reducer->CreateDoubleLeaf("varKminus_PID_rew", -999999.).Divide(reducer->GetInterimLeafByName("varKminus_ProbNNk_rew"), varKminus_SumProbNNkpi);
  ReducerLeaf<Double_t>& varKplus_SumProbNNkpi = reducer->CreateDoubleLeaf("varKplus_SumProbNNkpi_rew", -999999.);
  varKplus_SumProbNNkpi.Add(reducer->GetInterimLeafByName("varKplus_ProbNNk_rew"), reducer->GetInterimLeafByName("varKplus_ProbNNpi_rew"));
  reducer->CreateDoubleLeaf("varKplus_PID_rew", -999999.).Divide(reducer->GetInterimLeafByName("varKplus_ProbNNk_rew"), varKplus_SumProbNNkpi);

  reducer->Run();
  reducer->Finalize();
}

cfg_tuple Configure(Reducer* _rdcr, std::string& _channel){
  doocore::config::Summary& summary = doocore::config::Summary::GetInstance();
  summary.AddSection("Channel");
  // typedef tuple: head, daughters, stable particles, isMC, isFlat
  std::string head ="";
  std::list<std::string> daughters;
  std::list<std::string> stable_particles;
  bool isMC = false;
  bool isFlat = false;
  if (_channel == "B02DD"){
    head = "B0";
    daughters.push_back("Dplus");
    daughters.push_back("Dminus");
    stable_particles.push_back("Dplus_Kminus_or_piminus");
    stable_particles.push_back("Dplus_piplus_or_Kplus_One");
    stable_particles.push_back("Dplus_piplus_or_Kplus_Two");
    stable_particles.push_back("Dminus_Kplus_or_piplus");
    stable_particles.push_back("Dminus_piminus_or_Kminus_One");
    stable_particles.push_back("Dminus_piminus_or_Kminus_Two");
    isMC = _rdcr->LeafExists(head+"_BKGCAT");
    isFlat = (_rdcr->LeafExists("flat_array_index") || _rdcr->LeafExists("idxPV"));
  }
  else{
    serr << "-ERROR- \t" << "B02DDPIDReweightingGrimReaper \t" << "No valid decay channel. Possible decay channels are:" << endmsg;
    serr << "-ERROR- \t" << "B02DDPIDReweightingGrimReaper \t" << "- B02DD" << endmsg;
  }
  summary.Add("Name", _channel);
  summary.Add("Head", head);
  for (std::list<std::string>::iterator it = daughters.begin(); it != daughters.end(); ++it){
    summary.Add("Daughter", *it);
  }
  for (std::list<std::string>::iterator it = stable_particles.begin(); it != stable_particles.end(); ++it){
    summary.Add("Stable", *it);
  }
  summary.AddSection("Data Type");
  summary.Add("MC", isMC);
  summary.Add("Flat", isFlat);

  if (isFlat) sinfo << "-info-  \t" << "You are running the reducer over a flat tuple!" << endmsg;
  if (isMC) sinfo << "-info-  \t" << "You are running the reducer over a MC tuple!" << endmsg;

  return std::make_tuple(head, daughters, stable_particles, isMC, isFlat);
}
