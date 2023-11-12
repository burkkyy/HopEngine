#include "hop.hpp"

#include <vector>

int main(int argc, const char** argv){
	(void)argc;
	(void)argv;

	hop::Engine engine;

	std::shared_ptr<hop::Square> face = engine.create_square(
		0.0f,
		1.0f,
		2.0f,
		2.0f,
		hop::WHITE
	);
	std::shared_ptr<hop::Square> left_ear = engine.create_square(
		0.0f,
		2.0f,
		0.75f,
		1.0f,
		hop::WHITE
	);
	std::shared_ptr<hop::Square> right_ear = engine.create_square(
		1.25f,
		2.0f,
		0.75f,
		1.0f,
		hop::WHITE
	);
	std::shared_ptr<hop::Circle> left_eye = engine.create_circle(
		0.25f,
		1.25f,
		0.25f,
		hop::RED
	);
	std::shared_ptr<hop::Circle> right_eye = engine.create_circle(
		0.75f,
		1.25f,
		0.25f,
		hop::RED
	);
	engine.run();
    	return 0;
}
