#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/quad.hpp>
#include <array>


int main(){
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 800);
        azro::Quad quad1(800,800);
        
        while(!window.should_close()){
            window.poll_events();
            window.clear(250,250,250);
            quad1.draw(0, 0, 400, 400, 1.0f, 0.5f, 0.0f);
            quad1.draw(600, 600, 200, 200, 0.0f, 0.4f, 0.0f);
            window.present();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
