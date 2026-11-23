add_executable(sandbox main.cpp)
target_link_libraries(sandbox PRIVATE azro)
target_link_libraries(sandbox PRIVATE azro_warnings)
target_compile_definitions(sandbox PRIVATE AZRO_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
