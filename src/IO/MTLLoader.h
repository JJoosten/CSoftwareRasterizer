#ifndef CSR_MTL_LOADING_H
#define CSR_MTL_LOADING_H

#include "../Math/Vec3.h"

typedef struct
{
	char* FilePath;
	unsigned int FilePathLength;
} MTLTexture;

typedef struct
{
	Vec3 Diffuse;
	Vec3 Specular;
	float SpecularCoefficient;

	MTLTexture DiffuseTexture;
	MTLTexture SpecularTexture;
	MTLTexture AlphaTexture;
	MTLTexture NormalTexture;

	char* Name;
	unsigned int NameLength;

	void* Next;

} MTLMaterial;

typedef struct
{
	MTLMaterial* Material;
	unsigned int NumMaterialsInLinkedList;

} MTLFile;

MTLFile* MTLFile_Load( const char* const mtlFile);
void MTLFile_Unload( MTLFile* mtlFile);


#endif