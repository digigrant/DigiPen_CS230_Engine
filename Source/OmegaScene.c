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
#include "DGL.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "ScoreSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const unsigned ASTEROIDS_SPAWN_INITIAL = 8;
static const unsigned ASTEROIDS_SPAWN_MAX = 20;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct OmegaScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	unsigned asteroidSpawnCount;

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
static void OmegaSceneSpawnAsteroidWave(void);
static void OmegaSceneSpawnAsteroid(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static OmegaScene instance =
{
	// Initialize the base structure:
	{ "Omega", OmegaSceneLoad, OmegaSceneInit, OmegaSceneUpdate, OmegaSceneRender, OmegaSceneExit, OmegaSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Omega Scene.
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
void OmegaSceneLoad(void)
{
	ScoreSystemClear();
}

// Initialize the entities and variables used by the scene.
void OmegaSceneInit()
{
	Entity* ent_arena = EntityFactoryBuild("Arena");
	if (ent_arena) { SceneAddEntity(ent_arena); }

	Entity* ent_spaceship = EntityFactoryBuild("SpaceshipOmega");
	if (ent_spaceship) { SceneAddEntity(ent_spaceship); }

	Entity* ent_omega_score = EntityFactoryBuild("OmegaScore");
	if (ent_omega_score) { SceneAddEntity(ent_omega_score); }

	Entity* ent_omega_high_score = EntityFactoryBuild("OmegaHighScore");
	if (ent_omega_high_score) { SceneAddEntity(ent_omega_high_score); }

	Entity* ent_omega_wave = EntityFactoryBuild("OmegaWave");
	if (ent_omega_wave) { SceneAddEntity(ent_omega_wave); }

	ScoreSystemReset();
	instance.asteroidSpawnCount = ASTEROIDS_SPAWN_INITIAL;
	OmegaSceneSpawnAsteroidWave();

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void OmegaSceneUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (!SceneFindEntityByName("Asteroid"))
	{
		OmegaSceneSpawnAsteroidWave();
	}
}

// Render any objects associated with the scene.
void OmegaSceneRender(void)
{
}

// Free any objects associated with the scene.
void OmegaSceneExit()
{
}

// Unload any resources used by the scene.
void OmegaSceneUnload(void)
{
}

void OmegaSceneSpawnAsteroidWave()
{
	ScoreSystemIncreaseWave();

	for (unsigned int i = 0; i < instance.asteroidSpawnCount; ++i)
	{
		OmegaSceneSpawnAsteroid();
	}

	if (instance.asteroidSpawnCount < ASTEROIDS_SPAWN_MAX)
	{
		instance.asteroidSpawnCount++;
	}
}

void OmegaSceneSpawnAsteroid()
{
	Entity* ent_asteroid = EntityFactoryBuild("Asteroid");
	if (ent_asteroid)
	{
		SceneAddEntity(ent_asteroid);
	}
}