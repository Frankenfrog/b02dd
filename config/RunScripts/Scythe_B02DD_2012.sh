#!/bin/bash

RUN_NAME=Production
INPUT_PATH=/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/2012/
INPUT_FILE_NAME=DT2012_B02DD_Stripping21_DVv36r5_20150909_pseyfert_combined_TupleA_kkpikpipi_reduced.root
BASE_FILE_NAME=DT2012_B02DD_Stripping21_DVv36r5_20150909_pseyfert_combined_kkpikpipi
DATE=20150917
PRODUCER=fmeier

echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

echo ""
echo "**TupleAPlus** (common variables)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root"
B02DDVariablesGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars.log

echo ""
echo "**Tuple B** (common variables, pre-selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars_preselected.log

echo ""
echo "**Tuple C** (common variables, pre-selection, vetos + PID cuts)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleC.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleC.root" B02DD /home/fmeier/git/b02dd/config/Reducer/MassVetos.cfg > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars_preselected_massvetos.log

echo ""
echo "**Tuple CPlus** (common variables, pre-selection, vetos + PID cuts, BDT selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleCPlus.root"
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_2012.cfg > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars_preselected_massvetos_bdt.log

echo ""
echo "**Tuple D** (common variables, pre-selection, vetos + PID cuts, BDT selection applied, final selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleD.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleCPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleD.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FinalSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars_preselected_massvetos_bdt_finalselection.log

echo ""
echo "**Tuple DPlus** (common variables, pre-selection, vetos + PID cuts, BDT selection applied, final selection, FT variables)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleDPlus.root"
B02DDFlavourTaggingGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleD.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleDPlus.root" > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars_preselected_massvetos_bdt_finalselection_ft.log

echo ""
echo "**Tuple E** (common variables, pre-selection, vetos + PID cuts, BDT selection applied, final selection, FT variables, random candidate selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleE.root"
CandidateSelectionGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleDplus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleE.root" B02DD "idxRandom" > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars_preselected_bdt_finalselection_ft_random.log

# echo ""
# echo "**Fit Tuple** (common variables, pre-selection, BDT selection, final selection, FT variables)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FitTuple.root"
# FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_selected_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2012_B02DD_vars_preselected_bdt_finalselection_ft_fittuple.log

echo "finished!"