#include "gl.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>

azro::ClearFn azro::Clear = nullptr;
azro::ClearColorFn azro::ClearColor = nullptr;
azro::ViewportFn azro::Viewport = nullptr;

void azro::load_functions(){
    azro::Clear = reinterpret_cast<azro::ClearFn>(SDL_GL_GetProcAddress("glClear"));
    if(azro::Clear == nullptr) throw std::runtime_error(std::string("Clear function cannot be loaded ! \n"));

    azro::ClearColor = reinterpret_cast<azro::ClearColorFn>(SDL_GL_GetProcAddress("glClearColor"));
    if(azro::ClearColor) throw std::runtime_error(std::string("clear color function cannot be loaded \n"));

    azro::Viewport = reinterpret_cast<azro::ViewportFn>(SDL_GL_GetProcAddress("glViewport"));
    if(azro::Viewport) throw std::runtime_error(std::string("Viewport function cannot be loaded \n"));


}
