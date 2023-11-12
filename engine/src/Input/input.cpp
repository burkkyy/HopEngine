#include "input.hpp"
#include <iostream>
#include <string.h>
#include <ctype.h>

namespace hop{

std::vector<Keyboard::Key> Keyboard::bindings;

Keyboard::Keyboard(GLFWwindow* window){
    this->window = window;
    glfwSetKeyCallback(window, this->key_callback);
}
 
void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    window = window;
    (void)scancode;
    (void)mods;
    
    for(Key k: bindings){
        if((k.code == key)&&((action==GLFW_PRESS)||(action==GLFW_REPEAT))){
            k.function();
        }
    }
}

Keyboard::Key::Key(char c, void (*Ptr)()){
    if(((c - '0')>-1)&&((c - '0'<10))){
        bindings.push_back(Key((c - '0' + 48),Ptr));
    }
    else{
        c = toupper(c);
        this->code = (int)c;
        this-> function = Ptr;
    }
}

Keyboard::Key::Key(int code, void (*Ptr)()){
    this->code = code;
    this-> function = Ptr;
}

void Keyboard::bind(int code, void (*Ptr)()){
    bindings.push_back(Key(code,Ptr));
}

void Keyboard::bind(char c, void (*Ptr)()){
    bindings.push_back(Key(c,Ptr));
}
bool Keyboard::bind(const char* key_str, void (*Ptr)()){
   
    if(key_str == NULL){
        return 0;
    }

    if(strlen(key_str) == 0){
        return 0;
    }

    if(strlen(key_str) == 1 ){
        bindings.push_back(Key(key_str[0],Ptr));
        return 1;
    }

    else if((strcmp(key_str,"SPACE")==0)||(strcmp(key_str,"space")==0)){
        bindings.push_back(Key(GLFW_KEY_SPACE,Ptr));
        return 1;
    }

    else if((strcmp(key_str,"ENTER")==0)||(strcmp(key_str,"enter")==0)){
        bindings.push_back(Key(GLFW_KEY_ENTER,Ptr));
        return 1;
    }

    else if((strcmp(key_str,"TAB")==0)||(strcmp(key_str,"tab")==0)){
        bindings.push_back(Key(GLFW_KEY_TAB,Ptr));
        return 1;
    }

    else if((strcmp(key_str,"UP")==0)||(strcmp(key_str,"up")==0)){
        bindings.push_back(Key(GLFW_KEY_UP,Ptr));
        return 1;
    }

    else if((strcmp(key_str,"DOWN")==0)||(strcmp(key_str,"down")==0)){
        bindings.push_back(Key(GLFW_KEY_DOWN,Ptr));
        return 1;
    }

    else if((strcmp(key_str,"LEFT")==0)||(strcmp(key_str,"left")==0)){
        bindings.push_back(Key(GLFW_KEY_LEFT,Ptr));
        return 1;
    }

    else if((strcmp(key_str,"RIGHT")==0)||(strcmp(key_str,"right")==0)){
        bindings.push_back(Key(GLFW_KEY_RIGHT,Ptr));
        return 1;
    }
    
    else{
        return 0;
    }
}

}



