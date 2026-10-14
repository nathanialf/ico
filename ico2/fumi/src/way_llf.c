#include "debug.h"
#include <libvu0.h>
#include "typedef.h"
#include "way_llf.h"
#include "way_util.h"
#include "include_asm.h"

/* the way groups and the way points, zero-initialised; the points start on
   the 16-byte boundary their position vector gives them */
WayGroup way_group[94] = {0};

WayPoint way_point[275] = {0};

/* way_llf.o's .sdata globals (declared in way_llf.h), tentative definitions */
int first_waytool;

int n_way_group;

int current_select_gid;

/* defined `inline` below, and called before their definitions */
inline int DeleteWayPoint(int pno);
inline void SetWayGroupActive(int gno, int active);

/* The TU's shared group allocator, expanded into CreateWayGroup's and
 * CreateTempWayGroup's callers: the first free slot of the way-group table. */
/* the begin iterators start one record before the way-group table and step
   before the first test */

inline WayPoint *WayPoint_next(WayPoint *p)
{
    WayPoint *end = &way_point[274];
    if (p == 0)
        goto ret0;
    if (p == end)
        goto ret0;
    for (p++;; p++) {
        if (p->used != 0)
            return p;
        if (p == end)
            break;
    }
ret0:
    return 0;
}

/* WayPointList_next's body, a helper defined ahead of WayPointList_begin: the
 * next point of wp's group, or 0 at the end of the ring.  The group record is
 * read before the null test. */
static inline WayPoint *wayPointListNext(WayPoint *wp) /* derived name */
{
    WayGroup *grp = &way_group[wp->group];

    if (wp == 0)
        return 0;
    if (wp->next == grp->first)
        return 0;
    return wp->next;
}

inline WayPoint *WayPointList_begin(int gno)
{
    return way_group[gno].first;
}

inline WayPoint *WayPointList_next(WayPoint *p)
{
    return wayPointListNext(p);
}

inline WayPoint *waypoint_bidirectional_list(WayPoint *self, int which)
{
    if (self == 0) {
        return 0;
    }
    debug_StdPrintfDummy("bidir wp:%p\n", self);
    if (which == 0) {
        return self->prev;
    }
    return self->next;
}

INCLUDE_ASM(InitWayPointSystem);

inline void SetWayGroupActive(int gno, int active)
{
    way_group[gno].active = active;
}

inline int CheckWayGroupActive(int idx)
{
    return way_group[idx].active != 0;
}

INCLUDE_ASM(CreateWayGroup);

INCLUDE_ASM(CreateTempWayGroup);

INCLUDE_ASM(DeleteWayGroup);

INCLUDE_ASM(CloseWayGroup);

INCLUDE_ASM(CreateWayPoint);

INCLUDE_ASM(AddWayPoint);

INCLUDE_ASM(AddWayPointTop);

INCLUDE_ASM(InsertWayPointAfter);

INCLUDE_ASM(DeleteWayPoint);

INCLUDE_ASM(WayGroup_begin);

INCLUDE_ASM(WayGroup_next);

INCLUDE_ASM(WayBridge_begin);

INCLUDE_ASM(WayBridge_next);

INCLUDE_ASM(WayBridgeAll_begin);

INCLUDE_ASM(WayBridgeAll_next);

INCLUDE_ASM(WayBridgeVar_begin);

INCLUDE_ASM(WayBridgeVar_next);

INCLUDE_ASM(WayPoint_begin);
