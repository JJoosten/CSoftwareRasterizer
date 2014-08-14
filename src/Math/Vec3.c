#include "Vec3.h"
#include "../Defines.h"
#include <math.h>
#include <assert.h>


Vec3* Vec3_LoadZero( Vec3* const out)
{
	assert( out && "Vec3_LoadZero out == NULL");

	out->X = 0;
	out->Y = 0;
	out->Z = 0;

	return out;
}

Vec3* Vec3_LoadOne( Vec3* const out)
{
	assert( out && "Vec3_LoadOne out == NULL");

	out->X = 1;
	out->Y = 1;
	out->Z = 1;

	return out;
}

Vec3* Vec3_LoadXYZ( Vec3* const out, const float x, const float y, const float z)
{
	assert( out && "Vec3_LoadXYZ out == NULL");

	out->X = x;
	out->Y = y;
	out->Z = z;

	return out;
}

Vec3* Vec3_LoadScalar( Vec3* const out, const float x)
{
	assert( out && "Vec3_LoadScalar out == NULL");

	out->X = x;
	out->Y = x;
	out->Z = x;

	return out;
}

Vec3* Vec3_LoadArray( Vec3* const out, const float* const xyz)
{
	assert( out && "Vec3_LoadArray out == NULL");
	assert( xyz && "Vec3_LoadArray xyz == NULL");
	
	out->X = xyz[0];
	out->Y = xyz[1];
	out->Z = xyz[2];

	return out;
}

Vec3* Vec3_LoadForward( Vec3* const out)
{
	assert( out && "Vec3_LoadForward out == NULL");

	out->X = 0;
	out->Y = 0;
	out->Z = -1;

	return out;
}

Vec3* Vec3_LoadLeft( Vec3* const out)
{
	assert( out && "Vec3_LoadLeft out == NULL");

	out->X = -1;
	out->Y = 0;
	out->Z = 0;

	return out;
}

Vec3* Vec3_LoadUp( Vec3* const out)
{
	assert( out && "Vec3_LoadUp out == NULL");

	out->X = 0;
	out->Y = 1;
	out->Z = 0;

	return out;
}


Vec3* Vec3_Copy( Vec3* const out, const Vec3* const a)
{
	assert( out && "Vec3_Copy a == NULL");
	assert( a && "Vec3_Copy a == NULL");

	Vec3_LoadArray( out, a->XYZ);

	return out;
}


Vec3* Vec3_Add( Vec3* const out, const Vec3* const a, const Vec3* const b)
{
	assert( out && "Vec3_Add out == NULL");
	assert( a && "Vec3_Add a == NULL");
	assert( b && "Vec3_Add b == NULL");

	out->X = a->X + b->X;
	out->Y = a->Y + b->Y;
	out->Z = a->Z + b->Z;

	return out;
}

Vec3* Vec3_Sub( Vec3* const out, const Vec3* const a, const Vec3* const b)
{
	assert( out && "Vec3_Sub out == NULL");
	assert( a && "Vec3_Sub a == NULL");
	assert( b && "Vec3_Sub b == NULL");

	out->X = a->X - b->X;
	out->Y = a->Y - b->Y;
	out->Z = a->Z - b->Z;

	return out;
}

Vec3* Vec3_Mul( Vec3* const out, const Vec3* const a, const Vec3* const b)
{
	assert( out && "Vec3_Mul out == NULL");
	assert( a && "Vec3_Mul a == NULL");
	assert( b && "Vec3_Mul b == NULL");

	out->X = a->X * b->X;
	out->Y = a->Y * b->Y;
	out->Z = a->Z * b->Z;

	return out;
}


Vec3* Vec3_MulByFloat( Vec3* const out, const Vec3* const a, const float x)
{
	assert( out && "Vec3_MulByFloat out == NULL");
	assert( a && "Vec3_MulByFloat a == NULL");
	
	out->X = a->X * x;
	out->Y = a->Y * x;
	out->Z = a->Z * x;

	return out;
}

Vec3* Vec3_DivByFloat( Vec3* const out, const Vec3* const a, const float w)
{
	assert( out && "Vec3_Div out == NULL");
	assert( a && "Vec3_Div a == NULL");
	assert( w != 0.0f && "Vec4_Div w == NULL");

	out->X = a->X / w;
	out->Y = a->Y / w;
	out->Z = a->Z / w;

	return out;
}

Vec3* Vec3_Scale( Vec3* const out, const Vec3* const a, const float b)
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

Vec3* Vec3_Cross( Vec3* const out, const Vec3* const a, const Vec3* const b)
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

Vec3* Vec3_Normalize( Vec3* const out, const Vec3* const a)
{
	const float lengthSqrt = Vec3_LengthSqr(a);
	
	assert( out && "Vec3_Normalize out == NULL");
	assert( a && "Vec3_Normalize a == NULL");

	if( lengthSqrt > 0.0f)
	{
		const float oneOverLength = 1.0f / sqrtf(lengthSqrt);
		Vec3_Scale( out, a, oneOverLength);
	}

	return out;
}

float Vec3_Length( const Vec3* const a)
{
	assert( a && "Vec3_Normalize a == NULL");
	return (float)sqrt( Vec3_Dot( a, a));
}

float Vec3_LengthSqr( const Vec3* const a)
{
	assert( a && "Vec3_Normalize a == NULL");
	return Vec3_Dot( a, a);
}