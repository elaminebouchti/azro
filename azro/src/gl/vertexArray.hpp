#pragma once
#include "gl/gl.hpp"
#include "gl/buffer.hpp"
#include <utility>
#include <cstddef>

namespace azro::gl{
    class VertexArray{
        public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;
        VertexArray(VertexArray&& other) noexcept: vao_(std::exchange(other.vao_, 0)){}
        VertexArray& operator=(VertexArray&& other) noexcept{
            std::swap(vao_, other.vao_);
            return *this;
        }

        void bind() const;
        void attribute(const Buffer& vbo, GLuint index, GLint size, GLsizei stride, std::size_t offset);
        void index_buffer(const Buffer& ibo);
        private:
        azro::gl::GLuint vao_ = 0;
    };

}
