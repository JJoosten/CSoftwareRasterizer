#ifndef CSR_RENDERER_H
#define CSR_RENDERER_H

#include "../FrameBuffer/FrameBuffer.h"
#include "../Texture/Texture.h"
#include "../VertexData/Mesh.h"
#include "VertexShaders.h"

typedef struct
{
	FrameBuffer* FrameBuffer;
	Texture* DepthBuffer;
	VertexShaderFunction VertexShader;
	VertexShaderUniforms* VertexShaderUniforms;
} Renderer;

Renderer* Renderer_Create( const unsigned int width, const unsigned int height);
void Renderer_Destroy( Renderer* const renderer);


void Renderer_DrawMesh( Renderer* const renderer, const Mesh* const mesh);


// shader 
void Renderer_SetVertexShader( Renderer* const renderer, VertexShaderFunction const vertexShaderFunc, VertexShaderUniforms* const vertexShaderUniforms);
void Renderer_SetVertexShaderUniforms( Renderer* const renderer, VertexShaderUniforms* const vertexShaderUniforms);


// sampler
// void Renderer_SetSampler( Renderer* renderer, const unsigned int samplerIndex, const Texture* const texture, );
// void Renderer_SetSamplerFilterMode( Renderer* renderer, const unsigned int samplerIndex, const unsigned int filterMode);
// void Renderer_SetSamplerWrapMode( Renderer* renderer, const unsigned int samplerIndex, const unsigned int wrapMode);


// depth buffer
// void Renderer_EnableDepthBuffer( Renderer* renderer);
// void Renderer_DisableDepthBuffer( Renderer* renderer);


// culling
// void Renderer_EnableBackFaceCulling( Renderer* renderer);
// void Renderer_DisableBackFaceCulling( Renderer* renderer);


#endif // RENDERER_H