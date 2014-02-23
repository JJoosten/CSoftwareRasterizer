#ifndef CSR_VERTEX_SHADER_H
#define CSR_VERTEX_SHADER_H

#include "../VertexData/Triangle.h"
#include "../Math/Mat4.h"

typedef struct
{
	Mat4 WorldToViewToProjectionMatrix;
} VertexShaderUniforms;


// function description
typedef void (*VertexShaderFunction)( Triangle* const triangle_IN_OUT, const VertexShaderUniforms* const uniforms);


void DefaultVertexShader( Triangle* const triangle, const VertexShaderUniforms* const uniforms);

#endif // CSR_VERTEX_SHADER_H