# Executables
add_executable(DeltaGammad DeltaGammad.cpp)
add_executable(MistagTimeCorrelation MistagTimeCorrelation.cpp)
add_executable(DecayTimeFitValidation DecayTimeFitValidation.cpp)
add_executable(DeltaMd DeltaMd.cpp)
add_executable(FlavourTaggingCalibration FlavourTaggingCalibration.cpp)
add_executable(ProductionAsymmetry ProductionAsymmetry.cpp)
#add_executable(CorrelationMassTime CorrelationMassTime.cpp)
add_executable(DecayTimeAcceptance DecayTimeAcceptance.cpp)
add_executable(MassModel MassModel.cpp)

# Aliases for module libs

# Linker information
target_link_libraries(DeltaGammad ${ALL_LIBRARIES})
target_link_libraries(MistagTimeCorrelation ${ALL_LIBRARIES})
target_link_libraries(DecayTimeFitValidation ${ALL_LIBRARIES})
target_link_libraries(DeltaMd ${ALL_LIBRARIES})
target_link_libraries(FlavourTaggingCalibration ${ALL_LIBRARIES})
target_link_libraries(ProductionAsymmetry ${ALL_LIBRARIES})
#target_link_libraries(CorrelationMassTime ${ALL_LIBRARIES})
target_link_libraries(DecayTimeAcceptance ${ALL_LIBRARIES})
target_link_libraries(MassModel ${ALL_LIBRARIES})