#include "engine.hpp"

#include "Utilities/status_print.hpp"
#include "Render_Systems/object_render_system.hpp"

namespace hop {

Engine::Engine(){
    load_game_objects();
}

Engine::~Engine(){
}

void Engine::run(){
/*
    std::shared_ptr<ObjectModel> squareModel = createSquareModel(device, {.5f, .0f});
    std::shared_ptr<ObjectModel> circleModel = createCircleModel(device, 64);

    std::vector<GameObject> physicsObjects = {};

    auto red = GameObject::create_object();
    red.transform.scale = glm::vec2{.05f};
    red.transform.translation = {-0.97000436f, 0.24308753f};
    red.color = {1.f, 0.f, 0.f};
    red.rigidBody2d.velocity = {0.4662036850f, 0.4323657300f};
    red.model = circleModel;
    physicsObjects.push_back(std::move(red));

    auto blue = GameObject::create_object();
    blue.transform.scale = glm::vec2{.05f};
    blue.transform.translation = {0.97000436, -0.24308753};
    blue.color = {0.f, 0.f, 1.f};
    blue.rigidBody2d.velocity = {0.4662036850f, 0.4323657300f};
    blue.model = circleModel;
    physicsObjects.push_back(std::move(blue));

    auto white = GameObject::create_object();
    white.transform.scale = glm::vec2{.05f};
    white.transform.translation = {.0f, .0f};
    white.color = {1.f, 1.f, 1.f};
    white.rigidBody2d.velocity = {-0.93240737f, -0.86473146f};
    white.model = circleModel;
    physicsObjects.push_back(std::move(white));

    
    r1(0) = -r3(0) = (-0.97000436, 0.24308753);
    r2(0) = (0,0);
    v1(0) = v3(0) = (0.4662036850, 0.4323657300); 
    v2(0) = (-0.93240737, -0.86473146)
    

    // create vector field
    std::vector<GameObject> vectorField{};
    int gridCount = 40;
    for (int i = 0; i < gridCount; i++) {
        for (int j = 0; j < gridCount; j++) {
            auto vf = GameObject::create_object();
            vf.transform.scale = glm::vec2(0.005f);
            vf.transform.translation = {
                -1.0f + (i + 0.5f) * 2.0f / gridCount,
                -1.0f + (j + 0.5f) * 2.0f / gridCount};
            vf.color = glm::vec3(1.0f);
            vf.model = squareModel;
            vectorField.push_back(std::move(vf));
        }
    }

    GravityPhysicsSystem gravitySystem{0.81f};
    Vec2FieldSystem vecFieldSystem{};
*/
    ObjectRenderSystem render_system{device, renderer.get_swapchain_render_pass()};

    while(!window.should_close()){
        glfwPollEvents();
        //gravitySystem.update(physicsObjects, 1.f / 60, 5);
        //vecFieldSystem.update(gravitySystem, physicsObjects, vectorField);

        if(auto command_buffer = renderer.begin_frame()){
            renderer.begin_swapchain_render_pass(command_buffer);
            render_system.render_objects(command_buffer, game_objects);
            //render_system.render_game_objects(command_buffer, physicsObjects);
            //render_system.render_game_objects(command_buffer, vectorField);
            renderer.end_swapchain_render_pass(command_buffer);
            renderer.end_frame();
        }
    }
    vkDeviceWaitIdle(device.get_device());
}

void Engine::add_object(const std::vector<ObjectModel::Vertex>& vertices, glm::vec3 color){
    auto model = std::make_shared<ObjectModel>(device, vertices);
    Object object = {};
    object.model = model;
    object.color = color;
    game_objects.push_back(std::move(object));
}

void Engine::load_game_objects(){
}

}
