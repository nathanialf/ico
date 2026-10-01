/*
 * ico2/fumi/include/way_sys.h
 *
 * The declarations of what way_sys.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WAY_SYS_H
#define WAY_SYS_H

#include "way_util.h"

/* The guide-way work block way_sys.c allocates and threads through every
 * member: 0x80 bytes (the actor record embeds one at +0x360 and
 * waySystemManager's request one at +0x20), and only the words the TU reads
 * or writes are named.  act-way.c copies the actor's with 64-bit moves, so the
 * record is 8-byte aligned; act-way.c keeps its own view of it. */
typedef struct WVTObj { /* field names derived */
    char pad00[16];     /* 0x00 */
    int pos[4];         /* 0x10 the current target position */
    CheckWp chk;        /* 0x20 the way point being walked to (cur), the start
                          of the walk (start) and the far end of a crossing (cross),
                          the record set_check_wp fills */
    WayPoint *nearWp;   /* 0x2C */
    int stampFrame;     /* 0x30 */
    int direction;      /* 0x34 */
    int avoiding;       /* 0x38 */
    int flag3C;         /* 0x3C */
    char pad40[4];
    int reached;      /* 0x44 */
    char pad48[8];    /* 0x48 */
    float nrm[4];     /* 0x50 the unit direction to the current way point */
    int group;        /* 0x60 */
    int guideFirst;   /* 0x64 the first point of the guide way avoid_obstacle2
                          lays round an obstacle, -1 when none */
    int escapeFound;  /* 0x68 */
    int flag6C;       /* 0x6C */
    int pathKind;     /* 0x70 */
    WayPoint *fromWp; /* 0x74 */
    char pad78[8];    /* 0x78 */
} WVTObj; /* derived name */

/* way_sys.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
WayPoint *GetWay_begin(float *from, WVTObj *w, float *goal);
void BridgeBox(void);
inline void DeleteGuideWay(WVTObj *o);
int GetWay_next(WVTObj *w, float *pos);
WayPoint *_FUNC_GetWay_begin(float *from, WVTObj *w, float *goal, int threaded);
int GetNearNigePointN(void *out, int num, WVTObj *w, float *pos);

#endif /* WAY_SYS_H */
