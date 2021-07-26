#!/bin/bash

RUN_NAME=MCProduction
INPUT_PATH=/fhgfs/groups/e5/lhcb/analysis/B2OC/B02DD/MC/Sim08/2012/
INPUT_FILE_NAME=MC_Sim08a_2012_Pythia8_B02DsDst_Stripping20_DVv36r6_20150512_fmeier_combined_TupleA.root
BASE_FILE_NAME=MC_Sim08a_2012_Pythia8_B02DsDst_Stripping20_DVv36r6_20150512_fmeier
DATE=20150512
PRODUCER=fmeier
echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

# echo ""
# echo "**TupleA** (flat)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleA.root"
# ArrayFlattenerGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleA.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FlattenTuple.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DsDst.log

AddCategoryGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_TupleA.root" B02DD catYear 2012 > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DsDst_yearcat.log
AddCategoryGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_Pythia_TupleA.root" B02DD catPythia 8 > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DsDst_yearcat_pythiacat.log
rm ${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_TupleA.root

echo ""
echo "**TupleAPlus** (common variables)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root"
B02DDVariablesGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_Pythia_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DsDst_vars.log

echo ""
echo "**Tuple B** (common variables, pre-selected)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DsDst_vars_tupleb_cuts.log

echo ""
echo "**Tuple B** (common variables, pre-selected, BDT selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_BDT_TupleB.root"
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_MC_B02DsDst_2012_P8_BDT.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DsDst_vars_tupleb_cuts_bdt.log

echo "finished!"