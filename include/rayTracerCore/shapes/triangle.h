#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <util/vector.h>
#include <rayTracerCore/ray.h>
#include <rayTracerCore/material.h>
#include <rayTracerCore/shapes/geometry.h>

typedef struct
{
    point3f a,b,c;
} triangle_t;

bool triangleTestHit(const ray r, const object *obj);
bool triangleHit(const ray r, const object *o, float *time, rayHit *rayH);
void trianglePrint(void*);

#endif // _TRIANGLE_H_