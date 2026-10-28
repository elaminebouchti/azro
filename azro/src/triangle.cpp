#include "azro/triangle.hpp"
#include <SDL3/SDL.h>
#include "gl/gl.hpp"


azro::Triangle::Triangle(std::array<float, 6>& vertices){
    azro::gl::GenVertexArrays(vao_, &vao_);
    azro::gl::BindVertexArray(vao_);

    azro::gl::GenBuffers(vbo_, &vbo_);
    azro::gl::BindBuffer(vao_, vbo_);

    azro::gl::BufferData(vao_, static_cast<azro::gl::GLsizeiptr>(sizeof(vertices)), &vbo_, azro::gl::STATIC_DRAW);

    azro::gl::VertexAttribPointer(0, 2, azro::gl::FLOAT, azro::gl::FALSE, static_cast<azro::gl::GLsizei>(2 * sizeof(float)), nullptr);

    azro::gl::EnableVertexAttribArray(0);



}

azro::Triangle::~Triangle(){}

void azro::Triangle::draw()const{}
