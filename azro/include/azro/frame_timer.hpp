#pragma once
#include <chrono>


namespace azro{
    class FrameTimer{
        public:
        explicit FrameTimer(int target_fps);
        float tick();

        private:
        using Clock = std::chrono::steady_clock;
        Clock::duration frame_duration_;
        Clock::time_point last_;
        Clock::time_point next_;
    };
}
