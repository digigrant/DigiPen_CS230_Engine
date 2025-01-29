//------------------------------------------------------------------------------
//
// File Name:	Stream.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 1
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include <stdio.h>
#include "stdafx.h"
#include "Stream.h"
#include "Trace.h"
#include "Vector2D.h"

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

static char token_buffer[1024];

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Stream StreamOpen(const char* filePath)
{
	// Check if the file path is NULL
	if (!filePath) return NULL;
	
	// Open the file for reading
	Stream stream = NULL;

	_set_errno(0);
	
	if (fopen_s(&stream, filePath, "rt") != 0)
	{
		// If there was an error, trace the error message and return NULL
		char errorMsg[256];
		strerror_s(errorMsg, 256, errno);
		TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);

		return NULL;
	}

	return stream;
}

bool StreamReadBoolean(Stream stream)
{
	// Check if the stream is NULL
	if (!stream) return false;

	int value = 0;
	fscanf_s(stream, "%d", &value);

	return value != 0;
}

int StreamReadInt(Stream stream)
{
	// Check if the stream is NULL
	if (!stream) return 0;

	int value = 0;
	fscanf_s(stream, "%d", &value);

	return value;
}

float StreamReadFloat(Stream stream)
{
	// Check if the stream is NULL
	if (!stream) return 0;

	float value = 0.0f;
	fscanf_s(stream, "%f", &value);

	return value;
}

void StreamReadVector2D(Stream stream, Vector2D* v)
{
	// Check if the stream or vector is NULL
	if (!stream || !v) return;

	fscanf_s(stream, "%f %f", &v->x, &v->y);
}

void StreamReadColor(Stream stream, DGL_Color* color)
{
	// Check if the stream or color is NULL
	if (!stream || !color) return;

	fscanf_s(stream, "%f %f %f %f", &color->r, &color->g, &color->b, &color->a);
}

const char* StreamReadToken(Stream stream)
{
	// Check if the stream is NULL
	if (!stream) return NULL;

	token_buffer[0] = '\0';

	_set_errno(0);
	while (fgets(token_buffer, sizeof(token_buffer), stream))
	{
		if (!token_buffer)
		{
			// If there was an error, trace the error message and return NULL
			char errorMsg[256];
			strerror_s(errorMsg, 256, errno);
			TraceMessage("Error: StreamReadToken could not read token; %s", errorMsg);
		}

		if (token_buffer[0] != '\n') { break; }
	}

	size_t len = strlen(token_buffer);
	if (len > 0 && token_buffer[len - 1] == '\n')
	{
		token_buffer[len - 1] = '\0';
	}

	return token_buffer;
}

void StreamClose(Stream* stream)
{
	// Check if the stream is already closed
	if (!stream || !(*stream)) return;

	fclose(*stream);
	(*stream) = NULL;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

