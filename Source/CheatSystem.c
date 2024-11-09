//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 3
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>
#include "DGL.h"

#include "BaseSystem.h"
#include "CheatSystem.h"
#include "Scene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "AsteroidsScene.h"
#include "DemoScene.h"
#include "SandboxScene.h"
#include "SceneSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
typedef struct CheatSystemKeyBinding
{
	char key;
	const Scene* (*getInstance)(void);

} CheatSystemKeyBinding;

static const CheatSystemKeyBinding cheatSystemKeyBindings[] =
{
	{ '1', Level1SceneGetInstance },
	{ '2', Level2SceneGetInstance },
	{ '3', AsteroidsSceneGetInstance },
	{ '9', SandboxSceneGetInstance },
	{ '0', DemoSceneGetInstance }
};

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct CheatSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.

} CheatSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool CheatSystemInit(void);
static void CheatSystemUpdate(float dt);
static void CheatSystemRender(void);
static void CheatSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static CheatSystem instance =
{
	{ "CheatSystem", CheatSystemInit, CheatSystemUpdate, CheatSystemRender, CheatSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Cheat System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* CheatSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the Cheat System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool CheatSystemInit(void)
{
	// Return false if the system was NOT initialized successfully.

	// Return true if the system was initialized successfully.
	return true;
}

// Update the Cheat System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void CheatSystemUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	for (int i = 0; i < sizeof(cheatSystemKeyBindings) / sizeof(CheatSystemKeyBinding); ++i)
	{
		if (DGL_Input_KeyTriggered(cheatSystemKeyBindings[i].key))
		{
			SceneSystemSetNext(cheatSystemKeyBindings[i].getInstance());
		}
	}
}

// Render any objects associated with the Cheat System.
static void CheatSystemRender(void)
{
}

// Shutdown the Cheat System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void CheatSystemExit(void)
{
}

