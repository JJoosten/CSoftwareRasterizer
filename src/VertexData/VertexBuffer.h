#ifndef CSR_VERTEX_BUFFER_H
#define CSR_VERTEX_BUFFER_H

#include "Vertex.h"

typedef struct
{
	Vertex* Vertices;
	unsigned int NumVertices;
} VertexBuffer;

#endif //CSR_VERTEX_BUFFER_H