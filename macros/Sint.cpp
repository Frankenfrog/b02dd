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

using namespace RooFit;
using namespace std;

void Sint(){

  RooRealVar        Aint("Aint","Aint",-0.125);
  RooRealVar        omegaB("omegaB","omegaB",0.3861);
  RooRealVar        omegaBbar("omegaBbar","omegaBbar",0.394);
  RooRealVar        Ap("Ap","Ap",-0.0047);
  RooRealVar        dm("dm","dm",0.51);
  RooRealVar        tau("tau","tau",1.519);
  RooRealVar        tmin("tmin","tmin",0.25);
  RooRealVar        CDD("CDD","CDD",0.26);

  RooArgList        paramList(Aint,omegaB,omegaBbar,Ap,dm,tau,CDD,tmin);
  RooFormulaVar     Sint("Sint","Sint","(@0-(1-@1-@2)*@3+@3*@0*(@1-@2))/(1-@1-@2-@0*@3-@0*(@1-@2))*(1+@4*@4*@5*@5)/(sin(@4*@7)+@4*@5*cos(@4*@7))+@6*(@4*@5*sin(@4*@7)+cos(@4*@7))/(sin(@4*@7)+@4*@5*cos(@4*@7))",paramList);

  int nParameters = paramList.getSize() - 1 ;
  vector<Double_t> plusVar, minusVar ;
  
  // Create vector of plus,minus variations for each parameter
  TMatrixDSym V(nParameters);
  for (int i = 0; i < nParameters; ++i) {
    for (int j = 0; j < nParameters; ++j) {
      V[i][j] = 0;
    }
  }
  V[0][0] = 0.026*0.026;
  V[1][1] = 0.001*0.001;
  V[2][2] = 0.001*0.001;
  V[3][3] = 0.0106*0.0106;
  V[4][4] = 0.004*0.004;
  V[5][5] = 0.005*0.005;
  V[6][6] = 0.18*0.18;
  
  for (Int_t ivar=0 ; ivar<nParameters ; ivar++) {
    
    RooRealVar& rrv = (RooRealVar&)paramList[ivar] ;
    
    Double_t cenVal = rrv.getVal() ;
    Double_t errVal = sqrt(V(ivar,ivar)) ;
    
    // Make Plus variation
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal+errVal) ;
    plusVar.push_back(Sint.getVal()) ;
    
    // Make Minus variation
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal-errVal) ;
    minusVar.push_back(Sint.getVal()) ;
    
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal) ;
  }
  
  TMatrixDSym C(nParameters) ;
  for (int i=0 ; i<nParameters ; i++) {
    for (int j=i ; j<nParameters ; j++) {
      C(i,j) = V(i,j)/sqrt(V(i,i)*V(j,j)) ;
      C(j,i) = C(i,j) ;
    }
  }
  
  // Make vector of variations
  TVectorD F(plusVar.size()) ;
  for (unsigned int j=0 ; j<plusVar.size() ; j++) {
    F[j] = (plusVar[j]-minusVar[j])/2 ;
  }

  // Calculate error in linear approximation from variations and correlation coefficient
  Double_t sum = F*(C*F) ;

  cout  <<  Sint.getVal() <<  " pm "  <<  sqrt(sum) << endl;
}
