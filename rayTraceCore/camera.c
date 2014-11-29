#include <rayTracerCore/camera.h>
#include <util/vector.h>
#include <util/colors.h>

static void setNewUp(float newUp[3], const float oldUp[3], const float dir[3])
{
    float look[3];
    vector3f_normalize_new(look, dir);
    float side[3];
    vector3f_cross_new(side, look, oldUp);
    vector3f_normalize(side);
    vector3f_cross_new(newUp, side, look);
}


void printCamera(const camera cam)
{
    printf(KRED "Camera[" KBLU "origin:" KGRN);
    vector3f_print(cam.origin);
    printf(KBLU " direction:" KGRN);
    vector3f_print(cam.direction);
    printf(KBLU " up:" KGRN);
    vector3f_print(cam.up);
    printf(KRED "]\n" KNRM);
}

void setCamera(camera* cam, const float eye[3], const float center[3], const float up[3])
{
    vector3f_sub_new(cam->direction, center, eye);
    vector3f_normalize(cam->direction);
    setNewUp(cam->up, up, cam->direction);
    vector3f_copy(cam->origin, eye);
}

void getCameraRightVector(float right[3], const camera cam)
{
    vector3f_cross_new(right, cam.direction, cam.up);
    vector3f_normalize(right);
}