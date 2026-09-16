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

extern int ACTWayExec_Position(char *self, int a1, int a2, float speed, int a3);
extern int ACTWayMove_BeginDetail(void *obj, float *b, float *a, void *tgt, int e, int f);
extern int ACTWayMove_NextDetail(void *obj, char *w, float *a, int d, int e);
extern int ACTWay_IsMustWalkFromWay(char *a0);
extern void ACTWay_SetBeginPositionIllegal(char *a0);

#endif /* ACT_WAY_H */
