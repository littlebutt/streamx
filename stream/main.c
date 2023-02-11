#include <stdio.h>
#include <stdlib.h>
#include "macro.h"



int main(void) 
{
    short array[3] = {0, 1, 2};
    spliterator* spl = BUILD_SPLITERATOR(short, 3, array)

    // struct spliterator* spl;
    // spl = (struct spliterator*) malloc(sizeof(struct spliterator) + sizeof(void *) * 5);
    // spl->spliterator_ty = REFERENCE;
    // spl->length = 5;
    // demo* d = (demo *) malloc(sizeof(demo));
    // d->di = 1;
    // spl->v.reference_spl.body[0] = d;
    // demo* another = (demo *) spl->v.reference_spl.body[0];

    printf("%d\n", spl->v.short_spl.body[2]);
}
