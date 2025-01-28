//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 5
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>

#include "BaseSystem.h"
#include "ScoreSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ScoreSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	unsigned score;
	unsigned high_score;
	unsigned wave_count;

} ScoreSystem;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static bool ScoreSystemInit(void);
static void ScoreSystemUpdate(float dt);
static void ScoreSystemRender(void);
static void ScoreSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static ScoreSystem instance =
{
	{ "ScoreSystem", ScoreSystemInit, ScoreSystemUpdate, ScoreSystemRender, ScoreSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

BaseSystem* ScoreSystemGetInstance()
{
	return (BaseSystem*)&instance;
}

void ScoreSystemClear(void)
{
	instance.score = 0;
	instance.high_score = 0;
	instance.wave_count = 0;
}

void ScoreSystemReset(void)
{
	if (instance.score > instance.high_score)
	{
		instance.high_score = instance.score;
	}

	instance.score = 0;
	instance.wave_count = 0;
}

unsigned ScoreSystemGetValue(ScoreSystemId valueId)
{
	switch (valueId)
	{
	case SCORE_SYSTEM_ID_SCORE:
		return instance.score;
	case SCORE_SYSTEM_ID_HIGH_SCORE:
		return instance.high_score;
	case SCORE_SYSTEM_ID_WAVE_COUNT:
		return instance.wave_count;
	default:
		return 0;
	}
}

void ScoreSystemIncreaseScore(unsigned amount)
{
	instance.score += amount;
}

void ScoreSystemIncreaseWave(void)
{
	instance.wave_count++;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static bool ScoreSystemInit(void)
{
	return true;
}

static void ScoreSystemUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

static void ScoreSystemRender(void)
{
}

static void ScoreSystemExit(void)
{
}

