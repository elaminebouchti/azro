#include "azro/renderer.hpp"
#include "gl/buffer.hpp"
#include "gl/vertexArray.hpp"
#include "gl/shaderProgram.hpp"
#include "gl/gl.hpp"


namespace azro{
    namespace{
        const char* const VertexShaderSrc = R"(
        #version 330 core
        layout(location = 0) in vec2 a_pos;
        uniform mat4 u_projection;
        uniform vec4 u_rect;
        void main(){
        vec2 pixel = u_rect.xy + a_pos * u_rect.zw;
        gl_Position = u_projection * vec4(pixel, 0.0, 1.0);})";

        const char* const FragmenetShaderSrc = R"(
        #version 330 core
        uniform vec4 u_color;
        out vec4 frag_color;
        void main(){
            frag_color = u_color;
        })";

        constexpr std::array<float, 8> Vertices = {0,0 ,1,0 , 1,1, 0,1};
        constexpr std::array<unsigned int, 6> Indices = {0,1,2, 2,1,0};
    }
}
struct azro::Renderer::Impl{azro::gl::VertexArray vao; azro::gl::Buffer vbo{azro::gl::ARRAY_BUFFER}; azro::gl::ShaderProgram program{VertexShaderSrc, FragmenetShaderSrc};
                            azro::gl::Buffer ibo{azro::gl::ELEMENT_ARRAY_BUFFER}; std::array<float, 16> M;};

azro::Renderer::Renderer(int width, int height){
    impl_->M = {2/static_cast<float>(width), 0, 0, 0, 0, -2/static_cast<float>(height), 0, 0, 0, 0, 1, 0, -1, 1, 0, 1};
    impl_->program.set_mat4("u_projection", impl_->M);

    impl_->vbo.upload(sizeof(azro::Vertices), azro::Vertices.data());
    impl_->vao.index_buffer(impl_->ibo);
    impl_->ibo.upload(sizeof(azro::Indices), azro::Indices.data());
    impl_->vao.attribute(impl_->vbo, 0, 2, static_cast<azro::gl::GLsizei>(2 * sizeof(float)), 0);
    }

azro::Renderer::~Renderer() = default;

void azro::Renderer::draw_rect(float x, float y, float w, float h, azro::Color color) const{
    impl_->program.set_vec4("u_rect", x, y, w, h);
    impl_->program.set_vec4("u_color", color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0f);
    impl_->vao.bind();
    azro::gl::DrawElements(azro::gl::TRIANGLES, 6, azro::gl::UNSIGNED_INT, nullptr);
}



