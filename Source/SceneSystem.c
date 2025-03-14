//------------------------------------------------------------------------------
//
// File Name:	SceneSystem.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S24
//
// Copyright � 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>
#include <assert.h>

#include "BaseSystem.h"
#include "OmegaScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "StubScene.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Libraries
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

typedef struct Scene Scene;

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SceneSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.
	const Scene* activeScene;
	const Scene* nextScene;
	bool isRestarting;

} SceneSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool SceneSystemInit(void);
static void SceneSystemUpdate(float dt);
static void SceneSystemRender(void);
static void SceneSystemExit(void);

static bool SceneSystemIsChanging(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SceneSystem instance =
{
	{ "SceneSystem", SceneSystemInit, SceneSystemUpdate, SceneSystemRender, SceneSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Scene System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* SceneSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

// Check if the Scene System is still running (a scene is active).
// Returns:
//   bool	True is a scene is active, false otherwise.
bool SceneSystemIsRunning(void)
{
	return (instance.activeScene || instance.nextScene);
}

// Instruct the Scene System to restart the active scene.
void SceneSystemRestart(void)
{
	instance.isRestarting = true;
}

// Set a new active scene, replacing any existing active scene.
// Params:
//   scene	Pointer to the new scene.
void SceneSystemSetNext(const Scene* scene)
{
	if (scene)
	{
		assert(SceneIsValid(scene) && "SceneSystemSetNext Error: A scene is missing one or more functions.");
	}

	if (scene == instance.activeScene)
	{
		SceneSystemRestart();
		return;
	}

	instance.nextScene = scene;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the Scene System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool SceneSystemInit(void)
{
	// Set the starting (Default) scene.
	// TODO: Change the starting (Default) scene from "Stub" to "Demo":
	SceneSystemSetNext(OmegaSceneGetInstance());

	return true;
}

// Update the Scene System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SceneSystemUpdate(float dt)
{
	// Check for a scene change.
	if (SceneSystemIsChanging())
	{
		// Exit the current scene.
		SceneExit(instance.activeScene);

		// TODO: Add support for Load and Unload.
		
		// If the system is restarting, do not change the scene
		if (instance.isRestarting)
		{
			instance.isRestarting = false;
		}
		// Otherwise, unload the current scene and load the new scene
		else
		{
			// Unload the current scene
			SceneUnload(instance.activeScene);

			// Change the active scene
			instance.activeScene = instance.nextScene;

			// Load the new scene
			SceneLoad(instance.activeScene);
		}

		// Initialize the new scene.
		SceneInit(instance.activeScene);
	}

	// Update the active scene.
	SceneUpdate(instance.activeScene, dt);
}

// Render any objects associated with the Scene system.
static void SceneSystemRender(void)
{
	// Render the active scene.
	SceneRender(instance.activeScene);
}

// Shutdown the Scene System.
//   (HINT: Free any allocated resources and/or opened files).
static void SceneSystemExit(void)
{
}

// Check if it is time to change scenes or restart the existing scene.
// Returns:
//   Returns "true" if a change request has been received, otherwise returns "false".
static bool SceneSystemIsChanging(void)
{
	return (instance.isRestarting || (instance.activeScene != instance.nextScene));
}

