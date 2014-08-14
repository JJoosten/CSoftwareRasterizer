#ifndef CSR_VEC3_H
#define CSR_VEC3_H

#include "Vec2.h"

typedef struct
{
	union
	{
		float RGB[3];
		float XYZ[3];
		struct
		{
			float X, Y, Z;
		};
		struct 
		{
			float R, G, B;
		};
		Vec2 XY;
		Vec2 RG;
	};
} Vec3, RGB;


Vec3* Vec3_LoadZero( Vec3* const out);
Vec3* Vec3_LoadOne( Vec3* const out);
Vec3* Vec3_LoadXYZ( Vec3* const out, const float x, const float y, const float z);
Vec3* Vec3_LoadScalar( Vec3* const out, const float x);
Vec3* Vec3_LoadArray( Vec3* const out, const float* const xyz);
Vec3* Vec3_LoadForward( Vec3* const out);
Vec3* Vec3_LoadLeft( Vec3* const out);
Vec3* Vec3_LoadUp( Vec3* const out);

Vec3* Vec3_Copy( Vec3* const out, const Vec3* const a);

Vec3* Vec3_Add( Vec3* const out, const Vec3* const a, const Vec3* const b);
Vec3* Vec3_Sub( Vec3* const out, const Vec3* const a, const Vec3* const b);

Vec3* Vec3_Mul( Vec3* const out, const Vec3* const a, const Vec3* const b);
Vec3* Vec3_DivByFloat( Vec3* const out, const Vec3* const a, const float w);
Vec3* Vec3_Scale( Vec3* const out, const Vec3* const a, const float b);

float Vec3_Dot( const Vec3* const a, const Vec3* const b);
Vec3* Vec3_Cross( Vec3* const out, const Vec3* const a, const Vec3* const b);
Vec3* Vec3_Normalize( Vec3* const out, const Vec3* const a);

float Vec3_Length( const Vec3* const a);
float Vec3_LengthSqr( const Vec3* const a);

#endif //CSR_VEC3_H