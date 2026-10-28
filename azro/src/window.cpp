#include "azro/window.hpp"
#include "gl/gl.hpp"
#include <SDL3/SDL.h>
#include <stdexcept>
#include <iostream>


void azro::SDL_WindowDeleter::operator()(SDL_Window* window_) const{
    if(window_) SDL_DestroyWindow(window_);
}

void azro::SDL_GLContextStateDeleter::operator()(SDL_GLContextState* context_)const{
    if(context_) SDL_GL_DestroyContext(context_);
}

azro::Window::Window(const std::string& title, int width, int height){
    // Request
    if(!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3)) throw std::runtime_error("Error : Major is not accessible ");
    if(!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3)) throw std::runtime_error("Error : Minor is not accessible");
    if(!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)) throw std::runtime_error("Error : Context Profile Mask or Context profile Core is is not accessible");
    if(!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) throw std::runtime_error("Error : Double Buffer Failed");

    window_ = std::unique_ptr<SDL_Window, SDL_WindowDeleter>(SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL));
    if(!window_) throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    context_ = std::unique_ptr<SDL_GLContextState, SDL_GLContextStateDeleter>(SDL_GL_CreateContext(window_.get()));
    if(!context_) throw std::runtime_error(std::string("Context creation failed : ") + SDL_GetError());
    if(!SDL_GL_MakeCurrent(window_.get(), context_.get())) throw std::runtime_error(std::string("window cannot currently be made : ") + SDL_GetError());
    gl::load_functions();
    gl::print_info();
    gl::Viewport(0, 0, width, height);
    if(!SDL_GL_SetSwapInterval(1)) std::cerr<<"SDL_GL_SetSwapInterval failed : " << SDL_GetError() << "\n";


    // initialize the timer 
    last_time_ = SDL_GetTicks();
}

azro::Window::~Window(){
}

void azro::Window::poll_events(){
    SDL_Event events;
    while(SDL_PollEvent(&events)){
        if(events.type == SDL_EVENT_KEY_DOWN){
            if(events.key.key == SDLK_ESCAPE) quit_requested_ = true;
        }
        if(events.type == SDL_EVENT_QUIT) quit_requested_ = true;
    }
}

bool azro::Window::should_close()const{
    return quit_requested_;
}

void azro::Window::clear(std::uint8_t r, std::uint8_t g, std::uint8_t b){
    // converting the color value to values between 0 and 1
    float rf = static_cast<float>(r) / 255.0f;
    float gf = static_cast<float>(g) / 255.0f;
    float bf = static_cast<float>(b) / 255.0f;

    gl::ClearColor(rf, gf, bf, 1.0f);
    gl::Clear(gl::COLOR_BUFFER_BIT);
}

void azro::Window::present(){
    frame_count_++;
    std::uint64_t current_time = SDL_GetTicks();
    if(current_time - last_time_ >= 1000){
        float elapsed_sec = static_cast<float>(current_time - last_time_) / 1000.0f;
        float fps = static_cast<float>(frame_count_) / elapsed_sec;

        std::string title = "azro Engine | FPS: " + std::to_string(static_cast<int>(fps));
        // reset for the next second
        SDL_SetWindowTitle(window_.get(), title.c_str());
        frame_count_ = 0;
        last_time_ = current_time;
    }
    SDL_GL_SwapWindow(window_.get());

}
