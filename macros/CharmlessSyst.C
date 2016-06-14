#include <iostream>
#include <sstream>

// from ROOT
#include "TMatrixDSym.h"
#include "TVectorD.h"

//from RooFit
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooPoisson.h"

using namespace RooFit;
using namespace std;

void CharmlessSyst(){

  RooRealVar        charmless("charmless","charmless",0,1000);
  charmless.setVal(28.7);
  RooRealVar        mean("mean","mean",28.7);
  RooRealVar        sigma("sigma","sigma",5.4);
  RooGaussian       gauss("gauss","gauss",charmless,mean,sigma);
  RooPoisson        poisson("poisson","poisson",charmless,mean);

  RooFormulaVar     systematic("systematic","systematic","@0/(1610+@0)*1.8",charmless);
  cout << systematic.getVal() << endl;
  RooDataSet*       toydata = gauss.generate(charmless,1e7);
  toydata->addColumn(systematic);
  toydata->Print("v");
  RooRealVar*       systematic_var = dynamic_cast<RooRealVar*>(toydata->get()->find("systematic"));
  cout << toydata->mean(*systematic_var)  <<  endl;
}
