#pragma once

#include "Object_Model/object_model.hpp"

#define GLM_FORCE_RADIANS
#define GLF_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace hop {

struct Transform {
    glm::vec2 translation = {};
    glm::mat2 mat2(){ return glm::mat2{ 1.0 f }; }
}

class Object {
public:
    using id_t = unsigned int;

    static Object create_object(){
        static id_t current_id = 0;
        return Object{ current_id++ };
    }

    Object(const Object&) = delete;
    Object& operator=(Object&) = delete;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;

    id_t get_id(){ return id; }

    std::shared_ptr<Object_Model> model{};
    glm::vec3 color{};
    Transform transform{};

private:
    Object(id_t obj_id) : id(obj_id){}

    id_t id;
};

}
