#include "Mesh.h"

#include <stdlib.h>
#include <assert.h>

Mesh* Mesh_Create( Vertex* const verticesTransferedOwnership, const unsigned int numVertices, unsigned short* const indicesTransferedOwnership, const unsigned int numIndices)
{
	assert( verticesTransferedOwnership && "verticesTransferedOwnership is NULL");
	assert( indicesTransferedOwnership == NULL && numIndices > 0 && "indicesTransferedOwnership is NULL, indicesCount > 0");
	assert( indicesTransferedOwnership != NULL && numIndices == 0 && "indicesTransferedOwnership != NULL, indicesCount == 0");

	Mesh* mesh = malloc( sizeof(Mesh));
	mesh->NumTriangles = 0;
	mesh->VertexBuffer = malloc( sizeof(VertexBuffer));
	mesh->VertexBuffer->Vertices = verticesTransferedOwnership;
	mesh->VertexBuffer->NumVertices = numVertices;
	if(numIndices > 0)
	{
		mesh->IndexBuffer = malloc( sizeof(IndexBuffer));
		mesh->IndexBuffer->Indices = indicesTransferedOwnership;
		mesh->IndexBuffer->NumIndices = numIndices;
	}

	return mesh;
}

void Mesh_Destroy( Mesh* const mesh)
{
	assert( mesh && "Mesh is NULL");
	assert( mesh->VertexBuffer && "mesh->VertexBuffer is NULL");

	if(mesh->IndexBuffer != NULL)
	{
		free(mesh->IndexBuffer->Indices);
		free(mesh->IndexBuffer);
	}
	free(mesh->VertexBuffer->Vertices);
	free(mesh->VertexBuffer);
	free(mesh);
}