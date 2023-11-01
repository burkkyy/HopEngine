#pragma once

#include "Objects/object_model.hpp"

#define GLM_FORCE_RADIANS
#define GLF_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>

namespace hop {

struct RigidBody2dComponent {
    glm::vec2 velocity;
    float mass{1.0f};
};

struct Transform {
  glm::vec2 translation{};
  glm::vec2 scale{1.f, 1.f};
  float rotation;

  glm::mat2 mat2() {
    const float s = glm::sin(rotation);
    const float c = glm::cos(rotation);
    glm::mat2 rot_matrix{{c, s}, {-s, c}};

    glm::mat2 scale_mat{{scale.x, .0f}, {.0f, scale.y}};
    return rot_matrix * scale_mat;
  }
};

class GameObject {
public:
    using id_t = unsigned int;

    static GameObject create_object(){
        static id_t current_id = 0;
        return GameObject{ current_id++ };
    }

    GameObject(const GameObject&) = delete;
    GameObject& operator=(GameObject&) = delete;
    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    id_t get_id(){ return id; }

    std::shared_ptr<ObjectModel> model{};
    glm::vec3 color{};
    Transform transform = {};
    RigidBody2dComponent rigidBody2d = {};

private:
    GameObject(id_t obj_id) : id(obj_id){}

    id_t id;
};

}
