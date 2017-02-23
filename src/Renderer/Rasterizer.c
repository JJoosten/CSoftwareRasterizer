#include "Rasterizer.h"
#include "../PlatformDefines.h"
#include <assert.h>

void swap(RasterVertex** a, RasterVertex** b)
{
	RasterVertex* temp = *a;
	*a = *b;
	*b = temp;
}

void calculateScreenCoords( Renderer* const renderer, Vec4* const IN_OUT_screenCoordinates)
{
	// NDC -> screen coordinates
	IN_OUT_screenCoordinates->X = (1.0f + IN_OUT_screenCoordinates->X) * 0.5f * renderer->FrameBuffer->Width;
	IN_OUT_screenCoordinates->Y = (1.0f + IN_OUT_screenCoordinates->Y) * 0.5f * renderer->FrameBuffer->Height;
}

void RasterizeTriangle( Renderer* const renderer, RasterTriangle* const triangle)
{
	bool traversingTriangle = true;

	assert( renderer && "RasterizeTriangle renderer is NULL");
	assert( triangle && "RasterizeTriangle triangle is NULL");

	// calculate screen coords and store them in the xy of the triangle position
	calculateScreenCoords( renderer, &triangle->V1.Position);
	calculateScreenCoords( renderer, &triangle->V2.Position);
	calculateScreenCoords( renderer, &triangle->V3.Position);

	// go over triangle edges

	//while(traversingTriangle)
	{
		RasterTriangleEdge v0v1;
		RasterTriangleEdge v0v2;
		RasterTriangleEdge v1v2;

		// sort edges from top left to bottom right to get the edges to traverse
		{
			// positions go from 0,0 top left to 1,1 bottom right
			RasterVertex* topVertex = &triangle->V1;
			RasterVertex* midVertex = &triangle->V2;
			RasterVertex* bottomVertex = &triangle->V3;

			RasterVertex* leftVertex = &triangle->V1;
			RasterVertex* centerVertex = &triangle->V2;
			RasterVertex* rightVertex = &triangle->V3;

			// sort from top to bottom
			if(topVertex->Position.Y > midVertex->Position.Y)
				swap( &topVertex, &midVertex);
			if(midVertex->Position.Y > bottomVertex->Position.Y)
				swap( &midVertex, &bottomVertex);
			if(topVertex->Position.Y > midVertex->Position.Y)
				swap( &topVertex, &midVertex);

			// sort from left to right
			if(leftVertex->Position.X > centerVertex->Position.X)
				swap( &leftVertex, &centerVertex);
			if(centerVertex->Position.X > rightVertex->Position.X)
				swap( &centerVertex, &rightVertex);
			if(leftVertex->Position.X > centerVertex->Position.X)
				swap( &topVertex, &centerVertex);

			v0v1.Start = topVertex;
			v0v1.End = leftVertex != topVertex ? leftVertex : centerVertex;
			Vec2_Sub(&v0v1.Edge, &v0v1.End->Position.XY, &v0v1.Start->Position.XY);

			v0v2.Start = topVertex;
			v0v2.End = topVertex != rightVertex ? rightVertex : centerVertex;
			Vec2_Sub(&v0v2.Edge, &v0v2.End->Position.XY, &v0v2.Start->Position.XY);

			v1v2.Start = v0v1.End;
			v1v2.End = v0v2.End;
			Vec2_Sub(&v1v2.Edge, &v1v2.End->Position.XY, &v1v2.Start->Position.XY);
		}

		// go over v0v1 and v0v2
		{
			const float deltaStartX = v0v1.Edge.X / v0v1.Edge.Y;
			const float deltaEndX = v0v2.Edge.X / v0v2.Edge.Y;

			// calculate start positions and offset position to center of pixel
			float spanStartX = v0v1.Start->Position.X + 0.5f * deltaStartX;
			float spanStartY = v0v1.Start->Position.Y;
			float spanEndX = spanStartX;
			float spanEndY = spanStartY;

			unsigned int* frameBufferPixels = renderer->FrameBuffer->Pixels;
			unsigned int frameBufferWidth = renderer->FrameBuffer->Width;
			unsigned int frameBufferHeight = renderer->FrameBuffer->Height;

			// for test only traverse the shortest edge
			int y = (int)spanStartY;
			int height = (int)(v0v1.Edge.Y > v0v2.Edge.Y ? v0v2.Edge.Y : v0v1.Edge.Y) + y;
			for(y; y < height; ++y)
			{
				int x = (int)spanStartX;
				int width = (int)(spanEndX - spanStartX) + (int)spanStartX;
				for(x; x < width; ++x)
				{
					// QQQ temp solid color to see if walk over triangle span works
					frameBufferPixels[y * frameBufferWidth + x] = 0xFF0000FF;
				}

				// move over the edge
				spanStartX += deltaStartX;
				spanEndX += deltaEndX;
			}
		}


		// read depth fragment if depth test enabled


		// calculate current depth fragment if depth test enabled

	}
}
