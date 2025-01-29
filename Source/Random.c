//------------------------------------------------------------------------------
//
// File Name:	Random.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 5
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Random.h"
#include <time.h>

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

// Initialize the ...
void RandomInit()
{
	// Use current time
	// TODO: make this parameterized
	srand((unsigned int)time(NULL));
}

int RandomRange(int rangeMin, int rangeMax)
{
	// (float)rand() / (RAND_MAX + 1) generates a random number between 0 and 1 (exclusive)
	// Multiply by the range and add the minimum to get a random number in the desired range
	return (int)((float)rand() / (RAND_MAX + 1) * (rangeMax - rangeMin + 1) + rangeMin);
}

float RandomRangeFloat(float rangeMin, float rangeMax)
{
	// (float)rand() / (RAND_MAX) generates a random number between 0 and 1 (inclusive)
	// Multiply by the range and add the minimum to get a random number in the desired range
	return ((float)rand() / (RAND_MAX) * (rangeMax - rangeMin) + rangeMin);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

