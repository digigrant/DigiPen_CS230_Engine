# CS 230 Project 3 - Transformations

## Objectives
The objectives for this project are four-fold:
- To implement your own Matrix2D module.
- To calculate transformations for sprite positioning, scaling, and rotation.
- To implement displaying of sprite text.
- Implement a “cheat” system for controlling transitions between scenes.

## About the Project
### CS 230 Project3
This is the working directory for the project. Here's what it contains:
- **Assets**: Art assets for the project
- **Data**: Data files that get used by the engine to initialize stuff in the scenes
- **DGL**: Graphics library given by Doug. **There are two versions: DGL_d.lib (for Debug builds) and DGL.lib (for Release builds). When you build either configuration, the correct version needs to be linked.** Currently, building with CMake is hard-coded for the Release version to be linked - if you try to build Debug config, you will get a linker error.
- **Source**: All of the source files for the engine. This includes Project 3 source files given by Doug, source files copied from Project 2, and some empty source files created for the Project 3 implementations. Everything needed to build the project is in there now.
- **CMakeLists.txt**: This is the file that tells CMake how to generate the out-of-source VS build system. See *Building The Project (CMake Method)*.
- **Project3.sln**: This, along with **Project3.vcxproj** and **Project3.vcxproj.filters**, are the default VS project files you get for CS 230. You can open these in VS and build the project successfully - see *Building The Project (Normal Method)*.
- **Project3-Trasnformations.docx**: Guide for Project 3.

#### Building The Project (Normal Method)
For CS 230, the project build system is in-source. You build with the **Project3.sln** in the CS230 Project3 directory. When you open the .sln with Visual Studio, you can build the project in Debug/Release configurations and for x86/x64 architectures. The project will compile and link successfully and you will see a window open with a spaceship following the mouse. (Project3 has not been implemented yet.)

#### Building The Project (CMake Method - under construction)
My goal is to create an out-of-source build system using CMake and implement automated testing using Google Test.
To generate the out-of-source build system, navigate into the CS230 Project folder and create a "Build" folder. Navigate into the Build folder and open a Powershell window. Run this command:
```
cmake ..
```

The CMakeLists.txt file in the *CS230 Project3* directory will generate a MSVC build system into the Build folder. The build system will have Debug/Release configurations, only in x64 architecture. (My understanding is that CMake does not support multiple architectures for one build system.) If you open the .sln in Visual Studio, you will see the Project3 project with the folder structure as the one in the normal .sln. There are some improvements that need to be made:
- Compiler flags: in the Solution Window, right-click Project3 -> Properties. You will notice the compiler flags are not being set to the ones that are being set in the CMakeLists.txt file.
- Multiple Architectures: I would like to be able to build the project for x86 architectures as well as x64. The internet says CMake can't do it, but I'm sure there must be a way.
- Probably other improvements I havent detected yet

To build the project, in the Build folder, run this command:
```
cmake --build . --config <whatever config you're trying to build>
```
Example:
```
cmake --build . --config Release
```
Currently this wont work.
- Debug: You will get a linker error. The project is not linking to the DGL Debug library - DGL_d.lib
- Release: You will get a different linker error. The project is not finding some function. Currently I'm working on this to just get the Release build working.

### CS230 Project3.zip
This is the initial zip file you get for the project. In this zip, Source contains only some (*not all!*) of the source files for the project. Many of the missing source files are meant to be copied over from Project 2. A few .c files need to be created yourself to get the project in a state where it can compile.

### CS230 Project3 (Demo).zip
This is an example of a working, completed Project3.

## TODO
1. Get the CMake build system to build in Release - fix the linker error
2. Get the CMake build system to build in Debug, too - make it so the project links to the correct version of DGL.lib based on configration
3. Get CMake to configure the VS project with the correct compiler flags when building in Visual Studio
4. Implement Google Test - either integrate Google Tests directly into the built executable, or reorganize the project to build into static libraries that can be tested
5. Implement Github Actions - build the project and run automated tests when you push to dev branch
6. Implement Project 3
