#ifndef _CAMERA_H_
#define _CAMERA_H_

typedef struct camera_t
{
    float origin[3];
    float direction[3];
    float up[3];
} camera;

void setCamera(camera* cam, const float eye[3], const float center[3], const float up[3]);

void getCameraRightVector(float right[3], const camera cam);
void printCamera(const camera cam);


#endif // _CAMERA_H_