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
	UNREFERENCED_PARAMETER(other);
	return NULL;
}

void BehaviorFree(Behavior** behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}

void BehaviorRead(Behavior* behavior, Stream stream)
{
	UNREFERENCED_PARAMETER(behavior);
	UNREFERENCED_PARAMETER(stream);
}

void BehaviorSetParent(Behavior* behavior, Entity* parent)
{
	UNREFERENCED_PARAMETER(behavior);
	UNREFERENCED_PARAMETER(parent);
}

void BehaviorUpdate(Behavior* behavior, float dt)
{
	UNREFERENCED_PARAMETER(behavior);
	UNREFERENCED_PARAMETER(dt);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

