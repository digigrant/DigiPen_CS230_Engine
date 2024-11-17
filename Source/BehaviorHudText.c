//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 5
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "BehaviorHudText.h"
#include "Behavior.h"
#include "Stream.h"
#include "ScoreSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

typedef enum HudTextStates
{
	cHudTextInvalid = -1,
	cHudTextIdle
} HudTextStates;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct BehaviorHudText
{
	Behavior base;
	ScoreSystemId scoreSystemId; // Should be ScoreSystemId
	char format[32];
	char displayString[32];
	unsigned displayValue;
} BehaviorHudText;

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

Behavior* BehaviorHudTextCreate(void)
{
	return NULL;
}

void BehaviorHudTextRead(Behavior* behavior, Stream stream)
{
	UNREFERENCED_PARAMETER(behavior);
	UNREFERENCED_PARAMETER(stream);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------