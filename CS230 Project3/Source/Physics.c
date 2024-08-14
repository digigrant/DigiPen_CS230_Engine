//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 2
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Physics.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Physics
{
	Vector2D oldTranslation;
	Vector2D acceleration;
	Vector2D velocity;
	float inverseMass;
} Physics;

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

Physics* PhysicsCreate(void)
{
	// allocate physics and initialize variables to 0
	// if successful, physics is created. if not, physics is NULL
	Physics* physics = (Physics*)calloc(1, sizeof(Physics));

	if (physics)
	{
		// set inverse mass
		physics->inverseMass = 1.0f;
	}

	return physics;
}

void PhysicsFree(Physics** physics)
{
	// check if physics is NULL or *physics is NULL
	if (!physics || !*physics) return;

	free(*physics);
	(*physics) = NULL;
}

void PhysicsRead(Physics* physics, Stream stream)
{
	// read acceleration and velocity
	StreamReadVector2D(stream, &(physics->acceleration));
	StreamReadVector2D(stream, &(physics->velocity));
}

const Vector2D* PhysicsGetAcceleration(const Physics* physics)
{
	return (physics) ? &(physics->acceleration) : NULL;
}

const Vector2D* PhysicsGetVelocity(const Physics* physics)
{
	return (physics) ? &(physics->velocity) : NULL;
}

const Vector2D* PhysicsGetOldTranslation(Physics* physics)
{
	return (physics) ? &(physics->oldTranslation) : NULL;
}

void PhysicsSetAcceleration(Physics* physics, const Vector2D* acceleration)
{
	physics->acceleration = *acceleration;
}

void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity)
{
	physics->velocity = *velocity;
}

void PhysicsUpdate(Physics* physics, Transform* transform, float dt)
{
	// check if physics is NULL or transform is NULL
	if (!physics || !transform)
	{
		// crash tbh
	}

	// Get old translation
	physics->oldTranslation = *TransformGetTranslation(transform);

	// update velocity
	Vector2DScaleAdd(&(physics->velocity), &(physics->acceleration), dt, &(physics->velocity));

	// update translation
	Vector2D newTranslation;
	Vector2DScaleAdd(&newTranslation, &physics->velocity, dt, &physics->oldTranslation);
	TransformSetTranslation(transform, &newTranslation);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

