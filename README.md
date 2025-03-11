# CS 230 Game Engine

## About the Project
CS230 is 3-credit course with the goal of building a 2D game engine for Windows using C language and DGL graphics library.

Engine features include:
- scene system
- entity management
- mesh component & library
- sprite component & library
- animation component
- behavior component (using state machines)
- physics component
- collider components (circle, line), collision detection & handling
- trace system
- basic math - Vector2D, Matrix2D, RNG

I used this project as an opportunity to refine and expand my skills with version control and build/test automation.
- I use CMake to generate my MSVC project with the necessary compiler flags and build my project in 2 configurations
- I use GoogleTest and RapidTest to generate unit and property-based tests for my engine
- I use Github for version control and Github Actions to build the project and run automated tests on push

## Project Structure
Here's what the project contains:
- **Assets**: Art assets for the project
- **Data**: Data files that get used by the engine to initialize stuff in the scenes
- **DGL**: Graphics library given by Doug. **There are two versions: DGL_d.lib (for Debug builds) and DGL.lib (for Release builds). When you build either configuration, the correct version will be linked.**
- **Scripts**: some build scripts for copying data files
- **Source**: all of the source files for the engine
- **Tests**: tests for each system in the engine
- **CMakeLists.txt**: This is the file that tells CMake how to generate the out-of-source VS build system. See below.

## Building The Project
Engine uses an out-of-source build system. It builds into 3 projects:
- EngineLib.lib - contains all engine and game functionality
- EngineStart.exe - starts the game
- EngineLibTests.exe - runs over 80 automated tests

The Assets, Data, and DGL library are copied into the output folder when the project is built.

To generate the out-of-source build system, navigate into the CS230 Project folder and open a Powershell window. Run this command:
```
cmake -S . -B Build
```

The project will be generated in the **Build** folder.

To build the project in Release configuration, run this command:
```
cmake --build Build --config Release
```
Project will be built in **bin/Release**.

To run tests on Release build (after building the project from the Build folder):
````
ctest --test-dir Build --build-config Release
````
