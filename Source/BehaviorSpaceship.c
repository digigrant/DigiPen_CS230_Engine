//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorSpaceship.h"
#include "Behavior.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Transform.h"
#include "Physics.h"
#include "Vector2D.h"
#include "DGL.h"
#include "Scene.h"
#include "Teleporter.h"
#include "Collider.h"
#include "Sprite.h"

#define _USE_MATH_DEFINES
#include <math.h>

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

typedef enum
{
	SPACESHIP_INVALID = -1,
	SPACESHIP_IDLE,
	SPACESHIP_THRUST,
	SPACESHIP_DEAD
} SpaceshipState;

static const float SPACESHIP_ACCELERATION = 150.0f;
static const float SPACESHIP_SPEED_MAX = 500.0f;
static const float SPACESHIP_TURN_RATE_MAX = (float)(M_PI) / 1.5f;
static const float SPACESHIP_WEAPON_COOLDOWN_TIME = 0.25f;
static const float SPACESHIP_WEAPON_BULLET_SPEED = 750.0f;
static const float SPACESHIP_DEATH_DURATION = 3.0f;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void BehaviorSpaceshipOnInit(Behavior* behavior);
static void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt);
static void BehaviorSpaceshipOnExit(Behavior* behavior);
static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt);
static void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt);
static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt);
static void BehaviorSpaceshipSpawnBullet(Behavior* behavior);
static void BehaviorSpaceshipCollisionHandler(Entity* spaceship, Entity* other);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
Behavior* BehaviorSpaceshipCreate(void)
{
	Behavior* behavior = (Behavior*)calloc(1, sizeof(Behavior));

	if (!behavior) return NULL;

	behavior->memorySize = sizeof(Behavior);
	behavior->stateCurr = SPACESHIP_INVALID;
	behavior->stateNext = SPACESHIP_INVALID;
	behavior->onInit = BehaviorSpaceshipOnInit;
	behavior->onUpdate = BehaviorSpaceshipOnUpdate;
	behavior->onExit = BehaviorSpaceshipOnExit;

	return behavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void BehaviorSpaceshipOnInit(Behavior* behavior)
{
	if (!behavior) return;

	if (behavior->stateCurr == SPACESHIP_IDLE)
	{
		Collider* collider = EntityGetCollider(behavior->parent);
		if (collider)
		{
			ColliderSetCollisionHandler(collider, BehaviorSpaceshipCollisionHandler);
		}
	}
	else if (behavior->stateCurr == SPACESHIP_DEAD)
	{
		behavior->timer = SPACESHIP_DEATH_DURATION;
		// do something jere
	}
}

void BehaviorSpaceshipOnUpdate(Behavior* behavior, float dt)
{
	if (!behavior) return;

	switch (behavior->stateCurr)
	{
	case SPACESHIP_IDLE:
	{
		BehaviorSpaceshipUpdateRotation(behavior, dt);
		BehaviorSpaceshipUpdateWeapon(behavior, dt);

		if (DGL_Input_KeyDown(VK_UP))
		{
			behavior->stateNext = SPACESHIP_THRUST;
		}
		break;
	}

	case SPACESHIP_THRUST:
	{
		BehaviorSpaceshipUpdateRotation(behavior, dt);
		BehaviorSpaceshipUpdateWeapon(behavior, dt);
		BehaviorSpaceshipUpdateVelocity(behavior, dt);

		if (!DGL_Input_KeyDown(VK_UP))
		{
			behavior->stateNext = SPACESHIP_IDLE;
		}
		break;
	}

	case SPACESHIP_DEAD:
	{
		behavior->timer -= dt;

		if (behavior->timer <= 0.0f) { SceneRestart(); }

		SpriteSetAlpha(EntityGetSprite(behavior->parent), behavior->timer / SPACESHIP_DEATH_DURATION);
		TransformSetRotation(EntityGetTransform(behavior->parent), TransformGetRotation(EntityGetTransform(behavior->parent)) + (dt * 5.0f));

		break;
	}

	default:
		break;
	}

	TeleporterUpdateEntity(behavior->parent);
}

void BehaviorSpaceshipOnExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}

void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (!behavior) return;

	Physics* physics = EntityGetPhysics(behavior->parent);

	if (DGL_Input_KeyDown(VK_LEFT))
	{
		PhysicsSetRotationalVelocity(physics, SPACESHIP_TURN_RATE_MAX);
	}
	else if (DGL_Input_KeyDown(VK_RIGHT))
	{
		PhysicsSetRotationalVelocity(physics, -SPACESHIP_TURN_RATE_MAX);
	}
	else
	{
		PhysicsSetRotationalVelocity(physics, 0.0f);
	}
}

void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt)
{
	if (!behavior) return;

	Transform* transform = EntityGetTransform(behavior->parent);
	Physics* physics = EntityGetPhysics(behavior->parent);

	if (!transform || !physics) return;

	// calculate new velocity vector
	Vector2D direction, new_velocity;
	float rotation = TransformGetRotation(transform);
	Vector2DFromAngleRad(&direction, rotation);
	const Vector2D* velocity = PhysicsGetVelocity(physics);
	Vector2DScaleAdd(&new_velocity, &direction, SPACESHIP_ACCELERATION * dt, velocity);

	// limit speed if needed
	float speed = Vector2DLength(&new_velocity);
	if (speed > SPACESHIP_SPEED_MAX)
	{
		Vector2DNormalize(&new_velocity, &new_velocity);
		Vector2DScale(&new_velocity, &new_velocity, SPACESHIP_SPEED_MAX);
	}

	PhysicsSetVelocity(physics, &new_velocity);
}

void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt)
{
	if (!behavior) return;

	if (behavior->timer > 0.0f) { behavior->timer -= dt; } // decrement

	if (behavior->timer < 0.0f) { behavior->timer = 0.0f; } // clamp

	if (DGL_Input_KeyDown(VK_SPACE) && behavior->timer <= 0.0f)
	{
		BehaviorSpaceshipSpawnBullet(behavior);
		behavior->timer = SPACESHIP_WEAPON_COOLDOWN_TIME;
	}
}

void BehaviorSpaceshipSpawnBullet(Behavior* behavior)
{
	if (!behavior) return;

	Entity* bullet = EntityFactoryBuild("Bullet");
	if (!bullet) return;

	Transform* spaceship_transform = EntityGetTransform(behavior->parent);
	Transform* bullet_transform = EntityGetTransform(bullet);

	TransformSetTranslation(bullet_transform, TransformGetTranslation(spaceship_transform));
	TransformSetRotation(bullet_transform, TransformGetRotation(spaceship_transform));

	Vector2D velocity;
	Vector2DFromAngleRad(&velocity, TransformGetRotation(bullet_transform));
	Vector2DScale(&velocity, &velocity, SPACESHIP_WEAPON_BULLET_SPEED);
	Physics* bullet_physics = EntityGetPhysics(bullet);
	PhysicsSetVelocity(bullet_physics, &velocity);

	SceneAddEntity(bullet);
}

void BehaviorSpaceshipCollisionHandler(Entity* spaceship, Entity* other)
{
	if (!spaceship || !other) return;

	if (strcmp(EntityGetName(other), "Asteroid") == 0)
	{
		EntityGetBehavior(spaceship)->stateNext = SPACESHIP_DEAD;
	}
}
