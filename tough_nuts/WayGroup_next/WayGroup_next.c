#include "common.h"

typedef struct { int w[13]; } WayRecInit;
extern WayRecInit D_004C6FBC[];
void *InitWayPointSystem(void) {
    WayRecInit *p = D_004C6FBC;
    WayRecInit *end = D_004C6FBC + 64;
    if (p == 0) goto ret0;
    if (p == end) goto ret0;
    for (p++; ; p++) {
        if (p->w[0] != 0 && p->w[6] != 0 && p->w[10] != 0) return p;
        if (p == end) break;
    }
ret0:
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", CreateWayGroup);

typedef struct { int w[16]; } WayGroup_CT;
extern WayGroup_CT D_004C7CB0[];

void *CreateTempWayGroup(void) {
    WayGroup_CT *p = D_004C7CB0;
    WayGroup_CT *end = D_004C7CB0 + 215;
    if (p == 0) goto ret0;
    if (p == end) goto ret0;
    for (p++;; p++) {
        if (p->w[0] != 0) return p;
        if (p == end) break;
    }
ret0:
    return 0;
}

typedef struct { int w[16]; } WayGroup_DW;
extern WayGroup_DW D_004CB270;

void *DeleteWayGroup(WayGroup_DW *a0) {
    WayGroup_DW *end = &D_004CB270;
    if (a0 == 0) goto ret0;
    if (a0 == end) goto ret0;
    for (a0++; ; a0++) {
        if (a0->w[0] != 0) return a0;
        if (a0 == end) break;
    }
ret0:
    return 0;
}

typedef struct { int w[13]; } WayRec;
extern WayRec D_004C6FF0[];

int CloseWayGroup(int a0) {
    return D_004C6FF0[a0].w[2];
}

/* Recovered logic:
 *     WayRec *e = &D_004C6FF0[a0[8]];
 *     int ret = 0;
 *     if (a0) { ret = a0[3]; if (a0[3] == e->w[2]) ret = 0; }
 *     return ret;
 * ee-gcc 2.9 only reproduces the ROM's $4-coalesced ret + eager element-ptr
 * via a do{}while(0) BB-split, which drags in LOOP_ALIGN (.p2align 3) and a
 * pad nop before the shared-return label (cannot be demoted without cflags).
 * The loop-free body below keeps gcc's natural (unpadded) epilogue. */
int CreateWayPoint(int *a0) {
    register int v __asm__("$4") = (int)a0;
    __asm__ (
        ".set noreorder\n\t"
        "daddu  $5, $4, $0\n\t"
        "lui    $2, %%hi(D_004C6FF0)\n\t"
        "lw     $3, 0x20($5)\n\t"
        "addiu  $4, $0, 0x34\n\t"
        "addiu  $2, $2, %%lo(D_004C6FF0)\n\t"
        "mult   $3, $3, $4\n\t"
        "addu   $3, $3, $2\n\t"
        "beqz   $5, 1f\n\t"
        " daddu $4, $0, $0\n\t"
        "lw     $4, 0xC($5)\n\t"
        "lw     $2, 0x8($3)\n\t"
        "xor    $2, $4, $2\n\t"
        "movz   $4, $0, $2\n\t"
        "1:\n\t"
        ".set reorder\n\t"
        : "+r"(v) : : "$2", "$3", "$5");
    return v;
}

extern char D_00613D40[];
extern void debug_assertMessage(char *p, int *self);

int AddWayPoint(int *self, int which) {
    if (self == 0) {
        return 0;
    }
    debug_assertMessage(D_00613D40, self);
    if (which == 0) {
        return self[0x8 / 4];
    }
    return self[0xC / 4];
}

void AddWayPointTop(int a0, int a1) {
    D_004C6FF0[a0].w[10] = a1;
}

int InsertWayPointAfter(int a0) {
    return D_004C6FF0[a0].w[10] != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", DeleteWayPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", WayGroup_begin);

extern void NearestEnemyFromGirl(void);
extern void debug_assertMessage();
extern void func_00202900(int);
extern void traceLine();
extern void *visible_waypoint_of_all(void *, float);
extern char D_004CB2B0[];
extern char D_006141A8[];
extern char D_006141B8[];
extern char D_0062DA08[];
extern int D_0062AF84;
extern int D_0062BB7C;
extern int D_0062BB80;
extern int D_0070BBFC[];

int WayGroup_next(void) {
    WayRec *s16 = &D_004C6FF0[D_0062BB7C];
    int flags;
    void *r;
    int a1;
    if (D_0062AF84 & 1) {
        traceLine(0x12, 0x36, 0xFF000000, D_006141A8);
        if (D_0062AF84 & 1) {
            traceLine(0x1A, 0x42, 0xFF808000, D_0062DA08, s16->w[4]);
        }
    }
    flags = D_0070BBFC[0];
    if (flags & 0x20) {
        r = visible_waypoint_of_all(D_004CB2B0, 60.0f);
        if (r == 0) {
            goto ret0;
        }
        a1 = *(int *)((char *)r + 0x4);
        D_0062BB80 = a1;
        if (a1 < 0) {
            goto ret0;
        }
        NearestEnemyFromGirl();
        if (s16->w[4] == 0) {
            func_00202900(D_0062BB7C);
        }
        debug_assertMessage(D_006141B8, D_0062BB80);
        goto ret0;
    }
    if (flags & 0x40) {
        return -1;
    }
ret0:
    return 0;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", WayBridge_begin);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
} S_004C6FF0;  /* stride 0x34 */

/* end struct shapes */
