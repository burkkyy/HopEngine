/**
 * @file engine.hpp
 * @author Caleb Burke
 * @date Nov 9, 2023
 *
 * Main API for the graphics engine. Most functionality for users of this engine
 * can be found here.
 *
 */

#pragma once

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Renderer/renderer.hpp"
#include "Objects/object.hpp"
//#include "Render_Systems/object_render_system.hpp"
#include "Render_Systems/image_render_system.hpp"
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

/**
 * @brief Wrapper class for Object class
 *
 * Wrapper for Object class for better ease of use
 *
 */
class GameObject {
public:
    int x;
    int y;
    int width;
    int height;
    inline static int resolution_width;
    inline static int resolution_height;

    void move(int x_offset, int y_offset){
                x = x + x_offset;
                y = y + y_offset; 
                float f_move_x = coord_to_float_x(x_offset);
                float f_move_y = coord_to_float_y(y_offset);
                object->transform.translation.x += f_move_x;
                object->transform.translation.y += f_move_y;
        
    }

    void set_object(std::shared_ptr<Object>&& obj);
    void set_color(const Color& new_color);
    static void set_resolution(int res_width, int res_height);
    float coord_to_float_x(int i_x);
    float coord_to_float_y(int i_y);

private:
    Color color;
    std::shared_ptr<Object> object;


};

/**
 * @brief Wrapper class for GameObject
 *
 * This class is an abstraction from GameObject, to be more specific about what
 * kind of GameObject is being created 
 *
 */
class Rectangle : public GameObject {
public:

};

/**
 * @brief Wrapper class for GameObject
 *
 * This class is an abstraction from GameObject, to be more specific about what
 * kind of GameObject is being created 
 *
 */
class Circle : public GameObject {
public:
    int radius = 0;
};


/** 
 * @brief Plugin for Engine
 *
 * To create a plugin, any derived class must:
 *  1. Inherit from hop::EnginePlugin
 *  2. Have default consturtor defined as:
 *       ```cpp
 *           Plugin(hop::Engine& engine) : EnginePlugin(engine) { }
 *       ```
 *  3. Define the following functions:
 *       void init();
 *       void update(float);
 *       void close();
 *
 * NOTE: Every plugin has a reference to the engine, this is so plugins can
 *       create their own objects and call other engine functions
 */
class EnginePlugin {
public:
    EnginePlugin(Engine& _engine) : engine{_engine} {}

    /**
     * @brief starts plugin
     *
     * This function is called when right before the main game loop starts.
     * aka before engine.run() is called.
     *
     * @return void
     */
    virtual void init() = 0;

    /**
     * @brief updates plugin
     *
     * This function is called within the main game engine loop. Every draw
     * call this function is called, along with the functions of all other
     * plugins added to the engine.
     *
     * @param delta_time The amount of time passed since last frame drawn
     * @return void
     */
    virtual void update(float delta_time) = 0;

    /** 
     * @brief closes plugin
     *
     * This function is called right after the game loop ends.
     *
     * @return void
     */
    virtual void close() = 0;

    Engine& engine;
};

/**
 * @brief The game engine
 *
 * The main interface for the game engine. Nearly all the API is found here.
 * 
 * To use the game engine, create this object.
 *
 */
class Engine {

private:
bool cooldown = false;

public:

    /**
     * @brief Default Constructor
     */
    Engine(const char* window_title);
    
    /**
     * @brief Default Deconstructor
     */
    ~Engine();

    bool set_window_size(int width, int height);
    int get_resolution_width();
    int get_resolution_height();
    GLFWwindow* get_glfw_window(){
        return window->get_glfw_window();
    }
    // Prevents copying of this object
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    /**
     * @brief Starts the engine
     *
     * This function starts the main game loop
     * 
     * NOTE: Since this function start the main game loop, this function will
     *       hang until the window is closed 
     *
     * @return void
     */
    void run(bool fullscreen);
    
    void update();

    /**
     * @brief creates an object
     *
     * Creates an object the engine will render. This function takes in any amount
     * of vertices to different shapes. The vertices must be in groups of three,
     * three vertices is the minimum amount of vertices for a shape to have an area,
     * i.e able to render 
     * 
     * @param vertices Array of vertices the object is made up of
     * @param translation Where to object will be moved to
     * @param color Color of the object
     * @return pointer to the created object
     */
    std::shared_ptr<Object> create_object(const std::vector<ObjectModel::Vertex>& vertices, const glm::vec2& translation, const glm::vec3& color);
    
    /**
     * @brief Function to register a plugin
     *
     * This function registers a plugin by taking the type of the implemented
     * plugin and creating an instance of it. All instances of plugins are added
     * to an array of plugins
     *
     * @tparam P Class which derived from EnginePlugin
     * @return void
     */
    template<typename P>
    void plugin(){
        std::shared_ptr<P> plug = std::make_shared<P>(*this);
        plugins.push_back(std::move(plug));
    }

    /**
     * @brief creates a square
     *
     * Creates a square object the engine will render. The (x, y) coord refers 
     * to the top left corner of the shape.
     *
     * @param x x position of square on the screen
     * @param y y position of square on the screen
     * @param width The width of the square
     * @param height The height of the square
     * @param color The color of the square
     * @return pointer to created square object
     */
std::shared_ptr<Rectangle> create_rectangle(int x, int y, int width, int height, Color color);
    
    /**
     * @brief creates a triangle
     *
     * Creates a triangle object the engine will render. All the vertices of the
     * triangle must be specified
     *
     * @param v1 First vertex of the triangle
     * @param v2 Second vertex of the triangle
     * @param v3 Third vertex of the triangle
     * @param color The color of the triangle
     * @return pointer to created object
     */
    std::shared_ptr<GameObject> create_triangle( Vertex v1, Vertex v2, Vertex v3, Color color);
    
    /**
     * @brief creates a circle
     *
     * Creates a circle object the engine will render. The (x, y) coord refers
     * to the center of the circle
     *
     * @param x x position of circle on the screen
     * @param y y position of circle on the screen
     * @param radius The radius of the circle
     * @param color The color of the circle
     * @return pointer to created circle object
     */
    std::shared_ptr<Circle> create_circle(int x, int y, int radius, Color color);
    bool engine_valid;
    std::shared_ptr<Window> window;

private:
    std::shared_ptr<Device> device;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<ObjectRenderSystem> render_system;
    /*Window* window;
    Device* device;
    Renderer* renderer;*/
    const char* window_title;
    int width = 800;
    int height = 600;
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<EnginePlugin>> plugins;

};

}
