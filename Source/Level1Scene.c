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
#include "Animation.h"

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

enum MonkeyStates
{
	MonkeyIdle,
	MonkeyWalk,
	MonkeyJump,
	MonkeyInvalid = -1
};

static const float wallDistance = 462.0f;
static const float CheckSquareDistance = (75.0f * 75.0f);

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

	// Meshes
	Mesh* mesh1x1;
	Mesh* mesh3x3;
	Mesh* mesh16x8;

	// Mesh and SpriteSource for the planet
	Entity* ent_planet;
	SpriteSource* sprsrc_planet;

	// Mesh and SpriteSources for the monkey
	Entity* ent_monkey;
	SpriteSource* sprsrc_monkey_idle;
	SpriteSource* sprsrc_monkey_walk;
	SpriteSource* sprsrc_monkey_jump;

	// Mesh and SpriteSource for the lives display
	Entity* ent_lives;
	SpriteSource* sprsrc_lives;
	
	// Other data
	int numLives;
	char livesBuffer[16];
	enum MonkeyStates monkeyState;

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
static void Level1SceneSetMonkeyState(Entity* entity, enum MonkeyStates new_state);
static void Level1SceneBounceController(Entity* entity);
static bool Level1SceneIsColliding(const Entity* entityA, const Entity* entityB);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:

	// Meshes
	NULL,
	NULL,
	NULL,

	// Entity and SpriteSource for the planet
	NULL,
	NULL,

	// Entity and SpriteSources for the monkey
	NULL,
	NULL,
	NULL,
	NULL,

	// Entity and SpriteSource for the lives display
	NULL,
	NULL,

	// Other data
	-1,
	{ 0 },
	MonkeyInvalid
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

	// Create meshes
	instance.mesh1x1 = MeshCreate();
	MeshBuildQuad(instance.mesh1x1, 0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");
	instance.mesh3x3 = MeshCreate();
	MeshBuildQuad(instance.mesh3x3, 0.5f, 0.5f, 1.0f / 3, 1.0f / 3, "Mesh3x3");
	instance.mesh16x8 = MeshCreate();
	MeshBuildQuad(instance.mesh16x8, 0.5f, 0.5f, 1.0f / 16, 1.0f / 8, "Mesh16x8");

	// Create sprite sources
	instance.sprsrc_planet = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.sprsrc_planet, 1, 1, "PlanetTexture.png");
	instance.sprsrc_monkey_idle = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.sprsrc_monkey_idle, 1, 1, "MonkeyIdle.png");
	instance.sprsrc_monkey_walk = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.sprsrc_monkey_walk, 3, 3, "MonkeyWalk.png");
	instance.sprsrc_monkey_jump = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.sprsrc_monkey_jump, 1, 1, "MonkeyJump.png");
	instance.sprsrc_lives = SpriteSourceCreate();
	SpriteSourceLoadTexture(instance.sprsrc_lives, 16, 8, "Roboto_Mono_black.png");
}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
	// Create the planet entity
	instance.ent_planet = EntityFactoryBuild("PlanetBounce");
	if (instance.ent_planet)
	{
		SpriteSetMesh(EntityGetSprite(instance.ent_planet), instance.mesh1x1);
		SpriteSetSpriteSource(EntityGetSprite(instance.ent_planet), instance.sprsrc_planet);
		SpriteSetFrame(EntityGetSprite(instance.ent_planet), 0);
	}

	// Create the monkey entity
	instance.ent_monkey = EntityFactoryBuild("Monkey");
	if (instance.ent_monkey)
	{
		instance.monkeyState = MonkeyInvalid;
		Level1SceneSetMonkeyState(instance.ent_monkey, MonkeyIdle);
	}

	// Create the lives display entity
	instance.ent_lives = EntityFactoryBuild("MonkeyLivesText");
	if (instance.ent_lives)
	{
		Sprite* spr_lives = EntityGetSprite(instance.ent_lives);
		SpriteSetMesh(spr_lives, instance.mesh16x8);
		SpriteSetSpriteSource(spr_lives, instance.sprsrc_lives);
		sprintf_s(instance.livesBuffer, 16, "Lives: %d", instance.numLives);
		SpriteSetText(EntityGetSprite(instance.ent_lives), instance.livesBuffer);
	}

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 1.0f, 1.0f, 1.0f, 1.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	Level1SceneMovementController(instance.ent_monkey);
	Level1SceneBounceController(instance.ent_planet);
	EntityUpdate(instance.ent_monkey, dt);
	EntityUpdate(instance.ent_planet, dt);
	EntityUpdate(instance.ent_lives, dt);

	if (Level1SceneIsColliding(instance.ent_monkey, instance.ent_planet))
	{
		--instance.numLives;
		
		if (instance.numLives <= 0)
		{
			SceneSystemSetNext(Level2SceneGetInstance());
		}
		else
		{
			SceneRestart();
		}
	}
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
	EntityRender(instance.ent_planet);
	EntityRender(instance.ent_monkey);
	EntityRender(instance.ent_lives);
}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
	EntityFree(&instance.ent_planet);
	EntityFree(&instance.ent_monkey);
	EntityFree(&instance.ent_lives);
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	MeshFree(&instance.mesh1x1);
	MeshFree(&instance.mesh3x3);
	MeshFree(&instance.mesh16x8);
	SpriteSourceFree(&instance.sprsrc_planet);
	SpriteSourceFree(&instance.sprsrc_monkey_idle);
	SpriteSourceFree(&instance.sprsrc_monkey_walk);
	SpriteSourceFree(&instance.sprsrc_monkey_jump);
	SpriteSourceFree(&instance.sprsrc_lives);
}

static void Level1SceneMovementController(Entity* entity)
{
	Transform* transform = EntityGetTransform(entity);
	Physics* physics = EntityGetPhysics(entity);

	if (!transform || !physics) { return; }

	Vector2D velocity = *(PhysicsGetVelocity(physics));

	if (DGL_Input_KeyDown(VK_LEFT))
	{
		velocity.x = -moveVelocity;
		if (instance.monkeyState != MonkeyJump)
		{
			Level1SceneSetMonkeyState(entity, MonkeyWalk);
		}
	}
	if (DGL_Input_KeyDown(VK_RIGHT))
	{
		velocity.x = moveVelocity;
		if (instance.monkeyState != MonkeyJump)
		{
			Level1SceneSetMonkeyState(entity, MonkeyWalk);
		}
	}
	if (!DGL_Input_KeyDown(VK_LEFT) && !DGL_Input_KeyDown(VK_RIGHT))
	{
		velocity.x = 0.0f;
		if (instance.monkeyState != MonkeyJump)
		{
			Level1SceneSetMonkeyState(entity, MonkeyIdle);
		}
	}

	// Check for jump
	if (DGL_Input_KeyTriggered(VK_UP))
	{
		velocity.y = jumpVelocity;
		PhysicsSetAcceleration(physics, &gravityNormal);
		Level1SceneSetMonkeyState(entity, MonkeyJump);
	}

	if (TransformGetTranslation(transform)->y < groundHeight)
	{
		TransformSetTranslation(transform, &(Vector2D) { TransformGetTranslation(transform)->x, groundHeight });
		velocity.y = 0.0f;
		PhysicsSetAcceleration(physics, &gravityNone);
		Level1SceneSetMonkeyState(entity, MonkeyIdle);
	}

	PhysicsSetVelocity(physics, &velocity);
}

static void Level1SceneSetMonkeyState(Entity* entity, enum MonkeyStates new_state)
{
	if (instance.monkeyState == new_state) { return; }

	instance.monkeyState = new_state;

	Sprite* sprite = EntityGetSprite(entity);
	Animation* animation = EntityGetAnimation(entity);

	switch (new_state)
	{
	case MonkeyIdle:
		SpriteSetMesh(sprite, instance.mesh1x1);
		SpriteSetSpriteSource(sprite, instance.sprsrc_monkey_idle);
		AnimationPlay(animation, 1, 0.0f, false);
		break;

	case MonkeyWalk:
		SpriteSetMesh(sprite, instance.mesh3x3);
		SpriteSetSpriteSource(sprite, instance.sprsrc_monkey_walk);
		AnimationPlay(animation, 8, 0.05f, true);
		break;

	case MonkeyJump:
		SpriteSetMesh(sprite, instance.mesh1x1);
		SpriteSetSpriteSource(sprite, instance.sprsrc_monkey_jump);
		AnimationPlay(animation, 1, 0.0f, false);
		break;

	default:
		break;
	}
}

static void Level1SceneBounceController(Entity* entity)
{
	Transform* transform = EntityGetTransform(entity);
	Physics* physics = EntityGetPhysics(entity);

	if (!transform || !physics) { return; }

	Vector2D position = *(TransformGetTranslation(transform));
	Vector2D velocity = *(PhysicsGetVelocity(physics));

	if (position.x <= -wallDistance)
	{
		position.x = -wallDistance;
		velocity.x = -velocity.x;
	}
	else if (position.x >= wallDistance)
	{
		position.x = wallDistance;
		velocity.x = -velocity.x;
	}

	if (position.y < groundHeight)
	{
		position.y = groundHeight + (groundHeight - position.y);
		velocity.y = -velocity.y;
	}

	TransformSetTranslation(transform, &position);
	PhysicsSetVelocity(physics, &velocity);
}

static bool Level1SceneIsColliding(const Entity* entityA, const Entity* entityB)
{
	Transform* transformA = EntityGetTransform(entityA);
	Transform* transformB = EntityGetTransform(entityB);

	if (!transformA || !transformB) { return false; }

	const Vector2D* positionA = TransformGetTranslation(transformA);
	const Vector2D* positionB = TransformGetTranslation(transformB);

	float distanceSquared = Vector2DSquareDistance(positionA, positionB);

	return distanceSquared < CheckSquareDistance;
}