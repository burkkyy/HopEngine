# Specifications

## Product Overview
Hop Engine is a lightweight, low-level, open-source, and two-dimensional game engine in C++, which can run on Vancouver Island University (VIU) Linux machines. The engine will interface with the Vulkan graphics API and provide a much simpler code library for programmers to interact with than is otherwise available. Our goal is to create a software library that will allow aspiring programmers to transition from the command line into basic graphical game design with a minimal learning curve.

Our engine will support only the essential graphics rendering, input handling, and other necessary features. As much game-specific logic as possible will be left to the programmer. Through this design philosophy, we hope the programmer can spend more time programming in familliar C++ and less time learning engine-specific code.

## Product Behaviour and Features

As a C++ game-engine library, Hop allows user-programmers to handle graphics, sound, user input, and other essential game-related functionality using their existing knowledge of C++ programming. Our API, which is declared in *hop.hpp*, provides all classes and functions necessary for users to implement their game using our engine.

Here is a summary of some key classes and functions in our API.

#### Window (class)

The first step to creating any game is to create a window in which the game will reside.

 To generate a window,the user instantiates our Window class using the following syntax:
 
> *Game my_window("My Game's Name!");*
>*my_window.set_fullscreen();*

This code will create a fullscreen window called "My Game's Name!".
After the window has been given a name, the user can also set the size of the window by doing the following:

>*.set_window_size(1200, 1800);*

This will create a 1200 pixel by 1800 pixel window on the screen.

> *my_window.clear();*

Lastly, when the user is finished with their graphics window, they can close it by calling the close method:

> *my_window.close();*

#### TextBox (class)

The TextBox class will render supplied text on the screen by placing text within a larger box to hold the characters.

> *Text my_text(200, 800, 2, BLACK, "Hello World!");*

Where the parameters are as follows:
1. The x coordinate of the bottom left vertex of the box
2. The y coordinate of the bottom left vertex of the box
2. The font size, represented by an integer between 1 and 3 with 1 as the smallest and 3 the largest.
5. The colour of the text to be displayed.
6. The string of text to be displayed

## Input (class)
There are several functions within this class to track which keys have been used and how. KEY_CODE is the code attached to each key in the definitions.hpp file.

Inorder to be able to use the following functions key's must be tracked using the function call:
#### void monitor_key(KEY_CODE);

#### bool key_pressed(KEY_CODE)
This returns true to indicate that a supplied key has been pressed. The user can handle this information as they wish.

#### bool key_held(KEY_CODE)
This returns true to indicate that a supplied key has been held. The user can handle this information as they wish.

#### bool key_released(KEY_CODE)
This returns true to indicate that a supplied key has been released. The user can handle this information as they wish.

## AudioEngine (class)
Hop uses the MiniAudio library, an audioplayback and capture library, to produce sound. The user can add sound to their game calling functions within the AudioEngine class.

The user can play an audio file by using the following syntax:
*hop::sound dave_is_a_star = create_sound("party_in_the_usa_wessels_cover", true)*
dave_is_a_star->play() will play the music
dave_is_a_star->pause() will pause the music

Where the parameters are as follows:
1. The filename in the form of a string
2. The loop status of the audiofile; true to loop, false to not loop

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