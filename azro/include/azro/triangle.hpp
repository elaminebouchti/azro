#pragma once
#include <array>

namespace azro{
class Triangle{
    public:
    void create_vertex_shader(const char* VertexShader);
    void create_fragement_shader(const char* FragmentShader);
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
