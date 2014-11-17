#!/bin/bash

RUN_NAME=Production
INPUT_PATH=/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/2011/
INPUT_FILE_NAME=DT2011_B02DD_Stripping20r1_DVv35r1_20141102_fmeier_TupleA.root
BASE_FILE_NAME=DT2011_B02DD_Stripping20r1_DVv35r1_20141102_fmeier
DATE=20141107
PRODUCER=fmeier
echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

echo ""
echo "**TupleA** (flat)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleA.root"
ArrayFlattenerGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleA.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FlattenTuple.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat.log

echo ""
echo "**TupleAPlus** (flat, common variables)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleAPlus.root"
B02DDVariablesGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars.log

echo ""
echo "**Tuple B** (flat, common variables, sanity cuts)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleB.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_tupleb_cuts.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_TupleB.root"
#MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/DetachedFlatCombinedSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_tupleb_cuts_selection.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, FT variables)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_FT_TupleB.root"
#FlavourTaggingGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_FT_TupleB.root" B02DD B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_tupleb_cuts_selection_ft.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root"
#CandidateSelectionGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_FT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root" B02DD "idxRandom" > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_tupleb_cuts_selection_ft_random.log
#
#echo ""
#echo "**Fit Tuple** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_FitTuple.root"
#FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_tupleb_cuts_selection_ft_random_fittuple.log
#
#echo ""
#echo "**Fit Tuple** (flat, mass and time cuts, only used trigger lines, preselection applied, random candidate selection, equally filled time bins included)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_cats_FitTuple.root"
#VariableCategorizerGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_FitTuple.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_cats_FitTuple.root" B02DD /home/fmeier/git/b02dd/config/Reducer/ComputePropertimeQuantilesOnFitTupleDetached.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_tupleb_cuts_selection_ft_random_fittuple_catvars.log

echo "finished!"