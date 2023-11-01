#include "engine.hpp"

#include "Utilities/status_print.hpp"

namespace hop {

struct SimplePushConstantData {
    glm::mat3 transform{1.0f};
    alignas(16) glm::vec3 color;  
};

Engine::Engine(){
    load_game_objects();
    create_pipline_layout();
    create_pipeline(renderer.get_swapchain_render_pass());
    run();
}

Engine::~Engine(){

}

void Engine::run(){
    while(!window.should_close()){
        glfwPollEvents();

        if(auto command_buffer = renderer.begin_frame()){
            renderer.begin_swapchain_render_pass(command_buffer);
            render_game_objects(command_buffer, game_objects);
            renderer.end_swapchain_render_pass(command_buffer);
            renderer.end_frame();
        }
    }
    vkDeviceWaitIdle(device.get_device());
}

void Engine::render_game_objects(VkCommandBuffer command_buffer, std::vector<Object>& game_objects){
    pipeline->bind(command_buffer);

    for(auto& obj : game_objects){
        obj.model->bind(command_buffer);
        obj.model->draw(command_buffer);
    }
}

void Engine::create_pipline_layout(){
    VkPipelineLayoutCreateInfo pipeline_layout_info{};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pSetLayouts = nullptr;
    pipeline_layout_info.pushConstantRangeCount = 1;
    pipeline_layout_info.pPushConstantRanges = nullptr;

    if(vkCreatePipelineLayout(device.get_device(), &pipeline_layout_info, nullptr, &pipeline_layout) != VK_SUCCESS){
        VK_ERROR("failed to create pipeline layout");
    }
}

void Engine::create_pipeline(VkRenderPass render_pass){
    assert(pipeline_layout != nullptr);
    
    PipelineConfigInfo pipeline_config = {};
    Pipeline::default_config(pipeline_config);
    pipeline_config.renderPass = render_pass;
    pipeline_config.pipelineLayout = pipeline_layout;
    
    pipeline = std::make_unique<Pipeline>(
        device,
        "shader.vert.spv",
        "shader.frag.spv",
        pipeline_config
    );
}

void Engine::load_game_objects(){

}

}
