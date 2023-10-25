#pragma once

#include "Device/device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vulkan/vulkan.h>

#include <vector>

namespace hop {

class Object_Model {
public:
    struct Vertex {
        glm::vec2 position{};
        glm::vec3 color{};
        glm::vec3 normal{};
        glm::vec2 uv{};

        static std::vector<VkVertexInputBindingDescription> get_binding_descriptions();
        static std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions();

        bool operator==(const Vertex& v) const {
            return position == v.position && color == v.color && normal == v.color && uv == v.uv;
        }
    };

    Object_Model(Device& device, const std::vector<Vertex>& vertices);
    ~Object_Model();

    Object_Model(const Object_Model&) = delete;
    Object_Model& operator=(const Object_Model&) = delete;

    void bind(VkCommandBuffer command_buffer);
    void draw(VkCommandBuffer command_buffer);

private:
    void create_vertex_buffers(const std::vector<Vertex>& vertices);

    Device& device;
    VkBuffer vertex_buffer;
    VkDeviceMemory vertex_buffer_memory;
    uint32_t vertex_count;
};

}
