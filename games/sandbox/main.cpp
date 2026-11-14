#include <cmath>
#include <iostream>
#include <azro/platform.hpp>
#include <azro/window.hpp>
#include <azro/renderer.hpp>
#include <azro/frame_timer.hpp>


struct Vec2 {
    float x, y;
};

int main(){
    try {
        constexpr float Width  = 800.0f;
        constexpr float Height = 800.0f;

        azro::Platform platform;
        azro::Window window("azro sandbox", static_cast<int>(Width), static_cast<int>(Height));
        azro::Renderer renderer(static_cast<int>(Width), static_cast<int>(Height));

        constexpr float Speed = 200.0f;
        constexpr float Size  = 100.0f;
        constexpr float Cell  = 100.0f;
        constexpr azro::Color Light{235, 235, 210};
        constexpr azro::Color Dark{10, 20, 0};
        constexpr azro::Color Red{255, 0, 0};

        constexpr float MaxX = Width  - Size;
        constexpr float MaxY = Height - Size;

        const float alpha = std::atan2(-200.0f, 300.0f);
        float angle = 0.0f;

        Vec2 pos{0.0f, 200.0f};
        Vec2 vel{Speed * std::cos(alpha), Speed * std::sin(alpha)};

        azro::FrameTimer timer(60);
        while (!window.should_close()) {
            const float dt = timer.tick();
            window.poll_events();
            window.clear(250, 250, 250);

            angle += 3.0f * dt;
            pos.x += vel.x * dt;
            pos.y += vel.y * dt;

            if (pos.x < 0.0f)      { pos.x = -pos.x;            vel.x = -vel.x; }
            else if (pos.x > MaxX) { pos.x = 2.0f * MaxX - pos.x; vel.x = -vel.x; }

            if (pos.y < 0.0f)      { pos.y = -pos.y;            vel.y = -vel.y; }
            else if (pos.y > MaxY) { pos.y = 2.0f * MaxY - pos.y; vel.y = -vel.y; }

            pos.x = std::fmin(std::fmax(pos.x, 0.0f), MaxX);
            pos.y = std::fmin(std::fmax(pos.y, 0.0f), MaxY);

            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    const azro::Color c = (row + col) % 2 == 0 ? Light : Dark;
                    renderer.draw_rect(static_cast<float>(col) * Cell,
                                       static_cast<float>(row) * Cell,
                                       Cell, Cell, c);
                }
            }
            renderer.draw_rect(pos.x, pos.y, Size, Size, Red, angle);

            window.present();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
