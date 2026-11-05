#pragma once
#include "gl/gl.hpp"
#include <utility>

namespace azro::gl{
    class Buffer{
        public:
        explicit Buffer(azro::gl::GLenum);
        ~Buffer();
        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;
        
        Buffer(Buffer&& other) noexcept: vbo_(std::exchange(other.vbo_, 0)), type_(std::exchange(other.type_, 0)){}
        Buffer& operator=(Buffer&& other) noexcept{
            std::swap(vbo_, other.vbo_);
            std::swap(type_, other.type_);
            return *this;  
        }

        void upload(GLsizeiptr size, const GLvoid* data);
        void bind() const;


        private:
        azro::gl::GLuint vbo_ = 0;
        azro::gl::GLenum type_;

    };

}
