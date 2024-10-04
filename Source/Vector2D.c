//------------------------------------------------------------------------------
//
// File Name:	Vector2D.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 1
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Vector2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

// This function sets the coordinates of the 2D vector (pResult) to 0
void Vector2DZero(Vector2D* v)
{
	v->x = 0.0f;
	v->y = 0.0f;
}

// This function sets the coordinates of the 2D vector (pResult) to x & y
void Vector2DSet(Vector2D* v, float x, float y)
{
	v->x = x;
	v->y = y;
}

// In this function, pResult will be set to the opposite of pVec0 (e.g. x = -x & y = -y)
void Vector2DNeg(Vector2D* pResult, const Vector2D* pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;
}

// In this function, pResult will be the sum of pVec0 and pVec1 (x result = x0 + x1)
void Vector2DAdd(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;
}

// In this function, pResult will be the difference between pVec0 and pVec1 (specifically, pVec0 - pVec1)
void Vector2DSub(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// In this function, pResult will be the unit vector of pVec0
void Vector2DNormalize(Vector2D* pResult, const Vector2D* pVec0)
{
	// Calculate the length of the vector
	float length = sqrtf(pVec0->x * pVec0->x + pVec0->y * pVec0->y);
	// Divide the vector by its length to get the unit vector
	pResult->x = pVec0->x / length;
	pResult->y = pVec0->y / length;
}

// In this function, pResult will be the vector pVec0 scaled by the value 'scale'
void Vector2DScale(Vector2D* pResult, const Vector2D* pVec0, float scale)
{
	pResult->x = pVec0->x * scale;
	pResult->y = pVec0->y * scale;
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and added to pVec1
void Vector2DScaleAdd(Vector2D* pResult, const Vector2D* pVec0, float scale, const Vector2D* pVec1)
{
	pResult->x = pVec0->x * scale + pVec1->x;
	pResult->y = pVec0->y * scale + pVec1->y;
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and pVec1 will be subtracted from it
void Vector2DScaleSub(Vector2D* pResult, const Vector2D* pVec0, float scale, const Vector2D* pVec1)
{
	pResult->x = pVec0->x * scale - pVec1->x;
	pResult->y = pVec0->y * scale - pVec1->y;
}

// This function returns the length of the vector pVec0
float Vector2DLength(const Vector2D* pVec0)
{
	return sqrtf(pVec0->x * pVec0->x + pVec0->y * pVec0->y);
}

// This function returns the square of the length of the vector pVec0
float Vector2DSquareLength(const Vector2D* pVec0)
{
	return pVec0->x * pVec0->x + pVec0->y * pVec0->y;
}

// This function returns the distance between two points
float Vector2DDistance(const Vector2D* pVec0, const Vector2D* pVec1)
{
	float x = pVec1->x - pVec0->x;
	float y = pVec1->y - pVec0->y;
	return sqrtf(x * x + y * y);
}

// This function returns the distance squared between two points.
float Vector2DSquareDistance(const Vector2D* pVec0, const Vector2D* pVec1)
{
	float x = pVec1->x - pVec0->x;
	float y = pVec1->y - pVec0->y;
	return x * x + y * y;
}

// This function returns the dot product between pVec0 and pVec1
float Vector2DDotProduct(const Vector2D* pVec0, const Vector2D* pVec1)
{
	return pVec0->x * pVec1->x + pVec0->y * pVec1->y;
}

// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Degrees.
void Vector2DFromAngleDeg(Vector2D* pResult, float angle)
{
	float angleRad = angle * ((float)M_PI / 180.0f);
	pResult->x = cosf(angleRad);
	pResult->y = sinf(angleRad);
}

// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Radians.
void Vector2DFromAngleRad(Vector2D* pResult, float angle)
{
	pResult->x = cosf(angle);
	pResult->y = sinf(angle);
}

// This function computes the angle, in radians, of the specified vector.
float Vector2DToAngleRad(const Vector2D* pVec)
{
	return atan2f(pVec->y, pVec->x);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------