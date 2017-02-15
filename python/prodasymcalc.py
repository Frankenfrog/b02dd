#!/usr/bin/env python

import argparse

bins = {
  "Bd" : {
    "1" : { "pt"  : [ 1.0, 4.0], "eta" : [4.5,5.2], "AP" :  0.0016, "stat" : 0.0253, "syst" : 0.0016, "systcorr" : 0.0013},
    "2" : { "pt"  : [ 1.0, 4.0], "eta" : [3.7,4.5], "AP" : -0.0158, "stat" : 0.0162, "syst" : 0.0015, "systcorr" : 0.0013},
    "3" : { "pt"  : [ 2.0, 4.0], "eta" : [3.0,3.7], "AP" :  0.0055, "stat" : 0.0254, "syst" : 0.0016, "systcorr" : 0.0013},
    "4" : { "pt"  : [ 4.0,12.0], "eta" : [4.5,4.7], "AP" :  0.0160, "stat" : 0.0736, "syst" : 0.0067, "systcorr" : 0.0013},
    "5" : { "pt"  : [ 4.0, 7.0], "eta" : [3.7,4.5], "AP" : -0.0189, "stat" : 0.0158, "syst" : 0.0032, "systcorr" : 0.0013},
    "6" : { "pt"  : [ 4.0, 7.0], "eta" : [3.0,3.7], "AP" : -0.0311, "stat" : 0.0132, "syst" : 0.0014, "systcorr" : 0.0013},
    "7" : { "pt"  : [ 4.0, 7.0], "eta" : [2.5,3.0], "AP" :  0.0556, "stat" : 0.0254, "syst" : 0.0020, "systcorr" : 0.0013},
    "8" : { "pt"  : [ 7.0,12.0], "eta" : [3.7,4.5], "AP" : -0.0145, "stat" : 0.0205, "syst" : 0.0027, "systcorr" : 0.0013},
    "9" : { "pt"  : [ 7.0,12.0], "eta" : [3.0,3.7], "AP" : -0.0142, "stat" : 0.0111, "syst" : 0.0015, "systcorr" : 0.0013},
   "10" : { "pt"  : [ 7.0,12.0], "eta" : [2.5,3.0], "AP" : -0.0236, "stat" : 0.0138, "syst" : 0.0014, "systcorr" : 0.0013},
   "11" : { "pt"  : [ 7.0,12.0], "eta" : [2.2,2.5], "AP" : -0.0190, "stat" : 0.0348, "syst" : 0.0034, "systcorr" : 0.0013},
   "12" : { "pt"  : [12.0,30.0], "eta" : [3.7,4.5], "AP" : -0.0550, "stat" : 0.0473, "syst" : 0.0020, "systcorr" : 0.0013},
   "13" : { "pt"  : [12.0,30.0], "eta" : [3.0,3.7], "AP" :  0.0067, "stat" : 0.0180, "syst" : 0.0021, "systcorr" : 0.0013},
   "14" : { "pt"  : [12.0,30.0], "eta" : [2.5,3.0], "AP" :  0.0177, "stat" : 0.0162, "syst" : 0.0023, "systcorr" : 0.0013},
   "15" : { "pt"  : [12.0,30.0], "eta" : [2.0,2.5], "AP" : -0.0018, "stat" : 0.0236, "syst" : 0.0020, "systcorr" : 0.0013},
    "A" : { "pt"  : [ 0.2, 1.0], "eta" : [4.5,6.0], "AP" : -0.0391, "stat" : 0.0501, "syst" : 0.0016, "systcorr" : 0.0013},
    "B" : { "pt"  : [ 1.0, 2.2], "eta" : [5.2,6.0], "AP" :  0.0523, "stat" : 0.0684, "syst" : 0.0025, "systcorr" : 0.0013}
  },
  "Bs" : {
    "1" : { "pt"  : [ 2.0, 4.0], "eta" : [3.0,5.0], "AP" : -0.1475, "stat" : 0.0895, "syst" : 0.0192, "systcorr" : 0.0030},
    "2" : { "pt"  : [ 4.0, 8.0], "eta" : [3.5,4.5], "AP" : -0.0471, "stat" : 0.0513, "syst" : 0.0112, "systcorr" : 0.0030},
    "3" : { "pt"  : [ 4.0, 8.0], "eta" : [2.5,3.5], "AP" :  0.0376, "stat" : 0.0467, "syst" : 0.0083, "systcorr" : 0.0030},
    "4" : { "pt"  : [ 8.0,12.0], "eta" : [3.5,4.5], "AP" :  0.0582, "stat" : 0.0537, "syst" : 0.0053, "systcorr" : 0.0030},
    "5" : { "pt"  : [ 8.0,12.0], "eta" : [2.5,3.5], "AP" :  0.0370, "stat" : 0.0332, "syst" : 0.0051, "systcorr" : 0.0030},
    "6" : { "pt"  : [12.0,30.0], "eta" : [3.5,4.5], "AP" : -0.0339, "stat" : 0.0750, "syst" : 0.0095, "systcorr" : 0.0030},
    "7" : { "pt"  : [12.0,30.0], "eta" : [2.5,3.5], "AP" : -0.0333, "stat" : 0.0309, "syst" : 0.0040, "systcorr" : 0.0030},
    "8" : { "pt"  : [ 8.0,30.0], "eta" : [2.2,2.5], "AP" : -0.0351, "stat" : 0.0485, "syst" : 0.0059, "systcorr" : 0.0030}
  }
}

import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from ROOT import TFile, TTree, gPad, TH1F
from math import sqrt

def main(name_file,name_tree,branch_pt, branch_eta, branch_weight,meson_type,cuts = "1"):
  print cuts
  the_file = TFile(name_file,'READ')
  the_tree = the_file.Get(name_tree)

  #get dictionary
  the_bins = bins[meson_type]
  num_signal = 0.
  name_of_hist = ""
  # calculate number of events in bins
  for key, value in the_bins.iteritems():
    cut_string =  "("+cuts+")*"+branch_weight
    cut_string += "*("+branch_pt+">="+str(value["pt"][0]*1000)+"&&"+branch_pt+"<"+str(value["pt"][1]*1000)
    cut_string += "&&"+branch_eta+">="+str(value["eta"][0])+"&&"+branch_eta+"<"+str(value["eta"][1])+")"
    the_tree.Draw(branch_pt,cut_string)
    if gPad.GetPrimitive("hframe"):
      name_of_hist = "hframe"
    else:
      name_of_hist = "htemp"
    num_signal += gPad.GetPrimitive(name_of_hist).GetEffectiveEntries()


  AP_mean = 0.
  AP_err_stat = 0.  
  AP_err_syst = 0.
  AP_err_w = 0.
  AP_err_systcorr = 0.

  for key, value in the_bins.iteritems():
    cut_string =  "("+cuts+")*"+branch_weight
    cut_string += "*("+branch_pt+">="+str(value["pt"][0]*1000)+"&&"+branch_pt+"<"+str(value["pt"][1]*1000)
    cut_string += "&&"+branch_eta+">="+str(value["eta"][0])+"&&"+branch_eta+"<"+str(value["eta"][1])+")"
    the_tree.Draw(branch_pt,cut_string)
    if gPad.GetPrimitive("hframe"):
      name_of_hist = "hframe"
    else:
      name_of_hist = "htemp"
    frac = gPad.GetPrimitive(name_of_hist).GetEffectiveEntries() / num_signal
    frac_err = sqrt(frac*(1.-frac)/num_signal)
    AP_mean += frac * value["AP"]
    AP_err_stat += (frac*value["stat"])**2
    AP_err_syst += (frac*sqrt(value["syst"]**2 - value["systcorr"]**2))**2
    AP_err_w += (frac_err*value["AP"])**2
    AP_err_systcorr = value["systcorr"]**2
    print "bin ", key, " frac = ", frac, " +- ", frac_err, ", AP = ", value["AP"], " +- ", value["stat"], " (stat) +- ", value["syst"], " (syst)"


  print "AP = ", AP_mean, " +- ", sqrt(AP_err_stat+AP_err_w), " (stat) +- ", sqrt(AP_err_syst+AP_err_systcorr), " (syst)"



if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Calculate production asymmetry')
    parser.add_argument('--file'    , required = True,  help = 'Root TFile with TTree of events')
    parser.add_argument('--tree'    , required = True,  help = 'Root TTree path in the TFile')
    parser.add_argument('--meson'   , required = True,  help = "Meson type" , default = "Bd", choices = ["Bd","Bs"])
    parser.add_argument('--pT'      , required = True,  help = 'pT observable') # (in MeV/c)')
    parser.add_argument('--eta'     , required = True,  help = 'eta observable')
    parser.add_argument('--weight'  , required = False, help = 'Weight variable')
    parser.add_argument('--cuts'    , required = False, help = 'Additional cuts to be applied to the data set', default = "1")
    args = parser.parse_args()
    main(args.file, args.tree, args.pT, args.eta, args.weight, args.meson, args.cuts)

# cat $1.txt | awk '/./' | tail -n+2 | awk '
#  {
#    m+=$2*$4;
#    sstat+=($2*$5)**2;
#    ssyst+=($2*sqrt($6**2-$7**2))**2;
#    sw+=($3*$4)**2;
#    scorr=$7
#  }
#  END {
#    print "mean =", m
#    print "sigma_stat =",sqrt(sstat)
#    print "sigma_syst =",sqrt(ssyst**2+sw**2+scorr**2)
#  }
# '
 
 
 
 












