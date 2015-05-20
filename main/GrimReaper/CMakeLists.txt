# Executables
add_executable(B02DDVariablesGrimReaper B02DDVariablesGrimReaper.cpp)
add_executable(B02DDWSVariablesGrimReaper B02DDWSVariablesGrimReaper.cpp)

# Linker information
target_link_libraries(B02DDVariablesGrimReaper dsReducer ${ALL_LIBRARIES})
target_link_libraries(B02DDWSVariablesGrimReaper dsReducer ${ALL_LIBRARIES})

install(TARGETS B02DDVariablesGrimReaper DESTINATION bin)
install(TARGETS B02DDWSVariablesGrimReaper DESTINATION bin)
