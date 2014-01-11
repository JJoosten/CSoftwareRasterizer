#include "FrameBuffer.h"
#include "../Utility/Validate.h"
#include <stdlib.h>
#include <assert.h>


FrameBuffer* FrameBufferCreate( const unsigned int width, const unsigned int height)
{
	FrameBuffer* frameBuffer = malloc( sizeof(FrameBuffer));
	
	assert(frameBuffer && "TextureCreate texture is NULL");

	frameBuffer->Width = width;
	frameBuffer->Height = height;

	assert(frameBuffer->Pixels && "TextureCreate texture->Texels is NULL, probably not enough memory in RAM");

	return frameBuffer;
}

void FrameBufferDestroy( FrameBuffer* frameBuffer)
{
	assert( frameBuffer && "TextureDestroy texture is NULL");
	assert( frameBuffer->Pixels && "TextureDestroy texture->Data is NULL");

	free(frameBuffer);
}

void FrameBufferClear( FrameBuffer* frameBuffer, const unsigned int clearColor)
{
	unsigned int y = 0;
	for( y; y < frameBuffer->Height; ++y)
	{
		unsigned int x = 0;
		for( x; x < frameBuffer->Width; ++x)
		{
			frameBuffer->Pixels[y * frameBuffer->Width + x] = clearColor;
		}
	}
}