//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 0
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Matrix2D.h"
#include "DGL.h"

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

void Matrix2DIdentity(Matrix2D* pResult)
{
	if (pResult == NULL) { return; }

	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			Matrix2DRowCol(pResult, r, c) = (r == c) ? 1.0f : 0.0f;
		}
	}
}

void Matrix2DTranspose(Matrix2D* pResult, const Matrix2D* pMtx)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(pMtx);
}

void Matrix2DConcat(Matrix2D* pResult, const Matrix2D* pMtx0, const Matrix2D* pMtx1)
{
	if (pResult == NULL) { return; }

	if (pResult == pMtx0 || pResult == pMtx1)
	{
		Matrix2D temp;
		Matrix2DConcat(&temp, pMtx0, pMtx1);
		*pResult = temp;
		return;
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			pResult->m[i][j] = 0;

			for (int k = 0; k < 4; ++k)
			{
				pResult->m[i][j] += pMtx0->m[i][k] * pMtx1->m[k][j];
			}
		}
	}
}

void Matrix2DTranslate(Matrix2D* pResult, float x, float y)
{
	if (pResult == NULL) { return; }

	Matrix2DIdentity(pResult);

	Matrix2DRowCol(pResult, 0, 3) = x;
	Matrix2DRowCol(pResult, 1, 3) = y;
}

void Matrix2DScale(Matrix2D* pResult, float x, float y)
{
	if (pResult == NULL) { return; }

	Matrix2DIdentity(pResult);

	Matrix2DRowCol(pResult, 0, 0) = x;
	Matrix2DRowCol(pResult, 1, 1) = y;
}

void Matrix2DRotDeg(Matrix2D* pResult, float angle)
{
	if (pResult == NULL) { return; }

	float radians = (angle * (float)M_PI) / 180.0f;
	Matrix2DRotRad(pResult, radians);
}

void Matrix2DRotRad(Matrix2D* pResult, float angle)
{
	if (pResult == NULL) { return; }

	Matrix2DIdentity(pResult);

	pResult->m[0][0] = (float)cos(angle);
	pResult->m[0][1] = (float)-sin(angle);
	pResult->m[1][0] = (float)sin(angle);
	pResult->m[1][1] = (float)cos(angle);
	pResult->m[2][2] = 1;
	pResult->m[3][3] = 1;
}

void Matrix2DMultVec(Vector2D* pResult, const Matrix2D* pMtx, const Vector2D* pVec)
{
	UNREFERENCED_PARAMETER(pResult);
	UNREFERENCED_PARAMETER(pMtx);
	UNREFERENCED_PARAMETER(pVec);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

