#pragma once

#include "Device/device.hpp"

#include <string>

namespace hop {

class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;
};

}
