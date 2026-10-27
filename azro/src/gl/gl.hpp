#pragma once

namespace azro::gl{
    
    using GLenum = unsigned int;
    using GLbitfield = unsigned int;
    using GLint = int;
    using GLsizei = int;
    using GLfloat = float;
    using GLubyte = unsigned char;
    inline constexpr GLenum COLOR_BUFFER_BIT = 0x00004000;
    inline constexpr GLenum VERSION = 0x1F02;
    inline constexpr GLenum VENDOR = 0x1F00;
    inline constexpr GLenum RENDERER = 0x1F01;
    using ClearFn = void(*)(GLbitfield);
    using ClearColorFn = void(*)(GLfloat, GLfloat, GLfloat, GLfloat);
    using ViewportFn = void(*)(GLint, GLint, GLsizei, GLsizei);
    using GetStringFn = const GLubyte*(*)(GLenum);
    extern ClearFn Clear;
    extern ClearColorFn ClearColor;
    extern ViewportFn  Viewport;
    extern GetStringFn GetString;

    void load_functions();
    void print_info();


}
