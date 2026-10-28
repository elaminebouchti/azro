#include "azro/triangle.hpp"
#include <SDL3/SDL.h>
#include "gl/gl.hpp"


void azro::Triangle::create_vertex_shader(const char* VertexShader){
    azro::gl::ShaderSource(azro::gl::CreateShader(azro::gl::VERTEX_SHADER), 1, &VertexShader, nullptr);
}

void azro::Triangle::create_fragement_shader(const char* FragmentShader){
    azro::gl::ShaderSource(azro::gl::CreateShader(azro::gl::FRAGMENT_SHADER), 1, &FragmentShader, nullptr);
}

void azro::Triangle::create_program(const char* vertex_shader, const char* fragment_shader){
    azro::gl::GLuint program = azro::gl::CreateProgram();
    azro::gl::AttachShader(program, static_cast<azro::gl::GLuint>(*vertex_shader));
    azro::gl::AttachShader(program, static_cast<azro::gl::GLuint>(*fragment_shader));
    azro::gl::LinkProgram(program);
}

azro::Triangle::Triangle(std::array<float, 6>& vertices){
    azro::gl::GenVertexArrays(vao_, &vao_);
    azro::gl::BindVertexArray(vao_);

    azro::gl::GenBuffers(vbo_, &vbo_);
    azro::gl::BindBuffer(vao_, vbo_);

    azro::gl::BufferData(vao_, static_cast<azro::gl::GLsizeiptr>(sizeof(vertices)), &vbo_, azro::gl::STATIC_DRAW);

    azro::gl::VertexAttribPointer(0, 2, azro::gl::FLOAT, azro::gl::FALSE, static_cast<azro::gl::GLsizei>(2 * sizeof(float)), nullptr);

    azro::gl::EnableVertexAttribArray(0);

    const char* VertexShader = R"(
    #version 330 core
    layout(location = 0) in vec2 a_pos;
    void main(){
    gl_Position = vec4(a_pos, 0.0, 1.0);
    })";

    const char* FragmentShader = R"(
    version 330 core
    out vec4 frag_color;

    void main(){
    frag_color = vec4(0.0f, 0.5f, 0.0f, 0.0f);
    })";

    create_vertex_shader(VertexShader);
    create_fragement_shader(FragmentShader);
    create_program(VertexShader, FragmentShader);


}

azro::Triangle::~Triangle(){}

void azro::Triangle::draw()const{}
