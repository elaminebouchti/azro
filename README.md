# a 2D engine for turn-based strategy and puzzle games, in c++20
Requirement : Linux, a C++20 compiler(GCC13+), CMake 3.25+, Ninja, and SDL 3.4 built and installed.
Build : 
- cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=$HOME/.local -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
- cmake --build build
- ./build/games/sandbox/sandbox
