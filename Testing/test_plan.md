## Test Plan: Hop Engine

#### Bunny Game Co

### Overview

The general stucture of how a user will implement a game using the Hop Engine is as follows:
1. Include the Hop Engine library in the user's program:
	> ```cpp
	> #include "hop.hpp"
	> ```
2. Include any Plug-ins that the game will rely on:  
	> To create a plugin:
 	> 1. Class must inherit from hop::EnginePlugin
 	> 2. Class must have default consturtor defined as:  
    >		```cpp
    >		Plugin(hop::Engine& engine) : EnginePlugin(engine) { }
    >		```
    > 3. Class must define the following functions:
    >     void init();
    >     void update(float);
    >     void close();

3. In the main function:
	> - Initialize the Hop Engine:
	> 	```cpp
	>	hop::Engine engine;
	>	```
	> 
	> - Add the plug-in:
	>	```cpp
	>	engine.plugin<"plug-in name">();
	>	```
	> 
	> - Create any objects (shapes) needed for the game:
	>	```cpp
	>	// Creating a square
	>	std::shared_ptr<hop::Square> square = engine.create_square(
	>		0.25f,       // x
	>		0.25f,       // y
	>		0.5f,        // width
	>		0.5f,        // height
	>		hop::RED    // color
	>	);
	>	```
	>	```cpp
	>	// Creating a triangle
	>	std::shared_ptr<hop::GameObject> triangle = engine.create_triangle(
	>		{{1.0f, 1.0f}}, // vertex 1
	>		{{1.2f, 1.5f}}, // vertex 2
	>		{{1.5f, 1.5f}}, // vertex 3
	>		hop::GREEN      // color
	>	);
	>	```
	>	```cpp
	>	// Creating a circle
	>	std::shared_ptr<hop::Circle> circle = engine.create_circle(
	>		1.6f,       // x
	>		0.4,        // y
	>		0.2f,       // radius
	>		hop::WHITE  // color
	>	);
	>	```
	>
	> - Start the engine loop:
	>	```cpp
	>		engine.run();
	>	```

The nature of the Hop Engine creates unique challenges in testing. Because a large part of the game engine's possible errors are handled by the compiler, and a large part of what would consitute an error is the responsiblity of the user-programmer to avoid, the tests are limited to ensuring that the functionality a user is able to implement operates as expected. For this reason the test methedology of the Hop Engine will consitute an explanation of the possible actions a user programmer can take and the expected output of those actions. 



### Detailed Description of the Test Infrastructure  
In order to test the operation of the Hop Engine the test script must begin with the creation of a test file. This will be a C++ file in which the user will include the Hop Engine library. To demonstrate the structure of this file, an example is provided below.

```cpp
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

    // Creating a square
    std::shared_ptr<hop::Square> square = engine.create_square(
        0.25f,      // x
        0.25f,      // y
        0.5f,       // width
        0.5f,       // height
        hop::RED 	// color
    );

    // Creating a triangle
    std::shared_ptr<hop::GameObject> triangle = engine.create_triangle(
        {{1.0f, 1.0f}}, // vertex 1
        {{1.2f, 1.5f}}, // vertex 2
        {{1.5f, 1.5f}}, // vertex 3
        hop::GREEN      // color
    );

    // Creating a circle
    std::shared_ptr<hop::Circle> circle = engine.create_circle(
        1.6f,       // x
        0.4,        // y
        0.2f,       // radius
        hop::WHITE  // color
    );

    // Start the engine loop
    engine.run();
    return 0;
}
```

The tester should begin by commenting out the aspects of the above code refering to the move plug-in. The tester should then use the rest of this template and try creating each of the game objects (square, triangle, circle) with sizes at the lower limit ($0.1$), sizes in the middle of their range ($1.0$), shares at the upper edge of acceptable values ($2.0$), and finally values outside the range of acceptable values ($-1.0$, $2.1$). 
The tester will then test each shape's color as each of the available options (RED, GREEN, BLUE, BLACK, WHITE). 

Once the functions relating to game objects are tested, the tester should comment out that code, then uncomment the aspects refering to the move plug-in and ensure that the plug-in performs without any errors for a square of each of the applicable sizes detailed above ($0.1$, $1.0$) and check that the program does not work for the remaining values above ($-1.0$, $2.1$). Next the square's color can be tested for each of the available options (RED, GREEN, BLUE, BLACK, WHITE). Finally, the tester should experiment with velocity values of $0.1$, $1.0$ and $2.1$.

### Table of all test cases

| Test Case     | Description 										| Code __(*)__ 					| Test Options |
| ----------- 	| ----------- 										| -----------  					| ----------- |
| Square     	| Implement a square using the Hop Engine   		| `engine.create_square()` 		| Size: $1.0$ $2.0$ $-1.0$ $2.1$ / Color: RED, GREEN, BLUE, BLACK, WHITE  |
| Triangle  	| Implement a triangle using the Hop Engine   		| `engine.create_triangle()`   	| Size: $1.0$ $2.0$ $-1.0$ $2.1$ / Color: RED, GREEN, BLUE, BLACK, WHITE        |
| Circle  		| Implement a circle using the Hop Engine   		| `engine.create_circle()`   	| Size: $1.0$ $2.0$ $-1.0$ $2.1$ / Color: RED, GREEN, BLUE, BLACK, WHITE        |
| Move Plug-in  | Implement simple plug-in using the Hop Engine   	| `class Move`   				| Square Size: $1.0$ $2.0$ $-1.0$ $2.1$ / Velocity: $0.1$, $1.0$ $2.1$ |

__(*) See the code [above](#detailed-description-of-the-test-infrastructure), actual code will not fit in the table__

