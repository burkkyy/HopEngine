/**
 * @file object_render_system.hpp
 * @author Caleb Burke
 * @date Nov 9, 2023
 *
 * Defines classes for how objects are rendered
 *
 */

#pragma once

#include "Device/device.hpp"
#include "Pipeline/pipeline.hpp"
#include "Objects/object.hpp"

#include <memory>

namespace hop {

/**
 * @brief Rendering system for objects
 *
 * Class that defines a specific system of renderering. This specific system is
 * renderering `object`s, which is simply a bunch of verticies.
 *
 * NOTE: This class creates pipeline
 * NOTE: Depends on a device and a render pass. See renderer for render pass
 */
class ObjectRenderSystem {
public:

    /**
     * @brief Constructor
     *
     * Constructor is resonsible for creating the graphics pipeline object.
     *
     */
    ObjectRenderSystem(Device& device, VkRenderPass render_pass);
    
    /**
     * @brief Default deconstructor
     */
    ~ObjectRenderSystem();

    // Prevents copying of this object
    ObjectRenderSystem(const ObjectRenderSystem&) = delete;
    ObjectRenderSystem& operator=(const ObjectRenderSystem&) = delete;

    /**
     * @brief Renders the all the objects
     *
     * Renders the objects given in the command buffer.
     *
     * NOTE: The transformation of each object are put in a push constant.
     *
     * @param command_buffer list of operations vulkan needs to commit
     * @param objects list of transformations that will be put on objects
     * @return void
     */
    void render_objects(VkCommandBuffer command_buffer, std::vector<std::shared_ptr<Object>>& objects);

private:
    void create_pipline_layout();
    void create_pipeline(VkRenderPass render_pass);

    Device& device;

    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipeline_layout;
};

}
