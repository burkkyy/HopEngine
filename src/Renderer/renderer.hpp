#pragma once

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Swapchain/swapchain.hpp"

#include <vulkan/vulkan.h>

#include <cassert>
#include <memory>
#include <vector>

namespace hop {

class Renderer {
public:
    Renderer(Window& window, Device& device);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    VkRenderPass get_swapchain_render_pass() const { return swapchain->get_render_pass(); }
    
    float get_aspect_ratio() const { return swapchain->extent_aspect_ratio(); }
    
    bool is_frame_in_progress() const { return is_frame_started; }
    
    VkCommandBuffer get_current_command_buffer() const {
        assert(is_frame_started);
        return command_buffers[current_frame_index];
    }

    int get_frame_index() const {
        assert(is_frame_started);
        return current_frame_index;
    }
    
    VkCommandBuffer begin_frame();
    void end_frame();
    void begin_swapchain_render_pass(VkCommandBuffer command_buffer);
    void end_swapchain_render_pass(VkCommandBuffer command_buffer);

private:
    void create_command_buffers();
    void free_command_buffers();
    void recreate_swapchain();

    Window& window;
    Device& device;
    std::unique_ptr<SwapChain> swapchain;
    std::vector<VkCommandBuffer> command_buffers;

    uint32_t current_image_index;
    int current_frame_index = 0;
    bool is_frame_started = false;
};

}
