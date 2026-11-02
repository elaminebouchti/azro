#pragma once
#include <array>
#include <memory>


namespace azro{
class Triangle{
    public:
    Triangle(const std::array<float, 15>& vertices);

    ~Triangle();

    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
    void draw() const;
    private:
    struct Impl;
    std::unique_ptr<Impl> impl_;

};

}
