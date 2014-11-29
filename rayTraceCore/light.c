#include <rayTracerCore/light.h>
#include <rayTracerCore/ray.h>
#include <rayTracerCore/rayhit.h>
#include <rayTracerCore/shapes/geometry.h>

void getRayToLight(const point3f start, const light l, ray* r)
{
    switch(l.type)
    {
        case POINT:
        {
            vector3f_copy(r->origin, start);
            vector3f_sub_new(r->dir, l.l.point.location, start);
            vector3f_normalize(r->dir);
            r->tmax = INFINITY;
            r->tmin = 0.0f;
            break;
        }
        default: break;
    }
}

bool inShadow(const rayHit rh, const light l)
{
    ray lightRay;
    point3f start = {};
    vector3f_scaleMul_new(start, rh.normal, rh.offsetError);
    vector3f_add(start, rh.location);
    getRayToLight(start, l, &lightRay);
    bool hit = false;
    for(object* obj = rh.objects; obj != NULL; obj = obj->next)
    {
        hit = obj->test(lightRay, obj);
        if(hit) break;
    }

    return hit;
}



float getDiffuseFactor(const rayHit rh, const light l)
{
    float diffuse = 0.0f;
    switch(l.type)
    {
        case POINT:
        {
            ray lightRay;
            vector3f normal = {};
            vector3f_normalize_new(normal, rh.normal);
            getRayToLight(rh.location, l, &lightRay);
            #define MAX(x, y) (x > y ? x : y)
            diffuse = vector3f_dot(lightRay.dir, normal);
            diffuse = MAX(0, diffuse);
            #undef MAX
            break;
        }
        default: break;
    };
    return diffuse;
}

float getSpecularFactor(const rayHit rh, const light l)
{
    float specular = 0.0f;
    return specular;
}

