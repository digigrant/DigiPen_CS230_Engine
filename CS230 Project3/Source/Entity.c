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
#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"

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
	Transform* transform;
	Sprite* sprite;
	Physics* physics;
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

void EntityFree(Entity** entity)
{
	// check if entity is NULL or *entity is NULL
	if (!entity || !*entity) return;

	// free components
	if ((*entity)->transform)
	{
		TransformFree(&((*entity)->transform));
	}

	if ((*entity)->sprite)
	{
		SpriteFree(&((*entity)->sprite));
	}

	if ((*entity)->physics)
	{
		PhysicsFree(&((*entity)->physics));
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

		// Transform component
		if (strcmp(token, "Transform") == 0)
		{
			EntityAddTransform(entity, TransformCreate());
			TransformRead(entity->transform, stream);
			continue;
		}

		// Sprite component
		if (strcmp(token, "Sprite") == 0)
		{
			EntityAddSprite(entity, SpriteCreate());
			SpriteRead(entity->sprite, stream);
			continue;
		}

		// Physics component
		if (strcmp(token, "Physics") == 0)
		{
			EntityAddPhysics(entity, PhysicsCreate());
			PhysicsRead(entity->physics, stream);
			continue;
		}
	}
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
	if (entity->physics && entity->transform)
	{
		PhysicsUpdate(entity->physics, entity->transform, dt);
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
