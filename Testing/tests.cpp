#include "hop.hpp"

#include <iostream>

/* @brief plugin that moves objects around
 * 
 * This Move class is an example of the simplest plugin that moves a
 * square to the right until it hits the end of the screen
 *
 * To create a plugin:
 *  1. Class must inherit from hop::EnginePlugin
 *  2. Class must have default consturtor defined as:
 *     		Plugin(hop::Engine& engine) : EnginePlugin(engine) { }
 *  3. Class must define the following functions:
 *      void init();
 *	    void update(float);
 *	    void close();
 *
 * NOTE: Every plugin has a reference to the engine, this is so plugins can
 *       create their own objects and call other engine functions
 */
class Move : public hop::EnginePlugin {
public: // dont forget to make constructor functions public!
    Move(hop::Engine& engine) : EnginePlugin(engine) { }

    /* @brief starts plugin
     *
     * This function is called when right before the main game loop starts.
     * aka before engine.run() is called. Notice the
     *
     * @return void
     */
    void init(){
        /*
            This code will exec before the game loop starts, so lets create our
            objects here.

            To keep things simple lets just create a red square.
            
            Note that 'square' was already defined inside of this class. This is
            so other functions like update() can use square.
        */
        square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::RED);
		
		// These are the other cases, they should be checked the uncommented one at a time

		// square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::GREEN);
		// square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::BLUE);
		// square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::BLACK);
		// square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::WHITE);

		// square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::RED);
		// square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::GREEN);
		// square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::BLUE);
		// square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::BLACK);
		// square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::WHITE);

		// square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::RED);
		// square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::GREEN);
		// square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::BLUE);
		// square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::BLACK);
		// square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::WHITE);

		// square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::RED);
		// square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::GREEN);
		// square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::BLUE);
		// square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::BLACK);
		// square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::WHITE);
    }

    /* @brief updates plugin
     *
     * This function is called within the main game engine loop. Every draw
     * call this function is called, along with the functions of all other
     * plugins added to the engine.
     *
     * @param delta_time The amount of time passed since last frame drawn
     * @return void
     */
    void update(float delta_time){
        /*
            This code will exec every `game tick`

            That means simply moving an object will move it way too fast,
            we should only move it every relative to how much time has passed 
            since the previous frame.

            For this example lets move the square until its at the bottom right
            corner.

            NOTE: To move the square object, I use `->` to call move(), since
                  square is a pointer
        */
        const float velocity = 0.1f;
		// const float velocity = 1.0f;
		// const float velocity = 2.1f;
		// These are the velocity options, each one should be run for each of the sizes above

        const float speed = velocity * delta_time;

        if(square->position().x + square->width < 2.0f){
            square->move(speed, speed);
        }
    }

    /* @brief closes plugin
     *
     * This function is called right after the game loop ends.
     *
     * NOTE: We don't really have to do anything since the smart pointers
     *       handle the garbage collection for us
     *
     * @return void
     */
    void close(){ }

    std::shared_ptr<hop::Square> square;
};

int main(int argc, const char** argv){
    // Avoids -Wunused-parameter warning
    (void)argc;
    (void)argv;

    // Initialize the game engine
    hop::Engine engine;

    // Add our Move plugin to the engine's list of plugins
    engine.plugin<Move>();

    // Creating a square
    std::shared_ptr<hop::Square> square = engine.create_square(
        0.25f,      // x
        0.25f,      // y
        0.5f,       // width
        0.5f,       // height
        hop::RED 	// color
    );
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::GREEN);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::BLUE);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::BLACK);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 1.0f, 1.0f, hop::WHITE);

	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::RED);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::GREEN);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::BLUE);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::BLACK);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.0f, 2.0f, hop::WHITE);

	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::RED);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::GREEN);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::BLUE);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::BLACK);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, -1.0f, -1.0f, hop::WHITE);

	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::RED);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::GREEN);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::BLUE);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::BLACK);
	// std::shared_ptr<hop::Square> square = engine.create_square(0.0f, 0.0f, 2.1f, 2.1f, hop::WHITE);



    // Creating a triangle
    std::shared_ptr<hop::GameObject> triangle = engine.create_triangle(
        {{1.0f, 1.0f}}, // vertex 1
        {{1.2f, 1.5f}}, // vertex 2
        {{1.5f, 1.5f}}, // vertex 3
        hop::RED      // color
    );

	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{1.0f, 1.0f}}, {{1.2f, 1.5f}}, {{1.5f, 1.5f}}, hop::GREEN);
	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{1.0f, 1.0f}}, {{1.2f, 1.5f}}, {{1.5f, 1.5f}}, hop::BLUE);
	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{1.0f, 1.0f}}, {{1.2f, 1.5f}}, {{1.5f, 1.5f}}, hop::BLACK);
	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{1.0f, 1.0f}}, {{1.2f, 1.5f}}, {{1.5f, 1.5f}}, hop::WHITE);

	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{2.0f, 2.0f}}, {{2.2f, 2.5f}}, {{2.5f, 2.5f}}, hop::RED);
	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{2.0f, 2.0f}}, {{2.2f, 2.5f}}, {{2.5f, 2.5f}}, hop::GREEN);
	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{2.0f, 2.0f}}, {{2.2f, 2.5f}}, {{2.5f, 2.5f}}, hop::BLUE);
	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{2.0f, 2.0f}}, {{2.2f, 2.5f}}, {{2.5f, 2.5f}}, hop::BLACK);
	// std::shared_ptr<hop::GameObject> triangle = engine.create_triangle( {{2.0f, 2.0f}}, {{2.2f, 2.5f}}, {{2.5f, 2.5f}}, hop::WHITE);

    // Creating a circle
    std::shared_ptr<hop::Circle> circle = engine.create_circle(
        1.6f,       // x
        0.4,        // y
        0.2f,       // radius
        hop::WHITE  // color
    );

	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 0.1f, hop::GREEN);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 0.1f, hop::BLUE);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 0.1f, hop::BLACK);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 0.1f, hop::WHITE);

	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 1.0f, hop::RED);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 1.0f, hop::GREEN);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 1.0f, hop::BLUE);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 1.0f, hop::BLACK);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 1.0f, hop::WHITE);

	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, -1.0f, hop::RED);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, -1.0f, hop::GREEN);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, -1.0f, hop::BLUE);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, -1.0f, hop::BLACK);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, -1.0f, hop::WHITE);

	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 2.1f, hop::RED);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 2.1f, hop::GREEN);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 2.1f, hop::BLUE);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 2.1f, hop::BLACK);
	// std::shared_ptr<hop::Circle> circle = engine.create_circle( 1.6f, 0.4, 2.1f, hop::WHITE);


    // Start the engine loop
    engine.run();
    return 0;
}