#ifndef CSR_TRIANGLE_H
#define CSR_TRIANGLE_H

#include "Vertex.h"

typedef struct
{
	Vertex V1;
	Vertex V2;
	Vertex V3;
} Triangle;


typedef struct
{
	RasterVertex V1;
	RasterVertex V2;
	RasterVertex V3;
} RasterTriangle;

typedef struct
{
	Vec2 Edge;
	RasterVertex* Start;
	RasterVertex* End;
} RasterTriangleEdge;

#endif //CSR_TRIANGLE_H
