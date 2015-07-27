add_subdirectory(GrimReaper)
add_subdirectory(MassFits)

# Executables
add_executable(PID_cut_optimization PID_cut_optimization.cpp)
add_executable(BDT_cut_optimization BDT_cut_optimization.cpp)
add_executable(SweightCalculation SweightCalculation.cpp)
add_executable(TaggingPower TaggingPower.cpp)
add_executable(B02DDMCFit B02DDMCFit.cpp)
add_executable(sin2betaFitter_sFit sin2betaFitter_sFit.cpp)
add_executable(sin2betaFitter_MC sin2betaFitter_MC.cpp)
add_executable(DecayTimeResolution_MC DecayTimeResolution_MC.cpp)
add_executable(sin2betaFitter_bootstrapping sin2betaFitter_bootstrapping.cpp)

# Aliases for module libs

# Linker information
target_link_libraries(PID_cut_optimization ${ALL_LIBRARIES})
target_link_libraries(BDT_cut_optimization ${ALL_LIBRARIES})
target_link_libraries(SweightCalculation ${ALL_LIBRARIES})
target_link_libraries(TaggingPower ${ALL_LIBRARIES})
target_link_libraries(B02DDMCFit ${ALL_LIBRARIES})
target_link_libraries(sin2betaFitter_sFit ${ALL_LIBRARIES})
target_link_libraries(sin2betaFitter_MC ${ALL_LIBRARIES})
target_link_libraries(DecayTimeResolution_MC ${ALL_LIBRARIES})
target_link_libraries(sin2betaFitter_bootstrapping ${ALL_LIBRARIES})
