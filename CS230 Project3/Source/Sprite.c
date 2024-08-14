//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 2
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"
#include "Stream.h"
#include "Trace.h"
#include "DGL.h"
#include "Mesh.h"
#include "Transform.h"
#include "SpriteSource.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Sprite
{
	SpriteSource const* sprite_source;
	Mesh const* mesh;
	float alpha;
	unsigned int frameIndex;
} Sprite;

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

Sprite* SpriteCreate(void)
{
	// allocate sprite and initialize variables to 0
	// if successful, sprite is created. if not, sprite is NULL
	Sprite* sprite = (Sprite*)calloc(1, sizeof(Sprite));

	if (sprite)
	{
		// set alpha
		sprite->alpha = 1.0f;
	}

	return sprite;
}

void SpriteFree(Sprite** sprite)
{
	// if input isn't valid, gtfo
	if (!sprite || !(*sprite)) { return; }

	free(*sprite);
	(*sprite) = NULL;
}

void SpriteRead(Sprite* sprite, Stream stream)
{
	// if a bad sprite or stream is fed in, this will crash

	// read data from file
	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);
}

void SpriteRender(const Sprite* sprite, Transform* transform)
{
	// set shader mode based on whether sprite has a texture or not
	if (sprite->sprite_source)	// texture
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		SpriteSourceSetTexture(sprite->sprite_source);								// DGL_Graphics_SetTexture
		SpriteSourceSetTextureOffset(sprite->sprite_source, sprite->frameIndex);	// DGL_Graphics_SetTextureOffset
	}
	else	// colored mesh
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	}
	
	DGL_Graphics_SetCB_TransformData((DGL_Vec2*)TransformGetTranslation(transform), (DGL_Vec2*)TransformGetScale(transform), TransformGetRotation(transform));

	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });

	MeshRender(sprite->mesh);
}

float SpriteGetAlpha(const Sprite* sprite)
{
	return (sprite) ? sprite->alpha : 0.0f;
}

void SpriteSetAlpha(Sprite* sprite, float alpha)
{
	// clamp alpha to 0.0f - 1.0f
	sprite->alpha = min(max(alpha, 0.0f), 1.0f);
}

void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex)
{
	TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);

	// check out of bounds
	if (frameIndex >= SpriteSourceGetFrameCount(sprite->sprite_source))
	{
		TraceMessage("\tinvalid frame index");
		return;
	}

	sprite->frameIndex = frameIndex;
}

void SpriteSetMesh(Sprite* sprite, const Mesh* mesh)
{
	sprite->mesh = mesh;
}

void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource)
{
	// set sprite source - can be NULL
	sprite->sprite_source = spriteSource;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
