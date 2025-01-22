//------------------------------------------------------------------------------
//
// File Name:	Mesh.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 2
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Mesh.h"
#include "Stream.h"
#include "DGL.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define MAX_NAME_LENGTH 32

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Mesh
{
	char name[MAX_NAME_LENGTH];
	DGL_Mesh* mesh_resource;
	DGL_DrawMode draw_mode;
} Mesh;

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
Mesh* MeshCreate()
{
	return (Mesh*)calloc(1, sizeof(Mesh)); // returns NULL if memory allocation fails
}

void MeshFree(Mesh** mesh)
{
	if (!mesh || !*mesh) return;

	// free mesh resource
	DGL_Graphics_FreeMesh(&((*mesh)->mesh_resource));
	free(*mesh);
	(*mesh) = NULL;
}

void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	// Name
	strcpy_s(mesh->name, _countof(mesh->name), name);

	// Mesh
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2) { -xHalfSize, -yHalfSize }, &(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { 0.0f, vSize },
		&(DGL_Vec2) {  xHalfSize,  yHalfSize }, &(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { uSize, 0.0f },
		&(DGL_Vec2) {  xHalfSize, -yHalfSize }, &(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { uSize, vSize });
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2) { -xHalfSize, -yHalfSize }, &(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { 0.0f, vSize },
		&(DGL_Vec2) { -xHalfSize,  yHalfSize }, &(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { 0.0f, 0.0f },
		&(DGL_Vec2) {  xHalfSize,  yHalfSize }, &(DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { uSize, 0.0f });
	mesh->mesh_resource = DGL_Graphics_EndMesh();

	// Draw Mode
	mesh->draw_mode = DGL_DM_TRIANGLELIST;
}

void MeshBuildSpaceship(Mesh* mesh)
{
	// Name
	strcpy_s(mesh->name, 10, "Spaceship");

	// Create a triangular, colored mesh.
	DGL_Graphics_StartMesh();
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2) { 0.5f, 0.0f }, &(DGL_Color) { 1.0f, 1.0f, 0.0f, 1.0f }, &(DGL_Vec2) { 0.0f, 0.0f },
		&(DGL_Vec2) { -0.5f, -0.5f }, &(DGL_Color) { 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { 0.0f, 0.0f },
		&(DGL_Vec2) { -0.5f, 0.5f }, &(DGL_Color) { 1.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2) { 0.0f, 0.0f }
	);
	mesh->mesh_resource = DGL_Graphics_EndMesh();

	// Draw Mode
	mesh->draw_mode = DGL_DM_TRIANGLELIST;
}

void MeshRead(Mesh* mesh, Stream stream)
{
	// Read "Mesh"
	char token[MAX_NAME_LENGTH];
	strcpy_s(token, _countof(token), StreamReadToken(stream));
	if (strcmp(token, "Mesh") == 0)
	{
		// Read name
		strcpy_s(mesh->name, _countof(mesh->name), StreamReadToken(stream));

		// Read number of vertices
		int num_vertices = StreamReadInt(stream);

		// Read vertices
		DGL_Graphics_StartMesh();
		for (int i = 0; i < num_vertices; ++i)
		{
			Vector2D position, uv;
			DGL_Color color;

			StreamReadVector2D(stream, &position);
			StreamReadColor(stream, &color);
			StreamReadVector2D(stream, &uv);
			DGL_Graphics_AddVertex(&position, &color, &uv);
		}

		mesh->mesh_resource = DGL_Graphics_EndMesh();

		mesh->draw_mode = DGL_DM_TRIANGLELIST;
	}
	else if (strcmp(token, "Quad") == 0)
	{
		float xHalfSize = StreamReadFloat(stream);
		float yHalfSize = StreamReadFloat(stream);
		float uSize = StreamReadFloat(stream);
		float vSize = StreamReadFloat(stream);
		strcpy_s(token, _countof(token), StreamReadToken(stream));
		MeshBuildQuad(mesh, xHalfSize, yHalfSize, uSize, vSize, token);
	}
}

bool MeshIsNamed(const Mesh* mesh, const char* name)
{
	return (mesh && name) ? (strcmp(mesh->name, name) == 0) : false;
}

void MeshRender(const Mesh* mesh)
{
	DGL_Graphics_DrawMesh(mesh->mesh_resource, mesh->draw_mode);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
