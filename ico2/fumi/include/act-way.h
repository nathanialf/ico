/*
 * ico2/fumi/include/act-way.h
 *
 * The declarations of what act-way.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_WAY_H
#define ACT_WAY_H

#include "typedef.h"

#ifdef VERSION_JUN26
/* act-way.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order):
 * ACTWayMove_BeginDetail (also inlined in the two functions after it) and
 * ACTWay_IsMustWalkFromWay.  The demo's BeginDetail takes no sub-thread flag
 * and NextDetail no flag word (enemy_act.c's _ApproachTarget_Way and the
 * demo's act-way.c pass five and three arguments). */
int ACTWayMove_BeginDetail(GObj *self, float *goal, float *from, void *tgt, void *e);
int ACTWayMove_NextDetail(GObj *self, float *node, float *goal);
int ACTWayExec_Position(GObj *self, int tgt, float *dir, float speed, int flags);
int ACTWay_IsMustWalkFromWay(GObj *self);
#else
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
/* act-way.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
unsigned char WayMove_CheckCollis(float *p0, float *p1, void *actor, void *posout);
#endif

int ACTWayExec_Position(GObj *self, int tgt, float *dir, float speed, int flags);

int ACTWayMove_BeginDetail(GObj *self, float *goal, float *from, void *tgt, void *e,
                           unsigned char sub);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
int ACTWayMove_NextDetail(GObj *self, float *node, float *goal, unsigned char d);
#else
int ACTWayMove_NextDetail(GObj *self, float *node, float *goal, unsigned char d, unsigned char e);
#endif

int ACTWay_IsMustWalkFromWay(GObj *self);
void ACTWay_SetBeginPositionIllegal(GObj *self);
#endif

#endif /* ACT_WAY_H */
