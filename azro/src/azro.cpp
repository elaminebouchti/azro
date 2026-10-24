#include "azro/azro.hpp"
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
