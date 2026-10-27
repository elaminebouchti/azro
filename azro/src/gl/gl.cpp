#include "gl.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <iostream>

azro::gl::ClearFn azro::gl::Clear = nullptr;
azro::gl::ClearColorFn azro::gl::ClearColor = nullptr;
azro::gl::ViewportFn azro::gl::Viewport = nullptr;
azro::gl::GetStringFn azro::gl::GetString = nullptr;

void azro::gl::load_functions(){
    gl::Clear = reinterpret_cast<gl::ClearFn>(SDL_GL_GetProcAddress("glClear"));
    if(gl::Clear == nullptr) throw std::runtime_error(std::string("glClear ") + SDL_GetError());

    gl::ClearColor = reinterpret_cast<gl::ClearColorFn>(SDL_GL_GetProcAddress("glClearColor"));
    if(gl::ClearColor == nullptr) throw std::runtime_error(std::string("glClearColor") + SDL_GetError());

    gl::Viewport = reinterpret_cast<gl::ViewportFn>(SDL_GL_GetProcAddress("glViewport"));
    if(gl::Viewport == nullptr) throw std::runtime_error(std::string("glViewport") + SDL_GetError());

    gl::GetString = reinterpret_cast<gl::GetStringFn>(SDL_GL_GetProcAddress("glGetString"));
    if(gl::GetString == nullptr) throw std::runtime_error(std::string("glGetString") + SDL_GetError());
}

void azro::gl::print(){
    std::cout << "Version : " << reinterpret_cast<const char*>(gl::GetString(gl::VERSION)) << "\n"
              << "Vendor : "  << reinterpret_cast<const char*>(gl::GetString(gl::VENDOR)) << "\n"
              << "Renderer : "  << reinterpret_cast<const char*>(gl::GetString(gl::RENDERER)) << "\n";
}


