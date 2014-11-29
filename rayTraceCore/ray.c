#include <rayTracerCore/ray.h>
#include <string.h>
#include <stdlib.h>
#include <util/vector.h>
#include <util/usefulfunctions.h>
#include <assert.h>
#include <util/colors.h>

static SAMPLER raySampler = REGULAR;

static void printArrayRay(void* r)
{
    printRay(*(ray*)r);
}

static void copyRay(ray* dest, const ray* src)
{
    memcpy(dest, src, sizeof(ray));
}

void printRay(const ray r)
{
    printf(KRED "ray[" KBLU "origin:" KGRN);
    vector3f_print(r.origin);
    printf(KBLU" direction:"KGRN);
    vector3f_print(r.dir);
    printf(KRED"]"KNRM);
}

void printSampler(const sampler s)
{
    printArray(NULL, s.rays, s.numOfSamplesX, s.numOfSamplesY, printArrayRay, sizeof(ray));
}



static inline float getPixelWidth(float screenWidth, float res_x)
{
    return screenWidth / res_x;
}

static inline float getPixelHeight(float screenHeight, float res_y)
{
    return screenHeight / res_y;
}


/**
* Finds a pixels location is 3d Space based on
* the perspective and pixel coordinate.
*
* Location of pixel is in bottom left hand corner.
* Allows for pixels to be offset into 3d space based on right and up vectors
*/
static void getPixelDirection(float loc[3], const perspective p, const unsigned int pixel[2])
{
    float right[3], up[3];

    //get location
    vector3f_copy(loc, p.cam.direction);
    vector3f_scaleMul(loc, p.viewPlaneDistance);
    //get right and up vectors
    vector3f_copy(up, p.cam.up);
    getCameraRightVector(right, p.cam);

    // Map pixel to view plane
    float pixelMap[2];
    // X mapping
    pixelMap[0] = mapToRangef(pixel[0], 0, p.res_x, -p.width/2.0f, p.width/2.0f);
    // Y mapping
    pixelMap[1] = mapToRangef(pixel[1], 0, p.res_y, -p.height/2.0f, p.height/2.0f);


    float wOffset[3], hOffset[3];
    // Use X to get width offset from center of view plane
    vector3f_scaleMul_new(wOffset, right, pixelMap[0]);
    // Use Y to get height offset from center of view plane
    vector3f_scaleMul_new(hOffset, up, pixelMap[1]);
    // Apply offsets
    vector3f_add(loc, wOffset);
    vector3f_add(loc, hOffset);
}

static void getRayRegular(ray *r, const perspective p, unsigned int pixel[], unsigned int location, unsigned int numOfSamplesX, unsigned int numOfSamplesY)
{
    ASSERT((0 <= location && location <= (numOfSamplesX * numOfSamplesY) ));
    //Get Ray origin from camera
    vector3f_copy(r->origin, p.cam.origin);
    float dir[3], up[3], right[3];
    // Get pixel location in 3D space
    getPixelDirection(dir, p, pixel);
    vector3f_copy(up, p.cam.up);
    getCameraRightVector(right, p.cam);

    //Find offset
    int sampleLocation[2];
    float sampleOffset[2];
    sampleOffset[0] = (getPixelWidth(p.width, p.res_x) / numOfSamplesX);
    sampleOffset[1] = (getPixelHeight(p.height, p.res_y) / numOfSamplesY);
    indexToXY(location, &sampleLocation[0], &sampleLocation[1], numOfSamplesX);
    // Hort offset
    vector3f_scaleMul(right, sampleLocation[0]*sampleOffset[0] + sampleOffset[0] / 2);
    // Vert offset
    vector3f_scaleMul(up, sampleLocation[1]*sampleOffset[0] + sampleOffset[1] / 2);

    vector3f_add_new(r->dir, dir, right);
    vector3f_add(r->dir, up);


}

static void getRayRandom(ray * r, const perspective p, unsigned int pixel[2])
{
    ///TODO: Noise Ray Generator
}

static void getRayJitter(ray *r, const perspective p, unsigned int pixel[], unsigned int location, unsigned int numOfSamplesX, unsigned int numOfSamplesY)
{
    ///TODO: Jitter Ray Generator
}


void getRay(ray *r, const perspective p, unsigned int pixel_x, unsigned int pixel_y)
{
    sampler s;
    getSampler(&s, 1, 1, p, pixel_x, pixel_y, (JITTER));
    copyRay(r, s.rays);
    cleanSampler(&s);
}

void reflectRay(ray * reflect, const point3f reflectPoint, const vector3f normal, const ray incomingRay)
{
    vector3f_copy(reflect->origin, reflectPoint);
    vector3f_reflect_new(reflect->dir, incomingRay.dir, normal);
    reflect->tmin = 0;
    reflect->tmax = INFINITY;
}

void getSampler(sampler *s, unsigned numOfSamplesX, unsigned numOfSamplesY, const perspective p, unsigned int pixel_x, unsigned int pixel_y, SAMPLER sampleMethod)
{
    unsigned int totalSamples = numOfSamplesX * numOfSamplesY;
    unsigned int pixel[2] = { pixel_x, pixel_y};
    s->numOfSamplesX = numOfSamplesX;
    s->numOfSamplesY = numOfSamplesY;
    s->rays = malloc(totalSamples * sizeof(ray));
    if(sampleMethod == GLOBAL) sampleMethod = raySampler;
    for(unsigned int i = 0; i < totalSamples; i++)
    {
        switch (sampleMethod)
        {
            case REGULAR:
                getRayRegular(s->rays + i, p, pixel, i, numOfSamplesX, numOfSamplesY);
                break;
            case RANDOM:
                getRayRandom(s->rays + i, p, pixel);
                break;
            case JITTER:
                getRayJitter(s->rays + i, p, pixel, i, numOfSamplesX, numOfSamplesY);
                break;
            default:
                break;
        }
        (s->rays + i)->tmin = 0;
        (s->rays + i)->tmax = INFINITY;
    }
}

void cleanSampler(sampler* s)
{
    s->numOfSamplesX = s->numOfSamplesY = 0;
    free(s->rays);
    s->rays = NULL;
}

SAMPLER setSamplerMethod(SAMPLER s)
{
    if(s == GLOBAL) s = raySampler;
    SAMPLER old = raySampler;
    raySampler = s;
    return old;
}

SAMPLER getSamplerMethod(void)
{
    return raySampler;
}

