#ifndef _USEFULFUNCTIONS_H_
#define _USEFULFUNCTIONS_H_
#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#ifdef NDEBUG
#   define DEBUG
#   define ASSERT(x) assert(x)
#   define DPRINT(x, ... ) printf(KGRN"DEBUG: " KNRM x, ##__VA_ARGS__ );
#   define DEBUGOUT(x) do{ printf(KGRN"Debug: "); x; printf("\n");} while(0)
#else
#   define ASSERT(x)
#   define DPRINT(x)
#   define DEBUGOUT(x)
#endif

static void inline printDepth(int x)
{
    for( int print_depth = 0; print_depth < x-1; print_depth++)
    {
        printf("--");
    }
    printf("->");
}

static inline void swap(float * a, float* b)
{
    float tmp = *a;
    *a=*b;
    *b=tmp;
}

static inline float mapToRangef(float v, float origMin, float origMax, float newMin, float newMax)
{
    return newMin + ((v - origMin)*(newMax - newMin))/(origMax - origMin);
}

static inline double mapToRanged(double v, double origMin, double origMax, double newMin, double newMax)
{
    return newMin + ((v - origMin)*(newMax - newMin))/(origMax - origMin);
}

static inline void indexToXY(const int index, int* x, int *y, const int width)
{
    *x = index % width;
    *y = index / width;
}

static inline void xyToIndex(const int x, const int y, int* index, const int width)
{
    *index = y * width + x;
}

void printArray(const char* comment, const void* array, const int width, const int height, void(*print)(void* element), size_t size);

static inline bool quadratic(const float a, const float b, const float c, float* t0, float* t1)
{
    float d = b*b-4*a*c;
    if(d <= 0.f) return false;
    float rootd = sqrtf(d);
    float q =( b < 0 ? -.5f*(b - rootd) : -.5f*(b + rootd));
    *t0 = q / a;
    *t1 = c / q;
    if(*t0 > *t1) swap(t0, t1);
    return true;
}

static inline float getPixelWidth(float screenWidth, float res_x)
{
    return screenWidth / res_x;
}

static inline float getPixelHeight(float screenHeight, float res_y)
{
    return screenHeight / res_y;
}

#endif // _USEFULFUNCTIONS_H_