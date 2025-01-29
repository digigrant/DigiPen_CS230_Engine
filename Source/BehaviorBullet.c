//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorBullet.h"
#include "Behavior.h"
#include "Entity.h"
#include "Teleporter.h"
#include "Collider.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

typedef enum
{
	BULLET_INVALID = -1,
	BULLET_IDLE
} BulletState;

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

static void BehaviorBulletOnInit(Behavior* behavior);
static void BehaviorBulletOnUpdate(Behavior* behavior, float dt);
static void BehaviorBulletOnExit(Behavior* behavior);
static void BehaviorBulletUpdateLifeTimer(Behavior* behavior, float dt);
static void BehaviorBulletCollisionHandler(Entity* bullet, Entity* other);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the ...
Behavior* BehaviorBulletCreate(void)
{
	Behavior* behavior = (Behavior*)calloc(1, sizeof(Behavior));
	if (!behavior) { return NULL; }

	behavior->memorySize = sizeof(Behavior);
	behavior->stateCurr = BULLET_INVALID;
	behavior->stateNext = BULLET_IDLE;
	behavior->onInit = BehaviorBulletOnInit;
	behavior->onUpdate = BehaviorBulletOnUpdate;
	behavior->onExit = BehaviorBulletOnExit;

	return behavior;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void BehaviorBulletOnInit(Behavior* behavior)
{
	if (!behavior) return;

	if (behavior->stateCurr == BULLET_IDLE)
	{
		Collider* collider = EntityGetCollider(behavior->parent);
		if (collider)
		{
			ColliderSetCollisionHandler(collider, BehaviorBulletCollisionHandler);
		}
	}
}

void BehaviorBulletOnUpdate(Behavior* behavior, float dt)
{
	if (!behavior) return;

	switch (behavior->stateCurr)
	{
	case BULLET_IDLE:
		BehaviorBulletUpdateLifeTimer(behavior, dt);
		break;
	}

	TeleporterUpdateEntity(behavior->parent);
}

void BehaviorBulletOnExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}

void BehaviorBulletUpdateLifeTimer(Behavior* behavior, float dt)
{
	if (!behavior) return;

	if (behavior->timer > 0.0f)
	{
		behavior->timer -= dt; // decrement timer
	}

	if (behavior->timer <= 0.0f)
	{
		EntityDestroy(behavior->parent);
	}
}

void BehaviorBulletCollisionHandler(Entity* bullet, Entity* other)
{
	if (!bullet || !other) return;

	if (strcmp(EntityGetName(other), "Asteroid") == 0)
	{
		EntityDestroy(bullet);
	}
}