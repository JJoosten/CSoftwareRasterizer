#ifndef CSR_VEC3_H
#define CSR_VEC3_H

typedef struct sVec3
{
	union
	{
		float RGB[3];
		float XYZ[3];
		struct
		{
			float X, Y, Z;
		};
	};
} Vec3;

Vec3 Vec3Zero( void);
Vec3 Vec3Load( float x, float y, float z);
Vec3 Vec3LoadScalar( float x);
Vec3 Vec3LoadArray( const float* const xyz);
Vec3 Vec3Copy( const Vec3* const a);

Vec3* Vec3Mul( Vec3* out, const Vec3* const a, const Vec3* const b);
Vec3* Vec3Scale( Vec3* out, const Vec3* const a, const float b);

float Vec3Dot( const Vec3* const a, const Vec3* const b);
Vec3* Vec3Cross( Vec3* out, const Vec3* const a, const Vec3* const b);
Vec3* Vec3Normalize( Vec3* out, const Vec3* const a);

float Vec3Length( const Vec3* const a);
float Vec3LengthSqr( const Vec3* const a);

#endif //CSR_VEC3_H