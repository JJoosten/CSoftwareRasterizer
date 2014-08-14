#include "VertexShaders.h"
#include <assert.h>
#include <stdio.h>

void DefaultVertexShader( RasterTriangle* const triangle_IN_OUT, const VertexShaderUniforms* const uniforms)
{
	assert( triangle_IN_OUT && "DefaultVertexShader triangle_IN_OUT is NULL");
	assert( uniforms && "DefaultVertexShader uniforms is NULL");

	// transform position
	Vec4_MulMat4( &triangle_IN_OUT->V1.Position, &triangle_IN_OUT->V1.Position, &uniforms->WorldToViewToProjectionMatrix);
	Vec4_MulMat4( &triangle_IN_OUT->V2.Position, &triangle_IN_OUT->V2.Position, &uniforms->WorldToViewToProjectionMatrix);
	Vec4_MulMat4( &triangle_IN_OUT->V3.Position, &triangle_IN_OUT->V3.Position, &uniforms->WorldToViewToProjectionMatrix);

	// transform position into clip space
	Vec3_DivByFloat( &triangle_IN_OUT->V1.Position.XYZ, &triangle_IN_OUT->V1.Position.XYZ, triangle_IN_OUT->V1.Position.W);
	Vec3_DivByFloat( &triangle_IN_OUT->V2.Position.XYZ, &triangle_IN_OUT->V2.Position.XYZ, triangle_IN_OUT->V2.Position.W);
	Vec3_DivByFloat( &triangle_IN_OUT->V3.Position.XYZ, &triangle_IN_OUT->V3.Position.XYZ, triangle_IN_OUT->V3.Position.W);

}