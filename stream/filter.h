#ifndef FILTER_H_
#define FILTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "stream.h"


stream* FILTER(short)(stream* pre, FILTER_PTR(short) op)
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

//stream* filter_int(stream* pre, )

#ifdef __cplusplus
}
#endif

#endif // FILTER_H_