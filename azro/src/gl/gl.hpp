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
    using GLsizeiptr = ptrdiff_t;
    using GLvoid = void;

    inline constexpr GLenum COLOR_BUFFER_BIT = 0x00004000;
    inline constexpr GLenum VERSION = 0x1F02;
    inline constexpr GLenum VENDOR = 0x1F00;
    inline constexpr GLenum RENDERER = 0x1F01;
    inline constexpr GLenum ARRAY_BUFFER = 0x8892;
    inline constexpr GLenum STATIC_DRAW = 0x88E4;
    inline constexpr GLenum FLOAT = 0x1406;
    inline constexpr GLenum FALSE = 0;
    inline constexpr GLenum VERTEX_SHADER = 0x8B31;
    inline constexpr GLenum FRAGMENT_SHADER = 0x8B30;
    inline constexpr GLenum COMPILE_STATUS = 0x8B81;
    inline constexpr GLenum LINK_STATUS = 0x8B82;
    inline constexpr GLenum INFO_LOG_LENGTH = 0x8B84;
    inline constexpr GLenum NO_ERROR = 0;
    inline constexpr GLenum TRIANGLES = 0x0004;

    using ClearFn = void(*)(GLbitfield);
    using ClearColorFn = void(*)(GLfloat, GLfloat, GLfloat, GLfloat);
    using ViewportFn = void(*)(GLint, GLint, GLsizei, GLsizei);
    using GetStringFn = const GLubyte*(*)(GLenum);
    extern ClearFn Clear;
    extern ClearColorFn ClearColor;
    extern ViewportFn  Viewport;
    extern GetStringFn GetString;

    using GenBuffersFn = void(*)(GLsizei, GLuint*);
    using BindBufferFn = void(*)(GLenum, GLuint);
    using BufferDataFn = void(*)(GLenum, GLsizeiptr, const GLvoid*, GLenum);
    using DeleteBuffersFn = void(*)(GLsizei, const GLuint*);
    extern GenBuffersFn GenBuffers;
    extern BindBufferFn BindBuffer;
    extern BufferDataFn BufferData;
    extern DeleteBuffersFn DeleteBuffers;

    using GenVertexArrayFn = void(*)(GLsizei, GLuint*);
    using BindVertexArraysFn = void(*)(GLuint);
    using VertexAttribPointerFn = void(*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
    using EnableVertexAttribArrayFn = void(*)(GLuint);
    using DeleteVertexArraysFn = void(*)(GLsizei, const GLuint*);
    extern GenVertexArrayFn GenVertexArrays;
    extern BindVertexArraysFn BindVertexArray;
    extern VertexAttribPointerFn VertexAttribPointer;
    extern EnableVertexAttribArrayFn EnableVertexAttribArray;
    extern DeleteBuffersFn DeleteVertexArrays;

    using CreateShaderFn = GLuint(*)(GLenum);
    using ShaderSourceFn = void(*)(GLuint, GLsizei, const GLchar**, GLchar*);
    using CompileShaderFn = void(*)(GLuint);
    using GetShaderivFn = void(*)(GLuint, GLenum, GLint*);
    using GetShaderFn = void(*)(GLuint, GLenum, GLint*);
    using GetShaderInfoLogFn = void(*)(GLuint, GLsizei, GLsizei*, GLchar*);
    using DeleteShaderFn = void(*)(GLuint);
    extern CreateShaderFn CreateShader;
    extern ShaderSourceFn ShaderSource;
    extern CompileShaderFn CompileShader;
    extern GetShaderivFn GetShaderiv;
    extern GetShaderInfoLogFn GetShaderInfoLog;
    extern DeleteShaderFn DeleteShader;

    using CreateProgramFn = GLuint(*)(void);
    using AttachShaderFn = void(*)(GLuint, GLuint);
    using LinkProgramFn = void(*)(GLuint);
    using GetProgramivFn = void(*)(GLuint, GLenum, GLint*);
    using GetProgramInfoLogFn = void(*)(GLuint, GLsizei, GLsizei*, GLchar*);
    using UseProgramFn = void(*)(GLuint);
    using DeleteProgramFn = void(*)(GLuint);
    extern CreateProgramFn CreateProgram;
    extern AttachShaderFn AttachShader;
    extern LinkProgramFn LinkProgram;
    extern GetProgramivFn GetProgramiv;
    extern GetProgramInfoLogFn GetProgramInfoLog;
    extern UseProgramFn UseProgram;
    extern DeleteProgramFn DeleteProgram;

    using DrawArraysFn = void(*)(GLenum, GLint, GLsizei);
    using GetErrorFn = GLenum(*)(void);
    extern DrawArraysFn DrawArrays;
    extern GetErrorFn GetError;

    void load_functions();
    template <typename Fn>
    void load(Fn& out, const char* name);

    void print_info();
    void check_error(const char* where);

}
