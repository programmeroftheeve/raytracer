#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <stdbool.h>
#include <rayTracerCore/ray.h>
#include <rayTracerCore/material.h>
#include <util/vector.h>
#include <rayTracerCore/rayhit.h>

typedef enum
{
    SPHERE,
    TRIANGLE
} geoEnum;

typedef struct obj object;

typedef bool(*testHit)(const ray, const object*);
typedef bool(*hitFunction)(const ray, const object* ,float* /*time*/, rayHit *);
typedef void(*printFunction)(void*);

struct obj
{
    geoEnum type;
    material mat;
    void * shape;
    hitFunction hit;
    testHit test;
    printFunction print;
    object* next;
};

void printObjectList(const object* o);
void cleanObjectList(object** list);

object* createSphere(const material mat, const float radius, const point3f center);
object* createTriangle(const material mat, const point3f p1, const point3f p2, const point3f p3);


#endif // _GEOMETRY_H_