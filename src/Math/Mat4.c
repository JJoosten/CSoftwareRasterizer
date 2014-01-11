#include "Mat4.h"
#include <string.h>
#include <math.h>
#include <assert.h>

Mat4 Mat4_LoadZero( void)
{
	Mat4 mat;
	memset( &mat, 0, sizeof(float) * 16);

	return mat;
}

Mat4 Mat4_LoadIdentity( void)
{
	Mat4 mat;
	memset( &mat, 0, sizeof(float) * 16);
	mat.ColumnMajor[0] = 1.0f;
	mat.ColumnMajor[5] = 1.0f;
	mat.ColumnMajor[10] = 1.0f;
	mat.ColumnMajor[15] = 1.0f;
	return mat;
}

Mat4 Mat4_LoadOrtho( const float left, const float right, const float top, const float bottom, const float near, const float far)
{
	Mat4 mat;
	mat.ColumnMajor[0] = 2.0f / (right - left); mat.ColumnMajor[4] = 0.0f;					mat.ColumnMajor[ 8] = 0.0f;					mat.ColumnMajor[12] = -((right + left) / (right - left));
	mat.ColumnMajor[1] = 0.0f;					mat.ColumnMajor[5] = 2.0f / (top - bottom); mat.ColumnMajor[ 9] = 0.0f;					mat.ColumnMajor[13] = -((top + bottom) / (top - bottom));
	mat.ColumnMajor[2] = 0.0f;					mat.ColumnMajor[6] = 0.0f;					mat.ColumnMajor[10] = 1.0f / (far - near);	mat.ColumnMajor[14] = -(near / (far - near));
	mat.ColumnMajor[3] = 0.0f;					mat.ColumnMajor[7] = 0.0f;					mat.ColumnMajor[11] = 0.0f;					mat.ColumnMajor[15] = 1.0f;
	return mat;
}

Mat4 Mat4_LoadPerspective( const float fovInDegrees, const float aspectRatio, const float near, const float far)
{
	const float f = 1.0f / tanf( 0.0174532925 * fovInDegrees / 2.0f);

	Mat4 mat;
	mat.ColumnMajor[0] = f / aspectRatio;	mat.ColumnMajor[4] = 0.0f;	mat.ColumnMajor[ 8] = 0.0f;							mat.ColumnMajor[12] = 0.0f;
	mat.ColumnMajor[1] = 0.0f;				mat.ColumnMajor[5] = f;		mat.ColumnMajor[ 9] = 0.0f;							mat.ColumnMajor[13] = 0.0f;
	mat.ColumnMajor[2] = 0.0f;				mat.ColumnMajor[6] = 0.0f;	mat.ColumnMajor[10] = (far + near) / (near - far);	mat.ColumnMajor[14] = 2 * far * near / (near - far);
	mat.ColumnMajor[3] = 0.0f;				mat.ColumnMajor[7] = 0.0f;	mat.ColumnMajor[11] = -1.0f;						mat.ColumnMajor[15] = 0.0f;
	return mat;
}

Mat4 Mat4_LoadLookAt( const Vec3* const target, const Vec3* const eye, const Vec3* const up)
{
	Mat4 mat;
	Vec3 direction, localLeft, localUp;

	assert( target && "Mat4_LookAt target == NULL");
	assert( target && "Mat4_LookAt eye == NULL");
	assert( target && "Mat4_LookAt up == NULL");

	Vec3_Cross( &direction, target, eye);
	Vec3_Normalize( &direction, &direction);
	
	Vec3_Cross( &localLeft, &direction, up);
	Vec3_Normalize( &localLeft, &localLeft);
	
	Vec3_Cross( &localUp, &localLeft, &direction);

	mat.ColumnMajor[0] = localLeft.X;	mat.ColumnMajor[4] = localLeft.Y;	mat.ColumnMajor[ 8] = localLeft.Z;	mat.ColumnMajor[12] = -eye->X;
	mat.ColumnMajor[1] = localUp.X;		mat.ColumnMajor[5] = localUp.Y;		mat.ColumnMajor[ 9] = localUp.Z;	mat.ColumnMajor[13] = -eye->Y;
	mat.ColumnMajor[2] = -direction.X;	mat.ColumnMajor[6] = -direction.Y;	mat.ColumnMajor[10] = -direction.Z;	mat.ColumnMajor[14] = -eye->Z;
	mat.ColumnMajor[3] = 0.0f;			mat.ColumnMajor[7] = 0.0f;			mat.ColumnMajor[11] = 0.0f;			mat.ColumnMajor[15] = 1.0f;

	return mat;
}