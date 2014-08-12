#include "MTLLoader.h"
#include "FileLoading.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


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
			char valueBuffer[64];

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
			char tmpBuffer[64];

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

				startIndex = i;

				while( i < file.FileSizeInBytes && file.FileData[i] != ' ' && file.FileData[i] != '\n' && file.FileData[i] != '\0') { ++i; continue; }

				endIndex = i;

				// parse float TODO: make this a function
				{
					unsigned int valueLength = endIndex - startIndex - 1;
					memcpy( tmpBuffer, &file.FileData[startIndex], valueLength);
					tmpBuffer[valueLength] = '\0';

					(*currentMaterial)->SpecularCoefficient = (float)atof(tmpBuffer);
				}

			}
			// ENDOF specular coefficient
			
			// STARTOF index of refraction coefficient
			if( strncmp( &file.FileData[i], "Ni " , 3) == 0)
			{
				unsigned int startIndex = 0;
				unsigned int endIndex = 0;

				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				startIndex = i;

				while( i < file.FileSizeInBytes && file.FileData[i] != ' ' && file.FileData[i] != '\n' && file.FileData[i] != '\0') { ++i; continue; }

				endIndex = i;

				// parse float
				{
					unsigned int valueLength = endIndex - startIndex - 1;
					memcpy( tmpBuffer, &file.FileData[startIndex], valueLength);
					tmpBuffer[valueLength] = '\0';

					(*currentMaterial)->IndexOfRefraction = (float)atof(tmpBuffer);
				}

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
	// QQQ TODO:IMPLEMENT
}