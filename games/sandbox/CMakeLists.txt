add_executable(sandbox main.cpp)
target_link_libraries(sandbox PRIVATE azro)
target_link_libraries(azro PRIVATE azro_warnings)
