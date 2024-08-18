//------------------------------------------------------------------------------
//
// File Name:	Transform.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 2
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Transform
{
	Vector2D position;
	Vector2D scale;
	float rotation;
} Transform;

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

Transform* TransformCreate(void)
{
	// Allocate memory for the transform - all values are initialized to zero
	Transform* transform = (Transform*)calloc(1, sizeof(Transform));

	if (transform != NULL)
	{
		// Initialize scale to be non-zero
		transform->scale.x = 1.0f;
		transform->scale.y = 1.0f;
	}

	return transform;
}

void TransformFree(Transform** transform)
{
	// Check if the transform is NULL
	if (!transform || !*transform) { return; }

	// Free the transform
	free(*transform);
	(*transform) = NULL;
}

void TransformRead(Transform* transform, Stream stream)
{
	StreamReadVector2D(stream, &(transform->position));
	transform->rotation = StreamReadFloat(stream);
	StreamReadVector2D(stream, &(transform->scale));
}

const Vector2D* TransformGetTranslation(const Transform* transform)
{
	return &(transform->position);
}

float TransformGetRotation(const Transform* transform)
{
	return transform->rotation;
}

const Vector2D* TransformGetScale(const Transform* transform)
{
	return &(transform->scale);
}

void TransformSetTranslation(Transform* transform, const Vector2D* translation)
{
	transform->position = *translation;
}

void TransformSetRotation(Transform* transform, float rotation)
{
	transform->rotation = rotation;
}

void TransformSetScale(Transform* transform, const Vector2D* scale)
{
	transform->scale = *scale;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
