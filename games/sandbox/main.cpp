#include <iostream>
#include "azro/platform.hpp"
#include "azro/window.hpp"


int main(){
    try{
    azro::Platform platform;
    azro::Window window("azro sandbox", 500, 600);
    
    while(!window.should_close()){
        window.Poll_events();
        window.clear(30,30,46);
        window.present();
    }
    }catch(const std::exception& e) {std::cerr << e.what(); return 1;}
    return 0;
}
