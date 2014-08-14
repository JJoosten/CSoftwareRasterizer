#include "Vec4.h"
#include "../Defines.h"
#include <math.h>
#include <assert.h>


Vec4* Vec4_LoadZero( Vec4* const out)
{
	assert( out && "Vec4_LoadZero out == NULL");

	out->X = 0;
	out->Y = 0;
	out->Z = 0;
	out->W = 0;

	return out;
}

Vec4* Vec4_LoadOne( Vec4* const out)
{
	assert( out && "Vec4_LoadOne out == NULL");

	out->X = 1;
	out->Y = 1;
	out->Z = 1;
	out->W = 1;

	return out;
}


Vec4* Vec4_LoadVec3( Vec4* const out, const Vec3* const xyz, const float w)
{
	out->X = xyz->X;
	out->Y = xyz->Y;
	out->Z = xyz->Z;
	out->W = w;

	return out;
}

Vec4* Vec4_LoadXYZW( Vec4* const out, const float x, const float y, const float z, const float w)
{
	assert( out && "Vec4_LoadXYZ out == NULL");

	out->X = x;
	out->Y = y;
	out->Z = z;
	out->W = w;

	return out;
}

Vec4* Vec4_LoadScalar( Vec4* const out, const float x)
{
	assert( out && "Vec4_LoadScalar out == NULL");

	out->X = x;
	out->Y = x;
	out->Z = x;
	out->W = x;

	return out;
}

Vec4* Vec4_LoadArray( Vec4* const out, const float* const xyzw)
{
	assert( out && "Vec4_LoadArray out == NULL");
	assert( xyzw && "Vec4_LoadArray xyzw == NULL");
	
	out->X = xyzw[0];
	out->Y = xyzw[1];
	out->Z = xyzw[2];
	out->W = xyzw[3];

	return out;
}

Vec4* Vec4_LoadForward( Vec4* const out)
{
	assert( out && "Vec4_LoadForward out == NULL");

	out->X = 0;
	out->Y = 0;
	out->Z = -1;
	out->W = 1;

	return out;
}

Vec4* Vec4_LoadLeft( Vec4* const out)
{
	assert( out && "Vec4_LoadLeft out == NULL");

	out->X = -1;
	out->Y = 0;
	out->Z = 0;
	out->W = 1;

	return out;
}

Vec4* Vec4_LoadUp( Vec4* const out)
{
	assert( out && "Vec4_LoadUp out == NULL");

	out->X = 0;
	out->Y = 1;
	out->Z = 0;
	out->W = 1;

	return out;
}


Vec4* Vec4_Copy( Vec4* const out, const Vec4* const a)
{
	assert( out && "Vec4_Copy a == NULL");
	assert( a && "Vec4_Copy a == NULL");

	Vec4_LoadArray( out, a->XYZW);

	return out;
}


Vec4* Vec4_Add( Vec4* const out, const Vec4* const a, const Vec4* const b)
{
	assert( out && "Vec4_Add out == NULL");
	assert( a && "Vec4_Add a == NULL");
	assert( b && "Vec4_Add b == NULL");

	out->X = a->X + b->X;
	out->Y = a->Y + b->Y;
	out->Z = a->Z + b->Z;
	out->W = a->W + b->W;

	return out;
}

Vec4* Vec4_Sub( Vec4* const out, const Vec4* const a, const Vec4* const b)
{
	assert( out && "Vec4_Sub out == NULL");
	assert( a && "Vec4_Sub a == NULL");
	assert( b && "Vec4_Sub b == NULL");

	out->X = a->X - b->X;
	out->Y = a->Y - b->Y;
	out->Z = a->Z - b->Z;
	out->W = a->W - b->W;

	return out;
}

Vec4* Vec4_Mul( Vec4* const out, const Vec4* const a, const Vec4* const b)
{
	assert( out && "Vec4_Mul out == NULL");
	assert( a && "Vec4_Mul a == NULL");
	assert( b && "Vec4_Mul b == NULL");

	out->X = a->X * b->X;
	out->Y = a->Y * b->Y;
	out->Z = a->Z * b->Z;
	out->W = a->W * b->W;

	return out;
}


Vec4* Vec4_DivByFloat( Vec4* const out, const Vec4* const a, const float w)
{
	assert( out && "Vec4_Div out == NULL");
	assert( a && "Vec4_Div a == NULL");
	assert( w != 0.0f && "Vec4_Div w == NULL");

	out->X = a->X / w;
	out->Y = a->Y / w;
	out->Z = a->Z / w;
	out->W = a->W / w;

	return out;
}

Vec4* Vec4_Scale( Vec4* const out, const Vec4* const a, const float b)
{
	assert( out && "Vec4_Scale out == NULL");
	assert( a && "Vec4_Scale a == NULL");
	assert( b && "Vec4_Scale b == NULL");

	out->X = a->X * b;
	out->Y = a->Y * b;
	out->Z = a->Z * b;
	out->W = a->W * b;

	return out;
}

float Vec4_Dot( const Vec4* const a, const Vec4* const b)
{
	assert( a && "Vec4_Dot a == NULL");
	assert( b && "Vec4_Dot b == NULL");

	return a->X * b->X + a->Y * b->Y + a->Z * b->Z + a->W * b->W;
}


Vec4* Vec4_Normalize( Vec4* const out, const Vec4* const a)
{
	const float lengthSqrt = Vec4_LengthSqr(a);
	
	assert( out && "Vec4_Normalize out == NULL");
	assert( a && "Vec4_Normalize a == NULL");

	if( lengthSqrt > 0.0f)
	{
		const float oneOverLength = 1.0f / sqrtf(lengthSqrt);
		Vec4_Scale( out, a, oneOverLength);
	}

	return out;
}

float Vec4_Length( const Vec4* const a)
{
	assert( a && "Vec4_Normalize a == NULL");
	return (float)sqrt( Vec4_Dot( a, a));
}

float Vec4_LengthSqr( const Vec4* const a)
{
	assert( a && "Vec4_Normalize a == NULL");
	return Vec4_Dot( a, a);
}