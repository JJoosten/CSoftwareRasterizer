#include "Vec2.h"
#include "../Defines.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>


Vec2* Vec2_LoadZero( Vec2* const out)
{
	assert( out && "Vec2_LoadZero out == NULL");

	out->X = 0;
	out->Y = 0;

	return out;
}

Vec2* Vec2_LoadOne( Vec2* const out)
{
	assert( out && "Vec2_LoadOne out == NULL");

	out->X = 1;
	out->Y = 1;

	return out;
}

Vec2* Vec2_LoadXYZ( Vec2* const out, const float x, const float y, const float z)
{
	assert( out && "Vec2_LoadXY out == NULL");

	out->X = x;
	out->Y = y;

	return out;
}

Vec2* Vec2_LoadScalar( Vec2* const out, const float x)
{
	assert( out && "Vec2_LoadScalar out == NULL");

	out->X = x;
	out->Y = x;

	return out;
}

Vec2* Vec2_LoadArray( Vec2* const out, const float* const xyz)
{
	assert( out && "Vec2_LoadArray out == NULL");
	assert( xyz && "Vec2_LoadArray xyz == NULL");
	
	out->X = xyz[0];
	out->Y = xyz[1];

	return out;
}

Vec2* Vec2_LoadLeft( Vec2* const out)
{
	assert( out && "Vec2_LoadLeft out == NULL");

	out->X = -1;
	out->Y = 0;

	return out;
}

Vec2* Vec2_LoadUp( Vec2* const out)
{
	assert( out && "Vec2_LoadUp out == NULL");

	out->X = 0;
	out->Y = 1;

	return out;
}


Vec2* Vec2_Copy( Vec2* const out, const Vec2* const a)
{
	assert( out && "Vec2_Copy a == NULL");
	assert( a && "Vec2_Copy a == NULL");

	Vec2_LoadArray( out, a->XY);

	return out;
}


Vec2* Vec2_Add( Vec2* const out, const Vec2* const a, const Vec2* const b)
{
	assert( out && "Vec2_Add out == NULL");
	assert( a && "Vec2_Add a == NULL");
	assert( b && "Vec2_Add b == NULL");

	out->X = a->X + b->X;
	out->Y = a->Y + b->Y;

	return out;
}

Vec2* Vec2_Sub( Vec2* const out, const Vec2* const a, const Vec2* const b)
{
	assert( out && "Vec2_Sub out == NULL");
	assert( a && "Vec2_Sub a == NULL");
	assert( b && "Vec2_Sub b == NULL");

	out->X = a->X - b->X;
	out->Y = a->Y - b->Y;

	return out;
}

Vec2* Vec2_Mul( Vec2* const out, const Vec2* const a, const Vec2* const b)
{
	assert( out && "Vec2_Mul out == NULL");
	assert( a && "Vec2_Mul a == NULL");
	assert( b && "Vec2_Mul b == NULL");

	out->X = a->X * b->X;
	out->Y = a->Y * b->Y;

	return out;
}

Vec2* Vec2_Scale( Vec2* const out, const Vec2* const a, const float b)
{
	assert( out && "Vec2_Scale out == NULL");
	assert( a && "Vec2_Scale a == NULL");
	assert( b && "Vec2_Scale b == NULL");

	out->X = a->X * b;
	out->Y = a->Y * b;

	return out;
}

float Vec2_Dot( const Vec2* const a, const Vec2* const b)
{
	assert( a && "Vec2_Dot a == NULL");
	assert( b && "Vec2_Dot b == NULL");

	return a->X * b->X + a->Y * b->Y;
}


Vec2* Vec2_Normalize( Vec2* const out, const Vec2* const a)
{
	const float lengthSqrt = Vec2_LengthSqr(a);
	
	assert( out && "Vec2_Normalize out == NULL");
	assert( a && "Vec2_Normalize a == NULL");

	if( lengthSqrt > 0.0f)
	{
		const float oneOverLength = 1.0f / sqrtf(lengthSqrt);
		Vec2_Scale( out, a, oneOverLength);
	}

	return out;
}

float Vec2_Length( const Vec2* const a)
{
	assert( a && "Vec2_Normalize a == NULL");
	return (float)sqrt( Vec2_Dot( a, a));
}

float Vec2_LengthSqr( const Vec2* const a)
{
	assert( a && "Vec2_Normalize a == NULL");
	return Vec2_Dot( a, a);
}

// printf extension
void Printf_Vec2( const Vec2* const a)
{
	assert( a && "Printf_Vec2 a == NULL");

	printf("Vec2 X: %f Y: %f\n\n", a->X, a->Y);
}