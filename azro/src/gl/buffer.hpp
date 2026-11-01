#pragma once
#include "gl/gl.hpp"
#include <memory>

namespace azro::gl{
class Buffer{
    public:
    Buffer(azro::gl::GLuint buffer, azro::gl::GLenum type, azro::gl::GLsizeiptr size, azro::gl::GLvoid* data);
    ~Buffer();
    
    private:
    std::unique_ptr<azro::gl::GLuint> buffer_ = nullptr;
    azro::gl::GLenum type_;

};

}
