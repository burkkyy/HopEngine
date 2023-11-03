# Hop Engine
## Bunny Game Co.
Team Members:  
* Jake Mitton - jake.mitton@gmail.com  
* Azita Fariborz Saleh
* Caleb Burke
* Glen Beatty
* Indigo Stusek


## Design Overview  
Below is our context diagram, which describes how elements within our system interact with one-another. As the most complex subsystem, a data-flow diagram (DFD) for the graphics engine is provided in the logical design section.

*Figure 1: Context Diagram*

![Context Diagram](../Diagrams/graphics_engine_diagram_labeled.png)


## Logical Design  

 The Hop Engine is composed of the following components:  

### API  
Provides functions and classes that the user will use to create their game. The API is connected to the other components and the user in the following ways:  
* The API provides functions and classes used in window/context generation, playing sound, processing keyboard input, and loading images.  

* The API's functions and classes can be used by the user when developing a game using the Hop Engine.  

### Audio
Load audio files and allow users to play them. The sound is connected to the other components in the following ways:  

* The sound is played with help from the API.

### Input 
Process keyboard and mouse input from player and relay it to user. The input is connected to the other components in the following ways:  

* The mouse and keyboard input is processed with help from the API.  

### Window/Context Generation 

Create a valid window and rendering context on the user's system. Window/context generation is connected to the other components in the following ways:  

* The window/context generation is done with help from API functions/classes.  

* The window provides a space for the graphics engine to generate images/text. 

### Image Processing  

Load textures and other image assets so they are available to the user. Image loading is connected to the other components in the following ways:  

* Images are loaded with help from API functions/classes.

* The graphics engine displays the loaded images on screen. 

### Graphics Engine 

Render two-dimensional graphics by converting and relaying user code to the GPU. Used to generate images and text on screen according to the user's specifications. The graphics engine is connected to the other components in the following ways:  

* Graphics are displayed in a window.  

* Loaded images are displayed by the graphics engine.

---

Note 
  
A diagram which describes the components of the graphics engine and their relationship to one-another is shown in figure 2 below.

---

*Figure 2: Graphics Engine Diagram*

![Graphics Engine Diagram](../Diagrams/graphics_engine_diagram_labeled.png)

#### Graphics Engine Components
Below are brief descriptions of the components of our graphics engine and the function they perform.

* Renderer

* Swapchain

* Render System

* Pipeline

* Device

## Physical Design 

### Tools and Technologies
The Hop Engine will be developed using C++ with help from the Vulkan API as well as the following external libraries:

| Library  | Link  | License  | Function  |
|----	|----	|----	|----  |
| GLFW | https://www.glfw.org/ | zlib/libpng | * Interfaces with operating system to create the window in which graphics are rendered, and detects mouse and keyboard inputs from user. |
| Miniaudio | https://miniaud.io/  | MIT No Attribution | * Play audio files. |
| STB Image | https://github.com/nothings/stb | MIT License | * Loads image assets, which can then be rendered as textures. |
| FreeType | https://freetype.org/ | Freetype License | * Display text on screen |
| OpenGL Math Library (GLM) | https://github.com/g-truc/glm | MIT License | * Math library that provides objects and functions useful for rendering graphics, such as vectors and matrices.|

### Directory and File Structure
```c++
HopEngine                       //Root Directory
    Makefile
    main.cpp                    //Application entry point. Contains game contents
    assets                      //Root folder for all assets to be used in game
        audio                   //Directory contains audio files
        image                   //Directory contains image files, such as textures
    build                       //Build directory
        bin                     //Binary directory
            game.exe            //Executable containing completed game
        lib                     //Library directory
            libHopHopEngine.a   //Compiled static library for engine
        obj                     //Object file directory. Contains all compiled object files.
            device.o
            engine.o
            object_model.o
            pipeline.o
            swapchain.o
            window.o
            audio.o
            input.o
            main.o
    doc                         //Documentation folder. Contains documentation for engine.
            README.md           //High-level project documentation
                                //Quick-start instructions.
            design.md
            non-functional-requirements.md
            project-updates.md
            specifications.md
            design.md
            buildenv
                build.md
            git	
                git.md
            src
                Device.md
                Pipeline.md
                Swapchain.md
                Window.md
            standards
                Standards.md
    include                     //Folder contains API header file
        hop.hpp                 //Header file contains all classes and functions for user
    src                         //Root directory for all source engine source files and external libraries.
        Audio                   //Code necessary to play audio files
            audio.cpp
            audio.hpp
        Device                  //Code necessary to interface with GPU via virtual device
            device.cpp
            device.hpp
        Engine                  //Contains definitions for hop.hpp file, located in HopEngine/include.
            hop.cpp
        External                //Root directory for all included external libraries.
            miniaudio           //Library used to play audio files
            miniaudio.h         //In-line header file
            stb_image           //Library used to load image assets
            stb_image.h         //In-line header file
        Input                   //Code necessary to process user inputs
            input.cpp
            input.hpp
        Object_Model
            object_model.cpp
            object_model.hpp
        Pipeline
            pipeline.cpp
            pipeline.hpp
        Swapchain
            swapchain.cpp
            swapchain.hpp
        Utilities
            status_print.hpp
        Window                  //Code necessary to create window in user’s operating system
            window.cpp
            window.hpp

```

### Data Management
As our engine is geared towards the development of small games by beginner and intermediate programmers, data storage will be limited. Asset files, such as textures and sound files, will be stored in designated directories as described above. Otherwise, all data and instructions will be contained within project source files and will not persist once the application is closed. 

### Interfaces

In this section we have provided a summary of the public interfaces for each component of our project. Since our application is itself a library, public interfaces for each component take the form of C++ classes, functions, and data types.
#### API 
##### Defined in: HopEngine/include/hop.hpp
##### Function: Provides necessary functions and classes for user to build their game. 
##### Classes: 
- **Point:**
   - Description: A simple class containing an x and y coordinate, allowing positional data to be passed by value. 
    - Constructor:
        - Parameters:
            - `x_pos` (integer): The x coordinate of the point.
            - `y_pos` (integer): The y coordinate of the point.
    - Public variables.
        - `x` (integer): X component of point position.  
        - `y` (integer): y component of point position.
- **Game:**
    - Description: The game object is the central user-accessible class object used to generate the game window and provide other necessary services. Upon instantiation, validation checks are performed to determine if necessary services (such as graphics and audio support) are available.
    - Constructor:
        - Parameters:
            - `height` (integer): The vertical size of the game window.
            - `width` (integer): The horizontal size of the game window.
            - `title` (const char*): The title of the game window.
    - Public method: `run`
        - Description: After instantiating the Game object and setting desired parameters, the run method is called to launch the window and start the game loop.
        - Parameters: None
        - Returns: `Boolean` value. True if the game context was successfully created and false otherwise. 
  - Public method: `stop`
    - Description: Called to stop the existing game context. 
    - Parameters: None
    - Returns: Nothing.   
  - Public method: `is_running`
    - Description: Typically called at beginning of gameplay loop, is_running method tells the user whether the game window is still running.
    - Parameters: None
    - Returns: `Boolean` value. True if game is still running and false if it has stopped for some reason. 
  - Public method: `set_audio`
    - Description: Called to turn game audio on or off.
    - Parameters: `Boolean`. If set to true, game will play available audio. If set to false it will mute. 
    - Returns: Nothing.  
- **Block**
    - Description: Primitive graphics object to be displayed on screen. Renders a static, non-interactive rectangular image of a specified solid colour.  
     - Constructor:
        - Parameters:
            - `red` (short): Value of 0-255 determines red component of solid colour.
            - `green` (short): Value of 0-255 determines green component of solid colour.
            - `blue` (short): Value of 0-255 determines blue component of solid colour.
            - `height` (integer): The vertical size of the image.
            - `width` (integer): The horizontal size of the image.
            - `x_pos` (integer): The distance from the left edge of the window to the left edge of the image.
            - `y_pos` (integer): The distance from the bottom of the window to the bottom of the image. 
            - `z_pos` (integer): Positive integer between 1 and 5 which describes the depth layer in which the image resides. 1 Represents the absolute foreground while 5 represents the absolute background. 
    - Public method: `show`
        - Description: After instantiating the image object and setting desired parameters, the show method is called to display the image on the screen.
        - Parameters: None
        - Returns: `Boolean` value. True if the image was successfully displayed and false otherwise. 
  - Public method: `hide`
    - Description: Called to hide the image object.
    - Parameters: None
    - Returns: Nothing.   

- **Image**
    - Description: Primitive graphics object to be displayed on screen. Renders a provided texture of a specified size somewhere within the window.  
     - Constructor:
        - Parameters:
            - `texture_fn` (const char*): The name of the texture, located within the appropriate asset folder, to be projected upon the image.
            - `height` (integer): The vertical size of the image.
            - `width` (integer): The horizontal size of the image.
            - `x_pos` (integer): The distance from the left edge of the window to the left edge of the image.
            - `y_pos` (integer): The distance from the bottom of the window to the bottom of the image. 
            - `z_pos` (integer): Positive integer between 1 and 5 which describes the depth layer in which the image resides. 1 Represents the absolute foreground while 5 represents the absolute background. 
    - Public method: `show`
        - Description: After instantiating the image object and setting desired parameters, the show method is called to display the image on the screen.
        - Parameters: None
        - Returns: `Boolean` value. True if the image was successfully displayed and false otherwise. 
  - Public method: `hide`
    - Description: Called to hide the image object.
    - Parameters: None
    - Returns: Nothing.   

- **Sprite**
    - Description: A basic graphical object containing a texture. Unlike an image, a sprite cannot be directly rendered on the screen. Instead, it is later associated with another object (such as a character) upon which it is projected. 
     - Constructor:
        - Parameters:
            - `texture_fn` (const char*): The name of the texture, located within the appropriate asset folder.
            - `height` (integer): The vertical size of the texture.
            - `width` (integer): The horizontal size of the texture.

- **Character**
    - Description: A character that will exist in the user's game. Unlike Image and Block objects, a character is meant to be dynamic. It is displayed in the game window using one or more Sprite objects. By attaching multiple sprite objects to a character, animation is acheived. 
     - Constructor:
        - Parameters:
            - `height` (integer): The character's vertical size in pixels.
            - `width` (integer): The character's horizontal size in pixels. 
            - `x_pos` (integer): The intitial x position of the character.
            - `y_pos` (integer): The initial y position of the character. 
            - `z_pos` (integer): The depth position of the character expressed as an integer between 1 and 5. 1 Represents the absolute foreground while 5 represents the absolute background.
            - `num_sprites` (integer). The number of sprites necessary for the Character. A Character with more than one sprite can be animated. 
    - Public method `set_position`
        - Description: Change the position of a character.
        - Parameters:
            - `x_pos` (integer): The x-position of the character's new position.  
            - `y_pos` (integer): The y-position of the character's new position.
     - Public method `get_position`
        - Description: Get the position of the character.
        - Parameters: None.
        - Returns: `pos` (Point). A point object describing the character's position.
     - Public method `add_sprite`
        - Description: Add a sprite to the character.
        - Parameters: 
             - `sprite` (Sprite): The sprite.
             - `name` (const char*): The reference name of the sprite (eg: left).
        - Returns: A unique positive integer that is used to reference the sprite. -1 If the sprite was not successfully added.
     - Public method `set_sprite`
        - Description: Project a specified sprite upon the character by identifier. If one is already loaded, unload it first. 
        - Parameters: 
             - `id` (integer) The unique integer identifier that references the sprite to be applied. 
        - Returns: `Boolean`. True if sprite was successfully applied, and false otherwise. 

- **Title**
    - Description: A large-text title will be  displayed in the absolute foreground at a specified position. 
     - Constructor:
        - `text` (constchar*): The text to be displayed.
        - `x_pos` (integer): The distance in pixels from the left edge of the screen to the left edge of the textbox. 
        - `y_pos` (integer): The distance in pixels from the bottom of the screen to the bottom edge of the textbox. 
    - Public method `show`: 
        - Description: Show the textbox.
        - Returns: Nothing.
    - Public method `hide`: 
        - Description: Hide the textbox.
        - Returns: Nothing.
    - Public method `set_text`: 
        - Description: Apply a new text string to the textbox.
        - Parameters: text (const char*)
        - Returns: Nothing.

- **Device**

    - The `Device` directory will contain `device.cpp` and `device.hpp`.  

    - `device.hpp` will contain the structs `SCSD` for swapchain support details and `QFI` for que family indices.  

    - `device.hpp` will also contain a class `Device`, wherein the device is stored.  

    - Class `Device` will contain the following publicly callable functions:

        ```cpp  
        Device(Window&)
        ```
              
    _Constructor for the `Device` class_

    ##### Parameters  

    - `Window&` The GLFW generated window  

        ```cpp
        VkDevice get_device()
        ```

        _Gets the vulkan device_

    ##### Returns

    - Device in a `VkDevice` struct  

        ```cpp
        VkSurfaceKHR get_surface()
        ```

        _Gets the surface information_ 

    ##### Returns

    - Surface in a `VkSurfaceKHR` struct 

        ```cpp
        VkQueue get_graphics_que()
        ```

        _Gets the graphics que_ 

    ##### Returns

    - Graphics que in a `VkQueue` struct 

        ```cpp
        VkQueue get_present_que()
        ```

        _Gets the present que_

    ##### Returns

    - Present que in a `VkQueue` struct 

        ```cpp
        SCSD get_swapchain_support()
        ```

        _Gets swapchain support details_ 

    ##### Returns

    - Swapchain support details in a `SCSD` struct

        ```cpp
        QFI find_physical_que_families()
        ```

        _Finds physical que family indices_ 

    ##### Returns  

    - The physical que family indices in a `QFI` struct 
  
**Engine** 

- The `Engine` directory will contain `engine.cpp `and `engine.hpp`

- `engine.hpp` will contain a class `Engine`, wherein the engine is stored
  
    - Class `Engine` will contain the following publicly callable functions:

        ```cpp
        Engine()
        ```

        _Constructor for the `Engine` class_

        ```cpp
        void run()
        ```

        _Runs the engine_

**Pipeline**

- The `Pipeline` directory will contain `pipeline.cpp` and `pipeline.hpp`	
  
- `pipeline.hpp` will contain a class `Pipeline` wherein the pipeline is stored

    - Class `Pipeline` will contain the following publicly callable function:

        ```cpp
        Pipeline()
        ```

        _Constructor for the `Pipeline` class_

**SwapChain**

- The `Swapchain` directory will contain `swapchain.cpp` and `swapchain.hpp`

- `swapchain.hpp` will contain a class `SwapChain` wherein the swapchain is stored

    - Class `SwapChain` will contain the following publicly callable function:

        ```cpp
        SwapChain()
        ```

        _Constructor for the `SwapChain` class_

**Window**

- The `Window` directory will contain `window.cpp` and `window.hpp`

- `window.hpp` will contain a class `Window` wherein the GLFW generated window is stored

    - Class `Window` will contain the following publicly callable functions:

        ```cpp
        Window(int w, int h)
        ```

        _Constructor for the `Window` class_

    ##### Parameters  

    - `w` The width of the screen
    - `h` the height of the screen

            ```cpp
            bool should_close()
            ```

            _Checks if the window is closed or not_

    ##### Returns

    - Value of the close flag of the window

            ```cpp
            VkExtent2D get_extent()
            ```

            _Gets the dimensions of the window_ 

    ##### Returns

    - Width and height of the window in a `VkExtent2D` struct

            ```cpp
            void create_surface(VkInstance instance, VkSurfaceKHR* surface)
            ```

            _Creates a vulkan surface for a specific window_

    ##### Parameters

    - `instance` The vulkan instance

    - `surface` The handle for the surface
