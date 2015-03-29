#ifndef CSR_OBJ_LOADING_H
#define CSR_OBJ_LOADING_H

#include "../VertexData/Mesh.h"

typedef struct
{
	char* Name;
	unsigned int NameLength;

	char* MaterialName;
	unsigned int MaterialNameLength;

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
	
	unsigned int NumGroupsInLinkedList;
	OBJGroup* Groups;
	
	void* NextObject;

} OBJObject;

typedef struct
{
	unsigned int NumObjectsInLinkedList;
	OBJObject* Objects;

	char* MaterialFilePath;
	unsigned int MaterialFilePathLength;
} OBJFile;

OBJFile* OBJFile_Load( const char* const objFile);
void OBJFile_Unload( OBJFile* objFile);


// Mesh extension
Mesh* Mesh_CreateFromOBJGroup( OBJObject* const objObject, OBJGroup* const objGroup);

#endif