#include "Renderer.h"
#include "Rasterizer.h" // includes Triangle.h
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// global default settings
VertexShaderUniforms g_defaultUniforms;


Renderer* Renderer_Create( const unsigned int width, const unsigned int height)
{
	Renderer* renderer = malloc( sizeof(Renderer));
	
	assert( renderer && "Renderer_Create renderer == NULL");

	memset( renderer, 0, sizeof(Renderer));

	// set the default uniform matrix to a standard projection matrix
	Mat4_LoadPerspective( &g_defaultUniforms.WorldToViewToProjectionMatrix, 70.0f, (float)width / (float)height, 0.1f, 100.0f);

	renderer->FrameBuffer = FrameBuffer_Create( width, height);
	renderer->DepthBuffer = Texture_Create( width, height);
	renderer->VertexShader = DefaultVertexShader;
	renderer->VertexShaderUniforms = &g_defaultUniforms;

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

void Renderer_DrawMesh( Renderer* const renderer, const Mesh* const mesh)
{
	unsigned int i = 0;
	
	assert( renderer && "Renderer_DrawMesh renderer is NULL");
	assert( mesh && "Renderer_DrawMesh mesh is NULL");
	assert( mesh->VertexBuffer && "Renderer_DrawMesh mesh vertexbuffer is NULL");
	
	for( i; i < mesh->NumTriangles; ++i)
	{
		const unsigned int triangleVerticesOffset = i * 3;

		// triangle assembly
		RasterTriangle triangle;
		if( mesh->IndexBuffer != NULL)
		{
			// if index buffer -> triangle assembly
			// we could make this faster by creating a vertex cache
			const unsigned int index1 = mesh->IndexBuffer->Indices[triangleVerticesOffset + 0];
			const unsigned int index2 = mesh->IndexBuffer->Indices[triangleVerticesOffset + 1];
			const unsigned int index3 = mesh->IndexBuffer->Indices[triangleVerticesOffset + 2];
			RasterVertex_LoadVertex( &triangle.V1, &mesh->VertexBuffer->Vertices[index1]);
			RasterVertex_LoadVertex( &triangle.V2, &mesh->VertexBuffer->Vertices[index2]);
			RasterVertex_LoadVertex( &triangle.V3, &mesh->VertexBuffer->Vertices[index3]);
		}
		else
		{
			RasterVertex_LoadVertex( &triangle.V1, &mesh->VertexBuffer->Vertices[triangleVerticesOffset + 0]);
			RasterVertex_LoadVertex( &triangle.V2, &mesh->VertexBuffer->Vertices[triangleVerticesOffset + 1]);
			RasterVertex_LoadVertex( &triangle.V3, &mesh->VertexBuffer->Vertices[triangleVerticesOffset + 2]);
		}

		// transform triangle vertices (vertex shader stage)
		renderer->VertexShader( &triangle, renderer->VertexShaderUniforms);

		// backface culling
		{
			float zCross = 0;
			Vec4 triangleEdge1;
			Vec4 triangleEdge2;
			// calculate edge1
			Vec4_Sub( &triangleEdge1, &triangle.V2.Position, &triangle.V1.Position);
			// calculate edge2
			Vec4_Sub( &triangleEdge2, &triangle.V2.Position, &triangle.V3.Position);

			zCross = triangleEdge1.X * triangleEdge2.Y - triangleEdge2.X * triangleEdge1.Y;

			// we use OpenGL axis so -1 is looking away from camera, +1 is looking towards camera
			if( zCross < 0)
				continue;
		}

		// clipping Sutherland-hodgman 
		{
			// TODO: dO clipping in clip space (cube from -1 to 1 on XYZ)

		}

		// draw triangle(s) potentially a trianglefan due to clipping (fragment shader stage)
		RasterizeTriangle( renderer, &triangle);
	}
}


void Renderer_SetVertexShader( Renderer* const renderer, VertexShaderFunction const vertexShaderFunc, VertexShaderUniforms* const vertexShaderUniforms)
{
	assert( renderer && "Renderer_SetVertexShader renderer is NULL");
	assert( vertexShaderFunc && "Renderer_SetVertexShader vertexShaderFunc is NULL");
	assert( vertexShaderUniforms && "Renderer_SetVertexShader vertexShaderUniforms is NULL");

	renderer->VertexShader = vertexShaderFunc;
	renderer->VertexShaderUniforms = vertexShaderUniforms;
}

void Renderer_SetVertexShaderUniforms( Renderer* const renderer, VertexShaderUniforms* const vertexShaderUniforms)
{
	assert( renderer && "Renderer_SetVertexShaderUniforms renderer is NULL");
	assert( vertexShaderUniforms && "Renderer_SetVertexShaderUniforms vertexShaderUniforms is NULL");
	renderer->VertexShaderUniforms = vertexShaderUniforms;
}