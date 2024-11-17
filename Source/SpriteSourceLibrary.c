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

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define SPRITE_SOURCE_LIST_SIZE 10

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SpriteSourceLibrary
{
	unsigned int spriteSourceCount;
	SpriteSource* spriteSourceList[SPRITE_SOURCE_LIST_SIZE];
} SpriteSourceLibrary;

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

void SpriteSourceLibraryInit()
{

}

const SpriteSource* SpriteSourceLibraryBuild(const char* spriteSourceName)
{
	UNREFERENCED_PARAMETER(spriteSourceName);
	return NULL;
}

void SpriteSourceLibraryFreeAll()
{

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

