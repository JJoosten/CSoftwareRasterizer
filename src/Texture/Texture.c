#include "Texture.h"
#include "../Utility/Validate.h"
#include <stdlib.h>
#include <assert.h>
#include "../../libs/stb_image/stb_image.h"


Texture* TextureCreate( const unsigned int width, const unsigned int height)
{
	Texture* texture = malloc( sizeof(Texture));
	
	assert(texture && "TextureCreate texture is NULL");

	texture->Width = width;
	texture->Height = height;
	texture->Texels = malloc( sizeof(unsigned int) * width * height);

	assert(texture->Texels && "TextureCreate texture->Texels is NULL, probably not enough memory in RAM");

	return texture;
}

Texture* TextureLoad( const char* const textureFile)
{
	// QQQ add support for RGB textures and for !pow2 textures

	Texture* texture = malloc( sizeof(Texture));
	
	// currently all textures are saved as RGBA (req_cmp is set to 4 channels)
	unsigned int numComponents = 0;
	texture->Texels = (unsigned int*)stbi_load( textureFile, &texture->Width, &texture->Height, &numComponents, 4);
	
	assert( texture->Texels && "TextureLoad textureData is NULL, probably file not found!");
	assert( IsPow2(texture->Width) && "TextureLoad texture->Width != pow2");
	assert( IsPow2(texture->Height) && "TextureLoad texture->Height != pow2");

	return texture;
}

void TextureDestroy( Texture* texture)
{
	assert( texture && "TextureDestroy texture is NULL");
	assert( texture->Texels && "TextureDestroy texture->Data is NULL");

	free(texture->Texels);
	free(texture);
}