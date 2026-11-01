#pragma once
#include "gl/gl.hpp"
#include <memory>
#include <utility>

namespace azro::gl{
    class Buffer{
        public:
        Buffer(azro::gl::GLenum type);
        ~Buffer();
        Buffer& operator=(const Buffer&) = delete;

        Buffer(Buffer& other) noexcept: vbo_(std::exchange(other.vbo_, 0)){}
        Buffer(const Buffer&) = delete;
        Buffer& operator=(Buffer&& other) noexcept{
            std::swap(vbo_, other.vbo_);
            return *this;  
        }

        void upload(GLsizeiptr size, GLvoid* data) const;


        private:
        azro::gl::GLuint vbo_;

    };

}
