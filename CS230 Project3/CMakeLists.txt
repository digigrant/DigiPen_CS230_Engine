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

# Set the output directories for the build configurations
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Debug")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Release")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/Release")

add_executable(Project3 ${SOURCE_FILES})
target_include_directories(Project3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/DGL/inc)

# Link the DGL library for the appropriate configuration
set(DGL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/DGL/lib/x64")
find_library(DGL_LIB_DEBUG DGL_d HINTS "${DGL_PATH}")
find_library(DGL_LIB_RELEASE DGL HINTS "${DGL_PATH}")
target_link_libraries(Project3
        debug ${DGL_LIB_DEBUG}
        optimized ${DGL_LIB_RELEASE}
)

# Run script to copy DGL library, Assets, and Data to the output directory
set(COPY_FILES_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/CopyFiles.bat")
add_custom_command(TARGET Project3 POST_BUILD
        COMMAND ${COPY_FILES_SCRIPT} $<$<CONFIG:DEBUG>:Debug> $<$<CONFIG:RELEASE>:Release>
)

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
source_group("Engine\\Systems" FILES ${ENGINE_SYSTEMS_FILES})
source_group("Engine\\Systems\\Platform" FILES ${ENGINE_SYSTEMS_PLATFORM_FILES})
source_group("Engine\\Systems\\Scene" FILES ${ENGINE_SYSTEMS_SCENE_FILES})
source_group("Game\\Scenes" FILES ${GAME_SCENES_FILES})
source_group("Game\\Systems\\Cheat" FILES ${GAME_SYSTEMS_CHEAT_FILES})

# Visual Studio specific settings
if(MSVC)
        # Set the startup project
        set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Project3)

        # Set the working directory
        set_target_properties(Project3 PROPERTIES
                VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
        )
        
        # General properties
        # warning level 4, treat warnings as errors, SDL checks
        target_compile_options(Project3 PRIVATE /W4 /WX /sdl)
        # Debug - Debug information format = Program Database for Edit and Continue,  Just My Code
        # Release - Debug info format = Program Database
        target_compile_options(Project3 PRIVATE
                $<$<CONFIG:DEBUG>:/ZI /JMC>
                $<$<CONFIG:RELEASE>:/Zi>
        )

        # Optimization properties
        # Release - enable intrinsic functions, enable whole program optimization
        target_compile_options(Project3 PRIVATE
                $<$<CONFIG:RELEASE>:/Oi /GL>
        )

        # Preprocessor definitions
        # Debug - _DEBUG, _CONSOLE
        # Release - NDEBUG, _CONSOLE
        target_compile_options(Project3 PRIVATE
                $<$<CONFIG:DEBUG>:/D_DEBUG /D_CONSOLE>
                $<$<CONFIG:RELEASE>:/DNDEBUG /D_CONSOLE>
        )

        # Code Generation - Enable C++ exceptions, enable function-level linking
        target_compile_options(Project3 PRIVATE /EHsc /Gy)
        # Language - C++17, Conformance mode
        target_compile_options(Project3 PRIVATE /std:c++17 /permissive-)
        # Precompiled Headers - Use precompiled header file
        file(GLOB PCH_SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Source/stdafx.c")
        set(PCH_HEADER_NAME "stdafx.h")
        set(PCH_OUTPUT_DEBUG "${CMAKE_BINARY_DIR}/Project3.dir/Debug/Project3.pch")
        set(PCH_OUTPUT_RELEASE "${CMAKE_BINARY_DIR}/Project3.dir/Release/Project3.pch")
        target_compile_options(Project3 PRIVATE /Yu${PCH_HEADER_NAME}
                /Fp$<$<CONFIG:DEBUG>:${PCH_OUTPUT_DEBUG}>$<$<CONFIG:RELEASE>:${PCH_OUTPUT_RELEASE}>
        )
        set_source_files_properties(${PCH_SOURCE_FILE} PROPERTIES COMPILE_OPTIONS /Yc${PCH_HEADER_NAME})
        # Advanced - Compile as C code, use full paths
        target_compile_options(Project3 PRIVATE /TC /FC)

        # Linker general properties - SubSystem = Windows
        target_link_options(Project3 PRIVATE /SUBSYSTEM:WINDOWS)
        # Debugging properties - Generate debug information
        target_link_options(Project3 PRIVATE /DEBUG)
        # Optimization properties
        # Release - Enable references, enable COMDAT folding, fast link time code generation
        target_link_options(Project3 PRIVATE
                $<$<CONFIG:RELEASE>:/OPT:REF /OPT:ICF /LTCG:incremental>
        )
endif()