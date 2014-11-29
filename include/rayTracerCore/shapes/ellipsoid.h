#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <stdbool.h>
#include <rayTracerCore/material.h>
#include <rayTracerCore/ray.h>
#include <util/vector.h>
#include <rayTracerCore/shapes/geometry.h>

typedef struct
{
    float a,b,c;
    point3f center;
} ellipsoid_t;

bool ellipsoidTestHit(const ray, const object*);
bool ellipsoidHit(const ray r, const object *o, float *time, rayHit *rayH);
void ellipsoidPrint(void *);
#endif // _SPHERE_H_