#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <iostream>

struct SDL_Window;
struct SDL_GLContextState;
extern "C" void SDL_DestroyWindow(SDL_Window*);
extern "C" bool SDL_GL_DestroyContext(SDL_GLContextState*);

namespace azro{
    
    struct SDL_WindowDeleter{
        void operator()(SDL_Window* window_) const{
            if(window_){
                SDL_DestroyWindow(window_);
                std::cout << "Window deleted\n";
            }
        }
    };
    

    struct SDL_GLContextStateDeleter{
        void operator()(SDL_GLContextState* context_) const{
            if(context_) {
                SDL_GL_DestroyContext(context_);
                std::cout << "Context deleted\n";
            }
        }
    };

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
        std::uint64_t frame_count_ = 0;
        std::uint64_t last_time_ = 0;
        bool quit_requested_ = false;
        std::unique_ptr<SDL_Window, SDL_WindowDeleter> window_;
        std::unique_ptr<SDL_GLContextState, SDL_GLContextStateDeleter> context_;
    };
}
