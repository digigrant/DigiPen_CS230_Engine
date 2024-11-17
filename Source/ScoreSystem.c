//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 5
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>

#include "BaseSystem.h"
#include "ScoreSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ScoreSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.

} ScoreSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool ScoreSystemInit(void);
static void ScoreSystemUpdate(float dt);
static void ScoreSystemRender(void);
static void ScoreSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static ScoreSystem instance =
{
	{ "ScoreSystem", ScoreSystemInit, ScoreSystemUpdate, ScoreSystemRender, ScoreSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub System.
// Returns:
//	 Pointer to the abstract BaseSystem for this derived System.
BaseSystem* ScoreSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

void ScoreSystemClear(void)
{
}

void ScoreSystemReset(void)
{
}

unsigned ScoreSystemGetValue(ScoreSystemId valueId)
{
	UNREFERENCED_PARAMETER(valueId);
	return 0;
}

void ScoreSystemIncreaseScore(unsigned amount)
{
	UNREFERENCED_PARAMETER(amount);
}

void ScoreSystemIncreaseWave(void)
{
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the Stub System.
// Returns:
//   Return "true" if the system was initialized successfully, otherwise return "false".
static bool ScoreSystemInit(void)
{
	// Return false if the system was NOT initialized successfully.

	// Return true if the system was initialized successfully.
	return true;
}

// Update the Stub System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void ScoreSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
}

// Render any objects associated with the Stub System.
static void ScoreSystemRender(void)
{
}

// Shutdown the Stub System.
//   (HINT: Free any allocated resources and/or close any opened files).
static void ScoreSystemExit(void)
{
}

