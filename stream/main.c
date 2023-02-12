#include <stdio.h>
#include <stdlib.h>
#include "stream.h"

bint filter(short* s)
{
    return *s > 0;
}

void foreach(short* s)
{
    printf("%d\n", *s);
}


int main(void) 
{
    //short array[3] = {0, 1, 8};
    stream* str1 = stream_of_short(5, -1, -2, 2, 4, 5);
    stream* str2 = filter_short(str1, filter);
    for_each_short(str2, foreach);
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
