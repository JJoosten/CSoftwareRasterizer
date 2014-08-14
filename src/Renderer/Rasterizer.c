#include "Rasterizer.h"
#include <assert.h>

void calculateScreenCoords( Vec4* const IN_OUT_ndc)
{
	IN_OUT_ndc->X = 1.0f + IN_OUT_ndc->X * 0.5f;
	IN_OUT_ndc->Y = 1.0f + IN_OUT_ndc->Y * 0.5f;
}

void RasterizeTriangle( Renderer* const renderer, RasterTriangle* const triangle)
{
	assert( renderer && "RasterizeTriangle renderer is NULL");
	assert( triangle && "RasterizeTriangle triangle is NULL");

	// calculate screen coords and store them in the xy of the triangle position
	calculateScreenCoords( &triangle->V1.Position);
	calculateScreenCoords( &triangle->V2.Position);
	calculateScreenCoords( &triangle->V3.Position);

	// go over triangle edges

	// read depth fragment if depth test enabled

	// calculate current depth fragment if depth test enabled
	
	
}