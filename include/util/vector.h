/*************************************************************************************
**************************************************************************************
*** The MIT License (MIT)                                                          ***
***                                                                                ***
*** Copyright (c) 2014 Tim Bradt                                                   ***
***`                                                                               ***
*** Permission is hereby granted, free of charge, to any person obtaining a copy   ***
*** of this software and associated documentation files (the "Software"), to deal  ***
*** in the Software without restriction, including without limitation the rights   ***
*** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      ***
*** copies of the Software, and to permit persons to whom the Software is          ***
*** furnished to do so, subject to the following conditions:                       ***
***                                                                                ***
*** The above copyright notice and this permission notice shall be included in all ***
*** copies or substantial portions of the Software.                                ***
***                                                                                ***
*** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     ***
*** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       ***
*** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    ***
*** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         ***
*** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  ***
*** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  ***
*** SOFTWARE.                                                                      ***
**************************************************************************************
*************************************************************************************/
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


static inline void vectorN_copy( void* dest, const void* old, int count, size_t size)
{
    memcpy(dest, old, count*size);
}

// Integer Vector
typedef int vector3i[3];
typedef int vector4i[4];
typedef vector3i point3i;

static inline void vector3i_set(int v[3], int a, int b, int c)
{
    v[0] = a; v[1] = b; v[2] = c;
}

static inline void vector4i_set(int v[3], int a, int b, int c, int w)
{
    v[0] = a; v[1] = b; v[2] = c; v[3] = w;
}

static inline void vector3i_copy(int dest[3], const int src[3])
{
    vectorN_copy(dest, src, 3, sizeof(int));
}

static inline void vector4i_copy(int dest[4], const int src[4])
{
    vectorN_copy(dest, src, 4, sizeof(int));
}

static inline int vectorNi_dot(const int v1[], const int v2[], int count)
{
    int sum = 0;
    for(int i = 0; i < count; ++i)
    {
        sum+=(v1[i]*v2[i]);
    }
    return sum;
}

static inline int vector3i_dot(const int v1[3], const int v2[3])
{
    return vectorNi_dot(v1, v2, 3);
}

static inline int vector4i_dot(const int v1[4], const int v2[4])
{
    return vectorNi_dot(v1, v2, 4);
}

static inline void vector3i_cross_new(int result[3], const int v1[3], const int v2[3])
{
    int temp[3];
    temp[0] = v1[1]*v2[2] - v1[2]*v2[1];
    temp[1] = v1[2]*v2[0] - v1[0]*v2[2];
    temp[2] = v1[0]*v2[1] - v1[1]*v2[0];
    vector3i_copy(result, temp);
}

static inline int vector3i_normSq(const int v[3])
{
    return vector3i_dot(v, v);
}

static inline int vector4i_normSq(const int v[4])
{
    return vector4i_dot(v, v);
}

static inline int vector3i_norm(const int v[3])
{
    return (int) sqrtf((float)vector3i_dot(v, v));
}

static inline int vector4i_norm(const int v[4])
{
    return (int) sqrtf((float)vector4i_dot(v, v));
}

static inline void vectorNi_scaleDiv_new(int result[], const int v[], const int scale, int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v[i]/scale;
    }
}

static inline void vectorNi_scaleMul_new(int result[], const int v[], const int scale, int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v[i] * scale;
    }
}

static inline void vector3i_scaleDiv_new(int result[3], const int v[3], const int scale)
{
    vectorNi_scaleDiv_new(result, v, scale, 3);
}

static inline void vector4i_scaleDiv_new(int result[4], const int v[4], const int scale)
{
    vectorNi_scaleDiv_new(result, v, scale, 4);
}

static inline void vector3i_scaleMul_new(int result[3], const int v[3], const int scale)
{
    vectorNi_scaleMul_new(result, v, scale, 3);
}

static inline void vector4i_scaleMul_new(int result[4], const int v[4], const int scale)
{
    vectorNi_scaleMul_new(result, v, scale, 4);
}

static inline void vector3i_scaleDiv(int v[3], const int scale)
{
    vector3i_scaleDiv_new(v, v, scale);
}

static inline void vector3i_scaleMul(int v[3], const int scale)
{
    vector3i_scaleMul_new(v, v, scale);
}

static inline void vector4i_scaleDiv(int v[4], const int scale)
{
    vector4i_scaleDiv_new(v, v, scale);
}

static inline void vector4i_scaleMul(int v[4], const int scale)
{
    vector4i_scaleMul_new(v, v, scale);
}

static inline void vector3i_normalize_new(int result[3], const int v[3])
{
    int len = vector3i_norm(v);
    vector3i_scaleDiv_new(result, v, len);
}

static inline void vector4i_normalize_new(int result[4], const int v[4])
{
    int len = vector4i_norm(v);
    vector4i_scaleDiv_new(result, v, len);
}

static inline void vector3i_normalize(int v[3])
{
    vector3i_normalize_new(v, v);
}

static inline void vector4i_normalize(int v[4])
{
    vector4i_normalize_new(v, v);
}

static inline void vectorNi_add_new(int result[], const int v1[], const int v2[], const int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v1[i] + v2[i];
    }
}

static inline void vectorNi_sub_new(int result[], const int v1[], const int v2[], const int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v1[i] - v2[i];
    }
}

static inline void vector3i_add_new(int result[3], const int v1[3], const int v2[3])
{
    vectorNi_add_new(result, v1, v2, 3);
}

static inline void vector3i_sub_new(int result[3], const int v1[3], const int v2[3])
{
    vectorNi_sub_new(result, v1, v2, 3);
}

static inline void vector4i_add_new(int result[4], const int v1[4], const int v2[4])
{
    vectorNi_add_new(result, v1, v2, 4);
}

static inline void vector4i_sub_new(int result[4], const int v1[4], const int v2[4])
{
    vectorNi_sub_new(result, v1, v2, 4);
}

static inline void vector3i_add(int v1[3], const int v2[3])
{
    vectorNi_add_new(v1, v1, v2, 3);
}

static inline void vector3i_sub(int v1[3], const int v2[3])
{
    vectorNi_sub_new(v1, v1, v2, 3);
}

static inline void vector4i_add(int v1[4], const int v2[4])
{
    vectorNi_add_new(v1, v1, v2, 4);
}

static inline void vector4i_sub(int v1[4], const int v2[4])
{
    vectorNi_sub_new(v1, v1, v2, 4);
}

static inline void vector4i_homogenize_new(int result[4], const int v[4])
{
    vector4i_scaleDiv_new(result, v, v[3]);
}

static inline void vector4i_homogenize(int v[4])
{
    vector4i_scaleDiv_new(v, v, v[3]);
}

static inline void vectorNi_print(const int v[], int count)
{
    int temp[count];
    vectorN_copy(temp, v, count, sizeof(int));
    printf("vector%di[ ", count);
    for(int i = 0; i<count; i++)
    {
        printf("%+4d ", temp[i]);
    }
    printf("]");
}

static inline void vector3i_print(const int v[3])
{
    vectorNi_print(v, 3);
}

static inline void vector4i_print(const int v[4])
{
    vectorNi_print(v, 4);
}

static inline void vector3i_reflect_new(int result[3], const int d[3], const int n[3])
{
    int normD[3], normN[3];
    vector3i_normalize_new(normD, d);
    vector3i_normalize_new(normN, n);
    int scale = 2 * vector3i_dot(normD, normN);
    vector3i_scaleMul(normN, scale);
    vector3i_sub_new(result, normD, normN);
}

static inline void vector4i_reflect_new(int result[4], const int d[4], const int n[4])
{
    int normD[4], normN[4];
    vector4i_normalize_new(normD, d);
    vector4i_normalize_new(normN, n);
    int scale = 2 * vector4i_dot(normD, normN);
    vector4i_scaleMul(normN, scale);
    vector4i_sub_new(result, normD, normN);
}

// Float Vector
typedef float vector3f[3];
typedef float vector4f[4];
typedef vector3f point3f;

static inline void vector3f_set(float v[3], float a, float b, float c)
{
    v[0] = a; v[1] = b; v[2] = c;
}

static inline void vector4f_set(float v[3], float a, float b, float c, float w)
{
    v[0] = a; v[1] = b; v[2] = c; v[3] = w;
}

static inline void vector3f_copy(float dest[3], const float src[3])
{
    vectorN_copy(dest, src, 3, sizeof(float));
}

static inline void vector4f_copy(float dest[4], const float src[4])
{
    vectorN_copy(dest, src, 4, sizeof(float));
}

static inline float vectorNf_dot(const float v1[], const float v2[], int count)
{
    float sum = 0;
    for(int i = 0; i < count; ++i)
    {
        sum+=(v1[i]*v2[i]);
    }
    return sum;
}

static inline float vector3f_dot(const float v1[3], const float v2[3])
{
    return vectorNf_dot(v1, v2, 3);
}

static inline float vector4f_dot(const float v1[4], const float v2[4])
{
    return vectorNf_dot(v1, v2, 4);
}

static inline void vector3f_cross_new(float result[3], const float v1[3], const float v2[3])
{
    float temp[3];
    temp[0] = v1[1]*v2[2] - v1[2]*v2[1];
    temp[1] = v1[2]*v2[0] - v1[0]*v2[2];
    temp[2] = v1[0]*v2[1] - v1[1]*v2[0];
    vector3f_copy(result, temp);
}

static inline float vector3f_normSq(const float v[3])
{
    return vector3f_dot(v, v);
}

static inline float vector4f_normSq(const float v[4])
{
    return vector4f_dot(v, v);
}

static inline float vector3f_norm(const float v[3])
{
    return sqrtf(vector3f_dot(v, v));
}

static inline float vector4f_norm(const float v[4])
{
    return sqrtf(vector4f_dot(v, v));
}

static inline void vectorNf_scaleDiv_new(float result[], const float v[], const float scale, int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v[i]/scale;
    }
}

static inline void vectorNf_scaleMul_new(float result[], const float v[], const float scale, int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v[i] * scale;
    }
}

static inline void vector3f_scaleDiv_new(float result[3], const float v[3], const float scale)
{
    vectorNf_scaleDiv_new(result, v, scale, 3);
}

static inline void vector4f_scaleDiv_new(float result[4], const float v[4], const float scale)
{
    vectorNf_scaleDiv_new(result, v, scale, 4);
}

static inline void vector3f_scaleMul_new(float result[3], const float v[3], const float scale)
{
    vectorNf_scaleMul_new(result, v, scale, 3);
}

static inline void vector4f_scaleMul_new(float result[4], const float v[4], const float scale)
{
    vectorNf_scaleMul_new(result, v, scale, 4);
}

static inline void vector3f_scaleDiv(float v[3], const float scale)
{
    vector3f_scaleDiv_new(v, v, scale);
}

static inline void vector3f_scaleMul(float v[3], const float scale)
{
    vector3f_scaleMul_new(v, v, scale);
}

static inline void vector4f_scaleDiv(float v[4], const float scale)
{
    vector4f_scaleDiv_new(v, v, scale);
}

static inline void vector4f_scaleMul(float v[4], const float scale)
{
    vector4f_scaleMul_new(v, v, scale);
}

static inline void vector3f_normalize_new(float result[3], const float v[3])
{
    float len = vector3f_norm(v);
    vector3f_scaleDiv_new(result, v, len);
}

static inline void vector4f_normalize_new(float result[4], const float v[4])
{
    float len = vector4f_norm(v);
    vector4f_scaleDiv_new(result, v, len);
}

static inline void vector3f_normalize(float v[3])
{
    vector3f_normalize_new(v, v);
}

static inline void vector4f_normalize(float v[4])
{
    vector4f_normalize_new(v, v);
}

static inline void vectorNf_add_new(float result[], const float v1[], const float v2[], const int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v1[i] + v2[i];
    }
}

static inline void vectorNf_sub_new(float result[], const float v1[], const float v2[], const int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v1[i] - v2[i];
    }
}

static inline void vector3f_add_new(float result[3], const float v1[3], const float v2[3])
{
    vectorNf_add_new(result, v1, v2, 3);
}

static inline void vector3f_sub_new(float result[3], const float v1[3], const float v2[3])
{
    vectorNf_sub_new(result, v1, v2, 3);
}

static inline void vector4f_add_new(float result[4], const float v1[4], const float v2[4])
{
    vectorNf_add_new(result, v1, v2, 4);
}

static inline void vector4f_sub_new(float result[4], const float v1[4], const float v2[4])
{
    vectorNf_sub_new(result, v1, v2, 4);
}

static inline void vector3f_add(float v1[3], const float v2[3])
{
    vectorNf_add_new(v1, v1, v2, 3);
}

static inline void vector3f_sub(float v1[3], const float v2[3])
{
    vectorNf_sub_new(v1, v1, v2, 3);
}

static inline void vector4f_add(float v1[4], const float v2[4])
{
    vectorNf_add_new(v1, v1, v2, 4);
}

static inline void vector4f_sub(float v1[4], const float v2[4])
{
    vectorNf_sub_new(v1, v1, v2, 4);
}

static inline void vector4f_homogenize_new(float result[4], const float v[4])
{
    vector4f_scaleDiv_new(result, v, v[3]);
}

static inline void vector4f_homogenize(float v[4])
{
    vector4f_scaleDiv_new(v, v, v[3]);
}

static inline void vectorNf_print(const float v[], int count)
{
    float temp[count];
    vectorN_copy(temp, v, count, sizeof(float));
    printf("vector%df[ ", count);
    for(int i = 0; i<count; i++)
    {
        printf("%+4.4f ", temp[i]);
    }
    printf("]");
}

static inline void vector3f_print(const float v[3])
{
    vectorNf_print(v, 3);
}

static inline void vector4f_print(const float v[4])
{
    vectorNf_print(v, 4);
}

static inline void vector3f_reflect_new(float result[3], const float d[3], const float n[3])
{
    float normD[3], normN[3];
    vector3f_normalize_new(normD, d);
    vector3f_normalize_new(normN, n);
    float scale = 2 * vector3f_dot(normD, normN);
    vector3f_scaleMul(normN, scale);
    vector3f_sub_new(result, normD, normN);
}

static inline void vector4f_reflect_new(float result[4], const float d[4], const float n[4])
{
    float normD[4], normN[4];
    vector4f_normalize_new(normD, d);
    vector4f_normalize_new(normN, n);
    float scale = 2 * vector4f_dot(normD, normN);
    vector4f_scaleMul(normN, scale);
    vector4f_sub_new(result, normD, normN);
}

// Double Vector
static inline void vector3d_set(double v[3], double a, double b, double c)
{
    v[0] = a; v[1] = b; v[2] = c;
}

static inline void vector4d_set(double v[3], double a, double b, double c, double w)
{
    v[0] = a; v[1] = b; v[2] = c; v[3] = w;
}

static inline void vector3d_copy(double dest[3], const double src[3])
{
    vectorN_copy(dest, src, 3, sizeof(double));
}

static inline void vector4d_copy(double dest[4], const double src[4])
{
    vectorN_copy(dest, src, 4, sizeof(double));
}

static inline double vectorNd_dot(const double v1[], const double v2[], int count)
{
    double sum = 0;
    for(int i = 0; i < count; ++i)
    {
        sum+=(v1[i]*v2[i]);
    }
    return sum;
}

static inline double vector3d_dot(const double v1[3], const double v2[3])
{
    return vectorNd_dot(v1, v2, 3);
}

static inline double vector4d_dot(const double v1[4], const double v2[4])
{
    return vectorNd_dot(v1, v2, 4);
}

static inline void vector3d_cross_new(double result[3], const double v1[3], const double v2[3])
{
    double temp[3];
    temp[0] = v1[1]*v2[2] - v1[2]*v2[1];
    temp[1] = v1[2]*v2[0] - v1[0]*v2[2];
    temp[2] = v1[0]*v2[1] - v1[1]*v2[0];
    vector3d_copy(result, temp);
}

static inline double vector3d_normSq(const double v[3])
{
    return vector3d_dot(v, v);
}

static inline double vector4d_normSq(const double v[4])
{
    return vector4d_dot(v, v);
}

static inline double vector3d_norm(const double v[3])
{
    return sqrt(vector3d_dot(v, v));
}

static inline double vector4d_norm(const double v[4])
{
    return sqrt(vector4d_dot(v, v));
}

static inline void vectorNd_scaleDiv_new(double result[], const double v[], const double scale, int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v[i]/scale;
    }
}

static inline void vectorNd_scaleMul_new(double result[], const double v[], const double scale, int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v[i] * scale;
    }
}

static inline void vector3d_scaleDiv_new(double result[3], const double v[3], const double scale)
{
    vectorNd_scaleDiv_new(result, v, scale, 3);
}

static inline void vector4d_scaleDiv_new(double result[4], const double v[4], const double scale)
{
    vectorNd_scaleDiv_new(result, v, scale, 4);
}

static inline void vector3d_scaleMul_new(double result[3], const double v[3], const double scale)
{
    vectorNd_scaleMul_new(result, v, scale, 3);
}

static inline void vector4d_scaleMul_new(double result[4], const double v[4], const double scale)
{
    vectorNd_scaleMul_new(result, v, scale, 4);
}

static inline void vector3d_scaleDiv(double v[3], const double scale)
{
    vector3d_scaleDiv_new(v, v, scale);
}

static inline void vector3d_scaleMul(double v[3], const double scale)
{
    vector3d_scaleMul_new(v, v, scale);
}

static inline void vector4d_scaleDiv(double v[4], const double scale)
{
    vector4d_scaleDiv_new(v, v, scale);
}

static inline void vector4d_scaleMul(double v[4], const double scale)
{
    vector4d_scaleMul_new(v, v, scale);
}

static inline void vector3d_normalize_new(double result[3], const double v[3])
{
    double len = vector3d_norm(v);
    vector3d_scaleDiv_new(result, v, len);
}

static inline void vector4d_normalize_new(double result[4], const double v[4])
{
    double len = vector4d_norm(v);
    vector4d_scaleDiv_new(result, v, len);
}

static inline void vector3d_normalize(double v[3])
{
    vector3d_normalize_new(v, v);
}

static inline void vector4d_normalize(double v[4])
{
    vector4d_normalize_new(v, v);
}

static inline void vectorNd_add_new(double result[], const double v1[], const double v2[], const int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v1[i] + v2[i];
    }
}

static inline void vectorNd_sub_new(double result[], const double v1[], const double v2[], const int count)
{
    for(int i = 0; i < count; i++)
    {
        result[i] = v1[i] - v2[i];
    }
}

static inline void vector3d_add_new(double result[3], const double v1[3], const double v2[3])
{
    vectorNd_add_new(result, v1, v2, 3);
}

static inline void vector3d_sub_new(double result[3], const double v1[3], const double v2[3])
{
    vectorNd_sub_new(result, v1, v2, 3);
}

static inline void vector4d_add_new(double result[4], const double v1[4], const double v2[4])
{
    vectorNd_add_new(result, v1, v2, 4);
}

static inline void vector4d_sub_new(double result[4], const double v1[4], const double v2[4])
{
    vectorNd_sub_new(result, v1, v2, 4);
}

static inline void vector3d_add(double v1[3], const double v2[3])
{
    vectorNd_add_new(v1, v1, v2, 3);
}

static inline void vector3d_sub(double v1[3], const double v2[3])
{
    vectorNd_sub_new(v1, v1, v2, 3);
}

static inline void vector4d_add(double v1[4], const double v2[4])
{
    vectorNd_add_new(v1, v1, v2, 4);
}

static inline void vector4d_sub(double v1[4], const double v2[4])
{
    vectorNd_sub_new(v1, v1, v2, 4);
}

static inline void vector4d_homogenize_new(double result[4], const double v[4])
{
    vector4d_scaleDiv_new(result, v, v[3]);
}

static inline void vector4d_homogenize(double v[4])
{
    vector4d_scaleDiv_new(v, v, v[3]);
}

static inline void vectorNd_print(const double v[], int count)
{
    double temp[count];
    vectorN_copy(temp, v, count, sizeof(double));
    printf("vector%dd[ ", count);
    for(int i = 0; i<count; i++)
    {
        printf("%+4.4f ", temp[i]);
    }
    printf("]");
}

static inline void vector3d_print(const double v[3])
{
    vectorNd_print(v, 3);
}

static inline void vector4d_print(const double v[4])
{
    vectorNd_print(v, 4);
}

static inline void vector3d_reflect_new(double result[3], const double d[3], const double n[3])
{
    double normD[3], normN[3];
    vector3d_normalize_new(normD, d);
    vector3d_normalize_new(normN, n);
    double scale = 2 * vector3d_dot(normD, normN);
    vector3d_scaleMul(normN, scale);
    vector3d_sub_new(result, normD, normN);
}

static inline void vector4d_reflect_new(double result[4], const double d[4], const double n[4])
{
    double normD[4], normN[4];
    vector4d_normalize_new(normD, d);
    vector4d_normalize_new(normN, n);
    double scale = 2 * vector4d_dot(normD, normN);
    vector4d_scaleMul(normN, scale);
    vector4d_sub_new(result, normD, normN);
}

#endif // _VECTOR_H_