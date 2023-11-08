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

struct Color {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
};

struct GameObject {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    Color color;

    std::shared_ptr<Object> object;
};

class EnginePlugin {
public:
    virtual void init() = 0;
    virtual void update(float delta_time) = 0;
    virtual void close() = 0;
};

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
    
    std::shared_ptr<GameObject> create_object(const std::vector<ObjectModel::Vertex>& vertices, glm::vec2& translation, Color color);
    
    std::shared_ptr<GameObject> create_square(float x, float y, float width, float height, Color color);
    std::shared_ptr<GameObject> create_triangle(
        float x1,
        float y1,
        float x2,
        float y2,
        float x3,
        float y3,
        Color color
    );
    std::shared_ptr<GameObject> create_circle(float x, float y, float radius, Color color);
    
    void add_plugin(std::shared_ptr<EnginePlugin>&& plugin);

private:
    Window window{WIDTH, HEIGHT};
    Device device{window};
    Renderer renderer{window, device};

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<EnginePlugin>> plugins;

    float get_rand(){ return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); }
};

}
