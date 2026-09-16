/*
 * ico2/fumi/include/way_llf.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what way_llf.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef WAY_LLF_H
#define WAY_LLF_H

extern int AddWayPoint(int gno, int pno);
extern void CloseWayGroup(int idx);
extern void *CreateBridge(float *a, float *b);
extern int CreateWayGroup(void);
extern int CreateWayPoint(int a0);
extern int DeleteWayGroup(int gno);
extern int DeleteWayPoint(int pno);
extern int InsertWayPointAfter(int dummy, int idx1, int idx2);
extern void SetWayGroupActive(int a0, int a1);
extern int WayPointList_begin(int a0);
extern int WayPointList_next(int *a0);
extern void *WayPoint_begin(void);
extern int WayPoint_next(int a0);

#endif /* WAY_LLF_H */
