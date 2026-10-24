#include <azro/azro.hpp>
#include <iostream>


int main(){
    std::cout<<"Engine : "<< azro::version() << ", using SDL " << azro::sdl_version() <<"\n"; 
    return 0;
}
