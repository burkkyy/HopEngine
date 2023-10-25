#pragma once

#include "Device/device.hpp"

#include <vulkan/vulkan.h>

#include <memory>
#include <vector>

namespace hop {

class SwapChain {
public:
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    SwapChain(Device& d, VkExtent2D e);
    SwapChain(Device& d, VkExtent2D e, std::shared_ptr<SwapChain> prev);
    ~SwapChain();

    SwapChain(const SwapChain&) = delete;
    SwapChain& operator=(const SwapChain&) = delete;

    VkFramebuffer get_frame_buffer(int index) { return swapchain_framebuffers[index]; }
    VkRenderPass get_render_pass() { return render_pass; }
    VkImageView get_image_view(int index) { return swapchain_image_views[index]; }
    VkFormat get_swapchain_image_format() { return swapchain_image_format; }
    VkExtent2D get_swapchain_extent() { return swapchain_extent; }

    size_t image_count() { return swapchain_images.size(); }
    uint32_t height(){ return swapchain_extent.height; };
    uint32_t width(){ return swapchain_extent.width; };

    float extent_aspect_ratio() {
        return static_cast<float>(swapchain_extent.width) / static_cast<float>(swapchain_extent.height);
    }

    VkFormat find_depth_format();

    VkResult acquire_next_image(uint32_t* image_index);
    VkResult submit_command_buffers(const VkCommandBuffer* buffers, uint32_t* image_index);

    bool compare_swap_formats(const SwapChain& swapchain) const {
        return swapchain.swapchain_depth_format == swapchain_depth_format && swapchain.swapchain_image_format == swapchain_image_format;
    }

private:
    Device& device;
    VkExtent2D window_extent;

    VkSwapchainKHR swapchain;
    std::shared_ptr<SwapChain> old_swapchain;

    std::vector<VkImage> depth_images;
    std::vector<VkDeviceMemory> depth_image_memorys;
    std::vector<VkImageView> depth_image_views;
    std::vector<VkImage> swapchain_images;
    std::vector<VkImageView> swapchain_image_views;
    VkFormat swapchain_image_format;
    VkFormat swapchain_depth_format;
    VkExtent2D swapchain_extent;

    std::vector<VkFramebuffer> swapchain_framebuffers;
    VkRenderPass render_pass;

    std::vector<VkSemaphore> image_available_semaphores;
    std::vector<VkSemaphore> render_finished_semaphores;
    std::vector<VkFence> in_flight_fences;
    std::vector<VkFence> images_in_flight;
    size_t current_frame = 0;

    /* Functions for creating swapchain */
    VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>&);
    VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>&);
    VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR&);

    void init();
    void create_swap_chain();
    void create_image_views();
    void create_render_pass();
    void create_depth_resources();
    void create_framebuffers();
    void create_sync_objects();
};

}