add_subdirectory(GrimReaper)

# Executables
add_executable(PID_cut_optimization PID_cut_optimization.cpp)
add_executable(BDT_cut_optimization BDT_cut_optimization.cpp)
add_executable(SweightCalculation SweightCalculation.cpp)
add_executable(TaggingPower TaggingPower.cpp)
add_executable(B02DDMCFit B02DDMCFit.cpp)
add_executable(WSMassFit WSMassFit.cpp)
add_executable(B02DsDMCFit B02DsDMCFit.cpp)
add_executable(MassFit MassFit.cpp)
add_executable(DMassFit DMassFit.cpp)
add_executable(MassFit_DDweights MassFit_DDweights.cpp)

# Aliases for module libs

# Linker information
target_link_libraries(PID_cut_optimization ${ALL_LIBRARIES})
target_link_libraries(BDT_cut_optimization ${ALL_LIBRARIES})
target_link_libraries(SweightCalculation ${ALL_LIBRARIES})
target_link_libraries(TaggingPower ${ALL_LIBRARIES})
target_link_libraries(B02DDMCFit ${ALL_LIBRARIES})
target_link_libraries(WSMassFit ${ALL_LIBRARIES})
target_link_libraries(B02DsDMCFit ${ALL_LIBRARIES})
target_link_libraries(MassFit ${ALL_LIBRARIES})
target_link_libraries(DMassFit ${ALL_LIBRARIES})
target_link_libraries(MassFit_DDweights ${ALL_LIBRARIES})
