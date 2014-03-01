#include "Mesh.h"

#include <stdlib.h>
#include <assert.h>

Mesh* Mesh_Create( Vertex* const verticesTransferedOwnership, const unsigned int numVertices, unsigned short* const indicesTransferedOwnership, const unsigned int numIndices)
{
	Mesh* mesh = malloc( sizeof(Mesh));

	assert( verticesTransferedOwnership && "verticesTransferedOwnership is NULL");
	assert( (indicesTransferedOwnership != NULL && numIndices > 0) && "indicesTransferedOwnership == NULL, indicesCount > 0");
	assert( (indicesTransferedOwnership != NULL && numIndices != 0) && "indicesTransferedOwnership != NULL, indicesCount == 0");

	mesh->VertexBuffer = VertexBuffer_Create( verticesTransferedOwnership, numVertices);
	mesh->NumTriangles = numVertices / 3;
	if(numIndices > 0)
	{
		mesh->IndexBuffer = IndexBuffer_Create( indicesTransferedOwnership, numIndices);
		mesh->NumTriangles = numIndices / 3;
	}

	return mesh;
}

void Mesh_Destroy( Mesh* const mesh)
{
	assert( mesh && "Mesh is NULL");
	assert( mesh->VertexBuffer && "mesh->VertexBuffer is NULL");

	if(mesh->IndexBuffer != NULL)
	{
		IndexBuffer_Destroy( mesh->IndexBuffer);
	}
	
	VertexBuffer_Destroy( mesh->VertexBuffer);

	free(mesh);
}