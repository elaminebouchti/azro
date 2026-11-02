#include "gl/shaderProgram.hpp"
#include <string>
#include <stdexcept>

namespace azro::gl{
    namespace{
        class Shader{
            public:
            Shader(GLenum type, const char* source): Shader(type){
                ShaderSource(shader_, 1, &source, nullptr);
                CompileShader(shader_);
                GLint success = 0;
                GetShaderiv(shader_, COMPILE_STATUS, &success);
                if(success == gl::FALSE){
                    GLint log_length = 0;
                    GetShaderiv(shader_, INFO_LOG_LENGTH, &log_length);
                    std::string log_info(log_length,'\0');
                    GetShaderInfoLog(shader_, log_length, &log_length, log_info.data());
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
            Shader& operator=(const Shader&) = delete;

            GLuint id() const{
                return shader_;
            }
            private:
            explicit Shader(GLenum type): shader_(CreateShader(type)){}
            GLuint shader_ = 0;
        };
    }

    ShaderProgram::ShaderProgram(const char* vertex_src, const char* fragment_src): ShaderProgram(){
        Shader vs(VERTEX_SHADER , vertex_src);
        Shader fs(FRAGMENT_SHADER , fragment_src);

        AttachShader(program_, vs.id());
        AttachShader(program_, fs.id());

        LinkProgram(program_);

        GLint link_success = 0;
        GetProgramiv(program_, LINK_STATUS, &link_success);
        if(link_success == gl::FALSE){
            GLint log_length = 0;
            GetProgramiv(program_, INFO_LOG_LENGTH, &log_length);
            std::string info_log(log_length, '\0');
            GetProgramInfoLog(program_, log_length, &log_length, info_log.data());
            info_log.resize(log_length);
            throw std::runtime_error(std::string("Linking Program Failed : ") + info_log);
        }
    }

    ShaderProgram::~ShaderProgram(){
        if(program_ != 0){
            DeleteProgram(program_);
        }
    }

    void ShaderProgram::use() const{
        UseProgram(program_);
    }

    void ShaderProgram::set_vec4(const char* name, float x, float y, float z, float w){
        use();
        Uniform4f(location(name), x, y, z, w);
    }

    void ShaderProgram::set_mat4(const char* name, const std::array<float, 16>& m){
        use();
        UniformMatrix4fv(location(name), 1, gl::FALSE, m.data());
    }

    GLint ShaderProgram::location(const char* name) const{
        GLint uniform_found = GetUniformLocation(program_, name);
        if(uniform_found == -1) throw std::runtime_error(std::string("uniform not found : ") + name);
        return uniform_found;
    }
}
