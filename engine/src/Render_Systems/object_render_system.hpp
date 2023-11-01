/* @author Caleb Burke
 * @date 2023-10-5
 * NOTE: Finish writing doc
 * Main api for graphics engine
*/

#pragma once

#include "Device/device.hpp"
#include "Pipeline/pipeline.hpp"
#include "Objects/game_object.hpp"

#include <memory>

namespace hop {

class GameObjectRenderSystem {
public:
    GameObjectRenderSystem(Device& device, VkRenderPass render_pass);
    ~GameObjectRenderSystem();

    GameObjectRenderSystem(const GameObjectRenderSystem&) = delete;
    GameObjectRenderSystem& operator=(const GameObjectRenderSystem&) = delete;

    void render_game_objects(VkCommandBuffer command_buffer, std::vector<GameObject>& game_objects);

private:
    void create_pipline_layout();
    void create_pipeline(VkRenderPass render_pass);

    Device& device;

    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipeline_layout;
};

}
