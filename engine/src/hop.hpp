#pragma once

#include "Engine/engine.hpp"
#include "Objects/object_model.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace hop {

#define RED Color{1.0f, 0.0f, 0.0f}
#define GREEN Color{0.0f, 1.0f, 0.0f}
#define BLUE Color{0.0f, 0.0f, 1.0f}
#define BLACK Color{0.0f, 0.0f, 0.0f}
#define WHITE Color{1.0f, 1.0f, 1.0f}

}