#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/quad.hpp>
#include <array>


int main(){
    std::array<float, 20> vertices1 = {  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
                                         1.0f,  0.0, 0.0f, 1.0f, 1.0f,  
                                         1.0f , 1.0f, 1.0f, 0.0f, 1.0f,
                                         0.0f,  1.0f, 1.0f, 1.0f, 1.0f,};


    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 800);
        azro::Quad quad1(vertices1);
        
        while(!window.should_close()){
            window.poll_events();
            window.clear(250,250,250);
            quad1.draw();
            window.present();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
