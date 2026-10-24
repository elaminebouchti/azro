#include "azro/azro.hpp"
#include <SDL3/SDL.h>

std::string azro::version(){
    return "0.1.0";
}

int azro::sdl_version(){
    return SDL_GetVersion();
}
