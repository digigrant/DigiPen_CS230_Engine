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
#include "ColliderCircle.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Entity.h"
#include "Physics.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define LINE_SEGMENT_MAX 10

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ColliderLineSegment
{
	// A single line segment (P0 and P1).
	Vector2D	point[2];
} ColliderLineSegment;

typedef struct ColliderLine
{
	// Inherit the base collider structure.
	Collider	base;

	// The number of line segments in the list.
	unsigned int		lineCount;

	// The individual line segments.
	// (NOTE: Make sure to allocate enough memory for all line segments!)
	ColliderLineSegment	lineSegments[LINE_SEGMENT_MAX];

} ColliderLine;

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
	ColliderLine* collider_line = (ColliderLine*)calloc(1, sizeof(ColliderLine));
	if (!collider_line) { return NULL; }

	collider_line->base.memorySize = sizeof(ColliderLine);
	collider_line->base.type = COLLIDER_TYPE_LINE;
	return (Collider*)collider_line;
}

void ColliderLineRead(Collider* collider, Stream stream)
{
	if (!collider || (collider->type != COLLIDER_TYPE_LINE) || !stream) { return; }
	
	ColliderLine* collider_line = (ColliderLine*)collider;
	Vector2D p0, p1;
	unsigned int total_lines = StreamReadInt(stream);
	while(collider_line->lineCount < total_lines)
	{
		StreamReadVector2D(stream, &p0);
		StreamReadVector2D(stream, &p1);
		ColliderLineAddLineSegment(collider, &p0, &p1);
	}
}

void ColliderLineAddLineSegment(Collider* collider, const Vector2D* p0, const Vector2D* p1)
{
	if (!collider || (collider->type != COLLIDER_TYPE_LINE) || !p0 || !p1) { return; }

	ColliderLine* collider_line = (ColliderLine*)collider;
	memcpy(&(collider_line->lineSegments[collider_line->lineCount].point[0]), p0, sizeof(Vector2D));
	memcpy(&(collider_line->lineSegments[collider_line->lineCount].point[1]), p1, sizeof(Vector2D));
	++(collider_line->lineCount);
}

bool ColliderLineIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	if (!collider || !other || collider->type != COLLIDER_TYPE_LINE || other->type != COLLIDER_TYPE_CIRCLE) { return false; }

	Entity* other_entity = other->parent;
	const Vector2D* bs = PhysicsGetOldTranslation(EntityGetPhysics(other_entity));
	const Vector2D* be = TransformGetTranslation(EntityGetTransform(other_entity));

	Vector2D v, e, n, bi, p0p1, p1p0, bip0, bip1, i, s, r, br;
	const Vector2D* p0;
	const Vector2D* p1;
	float ti;

	Vector2DSub(&v, be, bs);	// displacement vector

	ColliderLine* collider_line = (ColliderLine*)collider;
	for (unsigned int x = 0; x < collider_line->lineCount; ++x)
	{
		p0 = &(collider_line->lineSegments[x].point[0]);
		p1 = &(collider_line->lineSegments[x].point[1]);

		Vector2DSub(&e, p1, p0);		// edge vector

		Vector2DSet(&n, e.y, -e.x);
		Vector2DNormalize(&n, &n);		// normal vector

		// trivial checks
		// is the point moving parallel to the line?
		if (Vector2DDotProduct(&n, &v) == 0.0f)							{ continue; }
		// is the displacement vector entirely inside the half-plane?
		if (Vector2DDotProduct(&n, bs) <= Vector2DDotProduct(&n, p0) &&
			Vector2DDotProduct(&n, be) <= Vector2DDotProduct(&n, p0))	{ continue; }
		// is the displacement vector entirely outside the half-plane?
		if (Vector2DDotProduct(&n, bs) >= Vector2DDotProduct(&n, p0) &&
			Vector2DDotProduct(&n, be) >= Vector2DDotProduct(&n, p0))	{ continue; }
		
		ti = (Vector2DDotProduct(&n, p0) - Vector2DDotProduct(&n, bs)) / Vector2DDotProduct(&n, &v);
		Vector2DScaleAdd(&bi, &v, ti, bs);
		
		// is point of intersection outside of the line segment?
		Vector2DSub(&p1p0, p1, p0);
		Vector2DSub(&bip0, &bi, p0);
		if (Vector2DDotProduct(&p1p0, &bip0) < 0)	{ continue; }

		Vector2DSub(&p0p1, p0, p1);
		Vector2DSub(&bip1, &bi, p1);
		if (Vector2DDotProduct(&p0p1, &bip1) < 0)	{ continue; }

		// at this point we know we are colliding
		Vector2DSub(&i, be, &bi);	// incident vector
		Vector2DScale(&s, &n, Vector2DDotProduct(&i, &n));		// penetration vector
		Vector2DScale(&r, &s, 2.0f);
		Vector2DSub(&r, &i, &r);	// reflection vector
		Vector2DAdd(&br, &bi, &r);	// reflection endpoint

		// set entity rotation
		TransformSetTranslation(EntityGetTransform(other_entity), &br);
		TransformSetRotation(EntityGetTransform(other_entity), Vector2DToAngleRad(&r));
		
		// set entity velocity
		const Vector2D* old_vel = PhysicsGetVelocity(EntityGetPhysics(other_entity));
		float speed = Vector2DLength(old_vel);
		Vector2D new_vel;
		Vector2DNormalize(&new_vel, &r);
		Vector2DScale(&new_vel, &new_vel, speed);
		PhysicsSetVelocity(EntityGetPhysics(other_entity), &new_vel);

		continue;
	}

	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

