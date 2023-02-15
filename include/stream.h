#ifndef STREAM_H_
#define STREAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdlib.h>
#include "head.h"
#include "macros.h"

enum stream_op_type 
{
    STR_FILTER = 1,
    STR_MAP,
    STR_FOREACH,
    STR_TOARRAY,
};

typedef struct _stream 
{
    head* h;
    struct _stream* source;
    struct _stream* next;
    enum stream_op_type op_ty;
    void* sink;
}stream;

stream* stream_of_short(int size, ...)
{
    va_list valist;
    va_start(valist, size);
    short* array = (short *)malloc(size * sizeof(short));
    for (int i = 0; i < size; ++i)
    {
        array[i] = va_arg(valist, int);
    }
    va_end(valist);

    spliterator* spl = _build_spliterator_short(size, array);
    head* h = (head *)malloc(sizeof(head));
    h->stream_op_flag = 0x00000000;
    h->spl = spl;
    stream* head_stream = (stream *)malloc(sizeof(stream));
    head_stream->h = h;
    head_stream->next = NULL;
    head_stream->source = head_stream;
    head_stream->sink = NULL;
    return head_stream;
}

void free_stream(stream* str)
{
    if (str->h->spl->spliterator_ty == SPL_REFERENCE)
    {
        _free_spliterator_reference(str->h->spl);
    }
    else
    {
        _free_spliterator(str->h->spl);
    }
    free(str->h);
    stream* p = str, *pp = str->next;
    for(; pp != NULL;)
    {   
        free(p);
        p = pp;
        pp = pp->next;
    }
    free(p);
}

typedef void(*FOREACH_PTR(short))(short);

typedef bint(*FILTER_PTR(short))(short);

typedef short(*MAP_PTR(short))(short);


#ifdef __cplusplus
}
#endif

#endif // STREAM_H_