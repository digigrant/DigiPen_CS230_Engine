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

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define entityArraySize 100

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct EntityContainer
{
	// This variable is not required but could be used for tracking the number
	//   of Entities currently in the list.  Instructions on how to do this
	//   are included in the function headers.
	unsigned entityCount;

	// This variable is not required but could be used for different purposes.
	// - For storing the maximum size of the container.
	// - For tracking peak usage of the container, used for testing purposes.
	unsigned entityMax;

	// This list can be a fixed-length array (minimum size of 100 entries)
	// or a dynamically sized array, such as a linked list.
	// (NOTE: The implementation details are left up to the student.  However,
	//    it is your responsiblity to ensure that memory is handled correctly.)
	Entity* entities[entityArraySize];

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
	return NULL;
}

void EntityContainerFree(EntityContainer** entities)
{
	UNREFERENCED_PARAMETER(entities);
}

bool EntityContainerAddEntity(EntityContainer* entities, Entity* entity)
{
	UNREFERENCED_PARAMETER(entities);
	UNREFERENCED_PARAMETER(entity);
	return false;
}

Entity* EntityContainerFindByName(const EntityContainer* entities, const char* entityName)
{
	UNREFERENCED_PARAMETER(entities);
	UNREFERENCED_PARAMETER(entityName);
	return NULL;
}

bool EntityContainerIsEmpty(const EntityContainer* entities)
{
	UNREFERENCED_PARAMETER(entities);
	return false;
}

void EntityContainerUpdateAll(EntityContainer* entities, float dt)
{
	UNREFERENCED_PARAMETER(entities);
	UNREFERENCED_PARAMETER(dt);
}

void EntityContainerRenderAll(const EntityContainer* entities)
{
	UNREFERENCED_PARAMETER(entities);
}

void EntityContainerFreeAll(EntityContainer* entities)
{
	UNREFERENCED_PARAMETER(entities);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

