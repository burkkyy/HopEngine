/**
 * @brief game engine tests
 * @author Jake
 * @date Dec 2, 2023
 */

#include <iostream>

#include <functional>

#include "Window/window.hpp"
#include "Device/device.hpp"
#include "Swapchain/swapchain.hpp"
#include "Pipeline/pipeline.hpp"
#include "Renderer/renderer.hpp"
#include "Engine/engine.hpp"

static int TESTS = 0;
static int TESTS_PASSED = 0;

#define TEST_START(...)	TESTS++; std::cout << __VA_ARGS__ << "..... "
#define TEST_OK()	TESTS_PASSED++; std::cout << "\033[1;32m[OK]\033[0m" << '\n'
#define TEST_FAIL()	std::cout << "\033[1;31m[FAIL]\033[0m" << '\n'
#define MSG(...)	std::cout << "\033[1;34m[TEST]\033[0m " << __VA_ARGS__ << '\n'
#define TEST_ASSERT(b)	if(!(b)){ TEST_FAIL(); throw 1; }

void RUN_TEST(const char* msg, std::function<void()> func){
	TEST_START(msg);
	try {
		func();
		TEST_OK();
	} catch(std::exception& e){
		TEST_FAIL();
		std::cout << e.what() << std::endl;
	}
}

int main(int argc, const char** argv){
    (void)argc;
    (void)argv;
	using namespace hop;

	MSG("Starting testing.");
	
	RUN_TEST("Testing window", [](){
		auto* window = new Window(100, 100);
		VkExtent2D extent = window->get_extent();
		TEST_ASSERT(extent.width == 100 && extent.height == 100);
		for(size_t i = 0; i < 100; i++){ glfwPollEvents(); }
		delete window;
	});
	
	RUN_TEST("Testing device", [](){
		Window window(100, 100);
		Device device(window);
	});
	
	RUN_TEST("Testing swapchain", [](){
		Window window(100, 100);
		Device device(window);
		SwapChain swapchain(device, {100, 100});
	});

	RUN_TEST("Testing pipeline", [](){
		Window window(100, 100);
		Device device(window);
		PipelineConfigInfo config_info = {};
		Pipeline::default_config(config_info);
	});

	RUN_TEST("Testing Render", [](){
		Window window(100, 100);
		Device device(window);
		Renderer renderer(window, device);
	});

	RUN_TEST("Testing Engine", [](){
		Engine engine;
	});
	
	MSG("Finished tesing.");
    return 0;
}

