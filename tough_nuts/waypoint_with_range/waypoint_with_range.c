#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_except_gid);

extern int GetNearNigePointN(void *a0, int a1, int a2, int a3);

int visible_waypoint_of_all_except_gid_ThreadVersion(void *a0, int a1, int a2) {
    return GetNearNigePointN(a0, a1, a2, 0);
}

void visible_waypoint_of_all_except_temp(void) {
}

extern char D_00553FB0[];
extern void debug_StdPrintfDummy();
extern int DeleteWayGroup(int a0);
typedef struct { int pad[8]; int f20; int pad2[7]; } WVTElem; /* 0x40 */
extern WVTElem D_004C7CF0_ve[] __asm__("D_004C7CF0");

typedef struct { char pad[0x64]; int w64; } WVTObj;

void visible_waypoint_of_all_except_temp_ThreadVersion(WVTObj *o) {
    if (o->w64 >= 0) {
        debug_StdPrintfDummy(D_00553FB0, o->w64);
        {
            WVTElem *e = &D_004C7CF0_ve[o->w64];
            DeleteWayGroup(e->f20);
        }
        o->w64 = -1;
    }
}


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

extern int iosFree(int, int, const char *, int);
extern char D_00554080[];
extern int D_0062A310;

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

typedef struct { int pad[8]; int f20; int pad2[7]; } WPElemG;          /* 0x40 */
typedef struct { char a[8]; int f8; int fc; char b[8]; int f18;
                 char c[4]; int i20; int i24; char d[12]; } WayRecG;    /* 0x34 */
extern WPElemG D_004C7CF0_g[] __asm__("D_004C7CF0");
extern WayRecG D_004C6FF0_g[] __asm__("D_004C6FF0");
extern void debug_StdPrintfDummy();
extern char D_00554128[];

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_from_gobj);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_of_group);

extern char *WayPointList_begin(int handle);
extern char *WayPointList_next(char *node);
extern void sceVu0SubVector(int *buf, int *p, int *q);
extern float func_00168128(int a0);

extern float D_00629128;

char *nearest_waypoint_by_lineseg(int *arg0, int handle)
{
    int buf[4];
    char *t = WayPointList_begin(handle);
    float bestDist = D_00629128;
    char *best, *cur;
    __asm__ __volatile__("" ::: "memory");
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            sceVu0SubVector(buf, (int *)(cur + 0x10), arg0);
            d = func_00168128((int)buf);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = WayPointList_next(cur);
        } while (cur != 0);
    }
    return best;
}




extern char *WayPointList_begin(int handle);
extern char *WayPointList_next(char *node);
extern void sceVu0SubVector(int *buf, int *p, int *q);
extern float func_00168128(int a0);
extern float D_0062912C;
extern int D_0062BB7C;

char *nearest_waypoint_by_lineseg_of_group_from_gobj(int *a0) {
    int buf[4];
    char *t = WayPointList_begin(D_0062BB7C);
    float bestDist = D_0062912C;
    char *best, *cur;
    __asm__ __volatile__("" ::: "memory");
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            sceVu0SubVector(buf, (int *)(cur + 0x10), a0);
            d = func_00168128((int)buf);
            if (d < bestDist) {
                bestDist = d;
                best = cur;
            }
            cur = WayPointList_next(cur);
        } while (cur != 0);
    }
    return best;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_by_lineseg_from_gobj);

extern float fzMagnitudeByLineSeg(void *a0, void *a1, void *a2);
extern float D_00629134;
extern char D_004C6FF0_wr[] __asm__("D_004C6FF0");

void *waypoint_with_range(void *arg0, int idx) {
    char *rec = D_004C6FF0_wr + idx * 0x34;
    char *node = *(char **)(rec + 0x8);
    float range = D_00629134;
    char *result = 0;
    char *nx = *(char **)(node + 0xC);
    __asm__ __volatile__("" ::: "memory");
    if (nx == 0 || nx == node) goto done;
    do {
        float d = fzMagnitudeByLineSeg(node + 0x10, nx + 0x10, arg0);
        if (d < range) {
            range = d;
            result = node;
        }
        node = *(char **)(node + 0xC);
        nx = *(char **)(node + 0xC);
    } while (nx != 0 && nx != node);
done:
    return result;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all_except_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all_not_bridge_except_group);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", nearest_waypoint_of_all);

extern int D_0062BB7C;

char *visible_waypoint_of_all(int *arg0, float thresh)
{
    int buf[4];
    char *node = WayPointList_begin(D_0062BB7C);
    if (node == 0) {
        return 0;
    }
    __asm__ __volatile__("" ::: "memory");
    do {
        sceVu0SubVector(buf, (int *)(node + 0x10), arg0);
        if (func_00168128((int)buf) < thresh) {
            return node;
        }
        node = WayPointList_next(node);
    } while (node != 0);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint_of_all_from_gobj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", visible_waypoint);

/* m2c scaffold from asm/aug6/nonmatchings/fumi/src/way_util/visible_waypoint_from_gobj.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern char *CreateTempWayGroup(void);
extern char *WayPoint_next(char *a0);
extern float D_0062914C;

char *visible_waypoint_from_gobj(int *a0) {
    int buf[4];
    int neg1 = -1;
    char *t = CreateTempWayGroup();
    float bestDist = D_0062914C;
    char *best, *cur;
    __asm__ __volatile__("" ::: "memory");
    best = t;
    cur = best;
    if (best != 0) {
        do {
            float d;
            if (*(int *)(cur + 0x20) != neg1) {
                sceVu0SubVector(buf, (int *)(cur + 0x10), a0);
                d = func_00168128((int)buf);
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

extern int ClipWallBoxStop(int *buf);
extern void sceVu0CopyVector(int *out, int *in);
extern float D_00629150;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", direction_across_bridge);


/* m2c scaffold from asm/aug6/nonmatchings/fumi/src/way_util/waybridge_between_group.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern float D_00629154;

typedef struct {
    float p0[4];                 /* 0x00 */
    float p1[4];                 /* 0x10 */
    char _pad20[0x70 - 0x20];    /* 0x20 */
    float radius;                /* 0x70 */
    char _pad74[0x88 - 0x74];    /* 0x74 */
    int result;                  /* 0x88 */
    char _pad8C[0xC0 - 0x8C];    /* 0x8C */
} WallBox;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_util", waybridge_between_group);


typedef struct {
    int f0;                  /* 0x0 */
    char _p1[0x18 - 0x4];
    int f18;                 /* 0x18 */
    char _p2[0x20 - 0x1c];
    int i20;                 /* 0x20 */
    int i24;                 /* 0x24 */
    char _p3[0x34 - 0x28];
} WayRecM;                   /* 0x34 */
extern WayRecM D_004C6FF0_m[] __asm__("D_004C6FF0");
extern char wcf_me[] __asm__("D_004C7CF0");

char *bridge_waypoint_side_me(int me, int target) {
    int p = (int)D_004C6FF0_m;
    int end = p + 0xD00;
    do {
        char *eA, *eB;
        int a;
        if (*(int *)p != 0 && *(int *)(p + 0x18) != 0) {
            eA = wcf_me + *(int *)(p + 0x20) * 0x40;
            eB = wcf_me + *(int *)(p + 0x24) * 0x40;
            a = *(int *)(eA + 0x20);
            if (a == me && *(int *)(eB + 0x20) == target) return eB;
            if (*(int *)(eB + 0x20) == me && a == target) return eA;
        }
        p += 0x34;
    } while (p < end);
    return 0;
}


int waypoint_connect_group_side_me(int me, int target) {
    int p = (int)D_004C6FF0_m;
    int end = p + 0xD00;
    do {
        char *eA, *eB;
        int a;
        if (*(int *)p != 0 && *(int *)(p + 0x18) != 0) {
            eA = wcf_me + *(int *)(p + 0x20) * 0x40;
            eB = wcf_me + *(int *)(p + 0x24) * 0x40;
            a = *(int *)(eA + 0x20);
            if (a == me && *(int *)(eB + 0x20) == target) return *(int *)(p + 0xC);
            if (*(int *)(eB + 0x20) == me && a == target) return *(int *)(p + 0x8);
        }
        p += 0x34;
    } while (p < end);
    return 0;
}


extern char wcf_c[] __asm__("D_004C7CF0");
extern char D_005540F8[];
extern char D_00554080[];
extern char D_0062C6F8[];
extern void debug_StdPrintfDummy();
extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);

int bridge_waypoint_side_bridge(void *a0, int a1) {
    char *e1 = wcf_c + *(int *)((char *)a0 + 0x20) * 0x40;
    char *e2;
    if (*(int *)(e1 + 0x20) == a1) {
        return 1;
    }
    e2 = wcf_c + *(int *)((char *)a0 + 0x24) * 0x40;
    if (*(int *)(e2 + 0x20) != a1) {
        debug_StdPrintfDummy(D_005540F8);
        func_001AAD00(D_00554080, 0x2C2);
        __assert(D_00554080, 0x2C2, D_0062C6F8);
    }
    return 0;
}

typedef struct WNODE { char _p[0x20]; int i20; int i24; } WNODE;
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


typedef struct { int pad[8]; int f20; int pad2[7]; } WPElem; /* 0x40 */
typedef struct { char pad[0x20]; int i20; int i24; } WPNode;
extern WPElem D_004C7CF0[];

WPElem *wpsort_compfnc(WPNode *a0, int a1) {
    WPElem *e = &D_004C7CF0[a0->i20];
    if (e->f20 == a1) return e;
    e = &D_004C7CF0[a0->i24];
    return e->f20 == a1 ? e : 0;
}

int func_00178B08(int me, int target) {
    WNODE *p = WayLengthOfGObj_Pos();
    while (p != 0) {
        char *eA = wcf_c + p->i20 * 0x40;
        char *eB = wcf_c + p->i24 * 0x40;
        int a = *(int *)(eA + 0x20);
        if (a == me && *(int *)(eB + 0x20) == target) return *(int *)((char *)p + 0xC);
        if (*(int *)(eB + 0x20) == me && a == target) return *(int *)((char *)p + 0x8);
        p = WayLengthOfGObj_GObj(p);
    }
    return 0;
}


typedef struct { char p0[8]; int f8; int fc; char p1[0x10]; int i20; int i24; } WPNode2;
int func_00178BB8(WPNode2 *a0, int a1) {
    WPElem *e = &D_004C7CF0[a0->i20];
    if (e->f20 == a1) return a0->f8;
    e = &D_004C7CF0[a0->i24];
    if (e->f20 == a1) return a0->fc;
    return 0;
}

extern char D_004C7008[];

int func_00178C00(int idx, int last, int *ctx) {
    int *arr14 = (int *)ctx[0x14 / 4];
    int *arr10 = (int *)ctx[0x10 / 4];
    while (1) {
        if (arr14[idx] != 0x7FFFFFFF) {
            if (*(int *)(D_004C7008 + idx * 0x34) == 0) {
                break;
            }
        }
        if (idx == last) {
            break;
        }
        idx = arr10[idx];
    }
    return idx;
}

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
extern void memset(void *a, int b, int c);
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
    memset(D_00286890, 0, 0x2E);
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
    memset(D_0027D2F8, 0, 0x10);
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

extern void gamesysMemoryHandlerRead(int a0, int *a1, int a2);

void func_00178D70(int a0) {
    gamesysMemoryHandlerRead(a0, &D_0062A890, 4);
    gamesysMemoryHandlerRead(a0, (int *)D_00286890, 0x2E);
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
