#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/triangle.hpp>
#include <array>


int main(){
    std::array<float, 15> vertices1 = { 0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
                                        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  
                                        1.0f , -1.0f, 1.0f, 0.0f, 1.0f};

    std::array<float,15> vertices2  = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                      -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                                      -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,};
    
    std::array<float, 15> vertices3 = { 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                                       -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                                        0.5f, 0.5f, 0.0f, 0.0f, 1.0f,};
    
    std::array<float, 15> vertices4 = { 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
                                       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                                        0.5f, -0.5f, 0.0f, 0.0f, 1.0f,};
    
    std::array<float, 15> vertices5 = { 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
                                        0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
                                        1.0f,  0.0f, 0.0f, 0.0f, 1.0f,};
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 1200, 1200);
        azro::Triangle triangle1(vertices1);
        azro::Triangle triangle2(vertices2);
        azro::Triangle triangle3(vertices3);
        azro::Triangle triangle4(vertices4);
        azro::Triangle triangle5(vertices5);

        
        while(!window.should_close()){
            window.poll_events();
            window.clear(250,250,250);
            triangle1.draw();
            triangle2.draw();   
            triangle3.draw();   
            triangle4.draw();
            triangle5.draw();   
            window.present();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
