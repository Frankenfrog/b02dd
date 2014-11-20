#!/bin/bash

RUN_NAME=Production
INPUT_PATH=/fhgfs/groups/e5/lhcb/NTuples/B02DD/Data/2011/
INPUT_FILE_NAME=DT2011_B02DD_Stripping20r1_DVv35r1_20141102_fmeier_TupleA.root
BASE_FILE_NAME=DT2011_B02DD_Stripping20r1_DVv35r1_20141102_fmeier
DATE=20141120
PRODUCER=fmeier

echo "Starting Scythe ${RUN_NAME}..."

echo "using input file: ${INPUT_PATH}${INPUT_FILE_NAME}"
echo "starting reducers..."

#echo ""
#echo "**TupleA** (flat)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_combined_TupleA.root"
#ArrayFlattenerGrimReaper "${INPUT_PATH}${INPUT_FILE_NAME}" B02DD/DecayTree "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_TupleA.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FlattenTuple.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat.log
#
echo ""
echo "**TupleAPlus** (flat, common variables)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_TupleAPlus.root"
B02DDVariablesGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_TupleA.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_TupleAPlus.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars.log

echo ""
echo "**Tuple B** (flat, common variables, pre-selection)"
echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_TupleB.root"
MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_TupleAPlus.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/PreSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, pre-selection, BDT selection of Dplus and Dminus)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_BDT_TupleB.root"
#TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_Dplus.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected_bdtDplus.log
#TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_Dminus.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected_bdtDminus.log
#TMVAGrimReaper /home/fmeier/git/b02dd/config/Reducer/TMVAGrimReaper_DD.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected_bdtDD.log

#echo ""
#echo "**Tuple B** (flat, common variables, pre-selection, BDT selection of Dplus and Dminus, final selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_TupleB.root"
#MultiCutGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_BDT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_TupleB.root" B02DD /home/fmeier/git/b02dd/config/Reducer/FinalSelection.cfg > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected_finalselection.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, pre-selection, BDT selection of Dplus and Dminus, final selection, FT variables)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_FT_TupleB.root"
#FlavourTaggingGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_FT_TupleB.root" B02DD B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected_finalselection_ft.log
#
#echo ""
#echo "**Tuple B** (flat, common variables, pre-selection, BDT selection of Dplus and Dminus, final selection, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_random_TupleB.root"
#CandidateSelectionGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_FT_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_random_TupleB.root" B02DD "idxRandom" > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected_finalselection_ft_random.log
#
#echo ""
#echo "**Fit Tuple** (flat, common variables, pre-selection, BDT selection of Dplus and Dminus, final selection, FT variables, random candidate selection)"
#echo "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_random_FitTuple.root"
#FitTupleGrimReaper "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_random_TupleB.root" B02DD "${INPUT_PATH}${BASE_FILE_NAME}_${DATE}_${PRODUCER}_flat_selected_random_FitTuple.root" B02DD > scythe_${RUN_NAME}_${DATE}_DT2011_B02DD_flat_vars_preselected_finalselection_ft_random_fittuple.log

echo "finished!"