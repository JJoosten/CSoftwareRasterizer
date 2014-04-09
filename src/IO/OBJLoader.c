#include "OBJLoader.h"
#include "FileLoading.h"
#include "../VertexData/Mesh.h" // includes, vertex.h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_VALUE_LENGTH_IN_CHARS 32


typedef enum
{
	eNone = -1,
	ePosition,
	eNormal,
	eUV
} PosNormUVTrackIndex;


void retrieveStringFromLine( char** stringOUT, unsigned int* stringLengthOUT, const char* lineIN, const unsigned int lineLengthIN)
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
		*stringLengthOUT = stringLength;
		*stringOUT = malloc(sizeof(char) * stringLength + 1);
		memcpy( *stringOUT,  &lineIN[startOfString], stringLength);
		(*stringOUT)[stringLength] = '\0';
	}
}

OBJFile* Load_OBJFile( const char* const objFilePath)
{
	File file;

	OBJFile* scene = malloc(sizeof(OBJFile));
	memset(scene, 0, sizeof(OBJFile));

	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, objFilePath);

	// itterate over data and create objects, groups and collect data
	{
		unsigned int startOfCurrentObjectInFile = 0;
		OBJObject** currentObject = NULL;

		unsigned int i = 0;
		for( i; i < file.FileSizeInBytes; ++i)
		{
			// create an object for each encountered and retrieve name 
			if( strncmp( &file.FileData[i], "o  ", 2) == 0 ||
				strncmp( &file.FileData[i], "##  ", 3) == 0)
			{
				++scene->NumObjects;	
				i += 2;

				if(scene->Objects != NULL)
				{
					currentObject = &(OBJObject*)(scene->Objects->NextObject);
					while(*currentObject != NULL)
						currentObject = &(OBJObject*)((*currentObject)->NextObject);
					*currentObject = malloc(sizeof(OBJObject));
					memset(*currentObject, 0, sizeof(OBJObject));
				}
				else
				{
					currentObject = &scene->Objects;
					*currentObject = malloc(sizeof(OBJObject));
					memset(*currentObject, 0, sizeof(OBJObject));
				}
				
				retrieveStringFromLine( &(*currentObject)->Name, &(*currentObject)->NameLength, &file.FileData[i], file.FileSizeInBytes); 
			
				i += (*currentObject)->NameLength;

				// count object data
				{
					unsigned int j = i;
					for( j; j < file.FileSizeInBytes; ++j)
					{
						// count positions
						if( strncmp( &file.FileData[j], "v ", 2) == 0)
						{
							(*currentObject)->NumPositions += 1;
							j += 2;
						}

						// count normals
						if( strncmp( &file.FileData[j], "vn ", 3) == 0)
						{
							(*currentObject)->NumNormals += 1;
							j += 3;
						}

						// count uvs
						if( strncmp( &file.FileData[j], "vt  ", 3) == 0)
						{
							(*currentObject)->NumUVs += 1;
							j += 3;
						}
					}
				} // END OF count object data

				// collect vertices
				if( strncmp( &file.FileData[i], "v ", 2) == 0)
				{

					i += 2;
				}

				// collect normals
				if( strncmp( &file.FileData[i], "vn ", 3) == 0)
				{

					i += 3;
				}

				// collect uvs
				if( strncmp( &file.FileData[i], "vt  ", 3) == 0)
				{

					i += 3;
				}

			}






		}
	}

	return scene;
}