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

	// parse file

	return materialSet;
}