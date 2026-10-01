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
typedef struct {
    long long x;
} __attribute__((packed, aligned(4))) PackedLL_19CAF0;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order DObj.c's inline tail has. */
void FreeDObj(void);
void LinkParentOfDObj(void *a0, PackedLL_19CAF0 *a1);
void UnlinkParentOfDObj(void *a0);

struct Sub15C *CSVSYSTEM_InitDObj(int id, SObjSimpleSetting *lay);
void initPolygonState(char *d, SObjSimpleSetting *lay);

#endif /* DOBJ_H */
