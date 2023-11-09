#pragma once

#include "Window/window.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <optional>

namespace hop {

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

struct QueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool operator~(){
        return graphics_family.has_value() && present_family.has_value();
    }
};

class Device {
public:
#ifdef NDEBUG
    const bool enable_validation_layers = false;
#else
    const bool enable_validation_layers = true;
#endif    

    Device(Window&);
    ~Device();

    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;
    Device(Device&&) = delete;
    Device& operator=(Device&&) = delete;

    VkDevice get_device(){ return device; }
    VkSurfaceKHR get_surface(){ return surface; }
    VkQueue get_graphics_que(){ return gfx_queue; }
    VkQueue get_present_que(){ return present_queue; }
    VkCommandPool get_command_pool(){ return command_pool; }

    SwapChainSupportDetails get_swapchain_support(){ return query_swapchain_support(physical_device); }
    uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties);
    QueFamilyIndices find_physical_que_families(){ return find_que_families(physical_device); }
    VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory);
    
    VkCommandBuffer begin_single_time_commands();
    void end_single_time_commands(VkCommandBuffer command_buffer);
    
    void copy_buffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);
    void copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layer_count);

    void create_image_with_info(const VkImageCreateInfo& image_info, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& image_memory);
    
    VkPhysicalDeviceProperties properties;

private:
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;
    VkSurfaceKHR surface;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    Window& window;
    VkDevice device;
    VkQueue gfx_queue;
    VkQueue present_queue;
    VkCommandPool command_pool;

    const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};
    const std::vector<const char*> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    /* Functions for the vulkan debugger */
    void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT&);
    VkResult create_debug_utils_messenger_EXT(VkInstance, const VkDebugUtilsMessengerCreateInfoEXT*, const VkAllocationCallbacks*, VkDebugUtilsMessengerEXT*);
    void setup_debug_messenger();
    void destroy_debug_utils_messenger_EXT(VkInstance, VkDebugUtilsMessengerEXT, const VkAllocationCallbacks*);

    /* Functions for creating instance */
    void create_instance();
    bool check_validation_layer_support();
    std::vector<const char*> get_required_extensions();

    /* Functions for picking and setting up physical device */
    void pick();
    bool is_device_suitable(VkPhysicalDevice);
    bool check_device_extension_support(VkPhysicalDevice);
    QueFamilyIndices find_que_families(VkPhysicalDevice);

    /* Functions for creating and setting up logical device*/
    void create_logical_device();

    /* Functions for checking swapchain support in device*/
    SwapChainSupportDetails query_swapchain_support(VkPhysicalDevice);

    /* Functions for command pool */
    void create_command_pool();
};

}