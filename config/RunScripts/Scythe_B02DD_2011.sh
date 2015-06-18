#!/bin/bash

RUN_NAME=Production
INPUT_PATH=/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/2011/
INPUT_FILE_NAME=DT2011_B02DD_Stripping21r1_DVv36r1_20150322_fmeier_combined_TupleA.root
BASE_FILE_NAME=DT2011_B02DD_Stripping21r1_DVv36r1_20150322_fmeier_combined
DATE=20150520
PRODUCER=fmeier

echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

echo ""
echo "**TupleAPlus** (common variables)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root"
B02DDVariablesGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_vars.log

echo ""
echo "**Tuple B** (common variables, pre-selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_vars_preselected.log

echo ""
echo "**Tuple B** (common variables, pre-selection, BDT selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_BDT_TupleB.root"
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_2011.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_vars_preselected_bdt.log

# echo ""
# echo "**Tuple B** (common variables, pre-selection, BDT selection, final selection)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_TupleB.root"
# MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_BDT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FinalSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_vars_preselected_bdt_finalselection.log

# echo ""
# echo "**Tuple B** (common variables, pre-selection, BDT selection, final selection, FT variables)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FT_TupleB.root"
# FlavourTaggingGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FT_TupleB.root" B02DD B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_vars_preselected_bdt_finalselection_ft.log

# echo ""
# echo "**Fit Tuple** (common variables, pre-selection, BDT selection, final selection, FT variables)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FitTuple.root"
# FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_vars_preselected_bdt_finalselection_ft_fittuple.log

echo "finished!"