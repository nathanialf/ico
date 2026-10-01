/*
 * ico2/fumi/include/act-way.h
 *
 * The declarations of what act-way.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_WAY_H
#define ACT_WAY_H

#include "typedef.h"

/* act-way.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
unsigned char WayMove_CheckCollis(float *p0, float *p1, void *a2, void *a3);
int ACTWayExec_Position(GObj *self, int a1, float *dir, float speed, int a3);

int ACTWayMove_BeginDetail(GObj *self, float *goal, float *from, void *tgt, void *e,
                           unsigned char sub);

int ACTWayMove_NextDetail(GObj *self, float *node, float *goal, unsigned char d, unsigned char e);
int ACTWay_IsMustWalkFromWay(GObj *a0);
void ACTWay_SetBeginPositionIllegal(char *a0);

#endif /* ACT_WAY_H */
