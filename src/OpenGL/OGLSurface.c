#include "OGLSurface.h"
#include "../PlatformDefines.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const GLchar vertexShaderSource[] =
{
	"#version 330 core\n"
	"const vec2 quadVertices[4] = vec2[4]( vec2( -1.0), vec2( 1.0, -1.0), vec2( -1.0, 1.0), vec2(1.0));\n"
	"out vec2 fragInUV;"
	"void main()\n"
	"{\n"
		"fragInUV = ((quadVertices[gl_VertexID] * vec2(1.0,-1.0)) + vec2(1)) * vec2(0.5);"
		"gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);\n"
	"}\n"
};

const GLchar fragmentShaderSource[] = {
	"#version 330 core\n"
	"uniform sampler2D texture;"
	"in vec2 fragInUV;"
	"out vec4 outColor;"
	"void main()\n"
	"{\n"
	"outColor = texture2D(texture,fragInUV); \n"
	"}\n"
};

bool OGL_Init( const unsigned int screenWidth, const unsigned int screenHeight)
{
	glViewport(0, 0, screenWidth, screenHeight);
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 0); 
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return OGL_HasError();
}

bool OGL_HasError()
{
	GLenum glError = glGetError();
	if (glError == GL_NO_ERROR)
		return false;

	switch (glError)
	{
	case GL_INVALID_ENUM:
		printf( "GLError: GL_INVALID_ENUM");
		break;
	case GL_INVALID_VALUE:
		printf("GLError: GL_INVALID_VALUE");
		break;
	case GL_INVALID_OPERATION:
		printf("GLError: GL_INVALID_OPERATION");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		printf("GLError: GL_INVALID_FRAMEBUFFER_OPERATION");
		break;
	case GL_OUT_OF_MEMORY:
		printf("GLError: GL_OUT_OF_MEMORY");
		break;
	case GL_STACK_UNDERFLOW:
		printf("GLError: GL_STACK_UNDERFLOW");
		break;
	case GL_STACK_OVERFLOW:
		printf("GLError: GL_STACK_OVERFLOW");
		break;
	}

	return true;
}

bool OGL_HasShaderCompilationError(GLuint shader)
{
	char infoLog[1024];
	GLint success = 0;
	GLint logSize = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (success == GL_TRUE)
		return false;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

	memset(infoLog, 0, 1024);
	glGetShaderInfoLog(shader, 1024, 0, infoLog);

	printf("Shader Compilation Error Log: %s \n", infoLog);

	return true;

}

bool OGL_HasShaderLinkError(GLuint shaderProgram)
{
	char infoLog[256];
	GLint success = 0;

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (success == GL_TRUE)
		return false;

	memset(infoLog, 0, 1024);
	
	glGetProgramInfoLog(shaderProgram, 1024, 0, infoLog);
	
	printf("Shader Linking Error Log: %s \n", infoLog);

	return true;
}

OGLSurface* OGLSurface_Create( const FrameBuffer* const framebuffer)
{
	const unsigned int sizeOfPixelBufferInBytes = framebuffer->Width * framebuffer->Height * 4;
	unsigned int numBuffer = 0;
	
	OGLSurface* surface = malloc( sizeof(OGLSurface));
	memset( surface, 0, sizeof(OGLSurface));
	
	// generate texture
	glGenTextures(NUM_BUFFERS, surface->TextureID);

	for (numBuffer; numBuffer < NUM_BUFFERS; ++numBuffer)
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

	// generate shader
	{
		// create shaders
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		GLuint shaderProgram = glCreateProgram();

		GLint vertexShaderLength = strlen(vertexShaderSource);
		GLint fragmentShaderLength = strlen(fragmentShaderSource);

		const GLchar* vertexShaderSourcePtr = vertexShaderSource;
		const GLchar* fragmentShaderSourcePtr = fragmentShaderSource;

		// vertex shader load and compile
		glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, &vertexShaderLength);
		glCompileShader(vertexShader);

		OGL_HasShaderCompilationError(vertexShader);

		// fragment shader load and compile
		glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, &fragmentShaderLength);
		glCompileShader(fragmentShader);

		OGL_HasShaderCompilationError(fragmentShader);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glLinkProgram(shaderProgram);

		OGL_HasShaderLinkError(shaderProgram);

		// delete shader objects
		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		surface->ShaderProgram = shaderProgram;
	}

	// generate dummy vao, is required to use glDrawArrays with no data
	{
		glGenVertexArrays(1, &surface->VaoDummy);
	}

	surface->SizeInBytes = sizeOfPixelBufferInBytes;

	// generate pixel buffer
	glGenBuffers(NUM_BUFFERS, surface->PixelBufferID);
	for (unsigned int i = 0; i < NUM_BUFFERS; ++i)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, surface->PixelBufferID[i]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, surface->SizeInBytes, NULL, GL_STREAM_DRAW);
	}
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	// we start with mapping the first buffer to the pixel data address space
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, surface->PixelBufferID[0]);
	surface->PixelData[0] = (unsigned int*)glMapBuffer( GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY_ARB );
	memset(surface->PixelData[0], 0, surface->SizeInBytes);

	return surface;
}

void OGLSurface_Destroy( OGLSurface* const surface)
{
	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

	glDeleteProgram(surface->ShaderProgram);

	glDeleteVertexArrays(1, &surface->VaoDummy);

	glDeleteTextures( NUM_BUFFERS, surface->TextureID);
	glDeleteBuffers(NUM_BUFFERS, surface->PixelBufferID);
	free(surface);
}

void OGLSurface_MapToFrameBuffer( OGLSurface* const surface, FrameBuffer* const frameBuffer)
{
	frameBuffer->Pixels = surface->PixelData[surface->CurrentBuffer];
}

void OGLSurface_Draw( OGLSurface* const surface)
{
	GLuint currentTexture = surface->CurrentBuffer;

	// stop the mapping of the current PBO
	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

	// bind the current PBO to a texture and copy the PBO data to the texture
	glBindTexture(GL_TEXTURE_2D, surface->TextureID[surface->CurrentBuffer]);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, surface->PixelBufferID[surface->CurrentBuffer]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->Width, surface->Height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// switch to a new PBO
	++surface->CurrentBuffer;
	surface->CurrentBuffer %= NUM_BUFFERS;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, surface->TextureID[currentTexture]);

	glBindVertexArray(surface->VaoDummy);

	glUseProgram(surface->ShaderProgram);

	glUniform1i(glGetUniformLocation(surface->ShaderProgram, "texture"), 0);

	CHECK_OGL_ERROR_IN_DEBUG;
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glUseProgram(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	// setup the next PBO mapping
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, surface->PixelBufferID[surface->CurrentBuffer]);
	glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, surface->SizeInBytes, 0, GL_STREAM_DRAW_ARB);
	surface->PixelData[surface->CurrentBuffer] = (unsigned int*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);

	glFinish();


}
