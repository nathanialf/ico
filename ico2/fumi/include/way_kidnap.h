/*
 * ico2/fumi/include/way_kidnap.h
 *
 * The declarations of what way_kidnap.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WAY_KIDNAP_H
#define WAY_KIDNAP_H

/* way_kidnap.c's functions in definition order.  NumOfWpPos, CopyWpPos,
   WayLengthOfGObj_Pos, WayLengthOfGObj_GObj and WayPointWithRangeFromGObj are
   `inline`: their out-of-line copies come at the end of the object in this
   order (first-declaration order), ahead of the file static wpsort_compfnc. */
int NumOfWpPos(void);
int CopyWpPos(float dst[][4], int from, int to);
float WayLengthOfPos_Pos(float *pos0, float *pos1);
float WayLengthOfGObj_Pos(void *obj, float *pos);
float WayLengthOfGObj_GObj(void *obj0, void *obj1);
int WayPointWithRangeFromPos(float *pos, float range, int mode);

struct WVTObj;

int WayPointWithRangeFromPos2(float *pos, struct WVTObj *w, float *out, int flag);
int WayPointWithRangeFromGObj(void *obj, float f);
void *NearestEnemyFromGirl(float *len);

#endif /* WAY_KIDNAP_H */
