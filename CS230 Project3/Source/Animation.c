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

Animation* AnimationCreate(void)
{
	return NULL;
}

void AnimationFree(Animation** animation)
{
	UNREFERENCED_PARAMETER(animation);
}

void AnimationRead(Animation* animation, Stream stream)
{
	UNREFERENCED_PARAMETER(animation);
	UNREFERENCED_PARAMETER(stream);
}

void AnimationSetParent(Animation* animation, Entity* parent)
{
	UNREFERENCED_PARAMETER(animation);
	UNREFERENCED_PARAMETER(parent);
}

void AnimationPlay(Animation* animation, int frameCount, float frameDuration, bool isLooping)
{
	UNREFERENCED_PARAMETER(animation);
	UNREFERENCED_PARAMETER(frameCount);
	UNREFERENCED_PARAMETER(frameDuration);
	UNREFERENCED_PARAMETER(isLooping);
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void AnimationUpdate(Animation* animation, float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(animation);
	UNREFERENCED_PARAMETER(dt);
}

bool AnimationIsDone(const Animation* animation)
{
	UNREFERENCED_PARAMETER(animation);
	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

