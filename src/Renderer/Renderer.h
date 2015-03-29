#ifndef CSR_RENDERER_H
#define CSR_RENDERER_H

#include "../FrameBuffer/FrameBuffer.h"
#include "../Texture/Texture.h"
#include "../VertexData/Mesh.h"
#include "VertexShaders.h"
#include "PixelShaders.h"

#define CSR_MAX_NUM_SAMPLERS 8

typedef struct
{
	Texture* Texture;
	unsigned char MagFilterMode;
	unsigned char MinFilterMode;
	unsigned char WrapMode;
	unsigned char _padding;
} Sampler;

typedef struct
{
	FrameBuffer* FrameBuffer;
	Texture* DepthBuffer;
	VertexShaderFunction VertexShader;
	void* VertexShaderUniforms;
	PixelShaderFunction PixelShader;
	void* PixelShaderUniforms;
	unsigned int RenderState;
	Sampler Samplers[CSR_MAX_NUM_SAMPLERS]; // 8 - 12 bytes
	unsigned int _padding; // 4 bytes
} Renderer;


// TODO: write renderer states (DEPTH_TEST, DEPTH_READ, )

Renderer* Renderer_Create( const unsigned int width, const unsigned int height);
void Renderer_Destroy( Renderer* const renderer);


void Renderer_DrawMesh( Renderer* const renderer, const Mesh* const mesh);


// shader
void Renderer_SetVertexShader( Renderer* const renderer, VertexShaderFunction const vertexShaderFunc, void* const vertexShaderUniforms);
void Renderer_SetVertexShaderUniforms( Renderer* const renderer, void* const vertexShaderUniforms);


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
