#ifndef CSR_RENDERER_H
#define CSR_RENDERER_H

#include "../Texture/Texture.h"

typedef struct sRenderer
{
	unsigned char CurrentFrameBuffer;
	Texture* FrameBuffer[2];
	Texture* DepthBuffer;
} Renderer;

Renderer* RendererCreate( const unsigned int width, const unsigned int height);
void RendererDestroy( Renderer* renderer);
void RendererFlipBuffer( Renderer* renderer);

#endif // RENDERER_H