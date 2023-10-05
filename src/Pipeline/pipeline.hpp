#pragma once

#include "Device/device.hpp"

#include <string>

namespace bun {

class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;
};

}
