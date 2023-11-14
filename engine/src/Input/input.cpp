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

// Necessary to define vector bindings here because it is static. 
std::vector<Keyboard::Key> Keyboard::bindings;

// Sole constructor for Keyboard class. Requires a pointer to the GLFW window object to implement GLFW callback function.
Keyboard::Keyboard(GLFWwindow* window){
    this->window = window; // Store the window object for future use.
    
    /* Use GLFW's native key callback function. First parameter is the GLFWwindow* which was provided via Keyboard
     * constructor. Second parameter is the key_callback function defined below.
     */
    glfwSetKeyCallback(window, this->key_callback);
}
 
/* Callback function require to use GLFW's native input callback. Function must be defined with these parameters. 
 * This function is called whenever *any* key is pressed, held, or released.
*/
void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

    // Silence compiler warnings (unused variable). These parameters must be accepted due to pre-defined callback function.
    window = window;
    (void)scancode;
    (void)mods;
    
    // Iterate over all currently bound keys.
    for(Key k: bindings){
        // If the pressed key is equal to the bound key and that key has either been pressed or is being held.
        if((k.code == key)&&((action==GLFW_PRESS)||(action==GLFW_REPEAT))){
            // Then call the function (void with no parameters) which is bound to that key.
            k.function();
        }
    }
}

/* Constructor that binds a callback function (void w/ no parameters) to a key provided as a char. 
 * Works for all number (0-9) and letter keys, inclusive of their opposite case version. For example,
 * binding to 'a' is the same as binding to 'A'.
 */
Keyboard::Key::Key(char c, void (*Ptr)()){
    // Check to see if c is a number (0-9)
    if(((c - '0')>-1)&&((c - '0'<10))){
        // If it is a number, convert to GLFW code.
        this->code = (int)(c - '0' + 48);
        // Store the function pointer.
        this->function = Ptr;
    }
    else{
        // If it's a letter, convert the letter to uppercase.
        c = toupper(c);
        // Convert the character to an integer. GLFW codes match UTF-8 numerical codes for letters.
        this->code = (int)c;
        // Store the function pointer.
        this-> function = Ptr;
    }
}

//Base constructor which binds a GLFW key code to a void function with no parameters. 
Keyboard::Key::Key(int code, void (*Ptr)()){
    this->code = code;
    this-> function = Ptr;
}

// Bind a callback function to a key using the key's GLFW character code. 
void Keyboard::bind(int code, void (*Ptr)()){
    bindings.push_back(Key(code,Ptr));
}

// Bind a callback function to a key using the key's char representation (0-9), (a-z), (A-Z).
// Not caps sensitive. 'a' and 'A' are the same. 
void Keyboard::bind(char c, void (*Ptr)()){
    bindings.push_back(Key(c,Ptr));
}
/* Bind a callback function to a key using the key's string representation. Works for characters
 * 0-9 (eg "6"), a-z(eg "h", "J") and special keys. These special keys include "left", "right", "up",
 * and "down" for the four arrow keys. Similarely, "space", "tab", and "enter" bind to those keys.
 * All uppercase and all lowercase work and are equivelant. 
 * 
 * Returns 1 if the key could be bound and 0 otherwise. Returns 0 if key_str is NULL, is an empty string,
 * or if the provided string does not match an implemented, bindable key
 */
bool Keyboard::bind(const char* key_str, void (*Ptr)()){
   
    // NULL check.
    if(key_str == NULL){
        return 0;
    }

    // Empty string check.
    if(strlen(key_str) == 0){
        return 0;
    }

    // If there's only one character in the string, use the single-char constructor.
    if(strlen(key_str) == 1 ){
        bindings.push_back(Key(key_str[0],Ptr));
        return 1;
    }

    // Check to see if the bound key is the spacebar.
    else if((strcmp(key_str,"SPACE")==0)||(strcmp(key_str,"space")==0)){
        bindings.push_back(Key(GLFW_KEY_SPACE,Ptr));
        return 1;
    }

    // Check to see if the bound key is the enter key.
    else if((strcmp(key_str,"ENTER")==0)||(strcmp(key_str,"enter")==0)){
        bindings.push_back(Key(GLFW_KEY_ENTER,Ptr));
        return 1;
    }

    // Check to see if the bound key is the tab key.
    else if((strcmp(key_str,"TAB")==0)||(strcmp(key_str,"tab")==0)){
        bindings.push_back(Key(GLFW_KEY_TAB,Ptr));
        return 1;
    }
    
    // Check to see if the bound key is the up arrow key.
    else if((strcmp(key_str,"UP")==0)||(strcmp(key_str,"up")==0)){
        bindings.push_back(Key(GLFW_KEY_UP,Ptr));
        return 1;
    }

    // Check to see if the bound key is the down arrow key.
    else if((strcmp(key_str,"DOWN")==0)||(strcmp(key_str,"down")==0)){
        bindings.push_back(Key(GLFW_KEY_DOWN,Ptr));
        return 1;
    }

    // Check to see if the bound key is the left arrow key.
    else if((strcmp(key_str,"LEFT")==0)||(strcmp(key_str,"left")==0)){
        bindings.push_back(Key(GLFW_KEY_LEFT,Ptr));
        return 1;
    }

    // Check to see if the bound key is the right arrow key.
    else if((strcmp(key_str,"RIGHT")==0)||(strcmp(key_str,"right")==0)){
        bindings.push_back(Key(GLFW_KEY_RIGHT,Ptr));
        return 1;
    }
    
    // Return 0 if the string didn't match any valid string key binding.
    else{
        return 0;
    }
}

}



