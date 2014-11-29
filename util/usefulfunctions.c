#include <util/usefulfunctions.h>
#include <stdio.h>

void printArray(const char* comment, const void* array, const int width, const int height, void(*print)(void*), size_t size)
{
    if (comment != NULL) printf("%s:\n", comment);
    char* elements = (char*)array;
    for(int y = 0; y < height; y++)
    {
        if(comment != NULL) printf("\t[ "); else printf("[ ");
        for(int x = 0; x < width; x++)
        {
            print(elements);
            printf(" ");
            elements += size;
        }
        printf("]\n");
    }
}