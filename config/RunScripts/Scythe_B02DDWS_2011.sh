#!/bin/bash

RUN_NAME=Production
INPUT_PATH=/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/2011/
INPUT_FILE_NAME=DT2011_B02DDWS_Stripping21r1_DVv36r1_20150501_fmeier_combined_TupleA.root
BASE_FILE_NAME=DT2011_B02DDWS_Stripping21r1_DVv36r1_20150501_fmeier_combined
DATE=20150504
PRODUCER=fmeier

echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

# echo ""
# echo "**TupleAPlus** (common variables)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root"
# B02DDWSVariablesGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DDWS_vars.log

# echo ""
# echo "**Tuple B** (common variables, pre-selection)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root"
# MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DDWS_vars_preselected.log

echo ""
echo "**Tuple B** (common variables, pre-selection, BDT selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_BDT_TupleB.root"
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_WS_2011.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DDWS_vars_preselected_bdt.log

echo "finished!"