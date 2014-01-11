#include "Camera.h"
#include <string.h>
#include <stdlib.h>

Camera* Camera_Create( void)
{
	Camera* camera = malloc( sizeof(Camera));
	memset( camera, 0, sizeof(Camera));

	return camera;
}

void Camera_Destroy( Camera* camera)
{
	free(camera);
}