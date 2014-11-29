#include <rayTracerCore/shapes/ellipsoid.h>
#include <util/colors.h>
#include <rayTracerCore/ray.h>
#include <util/usefulfunctions.h>
#include <rayTracerCore/rayhit.h>
#include <time.h>

bool ellipsoidTestHit(const ray r, const object *obj)
{
    ellipsoid_t e = *((ellipsoid_t*)(obj->shape));
    float invasq, invbsq, invcsq;
    invasq = 1.0f/(e.a*e.a);
    invbsq = 1.0f/(e.b*e.b);
    invcsq = 1.0f/(e.c*e.c);
    vector3f origin = {};
    vector3f_sub_new(origin, r.origin, e.center);
    float A = r.dir[0]*r.dir[0]* invasq + r.dir[1]*r.dir[1]* invbsq + r.dir[2]*r.dir[2]* invcsq;
    float B = 2*(r.dir[0]*origin[0]* invasq + r.dir[1]*origin[1]* invbsq + r.dir[2]*origin[2]* invcsq);
    float C = (origin[0]*origin[0]* invasq + origin[1]*origin[1]* invbsq + origin[2]*origin[2]* invcsq) - 1;

    float t0,t1;
    if(!quadratic(A, B, C, &t0, &t1))
        return false;

    if (t0 > r.tmax || t1 < r.tmin)
        return false;
    float thit = t0;
    if (t0 < r.tmin) {
        thit = t1;
        if (thit > r.tmax) return false;
    }
    return true;
}



bool ellipsoidHit(const ray r, const object *obj, float *time, rayHit *rayH)
{
    rayH->hit = false;
    rayH->mat = EMPTYNESS;
    ellipsoid_t e = *((ellipsoid_t*)(obj->shape));
    float invasq, invbsq, invcsq;
    invasq = 1.0f/(e.a*e.a);
    invbsq = 1.0f/(e.b*e.b);
    invcsq = 1.0f/(e.c*e.c);
    vector3f origin = {};
    vector3f_sub_new(origin, r.origin, e.center);
    float A = r.dir[0]*r.dir[0]* invasq + r.dir[1]*r.dir[1]* invbsq + r.dir[2]*r.dir[2]* invcsq;
    float B = 2*(r.dir[0]*origin[0]* invasq + r.dir[1]*origin[1]* invbsq + r.dir[2]*origin[2]* invcsq);
    float C = (origin[0]*origin[0]* invasq + origin[1]*origin[1]* invbsq + origin[2]*origin[2]* invcsq) - 1;

    float t0,t1;
    if(!quadratic(A, B, C, &t0, &t1))
        return false;

    if (t0 > r.tmax || t1 < r.tmin)
        return false;
    float thit = t0;
    if (t0 < r.tmin) {
        thit = t1;
        if (thit > r.tmax) return false;
    }

    *time = thit;
    rayH->hit = true;
    rayH->mat = obj->mat;
    vector3f dirOffset = {};
    vector3f_scaleMul_new(dirOffset, r.dir, thit);
    vector3f_add_new(rayH->location, r.origin, dirOffset);
    float normalX = 2 * (rayH->location[0] - e.center[0])*invasq;
    float normalY = 2 * (rayH->location[1] - e.center[1])*invbsq;
    float normalZ = 2 * (rayH->location[2] - e.center[2])*invcsq;
    vector3f_set(rayH->normal, normalX, normalY, normalZ);
    vector3f_normalize(rayH->normal);
    rayH->originRay = r;
    rayH->offsetError = .0001;
    return true;
}

void ellipsoidPrint(void *s)
{
    printf(KCYN"sphere[");
    printf(KBLU"a:"KGRN"%+4.4f ", ((ellipsoid_t *)s)->a);
    printf(KBLU"b:"KGRN"%+4.4f ", ((ellipsoid_t *)s)->b);
    printf(KBLU"c:"KGRN"%+4.4f ", ((ellipsoid_t *)s)->c);
    printf(KBLU"center:"KGRN);
    vector3f_print(((ellipsoid_t *)s)->center);
    printf(KCYN"]"KNRM);
}

