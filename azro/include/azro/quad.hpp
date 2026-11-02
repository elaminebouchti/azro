#pragma once

#include <utility>
#include <array>
#include <memory>

namespace azro{
    class Quad{
        public:
        Quad(const std::array<float, 20>& vertices);
        ~Quad();

        Quad(const Quad&) = delete;
        Quad& operator=(const Quad&) = delete;

        void draw() const;

        private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}
