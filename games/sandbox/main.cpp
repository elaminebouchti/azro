#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/renderer.hpp>
#include <array>

void print(azro::Window& window, azro::Renderer& renderer, float x, float y){
    window.poll_events();
    window.clear(250, 250, 250);
    renderer.draw_rect(x, y, 50, 50, {250, 0, 0});
    window.present();
}


int main(){
    try{
        azro::Platform platform;
        azro::Window window("azro sandbox", 800, 800);
        azro::Renderer renderer(800,800);

        float t = 0;
        bool alternate = true;

        constexpr float Cell = 100.0f;
        constexpr azro::Color Light{235, 235, 210};
        constexpr azro::Color Dark{10, 10, 0};

        while(!window.should_close()){
            window.poll_events();

            float center_x = t + 25;
            float center_y = t + 25;
            int hl_col = static_cast<int>(center_x / Cell);
            int hl_row = static_cast<int>(center_y / Cell);
            float hl_x = static_cast<float>(hl_col) * Cell;
            float hl_y = static_cast<float>(hl_row) * Cell;

            window.clear(250, 250, 250);

            for(int row = 0; row < 8; row++){
                for(int col = 0; col < 8; col++){
                    if((row + col) % 2 == 0){
                        renderer.draw_rect(static_cast<float>(col) * Cell, static_cast<float>(row) * Cell, 100, 100, Light);
                    }
                    else{
                        renderer.draw_rect(static_cast<float>(col) * Cell, static_cast<float>(row) * Cell, 100, 100, Dark);
                    }
                }
            }

            renderer.draw_rect(hl_x , hl_y, Cell, Cell, {150, 150, 150});

            if(t <= 0.0) alternate = true;
            if(t >= 700.0f) alternate = false;
            if(alternate){
                t += 0.1f;
                renderer.draw_rect(t, t, 100, 100, {250, 0, 0});
            }
            else{
                t -= 0.1f;
                renderer.draw_rect(t, t, 100, 100, {250, 0, 0});
            }

            window.present();
        }
    }catch(const std::exception& e) {std::cerr << e.what() << "\n"; return 1;}
    return 0;
}
