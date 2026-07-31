#include "common.h"

typedef struct {
    int f0, f4, f8, fC, f10, f14, f18;
} WgAll;

typedef struct WNODE { char _p[0x20]; int i20; int i24; } WNODE;

typedef struct { int pad[8]; int f20; int pad2[7]; } WVTElem;
typedef struct { char pad[0x64]; int w64; } WVTObj;

typedef struct { int pad[8]; int f20; int pad2[7]; } WPElem;
typedef struct { char pad[0x20]; int i20; int i24; } WPNode;







extern void func_001AE8A0(int *self, int a1, int a2);
extern int D_006325B0;
extern int D_00631990;
extern unsigned char D_0028A520[];
extern void func_001AE1B8(int *self, int n, int a2);
typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;
extern unsigned char D_004CAEC0[];
extern Nd D_004CC1E0[];
extern int D_00633874;
extern void func_00243AE8();
extern int CloseWayGroup();
extern float func_0016A2F8(int a0);
extern int CreateWayPoint();
extern void iosMallocCheckLeak2();
INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_gid);

extern int GetNearNigePointN(void *a0, int a1, int a2, int a3);

int visible_waypoint_of_all_except_gid_ThreadVersion(void *a0, int a1, int a2) {
    return GetNearNigePointN(a0, a1, a2, 0);
}

void visible_waypoint_of_all_except_temp(void) {}

extern WVTElem D_004C7CF0_ve[] __asm__("D_004CC1E0");
extern char D_00559CC0[];
extern extern void debug_assertMessage();
extern int func_00205498(int a0);

void visible_waypoint_of_all_except_temp_ThreadVersion(WVTObj *o) {
    if (o->w64 >= 0) {
        debug_assertMessage(D_00559CC0, o->w64);
        {
            WVTElem *e = &D_004C7CF0_ve[o->w64];
            func_00205498(e->f20);
        }
        o->w64 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", ez_line);

INCLUDE_ASM("asm/nonmatchings/src/way_util", ez_circle);

INCLUDE_ASM("asm/nonmatchings/src/way_util", short_direction_between_wp);

INCLUDE_ASM("asm/nonmatchings/src/way_util", wgid_next);

void WayUtilWorkAlloc(void) {
    volatile int local[12];
}

void WayUtilWorkFree(void) {
    volatile int local[12];
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path);

INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path_ThreadVersion);

extern char D_00559DA0[];
extern int D_00632010;
extern int func_0013A0F8(int, int, const char *, int);

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

extern float D_00630E3C;

char *nearest_waypoint_by_lineseg(int *arg0, int handle)
{
    int buf[4];
    char *t = CloseWayGroup(handle);
    float bestDist = D_00630E3C;
    char *best, *cur;
    __asm__ __volatile__("" ::: "memory");
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            func_00243AE8(buf, (int *)(cur + 0x10), arg0);
            d = func_0016A2F8((int)buf);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = CreateWayPoint(cur);
        } while (cur != 0);
    }
    return best;
}

extern float D_00630E40;

char *nearest_waypoint_by_lineseg_of_group_from_gobj(int *a0) {
    int buf[4];
    char *t = CloseWayGroup(D_00633874);
    float bestDist = D_00630E40;
    char *best, *cur;
    __asm__ __volatile__("" ::: "memory");
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            func_00243AE8(buf, (int *)(cur + 0x10), a0);
            d = func_0016A2F8((int)buf);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = CreateWayPoint(cur);
        } while (cur != 0);
    }
    return best;
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_by_lineseg_from_gobj);

INCLUDE_ASM("asm/nonmatchings/src/way_util", waypoint_with_range);

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_of_all_except_group);

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_of_all_not_bridge_except_group);

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_of_all);

char *visible_waypoint_of_all(int *arg0, float thresh)
{
    int buf[4];
    char *node = CloseWayGroup(D_00633874);
    if (node == 0) {
        return 0;
    }
    __asm__ __volatile__("" ::: "memory");
    do {
        func_00243AE8(buf, (int *)(node + 0x10), arg0);
        if (func_0016A2F8((int)buf) < thresh) {
            return node;
        }
        node = CreateWayPoint(node);
    } while (node != 0);
    return 0;
}

extern char *CreateTempWayGroup(void);
extern float D_00630E58;
extern char *DeleteWayGroup(char *a0);

char *visible_waypoint_of_all_from_gobj(int *arg0, int a1) {
    int buf[4];
    char *t = CreateTempWayGroup();
    float bestDist = D_00630E58;
    char *best, *cur;
    __asm__ __volatile__("" ::: "memory");
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            if (*(int *)(cur + 0x20) != a1) {
                func_00243AE8(buf, (int *)(cur + 0x10), arg0);
                d = func_0016A2F8((int)buf);
                if (d < bestDist) {
                    bestDist = d;
                    best = cur;
                }
            }
            cur = DeleteWayGroup(cur);
        } while (cur != 0);
    }
    return best;
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint);

extern float D_00630E60;

char *visible_waypoint_from_gobj(int *a0) {
    int buf[4];
    int neg1 = -1;
    char *t = CreateTempWayGroup();
    float bestDist = D_00630E60;
    char *best, *cur;
    __asm__ __volatile__("" ::: "memory");
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            if (*(int *)(cur + 0x20) != neg1) {
                func_00243AE8(buf, (int *)(cur + 0x10), a0);
                d = func_0016A2F8((int)buf);
                if (d < bestDist) {
                    bestDist = d;
                    best = cur;
                }
            }
            cur = DeleteWayGroup(cur);
        } while (cur != 0);
    }
    return best;
}

extern int ez_line(void *a0, int a1);

int get_wp_nearest_bridge_side_me(void *a0) {
    return ez_line(a0, -1);
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A9D8);

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AA08);

INCLUDE_ASM("asm/nonmatchings/src/way_util", waybridge_between_group);

void *bridge_waypoint_side_me(int arg0, int arg1)
{
    unsigned char *base = D_004CAEC0;
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

int waypoint_connect_group_side_me(int arg0, int arg1)
{
    unsigned char *base = D_004CAEC0;
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

extern char D_00559DA0[];
extern char D_00559E18[];
extern char D_00632598[];
extern void func_001AD768(void *a0, int a1);
extern void func_00263FF0(void *a0, int a1, void *a2);
extern char wcf_c[] __asm__("D_004CC1E0");

int bridge_waypoint_side_bridge(void *a0, int a1) {
    char *e1 = wcf_c + *(int *)((char *)a0 + 0x20) * 0x40;
    char *e2;
    if (*(int *)(e1 + 0x20) == a1) {
        return 1;
    }
    e2 = wcf_c + *(int *)((char *)a0 + 0x24) * 0x40;
    if (*(int *)(e2 + 0x20) != a1) {
        debug_assertMessage(D_00559E18);
        func_001AD768(D_00559DA0, 0x2C2);
        func_00263FF0(D_00559DA0, 0x2C2, D_00632598);
    }
    return 0;
}

extern WNODE *WayLengthOfGObj_GObj(WNODE *);
extern WNODE *WayLengthOfGObj_Pos(void);

WNODE *waypoint_connect_group_side_bridge(int a0, int a1) {
    WNODE *p = WayLengthOfGObj_Pos();
    while (p != 0) {
        char *eA = wcf_c + p->i20 * 0x40;
        char *eB = wcf_c + p->i24 * 0x40;
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
        char *eA = wcf_c + p->i20 * 0x40;
        char *eB = wcf_c + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        if (a == me && *(int *)(eB + 0x20) == target) return eB;
        if (*(int *)(eB + 0x20) == me && a == target) return eA;
        p = WayLengthOfGObj_GObj(p);
    }
    return 0;
}

WPElem *wpsort_compfnc(WPNode *a0, int a1) {
    WPElem *e = &D_004CC1E0[a0->i20];
    if (e->f20 == a1) return e;
    e = &D_004CC1E0[a0->i24];
    return e->f20 == a1 ? e : 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AF88);

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017B038);

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017B080);

int func_0017B0D8(float *a, float *b)
{
    if (a[1] < b[1]) return -1;
    if (b[1] < a[1]) return 1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017B110);

void func_0017B1A8(int a0)
{
    D_006325B0 = D_00631990;
    func_001AE1B8(a0, &D_006325B0, 4);
    return func_001AE1B8(a0, (int *)D_0028A520, 0x2E);
}

void func_0017B1F0(int a0) {
    func_001AE8A0(a0, &D_006325B0, 4);
    func_001AE8A0(a0, (int *)D_0028A520, 0x2E);
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

