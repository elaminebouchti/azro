#include "gl/buffer.hpp"
#include "gl/shaderProgram.hpp"
#include <string>
#include <stdexcept>


namespace azro::gl{
    namespace{
        class Shader{
            public:
            Shader(GLenum type, const char* source){
                ShaderSource(shader_, 1, &source, nullptr);
                CompileShader(shader_);
                GLint success = 0;
                GetShaderiv(shader_, COMPILE_STATUS, &success);
                if(success == gl::FALSE){
                    GLint log_length = 0;
                    GetShaderiv(shader_, INFO_LOG_LENGTH, &log_length);
                    std::string log_info(log_length,'\0');
                    GetProgramInfoLog(shader_, log_length, &log_length, log_info.data());
                    log_info.resize(log_length);
                    throw std::runtime_error(std::string(type == gl::VERTEX_SHADER ? "vertex" : "fragment") + " shader Compilation failed : " + log_info);
                }

            }
            ~Shader(){
                if(shader_ != 0){
                    DeleteShader(shader_);
                }
            }
            Shader(const Shader&) = delete;
            Shader& operator=(Shader&) = delete;

            GLuint id() const{
                return shader_;
            }
            private:
            explicit Shader(GLenum type){
                CreateShader(type);
            }
            GLuint shader_ = 0; 
        };
    }

}
