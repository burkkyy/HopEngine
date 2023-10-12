# Phase 2: Glen's Contributions to Team Specifications Document

## Product Overview
We intend to create Hop Engine, a lightweight, low-level and open-source two-dimensional game engine in C++ which we would like to make available on Vancouver Island University (VIU) Linux machines. The engine will interface with the Vulkan graphics API and provide a much simpler code library for programmers to interact with than is otherwise available. Our goal is to create a software library that will allow aspiring programmers to transition from the command line into basic graphical game design with a minimal learning curve.

Our engine will support only the essential graphics rendering, input handling, and other necessary features. As much game-specific logic as possible will be left to the programmer. Through this design philosophy, we hope the programmer can spend more time programming in familliar C++ and less time learning engine-specific code.

After developing this engine, we will create a playable game using our engine to demonstrate it's viability. The development and implementation of this game will also allow us to de-bug and refine our engine. 

## Product Behaviour and Features

As a C++ game-engine library, Hop allows user-programmers to handle graphics, sound, user input, and other essential game-related functionality using their existing knowledge of C++ programming. Our API, which is declared in *hop.hpp*, provides all classes and functions necessary for users to implement their game using our engine.

Here is a summary of some key classes and functions in our API.

#### Window (class)

The first step to creating any game is to create a window in which the game will reside.

 To generate a window,the user instantiates our Window class using the following syntax:

> *Window my_window ("Hello World!",1200,800);*

This code will create a 1200 x 800 pixel non-fullscreen window entitled "Hello World!" 

After creating their window, the user can apply a background image using the set_background method:

> *my_window.set_background("my_background.png");*

This code will render a texture located in *assets/img/background/my_background.png* as a background image spanning the entire window. 

The user can clear the current window of all rendered graphics using the clear method:

> *my_window.clear();*

Lastly, when the user is finished with their graphics window, they can close it by calling the close method:

> *my_window.close();*

#### Image (class)

After the user has created their window, they can use the image class to begin displaying graphics on the screen. As the name suggests, an image object is used to render an image file onto a particular location in the graphics window.

An image object can be created using the following syntax: 

> *Image my_image("cool_image.png",128,128,400,200,2)*

Where the parameters are as follows:
1. The name of the file within the *assets/img/images/* directory.
2. The horizontal dimensions of the image in pixels.
3. The vertical dimensions of the image in pixels.
4. The horizontal distance between the left edge of the image and the left side of the window.
5. The vertical distance between the bottom edge of the image and the bottom of the window.
6. The layer upon which the image resides, which determines the overlap between graphical elements in the z plane. Since this Image has a layer index of 2, it will overlap images with indexes of 0 and 1 and will be overlapped by any image with a layer index of 3 or more.

#### Character (class)

Character is a class that represents a moveable character within the game. Similar to an Image object, a Character has a size and position within the window. Unlike an Image object, which is a static image within the window, the character class can be also animated by changing the texture asset that is rendered on the character.

A Character object can be instantiated using the following code: 

> *Character my_character("my_character.png",64,64,64,64,3);*

Where the parameters are as follows:
1. The initial image asset to be rendered upon the character.
2. The horizontal dimensions of the character in pixels.
3. The vertical dimensions of the character in pixels.
4. The horizontal distance between the left edge of the character's intitial position and the left side of the window.
5. The vertical distance between the bottom edge of the character's initial position and the bottom of the window.
6. The layer upon which the image resides, which determines the overlap between graphical elements in the z plane. Since this Image has a layer index of 3, it will overlap images with indexes of 0 - 2 and will be overlapped by any image with a layer index of 4 or more.

Once created, a Character object can be animated by changing the image asset which is rendered on it.

> *my_character.set_image("my_character_run.png");*

These texture swaps can also be performed automatically, such as when a Character moves in a particular direction:

> *my_character.move_x(20);*

Will move the character 20 pixels horizontally to the right. By calling set_image from within move_x, a user could load an image asset depending on which direction the character was moving. 

#### Text (class)

Text class will render supplied text on the screen and can be used as follows:

> *Text my_text("Hello World!", 2, 200, 800, BLACK);*

Where the parameters are as follows:
1. The text to be displayed on the screen
2. The font size, represented by an integer between 1 and 3 with 1 as the smallest and 3 the largest.
3. The horizontal distance between the left side of the window and the left edge of the text box.
4. The vertical distance between the bottom of the window and the bottom of the text box.
5. The colour of the text to be displayed.

#### void btn_A() (function)

A series of functions will be called when a bound button is pressed by the user. From within these functions, the user-programmer can handle the registered input as they wish. 

#### void play_sound (function)

play_sound is a function that will play an audio file located within the designated asset directory by specifying the file name. For example:

> *play_sound("sound_1.wav");*  

Will play the sound file *sound_1.wav* from the directory *assets/sound* if such a file exists in that directory.  

## Target Users and Scenarios

The target user for Hop Engine is an aspiring programmer with some experience with the C++ programming language. In the context of VIU, we hope our library would be accessible to a second-year computer science student. Such a user would likely be comfortable writing code for command-line applications, but may have little experience creating more complex development environments or using non-standard libraries. 

#### Scenario 1: Aspiring Game Developer 

Ronald is an avid gamer who enrolled in VIU's Diploma in Computer Science after completing secondary school in Nanaimo. Having successfully completed the first of two years in the Diploma program, Ronald is excited to complete his diploma and look for jobs in the game development industry. While he has excelled academically at VIU, Ronald knows the importance of building a portfolio to demonstrate his interest and competency in game development. Ronald has tried a few open-source game engine, but was unable to install the required dependancies and get his project to build. Having heard about Hop Engine from a classmate, Ronald clones the project from the VIU GIT server. He is excited to see that the project builds using the included Makefile and a blank window is immediately generated. Ronald sets out to build a simple 2d platformer game which he hopes to show prospective employers. 

#### Scenario 2: Non-Gamer Computer Science Student

Melinda is a fourth-year computer science student at VIU who is mid-way through her second-to-last semester at university. She has a strong interest in mathematics and is also working towards a math minor. While she has never been interested in playing or developing video games, she decided to take a computer graphics course (CSCI 405: Computer Graphics) and enjoys the complexity of rendering graphics. Finding herself with a bit of free time, Melinda decides to experiment with Hop Engine, a open-source graphics engine created by fellow VIU computer science students. While Melinda wouldn't invest much time in learning a fully-fledged game engine, she gives Hop Engine a try. It's simple to install and is written in C++, the language she is most comfortable using. She spends a few hours creating a simple game using pre-packaged image assets. Because Hop Engine is open-source, she also explores how the engine uses the Vulkan graphics pipeline to actually generate computer graphics.