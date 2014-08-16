#include "Rasterizer.h"
#include <assert.h>

void calculateScreenCoords( Renderer* const renderer, Vec4* const IN_OUT_screenCoordinates)
{
	// clip coordinates -> NDC -> screen coordinates
	IN_OUT_screenCoordinates->X = (1.0f + IN_OUT_screenCoordinates->X) * 0.5f * renderer->FrameBuffer->Width;
	IN_OUT_screenCoordinates->Y = (1.0f + IN_OUT_screenCoordinates->Y) * 0.5f * renderer->FrameBuffer->Height;
}

void RasterizeTriangle( Renderer* const renderer, RasterTriangle* const triangle)
{
	assert( renderer && "RasterizeTriangle renderer is NULL");
	assert( triangle && "RasterizeTriangle triangle is NULL");

	// calculate screen coords and store them in the xy of the triangle position
	calculateScreenCoords( renderer,  &triangle->V1.Position);
	calculateScreenCoords( renderer, &triangle->V2.Position);
	calculateScreenCoords( renderer, &triangle->V3.Position);

	// go over triangle edges

	// read depth fragment if depth test enabled

	// calculate current depth fragment if depth test enabled
	
	
}