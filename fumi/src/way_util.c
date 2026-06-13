#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_except_gid);

extern int GetNearNigePointN(void *a0, int a1, int a2, int a3);

int visible_waypoint_of_all_except_gid_ThreadVersion(void *a0, int a1, int a2) {
    return GetNearNigePointN(a0, a1, a2, 0);
}

void visible_waypoint_of_all_except_temp(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_except_temp_ThreadVersion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", ez_line);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", ez_circle);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", short_direction_between_wp);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", wgid_next);

void WayUtilWorkAlloc(void) {
    unsigned char work[0x30];
}

void WayUtilWorkFree(void) {
    unsigned char work[0x30];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", shortest_path);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", shortest_path_ThreadVersion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", GetWgAll);

extern void iosMallocCheckLeak2(int x);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", set_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_of_group);

extern char *CloseWayGroup(int handle);
extern char *CreateWayPoint(char *node);
extern void func_00240008(int *buf, int *p, int *q);
extern float func_00168128(int a0);

/* parked: needs real matching. See tough_nuts/nearest_waypoint_by_lineseg/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_of_group_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waypoint_with_range);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all_except_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all_not_bridge_except_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all);

extern int D_0062BB7C;

char *visible_waypoint_of_all(int *arg0, float thresh)
{
    int buf[4];
    char *node = CloseWayGroup(D_0062BB7C);
    if (node == 0) {
        return 0;
    }
    __asm__ __volatile__("" ::: "memory");
    do {
        func_00240008(buf, (int *)(node + 0x10), arg0);
        if (func_00168128((int)buf) < thresh) {
            return node;
        }
        node = CreateWayPoint(node);
    } while (node != 0);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_from_gobj);

extern int ez_line(void *a0, int a1);

int get_wp_nearest_bridge_side_me(void *a0) {
    return ez_line(a0, -1);
}

extern void GetRootMatrixByDObj(void *a0, void *a1);

int get_wp_nearest_bridge_side_bridge(void *a0) {
    int buf[4];
    GetRootMatrixByDObj(buf, a0);
    return ez_line(buf, -1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", direction_across_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waybridge_between_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", bridge_waypoint_side_me);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waypoint_connect_group_side_me);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", bridge_waypoint_side_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waypoint_connect_group_side_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", NearestWgFromTarget);

typedef struct { int pad[8]; int f20; int pad2[7]; } WPElem; /* 0x40 */
typedef struct { char pad[0x20]; int i20; int i24; } WPNode;
extern WPElem D_004C7CF0[];

WPElem *wpsort_compfnc(WPNode *a0, int a1) {
    WPElem *e = &D_004C7CF0[a0->i20];
    if (e->f20 == a1) return e;
    e = &D_004C7CF0[a0->i24];
    return e->f20 == a1 ? e : 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178B08);

typedef struct { char p0[8]; int f8; int fc; char p1[0x10]; int i20; int i24; } WPNode2;
int func_00178BB8(WPNode2 *a0, int a1) {
    WPElem *e = &D_004C7CF0[a0->i20];
    if (e->f20 == a1) return a0->f8;
    e = &D_004C7CF0[a0->i24];
    if (e->f20 == a1) return a0->fc;
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", func_00178C00);

int func_00178C58(int a0, int a1) {
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

extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
extern void func_00260568(void *a, int b, int c);
extern void actBoyDitch3mExec(void);
extern void func_0019A3C8(void);
extern void func_001AB158(void);
extern void Generator_Init(void);
extern void AttackGenerate(void);
extern void itouGflagLoad(void);
extern int D_00629CA0, D_0062B240;
extern int D_0027124C[3];
extern char D_00286890[];
extern char D_0027D2F8[];
void func_00178C90(void) {
    int r = func_00178DB0(0x159);
    func_00260568(D_00286890, 0, 0x2E);
    D_00629CA0 = 0;
    if (r != 0) {
        func_00178DD8(0x159);
    }
    actBoyDitch3mExec();
    func_0019A3C8();
    func_001AB158();
    Generator_Init();
    AttackGenerate();
    D_0027124C[0] = 0;
    func_00260568(D_0027D2F8, 0, 0x10);
    D_0062B240 = 0;
    itouGflagLoad();
}

extern int D_00629C90;
extern int D_0062A890;
extern char D_00286890[];
extern int func_001AB750(int a0, int *a1, int a2);

void func_00178D28(int a0)
{
    D_0062A890 = D_00629C90;
    func_001AB750(a0, &D_0062A890, 4);
    return func_001AB750(a0, (int *)D_00286890, 0x2E);
}

extern void func_001ABE38(int a0, int *a1, int a2);

void func_00178D70(int a0) {
    func_001ABE38(a0, &D_0062A890, 4);
    func_001ABE38(a0, (int *)D_00286890, 0x2E);
}


int func_00178DB0(int a0) {
    return (((unsigned char *)D_00286890)[a0 >> 3] >> (a0 & 7)) & 1;
}

void func_00178DD8(int a0) {
    D_00286890[a0 >> 3] |= 1 << (a0 & 7);
}

void func_00178E08(int a0) {
    D_00286890[a0 >> 3] &= ~(1 << (a0 & 7));
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_28;  /* 0x28 */
} S_004C7CF0;  /* stride 0x40 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_006C8B28;  /* stride 0x8 */

typedef struct {
    unsigned char      f_0;  /* 0x00 */
} S_00286890;

/* end struct shapes */
