#include "azro/frmae_timer.hpp"
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
    frmae_duration_ = std::chrono::nanoseconds(1'000'000'000LL / target_fps);
    last_ = Clock::now();
    next_ = Clock::now();
}

float azro::FrameTimer::tick(){
    next_ += frmae_duration_;;
    if(next_ < Clock::now()) next_ = Clock::now();
    std::this_thread::sleep_until(next_);
    std::chrono::time_point now = Clock::now();
    std::chrono::duration<float> dt = now - last_;
    last_ = now;
    return std::min(dt.count(), azro::MaxDelta);
}
