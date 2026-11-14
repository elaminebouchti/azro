#pragma once
#include "gl/gl.hpp"
#include <utility>
#include <array>

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
        void set_vec4(GLint location, float x, float y, float z, float w) const;
        void set_mat4(GLint location, const std::array<float, 16>& m) const;

        GLint uniform_location(const char* name) const;

        private:
        GLuint program_ = 0;
        ShaderProgram(): program_(CreateProgram()){};

    };
}
