#include "gl/buffer.hpp"


azro::gl::Buffer::Buffer(azro::gl::GLenum type): type_(type){
    GenBuffers(1, &vbo_);
}

azro::gl::Buffer::~Buffer(){
    if(vbo_ != 0){
        azro::gl::DeleteBuffers(1, &vbo_);
    }
}
void azro::gl::Buffer::upload(GLsizeiptr size, const GLvoid* data){
    bind();
    BufferData(type_, size, data, STATIC_DRAW);
}
void azro::gl::Buffer::bind() const{
    BindBuffer(type_, vbo_);
}
