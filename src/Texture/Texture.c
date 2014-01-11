#include "Texture.h"
#include "../Utility/Validate.h"
#include <stdlib.h>
#include <assert.h>
#include "../../libs/stb_image/stb_image.h"


Texture* Texture_Create( const unsigned int width, const unsigned int height)
{
	unsigned int x = 0;
	unsigned int y = 0;

	Texture* texture = malloc( sizeof(Texture));
	
	assert(texture && "Texture_Create texture is NULL");

	texture->Width = width;
	texture->Height = height;
	texture->Texels = (unsigned int*)malloc( sizeof(unsigned int) * width * height);

	assert(texture->Texels && "Texture_Create texture->Texels is NULL, probably not enough memory in RAM");

	for( y; y < texture->Height; ++y)
	{
		for( x; x < texture->Width; ++x)
		{
			texture->Texels[y * texture->Width + x] = 0xFF0000FF;
		} 
	}

	return texture;
}

Texture* Texture_Load( const char* const textureFile)
{
	// QQQ add support for RGB textures and for !pow2 textures

	Texture* texture = malloc( sizeof(Texture));
	
	// currently all textures are saved as RGBA (req_cmp is set to 4 channels)
	unsigned int numComponents = 0;
	texture->Texels = (unsigned int*)stbi_load( textureFile, &texture->Width, &texture->Height, &numComponents, 4);
	
	assert( texture->Texels && "Texture_Load textureData is NULL, probably file not found!");
	assert( IsPow2(texture->Width) && "Texture_Load texture->Width != pow2");
	assert( IsPow2(texture->Height) && "Texture_Load texture->Height != pow2");

	return texture;
}

void Texture_Destroy( Texture* texture)
{
	assert( texture && "Texture_Destroy texture is NULL");
	assert( texture->Texels && "Texture_Destroy texture->Data is NULL");

	free(texture->Texels);
	free(texture);
}