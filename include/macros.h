#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define true    0x00000001
#define false   0x00000000

typedef int bint;

#define MASK_FLAG(fe, idx)       ((fe) >> (idx) & 1)

#define SET_FLAG_ON(fe, idx)     (fe) |= (1 << idx)

#define SET_FLAG_OFF(fe, idx)    (fe) &= ~(1 << idx)

#define TYPECMP(ty1, ty2) __builtin_types_compatible_p(ty1, ty2)

#define STREAM_OF(ty)           stream_of_ ## ty
#define BUILD_SPLITERATPR(ty)   _build_spliterator_ ## ty

#define STREAM_OF_METHOD(ty)                                                \
    stream* STREAM_OF(ty)(int size, ...)                                    \
    {                                                                       \
        va_list valist;                                                     \
        va_start(valist, size);                                             \
        ty* array = (ty *)malloc(size * sizeof(ty));                        \
        for (int i = 0; i < size; ++i)                                      \
        {                                                                   \
            array[i] = va_arg(valist, int);                                 \
        }                                                                   \
        va_end(valist);                                                     \
        spliterator* spl = BUILD_SPLITERATPR(ty)(size, array);              \
        head* h = (head *)malloc(sizeof(head));                             \
        h->stream_op_flag = 0x00000000;                                     \
        h->spl = spl;                                                       \
        stream* head_stream = (stream *)malloc(sizeof(stream));             \
        head_stream->h = h;                                                 \
        head_stream->next = NULL;                                           \
        head_stream->source = head_stream;                                  \
        head_stream->sink = NULL;                                           \
        head_stream->op_ty = STR_NONE;                                      \
        return head_stream;                                                 \
    }

#define FILTER_PTR(ty)          filter_ptr_ ## ty

#define FOREACH_PTR(ty)         foreach_ptr_ ## ty

#define MAP_PTR(ty)             map_ptr_ ## ty

#define DO_FILTER(ty, op, ar, idx, fe)                                      \
    do                                                                      \
    {                                                                       \
        if(((FILTER_PTR(ty))(p->sink))(ar[idx]) && MASK_FLAG(fe, idx))      \
        {                                                                   \
            SET_FLAG_ON(fe, idx);                                           \
        }                                                                   \
        else                                                                \
        {                                                                   \
            SET_FLAG_OFF(fe, idx);                                          \
        }                                                                   \
    } while (0);

#define DO_MAP(ty, op, ar, idx)                                             \
    do                                                                      \
    {                                                                       \
        ar[idx] = ((MAP_PTR(ty))(op))(ar[idx]);                             \
    } while (0);
        
#define DO_INTERMEDIATE_STAGE(ty, pre, idx, str_state)                      \
    do                                                                      \
    {                                                                       \
        for (stream* p = pre->source; p->next; p = p->next)                 \
        {                                                                   \
            switch (p->op_ty)                                               \
            {                                                               \
                case STR_NONE:                                              \
                {                                                           \
                    continue;                                               \
                }                                                           \
                case STR_FILTER:                                            \
                {                                                           \
                    DO_FILTER(short, p->sink,                               \
                    source->h->spl->v.short_spl.body,                       \
                    idx, str_state->spl_fence);                             \
                    break;                                                  \
                }                                                           \
                case STR_MAP:                                               \
                {                                                           \
                    DO_MAP(short, p->sink,                                  \
                    pre->source->h->spl->v.short_spl.body, idx);            \
                    break;                                                  \
                }                                                           \
                default:                                                    \
                {                                                           \
                    return;                                                 \
                }                                                           \
            }                                                               \
        }                                                                   \
    } while (0);
    
#ifdef __cplusplus
}
#endif

#endif