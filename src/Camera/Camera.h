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

void Camera_SetProjectionMatrix( Camera* const camera, const Mat4* const projectionMatrix);

//void Camera_SetPosition( const Vec3* const pos);

//void Camera_RotateGlobalX( const float rotationInDegrees);
//void Camera_RotateGlobalY( const float rotationInDegrees);
//void Camera_RotateGlobalZ( const float rotationInDegrees);

//void Camera_MoveLocalX( const float displacement);
//void Camera_MoveLocalY( const float displacement);
//void Camera_MoveLocalZ( const float displacement);


#endif // CSR_CAMERA_H