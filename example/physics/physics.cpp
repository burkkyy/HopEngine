#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>
#include <memory>

namespace hop {

class GravityPhysicsSystem {
 public:
  GravityPhysicsSystem(float strength) : strengthGravity{strength} {}
 
  const float strengthGravity;
 
  // dt stands for delta time, and specifies the amount of time to advance the simulation
  // substeps is how many intervals to divide the forward time step in. More substeps result in a
  // more stable simulation, but takes longer to compute
  void update(std::vector<GameObject>& objs, float dt, unsigned int substeps = 1) {
    const float stepDelta = dt / substeps;
    for (int i = 0; i < substeps; i++) {
      stepSimulation(objs, stepDelta);
    }
  }
 
  glm::vec2 computeForce(GameObject& fromObj, GameObject& toObj) const {
    auto offset = fromObj.transform.translation - toObj.transform.translation;
    float distanceSquared = glm::dot(offset, offset);
 
    // clown town - just going to return 0 if objects are too close together...
    if (glm::abs(distanceSquared) < 1e-10f) {
      return {.0f, .0f};
    }
 
    float force =
        strengthGravity * toObj.rigidBody2d.mass * fromObj.rigidBody2d.mass / distanceSquared;
    return force * offset / glm::sqrt(distanceSquared);
  }
 
 private:
  void stepSimulation(std::vector<GameObject>& physicsObjs, float dt) {
    // Loops through all pairs of objects and applies attractive force between them
    for (auto iterA = physicsObjs.begin(); iterA != physicsObjs.end(); ++iterA) {
      auto& objA = *iterA;
      for (auto iterB = iterA; iterB != physicsObjs.end(); ++iterB) {
        if (iterA == iterB) continue;
        auto& objB = *iterB;
 
        auto force = computeForce(objA, objB);
        objA.rigidBody2d.velocity += dt * -force / objA.rigidBody2d.mass;
        objB.rigidBody2d.velocity += dt * force / objB.rigidBody2d.mass;
      }
    }
 
    // update each objects position based on its final velocity
    for (auto& obj : physicsObjs) {
      obj.transform.translation += dt * obj.rigidBody2d.velocity;
    }
  }
};

std::unique_ptr<ObjectModel> createSquareModel(Device& device, glm::vec2 offset) {
  std::vector<ObjectModel::Vertex> vertices = {
      {{-0.5f, -0.5f}},
      {{0.5f, 0.5f}},
      {{-0.5f, 0.5f}},
      {{-0.5f, -0.5f}},
      {{0.5f, -0.5f}},
      {{0.5f, 0.5f}},  //
  };
  for (auto& v : vertices) {
    v.position += offset;
  }
  return std::make_unique<ObjectModel>(device, vertices);
}

std::unique_ptr<ObjectModel> createCircleModel(Device& device, unsigned int numSides) {
  std::vector<ObjectModel::Vertex> uniqueVertices{};
  for (int i = 0; i < numSides; i++) {
    float angle = i * glm::two_pi<float>() / numSides;
    uniqueVertices.push_back({{glm::cos(angle), glm::sin(angle)}});
  }
  uniqueVertices.push_back({});  // adds center vertex at 0, 0
 
  std::vector<ObjectModel::Vertex> vertices{};
  for (int i = 0; i < numSides; i++) {
    vertices.push_back(uniqueVertices[i]);
    vertices.push_back(uniqueVertices[(i + 1) % numSides]);
    vertices.push_back(uniqueVertices[numSides]);
  }
  return std::make_unique<ObjectModel>(device, vertices);
}

}

int main(){

}
