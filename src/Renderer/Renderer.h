#ifndef CSR_RENDERER_H
#define CSR_RENDERER_H

#include "../Defines.h"
#include "../Texture/Texture.h"

#define Renderer struct sRenderer

Renderer
{
	unsigned char CurrentFrameBuffer;
	Texture* FrameBuffer[2];
	Texture* DepthBuffer;
};

Renderer* RendererCreate( const unsigned int width, const unsigned int height);
void RendererDestroy( Renderer* renderer);
void RendererFlipBuffer( Renderer* renderer);

#endif // RENDERER_H