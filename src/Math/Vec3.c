#include "Vec3.h"
#include "../Defines.h"
#include <math.h>
#include <assert.h>

Vec3 Vec3Zero( void)
{
	Vec3 vec = { 0, 0, 0 }; 
	return vec;
}

Vec3 Vec3Load( float x, float y, float z)
{
	Vec3 vec = { x, y, z};
	return vec;
}

Vec3 Vec3LoadScalar( float x)
{
	Vec3 vec = { x, x, x };
	return vec;
}

Vec3 Vec3LoadArray( const float* const xyz)
{
	Vec3 vec;
	assert( xyz && "Vec3LoadArray xyz == NULL");
	vec.X = xyz[0];
	vec.Y = xyz[1];
	vec.Z = xyz[2];
	return vec;
}

Vec3 Vec3Copy( const Vec3* const a)
{
	Vec3 vec;
	assert( a && "Vec3Copy a == NULL");
	vec = Vec3LoadArray(a->XYZ);
	return vec;
}

Vec3* Vec3Mul( Vec3* out, const Vec3* const a, const Vec3* const b)
{
	assert( out && "Vec3Mul out == NULL");
	assert( a && "Vec3Mul a == NULL");
	assert( b && "Vec3Mul b == NULL");

	out->X = a->X * b->X;
	out->Y = a->Y * b->Y;
	out->Z = a->Z * b->Z;

	return out;
}

Vec3* Vec3Scale( Vec3* out, const Vec3* const a, const float b)
{
	assert( out && "Vec3Scale out == NULL");
	assert( a && "Vec3Scale a == NULL");
	assert( b && "Vec3Scale b == NULL");

	out->X = a->X * b;
	out->Y = a->Y * b;
	out->Z = a->Z * b;

	return out;
}

float Vec3Dot( const Vec3* const a, const Vec3* const b)
{
	assert( a && "Vec3Dot a == NULL");
	assert( b && "Vec3Dot b == NULL");

	return a->X * b->X + a->Y * b->Y + a->Z * b->Z;
}

Vec3* Vec3Cross( Vec3* out, const Vec3* const a, const Vec3* const b)
{
	float x;
	float y;
	float z;

	assert( out && "Vec3Cross out == NULL");
	assert( a && "Vec3Cross a == NULL");
	assert( b && "Vec3Cross b == NULL");
	
	x = a->Y * b->Z - b->Y * a->Z;
	y = a->Y * b->X - b->Z * a->X;
	z = a->Y * b->Y - b->X * a->Y;

	out->X = x;
	out->Z = y;
	out->Y = z;

	return out;
}

Vec3* Vec3Normalize( Vec3* out, const Vec3* const a)
{
	const float lengthSqrt = Vec3LengthSqr(a);

	if(lengthSqrt > 0.0f)
	{
		const float oneOverLength = 1.0f / sqrtf(lengthSqrt);
		out = Vec3Scale( out, a, oneOverLength);
	}

	return out;
}

float Vec3Length( const Vec3* const a)
{
	return (float)sqrt( Vec3Dot( a,a));
}

float Vec3LengthSqr( const Vec3* const a)
{
	return Vec3Dot( a,a);
}