#ifndef CSR_MESH_H
#define CSR_MESH_H

#include "VertexBuffer.h"
#include "IndexBuffer.h"

typedef struct
{
	VertexBuffer* VertexBuffer;
	IndexBuffer* IndexBuffer;
	unsigned int NumTriangles;
} Mesh;

Mesh* Mesh_Create( Vertex* const verticesTransferedOwnership, const unsigned int numVertices, unsigned short* const indicesTransferedOwnership, const unsigned int numIndices);
void Mesh_Destroy( Mesh* const mesh);

#endif //CSR_MESH_H