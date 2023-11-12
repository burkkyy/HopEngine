/** @file main.c
 *  @brief Maze demo (recreated after deletion error).
 *
 *  This is a re-creation of our team's maze demo for CSCI 265, after Glen accidentally
 *  deleted the source file prior to presentation.

 *  Several known issues exist within this demo, and our team will resolve them shortly. We have 
 *  not yet integrated some elements of the engine, most notably audio and user input, into the
 *  core game engine. As a result, this demo includes several poor coding practices. Global variables
 *  are used extensively, and the program produces a segmentation fault upon exiting the window. 
 *  These issues will be be resolved when these newer features are integrated into the engine in a 
 *  more permenent manner. 
 * 
 * 
 *  @author Glen Beatty
 *  @date November 11th, 2023.
 */


#include "hop.hpp"
#include <Input/input.hpp>
#include <iostream>
#include <vector>

/* Necessary code to include and use the miniaudio library. Miniaudio is a single-file library, so only the 
 * inclusion of the header file is needed. No amendments to the make file are necessary.
 *
 * The #define MINIAUDIO_IMPLEMENTATION is necessary for the miniaudio library to be used.
*/
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

/* These are the units of measurement. There is a corrosponding integer and float value which represent the same amount
 * of movement on the screen and in the logical representation of where objects are. It is necessary to record the 
 * position of objects in integer to avoid occasional floating-point rounding errors causing unintended behaviour.
*/
#define F_UNIT 0.2
#define I_UNIT 2

/* Simple Character struct which records the position of our circular "character" object.*/
struct Character{
	public:
	int x;
	int y;
	Character(int x, int y){
		this->x = x;
		this->y = y;
	}
};

/* Each wall object represents the position of a rectangle we have created on the screen,
 * each of which functions as a wall in this demo.
*/
struct Wall{

	public:
	int x;
	int y;
	int height;
	int width;

	Wall(int x, int y, int w, int h){
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
	}
};

/* Global variables used for this demo, which is normally not a great programming practice. 
 * Necessary in this case because we had not fully integrated all modules into the core demo
 * at the time of our demonstration.
 * 
*/
std::vector<Wall> walls; // All wall objects are stored in this vector.
Character c(0,0); // Instantiate our circular character. 
std::shared_ptr<hop::Circle> circle; // Pointer to the visual representation of the character.
std::shared_ptr<hop::Square> wall; // Pointer to a wall.
ma_engine audio_engine; // Miniaudio engine object, necessary for audio playback.

// Function declarations for our 4 movement functions, defined below main.
void move_left();
void move_right();
void move_down();
void move_up();


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
		circle = engine.create_circle(0.1f, 0.1f, 0.1f, hop::GREEN);
		
		wall = engine.create_square(0.2f, 0.2f, 1.2f,0.2f, hop::BLUE);
		walls.push_back(Wall(2,2,12,2));
		wall = engine.create_square(1.2f,0.0f,0.2f,0.2f, hop::BLUE);
		walls.push_back(Wall(12,0,2,2));
		wall = engine.create_square(0.2f,0.4f,0.2f,1.4f, hop::BLUE);
		walls.push_back(Wall(2,4,2,14));
		wall = engine.create_square(1.2f,0.6f,0.2f,1.4f, hop::BLUE);
		walls.push_back(Wall(12,6,2,14));
		wall = engine.create_square(0.4f,1.6f,0.6f,0.2f, hop::BLUE);
		walls.push_back(Wall(4,16,6,2));
		wall = engine.create_square(0.6f,1.2f,0.6f,0.2f, hop::BLUE);
		walls.push_back(Wall(6,12,6,2));
		wall = engine.create_square(0.6f,0.4f,0.4f,0.6f, hop::BLUE);
		walls.push_back(Wall(6,4,4,6));
		wall = engine.create_square(1.6f,0.0f,0.4f,1.8f, hop::BLUE);
		walls.push_back(Wall(16,0,4,18));

		wall = engine.create_square(1.85f,1.85f,0.1f,0.1f, hop::Color{1.0f, 0.5f, 0.0f});

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
		(void)delta_time;
 
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
    void close(){ 
	}

};

int main(int argc, const char** argv){
    // Avoids -Wunused-parameter warning. No command-line arguments are currently used.
    (void)argc;
    (void)argv;

    // Initialize the game engine
    hop::Engine engine;

	// Initialize keyboard object, which allows for user input.
	hop::Keyboard keyboard(engine.get_window());

	/* Keyboard.bind associates a keyboard key (in this case the 4 arrow keys) with a function that has been
	 * previously declared. Whenever that key is pressed or held, a function provided as the second argument
	 * in keyboard.bind will be called. This function must be of type void and have no parameters. 
	 * This is how the character moves around the maze. This implementation utilizes function pointers and 
	 * GLFW's native callback-style input.
	 */
	keyboard.bind("left",move_left);
	keyboard.bind("right",move_right);
	keyboard.bind("up",move_up);
	keyboard.bind("down",move_down);
	
	ma_engine_init(NULL, &audio_engine); // Initialize our global ma_engine object so we can play sound.
	ma_engine_play_sound(&audio_engine, "sounds/background_music.mp3", NULL); // Play the sound file in sounds/background_music.mp3.

    // Add our Move plugin to the engine's list of plugins
    engine.plugin<Move>();

    // Start the engine loop
    engine.run();

    ma_engine_uninit(&audio_engine); // Un-initialize miniaudio engine object.
    return 0;
}

/* move_left is called whenever the user presses or holds the left arrow button on their keyboard.
 * The character will move left and their logical position will be updated if moving left is possible.
 * Moving left is impossible if the character is on a far-left tile of the screen, if a wall is to the
 * left of the character, or if the maze has been solved. 
*/
void move_left(){
	bool mv_valid = true; // Tells us whether the character can move left.

	// If the character's x-position is 0, it is at the far-left of the screen and can't move.
	if(c.x<=0){
		// mv_valid flag is set to false, letting us know the character can't move left.
		mv_valid = false;
	}

	// If the character is at (18,18), the maze has been solved and no movement is allowed.
	if((c.x == 18)&&(c.y == 18)){
		// mv_valid flag is set to false, letting us know the character can't move left.
		mv_valid = false;
	}
	// Iterate over all walls to check for collisions. 
	for(Wall w: walls){

		/* Outer condition checks to see if the wall occupies the same x-coordinate as the character.
		*  If not, the character is definitely not blocked by the wall.
		*/
		if((c.y>=w.y)&&(c.y<=(w.y+w.height-I_UNIT))){
			/* Inner conditional checks to see if the character is directly to the right of the wall. If it is,
			 * the character has a wall to the left and may not move. Otherwise it can move. 
			 *
			*/
			if(c.x==(w.x+w.width)){
				
				// mv_valid flag is set to false, letting us know the character can't move left.
				mv_valid = false;
			}

		}
	}

	/* If all 3 movement checks are passed, the mv_valid flag remains true and the character can move left. 
	 * This means a.) the character is not at the left edge of the screen, b.) the character does not have
	 * a wall to its left, and c.) the maze has not yet been solved. 
	 *
	 * Move the character image and update the logical representation if it's position.
	*/
	if(mv_valid==true){

		// Character moves left by F_UNIT (defined at the top of this file). The negative x axis corrosponds with left.
		circle->move(-F_UNIT,0.0f);
		// Update the character object so we know where it is for the next movement request.
		c.x = c.x - I_UNIT;
	}
}

/* Please refer to the comments for move_left() above, since move_right is an equivelant function only the character
 * moves right, in the positive x direction. The only additional code involves a completion check, which I will comment in 
 * this function.
*/
void move_right(){
	bool mv_valid = true;
	if(c.x>=18){
		mv_valid = false;
	}
	for(Wall w: walls){
		if((c.y>=w.y)&&(c.y<=(w.y+w.height-I_UNIT))){
			if((c.x+I_UNIT)==(w.x)){
			mv_valid = false;
			}

		}
	}

	if(mv_valid==true){
		circle->move(F_UNIT,0.0f);
		c.x = c.x + I_UNIT;
	}

	/* See if the character moved right into the completion tile (18,18). If so, stop the 
	 * background music and play the completion sound.
	*/
	if((c.x==18)&&(c.y==18)){
		std::cout << "Congratulations!! You **WON** the maze." << std::endl;
		// Unititialize miniaudio engine to stop music playback. Temporary solution until audio is further developed.
		ma_engine_uninit(&audio_engine);
		// Re-initialize miniiaudio engine so we can play completion sound.
		ma_engine_init(NULL, &audio_engine);
		// Play sounds/bang.mp3
		ma_engine_play_sound(&audio_engine, "sounds/bang.mp3", NULL);
	}
}

/* Please refer to the comments for move_left() above, since move_up is an equivelant function only the character
 * moves up, in the negative y direction. 
*/
void move_up(){
	bool mv_valid = true;
	if(c.y<=0){
		mv_valid = false;
	}
		
	for(Wall w: walls){
		if((c.x>=w.x)&&(c.x<=(w.x+w.width-I_UNIT))){
			if(c.y==(w.y+w.height)){
				mv_valid = false;
			}

		}
	}

	if(mv_valid==true){
		circle->move(0.0f,-F_UNIT);
		c.y = c.y - I_UNIT;
	}
}

/* Please refer to the comments for move_left() above, since move_down is an equivelant function only the character
 * moves down, in the positive y direction. 
*/
void move_down(){
	bool mv_valid = true;
	if(c.y>=18){
		mv_valid = false;
	}

	for(Wall w: walls){
		if((c.x>=w.x)&&(c.x<=(w.x+w.width-I_UNIT))){
			if((c.y+I_UNIT)==(w.y)){
				mv_valid = false;
			}

		}
	}

	if(mv_valid==true){
		circle->move(0.0f,F_UNIT);
		c.y = c.y + I_UNIT;
	}
}
