#ifndef CSR_FRAMEBUFFER_H
#define CSR_FRAMEBUFFER_H

#include "../Defines.h"

typedef struct sFrameBuffer
{
	unsigned int Width;
	unsigned int Height;
	unsigned int* Pixels;
} FrameBuffer;

FrameBuffer* FrameBufferCreate( const unsigned int width, const unsigned int height);
void FrameBufferDestroy( FrameBuffer* texture);
void FrameBufferClear( FrameBuffer* frameBuffer, const unsigned int clearColor);


#endif // TEXTURE_H