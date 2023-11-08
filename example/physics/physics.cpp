#include "hop.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <vector>
#include <memory>

struct RigidBody {
  hop::GameObject game_object;
  glm::vec2 velocity;
  float mass = 3.0f;
};

class GravityPhysicsSystem : public hop::EnginePlugin {
 public:
  GravityPhysicsSystem(float strength) : strengthGravity{strength} {}

  const float strengthGravity;
 
  void init(){

  }

  void update(float delta_time){
    const float step_delta = delta_time / 5;
    for (int i = 0; i < 5; i++) {
      stepSimulation(step_delta);
    }
  }

  void close(){

  }
 
  glm::vec2 computeForce(RigidBody& fromObj, RigidBody& toObj) const {    
    auto offset = fromObj.game_object->transform.translation - toObj.game_object->transform.translation;
    float distanceSquared = glm::dot(offset, offset);
    
    // clown town - just going to return 0 if objects are too close together...
    if (glm::abs(distanceSquared) < 1e-10f) {
      return {.0f, .0f};
    }
    
    float force = strengthGravity * toObj.mass * fromObj.mass / distanceSquared;
    return force * offset / glm::sqrt(distanceSquared);
  }

  std::vector<RigidBody> game_objects;
 
 private:
  void stepSimulation(float dt) {
    // Loops through all pairs of objects and applies attractive force between them
    for (auto iterA = game_objects.begin(); iterA != game_objects.end(); ++iterA) {
      auto& objA = *iterA;
      for (auto iterB = iterA; iterB != game_objects.end(); ++iterB) {
        if (iterA == iterB) continue;
        auto& objB = *iterB;
 
        auto force = computeForce(objA, objB);
        objA.velocity += dt * -force / objA.mass;
        objB.velocity += dt * force / objB.mass;
      }
    }
 
    // update each objects position based on its final velocity
    for (auto& obj : game_objects) {
      obj.game_object->transform.translation += dt * obj.velocity;
    }
  }
};

int main(){
  hop::Engine engine;
  std::shared_ptr<GravityPhysicsSystem> system = std::make_shared<GravityPhysicsSystem>(.081f);
  
  hop::GameObject circle_object_1 = engine.create_circle(-0.97000436f + 1.0f, 1.24308753f, .02f, {1,1,1});
  RigidBody circle_1 = {circle_object_1, {0.4662036850f, 0.4323657300f}};
  system->game_objects.push_back(circle_1);
  
  hop::GameObject circle_object_2 = engine.create_circle(1.97000436f, -0.24308753f + 1.0f, .02f, {0,0,1});
  RigidBody circle_2 = {circle_object_2, {0.4662036850f, 0.4323657300f}};
  system->game_objects.push_back(circle_2);

  hop::GameObject circle_object_3 = engine.create_circle(1.0f, 1.0f, .02f, {1,0,0});
  RigidBody circle_3 = {circle_object_3, {-0.93240737f, -0.86473146f}};
  system->game_objects.push_back(circle_3);

  engine.add_plugin(system);
  
  engine.run();
  return 0;
}
