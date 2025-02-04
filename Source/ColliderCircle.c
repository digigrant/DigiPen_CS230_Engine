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
#include "Collider.h"
#include "Stream.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ColliderCircle {
	Collider base;
	float radius;
} ColliderCircle;

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
	ColliderCircle* collider_circle = (ColliderCircle*)calloc(1, sizeof(ColliderCircle));
	if (!collider_circle) { return NULL; }

	collider_circle->radius = 1.0f;
	collider_circle->base.memorySize = sizeof(ColliderCircle);
	collider_circle->base.type = COLLIDER_TYPE_CIRCLE;
	return (Collider*)collider_circle;
}

void ColliderCircleRead(Collider* collider, Stream stream)
{
	if (!collider || (collider->type != COLLIDER_TYPE_CIRCLE) || !stream) { return; }
	((ColliderCircle*)collider)->radius = StreamReadFloat(stream);
}

float ColliderCircleGetRadius(const Collider* collider)
{
	if (!collider || collider->type != COLLIDER_TYPE_CIRCLE) { return 0.0f; }
	return ((ColliderCircle*)collider)->radius;
}

void ColliderCircleSetRadius(Collider* collider, float radius)
{
	if (!collider || collider->type != COLLIDER_TYPE_CIRCLE) { return; }
	((ColliderCircle*)collider)->radius = radius;
}

bool ColliderCircleIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	if (!collider || !other || (collider->type != COLLIDER_TYPE_CIRCLE) ||
		(other->type != COLLIDER_TYPE_CIRCLE)) { return false; }

	const Vector2D* posA = TransformGetTranslation(EntityGetTransform(collider->parent));
	const Vector2D* posB = TransformGetTranslation(EntityGetTransform(other->parent));
	float distance_threshold = ((ColliderCircle*)collider)->radius + ((ColliderCircle*)other)->radius;
	
	return Vector2DDistance(posA, posB) < distance_threshold;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

