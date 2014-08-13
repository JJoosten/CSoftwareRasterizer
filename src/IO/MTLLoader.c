#include "MTLLoader.h"
#include "FileLoading.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void parseFloatFromLine( float* inOutFloat, char* stringToParse, unsigned int length)
{
	unsigned int startIndex = 0;
	unsigned int endIndex = 0;

	while( endIndex < length && stringToParse[endIndex] != ' ' && stringToParse[endIndex] != '\n' && stringToParse[endIndex] != '\0') { ++endIndex; continue; }

	// parse float
	{
		static char valueBuffer[64];

		unsigned int valueLength = endIndex - startIndex - 1;
		memcpy( valueBuffer, &stringToParse[startIndex], valueLength);
		valueBuffer[valueLength] = '\0';

		*inOutFloat = (float)atof(valueBuffer);
	}
}

static void parseVec3FromLine( Vec3* inOutVec3, char* stringToParse, unsigned int length)
{
	unsigned int startIndexOfValue = 0;
	unsigned int numIndexOfVector = 0;					

	// parse string with positions
	while( startIndexOfValue < length)
	{
		unsigned int endIndexOfValue = startIndexOfValue;
								
		// move forward as long as character is ' '
		while( endIndexOfValue < length && stringToParse[endIndexOfValue] != '\n' && stringToParse[endIndexOfValue] != ' ') { ++endIndexOfValue; continue; }

		// parse value
		{
			static char valueBuffer[64];

			memcpy( valueBuffer, &stringToParse[startIndexOfValue], endIndexOfValue - startIndexOfValue);
			valueBuffer[endIndexOfValue - startIndexOfValue] = '\0';

			(*inOutVec3).XYZ[numIndexOfVector] = (float)atof(valueBuffer);

			++numIndexOfVector;
		}
									
		startIndexOfValue = endIndexOfValue + 1;

		if(numIndexOfVector >= 3)
			break;

	}
}

MTLFile* MTLFile_Load( const char* const mtlFile)
{
	File file;

	MTLFile* materialSet = malloc(sizeof(MTLFile));
	memset( materialSet, 0, sizeof(MTLFile));

	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, mtlFile);

	// parse file
	{
		MTLMaterial** currentMaterial = &materialSet->Material;
		unsigned int i = 0;
		for( i; i < file.FileSizeInBytes; ++i)
		{
			// STARTOF newmtl
			if( strncmp( &file.FileData[i], "newmtl " , 7) == 0)
			{
				unsigned int nameLength = 0;

				materialSet->NumMaterialsInLinkedList++;

				if( *currentMaterial != NULL)
					currentMaterial = (MTLMaterial**)&(*currentMaterial)->Next;
				
				*currentMaterial = malloc(sizeof(MTLMaterial));
				memset(*currentMaterial, 0, sizeof(MTLMaterial));
				
				// jump over the newmtl 
				i += 7;

				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				// parse name by getting the remainder of the line length and copying the name
				{
					unsigned int startNameIndex = i;
					unsigned int endNameIndex = 0;

					while( i < file.FileSizeInBytes && file.FileData[i] != '\n') { ++i; continue; }

					endNameIndex = i;
					
					(*currentMaterial)->NameLength = endNameIndex - startNameIndex - 1;
					(*currentMaterial)->Name = malloc(sizeof(char) * (*currentMaterial)->NameLength + 1);
					memcpy( (*currentMaterial)->Name, &file.FileData[startNameIndex], (*currentMaterial)->NameLength);
					(*currentMaterial)->Name[(*currentMaterial)->NameLength] = '\0';
				}
			} // ENDOF newmtl

			// STARTOF specular coefficient
			if( strncmp( &file.FileData[i], "Ns " , 3) == 0)
			{
				unsigned int startIndex = 0;
				unsigned int endIndex = 0;

				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				parseFloatFromLine( &(*currentMaterial)->SpecularCoefficient, &file.FileData[i], file.FileSizeInBytes - i);

			}
			// ENDOF specular coefficient
			
			// STARTOF index of refraction coefficient
			if( strncmp( &file.FileData[i], "Ni " , 3) == 0)
			{
				unsigned int startIndex = 0;
				unsigned int endIndex = 0;

				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }
				
				parseFloatFromLine( &(*currentMaterial)->IndexOfRefraction, &file.FileData[i], file.FileSizeInBytes - i);

			}
			// ENDOF index of refraction coefficient

			// STARTOF ambient color
			if( strncmp( &file.FileData[i], "Ka " , 3) == 0)
			{
				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				parseVec3FromLine( &(*currentMaterial)->AmbientColor, &file.FileData[i], file.FileSizeInBytes - i);

			}
			// ENDOF ambient color

			// STARTOF specular color
			if( strncmp( &file.FileData[i], "Ks " , 3) == 0)
			{
				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				parseVec3FromLine( &(*currentMaterial)->SpecularColor, &file.FileData[i], file.FileSizeInBytes - i);

			}
			// ENDOF specular color

			// STARTOF diffuse color
			if( strncmp( &file.FileData[i], "Kd " , 3) == 0)
			{
				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				parseVec3FromLine( &(*currentMaterial)->DiffuseColor, &file.FileData[i], file.FileSizeInBytes - i);
			}
			// ENDOF diffuse color


		}
	}

	return materialSet;
}

void MTLFile_Unload( MTLFile* mtlFile)
{
	MTLMaterial* currentMaterial = mtlFile->Material;
	while( currentMaterial != NULL)
	{
		MTLMaterial* nextMaterial = (MTLMaterial*)currentMaterial->Next;
		
		// clear members
		free(currentMaterial->Name);
		
		// clear object
		free(currentMaterial);
		currentMaterial = nextMaterial;
	}
}