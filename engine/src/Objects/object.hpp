/**
 * @file object.hpp
 * @author Caleb Burke
 * @date Nov 8, 2023
 *
 * Class definitions for classes that abstracts from an object being a bunch
 * of vertices
 *
 */

#pragma once

#include "Device/device.hpp"

#define GLM_FORCE_RADIANS
#define GLF_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vulkan/vulkan.h>

#include <memory>

namespace hop {

/**
 * @brief Model for an object
 *
 * Class defining the base requirements for any object in the engine
 *
 */
class ObjectModel {
public:
    /**
     * @brief Vertex of a shape
     *
     * This struct stores the coords of a certain vertex in a shape. Instance's
     * of this object is put into an array and passed to the vertex shader.
     *
     */
    struct Vertex {
        glm::vec2 position = {};
        glm::vec3 color = {};

        static std::vector<VkVertexInputBindingDescription> get_binding_descriptions();
        static std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions();

        bool operator==(const Vertex& v) const {
            return position == v.position && color == v.color;
        }
    };

    /**
     * @brief Default Constructor
     * @param device
     * @param vertices
     */
    ObjectModel(Device& device, const std::vector<Vertex>& vertices);
    
    /**
     * @brief Default Deconstructor
     */
    ~ObjectModel();

    // Prevents copying of this object
    ObjectModel(const ObjectModel&) = delete;
    ObjectModel& operator=(const ObjectModel&) = delete;

    /**
     * @brief Binds vertex buffer to vulkan
     *
     * Binds a specific vertex buffer to a specific command buffer. This is done
     * so the graphics pipeline has access to the vertex data
     * 
     * @param command_buffer The command buffer the vertex buffers will be bound to
     * @return void
     */
    void bind(VkCommandBuffer command_buffer);
    
    /**
     * @brief Draw the vertex buffer
     *
     * Passes the vertex buffer to the vulkan pipeline for rendering of
     * the vertices
     *
     * @param command_buffer
     * @return void
     */
    void draw(VkCommandBuffer command_buffer);

private:
    void create_vertex_buffers(const std::vector<Vertex>& vertices);

    Device& device;
    VkBuffer vertex_buffer;
    VkDeviceMemory vertex_buffer_memory;
    uint32_t vertex_count;
};

/**
 * @brief Transform struct
 *
 * Struct definition of a object that holds the transform data of an object.
 * This can store where an object should be stored and how big it is
 *
 */
struct Transform {
    glm::vec2 translation = {};
    glm::vec2 scale = { 1.0f, 1.0f };

    glm::mat2 mat2(){
        return {
            { scale.x, 0.0f },
            { 0.0f, scale.y }
        };
    }
};

/**
 * @brief Class for objects 
 *
 * Holds the data of a object's model and where it should be on the screen.
 * This class is an abstraction from ObjectModel
 *
 */
class Object {
public:
    /**
     * @brief Default Constructor
     */
    Object(){}

    // Prevents copying and moving of this object
    Object(const Object&) = delete;
    Object& operator=(Object&) = delete;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;    

    std::shared_ptr<ObjectModel> model = {};
    glm::vec3 color = {};
    Transform transform = {};
};

}
