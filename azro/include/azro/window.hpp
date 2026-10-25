#pragma once

#include <string>
#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;

namespace azro{
    class Window{
        public:
        Window(const std::string& title, int width, int height);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        void poll_events();
        bool should_close()const;
        void clear(std::uint8_t r, std::uint8_t g, std::uint8_t b);
        void present();
        private:
        SDL_Window* window_;
        SDL_Renderer* renderer_;
        std::uint64_t frame_count_ = 0;
        std::uint64_t last_time_ = 0;
        bool quit_requested_ = false;
    };
}
