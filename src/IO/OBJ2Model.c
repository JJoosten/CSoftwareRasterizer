#include "OBJ2Model.h"
#include <string>

Mesh* CreateMeshFromObjGroup( OBJObject* objObject, OBJGroup* objGroup)
{
	Mesh* mesh = NULL;

	Vertex* vertices = (Vertex*)malloc(sizeof(Vertex) * objObject->NumPositions);
	Vertex* vertex = vertices;
	
	unsigned int numIndices = objGroup->NumFaces * objGroup->NumIndicesPerFace;
	unsigned short* indices = (unsigned short*)malloc(sizeof(unsigned short) * numIndices);

	int i = 0;
	for( i; i < objObject->NumPositions; ++i)
	{

		if(objObject->NumPositions > 0)
			vertex->Position = objObject->Positions[objGroup->PositionIndices[i]];
		if(objObject->NumUVs > 0)
			vertex->UV = objObject->UVs[objGroup->UVIndices[i]];
		if(objObject->NumNormals > 0)
			vertex->Normal = objObject->Normals[objGroup->NormalIndices[i]];
		
		// move further with the vertices
		++vertex;
	}

	// create vertex and index buffer
	mesh = Mesh_Create( vertices, objObject->NumPositions, indices, numIndices);
	
	return mesh;
}