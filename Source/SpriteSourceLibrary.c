//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceLibrary.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 5
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSourceLibrary.h"
#include "SpriteSource.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define SPRITE_SOURCE_LIST_SIZE 10

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SpriteSourceLibrary
{
	SpriteSource* spriteSourceList[SPRITE_SOURCE_LIST_SIZE];
	unsigned int spriteSourceCount;
} SpriteSourceLibrary;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static SpriteSourceLibrary spriteSources;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SpriteSourceLibraryAdd(const SpriteSource* spriteSource);
static const SpriteSource* SpriteSourceLibraryFind(const char* spriteSourceName);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void SpriteSourceLibraryInit()
{
	spriteSources.spriteSourceCount = 0;
	for (unsigned int i = 0; i < SPRITE_SOURCE_LIST_SIZE; ++i)
	{
		spriteSources.spriteSourceList[i] = NULL;
	}
}

const SpriteSource* SpriteSourceLibraryBuild(const char* spriteSourceName)
{
	if (!spriteSourceName) { return NULL; }

	const SpriteSource* spriteSource = SpriteSourceLibraryFind(spriteSourceName);

	if (!spriteSource)
	{
		char filename[256];
		sprintf(filename, "Data/%s.txt", spriteSourceName);
		Stream stream = StreamOpen(filename);

		if (stream)
		{
			SpriteSource* new_sprite_source = SpriteSourceCreate();
			SpriteSourceRead(new_sprite_source, stream);
			SpriteSourceLibraryAdd(new_sprite_source);
			spriteSource = new_sprite_source;
			StreamClose(&stream);
		}
	}

	return spriteSource;
}

void SpriteSourceLibraryFreeAll()
{
	for (unsigned int i = 0; i < spriteSources.spriteSourceCount; ++i)
	{
		SpriteSourceFree(&(spriteSources.spriteSourceList[i]));
	}
	SpriteSourceLibraryInit();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void SpriteSourceLibraryAdd(const SpriteSource* spriteSource)
{
	if (spriteSources.spriteSourceCount >= SPRITE_SOURCE_LIST_SIZE) { return; }

	spriteSources.spriteSourceList[spriteSources.spriteSourceCount] = spriteSource;
	++(spriteSources.spriteSourceCount);
}

static const SpriteSource* SpriteSourceLibraryFind(const char* spriteSourceName)
{
	for (unsigned int i = 0; i < spriteSources.spriteSourceCount; ++i)
	{
		if (SpriteSourceIsNamed(spriteSources.spriteSourceList[i], spriteSourceName))
		{
			return spriteSources.spriteSourceList[i];
		}
	}

	return NULL;
}