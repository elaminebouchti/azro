#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/triangle.hpp>


int main(){
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 600);
        azro::Triangle triangle();
        
        while(!window.should_close()){
            window.poll_events();
            window.clear(0,250,0);
            window.present();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
