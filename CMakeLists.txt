cmake_minimum_required(VERSION 3.25)
project(azro LANGUAGES CXX)

find_package(SDL3 REQUIRED CONFIG)

add_library(azro_warnings INTERFACE)
target_compile_options(azro_warnings INTERFACE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
add_subdirectory(azro)
add_subdirectory(games/sandbox)
