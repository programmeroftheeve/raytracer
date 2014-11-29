#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct
{
    int size;
    int offset;
    int start;
    int end;
    char* data;
} ringbuffer;

void createRB(ringbuffer *buffer, const int size, const int offset);
void resizeRB(ringbuffer *buffer, int const newSize);
void cleanRB(ringbuffer* buffer);
bool rbEmpty(ringbuffer *buffer);
bool rbFull(ringbuffer *buffer);
void rbadd(ringbuffer *buffer, const void *elem);
void rbpop(ringbuffer *buffer, void *elem);
void rbpeek(ringbuffer *buffer, void *elem);

#endif // _RING_BUFFER_H_