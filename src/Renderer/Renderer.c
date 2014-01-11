#include "Renderer.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Renderer* Renderer_Create( const unsigned int width, const unsigned int height)
{
	Renderer* renderer = malloc( sizeof(Renderer));
	
	assert( renderer && "Renderer_Create renderer == NULL");

	memset( renderer, 0, sizeof(Renderer));

	renderer->FrameBuffer = FrameBuffer_Create( width, height);
	renderer->DepthBuffer = Texture_Create( width, height);

	return renderer;
}

void Renderer_Destroy( Renderer* renderer)
{
	assert( renderer && "Renderer_Destroy renderer == NULL");
	assert( renderer->FrameBuffer && "Renderer_Destroy renderer->FrameBuffer == NULL");
	assert( renderer->DepthBuffer && "Renderer_Destroy renderer->DepthBuffer == NULL");

	FrameBuffer_Destroy(renderer->FrameBuffer);
	Texture_Destroy(renderer->DepthBuffer);
	free(renderer);
}