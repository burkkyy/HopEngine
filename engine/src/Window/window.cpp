#include "window.hpp"

#include "Utilities/status_print.hpp"

namespace hop {

Window::Window(const char* w_name){
    window_name = w_name;
    glfwInit();
    get_screen_resolution();    
}

void Window::Initialize(bool fullscreen){
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    if(fullscreen){
        win = glfwCreateWindow(width, height, window_name, glfwGetPrimaryMonitor(), nullptr);
    }
    else{
        win = glfwCreateWindow(width, height, window_name, nullptr, nullptr);
    }
    glfwSetWindowUserPointer(win, this);
    glfwSetFramebufferSizeCallback(win, framebuffer_resize_callback);
    window_open = true;
}

Window::~Window(){
    glfwDestroyWindow(win);
    glfwTerminate();
}

void Window::create_surface(VkInstance instance, VkSurfaceKHR* surface){
    if(glfwCreateWindowSurface(instance, win, nullptr, surface) != VK_SUCCESS){
        VK_ERROR("failed to create VkSurfaceKHR");
    }
    VK_INFO("created VkSurfaceKHR");
}

void Window::framebuffer_resize_callback(GLFWwindow* window, int width, int height){
    auto _win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    _win->framebuffer_resized = true;
    _win->width = width;
    _win->height = height;
}

void Window::get_screen_resolution(){
    const GLFWvidmode* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    this->resolution_width = video_mode->width;
    this->resolution_height = video_mode->height;

}

int Window::get_resolution_width(){
    return this->resolution_width;
    }
int Window::get_resolution_height(){return this->resolution_height;}
void Window::set_window_size(int w, int h){
    width = w;
    height = h;
}    
GLFWwindow* Window::get_glfw_window(){
    return win;
}

}

