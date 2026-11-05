#include "gl/vertexArray.hpp"


azro::gl::VertexArray::VertexArray(): vao_(){
    azro::gl::GenVertexArrays(1, &vao_);
}

azro::gl::VertexArray::~VertexArray(){
    if(vao_ != 0){
        azro::gl::DeleteVertexArrays(1, &vao_);
    }
}

void azro::gl::VertexArray::bind() const{
    BindVertexArray(vao_);
}

void azro::gl::VertexArray::attribute(const Buffer& vbo, GLuint index, GLint size, GLsizei stride, std::size_t offset){
    bind();
    vbo.bind();
    VertexAttribPointer(index, size, azro::gl::FLOAT, azro::gl::FALSE, stride, reinterpret_cast<const void*>(offset));
    EnableVertexAttribArray(index);
}

void azro::gl::VertexArray::index_buffer(const Buffer& ibo){
    bind();
    ibo.bind();
}
