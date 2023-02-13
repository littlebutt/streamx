#ifndef MACRO_H_
#define MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "spliterator.h"
#include "filter.h"
#include "foreach.h"
#include "map.h"

#define TYPECMP(ty1, ty2) __builtin_types_compatible_p(ty1, ty2)

#define BUILD_SPLITERATOR(ty, sz, ar)                                   \
    (TYPECMP(ty, short) || TYPECMP(ty, int) || TYPECMP(ty, long) ||     \
    TYPECMP(ty, char) || TYPECMP(ty, float) || TYPECMP(ty, double)) ?   \
        _build_spliterator_ ## ty (sz, ar):                             \
        _build_spliterator_reference(sz, ar, sizeof(ty));

#define FREE_SPLITERATOR(ty, spl) \
    (TYPECMP(ty, short) || TYPECMP(ty, int) || TYPECMP(ty, long) ||     \
    TYPECMP(ty, char) || TYPECMP(ty, float) || TYPECMP(ty, double)) ?   \
        _free_spliterator(spl):                                         \
        _free_spliterator_reference(spl)

#ifdef __cplusplus
}
#endif

#endif // MACRO_H_