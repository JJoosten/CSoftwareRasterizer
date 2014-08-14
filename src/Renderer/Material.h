#ifndef CSR_MATERIAL_H
#define CSR_MATERIAL_H

#include "../Math/Vec3.h"
#include "../Texture/Texture.h"

typedef struct
{
	//Vec3 AmbientColor;
	Vec3 DiffuseColor;
	Vec3 SpecularColor;
	float SpecularCoefficient;
	
	Texture* DiffuseTexture;
	Texture* SpecularTexture;
	//Texture* AlphaTexture;
	Texture* NormalTexture;

	unsigned int MaterialID;

} Material;

#endif