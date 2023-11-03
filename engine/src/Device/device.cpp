#include "device.hpp"

#include "Utilities/status_print.hpp"

#include <set>
#include <cstring>

namespace hop {

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT m_severity,
    VkDebugUtilsMessageTypeFlagsEXT m_type,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallback_data,
    void* pUser_data){
        if(m_severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
            ERROR("VALIDATION LAYER", pCallback_data->pMessage);
        } else if(m_severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT){
            WARNING("VALIDATION LAYER", pCallback_data->pMessage);
        } else {
            INFO("VALIDATION LAYER", pCallback_data->pMessage);
        }
        return VK_FALSE;
}

Device::Device(Window& win) : window{win} {
    create_instance();
    setup_debug_messenger();
    window.create_surface(instance, &surface);
    pick();
    create_logical_device();
    create_command_pool();
}

Device::~Device(){
    if(enable_validation_layers){
        destroy_debug_utils_messenger_EXT(instance, debug_messenger, nullptr);
    }

    vkDestroyCommandPool(device, command_pool, nullptr);
    VK_INFO("destroyed command pool");

    vkDestroyDevice(device, nullptr);
    VK_INFO("destroyed logical device");

    vkDestroySurfaceKHR(instance, surface, nullptr);
    VK_INFO("destroyed VkSurfaceKHR");

    /* Note that all other vulkan resources should be destroyed before VkInstance */
    vkDestroyInstance(instance, nullptr);
    VK_INFO("destroyed VkInstance");
}

void Device::populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& create_info){
    create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    create_info.pfnUserCallback = debug_callback;
}

void Device::setup_debug_messenger(){
    if(!enable_validation_layers){ return; }

    VkDebugUtilsMessengerCreateInfoEXT create_info;
    populate_debug_messenger_create_info(create_info);

    if(create_debug_utils_messenger_EXT(instance, &create_info, nullptr, &debug_messenger) != VK_SUCCESS){
        VK_ERROR("failed to set up debug messenger");
    }
    VK_INFO("set up debug messenger");
}

VkResult Device::create_debug_utils_messenger_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger){
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void Device::destroy_debug_utils_messenger_EXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator){
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if(func != nullptr){ func(instance, debugMessenger, pAllocator); }
}

void Device::create_instance(){
    if(enable_validation_layers && !check_validation_layer_support()){ VK_ERROR("validation layers requested but not available"); }
    if(enable_validation_layers){ VK_INFO("validation layers were requested successfully"); }
    
    /*
    VkApplicationInfo

    Infomation struct about our application. This is used
    by the driver to optimize our application (optional)
    */
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "Hop";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "No Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    /*
    VkInstanceCreateInfo

    This struct tells the vulkan driver which extensions
    and validation layers we want to use. These extensions
    are global meaning they apply to the entire program
    */
    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    /*
    Extensions
    */
    auto extensions = get_required_extensions();
    create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    create_info.ppEnabledExtensionNames = extensions.data();

    /*
    Validation layers and debug messenger
    */
    VkDebugUtilsMessengerCreateInfoEXT debug_create_info{};
    if(enable_validation_layers){
        create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        create_info.ppEnabledLayerNames = validation_layers.data();

        populate_debug_messenger_create_info(debug_create_info);
        create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
    } else {
        create_info.enabledLayerCount = 0;
        create_info.pNext = nullptr;
    }

    /*
    Note that most object creation functions in vulkan follow the same parameter structure:
    1. Pointer to struct with the object creation info
    2. Pointer to custom allocator callback (we just set this to nullptr)
    3. Pointer to the variable that stores the handle to the new object

    Object creation functions usally return a VkResult with value VK_SUCCESS or an error code
    such as VK_ERROR_INCOMPATIBLE_DRIVER
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    */
    if(vkCreateInstance(&create_info, nullptr, &instance) != VK_SUCCESS){ VK_ERROR("failed to create VkInstance"); }
    VK_INFO("created VkInstance");
}

bool Device::check_validation_layer_support(){
    // first get number of avalible validation layers
    uint32_t layer_c = 0;
    vkEnumerateInstanceLayerProperties(&layer_c, nullptr);

    // store all the properties of each layer in a vector
    std::vector<VkLayerProperties> layers(layer_c);
    vkEnumerateInstanceLayerProperties(&layer_c, layers.data());

    // check if properties of each layer is available
    for(auto V : validation_layers){
        bool layer_found = false;

        for(const auto& LP : layers){
            if(strcmp(V, LP.layerName) == 0){
                layer_found = true;
                break;
            }
        }

        // even if only one validation layer is not available return false
        if(!layer_found){ return false; }
    }
    return true;
}

std::vector<const char*> Device::get_required_extensions(){
    /*
    GLFW Extensions

    Extensions for vulkan to interface with GLFW so we use built in 
    glfw function that returns the extension(s)
    */
    uint32_t glfw_extension_c = 0;
    const char** glfw_extensions;
    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_c);

    // vector to hold all extensions
    std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_c);

    if(enable_validation_layers){
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    /*
    vkEnumerateInstanceExtensionProperties param structure:
    1. string to specify which validation layer to get extension layers from
    2. pointer to uint32_t to get or hold # of extensions
    3. pointer to a list of VkExtensionProperties structs
    
    If 3. is nullptr then 2. is simply set to the # of extensions
    */
    uint32_t available_extension_c = 0;
    
    vkEnumerateInstanceExtensionProperties(nullptr, &available_extension_c, nullptr); // get # of extentions
    std::vector<VkExtensionProperties> available_extensions(available_extension_c); // set up vector to hold VkExtensionProperties structs

    vkEnumerateInstanceExtensionProperties(nullptr, &available_extension_c, available_extensions.data());   // get VkExtensionProperties structs

    VK_INFO("number of available extensions: " << available_extension_c);
    
    VK_INFO("available extensions:");
    for(const auto& e : available_extensions){ P('\t' << e.extensionName << '\n'); }

    P("required extensions:\n");
    for(const auto& e : extensions){ P('\t' << e << '\n'); }
    
    return extensions;
}

void Device::pick(){
    uint32_t device_c = 0;
    
    /*
    vkEnumeratePhysicalDevices
    @param our VkInstance
    @param # of physical devices
    @param array of VkPhysicalDevice handles
    @return VK_SUCCESS or some error code
    */
    vkEnumeratePhysicalDevices(instance, &device_c, nullptr);

    if(device_c == 0){ VK_ERROR("failed to find GPUs with Vulkan support"); }
    VK_INFO("physical device count: " << device_c);

    std::vector<VkPhysicalDevice> devices(device_c);
    vkEnumeratePhysicalDevices(instance, &device_c, devices.data());

    // just pick the first device
    for(const auto& d : devices){
        if(is_device_suitable(d)){
            physical_device = d;
            break;
        }
    }

    if(physical_device == VK_NULL_HANDLE){ VK_ERROR("failed to find a suitable GPU"); }
    
    VkPhysicalDeviceProperties device_properties;
    vkGetPhysicalDeviceProperties(physical_device, &device_properties);
    VK_INFO("physical device: " << device_properties.deviceName);
}

bool Device::is_device_suitable(VkPhysicalDevice device){
    QueFamilyIndices indices = find_que_families(device);
    bool extensions_support = check_device_extension_support(device);

    /* Get basic device properties such as
    - api and driver version
    - vender and device id */
    VkPhysicalDeviceProperties device_properties;
    vkGetPhysicalDeviceProperties(device, &device_properties);

    /* Get device features, there are alot of features that
    are returned to device_features list of them are
    https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceFeatures.html*/
    VkPhysicalDeviceFeatures device_features;
    vkGetPhysicalDeviceFeatures(device, &device_features);
    
    /* Checking if device supports swapchain */
    bool sc = false;
    if(extensions_support){
        SwapChainSupportDetails support = query_swapchain_support(device);
        sc = !support.formats.empty() && !support.present_modes.empty();
    }

    return ~indices && extensions_support && sc && device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && device_features.geometryShader;
}

bool Device::check_device_extension_support(VkPhysicalDevice device){
    uint32_t count;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);

    std::vector<VkExtensionProperties> extensions(count);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &count, extensions.data());

    std::set<std::string> required_extensions(device_extensions.begin(), device_extensions.end());

    for(const auto& e : extensions){
        required_extensions.erase(e.extensionName);
    }
    return required_extensions.empty();
}

QueFamilyIndices Device::find_que_families(VkPhysicalDevice device){
    QueFamilyIndices indices;
    
    /* Get number of queue families available in device */
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
    
    /* Get queue family properties of device */
    std::vector<VkQueueFamilyProperties> que_families(count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, que_families.data());

    for(int i = 0; i < count; i++){
        /* Check to see if one of the queue families support VK_QUEUE_GRAPHICS_BIT */
        if(que_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
            indices.graphics_family = i;
        }

        /* Check to see if one of the queue families support surfaceKHR presentation */ 
        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);
        if(present_support){
            indices.present_family = i;
        }
    }

    return indices;
}

void Device::create_logical_device(){
    QueFamilyIndices indices = find_que_families(physical_device);

    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    std::set<uint32_t> unique_queue_families = {
        indices.graphics_family.value(),
        indices.present_family.value()
    };

    float queue_priority = 1.f;
    for(uint32_t qf : unique_queue_families){        
        VkDeviceQueueCreateInfo queue_create_info = {};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = qf;
        queue_create_info.queueCount = 1;
        queue_create_info.pQueuePriorities = &queue_priority;
        queue_create_infos.push_back(queue_create_info);
    }

    VkPhysicalDeviceFeatures features = {};

    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
    create_info.pQueueCreateInfos = queue_create_infos.data();
    create_info.pEnabledFeatures = &features;

    /* enable VK_KHR_swapchain */
    create_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.size());
    create_info.ppEnabledExtensionNames = device_extensions.data();

    /* This is unnecessary but we have this here to support older vulkan devices */
    if(enable_validation_layers){
        create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        create_info.ppEnabledLayerNames = validation_layers.data();
    } else {
        create_info.enabledLayerCount = 0;
    }

    if(vkCreateDevice(physical_device, &create_info, nullptr, &device) != VK_SUCCESS){
        VK_ERROR("failed to create logical device");
    }
    VK_INFO("created logical device");

    vkGetDeviceQueue(device, indices.graphics_family.value(), 0, &gfx_queue);
    vkGetDeviceQueue(device, indices.present_family.value(), 0, &present_queue);
}

SwapChainSupportDetails Device::query_swapchain_support(VkPhysicalDevice device){
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
    
    uint32_t format_c, present_c;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_c, nullptr);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_c, nullptr);

    if(format_c != 0){
        details.formats.resize(format_c);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_c, details.formats.data());
    }

    if(present_c != 0){
        details.present_modes.resize(present_c);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_c, details.present_modes.data());
    }

    return details;
}

VkFormat Device::find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features){
    for (VkFormat format : candidates) {
        VkFormatProperties properties;
        vkGetPhysicalDeviceFormatProperties(physical_device, format, &properties);

        if (tiling == VK_IMAGE_TILING_LINEAR && (properties.linearTilingFeatures & features) == features) {
            return format;
        } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (properties.optimalTilingFeatures & features) == features) {
            return format;
        }
    }
    VK_ERROR("failed to find supported format");
}

uint32_t Device::find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties mem_properties;
    vkGetPhysicalDeviceMemoryProperties(physical_device, &mem_properties);
    
    for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++){
        if((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties){
            return i;
        }
    }
    VK_ERROR("failed to find suitable memory type!");
}

void Device::create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory){
    VkBufferCreateInfo buffer_info = {};
    buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_info.size = size;
    buffer_info.usage = usage;
    buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(device, &buffer_info, nullptr, &buffer) != VK_SUCCESS){
        VK_ERROR("failed to create vertex buffer");
    }
    VK_INFO("Created vertex buffer");

    VkMemoryRequirements mem_requirements;
    vkGetBufferMemoryRequirements(device, buffer, &mem_requirements);

    VkMemoryAllocateInfo allocation_info = {};
    allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocation_info.allocationSize = mem_requirements.size;
    allocation_info.memoryTypeIndex = find_memory_type(mem_requirements.memoryTypeBits, properties);

    if(vkAllocateMemory(device, &allocation_info, nullptr, &buffer_memory) != VK_SUCCESS){
        VK_ERROR("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(device, buffer, buffer_memory, 0);
}

VkCommandBuffer Device::begin_single_time_commands(){
    VkCommandBufferAllocateInfo allocation_info = {};
    allocation_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocation_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocation_info.commandPool = command_pool;
    allocation_info.commandBufferCount = 1;

    VkCommandBuffer command_buffer;
    vkAllocateCommandBuffers(device, &allocation_info, &command_buffer);

    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(command_buffer, &begin_info);
    return command_buffer;
}

void Device::end_single_time_commands(VkCommandBuffer command_buffer){
    vkEndCommandBuffer(command_buffer);

    VkSubmitInfo submit_info = {};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command_buffer;

    vkQueueSubmit(gfx_queue, 1, &submit_info, VK_NULL_HANDLE);
    vkQueueWaitIdle(gfx_queue);

    vkFreeCommandBuffers(device, command_pool, 1, &command_buffer);
}

void Device::copy_buffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size){
    VkCommandBuffer command_buffer = begin_single_time_commands();

    VkBufferCopy copy_region{};
    copy_region.srcOffset = 0;
    copy_region.dstOffset = 0;
    copy_region.size = size;
    vkCmdCopyBuffer(command_buffer, src_buffer, dst_buffer, 1, &copy_region);

    end_single_time_commands(command_buffer);
}

void Device::copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layer_count){
    VkCommandBuffer command_buffer = begin_single_time_commands();

    VkBufferImageCopy region{};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = layer_count;

    region.imageOffset = {0, 0, 0};
    region.imageExtent = {width, height, 1};

    vkCmdCopyBufferToImage(command_buffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    end_single_time_commands(command_buffer);
}

void Device::create_image_with_info(const VkImageCreateInfo& image_info, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& image_memory){
    if(vkCreateImage(device, &image_info, nullptr, &image) != VK_SUCCESS){
        VK_ERROR("failed to create image");
    }

    VkMemoryRequirements mem_requirements;
    vkGetImageMemoryRequirements(device, image, &mem_requirements);

    VkMemoryAllocateInfo allocation_info = {};
    allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocation_info.allocationSize = mem_requirements.size;
    allocation_info.memoryTypeIndex = find_memory_type(mem_requirements.memoryTypeBits, properties);

    if(vkAllocateMemory(device, &allocation_info, nullptr, &image_memory) != VK_SUCCESS){
        VK_ERROR("failed to allocate image memory");
    }

    if(vkBindImageMemory(device, image, image_memory, 0) != VK_SUCCESS){
        VK_ERROR("failed to bind image memory");
    }
}

void Device::create_command_pool(){
    QueFamilyIndices qfi = find_physical_que_families();
    
    if (!~qfi){
        VK_ERROR("failed to create command pool");
    }

    VkCommandPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.queueFamilyIndex = qfi.graphics_family.value();
    pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(device, &pool_info, nullptr, &command_pool) != VK_SUCCESS) {
        VK_ERROR("failed to create command pool");
    }
    VK_INFO("created command pool");
}

}
