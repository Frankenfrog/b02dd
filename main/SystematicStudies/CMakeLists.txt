# Executables
add_executable(DeltaGammad DeltaGammad.cpp)
add_executable(MistagTimeCorrelation MistagTimeCorrelation.cpp)
add_executable(DecayTimeFitValidation DecayTimeFitValidation.cpp)

# Aliases for module libs

# Linker information
target_link_libraries(DeltaGammad ${ALL_LIBRARIES})
target_link_libraries(MistagTimeCorrelation ${ALL_LIBRARIES})
target_link_libraries(DecayTimeFitValidation ${ALL_LIBRARIES})
