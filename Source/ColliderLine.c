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
#include "Collider.h"
#include "Vector2D.h"
#include "Stream.h"

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
	UNREFERENCED_PARAMETER(collider);
	UNREFERENCED_PARAMETER(other);
	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

