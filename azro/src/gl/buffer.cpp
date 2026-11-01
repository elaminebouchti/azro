#include "gl/buffer.hpp"


azro::gl::Buffer::Buffer(azro::gl::GLuint buffer, azro::gl::GLenum type, azro::gl::GLsizeiptr size, azro::gl::GLvoid* data): buffer_(buffer), type_(type){
    azro::gl::GenBuffers(1, &buffer_);
    azro::gl::BindBuffer(type_, buffer_);
    azro::gl::BufferData(type, size, data, azro::gl::STATIC_DRAW);
}

azro::gl::Buffer::~Buffer(){
    if(buffer_ != 0){
        azro::gl::DeleteBuffers(1, &buffer_);
    }
}
