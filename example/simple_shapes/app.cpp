#include "hop.hpp"

int main(int argc, const char** argv){
    // Avoids -Wunused-parameter warning
    (void)argc;
    (void)argv;

    // Initialize the game engine
    hop::Engine engine;

    // Creating a square
    std::shared_ptr<hop::Square> square = engine.create_square(
        0.25f,       // x
        0.25f,       // y
        0.5f,        // width
        0.5f,        // height
        hop::RED    // color
    );

    // Creating a triangle
    std::shared_ptr<hop::GameObject> triangle = engine.create_triangle(
        {{1.0f, 1.0f}}, // vertex 1
        {{1.2f, 1.5f}}, // vertex 2
        {{1.5f, 1.5f}}, // vertex 3
        hop::GREEN      // color
    );

    // Creating a circle
    std::shared_ptr<hop::Circle> circle = engine.create_circle(
        1.6f,       // x
        0.4,        // y
        0.2f,       // radius
        hop::WHITE  // color
    );

    // Start the engine loop
    engine.run();

    return 0;
}
