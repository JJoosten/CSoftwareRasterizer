#include "OBJLoader.h"
#include "FileLoading.h"
#include "../VertexData/Mesh.h" // includes, vertex.h

#include <stdlib.h>
#include <string.h>

Mesh* Load_OBJMesh( const char* const objFile)
{
	Mesh* mesh = NULL;

	File file;
	// checks internally for loading errors, if so it asserts for now
	Load_FileIntoRAM( &file, objFile);

	// parse fileData in two passes

	// first pass counts data 
	{
		unsigned int i = 0;
		unsigned int numVertices = 0;
		unsigned int numIndices = 0;
		
		// parse data counts
		for( i; i < file.FileSizeInBytes; ++i)
		{

		}
		
		// second pass retrieves data
		{
			unsigned int i = 0;
			Vertex* vertices = malloc( sizeof(Vertex) * numVertices);
			unsigned short* indices = NULL;
			if( numIndices > 0)
			{
				indices = malloc( sizeof(unsigned short) * numIndices);
			}

			// retrieve data from file
			for( i; i < file.FileSizeInBytes; ++i)
			{

			}
			
			// create mesh
			mesh = Mesh_Create( vertices, numVertices, indices, numIndices);
		}
	}

	return mesh;
}