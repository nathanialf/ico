/*
 * ico2/common/include/DObj.h
 *
 * The declarations of what DObj.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DOBJ_H
#define DOBJ_H

#include "sceneManager.h"

struct Sub15C;

/* The parent-link word LinkParentOfDObj copies: one long long at a 4-byte
 * aligned address, so the struct is packed. */
typedef struct { /* field names derived */
    long long x;
} __attribute__((packed, aligned(4))) PackedLL_19CAF0; /* derived name */

/* DObj.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void FreeDObj(void);
void LinkParentOfDObj(void *obj, PackedLL_19CAF0 *link);
void UnlinkParentOfDObj(void *obj);
struct Sub15C *CSVSYSTEM_InitDObj(int id, SObjSimpleSetting *lay);

#endif /* DOBJ_H */
