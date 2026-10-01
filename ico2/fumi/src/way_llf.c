#include "debug.h"
#include <libvu0.h>
#include "typedef.h"
#include "way_llf.h"
#include "way_util.h"

/* .data, owned by way_llf.o (MAIN.MAP's two globals, in its order): the way
   groups and the way points, zero-initialised; the points start on the
   16-byte boundary their position vector gives them. */
WayGroup way_group[94] = {0};

WayPoint way_point[275] = {0};

/* MAIN.MAP globals of way_llf.o's .sdata (declared in way_llf.h), tentative
   definitions the compiler emits at the end of the file in this order */
int first_waytool;

int n_way_group;

int current_select_gid;

/* gcc 2.9 emits a non-static `inline` function's out-of-line copy at the end of
 * the object, in first-declaration order (way_llf.h's, which lists the whole TU
 * in ROM order); every definition below is `inline`, and these declarations
 * mark the bodies inline before the first call.  That reproduces the ROM's
 * .text layout exactly (see the per-function VMAs in the PAL listing). */
inline int CreateWayGroup(void);
inline int CreateTempWayGroup(void);
inline int DeleteWayGroup(int gno);
inline void CloseWayGroup(int idx);
inline int CreateWayPoint(float *pos);
inline int AddWayPoint(int gno, int pno);
inline int AddWayPointTop(int a0, int a1);
inline int InsertWayPointAfter(int dummy, int idx1, int idx2);
inline int DeleteWayPoint(int pno);
inline WayGroup *WayGroup_begin(void);
inline WayGroup *WayGroup_next(WayGroup *p);
inline WayGroup *WayBridge_begin(void);
inline WayGroup *WayBridge_next(WayGroup *p);
inline WayGroup *WayBridgeAll_begin(void);
inline WayGroup *WayBridgeAll_next(WayGroup *p);
inline WayGroup *WayBridgeVar_begin(void);
inline WayGroup *WayBridgeVar_next(WayGroup *a0);
inline WayPoint *WayPoint_begin(void);
inline WayPoint *WayPoint_next(WayPoint *a0);
inline WayPoint *WayPointList_begin(int a0);
inline WayPoint *WayPointList_next(WayPoint *a0);
inline WayPoint *waypoint_bidirectional_list(WayPoint *self, int which);
inline void SetWayGroupActive(int a0, int a1);
inline int CheckWayGroupActive(int idx);

/* The listing attributes lines 98-121 to CreateWayGroup, CreateTempWayGroup and
 * (in the Jan-2002 link only) CreateBridge: this is the TU's shared group
 * allocator, expanded into both callers.  Must index the table inside the loop
 * (a pointer walk changes the giv). */
inline int CreateWayGroup(void)
{
    int i;

    for (i = 0; i < 94; i++) {
        WayGroup *wg = &way_group[i];

        if (wg->f0 == 0) {
            wg->f0 = 1;
            wg->f8 = 0;
            wg->fC = 0;
            wg->f10 = 0;
            wg->f14 = 0;
            wg->f18 = 0;
            wg->f1C = 0;
            wg->end[0] = -1;
            wg->end[1] = -1;
            wg->f2C = 0;
            n_way_group++;
            return i;
        }
    }
    return -1;
}

inline int CreateTempWayGroup(void)
{
    int no = CreateWayGroup();

    if (no != -1) {
        way_group[no].f2C = 1;
    }
    return no;
}

inline int DeleteWayGroup(int gno)
{
    WayGroup *wg = &way_group[gno];

    if (wg->f0 == 1) {
        if (wg->f8 != 0) {
            WayPoint *wp = wg->f8;

            do {
                DeleteWayPoint(wp->f4);
                wp = wp->fC;
            } while (wp != 0);
        }

        wg->f0 = 0;
        n_way_group--;
        return 0;
    }
    return 1;
}

inline void CloseWayGroup(int idx)
{
    WayGroup *wg = &way_group[idx];
    WayPoint *first = wg->f8;
    WayPoint *last = wg->fC;
    wg->f14 = 1;
    first->f8 = last;
    last->fC = first;
}

inline int CreateWayPoint(float *pos)
{
    int i;

    for (i = 0; i < 275; i++) {
        WayPoint *node = &way_point[i];

        if (node->f0 == 0) {
            node->f0 = 1;
            node->f20 = -1;
            node->f8 = 0;
            node->fC = 0;
            node->f28 = 0;
            sceVu0CopyVector(node->pos, pos);
            return i;
        }
    }
    return -1;
}

inline int AddWayPoint(int gno, int pno)
{
    WayGroup *wg = &way_group[gno];
    WayPoint *wp = &way_point[pno];

    if (wg->f8 == 0) {
        wg->f8 = wp;
        wg->fC = wp;
    } else {
        wg->fC->fC = wp;
        wp->f8 = wg->fC;
        wp->fC = 0;

        wg->fC = wp;
    }

    wp->f20 = gno;
    wg->f10++;
    return 0;
}

inline int AddWayPointTop(int a0, int a1)
{
    WayGroup *wg = &way_group[a0];
    WayPoint *node = &way_point[a1];
    WayPoint *old;
    node->f8 = 0;
    old = wg->f8;
    wg->f8 = node;
    node->fC = old->f8;
    old->f8 = node;
    return 0;
}

inline int InsertWayPointAfter(int dummy, int idx1, int idx2)
{
    WayPoint *node_a = &way_point[idx1];
    WayPoint *node_b = &way_point[idx2];
    WayPoint *old = node_a->fC;
    node_a->fC = node_b;
    node_b->f8 = node_a;
    node_b->fC = old;
    old->f8 = node_b;
    return 0;
}

inline int DeleteWayPoint(int pno)
{
    WayPoint *wp = &way_point[pno];
    WayPoint *prev = wp->f8;
    WayPoint *next = wp->fC;
    WayGroup *wg = &way_group[wp->f20];

    if (wg->f10 < 4)
        wg->f14 = 0;

    if (wg->f14 != 0) {
        if (wp == wg->f8) {
            wg->f8 = next;

            wg->f10--;
            wp->f0 = 0;
            return 0;
        } else if (wp == wg->fC) {
            wg->fC = prev;

            wg->f10--;
            wp->f0 = 0;
            return 0;
        }
    }

    if (prev != 0) {
        prev->fC = next;
    } else if (next != 0) {
        wg->f8 = next;
    }

    if (next != 0) {
        next->f8 = prev;
    } else if (prev != 0) {
        wg->fC = prev;
    }

    if (prev == 0 && next == 0) {
        wg->f8 = 0;
        wg->fC = 0;
    }

    wp->f0 = 0;
    wg->f10--;
    return 0;
}

/* The January listing puts CreateBridge at way_llf.c:341-369, between
   DeleteWayPoint (285-333) and the begin iterators (376+), and it is the one
   function of the TU too large to inline, so gcc emits it first in the object,
   ahead of every deferred `inline` body.  Its source position still decides the
   constant pool: the failure message below is created before waypoint_
   bidirectional_list's "bidir wp:%p\n" and lands first in .rodata, as in ROM. */
int CreateBridge(float *a0, float *a1)
{
    int gno;
    int p0;
    int p1;

    gno = CreateWayGroup();
    if (gno < 0) {
        debug_StdPrintfDummy("WayPointCreateNewBridge: way group not create\n");
        return -1;
    }
    p0 = CreateWayPoint(a0);
    AddWayPoint(gno, p0);
    way_point[p0].f30 = 1;
    p1 = CreateWayPoint(a1);
    AddWayPoint(gno, p1);
    way_point[p1].f30 = 1;
    set_bridge(gno);
    SetWayGroupActive(gno, 1);
    return gno;
}

/* the begin iterators start one record before the way-group table (the ROM
   folds that base to 0x4F1E8C) and step before the first test */

inline WayGroup *WayGroup_begin(void)
{
    WayGroup *p = way_group - 1;
    WayGroup *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0)
                return p;
        } while (p != end);
    }
    return 0;
}

inline WayGroup *WayGroup_next(WayGroup *p)
{
    WayGroup *end = &way_group[93];
    if (p != 0 && p != end) {
        WayGroup *q = p;
        do {
            q++;
            if (q->f0 != 0)
                return q;
        } while (q != end);
    }
    return 0;
}

inline WayGroup *WayBridge_begin(void)
{
    WayGroup *p = way_group - 1;
    WayGroup *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0 && p->f28 != 0)
                return p;
        } while (p != end);
    }
    return 0;
}

inline WayGroup *WayBridge_next(WayGroup *p)
{
    WayGroup *end = &way_group[93];
    if (p != 0 && p != end) {
        WayGroup *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0 && q->f28 != 0)
                return q;
        } while (q != end);
    }
    return 0;
}

inline WayGroup *WayBridgeAll_begin(void)
{
    WayGroup *p = way_group - 1;
    WayGroup *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0)
                return p;
        } while (p != end);
    }
    return 0;
}

inline WayGroup *WayBridgeAll_next(WayGroup *p)
{
    WayGroup *end = &way_group[93];
    if (p != 0 && p != end) {
        WayGroup *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0)
                return q;
        } while (q != end);
    }
    return 0;
}

inline WayGroup *WayBridgeVar_begin(void)
{
    WayGroup *p = way_group - 1;
    WayGroup *end = way_group - 1 + 94;
    if (p == 0)
        goto ret0;
    if (p == end)
        goto ret0;
    for (p++;; p++) {
        if (p->f0 != 0 && p->f18 != 0 && p->f28 != 0)
            return p;
        if (p == end)
            break;
    }
ret0:
    return 0;
}

inline WayGroup *WayBridgeVar_next(WayGroup *a0)
{
    WayGroup *p, *end = &way_group[93];
    if (a0 != 0 && a0 != end) {
        for (p = a0 + 1;; p++) {
            if (p->f0 != 0 && p->f18 != 0 && p->f28 != 0)
                return p;
            if (p == end)
                break;
        }
    }
    return 0;
}

inline WayPoint *WayPoint_begin(void)
{
    WayPoint *p = way_point - 1;
    WayPoint *end = way_point - 1 + 275;
    if (p == 0)
        goto ret0;
    if (p == end)
        goto ret0;
    for (p++;; p++) {
        if (p->f0 != 0)
            return p;
        if (p == end)
            break;
    }
ret0:
    return 0;
}

inline WayPoint *WayPoint_next(WayPoint *a0)
{
    WayPoint *end = &way_point[274];
    if (a0 == 0)
        goto ret0;
    if (a0 == end)
        goto ret0;
    for (a0++;; a0++) {
        if (a0->f0 != 0)
            return a0;
        if (a0 == end)
            break;
    }
ret0:
    return 0;
}

/* The listing gives WayPointList_next's body to lines 507 to 512, a helper
 * defined ahead of WayPointList_begin (517) and never emitted out of line, so
 * a static inline; its name is ours.  The group record is read before the null
 * test, as the ROM's row order (507 then 509) has it. */
static inline WayPoint *wayPointListNext(WayPoint *wp)
{
    WayGroup *grp = &way_group[wp->f20];

    if (wp == 0)
        return 0;
    if (wp->fC == grp->f8)
        return 0;
    return wp->fC;
}

inline WayPoint *WayPointList_begin(int a0)
{
    return way_group[a0].f8;
}

inline WayPoint *WayPointList_next(WayPoint *a0)
{
    return wayPointListNext(a0);
}

inline WayPoint *waypoint_bidirectional_list(WayPoint *self, int which)
{
    if (self == 0) {
        return 0;
    }
    debug_StdPrintfDummy("bidir wp:%p\n", self);
    if (which == 0) {
        return self->f8;
    }
    return self->fC;
}

void InitWayPointSystem(void)
{
    int i;

    for (i = 0; i < 275; i++) {
        WayPoint *node = &way_point[i];

        node->f0 = 0;
        node->f4 = i;
        node->f8 = 0;
        node->fC = 0;
        node->f20 = -1;
    }

    for (i = 0; i < 94; i++) {
        WayGroup *wg = &way_group[i];

        wg->f0 = 0;
        wg->f4 = i;
        wg->f8 = 0;
        wg->fC = 0;
        wg->f10 = 0;
        wg->f14 = 0;
        wg->f18 = 0;
        wg->f1C = 0;
        wg->f28 = 0;
        wg->end[0] = -1;
        wg->end[1] = -1;
    }

    first_waytool = 0;
    n_way_group = 0;
}

inline void SetWayGroupActive(int a0, int a1)
{
    way_group[a0].f28 = a1;
}

inline int CheckWayGroupActive(int idx)
{
    return way_group[idx].f28 != 0;
}
