#pragma once
#include "gl/gl.hpp"
#include <memory>
#include <utility>

namespace azro::gl{
    class Buffer{
        public:
        Buffer(azro::gl::GLuint buffer, azro::gl::GLenum type, azro::gl::GLsizeiptr size, azro::gl::GLvoid* data);
        ~Buffer();
        Buffer& operator=(const Buffer&) = delete;

        Buffer(Buffer& other) noexcept: buffer_(std::exchange(other.buffer_, 0)){}
        Buffer(const Buffer&) = delete;
        Buffer& operator=(Buffer&& other) noexcept{
            std::swap(buffer_, other.buffer_);
            return *this;  
        }


        private:
        azro::gl::GLuint buffer_;
        azro::gl::GLenum type_;

    };

}
