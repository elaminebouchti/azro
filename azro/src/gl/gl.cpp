#include "gl.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <iostream>
#include <string>

azro::gl::ClearFn azro::gl::Clear = nullptr;
azro::gl::ClearColorFn azro::gl::ClearColor = nullptr;
azro::gl::ViewportFn azro::gl::Viewport = nullptr;
azro::gl::GetStringFn azro::gl::GetString = nullptr;

namespace azro::gl{
    namespace {
    const char* or_unknown(const char* text){
        if(text == nullptr) return "unknown";
        return text; 
        }
    }
}

template <typename Fn>
void azro::gl::load(Fn& out, const char* name){
    out = reinterpret_cast<Fn>(SDL_GL_GetProcAddress(name));
    if(out == nullptr) throw std::runtime_error(std::string("failed to load ") + name + SDL_GetError());
}

void azro::gl::load_functions(){
    
    load(gl::Clear, "glClear");
    load(gl::ClearColor, "glClearColor");
    load(gl::Viewport, "glViewport");
    load(gl::GetString, "glGetString");
}

void azro::gl::print_info(){
    const char* version = reinterpret_cast<const char*>(gl::GetString((gl::VERSION)));
    version = or_unknown(version);
    const char* vendor = reinterpret_cast<const char*>(gl::GetString(gl::VENDOR));
    vendor = or_unknown(vendor);
    const char* renderer = reinterpret_cast<const char*>(gl::GetString(gl::RENDERER));
    renderer = or_unknown(renderer);
    std::cout << "Version :" << version << "\nVendor : " << vendor << "\nRenderer : " << renderer <<"\n";
}

