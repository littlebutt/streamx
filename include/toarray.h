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

struct to_array_res_short to_array_short(stream* pre)
{
    struct to_array_res_short* res = (struct to_array_res_short*)malloc(sizeof(struct to_array_res_short));
    res->length = 0;
    stream* cur = (stream *)malloc(sizeof(stream));
    pre->next = cur;
    cur->next = NULL;
    stream* source = pre->source;
    spliterator* spl = source->h->spl;
    long spl_flag = (1 << spl->length) - 1;
    for (int i = 0; i < spl->length; ++i)
    {
        for (stream* p = source; p->next; p = p->next)
        {
            if (p->sink)
            {
                switch (p->op_ty)
                {
                    case STR_FILTER:
                    {
                        if(((FILTER_PTR(short))(p->sink))(spl->v.short_spl.body[i]) && MASK_FLAG(spl_flag, i))
                        {
                            SET_FLAG_ON(spl_flag, i);
                        }
                        else
                        {
                            SET_FLAG_OFF(spl_flag, i);
                        }
                        break;
                    }
                    case STR_MAP:
                    {
                        pre->source->h->spl->v.short_spl.body[i] = ((MAP_PTR(short))(p->sink))(spl->v.short_spl.body[i]);
                    }
                }
            }
        }
        if (MASK_FLAG(spl_flag, i))
        {
            res = (struct to_array_res_short*)realloc(res, sizeof(struct to_array_res_short) + (1 + res->length) * sizeof(short));
            res->res[res->length ++] = pre->source->h->spl->v.short_spl.body[i];
        }
    }
    return *res;
}

#ifdef __cplusplus
}
#endif

#endif // TOARRAY_H_