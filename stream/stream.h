#ifndef STREAM_H_
#define STREAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdlib.h>
#include "head.h"
#include "utils.h"

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


typedef bint(*filter_ptr_short)(short*);

typedef void(*foreach_ptr_short)(short*);

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

stream* filter_short(stream* pre, filter_ptr_short op)
{
    stream* cur = (stream *)malloc(sizeof(stream));
    pre->next = cur;
    cur->h = pre->h;
    cur->next = NULL;
    cur->sink = op;
    cur->source = pre->source;
    cur->op_ty = STR_FILTER;
    return cur;
}

void for_each_short(stream* pre, foreach_ptr_short op)
{
    stream* cur = (stream *)malloc(sizeof(stream));
    pre->next = cur;
    cur->next = NULL;
    stream* source = pre->source;
    spliterator* spl = source->h->spl;
    long spl_flag = (1 << spl->length) - 1;
    for (int i = 0; i < spl->length; ++i)
    {
        short _el = spl->v.short_spl.body[i];
        for (stream* p = source; p->next; p = p->next)
        {
            if (p->sink)
            {
                switch (p->op_ty)
                {
                    case STR_FILTER:
                    {
                        if(((filter_ptr_short)(p->sink))(&_el) && MASK_FLAG(spl_flag, i))
                        {
                            SET_FLAG_ON(spl_flag, i);
                        }
                        else
                        {
                            SET_FLAG_OFF(spl_flag, i);
                        }
                        break;
                    }
                }
            }
        }
        if (MASK_FLAG(spl_flag, i))
        {
            op(&_el);
        }
    }

}

#ifdef __cplusplus
}
#endif

#endif // STREAM_H_