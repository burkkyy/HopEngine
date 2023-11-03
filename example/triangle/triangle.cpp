#include "hop.hpp"

#include <vector>

int main(int argc, const char** argv){

    std::vector<hop::Vertex> square_vertices = {
        {{-0.5f, -0.5f}},
        {{0.5f, 0.5f}},
        {{-0.5f, 0.5f}},
        {{-0.5f, -0.5f}},
        {{0.5f, -0.5f}},
        {{0.5f, 0.5f}},
    };

    hop::Engine engine;
    engine.create_object(square_vertices);
    engine.run();

    return 0;
}
