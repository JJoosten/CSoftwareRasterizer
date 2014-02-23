#include "VertexShaders.h"


void DefaultVertexShader( RasterTriangle* const triangle_IN_OUT, const VertexShaderUniforms* const uniforms)
{
	// transform position
	Vec4_MulMat4( &triangle_IN_OUT->V1.Position, &triangle_IN_OUT->V1.Position, &uniforms->WorldToViewToProjectionMatrix);
	Vec4_MulMat4( &triangle_IN_OUT->V2.Position, &triangle_IN_OUT->V2.Position, &uniforms->WorldToViewToProjectionMatrix);
	Vec4_MulMat4( &triangle_IN_OUT->V3.Position, &triangle_IN_OUT->V3.Position, &uniforms->WorldToViewToProjectionMatrix);
}