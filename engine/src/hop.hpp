/**
 * @file hop.cpp
 * @author Caleb Burke
 * @date Nov 5, 2023
 *
 * Main header file users of library will use.
 * Other helper functions and constants defined here.
 *
 */

#pragma once

#include "Engine/engine.hpp"
//#include "Objects/object_model.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace hop {

// Colors objects can be set to
#define RED Color{1.0f, 0.0f, 0.0f}
#define GREEN Color{0.0f, 1.0f, 0.0f}
#define BLUE Color{0.0f, 0.0f, 1.0f}
#define BLACK Color{0.0f, 0.0f, 0.0f}
#define WHITE Color{1.0f, 1.0f, 1.0f}

}
