#pragma once

#include <array>
#include <memory>

namespace azro{
    class Quad{
        public:
        Quad(int window_width, int window_height);
        ~Quad();

        Quad(const Quad&) = delete;
        Quad& operator=(const Quad&) = delete;

        void draw(float x, float y, float w, float h, float r, float g, float b) const;

        private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
