#ifndef CSR_MAT4_H
#define CSR_MAT4_H

#include "Vec3.h"

typedef struct sMat4
{
	float ColumnMajor[16];
} Mat4;

Mat4 Mat4_LoadZero( void);
Mat4 Mat4_LoadIdentity( void);
Mat4 Mat4_LoadOrtho( const float left, const float right, const float top, const float bottom, const float near, const float far);
Mat4 Mat4_LoadPerspective( const float fovInDegrees, const float aspectRatio, const float near, const float far);
Mat4 Mat4_LoadLookAt( const Vec3* const target, const Vec3* const eye, const Vec3* const up);



#endif //CSR_MAT4_H
