#pragma once

#include <cstdint>
#include <memory>

namespace azro{
    struct Color{
        std::uint8_t r, g, b; 
    };

    struct TextureId{ std::uint32_t index;};

    class Renderer{
        public:
        Renderer(int width, int height);
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        Renderer(Renderer&&) noexcept;
        Renderer& operator=(Renderer&&) noexcept;
        
        TextureId load_texture(const char*path);
        void draw_sprite(TextureId texture, float x, float y, float w, float h, float angle = 0.0f);
        // angle in radians and the positive turns clockwise on screen (y points down)
        void  draw_rect(float x, float y, float w, float h, Color color, float angle = 0.0f);
        void flush();
        std::uint32_t take_draw_calls();

        private:
        struct Impl;
        std::unique_ptr<Impl> impl_; 
    };
}
