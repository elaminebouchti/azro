#include "azro/triangle.hpp"
#include "gl/gl.hpp"
#include "gl/buffer.hpp"
#include "gl/vertexArray.hpp"
#include <string>
#include <stdexcept>

namespace azro{
    namespace{
        unsigned int compile_shader(unsigned int type, const char* source){
            azro::gl::ShaderSource(shader, 1, &source, nullptr);
            azro::gl::CompileShader(shader);
            azro::gl::GLint success = 0;
            azro::gl::GetShaderiv(shader, azro::gl::COMPILE_STATUS, &success);
            if(success == azro::gl::FALSE){
                azro::gl::GLint log_length = 0;
                azro::gl::GetShaderiv(shader, azro::gl::INFO_LOG_LENGTH, &log_length);
                std::string infoLog(log_length, '\0');
                azro::gl::GetShaderInfoLog(shader, log_length, &log_length, infoLog.data());
                infoLog.resize(log_length);
                throw std::runtime_error(std::string(type == azro::gl::VERTEX_SHADER ? "vertex" : "fragment") + " shader compilation failed : " + infoLog);
            }
            return static_cast<azro::gl::GLuint>(shader);
        }
    }
}


struct azro::Triangle::Impl{azro::gl::VertexArray vao; azro::gl::Buffer vbo{azro::gl::ARRAY_BUFFER};};


azro::Triangle::Triangle(const std::array<float, 15>& vertices): impl_(new Impl{}){
    impl_->vao.bind();
    impl_->vbo.upload(sizeof(vertices), vertices.data());

    impl_->vao.attribute(impl_->vbo, 0, 2, 5 * sizeof(float), 0);
    impl_->vao.attribute(impl_->vbo, 1, 3, 5 * sizeof(float), 2 * sizeof(float));

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
    azro::gl::GLint link_success = 0;
    azro::gl::GetProgramiv(program_, azro::gl::LINK_STATUS, &link_success);
    if(link_success == azro::gl::FALSE){
        azro::gl::GLint log_length = 0;
        azro::gl::GetProgramiv(program_, azro::gl::INFO_LOG_LENGTH, &log_length);
        std::string infoLog(log_length, '\0');
        azro::gl::GetProgramInfoLog(program_, log_length, &log_length, infoLog.data());
        infoLog.resize(log_length);
        azro::gl::DeleteShader(vs);
        azro::gl::DeleteShader(fs);
        azro::gl::DeleteProgram(program_);
        throw std::runtime_error(std::string("linking program failed : ") + infoLog);
    }
    azro::gl::DeleteShader(vs);
    azro::gl::DeleteShader(fs);
}

azro::Triangle::~Triangle(){
    azro::gl::DeleteProgram(program_);
}

void azro::Triangle::draw()const{
    azro::gl::UseProgram(program_);
    impl_->vao.bind();
    azro::gl::DrawArrays(azro::gl::TRIANGLES, 0, 3);
    azro::gl::check_error("after draw : ");
}

