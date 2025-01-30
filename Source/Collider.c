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
#include "ColliderCircle.h" // bad coupling! replace with collision engine
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

bool ColliderIsColliding(const Collider* collider, const Collider* other);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Collider* ColliderClone(const Collider* other)
{
	if (!other) { return NULL; }

	Collider* clone_collider = (Collider*)malloc(other->memorySize);
	if (!clone_collider) { return NULL; }

	memcpy(clone_collider, other, other->memorySize);
	clone_collider->parent = NULL;
	return clone_collider; // parent pointer needs to be updated - caller is responsible
}

void ColliderFree(Collider** collider)
{
	if (!collider || !*collider) { return; }

	free(*collider);
	(*collider) = NULL;
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

	/*
	Transform* transformA = EntityGetTransform(entityA);
	Transform* transformB = EntityGetTransform(entityB);
	if (!transformA || !transformB) { return; }

	// Check for collision between the two entities.
	if (Vector2DDistance(TransformGetTranslation(transformA), TransformGetTranslation(transformB)) < 40.0f)
	{
	*/
	if (ColliderIsColliding(collider, other))
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

bool ColliderIsColliding(const Collider* collider, const Collider* other)
{
	if (!collider || !other) { return false; }

	if (collider->type == COLLIDER_TYPE_CIRCLE && other->type == COLLIDER_TYPE_CIRCLE)
	{
		return ColliderCircleIsCollidingWithCircle(collider, other);
	}
	else if (collider->type == COLLIDER_TYPE_CIRCLE && other->type == COLLIDER_TYPE_LINE)
	{
		return ColliderLineIsCollidingWithCircle(other, collider);
	}
	else if (collider->type == COLLIDER_TYPE_LINE && other->type == COLLIDER_TYPE_CIRCLE)
	{
		return ColliderLineIsCollidingWithCircle(collider, other);
	}

	return false; // else - line & line
}
