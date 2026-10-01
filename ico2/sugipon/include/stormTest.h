/*
 * ico2/sugipon/include/stormTest.h
 *
 * The declarations of what stormTest.c defines, for the files that use
 * them.  The file name is derived.
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
    int num;                   /* 0x00 */
    char pad04[12];            /* 0x04 */
    float color[4];            /* 0x10 */
    struct StormPackage *pkg;  /* 0x20 */
    char pad24[12];            /* 0x24 */
} StormTestWork;               /* derived name */

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order stormTest.c's inline tail has. */
StormTestWork *InitStormTestGeo(struct GObj *self, SObjSimpleSetting *lay);
struct StormPackage *InitStormPackage(int mode, int num, int flag);
void ClipStormByVolume(struct StormPackage *pkg);
void ClipStormByCamera(struct StormPackage *pkg);
void UpdateStormPackage(struct StormPackage *pkg);
void DispStormPackage(struct StormPackage *pkg, void *color);
void StormTestGeo(struct GObj *a0);
void StormTestDL(struct GObj *a0);

#endif /* STORMTEST_H */
