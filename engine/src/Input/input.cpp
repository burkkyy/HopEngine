/** @file input.cpp
 *  @brief Implementation of user input functions. 
 *
 *  This file contains definitions for all functions necessary to accept input from the user.
 *  As of now, only keyboard inputs have been implemented.
 *  
 *  @author Glen Beatty
 *  @version 1.0
 *  @date November 14th, 2023
 */


#include "input.hpp"
#include <iostream>
#include <string.h>
#include <ctype.h>

namespace hop{

Keyboard::Keyboard(GLFWwindow* window){
    this->window = window; 
    glfwSetKeyCallback(window, this->key_callback);
}
 

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

    window = window;
    (void)scancode;
    (void)mods;

    bool key_monitored = false;

    for(int k:keys_monitored){
        if(key == k){
            key_monitored = true;
        }
    }
    
    if(key_monitored == false){
        return;
    }

    if(action == GLFW_PRESS){
        keys_pressed.push_back(key);
    }

    if(action == GLFW_REPEAT){
        keys_held.push_back(key);
    }

    if(action == GLFW_RELEASE){
        keys_released.push_back(key);
    }
}

bool Keyboard::key_pressed(int key){
    int i = 0;
    for(int k: keys_pressed){
        if(k == key){
            keys_pressed.erase(keys_pressed.begin()+i);
            return true;
        }
        i++;
    }
    return false;
}

bool Keyboard::key_held(int key){
    int i = 0;
    for(int k: keys_held){
        if(k == key){
            keys_held.erase(keys_held.begin()+i);
            return true;
        }
        i++;
    }
    return false;
}

bool Keyboard::key_released(int key){
    int i = 0;
    for(int k: keys_released){
        if(k == key){
            keys_released.erase(keys_released.begin()+i);
            return true;
        }
        i++;
    }
    return false;
}

bool Keyboard::monitor_key(int key){

    for(int k:keys_monitored){
        if(k == key){
            return true;
        }
    }
    keys_monitored.push_back(key);
    return true;
}

std::vector<int> Keyboard::get_pressed_keys(){
    std::vector<int> tmp = keys_pressed;
    keys_pressed.clear();
    return tmp;
}
std::vector<int> Keyboard::get_held_keys(){
    std::vector<int> tmp = keys_held;
    keys_held.clear();
    return tmp;
}
std::vector<int> Keyboard::get_released_keys(){
    std::vector<int> tmp = keys_released;
    keys_released.clear();
    return tmp;
}
}


