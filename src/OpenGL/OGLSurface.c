#include "OGLSurface.h"
#include <string.h>
#include <stdlib.h>

static void transferSurfaceToTexture( OGLSurface* surface)
{
	glUnmapBuffer( GL_PIXEL_UNPACK_BUFFER_ARB );
	glBindTexture( GL_TEXTURE_2D, surface->TextureID[surface->CurrentBuffer] );
	glBindBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, surface->PixelBufferID[surface->CurrentBuffer] );
	glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, surface->Width, surface->Height, GL_RGBA, GL_UNSIGNED_BYTE, 0 ); 
	glBindBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, 0 );
}

bool OGL_Init( const unsigned int screenWidth, const unsigned int screenHeight)
{
	glViewport( 0, 0, screenWidth, screenHeight);
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0, 1, 0, 1, -1, 1 );
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
	glEnable( GL_TEXTURE_2D );
	glShadeModel( GL_SMOOTH );
	glClearColor( 0, 0, 0, 0);
	glClear( GL_COLOR_BUFFER_BIT);
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE);

	return true;
}

OGLSurface* OGLSurface_Create( const FrameBuffer* const framebuffer)
{
	const unsigned int sizeOfPixelBufferInBytes = framebuffer->Width * framebuffer->Height * 4;
	unsigned int numBuffer = 0;
	
	OGLSurface* surface = malloc( sizeof(OGLSurface));
	memset( surface, 0, sizeof(OGLSurface));
	
	// generate texture
	glGenTextures( 2, surface->TextureID);

	for(numBuffer; numBuffer < 2; ++numBuffer)
	{
		glBindTexture( GL_TEXTURE_2D, surface->TextureID[numBuffer]);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		surface->Width = framebuffer->Width;
		surface->Height = framebuffer->Height;

		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface->Width, surface->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glBindTexture( GL_TEXTURE_2D, 0);
	}

	// generate pixel buffer
	glGenBuffers( 2, surface->PixelBufferID);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, surface->PixelBufferID[0]);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeOfPixelBufferInBytes, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, surface->PixelBufferID[1]);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeOfPixelBufferInBytes, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	
	glBindTexture( GL_TEXTURE_2D, surface->TextureID[0]);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, surface->PixelBufferID[0]);
	surface->PixelData = (unsigned int*)glMapBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY_ARB );
	memset( surface->PixelData, 0, sizeOfPixelBufferInBytes);

	return surface;
}

void OGLSurface_Destroy( OGLSurface* surface)
{
	glDeleteTextures( 2, surface->TextureID);
	glDeleteBuffers( 2, surface->PixelBufferID); 
	free(surface);
}

void OGLSurface_MapToFrameBuffer( OGLSurface* surface, FrameBuffer* frameBuffer)
{
	frameBuffer->Pixels = surface->PixelData;
}

void OGLSurface_Draw( OGLSurface* surface)
{
	transferSurfaceToTexture( surface);

	++surface->CurrentBuffer;
	surface->CurrentBuffer &= 1;

	glBindBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, surface->PixelBufferID[surface->CurrentBuffer] );	
	surface->PixelData = (unsigned int*)glMapBuffer( GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY );

	glBegin( GL_QUADS);
	{
		glTexCoord2f( 0.0f, 0.0f );
		glVertex2f  ( 0.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f );
		glVertex2f  ( 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f );
		glVertex2f  ( 1.0f, 0.0f );
		glTexCoord2f( 0.0f, 1.0f );
		glVertex2f  ( 0.0f, 0.0f );
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glFinish();
}
