/** @file input.hpp
 *  @brief Header file for engine input module.
 *
 *  This file contains declarations for all functions and classes necessary to accept input from the user..
 *  As of now, only keyboard inputs have been implemented.
 *  
 *  @author Glen Beatty
 *  @version 1.0
 *  @date November 14th, 2023
 */

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <hop.hpp>
#include <GLFW/glfw3.h>
#include <vector>
namespace hop{
class Game;

class Keyboard{



    public:
    Keyboard(GLFWwindow* window);
    bool monitor_key(int key);
    bool key_pressed(int key);
    bool key_held(int key);
    bool key_released(int key);

    std::vector<int> get_pressed_keys();
    std::vector<int> get_held_keys();
    std::vector<int> get_released_keys();


    private:
    GLFWwindow* window; 
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    inline static std::vector<int> keys_monitored;
    inline static std::vector<int> keys_pressed;
    inline static std::vector<int> keys_held;
    inline static std::vector<int> keys_released;

};

}