# Executables
add_executable(WSMassFit WSMassFit.cpp)
add_executable(MassFit MassFit.cpp)
add_executable(DMassFit DMassFit.cpp)
add_executable(MassFit_DDweights MassFit_DDweights.cpp)
add_executable(WSDMassFit WSDMassFit.cpp)
add_executable(B0DDMassFit B0DDMassFit.cpp)

# Aliases for module libs

# Linker information
target_link_libraries(WSMassFit ${ALL_LIBRARIES})
target_link_libraries(MassFit ${ALL_LIBRARIES})
target_link_libraries(DMassFit ${ALL_LIBRARIES})
target_link_libraries(MassFit_DDweights ${ALL_LIBRARIES})
target_link_libraries(WSDMassFit ${ALL_LIBRARIES})
target_link_libraries(B0DDMassFit ${ALL_LIBRARIES})
