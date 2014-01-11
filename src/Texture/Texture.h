#ifndef CSR_TEXTURE_H
#define CSR_TEXTURE_H

#include "../Defines.h"

typedef struct sTexture
{
	unsigned int Width;
	unsigned int Height;
	unsigned int* Texels;
} Texture;

Texture* TextureCreate( const unsigned int width, const unsigned int height);
Texture* TextureLoad( const char* const textureFile);
void TextureDestroy( Texture* texture);


#endif // TEXTURE_H