/* @author Caleb Burke
 * @date 2023-10-5
 * NOTE: Finish writing doc
 * Main api for graphics engine
*/
#pragma once

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Swapchain/swapchain.hpp"
#include "Pipeline/pipeline.hpp"
#include "Renderer/renderer.hpp"
#include "Object_Model/object_model.hpp"
#include "Objects/objects.hpp"

#include <memory>

namespace hop {

class Engine {
public:
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const char* NAME = "hop engine";

    Engine();
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void run();
    void render_game_objects(VkCommandBuffer command_buffer, std::vector<Object>& game_objects);

private:
    void create_pipline_layout();
    void create_pipeline(VkRenderPass render_pass);
    void load_game_objects();

    Window window{WIDTH, HEIGHT};
    Device device{window};
    Renderer renderer{window, device};

    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipeline_layout;

    std::vector<Object> game_objects;

    float get_rand(){ return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); }
};

}
