// STL
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

// ROOT
#include "TBranch.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"

// from Project
#include "configuration/ToyConfig.h"
#include "generator/ToyGenerator.h"

int main(int argc, char * argv[]){
  if (argc < 2) {
    std::cout << "Usage:   " << argv[0] << " fit_config_file_name" << std::endl;
    return 0;
  }
  using cptoymc::configuration::ToyConfig;
  using cptoymc::generator::ToyGenerator;

  ToyConfig config;
  config.load(argv[1]);

  TFile out_file("ToyMC.root","RECREATE");
  TTree out_tree("ToyMCTree","A tree filled with ToyMC observables");
  
  ToyGenerator generator(config);
  generator.GenerateToy(out_tree,1234);
  
  out_file.Write();
  out_file.Close();

  return 0;
}


