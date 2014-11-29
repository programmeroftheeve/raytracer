#include <rayTracerCore/shapes/geometry.h>
#include <util/colors.h>
#include <rayTracerCore/shapes/ellipsoid.h>
#include <stdlib.h>
#include <rayTracerCore/shapes/triangle.h>

void printObject(const object o)
{
    printf(KRED"object[");
    printf(KBLU"mat:");
    printMaterial(o.mat);
    printf(KBLU" shape:");
    o.print(o.shape);
    printf(KRED"]"KNRM);
}

void printObjectList(const object* o)
{
    object* tmp = (object*)o;
    if(tmp != NULL)
    {
        for (; tmp->next != NULL; tmp = tmp->next)
        {
            printObject(*tmp);
            printf(" --> ");
        }
        printObject(*(tmp));
        printf("\n");
    }
}

object* createSphere(const material mat, const float radius, const point3f center)
{
    object* ret = malloc(sizeof(object));
    ret->mat = mat;
    ret->shape = malloc(sizeof(ellipsoid_t));
    ellipsoid_t * sph = (ellipsoid_t *)ret->shape;
    vector3f_copy(sph->center, center);
    sph->a = radius;
    sph->b = radius;
    sph->c = radius;
    ret->print = ellipsoidPrint;
    ret->hit = ellipsoidHit;
    ret->test = ellipsoidTestHit;
    ret->type = SPHERE;
    ret->next = NULL;
    return ret;
}


object*createTriangle(const material mat, const point3f p1, const point3f p2, const point3f p3)
{
    object* ret = malloc(sizeof(object));
    ret->mat = mat;
    ret->shape = malloc(sizeof(triangle_t));
    ret->type = TRIANGLE;
    triangle_t* tri = (triangle_t*)ret->shape;
    vector3f_copy(tri->a, p1);
    vector3f_copy(tri->b, p2);
    vector3f_copy(tri->c, p3);
    ret->print = trianglePrint;
    ret->hit = triangleHit;
    ret->test = triangleTestHit;
    ret->next = NULL;
    return ret;
}

void cleanObjectList(object** list)
{
    object* root = *list;
    *list = NULL;
    while(root != NULL)
    {
        object* tmp = root;
        root = root->next;
        free(tmp->shape);
        free(tmp);
    }
}