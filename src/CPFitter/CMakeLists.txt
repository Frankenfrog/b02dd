# Library
add_library(CPFitter 	CPFitter.h
                     	CPFitter.cpp)

# Executables

# Aliases for module libs

# Linker information
target_link_libraries(CPFitter decratecoeff_bd ${ALL_LIBRARIES})