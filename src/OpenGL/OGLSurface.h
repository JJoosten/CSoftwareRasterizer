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

bool OGLInit( const unsigned int screenWidth, const unsigned int screenHeight);

OGLSurface OGLSurfaceCreate( const FrameBuffer* const frameBuffer);
void OGLSurfaceDestroy( OGLSurface* surface);
void OGLSurfaceMapToFrameBuffer( OGLSurface* surface, FrameBuffer* frameBuffer);
void OGLSurfaceDraw( OGLSurface* surface);


#endif // CSR_OGLSURFACE_H