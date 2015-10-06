// from STL
#include <iostream>
#include <map>
#include <utility>

// from ROOT
#include "TROOT.h"
#include "TString.h"

// from DooCore
#include "doocore/io/MsgStream.h"

// from DooSelection
#include "dooselection/reducer/Reducer.h"

// for cool vector assignment
#include <boost/assign/std/vector.hpp>
using namespace boost::assign;

using std::map;
using namespace RooFit;
using namespace std;
using namespace doocore::io;
using namespace dooselection::reducer;

int main(int argc, const char * argv[]){
  
  if (argc != 5) {
    std::cout << "Parameters needed: InputFile InputTree OutputFile OutputTree" << std::endl;
    return 1;
  }
  
  Reducer AReducer;
  AReducer.set_input_file_path(argv[1]);
  AReducer.set_input_tree_path(argv[2]);
  AReducer.set_output_file_path(argv[3]);
  AReducer.set_output_tree_path(argv[4]);

  // Branches for Mirco's systemactics studies
  AReducer.add_branch_keep("varPseudorapidity");
  AReducer.add_branch_keep("obsTransverseMomentum");
  AReducer.add_branch_keep("catNTrack");
  AReducer.add_branch_keep("catNPV");
  AReducer.add_branch_keep("varPhi");
  
  AReducer.add_branch_keep("obsTagOS_StdComb");
  AReducer.add_branch_keep("obsTagOSwCharm");
  AReducer.add_branch_keep("obsTagSS");
  AReducer.add_branch_keep("obsTagSSProton");
  AReducer.add_branch_keep("obsTagSSPionBDT");

  AReducer.add_branch_keep("obsEtaOS_StdComb");
  AReducer.add_branch_keep("obsEtaOSwCharm");
  AReducer.add_branch_keep("obsEtaSS");
  AReducer.add_branch_keep("obsEtaSSProton");
  AReducer.add_branch_keep("obsEtaSSPionBDT");

  AReducer.add_branch_keep("SigWeight");

  AReducer.Initialize();
  AReducer.Run();
  AReducer.Finalize();
}