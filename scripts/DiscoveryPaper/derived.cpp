#include "derived.h"
#include <TLegend.h>
#include <iostream>
#include <TH2.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TROOT.h>

const float Dsmass = 1968.3f;
const float Dpmass = 1869.61f;
const float pimass = 139.57018f;
const float Kmass = 493.677f;
const float pmass = 938.272046f;
const float Lcmass = 2286.46f;
const float Phimass = 1019.461f;

TVector3 discoverypaper::getthreevector(int i) {
  TVector3 out;
  if (i==0) {
    out.SetXYZ(Dplus_Kminus_or_piminus_PX,Dplus_Kminus_or_piminus_PY,Dplus_Kminus_or_piminus_PZ);
  }
  if (i==1) {
    out.SetXYZ(Dplus_piplus_or_Kplus_One_PX,Dplus_piplus_or_Kplus_One_PY,Dplus_piplus_or_Kplus_One_PZ);
  }
  if (i==2) {
    out.SetXYZ(Dplus_piplus_or_Kplus_Two_PX,Dplus_piplus_or_Kplus_Two_PY,Dplus_piplus_or_Kplus_Two_PZ);
  }
  if (i==3) {
    out.SetXYZ(Dminus_Kplus_or_piplus_PX,Dminus_Kplus_or_piplus_PY,Dminus_Kplus_or_piplus_PZ);
  }
  if (i==4) {
    out.SetXYZ(Dminus_piminus_or_Kminus_One_PX,Dminus_piminus_or_Kminus_One_PY,Dminus_piminus_or_Kminus_One_PZ);
  }
  if (i==5) {
    out.SetXYZ(Dminus_piminus_or_Kminus_Two_PX,Dminus_piminus_or_Kminus_Two_PY,Dminus_piminus_or_Kminus_Two_PZ);
  }
  return out;
}
float discoverypaper::ppid(int i) {
  if (0==i)
    return Dplus_Kminus_or_piminus_ProbNNp/(Dplus_Kminus_or_piminus_ProbNNp+Dplus_Kminus_or_piminus_ProbNNpi);
  if (1==i)
    return Dplus_piplus_or_Kplus_One_ProbNNp/(Dplus_piplus_or_Kplus_One_ProbNNp+Dplus_piplus_or_Kplus_One_ProbNNpi);
  if (2==i)                                   
    return Dplus_piplus_or_Kplus_Two_ProbNNp/(Dplus_piplus_or_Kplus_Two_ProbNNp+Dplus_piplus_or_Kplus_Two_ProbNNpi);
  if (3==i)
    return Dminus_Kplus_or_piplus_ProbNNp/(Dminus_Kplus_or_piplus_ProbNNp+Dminus_Kplus_or_piplus_ProbNNpi);
  if (4==i)
    return Dminus_piminus_or_Kminus_One_ProbNNp/(Dminus_piminus_or_Kminus_One_ProbNNp+Dminus_piminus_or_Kminus_One_ProbNNpi);
  if (5==i)
    return Dminus_piminus_or_Kminus_Two_ProbNNp/(Dminus_piminus_or_Kminus_Two_ProbNNp+Dminus_piminus_or_Kminus_Two_ProbNNpi);
  return 0.5f;
}
float discoverypaper::pid(int i) {
  if (0==i)
    return Dplus_Kminus_or_piminus_ProbNNk/(Dplus_Kminus_or_piminus_ProbNNk+Dplus_Kminus_or_piminus_ProbNNpi);
  if (1==i)
    return Dplus_piplus_or_Kplus_One_ProbNNk/(Dplus_piplus_or_Kplus_One_ProbNNk+Dplus_piplus_or_Kplus_One_ProbNNpi);
  if (2==i)                                   
    return Dplus_piplus_or_Kplus_Two_ProbNNk/(Dplus_piplus_or_Kplus_Two_ProbNNk+Dplus_piplus_or_Kplus_Two_ProbNNpi);
  if (3==i)
    return Dminus_Kplus_or_piplus_ProbNNk/(Dminus_Kplus_or_piplus_ProbNNk+Dminus_Kplus_or_piplus_ProbNNpi);
  if (4==i)
    return Dminus_piminus_or_Kminus_One_ProbNNk/(Dminus_piminus_or_Kminus_One_ProbNNk+Dminus_piminus_or_Kminus_One_ProbNNpi);
  if (5==i)
    return Dminus_piminus_or_Kminus_Two_ProbNNk/(Dminus_piminus_or_Kminus_Two_ProbNNk+Dminus_piminus_or_Kminus_Two_ProbNNpi);
  return 0.5f;
}

TLorentzVector discoverypaper::settrackmasshypo(TVector3 in, float mass) {
  TLorentzVector out;
  float ebuffer = sqrt(mass*mass+in.Mag2());
  out.SetVect(in);
  out.SetE(ebuffer);
  return out;
}
float discoverypaper::Kpip(int i) {
  TLorentzVector Dbuffer;
  if (i==0) { // compute Kpipi hypothesis for Dplus
    Dbuffer = settrackmasshypo(getthreevector(0),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(1),pimass);
    Dbuffer += settrackmasshypo(getthreevector(2),pmass);
  } else { // compute Kpipi hypothesis for Dminus
    Dbuffer = settrackmasshypo(getthreevector(3),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(4),pimass);
    Dbuffer += settrackmasshypo(getthreevector(5),pmass);
  }
  return Dbuffer.M();
}
float discoverypaper::Kppi(int i) {
  TLorentzVector Dbuffer;
  if (i==0) { // compute Kpipi hypothesis for Dplus
    Dbuffer = settrackmasshypo(getthreevector(0),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(1),pmass);
    Dbuffer += settrackmasshypo(getthreevector(2),pimass);
  } else { // compute Kpipi hypothesis for Dminus
    Dbuffer = settrackmasshypo(getthreevector(3),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(4),pmass);
    Dbuffer += settrackmasshypo(getthreevector(5),pimass);
  }
  return Dbuffer.M();
}
float discoverypaper::Kpipi(int i) {
  TLorentzVector Dbuffer;
  if (i==0) { // compute Kpipi hypothesis for Dplus
    Dbuffer = settrackmasshypo(getthreevector(0),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(1),pimass);
    Dbuffer += settrackmasshypo(getthreevector(2),pimass);
  } else { // compute Kpipi hypothesis for Dminus
    Dbuffer = settrackmasshypo(getthreevector(3),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(4),pimass);
    Dbuffer += settrackmasshypo(getthreevector(5),pimass);
  }
  return Dbuffer.M();
}
float discoverypaper::KKpi(int i) {
  TLorentzVector Dbuffer;
  if (i==0) {
    Dbuffer = settrackmasshypo(getthreevector(0),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(1),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(2),pimass);
  } else {
    Dbuffer = settrackmasshypo(getthreevector(3),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(4),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(5),pimass);
  }
  return Dbuffer.M();
}
float discoverypaper::KpiK(int i) {
  TLorentzVector Dbuffer;
  if (i==0) {
    Dbuffer = settrackmasshypo(getthreevector(0),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(1),pimass);
    Dbuffer += settrackmasshypo(getthreevector(2),Kmass);
  } else {
    Dbuffer = settrackmasshypo(getthreevector(3),Kmass);
    Dbuffer += settrackmasshypo(getthreevector(4),pimass);
    Dbuffer += settrackmasshypo(getthreevector(5),Kmass);
  }
  return Dbuffer.M();
}
void resetbranches(TTree* fChain) {
  fChain->SetBranchStatus("*",0);  // disable all branches
  fChain->SetBranchStatus("*_MM",1);  // activate branchname
  fChain->SetBranchStatus("B0_FitDDPVConst_D*us_P?_P?",1);  // activate branchname
  fChain->SetBranchStatus("D*us_*us_or_*_PX",1);
  fChain->SetBranchStatus("D*us_*us_or_*_PY",1);
  fChain->SetBranchStatus("D*us_*us_or_*_PZ",1);
  fChain->SetBranchStatus("*ProbNNp",1);
  fChain->SetBranchStatus("*ProbNNpi",1);
  fChain->SetBranchStatus("*ProbNNk",1);
  fChain->SetBranchStatus("Dplus_MM",1);
  fChain->SetBranchStatus("Dminus_MM",1);

  fChain->SetBranchStatus("BDT1_classifier",1);

  fChain->SetBranchStatus("B0_ENDVERTEX_CHI2",1);
  fChain->SetBranchStatus("B0_ENDVERTEX_NDOF",1);
  fChain->SetBranchStatus("B0_FitPVConst_Dplus_decayLength",1);
  fChain->SetBranchStatus("B0_FitPVConst_Dplus_decayLengthErr",1);
  fChain->SetBranchStatus("B0_FitPVConst_Dminus_decayLength",1);
  fChain->SetBranchStatus("B0_FitPVConst_Dminus_decayLengthErr",1);
  fChain->SetBranchStatus("B0_FitPVConst_ctauErr",1);
  fChain->SetBranchStatus("B0_FitPVConst_MERR",1);
  fChain->SetBranchStatus("B0_FitDDPVConst_M",1);
  fChain->SetBranchStatus("catDDFinalState",1);
  fChain->SetBranchStatus("varD*MassHypo*",1);
  fChain->SetBranchStatus("Dminus_FDCHI2_ORIVX",1);
  fChain->SetBranchStatus("Dplus_FDCHI2_ORIVX",1);
  fChain->SetBranchStatus("*_PID*",1);
  fChain->SetBranchStatus("varBEndVtxChi2ndof",1);
  fChain->SetBranchStatus("obsMass",1);
  fChain->SetBranchStatus("obsMass",1);
  fChain->SetBranchStatus("varDDDTFSumPT",1);
  fChain->SetBranchStatus("obsTime",1);
  fChain->SetBranchStatus("varIPChi2",1);
  fChain->SetBranchStatus("varBDIRAOwnPV",1);
  fChain->SetBranchStatus("obsDTFMomentum",1);
  fChain->SetBranchStatus("varDMinDaughtersSumPT",1);
  fChain->SetBranchStatus("obsMassDauOne",1);
  fChain->SetBranchStatus("obsMassDauTwo",1);
  fChain->SetBranchStatus("varDMaxEndVtxChi2ndof",1);
  fChain->SetBranchStatus("varDMinVtxSepChi2",1);
  fChain->SetBranchStatus("varDMinDIRA",1);
  fChain->SetBranchStatus("varPionMaxTrackFitChi2ndof",1);
  fChain->SetBranchStatus("varKaonMaxTrackFitChi2ndof",1);
  fChain->SetBranchStatus("varKaonMinPT",1);
  fChain->SetBranchStatus("varPionOneMinPT",1);
  fChain->SetBranchStatus("varPionTwoMinPT",1);
  fChain->SetBranchStatus("varKaonMinP",1);
  fChain->SetBranchStatus("varPionOneMinP",1);
  fChain->SetBranchStatus("varPionTwoMinP",1);
  fChain->SetBranchStatus("varKaonIPChi2Minimum",1);
  fChain->SetBranchStatus("varPionOneIPChi2Minimum",1);
  fChain->SetBranchStatus("varPionTwoIPChi2Minimum",1);
  fChain->SetBranchStatus("varKaonMaxTrackGhostProb",1);
  fChain->SetBranchStatus("varPionMaxTrackGhostProb",1);
  fChain->SetBranchStatus("obsMassErr",1);
  //fChain->SetBranchStatus("idxPV",1);
  fChain->SetBranchStatus("obsTimeErr",1);
  fChain->SetBranchStatus("varDTFPVPosZ",1);
  fChain->SetBranchStatus("varDTFStatusPVConst",1);
  fChain->SetBranchStatus("varDMinTauSignificance",1);

}


void discoverypaper::Loop() {
  // METHOD1:
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  TFile* of = new TFile("of4.root","recreate"); /// 1 first approach, 2 fix D separation, 3 fix pid, 4 reorder bdt
  bool copytree = false;
  TTree* clone;
   if (copytree) clone = fChain->CloneTree(0);
  resetbranches(fChain);
  Long64_t nentries = fChain->GetEntriesFast();
  TH1F* before = new TH1F("before","before",60,5050,5650);
  TH1F* after = new TH1F("after","after",60,5050,5650);
  TH1F* aftert = new TH1F("aftert","aftert",60,5050,5650);


    int killed_at_front(0);
    int killed_by_Ds(0);
    int killed_by_Lc(0);
    int passed(0);



  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    //if (idxPV>0.5) {skipped++; continue;}

    if (BDT1_classifier<0.) continue;
    before->Fill(B0_FitDDPVConst_M[0]);
    if (B0_ENDVERTEX_CHI2/B0_ENDVERTEX_NDOF>10.) {killed_at_front++; continue;}
    //if (B0_FitPVConst_ctauErr[0]>0.2||B0_FitPVConst_MERR[0]>30.) continue;
    //if (B0_FitPVConst_Dplus_decayLength[0]/B0_FitPVConst_Dplus_decayLengthErr[0]<0.) continue;
    if (Dplus_FDCHI2_ORIVX<0.) {killed_at_front++; continue;}
    if (Dminus_FDCHI2_ORIVX<0.) {killed_at_front++; continue;}
    //if (B0_FitPVConst_Dminus_decayLength[0]/B0_FitPVConst_Dminus_decayLengthErr[0]<0.) {killed_at_front++; continue;}
    if (fabs(catDDFinalState-1)>0.5) {killed_at_front++; continue;}

    //std::cout << Kpipi(0) << "\t\t" << Dplus_MM << "\t\t" << varDplusMassHypo_Kpipi << std::endl;
    if (fabs(Kpipi(0)-Dpmass)>25.) {killed_at_front++; continue;}
    //std::cout << ".";
    if (fabs(Kpipi(1)-Dpmass)>25.) {killed_at_front++; continue;}

    if (fabs(KKpi(0)-Dsmass)<25.) {
      /// now things get complicated for the D+
      TLorentzVector phimass = settrackmasshypo(getthreevector(0),Kmass);
      phimass += settrackmasshypo(getthreevector(1),Kmass);
      if (fabs(phimass.M()-Phimass)<25.) {killed_by_Ds++; continue;}
      if (Dplus_piplus_or_Kplus_One_PIDK>-10.f) {killed_by_Ds++; continue;}
      //if (pid(1)>.5f) continue;
    } 
    if (fabs(KpiK(0)-Dsmass)<25.) {
      TLorentzVector phimass = settrackmasshypo(getthreevector(0),Kmass);
      phimass += settrackmasshypo(getthreevector(2),Kmass);
      if (fabs(phimass.M()-Phimass)<25.)  {killed_by_Ds++; continue;}
      if (Dplus_piplus_or_Kplus_Two_PIDK>-10.f)  {killed_by_Ds++; continue;}
      //if (pid(2)>.5f) continue;
    }

    if (fabs(KKpi(1)-Dsmass)<25.) {
      /// now things get complicated for the D-
      TLorentzVector phimass = settrackmasshypo(getthreevector(3),Kmass);
      phimass += settrackmasshypo(getthreevector(4),Kmass);
      if (fabs(phimass.M()-Phimass)<25.)  {killed_by_Ds++; continue;}
      if (Dminus_piminus_or_Kminus_One_PIDK>-10.f)  {killed_by_Ds++; continue;}
      //if (pid(4)>.5f) continue;
    } 
    if (fabs(KpiK(1)-Dsmass)<25.) {
      TLorentzVector phimass = settrackmasshypo(getthreevector(3),Kmass);
      phimass += settrackmasshypo(getthreevector(5),Kmass);
      if (fabs(phimass.M()-Phimass)<25.)  {killed_by_Ds++; continue;}
      if (Dminus_piminus_or_Kminus_Two_PIDK>-10.f)  {killed_by_Ds++; continue;}
      //if (pid(5)>.5f) continue;
    }

    if (fabs(Kppi(0)-Lcmass)<25.) {
      if (Dplus_piplus_or_Kplus_One_PIDp>0.f) {killed_by_Lc++; continue;}
      //if (ppid(1)>.5f) continue;
    }
    if (fabs(Kpip(0)-Lcmass)<25.) {
      if (Dplus_piplus_or_Kplus_Two_PIDp>0.f) {killed_by_Lc++; continue;}
      //if (ppid(2)>.5f) continue;
    }

    if (fabs(Kppi(1)-Lcmass)<25.) {
      if (Dminus_piminus_or_Kminus_One_PIDp>0.f) {killed_by_Lc++; continue;}
      //if (ppid(4)>.5f) continue;
    }
    if (fabs(Kpip(1)-Lcmass)<25.) {
      if (Dminus_piminus_or_Kminus_Two_PIDp>0.f) {killed_by_Lc++; continue;}
      //if (ppid(5)>.5f) continue;
    }
    passed++;

    after->Fill(B0_FitDDPVConst_M[0]);
    if (BDT1_classifier>0.3) {aftert->Fill(B0_FitDDPVConst_M[0]);}

    if (copytree) {
      fChain->SetBranchStatus("*",1);  // disable all branches
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      clone->Fill();
      resetbranches(fChain);
    }

  }
  TCanvas* c = new TCanvas();
  before->Draw("e");
  before->SetTitle("Franks preselection + BDT>0.0");
  before->SetLineColor(kBlue);
  before->SetMarkerColor(kBlue);
  before->GetYaxis()->SetRangeUser(0.,before->GetMaximum()*1.2);
  before->GetYaxis()->SetTitle("candidates / (10 MeV/c^{2})");
  before->GetXaxis()->SetTitle("m (DD, PV const) [MeV/c^{2}]");
  after->SetTitle("+ discovery paper, except their BDT");
  after->SetLineColor(kRed);
  after->SetMarkerColor(kRed);
  after->Draw("e same");
  aftert->SetTitle("+ BDT>0.3");
  aftert->Draw("e same");
  c->BuildLegend()->SetFillColor(kWhite);
  c->SaveAs("mass.png");
  of->WriteTObject(aftert);
  of->WriteTObject(c);
  of->WriteTObject(before);
  if(copytree) of->WriteTObject(clone);
  of->WriteTObject(after);
  of->Close();
  delete of;
  std::cout << " out of " << killed_by_Ds+killed_by_Lc+killed_at_front+passed << std::endl;
  std::cout << "presel  " << killed_at_front << std::endl;
  std::cout << "D_s     " << killed_by_Ds    << std::endl;
  std::cout << "L_c     " << killed_by_Lc    << std::endl;
  std::cout << "pass    " << passed          << std::endl;
}

int main() {
  gROOT->ProcessLine(".L official.C");
  discoverypaper d;
  d.Loop();
  return 0;
}
