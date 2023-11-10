/**
 * @file pipeline.hpp
 * @author Caleb Burke
 * @date Nov 6, 2023
 *
 * The files creates the graphics pipeline as defined in the vulkan sdk
 *
 */

#pragma once

#include "Device/device.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace hop {

/**
 * @brief Helper struct
 *
 * Helper struct for storing all the VK create info structs required for 
 * creating the pipeline
 *
 */
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

/**
 * @brief Vulkan Pipeline
 *
 * This class creates the graphics pipeline as defined by the vulkan sdk
 *
 * NOTE: Depends on a device to be created
 * NOTE: Depends on a PiplineConfigInfo struct to be filled out
 */
class Pipeline {
public:

    /**
     * @brief Constructor
     *
     * This creates the pipeline based on the config_info
     *
     * @param device Reference to the vulkan device
     * @param vert_filepath File path to the vertex shader spv
     * @param frag_filepath File path to the fragment shader spv
     * @param config_info Object holding the configuration of the pipeline
     */
    Pipeline(
        Device& device,
        const std::string& vert_filepath,
        const std::string& frag_filepath,
        const PipelineConfigInfo& config_info
    );

    /**
     * @brief Default Deconstructor
     * 
     * Responsible for destroying the vulkan pipleine and shader modules 
     *
     */
    ~Pipeline();

    // Prevents copying of this object
    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    /**
     * @brief Binds pipeline to a command buffer
     *
     * Specifics to the command buffer the graphics pipeline it should use while
     * rendering
     *
     * @param command_buffer
     * @return void
     */
    void bind(VkCommandBuffer command_buffer);

    /**
     * @brief Creates the default config for the pipeline
     *
     * This creates the default configuration of the graphics pipeline, this is 
     * used while initially creating the pipeline.
     *
     * @param config_info
     * @return void
     */
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
