//------------------------------------------------------------------------------
//
// File Name:	Teleporter.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Teleporter.h"
#include "Entity.h"
#include "Transform.h"
#include "Physics.h"
#include "DGL.h"
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

void TeleporterUpdateEntity(Entity* entity)
{
	Vector2D window_size = DGL_Window_GetSize();
	Vector2D window_half_size;
	Vector2DScale(&window_half_size, &window_size, 0.5f);

	Transform* entity_transform = EntityGetTransform(entity);
	Physics* entity_physics = EntityGetPhysics(entity);

	Vector2D delta_position = { 0.0f, 0.0f };
	
	// check x dir
	if (PhysicsGetVelocity(entity_physics)->x > 0.0f &&
		TransformGetTranslation(entity_transform)->x > window_half_size.x)
	{
		delta_position.x = -window_size.x;
	}
	else if (PhysicsGetVelocity(entity_physics)->x < 0.0f &&
		TransformGetTranslation(entity_transform)->x < -window_half_size.x)
	{
		delta_position.x = window_size.x;
	}

	// check y dir
	if (PhysicsGetVelocity(entity_physics)->y > 0.0f &&
		TransformGetTranslation(entity_transform)->y > window_half_size.y)
	{
		delta_position.y = -window_size.y;
	}
	else if (PhysicsGetVelocity(entity_physics)->y < 0.0f &&
		TransformGetTranslation(entity_transform)->y < -window_half_size.y)
	{
		delta_position.y = window_size.y;
	}

	if (delta_position.x != 0.0f || delta_position.y != 0.0f)
	{
		Vector2D new_position;
		Vector2DAdd(&new_position, TransformGetTranslation(entity_transform), &delta_position);
		TransformSetTranslation(entity_transform, &new_position);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
