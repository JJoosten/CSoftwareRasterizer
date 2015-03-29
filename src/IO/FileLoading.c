#include "FileLoading.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void Load_FileIntoRAM( File* const fileOUT, const char* const filePath)
{
	FILE* file = NULL;

	assert(filePath && "filePath is NULL");

	file = fopen( filePath, "rb");

	assert(file && "file is NULL");
	
	// find size
	fseek( file, 0, SEEK_END);   //QQQ non-portable, SEEK_END is not required to be supported!
	fileOUT->FileSizeInBytes = ftell(file);
	fseek( file, 0, SEEK_SET);

	// copy data file to RAM
	fileOUT->FileData = malloc( fileOUT->FileSizeInBytes);
	fread( fileOUT->FileData, sizeof(char), fileOUT->FileSizeInBytes, file);

	fclose(file);
}