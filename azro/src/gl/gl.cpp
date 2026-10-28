#include "gl.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <iostream>
#include <string>

azro::gl::ClearFn azro::gl::Clear = nullptr;
azro::gl::ClearColorFn azro::gl::ClearColor = nullptr;
azro::gl::ViewportFn azro::gl::Viewport = nullptr;
azro::gl::GetStringFn azro::gl::GetString = nullptr;

azro::gl::GenBuffersFn azro::gl::GenBuffers = nullptr;
azro::gl::BufferDataFn azro::gl::BufferData = nullptr;
azro::gl::BindBufferFn azro::gl::BindBuffer = nullptr;
azro::gl::DeleteBuffersFn azro::gl::DeleteBuffers = nullptr;

azro::gl::GenVertexArrayFn azro::gl::GenVertexArrays = nullptr;
azro::gl::BindVertexArraysFn azro::gl::BindVertexArray = nullptr;
azro::gl::VertexAttribPointerFn azro::gl::VertexAttribPointer = nullptr;
azro::gl::EnableVertexAttribArrayFn azro::gl::EnableVertexAttribArray = nullptr;
azro::gl::DeleteVertexArraysFn azro::gl::DeleteVertexArrays = nullptr;

azro::gl::CreateShaderFn azro::gl::CreateShader = nullptr;
azro::gl::ShaderSourceFn azro::gl::ShaderSource = nullptr;
azro::gl::CompileShaderFn azro::gl::CompileShader = nullptr;
azro::gl::GetShaderivFn azro::gl::GetShaderiv = nullptr;
azro::gl::GetShaderInfoLogFn azro::gl::GetShaderInfoLog = nullptr;
azro::gl::DeleteShaderFn azro::gl::DeleteShader = nullptr;

azro::gl::CreateProgramFn azro::gl::CreateProgram = nullptr;
azro::gl::AttachShaderFn azro::gl::AttachShader = nullptr;
azro::gl::LinkProgramFn azro::gl::LinkProgram = nullptr;
azro::gl::GetProgramivFn azro::gl::GetProgramiv = nullptr;
azro::gl::GetProgramInfoLogFn azro::gl::GetProgramInfoLog = nullptr;
azro::gl::UseProgramFn azro::gl::UseProgram = nullptr;
azro::gl::DeleteProgramFn azro::gl::DeleteProgram = nullptr;

azro::gl::DrawArraysFn azro::gl::DrawArrays = nullptr;
azro::gl::GetErrorFn azro::gl::GetError = nullptr;

namespace azro::gl{
    namespace {
    const char* or_unknown(const char* text){
        if(text == nullptr) return "unknown";
        return text; 
        }
        template <typename Fn>
    void load(Fn& out, const char* name){
        out = reinterpret_cast<Fn>(SDL_GL_GetProcAddress(name));
        if(out == nullptr) throw std::runtime_error(std::string("failed to load ") + name + SDL_GetError());
        }
    }
}


void azro::gl::load_functions(){
    
    load(gl::Clear, "glClear");
    load(gl::ClearColor, "glClearColor");
    load(gl::Viewport, "glViewport");
    load(gl::GetString, "glGetString");

    load(gl::GenBuffers, "glGenBuffers");
    load(gl::BindBuffer, "glBindBuffer");
    load(gl::BufferData, "glBufferData");
    load(gl::DeleteBuffers, "glDeleteBuffers");

    load(gl::GenVertexArrays, "glGenVertexArrays");
    load(gl::BindVertexArray, "glBindVertexArray");
    load(gl::VertexAttribPointer, "glVertexAttribPointer");
    load(gl::EnableVertexAttribArray, "glEnableVertexAttribArray");
    load(gl::DeleteVertexArrays, "glDeleteVertexArrays");

    load(gl::CreateShader, "glCreateShader");
    load(gl::ShaderSource, "glShaderSource");
    load(gl::CompileShader, "glCompileShader");
    load(gl::GetShaderiv, "glGetShaderiv");
    load(gl::GetShaderInfoLog, "glGetShaderInfoLog");
    load(gl::DeleteShader, "glDeleteShader");

    load(gl::CreateProgram, "glCreateProgram");
    load(gl::AttachShader, "glAttachShader");
    load(gl::LinkProgram, "glLinkProgram");
    load(gl::GetProgramiv, "glGetProgramiv");
    load(gl::GetProgramInfoLog, "glGetProgramInfoLog");
    load(gl::UseProgram, "glUseProgram");
    load(gl::DeleteProgram, "glDeleteProgram");

    load(gl::DrawArrays, "glDrawArrays");
    load(gl::GetError, "glGetError");
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

void azro::gl::check_error(const char* where){
    azro::gl::GLenum err;
    while((err = GetError()) != NO_ERROR){
        std::cout <<"OpenGl Error " << where << "triggered Error code :" << err << std::dec << "\n";
    }

}

