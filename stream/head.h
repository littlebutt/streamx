#ifndef HEAD_H_
#define HEAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "spliterator.h"

// stream op flag for distinct, set if method distinct() called
#define DISTINCT    0x00000001

// stream op flag for ordered, set if method ordered() called
#define ORDERED     0x00000010

// stream op flag for sorted, set if method sorted(void*) called
#define SORTED      0x00000100

typedef struct head
{
    // spliterator for source
    spliterator* spl;

    // stream op flag;
    int stream_op_flag;
} head;

#ifdef __cplusplus
}
#endif

#endif // HEAD_H_