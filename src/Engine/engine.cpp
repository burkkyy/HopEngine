#include "engine.hpp"

namespace hop {

Engine::Engine(){
}

Engine::~Engine(){
}

void Engine::run(){
    while(!win.should_close()){
        glfwPollEvents();
    }
}

}
