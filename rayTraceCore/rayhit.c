#include <rayTracerCore/rayhit.h>
#include <util/colors.h>
#include <rayTracerCore/material.h>

void getFinalColor(vector3f color, const rayHit* rayHits, const int count)
{
    vector3f_set(color, 0, 0, 0);
    for(int i = 0; i < count; i++)
    {
        vector3f_add(color, rayHits->mat.color);
    }
    vector3f_scaleMul(color, 1.0f/((float)count));
}



void printRayHit(const rayHit rh)
{
    printf(KRED"RayHit["KGRN"depth:%u ", rh.depth);
    printf(rh.hit ? "hit:TRUE " : "hit:FALSE ");
    printf("mat:");
    printMaterial(rh.mat);
    printf(KGRN" location:");
    vector3f_print(rh.location);
    printf(KGRN" normal:");
    vector3f_print(rh.normal);
    printf(KGRN" originRay:");
    printRay(rh.originRay);
    printf(KGRN" offsetError:%4.4f"KRED"]"KNRM, rh.offsetError);
}