#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define true    0x00000001
#define false   0x00000000

typedef int bint;

#define MASK_FLAG(fe, su)   \
    ((fe) >> (su) & 1)

#define SET_FLAG_ON(fe, su)    \
    (fe) |= (1 << su)

#define SET_FLAG_OFF(fe, su) \
    (fe) &= ~(1 << su)




#ifdef __cplusplus
}
#endif

#endif