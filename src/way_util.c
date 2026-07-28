#include "common.h"







extern void func_001AE8A0(int *self, int a1, int a2);
extern int D_006325B0;
extern int D_00631990;
extern char D_0028A520[];
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

INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_gid_ThreadVersion);

void visible_waypoint_of_all_except_temp(void) {}

INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_except_temp_ThreadVersion);

INCLUDE_ASM("asm/nonmatchings/src/way_util", ez_line);

INCLUDE_ASM("asm/nonmatchings/src/way_util", ez_circle);

INCLUDE_ASM("asm/nonmatchings/src/way_util", short_direction_between_wp);

INCLUDE_ASM("asm/nonmatchings/src/way_util", wgid_next);

void WayUtilWorkAlloc(void) {
    volatile int local[12];
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017904C);

void WayUtilWorkFree(void) {
    volatile int local[12];
}

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017905C);

INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path);

INCLUDE_ASM("asm/nonmatchings/src/way_util", shortest_path_ThreadVersion);

INCLUDE_ASM("asm/nonmatchings/src/way_util", GetWgAll);

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

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_by_lineseg);

INCLUDE_ASM("asm/nonmatchings/src/way_util", nearest_waypoint_by_lineseg_of_group_from_gobj);

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

INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_of_all_from_gobj);

INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint);

INCLUDE_ASM("asm/nonmatchings/src/way_util", visible_waypoint_from_gobj);

INCLUDE_ASM("asm/nonmatchings/src/way_util", get_wp_nearest_bridge_side_me);

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A9D4);

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017A9D8);

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017AA04);

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

INCLUDE_ASM("asm/nonmatchings/src/way_util", bridge_waypoint_side_bridge);

INCLUDE_ASM("asm/nonmatchings/src/way_util", waypoint_connect_group_side_bridge);

INCLUDE_ASM("asm/nonmatchings/src/way_util", NearestWgFromTarget);

INCLUDE_ASM("asm/nonmatchings/src/way_util", wpsort_compfnc);

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

INCLUDE_ASM("asm/nonmatchings/src/way_util", func_0017B230);

void func_0017B258(int bit_idx)
{
    D_0028A520[bit_idx >> 3] |= 1 << (bit_idx & 7);
}

void func_0017B288(int bit_idx)
{
    D_0028A520[bit_idx >> 3] &= ~(1 << (bit_idx & 7));
}

