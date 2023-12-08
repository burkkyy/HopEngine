# Hop Engine - User Manual

#### By Bunny Game Co.
Members: Azita, Caleb, Glen, Indigo, Jake

# Table of Contents

### [Using the Hop Engine](#using-the-hop-engine-1)
- __[Introduction](#introduction)__
- __[Getting Started](#getting-started)__
- __[Game Objects](#game-objects)__
	- __[Creating Game Objects](#creating-game-objects)__
		- [Square](#create_square)
		- [Circle](#create_circle)
		- [Triangle](#create_triangle)
	- __[Game Object Color](#game-object-color)__
- __[Images](#images)__
	- __[Creating Image Instances](#creating-image-instances)__
	- __[Image Color](#image-color)__
	- __[Moving and Transforming Images](#moving-and-transforming-images)__
	- __[Image Helper Functions](#image-helper-functions)__
- __[TextBoxes](#textboxes)__
- __[User Input](#user-input)__
- __[Sound](#sound)__
- __[Running a Game](#running-a-game)__


### [Building the Hop Engine from Source](#building-the-hop-engine-from-source-1)
- Subheading

### [Appendix A: Key Codes](#appendix-a-1)
### [Appendix B: PONG](#appendix-b-1)

---

# Using the Hop Engine

## Introduction

The Hop Engine can be used to implement basic games through C++ files. The instructions in this user manual will outline all the core functionality of the engine, however the project is open source and users are therefore encouraged to use and/or modify the engine as best suits their ideas. 

The layout of this document will follow the structure of the hop.hpp header file. This is the file through which the user is able to control the Hop Engine. 
 
_A note on spelling: In keeping with it's spelling in all major programming languages the Hop Engine spells colour using the American spelling, therefore all references to hue in this document and in the engine as a whole will be spelled color. We know it's annoying and we hate it too, but such is the world we live in._ 
 

## Getting Started

Before the user can begin displaying their brilliant ideas on the screen with the power of the Hop Engine they must first initialize the engine and window. This process is simple but essential and therefore will be detailed below.

 1. The first thing for the user to do is initialize their game. This is acheived with the syntax `hop::Game game("game_name");`. This should be the first line of the main function in the user's game files. 
 
 2. The next thing to do is declare the size of the window in which the game will run. There are three options for this action.
	- `game.set_window_size(width, height);`  
 		 - If the user wants to define the window to be a certain size this is the option to use. The parameters `width` and `height` are integers denoting the size of the window in pixels.  
 		 - The user may find the functions `game.get_resolution_height()` and `game.get_resolution_height()` helpful in order to get the players screen resolution and thus tailor their window size to the players screen. 
	- `void set_fullscreen();`  
 		- This function just calls `set_window_size(get_resolution_width(),get_resolution_height());` so it is an easier way for user's to get a full screen window tailored to their players screens. It also sets a public boolean attribute of the game (`fullscreen`) to true. 
	- `void set_windowed();`  
		- This function resets the public boolean `fullscreen` attribute of the game to false. The user should then set the window dimmension using `game.set_window_size(width, height)`;
 
 3. Finally, the user can being the game with the function call `game.run();`. 
  
Once these steps have been complete the user can begin creating game objects, images, and any other assets they desire for the game. The details of creating objects, handling user input, sound, and more are all detailed below.


## Game Objects

#### Creating Game Objects

```cpp
    Rectangle create_rectangle(int x, int y, int width, int height, Color color);
    Circle create_circle(int x, int y, int radius, Color color);
    Triangle create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color);
```
 
 There are three foundational objects that the user can render to the screen. Each shape rendered can be controlled individually in the window.
 Each of the following functions will create a user-customized shape that will be rendered to the screen. 
 
 ##### `create_square()`
 
 Parameters:
 - x (int) - The x-coordinate of the square's bottom left vertex.
 - y (int) - The y-coordinate of the square's bottom left vertex.
 - width (int) - The width of the square in pixels.
 - height (int) - The height of the square in pixels.
 - color (Color) - The color of the square _(See [Object Color](#object-color))_
 
 ##### `create_circle()`
 
 Parametes:
 - x (int) - The x-coordinate of the circle's centre.
 - y (int) - The y-coordinate of the circle's centre.
 - radius (int) - The radius of the circle.
 - color (Color) - The color of the circle. _(See [Object Color](#object-color))_
 
 ##### `create_triangle()`
 
 Parameters:
 - x (int) - The x-coordinate of the circle's centre.
 - y (int) - The y-coordinate of the circle's centre.
 - radius (int) - The radius of the circle.
 - color (Color) - The color of the circle. _(See [Object Color](#object-color))_
 
#### Game Object Color

```cpp
RED Color{1.0f, 0.0f, 0.0f}
GREEN Color{0.0f, 1.0f, 0.0f}
BLUE Color{0.0f, 0.0f, 1.0f}
BLACK Color{0.0f, 0.0f, 0.0f}
WHITE Color{1.0f, 1.0f, 1.0f}
```
 There are two main options for setting the color of objects. 
 
 1. The first choice is to use one of the predefined colors built into the Hop Engine. The syntax for the built-in color choices is `hop::COLOR`. Note that built in colors are defined in all caps. See the _[examples](#examples)_. 
 2. The second option is for users to define custom colors. To define a custom color the user will use the syntax `hop::Color custom_name={{0.0}, {0.0}, {0.0}};` The numerical values are RGB values of the color represented as percentages of $255$. In order to define a color the user should use an online RGB color selector (This google page works well: https://g.co/kgs/vVFMXQ). Once the user has the values of their color they should divide each value by $255$ to arrive at a result between $0.0$ and $1.0$. These result values are what can be used in the hop engine. See the _[examples](#examples)_ for more clarity.

## Images

```cpp
class Image{

    public:

    Image(int x, int y,int width, int height);
    void set_color_all(Color color);
    void move(int x, int y);  
    void flip();
    int get_x();
    int get_y();
    int get_height();
    int get_width();
    std::vector<GameObject> game_objects;
};
```
While user's can create instances of game objects directly in the game as described above, it is very useful to be able to group together sets of invidual objects to form more complex graphics. This is the puspose of the image class. By grouping game objects into an image the user can control the movement of the entire image as one, adjust the color of all objects in the image simultaniously, and manipulate the image's game elements as though they were a single entity. 

#### Creating Image Instances
 
 To define an image the user will use the syntax `hop::Image image_name(x, y, width, height)` with `x` and `y` being the position of the lower left corner of the image and the `width` and `height` being large enough to contain all the game objects to be defined within the image. See the _[examples](#examples)_ to see an implementation of an image.
 

#### Image Color

 Images allow users to set the color of all game objects within with a single command. Using the syntax `image_name.set_color_all(color)` will set the color. The color options for images are inherited from game objects, therefore for more information on color see _[Object Color](#object-color)_.
 

#### Moving and Transforming Images
 
 To move an object from one place to another, the user should call the move function on an image object.
 
 To use the move function on an image, simply use `image_name.move(x, y)` or `image_name->move(x, y)` depending on the user's implementation. 
 
 - x (int) is the positive or negative distance the object will move on the x axis.
 - y (int) is the positive or negative distance the object will move on the y axis. 
 
 The move function will change the position of the image instantaniously, so the user should not expect any intermidiate animation. It will seem as though this function has essentially “teleported” the object the specified distance, so to achieve the appearance of smooth movement the move function should be called in small increments. 
 
 Images can also be flipped on their center vertical axis using the syntax `image_name.flip()` or `image_name->flip()` depending on the user's implementation.

#### Image Helper Functions
 
 There are four helper functions that the user may find useful in their implementation. Each returns an applicable integer value. They are as follows.
 
 `get_x()` Will return the horizontal position of the lower left corner of the image as an integer. 
 `get_y()` Will return the vertical position of the lower left corner of the image as an integer.
 `get_height()` Will return the height of the image as an integer.
 `get_width()` Will return the width of the image as an integer.

## TextBoxes
 
 There is a class in the Hop Engine called TextBox which allows the user to enter a string and have it rendered on the screen as an image. The TextBox class shares many characteristics with the image class, however the sole function of the TextBox class is the ability to create an instance of it. To create and render a text on the screen using the TextBox class the user should use the syntax `hop::TextBox textbox_name(x, y, text_size, text_color, text_string);` with `x` and `y` being integers denoting the position of the lower left corner of the textbox, `text_size` being an integer representing the size of the text, `text_color` being the color of the text (for more information on how color works in the Hop Engine see _[Object Color](#object-color)_), and finally `text_string` being a const char* of the text the user would like displayed.
 

## User Input

 In order for a game to accept input the user must call the `monitor_key` function on any |keys they are expecting to receive input through. This is done using the syntax `game->monitor_key(KEY_RIGHT);` where `KEY` is the tag for the relevant key in the definitions.hpp file. A table of these |key tags is included in this document in [Appendix A](#appendix-a).

Once the user has set a key to be monitored the engine can detect input and the user can catch that input with the following functions.
    `game.key_pressed(KEY);` Will return a bool whether the key was pressed or not. KEY is the tag for the relevant key.
    `game.key_held(KEY);` Will return a bool whether the key was held down or not. KEY is the tag for the relevant key.
    `game.key_released(KEY);` Will return a bool whether the key was released or not. KEY is the tag for the relevant key.


## Sound
```cpp
	Sound create_sound(const char* file_name, bool loop_sound);
```

For a program to include sound effects the user must first define the sound they wish to use. To do this the `.mp3` or `.wav` file(s) must be loaded into a `sounds` directory inside the user's project directory. __It is essential that this directory be called `sounds`. The Hop engine looks for a sounds directory and any other name will result in the directory being ignored.__.

If there is a `sounds` directory present in the project and it contains `.mp3` or `.wav` files then the user can proceed to define the sound in their game. In the user's main function they should use the following syntax to name the relevant sound file: `hop::Sound sound_name = game.create_sound("file_name.mp3", true);` if the sound file should loop or `hop::Sound sound_name = game.create_sound("file_name.wav", false);` if the sound should only run once. 

Once the user has sounds defined they can being playing the sound by calling the `play()` function using the following syntax:
```cpp
if(background_music!=NULL){
        background_music->play();
}
```

There is also a `pause()` function which can be called on a defined sound using the syntax `sound_name->pause();`.

If the user ends the game then any sounds currently playing will be ended automatically. The user does not need to worry about canceling sounds as long as their game ends.

## Running a Game

When the user has initialized the Hop Engine, created the needed objects and images for their game, added any desired sounds or user interaction then they are ready to make their game run. Running a game using the Hop Engine is very straightforward. The user has already begun the game when they ran `game.run()` during [Getting Started](#getting-started). Now any gameplay can be put inside a loop with the condition `game.is_running()`. Each cycle of this loop must being with a call to update the game, the syntax for this call is `game.update();`. This call must be the first line inside the loop. To end the game the user should identify some condition which when met will call `game.stop()`. After running `game.stop()` the user should return 0 from their main function and end the program inorder to halt all remaining processes from the engine. 

## Examples
```cpp
#include "hop.hpp"

int main() {

	/* GETTING STARTED*/ 
	hop::Game game("Example_Game");
	game.set_window_size(game.get_resolution_height(),game.get_resolution_height());
	// game.set_fullscreen(); // Would do the same as the line above, except it would also set fullscreen=True
    game.run();

	/* DEFINING CUSTOM COLORS */
	hop::Color pink={{1.0}, {0.4}, {0.7}}; // The RGB values of pink are 255, 102, 178
	hop::Color orange={{0.9}, {0.5}, {0.0}}; // The RGB values of orange are 229, 127, 000
    hop::Color light_pink={{1}, {0.76}, {0.9}}; // The RGB values of light_pink are 255, 193, 229
    hop::Color brown={{0.7}, {0.4}, {0.1}}; // The RGB values of brown are 178, 102, 025 
    hop::Color grey={{0.4}, {0.5}, {0.5}}; // The RGB values of grey are 102, 127, 127
    hop::Color real_brown={{0.5}, {0.3}, {0.0}}; // The RGB values of real_brown are 127, 076, 000

	/* CREATING IMAGE INSTANCE */
    // Basic Heart Image
    hop::Image heart(820, 300, 50, 50);
    heart.create_rectangle(10, 15, 25, 10, light_pink);
    heart.create_rectangle(15, 10, 15, 5, light_pink);
    heart.create_rectangle(20, 5, 5, 5, light_pink);
    heart.create_rectangle(13, 25, 7, 5, light_pink);
    heart.create_rectangle(25, 25, 7, 5, light_pink);

	//Other shapes
	hop::triangle1 = game->create_triangle(70,60,0,0,90,20,orange);
	hop::circle1 = game->create_circle(950,600,20, hop::GREEN);

	/* CREATING TEXT */ 
	hop::TextBox title(660,25,5,hop::grey,"THIS IS HOW YOU MAKE TEXT!");

	/* IMPLEMENTING SOUNDS */
	hop::Sound background_music = game.create_sound("background.mp3", true);
    hop::Sound other = game.create_sound("noise.wav", false);
    if(background_music!=NULL) {
        background_music->play();
    }

	/* INITIALIZING USER INPUT */
	game->monitor_key(KEY_SPACE);
	game->monitor_key(KEY_P);
	game->monitor_key(KEY_ESCAPE);

	/* RUNNING THE GAME */

	while (game.is_running()) {
		
		game.update();

		if(game.key_pressed(KEY_ESCAPE)){
            game.stop();
        }  

		/* MOVING THE IMAGE WHEN USER INPUT IS RECEIVED */
		if(game.key_pressed(KEY_SPACE)) {
				heart.move(-200,100); // The heart is moved left 200 pixels and upwards 100 pixels.
		}

		/* CONTROLING THE SOUNDS BASED ON USER INPUT */
		if(game.key_pressed(KEY_P)) {
			background_music->pause();
		} 

	}


	return 0;
}
```

__There is an example of a more advanced game implementation in [Appendix B](#appendix-b). If you are interested in seeing how to implement more complex game mechanics using the features explained above please refer to it.__


# Building the Hop Engine from Source





# Appendix A

| Key Code | Key |
| :--- | ---: |
|KEY_SPACE | Space |
|KEY_0 | 0 |
|KEY_1 | 1 |
|KEY_2 | 2 |
|KEY_3 | 3 |
|KEY_4 | 4 |
|KEY_5 | 5 |
|KEY_6 | 6 |
|KEY_7 | 7 |
|KEY_8 | 8 |
|KEY_9 | 9 |
|KEY_SEMICOLON | ; |
|KEY_EQUAL | = |
|KEY_A | a |
|KEY_B | b |
|KEY_C | c |
|KEY_D | d |
|KEY_E | e |
|KEY_F | f |
|KEY_G | g |
|KEY_H | h |
|KEY_I | i |
|KEY_J | j |
|KEY_K | k |
|KEY_L | l |
|KEY_M | m |
|KEY_N | n |
|KEY_O | o |
|KEY_P | p |
|KEY_Q | q |
|KEY_R | r |
|KEY_S | s |
|KEY_T | t |
|KEY_U | u |
|KEY_V | v |
|KEY_W | w |
|KEY_X | x |
|KEY_Y | y |
|KEY_Z | z |
|KEY_LEFT_BRACKET | [ |
|KEY_BACKSLASH | \ |
|KEY_RIGHT_BRACKET | ] |
|KEY_GRAVE_ACCENT | ` |
|KEY_ESCAPE | Esc |
|KEY_ENTER | Enter |
|KEY_TAB | Tab |
|KEY_BACKSPACE | Backspace |
|KEY_INSERT | Insert |
|KEY_RIGHT | Right Arrow |
|KEY_LEFT | Left Arrow |
|KEY_DOWN | Downward Arrow |
|KEY_UP | Upward Arrow |
|KEY_CAPS_LOCK | Caps |
|KEY_F1 | F1 |
|KEY_F2 | F2 |
|KEY_F3 | F3 |
|KEY_F4 | F4 |
|KEY_F5 | F5 |
|KEY_F6 | F6 |
|KEY_F7 | F7 |
|KEY_F8 | F8 |
|KEY_F9 | F9 |
|KEY_F10 | F10 |
|KEY_F11 | F11 |
|KEY_F12 | F12 |
|KEY_KP_0 | Key Pad 0 |
|KEY_KP_1 | Key Pad 1 |
|KEY_KP_2 | Key Pad 2 |
|KEY_KP_3 | Key Pad 3 |
|KEY_KP_4 | Key Pad 4 |
|KEY_KP_5 | Key Pad 5 |
|KEY_KP_6 | Key Pad 6 |
|KEY_KP_7 | Key Pad 7 |
|KEY_KP_8 | Key Pad 8 |
|KEY_KP_9 | Key Pad 9 |
|KEY_LEFT_SHIFT | Left Shift |
|KEY_LEFT_CONTROL | Left Control |
|KEY_LEFT_ALT | Left Alt |
|KEY_RIGHT_SHIFT | Right Shift |
|KEY_RIGHT_CONTROL | Right Control |
|KEY_RIGHT_ALT | Right Alt |

# Appendix B

__Credit for this implementation of PONG: Glen Beatty__
__The original PONG was released on November 29 1972. It was developed by Allan Alcorn while working working for Atari.__

```cpp
#include "hop.hpp"
#include <time.h>
#include <stdlib.h>  
#include <iostream>


class Paddle{

public:
Paddle(hop::Game* game, int x, hop::Color color){
    this-> game = game;
    paddle_rectangle = game->create_rectangle(x,550,20,120,color);
    this-> y = 550;
    this->vy = 0;
}
void move_up( int magnitude){

    if(y+120 < 1014){
        paddle_rectangle->move(0,magnitude);
        y = y + magnitude;
        if(vy<5){
            this->vy +=1;
        }
    }

}

void move_down( int magnitude){

    if(y > 214){
        paddle_rectangle->move(0,-magnitude);
        this->y = this->y -magnitude;
        if(vy>-5){
            this->vy -=1;
        }
    }

}
int y;
int vy;
private:
hop::Rectangle paddle_rectangle;
hop::Game* game;


};

class Ball{
    public:
    Ball(hop::Game* game) {
        this->game = game;
        reset();
    }
    void reset (){
        circle = game->create_circle(950,600,20, hop::GREEN);
        this->vx = -10;
        this->vy = rand()%16 -8;
        this->x = 950;
        this->y = 600;
    }
    void update(){
        circle->move(vx,vy);
        x+= vx;
        y+=vy;
    }
    int x;
    int vx;
    int y;
    int vy;
    int radius = 10;
    int velo;

    private:
    hop::Game* game;
    hop::Circle circle;
    int speed = 10;

};

void collision(Ball& ball, Paddle& player_paddle, Paddle& cpu_paddle, hop::Sound boing){

    if((ball.x < 80) &&(ball.x>60)&&(ball.y>=player_paddle.y-20)&&((ball.y+30)<=(player_paddle.y + 150))){
        int new_y_vel = ((ball.y-player_paddle.y)/10) - 5; 
        ball.vy = new_y_vel;
        ball.vx = ball.vx * -1;
        if(boing!=NULL){
            boing->play();
        }
    }

    else if((ball.x > 1820) &&(ball.x<1840)&&(ball.y>=cpu_paddle.y)&&((ball.y+20)<=(cpu_paddle.y + 120))){
        int new_y_vel = ((ball.y-cpu_paddle.y)/10) - 5; 
        ball.vy = new_y_vel;
        ball.vx = ball.vx * -1;
        if(boing!=NULL){
            boing->play();
        }
    }
}

bool collision(Ball& ball){

    if((ball.y<220)&&(ball.y>200)){
        return true;
    }

    if((ball.y<1010)&&(ball.y>990)){
        return true;
    }

    return false;
}


int main(){
   
    srand (time(NULL));
    hop::Game game("My_Game_Name");
    game.set_fullscreen();
    game.run();
    game.monitor_key(KEY_ESCAPE);
    game.monitor_key(KEY_UP);
    game.monitor_key(KEY_DOWN);
    Paddle player_paddle(&game, 50, hop::BLUE);
    Paddle cpu_paddle(&game, 1850, hop::RED);
    hop::Rectangle bottom = game.create_rectangle(0,150,1920,60,hop::WHITE);
    hop::Rectangle top = game.create_rectangle(0,1020,1920,60,hop::WHITE);
    hop::Rectangle p1l3 = game.create_rectangle(40, 25, 20,100, hop::BLUE);
    hop::Rectangle p1l2 = game.create_rectangle(80, 25, 20,100, hop::BLUE);
    hop::Rectangle p1l1 = game.create_rectangle(120, 25, 20,100, hop::BLUE);
    hop::Rectangle cl3 = game.create_rectangle(1780, 25, 20,100, hop::RED);
    hop::Rectangle cl2 = game.create_rectangle(1820, 25, 20,100, hop::RED);
    hop::Rectangle cl1 = game.create_rectangle(1860, 25, 20,100, hop::RED);
    int player_lives = 3;
    int cpu_lives = 3;
    Ball ball(&game);
    hop::TextBox title(660,25,5,hop::GREEN,"PONG!");
    hop::Sound background_music = game.create_sound("pong_background.mp3", true);
    hop::Sound boing = game.create_sound("boing.wav", false);
    if(background_music!=NULL){
        background_music->play();
    }


    while(game.is_running()){
        game.update();
        if(game.key_pressed(KEY_ESCAPE)){
            game.stop();
        }    
        if(game.key_pressed(KEY_UP)||game.key_held(KEY_UP)){
            player_paddle.move_up(15);
        }
        if(game.key_pressed(KEY_DOWN)||game.key_held(KEY_DOWN)){
            player_paddle.move_down(15);
        }

        ball.update();

            if(ball.vx>0){
                if((cpu_paddle.y+60)<(ball.y+10-40)){
                    cpu_paddle.move_up(4);
                }
                else if((cpu_paddle.y+60)>(ball.y+10+40)){
                    cpu_paddle.move_down(4);
                }
        }    

        collision(ball,player_paddle, cpu_paddle, boing);
        
        if(collision(ball)){
            ball.vy = -1* ball.vy;
        }
        if(ball.x<-200){
            player_lives -=1;
            if(player_lives == 2){
                p1l1->move(0,-1000);
                ball.reset();
            }
            else if(player_lives == 1){
                p1l2->move(0,-1000);
                ball.reset();

            }
            else if(player_lives == 0){
                p1l3->move(0,-1000);
                hop::TextBox title(540,600,4,hop::RED,"GAME OVER!");
            }
        }
      if(ball.x>2100){
            cpu_lives -=1;
            if(cpu_lives == 2){
                cl1->move(0,-1000);
                ball.reset();
            }
            else if(cpu_lives == 1){
                cl2->move(0,-1000);
                ball.reset();

            }
            else if(cpu_lives == 0){
                cl3->move(0,-1000);
                hop::TextBox title(560,600,4,hop::RED,"You WIN!");
            }
        }
    }

    return 0;
}
```