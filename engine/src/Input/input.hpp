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

#include <GLFW/glfw3.h>
#include <vector>

namespace hop{

/* Keyboard class is responsible for accepting keyboard input from user. Keys are bound to callback functions 
 * and the provided function is called when the button is pressed or held. 
 *
 * Usage:   1.) Create keyboard object by providing GLFWwindow* object using the sole constructor. 
 *      2.) Create a void function with no parameters and bind it to a key. 
 * */
class Keyboard{

    private:
    // GLFWwindow* object is needed to implement GLFW callback-style input.
    GLFWwindow* window; 
    // Key callback function is required by GLFW (with these parameters) to handle input callbacks.
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // Inner class Key contains a key and corrosponding callback function.
    struct Key{
        public:
        int code; // The key code as defined by GLFW.
        void (*function)(); // Function pointer to a void function with no parameters. 
        Key(char c, void (*Ptr)()); // Constructor using char as parameter, works for alphanumeric symbols.
        Key(int code, void (*Ptr)()); // Constructor using GLFW key codes, can work for all keys.
    };
    // Vector bindings contains all keys which have been bound.
    static std::vector<Key> bindings;

    public:
    // Necessary GLFW window object.
    Keyboard(GLFWwindow* window);
    // Bind a GLFW key code to a void function with no parameters.
    void bind(int code, void (*Ptr)());
    // Bind a character (and it's opposite-case character) to a void function with no parameters.
    void bind(char c, void (*Ptr)());   
    // Bind a c-style string (eg "left", "space", "tab" to a void function with no parameters.
    bool bind(const char* key_str, void (*Ptr)());
};

}