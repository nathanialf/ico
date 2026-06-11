#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", InitWayPointSystem);

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

int CreateWayPoint(int *a0) {
    WayRec *e;
    int ret;
    e = &D_004C6FF0[a0[8]];
    do { ret = 0; } while (0);
    if (a0) {
        ret = a0[3];
        if (a0[3] == e->w[2]) ret = 0;
    }
    return ret;
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", WayGroup_next);

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
