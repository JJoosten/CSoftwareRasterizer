#include "Renderer.h"
#include "../VertexData/Triangle.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Renderer* Renderer_Create( const unsigned int width, const unsigned int height)
{
	Renderer* renderer = malloc( sizeof(Renderer));
	
	assert( renderer && "Renderer_Create renderer == NULL");

	memset( renderer, 0, sizeof(Renderer));

	renderer->FrameBuffer = FrameBuffer_Create( width, height);
	renderer->DepthBuffer = Texture_Create( width, height);

	return renderer;
}

void Renderer_Destroy( Renderer* const renderer)
{
	assert( renderer && "Renderer_Destroy renderer == NULL");
	assert( renderer->FrameBuffer && "Renderer_Destroy renderer->FrameBuffer == NULL");
	assert( renderer->DepthBuffer && "Renderer_Destroy renderer->DepthBuffer == NULL");

	FrameBuffer_Destroy(renderer->FrameBuffer);
	Texture_Destroy(renderer->DepthBuffer);
	free(renderer);
}

void Renderer_DrawMesh( const Mesh* const mesh)
{
	unsigned int i = 0;

	assert( mesh && "mesh is NULL");
	assert( mesh->VertexBuffer && "mesh vertexbuffer is NULL");

	for( i; i < mesh->NumTriangles; ++i)
	{
		const unsigned int triangleVerticesOffset = i * 3;

		Triangle triangle;
		if( mesh->IndexBuffer != NULL)
		{
			// if index buffer -> triangle assembly
			// we could make this faster by creating a vertex cache
			const unsigned int index1 = mesh->IndexBuffer->Indices[triangleVerticesOffset + 0];
			const unsigned int index2 = mesh->IndexBuffer->Indices[triangleVerticesOffset + 1];
			const unsigned int index3 = mesh->IndexBuffer->Indices[triangleVerticesOffset + 2];
			triangle.V1 = mesh->VertexBuffer->Vertices[index1];
			triangle.V2 = mesh->VertexBuffer->Vertices[index2];
			triangle.V3 = mesh->VertexBuffer->Vertices[index3];
		}
		else
		{
			triangle.V1 = mesh->VertexBuffer->Vertices[triangleVerticesOffset + 0];
			triangle.V2 = mesh->VertexBuffer->Vertices[triangleVerticesOffset + 1];
			triangle.V3 = mesh->VertexBuffer->Vertices[triangleVerticesOffset + 2];
		}

		// transform triangle vertices

		// backface culling
		
		// clipping Sutherland-hodgman

		// draw triangle(s) potentially a trianglefan due to clipping
	}
}