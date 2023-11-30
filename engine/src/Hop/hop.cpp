#include "../hop.hpp"
#include <Engine/engine.hpp>
#include <chrono>
#include <thread>
#include <memory>
using namespace hop;

Game::Game(const char* window_name){
    graphics_engine = new Engine(window_name);

}

bool Game::set_window_size(int width, int height){
    return graphics_engine->set_window_size(width, height);
}

void Game::run(){
    graphics_engine->run(fullscreen);
    keyboard = new Keyboard(graphics_engine->get_glfw_window());
}

int Game::get_resolution_width(){
    return graphics_engine->get_resolution_width();
}

int Game::get_resolution_height(){
    return graphics_engine->get_resolution_height();
}

bool Game::is_running(){
    return (graphics_engine->engine_valid)&&(!engine_stopped);
}

void Game::update(){
    if(graphics_engine->engine_valid == false){
        this->stop();
        return;
    }
    std::chrono::steady_clock::time_point beginning = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = beginning + std::chrono::milliseconds(5);
    graphics_engine->update();
    
    std::chrono::steady_clock:: time_point intermediate = std::chrono::steady_clock::now();
    std::chrono::duration<double> wait_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - intermediate);
    std::this_thread::sleep_for(wait_time);
}

void Game::set_fullscreen(){
    fullscreen = true;
    set_window_size(get_resolution_width(),get_resolution_height());
}

void Game::set_windowed(){
    this->fullscreen = false;
}

bool Game::monitor_key(int key){
    return keyboard->monitor_key(key);
}

bool Game::key_pressed(int key){
    return keyboard->key_pressed(key);
}

void Game::stop(){
    engine_stopped = true;
}

std::vector<int> Game::get_pressed_keys(){
    return keyboard->get_pressed_keys();
}

std::vector<int> Game::get_held_keys(){
    return keyboard->get_held_keys();
}

std::vector<int> Game::get_released_keys(){
    return keyboard->get_released_keys();
}

std::shared_ptr<hop::Rectangle> Game::create_rectangle(int x, int y, int width, int height, Color color){
    return graphics_engine->create_rectangle(x, y, width, height, color);
}
    
std::shared_ptr<hop::Circle> Game::create_circle(int x, int y, int radius, Color color){
    return graphics_engine->create_circle(x,y,radius,color);
}
