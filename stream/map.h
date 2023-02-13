#ifndef MAP_H_
#define MAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "stream.h"

stream* map_short(stream* pre, MAP_PTR(short) op)
{
    stream* cur = (stream *)malloc(sizeof(stream));
    pre->next = cur;
    cur->h = pre->h;
    cur->next = NULL;
    cur->sink = op;
    cur->source = pre->source;
    cur->op_ty = STR_MAP;
    return cur;

}

#ifdef __cplusplus
}
#endif

#endif // MAP_H_