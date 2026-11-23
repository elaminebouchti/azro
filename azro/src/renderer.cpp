#include "azro/renderer.hpp"
#include "gl/buffer.hpp"
#include "gl/vertexArray.hpp"
#include "gl/shaderProgram.hpp"
#include "gl/gl.hpp"
#include "gl/texture.hpp"
#include <SDL3/SDL.h>
#include <array>
#include <cmath>
#include <cstddef>
#include <vector>


namespace azro{
    namespace{
        using SurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)>;

        struct BatchVertex{ float x, y; float r, g, b, a;};

        const char* const VertexShaderSrc = R"(
        #version 330 core
        layout(location = 0) in vec2 a_pos;
        layout(location = 1) in vec4 a_color;
        uniform mat4 u_projection;
        out vec4 v_color;
        void main(){
            v_color = a_color;
            gl_Position = u_projection * vec4(a_pos, 0.0, 1.0);})";

        const char* const FragmentShaderSrc = R"(
        #version 330 core
        in vec4 v_color;
        out vec4 frag_color;
        void main(){
            frag_color = v_color;
        })";

        const char* const SpriteVertexShaderSrc = R"(
        #version 330 core
        layout(location = 0) in vec2 a_pos;
        uniform mat4 u_projection;
        uniform mat4 u_model;
        out vec2 v_uv;
        void main(){
            v_uv = a_pos + vec2(0.5);
            gl_Position = u_projection * u_model * vec4(a_pos, 0.0, 1.0);})";

        const char* const SpriteFragmentShaderSrc = R"(
        #version 330 core
        in vec2 v_uv;
        uniform sampler2D u_texture;
        out vec4 frag_color;
        void main(){
            frag_color = texture(u_texture, v_uv);})";

        constexpr std::array<float, 8> Vertices = {-0.5f,-0.5f ,0.5f,-0.5f , 0.5f,0.5f, -0.5f,0.5f};
        constexpr std::array<unsigned int, 6> Indices = {0,1,2, 2,3,0};
        constexpr int MaxQuads = 1000;

        std::array<float, 16> model_matrix(float x, float y, float w, float h, float angle){
            float c = std::cos(angle), s = std::sin(angle);
            float cx = x + 0.5f * w, cy = y + 0.5f * h;
            const std::array<float, 16> model = {
                w * c, w * s, 0, 0,
               -h * s, h * c, 0, 0,
                0    ,     0, 1, 0,
                cx   ,    cy, 0, 1,  
                
            };
            return model;
        }

    }
}

struct azro::Renderer::Impl{azro::gl::VertexArray vao; azro::gl::Buffer vbo{azro::gl::ARRAY_BUFFER}; azro::gl::VertexArray batch_vao; azro::gl::Buffer batch_vbo{azro::gl::ARRAY_BUFFER};
                            azro::gl::Buffer batch_ibo{azro::gl::ELEMENT_ARRAY_BUFFER}; azro::gl::ShaderProgram batch_program{VertexShaderSrc, FragmentShaderSrc};
                            azro::gl::GLint batch_u_projection = batch_program.uniform_location("u_projection"); std::vector<BatchVertex> batch; std::uint32_t draw_calls = 0;
                            azro::gl::ShaderProgram sprite_program{SpriteVertexShaderSrc, SpriteFragmentShaderSrc}; azro::gl::Buffer ibo{azro::gl::ELEMENT_ARRAY_BUFFER}; std::array<float, 16> M;
                            azro::gl::GLint sprite_u_projection = sprite_program.uniform_location("u_projection");
                            azro::gl::GLint sprite_u_model = sprite_program.uniform_location("u_model");
                            std::vector<azro::gl::Texture> textures;};

azro::Renderer::Renderer(int width, int height): impl_(new azro::Renderer::Impl{}){
    std::vector<unsigned int> BatchIndices;
    BatchIndices.reserve(MaxQuads * 6);
    for(int q = 0; q < MaxQuads; ++q){
        for(int i = 0; i < 3; ++i) BatchIndices.push_back(static_cast<unsigned int>(4 * q + i));
        for(int i = 2; i < 5; ++i) BatchIndices.push_back(static_cast<unsigned int>(4 * q + i % 4));
    }

    impl_->M = {2/static_cast<float>(width), 0, 0, 0, 0, -2/static_cast<float>(height), 0, 0, 0, 0, 1, 0, -1, 1, 0, 1};
    impl_->batch_program.set_mat4(impl_->batch_u_projection, impl_->M);
    impl_->sprite_program.set_mat4(impl_->sprite_u_projection, impl_->M);
    azro::gl::Enable(azro::gl::BLEND);
    azro::gl::BlendFunc(azro::gl::SRC_ALPHA, azro::gl::ONE_MINUS_SRC_ALPHA);

    impl_->batch_vao.index_buffer(impl_->batch_ibo);
    impl_->batch_ibo.upload(static_cast<azro::gl::GLsizeiptr>(BatchIndices.size() * sizeof(unsigned int)), BatchIndices.data());
    impl_->batch.reserve(MaxQuads * 4);

    impl_->batch_vao.attribute(impl_->batch_vbo, 0, 2, static_cast<azro::gl::GLsizei>(sizeof(BatchVertex)), offsetof(BatchVertex, x));
    impl_->batch_vao.attribute(impl_->batch_vbo, 1, 4, static_cast<azro::gl::GLsizei>(sizeof(BatchVertex)), offsetof(BatchVertex, r));

    impl_->vbo.upload(sizeof(azro::Vertices), azro::Vertices.data());
    impl_->vao.attribute(impl_->vbo, 0, 2, static_cast<azro::gl::GLsizei>(2 * sizeof(float)), 0);
    impl_->vao.index_buffer(impl_->ibo);
    impl_->ibo.upload(sizeof(Indices), Indices.data());
    }

azro::Renderer::~Renderer() = default;
azro::Renderer::Renderer(azro::Renderer&&) noexcept = default;
azro::Renderer& azro::Renderer::operator=(azro::Renderer&&) noexcept = default;

void azro::Renderer::draw_rect(float x, float y, float w, float h,azro::Color color, float angle){
    if(impl_->batch.size() == MaxQuads * 4) flush();
    float c = std::cos(angle), s = std::sin(angle);
    float cx = x + 0.5f * w, cy = y + 0.5f * h;
    float r = color.r / 255.0f, g = color.g / 255.0f, b = color.b / 255.0f, a = 1.0f;
    for(int i = 0; i < 4; ++i){
        float lx = Vertices[2 * i] * w, ly = Vertices[2 * i + 1] * h;
        float px = cx + c * lx - s * ly, py = cy + s * lx + c * ly;
        impl_->batch.push_back({px, py, r, g, b, a});
    }
}

azro::TextureId azro::Renderer::load_texture(const char* path){
    SurfacePtr loaded(SDL_LoadPNG(path), SDL_DestroySurface);
    if(!loaded) throw std::runtime_error(std::string("surface cannot be loaded : " ) + SDL_GetError());
    SurfacePtr converted(SDL_ConvertSurface(loaded.get(), SDL_PIXELFORMAT_RGBA32), SDL_DestroySurface);
    if(!converted) throw std::runtime_error(std::string("surface conversion failed : ") + SDL_GetError());
    if(converted->pitch != converted->w * 4){
        throw std::runtime_error(std::string("unexpected row padding (pitch != width * 4)"));
    }
    impl_->textures.emplace_back(converted->w, converted->h, converted->pixels);

    return TextureId{static_cast<std::uint32_t>(impl_->textures.size() - 1)};
}

void azro::Renderer::draw_sprite(TextureId texture, float x, float y, float w, float h, float angle){
    flush();
    const auto& tex = impl_->textures.at(texture.index);
    const std::array<float, 16> model = model_matrix(x, y, w, h, angle);
    impl_->sprite_program.set_mat4(impl_->sprite_u_model, model);
    tex.bind();
    impl_->vao.bind();
    azro::gl::DrawElements(azro::gl::TRIANGLES, 6, azro::gl::UNSIGNED_INT, nullptr);
    ++impl_->draw_calls;
    azro::gl::check_error("error in Draw Sprite : ");
}

void azro::Renderer::flush(){
    if(impl_->batch.empty()) return;
    impl_->batch_vbo.upload(static_cast<azro::gl::GLsizeiptr>(impl_->batch.size() * sizeof(BatchVertex)), impl_->batch.data(), azro::gl::DYNAMIC_DRAW);
    impl_->batch_program.use();
    impl_->batch_vao.bind();
    const auto index_count = static_cast<azro::gl::GLsizei>((impl_->batch.size() / 4) * Indices.size());
    azro::gl::DrawElements(azro::gl::TRIANGLES, index_count, azro::gl::UNSIGNED_INT, nullptr);
    azro::gl::check_error("error in flush : ");
    ++impl_->draw_calls;
    impl_->batch.clear();
}

std::uint32_t azro::Renderer::take_draw_calls(){
    std::uint32_t calls = impl_->draw_calls;
    impl_->draw_calls = 0;
    return calls;
}
