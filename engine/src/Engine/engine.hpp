/* @author Caleb Burke
 * @date 2023-10-5
 * NOTE: Finish writing doc
 * Main api for graphics engine
*/
#pragma once

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Renderer/renderer.hpp"
#include "Objects/object.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <memory>

namespace hop {

class Engine {
public:
    const int WIDTH = 800;
    const int HEIGHT = 800;
    const char* NAME = "hop engine";

    Engine();
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void run();
    void add_object(const std::vector<ObjectModel::Vertex>& vertices, glm::vec3 color);

private:
    void load_game_objects();

    Window window{WIDTH, HEIGHT};
    Device device{window};
    Renderer renderer{window, device};

    std::vector<Object> game_objects;

    float get_rand(){ return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); }
};

}
