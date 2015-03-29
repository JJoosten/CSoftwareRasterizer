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
		*stringLengthOUT = stringLength - 1;
		*stringOUT = malloc(sizeof(char) * stringLength);
		memcpy( *stringOUT,  &lineIN[startOfString], stringLength - 1);
		(*stringOUT)[stringLength - 1] = '\0';
	}
}


void parseVec2FromLine( Vec2* inOutVec2, char* stringToParse, unsigned int length)
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

			(*inOutVec2).XY[numIndexOfVector] = (float)atof(valueBuffer);

			++numIndexOfVector;
		}
									
		startIndexOfValue = endIndexOfValue + 1;

		if(numIndexOfVector >= 2)
			break;

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

OBJFile* OBJFile_Load( const char* const objFilePath)
{
	File file;

	OBJFile* scene = malloc(sizeof(OBJFile));
	memset(scene, 0, sizeof(OBJFile));

	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, objFilePath);

	// iterate over data and create objects, groups and collect data
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
				OBJGroup** currentGroup = NULL;

				++scene->NumObjectsInLinkedList;	
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

				currentGroup = &(*currentObject)->Groups;
				
				// retrieve name and name length of object
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

						// if we find another object or group, break loop
						if( strncmp( &file.FileData[j], "o  ", 2) == 0 ||
							strncmp( &file.FileData[j], "##  ", 3) == 0 ||
							strncmp( &file.FileData[j], "g ", 2) == 0 ||
							strncmp( &file.FileData[j], "f ", 2) == 0 ||
							strncmp( &file.FileData[j], "usemtl ", 7) == 0)
							break;
					}
				} // END OF count object data

				// generate the buffers to store the positions, normals and uvs in
				if((*currentObject)->NumPositions > 0)
					(*currentObject)->Positions = malloc(sizeof(Vec3) * (*currentObject)->NumPositions);
				if((*currentObject)->NumNormals > 0)
					(*currentObject)->Normals = malloc(sizeof(Vec3) * (*currentObject)->NumNormals);
				if((*currentObject)->NumUVs > 0)
					(*currentObject)->UVs = malloc(sizeof(Vec2) * (*currentObject)->NumUVs);

				{
					unsigned int numPositionsParsed = 0;
					unsigned int numNormalsParsed = 0;
					unsigned int numUVsParsed = 0;
					unsigned int currentStorePositionIndex = 0;
					unsigned int currentStoreUVIndex = 0;
					unsigned int currentStoreNormalIndex = 0;

					// collect object data
					for( i; i < file.FileSizeInBytes; ++i)
					{
						if( strncmp( &file.FileData[i], "o  ", 2) == 0 ||
							strncmp( &file.FileData[i], "##  ", 3) == 0)
						{
							// make sure we find the o and ## again on next big itteration!
							i -= 1;
							break;
						}

						// collect vertices
						if( strncmp( &file.FileData[i], "v ", 2) == 0)
						{
							i += 2;

							assert(numPositionsParsed < (*currentObject)->NumPositions && "NumPositionsParsed bigger then countend positions");

							parseVec3FromLine(&(*currentObject)->Positions[numPositionsParsed], &file.FileData[i], file.FileSizeInBytes - i);
						
							++numPositionsParsed;
						}

						// collect normals
						if( strncmp( &file.FileData[i], "vn ", 3) == 0)
						{
							i += 3;

							assert(numNormalsParsed < (*currentObject)->NumNormals && "numNormalsParsed bigger then countend positions");
							
							parseVec3FromLine(&(*currentObject)->Normals[numNormalsParsed], &file.FileData[i], file.FileSizeInBytes - i);

							++numNormalsParsed;
						}

						// collect uvs QQQ TEST THIS (parseVec2FromLine)
						if( strncmp( &file.FileData[i], "vt  ", 3) == 0)
						{
							i += 3;

							assert(numUVsParsed < (*currentObject)->NumUVs && "numUVsParsed bigger then countend positions");
	
							parseVec2FromLine(&(*currentObject)->UVs[numUVsParsed],  &file.FileData[i], file.FileSizeInBytes - i);

							++numUVsParsed;
						}

						// collect group data without current group
						if( strncmp( &file.FileData[i], "g ", 2) == 0 ||
							strncmp( &file.FileData[i], "f ", 2) == 0 ||
							strncmp( &file.FileData[i], "usemtl ", 7) == 0)
						{

							if( *currentGroup == NULL)
							{
								OBJGroup** group = &(*currentObject)->Groups;

								while(*group != NULL)
									*group = (*group)->NextGroup;
								*group =  malloc(sizeof(OBJGroup));
								*currentGroup = *group; 
								memset( *currentGroup, 0, sizeof(OBJGroup));
								++((*currentObject)->NumGroupsInLinkedList);
			
								if( strncmp( &file.FileData[i], "g ", 2) != 0)
								{
									const char rootName[] = "Root";

									(*currentGroup)->Name = malloc(sizeof(char) * 5);
									memcpy((*currentGroup)->Name, rootName, 4);
									(*currentGroup)->Name[4] = '\0';
									(*currentGroup)->NameLength = 4;
								}
								else
								{
									i += 2;
				
									// retrieve name and name length of object
									retrieveStringFromLine( &(*currentGroup)->Name, &(*currentGroup)->NameLength, &file.FileData[i], file.FileSizeInBytes); 
			
									i += (*currentGroup)->NameLength;
								}

								// count group data
								{
									unsigned int j = i;
									for( j; j < file.FileSizeInBytes; ++j)
									{
										// count positions
										if( strncmp( &file.FileData[j], "v ", 2) == 0 ||
											strncmp( &file.FileData[j], "vn ", 3) == 0 ||
											strncmp( &file.FileData[j], "vt  ", 3) == 0 ||
											strncmp( &file.FileData[j], "o  ", 2) == 0 ||
											strncmp( &file.FileData[j], "##  ", 3) == 0 ||
											strncmp( &file.FileData[j], "g ", 2) == 0)
											break;
								
										if( strncmp( &file.FileData[j], "f ", 2) == 0)
										{
											unsigned int numWhiteSpacesBetweenValues = 0;

											j += 2;
											(*currentGroup)->NumFaces += 1;
										
											// make sure to dont count whitespace before first set of indices
											while( j < file.FileSizeInBytes && file.FileData[j] == ' ') { ++j; continue; }
										
											// move forward as long as character is ' '
											while( j < file.FileSizeInBytes && file.FileData[j] != '\n') 
											{ 
												++j; 
										
												while( j < file.FileSizeInBytes && file.FileData[j] == ' ') { ++j; continue; }
												while( j < file.FileSizeInBytes && 
													  file.FileData[j] != ' ' && 
													  file.FileData[j] != '\n') 
												{ ++j; continue; }
										
												numWhiteSpacesBetweenValues += 1;

												continue;
											}

											// QQQ not really reliable
											(*currentGroup)->NumIndicesPerFace = numWhiteSpacesBetweenValues;
										}
									}
								} // END OF count group data

								// generate all the index buffers
								if((*currentObject)->NumPositions > 0)
									(*currentGroup)->PositionIndices = malloc( sizeof(unsigned int) * (*currentGroup)->NumIndicesPerFace * (*currentGroup)->NumFaces);
								if((*currentObject)->NumUVs > 0)
									(*currentGroup)->UVIndices = malloc( sizeof(unsigned int) * (*currentGroup)->NumIndicesPerFace * (*currentGroup)->NumFaces);
								if((*currentObject)->NumNormals > 0)
									(*currentGroup)->NormalIndices = malloc( sizeof(unsigned int) * (*currentGroup)->NumIndicesPerFace * (*currentGroup)->NumFaces);
							} // END OF *current group == NULL

							// collect data to *current group
							if(strncmp( &file.FileData[i], "usemtl ", 7) == 0)
							{
								i += 7;
							
								// retrieve material name and material name length of object
								retrieveStringFromLine( &(*currentGroup)->MaterialName, &(*currentGroup)->MaterialNameLength, &file.FileData[i], file.FileSizeInBytes); 
							}
							else if( strncmp( &file.FileData[i], "f ", 2) == 0)
							{
								char valueBuffer[64];
								int indexBuffer[9];
								unsigned int numIndex = 0;
								unsigned int startIndex = 0;
								unsigned int endIndex = 0;

								i += 2;
								
								// get to the starting point of the line
								while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

								while( i < file.FileSizeInBytes && file.FileData[i] != '\n' && file.FileData[i] != '\0')
								{
									int value = -1;

									// get to the starting point of the line
									while( i < file.FileSizeInBytes && file.FileData[i] == ' ') { ++i; continue; }

									startIndex = i;
								
									// get to the starting point of the line
									while( i < file.FileSizeInBytes && file.FileData[i] != '/' && file.FileData[i] != '\n' &&  file.FileData[i] != '\0' && file.FileData[i] != ' ' && file.FileData[i] != '\r') { ++i; continue; }

									endIndex = i;

									if(startIndex != endIndex)
									{	
										memcpy( valueBuffer, &file.FileData[startIndex], endIndex - startIndex);
										valueBuffer[endIndex - startIndex] = '\0';
								
										value = atoi(valueBuffer);
									}

									++i;

									indexBuffer[numIndex] = value;

									++numIndex;
								}

								// count the values and assign them properly
								{
									unsigned int j = 0;
									for(j; j < (*currentGroup)->NumIndicesPerFace; ++j)
									{
										if((*currentObject)->NumPositions > 0)
											(*currentGroup)->PositionIndices[currentStorePositionIndex++] = indexBuffer[j * 3 + 0];
										
										if((*currentObject)->NumUVs > 0)
											(*currentGroup)->UVIndices[currentStoreUVIndex++] = indexBuffer[j * 3 + 1];
								
										if((*currentObject)->NumNormals > 0)
											(*currentGroup)->NormalIndices[currentStoreNormalIndex++] = indexBuffer[j * 3 + 2];
									}
								}
							}
							
						}
					}
				}
			}
		}
	}

	return scene;
}

void OBJFile_Unload( OBJFile* objFile)
{
	OBJObject* curObjObject = objFile->Objects;

	free( objFile->MaterialFilePath);

	while( curObjObject != NULL)
	{
		OBJGroup* curObjGroup = curObjObject->Groups;
		OBJObject* objectToFree = curObjObject;

		while( curObjGroup != NULL)
		{
			OBJGroup* groupToFree = curObjGroup;

			free(curObjGroup->MaterialName);
			free(curObjGroup->Name);
			free(curObjGroup->NormalIndices);
			free(curObjGroup->PositionIndices);
			free(curObjGroup->UVIndices);

			curObjGroup = curObjGroup->NextGroup;
			free(groupToFree);
		}

		free(curObjObject->Name);
		free(curObjObject->Normals);
		free(curObjObject->Positions);
		free(curObjObject->UVs);

		curObjObject = curObjObject->NextObject;
		free(objectToFree);
	}
}

Mesh* Mesh_CreateFromOBJGroup( OBJObject* const objObject, OBJGroup* const objGroup)
{
	Mesh* mesh = NULL;

	Vertex* vertices = malloc(sizeof(Vertex) * objObject->NumPositions);
	Vertex* vertex = vertices;
	
	unsigned int numIndices = objGroup->NumFaces * objGroup->NumIndicesPerFace;
	unsigned short* indices = (unsigned short*)malloc(sizeof(unsigned short) * numIndices);

	// note that in OBJ files, indexing starts from 1, so to fix this we substract 1 from the index

	unsigned int i = 0;
	for( i; i < objObject->NumPositions; ++i)
	{

		if(objObject->NumPositions > 0)
			vertex->Position = objObject->Positions[objGroup->PositionIndices[i] - 1];
		if(objObject->NumUVs > 0)
			vertex->UV = objObject->UVs[objGroup->UVIndices[i] - 1];
		if(objObject->NumNormals > 0)
			vertex->Normal = objObject->Normals[objGroup->NormalIndices[i] - 1];
		
		// move further with the vertices
		++vertex;
	}

	// copy indices
	for( i = 0; i < numIndices; ++i)
		indices[i] = objGroup->PositionIndices[i] - 1;

	// create vertex and index buffer
	mesh = Mesh_Create( vertices, objObject->NumPositions, indices, numIndices);
	
	return mesh;
}