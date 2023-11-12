#pragma once

#include "object_model.hpp"

#define GLM_FORCE_RADIANS
#define GLF_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>

namespace hop {

struct Transform {
    glm::vec2 translation = {};
    glm::vec2 scale = { 1.0f, 1.0f };

    glm::mat2 mat2(){
        return {
            { scale.x, 0.0f },
            { 0.0f, scale.y }
        };
    }
};

class Object {
public:
    Object(const Object&) = delete;
    Object& operator=(Object&) = delete;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;
    
    Object(){}

    std::shared_ptr<ObjectModel> model = {};
    glm::vec3 color = {};
    Transform transform = {};
};

}
