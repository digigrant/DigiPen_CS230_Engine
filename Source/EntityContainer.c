//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "EntityContainer.h"
#include "Entity.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define entityArraySize 100

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct EntityContainer
{
	// This list can be a fixed-length array (minimum size of 100 entries)
	// or a dynamically sized array, such as a linked list.
	// (NOTE: The implementation details are left up to the student.  However,
	//    it is your responsiblity to ensure that memory is handled correctly.)
	Entity* (*entityArray)[entityArraySize];

	// This variable is not required but could be used for tracking the number
	//   of Entities currently in the list.  Instructions on how to do this
	//   are included in the function headers.
	unsigned entityCount;

	// This variable is not required but could be used for different purposes.
	// - For storing the maximum size of the container.
	// - For tracking peak usage of the container, used for testing purposes.
	unsigned entityMax;

} EntityContainer;

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

EntityContainer* EntityContainerCreate()
{
	EntityContainer* ec = (EntityContainer*)calloc(1, sizeof(EntityContainer));

	if (ec)
	{
		ec->entityArray = (Entity * (*)[entityArraySize])calloc(entityArraySize, sizeof(Entity*));
		ec->entityCount = 0;
		ec->entityMax = entityArraySize;
	}

	return ec;
}

void EntityContainerFree(EntityContainer** entities)
{
	if (!entities || !*entities) return;

	// TODO: Do we trust the caller to free all entities first?
	free((*entities)->entityArray);
	free(*entities);
	*entities = NULL;
}

bool EntityContainerAddEntity(EntityContainer* entities, Entity* entity)
{
	if (!entities || !entity) return false;

	if (entities->entityCount < entities->entityMax)
	{
		(*entities->entityArray)[entities->entityCount] = entity;
		++(entities->entityCount);
		return true;
	}

	return false;
}

Entity* EntityContainerFindByName(const EntityContainer* entities, const char* entityName)
{
	if (!entities || !entityName) return NULL;

	for (unsigned int i = 0; i < (entities->entityCount); ++i)
	{
		if (EntityIsNamed((*entities->entityArray)[i], entityName))
		{
			return (*entities->entityArray)[i];
		}
	}

	return NULL;
}

bool EntityContainerIsEmpty(const EntityContainer* entities)
{
	// TODO: What to return if entities is NULL?
	if (!entities) return true;

	return (entities->entityCount == 0);
}

void EntityContainerUpdateAll(EntityContainer* entities, float dt)
{
	for (unsigned int i = 0; i < (entities->entityCount); ++i)
	{
		EntityUpdate((*entities->entityArray)[i], dt);
	}
}

void EntityContainerRenderAll(const EntityContainer* entities)
{
	for (unsigned int i = 0; i < (entities->entityCount); ++i)
	{
		EntityRender((*entities->entityArray)[i]);
	}
}

void EntityContainerFreeAll(EntityContainer* entities)
{
	for (unsigned int i = 0; i < (entities->entityCount); ++i)
	{
		EntityFree(&(*entities->entityArray)[i]);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

