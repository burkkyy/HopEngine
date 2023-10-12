#include "window.hpp"

#include "Utilities/status_print.hpp"

namespace hop {

Window::Window(int w, int h) : width{w}, height{h} {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    win = glfwCreateWindow(width, height, NAME, nullptr, nullptr);

    while(!should_close()){
        glfwPollEvents();
    }
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

}
