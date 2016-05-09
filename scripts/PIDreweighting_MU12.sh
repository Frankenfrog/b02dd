#!/bin/bash

# Location of calibrated PID PDFs
EOSDIRKAON=root://eoslhcb.cern.ch//eos/lhcb/user/p/poluekt/PID/ProbNNK/
EOSDIRPION=root://eoslhcb.cern.ch//eos/lhcb/user/p/poluekt/PID/ProbNNpi/

# Location of the simulated ROOT file
INPUTFILE=/fhgfs/groups/e5/lhcb/NTuples/B02DD/PIDAnton/MC_Sim08g_2012_Pythia8_B02DD_CPV_Stripping21_DVv36r6_20160316_fmeier_TupleC_Kpipi_incl50_ForBDT_MagUp.root

# Name of the tree in the ROOT file
INPUTTREE=B02DD

# Name of the output file
OUTFILE=/fhgfs/groups/e5/lhcb/NTuples/B02DD/PIDAnton/MC_Sim08g_2012_Pythia8_B02DD_CPV_Stripping21_DVv36r6_20160316_fmeier_TupleC_Kpipi_incl50_ForBDT_MagUp_Calib_corrected.root

python /home/fmeier/git/b02dd/scripts/PIDGen.py -i $INPUTFILE -t $INPUTTREE -o /tmp/tmp1_MU12.root -p varKminus_ProbNNk_rew -m B0_FitPVConst_Dplus_P2_PT_flat -e Dplus_Kminus_or_piminus_ETA -n catNTrack_corrected -l 0 -c $EOSDIRKAON/K_MagUp_2012_distrib.root
python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp1_MU12.root -t $INPUTTREE -o /tmp/tmp2_MU12.root -p varKplus_ProbNNk_rew -m B0_FitPVConst_Dminus_P2_PT_flat -e Dminus_Kplus_or_piplus_ETA -n catNTrack_corrected -l 0 -c $EOSDIRKAON/K_MagUp_2012_distrib.root
rm /tmp/tmp1_MU12.root
python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp2_MU12.root -t $INPUTTREE -o /tmp/tmp3_MU12.root -p varPiOneplus_ProbNNpi_rew -m B0_FitPVConst_Dplus_P0_PT_flat -e Dplus_piplus_or_Kplus_One_ETA -n catNTrack_corrected -l 0 -c $EOSDIRPION/Pi_MagUp_2012_distrib.root
rm /tmp/tmp2_MU12.root
python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp3_MU12.root -t $INPUTTREE -o /tmp/tmp4_MU12.root -p varPiTwoplus_ProbNNpi_rew -m B0_FitPVConst_Dplus_P1_PT_flat -e Dplus_piplus_or_Kplus_Two_ETA -n catNTrack_corrected -l 0 -c $EOSDIRPION/Pi_MagUp_2012_distrib.root
rm /tmp/tmp3_MU12.root
python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp4_MU12.root -t $INPUTTREE -o /tmp/tmp5_MU12.root -p varPiOneminus_ProbNNpi_rew -m B0_FitPVConst_Dminus_P0_PT_flat -e Dminus_piminus_or_Kminus_One_ETA -n catNTrack_corrected -l 0 -c $EOSDIRPION/Pi_MagUp_2012_distrib.root
rm /tmp/tmp4_MU12.root
python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp5_MU12.root -t $INPUTTREE -o $OUTFILE -p varPiTwominus_ProbNNpi_rew -m B0_FitPVConst_Dminus_P1_PT_flat -e Dminus_piminus_or_Kminus_Two_ETA -n catNTrack_corrected -l 0 -c $EOSDIRPION/Pi_MagUp_2012_distrib.root
# python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp5_MU12.root -t $INPUTTREE -o /tmp/tmp6_MU12.root -p varPiTwominus_ProbNNpi_rew -m B0_FitPVConst_Dminus_P1_PT_flat -e Dminus_piminus_or_Kminus_Two_ETA -n catNTrack_corrected -l 0 -c $EOSDIRPION/Pi_MagUp_2012_distrib.root
rm /tmp/tmp5_MU12.root

# python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp6_MU12.root -t $INPUTTREE -o /tmp/tmp7_MU12.root -p varKminus_ProbNNpi_rew -switch -m B0_FitPVConst_Dplus_P2_PT_flat -e Dplus_Kminus_or_piminus_ETA -n catNTrack_corrected -l 0 -c $EOSDIRPION/Pi_MagUp_2012_distrib.root
# rm /tmp/tmp6_MU12.root
# python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp7_MU12.root -t $INPUTTREE -o /tmp/tmp8_MU12.root -p varKplus_ProbNNpi_rew -switch -m B0_FitPVConst_Dminus_P2_PT_flat -e Dminus_Kplus_or_piplus_ETA -n catNTrack_corrected -l 0 -c $EOSDIRPION/Pi_MagUp_2012_distrib.root
# rm /tmp/tmp7_MU12.root
# python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp8_MU12.root -t $INPUTTREE -o /tmp/tmp9_MU12.root -p varPiOneplus_ProbNNk_rew -switch -m B0_FitPVConst_Dplus_P0_PT_flat -e Dplus_piplus_or_Kplus_One_ETA -n catNTrack_corrected -l 0 -c $EOSDIRKAON/K_MagUp_2012_distrib.root
# rm /tmp/tmp8_MU12.root
# python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp9_MU12.root -t $INPUTTREE -o /tmp/tmp10_MU12.root -p varPiTwoplus_ProbNNk_rew -switch -m B0_FitPVConst_Dplus_P1_PT_flat -e Dplus_piplus_or_Kplus_Two_ETA -n catNTrack_corrected -l 0 -c $EOSDIRKAON/K_MagUp_2012_distrib.root
# rm /tmp/tmp9_MU12.root
# python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp10_MU12.root -t $INPUTTREE -o /tmp/tmp11_MU12.root -p varPiOneminus_ProbNNk_rew -switch -m B0_FitPVConst_Dminus_P0_PT_flat -e Dminus_piminus_or_Kminus_One_ETA -n catNTrack_corrected -l 0 -c $EOSDIRKAON/K_MagUp_2012_distrib.root
# rm /tmp/tmp10_MU12.root
# python /home/fmeier/git/b02dd/scripts/PIDGen.py -i /tmp/tmp11_MU12.root -t $INPUTTREE -o $OUTFILE -p varPiTwominus_ProbNNk_rew -switch -m B0_FitPVConst_Dminus_P1_PT_flat -e Dminus_piminus_or_Kminus_Two_ETA -n catNTrack_corrected -l 0 -c $EOSDIRKAON/K_MagUp_2012_distrib.root
# rm /tmp/tmp11_MU12.root