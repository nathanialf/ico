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

int AddWayPoint(int gno, int pno);
void CloseWayGroup(int idx);
void *CreateBridge(float *a, float *b);
int CreateWayGroup(void);
int CreateWayPoint(int a0);
int DeleteWayGroup(int gno);
int DeleteWayPoint(int pno);
int InsertWayPointAfter(int dummy, int idx1, int idx2);
void SetWayGroupActive(int a0, int a1);
int WayPointList_begin(int a0);
int WayPointList_next(int *a0);
void *WayPoint_begin(void);
int WayPoint_next(int a0);

#endif /* WAY_LLF_H */
