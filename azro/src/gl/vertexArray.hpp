#pragma once
#include "gl/gl.hpp"
#include <utility>

namespace azro::gl{
    class VertexArray{
        public:
        VertexArray(azro::gl::GLuint vao_);
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept: vao_(std::exchange(other.vao_, 0)){}
        VertexArray& operator=(VertexArray&& other) noexcept{
            std::swap(vao_, other.vao_);
            return *this;
        }
        private:
        azro::gl::GLuint vao_ = 0;
    };

}
