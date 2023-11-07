#pragma once

#include "Engine/engine.hpp"

#include <vector>

namespace hop {

using Vertex = ObjectModel::Vertex;
using Triangle = std::vector<Vertex>;
using Quad = std::vector<Vertex>;
using Circle = std::vector<Vertex>;

Triangle create_triangle(
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3
){
    std::vector<Vertex> vertices = {
        {{x1, y1}},
        {{x2, y2}},
        {{x3, y3}},
    };

    return vertices;
}

Quad create_square(float x, float y, float width, float height){
    std::vector<Vertex> vertices = {
        {{x, y}},
        {{x + width, y}},
        {{x + width, y + height}},
        {{x, y}},
        {{x, y + height}},
        {{x + width, y + height}}
    };

    return vertices;
}

Circle create_circle(float x, float y, float radius){
    int sides = std::max(static_cast<int>(radius * 100.0f), 8);
    std::vector<Vertex> side_vertices = {};

    for(int i = 0; i < sides; i++){
        float theta = glm::two_pi<float>() * i / sides;
        float x1 = x + radius * glm::cos(theta);
        float y1 = y + radius * glm::sin(theta);
        side_vertices.push_back({{x1, y1}});
    }

    side_vertices.push_back({{x, y}});

    std::vector<Vertex> vertices{};
    for(int i = 0; i < sides; i++){
        vertices.push_back(side_vertices[i]);
        vertices.push_back(side_vertices[(i + 1) % sides]);
        vertices.push_back(side_vertices[sides]);
    }

    return vertices;
}

}
