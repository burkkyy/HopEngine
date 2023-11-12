#pragma once

#include "Device/device.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace hop {

// Helper struct
struct PipelineConfigInfo {
    PipelineConfigInfo(const PipelineConfigInfo&) = delete;
    PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;
    
    VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    std::vector<VkDynamicState> dynamicStateEnables;
    VkPipelineDynamicStateCreateInfo dynamicStateInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
};

class Pipeline {
public:
    Pipeline(
        Device& d,
        const std::string& vert_filepath,
        const std::string& frag_filepath,
        const PipelineConfigInfo& config_info
    );
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    void bind(VkCommandBuffer command_buffer);

    static void default_config(PipelineConfigInfo& config_info);

private:
    static std::vector<char> read_file(const std::string& filepath);
    void create_shader_module(const std::string& filepath, VkShaderModule* shader_module);
    void create_graphics_pipeline(const PipelineConfigInfo& config_info);

    Device& device;
    VkPipeline pipeline;
    VkShaderModule vert;
    VkShaderModule frag;
};

}
