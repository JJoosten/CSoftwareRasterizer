#ifndef CSR_PIXEL_SHADER_H
#define CSR_PIXEL_SHADER_H

typedef struct
{
	float Time;
} DefaultPixelShaderUniforms;

typedef unsigned int RGBA8;

// function description

// TODO: add vertex interpolation values to this function
typedef RGBA8(*PixelShaderFunction)( const void* const uniforms);


RGBA8 DefaultPixelShader( const void* const uniforms);

#endif // CSR_PIXEL_SHADER_H
