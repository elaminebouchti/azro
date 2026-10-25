#include "azro/platform.hpp"
#include <SDL3/SDL.h>

azro::Platform::Platform(){
    SDL_Init(SDL_INIT_VIDEO);
}

azro::Platform::~Platform(){
    SDL_Quit();
}
