#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/renderer.hpp>
#include <azro/frame_timer.hpp>


int main(){
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 800);
        azro::Renderer renderer(800,800);

        constexpr float Speed = 200.0f;
        constexpr float size = 100.0f;
        constexpr float Cell = 100.0f;
        constexpr azro::Color Light{235, 235, 210};
        constexpr azro::Color Dark{10, 10, 0};
                

        float t = 0;
        float speed = Speed;
        float dt = 0.0f;
        azro::FrameTimer timer(60);
        while(!window.should_close()){
            window.poll_events();
            window.clear(250, 250, 250);

            t += speed * dt;
            if(t <= 0.0f){
                t = 0.0f;
                speed = Speed;
            }
            if(t >= 800.0f - size){
                t = 800.0f - size;
                speed = -Speed;
            }
            float center_x = t + size / 2;
            float center_y = t + size / 2;
            int hl_col = static_cast<int>(center_x / Cell);
            int hl_row = static_cast<int>(center_y / Cell);
            float hl_x = static_cast<float>(hl_col) * Cell;
            float hl_y = static_cast<float>(hl_row) * Cell;


            for(int row = 0; row < 8; row++){
                for(int col = 0; col < 8; col++){
                    const azro::Color c = (row + col) % 2 == 0 ? Light : Dark;
                    renderer.draw_rect(static_cast<float>(col) * Cell, static_cast<float>(row) * Cell, Cell, Cell, c);
                }
            }

            renderer.draw_rect(hl_x, hl_y, Cell, Cell, {150, 150, 150});
            renderer.draw_rect(t, t, size , size, {250, 0, 0});

            window.present();

            dt = timer.tick();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
