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

int CopyWpPos(float dst[][4], int from, int to);
void *NearestEnemyFromGirl(float *len);
int NumOfWpPos(void);
float WayLengthOfGObj_GObj(void *obj0, void *obj1);
float WayLengthOfPos_Pos(float *pos0, float *pos1);
int WayPointWithRangeFromPos(float *pos, int mode, float range);
struct WayWork;
int WayPointWithRangeFromPos2(float *pos, struct WayWork *w, float *out, int flag);

#endif /* WAY_KIDNAP_H */
