
/**
 * @file hop.cpp
 * @author Glen Beatty
 * @date December 8th, 2023
 *
 * Central header file necessary to include and use Hop Engine. 
 * All user-accessible classes and functions are declared in this file. 
 * Please refer to definitions.hpp to see constants.  
 *
 */

#ifndef HOPENGINE_HEADER
#define HOPENGINE_HEADER

#include <Input/input.hpp>
#include <Engine/engine.hpp>
#include "definitions.hpp"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <Audio/audio.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <memory>

namespace hop {
typedef std::shared_ptr<hop::EngineRectangle> Rectangle;
typedef std::shared_ptr<hop::EngineCircle> Circle;
typedef std::shared_ptr<hop::EngineGameObject> Triangle;
typedef std::shared_ptr<hop::EngineGameObject> GameObject;
typedef std::shared_ptr<hop::AudioEngine::EngineSound> Sound;
// Colors objects can be set to
#define RED Color{1.0f, 0.0f, 0.0f}
#define GREEN Color{0.0f, 1.0f, 0.0f}
#define BLUE Color{0.0f, 0.0f, 1.0f}
#define BLACK Color{0.0f, 0.0f, 0.0f}
#define WHITE Color{1.0f, 1.0f, 1.0f}

class Keyboard;

class Game{
    
    public:

    Game(const char* window_name);
    bool set_window_size(int width, int height);
    void set_fullscreen();
    void set_windowed();
    int get_resolution_width();
    int get_resolution_height();
    void run();
    void update();
    bool is_running();
    void stop();
    Rectangle create_rectangle(int x, int y, int width, int height, Color color);
    Circle create_circle(int x, int y, int radius, Color color);
    Triangle create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color);
    Sound create_sound(const char* file_name, bool loop_sound);
    bool monitor_key(int key_code);
    bool key_pressed(int key);
    bool key_held(int key);
    bool key_released(int key);
    std::vector<int> get_pressed_keys();
    std::vector<int> get_held_keys();
    std::vector<int> get_released_keys();

    private:
    AudioEngine audio_engine;
    std::shared_ptr<Engine> graphics_engine;
    std::shared_ptr<Keyboard> keyboard;
    bool engine_stopped = false;
    bool fullscreen = false;
    void console_warning(const char* function, const char* error_msg);
    std::vector<int> valid_keys;
    void initialize_valid_keys();
    static std::vector<int> keys_pressed;
    static std::vector<int> keys_held;
    static std::vector<int> keys_monitored;
};

class Image{

    public:

    Image(int x, int y,int width, int height);
    bool create_rectangle(int x, int y, int width, int height, Color color);
    bool create_circle(int x, int y, int radius, Color color);
    bool create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color);
    bool add_image(int x, int y, Image image);
    void set_color_all(Color color);
    void move(int x, int y);
    inline static void set_game(Game* game);    
    void flip();
    int get_x();
    int get_y();
    int get_height();
    int get_width();

    private:
    int x;
    int y;
    int width;
    int height;
    std::vector<Image> images;
    inline static Game* game;
    void console_warning(const char* function, const char* error_msg);
    std::vector<GameObject> game_objects;

};


class TextBox{

    public:
    
    TextBox(int x, int y, int text_size, Color text_color, const char* text_string);
    void set_color(Color color);

    private:
    int text_size;
    int stride;
    int place;
    Color color;
    std::string string;
    std::shared_ptr<Image> image; 
    void render_text();
    Image render_letter(char c, bool* valid_character);
    void console_warning(const char* function, const char* error_msg);

};
}
#endif 