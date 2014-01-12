#include "Mat4.h"
#include <string.h>
#include <math.h>
#include <assert.h>


Mat4* Mat4_LoadMat4( Mat4* out, const Mat4* a)
{
	assert( out && "Mat4_LoadMat4 out == NULL");
	assert( a && "Mat4_LoadMat4 a == NULL");
	return Mat4_Copy(out, a);
}

Mat4* Mat4_LoadIdentity( Mat4* out)
{
	assert( out && "Mat4_LoadPerspective out == NULL");
	memset( out, 0, sizeof(float) * 16);
	out->ColumnMajor[0] = 1.0f;
	out->ColumnMajor[5] = 1.0f;
	out->ColumnMajor[10] = 1.0f;
	out->ColumnMajor[15] = 1.0f;

	return out;
}

Mat4* Mat4_LoadOrtho( Mat4* out, const float left, const float right, const float top, const float bottom, const float near, const float far)
{
	assert( out && "Mat4_LoadPerspective out == NULL");

	out->ColumnMajor[0] = 2.0f / (right - left);	out->ColumnMajor[4] = 0.0f;						out->ColumnMajor[ 8] = 0.0f;					out->ColumnMajor[12] = -((right + left) / (right - left));
	out->ColumnMajor[1] = 0.0f;						out->ColumnMajor[5] = 2.0f / (top - bottom);	out->ColumnMajor[ 9] = 0.0f;					out->ColumnMajor[13] = -((top + bottom) / (top - bottom));
	out->ColumnMajor[2] = 0.0f;						out->ColumnMajor[6] = 0.0f;						out->ColumnMajor[10] = 1.0f / (far - near);		out->ColumnMajor[14] = -(near / (far - near));
	out->ColumnMajor[3] = 0.0f;						out->ColumnMajor[7] = 0.0f;						out->ColumnMajor[11] = 0.0f;					out->ColumnMajor[15] = 1.0f;

	return out;
}

Mat4* Mat4_LoadPerspective( Mat4* out, const float fovInDegrees, const float aspectRatio, const float near, const float far)
{
	const float f = 1.0f / tanf( 0.0174532925 * fovInDegrees / 2.0f);
	
	assert( out && "Mat4_LoadPerspective out == NULL");

	out->ColumnMajor[0] = f / aspectRatio;	out->ColumnMajor[4] = 0.0f;	out->ColumnMajor[ 8] = 0.0f;						out->ColumnMajor[12] = 0.0f;
	out->ColumnMajor[1] = 0.0f;				out->ColumnMajor[5] = f;	out->ColumnMajor[ 9] = 0.0f;						out->ColumnMajor[13] = 0.0f;
	out->ColumnMajor[2] = 0.0f;				out->ColumnMajor[6] = 0.0f;	out->ColumnMajor[10] = (far + near) / (near - far);	out->ColumnMajor[14] = 2 * far * near / (near - far);
	out->ColumnMajor[3] = 0.0f;				out->ColumnMajor[7] = 0.0f;	out->ColumnMajor[11] = -1.0f;						out->ColumnMajor[15] = 0.0f;
	return out;
}

Mat4* Mat4_LoadLookAt( Mat4* out, const Vec3* const target, const Vec3* const eye, const Vec3* const up)
{
	Vec3 direction, localLeft, localUp;

	assert( out && "Mat4_LoadLookAt out == NULL");
	assert( target && "Mat4_LoadLookAt target == NULL");
	assert( eye && "Mat4_LoadLookAt eye == NULL");
	assert( up && "Mat4_LoadLookAt up == NULL");

	Vec3_Cross( &direction, target, eye);
	Vec3_Normalize( &direction, &direction);
	
	Vec3_Cross( &localLeft, &direction, up);
	Vec3_Normalize( &localLeft, &localLeft);
	
	Vec3_Cross( &localUp, &localLeft, &direction);

	out->ColumnMajor[0] = localLeft.X;	out->ColumnMajor[4] = localLeft.Y;	out->ColumnMajor[ 8] = localLeft.Z;		out->ColumnMajor[12] = -eye->X;
	out->ColumnMajor[1] = localUp.X;	out->ColumnMajor[5] = localUp.Y;	out->ColumnMajor[ 9] = localUp.Z;		out->ColumnMajor[13] = -eye->Y;
	out->ColumnMajor[2] = -direction.X;	out->ColumnMajor[6] = -direction.Y;	out->ColumnMajor[10] = -direction.Z;	out->ColumnMajor[14] = -eye->Z;
	out->ColumnMajor[3] = 0.0f;			out->ColumnMajor[7] = 0.0f;			out->ColumnMajor[11] = 0.0f;			out->ColumnMajor[15] = 1.0f;

	return out;
}


Mat4* Mat4_Copy( Mat4* out, const Mat4* a)
{
	assert( out && "Mat4_Copy out == NULL");
	assert( a && "Mat4_Copy a == NULL");
	memcpy( out, a, sizeof(float) * 16);
	return out;
}


Mat4* Mat4_Transpose( Mat4* out, const Mat4* const a)
{
	float tempVal;
	
	assert( out && "Mat4_Transpose out == NULL");
	assert( a && "Mat4_Transpose a == NULL");

	// C1R1
	out->ColumnMajor[0] = a->ColumnMajor[0];

	// swap C1R2 with C2R1
	tempVal = a->ColumnMajor[1];
	out->ColumnMajor[1] = a->ColumnMajor[4];
	out->ColumnMajor[4] = tempVal;
	
	// C2R2
	out->ColumnMajor[5] = a->ColumnMajor[5];
	
	// swap C1R3 with C3R1
	tempVal = a->ColumnMajor[2];
	out->ColumnMajor[2] = a->ColumnMajor[8];
	out->ColumnMajor[8] = tempVal;
	
	// swap C1R4 with C4R1
	tempVal = a->ColumnMajor[3];
	out->ColumnMajor[3] = a->ColumnMajor[12];
	out->ColumnMajor[12] = tempVal;
	
	// swap C2R3 with C3R2
	tempVal = a->ColumnMajor[6];
	out->ColumnMajor[6] = a->ColumnMajor[9];
	out->ColumnMajor[9] = tempVal;
	
	// swap C2R4 with C4R2
	tempVal = a->ColumnMajor[7];
	out->ColumnMajor[7] = a->ColumnMajor[13];
	out->ColumnMajor[13] = tempVal;
	
	// C3R3
	out->ColumnMajor[10] = a->ColumnMajor[10];
	
	// swap C3R4 with C4R3
	tempVal = a->ColumnMajor[11];
	out->ColumnMajor[11] = a->ColumnMajor[14];
	out->ColumnMajor[14] = tempVal;
	
	// C4R4
	out->ColumnMajor[15] = a->ColumnMajor[15];
	
	return out;
}

Mat4* Mat4_Inverse( Mat4* out, const Mat4* const a)
{
	// calculate adjucate matrix
	float determinant3x3[16];
	float determinant;
	unsigned int i = 0;

	assert( out && "Mat4_Inverse out == NULL");
	assert( a && "Mat4_Inverse a == NULL");

	determinant3x3[0] = a->ColumnMajor[5]  * a->ColumnMajor[10] * a->ColumnMajor[15] - 
						a->ColumnMajor[5]  * a->ColumnMajor[11] * a->ColumnMajor[14] - 
						a->ColumnMajor[9]  * a->ColumnMajor[6]  * a->ColumnMajor[15] + 
						a->ColumnMajor[9]  * a->ColumnMajor[7]  * a->ColumnMajor[14] +
						a->ColumnMajor[13] * a->ColumnMajor[6]  * a->ColumnMajor[11] - 
						a->ColumnMajor[13] * a->ColumnMajor[7]  * a->ColumnMajor[10];

	determinant3x3[4] = -a->ColumnMajor[4]  * a->ColumnMajor[10] * a->ColumnMajor[15] + 
						a->ColumnMajor[4]  * a->ColumnMajor[11] * a->ColumnMajor[14] + 
						a->ColumnMajor[8]  * a->ColumnMajor[6]  * a->ColumnMajor[15] - 
						a->ColumnMajor[8]  * a->ColumnMajor[7]  * a->ColumnMajor[14] - 
						a->ColumnMajor[12] * a->ColumnMajor[6]  * a->ColumnMajor[11] + 
						a->ColumnMajor[12] * a->ColumnMajor[7]  * a->ColumnMajor[10];

	determinant3x3[8] = a->ColumnMajor[4]  * a->ColumnMajor[9] * a->ColumnMajor[15] - 
						a->ColumnMajor[4]  * a->ColumnMajor[11] * a->ColumnMajor[13] - 
						a->ColumnMajor[8]  * a->ColumnMajor[5] * a->ColumnMajor[15] + 
						a->ColumnMajor[8]  * a->ColumnMajor[7] * a->ColumnMajor[13] + 
						a->ColumnMajor[12] * a->ColumnMajor[5] * a->ColumnMajor[11] - 
						a->ColumnMajor[12] * a->ColumnMajor[7] * a->ColumnMajor[9];

	determinant3x3[12] = -a->ColumnMajor[4]  * a->ColumnMajor[9] * a->ColumnMajor[14] + 
						a->ColumnMajor[4]  * a->ColumnMajor[10] * a->ColumnMajor[13] +
						a->ColumnMajor[8]  * a->ColumnMajor[5] * a->ColumnMajor[14] - 
						a->ColumnMajor[8]  * a->ColumnMajor[6] * a->ColumnMajor[13] - 
						a->ColumnMajor[12] * a->ColumnMajor[5] * a->ColumnMajor[10] + 
						a->ColumnMajor[12] * a->ColumnMajor[6] * a->ColumnMajor[9];

	determinant3x3[1] = -a->ColumnMajor[1]  * a->ColumnMajor[10] * a->ColumnMajor[15] + 
						a->ColumnMajor[1]  * a->ColumnMajor[11] * a->ColumnMajor[14] + 
						a->ColumnMajor[9]  * a->ColumnMajor[2] * a->ColumnMajor[15] - 
						a->ColumnMajor[9]  * a->ColumnMajor[3] * a->ColumnMajor[14] - 
						a->ColumnMajor[13] * a->ColumnMajor[2] * a->ColumnMajor[11] + 
						a->ColumnMajor[13] * a->ColumnMajor[3] * a->ColumnMajor[10];

	determinant3x3[5] = a->ColumnMajor[0]  * a->ColumnMajor[10] * a->ColumnMajor[15] - 
						a->ColumnMajor[0]  * a->ColumnMajor[11] * a->ColumnMajor[14] - 
						a->ColumnMajor[8]  * a->ColumnMajor[2] * a->ColumnMajor[15] + 
						a->ColumnMajor[8]  * a->ColumnMajor[3] * a->ColumnMajor[14] + 
						a->ColumnMajor[12] * a->ColumnMajor[2] * a->ColumnMajor[11] - 
						a->ColumnMajor[12] * a->ColumnMajor[3] * a->ColumnMajor[10];

	determinant3x3[9] = -a->ColumnMajor[0]  * a->ColumnMajor[9] * a->ColumnMajor[15] + 
						a->ColumnMajor[0]  * a->ColumnMajor[11] * a->ColumnMajor[13] + 
						a->ColumnMajor[8]  * a->ColumnMajor[1] * a->ColumnMajor[15] - 
						a->ColumnMajor[8]  * a->ColumnMajor[3] * a->ColumnMajor[13] - 
						a->ColumnMajor[12] * a->ColumnMajor[1] * a->ColumnMajor[11] + 
						a->ColumnMajor[12] * a->ColumnMajor[3] * a->ColumnMajor[9];

	determinant3x3[13] = a->ColumnMajor[0]  * a->ColumnMajor[9] * a->ColumnMajor[14] - 
						a->ColumnMajor[0]  * a->ColumnMajor[10] * a->ColumnMajor[13] - 
						a->ColumnMajor[8]  * a->ColumnMajor[1] * a->ColumnMajor[14] + 
						a->ColumnMajor[8]  * a->ColumnMajor[2] * a->ColumnMajor[13] + 
						a->ColumnMajor[12] * a->ColumnMajor[1] * a->ColumnMajor[10] - 
						a->ColumnMajor[12] * a->ColumnMajor[2] * a->ColumnMajor[9];

	determinant3x3[2] = a->ColumnMajor[1]  * a->ColumnMajor[6] * a->ColumnMajor[15] - 
						a->ColumnMajor[1]  * a->ColumnMajor[7] * a->ColumnMajor[14] - 
						a->ColumnMajor[5]  * a->ColumnMajor[2] * a->ColumnMajor[15] + 
						a->ColumnMajor[5]  * a->ColumnMajor[3] * a->ColumnMajor[14] + 
						a->ColumnMajor[13] * a->ColumnMajor[2] * a->ColumnMajor[7] - 
						a->ColumnMajor[13] * a->ColumnMajor[3] * a->ColumnMajor[6];

	determinant3x3[6] = -a->ColumnMajor[0]  * a->ColumnMajor[6] * a->ColumnMajor[15] + 
						a->ColumnMajor[0]  * a->ColumnMajor[7] * a->ColumnMajor[14] + 
						a->ColumnMajor[4]  * a->ColumnMajor[2] * a->ColumnMajor[15] - 
						a->ColumnMajor[4]  * a->ColumnMajor[3] * a->ColumnMajor[14] - 
						a->ColumnMajor[12] * a->ColumnMajor[2] * a->ColumnMajor[7] + 
						a->ColumnMajor[12] * a->ColumnMajor[3] * a->ColumnMajor[6];

	determinant3x3[10] = a->ColumnMajor[0]  * a->ColumnMajor[5] * a->ColumnMajor[15] - 
						a->ColumnMajor[0]  * a->ColumnMajor[7] * a->ColumnMajor[13] - 
						a->ColumnMajor[4]  * a->ColumnMajor[1] * a->ColumnMajor[15] + 
						a->ColumnMajor[4]  * a->ColumnMajor[3] * a->ColumnMajor[13] + 
						a->ColumnMajor[12] * a->ColumnMajor[1] * a->ColumnMajor[7] - 
						a->ColumnMajor[12] * a->ColumnMajor[3] * a->ColumnMajor[5];

	determinant3x3[14] = -a->ColumnMajor[0]  * a->ColumnMajor[5] * a->ColumnMajor[14] + 
						a->ColumnMajor[0]  * a->ColumnMajor[6] * a->ColumnMajor[13] + 
						a->ColumnMajor[4]  * a->ColumnMajor[1] * a->ColumnMajor[14] - 
						a->ColumnMajor[4]  * a->ColumnMajor[2] * a->ColumnMajor[13] - 
						a->ColumnMajor[12] * a->ColumnMajor[1] * a->ColumnMajor[6] + 
						a->ColumnMajor[12] * a->ColumnMajor[2] * a->ColumnMajor[5];

	determinant3x3[3] = -a->ColumnMajor[1] * a->ColumnMajor[6] * a->ColumnMajor[11] + 
						a->ColumnMajor[1] * a->ColumnMajor[7] * a->ColumnMajor[10] + 
						a->ColumnMajor[5] * a->ColumnMajor[2] * a->ColumnMajor[11] - 
						a->ColumnMajor[5] * a->ColumnMajor[3] * a->ColumnMajor[10] - 
						a->ColumnMajor[9] * a->ColumnMajor[2] * a->ColumnMajor[7] + 
						a->ColumnMajor[9] * a->ColumnMajor[3] * a->ColumnMajor[6];

	determinant3x3[7] = a->ColumnMajor[0] * a->ColumnMajor[6] * a->ColumnMajor[11] - 
						a->ColumnMajor[0] * a->ColumnMajor[7] * a->ColumnMajor[10] - 
						a->ColumnMajor[4] * a->ColumnMajor[2] * a->ColumnMajor[11] + 
						a->ColumnMajor[4] * a->ColumnMajor[3] * a->ColumnMajor[10] + 
						a->ColumnMajor[8] * a->ColumnMajor[2] * a->ColumnMajor[7] - 
						a->ColumnMajor[8] * a->ColumnMajor[3] * a->ColumnMajor[6];

	determinant3x3[11] = -a->ColumnMajor[0] * a->ColumnMajor[5] * a->ColumnMajor[11] + 
						a->ColumnMajor[0] * a->ColumnMajor[7] * a->ColumnMajor[9] + 
						a->ColumnMajor[4] * a->ColumnMajor[1] * a->ColumnMajor[11] - 
						a->ColumnMajor[4] * a->ColumnMajor[3] * a->ColumnMajor[9] - 
						a->ColumnMajor[8] * a->ColumnMajor[1] * a->ColumnMajor[7] + 
						a->ColumnMajor[8] * a->ColumnMajor[3] * a->ColumnMajor[5];

	determinant3x3[15] = a->ColumnMajor[0] * a->ColumnMajor[5] * a->ColumnMajor[10] - 
						a->ColumnMajor[0] * a->ColumnMajor[6] * a->ColumnMajor[9] - 
						a->ColumnMajor[4] * a->ColumnMajor[1] * a->ColumnMajor[10] + 
						a->ColumnMajor[4] * a->ColumnMajor[2] * a->ColumnMajor[9] + 
						a->ColumnMajor[8] * a->ColumnMajor[1] * a->ColumnMajor[6] - 
						a->ColumnMajor[8] * a->ColumnMajor[2] * a->ColumnMajor[5];

	determinant = a->ColumnMajor[0] * determinant3x3[0] + a->ColumnMajor[1] * determinant3x3[4] + a->ColumnMajor[2] * determinant3x3[8] + a->ColumnMajor[3] * determinant3x3[12];

	if (determinant == 0)
	{
		return out;
	}

	determinant = 1.0f / determinant;

	// inverse = 1 / determinant * (adjugateMatrix)

	for ( i; i < 16; ++i)
	{
		out->ColumnMajor[i] = determinant3x3[i] * determinant;
	}

	return out;
}

Mat4* Mat4_Multiply( Mat4* out, const Mat4* const a, const Mat4* const b)
{
	// column major		convinience view on storage in mem
	// 00 04 08 12		00 01 02 03
	// 01 05 09 13		04 05 06 07
	// 02 06 10 14		08 09 10 11
	// 03 07 11 15		12 13 14 15
	
	assert( out && "Mat4_Mul out == NULL");
	assert( a && "Mat4_Mul a == NULL");
	assert( b && "Mat4_Mul b == NULL");

	out->ColumnMajor[ 0] = a->ColumnMajor[ 0] * b->ColumnMajor[ 0] +
						   a->ColumnMajor[ 1] * b->ColumnMajor[ 4] +
						   a->ColumnMajor[ 2] * b->ColumnMajor[ 8] +
						   a->ColumnMajor[ 3] * b->ColumnMajor[12];
										  
	out->ColumnMajor[ 1] = a->ColumnMajor[ 0] * b->ColumnMajor[ 1] +
						   a->ColumnMajor[ 1] * b->ColumnMajor[ 5] +
						   a->ColumnMajor[ 2] * b->ColumnMajor[ 9] +
						   a->ColumnMajor[ 3] * b->ColumnMajor[13];
										  
	out->ColumnMajor[ 2] = a->ColumnMajor[ 0] * b->ColumnMajor[ 2] +
						   a->ColumnMajor[ 1] * b->ColumnMajor[ 6] +
						   a->ColumnMajor[ 2] * b->ColumnMajor[10] +
						   a->ColumnMajor[ 3] * b->ColumnMajor[14];
										  
	out->ColumnMajor[ 3] = a->ColumnMajor[ 0] * b->ColumnMajor[ 3] +
						   a->ColumnMajor[ 1] * b->ColumnMajor[ 7] +
						   a->ColumnMajor[ 2] * b->ColumnMajor[11] +
						   a->ColumnMajor[ 3] * b->ColumnMajor[15];
										  
	out->ColumnMajor[ 4] = a->ColumnMajor[ 4] * b->ColumnMajor[ 0] +
						   a->ColumnMajor[ 5] * b->ColumnMajor[ 4] +
						   a->ColumnMajor[ 6] * b->ColumnMajor[ 8] +
						   a->ColumnMajor[ 7] * b->ColumnMajor[12];
										  
	out->ColumnMajor[ 5] = a->ColumnMajor[ 4] * b->ColumnMajor[ 1] +
						   a->ColumnMajor[ 5] * b->ColumnMajor[ 5] +
						   a->ColumnMajor[ 6] * b->ColumnMajor[ 9] +
						   a->ColumnMajor[ 7] * b->ColumnMajor[13];
	
	out->ColumnMajor[ 6] = a->ColumnMajor[ 4] * b->ColumnMajor[ 2] +
						   a->ColumnMajor[ 5] * b->ColumnMajor[ 6] +
						   a->ColumnMajor[ 6] * b->ColumnMajor[10] +
						   a->ColumnMajor[ 7] * b->ColumnMajor[14];

	out->ColumnMajor[ 7] = a->ColumnMajor[ 4] * b->ColumnMajor[ 3] +
						   a->ColumnMajor[ 5] * b->ColumnMajor[ 7] +
						   a->ColumnMajor[ 6] * b->ColumnMajor[11] +
						   a->ColumnMajor[ 7] * b->ColumnMajor[15];
										   
	out->ColumnMajor[ 8] = a->ColumnMajor[ 8] * b->ColumnMajor[ 0] +
						   a->ColumnMajor[ 9] * b->ColumnMajor[ 4] +
						   a->ColumnMajor[10] * b->ColumnMajor[ 8] +
						   a->ColumnMajor[11] * b->ColumnMajor[12];
										   
	out->ColumnMajor[ 9] = a->ColumnMajor[ 8] * b->ColumnMajor[ 1] +
						   a->ColumnMajor[ 9] * b->ColumnMajor[ 5] +
						   a->ColumnMajor[10] * b->ColumnMajor[ 9] +
						   a->ColumnMajor[11] * b->ColumnMajor[13];
										   
	out->ColumnMajor[10] = a->ColumnMajor[ 8] * b->ColumnMajor[ 2] +
						   a->ColumnMajor[ 9] * b->ColumnMajor[ 6] +
						   a->ColumnMajor[10] * b->ColumnMajor[10] +
						   a->ColumnMajor[11] * b->ColumnMajor[14];
										   
	out->ColumnMajor[11] = a->ColumnMajor[ 8] * b->ColumnMajor[ 3] +
						   a->ColumnMajor[ 9] * b->ColumnMajor[ 7] +
						   a->ColumnMajor[10] * b->ColumnMajor[11] +
						   a->ColumnMajor[11] * b->ColumnMajor[15];

	out->ColumnMajor[12] = a->ColumnMajor[12] * b->ColumnMajor[ 0] +
						   a->ColumnMajor[13] * b->ColumnMajor[ 4] +
						   a->ColumnMajor[14] * b->ColumnMajor[ 8] +
						   a->ColumnMajor[15] * b->ColumnMajor[12];
										   
	out->ColumnMajor[13] = a->ColumnMajor[12] * b->ColumnMajor[ 1] +
						   a->ColumnMajor[13] * b->ColumnMajor[ 5] +
						   a->ColumnMajor[14] * b->ColumnMajor[ 9] +
						   a->ColumnMajor[15] * b->ColumnMajor[13];
										   
	out->ColumnMajor[14] = a->ColumnMajor[12] * b->ColumnMajor[ 2] +
						   a->ColumnMajor[13] * b->ColumnMajor[ 6] +
						   a->ColumnMajor[14] * b->ColumnMajor[10] +
						   a->ColumnMajor[15] * b->ColumnMajor[14];
										   
	out->ColumnMajor[15] = a->ColumnMajor[12] * b->ColumnMajor[ 3] +
						   a->ColumnMajor[13] * b->ColumnMajor[ 7] +
						   a->ColumnMajor[14] * b->ColumnMajor[11] +
						   a->ColumnMajor[15] * b->ColumnMajor[15];
	return out;
}


Mat4* Mat4_Translate( Mat4* inOut, const Vec3* const translation)
{
	assert( inOut && "Mat4_Translate out == NULL");
	assert( translation && "Mat4_Translate translation == NULL");

	inOut->ColumnMajor[12] = inOut->ColumnMajor[12] + translation->X;
	inOut->ColumnMajor[13] = inOut->ColumnMajor[13] + translation->Y;
	inOut->ColumnMajor[14] = inOut->ColumnMajor[14] + translation->Z;
	
	return inOut;
}

Mat4* Mat4_TranslateTo( Mat4* inOut, const Vec3* const translation)
{
	assert( inOut && "Mat4_TranslateTo out == NULL");
	assert( translation && "Mat4_TranslateTo translation == NULL");

	inOut->ColumnMajor[12] = translation->X;
	inOut->ColumnMajor[13] = translation->Y;
	inOut->ColumnMajor[14] = translation->Z;

	return inOut;
}


Mat4* Mat4_RotateXTo( Mat4* inOut, const float rotationInDegrees)
{
	const float radians = rotationInDegrees * 0.0174532925f;
	
	assert( inOut && "Mat4_RotateXTo out == NULL");
	
	inOut->ColumnMajor[ 5] =  cosf(radians);
	inOut->ColumnMajor[ 6] = -sinf(radians);
	inOut->ColumnMajor[ 9] =  sinf(radians);
	inOut->ColumnMajor[10] =  cosf(radians);

	return inOut;
}

Mat4* Mat4_RotateYTo( Mat4* inOut, const float rotationInDegrees)
{
	const float radians = rotationInDegrees * 0.0174532925f;
	
	assert( inOut && "Mat4_RotateYTo out == NULL");
	
	inOut->ColumnMajor[ 0] =  cosf(radians);
	inOut->ColumnMajor[ 2] =  sinf(radians);
	inOut->ColumnMajor[ 8] = -sinf(radians);
	inOut->ColumnMajor[10] =  cosf(radians);

	return inOut;
}

Mat4* Mat4_RotateZTo( Mat4* inOut, const float rotationInDegrees)
{
	const float radians = rotationInDegrees * 0.0174532925f;
	
	assert( inOut && "Mat4_RotateZTo out == NULL");
	
	inOut->ColumnMajor[0] =  cosf(radians);
	inOut->ColumnMajor[1] = -sinf(radians);
	inOut->ColumnMajor[4] =  sinf(radians);
	inOut->ColumnMajor[5] =  cosf(radians);

	return inOut;
}

Mat4* Mat4_RotateOverAxisTo( Mat4* inOut, const Vec3* const rotationAxisNormalized, const float rotationInDegrees)
{
	const float radians = rotationInDegrees * 0.0174532925f;
	
	const float cosine = cosf( radians);
	const float oneMinCos = 1.0f - cosine;
	const float sine = sinf( radians);

	const float xz = rotationAxisNormalized->X * rotationAxisNormalized->Z * oneMinCos;
	const float xy = rotationAxisNormalized->X * rotationAxisNormalized->Y * oneMinCos;
	const float yz = rotationAxisNormalized->Y * rotationAxisNormalized->Z * oneMinCos;

	const float normalXSine = rotationAxisNormalized->X * sine;
	const float normalYSine = rotationAxisNormalized->X * sine;
	const float normalZSine = rotationAxisNormalized->Y * sine;
	
	assert( inOut && "Mat4_RotateOverAxisTo out == NULL");
	assert( rotationAxisNormalized && "Mat4_RotateOverAxisTo rotationAxis == NULL");
	
	inOut->ColumnMajor[ 0] = (rotationAxisNormalized->X * rotationAxisNormalized->X) * oneMinCos + cosine;
	inOut->ColumnMajor[ 1] = xy + normalZSine;
	inOut->ColumnMajor[ 2] = xz - normalYSine;

	inOut->ColumnMajor[ 4] = xy - normalZSine;
	inOut->ColumnMajor[ 5] = (rotationAxisNormalized->Y * rotationAxisNormalized->Y) * oneMinCos + cosine;
	inOut->ColumnMajor[ 6] = yz + normalXSine;

	inOut->ColumnMajor[ 0] = xz + normalYSine;
	inOut->ColumnMajor[ 1] = yz - normalXSine;
	inOut->ColumnMajor[ 2] = (rotationAxisNormalized->Z * rotationAxisNormalized->Z) * oneMinCos + cosine;

	return inOut;
}


Mat4* Mat4_ScaleUniform( Mat4* inOut, const float scale)
{
	assert( inOut && "Mat4_ScaleUniform out == NULL");
	
	inOut->ColumnMajor[ 0] = inOut->ColumnMajor[ 0] * scale;
	inOut->ColumnMajor[ 5] = inOut->ColumnMajor[ 5] * scale;
	inOut->ColumnMajor[10] = inOut->ColumnMajor[10] * scale;
	
	return inOut;
}

Mat4* Mat4_ScaleNonUniform( Mat4* inOut, const Vec3* const scale)
{
	assert( inOut && "Mat4_ScaleNonUniform out == NULL");
	assert( scale && "Mat4_ScaleNonUniform scale == NULL");
	
	inOut->ColumnMajor[ 0] = inOut->ColumnMajor[ 0] * scale->X;
	inOut->ColumnMajor[ 5] = inOut->ColumnMajor[ 5] * scale->Y;
	inOut->ColumnMajor[10] = inOut->ColumnMajor[10] * scale->Z;
	
	return inOut;
}


// vec3 extension
Vec3* Vec3_MulMat4( Vec3* out, float* inOutW, const Vec3* inVec, const Mat4* const a)
{
	float x; 
	float y; 
	float z; 
	float w; 

	assert( out && "Vec3_MulMat4 outVec == NULL");
	assert( inOutW && "Vec3_MulMat4 outW == NULL");
	assert( inVec && "Vec3_MulMat4 inVec == NULL");
	assert( a && "Vec3_MulMat4 a == NULL");
	
	x = inVec->X;
	y = inVec->Y;
	z = inVec->Z;
	w = *inOutW;
	
	out->X = a->ColumnMajor[0] * x + a->ColumnMajor[4] * y + a->ColumnMajor[ 8] * z + a->ColumnMajor[12] * w;
	out->Y = a->ColumnMajor[1] * x + a->ColumnMajor[5] * y + a->ColumnMajor[ 9] * z + a->ColumnMajor[13] * w;
	out->Z = a->ColumnMajor[2] * x + a->ColumnMajor[6] * y + a->ColumnMajor[10] * z + a->ColumnMajor[14] * w;
	
	// note that this is not totally mathematically correct, but because we know that we dont store data in 3, 7 and 11 we can ignore those (they would add up to 0)
	*inOutW = a->ColumnMajor[15] * w;
	
	return out;
}