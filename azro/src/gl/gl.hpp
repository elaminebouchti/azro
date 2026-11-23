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
    using GLboolean = unsigned char;
    using GLsizeiptr = ptrdiff_t;
    using GLvoid = void;

    inline constexpr GLenum COLOR_BUFFER_BIT = 0x00004000;
    inline constexpr GLenum VERSION = 0x1F02;
    inline constexpr GLenum VENDOR = 0x1F00;
    inline constexpr GLenum RENDERER = 0x1F01;
    inline constexpr GLenum ARRAY_BUFFER = 0x8892;
    inline constexpr GLenum STATIC_DRAW = 0x88E4;
    inline constexpr GLenum FLOAT = 0x1406;
    inline constexpr GLboolean FALSE = 0;
    inline constexpr GLenum VERTEX_SHADER = 0x8B31;
    inline constexpr GLenum FRAGMENT_SHADER = 0x8B30;
    inline constexpr GLenum COMPILE_STATUS = 0x8B81;
    inline constexpr GLenum LINK_STATUS = 0x8B82;
    inline constexpr GLenum INFO_LOG_LENGTH = 0x8B84;
    inline constexpr GLenum NO_ERROR = 0;
    inline constexpr GLenum TRIANGLES = 0x0004;
    inline constexpr GLenum ELEMENT_ARRAY_BUFFER = 0x8893;
    inline constexpr GLenum UNSIGNED_INT = 0x1405;
    inline constexpr GLenum TEXTURE_2D = 0x0DE1;
    inline constexpr GLenum TEXTURE_MIN_FILTER = 0x2801;
    inline constexpr GLenum TEXTURE_MAG_FILTER = 0x2800;
    inline constexpr GLenum TEXTURE_WRAP_S = 0x2802;
    inline constexpr GLenum TEXTURE_WRAP_T = 0x2803;
    inline constexpr GLenum TEXTURE_NEAREST = 0x2600;
    inline constexpr GLenum TEXTURE_LINEAR = 0x2601;
    inline constexpr GLenum TEXTURE_RGBA = 0x1908;
    inline constexpr GLenum TEXTURE_RGBA8 = 0x8058;
    inline constexpr GLenum UNSIGNED_BYTE = 0x1401;
    inline constexpr GLenum BLEND = 0x0BE2;
    inline constexpr GLenum SRC_ALPHA = 0x0302;
    inline constexpr GLenum ONE_MINUS_SRC_ALPHA = 0x0303;
    inline constexpr GLenum CLAMP_TO_EDGE = 0x812F;



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
    extern DeleteVertexArraysFn DeleteVertexArrays;

    using CreateShaderFn = GLuint(*)(GLenum);
    using ShaderSourceFn = void(*)(GLuint, GLsizei, const GLchar**, const GLint*);
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
    extern DrawArraysFn DrawArrays;
    using GetErrorFn = GLenum(*)(void);
    extern GetErrorFn GetError;
    using DrawElementsFn = void(*)(GLenum, GLsizei, GLenum, const GLvoid*);
    extern DrawElementsFn DrawElements;
    using GetUniformLocationFn = GLint(*)(GLuint, const GLchar*);
    extern GetUniformLocationFn GetUniformLocation;
    using Uniform4fFn = void(*)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
    extern Uniform4fFn Uniform4f; 
    using UniformMatrix4fvFn = void(*)(GLint, GLsizei, GLboolean, const GLfloat*);
    extern UniformMatrix4fvFn UniformMatrix4fv;

    using GenTexturesFn = void(*)(GLsizei, GLuint*);
    extern GenTexturesFn GenTextures;
    using BindTextureFn = void(*)(GLenum, GLuint);
    extern BindTextureFn BindTexture;
    using TexParameteriFn = void(*)(GLenum, GLenum, GLint);
    extern TexParameteriFn TexParameteri;
    using TexImage2DFn = void(*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
    extern TexImage2DFn TexImage2D;
    using DeleteTexturesFn = void(*)(GLsizei, const GLuint*);
    extern DeleteTexturesFn DeleteTextures;
    using EnableFn = void(*)(GLenum);
    extern EnableFn Enable;
    using BlendFuncFn = void(*)(GLenum, GLenum);
    extern BlendFuncFn BlendFunc;

    void load_functions();
    void print_info();
    void check_error(const char* where);
}
