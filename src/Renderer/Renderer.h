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


// void Renderer_SetSampler( const unsigned int samplerIndex, const Texture* const texture, );
// void Renderer_SetSamplerFilterMode( const unsigned int samplerIndex, const unsigned int filterMode);
// void Renderer_SetSamplerWrapMode( const unsigned int samplerIndex, const unsigned int wrapMode);

// void Renderer_EnableDepthBuffer( void);
// void Renderer_DisableDepthBuffer( void);

// void Renderer_EnableBackFaceCulling( void);
// void Renderer_DisableBackFaceCulling( void);


#endif // RENDERER_H