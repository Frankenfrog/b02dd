from ROOT import gROOT, TNtuple, TFile, TH1F, TH2F, TCanvas, TMath, TRandom3, gStyle, gSystem, RooRealVar

gSystem.Load("/home/fmeier/cmtuser/Urania_v2r4/Phys/Meerkat/lib/libMeerkat.so")

from ROOT import OneDimPhaseSpace, CombinedPhaseSpace, BinnedDensity

import argparse

parser = argparse.ArgumentParser(description='PIDGen')
parser.add_argument('-i', type=str, default = "histsim12.root", 
                    help='Input file name')
parser.add_argument('-t', type=str, default = "lb2lch_filt", 
                    help='Input tree name')
parser.add_argument('-o', type=str, default = "fakepid.root", 
                    help='Output file name')
parser.add_argument('-p', type=str, default = "lp_prp_gen", 
                    help='PID variable')
parser.add_argument('-m', type=str, default = "lp_pt", 
                    help='Pt variable')
parser.add_argument('-e', type=str, default = "lp_eta", 
                    help='Eta variable')
parser.add_argument('-n', type=str, default = "ntracks", 
                    help='Ntracks variable')
parser.add_argument('-c', type=str, default = "pidmometantr.root", 
                    help='Calibration file name')
parser.add_argument('-l', type=float, default = 0.0, 
                    help='Lower PID value to generate')
parser.add_argument('-switch', action="store_true", 
                    help='Switch PID value if you want different hypothesis')

parser.print_help()
args = parser.parse_args()

print args

infilename = args.i
intree = args.t
outfilename = args.o
pidvar = args.p
ptvar = args.m
etavar = args.e
ntrvar = args.n
calibfilename = args.c
minpid = args.l
switchpid = args.switch

from math import sqrt

minpid = 1.-sqrt(1.-minpid)

pid_phsp = OneDimPhaseSpace("PIDPhsp", 0. , 1. )
mom_phsp = OneDimPhaseSpace("MomPhsp", 5.5 , 9.5)
eta_phsp = OneDimPhaseSpace("EtaPhsp", 1.5, 5.5)
ntr_phsp = OneDimPhaseSpace("NtrPhsp", 3.0, 6.5)
pidmom_phsp = CombinedPhaseSpace("PIDMomPhsp", pid_phsp, mom_phsp) 
pidmometa_phsp = CombinedPhaseSpace("PIDMomEtaPhsp", pidmom_phsp, eta_phsp) 
phsp = CombinedPhaseSpace("FullPhsp", pidmometa_phsp, ntr_phsp) 

infile = TFile.Open(infilename)
tree = infile.Get(intree) 
if not tree :  
  print "Ntuple not found!"
  quit()

kde = BinnedDensity("KDEPDF", phsp, calibfilename)
nentries = tree.GetEntries()

gROOT.ProcessLine("struct MyStruct { \
  Double_t newpid; \
}")
from ROOT import MyStruct, AddressOf

s = MyStruct()

outfile = TFile.Open(outfilename, "RECREATE")
newtree = tree.CloneTree(0)
newtree.Branch(pidvar, AddressOf(s, "newpid"), pidvar + "/D")
infile.cd() 

h = TH1F("h", "h", 100, minpid, 1.) 
rnd = TRandom3()

from ROOT import std, Double
from math import log

n = 0
for i in tree : 
  point = std.vector(Double)(4) 
  point[0] = 0.5
  point[1] = log(eval("i." + ptvar))
  point[2] = eval("i." + etavar)
  point[3] = log(float(eval("i." + ntrvar))) 

  h.Reset() 
  kde.slice(point, 0, h, False) 

  if h.Integral() > 0 : 
    pid = h.GetRandom()
  else : 
    pid = minpid + (1.-minpid)*rnd.Rndm()

  if switchpid :
    s.newpid = (1.-pid)*(1.-pid)
  else :
    s.newpid = (1.-(1.-pid)*(1.-pid))

  newtree.Fill() 

  if (n % 1000 == 0) : 
    print "Event %d/%d : Pt=%f, Eta=%f, Ntr=%d, PIDGen=%f" % \
       (n, nentries, eval("i." + ptvar), eval("i." + etavar), eval("i." + ntrvar), \
        s.newpid)

  n += 1

outfile.cd() 
newtree.Write() 
infile.Close() 
outfile.Close() 
