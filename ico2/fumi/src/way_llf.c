#include "common.h"
#include "debug.h"
#include <libvu0.h>
#include "typedef.h"
#include "way_util.h"

typedef struct WayGroup {
    int f0;
    char _4[0x14];
    int f18;
    char _1c[0xC];
    int f28;
    char _2c[0x8];
} WayGroup;

typedef struct {
    int w[16];
} WayGroup_DW;

typedef struct {
    int w[16];
} WayGroup_CT;

typedef struct WpNode {
    int f0;
    char _4[0x14];
    int f18;
    char _1C[0x0C];
    int f28;
    char _2C[0x08];
} WpNode;

typedef struct NdW {
    int f0;
    int _4;
    struct NdW *f8;
    struct NdW *fC;
    int f10;
    char _14[0xC];
    int f20;
    char _24[0x4];
    int f28;
    char _2C[0x4];
    int f30;
    char _34[0xC];
} NdW;

typedef struct Nd {
    int pad[2];
    struct Nd *f8;
    struct Nd *fC;
    char pad2[0x40 - 16];
} Nd;

typedef struct WayGrp {
    int f0;
    int _4;
    NdW *f8;
    NdW *fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    int _28;
    int f2C;
    int _30;
} WayGrp;

extern WayRec D_004F1EC0[];
extern Nd D_004F31E0[];
extern int D_0063BD70;
extern int D_0063BD74;
/* gcc 2.9 emits a non-static `inline` function's out-of-line copy at the end of
 * the object, in first-declaration order, so the whole TU is declared here in
 * ROM order and every definition below is `inline`.  That reproduces the ROM's
 * .text layout exactly (see the per-function VMAs in the PAL listing). */
inline int CreateWayGroup(void);
inline int CreateTempWayGroup(void);
inline int DeleteWayGroup(int gno);
inline void CloseWayGroup(int idx);
inline int CreateWayPoint(int a0);
inline int AddWayPoint(int gno, int pno);
inline int AddWayPointTop(int a0, int a1);
inline int InsertWayPointAfter(int dummy, int idx1, int idx2);
inline int DeleteWayPoint(int pno);
inline WpNode *WayGroup_begin(void);
inline WpNode *WayGroup_next(WpNode *p);
inline WpNode *WayBridge_begin(void);
inline WpNode *WayBridge_next(WpNode *p);
inline WpNode *WayBridgeAll_begin(void);
inline WpNode *WayBridgeAll_next(WpNode *p);
inline void *WayBridgeVar_begin(void);
inline WayGroup *WayBridgeVar_next(WayGroup *a0);
inline void *WayPoint_begin(void);
inline void *WayPoint_next(WayGroup_DW *a0);
inline int WayPointList_begin(int a0);
inline int WayPointList_next(int *a0);
inline int waypoint_bidirectional_list(int *self, int which);
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
        WayGrp *wg = (WayGrp *)&D_004F1EC0[i];

        if (wg->f0 == 0) {
            wg->f0 = 1;
            wg->f8 = 0;
            wg->fC = 0;
            wg->f10 = 0;
            wg->f14 = 0;
            wg->f18 = 0;
            wg->f1C = 0;
            wg->f20 = -1;
            wg->f24 = -1;
            wg->f2C = 0;
            D_0063BD74++;
            return i;
        }
    }
    return -1;
}

inline int CreateTempWayGroup(void)
{
    int no = CreateWayGroup();

    if (no != -1) {
        D_004F1EC0[no].w[11] = 1;
    }
    return no;
}

inline int DeleteWayGroup(int gno)
{
    WayGrp *wg = (WayGrp *)&D_004F1EC0[gno];

    if (wg->f0 == 1) {
        if (wg->f8 != 0) {
            NdW *wp = wg->f8;

            do {
                DeleteWayPoint(wp->_4);
                wp = wp->fC;
            } while (wp != 0);
        }

        wg->f0 = 0;
        D_0063BD74--;
        return 0;
    }
    return 1;
}

inline void CloseWayGroup(int idx)
{
    int *node = (int *)((char *)D_004F1EC0 + idx * 0x34);
    int v1 = node[8 / 4];
    int v0 = node[12 / 4];
    node[20 / 4] = 1;
    *(int *)(v1 + 8) = v0;
    *(int *)(v0 + 12) = v1;
}

inline int CreateWayPoint(int a0)
{
    int i;

    for (i = 0; i < 275; i++) {
        NdW *node = (NdW *)&D_004F31E0[i];

        if (node->f0 == 0) {
            node->f0 = 1;
            node->f20 = -1;
            node->f8 = 0;
            node->fC = 0;
            node->f28 = 0;
            sceVu0CopyVector(&node->f10, a0);
            return i;
        }
    }
    return -1;
}

inline int AddWayPoint(int gno, int pno)
{
    WayGrp *wg = (WayGrp *)&D_004F1EC0[gno];
    NdW *wp = (NdW *)&D_004F31E0[pno];

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
    int *ch = (int *)&D_004F1EC0[a0];
    Nd *node = &D_004F31E0[a1];
    Nd *old;
    node->f8 = 0;
    old = (Nd *)ch[2];
    ch[2] = (int)node;
    node->fC = old->f8;
    old->f8 = node;
    return 0;
}

inline int InsertWayPointAfter(int dummy, int idx1, int idx2)
{
    int *node_a = (int *)((char *)D_004F31E0 + idx1 * 0x40);
    int *node_b = (int *)((char *)D_004F31E0 + idx2 * 0x40);
    int *old = (int *)node_a[3];
    node_a[3] = (int)node_b;
    node_b[2] = (int)node_a;
    node_b[3] = (int)old;
    old[2] = (int)node_b;
    return 0;
}

inline int DeleteWayPoint(int pno)
{
    NdW *wp = (NdW *)&D_004F31E0[pno];
    NdW *prev = wp->f8;
    NdW *next = wp->fC;
    WayGrp *wg = (WayGrp *)&D_004F1EC0[wp->f20];

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
int CreateBridge(int a0, int a1)
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
    ((NdW *)&D_004F31E0[p0])->f30 = 1;
    p1 = CreateWayPoint(a1);
    AddWayPoint(gno, p1);
    ((NdW *)&D_004F31E0[p1])->f30 = 1;
    set_bridge(gno);
    SetWayGroupActive(gno, 1);
    return gno;
}

/* the begin iterators start one record before the way-group table (the ROM
   folds that base to 0x4F1E8C) and step before the first test */

inline WpNode *WayGroup_begin(void)
{
    WpNode *p = (WpNode *)D_004F1EC0 - 1;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0)
                return p;
        } while (p != end);
    }
    return 0;
}

extern WpNode D_004F31A4;

inline WpNode *WayGroup_next(WpNode *p)
{
    WpNode *end = &D_004F31A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0)
                return q;
        } while (q != end);
    }
    return 0;
}

inline WpNode *WayBridge_begin(void)
{
    WpNode *p = (WpNode *)D_004F1EC0 - 1;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0 && p->f28 != 0)
                return p;
        } while (p != end);
    }
    return 0;
}

inline WpNode *WayBridge_next(WpNode *p)
{
    WpNode *end = &D_004F31A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0 && q->f28 != 0)
                return q;
        } while (q != end);
    }
    return 0;
}

inline WpNode *WayBridgeAll_begin(void)
{
    WpNode *p = (WpNode *)D_004F1EC0 - 1;
    WpNode *end = p + 94;
    if (p != 0 && p != end) {
        do {
            p++;
            if (p->f0 != 0 && p->f18 != 0)
                return p;
        } while (p != end);
    }
    return 0;
}

inline WpNode *WayBridgeAll_next(WpNode *p)
{
    WpNode *end = &D_004F31A4;
    if (p != 0 && p != end) {
        WpNode *q = p;
        do {
            q++;
            if (q->f0 != 0 && q->f18 != 0)
                return q;
        } while (q != end);
    }
    return 0;
}

inline void *WayBridgeVar_begin(void)
{
    WayRec *p = D_004F1EC0 - 1;
    WayRec *end = D_004F1EC0 - 1 + 94;
    if (p == 0)
        goto ret0;
    if (p == end)
        goto ret0;
    for (p++;; p++) {
        if (p->w[0] != 0 && p->w[6] != 0 && p->w[10] != 0)
            return p;
        if (p == end)
            break;
    }
ret0:
    return 0;
}

inline WayGroup *WayBridgeVar_next(WayGroup *a0)
{
    WayGroup *p, *end = (WayGroup *)&D_004F31A4;
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

extern WayGroup_CT D_004F31A0[];

inline void *WayPoint_begin(void)
{
    WayGroup_CT *p = D_004F31A0;
    WayGroup_CT *end = D_004F31A0 + 275;
    if (p == 0)
        goto ret0;
    if (p == end)
        goto ret0;
    for (p++;; p++) {
        if (p->w[0] != 0)
            return p;
        if (p == end)
            break;
    }
ret0:
    return 0;
}

extern WayGroup_DW D_004F7660;

inline void *WayPoint_next(WayGroup_DW *a0)
{
    WayGroup_DW *end = &D_004F7660;
    if (a0 == 0)
        goto ret0;
    if (a0 == end)
        goto ret0;
    for (a0++;; a0++) {
        if (a0->w[0] != 0)
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
static inline int wayPointListNext(int *wp)
{
    WayRec *grp = &D_004F1EC0[wp[8]];

    if (wp == 0)
        return 0;
    if (wp[3] == grp->w[2])
        return 0;
    return wp[3];
}

inline int WayPointList_begin(int a0)
{
    return D_004F1EC0[a0].w[2];
}

inline int WayPointList_next(int *a0)
{
    return wayPointListNext(a0);
}

inline int waypoint_bidirectional_list(int *self, int which)
{
    if (self == 0) {
        return 0;
    }
    debug_StdPrintfDummy("bidir wp:%p\n", self);
    if (which == 0) {
        return self[0x8 / 4];
    }
    return self[0xC / 4];
}

void InitWayPointSystem(void)
{
    int i;

    for (i = 0; i < 275; i++) {
        NdW *node = (NdW *)&D_004F31E0[i];

        node->f0 = 0;
        node->_4 = i;
        node->f8 = 0;
        node->fC = 0;
        node->f20 = -1;
    }

    for (i = 0; i < 94; i++) {
        WayGrp *wg = (WayGrp *)&D_004F1EC0[i];

        wg->f0 = 0;
        wg->_4 = i;
        wg->f8 = 0;
        wg->fC = 0;
        wg->f10 = 0;
        wg->f14 = 0;
        wg->f18 = 0;
        wg->f1C = 0;
        wg->_28 = 0;
        wg->f20 = -1;
        wg->f24 = -1;
    }

    D_0063BD70 = 0;
    D_0063BD74 = 0;
}

inline void SetWayGroupActive(int a0, int a1)
{
    D_004F1EC0[a0].w[10] = a1;
}

inline int CheckWayGroupActive(int idx)
{
    return D_004F1EC0[idx].w[10] != 0;
}
