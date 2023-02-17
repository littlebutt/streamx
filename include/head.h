#ifndef HEAD_H_
#define HEAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "spliterator.h"
#include "macros.h"

// stream op flag for distinct, set if method distinct() called
#define DISTINCT    0x00000001

// stream op flag for limit, set if method limit() called
#define LIMIT     0x00000010

// stream op flag for sorted, set if method sorted(void*) called
#define SORTED      0x00000100

#define REDUCE      0x00001000

typedef struct head
{
    // spliterator for source
    spliterator* spl;

    // stream op flag;
    int stream_op_flag;
} head;

bint is_parallel(int stream_op_flag)
{
    return ~(stream_op_flag & 0x00001111);
}

#ifdef __cplusplus
}
#endif

#endif // HEAD_H_