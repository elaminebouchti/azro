#include "gl/texture.hpp"



azro::gl::Texture::Texture(int width, int height, const void* rgba_pixels): type_(TEXTURE_2D){
    azro::gl::GenTextures(1 , &id_);
    azro::gl::BindTexture(TEXTURE_2D, id_);
    azro::gl::TexParameteri(TEXTURE_2D, TEXTURE_MIN_FILTER, TEXTURE_NEAREST);
    azro::gl::TexParameteri(TEXTURE_2D, TEXTURE_MAG_FILTER, TEXTURE_NEAREST);
    azro::gl::TexParameteri(TEXTURE_2D, TEXTURE_WRAP_S, CLAMP_TO_EDGE);
    azro::gl::TexParameteri(TEXTURE_2D, TEXTURE_WRAP_T, CLAMP_TO_EDGE);

    azro::gl::TexImage2D(TEXTURE_2D, 0, TEXTURE_RGBA8, width, height, 0, TEXTURE_RGBA, UNSIGNED_BYTE, rgba_pixels);
}

azro::gl::Texture::~Texture(){
    if(id_ != 0){
        azro::gl::DeleteTextures(1, &id_);
    }
}

void azro::gl::Texture::bind() const{
    azro::gl::BindTexture(type_, id_);
}
