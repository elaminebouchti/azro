#include "azro/triangle.hpp"
#include <SDL3/SDL.h>
#include "gl/gl.hpp"
#include <string>
#include <iostream>

namespace azro{
    namespace{
        unsigned int compile_shader(unsigned int type, const char* source){
            azro::gl::GLuint shader = azro::gl::CreateShader(static_cast<azro::gl::GLuint>(type));
            azro::gl::ShaderSource(shader, 1, &source, nullptr);
            azro::gl::CompileShader(shader);
            azro::gl::GLint success = 0;
            azro::gl::GetShaderiv(shader, azro::gl::COMPILE_STATUS, &success);
            if(success == azro::gl::FALSE) {
                azro::gl::GLint log_length = 0;
                azro::gl::GetShaderiv(shader, azro::gl::INFO_LOG_LENGTH, &log_length);
                std::string infoLog(log_length, '\0');
                azro::gl::GetShaderInfoLog(shader, log_length, &log_length, infoLog.data());
                std::cerr << "Error::Shader::COMPILATION_FAILED\n" << infoLog << "\n";
                azro::gl::DeleteShader(shader);
                return 0;
            }
            return static_cast<azro::gl::GLuint>(shader);
        }
    }
}

azro::Triangle::Triangle(const std::array<float, 15>& vertices){
    azro::gl::GenVertexArrays(1, &vao_);
    azro::gl::BindVertexArray(vao_);

    azro::gl::GenBuffers(1, &vbo_);
    azro::gl::BindBuffer(azro::gl::ARRAY_BUFFER, vbo_);

    azro::gl::BufferData(azro::gl::ARRAY_BUFFER, static_cast<azro::gl::GLsizeiptr>(sizeof(vertices)), static_cast<const azro::gl::GLvoid*>(vertices.data()), azro::gl::STATIC_DRAW);

    azro::gl::VertexAttribPointer(0, 2, azro::gl::FLOAT, azro::gl::FALSE, static_cast<azro::gl::GLsizei>(5 * sizeof(float)), reinterpret_cast<const void*>(0));
    azro::gl::VertexAttribPointer(1, 3, azro::gl::FLOAT, azro::gl::FALSE, static_cast<azro::gl::GLsizei>(5 * sizeof(float)), reinterpret_cast<const void*>(2*sizeof(float)));

    azro::gl::EnableVertexAttribArray(0);
    azro::gl::EnableVertexAttribArray(1);

    const char* VertexShadersSrc = R"(
    #version 330 core
    layout(location = 0) in vec2 a_pos;
    layout(location = 1) in vec3 a_color;
    out vec3 vertex_color;
    void main(){
        gl_Position = vec4(a_pos, 0.0, 1.0);
        vertex_color = a_color;
    })";

    const char* FragmentShaderSrc = R"(
    #version 330 core
    in vec3 vertex_color;
    out vec4 frag_color;
    void main(){
        frag_color = vec4(vertex_color, 1.0f);
    })";

    unsigned int vs = compile_shader(azro::gl::VERTEX_SHADER, VertexShadersSrc);
    unsigned int fs = compile_shader(azro::gl::FRAGMENT_SHADER, FragmentShaderSrc);

    program_ = azro::gl::CreateProgram();
    azro::gl::AttachShader(program_, static_cast<azro::gl::GLuint>(vs));
    azro::gl::AttachShader(program_, static_cast<azro::gl::GLuint>(fs));
    azro::gl::LinkProgram(program_);

    azro::gl::DeleteShader(vs);
    azro::gl::DeleteShader(fs);
}

azro::Triangle::~Triangle(){
    azro::gl::DeleteVertexArrays(1, &vao_);
    azro::gl::DeleteBuffers(1, &vbo_);
    azro::gl::DeleteProgram(program_);
}

void azro::Triangle::draw()const{
    azro::gl::UseProgram(program_);
    azro::gl::BindVertexArray(vao_);
    azro::gl::DrawArrays(azro::gl::TRIANGLES, 0, 3);
    azro::gl::check_error("after draw : ");
}
