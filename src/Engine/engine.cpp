#include "engine.hpp"

namespace bun {

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
