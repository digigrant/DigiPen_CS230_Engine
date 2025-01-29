//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 0
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColliderCircle.h"

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

Collider* ColliderCircleCreate()
{
	return NULL;
}

void ColliderCircleRead(Collider* collider, Stream stream)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(stream);
}

float ColliderCircleGetRadius(const Collider* collider)
{
	UNREFERENCED_PARAMETER(collider);
	return 0.0f;
}

bool ColliderCircleIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(other);
	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

