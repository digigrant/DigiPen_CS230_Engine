//------------------------------------------------------------------------------
//
// File Name:	Collider.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 5
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Collider.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Collider
{
	Entity* parent;
	CollisionEventHandler handler;
} Collider;

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

// Initialize the ...
Collider* ColliderCreate(void)
{
	return NULL;
}

Collider* ColliderClone(const Collider* other)
{
	UNREFERENCED_PARAMETER(other);
	return NULL;
}

void ColliderFree(Collider** collider)
{
	UNREFERENCED_PARAMETER(collider);
}

void ColliderRead(Collider* collider, Stream stream)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(stream);
}

void ColliderSetParent(Collider* collider, Entity* parent)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(parent);
}

void ColliderCheck(Collider* collider, Collider* other)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(other);
}

void ColliderSetHandler(Collider* collider, CollisionEventHandler handler)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(handler);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

