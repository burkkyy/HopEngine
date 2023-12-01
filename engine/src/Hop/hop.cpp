#include "../hop.hpp"
#include <Engine/engine.hpp>
#include <chrono>
#include <thread>
#include <memory>
#include <algorithm>
using namespace hop;

Game::Game(const char* window_name){
    graphics_engine = std::make_shared<Engine>(window_name);
        ObjectGroup::set_game(this);


}

bool Game::set_window_size(int width, int height){
    return graphics_engine->set_window_size(width, height);
}

void Game::run(){
    graphics_engine->run(fullscreen);
    keyboard = std::make_shared<Keyboard>(graphics_engine->get_glfw_window());
}

int Game::get_resolution_width(){
    return graphics_engine->get_resolution_width();
}

int Game::get_resolution_height(){
    return graphics_engine->get_resolution_height();
}

bool Game::is_running(){
    return (graphics_engine->window_open)&&(!engine_stopped);
}

void Game::update(){
    if(graphics_engine->window_open == false){
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

Rectangle Game::create_rectangle(int x, int y, int width, int height, Color color){
    return graphics_engine->create_rectangle(x, y, width, height, color);
}
    
Circle Game::create_circle(int x, int y, int radius, Color color){
    return graphics_engine->create_circle(x,y,radius,color);
}

Triangle Game::create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color){
    return graphics_engine->create_triangle(v1x,v1y,v2x,v2y,v3x,v3y,color);
}

ObjectGroup::ObjectGroup(int x, int y,int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool ObjectGroup::create_rectangle(int x, int y, int width, int height, Color color){
    if(((x + width)>this->width)||((y+height)>this->height)){
        return false;
    }
    else{
        game_objects.push_back(game->create_rectangle(x + this->x,y + this->y,width,height,color));
        return true;
    }
}

bool ObjectGroup::create_circle(int x, int y, int radius, Color color){
    
    if((x + (2*radius))>this->width){
        return false;
    }
    else{
        game_objects.push_back(game->create_circle(x + this->x,y + this->y,radius,color));
        return true;
    }
}

bool ObjectGroup::create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color){
    
    int min_x, max_x, min_y, max_y;

    min_x = std::min(v1x,v2x);
    min_x = std::min(min_x,v3x);
    max_x = std::max(v1x,v2x);
    max_x = std::max(max_x,v3x);
    min_y = std::min(v1y,v2y);
    min_y = std::min(min_y,v3y);
    max_y = std::max(v1y,v2y);
    max_y = std::max(max_y,v3y);

    if((min_x<0)||(min_y<0)||((max_x-min_x)>this->width)||((max_y-min_y)>height||(max_x>width)||(max_y>height))){
        return false;
    }

    else{
        game_objects.push_back(game->create_triangle(v1x+x,v1y+y,v2x+x,v2y+y,v3x+x,v3y+y,color));
        return true;
    }
}

void ObjectGroup::set_game(Game* g){
    game = g;
}

void ObjectGroup::set_color(hop::Color color){

}

void ObjectGroup::move(int x, int y){
    for(auto o:game_objects){
        o->move(x,y);
    }
}
