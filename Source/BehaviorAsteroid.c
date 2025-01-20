//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorAsteroid.h"
#include "Behavior.h"
#include "Random.h"
#include "Entity.h"
#include "Collider.h"
#include "Teleporter.h"
#include "DGL.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Physics.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

typedef enum
{
	ASTEROID_INVALID = -1,
	ASTEROID_IDLE
} AsteroidState;

typedef enum
{
	ASTEROID_ORIGIN_TOP_LEFT,
	ASTEROID_ORIGIN_TOP_RIGHT,
	ASTEROID_ORIGIN_BOTTOM_LEFT,
	ASTEROID_ORIGIN_BOTTOM_RIGHT,
	ASTEROID_ORIGIN_COUNT
} AsteroidOrigin;

static const float ASTEROID_SPEED_MIN = 50.0f;
static const float ASTEROID_SPEED_MAX = 100.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct BehaviorAsteroid
{
	Behavior base;
	AsteroidOrigin origin;
} BehaviorAsteroid;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BehaviorAsteroidOnInit(Behavior* behavior);
static void BehaviorAsteroidOnUpdate(Behavior* behavior, float dt);
static void BehaviorAsteroidOnExit(Behavior* behavior);
static void BehaviorAsteroidSetPosition(BehaviorAsteroid*);
static void BehaviorAsteroidSetVelocity(BehaviorAsteroid*);
static void BehaviorAsteroidCollisionHandler(Entity* asteroid, const Entity* other);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Behavior* BehaviorAsteroidCreate(void)
{
	BehaviorAsteroid* behavior = (BehaviorAsteroid*)calloc(1, sizeof(BehaviorAsteroid));
	if (!behavior) return NULL;

	behavior->base.stateCurr = ASTEROID_INVALID;
	behavior->base.memorySize = sizeof(BehaviorAsteroid);
	// behavior->origin = cAsteroidOriginTlc;
	behavior->base.onInit = BehaviorAsteroidOnInit;
	behavior->base.onUpdate = BehaviorAsteroidOnUpdate;
	behavior->base.onExit = BehaviorAsteroidOnExit;
	return (Behavior*)behavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void BehaviorAsteroidOnInit(Behavior* behavior)
{
	BehaviorAsteroid* asteroid = (BehaviorAsteroid*)behavior;

	// Set the initial state of the asteroid.
	if (asteroid->base.stateCurr == ASTEROID_IDLE)
	{
		asteroid->origin = (AsteroidOrigin)RandomRange(0, ASTEROID_ORIGIN_COUNT - 1);
		BehaviorAsteroidSetPosition(asteroid);
		BehaviorAsteroidSetVelocity(asteroid);

		Collider* collider = EntityGetCollider(asteroid->base.parent);
		if (collider)
		{
			ColliderSetCollisionHandler(collider, BehaviorAsteroidCollisionHandler);
		}
	}
}

void BehaviorAsteroidOnUpdate(Behavior* behavior, float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (!behavior) return;
	TeleporterUpdateEntity(behavior->parent);
}

void BehaviorAsteroidOnExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}

void BehaviorAsteroidSetPosition(BehaviorAsteroid* behavior)
{
	if (!behavior) return;

	Entity* entity = behavior->base.parent;
	if (!entity) return;

	Transform* transform = EntityGetTransform(entity);
	if (!transform) return;

	Vector2D window_size = DGL_Window_GetSize();
	Vector2D window_half_size;
	Vector2DScale(&window_half_size, &window_size, 0.5f);

	Vector2D position = { 0.0f, 0.0f };

	// Set the position of the asteroid based on the origin.
	switch (behavior->origin)
	{
	case ASTEROID_ORIGIN_TOP_LEFT:
		Vector2DSet(&position, -window_half_size.x, window_half_size.y);
		break;
	case ASTEROID_ORIGIN_TOP_RIGHT:
		Vector2DSet(&position, window_half_size.x, window_half_size.y);
		break;
	case ASTEROID_ORIGIN_BOTTOM_LEFT:
		Vector2DSet(&position, -window_half_size.x, -window_half_size.y);
		break;
	case ASTEROID_ORIGIN_BOTTOM_RIGHT:
		Vector2DSet(&position, window_half_size.x, -window_half_size.y);
		break;
	}

	TransformSetTranslation(transform, &position);
}

void BehaviorAsteroidSetVelocity(BehaviorAsteroid* behavior)
{
	if (!behavior) return;

	Entity* entity = behavior->base.parent;
	if (!entity) return;

	Physics* physics = EntityGetPhysics(entity);
	if (!physics) return;

	float angle_deg = 0.0f;
	float speed = RandomRangeFloat(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX);
	Vector2D velocity = { 0.0f, 0.0f };

	// Set the velocity of the asteroid based on the origin.
	switch (behavior->origin)
	{
	case ASTEROID_ORIGIN_TOP_LEFT:
		angle_deg = RandomRangeFloat(-10.0f, -80.0f);
		break;
	case ASTEROID_ORIGIN_TOP_RIGHT:
		angle_deg = RandomRangeFloat(-100.0f, -170.0f);
		break;
	case ASTEROID_ORIGIN_BOTTOM_LEFT:
		angle_deg = RandomRangeFloat(10.0f, 80.0f);
		break;
	case ASTEROID_ORIGIN_BOTTOM_RIGHT:
		angle_deg = RandomRangeFloat(100.0f, 170.0f);
		break;
	}

	Vector2DFromAngleDeg(&velocity, angle_deg);
	Vector2DScale(&velocity, &velocity, speed);

	PhysicsSetVelocity(physics, &velocity);
}

void BehaviorAsteroidCollisionHandler(Entity* asteroid, const Entity* other)
{
	if (!asteroid || !other) return;
	// add points to the board
	if (strcmp(EntityGetName(other), "Bullet") == 0)
	{
		EntityDestroy(asteroid);
	}
}