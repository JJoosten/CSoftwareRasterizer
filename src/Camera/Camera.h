#ifndef CSR_CAMERA_H
#define CSR_CAMERA_H

typedef struct sCamera
{
	
	float YawInDegrees;
	float PitchInDegrees;
	float RollInDegrees;
} Camera;

Camera CameraCreate( void);
void CameraDestroy( Camera* camera);


#endif // CSR_CAMERA_H