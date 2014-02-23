#include "Vertex.h"


void RasterVertex_LoadVertex( RasterVertex* const out, const Vertex* const vertex)
{
	Vec4_LoadVec3( &out->Position, &vertex->Position, 1.0f);
	out->Normal = vertex->Normal;
	out->UV = vertex->UV;
}