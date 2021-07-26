/******************************************/
// InvertBDTGrimReaper.cpp
//
// Standalone GrimReaper which inverts the BDT classifier
//
// Author: Frank Meier
// Date: 2015-11-20
/******************************************/

// from DooCore
#include "doocore/io/MsgStream.h"

// from DooSelection
#include "dooselection/reducer/Reducer.h"

int main(int argc, char * argv[]){
  doocore::io::sinfo << "-info-  \t" << "InvertBDTGrimReaper \t" << "Welcome!" << doocore::io::endmsg;
  std::string inputfile, inputtree, outputfile, outputtree;
  if (argc == 5){
    inputfile = argv[1];
    inputtree = argv[2];
    outputfile = argv[3];
    outputtree = argv[4];
  }
  else{
    doocore::io::serr << "-ERROR- \t" << "InvertBDTGrimReaper \t" << "Parameters needed:" << doocore::io::endmsg;
    doocore::io::serr << "-ERROR- \t" << "InvertBDTGrimReaper \t"<< "input_file_name input_tree_name output_file_name output_tree_name" << doocore::io::endmsg;
    return 1;
  }

  dooselection::reducer::Reducer reducer;

  reducer.set_input_file_path(inputfile);
  reducer.set_input_tree_path(inputtree);
  reducer.set_output_file_path(outputfile);
  reducer.set_output_tree_path(outputtree);

  reducer.Initialize();
  reducer.CreateDoubleCopyLeaf("BDT_wPIDs_Kpipi_inverted",reducer.GetInterimLeafByName("BDT_wPIDs_Kpipi_classifier"),-1.0);
  reducer.CreateDoubleCopyLeaf("BDT_wPIDs_KKpi_inverted",reducer.GetInterimLeafByName("BDT_wPIDs_KKpi_classifier"),-1.0);
  reducer.Run();
  reducer.Finalize();

  doocore::io::sinfo << "-info- \t" << "InvertBDTGrimReaper \t" << "Done!" << doocore::io::endmsg;
}
