#ifndef CSR_OGLSURFACE_H
#define CSR_OGLSURFACE_H

#include "../Typedefs.h"
#include "../FrameBuffer/FrameBuffer.h"
#include "GL/glew.h"

typedef struct sOGLSurface
{
	GLuint TextureID[2];
	GLuint PixelBufferID[2];
	GLuint Width;
	GLuint Height;
	GLbyte CurrentBuffer;
	unsigned int* PixelData;
} OGLSurface;

bool OGL_Init( const unsigned int screenWidth, const unsigned int screenHeight);

OGLSurface* OGLSurface_Create( const FrameBuffer* const frameBuffer);
void OGLSurface_Destroy( OGLSurface* surface);
void OGLSurface_MapToFrameBuffer( OGLSurface* surface, FrameBuffer* frameBuffer);
void OGLSurface_Draw( OGLSurface* surface);


#endif // CSR_OGLSURFACE_H