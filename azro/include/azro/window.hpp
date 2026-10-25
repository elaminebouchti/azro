#pragma once

#include <string>
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

namespace azro{
    class Window{
        public:
        Window(const std::string& titel, int width, int hight);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        void Poll_events();
        bool should_close() const;
        void clear(std::uint8_t r, std::uint8_t g, std::uint8_t b);
        void present();
        private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        uint64_t frame_count = 0;
        uint64_t last_time = 0;
    };
}
