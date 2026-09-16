/*
 * ico2/fumi/include/way_kidnap.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what way_kidnap.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WAY_KIDNAP_H
#define WAY_KIDNAP_H

extern int CopyWpPos(float dst[][4], int from, int to);
extern void *NearestEnemyFromGirl(float *len);
extern int NumOfWpPos(void);
extern float WayLengthOfGObj_GObj(void *obj0, void *obj1);
extern float WayLengthOfPos_Pos(float *pos0, float *pos1);
extern int WayPointWithRangeFromPos(float *pos, int mode, float range);
extern int WayPointWithRangeFromPos2(float *pos, void *a1, float *out, int flag);

#endif /* WAY_KIDNAP_H */
