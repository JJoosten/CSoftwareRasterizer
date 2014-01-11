#ifndef CSR_TEXTURE_H
#define CSR_TEXTURE_H

#include "../Defines.h"

#define Texture struct sTexture

Texture
{
	unsigned int Width;
	unsigned int Height;
	unsigned int* Texels;
};

Texture* TextureCreate( const unsigned int width, const unsigned int height);
Texture* TextureLoad( const char* const textureFile);
void TextureDestroy( Texture* texture);


#endif // TEXTURE_H