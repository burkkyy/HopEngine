/**
 * @file renderer.hpp
 * @author Caleb Burke
 * @date Nov 7, 2023
 *
 * Classes for handling bare bones rendering
 *
 */

#pragma once

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Swapchain/swapchain.hpp"

#include <vulkan/vulkan.h>

#include <cassert>
#include <memory>
#include <vector>

namespace hop {

/**
 * @brief Class for renderering
 *
 * This class is essentially an abstraction from the swapchain
 *
 * NOTE: This class creates the swapchain
 * NOTE: This class depends on a window and device to be created
*/
class Renderer {
public:

    /**
     * @brief Constructor
     *
     * Initilaes the renderer by creating the swapchain. This also creates
     * command buffers that are stored in the command pool in the device.
     *
     */
    Renderer(Window& window, Device& device);
    
    /**
     * @brief Default Deconstructor
     *
     * Releases the memory from the command buffers
     *
     */
    ~Renderer();

    // Prevents copying of this object
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    /**
     * @brief Gets the current swapchain renderpass
     *
     * This function returns the current swapchain renderpass in use. The
     * renderpass is a vulkan object that specifies a sequence of renderering
     * operations. The renderpass defines how images are used during renderering
     * operations.
     *
     * See for more info:
     *      https://vkguide.dev/docs/chapter-1/vulkan_renderpass/
     *
     * @return The render pass
     */
    VkRenderPass get_swapchain_render_pass() const { return swapchain->get_render_pass(); }    
    
    /**
     * @brief Safe getter function for getting command buffer
     *
     * This function gets the currnet command buffer to be executed. It's "safe"
     * because we make sure there is no frame in progress before we return the 
     * current command buffer we can prevent undefined behaviour. In other words
     * this function should NOT be called if a frame is currently rendering.
     *
     * @return the current command buffer
     */
    VkCommandBuffer get_current_command_buffer() const {
        assert(is_frame_started);
        return command_buffers[current_frame_index];
    }
    
    /**
     * @brief Begins a new frame for rendering
     *
     * This function starts a new frame that we can render onto. This is done
     * by first checking if the current swapchain is valid. Then we can begin
     * recording commands onto a command buffer
     * 
     * NOTE: Ensure previous frame has completed rendering
     * NOTE: Once this function is called is_frame_started is set to true
     *
     * @return A command buffer in recording state
     */
    VkCommandBuffer begin_frame();
    
    /**
     * @brief Ends the rendering of a new frame
     *
     * This function is called once all the commands were recorded onto the 
     * command buffer. Then the command buffer is sent to the swapchain for
     * presentation.
     *
     * NOTE: Ensure a frame has been started and the render pass was already ended
     * NOTE: This function sets is_frame_started to false
     *
     * @return void
     */
    void end_frame();
    
    /**
     * @brief Starts the render pass
     *
     * This function starts the render pass within the command buffer. The render
     * pass is essential as it is used by the vulkan driver to know more about
     * the state of the images you want to render
     *
     * See for more info:
     *      https://developer.samsung.com/galaxy-gamedev/resources/articles/renderpasses.html
     *
     * NOTE: Ensure begin_frame() was called
     * 
     * @param command_buffer The command buffer returned from begin_frame()
     * @return void
     */
    void begin_swapchain_render_pass(VkCommandBuffer command_buffer);

    /**
     * @brief Ends the render pass
     *
     * Simply ends the render pass. This should be called once all commands
     * are finished recording.
     *
     * NOTE: Ensure a frame and the render pass has started
     * 
     * @param command_buffer The command buffer returned from begin_frame()
     * @return void
     */
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
