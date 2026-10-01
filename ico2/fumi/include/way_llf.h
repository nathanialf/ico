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

#include <libvu0.h>

/* MAIN.MAP globals of way_llf.o's .sdata */
extern int first_waytool;
extern int n_way_group;
extern int current_select_gid;

/* One way point, 64 bytes, 16-aligned by its position vector.  A point
   belongs to one group and is chained to its neighbours in that group.
   Field roles are read from way_llf.c's stores and the users' accesses; the
   names are this repository's. */
typedef struct WayPoint {
    int f0;              /* 0x00, nonzero while the point is in use */
    int f4;              /* 0x04, the point's own index in way_point[] */
    struct WayPoint *f8; /* 0x08, previous point of the group */
    struct WayPoint *fC; /* 0x0C, next point of the group */
    sceVu0FVECTOR pos;   /* 0x10 */
    int f20;             /* 0x20, the owning group's index */
    float f24;           /* 0x24 */
    int f28;             /* 0x28 */
    float f2C;           /* 0x2C */
    int f30;             /* 0x30, set on the two end points of a bridge */
    char _pad34[0xC];
} WayPoint;

/* One way group, 52 bytes: a chain of points, or a bridge between two groups
   (f18 nonzero). */
typedef struct WayGroup {
    int f0;       /* 0x00, nonzero while the group is in use */
    int f4;       /* 0x04, the group's own index in way_group[] */
    WayPoint *f8; /* 0x08, first point */
    WayPoint *fC; /* 0x0C, last point */
    int f10;      /* 0x10, point count */
    int f14;      /* 0x14, closed into a loop */
    int f18;      /* 0x18, nonzero for a bridge */
    int f1C;      /* 0x1C */
    int end[2];   /* 0x20, a bridge's two end points' indices */
    int f28;      /* 0x28, active */
    int f2C;      /* 0x2C, temporary group */
    int f30;      /* 0x30 */
} WayGroup;

/* way_llf.o's .data globals (MAIN.MAP), the way-group and way-point tables */
extern WayGroup way_group[94];
extern WayPoint way_point[275];
/* way_llf.c's functions, in the order the file defines them: the order of
   these first declarations is the order gcc emits the inline bodies in. */
int CreateWayGroup(void);
int CreateTempWayGroup(void);
int DeleteWayGroup(int gno);
void CloseWayGroup(int idx);
int CreateWayPoint(float *pos);
int AddWayPoint(int gno, int pno);
int AddWayPointTop(int a0, int a1);
int InsertWayPointAfter(int dummy, int idx1, int idx2);
int DeleteWayPoint(int pno);
int CreateBridge(float *a, float *b);
WayGroup *WayGroup_begin(void);
WayGroup *WayGroup_next(WayGroup *p);
WayGroup *WayBridge_begin(void);
WayGroup *WayBridge_next(WayGroup *p);
WayGroup *WayBridgeAll_begin(void);
WayGroup *WayBridgeAll_next(WayGroup *p);
WayGroup *WayBridgeVar_begin(void);
WayGroup *WayBridgeVar_next(WayGroup *a0);
WayPoint *WayPoint_begin(void);
WayPoint *WayPoint_next(WayPoint *a0);
WayPoint *WayPointList_begin(int a0);
WayPoint *WayPointList_next(WayPoint *a0);
WayPoint *waypoint_bidirectional_list(WayPoint *self, int which);
void InitWayPointSystem(void);
void SetWayGroupActive(int a0, int a1);
int CheckWayGroupActive(int idx);

#endif /* WAY_LLF_H */
