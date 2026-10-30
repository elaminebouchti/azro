#pragma once
#include <array>

namespace azro{
class Triangle{
    public:
    Triangle(const std::array<float, 15>& vertices);

    ~Triangle();

    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;
    void draw() const;
    private:
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    unsigned int program_ = 0;

};

}
