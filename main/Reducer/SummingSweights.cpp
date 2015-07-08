// from STL
#include <iostream>
#include <map>
#include <utility>

// from ROOT
#include "TROOT.h"
#include "TString.h"

// from DooCore
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"

// from DooSelection
#include "dooselection/reducer/Reducer.h"

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