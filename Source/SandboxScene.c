//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 1
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "SandboxScene.h"
#include "Stream.h"
#include "Trace.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SandboxScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} SandboxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SandboxSceneLoad(void);
static void SandboxSceneInit(void);
static void SandboxSceneUpdate(float dt);
static void SandboxSceneExit(void);
static void SandboxSceneUnload(void);
static void SandboxSceneRender(void);
static void SandboxSceneTraceFloat(const char* text, float f);
static void SandboxSceneTraceVector(const char* text, const Vector2D* v);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SandboxScene instance =
{
	// Initialize the base structure:
	{ "Sandbox", SandboxSceneLoad, SandboxSceneInit, SandboxSceneUpdate, SandboxSceneRender, SandboxSceneExit, SandboxSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the SandboxScene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* SandboxSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void SandboxSceneLoad(void)
{
}

// Initialize the entities and variables used by the scene.
static void SandboxSceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandboxSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	Stream stream = StreamOpen("Data/VectorTests.txt");

	if (stream)
	{
		// Create vector to use for tests
		// Set it to (-1.0f, -1.0f) since the first test will zero it out
		Vector2D vec = { -1.0f, -1.0f };

		Vector2DZero(&vec);
		SandboxSceneTraceVector("Vector2DZero", &vec);

		Vector2DSet(&vec, 1.5f, 1.0f);
		SandboxSceneTraceVector("Vector2DSet", &vec);

		Vector2DNeg(&vec, &vec);
		SandboxSceneTraceVector("Vector2DNeg", &vec);

		Vector2DAdd(&vec, &vec, &vec);
		SandboxSceneTraceVector("Vector2DAdd", &vec);

		Vector2DSub(&vec, &vec, &vec);
		SandboxSceneTraceVector("Vector2DSub", &vec);

		StreamReadVector2D(stream, &vec);
		SandboxSceneTraceVector("StreamReadVector2D", &vec);

		Vector2DNormalize(&vec, &vec);
		SandboxSceneTraceVector("Vector2DNormalize", &vec);

		// Read a float from the stream and use it to scale the vector
		float f = StreamReadFloat(stream);
		SandboxSceneTraceFloat("StreamReadFloat", f);

		Vector2DScale(&vec, &vec, f);
		SandboxSceneTraceVector("Vector2DScale", &vec);

		Vector2DScaleAdd(&vec, &vec, f, &vec);
		SandboxSceneTraceVector("Vector2DScaleAdd", &vec);

		Vector2DScaleSub(&vec, &vec, f, &vec);
		SandboxSceneTraceVector("Vector2DScaleSub", &vec);

		f = Vector2DLength(&vec);
		SandboxSceneTraceFloat("Vector2DLength", f);

		f = Vector2DSquareLength(&vec);
		SandboxSceneTraceFloat("Vector2DSquareLength", f);

		// Create a second vector to use for tests and initialize both from file
		Vector2D vec2 = { 0.0f, 0.0f };
		StreamReadVector2D(stream, &vec);
		SandboxSceneTraceVector("StreamReadVector2D", &vec);
		StreamReadVector2D(stream, &vec2);
		SandboxSceneTraceVector("StreamReadVector2D", &vec2);

		f = Vector2DDistance(&vec, &vec2);
		SandboxSceneTraceFloat("Vector2DDistance", f);

		f = Vector2DSquareDistance(&vec, &vec2);
		SandboxSceneTraceFloat("Vector2DSquareDistance", f);

		f = Vector2DDotProduct(&vec, &vec2);
		SandboxSceneTraceFloat("Vector2DDotProduct", f);

		// Read a float from the stream and calculate the angle in degrees
		f = StreamReadFloat(stream);
		SandboxSceneTraceFloat("StreamReadFloat", f);
		Vector2DFromAngleDeg(&vec, f);
		SandboxSceneTraceVector("Vector2DFromAngleDeg", &vec);

		// Read a float from the stream and calculate the angle in radians
		f = StreamReadFloat(stream);
		SandboxSceneTraceFloat("StreamReadFloat", f);
		Vector2DFromAngleRad(&vec, f);
		SandboxSceneTraceVector("Vector2DFromAngleRad", &vec);

		Vector2DToAngleRad(&vec);
		SandboxSceneTraceFloat("Vector2DToAngleRad", f);
	}

	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void SandboxSceneRender(void)
{
}

// Free any objects associated with the scene.
static void SandboxSceneExit()
{
}

// Unload any resources used by the scene.
static void SandboxSceneUnload(void)
{
}

static void SandboxSceneTraceFloat(const char* text, float f)
{
	TraceMessage("Vector Test: %s = %f", text, f);
}

static void SandboxSceneTraceVector(const char* text, const Vector2D* v)
{
	TraceMessage("Vector Test: %s = [%f, %f]", text, v->x, v->y);
}