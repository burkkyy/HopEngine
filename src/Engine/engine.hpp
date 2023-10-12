/* @author Caleb Burke
 * @date 2023-10-5
 * NOTE: Finish writing doc
 * Main api for graphics engine
*/
#pragma once

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Swapchain/swapchain.hpp"
#include "Pipeline/pipeline.hpp"

namespace hop {

class Engine {
public:
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const char* NAME = "hop engine";

    Engine();
    ~Engine();

    void run();

private:
    Window win{WIDTH, HEIGHT};
    Device device{win};
    SwapChain* swapchain;
};

}
