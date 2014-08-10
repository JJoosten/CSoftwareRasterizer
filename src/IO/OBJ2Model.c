#include "OBJ2Model.h"
#include "../VertexData/IndexBuffer.h"
#include "../VertexData/VertexBuffer.h"

#include <stdlib.h>
#include <string>

Mesh* CreateMeshFromOBJGroup( OBJObject* objObject, OBJGroup* objGroup)
{
	// reconstruct vertex buffer 
	//VertexBuffer* vertexBuffer = malloc(sizeof(VertexBuffer));

	// reconstruct index buffer
	//IndexBuffer* indexBuffer = malloc(sizeof(IndexBuffer));

	unsigned int numIndices = objGroup->NumFaces * objGroup->NumIndicesPerFace;

	//unsigned int indices = malloc(sizeof(unsigned int) * objGroup->NumFaces * objGroup->NumIndicesPerFace);

	unsigned int i = 0;
	for( i; i < numIndices; ++i)
	{
		Vertex vertex;
		memset( &vertex, 0, sizeof(Vertex));
		
		if( objObject->NumUVs > 0)
			vertex.Position = objObject->Positions[objGroup->PositionIndices[i]];
		if( objObject->NumNormals > 0)
			vertex.Normal = objObject->Normals[objGroup->NormalIndices[i]];
		if( objObject->NumUVs > 0)
			vertex.UV = objObject->UVs[objGroup->UVIndices[i]];

		printf("test");
	}
}


