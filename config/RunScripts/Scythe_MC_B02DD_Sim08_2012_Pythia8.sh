#!/bin/bash

RUN_NAME=MCProduction
INPUT_PATH=/fhgfs/groups/e5/lhcb/NTuples/B02DD/MC/Sim08/2012/
INPUT_FILE_NAME=MC_Sim08a_2012_Pythia8_B02DD_Stripping20_DVv35r1_20141104_fmeier_TupleA.root
BASE_FILE_NAME=MC_Sim08a_2012_Pythia8_B02DD_Stripping20_DVv35r1_20141104_fmeier
DATE=20141110
PRODUCER=fmeier
echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

echo ""
echo "**TupleA** (flat)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleA.root"
ArrayFlattenerGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleA.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FlattenTuple.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_flat.log

AddCategoryGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_year_TupleA.root" B02DD catYear 2012 > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_flat_yearcat.log

echo ""
echo "**TupleAPlus** (flat, common variables)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleAPlus.root"
B02DDVariablesGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_year_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_flat_vars.log

echo ""
echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleB.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_flat_vars_tupleb_cuts.log

#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_TupleB.root"
#MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/DetachedFlatCombinedSelection.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_Pythia_TupleB.root"
#AddCategoryGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_Pythia_TupleB.root" B02DD catPythia 8 > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_pythiacat.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_FT_TupleB.root"
#FlavourTaggingGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_Pythia_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_FT_TupleB.root" B02DD B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root"
#CandidateSelectionGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_FT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root" B02DD "idxRandom" > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables, splitted into downstream and long track)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_TupleB.root"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_TupleB.root"
#SingleCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_TupleB.root" B02DD "catTrackType==55" > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_downstream.log
#SingleCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_TupleB.root" B02DD "catTrackType==33" > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_longtrack.log
#
#echo ""
#echo "**Fit Tuple** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_FitTuple.root"
#FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_fittuple.log
#
#echo ""
#echo "**Fit Tuple** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables, random candidate selection, splitted into downstream and long track)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_FitTuple.root"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_FitTuple.root"
#FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_downstream_fittuple.log
#FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_longtrack_fittuple.log
#
#echo ""
#echo "**Fit Tuple** (flat, mass and time cuts, only used trigger lines, preselection applied, random candidate selection, splitted into downstream and long track, equally filled time bins included)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_cats_FitTuple.root"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_cats_FitTuple.root"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_cats_FitTuple.root"
#VariableCategorizerGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_FitTuple.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_selected_random_cats_FitTuple.root" B02DD /home/fmeier/git/b02dd/config/Reducer/ComputePropertimeQuantilesOnFitTupleDetached.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_fittuple_catvars.log
#VariableCategorizerGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_FitTuple.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_downstream_selected_random_cats_FitTuple.root" B02DD /home/fmeier/git/b02dd/config/Reducer/ComputePropertimeQuantilesOnFitTupleDetached.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_downstream_fittuple_catvars.log
#VariableCategorizerGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_FitTuple.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_longtrack_selected_random_cats_FitTuple.root" B02DD /home/fmeier/git/b02dd/config/Reducer/ComputePropertimeQuantilesOnFitTupleDetached.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia8_B02DD_Detached_flat_vars_tupleb_cuts_selection_ft_random_longtrack_fittuple_catvars.log

echo "finished!"