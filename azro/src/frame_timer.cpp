#include "azro/frame_timer.hpp"
#include <thread>
#include <algorithm>
#include <stdexcept>

namespace azro{
    namespace{
        constexpr float MaxDelta = 0.1f;
    }
}

azro::FrameTimer::FrameTimer(int target_fps){
    if(target_fps <= 0) throw std::invalid_argument("the target fps cannot be smaller or equal to zero");
    frame_duration_ = std::chrono::nanoseconds(1'000'000'000LL / target_fps);
    last_ = Clock::now();
    next_ = Clock::now();
}

float azro::FrameTimer::tick(){
    next_ += frame_duration_;
    const auto now = Clock::now();
    if(next_ < now) next_ = now;
    std::this_thread::sleep_until(next_);
    const auto woke = Clock::now();
    std::chrono::duration<float> dt = woke - last_;
    last_ = woke;
    return std::min(dt.count(), azro::MaxDelta);
}
