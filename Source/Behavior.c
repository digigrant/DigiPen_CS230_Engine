//------------------------------------------------------------------------------
//
// File Name:	Behavior.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Behavior.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Behavior* BehaviorClone(Behavior* other)
{
	if (!other) return NULL;

	Behavior* behavior = (Behavior*)malloc(sizeof(Behavior));

	if (!behavior) return NULL;

	behavior->stateCurr = other->stateCurr;
	behavior->stateNext = other->stateNext;
	behavior->timer = other->timer;
	behavior->onInit = other->onInit;
	behavior->onUpdate = other->onUpdate;
	behavior->onExit = other->onExit;
	behavior->parent = other->parent;	// caller must set parent

	return behavior;
}

void BehaviorFree(Behavior** behavior)
{
	if (!behavior || !(*behavior)) return;

	free(*behavior);
	*behavior = NULL;
}

void BehaviorRead(Behavior* behavior, Stream stream)
{
	if (!behavior || !stream) return;

	behavior->stateCurr = StreamReadInt(stream);
	behavior->stateNext = StreamReadInt(stream);
	behavior->timer = StreamReadFloat(stream);
}

void BehaviorSetParent(Behavior* behavior, Entity* parent)
{
	if (behavior) { behavior->parent = parent; }
}

void BehaviorUpdate(Behavior* behavior, float dt)
{
	if (!behavior) return;

	if (behavior->stateNext != behavior->stateCurr)	// Change states
	{
		if (behavior->onExit)							// 1. Exit current state
		{
			behavior->onExit(behavior);
		}

		behavior->stateCurr = behavior->stateNext;	// 2. Change state

		if (behavior->onInit)							// 3. Initialize new state
		{
			behavior->onInit(behavior);
		}
	}

	if (behavior->onUpdate) // Update current state
	{
		behavior->onUpdate(behavior, dt);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------