#!/bin/bash

# Location of calibrated PID PDFs
EOSDIRKAON=root://eoslhcb.cern.ch//eos/lhcb/user/p/poluekt/PID/ProbNNK/
EOSDIRPION=root://eoslhcb.cern.ch//eos/lhcb/user/p/poluekt/PID/ProbNNpi/

# Location of the simulated ROOT file
INPUTFILE=/fhgfs/groups/e5/lhcb/NTuples/B02DD/PIDAnton/MC_Sim08g_2011_Pythia8_B02DD_CPV_Stripping21r1_DVv36r6_20160316_fmeier_TupleC_Kpipi_incl50_ForBDT_MagUp.root

# Name of the tree in the ROOT file
INPUTTREE=B02DD

# Name of the output file
OUTFILE=/fhgfs/groups/e5/lhcb/NTuples/B02DD/PIDAnton/MC_Sim08g_2011_Pythia8_B02DD_CPV_Stripping21r1_DVv36r6_20160316_fmeier_TupleC_Kpipi_incl50_ForBDT_MagUp_Calib.root

python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i $INPUTFILE -t $INPUTTREE -o /tmp/tmp1.root -p varKminus_ProbNNk_rew -m B0_FitPVConst_Dplus_P2_PT_flat -e Dplus_Kminus_or_piminus_ETA -n catNTrack -l 0 -c $EOSDIRKAON/K_MagUp_2011_distrib.root
python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp1.root -t $INPUTTREE -o /tmp/tmp2.root -p varKminus_ProbNNpi_rew -m B0_FitPVConst_Dplus_P2_PT_flat -e Dplus_Kminus_or_piminus_ETA -n catNTrack -l 0 -c $EOSDIRPION/Pi_MagUp_2011_distrib.root
rm /tmp/tmp1.root
python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp2.root -t $INPUTTREE -o /tmp/tmp3.root -p varKplus_ProbNNk_rew -m B0_FitPVConst_Dminus_P2_PT_flat -e Dminus_Kplus_or_piplus_ETA -n catNTrack -l 0 -c $EOSDIRKAON/K_MagUp_2011_distrib.root
rm /tmp/tmp2.root
python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp3.root -t $INPUTTREE -o /tmp/tmp4.root -p varKplus_ProbNNpi_rew -m B0_FitPVConst_Dminus_P2_PT_flat -e Dminus_Kplus_or_piplus_ETA -n catNTrack -l 0 -c $EOSDIRPION/Pi_MagUp_2011_distrib.root
rm /tmp/tmp3.root

python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp4.root -t $INPUTTREE -o /tmp/tmp5.root -p varPiOneplus_ProbNNk_rew -m B0_FitPVConst_Dplus_P0_PT_flat -e Dplus_piplus_or_Kplus_One_ETA -n catNTrack -l 0 -c $EOSDIRKAON/K_MagUp_2011_distrib.root
rm /tmp/tmp4.root
python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp5.root -t $INPUTTREE -o /tmp/tmp6.root -p varPiOneplus_ProbNNpi_rew -m B0_FitPVConst_Dplus_P0_PT_flat -e Dplus_piplus_or_Kplus_One_ETA -n catNTrack -l 0 -c $EOSDIRPION/Pi_MagUp_2011_distrib.root
rm /tmp/tmp5.root

python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp6.root -t $INPUTTREE -o /tmp/tmp7.root -p varPiTwoplus_ProbNNk_rew -m B0_FitPVConst_Dplus_P1_PT_flat -e Dplus_piplus_or_Kplus_Two_ETA -n catNTrack -l 0 -c $EOSDIRKAON/K_MagUp_2011_distrib.root
rm /tmp/tmp6.root
python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp7.root -t $INPUTTREE -o /tmp/tmp8.root -p varPiTwoplus_ProbNNpi_rew -m B0_FitPVConst_Dplus_P1_PT_flat -e Dplus_piplus_or_Kplus_Two_ETA -n catNTrack -l 0 -c $EOSDIRPION/Pi_MagUp_2011_distrib.root
rm /tmp/tmp7.root

python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp8.root -t $INPUTTREE -o /tmp/tmp9.root -p varPiOneminus_ProbNNk_rew -m B0_FitPVConst_Dminus_P0_PT_flat -e Dminus_piminus_or_Kminus_One_ETA -n catNTrack -l 0 -c $EOSDIRKAON/K_MagUp_2011_distrib.root
rm /tmp/tmp8.root
python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp9.root -t $INPUTTREE -o /tmp/tmp10.root -p varPiOneminus_ProbNNpi_rew -m B0_FitPVConst_Dminus_P0_PT_flat -e Dminus_piminus_or_Kminus_One_ETA -n catNTrack -l 0 -c $EOSDIRPION/Pi_MagUp_2011_distrib.root
rm /tmp/tmp9.root

python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp10.root -t $INPUTTREE -o /tmp/tmp11.root -p varPiTwoplus_ProbNNk_rew -m B0_FitPVConst_Dminus_P1_PT_flat -e Dminus_piminus_or_Kminus_Two_ETA -n catNTrack -l 0 -c $EOSDIRKAON/K_MagUp_2011_distrib.root
rm /tmp/tmp10.root
python /home/fmeier/cmtuser/Urania_v2r4/Phys/PIDGen/user/PIDGen.py -i /tmp/tmp11.root -t $INPUTTREE -o $OUTFILE -p varPiTwoplus_ProbNNpi_rew -m B0_FitPVConst_Dminus_P1_PT_flat -e Dminus_piminus_or_Kminus_Two_ETA -n catNTrack -l 0 -c $EOSDIRPION/Pi_MagUp_2011_distrib.root
rm /tmp/tmp11.root