#ifndef CSR_VERTEX_H
#define CSR_VERTEX_H

#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

typedef struct
{
	Vec3 Position;
	Vec3 Normal;
	Vec2 UV;

} Vertex;

#endif //CSR_VERTEX_H