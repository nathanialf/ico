/*
 * ico2/sugipon/include/motionManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONMANAGER_H
#define MOTIONMANAGER_H

struct GObj;

#include "typedef.h"

/* RECONSTRUCTION: the 0xC0-byte field/wall clip request block.  The sweep
   radius at +0x70 is _wallHitReaction's initialiser's single non-zero
   element; +0x74 is the element filter _wallCollisionPreProcess copies in
   from the root block, +0x80 and +0x8C the wall and floor the search hit, each
   an object node and the element, as fieldCollision.h's ClipWork has them.
   The block is quadword aligned: the ROM's constant initialiser of one
   (checkWallSideState's, at 0x61FD00 in .rodata) sits on a 16-byte boundary
   after EditRotEmphasys's 8-aligned strings, the alignment of the points the
   block opens with. */
typedef struct ClipBuf {
    float pt[3][4]; /* 0x00 the start, end and clipped points */
    char _30[64];
    float rad;      /* 0x70 sweep radius */
    WallCfg filter; /* 0x74 the element the search skips */
    WallCfg wall;   /* 0x80 the wall the search hit */
    WallCfg floor;  /* 0x8C the floor the search hit */
    int attr;       /* 0x98 */
    char _9C[4];
    Vec16 normal; /* 0xA0 the hit plane */
    char _B0[16];
} __attribute__((aligned(16))) ClipBuf;

/* RECONSTRUCTION, names ours: a node's 0x40-byte IK state: the blend rate
   _getFinalMatrix eases toward its target, the heading, pitch and pitch step
   of the look turn, and the node's three quaternions. */
typedef struct {
    float rate; /* 0x00 */
    short h;    /* 0x04 */
    short _6;
    short p; /* 0x08 */
    short _A[2];
    short dp;     /* 0x0E */
    float q[4];   /* 0x10 */
    float q20[4]; /* 0x20 */
    float q30[4]; /* 0x30 */
} MotIk;          /* derived name */

/* RECONSTRUCTION, names ours: one entry of a node's interp limit table, in
   degrees: the heading, pitch and bank limits _getFinalMatrix's turns are
   clamped to, read at 12-byte steps (the table's +0x30 and +0x48 headings are
   entries 4 and 6). */
typedef struct {
    float h;
    float p;
    float b;
} MotLimAng; /* derived name */

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionManager.c's inline tail has. */
void SetHitCollisionDisplay(int a, int b);
int ResetMotionProgramInterpInfo(struct GObj *a0, int a1);
int SetDirectMotionProgramInterpInfo(struct GObj *a0, int a1, float f);
void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, float *step, int k);
void _checkCliffAndWall(void);
void _getFinalMatrix(int id);
int adjustSideWall(ClipBuf *w, int a1, Vec16 *wallPlane);
int checkActPointWithHeight(int kind, float h);
void checkCliffState(int a0);
void checkWallSideState(void);
void checkWallState(int flag);
void clearCollisionStatus(void);
int findActPoint(int *list);
void getFinalMatrixWithNaturalGeometry(int id);
void _wallHitReaction(ClipBuf *w, void *pos, void *last, int noSlide);

#endif /* MOTIONMANAGER_H */
