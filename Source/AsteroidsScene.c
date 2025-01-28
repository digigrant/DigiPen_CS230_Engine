//------------------------------------------------------------------------------
//
// File Name:	AsteroidsScene.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "AsteroidsScene.h"
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

typedef struct AsteroidsScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	unsigned asteroidSpawnCount;

} AsteroidsScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void AsteroidsSceneLoad(void);
static void AsteroidsSceneInit(void);
static void AsteroidsSceneUpdate(float dt);
static void AsteroidsSceneExit(void);
static void AsteroidsSceneUnload(void);
static void AsteroidsSceneRender(void);
static void AsteroidsSceneSpawnAsteroidWave(void);
static void AsteroidsSceneSpawnAsteroid(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static AsteroidsScene instance =
{
	// Initialize the base structure:
	{ "Asteroids", AsteroidsSceneLoad, AsteroidsSceneInit, AsteroidsSceneUpdate, AsteroidsSceneRender, AsteroidsSceneExit, AsteroidsSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Asteroids Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* AsteroidsSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
void AsteroidsSceneLoad(void)
{
	ScoreSystemClear();
}

// Initialize the entities and variables used by the scene.
void AsteroidsSceneInit()
{
	Entity* ent_spaceship = EntityFactoryBuild("Spaceship");
	if (ent_spaceship) { SceneAddEntity(ent_spaceship); }

	Entity* ent_asteroids_score = EntityFactoryBuild("AsteroidsScore");
	if (ent_asteroids_score) { SceneAddEntity(ent_asteroids_score); }

	Entity* ent_asteroids_high_score = EntityFactoryBuild("AsteroidsHighScore");
	if (ent_asteroids_high_score) { SceneAddEntity(ent_asteroids_high_score); }

	Entity* ent_asteroids_wave = EntityFactoryBuild("AsteroidsWave");
	if (ent_asteroids_wave) { SceneAddEntity(ent_asteroids_wave); }

	ScoreSystemReset();
	instance.asteroidSpawnCount = ASTEROIDS_SPAWN_INITIAL;
	AsteroidsSceneSpawnAsteroidWave();

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void AsteroidsSceneUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (!SceneFindEntityByName("Asteroid"))
	{
		AsteroidsSceneSpawnAsteroidWave();
	}
}

// Render any objects associated with the scene.
void AsteroidsSceneRender(void)
{
}

// Free any objects associated with the scene.
void AsteroidsSceneExit()
{
}

// Unload any resources used by the scene.
void AsteroidsSceneUnload(void)
{
}

void AsteroidsSceneSpawnAsteroidWave()
{
	ScoreSystemIncreaseWave();

	for (unsigned int i = 0; i < instance.asteroidSpawnCount; ++i)
	{
		AsteroidsSceneSpawnAsteroid();
	}

	if (instance.asteroidSpawnCount < ASTEROIDS_SPAWN_MAX)
	{
		instance.asteroidSpawnCount++;
	}
}

void AsteroidsSceneSpawnAsteroid()
{
	Entity* ent_asteroid = EntityFactoryBuild("Asteroid");
	if (ent_asteroid)
	{
		SceneAddEntity(ent_asteroid);
	}
}