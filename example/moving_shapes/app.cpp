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
        ```cpp
            Plugin(hop::Engine& engine) : EnginePlugin(engine) { }
        ```
    3. Class must define the following functions:
        void init();
        void update(float);
        void close();
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
        square = engine.create_square(0.0f, 0.0f, 0.2f, 0.2f, hop::RED);
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

    // Start the engine loop
    engine.run();
    
    return 0;
}
