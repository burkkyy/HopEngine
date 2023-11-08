#include "hop.hpp"

#include <iostream>

class MovePlugin : public hop::EnginePlugin {
public:
    void init(){

    }

    void update(float delta_time){
        for(auto obj : objects){
            std::cout << obj->transform.translation.y << std::endl;
            obj->transform.translation.y += 0.01f;
        }
    }

    void close(){

    }

    std::vector<hop::GameObject> objects;    
};

int main(int argc, const char** argv){ 
    // Initialize the game engine
    hop::Engine engine;

    // x, y, width, height, color
    hop::GameObject square = engine.create_square(.25f, .25f, .5f, .5f, hop::RED);
    
    // x1, y1, x2, y2, x3, y3, color
    hop::GameObject triangle = engine.create_triangle(
        1.0f, 1.0f, // vertex 1
        1.2f, 1.5f, // vertex 2
        1.5f, 1.5f,  // vertex 3
        hop::GREEN
    );

    // x, y, radius, color
    hop::GameObject circle = engine.create_circle(1.6f, .4, .2f, hop::WHITE);

    // Create plugin
    std::shared_ptr<MovePlugin> plugin = std::make_shared<MovePlugin>();
    plugin->objects.push_back(square);

    // Add the plugin to the engine
    engine.add_plugin(plugin);

    engine.run();

    return 0;
}
