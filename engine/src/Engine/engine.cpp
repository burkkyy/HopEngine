#include "engine.hpp"

#include "Utilities/status_print.hpp"
#include "Render_Systems/object_render_system.hpp"

#include <chrono>

namespace hop {

Engine::Engine(){ }

Engine::~Engine(){ }

void Engine::run(){
    ObjectRenderSystem render_system{device, renderer.get_swapchain_render_pass()};

    auto old_time = std::chrono::high_resolution_clock::now();

    for(auto plugin : plugins){
        plugin->init();
    }

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

    for(auto plugin : plugins){
        plugin->close();
    }
}

std::shared_ptr<Object> Engine::create_object(const std::vector<Vertex>& vertices, const glm::vec2& translation, const glm::vec3& color){
    auto model = std::make_shared<ObjectModel>(device, vertices);
    std::shared_ptr<Object> object = std::make_shared<Object>();
    object->model = model;
    object->color = color;
    object->transform.translation = translation;
    objects.push_back(object);
    return object;
}

std::shared_ptr<Square> Engine::create_square(float x, float y, float width, float height, Color color){
    std::vector<Vertex> vertices = {
        {{0, 0}},
        {{width, 0}},
        {{width, height}},
        {{0, 0}},
        {{0, height}},
        {{width, height}}
    };

    auto square = std::make_shared<Square>();
    square->set_object(create_object(vertices, {x, y}, color));
    square->width = width;
    square->height = height;
    return square;
}

std::shared_ptr<GameObject> Engine::create_triangle(Vertex v1, Vertex v2, Vertex v3, Color color){
    std::vector<Vertex> vertices = {{v1}, {v2}, {v3}};

    auto game_object = std::make_shared<GameObject>();
    game_object->set_object(create_object(vertices, {0, 0}, color));

    return game_object;
}

std::shared_ptr<Circle> Engine::create_circle(float x, float y, float radius, Color color){
    int sides = std::max(static_cast<int>(radius * 100.0f), 8);
    std::vector<Vertex> side_vertices = {};

    for(int i = 0; i < sides; i++){
        float theta = glm::two_pi<float>() * i / sides;
        float x1 = radius * glm::cos(theta);
        float y1 = radius * glm::sin(theta);
        side_vertices.push_back({{x1, y1}});
    }

    side_vertices.push_back({{0, 0}});

    std::vector<Vertex> vertices{};
    for(int i = 0; i < sides; i++){
        vertices.push_back(side_vertices[i]);
        vertices.push_back(side_vertices[(i + 1) % sides]);
        vertices.push_back(side_vertices[sides]);
    }
    
    auto circle = std::make_shared<Circle>();
    circle->set_object(create_object(vertices, {x, y}, color));
    circle->radius = radius;
    
    return circle;
}

GLFWwindow* Engine::get_window(){
    return Window.get_window();
}


}
