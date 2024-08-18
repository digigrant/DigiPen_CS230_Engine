cmake_minimum_required(VERSION 3.28)
project(CS230_Project3
        VERSION 1.0
        DESCRIPTION "Project3 - Transformations"
        LANGUAGES CXX C)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the C standard to Legacy MSVC
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# set configuration types - Debug and Release - x64 only
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# get the architecture of the build machine
#if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#    set(ARCH "x64")
#else()
#    set(ARCH "Win32")
#endif()

# get configuration type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Debug)
    set(DGL_NAME DGL_d)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Release)
    set(DGL_NAME DGL)
endif()  

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/DGL/inc)
find_library(DGL_LIBRARY ${DGL_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/DGL/lib/x64")
message(STATUS "DGL Library: ${DGL_LIBRARY}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

add_executable(Project3 ${SOURCE_FILES})
target_link_libraries(Project3 ${DGL_LIBRARY})
target_include_directories(Project3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/DGL/inc)

# Project structure
file (GLOB ENGINE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Stub.*"
)
file(GLOB ENGINE_ENTITIES_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Entity.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/EntityFactory.*"
)
file(GLOB ENGINE_ENTITIES_COMPONENTS_GRAPHICS_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Animation.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Mesh.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Sprite.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/SpriteSource.*"
)
file(GLOB ENGINE_ENTITIES_COMPONENTS_PHYSICS_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Physics.*"
)
file(GLOB ENGINE_ENTITIES_COMPONENTS_TRANSFORM_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Transform.*"
)
file(GLOB ENGINE_FRAMEWORK_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Engine.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Matrix2D.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/stdafx.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Stream.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/targetver.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Trace.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Vector2D.*"
)
file(GLOB ENGINE_SYSTEMS_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/BaseSystem.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/StubSystem.*"
)
file(GLOB ENGINE_SYSTEMS_PLATFORM_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/PlatformSystem.*"
)
file(GLOB ENGINE_SYSTEMS_SCENE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Scene.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/SceneSystem.*"
)
file(GLOB GAME_SCENES_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/DemoScene.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Level1Scene.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/Level2Scene.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/SandboxScene.*"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/StubScene.*"
)
file(GLOB GAME_SYSTEMS_CHEAT_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/Source/CheatSystem.*"
)

# Add the files to the project
target_sources(Project3 PRIVATE
        ${ENGINE_FILES}
        ${ENGINE_ENTITIES_FILES}
        ${ENGINE_ENTITIES_COMPONENTS_GRAPHICS_FILES}
        ${ENGINE_ENTITIES_COMPONENTS_PHYSICS_FILES}
        ${ENGINE_ENTITIES_COMPONENTS_TRANSFORM_FILES}
        ${ENGINE_FRAMEWORK_FILES}
        ${ENGINE_SYSTEMS_FILES}
        ${ENGINE_SYSTEMS_PLATFORM_FILES}
        ${ENGINE_SYSTEMS_SCENE_FILES}
        ${GAME_SCENES_FILES}
        ${GAME_SYSTEMS_CHEAT_FILES}
)

# Group the files in the project
source_group("Engine" FILES ${ENGINE_FILES})
source_group("Engine\\Entities" FILES ${ENGINE_ENTITIES_FILES})
source_group("Engine\\Entities\\Components\\Graphics" FILES ${ENGINE_ENTITIES_COMPONENTS_GRAPHICS_FILES})
source_group("Engine\\Entities\\Components\\Physics" FILES ${ENGINE_ENTITIES_COMPONENTS_PHYSICS_FILES})
source_group("Engine\\Entities\\Components\\Transform" FILES ${ENGINE_ENTITIES_COMPONENTS_TRANSFORM_FILES})
source_group("Engine\\Framework" FILES ${ENGINE_FRAMEWORK_FILES})
source_group("Engine\\Systems" FILES ${ENGINE_SYSTEMS})
source_group("Engine\\Systems\\Platform" FILES ${ENGINE_SYSTEMS_PLATFORM_FILES})
source_group("Engine\\Systems\\Scene" FILES ${ENGINE_SYSTEMS_SCENE_FILES})
source_group("Game\\Scenes" FILES ${GAME_SCENES_FILES})
source_group("Game\\Systems\\Cheat" FILES ${GAME_SYSTEMS_CHEAT_FILES})

# Visual Studio specific settings
if(MSVC)
        # Set the startup project
        set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT Project3)
        
        # General properties
        # warning level 4, treat warnings as errors, SDL checks
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /sdl")
        # Debug - Debug information format = Program Database for Edit and Continue,  Just My Code
        # Release - Debug info format = Program Database
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI /JMC")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")

        # Optimization properties
        # Release - enable intrinsic functions, enable whole program optimization
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL")

        # Preprocessor definitions
        # Debug - _DEBUG, _CONSOLE
        # Release - NDEBUG, _CONSOLE
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG /D_CONSOLE")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DNDEBUG /D_CONSOLE")

        # Code Generation - Enable C++ exceptions, enable function-level linking
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /Gy")
        # Language - C++17, Conformance mode
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /permissive-")
        # Precompiled Headers - Create precompiled header file
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yu")
        # Advanced - Compile as C code, use full paths
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /TC /FC")
endif()