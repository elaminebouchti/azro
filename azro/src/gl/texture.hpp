#pragma once
#include "gl/gl.hpp"
#include <utility>



namespace azro::gl{
    class Texture{
        public:
        explicit Texture(int width, int height, const void* rgba_pixels);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&& other) noexcept: id_(std::exchange(other.id_, 0)), type_(std::exchange(other.type_, 0)){};
        Texture& operator=(Texture&& other) noexcept{
            std::swap(id_, other.id_);
            std::swap(type_, other.type_);
            return *this;
        };

        void bind() const;

        private:
        azro::gl::GLuint id_ = 0;
        azro::gl::GLenum type_;
    }; 
}
