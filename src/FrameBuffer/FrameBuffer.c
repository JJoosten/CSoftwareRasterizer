#include "FrameBuffer.h"
#include "../Utility/Validate.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


FrameBuffer* FrameBuffer_Create( const unsigned int width, const unsigned int height)
{
	FrameBuffer* frameBuffer = malloc( sizeof(FrameBuffer));
	
	assert(frameBuffer && "FrameBuffer_Create texture is NULL");

	frameBuffer->Width = width;
	frameBuffer->Height = height;

	assert(frameBuffer->Pixels && "FrameBuffer_Create texture->Texels is NULL, probably not enough memory in RAM");

	return frameBuffer;
}

void FrameBuffer_Destroy( FrameBuffer* const frameBuffer)
{
	assert( frameBuffer && "FrameBuffer_Destroy texture is NULL");
	assert( frameBuffer->Pixels && "FrameBuffer_Destroy texture->Data is NULL");

	free(frameBuffer);
}

void FrameBuffer_Clear( FrameBuffer* const frameBuffer, const unsigned int clearColor)
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

void FrameBuffer_ClearToBlack( FrameBuffer* const frameBuffer)
{
	memset( frameBuffer->Pixels, 0, 4 * frameBuffer->Width * frameBuffer->Height);
}