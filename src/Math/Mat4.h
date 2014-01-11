#ifndef CSR_MAT4_H
#define CSR_MAT4_H

#include "Vec3.h"

typedef struct sMat4
{
	float ColumnMajor[16];
} Mat4;

Mat4 Mat4Zero( void);
Mat4 Mat4Identity( void);
Mat4 Mat4Ortho( const float left, const float right, const float top, const float bottom, const float near, const float far);
Mat4 Mat4Perspective( const float fovInDegrees, const float aspectRatio, const float near, const float far);
Mat4 Mat4LookAt( const Vec3* const target, const Vec3* const eye, const Vec3* const up);


#endif //CSR_MAT4_H
