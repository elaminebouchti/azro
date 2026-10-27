#pragma once
#include <cstdint>

namespace azro{
    
    using GLenum = unsigned int;
    using GLbitfield = unsigned int;
    using GLint = int;
    using GLsizei = int;
    using GLfloat = float;
    using GLubyte = uint8_t;
    inline constexpr GLenum COLOR_BUFFER_BIT = 0x00004000;
    inline constexpr GLenum GL_VERSION = 0x1F02;
    using ClearFn = void(*)(GLbitfield);
    using ClearColorFn = void(*)(GLfloat, GLfloat, GLfloat, GLfloat);
    using ViewportFn = void(*)(GLint, GLint, GLsizei, GLsizei);
    extern ClearFn Clear;
    extern ClearColorFn ClearColor;
    extern ViewportFn Viewport;

    void load_functions();

    
}
