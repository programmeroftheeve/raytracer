#include <util/ringbuffer.h>
#include <stdlib.h>
#include <string.h>

void createRB(ringbuffer *buffer, const int size, const int offset)
{
    buffer->size = size;
    buffer->offset = offset;
    buffer->start = 0;
    buffer->end = 0;
    buffer->data = calloc((size_t) size, (size_t) offset);
}

void resizeRB(ringbuffer *buffer, int const newSize)
{
    buffer->data = realloc(buffer->data, (size_t) (newSize*buffer->offset));
}

void cleanRB(ringbuffer* buffer)
{
    free(buffer->data);
}

bool rbEmpty(ringbuffer *buffer)
{
    return buffer->end == buffer->start;
}

bool rbFull(ringbuffer *buffer)
{
    return (buffer->end + 1) % buffer->size == buffer->start;
}

void rbadd(ringbuffer *buffer, const void *elem)
{
    memcpy(buffer->data + (buffer->end * buffer->offset), elem, (size_t) buffer->offset);
    buffer->end = (buffer->end + 1) % buffer->size;
    if (buffer->end == buffer->start)
        buffer->start = (buffer->start + 1) % buffer->size; /* full, overwrite */
}

void rbpop(ringbuffer *buffer, void *elem)
{
    memcpy(elem, buffer->data+(buffer->start * buffer->offset), (size_t) buffer->offset);
    buffer->start = (buffer->start + 1) % buffer->size;
}

void rbpeek(ringbuffer *buffer, void *elem)
{
    memcpy(elem, buffer->data+(buffer->start * buffer->offset), (size_t) buffer->offset);
}


