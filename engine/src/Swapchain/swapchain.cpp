#include "swapchain.hpp"

#include "Utilities/status_print.hpp"

#include <limits>

namespace hop {

SwapChain::SwapChain(Device& d, VkExtent2D e) : device{d}, window_extent{e} {
    init();
}

SwapChain::SwapChain(Device& d, VkExtent2D e, std::shared_ptr<SwapChain> prev) : device{d}, window_extent{e}, old_swapchain{prev} { 
    init();
    old_swapchain = nullptr;
}

SwapChain::~SwapChain(){
    for(auto i : swapchain_image_views){
        vkDestroyImageView(device.get_device(), i, nullptr);
    }
    swapchain_image_views.clear();

    if(swapchain != nullptr){
        vkDestroySwapchainKHR(device.get_device(), swapchain, nullptr);
        swapchain = nullptr;
        VK_INFO("destroyed swapchain");
    }

    for (int i = 0; i < depth_images.size(); i++) {
        vkDestroyImageView(device.get_device(), depth_image_views[i], nullptr);
        vkDestroyImage(device.get_device(), depth_images[i], nullptr);
        vkFreeMemory(device.get_device(), depth_image_memorys[i], nullptr);
    }

    for (auto framebuffer : swapchain_framebuffers) {
        vkDestroyFramebuffer(device.get_device(), framebuffer, nullptr);
    }
    VK_INFO("destroyed swapchain framebuffers");

    vkDestroyRenderPass(device.get_device(), render_pass, nullptr);
    VK_INFO("destroyed render pass");

    // cleanup synchronization objects (semaphores)
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device.get_device(), render_finished_semaphores[i], nullptr);
        vkDestroySemaphore(device.get_device(), image_available_semaphores[i], nullptr);
        vkDestroyFence(device.get_device(), in_flight_fences[i], nullptr);
    }
    VK_INFO("destroyed synchronization objects");
}

void SwapChain::init(){
    create_swap_chain();
    create_image_views();
    create_render_pass();
    create_depth_resources();
    create_framebuffers();
    create_sync_objects();
}

VkFormat SwapChain::find_depth_format(){
  return device.find_supported_format(
      {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
      VK_IMAGE_TILING_OPTIMAL,
      VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

VkResult SwapChain::acquire_next_image(uint32_t* image_index){
    vkWaitForFences(device.get_device(), 1, &in_flight_fences[current_frame], VK_TRUE, std::numeric_limits<uint64_t>::max());
    VkResult result = vkAcquireNextImageKHR(device.get_device(), swapchain, std::numeric_limits<uint64_t>::max(), image_available_semaphores[current_frame], VK_NULL_HANDLE,image_index);
    return result;
}

VkResult SwapChain::submit_command_buffers(const VkCommandBuffer* buffers, uint32_t* image_index){
    if (images_in_flight[*image_index] != VK_NULL_HANDLE) {
        vkWaitForFences(device.get_device(), 1, &images_in_flight[*image_index], VK_TRUE, UINT64_MAX);
    }
    images_in_flight[*image_index] = in_flight_fences[current_frame];

    VkSubmitInfo submit_info = {};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore wait_semaphores[] = { image_available_semaphores[current_frame] };
    VkPipelineStageFlags wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores = wait_semaphores;
    submit_info.pWaitDstStageMask = wait_stages;

    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = buffers;

    VkSemaphore signal_semaphores[] = { render_finished_semaphores[current_frame] };
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = signal_semaphores;

    vkResetFences(device.get_device(), 1, &in_flight_fences[current_frame]);
    if (vkQueueSubmit(device.get_graphics_que(), 1, &submit_info, in_flight_fences[current_frame]) != VK_SUCCESS){
        VK_ERROR("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR present_info = {};
    present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    present_info.waitSemaphoreCount = 1;
    present_info.pWaitSemaphores = signal_semaphores;

    VkSwapchainKHR swapchains[] = { swapchain };
    present_info.swapchainCount = 1;
    present_info.pSwapchains = swapchains;

    present_info.pImageIndices = image_index;

    auto result = vkQueuePresentKHR(device.get_present_que(), &present_info);

    current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;

    return result;
}

VkSurfaceFormatKHR SwapChain::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& formats){
    /* We want to return the format with the 'best' color space */
    for(const auto& f : formats){
        if(f.format == VK_FORMAT_B8G8R8A8_SRGB && f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
            return f;
        }
    }
    VK_WARNING("choosing poor swapchain surface format");
    return formats[0];
}

VkPresentModeKHR SwapChain::choose_swap_present_mode(const std::vector<VkPresentModeKHR>& modes){
    /* 
    The presentation mode is most important setting for the swapchain.
    
    Possible presentation modes:
        VK_PRESENT_MODE_IMMEDIATE_KHR: 
            Images submitted by your application are transferred to 
            the screen right away, which may result in tearing.
        VK_PRESENT_MODE_FIFO_KHR: 
            The swap chain is a queue where the 
            display takes an image from the front of the queue when the 
            display is refreshed and the program inserts rendered images 
            at the back of the queue. If the queue is full then the program 
            has to wait. This is most similar to vertical sync as found 
            in modern games. The moment that the display is refreshed is 
            known as "vertical blank".
        VK_PRESENT_MODE_FIFO_RELAXED_KHR:
            This mode only differs from the 
            previous one if the application is late and the queue was empty at 
            the last vertical blank. Instead of waiting for the next vertical 
            blank, the image is transferred right away when it finally arrives. 
            This may result in visible tearing.
        VK_PRESENT_MODE_MAILBOX_KHR: 
            This is another variation of the second mode. 
            Instead of blocking the application when the 
            queue is full, the images that are already queued are simply 
            replaced with the newer ones. This mode can be used to render 
            frames as fast as possible while still avoiding tearing, 
            resulting in fewer latency issues than standard vertical sync. 
            This is commonly known as "triple buffering", although the 
            existence of three buffers alone does not necessarily mean 
            that the framerate is unlocked.
    */

    /*
    for(const auto& m : modes){
        if(m == VK_PRESENT_MODE_IMMEDIATE_KHR){
            VK_INFO("present mode: immediate");
            return m;
        }
    }
    */

    for(const auto& m : modes){
        if(m == VK_PRESENT_MODE_MAILBOX_KHR){
            VK_INFO("present mode: mailbox");
            return m;
        }
    }

    /* FIFO_KHR is guaranteed to be avalible */
    VK_INFO("present mode: V-Sync");
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChain::choose_swap_extent(const VkSurfaceCapabilitiesKHR& capa){
    if(capa.currentExtent.width != 0xFFFFFFFF){
        return capa.currentExtent;
    } else {
        VkExtent2D extent = window_extent;
        extent.width = std::max(capa.minImageExtent.width, std::min(capa.maxImageExtent.width, extent.width));
        extent.height = std::max(capa.minImageExtent.height, std::min(capa.maxImageExtent.height, extent.height));
        return extent;
    }
}

void SwapChain::create_swap_chain(){
    SwapChainSupportDetails ss = device.get_swapchain_support();

    VkSurfaceFormatKHR surface_format = choose_swap_surface_format(ss.formats);
    VkPresentModeKHR present_mode = choose_swap_present_mode(ss.present_modes);
    VkExtent2D extent = choose_swap_extent(ss.capabilities);

    uint32_t image_count = ss.capabilities.minImageCount + 1;
    if(ss.capabilities.maxImageCount > 0 && image_count > ss.capabilities.maxImageCount){
        image_count = ss.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = device.get_surface();
    create_info.minImageCount = image_count;
    create_info.imageFormat = surface_format.format;
    create_info.imageColorSpace = surface_format.colorSpace;
    create_info.imageExtent = extent;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueFamilyIndices indices = device.find_physical_que_families();
    uint32_t qfi[] = {indices.graphics_family.value(), indices.present_family.value()};
    if(indices.graphics_family != indices.present_family){
        create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount = 2;
        create_info.pQueueFamilyIndices = qfi;
    } else {
        create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        create_info.queueFamilyIndexCount = 0;
        create_info.pQueueFamilyIndices = nullptr;
    }

    create_info.preTransform = ss.capabilities.currentTransform;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = present_mode;
    create_info.clipped = VK_TRUE;
    // create_info.oldSwapchain = nullptr;
    create_info.oldSwapchain = old_swapchain == nullptr ? VK_NULL_HANDLE : old_swapchain->swapchain;

    if(vkCreateSwapchainKHR(device.get_device(), &create_info, nullptr, &swapchain) != VK_SUCCESS){
        VK_ERROR("failed to create swapchain");
    }
    VK_INFO("created swapchain");

    vkGetSwapchainImagesKHR(device.get_device(), swapchain, &image_count, nullptr);
    swapchain_images.resize(image_count);
    vkGetSwapchainImagesKHR(device.get_device(), swapchain, &image_count, swapchain_images.data());

    swapchain_image_format = surface_format.format;
    swapchain_extent = extent;
}

void SwapChain::create_image_views(){
    swapchain_image_views.resize(swapchain_images.size());

    for(size_t i = 0; i < swapchain_images.size(); i++){
        VkImageViewCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        create_info.image = swapchain_images[i];
        create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        create_info.format = swapchain_image_format;
        create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        create_info.subresourceRange.baseMipLevel = 0;
        create_info.subresourceRange.levelCount = 1;
        create_info.subresourceRange.baseArrayLayer = 0;
        create_info.subresourceRange.layerCount = 1;

        if(vkCreateImageView(device.get_device(), &create_info, nullptr, &swapchain_image_views[i]) != VK_SUCCESS){
            VK_ERROR("failed to create image views");
        }
        VK_INFO("Created image views");
    }
}

void SwapChain::create_render_pass(){
    VkAttachmentDescription depth_attachment = {};
    depth_attachment.format = find_depth_format();
    depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    depth_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depth_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depth_attachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depth_attachment_ref = {};
    depth_attachment_ref.attachment = 1;
    depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentDescription color_attachment = {};
    color_attachment.format = get_swapchain_image_format();
    color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference color_attachment_ref = {};
    color_attachment_ref.attachment = 0;
    color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment_ref;
    subpass.pDepthStencilAttachment = &depth_attachment_ref;

    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.srcAccessMask = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstSubpass = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    std::array<VkAttachmentDescription, 2> attachments = {color_attachment, depth_attachment};
    VkRenderPassCreateInfo render_pass_info = {};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_info.attachmentCount = static_cast<uint32_t>(attachments.size());
    render_pass_info.pAttachments = attachments.data();
    render_pass_info.subpassCount = 1;
    render_pass_info.pSubpasses = &subpass;
    render_pass_info.dependencyCount = 1;
    render_pass_info.pDependencies = &dependency;

    if(vkCreateRenderPass(device.get_device(), &render_pass_info, nullptr, &render_pass) != VK_SUCCESS){
        VK_ERROR("failed to create render pass!");
    }
    VK_INFO("Created render pass!");
}

void SwapChain::create_depth_resources(){
    VkFormat depth_format = find_depth_format();
    swapchain_depth_format = depth_format;
    VkExtent2D swapchain_extent = get_swapchain_extent();

    depth_images.resize(image_count());
    depth_image_memorys.resize(image_count());
    depth_image_views.resize(image_count());

    for (int i = 0; i < depth_images.size(); i++) {
        VkImageCreateInfo image_info = {};
        image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        image_info.imageType = VK_IMAGE_TYPE_2D;
        image_info.extent.width = swapchain_extent.width;
        image_info.extent.height = swapchain_extent.height;
        image_info.extent.depth = 1;
        image_info.mipLevels = 1;
        image_info.arrayLayers = 1;
        image_info.format = depth_format;
        image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
        image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        image_info.samples = VK_SAMPLE_COUNT_1_BIT;
        image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        image_info.flags = 0;

        device.create_image_with_info(image_info, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depth_images[i], depth_image_memorys[i]);

        VkImageViewCreateInfo view_info = {};
        view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        view_info.image = depth_images[i];
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.format = depth_format;
        view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        view_info.subresourceRange.baseMipLevel = 0;
        view_info.subresourceRange.levelCount = 1;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device.get_device(), &view_info, nullptr, &depth_image_views[i]) != VK_SUCCESS) {
            VK_ERROR("failed to create texture image view");
        }
        VK_INFO("Created texture image view");
    }
}

void SwapChain::create_framebuffers(){
    swapchain_framebuffers.resize(image_count());

    for(size_t i = 0; i < image_count(); i++){
        std::array<VkImageView, 2> attachments = {swapchain_image_views[i], depth_image_views[i]};

        VkExtent2D swapChainExtent = get_swapchain_extent();
        VkFramebufferCreateInfo framebuffer_info = {};
        framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebuffer_info.renderPass = render_pass;
        framebuffer_info.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebuffer_info.pAttachments = attachments.data();
        framebuffer_info.width = swapchain_extent.width;
        framebuffer_info.height = swapchain_extent.height;
        framebuffer_info.layers = 1;

        if (vkCreateFramebuffer(device.get_device(), &framebuffer_info, nullptr, &swapchain_framebuffers[i]) != VK_SUCCESS){
            VK_ERROR("failed to create framebuffers");
        }
    }
    VK_INFO("created frambuffers");
}

void SwapChain::create_sync_objects(){
    image_available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
    in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);
    images_in_flight.resize(image_count(), VK_NULL_HANDLE);

    VkSemaphoreCreateInfo semaphore_info = {};
    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fence_info = {};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if(vkCreateSemaphore(device.get_device(), &semaphore_info, nullptr, &image_available_semaphores[i]) != VK_SUCCESS){
            VK_ERROR("failed to create a synchronization object for images");
        }
        VK_INFO("Created a synchronization object for images");

        if(vkCreateSemaphore(device.get_device(), &semaphore_info, nullptr, &render_finished_semaphores[i]) != VK_SUCCESS){
            VK_ERROR("failed to create a synchronization object for rendering");
        }
        VK_INFO("Created a synchronization object for rendering");

        if(vkCreateFence(device.get_device(), &fence_info, nullptr, &in_flight_fences[i]) != VK_SUCCESS){
            VK_ERROR("failed to create a fence synchronization object");
        }
        VK_INFO("Created a fence synchronization object");
    }
}

}
