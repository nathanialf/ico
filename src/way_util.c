#include "common.h"

typedef struct {
    float a[4];
    float b[4];
    char pad0[0x70 - 0x20];
    float f70;
    char pad1[0x88 - 0x74];
    int f88;
    char pad2[0xC0 - 0x8C];
} ClipBox;

typedef struct { int pad[8]; int f20; int pad2[7]; } WPElem;
typedef struct { int f0; int f4; int i8; int iC; int f10; int f14; int i18; int f1C; int i20; int i24; } WPNode;

typedef struct WNODE { char _p[0x20]; int i20; int i24; } WNODE;

typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;
typedef struct { int f0, f4; char *f8; char *fC; int f10, f14, f18, f1C, f20, f24, f28, f2C; int f30; } WayGrp;

typedef struct {
    int f0, f4, f8, fC, f10, f14, f18;
} WgAll;

INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_gid);
INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_gid_ThreadVersion);
INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_temp);
INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_temp_ThreadVersion);
void ez_line(void) {
    volatile int local[12];
}
void ez_circle(void) {
    volatile int local[12];
}
INCLUDE_ASM("asm/nonmatchings/src/way_util", short_direction_between_wp);
INCLUDE_ASM("asm/nonmatchings/src/way_util", wgid_next);
extern char D_00554300[];
extern int D_0063A438;
extern int iosMallocDebug(int, int, const char *, int);

void *WayUtilWorkAlloc(void) {
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
    for (i = 0; i < 0x5E; i++) {
        q[i] = p->f4 + i * 0x178;
    }
    return p;
}
extern void iosFree();

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
INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path);
INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path_ThreadVersion);
INCLUDE_ASM("asm/nonmatchings/src/way_util", GetWgAll);
INCLUDE_ASM("asm/nonmatchings/src/way_util", set_check_wp);
INCLUDE_ASM("asm/nonmatchings/src/way_util", set_bridge);
extern int WayPointList_begin();
extern int WayPointList_next();
extern float fzMagnitudefv(int a0);
extern void sceVu0SubVector();

char *nearest_waypoint_of_group(int *arg0, int handle)
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

char *nearest_waypoint(int *a0) {
    int buf[4];
    char *t = WayPointList_begin(D_0063BD78);
    float bestDist = 100000.0f;
    char *best, *cur;
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            sceVu0SubVector(buf, (int *)(cur + 0x10), a0);
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
INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_from_gobj);
ASM_LIT4_SLOT(D_00639068, 100000.0f);
extern WayGrp D_004F1EC0[];
extern float fzMagnitudeByLineSeg(void *a0, void *a1, void *a2);

char *nearest_waypoint_by_lineseg_of_group(void *arg0, int gid)
{
    WayGrp *g = &D_004F1EC0[gid];
    char *cur = g->f8;
    float bestDist = 100000.0f;
    char *best = 0;
    char *next, *n;
    next = *(char **)(cur + 0xC);
    if (next == 0) goto out;
    if (next == cur) goto out;
    do {
        float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, arg0);
        if (d < bestDist) {
            bestDist = d;
            best = cur;
        }
        cur = *(char **)(cur + 0xC);
        n = *(char **)(cur + 0xC);
        next = n;
        if (n == 0) goto out;
    } while (n != cur);
out:
    return best;
}
char *nearest_waypoint_by_lineseg(void *arg0)
{
    WayGrp *g = &D_004F1EC0[D_0063BD78];
    char *cur = g->f8;
    float bestDist = 100000.0f;
    char *best = 0;
    char *next, *n;
    next = *(char **)(cur + 0xC);
    if (next == 0) goto out;
    if (next == cur) goto out;
    do {
        float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, arg0);
        if (d < bestDist) {
            bestDist = d;
            best = cur;
        }
        cur = *(char **)(cur + 0xC);
        n = *(char **)(cur + 0xC);
        next = n;
        if (n == 0) goto out;
    } while (n != cur);
out:
    return best;
}
extern void GetRootPosition(void *a0, void *a1);

char *nearest_waypoint_by_lineseg_of_group_from_gobj(void *dobj, int gid)
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
        if (next == 0) goto out;
        if (next == cur) goto out;
        do {
            float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, pos);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = *(char **)(cur + 0xC);
            n = *(char **)(cur + 0xC);
            next = n;
            if (n == 0) goto out;
        } while (n != cur);
out:
        return best;
    }
}
char *nearest_waypoint_by_lineseg_from_gobj(void *dobj)
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
        if (next == 0) goto out;
        if (next == cur) goto out;
        do {
            float d = fzMagnitudeByLineSeg(cur + 0x10, next + 0x10, pos);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = *(char **)(cur + 0xC);
            n = *(char **)(cur + 0xC);
            next = n;
            if (n == 0) goto out;
        } while (n != cur);
out:
        return best;
    }
}
extern int D_0063BD78;
extern int WayPointList_begin();
extern int WayPointList_next();
extern float fzMagnitudefv(int a0);
extern void sceVu0SubVector();

char *waypoint_with_range(int *arg0, float thresh)
{
    int buf[4];
    char *node = WayPointList_begin(D_0063BD78);
    if (node == 0) goto ret0;
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
extern char *WayPoint_begin(void);
extern int WayPoint_next(int a0);

char *nearest_waypoint_of_all_except_group(int *arg0, int a1) {
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

char *nearest_waypoint_of_all_not_bridge_except_group(int *arg0, int gid) {
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
char *nearest_waypoint_of_all(int *a0) {
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
extern char *visible_waypoint_of_all_except_gid(int *arg0, int gid);

int visible_waypoint_of_all(void *a0) {
    return visible_waypoint_of_all_except_gid(a0, -1);
}
extern void GetRootPosition(void *a0, void *a1);

void visible_waypoint_of_all_from_gobj(void *a0) {
    int buf[4];
    GetRootPosition(buf, a0);
    visible_waypoint_of_all_except_gid(buf, -1);
}
extern void ClipWall(void *);
extern void sceVu0CopyVector(void *buf, int x);

char *visible_waypoint(int *arg0, int handle)
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
INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_from_gobj);
ASM_LIT4_SLOT(D_0063908C, 100000.0f);
extern WayGrp D_004F1EC0[];
extern Nd D_004F31E0[];

void *get_wp_nearest_bridge_side_me(int arg0, int arg1)
{
    unsigned char *base = (unsigned char *)D_004F1EC0;
    char *b = (char *)D_004F31E0;
    int va, vb, new_var, i;
    char *bA, *bB, *a;
    for (i = 0; i < 0x1318; i += 0x34) {
        a = (char *)base + i;
        if (*(int *)(a + 0x0) == 0) continue;
        if (*(int *)(a + 0x18) == 0) continue;
        bA = (char *)(*(int *)(a + 0x20) * 0x40 + (int)b);
        new_var = *(int *)(a + 0x24) * 0x40;
        va = *(int *)(bA + 0x20);
        bB = (char *)(new_var + (int)b);
        if (va != arg0) goto skipA;
        vb = *(int *)(bB + 0x20);
        if (vb != arg1) goto chkB;
        return bB;
    skipA:
        vb = *(int *)(bB + 0x20);
    chkB:
        if (vb != arg0) continue;
        if (va != arg1) continue;
        return bA;
    }
    return 0;
}
int get_wp_nearest_bridge_side_bridge(int arg0, int arg1)
{
    unsigned char *base = (unsigned char *)D_004F1EC0;
    char *b = (char *)D_004F31E0;
    int va, vb, new_var, i;
    char *bA, *bB, *a;
    for (i = 0; i < 0x1318; i += 0x34) {
        a = (char *)base + i;
        if (*(int *)(a + 0x0) == 0) continue;
        if (*(int *)(a + 0x18) == 0) continue;
        bA = (char *)(*(int *)(a + 0x20) * 0x40 + (int)b);
        new_var = *(int *)(a + 0x24) * 0x40;
        va = *(int *)(bA + 0x20);
        bB = (char *)(new_var + (int)b);
        if (va != arg0) goto skipA;
        vb = *(int *)(bB + 0x20);
        if (vb != arg1) goto chkB;
        return *(int *)(a + 0xC);
    skipA:
        vb = *(int *)(bB + 0x20);
    chkB:
        if (vb != arg0) continue;
        if (va != arg1) continue;
        return *(int *)(a + 0x8);
    }
    return 0;
}
extern char D_00554378[];
extern char D_0063A9E8[];
extern void __assert(void *a0, int a1, void *a2);
extern extern void debug_StdPrintfDummy();
extern void debug_assert(void *a0, int a1);

int direction_across_bridge(void *a0, int a1) {
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

WNODE *waybridge_between_group(int a0, int a1) {
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
char *bridge_waypoint_side_me(int me, int target) {
    WNODE *p = WayBridge_begin();
    while (p != 0) {
        char *eA = (char *)D_004F31E0 + p->i20 * 0x40;
        char *eB = (char *)D_004F31E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        if (a == me && *(int *)(eB + 0x20) == target) return eB;
        if (*(int *)(eB + 0x20) == me && a == target) return eA;
        p = WayBridge_next(p);
    }
    return 0;
}
WPElem *waypoint_connect_group_side_me(WPNode *a0, int a1) {
    WPElem *e = &D_004F31E0[a0->i20];
    if (e->f20 == a1) return e;
    e = &D_004F31E0[a0->i24];
    return e->f20 == a1 ? e : 0;
}
int bridge_waypoint_side_bridge(int a0, int a1) {
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
int waypoint_connect_group_side_bridge(WPNode *a0, int a1) {
    WPElem *e = &D_004F31E0[a0->i20];
    if (e->f20 == a1) return a0->i8;
    e = &D_004F31E0[a0->i24];
    if (e->f20 == a1) return a0->iC;
    return 0;
}
extern unsigned char D_004F1ED8[];

int NearestWgFromTarget(int cur, int end, WgAll *w) {
    int *dist = (int *)w->f14;
    int *prev = (int *)w->f10;
    while (1) {
        if (dist[cur] != 0x7FFFFFFF) {
            if (*(int *)(D_004F1ED8 + cur * 0x34) == 0) break;
        }
        if (cur == end) break;
        cur = prev[cur];
    }
    return cur;
}
int wpsort_compfnc(int a0, int a1) {
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
