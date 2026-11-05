#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/renderer.hpp>
#include <array>


int main(){
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 800);
        azro::Renderer renderer(800,800);
        
        while(!window.should_close()){
            window.poll_events();
            window.clear(250, 250, 250);
            renderer.draw_rect(0, 0, 400, 400, {255, 128, 0});
            renderer.draw_rect(600, 600, 200, 200, {0, 102, 255});
            window.present();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
