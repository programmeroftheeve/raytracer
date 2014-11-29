#ifndef _MARERIAL_H_
#define _MARERIAL_H_

#include <stdbool.h>

typedef struct
{
    float color[3];
    bool reflect;
} material;

static const material EMPTYNESS = {.color = {0,0,0}, .reflect = false};
void printMaterial(const material mat);


#endif // _MARERIAL_H_