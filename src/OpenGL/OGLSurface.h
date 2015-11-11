#ifndef CSR_OGLSURFACE_H
#define CSR_OGLSURFACE_H

#include "../Typedefs.h"
#include "../FrameBuffer/FrameBuffer.h"
#include "GL/glew.h"


#ifdef _DEBUG
#define CHECK_OGL_ERROR_IN_DEBUG IF_OGL_BREAK
#else
#define CHECK_OGL_ERROR_IN_DEBUG { int _tmp = 0; }
#endif

#define IF_OGL_BREAK if(OGL_HasError()) CODE_BREAKPOINT

#define NUM_BUFFERS 2

typedef struct
{
	GLuint TextureID[NUM_BUFFERS];
	GLuint PixelBufferID[NUM_BUFFERS];
	GLuint Width;
	GLuint Height;
	GLuint ShaderProgram;
	GLuint VaoDummy;
	GLbyte CurrentBuffer;
	unsigned int* PixelData[NUM_BUFFERS];
	unsigned int SizeInBytes;
} OGLSurface;

bool OGL_Init( const unsigned int screenWidth, const unsigned int screenHeight);
bool OGL_HasError();


OGLSurface* OGLSurface_Create( const FrameBuffer* const frameBuffer);
void OGLSurface_Destroy( OGLSurface* const surface);
void OGLSurface_MapToFrameBuffer( OGLSurface* const surface, FrameBuffer* const frameBuffer);
void OGLSurface_Draw( OGLSurface* const surface);

#endif // CSR_OGLSURFACE_H