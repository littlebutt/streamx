#ifndef SPLITERATOR_H_
#define SPLITERATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

enum spliterator_type 
{
    SPL_SHORT = 0,
    SPL_INT,
    SPL_LONG,
    SPL_CHAR,
    SPL_FLOAT,
    SPL_DOUBLE,
    SPL_REFERENCE,
};

typedef struct spliterator
{
    // spliterator type
    enum spliterator_type spliterator_ty;

    // spliterator length
    int length;

    union 
    {
        struct 
        {
            short body[0];
        } short_spl;
        
        struct 
        {
            int body[0];
        } int_spl;

        struct 
        {
            long body[0];
        } long_spl;

        struct 
        {
            char body[0];
        } char_spl;

        struct 
        {
            float body[0];
        } float_spl;

        struct 
        {
            double body[0];
        } double_spl;

        struct 
        {
            size_t size;
            void* body[0];
        } reference_spl;   
    } v; 
}__attribute((packed)) spliterator;


spliterator* _build_spliterator_short(int num, short* array)
{
    spliterator* spl = (spliterator *)malloc(sizeof(spliterator) + num * sizeof(short));
    spl->length = num;
    spl->spliterator_ty = SPL_SHORT;
    for (int i = 0; i < num; ++i)
    {
        spl->v.short_spl.body[i] = array[i];
    }
    return spl;
}

spliterator* _build_spliterator_int(int num, int* array)
{
    spliterator* spl = (spliterator *)malloc(sizeof(spliterator) + num * sizeof(int));
    spl->length = num;
    spl->spliterator_ty = SPL_INT;
    for (int i = 0; i < num; ++i)
    {
        spl->v.int_spl.body[i] = array[i];
    }
    return spl;
}

spliterator* _build_spliterator_long(int num, long* array)
{
    spliterator* spl = (spliterator *)malloc(sizeof(spliterator) + num * sizeof(long));
    spl->length = num;
    spl->spliterator_ty = SPL_LONG;
    for (int i = 0; i < num; ++i)
    {
        spl->v.long_spl.body[i] = array[i];
    }
    return spl;
}

spliterator* _build_spliterator_char(int num, char* array)
{
    spliterator* spl = (spliterator *)malloc(sizeof(spliterator) + num * sizeof(char));
    spl->length = num;
    spl->spliterator_ty = SPL_CHAR;
    for (int i = 0; i < num; ++i)
    {
        spl->v.char_spl.body[i] = array[i];
    }
    return spl;
}

spliterator* _build_spliterator_float(int num, float* array)
{
    spliterator* spl = (spliterator *)malloc(sizeof(spliterator) + num * sizeof(float));
    spl->length = num;
    spl->spliterator_ty = SPL_FLOAT;
    for (int i = 0; i < num; ++i)
    {
        spl->v.float_spl.body[i] = array[i];
    }
    return spl;
}

spliterator* _build_spliterator_double(int num, double* array)
{
    spliterator* spl = (spliterator *)malloc(sizeof(spliterator) + num * sizeof(double));
    spl->length = num;
    spl->spliterator_ty = SPL_DOUBLE;
    for (int i = 0; i < num; ++i)
    {
        spl->v.double_spl.body[i] = array[i];
    }
    return spl;
}

void _free_spliterator(spliterator* spl)
{
    free(spl);
}

spliterator* _build_spliterator_reference(int num, void** array, size_t size)
{
    spliterator* spl = (spliterator*) malloc(sizeof(spliterator) + num * sizeof(void *));
    spl->length = num;
    spl->spliterator_ty = SPL_REFERENCE;
    for (int i = 0; i < num; ++i)
    {
        spl->v.reference_spl.size = size;
        spl->v.reference_spl.body[i] = array[i];
    }
    return spl;
}

void _free_spliterator_reference(spliterator* spl)
{
    for (int i = 0; i< spl->length; ++i)
    {
        free(spl->v.reference_spl.body[i]);
    }
    free(spl);
}

#ifdef __cplusplus
}
#endif

#endif // SPLITERATOR_H_