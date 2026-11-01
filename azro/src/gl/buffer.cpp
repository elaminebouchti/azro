#include "gl/buffer.hpp"


azro::gl::Buffer::Buffer(GLenum type){
    GenBuffers(type, &vbo_);
}

azro::gl::Buffer::~Buffer(){
    if(vbo_ != 0){
        azro::gl::DeleteBuffers(1, &vbo_);
    }
}
void azro::gl::Buffer::upload(GLsizeiptr size, GLvoid* data) const{
    bind();
    BufferData(ARRAY_BUFFER, size, data, STATIC_DRAW);
}
void azro::gl::Buffer::bind() const{
    BindBuffer(1, vbo_);
}
