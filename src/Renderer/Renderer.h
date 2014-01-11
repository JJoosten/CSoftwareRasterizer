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

// void RendererSetSampler( const unsigned int samplerIndex, const Texture* const texture, );



#endif // RENDERER_H