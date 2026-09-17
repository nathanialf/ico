/*
 * ico2/sugipon/include/waterDot.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what waterDot.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WATERDOT_H
#define WATERDOT_H

#include "typedef.h"   /* VECTOR */

typedef struct WaterDot {
    /* 0x00 */ int used;
    /* 0x04 */ int frame;
    /* 0x08 */ int life;
    /* 0x0C */ float scale;
    /* 0x10 */ VECTOR pos;
    /* 0x20 */ VECTOR vel;
} WaterDot;

typedef struct WaterDotWork {
    /* 0x00 */ int num;        /* ring size (AllocWaterDot's 2nd argument) */
    /* 0x04 */ int cur;        /* next ring slot */
    /* 0x08 */ WaterDot *dot;  /* num entries */
    /* 0x0C */ int num2;       /* the second ring's size */
    /* 0x10 */ int cur2;       /* the second ring's slot */
    /* 0x14 */ WaterDot *dot2; /* num2 entries */
    /* 0x18 */ int gobj;       /* the emitter the splash follows */
} WaterDotWork;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order waterDot.c's inline tail has. */
void InitializeWaterDot(void);
void EntryWaterDot(WaterDotWork *w, VECTOR *pos, VECTOR *vel, float range);

WaterDotWork *AllocWaterDot(int gobj, int num, int num2);
void DispWaterDot(WaterDotWork *w);
void ExecWaterDot(WaterDotWork *w);

#endif /* WATERDOT_H */
