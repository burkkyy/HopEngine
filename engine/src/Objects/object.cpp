#include "object.hpp"

#include <cstring>

namespace hop {

std::vector<VkVertexInputBindingDescription> ObjectModel::Vertex::get_binding_descriptions(){
    std::vector<VkVertexInputBindingDescription> binding_descriptions(1);
    binding_descriptions[0].binding = 0;
    binding_descriptions[0].stride = sizeof(Vertex);
    binding_descriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    return binding_descriptions;
}

std::vector<VkVertexInputAttributeDescription> ObjectModel::Vertex::get_attribute_descriptions(){
    std::vector<VkVertexInputAttributeDescription> attribute_descriptions(2);
    attribute_descriptions[0].binding = 0;
    attribute_descriptions[0].location = 0;
    attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[0].offset = offsetof(Vertex, position);

    attribute_descriptions[1].binding = 0;
    attribute_descriptions[1].location = 1;
    attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[1].offset = offsetof(Vertex, color);
    return attribute_descriptions;
}

ObjectModel::ObjectModel(Device& device, const std::vector<Vertex>& vertices) : device{device} {
    create_vertex_buffers(vertices);
}

ObjectModel::~ObjectModel(){
    vkDestroyBuffer(device.get_device(), vertex_buffer, nullptr);
    vkFreeMemory(device.get_device(), vertex_buffer_memory, nullptr);
}

void ObjectModel::bind(VkCommandBuffer command_buffer){
    VkBuffer buffer[] = { vertex_buffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(command_buffer, 0, 1, buffer, offsets);
}

void ObjectModel::draw(VkCommandBuffer command_buffer){
    vkCmdDraw(command_buffer, vertex_count, 1, 0, 0);
}

void ObjectModel::create_vertex_buffers(const std::vector<Vertex>& vertices){
    vertex_count = static_cast<uint32_t>(vertices.size());
    assert(vertex_count >= 3);
    
    VkDeviceSize buffer_size = sizeof(vertices[0]) * vertex_count;
    
    device.create_buffer(
        buffer_size,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        vertex_buffer,
        vertex_buffer_memory
    );

    void* data;
    vkMapMemory(device.get_device(), vertex_buffer_memory, 0, buffer_size, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(buffer_size));
    vkUnmapMemory(device.get_device(), vertex_buffer_memory);
}

}
