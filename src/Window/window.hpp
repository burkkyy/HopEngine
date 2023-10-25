#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace hop {

class Window {
public:
    Window(int w, int h);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool should_close(){ return glfwWindowShouldClose(win); }
    VkExtent2D get_extent(){ return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
    void create_surface(VkInstance instance, VkSurfaceKHR* surface);

    bool was_window_resized(){ return framebuffer_resized; }
    void reset_window_resized_flag(){ framebuffer_resized = false; }

private:
    static void framebuffer_resize_callback(GLFWwindow* win, int width, int height);
    bool framebuffer_resized = false;
    int width;
    int height;
    const char* window_name = "bunny sim";
    GLFWwindow* win;
};

}
