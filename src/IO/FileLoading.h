#ifndef CSR_FILE_LOADING_H
#define CSR_FILE_LOADING_H

typedef struct
{
	char* FileData;
	unsigned int FileSizeInBytes;
} File;

void Load_FileIntoRAM( File* const fileOUT, const char* const filePath);

#endif