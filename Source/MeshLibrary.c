//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.c
// Author(s):	Grant Joyner (g.joyner)
// Project:		Project 4
// Course:		CS230S24
//
// Copyright © 2024 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MeshLibrary.h"
#include "Mesh.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

#define MESH_LIST_SIZE 10

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct MeshLibrary
{
	const Mesh* meshList[MESH_LIST_SIZE];
	unsigned int meshCount;
} MeshLibrary;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static MeshLibrary meshes;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void MeshLibraryAdd(const Mesh* mesh);
static const Mesh* MeshLibraryFind(const char* meshName);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void MeshLibraryInit()
{
	// Set everything to 0
	meshes.meshCount = 0;
	for (unsigned int i = 0; i < MESH_LIST_SIZE; ++i)
	{
		meshes.meshList[i] = NULL;
	}
}

const Mesh* MeshLibraryBuild(const char* meshName)
{
	if (!meshName) { return NULL; }

	const Mesh* mesh = MeshLibraryFind(meshName);

	if (!mesh)
	{
		char filename[256] = "";
		sprintf_s(filename, _countof(filename), "Data/%s.txt", meshName);
		Stream stream = StreamOpen(filename);

		if (stream)
		{
			Mesh* new_mesh = MeshCreate();
			MeshRead(new_mesh, stream);

			MeshLibraryAdd(new_mesh);
			mesh = new_mesh;

			StreamClose(&stream);
		}
	}

	return mesh;
}

void MeshLibraryFreeAll()
{
	for (unsigned int i = 0; i < meshes.meshCount; ++i)
	{
		MeshFree((Mesh**)&meshes.meshList[i]);
	}
	MeshLibraryInit(); // Reset the mesh library
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void MeshLibraryAdd(const Mesh* mesh)
{
	meshes.meshList[meshes.meshCount] = mesh;
	++meshes.meshCount;
}

static const Mesh* MeshLibraryFind(const char* meshName)
{
	for (unsigned int i = 0; i < meshes.meshCount; ++i)
	{
		if (MeshIsNamed(meshes.meshList[i], meshName))
		{
			return meshes.meshList[i];
		}
	}

	return NULL;
}