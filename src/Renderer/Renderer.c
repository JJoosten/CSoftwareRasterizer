#include "Renderer.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Renderer* RendererCreate( const unsigned int width, const unsigned int height)
{
	Renderer* renderer = malloc( sizeof(Renderer));
	
	assert( renderer && "RendererDestroy renderer == NULL");

	memset( renderer, 0, sizeof(Renderer));

	renderer->FrameBuffer = FrameBufferCreate( width, height);
	renderer->DepthBuffer = TextureCreate( width, height);

	return renderer;
}

void RendererDestroy( Renderer* renderer)
{
	assert( renderer && "RendererDestroy renderer == NULL");
	assert( renderer->FrameBuffer && "RendererDestroy renderer->FrameBuffer == NULL");
	assert( renderer->DepthBuffer && "RendererDestroy renderer->DepthBuffer == NULL");

	FrameBufferDestroy(renderer->FrameBuffer);
	TextureDestroy(renderer->DepthBuffer);
	free(renderer);
}