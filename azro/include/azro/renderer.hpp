#pragma once

#include <cstdint>
#include <memory>

namespace azro{
    struct Color{
        std::uint8_t r, g, b; 
    };


    class Renderer{
        public:
        Renderer(int width, int height);
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        void  draw_rect(float x, float y, float w, float h, Color color) const;
        private:
        struct Impl;
        std::unique_ptr<Impl> impl_; 
    };
}
