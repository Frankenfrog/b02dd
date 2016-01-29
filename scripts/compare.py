#! /usr/bin/env python

import os
import argparse, ConfigParser


def main():
    parser = argparse.ArgumentParser(description='compares two distributions by plotting them normalised')
    parser.add_argument('--Configfile','-f', help='file name')
    args = parser.parse_args()
    
    config = ConfigParser.RawConfigParser()
    config.read(args.Configfile)

    # find inputs
    sections_all = config.sections()
    
    
    print(sections_all)
    
    #sections_input = sections_all.

if __name__ == "__main__":
    main()

def old_stuff():
file1_name = config.get('input_data1','file')
tree1_name = config.get('input_data1','tree')
var2compare1_name = config.get('input_data_1','var2compare')
weightVar1_name = config.get('input_data_1','weightVar')
cut1 = config.get('input_data_1','cut')

file2_name = config.get('input_data_2','file')
tree2_name = config.get('input_data_2','tree')
var2compare2_name = config.get('input_data_2','var2compare')
weightVar2_name = config.get('input_data_2','weightVar')
cut2 = config.get('input_data_2','cut')

import numpy, math
import re
import ROOT
from ROOT import TFile, TTree, TCanvas, TH1D, TLatex, TLegend
from ROOT import RooRealVar, RooDataSet, RooArgSet, RooArgList
import style
style.setLHCbStyle()

canv = TCanvas("canv","canv",1600,1200)

pad = canv.cd();
pad.SetPad(0.02,0,0.98,0.98);
pad.SetLeftMargin(0.16);
pad.SetRightMargin(0.09);
pad.SetBottomMargin(0.16);

normbinwidth = (config.getfloat('plot','range_high')-config.getfloat('plot','range_low'))/config.getint('plot','binning_data1')
if normbinwidth<1:
    normbinwidth = round(normbinwidth,3)
elif normbinwidth<10:
    normbinwidth = round(normbinwidth,2)
elif normbinwidth<100:
    normbinwidth = round(normbinwidth,1)
else:
    normbinwidth = round(normbinwidth,0)

if math.log10(normbinwidth) < 0: 
    yaxis_title_number = '%.3f' %normbinwidth # taking the digit before the comma, the comma itself and three behind it
elif math.log10(normbinwidth)<1: 
    yaxis_title_number = '%.2f' %normbinwidth # taking the digit before the comma, the comma itself and two behind it
elif math.log10(normbinwidth)<2:
    yaxis_title_number = '%.1f' %normbinwidth # taking the digits before the comma, the comma itself and one behind it
else:
    yaxis_title_number = '%.0f' %normbinwidth

file1 = TFile(file1_name,"READ")
tree1 = file1.Get(tree1_name)

import re 
tree1.SetBranchStatus("*",0)
tree1.SetBranchStatus(re.sub(r'\[[^)]*\]', '', var2compare1_name),1)

var_list1 = re.split("[><=!&|)(]",cut1)
from itertools import ifilterfalse
var_list1 = list(ifilterfalse(lambda var:var=='' or var.isdigit() or re.match("^[+-]?\d(>?\.\d+)?$",var) != None,var_list1))
var_list1 = list(set(var_list1))

for var in var_list1:
    tree1.SetBranchStatus(var,1)

if weightVar1_name != "" and cut1 == "":
    cut1_complete = weightVar1_name
    tree1.SetBranchStatus(weightVar1_name,1)
elif weightVar1_name != "":
    tree1.SetBranchStatus(weightVar1_name,1)
    cut1_complete = "("+cut1+")*"+weightVar1_name
else: 
    cut1_complete = cut1

histo1 = TH1D("histo1","histo1",config.getint('plot','binning_data1'),config.getfloat('plot','range_low'),config.getfloat('plot','range_high'))
tree1.Draw(var2compare1_name+">>histo1",cut1_complete)
norm_1_sig = histo1.GetSumOfWeights()
histo1.Scale(1/norm_1_sig)
# histo1.Sumw2() # gives warning 'RuntimeWarning: Sum of squares of weights structure already created' - probably not needed
histo1.SetLineColor(config.getint('plot','lineColor_firstdistribution'));
histo1.SetMarkerColor(config.getint('plot','markerColor_firstdistribution'));
XaxisTitle = config.get('plot','x_axis_title') + " (" + config.get('plot','x_axis_unit') +")"
if config.get('plot','x_axis_unit') == "":
    XaxisTitle = config.get('plot','x_axis_title')
histo1.GetXaxis().SetTitle(XaxisTitle)
YaxisTitle  = "Candidates / (" + yaxis_title_number + " " + config.get('plot','x_axis_unit') + ")"
if config.get('plot','x_axis_unit') == "":
    YaxisTitle  = "Candidates / (" + yaxis_title_number + ")"
histo1.GetYaxis().SetTitle(YaxisTitle) 
histo1.GetYaxis().SetTitleOffset(1.2)
histo1.SetLabelSize(0.06,"y")
histo1.SetTitleSize(0.066,"y")

######################################################################################################################################################

file2 = TFile(file2_name,"READ")
tree2 = file2.Get(tree2_name)

tree2.SetBranchStatus("*",0)
tree2.SetBranchStatus(re.sub(r'\[[^)]*\]', '', var2compare2_name),1)

var_list2 = re.split("[><=!&|)(]",cut2)
var_list2 = list(ifilterfalse(lambda var:var=='' or var.isdigit() or re.match("^[+-]?\d(>?\.\d+)?$",var) != None,var_list2))
var_list2 = list(set(var_list2))

for var in var_list2:
    tree2.SetBranchStatus(var,1)

if weightVar2_name != "" and cut2 == "":
    cut2_complete = weightVar2_name
    tree2.SetBranchStatus(weightVar2_name,1)
elif weightVar2_name != "":
    tree2.SetBranchStatus(weightVar2_name,1)
    cut2_complete = "("+cut2+")*"+weightVar2_name
else: 
    cut2_complete = cut2

histo2 = TH1D("histo2","histo2",config.getint('plot','binning_data2'),config.getfloat('plot','range_low'),config.getfloat('plot','range_high'))
tree2.Draw(var2compare2_name+">>histo2",cut2_complete)
norm_2_sig = histo2.GetSumOfWeights()
histo2.Scale(1/norm_2_sig)
# histo2.Sumw2() # gives warning 'RuntimeWarning: Sum of squares of weights structure already created' - probably not needed
histo2.SetLineColor(config.getint('plot','lineColor_seconddistribution'))
histo2.SetMarkerColor(config.getint('plot','markerColor_seconddistribution'))
histo2.GetXaxis().SetTitle(XaxisTitle)
histo2.GetYaxis().SetTitle(YaxisTitle) 
histo2.GetYaxis().SetTitleOffset(1.2)
histo2.SetLabelSize(0.06,"y")
histo2.SetTitleSize(0.066,"y")

if histo2.GetBinContent(histo2.GetMaximumBin()) > histo1.GetBinContent(histo1.GetMaximumBin()):
    histo2.Draw()
    histo1.Draw("SAME")
    if config.getboolean('plot','plot_twice'):
        histo2.Draw("SAME")
else:
    histo1.Draw()
    histo2.Draw("SAME")
    if config.getboolean('plot','plot_twice'):
        histo1.Draw("SAME")

label_x = 0.65
label_y = 0.88
label_base = TLatex(0,0,config.get('plot','label'))
xsize = label_base.GetXsize()
if xsize > 0.25:
    label_x = 0.65 - (max(0.0, xsize-0.25)*0.8)

label = TLatex(label_x, label_y, config.get('plot','label'));
label.SetTextSize(0.05)
label.SetNDC()
label.Draw()

leg = TLegend(0.6,0.75,0.9,0.85);
leg.AddEntry(histo1,config.get('plot','legend_data1'),"ep");
leg.AddEntry(histo2,config.get('plot','legend_data2'),"ep");
leg.SetTextFont(132);
leg.SetEntrySeparation(0.1);
leg.Draw();

if not os.path.exists(config.get('plot','directory')):
    os.makedirs(config.get('plot','directory'))

if config.get('plot','directory').endswith('/'):
    save_dir = config.get('plot','directory') + config.get('plot','name') 
else:
    save_dir = config.get('plot','directory') + '/' + config.get('plot','name') 

canv.SaveAs(save_dir + '.pdf')
canv.SaveAs(save_dir + '.tex')

ratio = TH1D(histo1)
ratio.Divide(histo2)
ratio.SetLineColor(1)
ratio.SetMarkerColor(1)
ratio.GetXaxis().SetTitle(XaxisTitle)
ratioyaxis = "(" + config.get('plot','legend_data1') + ") / (" + config.get('plot','legend_data2') + ")"
ratio.GetYaxis().SetTitle(ratioyaxis)
ratio.SetMaximum(4.5) # a bit ugly to set it hardcoded independent of everything, but it is somehow expected to get a ratio around 1
ratio.SetMinimum(-2.5)
ratio.Draw()

label.Draw()

if config.get('plot','directory').endswith('/'):
    save_dir = config.get('plot','directory') + "Ratio" 
else:
    save_dir = config.get('plot','directory') + '/' + "Ratio" 

canv.SaveAs(save_dir + '.pdf')
canv.SaveAs(save_dir + '.tex')
