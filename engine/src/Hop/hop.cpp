#include "../hop.hpp"
#include <Engine/engine.hpp>
#include <chrono>
#include <thread>
#include <memory>
#include <algorithm>
#include <ctype.h>
#include <stdexcept>
using namespace hop;

Game::Game(const char* window_name){
    graphics_engine = std::make_shared<Engine>(window_name);
    Image::set_game(this);
}

bool Game::set_window_size(int width, int height){
    
    if((width<100) && (height<100)){
        console_warning("Game::set_window_size", "Width and height are less than 100 pixels.");
        return false;
    }
    else if(width<100){
        console_warning("Game::set_window_size", "Width is less than 100 pixels.");
        return false;
    }
    else if(height<100){
        console_warning("Game::set_window_size", "Height is less than 100 pixels.");
        return false;
    }
    else{
        return graphics_engine->set_window_size(width, height);
    }
}

void Game::run(){
    graphics_engine->run(fullscreen);
    keyboard = std::make_shared<Keyboard>(graphics_engine->get_glfw_window());
    initialize_valid_keys();
    audio_engine.init();
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
    std::chrono::steady_clock::time_point end = beginning + std::chrono::milliseconds(20);
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
    bool key_valid = false;
    for(int i:valid_keys){
        if(i==key){
            key_valid = true;
            break;
        }
    }
    if(!key_valid){
        console_warning("Game::monitor_key()", "Invalid key provided. Please refer to definitions.hpp for all valid keys.");
    }
    return (key_valid)&&(keyboard->monitor_key(key));
}

bool Game::key_pressed(int key){
    bool key_valid = false;
    for(int i:valid_keys){
        if(i==key){
            key_valid = true;
            break;
        }
    }
    if(!key_valid){
        console_warning("Game::key_pressed()", "Invalid key provided. Please refer to definitions.hpp for all valid keys.");
    }
    return (key_valid)&&(keyboard->key_pressed(key));
}

bool Game::key_held(int key){
    bool key_valid = false;
    for(int i:valid_keys){
        if(i==key){
            key_valid = true;
            break;
        }
    }
    if(!key_valid){
        console_warning("Game::key_held()", "Invalid key provided. Please refer to definitions.hpp for all valid keys.");
    }
    return (key_valid)&&(keyboard->key_held(key));
}

bool Game::key_released(int key){

    bool key_valid = false;
    for(int i:valid_keys){
        if(i==key){
            key_valid = true;
            break;
        }
    }
    if(!key_valid){
        console_warning("Game::key_released()", "Invalid key provided. Please refer to definitions.hpp for all valid keys.");
    }

    return (key_valid)&&(keyboard->key_released(key));
}

void Game::stop(){
    engine_stopped = true;
}

void Game::initialize_valid_keys(){

    valid_keys.push_back(32);
    for(int i = 49; i<58;i++){
        valid_keys.push_back(i);
    }
    valid_keys.push_back(59);
    valid_keys.push_back(61);
   for(int i = 65; i<94;i++){
        valid_keys.push_back(i);
   }
    valid_keys.push_back(256);
    valid_keys.push_back(257);
    valid_keys.push_back(258);
    valid_keys.push_back(259);
    valid_keys.push_back(260);
    valid_keys.push_back(262);
    valid_keys.push_back(263);
    valid_keys.push_back(264);
    valid_keys.push_back(265);
    valid_keys.push_back(280);
    valid_keys.push_back(290);
    valid_keys.push_back(291);
    valid_keys.push_back(292);
    valid_keys.push_back(293);
    valid_keys.push_back(294);
    valid_keys.push_back(295);
    valid_keys.push_back(296);
    valid_keys.push_back(297);
    valid_keys.push_back(298);
    valid_keys.push_back(299);  
    valid_keys.push_back(300);  
    valid_keys.push_back(301);  
    valid_keys.push_back(320);
    valid_keys.push_back(321);
    valid_keys.push_back(322);
    valid_keys.push_back(323);
    valid_keys.push_back(324);
    valid_keys.push_back(325);
    valid_keys.push_back(326);
    valid_keys.push_back(327);
    valid_keys.push_back(328);
    valid_keys.push_back(329);  
    valid_keys.push_back(340);  
    valid_keys.push_back(341);  
    valid_keys.push_back(342);
    valid_keys.push_back(344);
    valid_keys.push_back(345);  
    valid_keys.push_back(346);  
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
    if((width<1)&&(height<1)){
        console_warning("Game::create_rectangle()", "Width and height are less than 1");
        return nullptr;
    }
    else if(width<1){
        console_warning("Game::create_rectangle()", "Width is less than 1");
        return nullptr;
    }
    else if(height<1){
        console_warning("Game::create_rectangle()", "Height is less than 1");
        return nullptr;
    }
    else{
    return graphics_engine->create_rectangle(x, y, width, height, color);

    }
}
    
Circle Game::create_circle(int x, int y, int radius, Color color){
    if(radius<1){
        console_warning("Game::create_circle()", "Radius is less than 1.");
        return nullptr; 
    }
    return graphics_engine->create_circle(x,y,radius,color);
}

Triangle Game::create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color){
    return graphics_engine->create_triangle(v1x,v1y,v2x,v2y,v3x,v3y,color);
}

Sound Game:: create_sound(const char* file_name, bool loop_sound){
    
    Sound return_sound = audio_engine.create_sound(file_name, loop_sound);
    if(return_sound == NULL){
        console_warning("Game::create_sound()", 
        "Sound could not be intialized. Verify that file is correctly named and located in project/sounds.");
    }
    return return_sound;
}

void Game::console_warning(const char* function, const char* error_msg){
    std::cout << "WARNING: Error in " << function << "." << std::endl;
    std::cout << "\t" << error_msg << std::endl << std::endl;
}


Image::Image(int x, int y,int width, int height){
    if((width<1)&&(height<1)){
        console_warning("Image::Image()", "Height and width are less than 1.");
    }
    else if(width<1){
        console_warning("Image::Image()", "Width is less than 1.");
    }
    else if(height<1){
        console_warning("Image::Image()", "Height is less than 1.");
    }
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool Image::create_rectangle(int x, int y, int width, int height, Color color){
    
    if((width<1)&&(height<1)){
        console_warning("Image::create_rectangle()", "Height and width are less than 1.");
        return false;
    }
    else if(width<1){
        console_warning("Image::create_rectangle()", "Width is less than 1.");
        return false;
    }
    else if(height<1){
        console_warning("Image::create_rectangle()", "Height is less than 1.");
        return false;
    }
    else if(((x + width)>this->width)||((y+height)>this->height)){
        console_warning("Image::create_rectangle()", "Rectangle falls outside of Image object boundary.");
        return false;
    }
    else{
        game_objects.push_back(game->create_rectangle(x + this->x,y + this->y,width,height,color));
        return true;
    }
}

bool Image::create_circle(int x, int y, int radius, Color color){
    
    if(radius<1){
        console_warning("Image::create_circle()", "Radius of circle is less than 1.");
        return false;
    }

    else if((x + (2*radius))>this->width){
        console_warning("Image::create_circle()", "Circle falls outside of Image object boundary.");
        return false;
    }
    else{
        game_objects.push_back(game->create_circle(x + this->x,y + this->y,radius,color));
        return true;
    }
}

bool Image::create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color){
    
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
        
        console_warning("Image::create_triangle()", "Triangle falls outside of Image object boundary.");
        return false;
    }

    else{
        game_objects.push_back(game->create_triangle(v1x+x,v1y+y,v2x+x,v2y+y,v3x+x,v3y+y,color));
        return true;
    }
}

void Image::set_game(Game* g){
    game = g;
}

void Image::set_color_all(hop::Color color){
    for(auto obj: game_objects){
        obj->set_color(color);
    }
    for(auto i: images){
        i.set_color_all(color);
    }
}

void Image::move(int x, int y){
    for(auto o:game_objects){
        o->move(x,y);
    }
    for(auto i:images){
        for(auto o:i.game_objects){
            o->move(x,y);
        }
    }
    this->x = this->x + x;
    this->y = this->y + y;
}

bool Image::add_image(int x, int y, Image image){
    
    if(((x + image.width)>this->width)||((y + image.height)>this->height)){
        console_warning("Image::add_image()","Image falls outside of parent Image object boundaries.");
        return false;
    }
    else{
        image.move((this->x - image.x + x), (this->y - image.y + y));
        images.push_back(image);
        return true;
    }

}

void Image::flip(){

    for(auto obj:game_objects){
        int new_x = this->width - obj->x +this->x - obj->width;
        obj->move((new_x - obj->x) +this->x,0);
    }
}
int Image::get_x(){
    return this->x;
}
int Image::get_y(){
    return this->y;
}
int Image::get_width(){
    return this->width;
}
int Image::get_height(){
    return this->height;
}

void Image::console_warning(const char* function, const char* error_msg){
    std::cout << "WARNING: Error in " << function << "." << std::endl;
    std::cout << "\t" << error_msg << std::endl << std::endl;
}

TextBox::TextBox(int x, int y, int text_size, Color text_color, const char* text_string){
    
    if(text_string==nullptr){
        console_warning("TextBox::TextBox()", "Null string provided");
        return;
    }
    
    else if(text_size<1){
        console_warning("Textbox::Textbox()", "Text size is less than 1. Please enter a size of 1 or larger");
        return;
    }

    else{
        this->string = text_string;
        this->text_size = text_size;
        this->color = text_color;
        this->stride = 20*text_size;
        this->place = 0;
        image = std::make_shared<Image>(x, y, (20*text_size*string.size()),20*text_size);
        render_text();
    }
}

void TextBox::render_text(){

    for(unsigned int i=0; i<string.size();i++){
        bool valid_character = true;
        Image tmp = render_letter(string[i],&valid_character);
        if(valid_character){
            image->add_image(place,0,tmp);
            this->place = this->place + this->stride;
        }        
    }
}

Image TextBox::render_letter(char c, bool* valid_character){

    c = toupper(c);
    Image letter(0,0,text_size*16,text_size*20);
    int s = text_size;
    switch (c) {
        
        case 'A':
        letter.create_rectangle(0,0,4*s,16*s,color);
        letter.create_rectangle(12*s,0,4*s,16*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        break;
        
        case 'B':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,0,8*s,4*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        letter.create_rectangle(12*s,12*s,4*s,4*s,color);
        letter.create_rectangle(12*s,4*s,4*s,4*s,color);
        break;

        case 'C':
        letter.create_rectangle(0,4*s,4*s,12*s,color);
        letter.create_rectangle(4*s,0,12*s,4*s,color);
        letter.create_rectangle(4*s,16*s,12*s,4*s,color);
        break;

        case 'D':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,0,8*s,4*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        letter.create_rectangle(12*s,4*s,4*s,12*s,color);
        break;

        case 'E':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,0,12*s,4*s,color);
        letter.create_rectangle(4*s,16*s,12*s,4*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        break;

        case 'F':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,16*s,12*s,4*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        break;
    
        case 'G':
        letter.create_rectangle(0,4*s,4*s,12*s,color);
        letter.create_rectangle(4*s,0,12*s,4*s,color);
        letter.create_rectangle(4*s,16*s,12*s,4*s,color);
        letter.create_rectangle(12*s,4*s,4*s,8*s,color);
        letter.create_rectangle(8*s,8*s,4*s,4*s,color);
        break;

        case 'H':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        letter.create_rectangle(12*s,0,4*s,20*s,color);
        break;

        case 'I':
        letter.create_rectangle(8*s,4*s,4*s,12*s,color);
        letter.create_rectangle(4*s,16*s,12*s,4*s,color);
        letter.create_rectangle(4*s,0,12*s,4*s,color);
        break;

        case 'J':
        letter.create_rectangle(12*s,4*s,4*s,16*s,color);
        letter.create_rectangle(4*s,0,8*s,4*s,color);
        letter.create_rectangle(0,4*s,4*s,4*s,color);
        break;

        case 'K':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,8*s,4*s,4*s,color);
        letter.create_rectangle(8*s,4*s,4*s,4*s,color);
        letter.create_rectangle(8*s,12*s,4*s,4*s,color);
        letter.create_rectangle(12*s,16*s,4*s,4*s,color);
        letter.create_rectangle(12*s,0*s,4*s,4*s,color);
        break;

        case 'L':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,0*s,8*s,4*s,color);
        break;

        case 'M':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(12*s,0,4*s,20*s,color);
        letter.create_rectangle(6*s,0,4*s,16*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        break;

        case 'N':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(12*s,0,4*s,20*s,color);
        letter.create_rectangle(4*s,12*s,4*s,4*s,color);
        letter.create_rectangle(8*s,8*s,8*s,4*s,color);
        break;

        case 'O':
        letter.create_rectangle(0,4*s,4*s,12*s,color);
        letter.create_rectangle(12*s,4*s,4*s,12*s,color);
        letter.create_rectangle(4*s,0*s,8*s,4*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        break;

        case 'P':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        letter.create_rectangle(12*s,12*s,4*s,4*s,color);
        break;

        case 'Q':
        letter.create_rectangle(0,4*s,4*s,12*s,color);
        letter.create_rectangle(12*s,4*s,4*s,12*s,color);
        letter.create_rectangle(4*s,0*s,8*s,4*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        letter.create_rectangle(12*s,0*s,4*s,4*s,color);
        letter.create_rectangle(8*s,4*s,4*s,4*s,color);
        break;

        case 'R':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,16*s,8*s,4*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        letter.create_rectangle(12*s,12*s,4*s,4*s,color);
        letter.create_rectangle(12*s,0*s,4*s,4*s,color);
        letter.create_rectangle(8*s,4*s,4*s,4*s,color);
        break;

        case 'S':
        letter.create_rectangle(0,12*s,4*s,4*s,color);
        letter.create_rectangle(0,0,12*s,4*s,color);
        letter.create_rectangle(4*s,16*s,12*s,4*s,color);
        letter.create_rectangle(4*s,8*s,8*s,4*s,color);
        letter.create_rectangle(12*s,4*s,4*s,4*s,color);
        break;

        case 'T':
        letter.create_rectangle(6*s,0,4*s,16*s,color);
        letter.create_rectangle(0*s,16*s,16*s,4*s,color);
        break;

        case 'U':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(4*s,0,8*s,4*s,color);
        letter.create_rectangle(12*s,0,4*s,20*s,color);
        break;
        
        case 'V':
        letter.create_rectangle(2*s,4*s,4*s,16*s,color);
        letter.create_rectangle(6*s,0,4*s,4*s,color);
        letter.create_rectangle(10*s,4*s,4*s,16*s,color);
        break;

        case 'W':
        letter.create_rectangle(0,0,4*s,20*s,color);
        letter.create_rectangle(12*s,0,4*s,20*s,color);
        letter.create_rectangle(6*s,4*s,4*s,16*s,color);
        letter.create_rectangle(4*s,0*s,8*s,4*s,color);
        break;

        case 'X':
        letter.create_rectangle(2*s,0,4*s,8*s,color);
        letter.create_rectangle(2*s,12*s,4*s,8*s,color);
        letter.create_rectangle(6*s,8*s,4*s,4*s,color);
        letter.create_rectangle(10*s,0,4*s,8*s,color);
        letter.create_rectangle(10*s,12*s,4*s,8*s,color);
        break;

        case 'Y':
        letter.create_rectangle(6*s,0,4*s,8*s,color);
        letter.create_rectangle(2*s,12*s,4*s,8*s,color);
        letter.create_rectangle(6*s,8*s,4*s,4*s,color);
        letter.create_rectangle(10*s,12*s,4*s,8*s,color);
        break;

        case 'Z':
        letter.create_rectangle(0,0,16*s,4*s,color);
        letter.create_rectangle(0,16*s,16*s,4*s,color);
        letter.create_rectangle(2*s,4*s,4*s,4*s,color);
        letter.create_rectangle(6*s,8*s,4*s,4*s,color);
        letter.create_rectangle(10*s,12*s,4*s,4*s,color);
        break;

        case '.':
        letter.create_rectangle(0*s,0,4*s,4*s,color);
        break;

        case ',':
        letter.create_rectangle(2*s,0,2*s,4*s,color);
        letter.create_rectangle(0*s,0,2*s,2*s,color);

        break;


        case '!':
        letter.create_rectangle(6*s,0,4*s,4*s,color);
        letter.create_rectangle(6*s,8*s,4*s,12*s,color);
        break;

        case '?':
        letter.create_rectangle(2*s,0,4*s,4*s,color);
        letter.create_rectangle(2*s,16*s,8*s,4*s,color);
        letter.create_rectangle(10*s,12*s,4*s,4*s,color);
        letter.create_rectangle(2*s,8*s,8*s,4*s,color);
        break;

        case '1':
        letter.create_rectangle(2*s,0,12*s,4*s,color);
        letter.create_rectangle(6*s,4*s,4*s,16*s,color);
        letter.create_rectangle(2*s,12*s,4*s,4*s,color);
        break;

        case '2':
        letter.create_rectangle(2*s,0,12*s,4*s,color); 
        letter.create_rectangle(2*s,4*s,4*s,4*s,color);
        letter.create_rectangle(6*s,8*s,4*s,4*s,color);
        letter.create_rectangle(10*s,12*s,4*s,4*s,color);
        letter.create_rectangle(2*s,16*s,12*s,4*s,color); 
        break;

        case '3':
        letter.create_rectangle(2*s,0,12*s,4*s,color); 
        letter.create_rectangle(10*s,4*s,4*s,4*s,color);
        letter.create_rectangle(6*s,8*s,4*s,4*s,color);
        letter.create_rectangle(10*s,12*s,4*s,4*s,color);
        letter.create_rectangle(2*s,16*s,12*s,4*s,color); 
        break;

        case '4':
        letter.create_rectangle(10*s,0,4*s,20*s,color);
        letter.create_rectangle(6*s,8*s,4*s,4*s,color); 
        letter.create_rectangle(2*s,8*s,4*s,12*s,color);
        break;

        case '5':
        letter.create_rectangle(2*s,0,12*s,4*s,color);
        letter.create_rectangle(2*s,8*s,12*s,4*s,color);
        letter.create_rectangle(2*s,16*s,12*s,4*s,color);
        letter.create_rectangle(2*s,12*s,4*s,4*s,color);
        letter.create_rectangle(10*s,4*s,4*s,4*s,color);
        break;

        case '6':
        letter.create_rectangle(2*s,0,12*s,4*s,color);
        letter.create_rectangle(2*s,8*s,12*s,4*s,color);
        letter.create_rectangle(2*s,16*s,12*s,4*s,color);
        letter.create_rectangle(2*s,12*s,4*s,4*s,color);
        letter.create_rectangle(2*s,4*s,4*s,4*s,color);
        letter.create_rectangle(10*s,4*s,4*s,4*s,color);
        break;

        case '7':
        letter.create_rectangle(2*s,16*s,12*s,4*s,color);
        letter.create_rectangle(10*s,0*s,4*s,16*s,color);
        break;

        case '8':
        letter.create_rectangle(2*s,0,12*s,4*s,color);
        letter.create_rectangle(2*s,8*s,12*s,4*s,color);
        letter.create_rectangle(2*s,16*s,12*s,4*s,color);
        letter.create_rectangle(2*s,12*s,4*s,4*s,color);
        letter.create_rectangle(2*s,4*s,4*s,4*s,color);
        letter.create_rectangle(10*s,4*s,4*s,4*s,color);
        letter.create_rectangle(10*s,12*s,4*s,4*s,color);
        break;

        case '9':
        letter.create_rectangle(2*s,16*s,12*s,4*s,color);
        letter.create_rectangle(10*s,0*s,4*s,16*s,color);
        letter.create_rectangle(2*s,8*s,4*s,8*s,color);
        letter.create_rectangle(6*s,8*s,4*s,4*s,color);
        break;

        case ' ':
        break;

        default:
        *valid_character = false;
        break;

    }

    return letter;
    
}

void TextBox::set_color(Color color){   
    image->set_color_all(color);
}

void TextBox::console_warning(const char* function, const char* error_msg){
    std::cout << "WARNING: Error in " << function << "." << std::endl;
    std::cout << "\t" << error_msg << std::endl << std::endl;
}
