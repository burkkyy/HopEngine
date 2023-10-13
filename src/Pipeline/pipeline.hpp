#pragma once

#include "Device/device.hpp"

#include <string>

namespace hop {

class Pipeline {
public:
    Pipeline(Device& d, const std::string&, const std::string&);
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    static void default_config();

private:
    static std::vector<char> load(const std::string&);
    void create(const std::string&, const std::string&);
    void create_shader_mod(const std::vector<char>&, VkShaderModule*);

    Device& device;
    VkPipeline pipeline;
    VkShaderModule vert;
    VkShaderModule frag;
};

}
