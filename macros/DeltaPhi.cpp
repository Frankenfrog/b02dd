#include <iostream>
#include <sstream>

// from ROOT
#include "TMatrixDSym.h"
#include "TVectorD.h"
#include "TString.h"

//from RooFit
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooFormulaVar.h"
#include "RooMultiVarGaussian.h"

using namespace RooFit;
using namespace std;

std::pair<double,double> SinPhi(RooRealVar S, RooRealVar C, double S_error, double C_error, double correlation);
std::pair<double,double> DeltaPhi(double SinPhi_value, double SinPhi_error);
void Uncertainty_with_toys();

void DeltaPhi(){

  RooRealVar        S_LHCb("S_LHCb","S_LHCb",-0.54);
  RooRealVar        C_LHCb("C_LHCb","C_LHCb",0.26);
  RooRealVar        S_BaBar("S_BaBar","S_BaBar",-0.63);
  RooRealVar        C_BaBar("C_BaBar","C_BaBar",-0.07);
  RooRealVar        S_Belle("S_Belle","S_Belle",-1.06);
  RooRealVar        C_Belle("C_Belle","C_Belle",-0.43);
  RooRealVar        S_WA("S_WA","S_WA",-0.98);
  RooRealVar        C_WA("C_WA","C_WA",-0.31);
  std::pair<double,double> SinPhi_val_and_error = SinPhi(S_LHCb, C_LHCb, 0.17, 0.18, 0.48); // upper stat errors
  cout  <<  "LHCb with upper stat errors: sin(phi_d + Delta phi) = " <<  SinPhi_val_and_error.first <<  " pm "  <<  SinPhi_val_and_error.second << endl;
  std::pair<double,double> DeltaPhi_val_and_error = DeltaPhi(SinPhi_val_and_error.first, SinPhi_val_and_error.second);
  cout  <<  "LHCb with upper stat errors: Delta phi = " <<  DeltaPhi_val_and_error.first <<  " pm "  <<  DeltaPhi_val_and_error.second << endl;
  SinPhi_val_and_error = SinPhi(S_LHCb, C_LHCb, 0.16, 0.17, 0.48); // lower stat errors
  cout  <<  "LHCb with lower stat errors: sin(phi_d + Delta phi) = " <<  SinPhi_val_and_error.first <<  " pm "  <<  SinPhi_val_and_error.second << endl;
  DeltaPhi_val_and_error = DeltaPhi(SinPhi_val_and_error.first, SinPhi_val_and_error.second);
  cout  <<  "LHCb with lower stat errors: Delta phi = " <<  DeltaPhi_val_and_error.first <<  " pm "  <<  DeltaPhi_val_and_error.second << endl;
  SinPhi_val_and_error = SinPhi(S_WA, C_WA, 0.17, 0.14, -0.08);
  cout  <<  "WA: sin(phi_d + Delta phi) = " <<  SinPhi_val_and_error.first <<  " pm "  <<  SinPhi_val_and_error.second << endl;
  // DeltaPhi_val_and_error = DeltaPhi(1.570796, 0.3);
  // cout  <<  "WA: Delta phi = " <<  DeltaPhi_val_and_error.first <<  " pm "  <<  DeltaPhi_val_and_error.second << endl;
  SinPhi_val_and_error = SinPhi(S_BaBar, C_BaBar, 0.36, 0.23, -0.01);
  cout  <<  "BaBar: sin(phi_d + Delta phi) = " <<  SinPhi_val_and_error.first <<  " pm "  <<  SinPhi_val_and_error.second << endl;
  SinPhi_val_and_error = SinPhi(S_Belle, C_Belle, 0.21, 0.16, -0.12);
  cout  <<  "Belle with upper stat error: sin(phi_d + Delta phi) = " <<  SinPhi_val_and_error.first <<  " pm "  <<  SinPhi_val_and_error.second << endl;
  SinPhi_val_and_error = SinPhi(S_Belle, C_Belle, 0.14, 0.16, -0.12);
  cout  <<  "Belle with lower stat error: sin(phi_d + Delta phi) = " <<  SinPhi_val_and_error.first <<  " pm "  <<  SinPhi_val_and_error.second << endl;
  Uncertainty_with_toys();

}

std::pair<double,double> SinPhi(RooRealVar S, RooRealVar C, double S_error, double C_error, double correlation){

  RooArgList        paramList(S,C);
  RooFormulaVar     SinPhi("SinPhi","SinPhi","-@0/sqrt(1-@1*@1)",paramList);

  int nParameters = paramList.getSize() ;
  vector<Double_t> plusVar, minusVar ;
  
  // Create vector of plus,minus variations for each parameter
  TMatrixDSym V(nParameters);
  for (int i = 0; i < nParameters; ++i) {
    for (int j = 0; j < nParameters; ++j) {
      V[i][j] = 0;
    }
  }
  V(0,0) = S_error*S_error;
  V(1,1) = C_error*C_error;
  
  for (Int_t ivar=0 ; ivar<nParameters ; ivar++) {
    
    RooRealVar& rrv = (RooRealVar&)paramList[ivar] ;
    
    Double_t cenVal = rrv.getVal() ;
    Double_t errVal = sqrt(V(ivar,ivar)) ;
    
    // Make Plus variation
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal+errVal) ;
    plusVar.push_back(SinPhi.getVal()) ;
    
    // Make Minus variation
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal-errVal) ;
    minusVar.push_back(SinPhi.getVal()) ;
    
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal) ;
  }
  
  TMatrixDSym CMatrix(nParameters) ;
  for (int i=0 ; i<nParameters ; i++) {
    for (int j=i ; j<nParameters ; j++) {
      CMatrix(i,j) = V(i,j)/sqrt(V(i,i)*V(j,j)) ;
      CMatrix(j,i) = CMatrix(i,j) ;
    }
  }
  CMatrix(0,1) = correlation*S_error*C_error;
  CMatrix(1,0) = correlation*S_error*C_error;

  // Make vector of variations
  TVectorD F(plusVar.size()) ;
  for (unsigned int j=0 ; j<plusVar.size() ; j++) {
    F[j] = (plusVar[j]-minusVar[j])/2 ;
  }

  // Calculate error in linear approximation from variations and correlation coefficient
  Double_t sum = F*(CMatrix*F) ;
  std::pair<double,double> SinPhi_val_and_error(SinPhi.getVal(),sqrt(sum));
  return SinPhi_val_and_error;
}

std::pair<double,double> DeltaPhi(double SinPhi_value, double SinPhi_error){

  RooRealVar        SinPhi("SinPhi","SinPhi",SinPhi_value);
  RooRealVar        SinPhi_bccs("SinPhi_bccs","SinPhi_bccs",0.682);
  RooArgList        paramList(SinPhi,SinPhi_bccs);
  RooFormulaVar     DeltaPhi("DeltaPhi","DeltaPhi","TMath::ASin(@0)-TMath::ASin(@1)",paramList);

  int nParameters = paramList.getSize() ;
  vector<Double_t> plusVar, minusVar ;
  
  // Create vector of plus,minus variations for each parameter
  TMatrixDSym V(nParameters);
  for (int i = 0; i < nParameters; ++i) {
    for (int j = 0; j < nParameters; ++j) {
      V[i][j] = 0;
    }
  }
  V(0,0) = SinPhi_error*SinPhi_error;
  V(1,1) = 0.02*0.02;
  
  for (Int_t ivar=0 ; ivar<nParameters ; ivar++) {
    
    RooRealVar& rrv = (RooRealVar&)paramList[ivar] ;
    
    Double_t cenVal = rrv.getVal() ;
    Double_t errVal = sqrt(V(ivar,ivar)) ;
    
    // Make Plus variation
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal+errVal) ;
    plusVar.push_back(DeltaPhi.getVal()) ;
    
    // Make Minus variation
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal-errVal) ;
    minusVar.push_back(DeltaPhi.getVal()) ;
    
    ((RooRealVar*)paramList.at(ivar))->setVal(cenVal) ;
  }
  
  TMatrixDSym CMatrix(nParameters) ;
  for (int i=0 ; i<nParameters ; i++) {
    for (int j=i ; j<nParameters ; j++) {
      CMatrix(i,j) = V(i,j)/sqrt(V(i,i)*V(j,j)) ;
      CMatrix(j,i) = CMatrix(i,j) ;
    }
  }

  // Make vector of variations
  TVectorD F(plusVar.size()) ;
  for (unsigned int j=0 ; j<plusVar.size() ; j++) {
    F[j] = (plusVar[j]-minusVar[j])/2 ;
  }

  // Calculate error in linear approximation from variations and correlation coefficient
  Double_t sum = F*(CMatrix*F) ;
  std::pair<double,double> DeltaPhi_val_and_error(DeltaPhi.getVal(),sqrt(sum));
  return DeltaPhi_val_and_error;
}

void Uncertainty_with_toys(){
  RooRealVar            S_LHCb("S_LHCb","S_LHCb",-2,2);
  RooRealVar            S_mean("S_mean","S_mean",-0.54);
  RooRealVar            S_sigma("S_sigma","S_sigma",sqrt(0.16*0.16+0.05*0.05));
  RooRealVar            C_LHCb("C_LHCb","C_LHCb",-2,2);
  RooRealVar            C_mean("C_mean","C_mean",0.26);
  RooRealVar            C_sigma("C_sigma","C_sigma",sqrt(0.17*0.17+0.02*0.02));
  TMatrixDSym           CovMatrix(2);
  CovMatrix(0,0) = S_sigma.getVal()*S_sigma.getVal();
  CovMatrix(0,1) = 0.48*S_sigma.getVal()*C_sigma.getVal();
  CovMatrix(1,0) = CovMatrix(0,1);
  CovMatrix(1,1) = C_sigma.getVal()*C_sigma.getVal();
  RooMultiVarGaussian   pdfmultigauss("pdfmultigauss","pdfmultigauss",RooArgList(S_LHCb,C_LHCb),RooArgList(S_mean,C_mean),CovMatrix);
  RooDataSet*           data = pdfmultigauss.generate(RooArgSet(S_LHCb,C_LHCb),3000000);
  RooFormulaVar         SinPhi("SinPhi","SinPhi","-@0/sqrt(1-@1*@1)",RooArgList(S_LHCb,C_LHCb));
  data->addColumn(SinPhi);
  std::vector<double> sorted_dataset;
  for(int i = 0; i < data->numEntries(); i++){
    const RooArgSet* params = data->get(i);
    sorted_dataset.push_back(params->getRealValue("SinPhi"));
  }
  std::sort(sorted_dataset.begin(), sorted_dataset.end());
  S_LHCb.setVal(S_mean.getVal());
  C_LHCb.setVal(C_mean.getVal());
  cout << "sin(phi_d + Delta phi) = " << SinPhi.getVal()  <<  " + " <<  sorted_dataset.at(floor(data->numEntries()*0.84135)) - SinPhi.getVal() << " - " << SinPhi.getVal() - sorted_dataset.at(floor(data->numEntries()*0.15865)) << endl;
}
