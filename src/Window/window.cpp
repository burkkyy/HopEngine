#include "window.hpp"

#include "Utilities/status_print.hpp"

namespace hop {

Window::Window(int w, int h) : width{w}, height{h} {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    win = glfwCreateWindow(width, height, window_name, nullptr, nullptr);
    glfwSetWindowUserPointer(win, this);
    glfwSetFramebufferSizeCallback(win, framebuffer_resize_callback);
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

}
