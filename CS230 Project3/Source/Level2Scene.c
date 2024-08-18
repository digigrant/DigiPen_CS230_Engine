//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.c
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
#include "Level2Scene.h"
#include "Level1Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Stream.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "DGL.h"
#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	Mesh* msh_spaceship;
	Entity* ent_spaceship;

} Level2Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static const float spaceship_speed = 500.0f;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level2SceneLoad(void);
static void Level2SceneInit(void);
static void Level2SceneUpdate(float dt);
static void Level2SceneExit(void);
static void Level2SceneUnload(void);
static void Level2SceneRender(void);
static void Level2SceneMovementController(Entity* entity);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level2Scene instance =
{
	// Initialize the base structure:
	{ "Level2", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
	0,	// numLives
	0	// numHealth
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level2Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level2SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level2SceneLoad(void)
{
	instance.msh_spaceship = MeshCreate();
	MeshBuildSpaceship(instance.msh_spaceship);
}

// Initialize the entities and variables used by the scene.
static void Level2SceneInit()
{
	instance.ent_spaceship = EntityFactoryBuild("./Data/SpaceshipHoming.txt");

	if (instance.ent_spaceship)
	{
		SpriteSetMesh(EntityGetSprite(instance.ent_spaceship), instance.msh_spaceship);
	}

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	Level2SceneMovementController(instance.ent_spaceship);
	EntityUpdate(instance.ent_spaceship, dt);

	if (DGL_Input_KeyDown('1'))
	{
		SceneSystemSetNext(Level1SceneGetInstance());
	}
	if (DGL_Input_KeyDown('2'))
	{
		SceneRestart();
	}
	if (DGL_Input_KeyDown('9'))
	{
		SceneSystemSetNext(SandboxSceneGetInstance());
	}
	if (DGL_Input_KeyDown('0'))
	{
		SceneSystemSetNext(DemoSceneGetInstance());
	}

	if (DGL_Input_KeyDown('Z'))
	{
		SpriteSetAlpha(EntityGetSprite(instance.ent_spaceship), 0.5f);
	}
	if (DGL_Input_KeyDown('X'))
	{
		SpriteSetAlpha(EntityGetSprite(instance.ent_spaceship), 1.0f);
	}
}

// Render any objects associated with the scene.
void Level2SceneRender(void)
{
	EntityRender(instance.ent_spaceship);
}

// Free any objects associated with the scene.
static void Level2SceneExit()
{
	EntityFree(&(instance.ent_spaceship));
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
	MeshFree(&(instance.msh_spaceship));
}

void Level2SceneMovementController(Entity* entity)
{
	// Get Transform
	Transform* transform = EntityGetTransform(entity);
	// Get Physics
	Physics* physics = EntityGetPhysics(entity);

	if (!transform || !physics) { return; }
	
	// Get mouse position
	DGL_Vec2 mouse_pos_screen = DGL_Input_GetMousePosition();
	DGL_Vec2 mouse_pos_world = DGL_Camera_ScreenCoordToWorld(&mouse_pos_screen);
	
	// Get normalized direction vector
	const Vector2D* translation = TransformGetTranslation(transform);
	Vector2D direction;
	Vector2DSub(&direction, &(Vector2D) { mouse_pos_world.x, mouse_pos_world.y }, translation);
	Vector2DNormalize(&direction, &direction);
	
	// Set rotation
	TransformSetRotation(transform, Vector2DToAngleRad(&direction));

	// Set velocity
	Vector2D new_velocity;
	Vector2DScale(&new_velocity, &direction, spaceship_speed);
	PhysicsSetVelocity(physics, &new_velocity);
}