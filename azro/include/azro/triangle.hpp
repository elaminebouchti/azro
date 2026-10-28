#pragma once
#include <array>

namespace azro{
class Triangle{
    public:
    unsigned int compile_shader(unsigned int type, const char* source);
    Triangle(std::array<float, 6>& vertices);

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
