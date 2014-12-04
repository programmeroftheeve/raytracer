#include <rayTracerCore/shapes/triangle.h>
#include <util/colors.h>
#include <stdio.h>
#include <rayTracerCore/ray.h>
#include <rayTracerCore/rayhit.h>

bool triangleTestHit(const ray r, const object *obj)
{
    return false;
}

bool triangleHit(const ray r, const object *o, float *time, rayHit *rayH)
{
    rayH->hit = false;
    rayH->mat = EMPTYNESS;
    triangle_t* tri = o->shape;
    // Get Points
    point3f p1= {},p2= {},p3= {};
    vector3f_copy(p1, tri->a);
    vector3f_copy(p2, tri->b);
    vector3f_copy(p3, tri->c);
    vector3f e1 = {}, e2 = {}, s1 = {};
    vector3f_sub_new(e1, p2, p1);
    vector3f_sub_new(e2, p3, p1);
    vector3f_cross_new(s1, r.dir, e2);
    float det = vector3f_dot(s1, e1);
    if(det == 0)
        return false;
    float invD = 1.f/ det;
    vector3f d = {};
    vector3f_sub_new(d, r.origin, p1);
    float b1 = vector3f_dot(d, s1) * invD;
    if(b1 < 0.f || b1 > 1.f)
        return false;
    vector3f s2 = {};
    vector3f_cross_new(s2, d, e1);
    float b2 = vector3f_dot(r.dir, s2) * invD;
    if(b2 < 0.f || (b1+b2) > 1.f)
        return false;

    float t = vector3f_dot(e2, s2)*invD;
    if(t < r.tmin || t > r.tmax)
        return false;

    *time = t;
    rayH->hit = true;
    rayH->mat = o->mat;
    vector3f dirOffset = {};
    vector3f_scaleMul_new(dirOffset, r.dir, t);
    vector3f_add_new(rayH->location, r.origin, dirOffset);
    vector3f_cross_new(rayH->normal, e1, e2);
    vector3f_normalize(rayH->normal);
    rayH->originRay = r;
    rayH->offsetError = .1;
    return true;
}

void trianglePrint(void* t)
{
    printf(KCYN"triangle[");
    printf(KBLU"a:"KGRN);
    vector3f_print(((triangle_t*)t)->a);
    printf(KBLU"b:"KGRN);
    vector3f_print(((triangle_t*)t)->b);
    printf(KBLU"c:"KGRN);
    vector3f_print(((triangle_t*)t)->c);
    printf(KCYN"]"KNRM);
}

