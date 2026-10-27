#include "azro/window.hpp"
#include "gl/gl.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>


azro::Window::Window(const std::string& title, int width, int height){
    // required the wanted Context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window_ = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
    if(!window_) throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    if(!SDL_GL_CreateContext(window_)) throw std::runtime_error(std::string("Context creation failed : ") + SDL_GetError());
    if(!SDL_GL_MakeCurrent(window_, context_)) throw std::runtime_error(std::string("window cannot currently be made : ") + SDL_GetError());
    
    SDL_GL_SetSwapInterval(1);


    // initialize the timer 
    last_time_ = SDL_GetTicks();
}

azro::Window::~Window(){

    if(context_){
        SDL_GL_DestroyContext(context_);
        context_ = nullptr;
    }

    if(renderer_){
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }

    if(window_){
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
}

void azro::Window::poll_events(){
    SDL_Event events;
    while(SDL_PollEvent(&events)){
        if(events.type == SDL_EVENT_KEY_DOWN){
            if(events.key.key == SDLK_ESCAPE) quit_requested_ = true;
        }
        if(events.type == SDL_EVENT_QUIT) quit_requested_ = true;
    }
}

bool azro::Window::should_close()const{
    return quit_requested_;
}

void azro::Window::clear(std::uint8_t r, std::uint8_t g, std::uint8_t b){
    SDL_SetRenderDrawColor(renderer_, r, g, b, 255);
    SDL_RenderClear(renderer_);
}

void azro::Window::present(){
    frame_count_++;
    std::uint64_t current_time = SDL_GetTicks();
    if(current_time - last_time_ >= 1000){
        float elapsed_sec = static_cast<float>(current_time - last_time_) / 1000.0f;
        float fps = static_cast<float>(frame_count_) / elapsed_sec;

        std::string title = "azro Engine | FPS: " + std::to_string(static_cast<int>(fps));
        SDL_GL_SwapWindow(window_);
        
        // reset for the next second
        frame_count_ = 0;
        last_time_ = current_time;
    }
    SDL_RenderPresent(renderer_);
}
