//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 2
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSource.h"
#include "DGL.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SpriteSource
{
	// Pointer to a texture resource created using the DigiPen Graphics Library (DGL).
	const DGL_Texture* texture;

	// The dimensions of the sprite sheet.
	// (Hint: These should be initialized to (1, 1).)
	int	num_rows;
	int	num_cols;

} SpriteSource;

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

SpriteSource* SpriteSourceCreate(void)
{
	// allocate sprite source and initialize variables to 0
	// if successful, sprite source is created. if not, sprite source is NULL
	SpriteSource* sprite_source = (SpriteSource*)calloc(1, sizeof(SpriteSource));

	if (sprite_source)
	{
		// set num_rows and num_cols
		sprite_source->num_rows = 1;
		sprite_source->num_cols = 1;
	}

	return sprite_source;
}

void SpriteSourceFree(SpriteSource** spriteSource)
{
	if (!spriteSource || !*spriteSource) return;

	DGL_Graphics_FreeTexture(&((*spriteSource)->texture));
	free(*spriteSource);
	(*spriteSource) = NULL;
}

void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName)
{
	// create a filepath string
	char filepath[256];
	if (sprintf_s(filepath, _countof(filepath), "Assets/%s", textureName) < 0)
	{
		// print the error using str_error_s
		char error[256];
		strerror_s(error, _countof(error), errno);
		printf("Error: %s\n", error);
		return;
	}

	spriteSource->texture = DGL_Graphics_LoadTexture(filepath);

	// set num_rows and num_cols
	spriteSource->num_rows = numRows;
	spriteSource->num_cols = numCols;
}

unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource)
{
	return spriteSource->num_rows * spriteSource->num_cols;
}

void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v)
{
	// calculate the u and v coordinates
	*u = (frameIndex % spriteSource->num_cols) / (float)spriteSource->num_cols;
	*v = (frameIndex / spriteSource->num_cols) / (float)spriteSource->num_rows;
}

void SpriteSourceSetTexture(const SpriteSource* spriteSource)
{
	DGL_Graphics_SetTexture(spriteSource->texture);
}

void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned int frameIndex)
{
	float u, v;
	SpriteSourceGetUV(spriteSource, frameIndex, &u, &v);
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { u, v });
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
