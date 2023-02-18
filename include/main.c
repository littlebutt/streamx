#include <stdio.h>
#include <stdlib.h>
#include "stream_api.h"

bint filter(short s)
{
    return s > 0;
}

short map(short s)
{
    short res = s + 5;
    s = res;
}

void foreach(short s)
{
    printf("%d\n", s);
}


int main(void) 
{
    //short array[3] = {0, 1, 8};
    stream* str1 = stream_of_short(5, -1, -2, 2, 4, 5);
    // stream* str2 = map_short(str1, map);
    stream* str2 = filter_short(str1, filter);
    for_each_short(str2, foreach);
    // short* dst =NULL;
    // struct to_array_res_short* res = to_array_short(str2);
    // for (int i = 0; i < res->length; i++)
    // {
    //     printf("%d ", (int)(res->res[i]));
    // }
    free_stream(str1);
    printf("PAUSE");
    
   // spliterator* spl = BUILD_SPLITERATOR(short, 3, array)

    // struct spliterator* spl;
    // spl = (struct spliterator*) malloc(sizeof(struct spliterator) + sizeof(void *) * 5);
    // spl->spliterator_ty = REFERENCE;
    // spl->length = 5;
    // demo* d = (demo *) malloc(sizeof(demo));
    // d->di = 1;
    // spl->v.reference_spl.body[0] = d;
    // demo* another = (demo *) spl->v.reference_spl.body[0];

    //printf("%d\n", spl->v.short_spl.body[2]);
}
