#ifndef CSR_RENDERER_H
#define CSR_RENDERER_H

#include "../FrameBuffer/FrameBuffer.h"
#include "../Texture/Texture.h"

typedef struct sRenderer
{
	FrameBuffer* FrameBuffer;
	Texture* DepthBuffer;
} Renderer;

Renderer* RendererCreate( const unsigned int width, const unsigned int height);
void RendererDestroy( Renderer* renderer);

#endif // RENDERER_H