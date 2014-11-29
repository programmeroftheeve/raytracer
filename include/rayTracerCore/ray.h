#ifndef _RAY_H_
#define _RAY_H_

#include <rayTracerCore/camera.h>
#include <util/vector.h>

typedef enum
{
    GLOBAL,
    REGULAR,
    RANDOM,
    JITTER
} SAMPLER;

typedef struct
{
    float viewPlaneDistance;
    float height, width;
    unsigned int res_x, res_y;
    camera cam;
} perspective;

typedef struct
{
    float origin[3];
    float dir[3];
    float tmin,tmax;
} ray;

typedef struct
{
    unsigned int numOfSamplesX, numOfSamplesY;
    ray* rays;
} sampler;

void printRay(const ray r);
void printSampler(const sampler s);

void getRay(ray *r, const perspective p, unsigned int pixel_x, unsigned int pixel_y);

void reflectRay(ray * reflect, const point3f reflectPoint, const vector3f normal, const ray incomingRay);

void getSampler(sampler *s, unsigned numOfSamplesX, unsigned numOfSamplesY, const perspective p, unsigned int pixel_x, unsigned int pixel_y, SAMPLER sampleMethod);
void cleanSampler(sampler* s);

SAMPLER setSamplerMethod(SAMPLER s);
SAMPLER getSamplerMethod(void);

#endif // _RAY_H_