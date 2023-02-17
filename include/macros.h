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

#define FILTER_PTR(ty)          filter_ptr_ ## ty

#define FOREACH_PTR(ty)         foreach_ptr_ ## ty

#define MAP_PTR(ty)             map_ptr_ ## ty

#define DO_FILTER(ty, op, ar, idx, fe)                                      \
        do                                                                  \
        {                                                                   \
            if(((FILTER_PTR(ty))(p->sink))(ar[idx]) && MASK_FLAG(fe, idx))  \
            {                                                               \
                SET_FLAG_ON(fe, idx);                                       \
            }                                                               \
            else                                                            \
            {                                                               \
                SET_FLAG_OFF(fe, idx);                                      \
            }                                                               \
        } while (0);

#define DO_MAP(ty, op, ar, idx)                                             \
        do                                                                  \
        {                                                                   \
            ar[idx] = ((MAP_PTR(ty))(op))(ar[idx]);                         \
        } while (0);
        

#ifdef __cplusplus
}
#endif

#endif