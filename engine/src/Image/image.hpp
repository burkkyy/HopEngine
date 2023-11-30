#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <memory>
#include <Device/device.hpp>

namespace hop{

class Image{
    public:
    Image(const char* filename);

    static void set_device(std::shared_ptr<Device> device);
    
    private:
    VkImage texture_image;
    VkDeviceMemory texture_image_memory;
    VkImageView texture_image_view;
    VkSampler textureSampler;
    VkDeviceSize image_size;
    int texture_width;
    int texture_height;
    int texture_channels;
    const char* filepath;
    void create_texture_image();
    inline static std::shared_ptr<Device> device; 
    void create_image(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    VkImageView createImageView(VkImage image, VkFormat format);
    void createTextureImageView();
    void createTextureSampler();
};
}