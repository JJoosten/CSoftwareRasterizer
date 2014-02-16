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

#endif //CSR_MESH_H