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
#include "DGL.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Mesh
{
	char name[32];
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
	// returns a pointer to a new Mesh object with all fields initialized to 0
	// returns NULL if memory allocation fails
	return (Mesh*)calloc(1, sizeof(Mesh));
}

void MeshFree(Mesh** mesh)
{
	// check if mesh is NULL or *mesh is NULL
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

void MeshRender(const Mesh* mesh)
{
	DGL_Graphics_DrawMesh(mesh->mesh_resource, mesh->draw_mode);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
