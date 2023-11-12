#include "renderer.hpp"

#include "Utilities/status_print.hpp"

namespace hop {

Renderer::Renderer(Window& window, Device& device) : window{window}, device{device}{
    recreate_swapchain();
    create_command_buffers();
}

Renderer::~Renderer(){
    free_command_buffers();
}

VkCommandBuffer Renderer::begin_frame(){
    assert(!is_frame_started);

    auto result = swapchain->acquire_next_image(&current_image_index);

    if(result == VK_ERROR_OUT_OF_DATE_KHR){
        recreate_swapchain();
        return nullptr;
    }

    if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
        VK_ERROR("failed to acquire swap chain image");
    }

    is_frame_started = true;

    auto command_buffer = get_current_command_buffer();
    VkCommandBufferBeginInfo begin_info{};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if(vkBeginCommandBuffer(command_buffer, &begin_info) != VK_SUCCESS){
        VK_ERROR("failed to begin to recording command buffer");
    }
    return command_buffer;
}

void Renderer::end_frame(){
    assert(is_frame_started);

    auto command_buffer = get_current_command_buffer();
    if(vkEndCommandBuffer(command_buffer) != VK_SUCCESS){
        VK_ERROR("failed to record command buffer");
    }

    auto result = swapchain->submit_command_buffers(&command_buffer, &current_image_index);
    if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window.was_window_resized()){
        window.reset_window_resized_flag();
        recreate_swapchain();
    } else if(result != VK_SUCCESS){
        VK_ERROR("failed to present swap chain image");
    }

    is_frame_started = false;
    current_frame_index = (current_frame_index + 1) % SwapChain::MAX_FRAMES_IN_FLIGHT;
}

void Renderer::begin_swapchain_render_pass(VkCommandBuffer command_buffer){
    assert(is_frame_started);
    assert(command_buffer == get_current_command_buffer());

    VkRenderPassBeginInfo render_pass_info{};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = swapchain->get_render_pass();
    render_pass_info.framebuffer = swapchain->get_frame_buffer(current_image_index);

    render_pass_info.renderArea.offset = {0, 0};
    render_pass_info.renderArea.extent = swapchain->get_swapchain_extent();

    std::array<VkClearValue, 2> clear_values{};
    clear_values[0].color = {0.01f, 0.01f, 0.01f, 0.1f};
    clear_values[1].depthStencil = {1.0f, 0};

    render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
    render_pass_info.pClearValues = clear_values.data();

    vkCmdBeginRenderPass(command_buffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain->get_swapchain_extent().width);
    viewport.height = static_cast<float>(swapchain->get_swapchain_extent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, swapchain->get_swapchain_extent()};
    vkCmdSetViewport(command_buffer, 0, 1, &viewport);
    vkCmdSetScissor(command_buffer, 0, 1, &scissor);
}

void Renderer::end_swapchain_render_pass(VkCommandBuffer command_buffer){
    assert(is_frame_started);
    assert(command_buffer == get_current_command_buffer());
    vkCmdEndRenderPass(command_buffer);
}

void Renderer::create_command_buffers(){
    command_buffers.resize(SwapChain::MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocation_info{};
    allocation_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocation_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocation_info.commandPool = device.get_command_pool();
    allocation_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());

    if(vkAllocateCommandBuffers(device.get_device(), &allocation_info, command_buffers.data()) != VK_SUCCESS){
        VK_ERROR("failed to allocate command buffers");
    }
}

void Renderer::free_command_buffers(){
    vkFreeCommandBuffers(device.get_device(), device.get_command_pool(), static_cast<uint32_t>(command_buffers.size()), command_buffers.data());
    command_buffers.clear();
}

void Renderer::recreate_swapchain(){
    auto extent = window.get_extent();

    while(extent.width == 0 || extent.height == 0){
        extent = window.get_extent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(device.get_device());

    if(swapchain == nullptr){
        swapchain = std::make_unique<SwapChain>(device, extent);
    } else {
        std::shared_ptr<SwapChain> old_swapchain = std::move(swapchain);
        swapchain = std::make_unique<SwapChain>(device, extent, old_swapchain);

        if(!old_swapchain->compare_swap_formats(*swapchain.get())){
            VK_ERROR("Swap chain image(or depth) format has changed!");
        } 
    }
}

}
