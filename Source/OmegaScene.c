//------------------------------------------------------------------------------
//
// File Name:	OmegaScene.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 6
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "OmegaScene.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct OmegaScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} OmegaScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void OmegaSceneLoad(void);
static void OmegaSceneInit(void);
static void OmegaSceneUpdate(float dt);
static void OmegaSceneExit(void);
static void OmegaSceneUnload(void);
static void OmegaSceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static OmegaScene instance =
{
	// Initialize the base structure:
	{ "Stub", OmegaSceneLoad, OmegaSceneInit, OmegaSceneUpdate, OmegaSceneRender, OmegaSceneExit, OmegaSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* OmegaSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void OmegaSceneLoad(void)
{
}

// Initialize the entities and variables used by the scene.
static void OmegaSceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void OmegaSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void OmegaSceneRender(void)
{
}

// Free any objects associated with the scene.
static void OmegaSceneExit()
{
}

// Unload any resources used by the scene.
static void OmegaSceneUnload(void)
{
}

