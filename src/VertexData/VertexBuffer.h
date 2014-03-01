#ifndef CSR_VERTEX_BUFFER_H
#define CSR_VERTEX_BUFFER_H

#include "Vertex.h"

typedef struct
{
	Vertex* Vertices;
	unsigned int NumVertices;
} VertexBuffer;

VertexBuffer* VertexBuffer_Create( Vertex* const verticesTransferOwnership, const unsigned int numVertices);
void VertexBuffer_Destroy( VertexBuffer* const vertexBuffer);

#endif //CSR_VERTEX_BUFFER_H