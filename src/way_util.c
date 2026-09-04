#include "common.h"

typedef struct {
    int f0, f4, f8, fC, f10, f14, f18;
} WgAll;

typedef struct WNODE { char _p[0x20]; int i20; int i24; } WNODE;

typedef struct { int pad[8]; int f20; int pad2[7]; } WVTElem;
typedef struct { char pad[0x64]; int w64; } WVTObj;

typedef struct { int pad[8]; int f20; int pad2[7]; } WPElem;
typedef struct { int f0; int f4; int i8; int iC; int f10; int f14; int i18; int f1C; int i20; int i24; } WPNode;







extern void gamesysMemoryHandlerRead(int *self, int a1, int a2);
extern int D_006325B0;
extern int D_00631990;
extern unsigned char D_0028A520[];
extern void func_001AE1B8(int *self, int n, int a2);
typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;
typedef struct { int f0, f4; char *f8; char *fC; int f10, f14, f18, f1C, f20, f24, f28, f2C; int f30; } WayGrp;
extern WayGrp D_004CAEC0[];
extern unsigned char D_004CAED8[];
extern Nd D_004CC1E0[];
extern int D_00633874;
extern void sceVu0SubVector();
extern int WayPointList_begin();
extern float func_0016A2F8(int a0);
extern int WayPointList_next();
extern void iosMallocCheckLeak2();
INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_gid);

extern int GetNearNigePointN(void *a0, int a1, int a2, int a3);

int visible_waypoint_of_all_except_gid_ThreadVersion(void *a0, int a1, int a2) {
    return GetNearNigePointN(a0, a1, a2, 0);
}

void visible_waypoint_of_all_except_temp(void) {}

extern char D_00559CC0[];
extern extern void debug_StdPrintfDummy();
extern int DeleteWayGroup(int a0);

void visible_waypoint_of_all_except_temp_ThreadVersion(WVTObj *o) {
    if (o->w64 >= 0) {
        debug_StdPrintfDummy(D_00559CC0, o->w64);
        {
            WVTElem *e = &((WVTElem *)D_004CC1E0)[o->w64];
            DeleteWayGroup(e->f20);
        }
        o->w64 = -1;
    }
}

extern char D_00559DA0[];
extern int D_00632010;
extern int func_0013A0F8(int, int, const char *, int);
extern char *WayPoint_begin(void);
extern char *WayPoint_next(char *a0);
extern void sceVu0CopyVector(void *a0, void *a1);
extern void ClipWall(void *a0);
extern void ClipWallField(void *a0);
extern void qsort(void *base, int n, int size, int (*cmp)(float *, float *));
extern int func_0017B0D8(float *a, float *b);

typedef struct {
    float a[4];
    float b[4];
    char pad0[0x70 - 0x20];
    float f70;
    char pad1[0x88 - 0x74];
    int f88;
    char pad2[0xC0 - 0x8C];
} ClipBox;

typedef struct { char *node; float dist; } WayEnt;


static __inline__ float wb_dist(int *buf, int *pos, char *node)
{
    sceVu0SubVector(buf, (int *)(node + 0x10), pos);
    return func_0016A2F8((int)buf);
}

static __inline__ int wall_box_hit(ClipBox *cb, int *pos, char *node)
{
    sceVu0CopyVector(cb->a, pos);
    sceVu0CopyVector(cb->b, node + 0x10);
    cb->a[1] -= 75.0f;
    cb->b[1] -= 75.0f;
    ClipWall(cb);
    return cb->f88;
}

char *ez_line(int *arg0, int gid)
{
    int buf[4];
    ClipBox cb;
    WayEnt *list = (WayEnt *)func_0013A0F8(D_00632010, 0x898, D_00559DA0, 0x139);
    int n = 0;
    char *cur = WayPoint_begin();
    char *result;
    int i;
    if (cur != 0) {
        do {
            if (*(int *)(cur + 0x20) != gid) {
                list[n].dist = wb_dist(buf, arg0, cur);
                list[n].node = cur;
                n++;
            }
            cur = WayPoint_next(cur);
        } while (cur != 0);
    }
    qsort(list, n, 8, func_0017B0D8);
    cb.f70 = 0.0f;
    result = 0;
    i = 0;
    while (i < n) {
        cur = list[i].node;
        if (wall_box_hit(&cb, arg0, cur) == 0) {
            ClipWallField(&cb);
            if (cb.f88 == 0) {
                result = cur;
                break;
            }
        }
        i++;
    }
    iosMallocCheckLeak2(list);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", ez_circle);

char *short_direction_between_wp(int *arg0, int gid)
{
    int buf[4];
    ClipBox cb;
    WayEnt *list = (WayEnt *)func_0013A0F8(D_00632010, 0x898, D_00559DA0, 0x17F);
    int n = 0;
    char *cur = WayPoint_begin();
    char *result;
    int i;
    if (cur != 0) {
        do {
            int g = *(int *)(cur + 0x20);
            if (D_004CAEC0[g].f2C == 0 || g == gid) {
                list[n].dist = wb_dist(buf, arg0, cur);
                list[n].node = cur;
                n++;
            }
            cur = WayPoint_next(cur);
        } while (cur != 0);
    }
    qsort(list, n, 8, func_0017B0D8);
    cb.f70 = 0.0f;
    result = 0;
    i = 0;
    while (i < n) {
        cur = list[i].node;
        if (wall_box_hit(&cb, arg0, cur) == 0) {
            ClipWallField(&cb);
            if (cb.f88 == 0) {
                result = cur;
                break;
            }
        }
        i++;
    }
    iosMallocCheckLeak2(list);
    return result;
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", wgid_next);

void WayUtilWorkAlloc(void) {
    volatile int local[12];
}

void WayUtilWorkFree(void) {
    volatile int local[12];
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path);

INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path_ThreadVersion);

void *GetWgAll(void) {
    WgAll *p = (WgAll *)func_0013A0F8(D_00632010, 0x1C, D_00559DA0, 0x359);
    int *q;
    int i;
    p->f0 = func_0013A0F8(D_00632010, 0x5F, D_00559DA0, 0x35B);
    p->f4 = func_0013A0F8(D_00632010, 0x8A10, D_00559DA0, 0x35C);
    p->fC = func_0013A0F8(D_00632010, 0x17C, D_00559DA0, 0x35D);
    p->f10 = func_0013A0F8(D_00632010, 0x17C, D_00559DA0, 0x35E);
    p->f14 = func_0013A0F8(D_00632010, 0x17C, D_00559DA0, 0x35F);
    p->f18 = func_0013A0F8(D_00632010, 0x17C, D_00559DA0, 0x360);
    q = (int *)func_0013A0F8(D_00632010, 0x178, D_00559DA0, 0x362);
    p->f8 = (int)q;
    for (i = 0; i < 0x5E; i++) {
        q[i] = p->f4 + i * 0x178;
    }
    return p;
}

void set_check_wp(int *self)
{
    iosMallocCheckLeak2(self[0]);
    iosMallocCheckLeak2(self[2]);
    iosMallocCheckLeak2(self[1]);
    iosMallocCheckLeak2(self[3]);
    iosMallocCheckLeak2(self[4]);
    iosMallocCheckLeak2(self[5]);
    iosMallocCheckLeak2(self[6]);
    iosMallocCheckLeak2((int)self);
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", set_bridge);

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_of_group);

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint);

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_from_gobj);
INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_by_lineseg_of_group);

char *nearest_waypoint_by_lineseg(int *arg0, int handle)
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
            d = func_0016A2F8((int)buf);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = WayPointList_next(cur);
        } while (cur != 0);
    }
    return best;
}

char *nearest_waypoint_by_lineseg_of_group_from_gobj(int *a0) {
    int buf[4];
    char *t = WayPointList_begin(D_00633874);
    float bestDist = 100000.0f;
    char *best, *cur;
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            sceVu0SubVector(buf, (int *)(cur + 0x10), a0);
            d = func_0016A2F8((int)buf);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = WayPointList_next(cur);
        } while (cur != 0);
    }
    return best;
}

char *nearest_waypoint_by_lineseg_from_gobj(void *dobj)
{
    int mtx[4];
    int buf[4];
    int *pos;
    GetRootPosition(mtx, dobj);
    pos = mtx;
    {
        char *t = WayPointList_begin(D_00633874);
        float bestDist = 100000.0f;
        char *best, *cur;
        best = t;
        cur = best;
        if (best != 0) {
            do {
                float d = wb_dist(buf, pos, cur);
                if (d < bestDist) {
                    bestDist = d;
                    best = cur;
                }
                cur = WayPointList_next(cur);
            } while (cur != 0);
        }
        return best;
    }
}

extern float fzMagnitudeByLineSeg(void *a0, void *a1, void *a2);


char *waypoint_with_range(void *arg0, int gid)
{
    WayGrp *g = &D_004CAEC0[gid];
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
char *nearest_waypoint_of_all_except_group(void *arg0)
{
    WayGrp *g = &D_004CAEC0[D_00633874];
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

char *nearest_waypoint_of_all_not_bridge_except_group(void *dobj, int gid)
{
    int mtx[4];
    int *pos;
    GetRootPosition(mtx, dobj);
    pos = mtx;
    {
        float bestDist = 100000.0f;
        char *best = 0;
        WayGrp *g = &D_004CAEC0[gid];
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

char *nearest_waypoint_of_all(void *dobj)
{
    int mtx[4];
    int gid = D_00633874;
    int *pos;
    GetRootPosition(mtx, dobj);
    pos = mtx;
    {
        float bestDist = 100000.0f;
        char *best = 0;
        WayGrp *g = &D_004CAEC0[gid];
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

char *visible_waypoint_of_all(int *arg0, float thresh)
{
    int buf[4];
    char *node = WayPointList_begin(D_00633874);
    if (node == 0) goto ret0;
    do {
        sceVu0SubVector(buf, (int *)(node + 0x10), arg0);
        if (func_0016A2F8((int)buf) < thresh) {
            return node;
        }
        node = WayPointList_next(node);
    } while (node != 0);
ret0:
    return 0;
}

char *visible_waypoint_of_all_from_gobj(int *arg0, int a1) {
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
                d = func_0016A2F8((int)buf);
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

char *visible_waypoint(int *arg0, int gid) {
    int buf[4];
    char *t = WayPoint_begin();
    float bestDist = 100000.0f;
    char *best, *cur;
    best = t;
    cur = best;
    if (best != 0) {
        do {
            int g = *(int *)(cur + 0x20);
            if (g != gid && *(int *)(D_004CAED8 + g * 0x34) != 1) {
                float d;
                sceVu0SubVector(buf, (int *)(cur + 0x10), arg0);
                d = func_0016A2F8((int)buf);
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

char *visible_waypoint_from_gobj(int *a0) {
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
                d = func_0016A2F8((int)buf);
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

int get_wp_nearest_bridge_side_me(void *a0) {
    return ez_line(a0, -1);
}

extern void GetRootPosition(void *a0, void *a1);

void func_0017A9D8(void *a0) {
    int buf[4];
    GetRootPosition(buf, a0);
    ez_line(buf, -1);
}

char *func_0017AA08(int *arg0, int handle)
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
            d = func_0016A2F8((int)buf);
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

char *waybridge_between_group(void *dobj, int handle)
{
    int mtx[4];
    int buf[4];
    ClipBox cb;
    int *pos;
    float bestDist;
    char *best = 0;
    char *cur;
    GetRootPosition(mtx, dobj);
    bestDist = 100000.0f;
    cb.f70 = 50.0f;
    pos = mtx;
    cur = WayPointList_begin(handle);
    if (cur != 0) {
        do {
            float d = wb_dist(buf, pos, cur);
            if (d < bestDist) {
                if (wall_box_hit(&cb, pos, cur) == 0) {
                    bestDist = d;
                    best = cur;
                }
            }
            cur = WayPointList_next(cur);
        } while (cur != 0);
    }
    return best;
}

void *bridge_waypoint_side_me(int arg0, int arg1)
{
    unsigned char *base = (unsigned char *)D_004CAEC0;
    char *b = (char *)D_004CC1E0;
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
    unsigned char *base = (unsigned char *)D_004CAEC0;
    char *b = (char *)D_004CC1E0;
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

extern char D_00559E18[];
extern char D_00632598[];
extern void func_001AD768(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);

int direction_across_bridge(void *a0, int a1) {
    char *e1 = (char *)D_004CC1E0 + *(int *)((char *)a0 + 0x20) * 0x40;
    char *e2;
    if (*(int *)(e1 + 0x20) == a1) {
        return 1;
    }
    e2 = (char *)D_004CC1E0 + *(int *)((char *)a0 + 0x24) * 0x40;
    if (*(int *)(e2 + 0x20) != a1) {
        debug_StdPrintfDummy(D_00559E18);
        func_001AD768(D_00559DA0, 0x2C2);
        __assert(D_00559DA0, 0x2C2, D_00632598);
    }
    return 0;
}

extern WNODE *WayLengthOfGObj_GObj(WNODE *);
extern WNODE *WayLengthOfGObj_Pos(void);

WNODE *waypoint_connect_group_side_bridge(int a0, int a1) {
    WNODE *p = WayLengthOfGObj_Pos();
    while (p != 0) {
        char *eA = (char *)D_004CC1E0 + p->i20 * 0x40;
        char *eB = (char *)D_004CC1E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        int b = *(int *)(eB + 0x20);
        if (a == a0 && b == a1) {
            return p;
        }
        if (b == a0 && a == a1) {
            return p;
        }
        p = WayLengthOfGObj_GObj(p);
    }
    return 0;
}

char *NearestWgFromTarget(int me, int target) {
    WNODE *p = WayLengthOfGObj_Pos();
    while (p != 0) {
        char *eA = (char *)D_004CC1E0 + p->i20 * 0x40;
        char *eB = (char *)D_004CC1E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        if (a == me && *(int *)(eB + 0x20) == target) return eB;
        if (*(int *)(eB + 0x20) == me && a == target) return eA;
        p = WayLengthOfGObj_GObj(p);
    }
    return 0;
}

WPElem *waypoint_connect_group_side_me(WPNode *a0, int a1) {
    WPElem *e = &D_004CC1E0[a0->i20];
    if (e->f20 == a1) return e;
    e = &D_004CC1E0[a0->i24];
    return e->f20 == a1 ? e : 0;
}

int bridge_waypoint_side_bridge(int a0, int a1) {
    WPNode *p = (WPNode *)WayLengthOfGObj_Pos();
    while (p != 0) {
        char *eA = (char *)D_004CC1E0 + p->i20 * 0x40;
        char *eB = (char *)D_004CC1E0 + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        if (a == a0 && *(int *)(eB + 0x20) == a1) {
            return p->iC;
        }
        if (*(int *)(eB + 0x20) == a0 && a == a1) {
            return p->i8;
        }
        p = (WPNode *)WayLengthOfGObj_GObj((WNODE *)p);
    }
    return 0;
}

int func_0017B038(WPNode *a0, int a1) {
    WPElem *e = &D_004CC1E0[a0->i20];
    if (e->f20 == a1) return a0->i8;
    e = &D_004CC1E0[a0->i24];
    if (e->f20 == a1) return a0->iC;
    return 0;
}

int func_0017B080(int cur, int end, WgAll *w) {
    int *dist = (int *)w->f14;
    int *prev = (int *)w->f10;
    while (1) {
        if (dist[cur] != 0x7FFFFFFF) {
            if (*(int *)(D_004CAED8 + cur * 0x34) == 0) break;
        }
        if (cur == end) break;
        cur = prev[cur];
    }
    return cur;
}

int func_0017B0D8(float *a, float *b)
{
    if (a[1] < b[1]) return -1;
    if (b[1] < a[1]) return 1;
    return 0;
}

extern int func_0017B230(int bit_idx);
extern void func_0017B258(int bit_idx);
extern void memset(void *a0, int a1, int a2);
extern int D_006319A0;
extern int D_00632F80;
extern int D_00274ECC[];
extern int D_00280F78[];
extern void actBoyDitch3mExec(void);
extern void func_0019CD50(void);
extern void func_001ADBC0(void);
extern void Generator_Init(void);
extern void AttackGenerate(void);
extern void itouGflagLoad(void);

void func_0017B110(void)
{
    int v = func_0017B230(0x15A);
    memset(D_0028A520, 0, 0x2E);
    D_006319A0 = 0;
    if (v != 0) {
        func_0017B258(0x15A);
    }
    actBoyDitch3mExec();
    func_0019CD50();
    func_001ADBC0();
    Generator_Init();
    AttackGenerate();
    D_00274ECC[0] = 0;
    memset(D_00280F78, 0, 0x10);
    D_00632F80 = 0;
    return itouGflagLoad();
}

void func_0017B1A8(int a0)
{
    D_006325B0 = D_00631990;
    func_001AE1B8(a0, &D_006325B0, 4);
    return func_001AE1B8(a0, (int *)D_0028A520, 0x2E);
}

void func_0017B1F0(int a0) {
    gamesysMemoryHandlerRead(a0, &D_006325B0, 4);
    gamesysMemoryHandlerRead(a0, (int *)D_0028A520, 0x2E);
}

int func_0017B230(int bit_idx)
{
    return (D_0028A520[bit_idx >> 3] >> (bit_idx & 7)) & 1;
}

void func_0017B258(int bit_idx)
{
    D_0028A520[bit_idx >> 3] |= 1 << (bit_idx & 7);
}

void func_0017B288(int bit_idx)
{
    D_0028A520[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
}

