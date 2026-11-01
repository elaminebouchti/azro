#include "gl/vertexArray.hpp"


azro::gl::VertexArray::VertexArray(azro::gl::GLuint vao): vao_(vao){
    azro::gl::GenVertexArrays(1, &vao_);
    azro::gl::BindVertexArray(vao_);
}

azro::gl::VertexArray::~VertexArray(){
    if(vao_ != 0){
        azro::gl::DeleteVertexArrays(1, &vao_);
    }
}

