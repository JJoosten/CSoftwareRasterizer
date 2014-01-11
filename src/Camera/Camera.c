#include "Camera.h"
#include <string.h>

Camera CameraCreate( void)
{
	Camera camera;
	memset( &camera, 0, sizeof(Camera));

	return camera;
}

void CameraDestroy( Camera* camera)
{

}