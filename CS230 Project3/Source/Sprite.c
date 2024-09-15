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
#include "Matrix2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Sprite
{
	const SpriteSource* sprite_source;
	const Mesh* mesh;
	const char* text;
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
		sprite->alpha = 1.0f;
	}

	return sprite;
}

void SpriteFree(Sprite** sprite)
{
	if (!sprite || !(*sprite)) { return; }

	free(*sprite);
	(*sprite) = NULL;
}

void SpriteRead(Sprite* sprite, Stream stream)
{
	// if a bad sprite or stream is fed in, this will crash

	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);
}

void SpriteRender(const Sprite* sprite, Transform* transform)
{
	if (!sprite || !sprite->mesh) { return; }

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
		DGL_Graphics_SetTexture(NULL);
	}
	
	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });

	if (!(sprite->text))
	{
		DGL_Graphics_SetCB_TransformMatrix(TransformGetMatrix(transform));
		MeshRender(sprite->mesh);
	}
	else
	{
		Matrix2D matrix, offset;
		matrix = *(TransformGetMatrix(transform));
		Matrix2DTranslate(&offset, TransformGetScale(transform)->x, 0.0f);

		const char* text_iter = sprite->text;
		while (*text_iter)
		{
			char current_char = *text_iter;
			current_char -= ' ';
			if (current_char >= 0 && current_char < 96)
			{
				SpriteSourceSetTextureOffset(sprite->sprite_source, current_char);

				DGL_Graphics_SetCB_TransformMatrix(&matrix);
				MeshRender(sprite->mesh);

				++text_iter;

				Matrix2DConcat(&matrix, &offset, &matrix);
			}
		}
	}

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
	sprite->sprite_source = spriteSource;
}

void SpriteSetText(Sprite* sprite, const char* text)
{
	sprite->text = text;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
