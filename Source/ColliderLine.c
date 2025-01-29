//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 6
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ColliderLine.h"

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

Collider* ColliderLineCreate()
{
	return NULL;
}

void ColliderLineRead(Collider* collider, Stream stream)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(stream);
}

void ColliderLineAddLineSegment(Collider* collider, const Vector2D* p0, const Vector2D* p1)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(p0);
	UNREFERENCED_PARAMETER(p1);
}

bool ColliderLineIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(other);
	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

