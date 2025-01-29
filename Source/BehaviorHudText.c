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
#include "Sprite.h"
#include "Entity.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

typedef enum HudTextStates
{
	HUD_TEXT_INVALID = -1,
	HUD_TEXT_IDLE,
} HudTextStates;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct BehaviorHudText
{
	Behavior base;
	ScoreSystemId score_system_id; // Should be ScoreSystemId
	char format[32];
	char display_string[32];
	unsigned display_value;
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

static void BehaviorHudTextInit(Behavior* behavior);
static void BehaviorHudTextUpdate(Behavior* behavior, float dt);
static void BehaviorHudTextExit(Behavior* behavior);
static void BehaviorHudTextUpdateText(BehaviorHudText* behavior_hud_text);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Behavior* BehaviorHudTextCreate(void)
{
	BehaviorHudText* behavior = (BehaviorHudText*)calloc(1, sizeof(BehaviorHudText));
	if (!behavior) { return NULL; }

	behavior->base.memorySize = sizeof(BehaviorHudText);
	behavior->base.stateCurr = HUD_TEXT_INVALID;
	behavior->base.stateNext = HUD_TEXT_INVALID;
	behavior->base.onInit = BehaviorHudTextInit;
	behavior->base.onUpdate = BehaviorHudTextUpdate;
	behavior->base.onExit = BehaviorHudTextExit;

	behavior->score_system_id = SCORE_SYSTEM_ID_INVALID;

	return (Behavior*)behavior;
}

void BehaviorHudTextRead(Behavior* behavior, Stream stream)
{
	BehaviorRead(behavior, stream);
	BehaviorHudText* behavior_hud_text = (BehaviorHudText*)behavior;

	strcpy_s((char*)&(behavior_hud_text->format), _countof(behavior_hud_text->format), StreamReadToken(stream));
	/*
	char* text_iter = behavior_hud_text->format;
	while (*text_iter) {
		if (*text_iter == 96) { *text_iter = ' '; }
		++text_iter;
	}
	*/

	behavior_hud_text->score_system_id = StreamReadInt(stream);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void BehaviorHudTextInit(Behavior* behavior)
{
	BehaviorHudText* behavior_hud_text = (BehaviorHudText*)behavior;
	BehaviorHudTextUpdateText(behavior_hud_text);
	SpriteSetText(EntityGetSprite(behavior_hud_text->base.parent), behavior_hud_text->display_string);
}

void BehaviorHudTextUpdate(Behavior* behavior, float dt)
{
	UNREFERENCED_PARAMETER(dt);
	BehaviorHudText* behavior_hud_text = (BehaviorHudText*)behavior;
	if (behavior_hud_text->display_value != ScoreSystemGetValue(behavior_hud_text->score_system_id))
	{
		BehaviorHudTextUpdateText(behavior_hud_text);
	}
}

void BehaviorHudTextExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}

void BehaviorHudTextUpdateText(BehaviorHudText* behavior_hud_text)
{
	if (!behavior_hud_text || behavior_hud_text->score_system_id == SCORE_SYSTEM_ID_INVALID) { return; }

	behavior_hud_text->display_value = ScoreSystemGetValue(behavior_hud_text->score_system_id);
	sprintf_s(behavior_hud_text->display_string, _countof(behavior_hud_text->display_string),
		behavior_hud_text->format, behavior_hud_text->display_value);
}