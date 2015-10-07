# Executables
add_executable(WSMassFit WSMassFit.cpp)
add_executable(DMassFit DMassFit.cpp)
add_executable(MassFit_DDweights MassFit_DDweights.cpp)
add_executable(WSDMassFit WSDMassFit.cpp)
add_executable(B0DDMassFit B0DDMassFit.cpp)
add_executable(B02DsDMCMassFit B02DsDMCMassFit.cpp)
add_executable(Bs2DsDMCMassFit Bs2DsDMCMassFit.cpp)

# Aliases for module libs

# Linker information
target_link_libraries(WSMassFit ${ALL_LIBRARIES})
target_link_libraries(DMassFit ${ALL_LIBRARIES})
target_link_libraries(MassFit_DDweights ${ALL_LIBRARIES})
target_link_libraries(WSDMassFit ${ALL_LIBRARIES})
target_link_libraries(B0DDMassFit ${ALL_LIBRARIES})
target_link_libraries(B02DsDMCMassFit ${ALL_LIBRARIES})
target_link_libraries(Bs2DsDMCMassFit ${ALL_LIBRARIES})
