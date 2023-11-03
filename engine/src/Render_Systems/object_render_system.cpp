#include "object_render_system.hpp"

#include "Utilities/status_print.hpp"

#include <cassert>

namespace hop {

struct PushConstantData {
    glm::mat2 transform{1.f};
    glm::vec2 offset;
    alignas(16) glm::vec3 color;
};

GameObjectRenderSystem::GameObjectRenderSystem(Device& device, VkRenderPass render_pass) : device{device} {
    create_pipline_layout();
    create_pipeline(render_pass);
}

GameObjectRenderSystem::~GameObjectRenderSystem(){
    vkDestroyPipelineLayout(device.get_device(), pipeline_layout, nullptr);
    VK_INFO("destroyed pipeline layout");
}


void GameObjectRenderSystem::render_game_objects(VkCommandBuffer command_buffer, std::vector<GameObject>& game_objects){
    pipeline->bind(command_buffer);

    for(auto& obj : game_objects){
        PushConstantData push{};
        push.offset = obj.transform.translation;
        push.color = obj.color;
        push.transform = obj.transform.mat2();

        vkCmdPushConstants(
            command_buffer,
            pipeline_layout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0,
            sizeof(PushConstantData),
            &push
        );
        obj.model->bind(command_buffer);
        obj.model->draw(command_buffer);
    }
}

void GameObjectRenderSystem::create_pipline_layout(){
    VkPushConstantRange push_constant_range = {};
    push_constant_range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    push_constant_range.offset = 0;
    push_constant_range.size = sizeof(PushConstantData);

    VkPipelineLayoutCreateInfo pipeline_layout_info{};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pSetLayouts = nullptr;
    pipeline_layout_info.pushConstantRangeCount = 1;
    pipeline_layout_info.pPushConstantRanges = &push_constant_range;

    if(vkCreatePipelineLayout(device.get_device(), &pipeline_layout_info, nullptr, &pipeline_layout) != VK_SUCCESS){
        VK_ERROR("failed to create pipeline layout");
    }
}

void GameObjectRenderSystem::create_pipeline(VkRenderPass render_pass){
    assert(pipeline_layout != nullptr);
    
    PipelineConfigInfo pipeline_config = {};
    Pipeline::default_config(pipeline_config);
    pipeline_config.renderPass = render_pass;
    pipeline_config.pipelineLayout = pipeline_layout;
    /*
    #ifndef SHADER_VERT_PATH
    #error "Please define the path of the vert shader spv in SHADER_VERT_PATH"
    #endif
    #ifndef SHADER_FRAG_PATH
    #error "Please define the path of the frag shader spv in SHADER_VERT_PATH"
    #endif
    */
    pipeline = std::make_unique<Pipeline>(
        device,
        //SHADER_VERT_PATH,
        //SHADER_FRAG_PATH,
        "shader.vert.spv",
        "shader.frag.spv",
        pipeline_config
    );
}

}
