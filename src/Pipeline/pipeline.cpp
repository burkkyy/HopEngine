#include "pipeline.hpp"

#include "Utilities/status_print.hpp"
#include "Object_Model/object_model.hpp"

#include <fstream>

namespace hop {

Pipeline::Pipeline(
    Device& d,
    const std::string& vert_filepath,
    const std::string& frag_filepath,
    const PipelineConfigInfo& config_info
) : device{d} {
    create_shader_module(vert_filepath, &vert);
    create_shader_module(frag_filepath, &frag);
    create_graphics_pipeline(config_info);
}

Pipeline::~Pipeline(){
    vkDestroyShaderModule(device.get_device(), vert, nullptr);
    VK_INFO("destroyed vertex shader module");

    vkDestroyShaderModule(device.get_device(), frag, nullptr);
    VK_INFO("destroyed fragment shader module");

    vkDestroyPipeline(device.get_device(), pipeline, nullptr);
    VK_INFO("destroyed graphics pipeline");
}

void Pipeline::bind(VkCommandBuffer command_buffer){
    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

void Pipeline::default_config(PipelineConfigInfo& config_info){
    /**
    Variables and definitions on how the graphics pipeline behaves.
    For more detail, see https://vulkan-tutorial.com/en/Drawing_a_triangle/Graphics_pipeline_basics/Fixed_functions
    
    The following will outline the config info struct for each step in the graphics pipeline
    */

    config_info.inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    config_info.inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    config_info.inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

    config_info.viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    config_info.viewportInfo.viewportCount = 1;
    config_info.viewportInfo.pViewports = nullptr;
    config_info.viewportInfo.scissorCount = 1;
    config_info.viewportInfo.pScissors = nullptr;

    config_info.rasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    config_info.rasterizationInfo.depthClampEnable = VK_FALSE;
    config_info.rasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
    config_info.rasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
    config_info.rasterizationInfo.lineWidth = 1.0f;
    config_info.rasterizationInfo.cullMode = VK_CULL_MODE_NONE;
    config_info.rasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    config_info.rasterizationInfo.depthBiasEnable = VK_FALSE;
    config_info.rasterizationInfo.depthBiasConstantFactor = 0.0f;  // Optional
    config_info.rasterizationInfo.depthBiasClamp = 0.0f;           // Optional
    config_info.rasterizationInfo.depthBiasSlopeFactor = 0.0f;     // Optional

    config_info.multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    config_info.multisampleInfo.sampleShadingEnable = VK_FALSE;
    config_info.multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    config_info.multisampleInfo.minSampleShading = 1.0f;           // Optional
    config_info.multisampleInfo.pSampleMask = nullptr;             // Optional
    config_info.multisampleInfo.alphaToCoverageEnable = VK_FALSE;  // Optional
    config_info.multisampleInfo.alphaToOneEnable = VK_FALSE;       // Optional

    config_info.colorBlendAttachment.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
        VK_COLOR_COMPONENT_A_BIT;
    config_info.colorBlendAttachment.blendEnable = VK_FALSE;
    config_info.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    config_info.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    config_info.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
    config_info.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    config_info.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    config_info.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional

    config_info.colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    config_info.colorBlendInfo.logicOpEnable = VK_FALSE;
    config_info.colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;  // Optional
    config_info.colorBlendInfo.attachmentCount = 1;
    config_info.colorBlendInfo.pAttachments = &config_info.colorBlendAttachment;
    config_info.colorBlendInfo.blendConstants[0] = 0.0f;  // Optional
    config_info.colorBlendInfo.blendConstants[1] = 0.0f;  // Optional
    config_info.colorBlendInfo.blendConstants[2] = 0.0f;  // Optional
    config_info.colorBlendInfo.blendConstants[3] = 0.0f;  // Optional

    config_info.depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    config_info.depthStencilInfo.depthTestEnable = VK_TRUE;
    config_info.depthStencilInfo.depthWriteEnable = VK_TRUE;
    config_info.depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
    config_info.depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
    config_info.depthStencilInfo.minDepthBounds = 0.0f;  // Optional
    config_info.depthStencilInfo.maxDepthBounds = 1.0f;  // Optional
    config_info.depthStencilInfo.stencilTestEnable = VK_FALSE;
    config_info.depthStencilInfo.front = {};  // Optional
    config_info.depthStencilInfo.back = {};   // Optional

    config_info.dynamicStateEnables = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    config_info.dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    config_info.dynamicStateInfo.pDynamicStates = config_info.dynamicStateEnables.data();
    config_info.dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(config_info.dynamicStateEnables.size());
    config_info.dynamicStateInfo.flags = 0;
}

std::vector<char> Pipeline::read_file(const std::string& fp){
    std::ifstream f(fp, std::ios::ate | std::ios::binary);
    if(!f.is_open()){ VK_ERROR("failed to open file: " + fp); }

    size_t size = (size_t)f.tellg();
    std::vector<char> buffer(size);

    f.seekg(0);
    f.read(buffer.data(), size);
    f.close();

    return buffer;
}

void Pipeline::create_shader_module(const std::string& filepath, VkShaderModule* mod){
    auto code = read_file(filepath);
    
    VkShaderModuleCreateInfo create_info{
        VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        nullptr,
        0,
        code.size(),
        reinterpret_cast<const uint32_t*>(code.data()),
    };

    if(vkCreateShaderModule(device.get_device(), &create_info, nullptr, mod) != VK_SUCCESS){
        VK_ERROR("failed to create shader module");
    }
    VK_INFO("Created shader module");
}

void Pipeline::create_graphics_pipeline(const PipelineConfigInfo& config_info){
    assert(config_info.pipelineLayout != VK_NULL_HANDLE);
    assert(config_info.renderPass != VK_NULL_HANDLE);

    VkPipelineShaderStageCreateInfo shader_stages[2] = {
        // vertex shader
        {
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            NULL,
            0, 
            VK_SHADER_STAGE_VERTEX_BIT,
            vert,
            "main",
            NULL,
        },
        // fragment shader
        {
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            NULL,
            0,
            VK_SHADER_STAGE_FRAGMENT_BIT,
            frag,
            "main",
            NULL,
        }
    };

    // Define how vertex data will be passed to the vertex shader in a struct
    auto binding_descriptions = Object_Model::Vertex::get_binding_descriptions();
    auto attribute_descriptions = Object_Model::Vertex::get_attribute_descriptions();

    VkPipelineVertexInputStateCreateInfo vertex_input_info{};
    vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(attribute_descriptions.size());
    vertex_input_info.vertexBindingDescriptionCount = static_cast<uint32_t>(binding_descriptions.size());
    vertex_input_info.pVertexAttributeDescriptions = attribute_descriptions.data();
    vertex_input_info.pVertexBindingDescriptions = binding_descriptions.data();

    VkGraphicsPipelineCreateInfo pipeline_info{};
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount = 2;
    pipeline_info.pStages = shader_stages;
    pipeline_info.pVertexInputState = &vertex_input_info;
    pipeline_info.pInputAssemblyState = &config_info.inputAssemblyInfo;
    pipeline_info.pViewportState = &config_info.viewportInfo;
    pipeline_info.pRasterizationState = &config_info.rasterizationInfo;
    pipeline_info.pMultisampleState = &config_info.multisampleInfo;
    pipeline_info.pColorBlendState = &config_info.colorBlendInfo;
    pipeline_info.pDepthStencilState = &config_info.depthStencilInfo;
    pipeline_info.pDynamicState = &config_info.dynamicStateInfo;

    pipeline_info.layout = config_info.pipelineLayout;
    pipeline_info.renderPass = config_info.renderPass;
    pipeline_info.subpass = config_info.subpass;

    pipeline_info.basePipelineIndex = -1;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

    if(vkCreateGraphicsPipelines(device.get_device(), VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline) != VK_SUCCESS){
        VK_ERROR("failed to create graphics pipeline");
    }
    VK_INFO("Created graphics pipeline!");
}

}
