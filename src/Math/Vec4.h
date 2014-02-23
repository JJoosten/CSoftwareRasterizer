#ifndef CSR_VEC4_H
#define CSR_VEC4_H

#include "Vec3.h"

typedef struct
{
	union
	{
		float RGBA[4];
		float XYZW[4];
		struct
		{
			float X, Y, Z, W;
		};
		struct 
		{
			float R, G, B, A;
		};
	};
} Vec4, RGBA;


Vec4* Vec4_LoadZero( Vec4* const out);
Vec4* Vec4_LoadOne( Vec4* const out);
Vec4* Vec4_LoadVec3( Vec4* const out, const Vec3* const xyz, const float w);
Vec4* Vec4_LoadXYZW( Vec4* const out, const float x, const float y, const float z, const float w);
Vec4* Vec4_LoadScalar( Vec4* const out, const float x);
Vec4* Vec4_LoadArray( Vec4* const out, const float* const xyzw);
Vec4* Vec4_LoadForward( Vec4* const out);
Vec4* Vec4_LoadLeft( Vec4* const out);
Vec4* Vec4_LoadUp( Vec4* const out);

Vec4* Vec4_Copy( Vec4* const out, const Vec4* const a);

Vec4* Vec4_Add( Vec4* const out, const Vec4* const a, const Vec4* const b);
Vec4* Vec4_Sub( Vec4* const out, const Vec4* const a, const Vec4* const b);

Vec4* Vec4_Mul( Vec4* const out, const Vec4* const a, const Vec4* const b);
Vec4* Vec4_Scale( Vec4* const out, const Vec4* const a, const float b);

float Vec4_Dot( const Vec4* const a, const Vec4* const b);
Vec4* Vec4_Normalize( Vec4* const out, const Vec4* const a);

float Vec4_Length( const Vec4* const a);
float Vec4_LengthSqr( const Vec4* const a);

#endif //CSR_VEC4_H