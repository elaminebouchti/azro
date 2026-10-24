#include "azro/azro.hpp"
#include <iostream>
#include <SDL3/SDL.h>

std::string azro::version(){
    return "0.1.0";
}

std::string azro::sdl_version(){
    int linked_version = SDL_GetVersion();
    std::string sdl_major = std::to_string(SDL_VERSIONNUM_MAJOR(linked_version));
    std::string sdl_minor = std::to_string(SDL_VERSIONNUM_MINOR(linked_version));
    std::string sdl_micro = std::to_string(SDL_VERSIONNUM_MICRO(linked_version));
    
    std::string sdl_version = sdl_major + '.' + sdl_minor + '.' + sdl_micro;
    return sdl_version;
}

void azro::window_demo(){
    if(!SDL_INIT_VIDEO){
        std::cerr << "SDL initialization failed : " << SDL_GetError() << "\n";
    }
    SDL_Window* window = SDL_CreateWindow("azro 1", 500, 500, 0);
    if(!window){
        std::cerr << "window creation failed: " << SDL_GetError() << "\n";
        SDL_EVENT_QUIT;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    bool is_running = true;
    SDL_Event event;
    SDL_SetRenderVSync(renderer, 1);

    // game loop 
    while(is_running){
        // handel events 
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT  || event.type == SDLK_ESCAPE) is_running = false;
            if(event.type == SDL_EVENT_KEY_DOWN){
                if(event.key.key == SDLK_R){
                    SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                }
                if(event.key.key == SDLK_G){
                    SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                }
                if(event.key.key == SDLK_B){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                }

            }
        }

        SDL_SetRenderDrawColor(renderer, 100, 30, 35, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    
    }

}
