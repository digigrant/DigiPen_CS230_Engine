//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
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
#include "Level1Scene.h"
#include "Stream.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Mesh.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "DGL.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Physics.h"
#include "Entity.h"
#include "EntityFactory.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//static const DGL_Vec2 posMesh = { 0.0f, 0.0f };
//static const DGL_Vec2 scaleMesh = { 100.0f, 100.0f };

static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;

	Mesh* my_mesh;
	SpriteSource* my_sprite_source;
	Entity* my_entity;

} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);
static void Level1SceneMovementController(Entity* entity);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:
	0,	// numLives
	NULL, // my_mesh
	NULL, // my_sprite_source
	NULL // my_entity
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Level1Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{
	// Load the number of lives from the file
	Stream s = StreamOpen("Data/Level1_Lives.txt");
	if (s)
	{
		instance.numLives = StreamReadInt(s);
		StreamClose(&s);
	}

	// Create a mesh
	instance.my_mesh = MeshCreate();
	MeshBuildQuad(instance.my_mesh, 0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");

	// Create a sprite source
	instance.my_sprite_source = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.my_sprite_source, 1, 1, "PlanetTexture.png");
}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
	instance.my_entity = EntityFactoryBuild("./Data/PlanetJump.txt");

	if (instance.my_entity)
	{
		SpriteSetMesh(EntityGetSprite(instance.my_entity), instance.my_mesh);
		SpriteSetSpriteSource(EntityGetSprite(instance.my_entity), instance.my_sprite_source);
		SpriteSetFrame(EntityGetSprite(instance.my_entity), 0);
	}

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 1.0f, 1.0f, 1.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	Level1SceneMovementController(instance.my_entity);
	EntityUpdate(instance.my_entity, dt);

	if (DGL_Input_KeyDown('1'))
	{
		SceneRestart();
	}
	if (DGL_Input_KeyDown('2'))
	{
		SceneSystemSetNext(Level2SceneGetInstance());
	}
	if (DGL_Input_KeyDown('9'))
	{
		SceneSystemSetNext(SandboxSceneGetInstance());
	}
	if (DGL_Input_KeyDown('0'))
	{
		SceneSystemSetNext(DemoSceneGetInstance());
	}
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
	//DGL_Camera_SetPosition(&posCamera);

	EntityRender(instance.my_entity);
}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
	EntityFree(&instance.my_entity);
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	SpriteSourceFree(&instance.my_sprite_source);
	MeshFree(&instance.my_mesh);
}

static void Level1SceneMovementController(Entity* entity)
{
	// Get Transform
	Transform* transform = EntityGetTransform(entity);
	// Get Physics
	Physics* physics = EntityGetPhysics(entity);

	if (!transform || !physics) { return; }

	// Get the velocity
	Vector2D velocity = *(PhysicsGetVelocity(physics));

	// Get horizontal velocity
	if (DGL_Input_KeyDown(VK_LEFT))
	{
		velocity.x = -moveVelocity;
	}
	if (DGL_Input_KeyDown(VK_RIGHT))
	{
		velocity.x = moveVelocity;
	}
	if (!DGL_Input_KeyDown(VK_LEFT) && !DGL_Input_KeyDown(VK_RIGHT))
	{
		velocity.x = 0.0f;
	}

	// Check for jump
	if (DGL_Input_KeyTriggered(VK_UP))
	{
		velocity.y = jumpVelocity;
		PhysicsSetAcceleration(physics, &gravityNormal);
	}

	if (TransformGetTranslation(transform)->y < groundHeight)
	{
		TransformSetTranslation(transform, &(Vector2D) { TransformGetTranslation(transform)->x, groundHeight });
		velocity.y = 0.0f;
		PhysicsSetAcceleration(physics, &gravityNone);

		--instance.numLives;
		if (instance.numLives <= 0)
		{
			SceneSystemSetNext(Level2SceneGetInstance());
		}
	}

	// Set the velocity
	PhysicsSetVelocity(physics, &velocity);
}