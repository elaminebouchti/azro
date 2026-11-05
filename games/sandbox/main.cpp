#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/renderer.hpp>
#include <array>

void print(azro::Window& window, azro::Renderer& renderer, float x, float y){
    window.poll_events();
    window.clear(250, 250, 250);
    renderer.draw_rect(x, y, 50, 50, {250, 250, 0});
    window.present();
}


int main(){
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 800);
        azro::Renderer renderer(800,800);
        float t = 0;
        bool alternate;
        while(!window.should_close()){
            if(t == 0.0f) alternate = true;
            if(t == 750.0f) alternate = false;
            if(alternate){
                t += 0.5f;
                print(window, renderer, t, t);
            }
            else{
                t -= 0.5f;
                print(window, renderer, t, t);
            }


            
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
