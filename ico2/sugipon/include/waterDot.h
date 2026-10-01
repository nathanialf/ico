/*
 * ico2/sugipon/include/waterDot.h
 *
 * The declarations of what waterDot.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WATERDOT_H
#define WATERDOT_H

#include "typedef.h" /* VECTOR */

typedef struct WaterDot { /* field names derived */
    /* 0x00 */ int used;
    /* 0x04 */ int frame;
    /* 0x08 */ int life;
    /* 0x0C */ float scale;
    /* 0x10 */ VECTOR pos;
    /* 0x20 */ VECTOR vel;
} WaterDot; /* derived name */

typedef struct WaterDotWork { /* field names derived */
    /* 0x00 */ int num;        /* ring size (AllocWaterDot's 2nd argument) */
    /* 0x04 */ int cur;        /* next ring slot */
    /* 0x08 */ WaterDot *dot;  /* num entries */
    /* 0x0C */ int num2;       /* the second ring's size */
    /* 0x10 */ int cur2;       /* the second ring's slot */
    /* 0x14 */ WaterDot *dot2; /* num2 entries */
    /* 0x18 */ struct GObj *gobj; /* the emitter the splash follows */
} WaterDotWork; /* derived name */

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order waterDot.c's inline tail has. */
void InitializeWaterDot(void);
void EntryWaterDot(WaterDotWork *w, void *pos, void *vel, float range);
WaterDotWork *AllocWaterDot(struct GObj *gobj, int num, int num2);
void DispWaterDot(WaterDotWork *w);
void ExecWaterDot(WaterDotWork *w);
void setWaterDot(WaterDot *dot, VECTOR *pos, VECTOR *vel);

#endif /* WATERDOT_H */
