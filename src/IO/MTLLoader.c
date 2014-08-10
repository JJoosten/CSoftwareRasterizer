#include "MTLLoader.h"
#include "FileLoading.h"
#include <string>

MTLFile* Load_MTLFile( const char* const mtlFile)
{
	File file;

	MTLFile* materialSet = malloc(sizeof(MTLFile));
	memset( materialSet, 0, sizeof(MTLFile));

	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, mtlFile);

	/*
	// parse file
	{
		MTLMaterial* currentMaterial = materialSet->Material;
		unsigned int i = 0;
		for( i; i < file.FileSizeInBytes; ++i)
		{
			if( strncmp( &file.FileData[j], "newmtl" , 6) == 0)
			{
				unsigned int nameLength = 0;

				materialSet->NumMaterialsInLinkedList++;

				if(currentMaterial != NULL)
					currentMaterial = currentMaterial->Next;
				
				currentMaterial = malloc(sizeof(MTLMaterial))

				// TODO:  parse name

				i = i + 6 + nameLength;
			}
		}
	}
	*/

	return materialSet;
}
