#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <rayTracerCore/rayhit.h>
#include <rayTracerCore/ray.h>

typedef enum
{
    POINT
} LIGHT_TYPE;

typedef struct
{
    float color[3];
    point3f location;
} pointLight;

typedef struct
{
    LIGHT_TYPE type;
    float ambinentFactor;
    union
    {
        pointLight point;
    };
} light;


void getRayToLight(const point3f start, const light l, ray* r);
float getDiffuseFactor(const rayHit rh, const light l);
float getSpecularFactor(const rayHit rh, const light l);
bool inShadow(const rayHit rh, const light l);

#endif // _LIGHT_H_