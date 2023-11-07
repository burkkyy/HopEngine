#include "hop.hpp"

#include <vector>

class RotateSystem(){
    void update(){
        
    }
};

int main(int argc, const char** argv){ 
    // Initialize the game engine
    hop::Engine engine;

    // Create any objects defined in hop.hpp
    hop::Quad square = hop::create_square(.25f, .25f, .5f, .5f);
    
    hop::Triangle triangle = hop::create_triangle(
        1.0f, 1.0f, // vertex 1
        1.2f, 1.5f, // vertex 2
        1.5f, 1.5f  // vertex 3
    );

    hop::Circle circle = hop::create_circle(1.6f, .4, .2f);

    // Add created objects to the engine with their color
    engine.add_object(square, {1, 0, 0});
    engine.add_object(triangle, {0, 1, 0});
    engine.add_object(circle, {1, 1, 1});

    engine.run();

    return 0;
}
