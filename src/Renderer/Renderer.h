#ifndef CSR_RENDERER_H
#define CSR_RENDERER_H

#include "../FrameBuffer/FrameBuffer.h"
#include "../Texture/Texture.h"


typedef struct sRenderer
{
	FrameBuffer* FrameBuffer;
	Texture* DepthBuffer;
} Renderer;

Renderer* Renderer_Create( const unsigned int width, const unsigned int height);
void Renderer_Destroy( Renderer* renderer);


// void Renderer_SetSampler( Renderer* renderer, const unsigned int samplerIndex, const Texture* const texture, );
// void Renderer_SetSamplerFilterMode( Renderer* renderer, const unsigned int samplerIndex, const unsigned int filterMode);
// void Renderer_SetSamplerWrapMode( Renderer* renderer, const unsigned int samplerIndex, const unsigned int wrapMode);

// void Renderer_EnableDepthBuffer( Renderer* renderer);
// void Renderer_DisableDepthBuffer( Renderer* renderer);

// void Renderer_EnableBackFaceCulling( Renderer* renderer);
// void Renderer_DisableBackFaceCulling( Renderer* renderer);


#endif // RENDERER_H