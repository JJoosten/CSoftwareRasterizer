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


Mesh* Load_OBJFile( const char* const objFile)
{
	Mesh* mesh = NULL;

	File file;
	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, objFile);

	// parse fileData in two passes

	// first pass counts data 
	{
		unsigned int i = 0;
		unsigned int numPositions = 0;
		unsigned int numNormals = 0;
		unsigned int numUVs = 0;
		unsigned int numFaces = 0;
		unsigned int numObjects = 0;
		unsigned int numMaterials = 0;

		// parse data counts
		for( i; i < file.FileSizeInBytes; ++i)
		{
			// count positions
			if( strncmp( &file.FileData[i], "v ", 2) == 0)
				numPositions++;

			// count normals
			if( strncmp( &file.FileData[i], "vn ", 3) == 0)
				numNormals++;

			// count uvs
			if( strncmp( &file.FileData[i], "vt  ", 3) == 0)
				numUVs++;

			// count faces
			if( strncmp( &file.FileData[i], "f  ", 2) == 0)
				numFaces++;

			// count objects
			if( strncmp( &file.FileData[i], "o  ", 2) == 0)
				numObjects++;
			
			// count materials
			if( strncmp( &file.FileData[i], "usemtl ", 7) == 0)
				numMaterials++;

		}

		assert( numPositions && "numVertices is 0");
		
		// second pass retrieves data
		{
			// setup data buffers
			unsigned int j = 0;
			Vec3* const positions = malloc( sizeof(Vec3) * numPositions);
			Vec3* normals = NULL;
			Vec3* uvs = NULL;
			unsigned short* indices = NULL;
			const unsigned int numIndices = numFaces * 6;
			char* materialLibFile = NULL;
			char** materialNames = NULL;
			
			if( numNormals > 0)
				normals = malloc( sizeof(Vec3) * numNormals);

			if( numUVs > 0)
				uvs = malloc( sizeof(Vec3) * numUVs);

			if( numIndices > 0)
				indices = malloc( sizeof(unsigned short) * numIndices);

			if( numMaterials > 0)
				materialNames = malloc( sizeof(char*) * numMaterials);

			// parse data
			{
				// data tracking
				unsigned int materialNameIndexToProcess = 0;
				unsigned int posNormUVIndexToProcess[3] = { 0, 0, 0 };
				Vec3* const arrayToPosOrNormOrUV[3] = { positions, normals, uvs };
				
				// line parsing data
				unsigned int startOfLine = 0;
				char valueToParse[MAX_VALUE_LENGTH_IN_CHARS];

				// retrieve data from file
				for( j; j < file.FileSizeInBytes; ++j)
				{
					// parse line
					if( file.FileData[j] == '\n')
					{
						unsigned int k = 0;

						// copy line to work buffer
						const unsigned int lineLength = j - startOfLine;
						
						char* lineToParse = &file.FileData[startOfLine];

						// check what data we are dealing with
						for( k; k < lineLength; ++k)
						{
							int isType = eNone;

							if( strncmp( &lineToParse[k], "v ", 2) == 0)
							{
								isType = ePosition;
								k += 2;
							}
							if( strncmp( &lineToParse[k], "vn ", 3) == 0)
							{
								isType = eNormal;
								k += 3;
							}
							if( strncmp( &lineToParse[k], "vt  ", 3) == 0)
							{
								isType = eUV;
								k += 3;
							}

							if(isType != eNone)
							{
								unsigned int indexOfPosition = 0;
								unsigned int startOfValue = 0;

								while( k < lineLength)
								{
									// move forward as long as character is ' '
									while( k < lineLength && lineToParse[k] == ' ') { ++k; continue; }

									startOfValue = k;

									// move forward until end of value
									while( k < lineLength && lineToParse[k] != ' ' && lineToParse[k] != '\0' && lineToParse[k] != '\n') { ++k; }

									// parse position, normal or UV
									{
										const unsigned int numCharactersDescribeValue = k - startOfValue - 1;

										assert( numCharactersDescribeValue < MAX_VALUE_LENGTH_IN_CHARS && "numCharactersDescribeValue is longer then MAX_VALUE_LENGTH_IN_CHARS");
									
										memcpy( valueToParse, &lineToParse[startOfValue], sizeof(char) * numCharactersDescribeValue);
										valueToParse[numCharactersDescribeValue] = '\0';

										// convert string to float
										{
											const float value = (float)atof(valueToParse);

											arrayToPosOrNormOrUV[isType][posNormUVIndexToProcess[isType]].XYZ[indexOfPosition] = value;

											printf("value: %f posNormUVIndex: %i index: %i \n", value, isType, indexOfPosition);

											indexOfPosition++;
										}
									}

								}

								++posNormUVIndexToProcess[isType];

								break;
							}

							// count faces
							if( strncmp( &lineToParse[k], "f  ", 2) == 0)
							{
								k += 2;

								// TODO: retrieve face (can be 3 or 4 elements)
								break;
							}

							// count objects
							if( strncmp( &lineToParse[k], "o  ", 2) == 0)
							{
								k += 2;

								// TODO: retrieve object

								break;
							}

							// get material lib file
							if( strncmp( &lineToParse[k], "mtllib ", 7) == 0)
							{
								unsigned int startOfString = 0;

								k += 7;

								// move forward as long as character is ' '
								while( k < lineLength && lineToParse[k] == ' ') { ++k; continue; }

								startOfString = k;
								
								while( k < lineLength && lineToParse[k] != ' ' && lineToParse[k] != '\0' && lineToParse[k] != '\n') { ++k; }

								// retrieve string
								{
									const unsigned int numCharactersDescribeValue = k - startOfString;
									materialLibFile = malloc(sizeof(char) * numCharactersDescribeValue);
									memcpy( materialLibFile,  &lineToParse[startOfString], numCharactersDescribeValue);
									materialLibFile[numCharactersDescribeValue] = '\0';
									printf(materialLibFile);
								}

								break;
							}
								
							if( strncmp( &lineToParse[k], "usemtl ", 7) == 0)
							{
								unsigned int startOfString = 0;

								k += 7;

								// move forward as long as character is ' '
								while( k < lineLength && lineToParse[k] == ' ') { ++k; continue; }

								startOfString = k;
								
								while( k < lineLength && lineToParse[k] != ' ' && lineToParse[k] != '\0' && lineToParse[k] != '\n') { ++k; }

								// retrieve string
								{
									const unsigned int numCharactersDescribeValue = k - startOfString;
									materialNames[materialNameIndexToProcess] = malloc(sizeof(char) * numCharactersDescribeValue);
									memcpy( materialNames[materialNameIndexToProcess],  &lineToParse[startOfString], numCharactersDescribeValue);
									materialNames[materialNameIndexToProcess][numCharactersDescribeValue] = '\0';
									printf(materialNames[materialNameIndexToProcess]);
								}

								++materialNameIndexToProcess;

								break;
							}


						}
					
						startOfLine = j + 1;
					}
				}
			}
			
			// create mesh
			//mesh = Mesh_Create( vertices, numVertices, indices, numIndices);
		}
	}

	return mesh;
}