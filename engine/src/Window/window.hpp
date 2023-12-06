/**
 * @file window.hpp
 * @author Caleb Burke
 * @date Nov 5, 2023
 *
 * Class definitions for creating a basic window for vulkan to integrate with
 *
 */

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
namespace hop {

/**
 * @brief Class for storing a window
 *
 * Class for storing a GLFWwindow that the swapchain can interface with
 *
 */
class Window {
public:
    /**
     * @brief Constructor
     *
     * Initializes a window using the glfw library
     *
     * @param w Width of the window
     * @param h Height of the window
     */
    Window(const char* w_name);
    
    /**
     * @brief Default Deconstructor
     *
     * Destorys the glfw window and instance
     *
     */
    ~Window();

    // Prevents copying of this object
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    /**
     * @brief If window closed
     *
     * Checks if the glfw window is closed
     *
     * @return If window closed
     */
    bool should_close(){ 
        return glfwWindowShouldClose(win); 
    }
    
    /**
     * @brief Dimensions of window
     * @return The dimensions of the window
     */
    VkExtent2D get_extent(){ return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

    /**
     * @brief Creates surface
     *
     * Creates a surface for vulkan that it can use to render onto
     * 
     * @param instance The vulkan instance
     * @param[out] surface The surface for vulkan created from glfw
     * @return void
     */
    void create_surface(VkInstance instance, VkSurfaceKHR* surface);

    /**
     * @brief Checks if window was resized
     * @return If the window was resized
     */
    bool was_window_resized(){ return framebuffer_resized; }
    
    /**
     * @brief sets window resize flag
     *
     * This function is called to set a flag to false, which is used to tell if
     * the screen was resized or not
     *
     * @return void
     */
    void reset_window_resized_flag(){ framebuffer_resized = false; }
    void Initialize(bool fullscreen);
    int get_resolution_width();
    int get_resolution_height();
    void set_window_size(int x, int y);
    GLFWwindow* get_glfw_window();
    bool window_open;

private:
    
    static void framebuffer_resize_callback(GLFWwindow* win, int width, int height);
    void get_screen_resolution();
    bool framebuffer_resized = false;
    int width;
    int height;
    int resolution_width;
    int resolution_height;
    const char* window_name;
    GLFWwindow* win;

};

}
