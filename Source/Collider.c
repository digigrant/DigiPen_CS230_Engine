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
#include "Entity.h"
#include "Stream.h"
#include "Transform.h"
#include "Vector2D.h"

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

// Initialize the ...
/*
Collider* ColliderCreate(void)
{
	return (Collider*)calloc(1, sizeof(Collider));
}
*/

Collider* ColliderClone(const Collider* other)
{
	if (!other) { return NULL; }

	Collider* collider = (Collider*)malloc(sizeof(Collider));
	if (!collider) { return NULL; }

	memcpy(collider, other, sizeof(Collider));
	return collider; // parent pointer needs to be updated - caller is responsible
}

void ColliderFree(Collider** collider)
{
	if (!collider || !*collider) { return; }

	free(*collider);
	(*collider) = NULL;
}

void ColliderRead(Collider* collider, Stream stream)
{
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(stream);
}

void ColliderSetParent(Collider* collider, Entity* parent)
{
	if (!collider) { return; }
	collider->parent = parent;
}

void ColliderCheck(const Collider* collider, const Collider* other)
{
	if (!collider || !other) { return; }

	Entity* entityA = collider->parent;
	Entity* entityB = other->parent;
	if (!entityA || !entityB) { return; }

	Transform* transformA = EntityGetTransform(entityA);
	Transform* transformB = EntityGetTransform(entityB);
	if (!transformA || !transformB) { return; }

	// Check for collision between the two entities.
	if (Vector2DDistance(TransformGetTranslation(transformA), TransformGetTranslation(transformB)) < 40.0f)
	{
		// Call the collision handler for both entities.
		if (collider->handler)	{ collider->handler(entityA, entityB); }
		if (other->handler)		{ other->handler(entityB, entityA); }
	}
}

void ColliderSetCollisionHandler(Collider* collider, CollisionEventHandler handler)
{
	if (!collider) { return; }
	collider->handler = handler;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

