#include "Camera.h"
#include <string.h>
#include <stdlib.h>


Camera* Camera_Create( const Mat4* const projectionMatrix)
{
	Vec3 worldUp, target;

	Camera* camera = malloc( sizeof(Camera));
	memset( camera, 0, sizeof(Camera));

	Vec3_LoadZero( &target);
	Vec3_LoadUp( &worldUp);
	Vec3_LoadOne( &camera->Position);

	Mat4_LoadLookAt( &camera->ViewMatrix, &target, &camera->Position, &worldUp);
	Mat4_Copy( &camera->ProjectionMatrix, projectionMatrix);

	return camera;
}

void Camera_Destroy( Camera* const camera)
{
	free(camera);
}