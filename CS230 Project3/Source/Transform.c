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
#include "Matrix2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Transform
{
	Matrix2D matrix;
	Vector2D position;
	Vector2D scale;
	float rotation;
	bool isDirty;
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

void CalculateTransformationMatrix(Transform* transform);

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

		transform->isDirty = true;
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
	transform->isDirty = true;
}

const Matrix2D* TransformGetMatrix(Transform* transform)
{
	if (!transform) { return NULL; }

	if (transform->isDirty)
	{
		CalculateTransformationMatrix(transform);
		transform->isDirty = false;
	}

	return &(transform->matrix);
}

const Vector2D* TransformGetTranslation(const Transform* transform)
{
	return (transform != NULL) ? &(transform->position) : NULL;
}

float TransformGetRotation(const Transform* transform)
{
	return (transform != NULL) ? transform->rotation : 0.0f;
}

const Vector2D* TransformGetScale(const Transform* transform)
{
	return (transform != NULL) ? &(transform->scale) : NULL;
}

void TransformSetTranslation(Transform* transform, const Vector2D* translation)
{
	transform->position = *translation;
	transform->isDirty = true;
}

void TransformSetRotation(Transform* transform, float rotation)
{
	transform->rotation = rotation;
	transform->isDirty = true;
}

void TransformSetScale(Transform* transform, const Vector2D* scale)
{
	transform->scale = *scale;
	transform->isDirty = true;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
void CalculateTransformationMatrix(Transform* transform)
{
	Matrix2D result, buffer;
	Matrix2DIdentity(&result);

	Matrix2DScale(&buffer, transform->scale.x, transform->scale.y);
	Matrix2DConcat(&result, &buffer, &result);

	Matrix2DRotRad(&buffer, transform->rotation);
	Matrix2DConcat(&result, &buffer, &result);

	Matrix2DTranslate(&buffer, transform->position.x, transform->position.y);
	Matrix2DConcat(&result, &buffer, &result);

	transform->matrix = result;
}