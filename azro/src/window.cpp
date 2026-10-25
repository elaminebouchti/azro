#include "azro/window.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>

azro::Window::Window(const std::string& title, int width, int height){
    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if(!window) throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    renderer = SDL_CreateRenderer(window, nullptr);
    if(!renderer){
        SDL_DestroyWindow(window);
        throw std::runtime_error(std::string("renderer creation failed : ") + SDL_GetError());

    }
    SDL_SetRenderVSync(renderer, 1);

    // initialize the timer 
    last_time = SDL_GetTicks();
}

azro::Window::~Window(){
    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if(window){
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void azro::Window::Poll_events(){
    SDL_Event events;
    while(SDL_PollEvent(&events)){
        if(events.type == SDL_EVENT_KEY_DOWN){
            if(events.key.key == SDLK_ESCAPE) quit_requested = true;
        }
        if(events.type == SDL_EVENT_QUIT) quit_requested = true;
    }
}

bool azro::Window::should_close()const{
    return quit_requested;
}

void azro::Window::clear(std::uint8_t r, std::uint8_t g, std::uint8_t b){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

void azro::Window::present(){
    frame_count++;
    uint64_t current_time = SDL_GetTicks();
    if(current_time - last_time >= 1000){
        float elapsed_sec = static_cast<float>(current_time - last_time) / 1000.0f;
        float fps = static_cast<float>(frame_count) / elapsed_sec;

        std::string title = "azro Engine | FPS: " + std::to_string(static_cast<int>(fps));
        SDL_SetWindowTitle(window, title.c_str());
        
        // reset for the next second
        frame_count = 0;
        last_time = current_time;
    }
    SDL_RenderPresent(renderer);
}
