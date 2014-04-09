#ifndef CSR_OBJ_LOADING_H
#define CSR_OBJ_LOADING_H

#include "../VertexData/Mesh.h"

typedef struct
{
	char* Name;
	unsigned int NameLength;

	unsigned int NumFaces;
	unsigned int NumIndicesPerFace;
	unsigned int* PositionIndices;
	unsigned int* NormalIndices;
	unsigned int* UVIndices;
	
	void* NextGroup;
} OBJGroup;

typedef struct
{
	char* Name;
	unsigned int NameLength;
	
	unsigned int NumPositions;
	Vec3* Positions;

	unsigned int NumNormals;
	Vec3* Normals;

	unsigned int NumUVs;
	Vec2* UVs;
	
	unsigned int NumGroups;
	OBJGroup* Groups;
	
	void* NextObject;

} OBJObject;

typedef struct
{
	unsigned int NumObjects;
	OBJObject* Objects;

	char* MaterialFilePath;
	unsigned int MaterialFilePathLength;
} OBJFile;

OBJFile* Load_OBJFile( const char* const objFile);

#endif