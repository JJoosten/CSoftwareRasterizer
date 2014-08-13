#include "VertexShaders.h"
#include <assert.h>

void DefaultVertexShader( RasterTriangle* const triangle_IN_OUT, const VertexShaderUniforms* const uniforms)
{
	assert( triangle_IN_OUT && "DefaultVertexShader triangle_IN_OUT is NULL");
	assert( uniforms && "DefaultVertexShader uniforms is NULL");

	// transform position
	Vec4_MulMat4( &triangle_IN_OUT->V1.Position, &triangle_IN_OUT->V1.Position, &uniforms->WorldToViewToProjectionMatrix);
	Vec4_MulMat4( &triangle_IN_OUT->V2.Position, &triangle_IN_OUT->V2.Position, &uniforms->WorldToViewToProjectionMatrix);
	Vec4_MulMat4( &triangle_IN_OUT->V3.Position, &triangle_IN_OUT->V3.Position, &uniforms->WorldToViewToProjectionMatrix);
}