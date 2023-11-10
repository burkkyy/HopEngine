/**
 * @file swapchain.hpp
 * @author Caleb Burke
 * @date Nov 5, 2023
 *
 * Classes here are critical for creating frames, drawing frames, 
 * presenting frames and destroying frames.
 *
 */

#pragma once

#include "Device/device.hpp"

#include <vulkan/vulkan.h>

#include <memory>
#include <vector>

namespace hop {

/**
 * @brief Swapchain for game engine
 *
 * This class is the swapchain for the game engine. This means that this class
 * keeps track of what image is being presented and which can be rendered to.
 *
 * NOTE: Depends on a device to be created
 */
class SwapChain {
public:
    static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

    /**
     * @brief Constructor
     *
     * A
     *
     * @param device
     * @param extent
     */
    SwapChain(Device& d, VkExtent2D e);
    
    /**
     * @brief Constructor
     *
     * A
     *
     * @param device
     * @param extent
     * @param prev
     */
    SwapChain(Device& d, VkExtent2D e, std::shared_ptr<SwapChain> prev);
    
    /**
     * @brief Default Deconstructor
     *
     * A
     *
     */
    ~SwapChain();

    // Prevents copying of this object
    SwapChain(const SwapChain&) = delete;
    SwapChain& operator=(const SwapChain&) = delete;

    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkFramebuffer get_frame_buffer(int index) { return swapchain_framebuffers[index]; }
    
    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkRenderPass get_render_pass() { return render_pass; }
    
    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkImageView get_image_view(int index) { return swapchain_image_views[index]; }
    
    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkFormat get_swapchain_image_format() { return swapchain_image_format; }
    
    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkExtent2D get_swapchain_extent() { return swapchain_extent; }

    /**
     * @brief
     *
     * A
     *
     * @return
     */
    size_t image_count() { return swapchain_images.size(); }
    
    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkFormat find_depth_format();

    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkResult acquire_next_image(uint32_t* image_index);
    
    /**
     * @brief
     *
     * A
     *
     * @return
     */
    VkResult submit_command_buffers(const VkCommandBuffer* buffers, uint32_t* image_index);

    /**
     * @brief
     *
     * A
     *
     * @return
     */
    bool compare_swap_formats(const SwapChain& swapchain) const {
        return swapchain.swapchain_depth_format == swapchain_depth_format && swapchain.swapchain_image_format == swapchain_image_format;
    }

private:
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
};

}