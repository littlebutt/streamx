#ifndef MACRO_H_
#define MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "spliterator.h"

#define BUILD_SPLITERATOR(ty, sz, ar) \
    _build_spliterator_ ## ty (sz, ar);

#define BUILD_SPLITERATOR_REFERENCE(ty, sz, ar) \
    _build_spliterator_reference(sz, ar, sizeof(ty));

#define FREE_SPLITERATOR(spl) \
    _free_spliterator(spl);

#define FREE_SPLITERATOR_REFERENCE(spl) \
    _free_spliterator_reference(spl);

#ifdef __cplusplus
}
#endif

#endif // MACRO_H_