# Specifications
Contains a description of what our product is, how it will work, and who it might be useful for.
# Product Overview
Hop Engine is a lightweight, low-level, open-source, and two-dimensional game engine in C++, which can run on Vancouver Island University (VIU) Linux machines. The engine will interface with the Vulkan graphics API and provide a much simpler code library for programmers to interact with than is otherwise available. Our goal is to create a software library that will allow aspiring programmers to transition from the command line into basic graphical game design with a minimal learning curve.

Our engine will support only the essential graphics rendering, input handling, and other necessary features. As much game-specific logic as possible will be left to the programmer. Through this design philosophy, we hope the programmer can spend more time programming in familliar C++ and less time learning engine-specific code.

# Product Behaviour and Features
As a C++ game-engine library, Hop allows user-programmers to handle graphics, sound, user input, and other essential game-related functionality using their existing knowledge of C++ programming. Our API, which is declared in ***hop.hpp***, provides all classes and functions necessary for users to implement their game using our engine.

## Data Types
In addition to the classes and functions which are documented in the following section, Hop Engine defines several data types which are not declared in the user-accessbile API declared in *hop.hpp* but are still necessary to make full use of Hop Engine. Those data types are described below.

#### Colour(float red, float green, float blue)
**Description:** Color is internally a 3-component vector as defined by the OpenGL Mathematics (GLM) library our engine uses to store vector data and perform linear algebra related operations. A Colour is really just a set of 3 floats with values ranging between 0.0 and 1.0. While it is possible to assign values outside of this range, they will behave as if they were the minimum and maximum valid values, 0.0 and 1.0 respectively. A Colour can be created in a project file using the following code:
> hop::Color my_colour(0.0,1.0,0.0);

In the previous code, a solid green colour is produced because the red and blue values are 0.0 and the green value is 1.0. Colors can also be defined within the set of arguments provided to create another object, such as a Circle, Rectangle, Square, or TextBox object. An example of how this is done is shown below.
> Rectangle my_rectangle = my_game.create_rectangle(0,0,200,200, hop::Color(0.5,0.5,0.5));

The previous line of code will create 200 pixels wide x 200 pixels high rectangle at the bottom-left corner of the game window that has a grey colour, since red, green, and blue are all set to 0.5

Lastly, there are a number of colours that are defined as static values. In place of a colour defined by 3 separate floats, the user can use several constants which are defined at the beginning of the *hop.hpp* header file. For example, to create the rectangle described above with a solid blue colour, the user can enter the following code.
> Rectangle my_rectangle(0,0,200,200,hop::BLUE);

#### GameObject Class
**Description:** The GameObject class is the parent class for the basic geometric objects, Rectangle, Triangle, and Circle. Each of these geometric shape classes inherits two important methods from the GameObject class which are not defined within hop.hpp. Those methods are shown here.

#### void move(int x, int y)
**Description:** Moves an object by a specified number of pixels in the x and y planes.
**Parameters:**
*int x:* The number of pixels to move an object relative to its current position in the horizontal plane. Positive values move the object to the right while negative values move it to the left.
*int y:* The number of pixels to move an object relative to its current position in the vertical plane. Positive values move the object up while negative values move it down.

#### void set_color(Color color)
**Description:** Changes the colour of an object.
**Parameters:**
*Color color* The Hop Engine color that the object should be changed to. Please see the previous section which describes how colors work in Hop Engine.

## Public Classes and Methods
Descriptions of all user-accessible classes and functions, which are declared in hop.hpp, are explained here.

## Game (class)

An instance of the Game class is used to initiate and stop the user's game window. This class also contains methods from which the user gets information about the state of the game, including whether the window is still open and whether the user has pressed any keys.

#### Game(const char* window_name)
**Description:** Sole constructor for the game object.
**Parameters:** 
*const char\* window_name*: The name of the game window as shown in the player's operating system.  
#### bool set_window_size(int width, int height)
**Description:** Called to set the desired height and width of the player's game window. This method is only necessary if a windowed game is desired. If the game window is set to fullscreen, this method has no effect.
**Parameters:** 
*int width*: The desired width of the game window in pixels.
*int height*: The desired height of the game window in pixels.
**Returns** *false* if either the height or width is less than 100 pixels and *true* otherwise. 

#### void set_fullscreen()
**Description:** Called to set the game window to be fullscreen. If this method is called, the game will have dimensions equal to the player's screen resolution. The game will also run in a fullscreen context, meaning it will not be contained within an operating system window. As a result, the user must implement a method to close the game window. This could be acheived by calling their Game object's stop() method when a key is pressed, or calling it based on some game logic.

#### void set_windowed()
**Description:** Called to set the game window to be generated in windowed mode. That means that the game will exist within a window context generated by the player's operating system and will behave as windows typically do. It will be possible to close and minimize the game window using the appropriate icons, typically located at the top-right of the window. By default, the Game object will open a window in this manner, so it is not usually necessary to call this method unless the game's window parameters are determined at runtime. 

#### int get_resolution_width();
**Description** Provides the horizontal component of the player's screen resolution in pixels. This method must be called after creating the Game object but before calling the run method, which creates the game window. This resolution screen data can be retreived and used to set the size parmeters of the game window. 
**Returns the number of horizontal pixels on the user's screen. 

#### int get_resolution_height();
**Description** Provides the vertical component of the player's screen resolution in pixels. This method must be called after creating the Game object but before calling the run method, which creates the game window. This resolution screen data can be retreived and used to set the size parmeters of the game window. 
**Returns the number of vertical pixels on the user's screen. 
    
#### void run()
**Description:** The run method is called to create the game window with the previously specified window parameters. Once run is called, the game window and all other necessary game components become active, and the user can begin using all other components of the engine.

#### bool is_running()
**Description:** After the run method has been called to create the game window, the is\_running function is called to determine whether the game is still running correctly. If the game window has been closed, or if something else has gone wrong with Hop Engine, is\_running returns false. Otherwise it returns true. 

Typical use of the is\_running method to validate the user's gameplay loop is shown below: 
> Game my_game;
> my_game.set_fullscreen();
> my_game.run();
> while(**my_game.is\_running()**){
> my_game.update();
> /* Code to execute once per frame */
> }
> return 0;

**Returns** *true* if the game is still open and running correctly and *false* otherwise.

#### void update()
**Description:** The update method is called each frame (see example in is\_running() method above) to update the Game object with any changes to the game state. These changes could include the game window closing, new user input being detected, or an (unlikely) error with any of Hop Engine's components. The update method does not directly provide information about the game state to the user, rather it ensures that other information-yielding methods provide current and accurate information.

#### void stop()
**Description:** The stop method terminates the game window, at which point the program will end. This method can be called to end the game based on game logic or upon receiving some user input. It is necessary for the user to provide the player some way to close the game window if a full-screen context has been specified, since the operating system will not provide a way to do it. In a windowed context, a button to close the widow will exist where it typically does in the player's window manager (usually the upper-right corner).

#### Rectangle create_rectangle(int x, int y, int width, int height, Color color)
**Description:**
The create_rectangle method creates a rectangle of a specified size at a specified position on the screen.
**Parameters**
*int x:* The distance in pixels between the left edge of the rectangle and the left edge of the game window.
*int y:* The distance in pixels between the bottom edge of the rectangle and the bottom edge of the game window.
*int width:* The width of the rectangle in pixels. 
*int height:* The height of the rectangle in pixels.
*color Colour*: The hop::Color object which describes the colour of the rectangle.
**Returns:** A pointer to the created rectangle. The Rectangle object cannot be directly instantiated, so a pointer to it is provided. 
#### Circle create_circle(int x, int y, int radius, Color color)
**Description:**
The create_circle method creates a rectangle with a specified radius at a specified position on the screen.
**Parameters**
*int x:* The distance in pixels between the left-most point of the circle and the left edge of the game window.
*int y:* The distance in pixels between the lowest point on the circle and the bottom edge of the game window.
*int radius:* The radius of the circle.
*color Colour*: The hop::Color object which describes the colour of the rectangle.
**Returns:** A pointer to the created circle. The Circle object cannot be directly instantiated, so a pointer to it is provided. 
#### Triangle create_triangle(int v1x, int v1y, int v2x, int v2y, int v3x, int v3y, Color color)
**Description:**
The create_triangle method creates a triangle according to the three provided vertexes.
**Parameters**
*int v1x:* The distance in pixels between the first vertex and the left edge of the game window.
*int v1y:* The distance in pixels between the first vertex and the bottom edge of the game window.
*int v2x:* The distance in pixels between the second vertex and the left edge of the game window.
*int v2y:* The distance in pixels between the second vertex and the bottom edge of the game window.
*int v3x:* The distance in pixels between the third vertex and the left edge of the game window.
*int v3y:* The distance in pixels between the third vertex and the bottom edge of the game window.
*color Colour*: The hop::Color object which describes the colour of the rectangle.
**Returns:** A pointer to the created triangle. The Triangle object cannot be directly instantiated, so a pointer to it is provided. 
#### bool monitor\_key(int key_code)
**Description:** Tells the Game object to monitor a specified key for player input. Before users can monitor a key to see if it has been activated, the Game object needs to be instructed to monitor it. 
**Parameters:** 
*int key_code:* An integer corrosponding to the key code for a desired key. Supported keys all have #define directives located in definitions.hpp, which is located within the engine/source directory. An example of how these key codes are used is shown below.
> Game my_game("cool game name");
> game.set_fullscreen();
> game.run();
> game.monitor\_key(KEY_LEFT);
> game.monitor\_key(KEY_RIGHT);
> game.monitor\_key(KEY_ESCAPE);

The above code will instruct the Game object to monitor the left and right arrow keys as well as the escape key for any user input. Once the Game object has received these instructions, the remaining keyboard input functions can be used with these monitored keys.
**Returns** true if the provided key code is supported by Hop Engine and false otherwise.

#### bool key\_pressed(int key_code)
**Description:** The key\_pressed method asks the Game object whether a specified key has been pressed.
**Parameters:** 
*int key_code:* An integer corrosponding to the key code for a desired key. Supported keys all have #define directives located in definitions.hpp, which is located within the engine/source directory. An example of how these key codes are used is shown below.
**Returns** true if the specified key has been pressed in the most recent frame and false otherwise.
#### bool key\_held(int key_code)
**Description:** The key\_held method asks the Game object whether a specified key has been held down.
**Parameters:** 
*int key_code:* An integer corrosponding to the key code for a desired key. Supported keys all have #define directives located in definitions.hpp, which is located within the engine/source directory. An example of how these key codes are used is shown below.
**Returns** true if the specified key was held in the most recent frame and false otherwise.

#### bool key\_released(int key_code)
**Description:** The key\_held method asks the Game object whether a specified key has been held down.
**Parameters:** 
*int key_code:* An integer corrosponding to the key code for a desired key. Supported keys all have #define directives located in definitions.hpp, which is located within the engine/source directory. An example of how these key codes are used is shown below.
**Returns** true if the specified key was held in the most recent frame and false otherwise.

#### std::vector<int> get\_pressed\_keys();
**Description:** The get\_pressed\_keys method is used to obtain a std::vector<int> containing all keys which were pressed in the previous frame. This is an alternative method of obtaining user input to the key_pressed method described earlier. This method of determining which keys were pressed will be more convenient for some users.
**Returns**  a std::vector<int> containing all keys which were pressed in the previous frame.

#### std::vector<int> get\_held\_keys();
**Description:** The get\_held\_keys method is used to obtain a std::vector<int> containing all keys which were held down in the previous frame. This is an alternative method of obtaining user input to the key_held method described earlier. This method of determining which keys were pressed will be more convenient for some users.
**Returns**  a std::vector<int> containing all keys which were held in the previous frame.

#### std::vector<int> get\_released\_keys();
**Description:** The get\_released\_keys method is used to obtain a std::vector<int> containing all keys which were released in the previous frame. This is an alternative method of obtaining user input to the key_released method described earlier. This method of determining which keys were pressed will be more convenient for some users.
**Returns**  a std::vector<int> containing all keys which were pressed in the previous frame.

#### Sound create\_sound(const char* file\_name, bool loop\_sound);
**Description:** The create_sound method loads an audio file from the sounds directory, which is located within each project directory. Once the sound file has been loaded, it can be played or stopped according to the user's game logic. Supported audio formats are .wav, .mp3, and .flac audio files. 
**Parameters:** 
*const char file\_name:* The name of the audio file, which must be located within project/sounds/. 
*bool loop_sound:* This parameter tells the Game object whether the sound file should loop back to the beginning of the track once it finishes. If true, the audio file will continue to repeat. If false, the audio file will only be played once.
**Returns** If the audio file was loaded succesfully, a pointer to the Sound object is returned. If not, typically due to an unsupported file format or incorrect file name, *nullptr* is returned. As a result, it is suggested that users check whether the returned pointer is NULL or not before playing a Sound object.
**Methods Avaialble for Sound Objects, which are returned as pointers:**
*Play:* Begins audio playback of a audio file. 
*Stop:* Begins audio playback of a audio file. 

An example of how Sound objects are created and played is shown below:
> *hop::Sound dave_is_a_star = create_sound("party_in_the_usa_wessels_cover", true)*
> if(dave_is_a_star!=NULL){
> dave_is_a_star->play();
> dave_is_a_star->pause();
> }
___
## Image (class)
**Description:** An Image class object is essentially a container for primitive shapes, such as triangles, rectangles, and circles, as well as other objects. Operations that can be performed on primitive shapes, such as movement and color change, can also be performed on Image objects. In this case, the appropriate operation will be performed on all shapes located within the Image object.

#### Image(int x, int y, int width, int height)
**Description:** The sole constructor for an image object. 
**Parameters:** 
*int x:* The horizontal distance between the left edge of the Image object and the left edge of the game window.
*int y:* The vertical distance between the bottom edge of the Image object and the bottom edge of the game window.
*int width:* the width of the Image object in pixels.
*int height:* the height of the Image object in pixels.
**Returns** True if the height and width parameters are positive integers and false otherwise. 
#### bool create_rectangle (int x, int y, int width, int height, Color color)
**Description:** A rectangle object created within the Image object. When a rectangle object is created within an Image object, it's position is specified relative to the inside of the Image object rather than relative to the edges of the game window, as was the case with the Game::create_rectangle method. Since all primitive shapes and child Image objects are located within the container defined by the image object, if any portion of the rectangle would fall outside of the Image object, the rectangle won't be created. 
**Parameters:**
*int x:* The horizontal distance between the left edge of the parent Image object and the left edge of the proposed rectangle in pixels. 
*int y:* The vertical distance between the bottom edge of the parent Image object and the bottom edge of the proposed rectangle in pixels.   
*int width:* The width of the rectangle in pixels.
*int height:* The height of the rectangle in pixels;
*Color color:* The desired color of the rectangle.
**Returns** false if the object cannot be contained within the bounds of the parent Image object. That is, x+width > the width of the Image and/or y+height > the height of the Image. False is also returned if the specified width and/or height is less than 1. Otherwise true is returned.
#### bool create_circle (int x, int y, int radius, Color color)
**Description:** A circle object created within the Image object. When a circle object is created within an Image object, it's position is specified relative to the inside of the Image object rather than relative to the edges of the game window, as was the case with the Game::create_circle method. Since all primitive shapes and child Image objects are located within the container defined by the image object, if any portion of the circle would fall outside of the Image object, the rectangle won't be created. 
**Parameters:**
*int x:* The horizontal distance between the left edge of the parent Image object and the left-most point of the proposed circle in pixels. 
*int y:* The vertical distance between the bottom edge of the parent Image object and the bottom-most point of the proposed circle in pixels.   
*int radius:* The radius of the circle.
*Color color:* The desired color of the circle.
**Returns** false if the object cannot be contained within the bounds of the parent Image object. That is, x+(2\*radius) > the width of the Image and/or y+(2\*radius) > the height of the Image. False is also returned if the specified radius is less than 1. Otherwise true is returned.

#### bool create_triangle (int v1x int v1y, int v2x, int v2y, int v3x, int v3y, Color color)
**Description:** A triangle object created within the Image object. When a triangle object is created within an Image object, it's position is specified relative to the inside of the Image object rather than relative to the edges of the game window, as was the case with the Game::create_triangle method. Since all primitive shapes and child Image objects are located within the container defined by the image object, if any portion of the triangle would fall outside of the Image object, the triangle won't be created. 
**Parameters:**
*int v1x:* The horizontal distance between the left edge of the parent Image object and the first vertex of the triangle in pixels. 
*int v1y:* The vertical distance between the bottom edge of the parent Image object and the first vertex of the triangle in pixels. 
*int v2x:* The horizontal distance between the left edge of the parent Image object and the second vertex of the triangle in pixels. 
*int v2y:* The vertical distance between the bottom edge of the parent Image object and the second vertex of the triangle in pixels. 
*int v3x:* The horizontal distance between the left edge of the parent Image object and the third vertex of the triangle in pixels. 
*int v3y:* The vertical distance between the bottom edge of the parent Image object and the third vertex of the triangle in pixels. 
*Color color:* The desired color of the circle.
**Returns** false if the object cannot be contained within the bounds of the parent Image object. In the is case, if the triangles (width + x) or (height + y) exceeds the height or width of the Image object respectively, false is returned.False is also returned if the specified radius is less than 1. Otherwise true is returned.

#### bool add_image(int x, int y, Image image)
**Description:** An existing Image object is added to the current Image object at a specified position. The Iamge object provided as a parameter becomes a child of this parent Iamge object, and behaves as a contained primtive object would.
**Parameters:**
*int x:* The horizontal distance between the left edge of the parent Image object and the left edge of the child Image object in pixels.
*int y:* The vertical distance between the bottom edge of the parent Image object and the bottom edge of the child Image object in pixels.  
*Image image:* The child Image object which will be inserted into this image object.
**Returns** True if the child Image object can be contained within the parent object and false otherwise.

#### void set\_color\_all(Color color)
**Description:** Sets the color of all shapes and child Image objects within the parent Image to be a specified color.
**Parameters:**
*color Color* The hop::Color which this image should be changed to.  

#### void move(int x, int y)
**Description:** Moves the Image object, and all contained shapes and child Images, by a specified number of horiztonal and vertical pixels
**Parameters:**
*int x:* The distance in the horizontal plane to move the Image object relative to it's current position. Positive values move the image right while negative values move it left.
*int y:* The distance in the vertical plane to move the Image object relative to it's current position. Positive values move the image up while negative values move it down.

## void flip()
**Description:** Flips the Image object horizntally, reflecting all component shapes and Images accross the horizontal mid-point line. 

## int get_x()
**Description:** Getter function for the x-position of the Image object. Tells the user where the Image is in the horizontal plane.
**Returns** The number of horizontal pixels between the left edge of the game window and the left edge of the Image. 
 
## int get_y()
**Description:** Getter function for the y-position of the Image object. Tells the user where the Image is in the vertical plane.
**Returns** The number of vertical pixels between the bottom edge of the game window and the bottom edge of the Image. 
 
## int get_width()
**Description:** Getter function for the width of the Image object. Tells the user how wide the Image object is.
**Returns** The width of the Image object in pixels.
 
## int get_height()
**Description:** Getter function for the height of the Image object. Tells the user how tall the Image object is.
**Returns** The height of the Image object in pixels.
____
## TextBox (class)
**Description:** The TextBox class displays a string of text in a described color at a certain place within the game window.

#### TextBox(int x, int y, int text\_size, Color text\_color, const char* text_string);
**Description:** The sole constructor for the TextBox object. 
**Parameters**
*int x:* The horizontal distance in pixels between the left edge of the TextBox and the left edge of the game window.
*int y:* The vertical distance in pixels between the bottom of the TextBox and the bottom of the game window.
*int text\_size:* The size of the text, which must be a positive integer. The base letter size is multipled by the text_size modifier.
*Color text\_color* The color of the text to be displayed. 
*const char* text_string* The content of the text to be displayed on screen.

#### void set_color(Color color)
**Description:** Change the color of all text within the TextBox to a specified color.
**Parameters:** 
*Color color:* The color that all text in the TextBox object will be changed to.

## Target Users and Scenarios

The target user for Hop Engine is an aspiring programmer with some experience with the C++ programming language. In the context of VIU, we hope our library would be accessible to a second-year computer science student. Such a user would likely be comfortable writing code for command-line applications, but may have little experience creating more complex development environments or using non-standard libraries. 

#### Scenario 1: Aspiring Game Developer 

Ronald is an avid gamer who enrolled in VIU's Diploma in Computer Science after completing secondary school in Nanaimo. Having successfully completed the first of two years in the Diploma program, Ronald is excited to complete his diploma and look for jobs in the game development industry. While he has excelled academically at VIU, Ronald knows the importance of building a portfolio to demonstrate his interest and competency in game development. Ronald has tried a few open-source game engine, but was unable to install the required dependancies and get his project to build. Having heard about Hop Engine from a classmate, Ronald clones the project from the VIU GIT server. He is excited to see that the project builds using the included Makefile and a blank window is immediately generated. Ronald sets out to build a simple 2d platformer game which he hopes to show prospective employers. 

#### Scenario 2: Non-Gamer Computer Science Student

Melinda is a fourth-year computer science student at VIU who is mid-way through her second-to-last semester at university. She has a strong interest in mathematics and is also working towards a math minor. While she has never been interested in playing or developing video games, she decided to take a computer graphics course (CSCI 405: Computer Graphics) and enjoys the complexity of rendering graphics. Finding herself with a bit of free time, Melinda decides to experiment with Hop Engine, a open-source graphics engine created by fellow VIU computer science students. While Melinda wouldn't invest much time in learning a fully-fledged game engine, she gives Hop Engine a try. It's simple to install and is written in C++, the language she is most comfortable using. She spends a few hours creating a simple game using pre-packaged image assets. Because Hop Engine is open-source, she also explores how the engine uses the Vulkan graphics pipeline to actually generate computer graphics.