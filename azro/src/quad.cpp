#include "azro/quad.hpp"
#include "gl/buffer.hpp"
#include "gl/vertexArray.hpp"
#include "gl/shaderProgram.hpp"
#include "gl/gl.hpp"

namespace azro{
    namespace{
        const char* const VertexSrc = R"(
        #version 330 core
        layout(location = 0) in vec2 a_pos;
        layout(location = 1) in vec3 a_color;
        out vec3 vertex_color;
        void main(){
            gl_Position = vec4(a_pos, 0.0, 1.0);
            vertex_color = a_color;
        })";

        const char* const FragmentSrc = R"(
        #version 330 core
        in vec3 vertex_color;
        out vec4 frag_color;
        void main(){
            frag_color = vec4(vertex_color, 1.0f);
        })";

        constexpr std::array<unsigned int, 6> Indices = {0,1,2, 2,3,0};
    }
}

struct azro::Quad::Impl{azro::gl::VertexArray vao; azro::gl::Buffer vbo{azro::gl::ARRAY_BUFFER}; azro::gl::ShaderProgram program{VertexSrc, FragmentSrc}; azro::gl::Buffer ibo{azro::gl::ELEMENT_ARRAY_BUFFER};};

azro::Quad::Quad(const std::array<float, 20>& vertices): impl_(new Impl{}){
    impl_->vbo.upload(sizeof(vertices), vertices.data());

    impl_->vao.index_buffer(impl_->ibo);
    impl_->ibo.upload(sizeof(azro::Indices), azro::Indices.data());
    impl_->vao.attribute(impl_->vbo, 0, 2, static_cast<azro::gl::GLint>(5 * sizeof(float)), 0);
    impl_->vao.attribute(impl_->vbo, 1, 3, static_cast<azro::gl::GLint>(5 * sizeof(float)), 2 * sizeof(float));

}

azro::Quad::~Quad() = default;

void azro::Quad::draw() const{
    impl_->program.use();
    impl_->vao.bind();
    azro::gl::DrawElements(azro::gl::TRIANGLES, 6, azro::gl::UNSIGNED_INT, nullptr);
    azro::gl::check_error("after a Draw : ");
}
