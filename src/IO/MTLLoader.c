#include "MTLLoader.h"
#include "FileLoading.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void retrieveStringFromLine( char** stringOUT, unsigned int* stringLengthOUT, const char* lineIN, const unsigned int lineLengthIN)
{
	unsigned int startOfString = 0;

	unsigned int i = 0;

	// move forward as long as character is ' '
	while( i < lineLengthIN && lineIN[i] == ' ') { ++i; continue; }

	startOfString = i;
								
	while( i < lineLengthIN && lineIN[i] != ' ' &&  lineIN[i] != '\0' &&  lineIN[i] != '\n') { ++i; }

	// retrieve string
	{
		const unsigned int stringLength = i - startOfString;
		*stringLengthOUT = stringLength - 1;
		*stringOUT = malloc(sizeof(char) * stringLength);
		memcpy( *stringOUT,  &lineIN[startOfString], stringLength - 1);
		(*stringOUT)[stringLength - 1] = '\0';
	}
}

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

				retrieveStringFromLine( &(*currentMaterial)->Name, &(*currentMaterial)->NameLength, &file.FileData[i], file.FileSizeInBytes); 
			
				i += (*currentMaterial)->NameLength;
			} // ENDOF newmtl

			// STARTOF specular coefficient
			if( strncmp( &file.FileData[i], "Ns " , 3) == 0)
			{
				i += 3;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

				parseFloatFromLine( &(*currentMaterial)->SpecularCoefficient, &file.FileData[i], file.FileSizeInBytes - i);
			}
			// ENDOF specular coefficient
			
			// STARTOF index of refraction coefficient
			if( strncmp( &file.FileData[i], "Ni " , 3) == 0)
			{
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
			
			// STARTOF alpha
			if( strncmp( &file.FileData[i], "d " , 2) == 0 || strncmp( &file.FileData[i], "Tr" , 2) == 0)
			{
				unsigned int startIndex = 0;
				unsigned int endIndex = 0;

				i += 2;
				
				while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }
				
				(*currentMaterial)->AlphaValue = 1.0f;
				parseFloatFromLine( &(*currentMaterial)->AlphaValue, &file.FileData[i], file.FileSizeInBytes - i);
			}
			// ENDOF alpha
			
			// STARTOF texture diffuse
			if( strncmp( &file.FileData[i], "map_Kd " , 7) == 0)
			{
				i += 7;

				retrieveStringFromLine( &(*currentMaterial)->DiffuseTexture.FilePath, &(*currentMaterial)->DiffuseTexture.FilePathLength, &file.FileData[i], file.FileSizeInBytes); 
			
				i += (*currentMaterial)->DiffuseTexture.FilePathLength;
			}
			// ENDOF texture diffuse
		
			// STARTOF texture specular
			if( strncmp( &file.FileData[i], "map_Ks " , 7) == 0)
			{
				i += 7;

				retrieveStringFromLine( &(*currentMaterial)->SpecularTexture.FilePath, &(*currentMaterial)->SpecularTexture.FilePathLength, &file.FileData[i], file.FileSizeInBytes); 
			
				i += (*currentMaterial)->SpecularTexture.FilePathLength;
			}
			// ENDOF texture specular
		
			// STARTOF texture alpha
			if( strncmp( &file.FileData[i], "map_d " , 6) == 0)
			{
				i += 6;

				retrieveStringFromLine( &(*currentMaterial)->AlphaTexture.FilePath, &(*currentMaterial)->AlphaTexture.FilePathLength, &file.FileData[i], file.FileSizeInBytes); 
			
				i += (*currentMaterial)->AlphaTexture.FilePathLength;
			}
			// ENDOF texture alpha
	
			// STARTOF texture normal 
			if( strncmp( &file.FileData[i], "map_bump " , 9) == 0)
			{
				i += 9;

				retrieveStringFromLine( &(*currentMaterial)->NormalTexture.FilePath, &(*currentMaterial)->NormalTexture.FilePathLength, &file.FileData[i], file.FileSizeInBytes); 
			
				i += (*currentMaterial)->NormalTexture.FilePathLength;
			}
			// ENDOF texture normal
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

		if( currentMaterial->DiffuseTexture.FilePath != NULL)
			free(currentMaterial->DiffuseTexture.FilePath);
		if( currentMaterial->SpecularTexture.FilePath != NULL)
			free(currentMaterial->SpecularTexture.FilePath);
		if( currentMaterial->AlphaTexture.FilePath != NULL)
			free(currentMaterial->AlphaTexture.FilePath);
		if( currentMaterial->NormalTexture.FilePath != NULL)
			free(currentMaterial->NormalTexture.FilePath);
		
		// clear object
		free(currentMaterial);
		currentMaterial = nextMaterial;
	}
}