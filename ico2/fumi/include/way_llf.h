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
typedef struct WayPoint {  /* field names derived */
    int used;              /* 0x00, nonzero while the point is in use */
    int index;             /* 0x04, the point's own index in way_point[] */
    struct WayPoint *prev; /* 0x08, previous point of the group */
    struct WayPoint *next; /* 0x0C, next point of the group */
    sceVu0FVECTOR pos;     /* 0x10 */
    int group;             /* 0x20, the owning group's index */
    float radius;          /* 0x24, the distance within which the point counts as reached */
    int escape;            /* 0x28, nonzero for an escape point (point_nige, GetNearNigePointN) */
    float float2C;         /* 0x2C */
    int bridgeEnd;         /* 0x30, set on the two end points of a bridge */
    char pad34[12];
} WayPoint;

/* One way group, 52 bytes: a chain of points, or a bridge between two groups
   (bridge nonzero). */
typedef struct WayGroup { /* field names derived */
    int used;             /* 0x00, nonzero while the group is in use */
    int index;            /* 0x04, the group's own index in way_group[] */
    WayPoint *first;      /* 0x08, first point */
    WayPoint *last;       /* 0x0C, last point */
    int count;            /* 0x10, point count */
    int closed;           /* 0x14, closed into a loop */
    int bridge;           /* 0x18, nonzero for a bridge */
    int boxBridge;        /* 0x1C, set for the bridge a box makes (create_box_bridge) */
    int end[2];           /* 0x20, a bridge's two end points' indices */
    int active;           /* 0x28, active */
    int temp;             /* 0x2C, temporary group */
    char pad30[4];
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
