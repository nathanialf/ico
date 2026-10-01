/*
 * ico2/sugipon/include/stormTest.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what stormTest.c.inc defines, in the order the
 * coalescing TU's prototype block carried them; every type here is read from
 * the ROM's calling convention at the call sites.
 */

#ifndef STORMTEST_H
#define STORMTEST_H

#include "sceneManager.h"

struct GObj;
struct StormPackage;

/* The 48-byte work record InitStormTestGeo allocates for a storm object: the
 * particle count from the layout's object word, the colour from its scale
 * (alpha 128), and the package the geometry and display functions run. */
typedef struct StormTestWork { /* field names derived */
    int num;                  /* 0x00 */
    char pad04[12];           /* 0x04 */
    float color[4];           /* 0x10 */
    struct StormPackage *pkg; /* 0x20 */
    char pad24[12];           /* 0x24 */
} StormTestWork;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order stormTest.c's inline tail has. */
StormTestWork *InitStormTestGeo(struct GObj *self, SObjSimpleSetting *lay);

#endif /* STORMTEST_H */
