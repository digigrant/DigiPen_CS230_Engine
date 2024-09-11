//------------------------------------------------------------------------------
//
// File Name:	Animation.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 3
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Animation.h"
#include "Stream.h"
#include "Entity.h"
#include "Sprite.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Animation
{
	// Pointer to the parent Entity associated with the Animation component.
	Entity* parent;

	// The current frame being displayed.
	unsigned int frameIndex;

	// The maximum number of frames in the sequence.
	unsigned int frameCount;

	// The time remaining for the current frame.
	float frameDelay;

	// The amount of time to display each successive frame.
	float frameDuration;

	// Whether the animation should loop.
	bool isLooping;

	// Whether the animation is currently playing.
	bool isPlaying;

	// Whether the animation has finished playing.
	bool isDone;
} Animation;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void AnimationAdvanceFrame(Animation* animation);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Animation* AnimationCreate(void)
{
	Animation* animation = (Animation*)calloc(1, sizeof(Animation));

	return animation;
}

void AnimationFree(Animation** animation)
{
	if (!animation || !(*animation)) { return; }

	free(*animation);
	(*animation) = NULL;
}

void AnimationRead(Animation* animation, Stream stream)
{
	animation->frameIndex = StreamReadInt(stream);
	animation->frameCount = StreamReadInt(stream);
	animation->frameDelay = StreamReadFloat(stream);
	animation->frameDuration = StreamReadFloat(stream);
	animation->isPlaying = StreamReadBoolean(stream);
	animation->isLooping = StreamReadBoolean(stream);
}

void AnimationSetParent(Animation* animation, Entity* parent)
{
	if (!animation) { return; }

	animation->parent = parent;
}

void AnimationPlay(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
	if (!animation) { return; }

	animation->frameIndex = 0;
	animation->frameCount = frameCount;
	animation->frameDelay = frameDuration;
	animation->frameDuration = frameDuration;
	animation->isPlaying = true;
	animation->isLooping = isLooping;
	animation->isDone = false;

	// Set the parent's sprite frame index to the first frame
	SpriteSetFrame(EntityGetSprite(animation->parent), 0);
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void AnimationUpdate(Animation* animation, float dt)
{
	if (!animation) { return; }

	animation->isDone = false;

	if (!animation->isPlaying) { return; }

	animation->frameDelay -= dt;

	if (animation->frameDelay <= 0.0f)
	{
		AnimationAdvanceFrame(animation);
	}
}

bool AnimationIsDone(const Animation* animation)
{
	if (!animation) { return false; }

	return animation->isDone;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void AnimationAdvanceFrame(Animation* animation)
{
	if (!animation) { return; }

	// Increment the frame index
	animation->frameIndex++;

	// If the frame index is greater than the frame count, then the animation is done
	if (animation->frameIndex >= animation->frameCount)
	{
		animation->isDone = true;

		// If the animation is not looping, then stop playing
		if (!animation->isLooping)
		{
			animation->isPlaying = false;
			animation->frameDelay = 0.0f;
			return;
		}

		animation->frameIndex = 0;
	}

	// Set the parent's sprite frame index to the current frame
	SpriteSetFrame(EntityGetSprite(animation->parent), animation->frameIndex);

	// Reset the frame delay (with any overflow - Doug's better solution)
	animation->frameDelay += animation->frameDuration;
}
