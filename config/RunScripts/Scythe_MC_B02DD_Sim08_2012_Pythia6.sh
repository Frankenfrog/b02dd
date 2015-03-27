#!/bin/bash

RUN_NAME=MCProduction
INPUT_PATH=/fhgfs/groups/e5/lhcb/NTuples/B02DD/MC/Sim08/2012/
INPUT_FILE_NAME=MC_Sim08a_2012_Pythia6_B02DD_Stripping20_DVv36r1_20150325_fmeier_TupleA.root
BASE_FILE_NAME=MC_Sim08a_2012_Pythia6_B02DD_Stripping20_DVv36r1_20150325_fmeier
DATE=20150325
PRODUCER=fmeier
echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

#echo ""
#echo "**TupleA** (flat)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleA.root"
#ArrayFlattenerGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleA.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FlattenTuple.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD.log

# AddCategoryGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_TupleA.root" B02DD catYear 2012 > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_yearcat.log
# AddCategoryGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_Pythia_TupleA.root" B02DD catPythia 6 > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_yearcat_pythiacat.log
# rm ${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_TupleA.root

# echo ""
# echo "**TupleAPlus** (common variables)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root"
# B02DDVariablesGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_year_Pythia_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_vars.log

# echo ""
# echo "**Tuple B** (common variables, pre-selected)"
# echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root"
# MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_vars_tupleb_cuts.log

echo ""
echo "**Tuple B** (common variables, pre-selected, BDT selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_BDT_TupleB.root"
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_MC_2012_P6_BDT1.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_vars_tupleb_cuts_bdt1.log
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_MC_2012_P6_BDT2.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_vars_tupleb_cuts_bdt2.log
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_MC_2012_P6_BDT3.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_vars_tupleb_cuts_bdt3.log
TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_MC_2012_P6_BDT4.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_vars_tupleb_cuts_bdt4.log

#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_TupleB.root"
#MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/DetachedFlatCombinedSelection.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_Detached_vars_tupleb_cuts_selection.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_FT_TupleB.root"
#FlavourTaggingGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_Pythia_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_FT_TupleB.root" B02DD B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_Detached_vars_tupleb_cuts_selection_ft.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_TupleB.root"
#CandidateSelectionGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_FT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_TupleB.root" B02DD "idxRandom" > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_Detached_vars_tupleb_cuts_selection_ft_random.log
#
#echo ""
#echo "**Fit Tuple** (flat, common variables, mass and time cuts, only used trigger lines, offline selection applied, Pythia category, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_FitTuple.root"
#FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_Detached_vars_tupleb_cuts_selection_ft_random_fittuple.log
#
#echo ""
#echo "**Fit Tuple** (flat, mass and time cuts, only used trigger lines, preselection applied, random candidate selection, equally filled time bins included)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_cats_FitTuple.root"
#VariableCategorizerGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_FitTuple.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_combined_selected_random_cats_FitTuple.root" B02DD /home/fmeier/git/b02dd/config/Reducer/ComputePropertimeQuantilesOnFitTupleDetached.cfg > scythe_${RUN_NAME}_${DATE}_Sim08a_2012_Pythia6_B02DD_Detached_vars_tupleb_cuts_selection_ft_random_fittuple_catvars.log

echo "finished!"