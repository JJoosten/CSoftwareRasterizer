#include "MTLLoader.h"
#include "FileLoading.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

MTLFile* MTLFile_Load( const char* const mtlFile)
{
	File file;

	MTLFile* materialSet = malloc(sizeof(MTLFile));
	memset( materialSet, 0, sizeof(MTLFile));

	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, mtlFile);

	// parse file
	{
		MTLMaterial* currentMaterial = materialSet->Material;
		unsigned int i = 0;
		for( i; i < file.FileSizeInBytes; ++i)
		{
			// STARTOF newmtl
			if( strncmp( &file.FileData[i], "newmtl " , 7) == 0)
			{
				unsigned int nameLength = 0;

				materialSet->NumMaterialsInLinkedList++;

				if(currentMaterial != NULL)
					currentMaterial = (MTLMaterial*)currentMaterial->Next;
				
				currentMaterial = malloc(sizeof(MTLMaterial));
				
				// jump over the newmtl 
				i += 7;

				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				// parse name by getting the remainder of the line length and copying the name
				{
					unsigned int startNameIndex = i;
					unsigned int endNameIndex = 0;

					while( i < file.FileSizeInBytes && file.FileData[i] != '\n') { ++i; continue; }

					endNameIndex = i;
					
					currentMaterial->NameLength = endNameIndex - startNameIndex - 1;
					currentMaterial->Name = malloc(sizeof(char) * currentMaterial->NameLength + 1);
					memcpy( currentMaterial->Name, &file.FileData[startNameIndex], currentMaterial->NameLength);
					currentMaterial->Name[currentMaterial->NameLength] = '\0';

					printf(currentMaterial->Name);
				}

				i += currentMaterial->NameLength;
			} // ENDOF newmtl

			// STARTOF specular coefficient
			if( strncmp( &file.FileData[i], "Ns " , 3) == 0)
			{
				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }


			}
			// ENDOF specular coefficient

			// STARTOF specular color
			if( strncmp( &file.FileData[i], "Ks " , 3) == 0)
			{
				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }


			}
			// ENDOF specular color

			// STARTOF diffuse color
			if( strncmp( &file.FileData[i], "Kd " , 3) == 0)
			{
				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }


			}
			// ENDOF diffuse color



		}
	}

	return materialSet;
}

void MTLFile_Unload( MTLFile* mtlFile)
{
	// QQQ TODO:IMPLEMENT
}