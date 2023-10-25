/* @author Caleb Burke
 * @date 2023-10-5
 * NOTE: Finish writing doc
 * Main api for graphics engine
*/
#pragma once

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Renderer/renderer.hpp"
#include "Objects/game_object.hpp"

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

private:
    void load_game_objects();

    Window window{WIDTH, HEIGHT};
    Device device{window};
    Renderer renderer{window, device};

    std::vector<GameObject> game_objects;

    float get_rand(){ return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); }
};

}
