#ifndef CSR_FRAMEBUFFER_H
#define CSR_FRAMEBUFFER_H

#include "../Defines.h"

typedef struct sFrameBuffer
{
	unsigned int Width;
	unsigned int Height;
	unsigned int* Pixels;
} FrameBuffer;

FrameBuffer* FrameBuffer_Create( const unsigned int width, const unsigned int height);
void FrameBuffer_Destroy( FrameBuffer* texture);
void FrameBuffer_Clear( FrameBuffer* frameBuffer, const unsigned int clearColor);
void FrameBuffer_ClearToBlack( FrameBuffer* frameBuffer);



#endif // TEXTURE_H