#pragma once
#include "gl/gl.hpp"
#include <utility>

namespace azro::gl{
    class ShaderProgram{
        public:
        ShaderProgram(const char* vertex_src, const char* fragment_src);
        ~ShaderProgram();
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram& other) = delete;

        ShaderProgram(ShaderProgram&& other) noexcept: program_(std::exchange(other.program_, 0)){};
        ShaderProgram& operator=(ShaderProgram&& other) noexcept{
            std::swap(program_, other.program_);
            return *this;
        }
        void use() const;

        private:
        azro::gl::GLuint program_ = 0;
        ShaderProgram(): program_(CreateProgram()){};

    };
}
