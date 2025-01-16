//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 2
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Entity.h"
#include "Stream.h"
#include "Animation.h"
#include "Behavior.h"
#include "BehaviorAsteroid.h"
#include "BehaviorBullet.h"
#include "BehaviorSpaceship.h"
#include "Collider.h"
#include "Physics.h"
#include "Sprite.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define MAX_NAME_LENGTH 32

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Entity
{
	char name[MAX_NAME_LENGTH];
	Animation* animation;
	Behavior* behavior;
	Physics* physics;
	Sprite* sprite;
	Transform* transform;
	bool isDestroyed;
} Entity;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Entity* EntityCreate(void)
{
	// allocate entity and initialize variables to 0
	// if successful, entity is created. if not, entity is NULL
	Entity* entity = (Entity*)calloc(1, sizeof(Entity));
	return entity;
}

Entity* EntityClone(const Entity* other)
{
	if (!other) { return NULL; }

	Entity* entity = EntityCreate();
	if (!entity) { return NULL; }

	memcpy_s(entity->name, _countof(entity->name), other->name, _countof(other->name));
	entity->isDestroyed = other->isDestroyed;

	if (other->animation)
	{
		Animation* animation = AnimationClone(other->animation);
		EntityAddAnimation(entity, animation);
	}
	if (other->behavior)
	{
		Behavior* behavior = BehaviorClone(other->behavior);
		EntityAddBehavior(entity, behavior);
	}
	if (other->physics)
	{
		Physics* physics = PhysicsClone(other->physics);
		EntityAddPhysics(entity, physics);
	}
	if (other->sprite)
	{
		Sprite* sprite = SpriteClone(other->sprite);
		EntityAddSprite(entity, sprite);
	}
	if (other->transform)
	{
		Transform* transform = TransformClone(other->transform);
		EntityAddTransform(entity, transform);
	}

	return entity;
}

void EntityFree(Entity** entity)
{
	// check if entity is NULL or *entity is NULL
	if (!entity || !*entity) return;

	// free components
	if ((*entity)->animation)
	{
		AnimationFree(&((*entity)->animation));
	}
	if ((*entity)->behavior)
	{
		BehaviorFree(&((*entity)->behavior));
	}
	if ((*entity)->physics)
	{
		PhysicsFree(&((*entity)->physics));
	}
	if ((*entity)->sprite)
	{
		SpriteFree(&((*entity)->sprite));
	}
	if ((*entity)->transform)
	{
		TransformFree(&((*entity)->transform));
	}

	// free entity
	free(*entity);
	(*entity) = NULL;
}

void EntityRead(Entity* entity, Stream stream)
{
	// read name from token
	EntitySetName(entity, StreamReadToken(stream));

	// get components
	char token[MAX_NAME_LENGTH];
	while (true)
	{
		// read next token
		strcpy_s(token, _countof(token), StreamReadToken(stream));
		// if token is empty, we're done
		if (strcmp(token, "") == 0) break;

		// Animation component
		if (strcmp(token, "Animation") == 0)
		{
			EntityAddAnimation(entity, AnimationCreate());
			AnimationRead(entity->animation, stream);
			continue;
		}
		// Behavior components
		if (strcmp(token, "BehaviorAsteroid") == 0)
		{
			EntityAddBehavior(entity, BehaviorAsteroidCreate());
			BehaviorRead(entity->behavior, stream);
			continue;
		}
		if (strcmp(token, "BehaviorBullet") == 0)
		{
			EntityAddBehavior(entity, BehaviorBulletCreate());
			BehaviorRead(entity->behavior, stream);
			continue;
		}
		if (strcmp(token, "BehaviorSpaceship") == 0)
		{
			EntityAddBehavior(entity, BehaviorSpaceshipCreate());
			BehaviorRead(entity->behavior, stream);
			continue;
		}
		// Collider component
		if (strcmp(token, "Collider") == 0)
		{
			// EntityAddCollider(entity, ColliderCreate());
			// ColliderRead(entity->collider, stream);
			continue;
		}
		// Physics component
		if (strcmp(token, "Physics") == 0)
		{
			EntityAddPhysics(entity, PhysicsCreate());
			PhysicsRead(entity->physics, stream);
			continue;
		}
		// Sprite component
		if (strcmp(token, "Sprite") == 0)
		{
			EntityAddSprite(entity, SpriteCreate());
			SpriteRead(entity->sprite, stream);
			continue;
		}
		// Transform component
		if (strcmp(token, "Transform") == 0)
		{
			EntityAddTransform(entity, TransformCreate());
			TransformRead(entity->transform, stream);
			continue;
		}
	}
}

void EntityDestroy(Entity* entity)
{
	entity->isDestroyed = true;
}

bool EntityIsDestroyed(const Entity* entity)
{
	return (entity) ? entity->isDestroyed : false;
}

void EntityAddAnimation(Entity* entity, Animation* animation)
{
	entity->animation = animation;
	AnimationSetParent(entity->animation, entity);
}

void EntityAddBehavior(Entity* entity, Behavior* behavior)
{
	entity->behavior = behavior;
	BehaviorSetParent(entity->behavior, entity);
}

void EntityAddPhysics(Entity* entity, Physics* physics)
{
	entity->physics = physics;
}

void EntityAddSprite(Entity* entity, Sprite* sprite)
{
	entity->sprite = sprite;
}

void EntityAddTransform(Entity* entity, Transform* transform)
{
	entity->transform = transform;
}

void EntitySetName(Entity* entity, const char* name)
{
	strcpy_s(entity->name, _countof(entity->name), name);
}

const char* EntityGetName(const Entity* entity)
{
	return (entity) ? entity->name : NULL;
}

bool EntityIsNamed(const Entity* entity, const char* name)
{
	return (entity && name) ? (strcmp(entity->name, name) == 0) : false;
}

Animation* EntityGetAnimation(const Entity* entity)
{
	return (entity) ? entity->animation : NULL;
}

Behavior* EntityGetBehavior(const Entity* entity)
{
	return (entity) ? entity->behavior : NULL;
}

Physics* EntityGetPhysics(const Entity* entity)
{
	return (entity) ? entity->physics : NULL;
}

Sprite* EntityGetSprite(const Entity* entity)
{
	return (entity) ? entity->sprite : NULL;
}

Transform* EntityGetTransform(const Entity* entity)
{
	return (entity) ? entity->transform : NULL;
}

void EntityUpdate(Entity* entity, float dt)
{
	// Order of update matters!!
	if (entity->behavior)
	{
		BehaviorUpdate(entity->behavior, dt);
	}

	if (entity->physics && entity->transform)
	{
		PhysicsUpdate(entity->physics, entity->transform, dt);
	}

	if (entity->animation)
	{
		AnimationUpdate(entity->animation, dt);
	}
}

void EntityRender(Entity* entity)
{
	if (entity->sprite && entity->transform)
	{
		SpriteRender(entity->sprite, entity->transform);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
