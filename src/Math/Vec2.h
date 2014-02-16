#ifndef CSR_VEC2_H
#define CSR_VEC2_H

typedef struct
{
	union
	{
		float XY[2];
		struct
		{
			float X, Y;
		};
	};
} Vec2;


Vec2* Vec2_LoadZero( Vec2* const out);
Vec2* Vec2_LoadOne( Vec2* const out);
Vec2* Vec2_LoadXY( Vec2* const out, const float x, const float y);
Vec2* Vec2_LoadScalar( Vec2* const out, const float x);
Vec2* Vec2_LoadArray( Vec2* const out, const float* const xy);
Vec2* Vec2_LoadLeft( Vec2* const out);
Vec2* Vec2_LoadUp( Vec2* const out);

Vec2* Vec2_Copy( Vec2* const out, const Vec2* const a);

Vec2* Vec2_Add( Vec2* const out, const Vec2* const a, const Vec2* const b);
Vec2* Vec2_Sub( Vec2* const out, const Vec2* const a, const Vec2* const b);

Vec2* Vec2_Mul( Vec2* const out, const Vec2* const a, const Vec2* const b);
Vec2* Vec2_Scale( Vec2* const out, const Vec2* const a, const float b);

float Vec2_Dot( const Vec2* const a, const Vec2* const b);
Vec2* Vec2_Normalize( Vec2* const out, const Vec2* const a);

float Vec2_Length( const Vec2* const a);
float Vec2_LengthSqr( const Vec2* const a);

#endif //CSR_VEC2_H