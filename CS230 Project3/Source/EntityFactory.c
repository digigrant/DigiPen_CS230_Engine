//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 2
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Stream.h"

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

Entity* EntityFactoryBuild(char const* filename)
{
	// Check if the filename is NULL
	if (!filename) { return NULL; }

	Entity* entity = NULL;
	Stream stream = StreamOpen(filename);

	// If the stream is valid
	if (stream)
	{
		// If the first token is "Entity"
		if (strncmp(StreamReadToken(stream), "Entity", _countof("Entity")) == 0)
		{
			// Create a new entity
			entity = EntityCreate();

			if (entity)
			{
				// Read the entity from the stream
				EntityRead(entity, stream);
			}
		}

		// Close the stream
		StreamClose(&stream);
	}

	return entity;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

