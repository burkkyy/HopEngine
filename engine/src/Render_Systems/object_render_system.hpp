#pragma once

#include "Device/device.hpp"
#include "Pipeline/pipeline.hpp"
#include "Objects/object.hpp"

#include <memory>

namespace hop {

class ObjectRenderSystem {
public:
    ObjectRenderSystem(Device& device, VkRenderPass render_pass);
    ~ObjectRenderSystem();

    ObjectRenderSystem(const ObjectRenderSystem&) = delete;
    ObjectRenderSystem& operator=(const ObjectRenderSystem&) = delete;

    void render_objects(VkCommandBuffer command_buffer, std::vector<Object>& objects);

private:
    void create_pipline_layout();
    void create_pipeline(VkRenderPass render_pass);

    Device& device;

    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipeline_layout;
};

}
