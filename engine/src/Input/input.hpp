#pragma once
#include "GLFW/glfw3.h"
#include <vector>

namespace hop{

class Keyboard{

    private:
    GLFWwindow* window;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    struct Key{
        public:
        int code;
        void (*function)(); 
        Key(char c, void (*Ptr)());
        Key(int code, void (*Ptr)());
    };
    static std::vector<Key> bindings;

    public:
    Keyboard(GLFWwindow* window);
    void bind(int code, void (*Ptr)());
    void bind(char c, void (*Ptr)());
    bool bind(const char* key_str, void (*Ptr)());
};

}