#include "azro/triangle.hpp"
#include "gl/gl.hpp"
#include "gl/buffer.hpp"
#include "gl/vertexArray.hpp"
#include "gl/shaderProgram.hpp"

namespace azro{
    namespace{
        const char* const VertexShadersSrc = R"(
        #version 330 core
        layout(location = 0) in vec2 a_pos;
        layout(location = 1) in vec3 a_color;
        out vec3 vertex_color;
        void main(){
            gl_Position = vec4(a_pos, 0.0, 1.0);
            vertex_color = a_color;
        })";

        const char* const FragmentShaderSrc = R"(
        #version 330 core
        in vec3 vertex_color;
        out vec4 frag_color;
        void main(){
            frag_color = vec4(vertex_color, 1.0f);
        })";
    }
}


struct azro::Triangle::Impl{azro::gl::VertexArray vao; azro::gl::Buffer vbo{azro::gl::ARRAY_BUFFER}; azro::gl::ShaderProgram program{azro::VertexShadersSrc, azro::FragmentShaderSrc};};


azro::Triangle::Triangle(const std::array<float, 15>& vertices): impl_(new Impl{}){
    impl_->vbo.upload(sizeof(vertices), vertices.data());

    impl_->vao.attribute(impl_->vbo, 0, 2, 5 * sizeof(float), 0);
    impl_->vao.attribute(impl_->vbo, 1, 3, 5 * sizeof(float), 2 * sizeof(float));
}

azro::Triangle::~Triangle() = default;

void azro::Triangle::draw()const{
    impl_->program.use();
    impl_->vao.bind();
    azro::gl::DrawArrays(azro::gl::TRIANGLES, 0, 3);
    azro::gl::check_error("after draw : ");
}

