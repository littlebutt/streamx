#ifndef TOARRAY_H_
#define TOARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include "stream.h"

struct to_array_res_short {
    long length;
    short res[0];
}__attribute((packed));

struct to_array_res_short* to_array_short(stream* pre)
{
    struct to_array_res_short* res = (struct to_array_res_short*)malloc(sizeof(struct to_array_res_short));
    res->length = 0;
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
        for (stream* p = source; p->next; p = p->next)
        {
            switch (p->op_ty)
            {
                case STR_NONE:
                {
                    continue;
                }
                case STR_FILTER:
                {
                    DO_FILTER(short, p->sink, spl->v.short_spl.body, i, str_state->spl_fence);
                    break;
                }
                case STR_MAP:
                {
                    DO_MAP(short, p->sink, pre->source->h->spl->v.short_spl.body, i);
                    break;
                }
                default:
                {
                    return;
                }
            }
        }
        if (MASK_FLAG(str_state->spl_fence, i))
        {
            res = (struct to_array_res_short*)realloc(res, sizeof(struct to_array_res_short) + (1 + res->length) * sizeof(short));
            res->res[res->length ++] = pre->source->h->spl->v.short_spl.body[i];
        }
    }
    return res;
}

#ifdef __cplusplus
}
#endif

#endif // TOARRAY_H_