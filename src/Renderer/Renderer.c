#include "Renderer.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Renderer* RendererCreate( const unsigned int width, const unsigned int height)
{
	Renderer* renderer = malloc( sizeof(Renderer));
	
	assert( renderer && "RendererDestroy renderer == NULL");

	memset( renderer, 0, sizeof(Renderer));

	renderer->FrameBuffer[0] = TextureCreate( width, height);
	renderer->FrameBuffer[1] = TextureCreate( width, height);
	renderer->DepthBuffer = TextureCreate( width, height);

	return renderer;
}

void RendererDestroy( Renderer* renderer)
{
	assert( renderer && "RendererDestroy renderer == NULL");
	assert( renderer->FrameBuffer[0] && "RendererDestroy renderer->FrameBuffer[0] == NULL");
	assert( renderer->FrameBuffer[1] && "RendererDestroy renderer->FrameBuffer[1] == NULL");
	assert( renderer->DepthBuffer && "RendererDestroy renderer->DepthBuffer == NULL");

	TextureDestroy(renderer->FrameBuffer[0]);
	TextureDestroy(renderer->FrameBuffer[1]);
	TextureDestroy(renderer->DepthBuffer);
	free(renderer);
}

void RendererFlipBuffer( Renderer* renderer)
{
	++renderer->CurrentFrameBuffer;
	renderer->CurrentFrameBuffer &= 1;
}