

add_library(azro STATIC src/platform.cpp src/window.cpp src/gl/gl.cpp src/triangle.cpp)
target_include_directories(azro PUBLIC include)
target_include_directories(azro PRIVATE src)
target_compile_features(azro PUBLIC cxx_std_20)
target_link_libraries(azro PRIVATE SDL3::SDL3)
target_link_libraries(azro PRIVATE azro_warnings)
