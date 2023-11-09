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
#include <optional>

namespace hop {

using Vertex = ObjectModel::Vertex;
using Color = glm::vec3;

class Engine;

/* @brief Wrapper class for Object class
 *
 *  Wrapper for Object class for better ease of use
 *
 */
class GameObject {
public:
    glm::vec2 position(){
        return object->transform.translation;
    }

    void move(float x, float y){
        object->transform.translation.x += x;
        object->transform.translation.y += y;
    }

    void set_object(std::shared_ptr<Object>&& obj){
        object.reset();
        object = obj;
    }

    void set_color(const Color& new_color){
        color = new_color;
    }

private:
    Color color;
    std::shared_ptr<Object> object;
};


class Square : public GameObject {
public:
    float width = 0.0f;
    float height = 0.0f;
};


class Circle : public GameObject {
public:
    float radius = 0.0f;
};


class EnginePlugin {
public:
    EnginePlugin(Engine& _engine) : engine{_engine} {}

    virtual void init() = 0;
    virtual void update(float delta_time) = 0;
    virtual void close() = 0;

    Engine& engine;
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
    
    std::shared_ptr<Object> create_object(const std::vector<ObjectModel::Vertex>& vertices, const glm::vec2& translation, const glm::vec3& color);
    
    template<typename P>
    void plugin(){
        std::shared_ptr<P> plug = std::make_shared<P>(*this);
        plugins.push_back(std::move(plug));
    }

    std::shared_ptr<Square> create_square(float x, float y, float width, float height, Color color);
    std::shared_ptr<GameObject> create_triangle(Vertex v1, Vertex v2, Vertex v3, Color color);
    std::shared_ptr<Circle> create_circle(float x, float y, float radius, Color color);

private:
    Window window{WIDTH, HEIGHT};
    Device device{window};
    Renderer renderer{window, device};

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<EnginePlugin>> plugins;

    float get_rand(){ return static_cast <float> (rand()) / static_cast <float> (RAND_MAX); }
};

}
