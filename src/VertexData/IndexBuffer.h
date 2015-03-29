#ifndef CSR_INDEX_BUFFER_H
#define CSR_INDEX_BUFFER_H

typedef struct
{
	unsigned short* Indices;
	unsigned int NumIndices;
} IndexBuffer;

IndexBuffer* IndexBuffer_Create( unsigned short* const indicesTransferOwnership, const unsigned int numIndices);
void IndexBuffer_Destroy( IndexBuffer* const indexBuffer);

#endif //CSR_INDEX_BUFFER_H