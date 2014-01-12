#ifndef CSR_MAT4_H
#define CSR_MAT4_H

#include "Vec3.h"
#include "../Typedefs.h"

typedef struct sMat4
{
	float ColumnMajor[16];
} Mat4;

Mat4 Mat4_CreateZero( void);
Mat4 Mat4_CreateIdentity( void);
Mat4 Mat4_CreateOrtho( const float left, const float right, const float top, const float bottom, const float near, const float far);
Mat4 Mat4_CreatePerspective( const float fovInDegrees, const float aspectRatio, const float near, const float far);
Mat4 Mat4_CreateLookAt( const Vec3* const target, const Vec3* const eye, const Vec3* const up);

Mat4* Mat4_LoadMat4( Mat4* out, const Mat4* a);
Mat4* Mat4_LoadIdentity( Mat4* out);
Mat4* Mat4_LoadOrtho( Mat4* out, const float left, const float right, const float top, const float bottom, const float near, const float far);
Mat4* Mat4_LoadPerspective( Mat4* out, const float fovInDegrees, const float aspectRatio, const float near, const float far);
Mat4* Mat4_LoadLookAt( Mat4* out, const Vec3* const target, const Vec3* const eye, const Vec3* const up);

Mat4* Mat4_Copy( Mat4* out, const Mat4* a);

Mat4* Mat4_Transpose( Mat4* out, const Mat4* const a);
Mat4* Mat4_Inverse( Mat4* out, const Mat4* const a);
Mat4* Mat4_Multiply( Mat4* out, const Mat4* const a, const Mat4* const b);

Mat4* Mat4_Translate( Mat4* inOut, const Vec3* const translation);
Mat4* Mat4_TranslateTo( Mat4* inOut, const Vec3* const translation);

Mat4* Mat4_RotateXTo( Mat4* inOut, const float rotationInDegrees);
Mat4* Mat4_RotateYTo( Mat4* inOut, const float rotationInDegrees);
Mat4* Mat4_RotateZTo( Mat4* inOut, const float rotationInDegrees);
Mat4* Mat4_RotateOverAxisTo( Mat4* inOut, const Vec3* const rotationAxisNormalized, const float rotationInDegrees);

Mat4* Mat4_ScaleUniform( Mat4* inOut, const float scale);
Mat4* Mat4_ScaleNonUniform( Mat4* inOut, const Vec3* const scale);

// vec3 extension
Vec3* Vec3_MulMat4( Vec3* out, float* outW, const Vec3* inVec, const Mat4* const a);


#endif //CSR_MAT4_H
