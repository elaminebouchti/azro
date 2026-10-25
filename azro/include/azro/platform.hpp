#pragma once

namespace azro{
    class Platform{
        public:
        Platform();
        Platform(const Platform&) = delete;
        Platform& operator=(const Platform&) = delete;
        ~Platform();
    };
}
