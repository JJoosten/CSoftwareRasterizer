#ifndef CSR_VERTEX_H
#define CSR_VERTEX_H

#include "../Math/Vec4.h"
#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

typedef struct
{
	Vec3 Position;
	Vec3 Normal;
	Vec2 UV;

} Vertex;

typedef struct 
{
	Vec4 Position;
	Vec3 Normal;
	Vec2 UV;

} RasterVertex;

void RasterVertex_LoadVertex( RasterVertex* const out, const Vertex* const vertex);

#endif //CSR_VERTEX_H