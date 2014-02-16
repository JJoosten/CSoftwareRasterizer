#ifndef CSR_CAMERA_H
#define CSR_CAMERA_H

#include "../Math/Mat4.h"

typedef struct
{
	Mat4 ProjectionMatrix;
	Mat4 ViewMatrix;
	Vec3 Position;
	float YawInDegrees;
	float PitchInDegrees;
	float RollInDegrees;
} Camera;

Camera* Camera_Create( const Mat4* const projectionMatrix);
void Camera_Destroy( Camera* const camera);


#endif // CSR_CAMERA_H