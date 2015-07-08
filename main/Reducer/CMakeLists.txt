# Executables
add_executable(SummingSweights SummingSweights.cpp)

# Linker information
target_link_libraries(SummingSweights dsReducer ${ALL_LIBRARIES})
