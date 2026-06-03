#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", InitWayPointSystem);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", CreateWayGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", CreateTempWayGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", DeleteWayGroup);

typedef struct { int w[13]; } WayRec;
extern WayRec D_004C6FF0[];

int CloseWayGroup(int a0) {
    return D_004C6FF0[a0].w[2];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", CreateWayPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_llf", AddWayPoint);

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
