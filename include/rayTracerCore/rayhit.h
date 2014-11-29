#ifndef _RAYHIT_H_
#define _RAYHIT_H_

#include <rayTracerCore/ray.h>
#include <util/vector.h>
#include <rayTracerCore/material.h>

struct obj;

typedef struct
{
    unsigned int depth;
    bool hit;
    material mat;
    point3f location;
    vector3f normal;
    ray originRay;
    float offsetError;
    struct obj* objects;
} rayHit;

void printRayHit(const rayHit);
void getFinalColor(vector3f color, const rayHit* rayHits, const int count);



#endif // _RAYHIT_H_