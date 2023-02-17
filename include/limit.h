#ifndef LIMIT_H_
#define LIMIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stream.h"

stream* limit_short(stream* pre, long size)
{
    stream* cur = (stream *)malloc(sizeof(stream));
    pre->next = cur;
    cur->h = pre->h;
    cur->next = NULL;
    cur->limit_size = size;
    cur->source = pre->source;
    cur->op_ty = STR_LIMIT;
    cur->h->stream_op_flag &= LIMIT;
    return cur;
}

#ifdef __cplusplus
}
#endif

#endif