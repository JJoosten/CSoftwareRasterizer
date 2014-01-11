#include "Vec3.h"
#include "../Defines.h"
#include <math.h>
#include <assert.h>

Vec3 Vec3_LoadZero( void)
{
	Vec3 vec = { 0, 0, 0 }; 
	return vec;
}

Vec3 Vec3_LoadXYZ( const float x, const float y, const float z)
{
	Vec3 vec = { x, y, z};
	return vec;
}

Vec3 Vec3_LoadScalar( const float x)
{
	Vec3 vec = { x, x, x };
	return vec;
}

Vec3 Vec3_LoadArray( const float* const xyz)
{
	Vec3 vec;
	assert( xyz && "Vec3_LoadArray xyz == NULL");
	vec.X = xyz[0];
	vec.Y = xyz[1];
	vec.Z = xyz[2];
	return vec;
}

Vec3 Vec3_LoadForward( void)
{
	Vec3 vec = { 0, 0, -1 };
	return vec;
}

Vec3 Vec3_LoadLeft( void)
{
	Vec3 vec = { -1, 0, 0 };
	return vec;
}

Vec3 Vec3_LoadUp( void)
{
	Vec3 vec = { 0, 1, 0 };
	return vec;
}

Vec3 Vec3_Copy( const Vec3* const a)
{
	Vec3 vec;
	assert( a && "Vec3_Copy a == NULL");
	vec = Vec3_LoadArray(a->XYZ);
	return vec;
}


Vec3* Vec3_Zero( Vec3* out)
{
	assert( out && "Vec3_Zero out == NULL");

	out->X = 0;
	out->Y = 0;
	out->Z = 0;

	return out;
}


Vec3* Vec3_Add( Vec3* out, const Vec3* const a, const Vec3* const b)
{
	assert( out && "Vec3_Add out == NULL");
	assert( a && "Vec3_Add a == NULL");
	assert( b && "Vec3_Add b == NULL");

	out->X = a->X + b->X;
	out->Y = a->Y + b->Y;
	out->Z = a->Z + b->Z;

	return out;
}

Vec3* Vec3_Sub( Vec3* out, const Vec3* const a, const Vec3* const b)
{
	assert( out && "Vec3_Sub out == NULL");
	assert( a && "Vec3_Sub a == NULL");
	assert( b && "Vec3_Sub b == NULL");

	out->X = a->X - b->X;
	out->Y = a->Y - b->Y;
	out->Z = a->Z - b->Z;

	return out;
}

Vec3* Vec3_Mul( Vec3* out, const Vec3* const a, const Vec3* const b)
{
	assert( out && "Vec3_Mul out == NULL");
	assert( a && "Vec3_Mul a == NULL");
	assert( b && "Vec3_Mul b == NULL");

	out->X = a->X * b->X;
	out->Y = a->Y * b->Y;
	out->Z = a->Z * b->Z;

	return out;
}

Vec3* Vec3_Scale( Vec3* out, const Vec3* const a, const float b)
{
	assert( out && "Vec3_Scale out == NULL");
	assert( a && "Vec3_Scale a == NULL");
	assert( b && "Vec3_Scale b == NULL");

	out->X = a->X * b;
	out->Y = a->Y * b;
	out->Z = a->Z * b;

	return out;
}

float Vec3_Dot( const Vec3* const a, const Vec3* const b)
{
	assert( a && "Vec3_Dot a == NULL");
	assert( b && "Vec3_Dot b == NULL");

	return a->X * b->X + a->Y * b->Y + a->Z * b->Z;
}

Vec3* Vec3_Cross( Vec3* out, const Vec3* const a, const Vec3* const b)
{
	float x;
	float y;
	float z;

	assert( out && "Vec3_Cross out == NULL");
	assert( a && "Vec3_Cross a == NULL");
	assert( b && "Vec3_Cross b == NULL");
	
	x = a->Y * b->Z - b->Y * a->Z;
	y = a->Y * b->X - b->Z * a->X;
	z = a->Y * b->Y - b->X * a->Y;

	out->X = x;
	out->Z = y;
	out->Y = z;

	return out;
}

Vec3* Vec3_Normalize( Vec3* out, const Vec3* const a)
{
	const float lengthSqrt = Vec3_LengthSqr(a);
	
	assert( out && "Vec3_Normalize out == NULL");
	assert( a && "Vec3_Normalize a == NULL");

	if( lengthSqrt > 0.0f)
	{
		const float oneOverLength = 1.0f / sqrtf(lengthSqrt);
		out = Vec3_Scale( out, a, oneOverLength);
	}

	return out;
}

float Vec3_Length( const Vec3* const a)
{
	return (float)sqrt( Vec3_Dot( a, a));
}

float Vec3_LengthSqr( const Vec3* const a)
{
	return Vec3_Dot( a, a);
}