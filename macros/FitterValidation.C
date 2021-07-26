#include <iostream>
#include <sstream>

// from ROOT
#include "TMatrixDSym.h"
#include "TVectorD.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"

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

void FitterValidation(){

  Int_t kLHCbFont        = 132;
  Double_t lhcbWidth    = 2.0; // Old LHCb style: 3.00;
  // Text size
  Double_t lhcbTSize    = 0.06;

  // use plain black on white colors
  gROOT->SetStyle("Plain");
  TStyle *lhcbStyle= new TStyle("lhcbStyle","LHCb plots style");
  
  lhcbStyle->SetFillColor(1);
  lhcbStyle->SetFillStyle(1001);   // solid
  lhcbStyle->SetFrameFillColor(0);
  lhcbStyle->SetFrameBorderMode(0);
  lhcbStyle->SetPadBorderMode(0);
  lhcbStyle->SetPadColor(0);
  lhcbStyle->SetCanvasBorderMode(0);
  lhcbStyle->SetCanvasColor(0);
  lhcbStyle->SetStatColor(0);
  lhcbStyle->SetLegendBorderSize(0);

  lhcbStyle->SetPalette(1);
    
  // set the paper & margin sizes
  lhcbStyle->SetPaperSize(20,26);
  lhcbStyle->SetPadTopMargin(0.05);
  lhcbStyle->SetPadRightMargin(0.05); // increase for colz plots
  lhcbStyle->SetPadBottomMargin(0.16);
  lhcbStyle->SetPadLeftMargin(0.14);
  // use large fonts
  lhcbStyle->SetTextFont(kLHCbFont);
  lhcbStyle->SetTextSize(lhcbTSize);
  lhcbStyle->SetLabelFont(kLHCbFont,"x");
  lhcbStyle->SetLabelFont(kLHCbFont,"y");
  lhcbStyle->SetLabelFont(kLHCbFont,"z");
  lhcbStyle->SetLabelSize(lhcbTSize,"x");
  lhcbStyle->SetLabelSize(lhcbTSize,"y");
  lhcbStyle->SetLabelSize(lhcbTSize,"z");
  lhcbStyle->SetTitleFont(kLHCbFont);
  lhcbStyle->SetTitleFont(kLHCbFont,"x");
  lhcbStyle->SetTitleFont(kLHCbFont,"y");
  lhcbStyle->SetTitleFont(kLHCbFont,"z");
  lhcbStyle->SetTitleSize(1.2*lhcbTSize,"x");
  lhcbStyle->SetTitleSize(1.2*lhcbTSize,"y");
  lhcbStyle->SetTitleSize(1.2*lhcbTSize,"z");
  
  // use medium bold lines and thick markers
  lhcbStyle->SetLineWidth(lhcbWidth);
  
  lhcbStyle->SetHistLineWidth(lhcbWidth);
  lhcbStyle->SetFuncWidth(lhcbWidth);
  lhcbStyle->SetGridWidth(lhcbWidth);
  lhcbStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
  lhcbStyle->SetMarkerStyle(20);
  lhcbStyle->SetMarkerSize(1.0);
  
  // label offsets
  lhcbStyle->SetLabelOffset(0.010,"X");
  lhcbStyle->SetLabelOffset(0.010,"Y");
  
  // by default, do not display histogram decorations:
  lhcbStyle->SetOptStat(0);
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  lhcbStyle->SetStatFormat("6.3g"); // specified as c printf options
  lhcbStyle->SetOptTitle(0);
  lhcbStyle->SetOptFit(0);
  //titles
  lhcbStyle->SetTitleOffset(0.95,"X");
  lhcbStyle->SetTitleOffset(0.95,"Y");
  lhcbStyle->SetTitleOffset(1.2,"Z");
  lhcbStyle->SetTitleFillColor(0);
  lhcbStyle->SetTitleStyle(0);
  lhcbStyle->SetTitleBorderSize(0);
  lhcbStyle->SetTitleFont(kLHCbFont,"title");
  lhcbStyle->SetTitleX(0.0);
  lhcbStyle->SetTitleY(1.0);
  lhcbStyle->SetTitleW(1.0);
  lhcbStyle->SetTitleH(0.05);
  
  // look of the statistics box:
  lhcbStyle->SetStatBorderSize(0);
  lhcbStyle->SetStatFont(kLHCbFont);
  lhcbStyle->SetStatFontSize(0.05);
  lhcbStyle->SetStatX(0.9);
  lhcbStyle->SetStatY(0.9);
  lhcbStyle->SetStatW(0.25);
  lhcbStyle->SetStatH(0.15);
  // put tick marks on top and RHS of plots
  lhcbStyle->SetPadTickX(1);
  lhcbStyle->SetPadTickY(1);
  
  // histogram divisions: only 5 in x to avoid label overlaps
  lhcbStyle->SetNdivisions(505,"x");
  lhcbStyle->SetNdivisions(510,"y");
  
  gROOT->SetStyle("lhcbStyle");
  gROOT->ForceStyle();

  TCanvas           c("c","c",800,600);
  // const double fittervalidationshifts_mean[51] = { 1.63,  0.30,  0.52,  0.76,  1.46,
  //                                                  2.13,  1.28,  0.86,  2.61,  0.13,
  //                                                  1.69,  0.55,  1.32,  2.37,  1.05,
  //                                                  0.11,  2.38,  2.00,  1.10,  2.79,
  //                                                  1.65,  1.09,  1.92,  1.56,  0.15,
  //                                                  1.33, -0.39,  1.68, -0.03,  1.55,
  //                                                  1.85,  1.19,  1.28,  3.06,  0.82,
  //                                                  0.50,  0.52,  2.17,  0.34,  1.33,
  //                                                  0.60,  2.55,  0.93,  1.43,  0.32,
  //                                                  1.72,  1.46,  0.29,  0.34, -0.36};

  const double fittervalidationshifts_mean[51] = { 2.32, -0.06, -0.30,  0.96,  0.89,
                                                   1.67, -0.96, -0.61,  1.21,  1.68,
                                                   1.62,  0.04,  0.16,  1.61,  0.54,
                                                  -0.12, -0.21,  0.48,  0.72,  0.64,
                                                   0.85,  0.45, -1.45,  0.31,  0.60,
                                                   0.30, -0.45, -1.70,  0.86, -1.02,
                                                   1.30,  1.61,  1.17,  0.60,  1.46,
                                                   1.52,  0.56,  2.02, -0.02, -0.46,
                                                   1.29,  0.52,  0.30,  2.21,  2.95,
                                                   0.98,  0.42,  2.17,  0.82,  1.55};

  TH1D* hist_mean = new TH1D("hist_mean","hist_mean",10,-5,5);
  for (int i = 0; i < 50; ++i) hist_mean->Fill(fittervalidationshifts_mean[i]);

  // TF1* f_gauss_norm = new TF1("fGauss","gaus(0)/([2]*sqrt(2*3.1415))",-5,5);
  // f_gauss_norm->SetLineColor(kBlack);
  // f_gauss_norm->SetLineWidth(4);
  
  TF1* gauss = new TF1("gauss","gaus(0)/([2]*sqrt(2*3.1415))",-5,5);
  gauss->SetParameters(50,0,1);
  gauss->SetLineColor(12);
  gauss->SetLineStyle(kDashed);
  gauss->SetLineWidth(4);
  
  hist_mean->SetFillColor(16);
  hist_mean->SetFillStyle(1001);
  hist_mean->SetLineColor(kBlack);
  hist_mean->SetLineWidth(2);
  
  // f_gauss_norm->Draw();
  
  hist_mean->Fit("gauss", "Q");
  
  //Get error Band histogram
  TH1D* h_error = new TH1D("hError","hError",500,-5,5);
  for (int i = 1; i <= h_error->GetNbinsX(); ++i) {
    const Double_t pos = -5. + double(i)*10./500.+(10./500./2);
    
    Double_t dev0 = gauss->GradientPar(0, &pos, 0.01);
    Double_t dev1 = gauss->GradientPar(1, &pos, 0.01);
    Double_t dev2 = gauss->GradientPar(2, &pos, 0.01);
    
    double err0 = gauss->GetParError(0);
    double err1 = gauss->GetParError(1);
    double err2 = gauss->GetParError(2);
    
    double error = sqrt(dev0*dev0*err0*err0+dev1*dev1*err1*err1+dev2*dev2*err2*err2);
    
    h_error->SetBinContent(i,gauss->Eval(pos));
    h_error->SetBinError(i,error);
  }
  
  h_error->SetFillColor(12);
  h_error->SetFillStyle(3001);
  h_error->SetLineColor(12);
  h_error->SetLineStyle(kDashed);
  h_error->SetLineWidth(4);
  h_error->SetMarkerStyle(0);
  
  hist_mean->SetMaximum(hist_mean->GetMaximum()+4*sqrt(hist_mean->GetMaximum()));
  
  //legend
  double nVal, nErr, mVal, mErr, sVal, sErr;
  
  nVal = 50 - gauss->GetParameter(0);
  mVal = gauss->GetParameter(1);
  sVal = gauss->GetParameter(2)-1;
  
  nErr = gauss->GetParError(0);
  mErr = gauss->GetParError(1);
  sErr = gauss->GetParError(2);
  
  TLegend* legend = new TLegend(0.2,0.65,0.48,0.93);
  // legend->SetTextFont(kLHCbFont);
  legend->SetTextSize(0.04);
  legend->AddEntry(h_error,Form("#splitline{Gaussian fit}{#scale[0.7]{#Delta#it{N}=%.0f#pm%.0f, #Delta#mu=%.2f#pm%.2f, #Delta#sigma=%.2f#pm%.2f}}",nVal, nErr, mVal, mErr, sVal, sErr),"lf");
  // legend->AddEntry(f_gauss_norm,"Normal distribution","l");
  legend->AddEntry(hist_mean,"Distribution of deviations from optimal","f");
  legend->SetFillColor(0);
  
  //redraw
  hist_mean->Draw();
  
  legend->Draw("NCP");
  
  hist_mean->Draw("same");
  h_error->Draw("E4 same");
  // f_gauss_norm->Draw("same");

  c.SaveAs("fittervalidation_mean.pdf");

  const double fittervalidationshifts_sigma[51] = {0.41, -1.38, -0.03,  0.49, -0.84,
                                                   0.09,  1.02,  2.34,  0.58,  1.74,
                                                   2.66,  0.11,  0.72,  1.33,  3.43,
                                                   0.76,  1.65,  3.39,  3.94,  2.53,
                                                   3.58,  2.05, -0.87,  1,93,  2.37,
                                                  -0.05, -1.62,  2.95,  1.16, -0.84,
                                                  -0.40,  1.58,  1.26,  0.95,  0.60,
                                                   1.62, -0.46,  1.81, -1.33,  2.07,
                                                   1.21,  1.44, -0.20,  0.44,  2.60,
                                                   2.24,  1.01,  0.90, -0.44, -0.77};

  // f_gauss_norm->Draw();
  TH1D* hist_sigma = new TH1D("hist_sigma","hist_sigma",10,-5,5);
  for (int i = 0; i < 50; ++i) hist_sigma->Fill(fittervalidationshifts_sigma[i]);

  hist_sigma->SetFillColor(16);
  hist_sigma->SetFillStyle(1001);
  hist_sigma->SetLineColor(kBlack);
  hist_sigma->SetLineWidth(2);
  
  // f_gauss_norm->Draw();
  
  hist_sigma->Fit("gauss", "Q");

  //Get error Band histogram
  h_error = new TH1D("hError","hError",500,-5,5);
  for (int i = 1; i <= h_error->GetNbinsX(); ++i) {
    const Double_t pos = -5. + double(i)*10./500.+(10./500./2);
    
    Double_t dev0 = gauss->GradientPar(0, &pos, 0.01);
    Double_t dev1 = gauss->GradientPar(1, &pos, 0.01);
    Double_t dev2 = gauss->GradientPar(2, &pos, 0.01);
    
    double err0 = gauss->GetParError(0);
    double err1 = gauss->GetParError(1);
    double err2 = gauss->GetParError(2);
    
    double error = sqrt(dev0*dev0*err0*err0+dev1*dev1*err1*err1+dev2*dev2*err2*err2);
    
    h_error->SetBinContent(i,gauss->Eval(pos));
    h_error->SetBinError(i,error);
  }
  
  h_error->SetFillColor(12);
  h_error->SetFillStyle(3001);
  h_error->SetLineColor(12);
  h_error->SetLineStyle(kDashed);
  h_error->SetLineWidth(4);
  h_error->SetMarkerStyle(0);
  
  hist_sigma->SetMaximum(hist_sigma->GetMaximum()+4*sqrt(hist_sigma->GetMaximum()));
  
  //legend
  nVal = 50 - gauss->GetParameter(0);
  mVal = gauss->GetParameter(1);
  sVal = gauss->GetParameter(2)-1;
  
  nErr = gauss->GetParError(0);
  mErr = gauss->GetParError(1);
  sErr = gauss->GetParError(2);
  
  legend = new TLegend(0.2,0.65,0.48,0.93);
  legend->SetTextSize(0.04);
  legend->AddEntry(h_error,Form("#splitline{Gaussian fit}{#scale[0.7]{#Delta#it{N}=%.0f#pm%.0f, #Delta#mu=%.2f#pm%.2f, #Delta#sigma=%.2f#pm%.2f}}",nVal, nErr, mVal, mErr, sVal, sErr),"lf");
  // legend->AddEntry(f_gauss_norm,"Normal distribution","l");
  legend->AddEntry(hist_sigma,"Distribution of deviations from optimal","f");
  legend->SetFillColor(0);
  
  //redraw
  hist_sigma->Draw();
  
  legend->Draw("NCP");
  
  hist_sigma->Draw("same");
  h_error->Draw("E4 same");
  // f_gauss_norm->Draw("same");

  c.SaveAs("fittervalidation_sigma.pdf");
}
