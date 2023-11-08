#include "engine.hpp"

#include "Utilities/status_print.hpp"
#include "Render_Systems/object_render_system.hpp"

#include <chrono>

namespace hop {

Engine::Engine(){
    for(auto plugin : plugins){
        plugin->init();
    }
}

Engine::~Engine(){
    for(auto plugin : plugins){
        plugin->close();
    }
}

void Engine::run(){
    ObjectRenderSystem render_system{device, renderer.get_swapchain_render_pass()};

    auto old_time = std::chrono::high_resolution_clock::now();

    while(!window.should_close()){
        glfwPollEvents();

        if(auto command_buffer = renderer.begin_frame()){
            renderer.begin_swapchain_render_pass(command_buffer);
            render_system.render_objects(command_buffer, objects);
            renderer.end_swapchain_render_pass(command_buffer);
            renderer.end_frame();
        }

        auto new_time = std::chrono::high_resolution_clock::now();
        float delta_time = std::chrono::duration<float, std::chrono::seconds::period>(new_time - old_time).count();
        old_time = new_time;
        for(auto plugin : plugins){
            plugin->update(delta_time);
        }
    }
    vkDeviceWaitIdle(device.get_device());
}

std::shared_ptr<Object> Engine::create_object(const std::vector<ObjectModel::Vertex>& vertices, glm::vec2& translation, Color color){
    auto model = std::make_shared<ObjectModel>(device, vertices);
    std::shared_ptr<Object> object = std::make_shared<Object>();
    object->model = model;
    object->color = {color.r, color.g, color.b};
    object->transform.translation = translation;
    objects.push_back(object);
    return object;
}

std::shared_ptr<Object> Engine::create_square(float x, float y, float width, float height, Color color){
    std::vector<ObjectModel::Vertex> vertices = {
        {{0, 0}},
        {{width, 0}},
        {{width, height}},
        {{0, 0}},
        {{0, height}},
        {{width, height}}
    };

    glm::vec2 translation = {x, y};

    return create_object(vertices, translation, color);
}

std::shared_ptr<Object> Engine::create_triangle(
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3,
    Color color
){
    std::vector<ObjectModel::Vertex> vertices = {
        {{x1, y1}},
        {{x2, y2}},
        {{x3, y3}},
    };

    glm::vec2 translation = {0, 0};

    return create_object(vertices, translation, color);
}

std::shared_ptr<Object> Engine::create_circle(float x, float y, float radius, Color color){
    int sides = std::max(static_cast<int>(radius * 100.0f), 8);
    std::vector<ObjectModel::Vertex> side_vertices = {};

    for(int i = 0; i < sides; i++){
        float theta = glm::two_pi<float>() * i / sides;
        float x1 = radius * glm::cos(theta);
        float y1 = radius * glm::sin(theta);
        side_vertices.push_back({{x1, y1}});
    }

    side_vertices.push_back({{0, 0}});

    std::vector<ObjectModel::Vertex> vertices{};
    for(int i = 0; i < sides; i++){
        vertices.push_back(side_vertices[i]);
        vertices.push_back(side_vertices[(i + 1) % sides]);
        vertices.push_back(side_vertices[sides]);
    }

    glm::vec2 translation = {x, y};

    return create_object(vertices, translation, color);
}

void Engine::add_plugin(std::shared_ptr<EnginePlugin>&& plugin){
    plugins.push_back(std::move(plugin));
}

}
