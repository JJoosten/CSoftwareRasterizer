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

typedef struct
{
	unsigned int NumFaces;
	unsigned int NumIndicesPerFace;
	unsigned int NameLength;
	unsigned int* PositionIndices;
	unsigned int* NormalIndices;
	unsigned int* UVIndices;
	char* Name;
} objGroup;

typedef struct 
{
	unsigned int NumPositions;
	unsigned int NumNormals;
	unsigned int NumUVs;
	unsigned int NumGroups;
	unsigned int NameLength;
	Vec3* Positions;
	Vec3* Normals;
	Vec2* UVs;
	objGroup* Groups;
	char* Name;

} objObjects;

typedef struct
{
	unsigned int NumObjects;
	unsigned int MaterialFilePathLength;
	objObjects* Objects;
	char* MaterialFilePath;
} objFile;


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
		printf(*stringOUT);
		printf("\n");
	}
}

Mesh* Load_OBJFile( const char* const objFilePath)
{
	Mesh* mesh = NULL;

	File file;

	objFile objectFile;
	memset(&objectFile, 0, sizeof(objFile));

	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, objFilePath);

	// retrieve num objects and material lib filePath
	{
		unsigned int numObjects = 0;

		// parse num objects and material file path
		unsigned int i = 0;
		for( i; i < file.FileSizeInBytes; ++i)
		{
			// count objects
			if( strncmp( &file.FileData[i], "o  ", 2) == 0)
			{
				numObjects++;	
				i += 2;
			}

			// count objects
			if( strncmp( &file.FileData[i], "##  ", 3) == 0)
			{
				numObjects++;	
				i += 3;
			}

			// get material lib file
			if( strncmp( &file.FileData[i], "mtllib ", 7) == 0)
			{
				i += 7;

				retrieveStringFromLine( &objectFile.MaterialFilePath, &objectFile.MaterialFilePathLength, &file.FileData[i], file.FileSizeInBytes); 
			
				i += objectFile.MaterialFilePathLength;
			}
		}

		if( numObjects > 0)
		{
			objectFile.NumObjects = numObjects;
			objectFile.Objects = malloc( sizeof(objectFile) * numObjects);
		}

		// parse num groups and object names
		{
			int currentObjectIndex = 0;
			unsigned int numGroupsPerObject = 0;

			i = 0; // reset i
			for( i; i < file.FileSizeInBytes; ++i)
			{
				// retrieve object name
				if( strncmp( &file.FileData[i], "o  ", 2) == 0 ||
					strncmp( &file.FileData[i], "##  ", 3) == 0)
				{
					i += 2;
				
					retrieveStringFromLine( &objectFile.Objects[currentObjectIndex].Name, &objectFile.Objects[currentObjectIndex].NameLength, &file.FileData[i], file.FileSizeInBytes); 
			
					i += objectFile.Objects[currentObjectIndex].NameLength;
				
					// make sure every object gets atleast 1 group
					if(currentObjectIndex != 0)
					{
						if(objectFile.Objects[currentObjectIndex - 1].NumGroups == 0)
						{
							objectFile.Objects[currentObjectIndex - 1].NumGroups = 1;
						}
					}

					++currentObjectIndex;
				}
			
				if( strncmp( &file.FileData[i], "g ", 2) == 0)
				{
					i += 2;
					objectFile.Objects[currentObjectIndex].NumGroups += 1;
				}

				// count positions
				if( strncmp( &file.FileData[i], "v ", 2) == 0)
				{
					objectFile.Objects[currentObjectIndex].NumPositions += 1;
					i += 2;
				}

				// count normals
				if( strncmp( &file.FileData[i], "vn ", 3) == 0)
				{
					objectFile.Objects[currentObjectIndex].NumNormals += 1;
					i += 3;
				}

				// count uvs
				if( strncmp( &file.FileData[i], "vt  ", 3) == 0)
				{
					objectFile.Objects[currentObjectIndex].NumUVs += 1;
					i += 3;
				}

			}
			
			i = 0; // reset i
			for( i; i < objectFile.NumObjects; ++i)
			{
				objectFile.Objects[i].Groups = malloc(sizeof(objGroup) * objectFile.Objects[i].NumGroups);
			}

			// parse group names and indices
			{
				unsigned int currentGroupIndex = 0;
				unsigned int numPositions = 0;
				unsigned int numNormals = 0;
				unsigned int numUVs = 0;
				currentObjectIndex = -1; // reset
				
				i = 0; // reset i
				for( i; i < file.FileSizeInBytes; ++i)
				{
					// retrieve object name
					if( strncmp( &file.FileData[i], "o  ", 2) == 0 ||
						strncmp( &file.FileData[i], "##  ", 3) == 0)
					{
						++currentObjectIndex;

						i += 2;
					}

				}
			}

		}

	}
	/*
	// first pass counts data 
	{
		unsigned int numPositions = 0;
		unsigned int numNormals = 0;
		unsigned int numUVs = 0;
		unsigned int numFaces = 0;
		//unsigned int numObjects = 0;
		unsigned int numGroups = 0;
		unsigned int numMaterials = 0;

		// parse data counts
		for( i; i < file.FileSizeInBytes; ++i)
		{
			// count faces
			if( strncmp( &file.FileData[i], "f  ", 2) == 0)
				numFaces++;

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
			unsigned short* indicesForVertices = NULL;
			unsigned short* indicesForNormals = NULL;
			unsigned short* indicesForUVs = NULL;
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


								
								break;
							}

							// count objects
							if( strncmp( &lineToParse[k], "o  ", 2) == 0)
							{
								k += 2;



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
									printf("\n");
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
	*/

	return mesh;
}