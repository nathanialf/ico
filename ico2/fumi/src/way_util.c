#include "common.h"
#include "debug.h"
#include "act.h"
#include "way_llf.h"
#include "geometryManager.h"
#include <stdlib.h>
#include <libvu0.h>
#include "fuzio.h"
#include "memory.h"

typedef struct {
    float a[4];
    float b[4];
    char pad0[0x70 - 0x20];
    float f70;
    char pad1[0x88 - 0x74];
    int f88;
    char pad2[0xC0 - 0x8C];
} ClipBox;

typedef struct {
    int pad[8];
    int f20;
    int f24;
    int f28;
    int pad2[5];
} WPElem;

typedef struct {
    int f0;
    int f4;
    int i8;
    int iC;
    int f10;
    int f14;
    int i18;
    int f1C;
    int i20;
    int i24;
} WPNode;

typedef struct WNODE {
    int f0;
    int f4;
    char _p[0x20 - 8];
    int i20;
    int i24;
} WNODE;

typedef struct Nd {
    int pad[2];
    struct Nd *f8;
    struct Nd *fC;
    char pad2[0x40 - 16];
} Nd;

typedef struct {
    int f0, f4;
    char *f8;
    char *fC;
    int f10, f14, f18, f1C, f20, f24, f28, f2C;
    int f30;
} WayGrp;

typedef struct {
    int f0, f4, f8, fC, f10, f14, f18;
} WgAll;

typedef struct WpSortEnt {
    char *wp;
    float d;
} WpSortEnt;

/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *);
/* kept local: this TU's uses of ClipWallField do not fit the prototype in fieldCollision.h */
extern void ClipWallField(void *);
extern int D_0063A438;
extern char D_00554300[];

/* way_util.c:313-356.  The listing gives both visible_waypoint_of_all_except_gid
   (def line 360) and its _ThreadVersion (def 365) these same rows, the thread
   build keeping the _ACTWait arms at 329/345/352, so the body is one shared
   static inline helper taking the thread flag. */
static inline char *visible_waypoint_of_all_except_gid_sub(int *pos, int gid, int thread)
{
    /* wpsort_compfnc is one of this file's deferred inline bodies and the ROM
       emits it LAST of them; a file-scope prototype up here would make it the
       first-declared of the group and move its out-of-line copy to the front,
       so the declaration stays local to the only function that takes its
       address. */
    extern int wpsort_compfnc(int a0, int a1);
    int buf[4];
    ClipBox cb;
    WpSortEnt *tbl;
    char *wp;
    char *ret;
    int n;
    int i;

    tbl = (WpSortEnt *)iosMallocDebug(D_0063A438, 0x898, D_00554300, 0x139);

    n = 0;
    for (wp = WayPoint_begin(); wp != 0; wp = (char *)WayPoint_next((int)wp)) {
        if (*(int *)(wp + 0x20) != gid) {
            float d;

            sceVu0SubVector(buf, wp + 0x10, pos);
            d = fzMagnitudefv((int)buf);
            tbl[n].wp = wp;
            tbl[n].d = d;
            n++;
        }
    }

    qsort(tbl, n, 8, wpsort_compfnc);
    if (thread) {
        _ACTWait(1);
    }
    cb.f70 = 0.0f;

    ret = 0;
    for (i = 0; i < n; i++) {
        wp = tbl[i].wp;
        sceVu0CopyVector(cb.a, pos);
        sceVu0CopyVector(cb.b, wp + 0x10);
        cb.a[1] -= 75.0f;
        cb.b[1] -= 75.0f;
        ClipWall(&cb);
        if (cb.f88 == 0) {
            if (thread) {
                _ACTWait(1);
            }
            ClipWallField(&cb);
            if (cb.f88 == 0) {
                ret = wp;
                break;
            }
        }
        if (thread) {
            _ACTWait(1);
        }
    }

    iosFree(tbl);
    return ret;
}

char *visible_waypoint_of_all_except_gid(int *pos, int gid)
{
    return visible_waypoint_of_all_except_gid_sub(pos, gid, 0);
}

char *visible_waypoint_of_all_except_gid_ThreadVersion(int *pos, int gid)
{
    return visible_waypoint_of_all_except_gid_sub(pos, gid, 1);
}

extern WayGrp D_004F1EC0[];

/* way_util.c:383-426.  Same two-wrapper shape as the pair above: the listing
   gives visible_waypoint_of_all_except_temp (def line 430) and its
   _ThreadVersion (def 435) the same body rows 383-425, the thread build keeping
   the _ACTWait arms at 401, 416 and 423. */
static inline char *visible_waypoint_of_all_except_temp_sub(int *pos, int gid, int thread)
{
    extern int wpsort_compfnc(int a0, int a1);
    int buf[4];
    ClipBox cb;
    WpSortEnt *tbl;
    char *wp;
    char *ret;
    int n;
    int i;

    tbl = (WpSortEnt *)iosMallocDebug(D_0063A438, 0x898, D_00554300, 383);

    n = 0;
    for (wp = WayPoint_begin(); wp != 0; wp = (char *)WayPoint_next((int)wp)) {
        int g = *(int *)(wp + 0x20);

        if (D_004F1EC0[g].f2C == 0 || g == gid) {
            float d;

            sceVu0SubVector(buf, wp + 0x10, pos);
            d = fzMagnitudefv((int)buf);
            tbl[n].wp = wp;
            tbl[n].d = d;
            n++;
        }
    }

    qsort(tbl, n, 8, wpsort_compfnc);
    if (thread) {
        _ACTWait(1);
    }
    cb.f70 = 0.0f;

    ret = 0;
    for (i = 0; i < n; i++) {
        wp = tbl[i].wp;
        sceVu0CopyVector(cb.a, pos);
        sceVu0CopyVector(cb.b, wp + 0x10);
        cb.a[1] -= 75.0f;
        cb.b[1] -= 75.0f;
        ClipWall(&cb);
        if (cb.f88 == 0) {
            if (thread) {
                _ACTWait(1);
            }
            ClipWallField(&cb);
            if (cb.f88 == 0) {
                ret = wp;
                break;
            }
        }
        if (thread) {
            _ACTWait(1);
        }
    }

    iosFree(tbl);
    return ret;
}

char *visible_waypoint_of_all_except_temp(int *pos, int gid)
{
    return visible_waypoint_of_all_except_temp_sub(pos, gid, 0);
}

char *visible_waypoint_of_all_except_temp_ThreadVersion(int *pos, int gid)
{
    return visible_waypoint_of_all_except_temp_sub(pos, gid, 1);
}

void ez_line(void)
{
    volatile int local[12];
}

void ez_circle(void)
{
    volatile int local[12];
}

extern void *memset(void *dst, int c, int n);
extern char D_00554340[];
extern char D_00554350[];
extern char D_00554368[];

int short_direction_between_wp(char *from, char *to)
{
    float len[2];
    char *wp;
    char *nxt;
    int dir;

    memset(len, 0, 8);
    dir = -1;

    for (wp = (char *)WayPointList_begin(*(int *)(to + 0x20)); wp != 0;
         wp = (char *)WayPointList_next(wp)) {
        if (wp == from) {
            dir = 0;
            break;
        }
        if (wp == to) {
            dir = 1;
            break;
        }
        nxt = *(char **)(wp + 0xC);
        if (nxt != 0) {
            len[0] += fzMagnitude2fv(wp + 0x10, nxt + 0x10);
        }
    }

    for (; wp != 0; wp = (char *)WayPointList_next(wp)) {
        if (dir == 1 && wp == from) {
            break;
        }
        if (dir == 0 && wp == to) {
            break;
        }
        nxt = *(char **)(wp + 0xC);
        if (nxt != 0) {
            len[1] += fzMagnitude2fv(wp + 0x10, nxt + 0x10);
        }
    }

    if (wp == 0) {
        debug_StdPrintfDummy(D_00554340);
        debug_StdPrintfDummy(D_00554350, *(int *)(to + 0x20));
        for (wp = (char *)WayPointList_begin(*(int *)(to + 0x20)); wp != 0;
             wp = (char *)WayPointList_next(wp)) {
            debug_StdPrintfDummy(D_00554368, wp, *(int *)(wp + 4));
        }
        return -2;
    }

    if (D_004F1EC0[*(int *)(wp + 0x20)].f14 == 0) {
        return dir;
    }

    for (; wp != 0; wp = (char *)WayPointList_next(wp)) {
        nxt = *(char **)(wp + 0xC);
        if (nxt != 0) {
            len[1] += fzMagnitude2fv(wp + 0x10, nxt + 0x10);
        }
    }

    if (len[0] < len[1]) {
        dir ^= 1;
    }
    return dir;
}

extern WNODE *WayBridge_begin(void);
extern WNODE *WayBridge_next(WNODE *);
extern Nd D_004F31E0[];
extern char D_0063A9F0[];
extern char D_00554390[];

/* INTERIM stand-in: waybridge_between_group is a real function of this TU whose
   out-of-line copy sits in the tail at its ROM slot; the compiler inlines it
   here, and moving the real definition above this caller would reorder the
   deferred inline group the tail already matches. */
static inline WNODE *waybridge_between_groupInline(int a0, int a1)
{
    WNODE *p = WayBridge_begin();
    while (p != 0) {
        char *eA = (char *)D_004F31E0 + p->i20 * 0x40;
        char *eB = (char *)D_004F31E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        int b = *(int *)(eB + 0x20);
        if (a == a0 && b == a1) {
            return p;
        }
        if (b == a0 && a == a1) {
            return p;
        }
        p = WayBridge_next(p);
    }
    return 0;
}

int wgid_next(int me, int target)
{
    WNODE *p;

    switch (D_004F1EC0[target].f18) {
    case 0:
        for (p = WayBridge_begin(); p != 0; p = WayBridge_next(p)) {
            WNODE *br;

            if (p->f4 == me) {
                int g = ((WPElem *)D_004F31E0)[p->i20].f20;
                debug_StdPrintfDummy(D_0063A9F0, g);
                if (g == target) {
                    return me;
                }
                g = ((WPElem *)D_004F31E0)[p->i24].f20;
                debug_StdPrintfDummy(D_0063A9F0, g);
                if (g == target) {
                    return me;
                }
            }

            br = waybridge_between_groupInline(me, target);
            if (br != 0) {
                debug_StdPrintfDummy(D_00554390);
                return br->f4;
            }
        }
        break;

    case 1: {
        WayGrp *wg = &D_004F1EC0[target];

        int g = ((WPElem *)D_004F31E0)[wg->f20].f20;
        if (g == me) {
            return me;
        }
        return ((WPElem *)D_004F31E0)[wg->f24].f20;
    }
    }

    return -1;
}

extern char D_00554300[];
extern int D_0063A438;

void *WayUtilWorkAlloc(void)
{
    WgAll *p = (WgAll *)iosMallocDebug(D_0063A438, 0x1C, D_00554300, 0x359);
    int *q;
    int i;
    p->f0 = iosMallocDebug(D_0063A438, 0x5F, D_00554300, 0x35B);
    p->f4 = iosMallocDebug(D_0063A438, 0x8A10, D_00554300, 0x35C);
    p->fC = iosMallocDebug(D_0063A438, 0x17C, D_00554300, 0x35D);
    p->f10 = iosMallocDebug(D_0063A438, 0x17C, D_00554300, 0x35E);
    p->f14 = iosMallocDebug(D_0063A438, 0x17C, D_00554300, 0x35F);
    p->f18 = iosMallocDebug(D_0063A438, 0x17C, D_00554300, 0x360);
    q = (int *)iosMallocDebug(D_0063A438, 0x178, D_00554300, 0x362);
    p->f8 = (int)q;
    for (i = 0; i < 94; i++) {
        q[i] = p->f4 + i * 0x178;
    }
    return p;
}

void WayUtilWorkFree(int *self)
{
    iosFree(self[0]);
    iosFree(self[2]);
    iosFree(self[1]);
    iosFree(self[3]);
    iosFree(self[4]);
    iosFree(self[5]);
    iosFree(self[6]);
    iosFree((int)self);
}

/* way_util.c:899-961.  The listing gives shortest_path (def line 968) and
   shortest_path_ThreadVersion (def line 973) the same rows, the thread build
   keeping the _ACTWait arms at 909, 921 and 926, so the body is one shared
   static inline helper taking the thread flag. */
static inline int shortest_path_sub(int from, int to, WgAll *w, int thread)
{
    char *visited = (char *)w->f0;
    int *prev = (int *)w->fC;
    int *dist = (int *)w->f14;
    int **cost = (int **)w->f8;
    WNODE *p;
    int i, j;
    int next, best;

    for (i = 0; i < 94; i++) {
        for (j = 93; j >= 0; j--) {
            cost[i][j] = 0x7FFFFFFF;
        }
    }

    if (thread) {
        _ACTWait(1);
    }

    for (p = WayBridge_begin(); p != 0; p = WayBridge_next(p)) {
        int g1 = ((WPElem *)D_004F31E0)[p->i20].f20;
        int g2 = ((WPElem *)D_004F31E0)[p->i24].f20;
        int b = p->f4;

        cost[g1][b] = 1;
        cost[g2][b] = 1;
        cost[b][g1] = 1;
        cost[b][g2] = 1;
    }

    if (thread) {
        _ACTWait(1);
    }

    for (i = 0; i < 94; i++) {
        visited[i] = 0;
        dist[i] = 0x7FFFFFFF;
    }

    if (thread) {
        _ACTWait(1);
    }

    dist[to] = 0;
    next = to;
    do {
        i = next;
        best = 0x7FFFFFFF;
        visited[i] = 1;
        for (j = 0; j < 94; j++) {
            if (visited[j]) {
                continue;
            }
            if (cost[i][j] < 0x7FFFFFFF && dist[i] + cost[i][j] < dist[j]) {
                dist[j] = dist[i] + cost[i][j];
                prev[j] = i;
            }
            if (dist[j] < best) {
                best = dist[j];
                next = j;
            }
        }
    } while (best < 0x7FFFFFFF);

    if (dist[from] >= 0x7FFFFFFF) {
        i = -1;
    } else {
        i = from;
        while (prev[i] != to) {
            i = prev[i];
        }
    }
    return i;
}

int shortest_path(int from, int to, WgAll *w)
{
    return shortest_path_sub(from, to, w, 0);
}

int shortest_path_ThreadVersion(int from, int to, WgAll *w)
{
    return shortest_path_sub(from, to, w, 1);
}

extern WNODE *WayBridgeAll_begin(void);
extern WNODE *WayBridgeAll_next(WNODE *);

int GetWgAll(int from, int to, WgAll *w)
{
    char *visited = (char *)w->f0;
    int *prev = (int *)w->f10;
    int *dist = (int *)w->f18;
    int **cost = (int **)w->f8;
    WNODE *p;
    int i, j;
    int next, best;

    for (i = 0; i < 94; i++) {
        for (j = 93; j >= 0; j--) {
            cost[i][j] = 0x7FFFFFFF;
        }
    }

    for (p = WayBridgeAll_begin(); p != 0; p = WayBridgeAll_next(p)) {
        int g1 = ((WPElem *)D_004F31E0)[p->i20].f20;
        int g2 = ((WPElem *)D_004F31E0)[p->i24].f20;
        int b = p->f4;

        cost[g1][b] = 1;
        cost[g2][b] = 1;
        cost[b][g1] = 1;
        cost[b][g2] = 1;
    }

    for (i = 0; i < 94; i++) {
        visited[i] = 0;
        dist[i] = 0x7FFFFFFF;
    }

    dist[to] = 0;
    next = to;
    do {
        i = next;
        best = 0x7FFFFFFF;
        visited[i] = 1;
        for (j = 0; j < 94; j++) {
            if (visited[j]) {
                continue;
            }
            if (cost[i][j] < 0x7FFFFFFF && dist[i] + cost[i][j] < dist[j]) {
                dist[j] = dist[i] + cost[i][j];
                prev[j] = i;
            }
            if (dist[j] < best) {
                best = dist[j];
                next = j;
            }
        }
    } while (best < 0x7FFFFFFF);

    if (dist[from] >= 0x7FFFFFFF) {
        i = -1;
    } else {
        i = from;
        while (prev[i] != to) {
            i = prev[i];
        }
    }
    return i;
}

extern WayGrp D_004F1EC0[];
extern Nd D_004F31E0[];
extern char D_005543A8[];

/* INTERIM stand-ins: waypoint_connect_group_side_me and
   waypoint_connect_group_side_bridge are real TU functions whose out-of-line
   copies sit in the tail of this file at their ROM slots; the compiler inlines
   them here, and the tail copies must keep their emission order. */
static inline WPElem *waypoint_connect_group_side_meInline(WPNode *a0, int a1)
{
    WPElem *e = &D_004F31E0[a0->i20];
    if (e->f20 == a1)
        return e;
    e = &D_004F31E0[a0->i24];
    return e->f20 == a1 ? e : 0;
}

static inline int waypoint_connect_group_side_bridgeInline(WPNode *a0, int a1)
{
    WPElem *e = &D_004F31E0[a0->i20];
    if (e->f20 == a1)
        return a0->i8;
    e = &D_004F31E0[a0->i24];
    if (e->f20 == a1)
        return a0->iC;
    return 0;
}

typedef struct CheckWp {
    int f0;
    void *f4;
    void *f8;
} CheckWp;

void set_check_wp(CheckWp *out, int wp, int gid)
{
    switch (D_004F1EC0[gid].f18) {
    case 0: {
        WayGrp *f = &D_004F1EC0[wp];

        out->f4 = waypoint_connect_group_side_meInline((WPNode *)f, gid);
        out->f8 = (void *)waypoint_connect_group_side_bridgeInline((WPNode *)f, gid);
        debug_StdPrintfDummy(D_005543A8, out->f4, out->f8);
        break;
    }
    case 1: {
        WayGrp *g = &D_004F1EC0[gid];

        out->f4 = (void *)waypoint_connect_group_side_bridgeInline((WPNode *)g, wp);
        out->f8 = waypoint_connect_group_side_meInline((WPNode *)g, wp);
        break;
    }
    }
}

extern void *memset(void *dst, int c, int n);

typedef struct WayDist {
    float d0;
    float d1;
} WayDist;

/* gcc's anonymous 8-byte constant for the two {100000.0f, 100000.0f}
   initialisers, declared as an array so the reference is %hi/%lo and not
   gp-relative. */
extern WayDist D_0063A9F8[];

int set_bridge(int gid)
{
    char *wpA[2];
    char *wpB[2];
    WayDist dA;
    WayDist dB;
    int buf[4];
    char *wp;
    float d;

    WayGrp *g = &D_004F1EC0[gid];

    memset(wpA, 0, 8);
    memset(wpB, 0, 8);
    dA = D_0063A9F8[0];
    dB = D_0063A9F8[0];

    if (g->f14 == 1) {
        g->f18 = 0;
        return 0;
    }

    for (wp = WayPoint_begin(); wp != 0; wp = (char *)WayPoint_next((int)wp)) {
        if (*(int *)(wp + 0x20) == gid) {
            continue;
        }
        if (D_004F1EC0[*(int *)(wp + 0x20)].f18 == 1) {
            continue;
        }
        sceVu0SubVector(buf, wp + 0x10, g->f8 + 0x10);
        d = fzMagnitudefv((int)buf);
        if (d < dA.d0) {
            dA.d1 = dA.d0;
            wpA[1] = wpA[0];
            dA.d0 = d;

            wpA[0] = wp;
        } else if (d < dA.d1) {
            dA.d1 = d;
            wpA[1] = wp;
        }
    }

    if (wpA[0] == 0) {
        return 0;
    }

    for (wp = WayPoint_begin(); wp != 0; wp = (char *)WayPoint_next((int)wp)) {
        if (*(int *)(wp + 0x20) == gid) {
            continue;
        }
        if (D_004F1EC0[*(int *)(wp + 0x20)].f18 == 1) {
            continue;
        }
        sceVu0SubVector(buf, wp + 0x10, g->fC + 0x10);
        d = fzMagnitudefv((int)buf);
        if (d < dB.d0) {
            dB.d1 = dB.d0;
            wpB[1] = wpB[0];
            dB.d0 = d;

            wpB[0] = wp;
        } else if (d < dB.d1) {
            dB.d1 = d;
            wpB[1] = wp;
        }
    }

    if (wpA[0] == wpB[0]) {
        if (dA.d0 < dB.d0) {
            if (wpB[1] == 0) {
                return 0;
            }
            wpB[0] = wpB[1];
        } else {
            if (wpA[1] == 0) {
                return 0;
            }
            wpA[0] = wpA[1];
        }
    }

    g->f20 = *(int *)(wpA[0] + 4);
    g->f24 = *(int *)(wpB[0] + 4);

    g->f18 = 1;

    ((WPElem *)D_004F31E0)[g->f20].f28 = 1;
    ((WPElem *)D_004F31E0)[g->f24].f28 = 1;

    return 1;
}

inline char *nearest_waypoint_of_group(int *arg0, int handle)
{
    int buf[4];
    char *t = WayPointList_begin(handle);
    float bestDist = 100000.0f;
    char *best, *cur;
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            sceVu0SubVector(buf, (int *)(cur + 0x10), arg0);
            d = fzMagnitudefv((int)buf);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = WayPointList_next(cur);
        } while (cur != 0);
    }
    return best;
}

extern int D_0063BD78;

inline char *nearest_waypoint(int *a0)
{
    return nearest_waypoint_of_group(a0, D_0063BD78);
}

inline char *nearest_waypoint_from_gobj(void *dobj)
{
    int mtx[4];
    GetRootPosition(mtx, dobj);
    return nearest_waypoint_of_group(mtx, D_0063BD78);
}

extern WayGrp D_004F1EC0[];

inline char *nearest_waypoint_by_lineseg_of_group(void *arg0, int gid)
{
    WayGrp *g = &D_004F1EC0[gid];
    char *cur = g->f8;
    float bestDist = 100000.0f;
    char *best = 0;
    char *next, *n;
    next = *(char **)(cur + 0xC);
    if (next == 0)
        goto out;
    if (next == cur)
        goto out;
    do {
        float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, arg0);
        if (d < bestDist) {
            bestDist = d;
            best = cur;
        }
        cur = *(char **)(cur + 0xC);
        n = *(char **)(cur + 0xC);
        next = n;
        if (n == 0)
            goto out;
    } while (n != cur);
out:
    return best;
}

inline char *nearest_waypoint_by_lineseg(void *arg0)
{
    WayGrp *g = &D_004F1EC0[D_0063BD78];
    char *cur = g->f8;
    float bestDist = 100000.0f;
    char *best = 0;
    char *next, *n;
    next = *(char **)(cur + 0xC);
    if (next == 0)
        goto out;
    if (next == cur)
        goto out;
    do {
        float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, arg0);
        if (d < bestDist) {
            bestDist = d;
            best = cur;
        }
        cur = *(char **)(cur + 0xC);
        n = *(char **)(cur + 0xC);
        next = n;
        if (n == 0)
            goto out;
    } while (n != cur);
out:
    return best;
}

inline char *nearest_waypoint_by_lineseg_of_group_from_gobj(void *dobj, int gid)
{
    int mtx[4];
    int *pos;
    GetRootPosition(mtx, dobj);
    pos = mtx;
    {
        float bestDist = 100000.0f;
        char *best = 0;
        WayGrp *g = &D_004F1EC0[gid];
        char *cur = g->f8;
        char *next, *n;
        next = *(char **)(cur + 0xC);
        if (next == 0)
            goto out;
        if (next == cur)
            goto out;
        do {
            float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, pos);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = *(char **)(cur + 0xC);
            n = *(char **)(cur + 0xC);
            next = n;
            if (n == 0)
                goto out;
        } while (n != cur);
    out:
        return best;
    }
}

inline char *nearest_waypoint_by_lineseg_from_gobj(void *dobj)
{
    int mtx[4];
    int gid = D_0063BD78;
    int *pos;
    GetRootPosition(mtx, dobj);
    pos = mtx;
    {
        float bestDist = 100000.0f;
        char *best = 0;
        WayGrp *g = &D_004F1EC0[gid];
        char *cur = g->f8;
        char *next, *n;
        next = *(char **)(cur + 0xC);
        if (next == 0)
            goto out;
        if (next == cur)
            goto out;
        do {
            float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, pos);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = *(char **)(cur + 0xC);
            n = *(char **)(cur + 0xC);
            next = n;
            if (n == 0)
                goto out;
        } while (n != cur);
    out:
        return best;
    }
}

extern int D_0063BD78;

inline char *waypoint_with_range(int *arg0, float thresh)
{
    int buf[4];
    char *node = WayPointList_begin(D_0063BD78);
    if (node == 0)
        goto ret0;
    do {
        sceVu0SubVector(buf, (int *)(node + 0x10), arg0);
        if (fzMagnitudefv((int)buf) < thresh) {
            return node;
        }
        node = WayPointList_next(node);
    } while (node != 0);
ret0:
    return 0;
}

inline char *nearest_waypoint_of_all_except_group(int *arg0, int a1)
{
    int buf[4];
    char *t = WayPoint_begin();
    float bestDist = 100000.0f;
    char *best, *cur;
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            if (*(int *)(cur + 0x20) != a1) {
                sceVu0SubVector(buf, (int *)(cur + 0x10), arg0);
                d = fzMagnitudefv((int)buf);
                if (d < bestDist) {
                    bestDist = d;
                    best = cur;
                }
            }
            cur = WayPoint_next(cur);
        } while (cur != 0);
    }
    return best;
}

extern unsigned char D_004F1ED8[];

inline char *nearest_waypoint_of_all_not_bridge_except_group(int *arg0, int gid)
{
    int buf[4];
    char *t = WayPoint_begin();
    float bestDist = 100000.0f;
    char *best, *cur;
    best = t;
    cur = best;
    if (best != 0) {
        do {
            int g = *(int *)(cur + 0x20);
            if (g != gid && *(int *)(D_004F1ED8 + g * 0x34) != 1) {
                float d;
                sceVu0SubVector(buf, (int *)(cur + 0x10), arg0);
                d = fzMagnitudefv((int)buf);
                if (d < bestDist) {
                    bestDist = d;
                    best = cur;
                }
            }
            cur = WayPoint_next(cur);
        } while (cur != 0);
    }
    return best;
}

inline char *nearest_waypoint_of_all(int *a0)
{
    int buf[4];
    int neg1 = -1;
    char *t = WayPoint_begin();
    float bestDist = 100000.0f;
    char *best, *cur;
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            if (*(int *)(cur + 0x20) != neg1) {
                sceVu0SubVector(buf, (int *)(cur + 0x10), a0);
                d = fzMagnitudefv((int)buf);
                if (d < bestDist) {
                    bestDist = d;
                    best = cur;
                }
            }
            cur = WayPoint_next(cur);
        } while (cur != 0);
    }
    return best;
}

/* kept local: the declaration in way_util.h changes this TU codegen */
extern char *visible_waypoint_of_all_except_gid(int *arg0, int gid);

inline int visible_waypoint_of_all(void *a0)
{
    return visible_waypoint_of_all_except_gid(a0, -1);
}

inline void visible_waypoint_of_all_from_gobj(void *a0)
{
    int buf[4];
    GetRootPosition(buf, a0);
    visible_waypoint_of_all_except_gid(buf, -1);
}

/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *);

inline char *visible_waypoint(int *arg0, int handle)
{
    int buf[4];
    ClipBox cb;
    float bestDist;
    char *best = 0;
    char *cur;
    cb.f70 = 50.0f;
    cur = WayPointList_begin(handle);
    bestDist = 100000.0f;
    if (cur != 0) {
        do {
            float d;
            sceVu0SubVector(buf, (int *)(cur + 0x10), arg0);
            d = fzMagnitudefv((int)buf);
            if (d < bestDist) {
                sceVu0CopyVector(cb.a, arg0);
                sceVu0CopyVector(cb.b, cur + 0x10);
                cb.a[1] -= 75.0f;
                cb.b[1] -= 75.0f;
                ClipWall(&cb);
                if (cb.f88 == 0) {
                    bestDist = d;
                    best = cur;
                }
            }
            cur = WayPointList_next(cur);
        } while (cur != 0);
    }
    return best;
}

inline char *visible_waypoint_from_gobj(void *dobj, int handle)
{
    int mtx[4];
    GetRootPosition(mtx, dobj);
    return visible_waypoint(mtx, handle);
}

extern WayGrp D_004F1EC0[];
extern Nd D_004F31E0[];

inline void *get_wp_nearest_bridge_side_me(int arg0, int arg1)
{
    unsigned char *base = (unsigned char *)D_004F1EC0;
    char *b = (char *)D_004F31E0;
    int va, vb, new_var, i;
    char *bA, *bB, *a;
    for (i = 0; i < 4888; i += 0x34) {
        a = (char *)base + i;
        if (*(int *)(a + 0x0) == 0)
            continue;
        if (*(int *)(a + 0x18) == 0)
            continue;
        bA = (char *)(*(int *)(a + 0x20) * 0x40 + (int)b);
        new_var = *(int *)(a + 0x24) * 0x40;
        va = *(int *)(bA + 0x20);
        bB = (char *)(new_var + (int)b);
        if (va != arg0)
            goto skipA;
        vb = *(int *)(bB + 0x20);
        if (vb != arg1)
            goto chkB;
        return bB;
    skipA:
        vb = *(int *)(bB + 0x20);
    chkB:
        if (vb != arg0)
            continue;
        if (va != arg1)
            continue;
        return bA;
    }
    return 0;
}

inline int get_wp_nearest_bridge_side_bridge(int arg0, int arg1)
{
    unsigned char *base = (unsigned char *)D_004F1EC0;
    char *b = (char *)D_004F31E0;
    int va, vb, new_var, i;
    char *bA, *bB, *a;
    for (i = 0; i < 4888; i += 0x34) {
        a = (char *)base + i;
        if (*(int *)(a + 0x0) == 0)
            continue;
        if (*(int *)(a + 0x18) == 0)
            continue;
        bA = (char *)(*(int *)(a + 0x20) * 0x40 + (int)b);
        new_var = *(int *)(a + 0x24) * 0x40;
        va = *(int *)(bA + 0x20);
        bB = (char *)(new_var + (int)b);
        if (va != arg0)
            goto skipA;
        vb = *(int *)(bB + 0x20);
        if (vb != arg1)
            goto chkB;
        return *(int *)(a + 0xC);
    skipA:
        vb = *(int *)(bB + 0x20);
    chkB:
        if (vb != arg0)
            continue;
        if (va != arg1)
            continue;
        return *(int *)(a + 0x8);
    }
    return 0;
}

extern char D_00554378[];
extern char D_0063A9E8[];
extern void __assert(void *a0, int a1, void *a2);
extern void debug_assert(void *a0, int a1);

inline int direction_across_bridge(void *a0, int a1)
{
    char *e1 = (char *)D_004F31E0 + *(int *)((char *)a0 + 0x20) * 0x40;
    char *e2;
    if (*(int *)(e1 + 0x20) == a1) {
        return 1;
    }
    e2 = (char *)D_004F31E0 + *(int *)((char *)a0 + 0x24) * 0x40;
    if (*(int *)(e2 + 0x20) != a1) {
        debug_StdPrintfDummy(D_00554378);
        debug_assert(D_00554300, 0x2C2);
        __assert(D_00554300, 0x2C2, D_0063A9E8);
    }
    return 0;
}

extern WNODE *WayBridge_begin(void);
extern WNODE *WayBridge_next(WNODE *);

inline WNODE *waybridge_between_group(int a0, int a1)
{
    WNODE *p = WayBridge_begin();
    while (p != 0) {
        char *eA = (char *)D_004F31E0 + p->i20 * 0x40;
        char *eB = (char *)D_004F31E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        int b = *(int *)(eB + 0x20);
        if (a == a0 && b == a1) {
            return p;
        }
        if (b == a0 && a == a1) {
            return p;
        }
        p = WayBridge_next(p);
    }
    return 0;
}

inline char *bridge_waypoint_side_me(int me, int target)
{
    WNODE *p = WayBridge_begin();
    while (p != 0) {
        char *eA = (char *)D_004F31E0 + p->i20 * 0x40;
        char *eB = (char *)D_004F31E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        if (a == me && *(int *)(eB + 0x20) == target)
            return eB;
        if (*(int *)(eB + 0x20) == me && a == target)
            return eA;
        p = WayBridge_next(p);
    }
    return 0;
}

inline WPElem *waypoint_connect_group_side_me(WPNode *a0, int a1)
{
    WPElem *e = &D_004F31E0[a0->i20];
    if (e->f20 == a1)
        return e;
    e = &D_004F31E0[a0->i24];
    return e->f20 == a1 ? e : 0;
}

inline int bridge_waypoint_side_bridge(int a0, int a1)
{
    WPNode *p = (WPNode *)WayBridge_begin();
    while (p != 0) {
        char *eA = (char *)D_004F31E0 + p->i20 * 0x40;
        char *eB = (char *)D_004F31E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        if (a == a0 && *(int *)(eB + 0x20) == a1) {
            return p->iC;
        }
        if (*(int *)(eB + 0x20) == a0 && a == a1) {
            return p->i8;
        }
        p = (WPNode *)WayBridge_next((WNODE *)p);
    }
    return 0;
}

inline int waypoint_connect_group_side_bridge(WPNode *a0, int a1)
{
    WPElem *e = &D_004F31E0[a0->i20];
    if (e->f20 == a1)
        return a0->i8;
    e = &D_004F31E0[a0->i24];
    if (e->f20 == a1)
        return a0->iC;
    return 0;
}

extern unsigned char D_004F1ED8[];

inline int NearestWgFromTarget(int cur, int end, WgAll *w)
{
    int *dist = (int *)w->f14;
    int *prev = (int *)w->f10;
    while (1) {
        if (dist[cur] != 0x7FFFFFFF) {
            if (*(int *)(D_004F1ED8 + cur * 0x34) == 0)
                break;
        }
        if (cur == end)
            break;
        cur = prev[cur];
    }
    return cur;
}

inline int wpsort_compfnc(int a0, int a1)
{
    float x = *(float *)(a0 + 4);
    float y = *(float *)(a1 + 4);
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}
