#ifndef FOREACH_H_
#define FOREACH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include "stream.h"

void for_each_short(stream* pre, FOREACH_PTR(short) op)
{
    // 1. appending stream 
    stream* cur = (stream *)malloc(sizeof(stream));
    pre->next = cur;
    cur->next = NULL;
    // 2. building stream_state
    stream_state* str_state = (stream_state *)malloc(sizeof(stream_state));
    long length = pre->source->h->spl->length;
    str_state->length = length;
    str_state->spl_fence = (1 << length) - 1;
    // 3. iterating stream
    stream* source = pre->source;
    spliterator* spl = source->h->spl;
    for (int i = 0; i < length; ++i)
    {
        DO_INTERMEDIATE_STAGE(short, pre, i, str_state);
        
        if (MASK_FLAG(str_state->spl_fence, i))
        {
            op(pre->source->h->spl->v.short_spl.body[i]);
        }
    }

}


#ifdef __cplusplus
}
#endif

#endif // FOREACH_H_