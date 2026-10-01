/*
 * ico2/sugipon/include/motionManager.h
 *
 * The declarations of what motionManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MOTIONMANAGER_H
#define MOTIONMANAGER_H

struct GObj;

#include "typedef.h"

/* The 0xC0-byte field/wall clip request block.  The sweep radius at +0x70
   is _wallHitReaction's initialiser's single non-zero element; +0x74 is the
   element filter _wallCollisionPreProcess copies in from the root block,
   +0x80 and +0x8C the wall and floor the search hit, each an object node and
   the element, as fieldCollision.h's ClipWork has them.  The block is
   quadword aligned, the alignment of the points it opens with. */
typedef struct ClipBuf { /* field names derived */
    float pt[3][4];      /* 0x00 the start, end and clipped points */
    char _30[64];
    float rad;      /* 0x70 sweep radius */
    WallCfg filter; /* 0x74 the element the search skips */
    WallCfg wall;   /* 0x80 the wall the search hit */
    WallCfg floor;  /* 0x8C the floor the search hit */
    int attr;       /* 0x98 */
    char _9C[4];
    Vec16 normal; /* 0xA0 the hit plane */
    char _B0[16];
} __attribute__((aligned(16))) ClipBuf; /* derived name */

/* a node's 0x40-byte IK state: the blend rate _getFinalMatrix eases toward
   its target, the heading, pitch and pitch step of the look turn, and the
   node's three quaternions */
typedef struct { /* field names derived */
    float rate;  /* 0x00 */
    short h;     /* 0x04 */
    short _6;
    short p; /* 0x08 */
    short _A[2];
    short dp;     /* 0x0E */
    float q[4];   /* 0x10 */
    float q20[4]; /* 0x20 */
    float q30[4]; /* 0x30 */
} MotIk;          /* derived name */

/* one entry of a node's interp limit table, in degrees: the heading, pitch
   and bank limits _getFinalMatrix's turns are clamped to, read at 12-byte
   steps (the table's +0x30 and +0x48 headings are entries 4 and 6) */
typedef struct { /* field names derived */
    float h;
    float p;
    float b;
} MotLimAng; /* derived name */

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionManager.c's inline tail has. */
void SetHitCollisionDisplay(int a, int b);
int ResetMotionProgramInterpInfo(struct GObj *self, int focus);
int SetDirectMotionProgramInterpInfo(struct GObj *self, int focus, float rate);
void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, float *step, int k);
void EditRotEmphasys(void);
void landingFieldAction(ClipBuf *w);
void SkelTest(GObj *self);
void SkelTestGeo(GObj *self);

void GetMatrixOfMotion(GObj *self, char *tbl, void *ofs);

#endif /* MOTIONMANAGER_H */
