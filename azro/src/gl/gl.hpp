#pragma once

#include <cstddef>

namespace azro::gl{
    
    using GLenum = unsigned int;
    using GLbitfield = unsigned int;
    using GLint = int;
    using GLsizei = int;
    using GLfloat = float;
    using GLubyte = unsigned char;
    using GLuint = unsigned int;
    using GLchar = char;
    using GLboolean = bool;
    using GLsizeptr = ptrdiff_t;
    inline constexpr GLenum COLOR_BUFFER_BIT = 0x00004000;
    inline constexpr GLenum VERSION = 0x1F02;
    inline constexpr GLenum VENDOR = 0x1F00;
    inline constexpr GLenum RENDERER = 0x1F01;
    inline constexpr GLenum ARRAY_BUFFER = 0x8892;
    inline constexpr GLenum STATIC_DRAW = 0x88E4;
    inline constexpr GLenum FLOAT = 0x8B50;
    inline constexpr GLenum FALSE = 0;
    inline constexpr GLenum VERTEX_SHADER = 0x8B31;
    inline constexpr GLenum FRAGMENT_SHADER = 0x8B30;
    inline constexpr GLenum COMPILE_STATUS = 0x8B81;
    inline constexpr GLenum LINK_STATUS = 0x8B82;
    inline constexpr GLenum INFO_LOG_LENGTH = 0x8B84;
    inline constexpr GLenum NO_ERROR = 0;
    using ClearFn = void(*)(GLbitfield);
    using ClearColorFn = void(*)(GLfloat, GLfloat, GLfloat, GLfloat);
    using ViewportFn = void(*)(GLint, GLint, GLsizei, GLsizei);
    using GetStringFn = const GLubyte*(*)(GLenum);
    extern ClearFn Clear;
    extern ClearColorFn ClearColor;
    extern ViewportFn  Viewport;
    extern GetStringFn GetString;

    void load_functions();
    template <typename Fn>
    void load(Fn& out, const char* name);

    void print_info();

}
