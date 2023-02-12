#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define true    0x00000001
#define false   0x00000000

typedef int bint;

bint* build_bint_array(int size)
{
    bint* _array = (bint *)malloc(size * sizeof(bint));
    for (int i = 0; i < size; ++i)
    {
        _array[i] = true;
    }
    return _array;
}

void free_bint_array(bint* array)
{
    free(array);
}


#ifdef __cplusplus
}
#endif

#endif