/*
 * ico2/fumi/include/act-way.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act-way.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_WAY_H
#define ACT_WAY_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act-way.c's inline tail has. */
unsigned char WayMove_CheckCollis(float *p0, float *p1, void *a2, void *a3);

int ACTWayExec_Position(char *self, int a1, int a2, float speed, int a3);
int ACTWayMove_BeginDetail(char *self, float *goal, float *from, void *tgt,
                           void *e, unsigned char sub);
int ACTWayMove_NextDetail(char *self, float *node, float *goal, unsigned char d,
                          unsigned char e);
int ACTWay_IsMustWalkFromWay(char *a0);
void ACTWay_SetBeginPositionIllegal(char *a0);

#endif /* ACT_WAY_H */
