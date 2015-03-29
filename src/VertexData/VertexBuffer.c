#include "VertexBuffer.h"

#include <stdlib.h>
#include <assert.h>

VertexBuffer* VertexBuffer_Create( Vertex* const verticesTransferOwnership, const unsigned int numVertices)
{
	VertexBuffer* vertexBuffer = malloc( sizeof(VertexBuffer));

	assert( verticesTransferOwnership && "verticesTransferOwnership is NULL");
	assert( numVertices && "numVertices is 0");

	vertexBuffer->Vertices = verticesTransferOwnership;
	vertexBuffer->NumVertices = numVertices;

	return vertexBuffer;
}

void VertexBuffer_Destroy( VertexBuffer* const vertexBuffer)
{
	assert( vertexBuffer && "vertexBuffer is NULL");
	assert( vertexBuffer->Vertices && "vertexBuffer->Vertices is NULL");

	free( vertexBuffer->Vertices);
	free( vertexBuffer);
}