#ifndef CSR_TEXTURE_H
#define CSR_TEXTURE_H

#include "../Defines.h"

typedef struct sTexture
{
	unsigned int Width;
	unsigned int Height;
	unsigned int* Texels;
} Texture;

Texture* Texture_Create( const unsigned int width, const unsigned int height);
Texture* Texture_Load( const char* const textureFile);
void Texture_Destroy( Texture* texture);

// unsigned int FetchTexel( const float u, const float v, const unsigned int mipLevel);
// unsigned int FetchBilinearFilteredTexel( const float u, const float v, const unsigned int mipLevel);
// unsigned int FetchTrilinearFilteredTexel( const float u, const float v, const unsigned int mipLevel);


#endif // TEXTURE_H