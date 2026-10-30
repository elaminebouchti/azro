#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/triangle.hpp>


int main(){
    std::array<float, 15> vertices = { 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
                                      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  
                                       0.5f , -0.5f, 0.0f, 0.0f, 1.0f};
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 600);
        azro::Triangle triangle(vertices);
        
        while(!window.should_close()){
            window.poll_events();
            window.clear(0,0,100);
            triangle.draw();    
            window.present();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
