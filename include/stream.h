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
    STR_NONE = 0,
    STR_FILTER,
    STR_MAP,
    STR_DISTINCT,
    STR_SORTED,
    STR_LIMIT,
    STR_REDUCE,
    STR_FOREACH,
    STR_TOARRAY,
    STR_MAX,
    STR_MIN,
    STR_COUNT,
    STR_ANYMATCH,
    STR_ALLMATCH,
};

typedef struct _stream 
{
    head* h;
    struct _stream* source;
    struct _stream* next;
    enum stream_op_type op_ty;
    void* sink;
    long limit_size;
}stream;

typedef struct 
{
    long length;
    long spl_fence;
    long spl_max;
    long spl_min;
}stream_state;


STREAM_OF_METHOD(short)

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