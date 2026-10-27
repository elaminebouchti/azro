#include "gl.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <iostream>

gl::ClearFn gl::Clear = nullptr;
gl::ClearColorFn gl::ClearColor = nullptr;
gl::ViewportFn gl::Viewport = nullptr;
gl::GetStringFn gl::GetString = nullptr;

void gl::load_functions(){
    gl::Clear = reinterpret_cast<gl::ClearFn>(SDL_GL_GetProcAddress("glClear"));
    if(gl::Clear == nullptr) throw std::runtime_error(std::string("Clear function cannot be loaded ! \n"));

    gl::ClearColor = reinterpret_cast<gl::ClearColorFn>(SDL_GL_GetProcAddress("glClearColor"));
    if(gl::ClearColor == nullptr) throw std::runtime_error(std::string("clear color function cannot be loaded \n"));

    gl::Viewport = reinterpret_cast<gl::ViewportFn>(SDL_GL_GetProcAddress("glViewport"));
    if(gl::Viewport == nullptr) throw std::runtime_error(std::string("Viewport function cannot be loaded \n"));

    gl::GetString = reinterpret_cast<gl::GetStringFn>(SDL_GL_GetProcAddress("glGetString"));
    if(gl::GetString == nullptr) throw std::runtime_error(std::string("Get string function cannot be loaded \n"));
}

void gl::print(){
    std::cout << "Version : " << reinterpret_cast<const char*>(gl::GetString(gl::GL_VERSION)) << "\n"
              << "Vendor : "  << reinterpret_cast<const char*>(gl::GetString(gl::GL_VENDOR)) << "\n"
              << "Renderer : "  << reinterpret_cast<const char*>(gl::GetString(gl::GL_RENDERER)) << "\n";
}


