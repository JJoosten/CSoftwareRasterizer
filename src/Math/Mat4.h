#ifndef CSR_MAT4_H
#define CSR_MAT4_H

#include "Vec4.h" // includes vec3
#include "../Typedefs.h"

typedef struct
{
	float ColumnMajor[16];
} Mat4;


Mat4* Mat4_LoadMat4( Mat4* const out, const Mat4* const a);
Mat4* Mat4_LoadIdentity( Mat4* const out);
Mat4* Mat4_LoadOrtho( Mat4* const out, const float left, const float right, const float top, const float bottom, const float near, const float far);
Mat4* Mat4_LoadPerspective( Mat4* const out, const float fovInDegrees, const float aspectRatio, const float near, const float far);
Mat4* Mat4_LoadLookAt( Mat4* const out, const Vec3* const target, const Vec3* const eye, const Vec3* const up);

Mat4* Mat4_Copy( Mat4* const out, const Mat4* a);

Mat4* Mat4_Transpose( Mat4* const out, const Mat4* const a);
Mat4* Mat4_Inverse( Mat4* const out, const Mat4* const a);
Mat4* Mat4_Multiply( Mat4* const out, const Mat4* const a, const Mat4* const b);

Mat4* Mat4_Translate( Mat4* const inOut, const Vec3* const translation);
Mat4* Mat4_TranslateTo( Mat4* const inOut, const Vec3* const translation);

Mat4* Mat4_RotateXTo( Mat4* const inOut, const float rotationInDegrees);
Mat4* Mat4_RotateYTo( Mat4* const inOut, const float rotationInDegrees);
Mat4* Mat4_RotateZTo( Mat4* const inOut, const float rotationInDegrees);
Mat4* Mat4_RotateOverAxisTo( Mat4* const inOut, const Vec3* const rotationAxisNormalized, const float rotationInDegrees);

Mat4* Mat4_ScaleUniform( Mat4* const inOut, const float scale);
Mat4* Mat4_ScaleNonUniform( Mat4* const inOut, const Vec3* const scale);

// vec3 extension
Vec3* Vec3_MulMat4( Vec3* const out, float* outW, const Vec3* inVec, const Mat4* const a);

// vec4 extension
Vec4* Vec4_MulMat4( Vec4* const out, const Vec4* inVec, const Mat4* const a);

// printf extension
void Printf_Mat4( const Mat4* const a);

#endif //CSR_MAT4_H
