/*
 * ico2/sugipon/include/rope.h
 *
 * The declarations of what rope.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ROPE_H
#define ROPE_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order rope.c's inline tail has. */
int CheckRopeUpperWallClimbable(int a0, struct GObj *a1);
void ReleaseRope(void);
void RopeGeo(void *a0);
void SetRopeFixPoint(struct GObj *rope, void *pos, int flag);
void *InitRopeGeo(struct GObj *o, const float *p);
void HoldRope(void *a0, void *a1);
void RopeDL(struct GObj *a0);

#endif /* ROPE_H */
