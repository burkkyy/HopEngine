#include "engine.hpp"
#include "Utilities/status_print.hpp"
#include <algorithm>

namespace hop {

Engine::Engine(const char* window_title){ 
    this->window_title = window_title;
    window = std::make_shared<Window>(window_title);
}

Engine::~Engine(){

}

void Engine::run(bool fullscreen){
    window->set_window_size(width,height);
    EngineGameObject::set_resolution(this->width,this->height);
    window->Initialize(fullscreen);
    device = std::make_shared<Device>(*window);
    renderer = std::make_shared<Renderer>(*window, *device);
    render_system = std::make_shared<ObjectRenderSystem>(*device, renderer->get_swapchain_render_pass());
    this->update();
}

std::shared_ptr<Object> Engine::create_object(const std::vector<Vertex>& vertices, const glm::vec2& translation, const glm::vec3& color){
    auto model = std::make_shared<ObjectModel>(*device, vertices);
    std::shared_ptr<Object> object = std::make_shared<Object>();
    object->model = model;
    object->color = color;
    object->transform.translation = translation;
    objects.push_back(object);
    return object;
}

std::shared_ptr<EngineRectangle> Engine::create_rectangle(int x, int y, int width, int height, Color color){
    float float_width = 2.0 * width / this->width;
    float float_height = 2.0 * height / this->height;
    float float_x = x*2.0/this->width;
    float float_y = 2.0 - ((2.0*y + 2.0*height)/this->height);
    std::vector<Vertex> vertices = {
        {{0, 0}},
        {{0, float_height}},
        {{float_width, 0}},
        {{0, float_height}},
        {{float_width, 0 }},
        {{float_width, float_height}}
    };

    auto rectangle = std::make_shared<EngineRectangle>();
    rectangle->set_object(create_object(vertices, {float_x, float_y}, color));
    rectangle->x = x;
    rectangle->y = y;
    rectangle->width = width;
    rectangle->height = height;
    return rectangle;
}

std::shared_ptr<EngineGameObject> Engine::create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color){
    
    int min_x = std::min(v1x,v2x);
    min_x = std::min(min_x, v3x);
    int min_y = std::min(v1y,v2y);
    min_y = std::min(min_y,v3y);
    int max_x = std::max(v1x,v2x);
    max_x = std::max(max_x,v3x);
    int max_y = std::max(v1y,v2y);
    max_y = std::max(max_y,v3y);
    float f_v1x = (2.0 * v1x)/this->width;
    float f_v1y = 2 - (2.0 * v1y)/this->height;
    float f_v2x = (2.0 * v2x)/this->width;
    float f_v2y = 2 - (2.0 * v2y)/this->height;
    float f_v3x = (2.0 * v3x)/this->width;
    float f_v3y = 2 - (2.0 * v3y)/this->height;
    Vertex v1{{f_v1x,f_v1y}};
    Vertex v2{{f_v2x,f_v2y}};
    Vertex v3{{f_v3x,f_v3y}};
    std::vector<Vertex> vertices = {{v1}, {v2}, {v3}};
    auto game_object = std::make_shared<EngineGameObject>();
    game_object->set_object(create_object(vertices, {0, 0}, color));
    game_object->x = min_x;
    game_object->y = min_y;
    game_object->width = max_x - min_x;
    game_object->height = max_y - min_y;
    return game_object;
}

std::shared_ptr<EngineCircle> Engine::create_circle(int x, int y, int radius, Color color){
    float f_radius = 2.0*radius/EngineGameObject::resolution_height;
    float r_x = (2.0*radius)/EngineGameObject::resolution_width;
    float r_y = (-2.0*radius)/EngineGameObject::resolution_height;
    float f_x = (2.0*x)/EngineGameObject::resolution_width;
    float f_y =  2.0 - (2.0*y + 4.0*radius)/EngineGameObject::resolution_height;

    int sides = std::max(static_cast<int>(f_radius * 100.0f), 8);
    std::vector<Vertex> side_vertices = {};
    for(int i = 0; i < sides; i++){
        float theta = glm::two_pi<float>() * i / sides;
        float x1 = r_x * glm::cos(theta);
        float y1 = r_y * glm::sin(theta);
        side_vertices.push_back({{x1, y1}});
    }

    side_vertices.push_back({{0, 0}});

    std::vector<Vertex> vertices{};
    for(int i = 0; i < sides; i++){
        vertices.push_back(side_vertices[i]);
        vertices.push_back(side_vertices[(i + 1) % sides]);
        vertices.push_back(side_vertices[sides]);
    }
    
    auto circle = std::make_shared<EngineCircle>();
    circle->set_object(create_object(vertices, {f_x + r_x,f_y - r_y}, color));
    circle->radius = radius;
    circle->x = x;
    circle->y = y;
    circle->width = 2*radius;
    circle->height = 2*radius;
    
    return circle;
}

bool Engine::set_window_size(int width, int height){
    
    if((width < 1)||(width > 2000)){
        return false;
    }
    
    else if((height < 1)||(height > 2000)){
        return false;
    }
    else{
        this->width = width;
        this->height = height;
        return true;
    }
}

int Engine::get_resolution_width(){
    return window->get_resolution_width();
}

int Engine::get_resolution_height(){
    return window->get_resolution_height();
}

void Engine::update(){

    if(!(window->should_close())){
        glfwPollEvents();
        if(auto command_buffer = renderer->begin_frame()){
            renderer->begin_swapchain_render_pass(command_buffer);
            render_system->render_objects(command_buffer, objects);
            renderer->end_swapchain_render_pass(command_buffer);
            renderer->end_frame();
        }
    }
    else{
        this->window_open= false;
    }
    vkDeviceWaitIdle(device->get_device());

}

float EngineGameObject::coord_to_float_x(int i_x){
    return i_x*2.0/this->resolution_width;
}

float EngineGameObject::coord_to_float_y(int i_y){
    return (-2.0 *i_y)/this->resolution_height;
}

void EngineGameObject::set_object(std::shared_ptr<Object>&& obj){
    object.reset();
    object = obj;
}

void EngineGameObject::set_color(const Color& new_color){
    color = new_color;
    object->color = new_color;
}

void EngineGameObject::set_resolution(int res_width, int res_height ){
    resolution_width = res_width;
    resolution_height = res_height;
}
}

