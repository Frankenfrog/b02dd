# Executables
add_executable(HelloMain HelloMain.cpp)
add_executable(PID_cut_optimization PID_cut_optimization.cpp)
add_executable(SweightCalculation SweightCalculation.cpp)
add_executable(TaggingPower TaggingPower.cpp)

# Aliases for module libs

# Linker information
target_link_libraries(HelloMain ${ALL_LIBRARIES})
target_link_libraries(PID_cut_optimization ${ALL_LIBRARIES})
target_link_libraries(SweightCalculation ${ALL_LIBRARIES})
target_link_libraries(TaggingPower ${ALL_LIBRARIES})
