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
#include "EntityContainer.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

static EntityContainer* archetypes = NULL;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Entity* EntityFactoryBuild(char const* entityName)
{
	if (!entityName) { return NULL; }

	if (!archetypes)
	{
		archetypes = EntityContainerCreate();
	}

	Entity* entity = EntityContainerFindByName(archetypes, entityName);

	if (!entity)
	{
		// Construct the filename
		char filename[256] = "";
		sprintf_s(filename, _countof(filename), "./Data/%s.txt", entityName);
		Stream stream = StreamOpen(filename);

		if (stream)
		{
			// If the first token is "Entity"
			if (strncmp(StreamReadToken(stream), "Entity", _countof("Entity")) == 0)
			{
				entity = EntityCreate();

				if (entity)
				{
					// Read the entity from the stream
					EntityRead(entity, stream);
					EntityContainerAddEntity(archetypes, entity);
				}
			}

			StreamClose(&stream);
		}
	}

	Entity* clone = EntityClone(entity);
	return clone;
}

void EntityFactoryFreeAll()
{
	if (archetypes)
	{
		EntityContainerFree(&archetypes);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

