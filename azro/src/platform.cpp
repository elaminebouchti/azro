#include "azro/platform.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <stdexcept>

azro::Platform::Platform(){
    if(!SDL_Init(SDL_INIT_VIDEO)) throw std::runtime_error(std::string("video display initialiation failed :") + SDL_GetError());
    
}

azro::Platform::~Platform(){
    SDL_Quit();
}
