#include "IndexBuffer.h"

#include <stdlib.h>
#include <assert.h>

IndexBuffer* IndexBuffer_Create( unsigned short* const indicesTransferOwnership, const unsigned int numIndices)
{
	IndexBuffer* indexBuffer = malloc( sizeof(IndexBuffer));

	assert( indicesTransferOwnership && "indicesTransferOwnership is NULL");
	assert( numIndices && "numIndices is 0");

	indexBuffer->Indices = indicesTransferOwnership;
	indexBuffer->NumIndices = numIndices;

	return indexBuffer;
}

void IndexBuffer_Destroy( IndexBuffer* const indexBuffer)
{
	assert( indexBuffer && "indexBuffer is NULL");
	assert( indexBuffer->Indices && "indexBuffer->Indices is NULL");

	free( indexBuffer->Indices);
	free( indexBuffer);
}